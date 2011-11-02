/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2009
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

#include "libcnnet.h"

#define STATUS_BUF 2048
#define BUFSZ (512)
#define MAX_COUNT_OF_PRINTERS   (64)

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
/*		argv[2]: MacAdress(00-00-85-XX-XX-XX) */
/*		argv[3]: Computer Name                */
/*		argv[4]: User Name(loginame           */
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
	unsigned long	buffsz     = 0;
	static char		session_errcount = 0;


	if( (argv[1] == NULL) || (argv[2] == NULL) || (argv[3] == NULL) || (argv[4] == NULL) )
		return (-1);

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
		/* Get IPAddress */
		while(1){
			/* Ready : 0-0.9sec */
			/* Collecting Printer Status : 0.9-56.2sec */
			if(CNNL_GetIPAddress(CNIJNET_CASHFILE, argv[2], ipaddr, sizeof(ipaddr), CNNET_SEARCH_AUTO, 3, 300) == CNNL_RET_SUCCESS){
				p_search_result = 1;
				break;
			}
			else{
				//printf("############ CNNL_GetIPAddress Err!!! ############\n");
				//err_count = err_count + 1;
				//if( err_count == 1 || poweroff_flag == 1 ){
					/* Printer is not responding : 56.2sec- */
					buf[0] = '@'; /* '@' : Power Off */
					poweroff_flag = 1;
					err_count = 0;
				//}else{
				//	/* Collecting Printer Status : 0.9-3.8sec */
				//	buf[0] = '*'; /* '*' : can't analize */
				//	poweroff_flag = 0;
				//}
				wrtn = write(fd, buf, STATUS_BUF);
			}
			sleep(1);
		}

		/* Library Initialize */
		if (CNNL_Init(&h) != CNNL_RET_SUCCESS) goto error;

		/* open Printer */
		if (CNNL_Open(h, ipaddr) != CNNL_RET_SUCCESS) goto error01;

		/* Data read from Printer and write to pipe */
		while(1){
			memset( buf, 0, sizeof(buf) );
			
				buffsz = STATUS_BUF;
				{
					int count,activeid,ret1=-1,ret2=-1;
					char user[256],computer[256],hostname[256],document[256];

					memset(user, 0, sizeof(user));
					memset(computer, 0, sizeof(computer));
					memset(hostname, 0, sizeof(hostname));
					memset(document, 0, sizeof(document));

					rtn = CNNL_GetSessionInfo(h, &count, &activeid, user, sizeof(user), computer, sizeof(computer), document, sizeof(document), 3, 500);
					if(rtn != CNNL_RET_SUCCESS){
						session_errcount++;
						//printf("############ GetSessionInfo Err!!! ############ rtn = %d, session_errcount = %d\n",rtn,session_errcount);
					}
					else{
						session_errcount = 0;
					}

					ret1 = strncmp(argv[3], computer, sizeof(computer));
					ret2 = strncmp(argv[4], user, sizeof(user));
					//ret1 = strncmp(argv[3], computer, sizeof(argv[3]));
					//ret2 = strncmp(argv[4], user, sizeof(argv[4]));

					/*  My Job is Printing and Cable OFF ---> CNNL_RET_FAILURE && activeid != 0 && (ret1 != 0 || ret2 != 0) */
					if( rtn == CNNL_RET_SUCCESS ){
						if( (activeid != 0) && ( (ret1 != 0) || (ret2 != 0) ) ){
							buf[0] = '#';
						}
					}
				}

				if(rtn == CNNL_RET_SUCCESS){
					rtn = CNNL_DataRead(h, &buf[1], &buffsz, BUFSZ, 3, 1000);
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
					/* Keep status : (1.5s)*4 + (1s)*3 = 0-9.0sec */
					if( session_errcount > 3 ){
						/* Printer is not responding : (1.5s)*8 + (1s)*7 -- (1.5s)*24 + (1s)*23 = 19.0-59.0sec */
						if( err_count == 8 || poweroff_flag == 1 ){
							//printf("XXXXXXXXXXXXXXXX err_count, session_errcount = %d, %d\n\n",err_count, session_errcount);
							buf[0] = '@'; /* '@' : Power Off */
							poweroff_flag = 1;
							/* search again IP Address */
							if(err_count == 24) goto error01; /* about 60(s) */
							//err_count = 0;
						/* collecting status : (1.5s)*4 + (1s)*3 -- (1.5s)*8 + (1s)*7 = 9.0-19.0sec */
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
					wrtn = write(fd, buf, buffsz);
					poweroff_flag = 0;
					err_count = 0;
				}
				sleep(1);
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
