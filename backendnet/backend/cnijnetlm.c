/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2009-2012
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


// Linux System Header
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/stat.h>
#include <poll.h>

// CUPS Header
#include <cups/cups.h>
#include <cups/ppd.h>
#include <cups/ipp.h>

/* lgmon command length		 */
#define	LGMON_CMD_BASE_STR				PROG_PATH "/cnijnetprn"

int     g_pid = -1;
int     g_signal = 0;

/* Messagess table */
enum {
	CANON_STS_SUCCESS,
	CANON_STS_NG	 ,
	CANON_STS_PIPE_ERR,
	CANON_STS_FORK_ERR,
	CANON_STS_LGMON_EXEC_ERR,
	CANON_STS_PRINT_CANCEL,
	CANON_STS_CUPS_ERR,
	CANON_STS_DEFAULT
} ;

// Header file for CANON
#include "cnijnetlm.h"

/*--------- Prototypes.	*/
static void lgmon_sigterm_handler( int ) ;
static int  net_lgmon_exec( int, int, FILE *, int , char *  , char *  , char * , char * ) ;
static void data_write( int, FILE *, int , int ) ;
static int is_exist_option(char * , char *);

/*----------------------------------------------------------------------------*
 * This function is a main function for calling a monitor process. 
 */

int 	_net_canon_bj( int argc, int mode, FILE *fp, int copies, char* option, char *resource, char *user, char *document)
{
#if defined(HAVE_SIGACTION) && !defined(HAVE_SIGSET)
    struct  sigaction action;			/* Actions for POSIX signals        */
#endif /* HAVE_SIGACTION && !HAVE_SIGSET */

	int sts ;									/* function status		*/

/*
* When a signal (SIGTERM/SIGPIPE) is received, printing process
* and the lgmon process will be terminated.
*/


#ifdef HAVE_SIGSET
	sigset(SIGPIPE, SIG_IGN);
	sigset(SIGTERM, lgmon_sigterm_handler);
#elif defined(HAVE_SIGACTION)
	memset(&action, 0, sizeof(action));
	action.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &action, NULL);

	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGTERM);
	
	action.sa_handler = lgmon_sigterm_handler;
	sigaction(SIGTERM, &action, NULL);
#else
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTERM, lgmon_sigterm_handler);
#endif
	
	/* Clear printer status */
	setbuf(stderr, NULL);
	//fprintf( stderr, "INFO: \n" );
	
	sts = net_lgmon_exec( argc, mode, fp, copies, resource, user, document, option);
	
	/* Clear printer status */
	//fprintf( stderr, "INFO: \n" );
	
	return( sts ) ;
}


/*----------------------------------------------------------------------------*
 * When a signal (SIGTERM) is received, printing process
 * and the lgmon process will be terminated.
 */
static
void lgmon_sigterm_handler(int sig_code)
{
	/* Clear printer status */
	fprintf( stderr, "INFO: \n" );

	if( g_pid > 0 )
		kill(g_pid, SIGTERM);
	
	g_signal = 1;
}


/*----------------------------------------------------------------------------*
 * This function is carrying out processing which calls a lgmon process. 
 * And pipes create.
 *
 * Attention: param(char *command) is unused.
 */
static
int		net_lgmon_exec( int argc, int mode, FILE *fp, int copies , char *resource, char *user, char *document, char *options ) {
	int		rtn ;								/* return status buffer		*/
	int		pipe_fds[2] ;						/* pipe disripter			*/
	
	char model_number[64];
	int is_direct=0;
	
	ppd_file_t *ppd;
	ppd_attr_t *attr;

	if	( pipe(pipe_fds) < 0 ) {				/* pipe cleate				*/
		return( CANON_STS_PIPE_ERR ) ;
	}
	
	/* check direct option */
	if (is_exist_option(options, CNBJ_OPTION_DIRECT) >= 0){
		is_direct = 1;
	} else {
		is_direct = 0;
	}
	
	g_pid = fork() ;							/* fork()					*/

	if	( g_pid == -1 ) {    		          	/* fork() error 			*/
		return( CANON_STS_FORK_ERR ) ;
	}
	else if ( g_pid == 0 ) {					/* child process 			*/
		static	int		cmd_argv_cnt = 0 ;		/* argument counter			*/
		static	char	*cmd_argv[16] ;			/* command argument beffer	*/
		static	char	str_msg[128] ;			/* message beffer			*/
		memset( str_msg, 0x00, sizeof(str_msg) ) ;
		
		if (mode == CNNET_MODE_SEARCH){
			close(0);
			dup2(pipe_fds[0], 0);
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			
			/* set argv */
			cmd_argv[cmd_argv_cnt++] = "--search";
			cmd_argv[cmd_argv_cnt++] = "broadcast";
			cmd_argv[cmd_argv_cnt++] = NULL ;
		} else {
			
			/* get ppd file */
			memset(model_number, 0x00, sizeof(model_number));
			ppd = ppdOpenFile(getenv("PPD"));
			if (ppd != NULL){
				attr = ppdFindAttr(ppd, "cupsModelNumber", NULL);
				if (attr != NULL){
					snprintf(model_number, sizeof(model_number)-1, "%s", attr->value);
				}
				ppdClose(ppd);
			} else {
				fprintf(stderr, "ERROR: cannot open ppd file.\n");
				return CANON_STS_CUPS_ERR;
			}
			if (model_number[0] == '\0'){
				fprintf(stderr, "ERROR: cannot specify model number.\n");
				return CANON_STS_CUPS_ERR;
			}
			
			close(0);
			close(1);
			dup2(pipe_fds[0], 0);
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			
			/* set argv */
			cmd_argv[cmd_argv_cnt++] = "--macaddr";
			cmd_argv[cmd_argv_cnt++] = resource;
			cmd_argv[cmd_argv_cnt++] = "--user";
			cmd_argv[cmd_argv_cnt++] = user;
			cmd_argv[cmd_argv_cnt++] = "--job";
			cmd_argv[cmd_argv_cnt++] = document;
			cmd_argv[cmd_argv_cnt++] = "--model";
			cmd_argv[cmd_argv_cnt++] = model_number;
			if (is_direct == 1) cmd_argv[cmd_argv_cnt++] = "--direct";
			
			cmd_argv[cmd_argv_cnt++] = NULL ;
		}
		rtn = execvp ( LGMON_CMD_BASE_STR, cmd_argv ) ;/* lgmon exec 				*/
		
		if  ( rtn == -1 ) {						/* error					*/
			switch( errno ) {
				case    ENOENT :				/* Command not found 		*/
					fprintf( stderr, "ERROR: Command not found \n") ;
					break ;
				case    EACCES :				/* Command Permission denied*/
					fprintf( stderr, "ERROR: Command Permission denied \n") ;
					break ;
				default :
					fprintf( stderr, "ERROR: Please refer to <asm/errno.h>\n") ;
			}
			return( CANON_STS_NG ) ;
		}
	}
	else {										/* parents process			*/
		close( pipe_fds[0] ) ;					/* pipe(in) close           */
		if (mode != CNNET_MODE_SEARCH){
			data_write( argc, fp, copies, pipe_fds[1] ) ;	/* data write 	*/
		}
		close( pipe_fds[1] ) ;					/* pipe(out) close          */
	}
	
	
	if	( g_pid > 0 ) {				/* if child process has started....	*/
		int child_status = 0;
		pid_t __attribute__ ((unused)) child_pid = 0;
		
		// waitpid( g_pid, NULL, 0) ;		/* child process wait		*/
		child_pid = wait(&child_status);
		
		if (!WIFEXITED(child_status)){
			return( CANON_STS_NG ) ;
		}
		rtn = WEXITSTATUS(child_status);
		
		if (rtn == 0){
			return( CANON_STS_SUCCESS ) ;
		} else {
			return( CANON_STS_NG ) ;
		}
	}
	
	return( CANON_STS_SUCCESS ) ;
}

