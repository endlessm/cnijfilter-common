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
 *
 * NOTE:
 *  - As a special exception, this program is permissible to link with the
 *    libraries released as the binary modules.
 *  - If you write modifications of your own for these programs, it is your
 *    choice whether to permit this exception to apply to your modifications.
 *    If you do not wish that, delete this exception.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>
#include <dlfcn.h>

#include <cncldef.h>
#include <cncl.h>
#include <cnclcmdutils.h>

#include <libcnnet.h>
#include <cnijnetchk.h>
#include <cnijnetprn.h>


/*******************************************************************************
	Definitions of function
********************************************************************************/

unsigned long fread_with_retry(char *rbuffer, unsigned long bufsize, FILE *fp);
static int  _ij_network_print(const char *, const char *, const char *, const char *, int, FILE *);
static void _ij_network_terminate(int);
static int  _ij_network_search(int, int);


/*******************************************************************************
	Definitions of variants
********************************************************************************/

CNNLHANDLE    hnd        = NULL;
volatile int  mode       = CNNL_JOB_PREPARING;
int           command    = CNNL_COMMAND_NONIVEC;
unsigned long packet_size= 4*1024;

CNNL_PRINTCHECK_FUNC start_print  = NULL;
CNNL_PRINTCHECK_FUNC end_print    = NULL;
CNNL_PRINTCHECK_FUNC check_print  = NULL;

CNCLErr (*makePrintCommand)( short  , char * , short  , char *, char *)   = NULL;
CNCLErr (*checkPrintCommand)( short  , char * , short  , char * , short ) = NULL;
CNCLErr (*getStatusCommand)( char * , short , char * , short , short * )  = NULL;

/*******************************************************************************
	Main
********************************************************************************/
int main(int argc, char **argv){
	int retcode = CNNL_RET_SUCCESS;
	struct sigaction action_pipe, action_term;
	FILE *fp=NULL;
	
	OPTIONTABLE opt_start;
	
	char macaddr[64], user[32], job[64], model_number[64];
	char file_path[512], search_mode[64];
	int is_direct=0, is_installer=0;
	
	/* init */
	memset(macaddr, 0x00, sizeof(macaddr));
	memset(user, 0x00, sizeof(user));
	memset(job, 0x00, sizeof(job));
	memset(model_number, 0x00, sizeof(model_number));
	memset(file_path, 0x00, sizeof(file_path));
	memset(search_mode, 0x00, sizeof(search_mode));
	
	/* ignore SIGPIPE */
	memset(&action_pipe, 0, sizeof(action_pipe));
	action_pipe.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &action_pipe, NULL);
	
	/* set signal handler for SIGTERM */
	memset(&action_term, 0, sizeof(action_term));
	sigemptyset(&action_term.sa_mask);
	sigaddset(&action_term.sa_mask, SIGTERM);
	action_term.sa_handler = _ij_network_terminate;
	action_term.sa_flags = 0;
	sigaction(SIGTERM, &action_term, NULL);
	
	/* parse options */
	if (parse_options(&opt_start, argc, argv) < 0){
		fprintf(stderr, "ERROR: cannot parse options\n");
		exit(1);
	}
	
	/* get installer option */
	if (get_options(&opt_start, OPTION_STRING_INSTALLER, NULL, 0) < 0){
		is_installer = 0;
	} else {
		is_installer = 1;
	}
	
	if (get_options(&opt_start, OPTION_STRING_SEARCH, search_mode, sizeof(search_mode)) >= 0){
		/* search mode */
		int mode = CNNET_SEARCH_AUTO;
		
		if (search_mode != NULL){
			if        (strcmp(search_mode, CNIJNET_SEARCH_MODE_BROADCAST) == 0){
				mode = CNNET_SEARCH_BROADCAST;
			} else if (strcmp(search_mode, CNIJNET_SEARCH_MODE_UNICAST) == 0){
				mode = CNNET_SEARCH_UNICAST;
			} else if (strcmp(search_mode, CNIJNET_SEARCH_MODE_AUTO) == 0){
				mode = CNNET_SEARCH_AUTO;
			} else if (strcmp(search_mode, CNIJNET_SEARCH_MODE_CACHE_ACTIVEONLY) == 0){
				mode = CNNET_SEARCH_CACHE_ACTIVEONLY;
			} else {
				fprintf(stderr, "ERROR: invalid parameter(%s)\n", OPTION_STRING_SEARCH);
				exit(1);
			}
		} else {
			fprintf(stderr, "ERROR: missing parameter(%s)\n", OPTION_STRING_SEARCH);
			exit(1);
		}

		
		_ij_network_search(mode, is_installer);
		exit(0);
	} else {
		/* print mode */
		if (is_installer == 1){
			fprintf(stderr, "ERROR: too few options(%s)\n", OPTION_STRING_SEARCH);
			exit(1);
		}
	}
	
	
	/* get macaddr */
	if (get_options(&opt_start, OPTION_STRING_MACADDR, macaddr, sizeof(macaddr))< 0){
		fprintf(stderr, "ERROR: too few options(%s)\n", OPTION_STRING_MACADDR);
		exit(1);
	}
	
	/* get model_number */
	if (get_options(&opt_start, OPTION_STRING_MODELNUM, model_number, sizeof(model_number)) < 0){
		fprintf(stderr, "ERROR: too few options(%s)\n", OPTION_STRING_MODELNUM);
		exit(1);
	}
	
	/* get file desc. */
	fp = stdin;
	
	/* get user */
	get_options(&opt_start, OPTION_STRING_USERNAME, user, sizeof(user));
	
	/* get job */
	get_options(&opt_start, OPTION_STRING_JOBNAME, job, sizeof(job));
	
	/* get direct */
	if (get_options(&opt_start, OPTION_STRING_DIRECT, NULL, 0) < 0){
		is_direct=0;
	} else {
		is_direct=1;
	}
	
	retcode = _ij_network_print(macaddr, user, job, model_number, is_direct, fp);
	switch (retcode){
		case 0:
			exit(0);
		default:
			exit(1);
	}
}


