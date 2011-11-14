/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2007
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

#include	<signal.h>
#include	<sys/types.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	<errno.h>
#include	<sys/ioctl.h>
#include	<linux/lp.h>
#include	<string.h>

#ifdef DATA_LOG
#include        <sys/stat.h>
#endif

#include	"lmsmsock.h"
#include	"lm.h"

volatile static int end_signal   = 0; /* SIGTERM = program end       */
volatile static int last_signal  = 0; /* SIGUSR1 = print data is end */
volatile static int start_signal = 0; /* SIGUSR2 = data write start  */
static sigset_t sigmask;

extern int sem_id;
extern int errno;
extern int device_type;
extern int print_system;
extern struct ptdev_func *p_dvacs;
extern unsigned int total_bytes;
extern int header_data;

#define DETECT_LAST  0x01 /* SIGUSR1 detect */
#define DETECT_END   0x02 /* SIGTERM detect */
#define DETECT_START 0x04 /* SIGUSR2 detect */
#define DETECT_NOT   0    /* no signals */

#define signal_last(x)  ((x&DETECT_LAST) == DETECT_LAST)
#define signal_end(x)   ((x&DETECT_END) == DETECT_END)
#define signal_start(x) ((x&DETECT_START) == DETECT_START)

#ifdef DEBUG
extern FILE *log_path;
#endif

static int check_signals(void)
{
	int sig = 0;

	signal_block(sigmask);
	if(end_signal){
#ifdef DEBUG
		write_log("LM(P) SIGTERM receive(data_output_process)\n");
#endif
		sig |= DETECT_END; /* SIGTERM */
	}

	if(last_signal){
#ifdef DEBUG
		write_log("LM(P) SIGUSR1 receive(data_output_process)\n");
#endif
		/* data read until pipe empty */
		fcntl(DATA_PATH, F_SETFL, fcntl(DATA_PATH, F_GETFL, 0) | O_NONBLOCK);
		last_signal = 0;
		sig |= DETECT_LAST; /* SIGUSR1 */
	}

	if(start_signal){
#ifdef DEBUG
		write_log("LM(P) SIGUSR2 receive(data_output_process)\n");
#endif
		sig |= DETECT_START;
	}
	signal_unblock(sigmask);

	return sig;
}

static int read_data(char *buf)
{
	int count;
	int sig = 0;

	while(1){
		count = read(DATA_PATH , buf, MAX_DATA);
		if(count < 0){
#ifdef DEBUG
			write_log("LM(P) read error\n");
#endif
			/* read error !? and check */
			sig = check_signals();
			if(signal_last(sig))
				continue; /* retry */
			if(signal_start(sig)){
				start_signal = 0;
				continue;
			}

			return -1; /* SIGTERM or EAGAIN or other read error */
		}

		break; /* read SUCCESS */
	}

	return count;
}

void lm_dataout_sighand(int sigcode)
{
	/* SIGTERM receive */
	end_signal = 1;
}

void lm_last_sighand(int sigcode)
{
	/* SIGUSR1 receive */
	last_signal = 1;
}

void lm_start_sighand(int sigcode)
{
	/* SIGUSR2 receive */
	start_signal = 1;
}

int wait_restart(void)
{
	int sig;

	/* wait restart(BSCC success) */
	while(1){
		sig = check_signals();

		if(signal_end(sig))
			return DETECT_END; /* SIGTERM */

		if(signal_start(sig)){
			start_signal = 0;
			return DETECT_START;
		}

		pause(); /* wait signal */
	}
}

int check_power(int sm_sock_fd, int dev_path)
{
	struct bjst_rback rback;

	rback.dev_handle = dev_path;
	rback.st_buf     = NULL; /* no request status body */
	if(print_system == PRNSYS_LPR)
		rback.rback_handle = sm_sock_fd;
	else
		rback.rback_handle = STAT_PATH; /* stderr */

	status_to_viewer(&rback);

	return rback.fault;
}

static void setup_signals()
{
        /* signal mask define */
        sigemptyset(&sigmask);
        sigaddset(&sigmask, SIGTERM);
        sigaddset(&sigmask, SIGUSR1);
        sigaddset(&sigmask, SIGUSR2);

	/* setup signal handler */
	signal_setup(SIGTERM, lm_dataout_sighand);
	signal_setup(SIGUSR1, lm_last_sighand);
	signal_setup(SIGUSR2, lm_start_sighand);
}

static void wait_pstart()
{
	/* wait PRT_START */
	while(1){
		if(end_signal){
#ifdef DEBUG
			write_log("LM(P) SIGTERM receive\n");
			write_log("LM(P) data_output_process end\n");
#endif
			exit(0);
		}
		if(start_signal){
			start_signal = 0;
			break;
		}
		pause();
	}

	return;
}

#define PRN_DATA_NORMAL 0x01
#define PRN_DATA_UTIL	0x02

typedef struct {
	unsigned int type;
	unsigned int size;
} bjdata_header;

