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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>
#ifdef	USE_LIB_GLADE
#	include <glade/glade.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h> //
#include <signal.h> //
#include <sys/types.h> //
#include <sys/wait.h> //
#include <sys/ioctl.h> //
#include <unistd.h> //
#include <fcntl.h> //
#include <termios.h> //


#include "callbacks.h"
#ifndef USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"

#include "util_cmd.h"
#include "util_com.h"
#include "util_msi.h"

#include "libcnnet.h"

#define BJ_LIB_DIR	mkpath(XBJLIBPATH)
#define CNIJNET_CASHFILE	BJ_LIB_DIR "/cnnet.ini"


/* SetConfigInfo */
#define BUTTON_NAME_STR_SIZE	64	
typedef struct {
	const char *uiStr;
	const char *cmd1Str;
	const char *cmd2Str;
	const int index;
}SETCONFIGTABLE;


SETCONFIGTABLE setConfigTablePaperGap[] = {
	{ NULL, BJL_STR_AUTO, MSI_STR_AT, 0 },
	{ NULL, BJL_STR_WIDE, MSI_STR_CW, 1 },
	{ NULL, NULL, NULL, -1 },
};

SETCONFIGTABLE setConfigTablePaperJam[] = {
	{ NULL, BJL_STR_OFF, MSI_STR_OFF, 0 },
	{ NULL, BJL_STR_ON, MSI_STR_ON, 1 },
	{ NULL, NULL, NULL, -1 },
};

SETCONFIGTABLE setConfigTableWFeed[] = {
	{ NULL, BJL_STR_OFF, MSI_STR_OFF, 0 },
	{ NULL, BJL_STR_ON, MSI_STR_ON, 1 },
	{ NULL, NULL, NULL, -1 },
};

SETCONFIGTABLE setConfigTableAutoPowerOn[] = {
	{ "autopower_disable", BJL_STR_DISABLE, MSI_STR_OFF, 0 },
	{ "autopower_enable", BJL_STR_ENABLE, MSI_STR_ON, 1 },
	{ NULL, NULL, NULL, -1 },
};

SETCONFIGTABLE setConfigTableAutoPowerOff[] = {
	{ "autopower_disable", BJL_STR_DISABLE, MSI_STR_OFF, 0 },
	{ "autopower_5min", BJL_STR_005_MIN, MSI_STR_005_MIN, 1 },
	{ "autopower_10min", BJL_STR_010_MIN, MSI_STR_010_MIN, 2 },
	{ "autopower_15min", BJL_STR_015_MIN, MSI_STR_015_MIN, 3 },
	{ "autopower_30min", BJL_STR_030_MIN, MSI_STR_030_MIN, 4 },
	{ "autopower_60min", BJL_STR_060_MIN, MSI_STR_060_MIN, 5 },
	{ NULL, NULL, NULL, -1 },
};

#define AUTO_POWEROFF_02_DEFAULT 5
SETCONFIGTABLE setConfigTableAutoPowerOff02[] = {
	{ "autopower_disable", BJL_STR_DISABLE, MSI_STR_OFF, 0 },
	{ "autopower_15min", BJL_STR_015_MIN, MSI_STR_015_MIN, 1 },
	{ "autopower_30min", BJL_STR_030_MIN, MSI_STR_030_MIN, 2 },
	{ "autopower_60min", BJL_STR_060_MIN, MSI_STR_060_MIN, 3 },
	{ "LUM_IDS_AUTOPOWER_120MINUTES", BJL_STR_120_MIN, MSI_STR_120_MIN, 4 },
	{ "LUM_IDS_AUTOPOWER_240MINUTES", BJL_STR_240_MIN, MSI_STR_240_MIN, 5 },
	{ NULL, NULL, NULL, -1 },
};

#define AUTO_POWEROFF_03_DEFAULT 2
SETCONFIGTABLE setConfigTableAutoPowerOff03[] = {
	{ "autopower_5min", BJL_STR_BT005_MIN, MSI_STR_005_MIN, 0 },
	{ "autopower_10min", BJL_STR_BT010_MIN, MSI_STR_010_MIN, 1 },
	{ "autopower_15min", BJL_STR_BT015_MIN, MSI_STR_015_MIN, 2 },
	{ "autopower_30min", BJL_STR_BT030_MIN, MSI_STR_030_MIN, 3 },
	{ NULL, NULL, NULL, -1 },
};

#define CUSTOM_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT 2
SETCONFIGTABLE setConfigTableDryLevel[] = {
	{ "setconfig_type001_radiobutton1", BJL_STR_VAL_1, MSI_STR_VAL_1, 0 },
	{ "setconfig_type001_radiobutton2", BJL_STR_VAL_2, MSI_STR_VAL_2, 1 },
	{ "setconfig_type001_radiobutton3", BJL_STR_VAL_3, MSI_STR_VAL_3, 2 },
	{ "setconfig_type001_radiobutton4", BJL_STR_VAL_4, MSI_STR_VAL_4, 3 },
	{ "setconfig_type001_radiobutton5", BJL_STR_VAL_5, MSI_STR_VAL_5, 4 },
	{ NULL, NULL, NULL, -1 },
};

#define PAPERSOURCE_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT 1
SETCONFIGTABLE setConfigTablePlainPaperFeeder[] = {
	{ "setconfig_type001_radiobutton301", NULL, MSI_STR_ASF, 0 },
	{ "setconfig_type001_radiobutton302", NULL, MSI_STR_FSF, 1 },
	{ NULL, NULL, NULL, -1 },
};

#define QUIET_TYPE002_RADIOBUTTON_DEFAULT 0
SETCONFIGTABLE setConfigTableQuietMode[] = {
	{ "setconfig_type001_radiobutton501", BJL_STR_OFF, MSI_STR_OFF, 0 },
	{ "setconfig_type001_radiobutton502", BJL_STR_ON, MSI_STR_ON, 1 },
	{ "setconfig_type001_radiobutton503", BJL_STR_TIME, MSI_STR_TIME, 2 },
	{ NULL, NULL, NULL, -1 },
};


/* UI type */
enum {
	UI_CUSTOMSETTINGS_TYPE001 = 1,
	UI_CUSTOMSETTINGS_TYPE002,
	UI_CUSTOMSETTINGS_TYPE003,
	UI_AUTOPOWER_TYPE001,
	UI_AUTOPOWER_TYPE002,
	UI_AUTOPOWER_TYPE003,
	UI_AUTOPOWER_TYPE004,
	UI_PAPERSOURCESETTINGS_TYPE001,
	UI_QUIET_TYPE001,
	UI_QUIET_TYPE002,
	UI_POWEROFF_TYPE001,
};

#if 0
/* Output command list */
static const char	*paperGapString[] = {
	"AUTO",
	"WIDE"
};

/* Ver.3.50 */
static const char	*paperJamString[] = {
	"OFF",
	"ON",
};

/* Ver.3.60 */
static const char	*paperWFeedString[] = {
	"OFF",
	"ON",
};

static const char	*autoPowerOnValue[] = {		
	"Disable",                  
	"Enable",					
};

static const short drylevel5_button_value[] =
{
	1,
	2,
	3,
	4,
	5,
};

static const char	*autoPowerOffValue[] = {		
	"Disable",                  
	"5",                        
	"10",                       
	"15",                       
	"30",                       
	"60"                        
};

static const char	*autoPowerOffValueType2[] = {		
	"Disable",                  
	"15",                        
	"30",                       
	"60",
	"120",                       
	"240"                        
};

static const char	*switchString[] = {
	"OFF",
	"ON"
};

static const char *switchString2[] = {
	"OFF",
	"ON",
	"TIME"
};

#endif


#define INKCRTRG_NUM_MAX		3
typedef struct{
	int   index_num;
	int   index_default;
	char* type[INKCRTRG_NUM_MAX];
	char* info[INKCRTRG_NUM_MAX];
	short nValue[INKCRTRG_NUM_MAX];
}INKCRTRGMSGINFO;

INKCRTRGMSGINFO inkCartridgeInfo[] = 
{ 
	{ 3, 2, { "util_ink_cartridge_1", 		// type A
	   		"util_ink_cartridge_2", 
		    "util_ink_cartridge_3" },
 		  { "utility_message_55",
		   	"utility_message_56",
			"utility_message_57" },
 		  { CND_CARTRIDGE_COLOR,
		   	CND_CARTRIDGE_BK,
			CND_CARTRIDGE_BK_COLOR } },
	{ 3, 2, { "util_ink_cartridge_1", 		// type B
	   		"util_ink_cartridge_2", 
		    "util_ink_cartridge_3" },
 		  { "utility_message_55",
		   	"LUM_IDS_CARTRIDGE_EXP_BK_2",
			"utility_message_57" },
 		  { CND_CARTRIDGE_COLOR,
		   	CND_CARTRIDGE_BK,
			CND_CARTRIDGE_BK_COLOR } },
	{ 3, 2, { "util_ink_cartridge_1", 		// type C
	   		"util_ink_cartridge_2", 
		    "util_ink_cartridge_3" },
 		  { "utility_message_55",
		   	"LUM_IDS_CARTRIDGE_EXP_BK_3",
			"utility_message_57" },
 		  { CND_CARTRIDGE_COLOR,
		   	CND_CARTRIDGE_BK,
			CND_CARTRIDGE_BK_COLOR } },
};


/* Each Type Function Resource */
enum {
	RES_SETCONFIG_COMPTYPE001=1,
	RES_SETCONFIG_COMPTYPE002,
	RES_SETCONFIG_COMPTYPE003,
	RES_SETCONFIG_COMPTYPE004,
};


/* SETCONFIG COMPTYPE001 */
typedef struct {
	long	resType;
//	long uiType;
	GtkWidget *(*ptrCreateDialog )( void );
} SETCONFIGCOMPTYPE001RES, *LPSETCONFIGCOMPTYPE001RES;

SETCONFIGCOMPTYPE001RES setConfigType001Res[] = {
	{ RES_SETCONFIG_COMPTYPE001, create_setconfig_type001_dialog }, 
	{ RES_SETCONFIG_COMPTYPE001, create_setconfig_type001_dialog }, 
	{ RES_SETCONFIG_COMPTYPE001, create_setconfig_type001_dialog }, 
	{ RES_SETCONFIG_COMPTYPE001, create_setconfig_type001_dialog }, 
	{ RES_SETCONFIG_COMPTYPE001, create_setconfig_type001_dialog }, /* Ver.3.50 */
	{ RES_SETCONFIG_COMPTYPE001, create_setconfig_type001_dialog }, /* Ver.3.50 */
	{ RES_SETCONFIG_COMPTYPE001, create_setconfig_type001_dialog }, /* Ver.3.60 */
	{ RES_SETCONFIG_COMPTYPE001, create_setconfig_type001_dialog }, /* Ver.3.60 */
	{ RES_SETCONFIG_COMPTYPE001, create_setconfig_type001_dialog }, /* Ver.3.60 */
};

/* SETCONFIG COMPTYPE002 */
typedef struct {
	long	resType;
	unsigned int flag;
} SETCONFIGCOMPTYPE002RES, *LPSETCONFIGCOMPTYPE002RES;

SETCONFIGCOMPTYPE002RES setConfigType002Res[] = {
	{ RES_SETCONFIG_COMPTYPE002, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL },
};

/* SETCONFIG COMPTYPE003 */
typedef struct {
	long	resType;
	INKCRTRGMSGINFO *lpInkCartridgeMsgInfo;
	GtkWidget *(*ptrCreateDialog )( void );
} SETCONFIGCOMPTYPE003RES, *LPSETCONFIGCOMPTYPE003RES;

SETCONFIGCOMPTYPE003RES setConfigType003Res[] = {
	{ RES_SETCONFIG_COMPTYPE003, &inkCartridgeInfo[2], create_setconfig_type003_dialog },
};

/* SETCONFIG COMPTYPE004 */
typedef struct {
	long	resType;
	unsigned int flag;
} SETCONFIGCOMPTYPE004RES, *LPSETCONFIGCOMPTYPE004RES;

SETCONFIGCOMPTYPE004RES setConfigType004Res[] = {
	{ RES_SETCONFIG_COMPTYPE004, MB_ICON_INFORMATION | MB_OK | MB_CANCEL },
};



/* Each Type Function Work */
enum {
	WORK_SETCONFIG_COMPTYPE001=1,
	WORK_SETCONFIG_COMPTYPE002,
	WORK_SETCONFIG_COMPTYPE003,
	WORK_SETCONFIG_COMPTYPE004,
};

/* SETCONFIG COMPTYPE001 */
typedef struct {
	long	workType;
	int uiType;
	GtkWidget	*dialog;
	COMMANDCOMP		*lpCmdComp;
	short status;
} SETCONFIGCOMPTYPE001WORK, *LPSETCONFIGCOMPTYPE001WORK;

/* SETCONFIG COMPTYPE002 */
typedef struct {
	long	workType;
	unsigned int flag;
	COMMANDCOMP		*lpCmdComp;
	short status;
} SETCONFIGCOMPTYPE002WORK, *LPSETCONFIGCOMPTYPE002WORK;