/*******************************************************************************
	_ij_network_print
********************************************************************************/
static int _ij_network_print(
	const char  *macaddr,
	const char  *user,
	const char  *job,
	const char  *model_number,
	const int    is_direct,
	FILE *fp
){
	int  errcode = 0;
	
	char ipaddr[STRING_SHORT];
	char hostname[HOST_NAME_MAX+1];
	char library_path[512];
	
	char *rbuffer    = NULL;
	char *p          = NULL;
	void *lib_handle = NULL;
	
	uint32_t len     = 0;
	int  working     = 0;
	int  count       = 0;
	int  tmp_ret     = CNNL_RET_SUCCESS;
	
	// clear buffer
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	memset(ipaddr, 0x00, STRING_SHORT);
	memset(hostname, 0x00, HOST_NAME_MAX+1);
	
	// allocate memory
	if ((rbuffer=(char*)malloc(sizeof(char)*READ_BUFFER_SIZE)) == NULL){
		goto error_init;
	}
	
	// get hostname
	if (gethostname(hostname, HOST_NAME_MAX) != 0){
		errcode = 1;
		fprintf(stderr, "ERROR: cannot get hostname\n");
		goto error_init;
	}
	hostname[(HOST_NAME_MAX > 31)? 31:HOST_NAME_MAX] = 0;
	mode = CNNL_JOB_PREPARING;

init_printing:
	/* write to printer */
	{
		unsigned long latest_version = CNNL_LIB_LATEST_VERSION;
		unsigned long regacy_version = 100;
		unsigned long param_size     = sizeof(unsigned long);
		
		/* Init */
		if (CNNL_Init(&hnd) != CNNL_RET_SUCCESS){
			errcode = 1;
			fprintf(stderr, "ERROR: error occurred while preparing(%d)\n", __LINE__);
			goto error_init;
		}
		if (CNNL_Config(hnd, CNNL_CONFIG_SET_VERSION, &latest_version, &param_size) != CNNL_RET_SUCCESS){
			goto error_open;
		}
		
		/* ---------------------------------------------------------------------
		    find printers 
		*/
		{
			int i, j, found=0;
			
			fprintf(stderr, "INFO: \n");
			for (i=0; !(mode & CNNL_JOB_CANCELLED); i++){
				
				memset(ipaddr, 0x00, STRING_SHORT);
				if (CNNL_GetIPAddressEx(hnd, CACHE_PATH, macaddr, ipaddr, STRING_SHORT, CNNET_SEARCH_AUTO, 1, 5000) == CNNL_RET_SUCCESS){
					found=1;
					break;
				}
				
				fprintf(stderr, "INFO: printer not responding; will retry in %d seconds...\n", WAITTIME_FIND_PRINTERS);
				for (j=0; j<WAITTIME_FIND_PRINTERS; j++, sleep(1)){
					// cancelled
					if ((mode & CNNL_JOB_CANCELLED)) goto error_init;
				}
				fprintf(stderr, "INFO: \n");
			}
			
			/* not found */
			if (found == 0){
				errcode = 1;
				fprintf(stderr, "ERROR: printer not found; job failed\n");
				goto error_init;
			}
			
			/* cancelled */
			if ((mode & CNNL_JOB_CANCELLED)) goto error_init;
		}
		fprintf(stderr, "INFO: \n");
		
		/* ---------------------------------------------------------------------
		    open printer 
		*/

		if (CNNL_OpenEx(hnd, ipaddr, CNNET_TYPE_PRINTER, 10, 60000) != CNNL_RET_SUCCESS){
			errcode = 1;
			fprintf(stderr, "ERROR: error occurred while preparing(%d)\n", __LINE__);
			goto error_open;
		}
		
		// check wether the printer exists or not
		if (CNNL_CheckVersion(hnd, 10, 60000) != CNNL_RET_SUCCESS){
			errcode = 1;
			fprintf(stderr, "ERROR: error occurred while preparing(%d)\n", __LINE__);
			goto error_close;
		}
		
		// check command type
		if (CNNL_GetCommandType(hnd, &command, 10, 60000) != CNNL_RET_SUCCESS){
			errcode = 1;
			fprintf(stderr, "ERROR: error occurred while preparing(%d)\n", __LINE__);
			goto error_close;
		}
		
		// switch functions
		if (command == CNNL_COMMAND_IVEC){
			// support ivec commands
			start_print  = CheckStartPrint;
			end_print    = CheckEndPrint;
			check_print  = CheckExecutePrint;
			
			memset(library_path, 0x00, sizeof(library_path));
			snprintf(library_path, sizeof(library_path)-1, CNCL_LIB_PATH, model_number);
			
			// load functions
			lib_handle = dlopen(library_path, RTLD_LAZY);
			if (lib_handle == NULL){
				fprintf(stderr, "ERROR: cannot load library(%d)\n", __LINE__);
				errcode = 1;
				goto error_close;
			}
			
			makePrintCommand  = dlsym(lib_handle, "CNCL_MakePrintCommand");
			if (dlerror() != NULL){
				fprintf(stderr, "ERROR: cannot load function(%d)\n", __LINE__);
				errcode = 1;
				goto error_close;
			}
			
			checkPrintCommand = dlsym(lib_handle, "CNCL_CheckPrintCommand");
			if (dlerror() != NULL){
				fprintf(stderr, "ERROR: cannot load function(%d)\n", __LINE__);
				errcode = 1;
				goto error_close;
			}
			
			getStatusCommand  = dlsym(lib_handle, "CNCL_GetStatusCommand");
			if (dlerror() != NULL){
				fprintf(stderr, "ERROR: cannot load function(%d)\n", __LINE__);
				errcode = 1;
				goto error_close;
			}
		} else {
			param_size = sizeof(unsigned long);
			if (CNNL_Config(hnd, CNNL_CONFIG_SET_VERSION, &regacy_version, &param_size) != CNNL_RET_SUCCESS){
				goto error_close;
			}
			
			// not support ivec commands
			start_print  = CNNL_StartPrint;
			end_print    = CNNL_EndPrint;
			check_print  = CNNL_CheckPrint;
		}
		packet_size = get_packet_size(hnd, atoi(model_number));
		
		/* ---------------------------------------------------------------------
		    start session
		*/
		mode = CNNL_JOB_WAITING;
		{
			int j=0, ret;
			
			if (!(mode & CNNL_JOB_CANCELLED)){ // if job is not cancelled
				while (!(mode & CNNL_JOB_CANCELLED)){
					// request to start session
					if ((ret=CNNL_SessionStart(hnd, user, hostname, job, 3, 9000)) == CNNL_RET_SUCCESS){
						// succeed to start session
						mode=CNNL_JOB_PRINTING;
						break;
					}
					
					// failed to start session
					if (ret == CNNL_RET_BUSY){
						for (j=0; j<WAITTIME_START_SESSION; j++, sleep(1)){
							// cancelled 
							CheckParentProcess(hnd);							
							if ((mode & CNNL_JOB_CANCELLED)) goto error_close;
						}
					} else {
						fprintf(stderr, "INFO: cannot start printing; will retry in %d seconds...\n", WAITTIME_RETRY_SEARCH);
						
						for (j=0; j<WAITTIME_RETRY_SEARCH; j++, sleep(1)){
							// cancelled 
							CheckParentProcess(hnd);
							if ((mode & CNNL_JOB_CANCELLED)) goto error_init;
						}
						
						CNNL_Close(hnd);
						CNNL_Terminate(&hnd);
						hnd = NULL;
						goto init_printing;
					}
				}
			}
			if ((mode & CNNL_JOB_CANCELLED)){
				goto error_job_cancelled;
			}
		}
		fprintf(stderr, "INFO: \n");
		
		/* set timeout */
		CNNL_SetTimeout(hnd, SESSION_TIMEOUT, 3, 15000);
		
		/* start printing */
		if (!(mode & CNNL_JOB_ERROR) && start_print(hnd, 3, 9000) != CNNL_RET_SUCCESS){
			errcode = 1;
			mode |= CNNL_JOB_ERROR;
			fprintf(stderr, "ERROR: error occurred while preparing(%d)\n", __LINE__);
			goto error_printing;
		}
		
		/* ---------------------------------------------------------------------
		    print(after this line, response error is fatal; job is canceled)
		*/
		
		/* send start command... */
		if (is_direct == 0 && command == CNNL_COMMAND_IVEC){
			// IVEC
			dispatchCommandIVEC(hnd, CNCL_COMMAND_POWERON);
			
			if (dispatchCommandIVEC(hnd, CNCL_COMMAND_START1) < 0){
				errcode = 1;
				mode |= CNNL_JOB_ERROR;
				fprintf(stderr, "ERROR: error occurred while printing(%d)\n", __LINE__);
				goto error_printing;
			}
			
			if (dispatchCommandIVEC(hnd, CNCL_COMMAND_START2) < 0){
				errcode = 1;
				mode |= CNNL_JOB_ERROR;
				fprintf(stderr, "ERROR: error occurred while printing(%d)\n", __LINE__);
				goto error_printing;
			}
		} else {
			// standard commands
		}
		
		/* send print data... */
		{
			// waiting for print data...
			fprintf(stderr, "INFO: waiting print data ...\n");
			len = fread_with_retry(rbuffer, READ_BUFFER_SIZE, fp);
			if ((mode & CNNL_JOB_ERROR)){
				errcode = 1;
				fprintf(stderr, "ERROR: error occurred while printing(%d)\n", __LINE__);
				goto error_close;
			}
			
			p = rbuffer;
			fprintf(stderr, "INFO: \n");
			while (!(mode & CNNL_JOB_ERROR) && !(mode & CNNL_JOB_CANCELLED) && len > 0){
				
				if (sendData(hnd, p, len, SEND_PRINT_DATA, fp) < 0){
					errcode = 1;
					mode |= CNNL_JOB_ERROR;
					fprintf(stderr, "ERROR: error occurred while printing(%d)\n", __LINE__);
					goto error_printing;
				}
				
				len = fread_with_retry(rbuffer, READ_BUFFER_SIZE, fp);
				p   = rbuffer;
				
				// check if printer is working
				if (working != 1){
					tmp_ret = check_print(hnd, 3, 9000);
					if (tmp_ret == CNNL_RET_SUCCESS) working = 1;
				}
				
				usleep(40*1000);
			}
			if ((mode & CNNL_JOB_CANCELLED)) goto error_job_cancelled;
		}
		
		/* send end command... */
		if (is_direct == 0 && command == CNNL_COMMAND_IVEC){
			if (dispatchCommandIVEC(hnd, CNCL_COMMAND_END) < 0){
				errcode = 1;
				mode |= CNNL_JOB_ERROR;
				fprintf(stderr, "ERROR: error occurred while printing(%d)\n", __LINE__);
				goto error_printing;
			}
		}
		
		/* wait until printer starts working (for utility) */
		for (count=0; working!=1 && count<10; sleep(1)){
			tmp_ret = check_print(hnd, 3, 6000);
			if (tmp_ret == CNNL_RET_SUCCESS){
				break;
			} else if (tmp_ret == CNNL_RET_POWEROFF){
				goto error_job_cancelled;
			} else {
				count++;
			}
			if ((mode & CNNL_JOB_CANCELLED)) goto error_job_cancelled;
		}
		
		/* wait until printer is idle */
		if (!(mode & CNNL_JOB_ERROR) && end_print(hnd, 3, 9000) != CNNL_RET_SUCCESS){
			// cannot get end of print
			errcode = 1;
			mode |= CNNL_JOB_ERROR;
			fprintf(stderr, "ERROR: error occurred while printing(%d)\n", __LINE__);
			goto error_printing;
		}
		
		/* ---------------------------------------------------------------------
		    close printer
		*/
error_job_cancelled:
		
error_printing:
		
		if ((mode & CNNL_JOB_ERROR) || (mode & CNNL_JOB_CANCELLED)){
			CNNL_SoftReset(hnd, 5, 30000);
		}
		CNNL_SessionEnd(hnd, 5, 30000);

error_close:
		if (lib_handle != NULL) dlclose(lib_handle);
		CNNL_Close(hnd);
		
error_open:
		CNNL_Terminate(&hnd);
		
error_init:
		fprintf(stderr, "INFO: \n");
		free(rbuffer);
	}
	
	// read buffer(flush)
	{
		unsigned char dummy;
		while (fread(&dummy, sizeof(unsigned char), 1, fp) > 0);
	}
	fflush(stdout);
	fflush(stderr);
	
	// wait for next job
	sleep(1);
	
	// clear error if job is cancelled
	if (mode & CNNL_JOB_CANCELLED) errcode = 0;
	
	return (errcode == 0)? 0: 1;
}


