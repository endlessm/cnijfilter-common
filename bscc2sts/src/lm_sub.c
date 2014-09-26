/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2013
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

#include	<arpa/inet.h>
#include	<netinet/in.h>
#include	<unistd.h>
#include	<sys/socket.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sys/ipc.h>
#include	<sys/sem.h>
#include	<linux/lp.h>
#include	<stdio.h>
#include	<string.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<signal.h>
#include	<sys/ioctl.h>
#include	<stdlib.h>
#include	<errno.h>					/* asm/errno.h -> errno.h */

#include	"lmsmsock.h"
#include	"lm.h"
#include	"config.h"
#include	"bscc2sts.h"

#include "cncl.h"
#include "cncldef.h"
#include "cnclcmdutils.h"


/* semapho union define */
union semun
{
	int val;                           /* value for SETVAL */
	struct semid_ds *buf;              /* buffer for IPC_STAT & IPC_SET */
	unsigned short int *array;         /* array for GETALL & SETALL */
	struct seminfo *__buf;             /* buffer for IPC_INFO */
};

extern int sem_id;
extern char *stamon_arg[ARGV_MAX];
extern int filter_exist;
extern int device_type;
extern int errno;
extern int print_system;
extern struct ptdev_func dev_access;
extern struct ptdev_func *p_dvacs;
extern unsigned int total_bytes;
extern int header_data;

extern int ivec_poweroff_flag;
extern int command_type;

#ifdef DEBUG
FILE *log_path;
#endif

int create_sem(int *);
int create_arg(int, char **);

/*
   LP access low level functions
*/
int read_lp_p(int dev_path, char *buf, int size)
{
	return read(dev_path, (void *)buf, (size_t)size);
}

int write_lp_p(int dev_path, char *buf, int size)
{
	return write(dev_path, (void *)buf, (size_t)size);
}

int ioctl_lp_p(int dev_path, int request , int arg)
{
	return ioctl(dev_path, request, arg);
}

int poll_lp_p(void *ptr, unsigned int nfds, int timeout)
{
	return 0;
}

/*
   USB access low level functions
*/
int read_usb_p(int dev_path, char *buf, int size)
{
	return read(dev_path, (void *)buf, (size_t)size);
}

int write_usb_p(int dev_path, char *buf, int size)
{
	return write(dev_path, (void *)buf, (size_t)size);
}

int ioctl_usb_p(int dev_path, int request , int arg)
{
	return ioctl(dev_path, request, arg);
}

int poll_usb_p(void *ptr, unsigned int nfds, int timeout)
{
	return 0;
}

/*
   1394 access low level functions
*/
int read_1394_p(int dev_path, char *buf, int size)
{
	return 0;
}

int write_1394_p(int dev_path, char *buf, int size)
{
	return 0;
}

int ioctl_1394_p(int dev_path, int request , int arg)
{
	return 0;
}

int poll_1394_p(void *ptr, unsigned int nfds, int timeout)
{
	return 0;
}

/*******************************/
/*  Device ID request function */
/*******************************/
int get_printer_devid()
{
	char	devid[1024];
	char	*ivec = NULL;
	
	memset(devid, '\0', sizeof(devid));

	if (ioctl(PRNT_PATH, _IOC(_IOC_READ, 'P', 1, sizeof(devid)), devid) == 0){
		if ((ivec = strstr(devid+2, "MFG:")) != NULL){
			if ((ivec = strstr(ivec, "Canon")) != NULL){
				if ((ivec = strstr(ivec, "CMD:")) != NULL){
					if ((ivec = strstr(ivec, "IVEC,")) != NULL){
						command_type = IVEC__COMMAND;
					}else{
						command_type = NORMAL_COMMAND;
					}
				}	
			}
     	}
	}

	return command_type;
}

