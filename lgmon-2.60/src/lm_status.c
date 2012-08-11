/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2010
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

#include	<signal.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<sys/wait.h>
#include	<fcntl.h>
#include	<sys/ioctl.h>
#include	<linux/lp.h>
#include	<sys/poll.h>
#include	<asm/errno.h>
#include	<stdlib.h>
#include	<string.h>

#include	"lm.h"
#include	"lmsmsock.h"

volatile static int abort_signal = 0;
static sigset_t sigmask;
static int willbe_end = 0;
extern int sem_id;
extern int device_type;
extern int errno;
extern int print_system;
extern struct ptdev_func dev_access;
extern struct ptdev_func *p_dvacs;

extern int write_printer_command();

#ifdef DEBUG
extern FILE *log_path;
#endif


static struct bjst_rback prn_st;

static int status_get_main(void);

void lm_stget_sighand(int sig)
{
	/* SIGTERM receive */
	abort_signal = 1;
}

static void wait_readtime()
{
	if(device_type == DEVICE_TYPE_USB || device_type == DEVICE_TYPE_1394)
		sleep(2);
	else
		sleep(5);
	return;
}

//#define BSCC_SSR "SSR=BST,SFA,CHD,CIL,CIR,LVR,DBS,DWS,DOC,DSC,DJS,CTK,HCF;"
#define BSCC_SSR "SSR=BST,SFA,CHD,CIL,CIR,HRI,DBS,DWS,DOC,DSC,DJS,CTK,HCF;"
#define COUNT_LO 3
#define COUNT_HI 4
#define LENGTH_HI 7
#define LENGTH_LO 8
#define BSCC_HEADSIZE 9
static int setup_bscc(int dev_path)
{
	int error;
	int count;
	char *bscc_com; 
	//                  ESC   [    K   C-lo C-hi INIT  ID  L-hi L-lo (total 9byte)
	char bscc_head[] = {0x1b,0x5b,0x4b,0x00,0x00,0x00,0x1e,0x00,0x00};
	int size = BSCC_HEADSIZE; /* bscc_head size */

	bscc_com = (char *)(malloc(512));
	if(bscc_com == NULL)
		return -1; /* no RAM */

	/* build BSCC command */
	memset(bscc_com, 0, 512);
	memcpy((void *)bscc_com, (void *)bscc_head, size);    /* BSCC header copy */
	size = strlen(BSCC_SSR);
	memcpy((void *)(bscc_com+BSCC_HEADSIZE), (void *)BSCC_SSR, size); /* BSCC body copy */
	size = strlen(BSCC_SSR) + 4;                          /* size = BSCC body + 4(INIT,ID,L-hi,L-lo) */
	*(bscc_com + COUNT_LO) = (char)(0x0000ff & size);     /* set Low  byte */
	*(bscc_com + COUNT_HI) = (char)(0x00ff00 & size);     /* set High byte */
	size = strlen(BSCC_SSR) + 2;                          /* size = BSCC body + 2(L-hi,L-lo) */
	*(bscc_com + LENGTH_LO) = (char)(0x0000ff & size);    /* set Low  byte */
	*(bscc_com + LENGTH_HI) = (char)(0x00ff00 & size);    /* set High byte */

#ifdef DEBUG
	write_log(bscc_com+BSCC_HEADSIZE);
	write_log("\n");
#endif

	size = strlen(BSCC_SSR) + BSCC_HEADSIZE;
	get_printer_sem(sem_id);
	while(1){
		if(abort_signal){
			error = -1;
			break;
		}

		count = status_to_viewer(&prn_st);	/* pre-read */

		error = write_printer_command(dev_path, bscc_com, size);
		count = status_to_viewer(&prn_st);

		if(error){
			if(abort_signal)
				break; /* SIGTERM detect */
			sleep(2);
#ifdef DEBUG
			write_log("LM(S) BSCC write failed now retry.\n");
#endif
			continue;
		}

		if(count){
#ifdef DEBUG
			write_log("LM(S) BSCC setup successed\n");
#endif
			/* BSCC setup success */
			kill(getppid(), SIGUSR2); /* data_output_process start */
			break;
		}
		else
			sleep(1);
	}

	release_printer_sem(sem_id);
	free(bscc_com);

	return error;
}

