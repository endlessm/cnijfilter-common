/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2013
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

// CUPS Header
#include <cups/cups.h>
#include <cups/ipp.h>
#include <cups/ppd.h>

// Header file for CANON
#include "cnij_backend_common.h"
#include "cnij_common_function.h"


/*--------- Prototypes.	*/
/* _canon_bj() local function */
static void lgmon_sigterm_handler( int ) ;
static int  get_model_name( char * ) ;
static int  make_lgmon_command( char *, char*, int, short ) ;		/* Ver.3.20 add param */
static int  lgmon_exec( int, FILE *, int , char *, int ) ;
static void data_write( int, FILE *, int , int ) ;

static int check_options( FILE**, short*, int*, char*, char*, short* );		/* Ver.3.20 add param */
static int write_to_bsccfile( char*, char*, short );

//* Functions *****************************************************************
/*----------------------------------------------------------------------------*
 * This function is a main function for calling a monitor process. 
 */

int 	_canon_bj( int argc, FILE *fp, int fd, int copies, char* option )
{
#if defined(HAVE_SIGACTION) && !defined(HAVE_SIGSET)
    struct  sigaction action;			/* Actions for POSIX signals        */
#endif /* HAVE_SIGACTION && !HAVE_SIGSET */
    struct  termios opts;				/* Parallel port options            */

	char	lgmon_command[LGMON_CMD_MAX_STR_LEN] ;  /* command buffer		*/
	int		sts ;									/* function status		*/

	short is_setregi=0;
	short is_direct=0;		/* Ver.3.20 */
	char tmp_file[256];
	int utilbyte = 0;

/*
* Set any options provided...
*/

    tcgetattr(fd, &opts);

    opts.c_lflag &= ~(ICANON | ECHO | ISIG);    /* Raw mode					*/
    /**** No options supported yet ****/

    tcsetattr(fd, TCSANOW, &opts);

/*
* When a signal (SIGTERM) is received, printing process
* and the lgmon process will be terminated.
*/

#ifdef HAVE_SIGSET
	sigset(SIGTERM, lgmon_sigterm_handler);
#elif defined(HAVE_SIGACTION)
	memset(&action, 0, sizeof(action));
	sigemptyset(&action.sa_mask);
	action.sa_handler = lgmon_sigterm_handler;
	sigaction(SIGTERM, &action, NULL);
#else
	signal(SIGTERM, lgmon_sigterm_handler);
#endif

	if( option != NULL )
		check_options( &fp, &is_setregi, &utilbyte, tmp_file, option, &is_direct );	/* Ver.3.20 add param */

	sts = make_lgmon_command( lgmon_command, option, utilbyte, is_direct ) ;		/* Ver.3.20 */

	if	( sts == CANON_STS_SUCCESS ) {
		/* Clear printer status */
		fprintf( stderr, "INFO: \n" );

		sts = lgmon_exec( argc, fp, fd, lgmon_command, copies ) ; 
	}
	if  ( sts != CANON_STS_SUCCESS ) {			/* status check				*/
												/* error					*/
		fprintf( stderr, "%s %s %s\n",  message_str_base[ERROR_MASSAGE],
                                        sts_message_str[CANON_STS_DEFAULT],
                                        sts_message_str[sts] ) ;
	}
	else {
		/* Clear printer status */
		fprintf( stderr, "INFO: \n" );
	}

	if( is_setregi ){
			fclose(fp);
			unlink(tmp_file);
	}

	return( sts ) ;
}


/*----------------------------------------------------------------------------*
 * When a signal (SIGTERM) is received, printing process
 * and the lgmon process will be terminated.
 */
static
void lgmon_sigterm_handler(int sig_code)
{
	if( g_pid > 0 )
		kill(g_pid, SIGTERM);

	g_signal = 1;
}

/*----------------------------------------------------------------------------*
 * This function making the lgmon command by the model of a printer.
 */

