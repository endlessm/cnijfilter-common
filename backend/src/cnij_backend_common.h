/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2012
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
 */

/*-------------- Canon Local Defines.	*/
/* lgmon command strings				*/
//#define	LGMON_CMD_BASE_STR			"/usr/local/bin/lgmon"	/* base command  */
#define	LGMON_CMD_BASE_STR			PROG_PATH "/lgmon"	/* base command  */
#define	LGMON_CMD_GUI_OPTIN_STR		"--gui"				/* status get option */
#define	LGMON_CMD_CUPS_OPTIN_STR	"--cups"			/* cups only option  */
#define	LGMON_CMD_UTIL_OPTIN_STR	"--utilbyte"		/* cups utility  option  */
#define	LGMON_CMD_DIRECT_OPTIN_STR	"--direct"			/* Ver.3.20 */

/* Number or Intger						*/

/* lgmon command length		 */
#define	LGMON_CMD_MAX_STR_LEN			1028		/* lgmon command length		 */
#define LGMON_DATA_WRITE_STR_LEN		8192	/* device write data length	 */
#define MODEL_NAME_STR_LEN				64		/* printer model name length */

/*-------------- variable 				*/
/*
* When backend receives a signal (SIGTERM),
* it is used for the processing for ending printing and lgmon.
*/
int     g_pid = -1;							/* fork prossece id buffer      */
int     g_signal = 0;  						/* 0: not received, 1: received.*/

/* CUPS base Massegess table			*/
enum {
	INFO_MASSAGE,
	WARNING_MASSAGE,
	ERROR_MASSAGE,
	DEBUG_MESSAGE
} ;

const char *message_str_base[] = {
	"INFO: ", 								/* INFO_MASSAGE					*/
	"WARNING",								/* WARNING_MASSAGE				*/
	"ERROR: ",								/* ERROR_MASSAGE				*/
	"DEBUG: "								/* DEBUG_MESSAGE				*/
} ;

/* Massegess table						*/
enum {
	CANON_STS_SUCCESS,
	CANON_STS_NG	 ,
	CANON_STS_PIPE_ERR,
	CANON_STS_FORK_ERR,
	CANON_STS_LGMON_EXEC_ERR,
	CANON_STS_PPD_FILE_OPEN_ERR,
	CANON_STS_PPD_KEY_SET_ERR,
	CANON_STS_PRINT_CANCEL,
	CANON_STS_DEFAULT
} ;

const char *sts_message_str[] = {
	"function success.",					/* CANON_STS_SUCCESS			*/
	"function error.",						/* CANON_STS_NG					*/
											/* CANON_STS_PIPE_ERR			*/
	"When beginning lgmon, generation of a pipe went wrong.",
	"lgmon process fork error.",			/* CANON_STS_FORK_ERR			*/
	"lgmon process exec error.",			/* CANON_STS_LGMON_EXEC_ERR		*/
	"The ppd file open erorr.",				/* CANON_STS_PPD_FILE_OPEN_ERR	*/
											/* CANON_STS_PPD_KEY_SET_ERR	*/
	"The product key is not set to ppd file.",
	"Printing was canceled",				/* CANON_STS_PRINT_CANCEL 		*/
	"[Canon language moniter]"				/* CANON_STS_DEFAULT			*/
} ;


