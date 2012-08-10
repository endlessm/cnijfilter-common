/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2012
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


//#define DEBUG

#define STGET_INTERVAL       5
#define MAX_DATA             (64*1024) /* 64KB */
#define RESET_NULL_SIZE      (2*1024)  /*  2KB */

#define SM_COM_PORT	     19999
// #define STMON_PATH           "/usr/local/bin/"
#define STMON_PATH           PROG_PATH
#define ARGV_MAX             64
#define PARPORT_NFAULT	     0x0008
#define PARPORT_NBSY         0x0080
#define SM_SOCK		     2

/* device type */
#define MAJOR_LP             6       /* /dev/lpX */
#define MAJOR_PARPORT        99      /* /dev/parportX */
#define MAJOR_USB            180     /* /dev/usb/lpX */
#define MAJOR_SCSI           21      /* /dev/sgX  Generic SCSI device */
#define DATA_PATH            0       /* print data read path(stdin) */
#define PRNT_PATH            1       /* device(printer) path(stdout) */
#define STAT_PATH            2       /* status output   path(stderr) for CUPS */
#define DEVICE_TYPE_LP       MAJOR_LP
#define DEVICE_TYPE_PARPORT  MAJOR_PARPORT
#define DEVICE_TYPE_USB      MAJOR_USB
#define DEVICE_TYPE_1394     MAJOR_SCSI

/* printer system type */
#define PRNSYS_LPR           1 /* LPR(ng) system */
#define PRNSYS_CUPS          2 /* CUPS system */

/* power off flag */
#define NORMAL_POWEROFF      0 /* Normal Power Off */
#define IVEC_POWEROFF        1 /* IVEC Power Off */

/* Command Type  */
#define NORMAL_COMMAND       0 /* Normal Command */
#define IVEC__COMMAND        1 /* IVEC Command */


/* dispatch fanction struct */
typedef struct ptdev_func {
	int (*ptdev_read)();   /* device Read  function pointer */
	int (*ptdev_write)();  /* device Write function pointer */
	int (*ptdev_ioctl)();  /* device Ioctl function pointer */
	int (*ptdev_poll)();   /* device Poll  function pointer */
} ptdev_func,*Ptdev_func;

/* printer status read back struct */
typedef struct bjst_rback {
	int dev_handle;        /* device handle */
	int rback_handle;      /* status output handle */
	int fault;             /* printer fault status */
	char *st_buf;          /* status body */
} bjst_rback, *Pbjst_rback;

int read_lp_p(int, char*, int);    /* read */
int read_usb_p(int, char*, int);
int read_1394_p(int, char*, int);
int write_lp_p(int, char*, int);   /* write */
int write_usb_p(int, char*, int);
int write_1394_p(int, char*, int);
int ioctl_lp_p(int, int, int);         /* ioctl */
int ioctl_usb_p(int, int, int);
int ioctl_1394_p(int, int, int);
int poll_lp_p(void*, unsigned int, int);   /* poll */
int poll_usb_p(void*, unsigned int, int);
int poll_1394_p(void*, unsigned int, int);

int get_printer_sem(int);
int release_printer_sem(int);
int do_printer_reset(int);
int get_printer_status(int, char *, int *, int *);
int get_printer_devid(void);
int signal_setup(int, void (*func)());
int remove_sem(int);
int lm_init(int);
int check_arg(int, char **);
int status_to_viewer(struct bjst_rback *);
int write_status_info(struct bjst_rback *, int, char*);
int free_arg(void);
int write_printer_com(int, char*, int);
void signal_block(sigset_t);
void signal_unblock(sigset_t);
#ifdef DEBUG
void create_log(void);
void write_log(char *);
#endif