int lm_init(int dev_path)
{
	int error;
	struct stat st;

	/* printer access semapho create */
	error = create_sem(&sem_id);
	if(error)
		return error;

        fstat(dev_path, &st);
        device_type = (st.st_rdev&0x00ff00)>>8;

	switch(device_type){
	case DEVICE_TYPE_LP:
#ifdef DEBUG
		write_log("device type LP\n");
#endif
		/* parport setup */
		p_dvacs->ptdev_read  = read_lp_p;
		p_dvacs->ptdev_write = write_lp_p;
		p_dvacs->ptdev_ioctl = ioctl_lp_p;
		p_dvacs->ptdev_poll  = poll_lp_p;

		get_printer_sem(sem_id);
		/* error abort select */
		p_dvacs->ptdev_ioctl(dev_path, LPABORT, 1);
		/* Non Blocking I/O select */
		fcntl(dev_path, F_SETFL, fcntl(dev_path, F_GETFL, 0) | O_NONBLOCK);
		release_printer_sem(sem_id);
		break;
	case DEVICE_TYPE_USB:
#ifdef DEBUG
		write_log("device type USB\n");
#endif
		/* usb setup */
		p_dvacs->ptdev_read  = read_usb_p;
		p_dvacs->ptdev_write = write_usb_p;
		p_dvacs->ptdev_ioctl = ioctl_usb_p;
		p_dvacs->ptdev_poll  = poll_usb_p;
		break;
	case DEVICE_TYPE_1394:
#ifdef DEBUG
		write_log("device type 1394\n");
#endif
		/* ieee1394 setup */
		p_dvacs->ptdev_read  = read_1394_p;
		p_dvacs->ptdev_write = write_1394_p;
		p_dvacs->ptdev_ioctl = ioctl_1394_p;
		p_dvacs->ptdev_poll  = poll_1394_p;
		break;
	default:
#ifdef DEBUG
		write_log("device type unknown(default use)\n");
#endif
		/* default device = lp */
		p_dvacs->ptdev_read  = read_lp_p;
		p_dvacs->ptdev_write = write_lp_p;
		p_dvacs->ptdev_ioctl = ioctl_lp_p;
		p_dvacs->ptdev_poll  = poll_lp_p;
		break;
	}

	return 0;
}

int create_sem(int *sem)
{
	key_t ipckey;
	union semun sem_union;
	int s;

	ipckey = IPC_PRIVATE;

	s = semget(ipckey, 1, 0666|IPC_CREAT);
	if(s == -1){
#ifdef DEBUG
		write_log("semget error\n");
#endif
		return -1;
	}

	/* init semapho=1 */
	sem_union.val = 1;
	if(semctl(s, 0, SETVAL, sem_union) == -1){
		/* error */
		remove_sem(s);
		return -1;
	}

	/* save semapho id */
	*sem = s;

	return 0;
}

int remove_sem(int sem)
{
	union semun sem_union;

	return semctl(sem, 0, IPC_RMID, sem_union);
}

int get_printer_sem(int id)
{
	struct sembuf sem_buf;

	if(device_type == DEVICE_TYPE_1394)
		return 0;

#ifndef USB_SEMA
	if(device_type == DEVICE_TYPE_USB)
		return 0;
#endif

	sem_buf.sem_num = 0;
	sem_buf.sem_op  = -1;
	sem_buf.sem_flg = SEM_UNDO;

	while(1){
		if(semop(id, &sem_buf, 1) == 0)
			break;
	}
	return 0;	
}

int release_printer_sem(int id)
{
	struct sembuf sem_buf;

	if(device_type == DEVICE_TYPE_1394)
		return 0;

#ifndef USB_SEMA
	if(device_type == DEVICE_TYPE_USB)
		return 0;
#endif

	sem_buf.sem_num = 0;
	sem_buf.sem_op  = 1;
	sem_buf.sem_flg = SEM_UNDO;

	while(1){
		if(semop(id, &sem_buf, 1) == 0) 
			break;
	}
	return 0;
}


int write_printer_command(int dev_path, char *buf, int size)
{
	int w_size;

	if(size == 0)
		return 0;

	w_size = p_dvacs->ptdev_write(dev_path, buf, size);

	if(w_size == size)
		return 0;

	return -1;
}