/*******************************************************************************
	_ij_network_search
********************************************************************************/
static int _ij_network_search(int search_type, int is_installer){
	CNNLHANDLE    hmdl           = NULL;
	unsigned long latest_version = CNNL_LIB_LATEST_VERSION;
	unsigned long param_size     = sizeof(unsigned long);
	CNNLNICINFO   *nic;
	char          model[STRING_SHORT];
	char          model2[STRING_SHORT];
	char          ipaddr[STRING_SHORT];
	int           i=0, j=0, max = MAX_COUNT_OF_PRINTERS, found=0;
	
	if (CNNL_Init(&hmdl) != CNNL_RET_SUCCESS) goto error;
	
	if (CNNL_Config(hmdl, CNNL_CONFIG_SET_VERSION, &latest_version, &param_size) != CNNL_RET_SUCCESS){
		goto error;
	}
	
	// find printers
	nic = (CNNLNICINFO *)malloc(sizeof(CNNLNICINFO)*max);
	memset(nic, 0x00, sizeof(CNNLNICINFO)*max);
	
	if (CNNL_SearchPrintersEx(hmdl, nic, CACHE_PATH, max, &found, search_type, 1, 5000) == CNNL_RET_SUCCESS){
		
		for (j=0; j<found; j++){
			
			memset(model, 0x00, sizeof(model));
			memset(model2, 0x00, sizeof(model2));
			
			memset(ipaddr, 0x00, STRING_SHORT);
			snprintf(ipaddr, STRING_SHORT-1, "%d.%d.%d.%d", 
					nic[j].ipaddr[0],nic[j].ipaddr[1],nic[j].ipaddr[2],nic[j].ipaddr[3]);
			
			if (CNNL_OpenEx(hmdl, ipaddr, CNNET_TYPE_PRINTER, 1, 3000) == CNNL_RET_SUCCESS){
				if (CNNL_GetModelName(hmdl, model, STRING_SHORT-1, 1, 3000) == CNNL_RET_SUCCESS){
					
					for (i=0; model[i]!='\0'; i++){
						if (model[i] == ' '){
							model2[i]='-';
						} else {
							model2[i]=model[i];
						}
					}
					
					if (is_installer == 0){
						/* cups list device mode */
						printf("network cnijnet:/%02X-%02X-%02X-%02X-%02X-%02X \"%s\" \"%s_%02X-%02X-%02X-%02X-%02X-%02X\"\n", 
							nic[j].macaddr[0],nic[j].macaddr[1],nic[j].macaddr[2],
							nic[j].macaddr[3],nic[j].macaddr[4],nic[j].macaddr[5],
							model,
							model2,
							nic[j].macaddr[0],nic[j].macaddr[1],nic[j].macaddr[2],
							nic[j].macaddr[3],nic[j].macaddr[4],nic[j].macaddr[5]);
					} else {
						/* installer mode */
						printf("network cnijnet:/%02X-%02X-%02X-%02X-%02X-%02X \"%s\" \"IP:%s\"\n", 
							nic[j].macaddr[0],nic[j].macaddr[1],nic[j].macaddr[2],
							nic[j].macaddr[3],nic[j].macaddr[4],nic[j].macaddr[5],
							model, ipaddr);
					}
				}
				CNNL_Close(hmdl);
			}
		}
	} else {
		free(nic);
		goto error;
	}
	
	free(nic);
	CNNL_Terminate(&hmdl);
	
	return 0;
	
error:
	if (hmdl!= NULL) CNNL_Terminate(&hmdl);

	return 0;
}