static
int	make_lgmon_command( char *command, char *option, int utilbyte, short is_direct )	/* Ver.3.20 add param */
{
	char		model_name[MODEL_NAME_STR_LEN] ;
	int			status = CANON_STS_SUCCESS ;
	/* Ver.3.20 */
	short		add_direct = 0;
	char		*p_ppd_name = getenv("PPD");
	ppd_file_t	*p_ppd;

	/* Ver.3.20 */
	add_direct = is_direct;
	if( (p_ppd = ppdOpenFile(p_ppd_name)) == NULL )
		return CANON_STS_NG;
	
	if( p_ppd->model_number < 356 ) add_direct = 0;
	fprintf(stderr,"DEBUG: (cnijusb)p_ppd->model_number=(%d)\n",p_ppd->model_number);
	ppdClose(p_ppd);

										/* model name buffer initialization */
	memset( model_name, 0x00, sizeof( model_name ) ) ;

										/* model neme get 					*/
	if	( ( status = get_model_name( model_name ) ) == CANON_STS_SUCCESS ) { 

										/* making lgmon command 			*/
		if( utilbyte > 0 ){
			if( add_direct == 1 ){		/* Ver.3.20 */
				sprintf( command, "%s%s %s %s %s %s %d",	LGMON_CMD_BASE_STR,
					 model_name,
					 LGMON_CMD_GUI_OPTIN_STR,
					 LGMON_CMD_CUPS_OPTIN_STR,
					 LGMON_CMD_DIRECT_OPTIN_STR,
					 LGMON_CMD_UTIL_OPTIN_STR,
					 utilbyte) ;
			}
			else{
				sprintf( command, "%s%s %s %s %s %d",	LGMON_CMD_BASE_STR,
					 model_name,
					 LGMON_CMD_GUI_OPTIN_STR,
					 LGMON_CMD_CUPS_OPTIN_STR,
					 LGMON_CMD_UTIL_OPTIN_STR,
					 utilbyte) ;	
			}
		}
		else{		/* in this case, CNBjDirect is never specified. */
			sprintf( command, "%s%s %s %s",	LGMON_CMD_BASE_STR,
					 model_name, LGMON_CMD_GUI_OPTIN_STR,
					 LGMON_CMD_CUPS_OPTIN_STR) ;
		}
	}
	return( status ) ;
}


/*----------------------------------------------------------------------------*
 * This function is carrying out processing which acquires 
 * the model name of a device (printer) from the product key of a PPD file.
 */
static
int     get_model_name( char *model_name )
{
	ppd_file_t	*p_file  ;
	int	status = CANON_STS_SUCCESS ;

									/* ppd file key get 					*/
	if  ( ( p_file = ppdOpenFile( getenv( "PPD" ) ) ) != NULL ) {
									/* product key length check				*/
		if  ( strlen( p_file->product ) > 0 ) {
			char product[MODEL_NAME_STR_LEN];
			char *p_product;
			char *p_tail;

			memset( product, 0, MODEL_NAME_STR_LEN );
			strncpy( product, p_file->product, MODEL_NAME_STR_LEN - 1 ) ;
			p_product = product;

			while( *p_product == '(' )
				p_product++;
			p_tail = p_product;
			while( *p_tail != ')' && *p_tail != '\0' )
				p_tail++;
			*p_tail = '\0';
			strcpy( model_name, p_product ) ;
		}
		else { 						/* product key (*products:) is not set	*/
			status = CANON_STS_PPD_KEY_SET_ERR ;
		}
		ppdClose( p_file ) ;
	}
	else {							/* ppd file open eror	r				*/ 
			status = CANON_STS_PPD_FILE_OPEN_ERR ;
	}

	return( status ) ;
}


/*----------------------------------------------------------------------------*
 * This function is carrying out processing which calls a lgmon process. 
 * And pipes create.
 */