int do_printer_reset(int dev_path)
{
	int error;
#ifdef SOFT_RESET
	char *buf;
	char reset_com[] = {0x1b,0x5b,0x4b,0x04,0x00,0x00,0x0f,0x00,0x00};
	char ret_emu[] = {0x1b,0x40};
#else
	if(device_type == DEVICE_TYPE_USB || device_type == DEVICE_TYPE_1394)
		return 0;
#endif

	get_printer_sem(sem_id);

#ifdef SOFT_RESET
	if(device_type == DEVICE_TYPE_USB || device_type == DEVICE_TYPE_1394){
		buf = malloc(RESET_NULL_SIZE);
		if(buf == NULL){
			/* no RAM error */
			release_printer_sem(sem_id);
			return -1;
		}
		memset((void *)buf, 0, RESET_NULL_SIZE);
		error = write_printer_command(dev_path, buf, RESET_NULL_SIZE);
		if(!error)
			error = write_printer_command(dev_path, reset_com, 9);
		if(!error)
			error = write_printer_command(dev_path, ret_emu, 2);

		free(buf);
	}
	else
#endif
		error = p_dvacs->ptdev_ioctl(dev_path, LPRESET, 0);

	release_printer_sem(sem_id);

	return error;
}

int get_printer_status(int dev_path, char *buf, int *reg, int *bytes)
{
	int error;
	int status;
	int r_size = 0;
	/* Ver.3.90 delete */
	/* short	separate_flag = 0; */

	if((r_size = p_dvacs->ptdev_read(dev_path, buf, MAX_STATBUF)) < 0){
#ifdef DEBUG
		fprintf(log_path, "status read error(R)=%x\n",errno);
		fflush(log_path);
#endif
		return errno;
	}

#ifdef DEBUG
	fprintf(log_path, "r_size:1st = %d\n",r_size);
	fflush(log_path);
#endif

	/***************************************************/
	/* limit read size r_size <=1024 --> loop read xml */
	/* when core2duo... Ver3.20                        */
	/* call CNCL_GetStatusCommand() for check xml data */
	/***************************************************/
	if( command_type == IVEC__COMMAND ){

		char *buf2 = NULL;
		char *buf3 = NULL;
		short	r_size2 = 0;
		short	bscc_size = 0;
		short	count = 0;
		int		ret3 = -1;

		buf2 = (char *)malloc(MAX_STATBUF);
		if(buf2 == NULL){
			return ret3; /* no RAM */
		}
		memset(buf2, 0, MAX_STATBUF);

		buf3 = (char *)malloc(MAX_STATBUF);
		if(buf3 == NULL){
			free(buf2);
			return ret3; /* no RAM */
		}
		memset(buf3, 0, MAX_STATBUF);

		/* Printer Status Convert */
		/* Ver.3.80 fix */
		//ret3 = CNCL_GetStatusCommand( buf, r_size, buf2, MAX_STATBUF, &bscc_size );
		ret3 = CNCL_GetStatusCommand( buf, MAX_STATBUF, buf2, r_size, &bscc_size );

#ifdef DEBUG
		fprintf(log_path, "buf$$$$$$$ = %s\n",buf);
		fprintf(log_path, "ret3$$$$$$$ = %d\n",ret3);
		fflush(log_path);
#endif

		/* get status quickly for Ver.3.20 a3 */
		if( (ret3 == -1) && (r_size > 0) ){
		//if( ret3 == -1 ){
			while(1){
				/* for Ver.3.90 delete */
				/* separate_flag = 1; */
				count++;
				if(count == 5) break;
				sleep(2);
#ifdef DEBUG
				fprintf(log_path, "###2 sleep(2)\n");
				fflush(log_path);
#endif
				//sleep(4);
				if((r_size2 = p_dvacs->ptdev_read(dev_path, buf3, MAX_STATBUF)) < 0){
				//if((r_size2 = p_dvacs->ptdev_read(dev_path, &buf[r_size], (MAX_STATBUF - r_size))) < 0){
					free(buf3);
					free(buf2);
					return errno;
				}
				if( (r_size2 + r_size) >= MAX_STATBUF ) break;
				memcpy( &buf[r_size], buf3, r_size2 );

				r_size += r_size2;
				if(r_size >= MAX_STATBUF) break;
#ifdef DEBUG
				//fprintf(log_path, "buf3 = %s\n",buf3);
				fprintf(log_path, "r_size:222222ed = %d\n",r_size);
				fflush(log_path);
#endif
				/* Ver.3.80 fix */
				//ret3 = CNCL_GetStatusCommand( buf, r_size, buf2, MAX_STATBUF, &bscc_size );
				ret3 = CNCL_GetStatusCommand( buf, MAX_STATBUF, buf2, r_size, &bscc_size );
#ifdef DEBUG
				fprintf(log_path, "ret3##### = %d\n",ret3);
				fflush(log_path);
#endif
				if(ret3 == OK) break;
			}
		}

		free(buf3);
		free(buf2);
	}
	
/* Ver.3.90 delete	
#ifdef DEBUG
		fprintf(log_path, "separate_flag##### = %d\n",separate_flag);
		fflush(log_path);
#endif
	if( separate_flag == 0 ){
		sleep(2);
#ifdef DEBUG
		fprintf(log_path, "###0 sleep(2)\n");
		fflush(log_path);
#endif
	}
*/
	/***************************************************/

	*bytes = r_size;

        if(device_type == DEVICE_TYPE_USB || device_type == DEVICE_TYPE_1394){
                *reg = PARPORT_NFAULT; /* set default(dummy) */
                return 0;
        }

	error = p_dvacs->ptdev_ioctl(dev_path, LPGETSTATUS, (int)&status);
	if(!error){
		*reg = status;
		return 0;
	}

#ifdef DEBUG
	fprintf(log_path, "status read error(I)=%x\n",errno);
	fflush(log_path);
#endif

	return errno;
}

