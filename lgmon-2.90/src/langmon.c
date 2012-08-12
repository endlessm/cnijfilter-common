/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2008
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
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<sys/wait.h>
#include	<string.h>

#include	"config.h"
#include	"lmsmsock.h"
#include	"lm.h"

int  sem_id = 0;			/* printer access semapho id */
int  filter_exist = 1;			/* parent process is bjfilter(flag) */
int  device_type;			/* Device type (USB/LP/PARPORT/1394......) */
int  print_system = PRNSYS_CUPS;		/* lpr(ng) or CUPS (default is CUPS) */
//int  print_system = PRNSYS_LPR;		/* lpr(ng) or CUPS (default is lpr(ng)) */
char *stamon_arg[ARGV_MAX];		/* arg space */
struct ptdev_func dev_access;		/* read/write dispatch struct */
struct ptdev_func *p_dvacs = &dev_access;
unsigned int total_bytes = 0;		/* write data total bytes --utilbyte=xxxxx */
int  header_data = 0;			/* bjfiler > "header-data" > data_output_process */ 

static int   data_end  = 0;             /* print data outputed flag */
static int   do_cancel = 0;		/* print cancel flag */
static pid_t stmon_pid = 0;		/* status monitor process id */
static pid_t data_pid  = 0;		/* data output process id */
static pid_t stat_pid  = 0;		/* status get process id */

volatile static int int_sig   = 0;	/* SIGINT flag */
volatile static int term_sig  = 0;	/* SIGTERM flag */
volatile static int user1_sig = 0;	/* print data end flag */
volatile static int user2_sig = 0;	/* SM(status monitor) show flag */
volatile static int hup_sig   = 0;	/* SIGHUP flag */
volatile static int pipe_sig  = 0;	/* SIGPIPE flag */
volatile static int quit_sig  = 0;	/* SIGQUIT flag */

int data_output_process(int);
int status_get_process(int);
int lm_create_server_socket(void);
int lm_wait_client_connect(int);
int write_printer_command(int, char *, int);

static int print_normal(void);
static int lm_main_fork(void);
static int connect_socket(int *, int *);
static int lm_main_lpr(int);
static int lm_main_cups(void);
static int check_signal(void);
static int check_signal_arrive(void);
static int do_prn_com(int, lmsm_socket, int);
static int do_prn_cancel(void);

#ifdef DEBUG
extern FILE *log_path;
#endif

/* signal handlers */
void sighand_int(int sig)
{
	/* SIGINT handler */
	int_sig = 1;
}

void sighand_hup(int sig)
{
	/* SIGHUP handler */
	hup_sig = 1;
}

void sighand_pipe(int sig)
{
	/* SIGPIPE handler */
	pipe_sig = 1;
}

void sighand_quit(int sig)
{
	/* SIGQUIT handler */
	quit_sig = 1;
}

void sighand_term(int sig)
{
	/* SIGTERM handler */
#ifdef DEBUG
	term_sig ++;
#else
	term_sig = 1;
#endif
}

void sighand_user1(int sig)
{
	/* SIGUSR1 handler */
	user1_sig = 1;
}

void sighand_user2(int sig)
{
	/* SIGUSR2 handler */
	user2_sig = 1;
}

void init_signals(void)
{
	signal_setup(SIGTERM, sighand_term);
	signal_setup(SIGUSR1, sighand_user1);
	signal_setup(SIGUSR2, sighand_user2);
	signal_setup(SIGINT,  sighand_int);
	signal_setup(SIGHUP,  sighand_hup);
	signal_setup(SIGPIPE, sighand_pipe);
	signal_setup(SIGQUIT, sighand_quit);
}

int main(int ac, char **arv)
{
	int error;

#ifdef DEBUG
	/* logfile=/var/log/log.txt */
	create_log();
	fprintf(log_path, "ac = %d\n", ac);
	fflush(log_path);
#endif

	/* setup signal handlers */
	init_signals();

	/* printer DEVICE ID and command line option check */
	if((error = get_printer_devid()) < 0 || check_arg(ac,arv) < 0){

		/*
		   Not Canon printer
			or
		   "--gui" option not found
		*/
#ifdef DEBUG
		write_log("Now normal printing ......\n");
#endif
		print_normal();
		exit(0);
	}

	/* create semapho and other setup */
	if((error = lm_init(PRNT_PATH))){
		exit(0);
	}

	/* monitor_process/print_process/status_process start */
	lm_main_fork();

	/* delete semapho */
	remove_sem(sem_id);
	/* free memory (status monitor argv string) */
	free_arg();

#ifdef DEBUG
	write_log("LM end \n");
#endif
	exit(0);
}