static
int		lgmon_exec( int argc, FILE *fp, int fd, char *command, int copies  ) {
	int		rtn ;								/* return status buffer		*/
	int		pipe_fds[2] ;						/* pipe disripter			*/

	if	( pipe(pipe_fds) < 0 ) {				/* pipe cleate				*/
		return( CANON_STS_PIPE_ERR ) ;
	}

	g_pid = fork() ;							/* fork()					*/

	if	( g_pid == -1 ) {    		          	/* fork() error 			*/
		return( CANON_STS_FORK_ERR ) ;
	}
	else if ( g_pid == 0 ) {					/* child process 			*/
		static	int		cmd_argv_cnt = 0 ;		/* argument counter			*/
		static	char	*cmd_argv[4] ;			/* command argument beffer	*/
		static  char	*cmd_sh_path = "/bin/sh";	/* shell path			*/
		static	char	str_msg[128] ;			/* message beffer			*/
		memset( str_msg, 0x00, sizeof(str_msg) ) ;

		close( 0 ) ;							/* stdin close				*/
		close( 1 ) ;							/* stdout close				*/
		dup2( pipe_fds[0], 0 ) ;				/* pipe cleate				*/
		dup2( fd, 1 ) ;							/* stdout to device			*/
		close( fd ) ;							/* device fd close			*/
		close( pipe_fds[0] ) ;					/* pipe(in) close			*/
		close( pipe_fds[1] ) ;					/* pipe(out) close			*/

		cmd_argv[cmd_argv_cnt++] = "sh" ;		/* create lgmon command 	*/
		cmd_argv[cmd_argv_cnt++] = "-c" ;
		cmd_argv[cmd_argv_cnt++] = (char *)command ;
		cmd_argv[cmd_argv_cnt++] = NULL ;

		fprintf( stderr, "%s(Canon) langage moniter[%s] start!\n",
                       message_str_base[DEBUG_MESSAGE], cmd_argv[2] ) ;

   		rtn = execvp ( cmd_sh_path, cmd_argv ) ;/* lgmon exec 				*/

		if  ( rtn == -1 ) {						/* error					*/
			switch( errno ) {
				case    ENOENT :				/* Command not found 		*/
					strcpy( str_msg, "Command not found" ) ;
					break ;
				case    EACCES :				/* Command Permission denied*/
					strcpy( str_msg, "Command Permission denied" ) ;
					break ;
				default :
					strcpy( str_msg, "Please refer to <asm/errno.h>" ) ;
			}
			fprintf( stderr, "%s %s %s(errno=%d[%s])\n",
								message_str_base[ERROR_MASSAGE],
          	                    sts_message_str[CANON_STS_DEFAULT],
          	                    sts_message_str[CANON_STS_LGMON_EXEC_ERR],
         	                    errno, str_msg ) ;
			exit(0) ;
		}
	}
	else {										/* parents process			*/
		close( pipe_fds[0] ) ;					/* pipe(in) close           */
		data_write( argc, fp, copies, pipe_fds[1] ) ;		/* data write 	*/
		close( pipe_fds[1] ) ;					/* pipe(out) close          */

	}


	if	( g_pid > 0 ) {				/* if child process has started....	*/
		waitpid( g_pid, NULL, 0) ;		/* child process wait		*/
	}

	return( CANON_STS_SUCCESS ) ;
}

/*----------------------------------------------------------------------------*
 *  This function writes data in a device (printer).
 */
