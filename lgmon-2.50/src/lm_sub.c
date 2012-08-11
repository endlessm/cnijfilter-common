/*  Canon Bubble Jet Print Filter.
 *  Copyright CANON INC. 2001-2005
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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

/*
  Device ID request function
*/
int get_printer_devid()
{
	return 0;
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

int lm_create_server_socket()
{
	struct sockaddr_in sin;
	int server_fd;
	int i;

	if((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		return -1;

	i = 1;
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));

	sin.sin_family = AF_INET;
	sin.sin_port = htons(SM_COM_PORT);
	memset(&sin.sin_addr, 0, sizeof(sin.sin_addr));

	if(bind(server_fd, (struct sockaddr *)&sin, sizeof(sin))){
		close(server_fd);
		return -1;
	}

	if(listen(server_fd, 5)){
		close(server_fd);
		return -1;
	}

	return server_fd;
}

int lm_wait_client_connect(int fd)
{
	struct sockaddr_in sin;
	size_t adrlen = sizeof(struct sockaddr_in);
	int client_fd;

	client_fd = accept(fd, (struct sockaddr *)&sin, &adrlen);

	return client_fd;
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

	if((r_size = p_dvacs->ptdev_read(dev_path, buf, MAX_STATBUF)) < 0){
#ifdef DEBUG
		fprintf(log_path, "status read error(R)=%x\n",errno);
		fflush(log_path);
#endif
		return errno;
	}

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

int check_arg(int ac, char **av)
{
	int i;
	int error = -1;

	if(ac == 1)
		return -1;

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

		if(strcmp(&(av[i][0]), "--header") == 0)
			header_data = 1;

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
        char *buf;
        int reg = 0;
        lmsm_socket sm_data;
	int retry;
	int r_bytes;

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


#ifdef DEBUG
	if(r_bytes != 0){
		fprintf(log_path, "STATUS=%s\n", buf+2);
		fflush(log_path);
	}
#endif

	if(print_system == PRNSYS_LPR){
		/* status return to socket(used by status monitor) */
		/* create socket data */
	        sm_data.socket_type = LMtoSM;
		sm_data.command     = 0;
		sm_data.device_type = device_type; /* USB or PARPORT */
		memcpy(sm_data.prn_data.stat.stat_buffer, buf, MAX_STATBUF);

		if(rback->rback_handle > 0)
			write(rback->rback_handle, &sm_data, sizeof(sm_data));
	}
	else{
		/* status return to stderr(used by CUPS system) */

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

	rback->fault = sm_data.prn_data.stat.printer_fault; /* save fault status */
	if(rback->st_buf != NULL)
		memcpy(rback->st_buf, buf, MAX_STATBUF);

	free(buf);

	return r_bytes;
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