static int wait_forked_procs()
{
	int child_sm;
	int child_stat;
	int child_data;

	/* wait child process end */
	if(data_pid){
		while(1){
			if(wait(&child_data) != -1)
				break;
		}
	}
	if(stat_pid){
		while(1){
			if(wait(&child_stat) != -1)
				break;
		}
	}
	if(stmon_pid){
		while(1){
			if(wait(&child_sm) != -1)
				break;
		}
	}

	return 0;
}

/*
  Fork lgmon's process - for LPR(ng) system

       lm_main_lpr()        : parent process.
       data_output_process(): print data output process.
       status_get_process() : print status read process.
*/
static void lm_main_fork_lpr()
{
	char *nbuf;

	if((stmon_pid = fork())){
		int server_fd  = 0;
		int sm_sock_fd = 0;

		/* create socket and connect LM<->SM */
		if(connect_socket(&server_fd, &sm_sock_fd) < 0){
			/* socket error */

			if(server_fd > 0)
				close(server_fd);
			if(sm_sock_fd > 0)
				close(sm_sock_fd);

			kill(stmon_pid, SIGTERM);
			goto lm_exit;
		}

		if((stat_pid = fork())){
			if((data_pid = fork())){
				/* LM main process */

				/* exec lgmon main process */
				lm_main_lpr(sm_sock_fd);
				close(sm_sock_fd);
				close(server_fd);
			}
			else
				/* print data output process */
				data_output_process(sm_sock_fd); /* never return */
		}
		else
			/* printer status get process */
			status_get_process(sm_sock_fd); /* never return */
	}
	else{
		nbuf = (char *)malloc ((strlen (STMON_PATH)+strlen (PACKAGE)+2));
		if (nbuf == NULL)
			exit (0);
		
		memset((void*)nbuf, 0, (strlen (STMON_PATH)+strlen (PACKAGE)+1));
		strncpy(nbuf, STMON_PATH, strlen (STMON_PATH) );
		strncat(nbuf, "/", strlen("/"));
		strncat(nbuf, PACKAGE, strlen(PACKAGE));
		/* status monitor process */
		if(execv(nbuf, stamon_arg) < 0){
#ifdef DEBUG
			write_log("SM execv error\n");
#endif
		}
		exit(0); /* never arrive this point */
	}

lm_exit:
	return;
}

/*
  Fork lgmon's process - for CUPS system

       lm_main_cups()       : parent process.
       data_output_process(): print data output process.
       status_get_process() : print status read process.
*/
static void lm_main_fork_cups()
{
	if((stat_pid = fork())){
		if((data_pid = fork()))
			/* LM main process */
			lm_main_cups();
		else
			/* print data output process */
			data_output_process(-1); /* never return */
	}
	else
		/* printer status get process */
		status_get_process(-1); /* never return */

	return;
}

static int lm_main_fork()
{
	if(print_system == PRNSYS_LPR)
		lm_main_fork_lpr();
	else
		lm_main_fork_cups();

	wait_forked_procs(); /* wait child process end */

	if(do_cancel && total_bytes == 0){
		/*
			what's total_bytes ?? see below.
			if utility command(--utilbyte xxx option) : do not exec printer reset
		*/
		while(1){
			if(do_printer_reset(PRNT_PATH) == 0)
				break;
		}
	}

	return 0;
}

static int connect_socket(int *sv, int *sk)
{
	int v,k;
	int i;

	/* create socket */
	for(i = 5; i > 0; i--){
		v = lm_create_server_socket();
		if(v >= 0)
			break; /* SUCCESS */
		else{
			if(check_signal() == -1){
#ifdef DEBUG
				write_log("socket create error(signal detected)\n");
#endif
				break;
			}
		}
#ifdef DEBUG
		write_log("socket create error(no signal and retry)\n");
#endif
	}
	if(v < 0){
		/* create error */
		*sv = -1;
		*sk = -1;
		return -1;
	}

	*sv = v;

	/* connect wait */
	for(i = 5; i > 0; i--){
#ifdef DEBUG
		write_log("start accept (LM main)\n");
#endif
		k = lm_wait_client_connect(v);
		if(k >= 0)
			break; /* SUCCESS */
		else{
			if(check_signal() == -1){
#ifdef DEBUG
				write_log("socket connect error(signal detected)\n");
#endif
				break;
			}
		}
#ifdef DEBUG
		write_log("socket connect error(no signal and retry)\n");
#endif
	}
	if(k < 0){
		/* connect error */
		*sk = -1;
		return -1;
	}

	*sk = k;

	return 0;
}