static
void	data_write( int argc, FILE *fp, int copies, int pipe_fds )
{

	int			wbytes;     				/* Number of bytes written		*/
	size_t		nbytes,     				/* Number of bytes read			*/
				tbytes;						/* Total number of bytes written*/
	char		buffer[LGMON_DATA_WRITE_STR_LEN],		/* Output buffer	*/
				*bufptr;    				/* Pointer into buffer			*/

	while (copies > 0) {

		copies --;

 		if  ( fp != stdin ) {
			/*---------------------------------------------------------------*
			*	mixture of the printer status by lgmon is prevented.
			*
			fputs( "PAGE: 1 1\n", stderr ) ;
			-----------------------------------------------------------------*/
			rewind(fp);
		}

		tbytes = 0;

		/*
		*	data read
		*/
		while ((nbytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {

			if( g_signal != 0 )			/* signal(SIGTERM) writing end. */
				break;

			/*
			* Write the print data to the printer...
			*/
			tbytes += nbytes;
			bufptr = buffer;

			while (nbytes > 0) {
				if ((wbytes = write(pipe_fds, bufptr, nbytes)) < 0)
					if (errno == ENOTTY)			/* retry. 				*/
						wbytes = write(pipe_fds, bufptr, nbytes);

				if (wbytes < 0) {					/* write error			*/
					perror("ERROR: Unable to send print file to printer");
					break;
				}

				nbytes -= wbytes;
				bufptr += wbytes;

				if( g_signal != 0 )		/* signal(SIGTERM) writing end. */
					break;
			}

			/*---------------------------------------------------------------*
			*	mixture of the printer status by lgmon is prevented.
			*
			if (argc > 6) {
				fprintf(stderr, "INFO: Sending print file, %lu bytes...\n", (unsigned long)tbytes);
			}
			-----------------------------------------------------------------*/
		}

		if( g_signal != 0 )				/* signal(SIGTERM) writing end. */
			break;

	} /* while end */

	if( g_signal != 0 ) {
		fprintf( stderr, "%s %s %s\n", message_str_base[INFO_MASSAGE],
                                    sts_message_str[CANON_STS_DEFAULT],
                                    sts_message_str[CANON_STS_PRINT_CANCEL] ) ;
	}
}


#define REGI_OPTION	"CNBjSetRegi"
#define BSCCFILEPATH "/usr/lib/bjlib/"
#define UTIL_OPTION	"CNBjUtilByte"
#define DIRECT_OPTION	"CNBjDirect"

static 
int check_options( FILE** fp, short *is_setregi, int *utilbyte,
				  char* tmp_file, char* option , short *is_direct)
{

	cups_option_t *p_opt = NULL;
	int num_opt = 0; 
	int i,result = 0;
	short regi_flag=0;
	short direct_flag=0;
	int cmdlen = 0;
	int bscc_id = 0;

	if( (num_opt = cupsParseOptions(option, 0, &p_opt)) > 0 ){
		for( i=0; i< num_opt; i++ ){
	
			/* bscc */	
			if( strcmp( p_opt[i].name, REGI_OPTION)== 0){
				bscc_id = atoi(p_opt[i].value);
				regi_flag = 1;
			}
			else if( strcmp( p_opt[i].name, UTIL_OPTION)== 0 ){
				cmdlen = atoi(p_opt[i].value);
				*utilbyte = cmdlen;
			}
			/* Ver.3.20 */
			else if( strcmp( p_opt[i].name, DIRECT_OPTION)== 0 ){
				direct_flag = 1;
			}
		}
	}
	
	if( regi_flag ){
		char model_name[MODEL_NAME_STR_LEN] ;
		char bscc_file[256];
		char bscc_buf[256];
		char cmd_buf[512];
		int r_size,total_size;
		FILE* tmp_fp = NULL;

		sprintf( tmp_file, "/tmp/CNBjBackend%d", getpid());
//		if( (tmp_fp =fopen( tmp_file, "w")) == NULL )
		if( (tmp_fp =fopen( tmp_file, "w+b")) == NULL ){	/* Ver.2.90 */
			fprintf(stderr,"CNBjBackend open_error\n");
			goto open_error;	
		}

		total_size = cmdlen;
		while( total_size > 0 ){
			r_size = fread( cmd_buf, 1,total_size,(FILE*)(*fp) );
			fwrite( cmd_buf, r_size, 1, tmp_fp);
			total_size -= r_size;
		}
		fseek( tmp_fp, 0, SEEK_SET );
		
		r_size = fread( bscc_buf, 1, 256, (FILE*)(*fp) );
		fprintf(stderr,"bscc_buf r_size=%d\n",r_size);
		/* bscc file */
		get_model_name( model_name );
		sprintf( bscc_file, "%scif%s.bscc", BSCCFILEPATH, model_name );
		//sprintf( bscc_file, "%sbjfilter%s.bscc", BSCCFILEPATH, model_name );
		
		if( write_to_bsccfile( bscc_file, bscc_buf, bscc_id ) )
			result = -1;

		*fp = tmp_fp;
	}
	
	*is_setregi = regi_flag;
	*is_direct = direct_flag;	/* Ver.3.20 */
	
	cupsFreeOptions( num_opt, p_opt );
	return result;
	
 open_error:
	cupsFreeOptions( num_opt, p_opt );
	return -1;
		
}

static int is_bscctag( FILE** fp )
{

	FILE* fpTmp = NULL;
	int cc;
	char bufTmp[128];
	int pos = 0;
	int result = 1;

	fpTmp = *fp;

	while( (cc=fgetc(fpTmp)) != EOF ){
		if( cc == ']' )
			bufTmp[pos] = 0x00;	
		else if( cc == 0x09 || cc == 0x20 )
			;
		else if( cc == 0x0A ){
			result = strcmp( bufTmp, "bscc" ) ? 0 : 1;
			break;
		}	
		else
			bufTmp[pos++] = cc;	
	}
		
	*fp = fpTmp;
	return result;
		
}


static int write_to_bsccfile( char* bscc_file, char* bscc_buf, short bscc_id )
{

	FILE* fp = NULL;	
	int cc;
	char bufTmp[128];
	char *pStr[2];
	short id;

	int isBscc, isFirst;
	int index = 0;
	int pos = 0;
	int result = 1;
	
	if( strncmp( bscc_buf, "REG", 3 ) != 0 ){
		fprintf( stderr, "bscc command error \n" );
		return -1;	
	}

	/* Open BSCC File */
	if( (fp = fopen( bscc_file, "r+")) == NULL ){
		fprintf( stderr, "bscc file error \n" );
		return -1;	
	}		

	isFirst = 0;
	isBscc = 0;
	while( (cc = fgetc(fp)) != EOF ){

		if( cc == '#' ){		// Comment
			while( (cc = fgetc(fp)) != EOF )
				if( cc == 0x0A )
					break;
		}
		else if( cc == '[' ){
			isBscc = is_bscctag( &fp ) ? 1:0;
			if( isBscc )
				isFirst = 1;	
		}
		else{
			if( isBscc ){
				if( cc == 0x0A ){	// End Of Command Line
					bufTmp[pos] = 0x00;	
					id = (short)atoi( pStr[1] );
					if( id == bscc_id ){
						if(	strlen( pStr[0] ) == strlen( bscc_buf ) ){
							fseek( fp, -(strlen(pStr[0])+strlen(pStr[1])+2),
								   SEEK_CUR );
							if( (fputs(bscc_buf,fp)) != EOF )
								result = 0;	
							break;
						}
					}
					else{
						isFirst = 1; 
						index = 0;
						pos = 0;
					}
				}
				else if( cc == 0x09 || cc == 0x20 ){	// Space or Tab
					isFirst = 1;	
					bufTmp[pos++] = 0x00;
				}
				else{			// Command string or Id string
					if( isFirst ){
						bufTmp[pos] = cc;
						pStr[index++] = &bufTmp[pos];
						pos++;
						isFirst = 0;
					}
					else
						bufTmp[pos++] = cc;
				}
			}
		}
	}
			
	
	if( fp != NULL )
		fclose( fp );	
	return result;

}
		
				

	