/* SETCONFIG COMPTYPE003 */
typedef struct {
	long	workType;
	GtkWidget	*dialog;
	INKCRTRGMSGINFO *lpInkCartridgeMsgInfo;
	short status;
} SETCONFIGCOMPTYPE003WORK, *LPSETCONFIGCOMPTYPE003WORK;

/* SETCONFIG COMPTYPE004 */
typedef struct {
	long	workType;
	unsigned int flag;
	short status;
} SETCONFIGCOMPTYPE004WORK, *LPSETCONFIGCOMPTYPE004WORK;


#if 0
/* const table */
#define CUSTOM_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT 2
static const gchar* setconfig_type001_radiobutton_name[] =
{
	"setconfig_type001_radiobutton1",
	"setconfig_type001_radiobutton2",
	"setconfig_type001_radiobutton3",
	"setconfig_type001_radiobutton4",
	"setconfig_type001_radiobutton5",
	NULL
};


static const gchar	*setconfig_type001_02_onlist[] = {		
	"autopower_disable",		
	"autopower_enable",
	NULL
};

static const gchar	*setconfig_type001_02_offlist[] = {		
	"autopower_disable",		
	"autopower_5min",			
	"autopower_10min",			
	"autopower_15min",			
	"autopower_30min",			
	"autopower_60min",
	NULL
};

static const gchar *setconfig_type001_03list[] = {
	"autopower_disable",		
	"autopower_15min",			
	"autopower_30min",			
	"autopower_60min",
	"LUM_IDS_AUTOPOWER_120MINUTES",			
	"LUM_IDS_AUTOPOWER_240MINUTES",			
	NULL
};

#define PAPERSOURCE_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT 1
static const gchar *setconfig_type001_ps_radiobutton_name[] =
{
	"setconfig_type001_radiobutton301",
	"setconfig_type001_radiobutton302",
	NULL
};
#define QUIET_TYPE002_RADIOBUTTON_DEFAULT 0
static const gchar *setconfig_type001_quiet_type002_radiobutton_name[] =
{
	"setconfig_type001_radiobutton501",
	"setconfig_type001_radiobutton502",
	"setconfig_type001_radiobutton503",
	NULL
};

#endif
#define QUIET_TYPE002_START_HOUR	21
#define QUIET_TYPE002_START_MIN		0
#define QUIET_TYPE002_END_HOUR	7
#define QUIET_TYPE002_END_MIN	0

enum {
	QUIET_TYPE002_OFF=0,
	QUIET_TYPE002_ON,
	QUIET_TYPE002_TIMER, };

static const gchar* quiet_type002_sensitive_name[] =
{
	"setconfig_type001_label501",
	"setconfig_type001_label502",
	"setconfig_type001_spinbutton501",
	"setconfig_type001_spinbutton502",
	"setconfig_type001_spinbutton503",
	"setconfig_type001_spinbutton504",
	NULL
};

/* global */
static void *gLPSetConfigWork = NULL;
static int gUiType;
static int gDryLevelValue;				/* dry level */
static int gCurrentDryLevelValue;
static int gManualHeadMode;				/* manual head mode */
static int gCurrentManualHeadMode;
static int gAbrasionPrevention;				/* paper gap mode */
static int gCurrentAbrasionPrevention;
static int gAutoPowerOnIndex;				/* Auto Power ON */
static int gCurrentAutoPowerOnIndex;
static int gAutoPowerOffIndex;				/* Auto Power OFF */
static int gCurrentAutoPowerOffIndex;
static int gAutoPowerOffBtIndex;			/* Auto Power Battery OFF */
static int gCurrentAutoPowerOffBtIndex;
static int gPaperSourceSettingsValue;	/* Paper Source Settigs */
static int gCurrentPaperSourceSettingsValue;
static int gQuietMode; /* Quiet mode */
static int gCurrentQuietMode;
static int gQuietModeType002; /* Quiet mode Type002 */
static int gCurrentQuietModeType002;
static int gQuietModeType002StartHour;
static int gCurrentQuietModeType002StartHour;
static int gQuietModeType002StartMin;
static int gCurrentQuietModeType002StartMin;
static int gQuietModeType002EndHour;
static int gCurrentQuietModeType002EndHour;
static int gQuietModeType002EndMin;
static int gCurrentQuietModeType002EndMin;
static int gPreventPaperJam;	/* Prevent Paper Jam */
static int gCurrentPreventPaperJam;
static int gPreventPaperDoubleFeed;	/* Prevent Paper Double-feed */
static int gCurrentPreventPaperDoubleFeed;
static int gIsFirstExecAutoPower = 1;
static int gIsFirstExecCustom = 1;
static int gIsFirstExecQuiet = 1;
static int gIsFirstPaperSource = 1;
//static GList *gGlist = NULL; /* Ver.3.70 */
static CNNLHANDLE gHandle = NULL;
static int gPaperSourceSettingsValueForUI = -1;

/* function prototypes */
static void update_quiet_type002_radiobutton( GtkWidget* );
static int GetActiveButtonIndexFromSetConfigTable( GtkWidget* window, const SETCONFIGTABLE* table, int default_index);
static void SetComboBoxItemsFromSetConfigTable(GtkWidget *combo, const SETCONFIGTABLE* table, int n, int index);
static int GetMSIList01( void );
static void ModifyZeroValue( GtkSpinButton *spinbutton );

/*** Common **************************************************************************************************/
gboolean IsManualHeadMode( void )
{
	if ( gManualHeadMode ) return TRUE;
	else return FALSE;
}

/*** Output **************************************************************************************************/
static short OutputUtilityCommand_CMD_SETCONFIG( short type, short index, COMMANDDATA *cmdData, short cmdNum )
{
	char buf[CMD_BUF_MAX_SIZE];
	char *p;
	long size;
	short dryLevelValue;
	short isSetTime;
	short result = -1;

	if ( cmdData == NULL ) goto Err;
	if ( index > (cmdNum - 1) ) goto Err;

	p = buf;
	size = 0;
	isSetTime = 1;
	if ( type == CMD_SETCONFIG_TYPE001 ){
		//dryLevelValue = drylevel5_button_value[gDryLevelValue];
		dryLevelValue = atoi(setConfigTableDryLevel[gDryLevelValue].cmd1Str);
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, dryLevelValue ); p += size;
		//size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, paperGapString[gAbrasionPrevention] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, setConfigTablePaperGap[gAbrasionPrevention].cmd1Str ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE002 ){
		//size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, autoPowerOnValue[gAutoPowerOnIndex] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, setConfigTableAutoPowerOn[gAutoPowerOnIndex].cmd1Str ); p += size;
		//size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, autoPowerOffValue[gAutoPowerOffIndex] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, setConfigTableAutoPowerOff[gAutoPowerOffIndex].cmd1Str ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE003 ){
		size = cmdData[gPaperSourceSettingsValue].len;
		memcpy( p, cmdData[gPaperSourceSettingsValue].cmd, size ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE004 ){
		//size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, switchString[gQuietMode]  ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, setConfigTableQuietMode[gQuietMode].cmd1Str  ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE005 ){
		//size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, autoPowerOnValue[gAutoPowerOnIndex] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, setConfigTableAutoPowerOn[gAutoPowerOnIndex].cmd1Str ); p += size;
		//size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, autoPowerOffValueType2[gAutoPowerOffIndex] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, setConfigTableAutoPowerOff02[gAutoPowerOffIndex].cmd1Str ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE006 ){
		//dryLevelValue = drylevel5_button_value[gDryLevelValue];
		dryLevelValue = atoi(setConfigTableDryLevel[gDryLevelValue].cmd1Str);
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, dryLevelValue ); p += size;
		//size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, paperGapString[gAbrasionPrevention] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, setConfigTablePaperGap[gAbrasionPrevention].cmd1Str ); p += size;
		//size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[2].cmd, paperJamString[gPreventPaperJam] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[2].cmd, setConfigTablePaperJam[gPreventPaperJam].cmd1Str ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE007 ){
		if ( gQuietModeType002 == QUIET_TYPE002_TIMER ){
			char timeBuf[CMD_BUF_MAX_SIZE];
			memset( timeBuf, 0, CMD_BUF_MAX_SIZE );

			snprintf( timeBuf, CMD_BUF_MAX_SIZE, "%02d%02d%02d%02d", gQuietModeType002StartHour, gQuietModeType002StartMin,
				gQuietModeType002EndHour, gQuietModeType002EndMin );

			//size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, switchString2[gQuietModeType002] ); p += size;
			size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, setConfigTableQuietMode[gQuietModeType002].cmd1Str ); p += size;
			size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[1].cmd, timeBuf ); p += size;
		}
		else {
			//size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, switchString2[gQuietModeType002] ); p += size;
			size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, setConfigTableQuietMode[gQuietModeType002].cmd1Str ); p += size;
		}
	}
	else if ( type == CMD_SETCONFIG_TYPE008 ){
		//size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[1].cmd, autoPowerOffValueType2[gAutoPowerOffIndex] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[1].cmd, setConfigTableAutoPowerOff02[gAutoPowerOffIndex].cmd1Str ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE009 ){
		//dryLevelValue = drylevel5_button_value[gDryLevelValue];
		dryLevelValue = atoi(setConfigTableDryLevel[gDryLevelValue].cmd1Str);
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, dryLevelValue ); p += size;
		//size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, paperGapString[gAbrasionPrevention] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, setConfigTablePaperGap[gAbrasionPrevention].cmd1Str ); p += size;
		//size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[2].cmd, paperWFeedString[gPreventPaperDoubleFeed] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[2].cmd, setConfigTableWFeed[gPreventPaperDoubleFeed].cmd1Str ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE010 ){
		isSetTime = 0; /* Not output SETTIME for old printer. */
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[1].cmd, setConfigTableAutoPowerOff[gAutoPowerOffIndex].cmd1Str ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[1].cmd, setConfigTableAutoPowerOff03[gAutoPowerOffBtIndex].cmd1Str ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE011 ){
		isSetTime = 0; /* Not output SETTIME for old printer. */
		dryLevelValue = atoi(setConfigTableDryLevel[gDryLevelValue].cmd1Str);
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, dryLevelValue ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE012 ){
		isSetTime = 0; /* Not output SETTIME for old printer. */
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, setConfigTableQuietMode[gQuietMode].cmd1Str  ); p += size;
	}

	if ( size != 0 ){
		*p = 0x00; p++;
		size = (long)(p - buf);
		OutputCmdType002( buf, size, isSetTime );
	}

	result = 0;
Err:
	return result;
}

short OutputUtilityCommand_CMD_SETCONFIG_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE001, index, cmdData, cmdNum );
}

short OutputUtilityCommand_CMD_SETCONFIG_TYPE002( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE002, index, cmdData, cmdNum );
}

short OutputUtilityCommand_CMD_SETCONFIG_TYPE003( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE003, index, cmdData, cmdNum );
}

short OutputUtilityCommand_CMD_SETCONFIG_TYPE004( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE004, index, cmdData, cmdNum );
}

/* Ver.3.50 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE005( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE005, index, cmdData, cmdNum );
}

/* Ver.3.50 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE006( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE006, index, cmdData, cmdNum );
}

/* Ver.3.60 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE007( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE007, index, cmdData, cmdNum );
}

/* Ver.3.60 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE008( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE008, index, cmdData, cmdNum );
}

/* Ver.3.60 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE009( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE009, index, cmdData, cmdNum );
}

/* Ver.3.70 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE010( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE010, index, cmdData, cmdNum );
}

/* Ver.3.70 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE011( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE011, index, cmdData, cmdNum );
}

/* Ver.3.70 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE012( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_SETCONFIG( CMD_SETCONFIG_TYPE012, index, cmdData, cmdNum );
}


/*** COMPTYPE001 *********************************************************************************************/

static gboolean IsCustomSettings( int type )
{
	gboolean ret = FALSE;

	switch ( type ) {
		case UI_CUSTOMSETTINGS_TYPE001:
		case UI_CUSTOMSETTINGS_TYPE002:
		case UI_CUSTOMSETTINGS_TYPE003:
			ret = TRUE;
			break;
		default:
			break;
	}
	return ret;
}

static gboolean IsAutoPower( int type )
{
	gboolean ret = FALSE;

	switch ( type ) {
		case UI_AUTOPOWER_TYPE001:
		case UI_AUTOPOWER_TYPE002:
		case UI_AUTOPOWER_TYPE003:
		case UI_AUTOPOWER_TYPE004:
			ret = TRUE;
			break;
		default:
			break;
	}
	return ret;
}

static gboolean IsPaperSourceSettings( int type )
{
	gboolean ret = FALSE;

	switch ( type ) {
		case UI_PAPERSOURCESETTINGS_TYPE001:
			ret = TRUE;
			break;
		default:
			break;
	}
	return ret;
}

static gboolean IsQuietMode( int type )
{
	gboolean ret = FALSE;

	switch ( type ) {
		case UI_QUIET_TYPE001:
		case UI_QUIET_TYPE002:
			ret = TRUE;
			break;
		default:
			break;
	}
	return ret;
}