static int header_read(int sm_sock_fd, int *type, int *size)
{
	int err , __attribute__ ((unused)) result2;
	bjdata_header head;
	lmsm_socket sm_data;

	while(1){
		err = read(DATA_PATH, &head, sizeof(head));
		if(err < 0){
			if(errno == EINTR)
				return -1;
		}
		else{
			sm_data.socket_type = LMtoSM_TYPEMSG;
			if(head.type == PRN_DATA_NORMAL)
				sm_data.command = LM_PRN_DATA;
			else
				sm_data.command = LM_PRN_UTIL;

			result2 = write(sm_sock_fd, &sm_data, sizeof(sm_data));	/* message to stsmon */

			*type = head.type;
			*size = head.size;
			break;
		}
	}

	return 0;

}

static unsigned int data_output_main(int sm_sock_fd, int fix_size)
{
	int sig = 0;
	int r_size;
	int w_size;
	int dev_path = PRNT_PATH;
	unsigned int total = 0; /* total data size (wrote size) */
	char *buf;
	char *ptr;

	/* read buffer get */
	buf = (char *)malloc(MAX_DATA);
	if(!buf)
		exit(0); /* no ram */

	/* print data read(from stdin) and write(to stdout) */
	while((r_size = read_data(buf)) > 0){
		ptr = buf;
		/* data print(output) loop */
		for(;r_size > 0;r_size -= w_size){
			int __attribute__ ((unused)) err;

			signal_block(sigmask);   /* signal block */
			get_printer_sem(sem_id); /* printer lock */

			w_size = p_dvacs->ptdev_write(dev_path, ptr, r_size); /* data write -> printer */
			err = errno;
#ifdef DATA_LOG
                        if(log_hand >=0 && w_size > 0)
                                write(log_hand, ptr, w_size);
#endif

			/* write() error check (power off??) */
			if(w_size <= 0){
				w_size = 0;
				if(check_power(sm_sock_fd, dev_path) == LM_PRN_POWOFF){
#ifdef DEBUG
					write_log("LM(P) into wait_restart()\n");
#endif
					release_printer_sem(sem_id);
					signal_unblock(sigmask);

					/* wait BSCC SUCCESS */
					if(wait_restart() == DETECT_END)
						goto dataout_exit;
					else
						continue;
				}
#ifdef DEBUG
				fprintf(log_path, "LM(P) write error. normal=%x\n",err);
				fflush(log_path);
#endif
				sleep(1);
			}
			else
				total += w_size; /* total write size save */

			/* write() is normal end */
			release_printer_sem(sem_id);
			signal_unblock(sigmask);

                        if((sig = check_signals()) != 0){
                                /* signal detect */

                                if(signal_end(sig))
                                        goto dataout_exit; /* SIGTERM */
 

                                /* other signal ignore */
                                start_signal = 0;
                                last_signal  = 0;
                        }
			ptr += w_size;
		}

		/* written data size == request data size ?*/
		if(fix_size && (total >= fix_size) )
			break;
	}
dataout_exit:
	free(buf);

	return total;
}


static void data_output_normal(int sm_sock_fd)
{
	unsigned int total;

	total = data_output_main(sm_sock_fd, total_bytes);

	if(end_signal == 0){
		if(print_system == PRNSYS_CUPS){
			/* no write data ? */
			if(total == 0)
				kill(getppid(), SIGTERM);
			/* total_bytes output finish ? */
			else if(total_bytes && (total >= total_bytes))
				kill(getppid(), SIGTERM);
		}
#ifdef DEBUG
		write_log("LM(P) data_output_normal end. now waiting SIGTERM\n");
#endif

		/* wait SIGTERM */
		while(1){
			if(end_signal)
				break;
			pause();
		}
	}

	return;
}


static void data_output_header(int sm_sock_fd)
{
	int type = 0;
	int size = 0;
	unsigned int __attribute__ ((unused)) total;

	while(1){
		if(header_read(sm_sock_fd, &type, &size) != 0)
			break;

		total = data_output_main(sm_sock_fd, size);

		if(end_signal)
			break;

		if(type == PRN_DATA_NORMAL)
			break;
	}

	/* wait SIGTERM */
	while(1){
		if(end_signal)
			break;
		pause();
	}

	return;
}

int data_output_process(int sm_sock_fd)
{
#ifdef DATA_LOG
        int log_hand;

        log_hand = open("/var/log/bjfilter-data.log", O_WRONLY|O_CREAT|O_TRUNC, 0666);
#endif

	setup_signals(); /* signal setup */
	wait_pstart();   /* wait PRINT START */

#ifdef DEBUG
	write_log("LM(P) data_output_process start\n");
#endif

	if(header_data)
		data_output_header(sm_sock_fd);	/* header->prn_data type output */
	else
		data_output_normal(sm_sock_fd);	/* only prn_data type output */

#ifdef DEBUG
	write_log("LM(P) data_output_process end\n");
#endif

#ifdef DATA_LOG
        if(log_hand >=0)
                close(log_hand);
#endif

	exit(0);
}