#define WSIZE_OPTION "--utilbyte"
#define DIRECTMODE "--direct"

int check_arg(int ac, char **av)
{
	int i;
	int error = -1;

	if(ac == 1)
		return -1;

	/* for init */
	ivec_poweroff_flag = NORMAL_POWEROFF;
	
	for(i = 1;ac > i;i++){
		/* check gui flag */
		if((error == -1) && (strcmp(&(av[i][0]), "--gui") == 0)){
			/* create argv(stamon_arg) for status monitor */
			create_arg(ac, av);
			error = 0; /* "--gui" detect */
			continue;
		}
		/* check parent process */
		if(strcmp(&(av[i][0]), "--noparent") == 0)
			filter_exist = 0;
		else if(strcmp(&(av[i][0]), "--cups") == 0)
			print_system = PRNSYS_CUPS; /* CUPS system detected */

		/* check write size option */
		if(strncmp(&(av[i][0]), WSIZE_OPTION, strlen(WSIZE_OPTION)) == 0){
			total_bytes = atoi(&(av[i+1][0]));
			/*
			sscanf(&(av[i][strlen(WSIZE_OPTION)]), "%d", &total_bytes);
			*/
		}

		/* check direct mode */
		if(strncmp(&(av[i][0]), DIRECTMODE, strlen(DIRECTMODE)) == 0){
			/* for Power OFF */
			ivec_poweroff_flag = IVEC_POWEROFF;
#ifdef DEBUG
			fprintf(log_path, "###ivec_poweroff_flag= %d ###\n",ivec_poweroff_flag);
			fflush(log_path);
#endif
		}

	}
#ifdef DEBUG_CUPS
	print_system = PRNSYS_CUPS;
#endif

	return error; 
}

int create_arg(int ac, char **av)
{
	int i;

	/* copy "/usr/local/bin/stsmon" string */
	stamon_arg[0] = strdup(STMON_PATH);

	/* copy argv(from bjfilter) */
	for(i = 1; ac > i; i++){
		stamon_arg[i] = strdup(av[i]);
	}

	stamon_arg[ac]   = NULL;

#ifdef DEBUG
	i = 0;
	while(1){
		write_log(stamon_arg[i++]);
		if(stamon_arg[i] == NULL)
			break;
		write_log(" ");
	}
	write_log("\n");
#endif

	return 0;
}