static int check_signal()
{
	/* SIGTERM/SIGCHILD/SIGINT arrive? */
	if(term_sig || int_sig)
		return -1;

	return 0;
}

static int print_normal()
{
	int __attribute__ ((unused)) error = 0;
	int r_size;
	int w_size;
	char *buf;
	char *ptr;

	buf = (char *)malloc(MAX_DATA);

	signal_setup(SIGTERM, sighand_term);

	while((r_size = read(DATA_PATH, buf, MAX_DATA)) > 0){
		ptr = buf;
		for(;r_size > 0;r_size -= w_size){
			w_size = write(PRNT_PATH, ptr, r_size);
			if(w_size < 0){
				/* write error */
				error = -1;
				goto print_normal_exit;
			}
			ptr += w_size;
		}
	}

print_normal_exit:
	if(term_sig)
		do_printer_reset(1);

	free(buf);
	return 0;
}

static int lm_main_lpr(int sm_sock_fd)
{
	int error = 0;
	int prn_end = 0;
	lmsm_socket sm_data;
	int first_start = 0;

#ifdef DEBUG
	write_log("into lm_main_lpr\n");
#endif

	sleep(1); /* wait child process setup */

	/*
	  LM<->SM socket read loop start.
	  signal-infomation
		SIGTERM ---- program end.
		SIGUSR1 ---- print data end.
		SIGUSR2 ---- status monitor show request.
		SIGINT  ---- program end.
	*/
	while(!prn_end){
		/* socket read */
		error = read(sm_sock_fd, &sm_data, sizeof(sm_data));

		prn_end = check_signal_arrive();

		if(error < 0)
			continue; /* socket read error */

		switch(sm_data.command){
			case LM_PRN_COM:
				/* output printer command */
				get_printer_sem(sem_id);     /* lock printer */
				prn_end = do_prn_com(sm_sock_fd, sm_data, first_start);
				release_printer_sem(sem_id); /* release printer */
#ifdef DEBUG
				write_log("PRN command SUCCESS\n");
#endif
				break;
			case LM_PRN_CANCEL:
				prn_end = do_prn_cancel();
				break;
			case LM_PRN_START:
#ifdef DEBUG
				write_log("SM message LM_PRN_START\n");
#endif
				if(first_start != 0)
					break;

				/* printing start!! */
				kill(data_pid, SIGUSR2); /* message to data_output_process */
				first_start = 1; /* next START is ignore */
				break;
			case LM_PRN_END:
#ifdef DEBUG
				write_log("SM message LM_PRN_END\n");
#endif
				/* end of all job's */
				/* print end(last page ejected from printer) */
				do_cancel = 1;
				prn_end = 1;
				break;
			default:
				break;
		}
	}

	/* print end */

	/* child process end */
	if(data_pid)
		kill(data_pid, SIGTERM);
	if(stat_pid)
		kill(stat_pid, SIGTERM);
	if(stmon_pid)
		kill(stmon_pid, SIGTERM);

	return 0;
}


static int lm_main_cups(void)
{
	int prn_end = 0;

#ifdef DEBUG
	write_log("into lm_main_cups\n");
#endif
	/*
	   wait signal ....
		SIGUSR2 : Print start(restart). Signal from status_process(BSCC success).
		SIGTERM : Print end. Signal from CUPS/status_process(power off detect).
		SIGINT
		SIGHUP
		SIGPIPE : Print abort. Signal from CUPS.
	*/
	while(!prn_end){
		prn_end = check_signal_arrive();
		if(!prn_end)
			pause(); /* wait signal .... */
	}
#ifdef DEBUG
	fprintf(log_path, "sigterm count = %d\n", term_sig);
	fprintf(log_path, "sigint  count = %d\n", int_sig);
	fprintf(log_path, "sigpipe count = %d\n", pipe_sig);
	fprintf(log_path, "sighup  count = %d\n", hup_sig);
	fprintf(log_path, "sigquit count = %d\n", quit_sig);
	fflush(log_path);
#endif

	/* child process end */
	if(data_pid)
		kill(data_pid, SIGTERM);
	if(stat_pid)
		kill(stat_pid, SIGTERM);

	return 0;
}