static void InitCreate_SetconfigType001_CustomSettings( int uiType )
{
	if ( gIsFirstExecCustom ){
		gAbrasionPrevention = 0;
		gCurrentAbrasionPrevention = 0;

		gManualHeadMode = 0;
		gCurrentManualHeadMode = 0;

		gDryLevelValue = CUSTOM_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT;
		gCurrentDryLevelValue = 0;

		if ( uiType == UI_CUSTOMSETTINGS_TYPE002 ) {
			gPreventPaperJam = 0;
			gCurrentPreventPaperJam = 0;
		}

		if ( uiType == UI_CUSTOMSETTINGS_TYPE003 ) {
			gPreventPaperDoubleFeed = 0;
			gCurrentPreventPaperDoubleFeed = 0;
		}

		/* Updage isFirst flag */
		gIsFirstExecCustom = 0;
	}
}

static void InitCreate_SetConfigType001_AutoPower( int uiType )
{
	if ( gIsFirstExecAutoPower ){
		gAutoPowerOnIndex = 0;
		gCurrentAutoPowerOnIndex = 0;

		if ( uiType == UI_AUTOPOWER_TYPE001 ){
			gAutoPowerOffIndex = 0;
		}
		else if ( (uiType == UI_AUTOPOWER_TYPE002) || (uiType == UI_AUTOPOWER_TYPE003) || (uiType == UI_AUTOPOWER_TYPE004)){
			gAutoPowerOffIndex = AUTO_POWEROFF_02_DEFAULT;
		}
		gCurrentAutoPowerOffIndex = 0;

		if ( uiType == UI_AUTOPOWER_TYPE004 ){
			gAutoPowerOffBtIndex = AUTO_POWEROFF_03_DEFAULT;
			gCurrentAutoPowerOffBtIndex = 0;
		}

		/* Update isFirst flag */
		gIsFirstExecAutoPower = 0;
	}
}

static void InitCreate_SetConfigType001_PaperSourceSettings( void )
{
	if ( gIsFirstPaperSource ) {
		gPaperSourceSettingsValue = PAPERSOURCE_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT;
		gCurrentPaperSourceSettingsValue = 0;

		/* Update isFirst flag */
		gIsFirstPaperSource = 0;
	}
}

static void InitCreate_SetConfigType001_QuietMode( int uiType )
{
	if ( gIsFirstExecQuiet ) {
		if ( uiType == UI_QUIET_TYPE001 ){
			gQuietMode = 0;
			gCurrentQuietMode = 0;
		}
		else if ( uiType == UI_QUIET_TYPE002 ){
			gQuietModeType002 = QUIET_TYPE002_OFF;
			gCurrentQuietModeType002 = QUIET_TYPE002_OFF;

			gQuietModeType002StartHour = QUIET_TYPE002_START_HOUR;
			gCurrentQuietModeType002StartHour = QUIET_TYPE002_START_HOUR;
			gQuietModeType002StartMin = QUIET_TYPE002_START_MIN;
			gCurrentQuietModeType002StartMin = QUIET_TYPE002_START_MIN;
			gQuietModeType002EndHour = QUIET_TYPE002_END_HOUR;
			gCurrentQuietModeType002EndHour = QUIET_TYPE002_END_HOUR;
			gQuietModeType002EndMin = QUIET_TYPE002_END_MIN;
			gCurrentQuietModeType002EndMin = QUIET_TYPE002_END_MIN;
		}

		/* Update isFirst flag */
		gIsFirstExecQuiet = 0;	
	}
}

static int GetAutoPowerIndex(const SETCONFIGTABLE *table, int n, char *mode)
{
	int			i;
	
	for (i=0; i < n; i++) {
		if (!strcmp(LookupText(g_keytext_list, table[i].uiStr), mode))	
			return i;		
	}
	return 0;		
}

static LPSETCONFIGCOMPTYPE001WORK CreateWorkSetConfigType001( LPSETCONFIGCOMPTYPE001RES lpRes )
{
	LPSETCONFIGCOMPTYPE001WORK lpWork = NULL;

	if ( lpRes == NULL ) goto Err;
	if ( (lpWork = g_malloc0(sizeof(SETCONFIGCOMPTYPE001WORK))) == NULL ) goto Err;

	lpWork->workType = WORK_SETCONFIG_COMPTYPE001;
Err:
	return lpWork;
}

/*-- Init --*/
static void InitParamSetConfigType001( LPSETCONFIGCOMPTYPE001RES lpRes, void *lpGWork )
{
	LPSETCONFIGCOMPTYPE001WORK lpWork = (LPSETCONFIGCOMPTYPE001WORK)lpGWork;

	lpWork->status = US_DEFAULT;
	lpWork->dialog = lpRes->ptrCreateDialog();

	if ( IsCustomSettings( gUiType ) ){
		InitCreate_SetconfigType001_CustomSettings( gUiType );
	}
	else if ( IsAutoPower( gUiType ) ){
		InitCreate_SetConfigType001_AutoPower( gUiType );
	}
	else if ( IsPaperSourceSettings( gUiType ) ) {
		InitCreate_SetConfigType001_PaperSourceSettings();
	}
	else if ( IsQuietMode( gUiType ) ) {
		InitCreate_SetConfigType001_QuietMode( gUiType );
	}
}

/*-- Set Labels --*/
static void SetLabelSetConfigType001( LPSETCONFIGCOMPTYPE001RES lpRes, void *lpGWork, char *dialogName )
{
	LPSETCONFIGCOMPTYPE001WORK lpWork = (LPSETCONFIGCOMPTYPE001WORK)lpGWork;
	SetLabelUtilDialog( lpWork->dialog, dialogName );
}

static void SetUICustomSettings( int uiType, GtkWidget *dialog, int isDefault )
{
	GtkWidget *button;

	/* paper gap */
	button = LookupWidget( dialog, "setconfig_type001_checkbutton1");
	if ( isDefault ){
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), FALSE );
	}
	else {
		if ( gAbrasionPrevention ){
			gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
		}
		else {
			gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), FALSE );
		}
	}

	/* manual head */
	button = LookupWidget( dialog, "setconfig_type001_checkbutton2");
	if ( isDefault ){
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), FALSE );
	}
	else {
		if ( gManualHeadMode ){
			gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
		}
		else {
			gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), FALSE );
		}
	}

	/* radio button */
	if ( isDefault ){
		//button = LookupWidget( dialog,  setconfig_type001_radiobutton_name[CUSTOM_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT] );
		button = LookupWidget( dialog,  setConfigTableDryLevel[CUSTOM_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT].uiStr );
	}
	else {
		//button = LookupWidget( dialog,  setconfig_type001_radiobutton_name[gDryLevelValue] );
		button = LookupWidget( dialog,  setConfigTableDryLevel[gDryLevelValue].uiStr );
	}
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );

	if ( uiType == UI_CUSTOMSETTINGS_TYPE002 ){
		/* Prevent Paper Jam */
		button = LookupWidget( dialog, "setconfig_type001_checkbutton3");
		if ( isDefault ){
			gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), FALSE );
		}
		else {
			if ( gPreventPaperJam ){
				gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
			}
			else{
				gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), FALSE );
			}
		}
	}

	if ( uiType == UI_CUSTOMSETTINGS_TYPE003 ){
		/* Prevent Paper Double-feed */
		button = LookupWidget( dialog, "setconfig_type001_checkbutton4");
		if ( isDefault ){
			gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), FALSE );
		}
		else {
			if ( gPreventPaperDoubleFeed ){
				gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
			}
			else{
				gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), FALSE );
			}
		}

	}
}

static void InitUISetConfigType001_CustomSettings( int uiType, GtkWidget *dialog )
{
	SetUICustomSettings( uiType, dialog, 0 );
}

static void SetDefaultUISetConfigType001_CustomSettings( int uiType, GtkWidget *dialog )
{
	SetUICustomSettings( uiType, dialog, 1 );
}

static void SetUISetConfigType001_AutoPower( int uiType, GtkWidget *dialog, int isDefault  )
{
	GtkWidget *combo1, *combo2;
	short onSize, offSize, offSize02, offSize03;

	combo1 = LookupWidget(dialog, "setconfig_type001_combobox201");
	combo2 = LookupWidget(dialog, "setconfig_type001_combobox202");

	onSize    = sizeof(setConfigTableAutoPowerOn)/sizeof(*setConfigTableAutoPowerOn) - 1;
	offSize   = sizeof(setConfigTableAutoPowerOff)/sizeof(*setConfigTableAutoPowerOff) - 1;
	offSize02 = sizeof(setConfigTableAutoPowerOff02)/sizeof(*setConfigTableAutoPowerOff02) - 1;
	offSize03 = sizeof(setConfigTableAutoPowerOff03)/sizeof(*setConfigTableAutoPowerOff03) - 1;

	if ( uiType == UI_AUTOPOWER_TYPE001 ){
		if ( isDefault ){
			SetComboBoxItemsFromSetConfigTable(combo1, setConfigTableAutoPowerOn, onSize, 0 );
			SetComboBoxItemsFromSetConfigTable(combo2, setConfigTableAutoPowerOff, offSize ,0 );
		}
		else {
			SetComboBoxItemsFromSetConfigTable(combo1, setConfigTableAutoPowerOn, onSize, gAutoPowerOnIndex );
			SetComboBoxItemsFromSetConfigTable(combo2, setConfigTableAutoPowerOff, offSize, gAutoPowerOffIndex );
		}
		gtk_widget_show( combo1 );
		gtk_widget_show( combo2 );
	}
	else if ( uiType == UI_AUTOPOWER_TYPE002 ){
		if ( isDefault ){
			SetComboBoxItemsFromSetConfigTable(combo1, setConfigTableAutoPowerOn, onSize, 0 );
			SetComboBoxItemsFromSetConfigTable(combo2, setConfigTableAutoPowerOff02, offSize02, AUTO_POWEROFF_02_DEFAULT );
		}
		else {
			SetComboBoxItemsFromSetConfigTable(combo1, setConfigTableAutoPowerOn, onSize, gAutoPowerOnIndex );
			SetComboBoxItemsFromSetConfigTable(combo2, setConfigTableAutoPowerOff02, offSize02, gAutoPowerOffIndex);
		}
		gtk_widget_show( combo1 );
		gtk_widget_show( combo2 );
	}
	else if ( uiType == UI_AUTOPOWER_TYPE003 ){
		if ( isDefault ){
			SetComboBoxItemsFromSetConfigTable(combo2, setConfigTableAutoPowerOff02, offSize02 , AUTO_POWEROFF_02_DEFAULT );
		}
		else {
			SetComboBoxItemsFromSetConfigTable(combo2, setConfigTableAutoPowerOff02, offSize02, gAutoPowerOffIndex);
		}
		gtk_widget_show( combo2 );
	}
	else if ( uiType == UI_AUTOPOWER_TYPE004 ){
		if ( isDefault ){
			SetComboBoxItemsFromSetConfigTable(combo1, setConfigTableAutoPowerOff, offSize, AUTO_POWEROFF_02_DEFAULT );
			SetComboBoxItemsFromSetConfigTable(combo2, setConfigTableAutoPowerOff03, offSize03 , AUTO_POWEROFF_03_DEFAULT );
		}
		else {
			SetComboBoxItemsFromSetConfigTable(combo1, setConfigTableAutoPowerOff, offSize, gAutoPowerOffIndex);
			SetComboBoxItemsFromSetConfigTable(combo2, setConfigTableAutoPowerOff03, offSize03, gAutoPowerOffBtIndex);
		}
		gtk_widget_show( combo1 );
		gtk_widget_show( combo2 );
	}
}

static void InitUISetConfigType001_AutoPower( int uiType, GtkWidget *dialog )
{
	SetUISetConfigType001_AutoPower( uiType, dialog, 0 );
}

static void SetUISetConfigType001_PaperSourceSettings( GtkWidget *dialog, int isDefault )
{
	GtkWidget *button;

	if ( isDefault ){
		//button = LookupWidget( dialog, setconfig_type001_ps_radiobutton_name[PAPERSOURCE_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT] );
		button = LookupWidget( dialog, setConfigTablePlainPaperFeeder[PAPERSOURCE_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT].uiStr );
	}
	else {
		//button = LookupWidget( dialog, setconfig_type001_ps_radiobutton_name[gPaperSourceSettingsValue] );
		button = LookupWidget( dialog, setConfigTablePlainPaperFeeder[gPaperSourceSettingsValue].uiStr );
	}
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
}

static void InitUISetConfigType001_PaperSourceSettings( GtkWidget *dialog )
{
	SetUISetConfigType001_PaperSourceSettings( dialog, 0 );
}

static void SetDefaultUISetConfigType001_PaperSourceSettings( GtkWidget *dialog )
{
	SetUISetConfigType001_PaperSourceSettings( dialog, 1 );
}

