/*
 *  CUPS add-on module for Canon Inkjet Printer.
 *  Copyright CANON INC. 2001-2012
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


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#if 0
#include "cncl.h"
#include "cncldef.h"
#include "cncl2def.h"
#include "cncludef.h"
#include "cnclucom.h"
#endif

#include "mntipc.h"
#include "bjutil.h"

#define UTILBYTESTR "CNBjUtilByte=%ld"
#define BSCCOPTSTR "CNBjSetRegi=%d"
#define RBUFSIZ 	256

char **make_pdata_lpr_param( char *printer,	IPCU* p_ipc ,short direct_flag)	/* Ver.3.20 add param */
{

	char **cmd_buf;
	int cmd_fd;
	int total_size, w_size;
	char *ptr;
	static char cmd_filename[256];
	static char utilbyte[32];

	/* Ver.3.20 */
	/* If direct_flag is 1 , add "-o CNBjDirect" */
	if( direct_flag == 1 ) cmd_buf = (char**)malloc( 11 * sizeof(char*) );
	else cmd_buf = (char**)malloc( 9 * sizeof(char*) );

	if( cmd_buf ){

		snprintf(cmd_filename, 255, "%s%d", BJ_UTILFILE, getpid());
		snprintf(utilbyte, 31, UTILBYTESTR, p_ipc->cmds.cmdslen );
		if( (cmd_fd=open(cmd_filename, O_WRONLY|O_CREAT|O_TRUNC,0644 )) 
			== -1 )
			goto open_error;
	
		ptr = p_ipc->cmds.cmds;
		total_size = p_ipc->cmds.cmdslen;
		while( 1 ){
			w_size = write( cmd_fd, ptr, total_size );

			if ( w_size == -1 ){
				goto write_error;
			}
			
			if ( w_size < total_size ){
				total_size -= w_size;
				ptr    += w_size;
			}
			else break;
		}

		cmd_buf[0] = "lpr";
		cmd_buf[1] = "-P";
		cmd_buf[2] = printer;
		cmd_buf[3] = "-o";
		cmd_buf[4] = "raw";
		cmd_buf[5] = cmd_filename;
		cmd_buf[6] = "-o";
		cmd_buf[7] = utilbyte;

		/* If direct_flag is 1 , add "-o CNBjDirect" */
		if( direct_flag == 1 ){
			cmd_buf[8] = "-o";
			cmd_buf[9] = "CNBjDirect";
			cmd_buf[10] = NULL;
		}
		else{
			cmd_buf[8] = NULL;
		}

		close( cmd_fd );
	}

#if 0
	/* for debug */
	{
		short i=0;
		while( cmd_buf[i]!=NULL )
		{
			fprintf(stderr,"cmd_buf[%d]=%s\n",i,cmd_buf[i]);
			i++;
		}
	}
#endif

	return cmd_buf;

 write_error:
	close(cmd_fd);
	unlink(cmd_filename);
 open_error:
	free( cmd_buf );
	return NULL;	

}

char **make_fdata_lpr_param( char *printer, IPCU *p_ipc )
{
	
	char **cmd_buf;
	int cmd_fd, pfile_fd;
	int total_size, w_size, r_size;
	char *ptr;
	static char cmd_filename[256];
	char r_buf[RBUFSIZ];
	
	cmd_buf = (char**)malloc( 9 * sizeof(char*) );
	
	if( cmd_buf ){
	
		snprintf(cmd_filename, 255, "%s%d", BJ_UTILFILE, getpid());

		if( (cmd_fd=open(cmd_filename, O_WRONLY|O_CREAT|O_TRUNC, 0644 )) 
			== -1 )
			goto open_error;
	
		ptr = p_ipc->fncmds.cmds;
		total_size = p_ipc->fncmds.cmdslen;
		while( 1 ){
			w_size = write( cmd_fd, ptr, total_size );

			if ( w_size == -1 ){
				goto write_error;
			}
			
			if ( w_size < total_size ){
				total_size -= w_size;
				ptr    += w_size;
			}
			else break;
		}
		
		if( (pfile_fd=open(p_ipc->fncmds.filename, O_RDONLY)) == -1 )
			goto pfile_error;
		
		
		while( (r_size=read(pfile_fd,r_buf,RBUFSIZ)) > 0 ){
			ptr = r_buf;
			while( 1 ){
				w_size = write( cmd_fd, ptr, r_size );

				if ( w_size <= 0 ){
					w_size = 0;
					continue;
				}

				if ( w_size < r_size ){
						r_size -= w_size;
						ptr    += w_size;
				}
				else break;
			}
		}

		cmd_buf[0] = "lpr";
		cmd_buf[1] = "-P";
		cmd_buf[2] = printer;
		cmd_buf[3] = "-o";
		cmd_buf[4] = "raw";
		cmd_buf[5] = cmd_filename;
		cmd_buf[6] = NULL;

		close( cmd_fd );
		close( pfile_fd );
	}
	
	return cmd_buf;

 pfile_error:
 write_error:
	close(cmd_fd);
	unlink(cmd_filename);
 open_error:
	free( cmd_buf );
	return NULL;	

}

