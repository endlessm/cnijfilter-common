/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2009-2011
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
#include <time.h>

#include <cncldef.h>
#include <cncl.h>
#include <cnclcmdutils.h>

#include <libcnnet.h>
#include <cnijnetprn.h>
#include <cnijnetchk.h>

extern volatile int mode;
extern CNNL_PRINTCHECK_FUNC  start_print, end_print, check_print;
extern CNCLErr (*makePrintCommand)( short  , char * , short  , char *, char *);
extern CNCLErr (*checkPrintCommand)( short  , char * , short  , char * , short ) ;
extern CNCLErr (*getStatusCommand)( char * , short , char * , short , short * );
extern int packet_size;

static int getStatusCode(const char *src, const char *key, const char *val, const int index);
static int isPrinterWorking(CNNLHANDLE h, const int retry, const unsigned long timeout);

/*******************************************************************************
	get_packet_size
********************************************************************************/
unsigned long get_packet_size(CNNLHANDLE h, int model){
	int support_type=0;
	unsigned long data_size=0;
	
	if (CNNL_GetExtensionSupport(h, &support_type, 5, 15000) == CNNL_RET_SUCCESS){
		if (support_type == CNNL_COMMAND_SUPPORT){
			/* supports */
			if (CNNL_GetMaxDataSize(h, &data_size, 5, 15000) == CNNL_RET_SUCCESS){
				return data_size;
			}
		} else {
			/* not supports */
			PACKETSIZE_TABLE *p=NULL;
			PACKETSIZE_TABLE size_table[] = {
				{360,	10},
				{362,	10},
				{365,	10},
				{366,	10},
				{367,	10},
				{-1,	-1}
			};
			
			for (p=size_table; p->model>0; p++){
				if (p->model == model){
					return p->packet_size*1024;
				}
			}
		}
	}
	return 4*1024;
}

/*******************************************************************************
	parse_options
********************************************************************************/
int parse_options(OPTIONTABLE *start, int argc, char **argv){
	int i=0;
	OPTIONTABLE *current = start;
	
	memset(start, 0x00, sizeof(OPTIONTABLE));
	
	for (i=0; i<argc; i++){
		char *p = argv[i];
		
		if (strlen(p) > 3 && p[0] == '-' && p[1] == '-'){
			char *option = &p[0];
			
			current->next = (OPTIONTABLE *)malloc(sizeof(OPTIONTABLE));
			if (current->next != NULL){
				memset(current->next, 0x00, sizeof(OPTIONTABLE));
			
				current = current->next;
				strncpy(current->key, option, sizeof(current->key)-1);
			} else {
				/* failed to allocate memory */
				return -1;
			}
		} else {
			char *param = p;
			memset(current->value, 0x00, sizeof(current->value));
			strncpy(current->value, param, sizeof(current->value)-1);
		}
	}
	return 0;
}

/*******************************************************************************
	get_options
********************************************************************************/
int get_options(OPTIONTABLE *start, const char *key, char *val, const int size){
	OPTIONTABLE *current;
	
	for (current=start; current!=NULL; current=current->next){
		//fprintf(stderr, "MATCH: %s <=> %s\n",current->key, key);
		if (strcmp(current->key, key)==0){
			if (key != NULL){
				if (val != NULL){
					strncpy(val, current->value, size-1);
				}
				return 0;
			}
		}
	}
	return -1;
}

/*******************************************************************************
	release_options
********************************************************************************/
void release_options(OPTIONTABLE *start){
	OPTIONTABLE *current, *p;
	
	for (current=start; current->next!=NULL; ){
		p = current->next;
		if (current != start) free(current);
		current = p;
	}
}

/*******************************************************************************
	sendData
********************************************************************************/
int sendData(CNNLHANDLE hnd, void *buffer, unsigned long size, int sendmode, FILE *fp){
	unsigned long wsize=0, res_size=0, req_size=0;
	int ret, status;
	time_t lastchecktime=0;
	
	while (!(mode & CNNL_JOB_ERROR) && !(mode & CNNL_JOB_CANCELLED) && wsize < size){
		
		req_size = (size - wsize > packet_size)? packet_size: (size - wsize);
		ret = CNNL_DataWrite(hnd, buffer+wsize, req_size, &res_size, 5, 30000);
		
		if (ret == CNNL_RET_SUCCESS){
			wsize += res_size;
		} else if (ret == CNNL_RET_FAILURE){
			/* printing is failed */
			return -1;
		} else {
			wsize += res_size;
			usleep(40*1000);
		}
		
		/* check power off */
		if (time(NULL) - lastchecktime > 4){
			if (sendmode != SEND_IVEC){
				status = check_print(hnd, 1, 3000);
				if (status == CNNL_RET_POWEROFF){
					mode |= CNNL_JOB_CANCELLED;
					return 0;
				}
			}
			lastchecktime = time(NULL);
		}
		usleep(40*1000);
		
		CheckParentProcess(hnd);
	}
	return 0;
}