static void SetUISetConfigType001_QuietMode( int uiType, GtkWidget *dialog, int isDefault )
{
	GtkWidget *button;

	if ( uiType == UI_QUIET_TYPE001 ){
		button = LookupWidget( dialog, "setconfig_type001_checkbutton401" );
		if ( isDefault ){
			gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), FALSE );
		}	
		else {
			if ( gQuietMode ){
				gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
			}
			else {
				gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), FALSE );
			}
		}
	}
	else if ( uiType == UI_QUIET_TYPE002 ){
		GtkSpinButton* start_hour_spin = (GtkSpinButton*)LookupWidget( dialog, "setconfig_type001_spinbutton501" );
		GtkSpinButton* start_min_spin = (GtkSpinButton*)LookupWidget( dialog, "setconfig_type001_spinbutton502" );
		GtkSpinButton* end_hour_spin = (GtkSpinButton*)LookupWidget( dialog, "setconfig_type001_spinbutton503" );
		GtkSpinButton* end_min_spin = (GtkSpinButton*)LookupWidget( dialog, "setconfig_type001_spinbutton504" );

		GtkAdjustment* start_hour_adjust = start_hour_spin->adjustment;
		GtkAdjustment* start_min_adjust = start_min_spin->adjustment;
		GtkAdjustment* end_hour_adjust = end_hour_spin->adjustment;
		GtkAdjustment* end_min_adjust = end_min_spin->adjustment;

		if ( isDefault ){
			start_hour_adjust->value = QUIET_TYPE002_START_HOUR;
			start_min_adjust->value = QUIET_TYPE002_START_MIN;
			end_hour_adjust->value = QUIET_TYPE002_END_HOUR;
			end_min_adjust->value = QUIET_TYPE002_END_MIN;
		}
		else {
			start_hour_adjust->value = gQuietModeType002StartHour;
			start_min_adjust->value = gQuietModeType002StartMin;
			end_hour_adjust->value = gQuietModeType002EndHour;
			end_min_adjust->value = gQuietModeType002EndMin;
		}

		gtk_spin_button_set_value( start_hour_spin, start_hour_adjust->value );
		gtk_spin_button_set_value( start_min_spin, start_min_adjust->value );
		gtk_spin_button_set_value( end_hour_spin, end_hour_adjust->value );
		gtk_spin_button_set_value( end_min_spin, end_min_adjust->value );

		if ( isDefault ){
			//button = LookupWidget( dialog,  setconfig_type001_quiet_type002_radiobutton_name[QUIET_TYPE002_OFF] );
			button = LookupWidget( dialog,  setConfigTableQuietMode[QUIET_TYPE002_OFF].uiStr );
			gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
		}
		else {
			//button = LookupWidget( dialog,  setconfig_type001_quiet_type002_radiobutton_name[gQuietModeType002] );
			button = LookupWidget( dialog,  setConfigTableQuietMode[gQuietModeType002].uiStr );
			gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
		}
		update_quiet_type002_radiobutton( dialog );

	}
}

static void InitUISetConfigType001_QuietMode( int uiType, GtkWidget *dialog )
{
	SetUISetConfigType001_QuietMode( uiType, dialog, 0 );
}

static void SetDefaultUISetConfigType001_QuietMode( int uiType, GtkWidget *dialog )
{
	SetUISetConfigType001_QuietMode( uiType, dialog, 1 );
}

/*-- set default --*/
static void SetDefaultSetConfigType001( LPSETCONFIGCOMPTYPE001RES lpRes, void *lpGWork )
{
	LPSETCONFIGCOMPTYPE001WORK lpWork = (LPSETCONFIGCOMPTYPE001WORK)lpGWork;

	if ( IsCustomSettings( gUiType ) ){
		InitUISetConfigType001_CustomSettings( gUiType, lpWork->dialog );
	}
	else if ( IsAutoPower( gUiType ) ){
		InitUISetConfigType001_AutoPower( gUiType, lpWork->dialog );
	}
	else if ( IsPaperSourceSettings( gUiType ) ) {
		InitUISetConfigType001_PaperSourceSettings( lpWork->dialog );
	}
	else if ( IsQuietMode( gUiType ) ) {
		InitUISetConfigType001_QuietMode( gUiType, lpWork->dialog );
	}
}

/*-- show dialog --*/
static void ShowDialogSetConfigType001( LPSETCONFIGCOMPTYPE001RES lpRes, void *lpGWork )
{
	LPSETCONFIGCOMPTYPE001WORK lpWork = (LPSETCONFIGCOMPTYPE001WORK)lpGWork;

	gtk_widget_show( lpWork->dialog );
	gtk_window_set_transient_for( GTK_WINDOW(lpWork->dialog), GTK_WINDOW(UI_DIALOG(g_main_window)->window) );
	gtk_main();
}

/*-- dispose --*/
static void DisposeWorkSetConfigType001( LPSETCONFIGCOMPTYPE001WORK lpWork )
{
	if ( lpWork == NULL ) goto Err;

	g_free( lpWork );
Err:
	return;
}

static short CheckWorkType001( void )
{
	LPSETCONFIGCOMPTYPE001WORK lpWork = (LPSETCONFIGCOMPTYPE001WORK)gLPSetConfigWork;
	short result = -1;

	if ( lpWork == NULL ) goto Err;
	if ( lpWork->workType !=  WORK_SETCONFIG_COMPTYPE001 ) goto Err;

	result = 0;
Err:
	return result;
}

/*-- get status --*/
static short GetStatusSetConfigType001( void *lpGWork )
{
	LPSETCONFIGCOMPTYPE001WORK lpWork = (LPSETCONFIGCOMPTYPE001WORK)lpGWork;
	return lpWork->status;
}



/*-------------------------------------------------------------------------------
	short ExecSetConfigType001( void *lpWork, char *dialogName )
-------------------------------------------------------------------------------*/
short ExecSetConfigType001( void *lpWork, char *dialogName )
{
	LPSETCONFIGCOMPTYPE001RES lpRes = (LPSETCONFIGCOMPTYPE001RES)lpWork;
	short	result = -1;

	/* confirm data type */
	if ( lpRes->resType != RES_SETCONFIG_COMPTYPE001 ) goto Err;

	/* allocate  work */
	if ( (gLPSetConfigWork = CreateWorkSetConfigType001( lpRes )) == NULL ) goto Err;

	/* ---- Show Dialog ---- */
	/* init parameter */
	InitParamSetConfigType001( lpRes, gLPSetConfigWork );
	
	/* show labels */
	SetLabelSetConfigType001( lpRes, gLPSetConfigWork, dialogName );

	/* set default */
	SetDefaultSetConfigType001( lpRes, gLPSetConfigWork );

	/* show dialog */
	ShowDialogSetConfigType001( lpRes, gLPSetConfigWork );

	/* get status */
	result = GetStatusSetConfigType001( gLPSetConfigWork );

	DisposeWorkSetConfigType001( gLPSetConfigWork );
Err:
	gLPSetConfigWork = NULL;	
	return result;
}

/*-------------------------------------------------------------------------------
	SetConfigType001 callback functions
-------------------------------------------------------------------------------*/
static void GetParmSetConfigType001_CustomSettings( int uiType, GtkButton *button )
{
	GtkWidget* check_button = NULL;
	GtkWidget* window = GetTopWidget(GTK_WIDGET(button));

	/* Abrasion Prevention */
	check_button = LookupWidget( GTK_WIDGET(button), "setconfig_type001_checkbutton1");
	gCurrentAbrasionPrevention =  GTK_TOGGLE_BUTTON(check_button)->active;

	/* Manual Head Alignment */
	check_button = LookupWidget( GTK_WIDGET(button), "setconfig_type001_checkbutton2");
	gCurrentManualHeadMode =  GTK_TOGGLE_BUTTON(check_button)->active;

	/* Dry Level */
	//gCurrentDryLevelValue = (short)GetActiveButtonIndex( window, setconfig_type001_radiobutton_name, CUSTOM_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT );
	gCurrentDryLevelValue = (short)GetActiveButtonIndexFromSetConfigTable( window, 
					setConfigTableDryLevel, CUSTOM_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT );

	if ( uiType == UI_CUSTOMSETTINGS_TYPE002 ){
		/* Prevent Paper Jam */
		check_button = LookupWidget( GTK_WIDGET(button), "setconfig_type001_checkbutton3");
		gCurrentPreventPaperJam = GTK_TOGGLE_BUTTON(check_button)->active;
	}

	if ( uiType == UI_CUSTOMSETTINGS_TYPE003 ){
		/* Prevent Paper Double-feed */
		check_button = LookupWidget( GTK_WIDGET(button), "setconfig_type001_checkbutton4");
		gCurrentPreventPaperDoubleFeed = GTK_TOGGLE_BUTTON(check_button)->active;
	}
}


static void GetParmSetConfigType001_AutoPower( int uiType, GtkButton *button )
{
	GtkWidget *combo1, *combo2;
	gchar *str1, *str2;
	short onSize, offSize, offSize02, offSize03;

	combo1 = LookupWidget( GTK_WIDGET(button), "setconfig_type001_combobox201" );
	combo2 = LookupWidget( GTK_WIDGET(button), "setconfig_type001_combobox202" );

	str1 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo1));
	str2 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo2));

	onSize = sizeof(setConfigTableAutoPowerOn)/sizeof(*setConfigTableAutoPowerOn);
	offSize = sizeof(setConfigTableAutoPowerOff)/sizeof(*setConfigTableAutoPowerOff);
	offSize02 = sizeof(setConfigTableAutoPowerOff02)/sizeof(*setConfigTableAutoPowerOff02);
	offSize03 = sizeof(setConfigTableAutoPowerOff03)/sizeof(*setConfigTableAutoPowerOff03);

	if ( uiType == UI_AUTOPOWER_TYPE001 ){
		gCurrentAutoPowerOnIndex = GetAutoPowerIndex( setConfigTableAutoPowerOn, onSize, str1 );
		gCurrentAutoPowerOffIndex = GetAutoPowerIndex( setConfigTableAutoPowerOff, offSize, str2 );
	}
	else if ( uiType == UI_AUTOPOWER_TYPE002 ){
		gCurrentAutoPowerOnIndex = GetAutoPowerIndex( setConfigTableAutoPowerOn, onSize, str1 );
		gCurrentAutoPowerOffIndex = GetAutoPowerIndex( setConfigTableAutoPowerOff02, offSize02, str2 );
	}
	else if ( uiType == UI_AUTOPOWER_TYPE003 ){
		gCurrentAutoPowerOffIndex = GetAutoPowerIndex( setConfigTableAutoPowerOff02, offSize02, str2 );
	}	
	else if ( uiType == UI_AUTOPOWER_TYPE004 ){
		gCurrentAutoPowerOffIndex   = GetAutoPowerIndex( setConfigTableAutoPowerOff, offSize, str1 );
		gCurrentAutoPowerOffBtIndex = GetAutoPowerIndex( setConfigTableAutoPowerOff03, offSize03, str2 );
	}
}

static void GetParmSetConfigType001_QuietMode( int uiType, GtkButton *button )
{
	GtkWidget* widget = NULL;
	GtkWidget* window = GetTopWidget(GTK_WIDGET(button));

	if ( uiType == UI_QUIET_TYPE001 ){
		widget = LookupWidget( GTK_WIDGET(button), "setconfig_type001_checkbutton401");
		gCurrentQuietMode =  GTK_TOGGLE_BUTTON(widget)->active;
	}
	else if ( uiType == UI_QUIET_TYPE002 ){
		GtkSpinButton* start_hour_spin = (GtkSpinButton*)LookupWidget( window, "setconfig_type001_spinbutton501" );
		GtkSpinButton* start_min_spin = (GtkSpinButton*)LookupWidget( window, "setconfig_type001_spinbutton502" );
		GtkSpinButton* end_hour_spin = (GtkSpinButton*)LookupWidget( window, "setconfig_type001_spinbutton503" );
		GtkSpinButton* end_min_spin = (GtkSpinButton*)LookupWidget( window, "setconfig_type001_spinbutton504" );

		gCurrentQuietModeType002StartHour = start_hour_spin->adjustment->value;
		gCurrentQuietModeType002StartMin = start_min_spin->adjustment->value;
		gCurrentQuietModeType002EndHour = end_hour_spin->adjustment->value;
		gCurrentQuietModeType002EndMin = end_min_spin->adjustment->value;

		//gCurrentQuietModeType002 = (short)GetActiveButtonIndex( window, setconfig_type001_quiet_type002_radiobutton_name, QUIET_TYPE002_RADIOBUTTON_DEFAULT );
		gCurrentQuietModeType002 = (short)GetActiveButtonIndexFromSetConfigTable( window, setConfigTableQuietMode, QUIET_TYPE002_RADIOBUTTON_DEFAULT );
	}
}

static short GetStatusSetConfigType001_AutoPower( int uiType )
{
	//short status = US_X;
	short status = US_DEFAULT;

	switch ( uiType ) {
		case UI_AUTOPOWER_TYPE001:
		case UI_AUTOPOWER_TYPE002:
		case UI_AUTOPOWER_TYPE004:
			status = US_OK;
			break;
		case UI_AUTOPOWER_TYPE003:
			if ( gCurrentAutoPowerOffIndex == 0 ){
				status = US_OK_DISABLE;
			}
			else {
				status = US_OK_WITHOUT_DISABLE;
			}
			break;
		default:
			break;
	}
	return status;
}