static int check_signal_arrive(void)
{
#ifdef DEBUG
	if(term_sig)
		write_log("SIGTERM receive(LM main)\n");
	if(user1_sig)
		write_log("SIGUSR1 receive(LM main)\n");
	if(user2_sig)
		write_log("SIGUSR2 receive(LM main)\n");
	if(int_sig)
		write_log("SIGINT receive(LM main)\n");
	if(hup_sig)
		write_log("SIGHUP receive(LM main)\n");
	if(pipe_sig)
		write_log("SIGPIPE receive(LM main)\n");
	if(quit_sig)
		write_log("SIGQUIT receive(LM main)\n");
#endif

	if(term_sig || int_sig || hup_sig || pipe_sig || quit_sig){
		/* SIGINT from lpd ? */
		if(int_sig || hup_sig)
			do_cancel = 1; /* printer reset */

		if(print_system == PRNSYS_CUPS && term_sig)
			do_cancel = 1;

		return 1; /* program end */
	}

	if(print_system == PRNSYS_CUPS){
		if(user2_sig){
			/* printing start(restart) */
			kill(data_pid, SIGUSR2); /* message to data_output_process */
			user2_sig = 0;
		}

		/* Under CUPS system SIGUSR1 not use(ignore). */
		if(user1_sig)
			user1_sig = 0;

		goto _END;
	}

	/* print data end from bjfilter? */
	if(user1_sig){
		/* message to data_output_process (print data is end) */
		kill(data_pid, SIGUSR1);
		user1_sig = 0;
		data_end = 1; /* print data output is end */
		goto _END;
	}

	/* show SM ? */
	if(user2_sig){
		/* status monitor show signal send */
		kill(stmon_pid, SIGUSR1);
		user2_sig = 0;
		goto _END;
	}

_END:
	if(term_sig || int_sig || hup_sig || pipe_sig || quit_sig){
		/* SIGINT from lpd ? */
		if(int_sig || hup_sig)
			do_cancel = 1; /* printer reset */

		if(print_system == PRNSYS_CUPS && term_sig)
			do_cancel = 1;

		return 1; /* program end */
	}

	/* no signals. */
	return 0;
}

static int do_prn_com(int sm_sock_fd, lmsm_socket sm_data, int first_start)
{
	int error;
	Prcom_st ptr;
	int count;
	struct bjst_rback rback;

	ptr = &(sm_data.prn_data.com);
#ifdef DEBUG
	write_log("SM message LM_PRN_COM\n");
	write_log(ptr->com_buffer+9);
	write_log("\n");
#endif

	rback.dev_handle   = PRNT_PATH;
	rback.rback_handle = sm_sock_fd;
	rback.st_buf       = NULL; /* no request status body */

	while(1){
		error = write_printer_command(PRNT_PATH, ptr->com_buffer, ptr->com_size);
		count = status_to_viewer(&rback);
		if(error){
			if(check_signal_arrive() == 1)
				return 1; /* SIGINT/SIGTERM detect(abort) */
#ifdef DEBUG
			write_log("PRN_COM error(retry)\n");
#endif
			sleep(2); /* retry */
			continue;
		}

		/* write command until printer respond */
		if(count)
			break;
		else
			sleep(1);
	}

	if(first_start)
		kill(data_pid, SIGUSR2); /* message to output process(restart) */

	return 0;
}

static int do_prn_cancel(void)
{
#ifdef DEBUG
	write_log("SM message LM_PRN_CANCEL\n");
#endif
	/*
	   print data already outputed to printer.
			or
	   bjfilter is not parent process. ----> force print end.
	*/
	if(data_end == 1 || filter_exist == 0){
		do_cancel = 1;
		return 1;
	}

	/* message to bjfilter (lgmon will soon end) */
	user1_sig = 0;
	kill(getppid(), SIGUSR1);
	sleep(1);

	/* wait until SIGUSR1(bjfilter ACK) receive */
	while(1){
		/* wait signal from bjfilter */
		if(user1_sig | term_sig | int_sig)
			break; /* ACK receive. */

		pause();
	}
#ifdef DEBUG
	write_log("receive SIGUSR1\n");
#endif
	do_cancel = 1;
	return 1;
}