static int init_rback(int sock, int dev_path)
{
	if(print_system == PRNSYS_LPR)
		prn_st.rback_handle = sock; /* Status Monitor communication socket */
	else
		prn_st.rback_handle = STAT_PATH;    /* stderr (CUPS system) */

	prn_st.dev_handle = dev_path;
	prn_st.fault      = 0;
	prn_st.st_buf     = (char *)malloc(MAX_STATBUF);
	if(prn_st.st_buf == NULL)
		return -1; /* no RAM */

	return 0;
}

int status_get_process(int sm_sock_fd)
{

	int dev_path = PRNT_PATH;

        sigemptyset(&sigmask);
        sigaddset(&sigmask, SIGTERM);

	/* signal handler setup */
	signal_setup(SIGTERM, lm_stget_sighand);
#ifdef DEBUG
	write_log("LM(S) status_get_process start\n");
#endif

	/* status read back struct init */
	if(init_rback(sm_sock_fd, dev_path) != 0){
#ifdef DEBUG
		write_log("LM(S) init_rback() error\n");
#endif
		exit(0);
	}

	if(print_system == PRNSYS_CUPS){
		sleep(2); /* wait lm_main_cups() and data_output_process() setup */
		if(setup_bscc(dev_path) != 0){
			free(prn_st.st_buf);
#ifdef DEBUG
			write_log("LM(S) status_get_process end\n");
#endif
			exit(0);
		}
	}

	/* printer status read until SIGTERM receive */
	while(1){

		/* SIGTERM receive? */
		if(abort_signal){
#ifdef DEBUG
			write_log("LM(S) SIGTERM receive(status_get_process)\n");
#endif
			break;
		}

		if(willbe_end == 0){
			signal_block(sigmask);
			status_get_main();
			signal_unblock(sigmask);
		}

		wait_readtime();
	}

	free(prn_st.st_buf);

#ifdef DEBUG
	write_log("LM(S) status_get_process end\n");
#endif

	exit(0);
}

static int printing = 0;
#define BST_PRINTING 0x80
#define BST_BUSY     0x20
#define BST_OPCALL   0x08
#define STR_BST      "BST:"
static unsigned char get_bst(char *buf)
{
	char *ptr;
	unsigned char val = 0;
	unsigned char work[2];
	unsigned int  wk;

	ptr = strstr(buf+2, STR_BST);
	if(ptr == NULL)
		return val;

	ptr += strlen(STR_BST);
	work[0] = *ptr;
	work[1] = 0x00;
	sscanf((char*)work, "%x", &wk); /* conv Hex string to value(Hi) */
	/* sscanf(work, "%x", &wk);*/ /* conv Hex string to value(Hi) */
	val = (char)(wk<<4); 

	ptr++;
	work[0] = *ptr;
	work[1] = 0x00;
	sscanf((char*)work, "%x", &wk); /* conv HEX string to value(Lo) */
	/* sscanf(work, "%x", &wk);*/  /* conv HEX string to value(Lo) */
	val |= (char)wk;

	return val;
}
static int status_check(int s_count)
{
	struct bjst_rback *ptr = &prn_st;
	unsigned char bst;

	if(ptr->fault == LM_PRN_POWOFF){
		/* power off detect */

		if(printing){
			kill(getppid(), SIGTERM); /* after print start -> force print end */
			willbe_end = 1;
		}
		else{
			signal_unblock(sigmask);
			setup_bscc(PRNT_PATH);	  /* before print start -> retry BSCC setup */
			signal_block(sigmask);
		}

		printing = 0;
		return 0;
	}

	if(s_count == 0){
#ifdef DEBUG
		write_log("LM(S) status is NULL.\n");
#endif
		return 0; /* no status data */
	}

	bst = get_bst(ptr->st_buf);
	if(printing == 0){
		if(bst & BST_PRINTING){
			printing = 1;
#ifdef DEBUG
			write_log("LM(S) printing flag UP\n");
#endif
		}
	}
	else{
		if(!(bst & BST_PRINTING)){
			printing = 0;
#ifdef DEBUG
			write_log("LM(S) printing flag DOWN\n");
#endif
			kill(getppid(), SIGTERM);
			willbe_end = 1;
		}
	}

	return 0;
}

static int status_get_main(void)
{
	int count;

	get_printer_sem(sem_id);
	count = status_to_viewer(&prn_st);
	release_printer_sem(sem_id);

	if(print_system == PRNSYS_CUPS)
		status_check(count);

	return 0;
}