int free_arg()
{
	int i = 0;

	while(1){
		free(stamon_arg[i++]);
		if(stamon_arg[i] == NULL)
			break;
	}

	return 0;
}



#ifdef DEBUG
void create_log(void)
{
        FILE *path;

        path = fopen("/var/log/log.txt", "w");

        log_path = path;
        write_log("**********  LOG start  ***********\n");
}

void write_log(char *str)
{
	if(log_path == 0)
		return ;

        fwrite(str, 1, strlen(str), log_path);
        fflush(log_path);
}
#endif

int signal_setup(int sig, void (*func)())
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = func;

	while(1){
		if(sigaction(sig, &sa, NULL) == 0)
			break;
#ifdef DEBUG
		write_log("sigaction error\n");
#endif
	}

	return 0;
}


int status_to_viewer(struct bjst_rback *rback)
{
	int error;
	char *buf = NULL;
	int reg = 0;
	lmsm_socket sm_data;
	int retry;
	int r_bytes;
	int ret3=-1;

	buf = (char *)malloc(MAX_STATBUF);
	if(buf == NULL)
		return 0; /* no RAM */

	memset(buf, 0, MAX_STATBUF);
	r_bytes = 0;
	reg = 0;

        /* printer status get */
	for(retry = 3; retry > 0; retry --){
        	error = get_printer_status(rback->dev_handle, buf, &reg, &r_bytes);
		if(!error || error == EAGAIN)
			break;
	}

	switch(error){
		case 0:
			/* read SUCCESS */
			if(reg & PARPORT_NFAULT)
				sm_data.prn_data.stat.printer_fault = LM_PRN_NORMAL;
			else
				sm_data.prn_data.stat.printer_fault = LM_PRN_FAULT;
			break;
		case EAGAIN:
			/* no read data */
			sm_data.prn_data.stat.printer_fault = LM_PRN_NORMAL;
			break;
		default:
			/* read error */
			sm_data.prn_data.stat.printer_fault = LM_PRN_POWOFF; /* Power off */
#ifdef DEBUG
			write_log("Power off detect\n");
#endif
			break;
	}

//#ifdef DEBUG
//	if(r_bytes != 0){
//		fprintf(log_path, "STATUS=%s\n", buf+2);
//		fflush(log_path);
//	}
//#endif

	/* status return to stderr(used by CUPS system) */
	if(r_bytes != 0)
		ret3 = write_status_info( rback, r_bytes, buf );
		/* clear buf */
		if( ret3 < 0 )
			memset(buf, 0, MAX_STATBUF);

#if 0
	{
		output_dev   odev;

		struct {			
			char 	header[5];
			bscc2sts_tbl sts;
		}info_sts;
		int	lib_stat;

		if(r_bytes != 0){
			odev.status = 0;
			switch(device_type){
				case DEVICE_TYPE_LP:   odev.dev = 0; break;
				case DEVICE_TYPE_USB:  odev.dev = 1; break;
				case DEVICE_TYPE_1394: odev.dev = 2; break;
				default:               odev.dev = 0; break;
			}

			strncpy( &info_sts.header[0], "INFO:" ,strlen("INFO:"));

			/* Printer Status Convert */
			/* Ver.3.20 parse xml->bscc */
			if( command_type == IVEC__COMMAND ){
				/* Ver.3.80 fix */
				//ret3 = CNCL_GetStatusCommand( buf, r_bytes, buf2, MAX_STATBUF, &bscc_size );
				ret3 = CNCL_GetStatusCommand( buf, MAX_STATBUF, buf2, r_bytes, &bscc_size );
#ifdef DEBUG
				//fprintf(log_path,"buf :%s\n",buf);
				//fprintf(log_path,"buf2 :%s\n",buf2);
				//fprintf(log_path,"ret3,r_bytes,bscc_size :%d,%d,%d\n",ret3,r_bytes,bscc_size);
				//fflush(log_path);
#endif
				if( ret3 == CNCL_OK ){
					memset( buf, 0, sizeof(buf) );
					memcpy( &buf[0], &buf2[0], MAX_STATBUF );
				}
			}
			/* bscc->sts */
			lib_stat = bscc2sts(PACKAGE_PRINTER_MODEL, buf, &odev, &info_sts.sts);

			if(rback->rback_handle > 0 && lib_stat == OK )	
				write(rback->rback_handle, (void *)&info_sts, (size_t)sizeof(info_sts));
#ifdef DEBUG
			else {
				fprintf(log_path,"Status Convert Error rback_handle:%d lib_stat:%d\n",rback->rback_handle,lib_stat);
				fflush(log_path);
			}
#endif
		}
	}
#endif


	rback->fault = sm_data.prn_data.stat.printer_fault; /* save fault status */
	if(rback->st_buf != NULL)
		memcpy(rback->st_buf, buf, MAX_STATBUF);

	free(buf);

	return r_bytes;
}


