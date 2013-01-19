/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2009-2012
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
#include <fcntl.h>

#include <dlfcn.h>
#include "cncl.h"
#include "cncldef.h"
#include "cnclcmdutils.h"

#include "libcnnet.h"
#include "bscc2sts.h"

#define STATUS_BUF 4096
#define BUFSZ      4096

#define	CNIJNET_CASHFILE		BJLIB_PATH "/cnnet.ini"
#define COMPARE_LENGTH			(31)
#define STR_STA					"STA:"
#define MAX_SHORT				32767
#define DEV_NULL_FIRMUP			9998
#define DEV_NULL_NUMBER			9999



/****/
CNNLHANDLE h=NULL;


int     p_search_result = 0;

static short check_deviceid_sta(char*);
static int get_printer_devid(int);

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
/*		argv[7]: backend_type                 */
/*		argv[8]: /dev/usb/lp0                 */
/*                                            */
/**********************************************/
int main (int argc, const char **argv)
{
	int		fd;
	int		rtn = 0 ;
	int		wrtn = 0 ;
	int		err_count = 0 ;
	int		poweroff_flag = 0;
	int		command_type = -1;
	short	sta = -1;
	short 	(*prntobscc)( char *, short, char *, short, short * );
	char	statusStr[2048];
	/* char	statusStr[1024]; */
	char	ipaddr[32];
	char			module_name[128];
	char			*deviceid_buf;
	//char			deviceid_buf[BUFSZ];
	static char		buf[STATUS_BUF];
	static char		buf2[STATUS_BUF];
	static char		session_errcount = 0;
	unsigned long	buffsz     = 0;
	output_dev		Odev;
	CNCLData		CnclData;
	CNCLErr			cnclerr = -1;
	void	*handle = NULL;


	if( (argv[1] == NULL) || (argv[2] == NULL) || (argv[3] == NULL) || (argv[4] == NULL) )
		return (-1);

	deviceid_buf = (char *)malloc(BUFSZ);
	if(deviceid_buf == NULL)	return (-1);
	memset(deviceid_buf, 0, BUFSZ);

	Odev.status = 0;
	Odev.dev = 0;
	memset(statusStr, 0x00, sizeof(statusStr)) ;
	memset(ipaddr, 0, sizeof(ipaddr));
//	memset(deviceid_buf, 0, sizeof(deviceid_buf));

	signal( SIGTERM, cnijnpr_sigterm_handler );

	fd = atoi( argv[1] );
	/* printf("FDqs   = %d\n\n", fd); */

	/* Search Printer */
	buf[0] = '*'; /* '*' : can't analize */
	wrtn = write(fd, buf, STATUS_BUF);
	sleep(1);

	/******  Start USB process *****/
	if ( (argv[7] != NULL) && (strncmp("1", argv[7], strlen(argv[7]) ) == 0) )
	{
		int		fdusb;
		short	ret;
		short	bscc_size=-1;
		short	i;
		short	x = 0;
		char	tempbuf = buf[0];
		char	before_buf = buf[0];
		char	*buf3 = NULL;
		char	*buf4 = NULL;
		short	r_size = 0;
		short	r_size2 = 0;
		short	count = 0;

		/* Command Type Decide */
		memset(module_name, '\0', sizeof(module_name));
		snprintf(module_name, sizeof(module_name), "%s%s%s", "libcnbpcnclapi", argv[6], ".so");

		handle = dlopen(module_name, RTLD_NOW);
		if ( handle == NULL ) goto error01;
		if( (prntobscc = dlsym(handle, "CNCL_GetStatusCommand")) == NULL )	goto error03;

		buf3 = (char *)malloc(STATUS_BUF);
		if(buf3 == NULL)	goto error04;
		memset(buf3, 0, STATUS_BUF);
	
		buf4 = (char *)malloc(STATUS_BUF);
		if(buf4 == NULL)	goto error05;
		memset(buf4, 0, STATUS_BUF);

		while(1){
			short	err_dev_flag=-1;

			memset( buf, 0, sizeof(buf) );
			memset( buf2, 0, sizeof(buf2) );

			fdusb = open(argv[8], O_RDONLY);
			ret = strncmp(argv[8], "/dev/null", COMPARE_LENGTH);
			if( ret == 0 ) {
				fdusb = -1;
				err_dev_flag = DEV_NULL_NUMBER;
			}

			ret = strncmp(argv[8], "/dev/nullfirmupxxx", COMPARE_LENGTH);
			if( ret == 0 ) {
				fdusb = -1;
				err_dev_flag = DEV_NULL_FIRMUP;
			}

			if( fdusb < 0 ) {
				//when open OK --> NG, keep buf[0]
				if( x == 0 ) buf[0] = before_buf;
				if( x != 0 ) {
					if( (errno == EBUSY) || (err_dev_flag == DEV_NULL_NUMBER) )		buf[0] = '!'; /* Printing , Dummy Printing */
					else if( err_dev_flag == DEV_NULL_FIRMUP )						buf[0] = 'f'; /* FirmUp */
					else															buf[0] = '?'; /* Cable disconnect :errno=2 */
				}
				x += 1;
				if( x == MAX_SHORT ) x = 1;
				goto datawrite01;
			}
			else{
				x = 0;
				before_buf = buf[0];
			}

			ret = ioctl(fdusb, _IOC(_IOC_READ, 'P', 1, BUFSZ), deviceid_buf);
			//ret = ioctl(fdusb, _IOC(_IOC_READ, 'P', 1, sizeof(deviceid_buf)), deviceid_buf);
			/* for Ver.3.80 */
			if( ret != 0 ) {
				buf[0] = '?';
				goto datawrite01;
			}
			sta = check_deviceid_sta( deviceid_buf );

			switch( sta ){
				case 0x20:
					buf[0] = 's';
				break;
				
				case 0x11:
					buf[0] = 'o';
				break;
			}

			sta = (sta >> 4) & 0x000F;
			switch( sta ){
				case 0x08:
					buf[0] = 'f';
				break;
				
				case 0x03:
					buf[0] = 'w';
				break;
			}
			if( buf[0] == 's') goto datawrite01;
			if( buf[0] == 'o') goto datawrite01;
			if( buf[0] == 'f') goto datawrite01;
			if( buf[0] == 'w') goto datawrite01;

			r_size = read(fdusb, buf3, BUFSZ);
			if (r_size > 0) tempbuf = buf[0];
			memcpy( &buf4[0], buf3, r_size );

			command_type = get_printer_devid(fdusb);
			if( command_type == CNNL_COMMAND_IVEC ){
				/* pharse xml->bscc */
				rtn = prntobscc( buf3 , r_size , &buf2[1] , BUFSZ , &bscc_size );
				/* for kernel readsize=<1024 : Ver.3.80 */
				if( (rtn == CNCL_ERROR) && (r_size > 0) ){
					count = 0;
					while(1){
						count++;
						if(count == 5) break;
						/* for print */
						usleep(10000);
						/* sleep(2); */
						/* check deviceid */
						ret = ioctl(fdusb, _IOC(_IOC_READ, 'P', 1, sizeof(deviceid_buf)), deviceid_buf);
						if( ret != 0 ) {
							buf[0] = '?';
							goto datawrite01;
						}

						if( (r_size2 = read(fdusb, buf3, BUFSZ)) < 0 )	goto error05;
						if( (r_size2 + r_size) >= BUFSZ )	goto error05;
						memcpy( &buf4[r_size], buf3, r_size2 );
						r_size += r_size2;

						rtn = prntobscc( buf4 , r_size , &buf2[1] , BUFSZ , &bscc_size );
						if(rtn == CNCL_OK) break;
					}
				}

				//printf("############ CNCL_GetStatusCommad (rtn, bscc_size) ############= %d,%d\n", rtn, bscc_size);  
				//buf2[0] = buf[0];
				buf2[0] = tempbuf;
				memset( buf, 0, sizeof(buf) );
				memcpy( &buf[0], &buf2[0], BUFSZ );
			}
			/* bscc->sts */
			ret = bscc2sts((char *)argv[5], &buf[1], &Odev, (Bscc2sts_tbl)&statusStr);

			memset( &buf[1], 0, STATUS_BUF-1 );
			i= 0;
			while( 1 ){
				buf[i + 1] = statusStr[i];
				if( statusStr[i] == '\n' ) break;
				i = i + 1;
			}

			datawrite01:
			//printf("child :X--- buf[0] ---X = %s\n", &buf[0]);
			//printf("child :X--- buf[1] ---X = %s\n", &buf[1]);
			wrtn = write(fd, buf, STATUS_BUF + 1); /* for bug fix Ver.3.20 buf[0] */
			//wrtn = write(fd, buf, 4096); /* for bug fix Ver.3.20 buf[0] */

			if( fdusb > 0 ) {
				close(fdusb);
			}
			sleep(2);
		}
	/********/
	error05:
		free(buf4);
	error04:
		free(buf3);
	/********/
	error03:
		/* close cnclapixxx */
		if( (command_type == CNNL_COMMAND_IVEC) && (handle != NULL) ){
			dlclose(handle);
			handle = NULL;
		}

	}
	/******  End USB process *****/


	/******  Start Network process *****/
	else{
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
	
						/* change Ver.3.50 */
						ret1 = strncmp(argv[3], computer, COMPARE_LENGTH);
						ret2 = strncmp(argv[4], user, COMPARE_LENGTH);
						/* ret1 = strncmp(argv[3], computer, sizeof(computer)); */
						/* ret2 = strncmp(argv[4], user, sizeof(user)); */
	
						/*  My Job is Printing and Cable OFF ---> CNNL_RET_FAILURE && activeid != 0 && (ret1 != 0 || ret2 != 0) */
						if( rtn == CNNL_RET_SUCCESS ){
							if( (activeid != 0) && ( (ret1 != 0) || (ret2 != 0) ) ){
								buf[0] = '#';
							}
						}

						/* Get DeviceID STA Ver.3.70 */
						rtn = CNNL_GetDeviceID(h, deviceid_buf, &buffsz, BUFSZ, 3, 3000);
						//printf("############ CNNL_GetDeviceID rtn ############ rtn = %d\n", rtn);
						//printf("############ CNNL_GetDeviceID device_id ############ rtn = %s\n", (deviceid_buf + 2));
						sta = check_deviceid_sta( deviceid_buf );
						//printf("sta = 0x%x\n", sta );

						switch( sta ){
							case 0x20:
								buf[0] = 's';
							break;
							
							case 0x11:
								buf[0] = 'o';
							break;
						}
						
						sta = (sta >> 4) & 0x000F;
						switch( sta ){
							case 0x08:
								buf[0] = 'f';
							break;
							
							case 0x03:
								buf[0] = 'w';
							break;
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
							ret3 = bscc2sts((char *)argv[5], &buf[1], &Odev, (Bscc2sts_tbl)&statusStr);
		
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

	}
	/******  End Network process *****/
	free(deviceid_buf);

	return 0;
}


/************************************************/
/*             check_deviceid_sta               */
/************************************************/
static short check_deviceid_sta(char* devid)
{
	char	*ivec = NULL;
	int		error = -1;
	int		val = 0;
	unsigned char work[2];
	unsigned int  wk;

	if(devid == NULL) goto err01;

	if((ivec = strstr(devid+2, STR_STA)) == NULL) goto err01;

	ivec = ivec + strlen(STR_STA);

	work[0] = *ivec;
	work[1] = 0x00;
	sscanf((char *)work, "%x", &wk);
	val = (char)(wk<<4);

	ivec++;
	work[0] = *ivec;
	work[1] = 0x00;
	sscanf((char *)work, "%x", &wk);
	val |= (char)wk;

	error = 0;

	if(val)
		error = val;

err01:
	return error;
}

/************************************************/
/*             get_printer_devid               */
/************************************************/
static int get_printer_devid(fdusb)
{
	char	devid[1024];
	char	*ivec = NULL;
	int		command_type = -1;
	
	memset(devid, '\0', sizeof(devid));

	if (ioctl(fdusb, _IOC(_IOC_READ, 'P', 1, sizeof(devid)), devid) == 0){
		if ((ivec = strstr(devid+2, "MFG:")) != NULL){
			if ((ivec = strstr(ivec, "Canon")) != NULL){
				if ((ivec = strstr(ivec, "CMD:")) != NULL){
					if ((ivec = strstr(ivec, "IVEC,")) != NULL){
						command_type = CNNL_COMMAND_IVEC;
					}else{
						command_type = CNNL_COMMAND_NONIVEC;
					}
				}	
			}
     	}
	}

	return command_type;
}

