/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2009-2010
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.
 *
 * NOTE:
 *  - As a special exception, this program is permissible to link with the
 *    libraries released as the binary modules.
 *  - If you write modifications of your own for these programs, it is your
 *    choice whether to permit this exception to apply to your modifications.
 *    If you do not wish that, delete this exception.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/sysctl.h>
#include <config.h>

#include <dlfcn.h>
#include "cncl.h"
#include "cncldef.h"
#include "cnclcmdutils.h"

#include "libcnnet.h"
#include "bscc2sts.h"

#define STATUS_BUF 4096
#define BUFSZ      4096

#define	CNIJNET_CASHFILE		BJLIB_PATH "/cnnet.ini"

/****/
CNNLHANDLE h=NULL;

int     p_search_result = 0;



void cnijnpr_sigterm_handler(int sig_code)
{
	int err;

	if( p_search_result == 1 ){
		err = CNNL_Abort(h);
		//printf("@@@CNNL_Abort = %d\n",err);
	}

	if( h == NULL )
		CNNL_Terminate(&h);

    exit(0);
}


/**********************************************/
/*                                            */
/*	main routin                               */
/*                                            */
/*		argv[0]: cnijnpr(process)             */
/*		argv[1]: pipe number(4)               */
/*		argv[2]: MacAdress(00-00-XX-XX-XX-XX) */
/*		argv[3]: Computer Name                */
/*		argv[4]: User Name(loginame)          */
/*		argv[5]: small modelname              */
/*		argv[6]: modelID                      */
/*                                            */
/**********************************************/
int main (int argc, const char **argv)
{
	int		rtn = 0 ;
	int		wrtn = 0 ;
	int		err_count = 0 ;
	int		poweroff_flag = 0;
	int		fd;
	char	ipaddr[32];
	static char		buf[STATUS_BUF];
	static char		buf2[STATUS_BUF];
	unsigned long	buffsz     = 0;
	static char		session_errcount = 0;
	char	statusStr[1024];
	output_dev		Odev;
	CNCLData		CnclData;
	CNCLErr			cnclerr = -1;
	char			module_name[128];
	char			deviceid_buf[512];
	int				command_type = -1;
	void	*handle = NULL;
	short 	(*prntobscc)( char *, short, char *, short, short * );

	if( (argv[1] == NULL) || (argv[2] == NULL) || (argv[3] == NULL) || (argv[4] == NULL) )
		return (-1);

	Odev.status = 0;
	Odev.dev = 0;
	memset(statusStr, 0x00, sizeof(statusStr)) ;
	memset(ipaddr, 0, sizeof(ipaddr));

	signal( SIGTERM, cnijnpr_sigterm_handler );

	fd = atoi( argv[1] );
	//printf("FDqs   = %d\n\n", fd);

	/* Search Printer */
	buf[0] = '*'; /* '*' : can't analize */
	wrtn = write(fd, buf, STATUS_BUF);

	/* for IP Address automatically change */
	while(1){
		//printf("############ Loop ############\n");
		p_search_result = 0;

		/* Library Initialize */
		if( CNNL_Init(&h) != CNNL_RET_SUCCESS ) goto error;

		/* Get IPAddress */
		while(1){
			/* Ready : 0-0.9sec */
			/* Collecting Printer Status : 0.9-56.2sec */
			if( CNNL_GetIPAddressEx(h, CNIJNET_CASHFILE, argv[2], ipaddr, sizeof(ipaddr), CNNET_SEARCH_AUTO, 3, 900) == CNNL_RET_SUCCESS ){
			//if(CNNL_GetIPAddress(CNIJNET_CASHFILE, argv[2], ipaddr, sizeof(ipaddr), CNNET_SEARCH_AUTO, 3, 300) == CNNL_RET_SUCCESS){
				p_search_result = 1;
				break;
			}
			else{
				//printf("############ CNNL_GetIPAddress Err!!! ############\n");
				/* Printer is not responding : 56.2sec- */
				buf[0] = '@'; /* '@' : Power Off */
				poweroff_flag = 1;
				err_count = 0;
				wrtn = write(fd, buf, STATUS_BUF);
			}
			sleep(1);
		}

		/* open Printer */
		if( CNNL_OpenEx(h, ipaddr, CNNET_TYPE_PRINTER, 3, 3000) != CNNL_RET_SUCCESS ) goto error01;
		//if (CNNL_Open(h, ipaddr) != CNNL_RET_SUCCESS) goto error01;

		/* decide command_type */
		if( CNNL_GetCommandType(h, &command_type, 3, 3000) != CNNL_RET_SUCCESS ) goto error01;

		/* open cnclapixxx */
		if( command_type == CNNL_COMMAND_IVEC ){
			memset(module_name, '\0', sizeof(module_name));
			snprintf(module_name, sizeof(module_name), "%s%s%s", "libcnbpcnclapi", argv[6], ".so");
			//printf("\nmodule_name %s\n" ,module_name);

			handle = dlopen(module_name, RTLD_NOW);
			if ( handle == NULL ) goto error01;
			if( (prntobscc = dlsym(handle, "CNCL_GetStatusCommand")) == NULL )	goto error02;
		}

		/* Data read from Printer and write to pipe */
		while(1){
			memset( buf, 0, sizeof(buf) );
			memset( buf2, 0, sizeof(buf2) );

				buffsz = STATUS_BUF;
				{
					int count,activeid,ret1=-1,ret2=-1;
					char user[256],computer[256],hostname[256],document[256];

					memset(user, 0, sizeof(user));
					memset(computer, 0, sizeof(computer));
					memset(hostname, 0, sizeof(hostname));
					memset(document, 0, sizeof(document));

					rtn = CNNL_GetSessionInfo(h, &count, &activeid, user, sizeof(user), computer, sizeof(computer), document, sizeof(document), 3, 1500);
					//rtn = CNNL_GetSessionInfo(h, &count, &activeid, user, sizeof(user), computer, sizeof(computer), document, sizeof(document), 3, 500);
					if(rtn != CNNL_RET_SUCCESS){
						session_errcount++;
						//printf("############ GetSessionInfo Err!!! ############ rtn = %d, session_errcount = %d\n",rtn,session_errcount);
					}
					else{
						session_errcount = 0;
					}

					ret1 = strncmp(argv[3], computer, sizeof(computer));
					ret2 = strncmp(argv[4], user, sizeof(user));

					/*  My Job is Printing and Cable OFF ---> CNNL_RET_FAILURE && activeid != 0 && (ret1 != 0 || ret2 != 0) */
					if( rtn == CNNL_RET_SUCCESS ){
						if( (activeid != 0) && ( (ret1 != 0) || (ret2 != 0) ) ){
							buf[0] = '#';
						}
					}
				}

				if(rtn == CNNL_RET_SUCCESS){
					int i=0,ret3=-1;
					short bscc_size=-1;

					rtn = CNNL_DataRead(h, &buf[1], &buffsz, BUFSZ, 3, 3000);
					//rtn = CNNL_DataRead(h, &buf[1], &buffsz, BUFSZ, 3, 1000);
					//printf("############ buf[1] ############ rtn = %s\n", &buf[1]);

					/* Ver.3.20 pharse xml->sts */
					if( command_type == CNNL_COMMAND_IVEC ){
						char tempbuf = buf[0];
						/* Ver.3.20 pharse xml->bscc */
						//printf("############ # CNCL_GetStatusCommad (rtn, bscc_size) ############= %d,%d\n", rtn, bscc_size);
						rtn = prntobscc( &buf[1] , buffsz , &buf2[1] , BUFSZ , &bscc_size );
						//buf2[0] = buf[0];
						buf2[0] = tempbuf;
						memset( buf, 0, sizeof(buf) );
						memcpy( &buf[0], &buf2[0], BUFSZ );
						//memcpy( &buf[1], &buf2[1], BUFSZ-1 );
						//printf("############ CNCL_GetStatusCommad (rtn, bscc_size) ############= %d,%d\n", rtn, bscc_size);
					}

					/* Ver.3.20 bscc->sts  */
					if( argv[5] != NULL ){
						ret3 = bscc2sts(argv[5], &buf[1], &Odev, (Bscc2sts_tbl)&statusStr);
	
						memset( &buf[1], 0, STATUS_BUF-1 );
						while( 1 ){
							buf[i + 1] = statusStr[i];
							if( statusStr[i] == '\n' ) break;
							i = i + 1;
						}
						//printf("X--- buf[1] ---X = %s\n", &buf[1]);
					}

					if(rtn != CNNL_RET_SUCCESS){
						session_errcount++;
						//printf("############ DataRead Err!!! ############ rtn = %d, session_errcount = %d\n",rtn,session_errcount);
					}
					else{
						session_errcount = 0;
					}
				}

				if (rtn != CNNL_RET_SUCCESS) {
					//memset( buf, 0, sizeof(buf) );
					err_count = err_count + 1;
					/* Keep status : (1.5s)*5 + (1s)*4 = 0-11.5sec */
					if( session_errcount > 4 ){
						/* Printer is not responding : (1.5s)*8 + (1s)*7 -- (1.5s)*24 + (1s)*23 = 19.0-59.0sec */
						if( err_count == 8 || poweroff_flag == 1 ){
							//printf("XXXXXXXXXXXXXXXX err_count, session_errcount = %d, %d\n\n",err_count, session_errcount);
							buf[0] = '@'; /* '@' : Power Off */
							poweroff_flag = 1;
							/* search again IP Address */
							if(err_count == 24)	goto error02; /* about 60(s) */
							//err_count = 0;
						/* collecting status : (1.5s)*5 + (1s)*4 -- (1.5s)*8 + (1s)*7 = 11.5-19.0sec */
						}else{
							//printf("YYYYYYYYYYYYYYYYY err_count, session_errcount = %d, %d\n\n",err_count, session_errcount);
							buf[0] = '*'; /* '*' : can't analize */
							poweroff_flag = 0;
						}
					}
					//printf("DATA READ\t\t(data = %s)\n", buf);
					wrtn = write(fd, buf, STATUS_BUF);
					//exit(-1);
				} else {
					wrtn = write(fd, buf, buffsz + 1); /* for bug fix Ver.3.20 buf[0] */
					//wrtn = write(fd, buf, buffsz);
					//printf("DATA READ %d, (data = %s)\n", buffsz, buf+2);
					poweroff_flag = 0;
					err_count = 0;
				}
				sleep(1);
		}

	error02:
		/* close cnclapixxx */
		if( (command_type == CNNL_COMMAND_IVEC) && (handle != NULL) ){
			dlclose(handle);
			handle = NULL;
		}

	error01:
		/* Close Library */
		CNNL_Close(h);

	error:
		/* Terminate Library */
		CNNL_Terminate(&h);
		h = NULL;
	}

	return 0;
}


/*EOF*/