gboolean
on_setconfig_type001_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	if ( GTK_WIDGET_SENSITIVE( widget )) {
		gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(widget)));
		return FALSE;
	}
	else {
		return TRUE;
	}
}


void
on_setconfig_type001_dialog_destroy
                                        (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


void
on_setconfig_type001_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	GtkWidget* window = GetTopWidget(GTK_WIDGET(togglebutton));	

	if ( GTK_WIDGET_VISIBLE( window ) == TRUE ){	
		if( GTK_TOGGLE_BUTTON(togglebutton)->active ) {
			DisableSensitiveDialog( window );
			UtilMessageBox(LookupText(g_keytext_list, "LUM_LID_WARNING_PAPER_ABRASION"), g_window_title, MB_ICON_NO | MB_OK, window);
			EnableSensitiveDialog( window );
		}
	}
}

/* Ver.3.50 */
void
on_setconfig_type001_checkbutton3_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	GtkWidget* window = GetTopWidget(GTK_WIDGET(togglebutton));
	int status;

	if ( GTK_WIDGET_VISIBLE( window ) == TRUE ){	
		if( GTK_TOGGLE_BUTTON(togglebutton)->active ) {
			DisableSensitiveDialog( window );
			status = UtilMessageBox(LookupText(g_keytext_list, "LUM_IDS_MNTMSG_PREVENTPAPERGAP_MSG"), g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL, window);
			EnableSensitiveDialog( window );
			//if ( (status == US_CANCEL) || (status == US_X) ){
			if ( status == US_CANCEL ){
				gtk_toggle_button_set_active( togglebutton, FALSE );
			}
		}
	}
}

/* Ver.3.60 */
void
on_setconfig_type001_checkbutton4_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	GtkWidget* window = GetTopWidget(GTK_WIDGET(togglebutton));
	int status;

	if ( GTK_WIDGET_VISIBLE( window ) == TRUE ){	
		if( GTK_TOGGLE_BUTTON(togglebutton)->active ) {
			DisableSensitiveDialog( window );
			status = UtilMessageBox(LookupText(g_keytext_list, "LUM_IDS_MNTMSG_PREVENTWFEED_MSG"), g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL, window);
			EnableSensitiveDialog( window );
			//if ( (status == US_CANCEL) || (status == US_X) ){
			if ( status == US_CANCEL ){
				gtk_toggle_button_set_active( togglebutton, FALSE );
			}
		}
	}
}

/* Send button */
void
on_setconfig_type001_button1_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	LPSETCONFIGCOMPTYPE001WORK lpWk = (LPSETCONFIGCOMPTYPE001WORK)gLPSetConfigWork;
	short status = US_OK;
	if ( CheckWorkType001() != 0 ) goto Err;
	GtkWidget* window = GetTopWidget(GTK_WIDGET(button));	


	if ( IsCustomSettings( gUiType ) ){
		GetParmSetConfigType001_CustomSettings( gUiType, button );
	}
	else if ( IsAutoPower( gUiType ) ){
		GetParmSetConfigType001_AutoPower( gUiType, button );
		status = GetStatusSetConfigType001_AutoPower( gUiType );
	}	
	else if ( IsPaperSourceSettings( gUiType ) ) {
		gCurrentPaperSourceSettingsValue = 
			//(short)GetActiveButtonIndex( window, setconfig_type001_ps_radiobutton_name, PAPERSOURCE_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT );
			(short)GetActiveButtonIndexFromSetConfigTable( window, setConfigTablePlainPaperFeeder, PAPERSOURCE_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT );
	}
	else if ( IsQuietMode( gUiType ) ) {
		GetParmSetConfigType001_QuietMode( gUiType, button );
	}

	lpWk->status = status;
Err:
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
}

/* Cancel button */
void
on_setconfig_type001_button2_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	LPSETCONFIGCOMPTYPE001WORK lpWk = (LPSETCONFIGCOMPTYPE001WORK)gLPSetConfigWork;
	lpWk->status = US_CANCEL;
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
}

/* Defaults button */
void
on_setconfig_type001_button3_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	if ( CheckWorkType001() != 0 ) goto Err;

	if ( IsCustomSettings( gUiType ) ){
		SetDefaultUISetConfigType001_CustomSettings( gUiType, (GtkWidget *)button );
	}	
	else if ( IsPaperSourceSettings( gUiType ) ) {
		SetDefaultUISetConfigType001_PaperSourceSettings( (GtkWidget *)button );
	}	
	else if ( IsQuietMode( gUiType ) ) {
		SetDefaultUISetConfigType001_QuietMode( gUiType, (GtkWidget *)button );
	}
Err:
	return;
}

/* Ver.3.60 */
static void 
update_quiet_type002_radiobutton( GtkWidget* dialog )
{
	GtkWidget *window = GetTopWidget( dialog );
	gboolean sensitive;
	int current;
	int i;

	//current = (short)GetActiveButtonIndex( window, setconfig_type001_quiet_type002_radiobutton_name, QUIET_TYPE002_RADIOBUTTON_DEFAULT );
	current = (short)GetActiveButtonIndexFromSetConfigTable( window, setConfigTableQuietMode, QUIET_TYPE002_RADIOBUTTON_DEFAULT );

	if ( current != QUIET_TYPE002_TIMER ){
		sensitive = FALSE;
	}
	else {
		sensitive = TRUE;
	}

	for ( i=0; quiet_type002_sensitive_name[i] != NULL; i++ ){
		gtk_widget_set_sensitive(LookupWidget(window, quiet_type002_sensitive_name[i]), sensitive);
	}
}

void
on_setconfig_type001_radiobutton50x_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	update_quiet_type002_radiobutton( gtk_widget_get_toplevel(GTK_WIDGET(button)) );
}


void
on_setconfig_type001_spinbutton502_state_changed
                                        (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data)
{
	ReleaseEditableState( widget, state);
}


void
on_setconfig_type001_spinbutton501_state_changed
                                        (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data)
{
	ReleaseEditableState( widget, state);
}


void
on_setconfig_type001_spinbutton503_state_changed
                                        (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data)
{
	ReleaseEditableState( widget, state);
}


void
on_setconfig_type001_spinbutton504_state_changed
                                        (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data)
{
	ReleaseEditableState( widget, state);
}

void
on_setconfig_type001_spinbutton502_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	ModifyZeroValue( spinbutton );
}


void
on_setconfig_type001_spinbutton501_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	ModifyZeroValue( spinbutton );
}


void
on_setconfig_type001_spinbutton503_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	ModifyZeroValue( spinbutton );
}


void
on_setconfig_type001_spinbutton504_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	ModifyZeroValue( spinbutton );
}


/*** COMPTYPE002 *********************************************************************************************/
//static LPSETCONFIGCOMPTYPE002WORK CreateWorkSetConfigType002( LPSETCONFIGCOMPTYPE002RES lpRes )
static LPSETCONFIGCOMPTYPE002WORK CreateWorkSetConfigType002( LPSETCONFIGCOMPTYPE002RES lpRes )
{
	LPSETCONFIGCOMPTYPE002WORK lpWork = NULL;

	if ( lpRes == NULL ) goto Err;
	if ( (lpWork = g_malloc0(sizeof(SETCONFIGCOMPTYPE002WORK))) == NULL ) goto Err;

	lpWork->workType = WORK_SETCONFIG_COMPTYPE002;
Err:
	return lpWork;
}

static void InitParamSetConfigType002( LPSETCONFIGCOMPTYPE002RES lpRes, void *lpGWork )
{
	LPSETCONFIGCOMPTYPE002WORK lpWork = (LPSETCONFIGCOMPTYPE002WORK)lpGWork;

	lpWork->status = US_DEFAULT;
	lpWork->flag = lpRes->flag;
}

static short ShowDialogSetConfigType002( LPSETCONFIGCOMPTYPE002RES lpRes, void *lpGWork, char *dialogName )
{
	LPSETCONFIGCOMPTYPE002WORK lpWork = (LPSETCONFIGCOMPTYPE002WORK)lpGWork;
	short result = -1;

	//SetLabelCommonUtilDialogForSetConfig( dialogName, lpWork->flag, &lpWork->status );
	ShowCommonUtilDialog( dialogName, lpWork->flag, &lpWork->status );
	result = 0;
	return result;
}


static short SetCurrentStatusSetConfigType002_CustomSettings( int uiType )
{
	switch ( uiType ){
		case UI_CUSTOMSETTINGS_TYPE003:
			gPreventPaperDoubleFeed = gCurrentPreventPaperDoubleFeed;
			break;
		case UI_CUSTOMSETTINGS_TYPE002:
			gPreventPaperJam = gCurrentPreventPaperJam;
			break;
		case UI_CUSTOMSETTINGS_TYPE001:
			break;
		default:
			break;
	}
	gDryLevelValue = gCurrentDryLevelValue;
	gManualHeadMode = gCurrentManualHeadMode;
	gAbrasionPrevention = gCurrentAbrasionPrevention;
	return 0;
}

static short SetCurrentStatusSetConfigType002_AutoPower( int uiType )
{
	switch ( uiType ){
		case UI_AUTOPOWER_TYPE001:
		case UI_AUTOPOWER_TYPE002:
			gAutoPowerOnIndex = gCurrentAutoPowerOnIndex;
		case UI_AUTOPOWER_TYPE003:
			gAutoPowerOffIndex = gCurrentAutoPowerOffIndex;
			break;
		case UI_AUTOPOWER_TYPE004:
			gAutoPowerOffIndex = gCurrentAutoPowerOffIndex;
			gAutoPowerOffBtIndex = gCurrentAutoPowerOffBtIndex;
			break;
		default:
			break;
	}
	return 0;
}

static short SetCurrentStatusSetConfigType002_QuietMode( int uiType )
{
	switch( uiType ){
		case UI_QUIET_TYPE001:
			gQuietMode = gCurrentQuietMode;
			break;
		case UI_QUIET_TYPE002:
			gQuietModeType002 = gCurrentQuietModeType002;
			gQuietModeType002StartHour = gCurrentQuietModeType002StartHour;
			gQuietModeType002StartMin = gCurrentQuietModeType002StartMin;
			gQuietModeType002EndHour = gCurrentQuietModeType002EndHour;
			gQuietModeType002EndMin = gCurrentQuietModeType002EndMin;
			break;
		default:
			break;
	}
	return 0;
}

static short SetCurrentStatusSetConfigType002( LPSETCONFIGCOMPTYPE002RES lpRes, void *lpGWork )
{
	LPSETCONFIGCOMPTYPE002WORK lpWork = (LPSETCONFIGCOMPTYPE002WORK)lpGWork;
	short result = -1;

	/* write current status */
	if( lpWork->status == US_OK ){
		if ( IsCustomSettings( gUiType )  ){
			SetCurrentStatusSetConfigType002_CustomSettings( gUiType );
		}
		else if ( IsAutoPower( gUiType ) ){
			SetCurrentStatusSetConfigType002_AutoPower( gUiType );
		}
		else if ( IsPaperSourceSettings( gUiType ) ) {
			gPaperSourceSettingsValue = gCurrentPaperSourceSettingsValue;
		}
		else if ( IsQuietMode( gUiType ) ) {
			SetCurrentStatusSetConfigType002_QuietMode( gUiType );
		}
	}

	result = 0;
	return result;
}

static void DisposeWorkSetConfigType002( void *lpGWork )
{
	if ( lpGWork == NULL ) goto Err;
	g_free( lpGWork );
Err:
	return;
}

static short GetStatusSetConfigType002( void *lpGWork )
{
	LPSETCONFIGCOMPTYPE002WORK lpWork = (LPSETCONFIGCOMPTYPE002WORK)lpGWork;
	return lpWork->status;
}

#if 0
/*-------------------------------------------------------------------------------
	unsigned int  GetFlagSetConfigType002( void )
-------------------------------------------------------------------------------*/
unsigned int GetFlagSetConfigType002( void )
{
	LPSETCONFIGCOMPTYPE002WORK lpWk = (LPSETCONFIGCOMPTYPE002WORK)gLPSetConfigWork;	
	if ( lpWk != NULL ) {
		return lpWk->flag;
	}
	else {
		return 0;
	}
}
#endif
/*-------------------------------------------------------------------------------
	short ExecSetConfigType002( void *lpWork, char *dialogName )
-------------------------------------------------------------------------------*/
short ExecSetConfigType002( void *lpWork, char *dialogName )
{
	LPSETCONFIGCOMPTYPE002RES lpRes = (LPSETCONFIGCOMPTYPE002RES)lpWork;
	short result = -1;

	/* confirm data type */
	if ( lpRes->resType != RES_SETCONFIG_COMPTYPE002 ) goto Err;

	/* allocate  work */
	if ( (gLPSetConfigWork = CreateWorkSetConfigType002( lpRes )) == NULL ) goto Err;

	/* init parameter */
	InitParamSetConfigType002( lpRes, gLPSetConfigWork );

	/* show dialog */
	ShowDialogSetConfigType002 ( lpRes, gLPSetConfigWork, dialogName );

	/* set current status */
	SetCurrentStatusSetConfigType002( lpRes, gLPSetConfigWork );

	/* get status */
	result = GetStatusSetConfigType002( gLPSetConfigWork );

	DisposeWorkSetConfigType002( gLPSetConfigWork );

Err:
	gLPSetConfigWork = NULL;
	return result;
}



