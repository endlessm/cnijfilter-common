/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2010
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


#ifndef _UTIL_COM_H_
#define _UTIL_COM_H_

#define SIZE_OF_ARRAY( VAL ) sizeof((VAL))/sizeof((VAL[0]))
#define MAINTENANCE_RESPATH	PACKAGE_DATA_DIR
#define MAINTENANCE_RESFILE	"cnb_maintenance.res"

typedef struct {
	short len;
	char *cmd;
} COMMANDDATA, *LPCOMMANDDATA;

typedef struct {
	int type;
	short index;
	short cmdNum;
	COMMANDDATA *lpCmdData;
} COMMANDCOMP, *LPCOMMANDCOMP;


short ExecCommonDialogType001_000( char *dailogName );
short ExecCommonDialogType001_001( char *dailogName );
short ExecCommonDialogType001_002( char *dailogName );
short ExecCommonDialogType001_003( char *dailogName );
int KeyToIndex(char **Keytbl, int n, char *type);
void SetComboBoxItems(GtkWidget *combo, char **Keytbl, int n, int index);
int UtilMessageBox(char *message, char *title, unsigned int flag);
void OutputCmdType001( char *cmdPtr, long cmdLen );
void OutputCmdType002( char *cmdPtr, long cmdLen, short isSetTime );
short OutputUtilityCommand_CMD_COMMON_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_COMMON_TYPE002( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_COMMON_TYPE003( short index, COMMANDDATA *cmdData, short cmdNum );
short SetLabelUtilDialog( GtkWidget *dialog, char *dialogName );
short SetLabelCommonUtilDialog( char *dialogName, unsigned int flag, short *retVal );
short SetLabelCommonUtilDialogForSetConfig( char *dialogName, unsigned int flag, short *retVal );
short ExecMaintenance( short funcType );

/* Action type */
enum {
	US_F_CLEANING = 1,
	US_F_DEEP_CLEANING,
	US_F_ROLLER_CLEANING,
	US_F_PLATE_CLEANING,
	US_F_NOZZLE_CHECK,
	US_F_NOZZLE_CHECK_ONECE,
	US_F_NOZZLE_CHECK_TWICE_REARTRAY,
	US_F_NOZZLE_CHECK_TWICE_CASETTE,
	US_F_POWER_OFF,
	US_F_AUTO_POWER,
	US_F_INK_CARTRIDGE,
	US_F_QUIET,
	US_F_HEAD_ALIGNMENT,
	US_F_CUSTOM,
	US_F_PAPER_SOURCE_SETTING,
	US_F_INK_RESET,
	US_F_INK_WARNING,
	US_OK = 100,
	US_CANCEL,
	US_YES,
	US_NO,
	US_PRINT_ALIGINMENT_VALUE,
	US_ALIGIN_PRINT_HEAD,
	US_PRINT_ALIGINMENT_VALUE_REARTRAY,
	US_PRINT_ALIGINMENT_VALUE_CASETTE,
	US_ALIGIN_PRINT_HEAD_REARTRAY,
	US_ALIGIN_PRINT_HEAD_CASETTE,
	US_CLOSE,
	US_OK_REARTRAY,
	US_OK_CASETTE,
	US_SEND,
	US_ABORT,
	US_RETRY,
	US_IGNORE,
	US_EXECUTE,
	US_EXECUTE_ALL_COLOR,
	US_EXECUTE_COLOR,
	US_EXECUTE_BLACK,
	US_PRINT_CHECK_PATTERN,
	US_EXIT,
	US_MAINTENANCE_EXIT = 1000,
};

/* Output command type */
enum {
	CMD_COMMON_TYPE001 = 0,
	CMD_COMMON_TYPE002,
	CMD_COMMON_TYPE003,
	CMD_CLEANING_TYPE001,
	CMD_CLEANING_TYPE002,
	CMD_NOZZLECHECK_TYPE001,
	CMD_REGI_TYPE001,
	CMD_REGI_TYPE002,
	CMD_SETCONFIG_TYPE001,
	CMD_SETCONFIG_TYPE002,
	CMD_SETCONFIG_TYPE003,
	CMD_SETCONFIG_TYPE004,
};

#define	MB_ICON_INFORMATION	0x00000000L
#define	MB_ICON_EXCLAMATION	0x00000001L

#define	MB_ICON_QUESTION	0x00000002L
#define MB_ICON_SYSERR		0x00000003L

#define	MB_ICON_NO			0x00000004L

#define	MB_OK				0x00000010L
#define	MB_CANCEL			0x00000020L
#define	MB_YES				0x00000040L
#define	MB_NO				0x00000080L
#define	MB_ABORT			0x00000100L
#define	MB_RETRY			0x00000200L
#define	MB_IGNORE			0x00000400L

#define CMD_BUF_MAX_SIZE	1024
#define NAME_BUF_MAX_SIZE	256



#endif