/*******************************************************************************
	DispatchCommandIVEC
********************************************************************************/
int dispatchCommandIVEC(CNNLHANDLE hnd, int type){
	char command_buffer[CNCL_MAKECOMMAND_BUF_LEN];
	char read_buffer[2048];
	static char job_id[16];
	
	unsigned long timeout = 6000;
	int error_count=0;
	
	memset(command_buffer, 0x00, sizeof(command_buffer));
	
	switch (type){
		case CNCL_COMMAND_START1:
			memset(job_id, 0x00, sizeof(job_id));
			if (makePrintCommand(type, command_buffer, sizeof(command_buffer), NULL, "1") != CNCL_OK){
				return -1;
			}
			type = CNCL_CHECK_START1;
			break;
		case CNCL_COMMAND_START2:
			if (makePrintCommand(type, command_buffer, sizeof(command_buffer), job_id, NULL) != CNCL_OK){
				return -1;
			}
			type = CNCL_CHECK_START2;
			break;
		case CNCL_COMMAND_END:
			if (makePrintCommand(type, command_buffer, sizeof(command_buffer), job_id, NULL) != CNCL_OK){
				return -1;
			}
			type = CNCL_CHECK_END;
			break;
		default:
			return -1;
	}
	
	/* send */
	if (sendData(hnd, command_buffer, strlen(command_buffer), SEND_IVEC, NULL) < 0){
		return -1;
	}
	
	/* receive */
	while (!(mode & CNNL_JOB_ERROR) && !(mode & CNNL_JOB_CANCELLED)){
		unsigned long rsize = 0;
		memset(read_buffer, 0x00, sizeof(read_buffer));
		
		usleep(100*1000);
		
		fprintf(stderr, "DEBUG: [cnijnetprn] dispatchCommandIVEC Receive(%d)\n", type);
		if (CNNL_DataRead(hnd, read_buffer, &rsize, sizeof(read_buffer), 3, timeout) == CNNL_RET_SUCCESS){
			// check response
			if (checkPrintCommand(type, read_buffer, (short)rsize, job_id, sizeof(job_id)) == CNCL_OK){
				// response status is OK
				return 0;
			}
			
			error_count = 0;
		} else {
			if (error_count > (SESSION_TIMEOUT*1000/timeout)){
				return -1;
			} else {
				error_count++;
			}
		}
		CheckParentProcess(hnd);
	}
	return -1;
}


/*******************************************************************************
	getPrinterStatus
********************************************************************************/
static int getPrinterStatus(CNNLHANDLE hnd, char *buf, unsigned long size){
	char read_buffer[2048], status_buffer[2048];
	unsigned long rsize = 0, ssize=0, copysize=0;
	
	memset(read_buffer, 0x00, sizeof(read_buffer));
	memset(buf, 0x00, sizeof(size));
	
	fprintf(stderr, "DEBUG: [cnijnetprn] getPrinterStatus\n");
	if (CNNL_DataRead(hnd, read_buffer, &rsize, sizeof(read_buffer), 3, 6000) == CNNL_RET_SUCCESS){
		short short_ssize = (short)ssize;
		memset(status_buffer, 0x00, sizeof(status_buffer));
		if (getStatusCommand(read_buffer, (short)rsize, status_buffer, sizeof(status_buffer), &short_ssize) == CNCL_OK){
			ssize = (unsigned long)short_ssize;
			copysize = (sizeof(status_buffer)-1 < ssize)? sizeof(status_buffer)-1 : ssize;
			memcpy(buf, status_buffer, copysize);
			return 0;
		} else {
			
			return 0;
		}
	}
	return -1;
}


/*******************************************************************************
	getStatusCode
********************************************************************************/
static int getStatusCode(const char *src, const char *key, const char *val, const int index){
	int i, j, start=-1;
	int len = 0, keylen=0;
	unsigned long __attribute__ ((unused)) bufsize=0; 
	char result[1024];
	char tmp[1024], *buf=NULL;
	
	if (src==NULL) return CNNL_RET_FAILURE;
	if (key==NULL) return CNNL_RET_FAILURE;
	
	bufsize = (src[0] << 8) + src[1]; 
	buf = (char*)&(src[2]);

	len = strlen(buf);
	if (len > 1023) len = 1023;
	
	keylen = strlen(key);
	
	memset(tmp, 0, sizeof(tmp));
	memset(result, 0, sizeof(result));
	memcpy(tmp, buf, len);
	
	// split string
	for (i=0; i<len; i++){
		if (tmp[i] == ';') tmp[i]='\0';
	}
	
	for (i=0; i<len; i++){
		if (strncmp((char *)&tmp[i], key, keylen) == 0){
			start = i+keylen;
			if (start >= len) return CNNL_RET_FAILURE;
		}
		if (start>=0 && tmp[i] == '\0'){
			len = i - start;
			if (len > 1023) len=1023;
			
			if (index < 0){
				strncpy(result, (char *)(tmp+start), len);
				goto success;
			} else {
				// find target string
				int tmp_idx=1, result_idx=0;
				for (j=0; j<len; j++){
					if (tmp_idx == index){
						if (*(char *)(tmp+start+j) != ','){
							result[result_idx++] = *(char *)(tmp+start+j);
						} else {
							break;
						}
					}
					if (*(char *)(tmp+start+j) == ',') tmp_idx++;
				}
				
				goto success;
			}
		}
	}
	return CNNL_RET_FAILURE;
	
success:
	if (strncmp((char *)&result, val, sizeof(result)) == 0){
		return CNNL_RET_SUCCESS;
	} else {
		return CNNL_RET_FAILURE;
	}
}