/*** COMPTYPE003 *********************************************************************************************/
int nValueToIndex(short *nValuetbl, int n, short nValue)
{
	int	i;

	for (i=0; i < n; i++) {
		if ( nValuetbl[i] == nValue )
			return i;
	}
	return 0;
}

static LPSETCONFIGCOMPTYPE003WORK CreateWorkSetConfigType003( LPSETCONFIGCOMPTYPE003RES lpRes )
{
	LPSETCONFIGCOMPTYPE003WORK lpWork = NULL;

	if ( lpRes == NULL ) goto Err;
	if ( (lpWork = g_malloc0(sizeof(SETCONFIGCOMPTYPE003WORK))) == NULL ) goto Err;

	lpWork->workType = WORK_SETCONFIG_COMPTYPE003;
Err:
	return lpWork;
}

static void InitParamSetConfigType003( LPSETCONFIGCOMPTYPE003RES lpRes, void *lpGWork )
{
	LPSETCONFIGCOMPTYPE003WORK lpWork = (LPSETCONFIGCOMPTYPE003WORK)lpGWork;

	lpWork->status = US_DEFAULT;
	lpWork->lpInkCartridgeMsgInfo = lpRes->lpInkCartridgeMsgInfo;
	lpWork->dialog = lpRes->ptrCreateDialog();
}

static void SetLabelSetConfigType003( LPSETCONFIGCOMPTYPE003RES lpRes, void *lpGWork, char *dialogName )
{
	LPSETCONFIGCOMPTYPE003WORK lpWork = (LPSETCONFIGCOMPTYPE003WORK)lpGWork;
	SetLabelUtilDialog( lpWork->dialog, dialogName );
}

static void SetDefaultSetConfigType003( LPSETCONFIGCOMPTYPE003RES lpRes, void *lpGWork )
{
	LPSETCONFIGCOMPTYPE003WORK lpWork = (LPSETCONFIGCOMPTYPE003WORK)lpGWork;
	GtkWidget*	combo;
	GtkWidget*	label;
	gchar* 		msg;
	int index_num = lpWork->lpInkCartridgeMsgInfo->index_num;
	int currentIndex;

	currentIndex= nValueToIndex(lpWork->lpInkCartridgeMsgInfo->nValue, index_num, GetCurrentnValue(CNCL_INKCARTRIDGESETTINGS) );
	combo = LookupWidget( lpWork->dialog, "setconfig_type003_combobox1" );

	if( DisableSignal() )
	{
		SetComboBoxItems(combo, (const char **)lpWork->lpInkCartridgeMsgInfo->type, index_num, currentIndex);
	}
	EnableSignal();

	msg = LookupText(g_keytext_list, lpWork->lpInkCartridgeMsgInfo->info[currentIndex]);
	label = LookupWidget(GTK_WIDGET(lpWork->dialog), "setconfig_type003_label3");
	gtk_label_set_text(GTK_LABEL(label), msg);
}

static void ShowDialogSetConfigType003( LPSETCONFIGCOMPTYPE003RES lpRes, void *lpGWork )
{
	LPSETCONFIGCOMPTYPE003WORK lpWork = (LPSETCONFIGCOMPTYPE003WORK)lpGWork;

	gtk_widget_show( lpWork->dialog );
	gtk_window_set_transient_for( GTK_WINDOW(lpWork->dialog), GTK_WINDOW(UI_DIALOG(g_main_window)->window) );
	gtk_main();
}

static void DisposeWorkSetConfigType003( LPSETCONFIGCOMPTYPE003WORK lpWork )
{
	if ( lpWork == NULL ) goto Err;
	g_free( lpWork );
Err:
	return;
}

static short GetStatusSetConfigType003( void *lpGWork )
{
	LPSETCONFIGCOMPTYPE003WORK lpWork = (LPSETCONFIGCOMPTYPE003WORK)lpGWork;
	return lpWork->status;
}

/*-------------------------------------------------------------------------------
	short ExecSetConfigType003( void *lpWork, char *dialogName )
-------------------------------------------------------------------------------*/
short ExecSetConfigType003( void *lpWork, char *dialogName )
{
	LPSETCONFIGCOMPTYPE003RES lpRes = (LPSETCONFIGCOMPTYPE003RES)lpWork;
	short	result = -1;

	/* confirm data type */
	if ( lpRes->resType != RES_SETCONFIG_COMPTYPE003 ) goto Err;

	/* allocate  work */
	if ( (gLPSetConfigWork = CreateWorkSetConfigType003( lpRes )) == NULL ) goto Err;

	/* ---- Show Dialog ---- */
	/* init parameter */
	InitParamSetConfigType003( lpRes, gLPSetConfigWork );
	
	/* show labels */
	SetLabelSetConfigType003( lpRes, gLPSetConfigWork, dialogName );

	/* set default */
	SetDefaultSetConfigType003( lpRes, gLPSetConfigWork );

	/* show dialog */
	ShowDialogSetConfigType003( lpRes, gLPSetConfigWork );

	/* get status */
	result = GetStatusSetConfigType003( gLPSetConfigWork );

	DisposeWorkSetConfigType003( gLPSetConfigWork );

Err:
	gLPSetConfigWork = NULL;
	return result;
}
/*-------------------------------------------------------------------------------
	SetConfigType003 callback functions
-------------------------------------------------------------------------------*/
gboolean
on_setconfig_type003_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	gtk_widget_destroy( GTK_WIDGET(widget) );
	return TRUE;
}


void
on_setconfig_type003_dialog_destroy    (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


void
on_setconfig_type003_dialog_combo_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	LPSETCONFIGCOMPTYPE003WORK lpWk = (LPSETCONFIGCOMPTYPE003WORK)gLPSetConfigWork;
	GtkWidget*	label;
	char*		type;
	gchar* 		msg;
	int index_num = lpWk->lpInkCartridgeMsgInfo->index_num;
	int currentIndex;

	if( DisableSignal() )
	{
		type = (char*)gtk_combo_box_get_active_text( combobox );
	
		currentIndex = KeyToIndex(lpWk->lpInkCartridgeMsgInfo->type, index_num, type );
	
		msg = LookupText(g_keytext_list, lpWk->lpInkCartridgeMsgInfo->info[currentIndex]);
		label = LookupWidget(GTK_WIDGET(combobox), "setconfig_type003_label3");
		gtk_label_set_text(GTK_LABEL(label), msg);
	}
	EnableSignal();
}

/* OK button */
void
on_setconfig_type003_button1_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	LPSETCONFIGCOMPTYPE003WORK lpWk = (LPSETCONFIGCOMPTYPE003WORK)gLPSetConfigWork;
	GtkWidget	*combo;
  	char		*type;
	int index_num = lpWk->lpInkCartridgeMsgInfo->index_num;
	int currentIndex;

	combo = LookupWidget(GTK_WIDGET(button), "setconfig_type003_combobox1");
	type = (char*)gtk_combo_box_get_active_text( GTK_COMBO_BOX(combo) );	/* Ver.2.80 */

	currentIndex = KeyToIndex(lpWk->lpInkCartridgeMsgInfo->type, index_num, type );

	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));

	/* update database */
	UpdateMenuLink(CNCL_INKCARTRIDGESETTINGS, lpWk->lpInkCartridgeMsgInfo->nValue[currentIndex]);
	lpWk->status = US_OK;
}

/* Cancel button */
void
on_setconfig_type003_button2_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	LPSETCONFIGCOMPTYPE003WORK lpWk = (LPSETCONFIGCOMPTYPE003WORK)gLPSetConfigWork;

	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	lpWk->status = US_CANCEL;
}

/* defaults button */
void
on_setconfig_type003_button3_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	LPSETCONFIGCOMPTYPE003WORK lpWk = (LPSETCONFIGCOMPTYPE003WORK)gLPSetConfigWork;
	GtkWidget*	combo;
	GtkWidget*	label;
	gchar* 		msg;
	int index_num = lpWk->lpInkCartridgeMsgInfo->index_num;
	int defIndex;

	defIndex = lpWk->lpInkCartridgeMsgInfo->index_default;
	combo = LookupWidget(GTK_WIDGET(button), "setconfig_type003_combobox1");

	/* Ver.2.80 */
	if( DisableSignal() )
	{
		SetComboBoxItems(combo, (const char **)lpWk->lpInkCartridgeMsgInfo->type, index_num, defIndex );
	}
	EnableSignal();

	msg = LookupText(g_keytext_list, lpWk->lpInkCartridgeMsgInfo->info[defIndex]);
	label = LookupWidget(GTK_WIDGET(button), "setconfig_type003_label3");
	gtk_label_set_text(GTK_LABEL(label), msg);
}


/*** COMPTYPE004 *********************************************************************************************/
static LPSETCONFIGCOMPTYPE004WORK CreateWorkSetConfigType004( LPSETCONFIGCOMPTYPE004RES lpRes )
{
	LPSETCONFIGCOMPTYPE004WORK lpWork = NULL;

	if ( lpRes == NULL ) goto Err;
	if ( (lpWork = g_malloc0(sizeof(SETCONFIGCOMPTYPE004WORK))) == NULL ) goto Err;

	lpWork->workType = WORK_SETCONFIG_COMPTYPE004;
Err:
	return lpWork;
}

static void InitParamSetConfigType004( LPSETCONFIGCOMPTYPE004RES lpRes, void *lpGWork )
{
	LPSETCONFIGCOMPTYPE004WORK lpWork = (LPSETCONFIGCOMPTYPE004WORK)lpGWork;

	lpWork->status = US_DEFAULT;
	lpWork->flag = lpRes->flag;
}

static short ShowDialogSetConfigType004( LPSETCONFIGCOMPTYPE004RES lpRes, void *lpGWork, char *dialogName )
{
	LPSETCONFIGCOMPTYPE004WORK lpWork = (LPSETCONFIGCOMPTYPE004WORK)lpGWork;
	short result = -1;

	ShowCommonUtilDialogWithConnection( dialogName, lpWork->flag, &lpWork->status, GetMSIList01 );

	result = 0;
	return result;
}

static short SetCurrentStatusSetConfigType004( LPSETCONFIGCOMPTYPE004RES lpRes, void *lpGWork )
{
	//LPSETCONFIGCOMPTYPE004WORK lpWork = (LPSETCONFIGCOMPTYPE004WORK)lpGWork;
	short result = -1;

	/* write current status */
	result = 0;
	return result;
}

static void DisposeWorkSetConfigType004( void *lpGWork )
{
	if ( lpGWork == NULL ) goto Err;
	g_free( lpGWork );
Err:
	return;
}

static short GetStatusSetConfigType004( void *lpGWork )
{
	LPSETCONFIGCOMPTYPE004WORK lpWork = (LPSETCONFIGCOMPTYPE004WORK)lpGWork;
	return lpWork->status;
}

/*-------------------------------------------------------------------------------
	short ExecSetConfigType004( void *lpWork, char *dialogName )
-------------------------------------------------------------------------------*/
short ExecSetConfigType004( void *lpWork, char *dialogName )
{
	LPSETCONFIGCOMPTYPE004RES lpRes = (LPSETCONFIGCOMPTYPE004RES)lpWork;
	short result = -1;


	/* confirm data type */
	if ( lpRes->resType != RES_SETCONFIG_COMPTYPE004 ) goto Err;

	/* allocate  work */
	if ( (gLPSetConfigWork = CreateWorkSetConfigType004( lpRes )) == NULL ) goto Err;

	/* init parameter */
	InitParamSetConfigType004( lpRes, gLPSetConfigWork );

	/* show dialog */
	ShowDialogSetConfigType004 ( lpRes, gLPSetConfigWork, dialogName );

	/* set current status */
	SetCurrentStatusSetConfigType004( lpRes, gLPSetConfigWork );

	/* get status */
	result = GetStatusSetConfigType004( gLPSetConfigWork );

	DisposeWorkSetConfigType004( gLPSetConfigWork );

Err:
	gLPSetConfigWork = NULL;
	return result;
}

#define DEVID_BUF_SIZE 1024
#define URI_BUF_SIZE 64
static int CreateMSIListFromDeviceID( char *buf, int bufSize, GList **gList )
{
	GList *lGlist = NULL;
	char *curPtr = NULL;
	char *dstPtr = NULL;
	char msiBuf[DEVID_BUF_SIZE];
	int result = -1;

	if ( buf == NULL ) goto onErr;

	curPtr = strstr( buf + 2, "MSI" );
	curPtr += 4; /* skip MSI */

	while( (curPtr - buf) <= bufSize ){
		dstPtr = msiBuf;
		while ( (*curPtr != ',') && (*curPtr != ';') ){
			*dstPtr++ = *curPtr++;
		}
		*dstPtr = '\0';
		lGlist = g_list_append( lGlist, g_strdup(msiBuf) );

		if ( *curPtr == ';' ) break;
		curPtr++;
	}
	
	*gList = lGlist;
	result = 0;
onErr:
	return result;
}


