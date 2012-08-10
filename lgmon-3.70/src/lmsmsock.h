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


#define MAX_COMBUF  512
#define MAX_STATBUF 1024*4 
//#define MAX_STATBUF 512
#define MAX_DATA    (64*1024)

/* socket type */
#define LMtoSM 1
#define SMtoLM 2
#define LMtoSM_TYPEMSG 3

/* command */
#define LM_PRN_COM    1
#define LM_PRN_CANCEL 2
#define LM_PRN_RETRY  3
#define LM_PRN_START  4
#define LM_PRN_CONT   5
#define LM_PRN_END    6
#define LM_PRN_STOP   7
#define LM_PRN_POWST  LM_PRN_STOP /* printer power check start */
#define LM_PRN_POWED  LM_PRN_CONT /* printer power check stop  */
#define LM_PRN_DATA   8
#define LM_PRN_UTIL   9

/* printer status */
#define LM_PRN_NORMAL 0
#define LM_PRN_FAULT  1
#define LM_PRN_POWOFF 2

typedef struct {
	char com_buffer[MAX_COMBUF];
	int  com_size;
} prcom_st, *Prcom_st;

typedef struct {
	char stat_buffer[MAX_STATBUF];
	int  printer_fault;
} prstat_st, *Prstat_st;

/* LM <-> SM socket */
typedef struct {
	int socket_type;
	int command;
	int device_type;

	union {
		prcom_st  com;
		prstat_st stat;
	} prn_data;
} lmsm_socket, *Lmsm_socket;

/* LM <-> LM socket */
typedef struct {
	int command;
} lm_socket, *Lm_socket;