char **make_wdata_lpr_param( char *printer, IPCU *p_ipc )
{

	char **cmd_buf;
	int cmd_fd,pfile_fd;
	int total_size, w_size, r_size;
	char *ptr;
	static char cmd_filename[256];
	static char bscc_opt[256];
	static char utilbyte[32];
	char r_buf[RBUFSIZ];
	char id_buf[3];
	int bscc_id;
	char* p_top=NULL;
	
	cmd_buf = (char**)malloc( 11 * sizeof(char*) );
	
	if( cmd_buf ){

		snprintf(cmd_filename, 255, "%s%d", BJ_UTILFILE, getpid());
		if( (cmd_fd=open(cmd_filename, O_WRONLY|O_CREAT|O_TRUNC, 0644 )) 
			== -1 )
			goto open_error;
	
		ptr = p_ipc->fncmds.cmds;
		total_size = p_ipc->fncmds.cmdslen;
		while( 1 ){
			w_size = write( cmd_fd, ptr, total_size );

			if ( w_size == -1 ){
				goto write_error;
			}
			
			if ( w_size < total_size ){
				total_size -= w_size;
				ptr    += w_size;
			}
			else break;
		}
		if( (pfile_fd=open(p_ipc->fncmds.filename, O_RDONLY)) == -1 )
			goto pfile_error;
				
		while( (r_size=read(pfile_fd,r_buf,RBUFSIZ)) > 0 ){
			ptr = r_buf;
			while( 1 ){
				w_size = write( cmd_fd, ptr, r_size );

				if ( w_size <= 0 ){
					w_size = 0;
					continue;
				}
				if ( w_size < r_size ){
						r_size -= w_size;
						ptr    += w_size;
				}
				else break;
			}
		}
		
		/* bscc file option  */
		p_top = strrchr( p_ipc->fncmds.filename, '/');
		if( p_top )
			strncpy( id_buf, p_top+1, 2);
		else
			strncpy( id_buf, p_ipc->fncmds.filename, 2);	

		id_buf[2] = '\0';
		bscc_id = atoi(id_buf);

		snprintf(bscc_opt, 255, BSCCOPTSTR, bscc_id );
		/* utility cmd lenght option */
		snprintf(utilbyte, 31, UTILBYTESTR, p_ipc->fncmds.cmdslen );
		
		cmd_buf[0] = "lpr";
		cmd_buf[1] = "-P";
		cmd_buf[2] = printer;
		cmd_buf[3] = "-o";
		cmd_buf[4] = "raw";
		cmd_buf[5] = cmd_filename;
		cmd_buf[6] = "-o";
		cmd_buf[7] = utilbyte;
		cmd_buf[8] = "-o";
		cmd_buf[9] = bscc_opt;
		cmd_buf[10] = NULL;

		close(cmd_fd);
		close(pfile_fd);
		unlink(p_ipc->fncmds.filename);
	}
	
	return cmd_buf;

 pfile_error:
 write_error:
	close(cmd_fd);
	unlink(cmd_filename);
 open_error:
	free( cmd_buf );
	return NULL;	
}

void free_util_cmd_param( char** cmd_param )
{

	unlink( cmd_param[5] );	

	if( cmd_param )
		free( cmd_param );
	
}