/* -----------------------------------------------------------------------------
	[Name] CreateMSIListViaNet
	[Args]
		glist : list include MSI
		uriBuf : uri string
		uriBufSize : uri buf size
		retry : retry number of times of the communication
		timeout : the time-out of communication
	[Return]
		-1 : Error
----------------------------------------------------------------------------- */
static int CreateMSIListViaNet( GList **gList, char *uriBuf, int uriBufSize, int retry, int timeout )
{
	char devid[DEVID_BUF_SIZE];
	char ipAddr[URI_BUF_SIZE];
	int commandType = -1;
	unsigned long bufSize = 0;
	int cnt;
	int result = -1;
	int isCash = 0;
	int status = 0;
	
	if ( gList == NULL ) goto onErr1;
	*gList = NULL;

	memset( devid, 0x00, DEVID_BUF_SIZE );

	/* init */
	if ( CNNL_Init(&gHandle) != CNNL_RET_SUCCESS ) goto onErr1;

	/* Get IPAdress */
	if ( retry > 0 ) {
		status = CNNL_GetIPAddressEx( gHandle, CNIJNET_CASHFILE, uriBuf, ipAddr, sizeof(ipAddr), CNNET_SEARCH_CACHE_ALL, 5, 200 );
	
		if ( status == CNNL_RET_SUCCESS ){
			if( CNNL_OpenEx( gHandle, ipAddr, CNNET_TYPE_PRINTER, 3, 1500) == CNNL_RET_SUCCESS ){
				isCash = 1;
			}
			CNNL_Close( gHandle );
		}
		
		if ( isCash == 0 ) {
			for ( cnt=0; cnt<retry; cnt++ ){
				status = CNNL_GetIPAddressEx( gHandle, CNIJNET_CASHFILE, uriBuf, ipAddr, sizeof(ipAddr), CNNET_SEARCH_BROADCAST, 1, timeout );
				if ( status == CNNL_RET_SUCCESS ) break;
				usleep( 500000 );
			}
		}
	}
	else {
		status = CNNL_GetIPAddressEx( gHandle, CNIJNET_CASHFILE, uriBuf, ipAddr, sizeof(ipAddr), CNNET_SEARCH_CACHE_ALL, 5, 200 );
	}
	if ( status != CNNL_RET_SUCCESS ) goto onErr2;


	/* Open Printer */
	if( CNNL_OpenEx( gHandle, ipAddr, CNNET_TYPE_PRINTER, 3, 1500) != CNNL_RET_SUCCESS ){
		goto onErr2;
	}

	/* Decide command_type */
	if( CNNL_GetCommandType( gHandle, &commandType, 3, 1500) != CNNL_RET_SUCCESS ){
		goto onErr3;
	}
	if( commandType != CNNL_COMMAND_IVEC ) goto onErr3;

	/* Get DeviceID STA Ver.3.70 */
	if ( CNNL_GetDeviceID(gHandle, devid, &bufSize, DEVID_BUF_SIZE, 3, 1500) != CNNL_RET_SUCCESS ){
		goto onErr3;
	}

	/* Get MSI List */
	if ( CreateMSIListFromDeviceID( devid, DEVID_BUF_SIZE, gList ) == -1){
		goto onErr3;
	}

	result = 0;	
onErr3:
	/* Close printer */
	CNNL_Close( gHandle );
onErr2:
	/* Terminate */
	CNNL_Terminate( &gHandle );
onErr1:
	return result;
}

static int CreateMSIListViaUSB( GList **gList, char *uriBuf, int uriBufSize )
{
	char devid[DEVID_BUF_SIZE];
	int fd;
	int result = -1;

	if ( gList == NULL ) goto onErr1;
	*gList = NULL;

	if ( (fd = open( uriBuf, O_RDONLY)) >= 0 ) {
		memset( devid, 0x00, DEVID_BUF_SIZE );

		/* Get DeviceID */
		if ( ioctl( fd, _IOC(_IOC_READ, 'P', 1, sizeof(devid)), devid) ==0 ) {
			if ( CreateMSIListFromDeviceID( devid, DEVID_BUF_SIZE, gList ) == -1) goto onErr2;
		}
		else goto onErr2;
	}
	else goto onErr1;

	result = 0;
onErr2:
	close( fd );
onErr1:
	return result;
}


typedef struct {
	int type;
	const char *beName;
} DEVURICOMP;

enum {
	DEVURI_TYPE_USB = 0,	
	DEVURI_TYPE_NET,	
};

static DEVURICOMP backendComp[] =
{
	{ DEVURI_TYPE_USB, "cnijusb" },
	{ DEVURI_TYPE_NET, "cnijnet" },
	{ -1, NULL },
};


static int ParseDeviceURI( int *type, char *uriBuf, int bufSize )
{
	int i;
	int result = -1;
	char *curPtr, *dstPtr;

	if ( (type == NULL) || (uriBuf == NULL) ) goto onErr;

	if ( g_device_uri == NULL ) goto onErr;

	i = 0;
	dstPtr = uriBuf;
	while ( backendComp[i].type != -1 ) {
		curPtr = strstr( g_device_uri, backendComp[i].beName );
		if ( curPtr != NULL ){
			curPtr += strlen( backendComp[i].beName ) + 1; /* "+ 1" is ":" */

			if ( backendComp[i].type == DEVURI_TYPE_NET ) curPtr++;

			while( *curPtr != '\0' ) {
				*dstPtr++ = *curPtr++;
			}
			*dstPtr = '\0';
			*type = backendComp[i].type;
			break;
		}
		i++;
	}

	if ( backendComp[i].type == -1 ) {
		goto onErr;
	}

	result = 0;
onErr:
	return result;
}


static int CreateMSIList( GList **gList, int retry, int timeout )
{
	int type;
	char uriBuf[URI_BUF_SIZE];
	int result = -1;

	type = -1;	
	if ( ParseDeviceURI( &type, uriBuf, URI_BUF_SIZE ) == -1 ) goto onErr;

	switch( type ){
		case DEVURI_TYPE_USB:
			if ( CreateMSIListViaUSB( gList, uriBuf, URI_BUF_SIZE ) == -1 ) goto onErr;
			break;
		case DEVURI_TYPE_NET:
			if ( CreateMSIListViaNet( gList, uriBuf, URI_BUF_SIZE, retry, timeout ) == -1 ) goto onErr;
			break;
		default:
			break;
	}
	result = 0;
onErr:
	return result;
}

static int DisposeMSIList( GList *gList )
{
	if ( gList != NULL ) g_list_foreach( gList, (GFunc)g_free, NULL );
	if ( gList != NULL ) g_list_free( gList );

	return 0;
}




/* -----------------------------------------------------------------------------
	[Name] GetMSIStr
	[Args]
		glist : list include MSI
		type : MSI type
	[Return]
		NULL : Not found string.
		Not NULL : Return string ptr appropriate to type.
----------------------------------------------------------------------------- */
static char * GetMSIStr( GList *glist, short type )
{
	GList *current = glist;
	int i;
	char *result = NULL;
	char *chCode;

	if ( glist == NULL ) goto onErr;

	i = 0;
	while( msiCompTable[i].type != -1 ){
		if ( msiCompTable[i].type == type ) break;
		i++;
	}
	if ( i == -1 ) goto onErr;

	while( current != NULL ) {
		chCode = (char*)current->data;
		if ( *chCode == msiCompTable[i].id ) {
			result = ++chCode;
			break;
		}
		current = g_list_next(current);
	}

onErr:
	return result;
}


#define CHECK_HOUR(VAL) ((VAL)>23? -1:((VAL)<0? (-1):(VAL)))
#define CHECK_MIN(VAL) ((VAL)>59? -1:((VAL)<0? (-1):(VAL)))
static int GetMSITime( GList *glist, int *startHour, int *startMin, int *endHour, int *endMin )
{
	GList *current = glist;
	char timeBuf[4][3];
	char *chCode;
	int result = -1;
	int i,j;

	if ( glist == NULL ) goto onErr;
	if ( (startHour == NULL) || (startMin == NULL) || (endHour == NULL) || (endMin == NULL) ) goto onErr;
	*startHour = 0;
	*startMin  = 0;
	*endHour   = 0;
	*endMin    = 0;

	for ( i=0; i<4; i++ ){
		for ( j=0; j<3; j++ ){
			timeBuf[i][j] = '\0';
		}
	}

	while( current != NULL ){
		chCode = (char*)current->data;
		if ( *chCode == 'K' ){
			chCode++;

			memcpy( timeBuf[0], chCode, 2 ); chCode += 2;
			memcpy( timeBuf[1], chCode, 2 ); chCode += 2;
			memcpy( timeBuf[2], chCode, 2 ); chCode += 2;
			memcpy( timeBuf[3], chCode, 2 ); chCode += 2;

			*startHour = atoi( timeBuf[0] );
			*startMin  = atoi( timeBuf[1] );
			*endHour   = atoi( timeBuf[2] );
			*endMin    = atoi( timeBuf[3] );

			break;
		}
		current = g_list_next(current);
	}

	if ( (CHECK_HOUR(*startHour) == -1) || (CHECK_MIN(*startMin) == -1) ){
		*startHour = QUIET_TYPE002_START_HOUR;
		*startMin = QUIET_TYPE002_START_MIN;
	}
	if ( (CHECK_HOUR(*endHour) == -1) || (CHECK_MIN(*endMin) == -1) ){
		*endHour = QUIET_TYPE002_END_HOUR;
		*endMin = QUIET_TYPE002_END_MIN;
	}

	result = 0;
onErr:
	return result;	
}




static int SearchSetConfigTableIndex( SETCONFIGTABLE *table, char *str )
{
	int i = -1;

	if ( (table == NULL) || (str == NULL) ) goto  onErr;

	i = 0;
	while( table[i].index != -1 ){
		if ( !strcmp( table[i].cmd2Str, str ) ) {
			break;
		} 
		i++;
	}
	if ( table[i].index == -1 ) i = -1;

onErr:
	return i;
}