/*******************************************************************************
	isPrinterWorking
********************************************************************************/
static int isPrinterWorking(CNNLHANDLE h, const int retry, const unsigned long timeout){
	char *buf;
	char buffer[512];
	
	fprintf(stderr, "DEBUG: [cnijnetprn] IsPrinterWorking\n");

	CheckParentProcess(h);
	if (getPrinterStatus(h, buffer, sizeof(buffer)) < 0){
		return CNNL_RET_FAILURE;
	} else {
		buf = buffer+2;
		
		// check wether job is cancelled by cancel button
		if (getStatusCode((char *)buf, "DJS:", "CC", 1) == CNNL_RET_SUCCESS){
			mode |= CNNL_JOB_CANCELLED;
			return CNNL_RET_SUCCESS;
		}
		if (getStatusCode((char *)buf, "DJS:", "SC", 1) == CNNL_RET_SUCCESS){
			mode |= CNNL_JOB_CANCELLED;
			return CNNL_RET_SUCCESS;
		}
		
		// check wether printer is work
		if (getStatusCode((char *)buf, "DBS:", "DS", 1) == CNNL_RET_SUCCESS) return CNNL_RET_NOT_WORKING;
		
		// check wether printer is poweroff
		if (getStatusCode((char *)buf, "DBS:", "SL", 1) == CNNL_RET_SUCCESS) return CNNL_RET_POWEROFF;
		if (getStatusCode((char *)buf, "DBS:", "SD", 1) == CNNL_RET_SUCCESS) return CNNL_RET_POWEROFF;
		
		// check wether printer is work
		if (getStatusCode((char *)buf, "DBS:", "NO", 1) != CNNL_RET_SUCCESS
		 && getStatusCode((char *)buf, "DBS:", "UK", 1) != CNNL_RET_SUCCESS) return CNNL_RET_SUCCESS;
			
		// check pid
		if (getStatusCode((char *)buf, "PID:", "00", 2) != CNNL_RET_SUCCESS) return CNNL_RET_SUCCESS;
		
		// check doc
		if (getStatusCode((char *)buf, "DOC:", "NO", 3) != CNNL_RET_SUCCESS) return CNNL_RET_SUCCESS;
			
		// check dsc
		if (getStatusCode((char *)buf, "DSC:", "NO", 1) != CNNL_RET_SUCCESS) return CNNL_RET_SUCCESS;
		
		return CNNL_RET_NOT_WORKING;
	}
}

/*******************************************************************************
	StatusCheck Functions
********************************************************************************/
int CheckStartPrint(CNNLHANDLE h, const int retry, const unsigned long timeout){
	int i=0, ret=0;
	for (i=0; i<60 && !(mode & CNNL_JOB_ERROR) && !(mode & CNNL_JOB_CANCELLED); i++, sleep(1)){
		fprintf(stderr, "DEBUG: [cnijnetprn] CheckStartPrint(%d)\n", i);
		ret = isPrinterWorking(h, retry, timeout);
		if (ret == CNNL_RET_NOT_WORKING){
			return CNNL_RET_SUCCESS;
		} else if (ret == CNNL_RET_POWEROFF){
			return CNNL_RET_SUCCESS;
		}
	}
	return CNNL_RET_FAILURE;
}

int CheckEndPrint(CNNLHANDLE h, const int retry, const unsigned long timeout){
	int i=0, ret=0;
	for (i=0; i<900 && !(mode & CNNL_JOB_ERROR) && !(mode & CNNL_JOB_CANCELLED); i++, sleep(1)){
		fprintf(stderr, "DEBUG: [cnijnetprn] CheckEndPrint(%d)\n", i);
		ret = isPrinterWorking(h, retry, timeout);
		if (ret == CNNL_RET_NOT_WORKING){
			return CNNL_RET_SUCCESS;
		} else if (ret == CNNL_RET_POWEROFF){
			return CNNL_RET_SUCCESS;
		}
	}
	return CNNL_RET_FAILURE;
}

int CheckExecutePrint(CNNLHANDLE h, const int retry, const unsigned long timeout){
	fprintf(stderr, "DEBUG: [cnijnetprn] CheckExecutePrint\n");
	return isPrinterWorking(h, retry, timeout);
}

int CheckParentProcess(CNNLHANDLE h){
	if (getppid() == 1){
		CNNL_Abort(h);
		mode |= CNNL_JOB_CANCELLED;
	}	
	return 0;
}