/*----------------------------------------------------------------------------*
 *  This function checks wether option is exist or not.
 */
static int is_exist_option(char *options, char *target)
{
	cups_option_t *p_opt = NULL;
	int num_opt = 0; 
	int i,result = -1;
	
	if( (num_opt = cupsParseOptions(options, 0, &p_opt)) > 0 ){
		for( i=0; i< num_opt; i++ ){
			/* CNBjDirect */	
			if( strcmp( p_opt[i].name, target)== 0){
				result = 0;
				break;
			}
		}
	}
	cupsFreeOptions( num_opt, p_opt );
	
	return result;
}

/*----------------------------------------------------------------------------*
 *  This function writes data in a device (printer).
 */
static
void	data_write( int argc, FILE *fp, int copies, int pipe_fds )
{
	char		buffer[1024];				/* Output buffer	*/
	int 		tmp_mask, tmp_fd;
	char 		*tmp_dir = NULL, tmp_base[]= "/tmp", tmp_file[256];
	
	FILE		*tempfp;
	int 		nbytes, wbytes;
	long		read_position=0, polltime=0;
	
	// create temp file
	if ((tmp_dir=getenv("TMPDIR")) == NULL){
		if ((tmp_dir=getenv("TMP")) == NULL) tmp_dir = tmp_base;
	}
	memset(tmp_file, 0x00, sizeof(tmp_file));
	strncpy(tmp_file, tmp_dir, sizeof(tmp_file)-1);
	strncat(tmp_file, "/cnijnetXXXXXX", sizeof(tmp_file)-1);
	
	tmp_mask = umask(077);
	tmp_fd   = mkstemp(tmp_file);
	umask(tmp_mask);
	
	if (tmp_fd == -1){
		perror("ERROR: cannot create temporary file.");
		goto error;
	}
	
	// set file descriptor
	if ((tempfp=fdopen(tmp_fd, "w+"))==NULL){
		perror("ERROR: cannot open temporary file.");
		goto error;
	}
	
	// hide temporary file
	unlink(tmp_file);
	
	polltime = 0;
	while (copies > 0){
		
		copies--;
		if  ( fp != stdin ) {
			rewind(fp);
		}
		
		while (g_signal == 0) {
			
			nbytes = fread(buffer, 1, sizeof(buffer), fp);
			if (nbytes <= 0){
				polltime = 1;
				fseek(tempfp, 0, SEEK_END);
				if (read_position == ftell(tempfp)) break;
			} else {
				wbytes = 0;
				fseek(tempfp, 0, SEEK_END);
				while (wbytes < nbytes && g_signal == 0){
					wbytes += fwrite(buffer, 1, nbytes-wbytes, tempfp);
				}
			}
			
			struct pollfd fds;
			int __attribute__ ((unused)) pollst;
			
			fds.fd = pipe_fds;
			fds.events = POLLOUT;
			
			pollst = poll(&fds, 1, polltime);
			
			if (fds.revents & POLLOUT){
				fseek(tempfp, read_position, SEEK_SET);
				nbytes = fread(buffer, 1, sizeof(buffer), tempfp);
				
				// write to pipe
				if ((wbytes = write(pipe_fds, buffer, nbytes)) < 0){
					break;
				}
				read_position += wbytes;
			}
		}
	}
	
	
error:
	if( g_signal != 0 ) {
		// read all
		while (fread(buffer, 1, sizeof(buffer), fp) > 0);
		// flush
		fflush(fp);
	}
}