/* -----------------------------------------------------------------------------
	[Name] GetMSIList01
	[Memo]
		Get printer status, update it to internal variable.
	[Args]
		void
	[Return]
		-1 : Error 
----------------------------------------------------------------------------- */
static int GetMSIList01( void ) {
	GList *gList = NULL;
	int index;
	int startHour, startMin, endHour, endMin;
	int result = -1;

	/* Create MSI List */
	if ( CreateMSIList( &gList, 5, 4000 ) != 0 ) goto onErr;

	/* Set MSI to global */
	if ( IsCustomSettings( gUiType )  ){
		/* init */
		InitCreate_SetconfigType001_CustomSettings( gUiType );

		/* PaperGap */
		if ( (index = SearchSetConfigTableIndex( setConfigTablePaperGap, GetMSIStr( gList, MSI_TYPE_PAPERGAP ) )) != -1 ) {
			gAbrasionPrevention = index;
			//fprintf( stderr, "gAbrasionPrevention : %d\n", gAbrasionPrevention );
		}

		/* Dry Level */
		if ( (index = SearchSetConfigTableIndex( setConfigTableDryLevel, GetMSIStr( gList, MSI_TYPE_DRYLEVEL ) )) != -1 ) {
			gDryLevelValue = index;
			//fprintf( stderr, "gDryLevelValue : %d\n", gDryLevelValue );
		}

		if ( gUiType == UI_CUSTOMSETTINGS_TYPE002 ){
			/* PerventPaperJam */
			if ( (index = SearchSetConfigTableIndex( setConfigTablePaperJam, GetMSIStr( gList, MSI_TYPE_PLAINPAPERFEEDER) )) != -1 ) {
				gPreventPaperJam = index;
				//fprintf( stderr, "gPreventPaperJam : %d\n", gPreventPaperJam );
			}
		}

		if ( gUiType == UI_CUSTOMSETTINGS_TYPE003 ){
			/* W Feed */
			if ( (index = SearchSetConfigTableIndex( setConfigTableWFeed, GetMSIStr( gList, MSI_TYPE_WFEED) )) != -1 ) {
				gPreventPaperDoubleFeed = index;
				//fprintf( stderr, "gPreventPaperDoubleFeed : %d\n", gPreventPaperDoubleFeed );
			}
		}
	}
	else if ( IsAutoPower( gUiType ) ){
		/* init */
		InitCreate_SetConfigType001_AutoPower( gUiType );

		if ( (gUiType == UI_AUTOPOWER_TYPE001) || (gUiType == UI_AUTOPOWER_TYPE002) ){
			/* Auto Power ON */
			if ( (index = SearchSetConfigTableIndex( setConfigTableAutoPowerOn, GetMSIStr( gList, MSI_TYPE_AUTOPOWERON ))) != -1 ){
				gAutoPowerOnIndex = index;
				//fprintf( stderr, "gAutoPowerOnIndex : %s\n", GetMSIStr( gList, MSI_TYPE_AUTOPOWERON ) );
				//fprintf( stderr, "gAutoPowerOnIndex : %d\n", gAutoPowerOnIndex );
			}
		}

		/* Auto Power OFF */
		if ( gUiType == UI_AUTOPOWER_TYPE001 ){
			if ( (index = SearchSetConfigTableIndex( setConfigTableAutoPowerOff, GetMSIStr( gList, MSI_TYPE_AUTOPOWEROFF ) )) != -1){
				gAutoPowerOffIndex = index;
			}
		}
		/* Auto Power OFF */
		if ( (gUiType == UI_AUTOPOWER_TYPE002) || (gUiType == UI_AUTOPOWER_TYPE003) ){
			//fprintf( stderr, "Auto Power OFF<1>\n" );
			if ( (index = SearchSetConfigTableIndex( setConfigTableAutoPowerOff02, GetMSIStr( gList, MSI_TYPE_AUTOPOWEROFF ) )) != -1 ){
			//fprintf( stderr, "Auto Power OFF<2>\n" );
				gAutoPowerOffIndex = index;
			}
		}
		/* Auto Power OFF */
		if ( gUiType == UI_AUTOPOWER_TYPE004 ){
			if ( (index = SearchSetConfigTableIndex( setConfigTableAutoPowerOff, GetMSIStr( gList, MSI_TYPE_AUTOPOWEROFF ) )) != -1){
				gAutoPowerOffIndex = index;
			}
			if ( (index = SearchSetConfigTableIndex( setConfigTableAutoPowerOff03, GetMSIStr( gList, MSI_TYPE_AUTOPOWERBTOFF) )) != -1){
				gAutoPowerOffBtIndex = index;
			}
			else{
				//fprintf( stderr, "Error in SearchSetConfigTableIndex\n" );
			}
		}
	}
	else if ( IsPaperSourceSettings( gUiType ) ) {
		/* init */
		InitCreate_SetConfigType001_PaperSourceSettings();

		/* Plain Paper Feeder */
		if ( (index = SearchSetConfigTableIndex( setConfigTablePlainPaperFeeder, GetMSIStr( gList, MSI_TYPE_PLAINPAPERFEEDER ) )) != -1 ) {
			gPaperSourceSettingsValue = index;
			//fprintf( stderr, "gPaperSourceSettingsValue : %d\n", gPaperSourceSettingsValue );
		}
	}
	else if ( IsQuietMode( gUiType ) ) {
		//fprintf( stderr, "IsQuietMode\n" );
		/* init */
		InitCreate_SetConfigType001_QuietMode( gUiType );

		/* Silent */
		//fprintf( stderr, "str:%s\n", GetMSIStr( gList, MSI_TYPE_SILENT) );
		if ( (index = SearchSetConfigTableIndex( setConfigTableQuietMode, GetMSIStr( gList, MSI_TYPE_SILENT) )) != -1 ) {
			//fprintf( stderr, "index : %d IsQuietMode\n", index );
			gQuietModeType002 = index;
			//fprintf( stderr, "gQuietModeType002 : %d\n", gQuietModeType002 );
		}

		/* Silent Time */
		if ( GetMSITime( gList, &startHour, &startMin, &endHour, &endMin ) != -1 ){
			gQuietModeType002StartHour = startHour;
			gQuietModeType002StartMin = startMin;
			gQuietModeType002EndHour = endHour;
			gQuietModeType002EndMin = endMin;
			//fprintf( stderr, "TIME :%d %d %d %d\n", startHour, startMin, endHour, endMin );
		}
	}

	result = 0;
onErr:
	DisposeMSIList( gList );
	return result;
}

/* -----------------------------------------------------------------------------
	[Name] GetMSIPaperSourceSettingsViaPrinter
	[Memo]
		Get printer status for papersource settings via printer.
	[Args]
	[Return]
		-1 : Error 
----------------------------------------------------------------------------- */
int SetMSIPaperSourceSettings( void )
{
	GList *gList = NULL;
	char *strPtr;
	int result = -1;

	gPaperSourceSettingsValueForUI = -1;

	/* Create MSI List */
	if ( CreateMSIList( &gList, 0, 0 ) != 0 ) goto onErr;;

	/* Plain Paper Feeder */
	if ( (strPtr = GetMSIStr(gList, MSI_TYPE_PLAINPAPERFEEDER)) == NULL ) goto onErr;
	
	if ( !strcmp( strPtr, MSI_STR_FSF )){
		gPaperSourceSettingsValueForUI = CND_SUPPLY_CASSETTE;
	}
	else if ( !strcmp( strPtr, MSI_STR_ASF )){
		gPaperSourceSettingsValueForUI = CND_SUPPLY_ASF;
	}
	else{
		goto onErr;
	}

	result = 0;
onErr:
	/* Dispose MSI List */
	DisposeMSIList( gList );
	return result;
}

int GetMSIPaperSourceSettingsCurrentValue( void )
{
	return gPaperSourceSettingsValueForUI;
}

/* -----------------------------------------------------------------------------
	[Name] GetMSIPaperSourceSettings01
	[Memo]
		Get printer status for papersource settings when selected plain paper.
	[Args]
		(OUT)PaperSource
			The following is set.
				CND_SUPPLY_ASF or CND_SUPPLY_CASSETTE
	[Return]
		-1 : Error 
----------------------------------------------------------------------------- */
int GetMSIPaperSourceSettings01( int *paperSource )
{
	GList *gList = NULL;
	char *strPtr;
	int result = -1;

	if ( paperSource == NULL ) goto onErr;
	*paperSource = CND_SUPPLY_CASSETTE;

	/* Create MSI List */
	if ( CreateMSIList( &gList, 0, 0 ) != 0 ) goto onErr;;

	/* Plain Paper Feeder */
	if ( (strPtr = GetMSIStr(gList, MSI_TYPE_PLAINPAPERFEEDER)) == NULL ) goto onErr;

	if ( !strcmp( strPtr, MSI_STR_FSF )){
		*paperSource = CND_SUPPLY_CASSETTE;
	}
	else if ( !strcmp( strPtr, MSI_STR_ASF )){
		*paperSource = CND_SUPPLY_ASF;
	}
	else goto onErr;

	result = 0;
onErr:
	/* Dispose MSI List */
	DisposeMSIList( gList );
	return result;
}


static int GetActiveButtonIndexFromSetConfigTable( GtkWidget* window, const SETCONFIGTABLE* table, int default_index)
{
	GtkWidget* button;
	int index = 0;

	while( table[index].index != -1 )
	{
		if( (button = LookupWidget(window, table[index].uiStr)) != NULL )
		{
			if( GTK_TOGGLE_BUTTON(button)->active )
				return index;
		}
		index++;
	}
	return default_index;
}

static void SetComboBoxItemsFromSetConfigTable(GtkWidget *combo, const SETCONFIGTABLE* table, int n, int index)
{
	int		i;

	/* Remove all items in current list */
	if(gtk_combo_box_get_active_text( GTK_COMBO_BOX( combo )) ){
		while( 1 ){
			gtk_combo_box_set_active( GTK_COMBO_BOX( combo ), 0 );
			if( ! gtk_combo_box_get_active_text( GTK_COMBO_BOX( combo )) ) break;
			gtk_combo_box_remove_text( GTK_COMBO_BOX( combo ), 0 );
		}
	}


	/* Add items in "table" */
	for (i=0; i < n; i++)
	{
		gtk_combo_box_append_text( GTK_COMBO_BOX( combo ), LookupText(g_keytext_list, table[i].uiStr) );
	}

	if( index >= n ) index = 0;
	gtk_combo_box_set_active( GTK_COMBO_BOX( combo ), index );
}

static short RetFunctionStatusWithConnectSwitch( int uiType, short okStatus, short ngStatus )
{
	int type;
	char uriBuf[URI_BUF_SIZE];
	gUiType = uiType;
	short result  =  ngStatus;

	if ( ParseDeviceURI( &type, uriBuf, URI_BUF_SIZE ) == -1 ) goto onErr;

	if ( type != -1 ) {
		result = okStatus;
	}

onErr:
	return result;
}

static void ModifyZeroValue( GtkSpinButton *spinbutton )
{
	if( !strncmp( gtk_entry_get_text( GTK_ENTRY( spinbutton ) ), "-0" , 2 ) ) {
		gtk_spin_button_set_value( GTK_SPIN_BUTTON( spinbutton ), 1 );
		gtk_spin_button_set_value( GTK_SPIN_BUTTON( spinbutton ), 0 );
	}
}

/* export functions */
short ExecSetConfigType000_000( char *dialogName ){ return US_F_PAPER_SOURCE_SETTING; }
short ExecSetConfigType000_001( char *dialogName ){ return US_F_INK_CARTRIDGE; }
short ExecSetConfigType000_002( char *dialogName ){ return US_F_POWER_OFF; }
short ExecSetConfigType000_003( char *dialogName ){ return US_F_AUTO_POWER; }
short ExecSetConfigType000_004( char *dialogName ){ return US_F_CUSTOM; }
short ExecSetConfigType000_005( char *dialogName ){ return US_F_QUIET; }
short ExecSetConfigType000_006( char *dialogName ){ return US_F_QUIET_SETTING; } /* Ver.3.60 */
//short ExecSetConfigType000_007( char *dialogName ){ gUiType = UI_CUSTOMSETTINGS_TYPE001; return US_F_CUSTOM; } /* Ver.3.70 */
short ExecSetConfigType000_007( char *dialogName ){ return RetFunctionStatusWithConnectSwitch( UI_CUSTOMSETTINGS_TYPE001, US_F_CUSTOM, US_F_CUSTOM_CONNECTIONOFF); } /* Ver.3.70 */
short ExecSetConfigType000_008( char *dialogName ){ gUiType = UI_CUSTOMSETTINGS_TYPE002; return US_F_CUSTOM; } /* Ver.3.70 */
//short ExecSetConfigType000_009( char *dialogName ){ gUiType = UI_CUSTOMSETTINGS_TYPE003; return US_F_CUSTOM; } /* Ver.3.70 */
short ExecSetConfigType000_009( char *dialogName ){ return RetFunctionStatusWithConnectSwitch( UI_CUSTOMSETTINGS_TYPE003, US_F_CUSTOM, US_F_CUSTOM_CONNECTIONOFF); } /* Ver.3.70 */
short ExecSetConfigType000_010( char *dialogName ){ gUiType = UI_AUTOPOWER_TYPE001; return US_F_AUTO_POWER; } /* Ver.3.70 */
short ExecSetConfigType000_011( char *dialogName ){ gUiType = UI_AUTOPOWER_TYPE002; return US_F_AUTO_POWER; } /* Ver.3.70 */
//short ExecSetConfigType000_012( char *dialogName ){ gUiType = UI_AUTOPOWER_TYPE003; return US_F_AUTO_POWER; } /* Ver.3.70 */
short ExecSetConfigType000_012( char *dialogName ){ return RetFunctionStatusWithConnectSwitch( UI_AUTOPOWER_TYPE003, US_F_AUTO_POWER, US_F_AUTO_POWER_CONNECTIONOFF); } /* Ver.3.70 */
//short ExecSetConfigType000_013( char *dialogName ){ gUiType = UI_PAPERSOURCESETTINGS_TYPE001; return US_F_PAPER_SOURCE_SETTING; } /* Ver.3.70 */
short ExecSetConfigType000_013( char *dialogName ){ return RetFunctionStatusWithConnectSwitch( UI_PAPERSOURCESETTINGS_TYPE001, US_F_PAPER_SOURCE_SETTING, US_F_PAPER_SOURCE_SETTING_CONNECTIONOFF); } /* Ver.3.70 */
short ExecSetConfigType000_014( char *dialogName ){ gUiType = UI_QUIET_TYPE001; return US_F_QUIET; } /* Ver.3.70 */
//short ExecSetConfigType000_015( char *dialogName ){ gUiType = UI_QUIET_TYPE002; return US_F_QUIET_SETTING; } /* Ver.3.70 */
short ExecSetConfigType000_015( char *dialogName ){ return RetFunctionStatusWithConnectSwitch( UI_QUIET_TYPE002, US_F_QUIET_SETTING, US_F_QUIET_SETTING_CONNECTIONOFF); } /* Ver.3.70 */
//short ExecSetConfigType000_016( char *dialogName ){ gUiType = UI_AUTOPOWER_TYPE004; return US_F_AUTO_POWER; } /* Ver.3.70 */
short ExecSetConfigType000_016( char *dialogName ){ return RetFunctionStatusWithConnectSwitch( UI_AUTOPOWER_TYPE004, US_F_AUTO_POWER, US_F_AUTO_POWER_CONNECTIONOFF); } /* Ver.3.70 */
short ExecSetConfigType001_000( char *dialogName ){ return ( ExecSetConfigType001( (void *)&setConfigType001Res[0], dialogName) ); }
short ExecSetConfigType002_000( char *dialogName ){ return ( ExecSetConfigType002( (void *)&setConfigType002Res[0], dialogName) ); }
short ExecSetConfigType003_000( char *dialogName ){ return ( ExecSetConfigType003( (void *)&setConfigType003Res[0], dialogName) ); }
short ExecSetConfigType004_000( char *dialogName ){ return ( ExecSetConfigType004( (void *)&setConfigType004Res[0], dialogName) ); }