/*******************************************************************************
	_ij_network_terminate
********************************************************************************/
static void _ij_network_terminate(int sig_code){
	fprintf(stderr, "DEBUG: _ij_network_terminate called(%d)\n", __LINE__);
			
	CNNL_Abort(hnd);
	mode |= CNNL_JOB_CANCELLED;
}


/*******************************************************************************
	fread_with_retry
********************************************************************************/
unsigned long fread_with_retry(char *rbuffer, unsigned long bufsize, FILE *fp){
	unsigned long d_time;
	fd_set  fds;
	struct timeval timeout;
	int errorcount=0;
	
	while (!(mode & CNNL_JOB_CANCELLED) && !(mode & CNNL_JOB_ERROR)){
		CheckParentProcess(hnd);
		
		timeout.tv_sec = 3;
		timeout.tv_usec = 0;
		
		FD_ZERO(&fds);
		FD_SET(0,&fds);
		select(1,&fds,NULL,NULL,&timeout);
		
		if(FD_ISSET(0,&fds)){
			size_t s = fread(rbuffer, sizeof(char), bufsize, fp);
			
			if (ferror(fp) == 0){
				return (s * sizeof(char));
			} else {
				mode |= CNNL_JOB_ERROR;
				return 0;
			}
		} else {
			// keep connection
			if (CNNL_GetTimeout(hnd, &d_time, 3, 6000) != CNNL_RET_SUCCESS){
				if (errorcount > 10){
					mode |= CNNL_JOB_ERROR;
					return 0;
				} else {
					errorcount++;
				}
			} else {
				errorcount=0;
			}
		}
	}
	return 0;
}

