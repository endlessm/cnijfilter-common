/*  Canon Inkjet Printer Driver for Linux
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

#if 0
typedef struct {
	char *name;
	short (*proc)( char * );
} DIALOGCOMPTABLE;
#endif


short ExecCommonDialogType001_000( char *dailogName );
short ExecCommonDialogType001_001( char *dailogName );
short ExecCommonDialogType001_002( char *dailogName );
short ExecCommonDialogType001_003( char *dailogName );
int KeyToIndex(char **Keytbl, int n, char *type);
void SetComboBoxItems(GtkWidget *combo, const char **Keytbl, int n, int index);
int UtilMessageBox(char *message, char *title, unsigned int flag, GtkWidget *parent);
void OutputCmdType001( char *cmdPtr, long cmdLen );
void OutputCmdType002( char *cmdPtr, long cmdLen, short isSetTime );
void OutputCmdType003( char *cmdPtr, long cmdLen, char *devMode );
void OutputCmdType004( char *cmdPtr, long cmdLen, short num );
short OutputUtilityCommand_CMD_COMMON_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_COMMON_TYPE002( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_COMMON_TYPE003( short index, COMMANDDATA *cmdData, short cmdNum );
short SetLabelUtilDialog( GtkWidget *dialog, char *dialogName );
short ShowCommonUtilDialog( char *dialogName, unsigned int flag, short *retVal );
short ShowCommonUtilDialogWithConnection( char *dialogName, unsigned int flag, short *retVal, int (*callback)(void) );
short ExecMaintenance( short funcType );
gchar *GetMaintenanceFuncName( short type );
void EnableSensitiveDialog( GtkWidget *widget );
void DisableSensitiveDialog( GtkWidget *widget );
gchar* CheckFileExists(const gchar *dirname, const gchar *filename);
void ShowUtilButtons(GtkWidget* main_window);
void UpperAsciiStr(char *str);
int LowerAsciiCode( int c );
gboolean SameName(gchar* name1, gchar* name2);
GtkWidget* LookupWidget(GtkWidget* window, const gchar* name);
GtkWidget* GetTopWidget(GtkWidget* widget);
int GetActiveButtonIndex(GtkWidget* window, const gchar* button_name[], int default_index);
short GetUtilFlag(short model_id);

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
	US_F_QUIET_SETTING,
	US_F_PAPER_SOURCE_SETTING_CONNECTIONOFF,
	US_F_AUTO_POWER_CONNECTIONOFF,
	US_F_CUSTOM_CONNECTIONOFF,
	US_F_QUIET_SETTING_CONNECTIONOFF,
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
	US_PREVENT_PAPER_ABRATION,
	US_PREVENT_PAPER_JAM,
	US_OK_DISABLE,
	US_OK_WITHOUT_DISABLE,
	US_PREVENT_PAPER_DOUBLE_FEED,
	US_NB_CONNECT_OK,
	US_NB_CONNECT_NG,
	US_F_NOZZLE_CHECK_ASF,
	US_F_NOZZLE_CHECK_FSF,
	US_F_NOZZLE_CHECK_SELECT_BIN,
	US_F_NOZZLE_CHECK_UNKNOWWN,
	US_PAV_SELECT_BIN,
	US_PAV_ASF,
	US_PAV_FSF,
	US_PAV_UNKNOWN,
	US_OK_ASF,
	US_OK_FSF,
	US_APH_ASF,
	US_APH_FSF,
	US_F_PHA_SELECT_BIN,
	US_F_PHA_ASF,
	US_F_PHA_FSF,
	US_F_PHA_UNKNOWN,
	US_NOZZLE_CHECK_FRONT2,	/* Ver.3.80 */
	US_OK_FRONT2_UPPER,		/* Ver.3.80 */
	US_OK_FRONT2_LOWER,		/* Ver.3.80 */
	US_PAV_FRONT2,			/* Ver.3.80 */
	US_F_PHA_FRONT2,		/* Ver.3.80 */
	US_DEFAULT = 1000,
	US_X,
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
	CMD_SETCONFIG_TYPE005,
	CMD_SETCONFIG_TYPE006,
	CMD_SETCONFIG_TYPE007,
	CMD_SETCONFIG_TYPE008,
	CMD_SETCONFIG_TYPE009,
	CMD_SETCONFIG_TYPE010,
	CMD_SETCONFIG_TYPE011,
	CMD_SETCONFIG_TYPE012,
};

/* Special Status type */
enum {
	U_STATUS_END = -1,
	U_STATUS_EXIT = 999,
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

#define CAPTION_ID	"LUM_LID_CAPTION"

// Utility button flag.
#define	UF_CLEANING			1
#define	UF_DEEP_CLEANING	2
#define	UF_ROLLER_CLEANING	4
#define UF_PLATE_CLEANING	8
#define	UF_NOZZLE_CHECK		0x10
#define	UF_HEAD_ALIGNMENT	0x20
#define UI_PAPER_SOURCE_SETTING 0x40		// 2008/05/09
#define	UF_INK_RESET		0x100
#define	UF_INK_WARNING		0x200
#define	UF_INK_CARTRIDGE	0x400
#define	UF_POWER_OFF		0x1000
#define	UF_AUTO_POWER		0x2000
#define	UF_CUSTOM			0x4000
#define	UF_QUIET			0x8000


#endif