/************************************************/
/* status return to stderr(used by CUPS system) */
/************************************************/
int write_status_info( struct bjst_rback *rback, int r_bytes, char *buf )
{
	int ret3=-1;
	short	bscc_size = 0;
	output_dev   odev;
	char *buf2 = NULL;
	short	w_size = 0;

	struct {			
		char 	header[5];
		bscc2sts_tbl sts;
	}info_sts;

	if(buf == NULL)	return ret3;

	buf2 = (char *)malloc(MAX_STATBUF);
	if(buf2 == NULL){
		return ret3; /* no RAM */
	}
	memset(buf2, 0, MAX_STATBUF);

	odev.status = 0;
	switch(device_type){
		case DEVICE_TYPE_LP:   odev.dev = 0; break;
		case DEVICE_TYPE_USB:  odev.dev = 1; break;
		case DEVICE_TYPE_1394: odev.dev = 2; break;
		default:               odev.dev = 0; break;
	}

	strncpy( &info_sts.header[0], "INFO:" ,strlen("INFO:"));

	/* Printer Status Convert */
	/* Ver.3.20 parse xml->bscc */
	if( command_type == IVEC__COMMAND ){
		/* Ver.3.80 fix */
		//ret3 = CNCL_GetStatusCommand( buf, r_bytes, buf2, MAX_STATBUF, &bscc_size );
		ret3 = CNCL_GetStatusCommand( buf, MAX_STATBUF, buf2, r_bytes, &bscc_size );
#ifdef DEBUG
		fprintf(log_path,"buf :%s\n",buf);
		fprintf(log_path,"buf2+2 :%s\n",buf2 + 2);
		fprintf(log_path,"ret3,r_bytes,bscc_size :%d,%d,%d\n",ret3,r_bytes,bscc_size);
		fflush(log_path);
#endif
		if( ret3 == CNCL_OK ){
			memset( buf, 0, sizeof(buf) );
			memcpy( &buf[0], &buf2[0], MAX_STATBUF );
		}
		else
			goto Err01;
	}
	/* bscc->sts */
	ret3 = bscc2sts(PACKAGE_PRINTER_MODEL, buf, &odev, &info_sts.sts);

	if(rback->rback_handle > 0 && ret3 == OK )	
		//write(rback->rback_handle, (void *)&info_sts, (size_t)sizeof(info_sts));
		w_size = write(rback->rback_handle, (void *)&info_sts, (size_t)sizeof(info_sts));
		if(w_size < 0){
			ret3 = -1;
		}
#ifdef DEBUG
	else {
		fprintf(log_path,"Status Convert Error rback_handle:%d lib_stat:%d\n",rback->rback_handle,ret3);
		fflush(log_path);
	}
#endif

Err01:	
	free(buf2);

	return ret3;
}


void signal_block(sigset_t sigmask)
{
        while(1){
                if(sigprocmask(SIG_BLOCK, &sigmask, NULL) == 0)
                        break;
        }

        return;
}


void signal_unblock(sigset_t sigmask)
{
        while(1){
                if(sigprocmask(SIG_UNBLOCK, &sigmask, NULL) == 0)
                        break;
        }

        return;
}

