/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2011
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

#include "callbacks.h"
#ifndef USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"

#include "util_cmd.h"
#include "util_com.h"
#include "util_parse_flow.h"
#include "util_setconfig.h"


/* UI type */
enum {
	UI_CUSTOMSETTINGS_TYPE001 = 1,
	UI_CUSTOMSETTINGS_TYPE002,
	UI_CUSTOMSETTINGS_TYPE003,
	UI_AUTOPOWER_TYPE001,
	UI_AUTOPOWER_TYPE002,
	UI_AUTOPOWER_TYPE003,
	UI_PAPERSOURCESETTINGS_TYPE001,
	UI_QUIET_TYPE001,
	UI_QUIET_TYPE002,
	UI_POWEROFF_TYPE001,
};

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
};


/* SETCONFIG COMPTYPE001 */
typedef struct {
	long	resType;
	long uiType;
	GtkWidget *(*ptrCreateDialog )( void );
} SETCONFIGCOMPTYPE001RES, *LPSETCONFIGCOMPTYPE001RES;

SETCONFIGCOMPTYPE001RES setConfigType001Res[] = {
	{ RES_SETCONFIG_COMPTYPE001, UI_CUSTOMSETTINGS_TYPE001, create_setconfig_type001_dialog }, 
	{ RES_SETCONFIG_COMPTYPE001, UI_AUTOPOWER_TYPE001, create_setconfig_type001_dialog }, 
	{ RES_SETCONFIG_COMPTYPE001, UI_PAPERSOURCESETTINGS_TYPE001, create_setconfig_type001_dialog }, 
	{ RES_SETCONFIG_COMPTYPE001, UI_QUIET_TYPE001, create_setconfig_type001_dialog }, 
	{ RES_SETCONFIG_COMPTYPE001, UI_AUTOPOWER_TYPE002, create_setconfig_type001_dialog }, /* Ver.3.50 */
	{ RES_SETCONFIG_COMPTYPE001, UI_CUSTOMSETTINGS_TYPE002, create_setconfig_type001_dialog }, /* Ver.3.50 */
	{ RES_SETCONFIG_COMPTYPE001, UI_QUIET_TYPE002, create_setconfig_type001_dialog }, /* Ver.3.60 */
	{ RES_SETCONFIG_COMPTYPE001, UI_AUTOPOWER_TYPE003, create_setconfig_type001_dialog }, /* Ver.3.60 */
	{ RES_SETCONFIG_COMPTYPE001, UI_CUSTOMSETTINGS_TYPE003, create_setconfig_type001_dialog }, /* Ver.3.60 */
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


/* Each Type Function Work */
enum {
	WORK_SETCONFIG_COMPTYPE001=1,
	WORK_SETCONFIG_COMPTYPE002,
	WORK_SETCONFIG_COMPTYPE003,
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

#define QUIET_TYPE002_START_HOUR	21
#define QUIET_TYPE002_START_MIN		0
#define QUIET_TYPE002_END_HOUR	7
#define QUIET_TYPE002_END_MIN	0

enum {
	QUIET_TYPE002_OFF=0,
	QUIET_TYPE002_ON,
	QUIET_TYPE002_TIMER,
};

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

/* function prototypes */
static void update_quiet_type002_radiobutton( GtkWidget* );


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
		dryLevelValue = drylevel5_button_value[gDryLevelValue];
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, dryLevelValue ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, paperGapString[gAbrasionPrevention] ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE002 ){
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, autoPowerOnValue[gAutoPowerOnIndex] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, autoPowerOffValue[gAutoPowerOffIndex] ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE003 ){
		size = cmdData[gPaperSourceSettingsValue].len;
		memcpy( p, cmdData[gPaperSourceSettingsValue].cmd, size ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE004 ){
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, switchString[gQuietMode]  ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE005 ){
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, autoPowerOnValue[gAutoPowerOnIndex] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, autoPowerOffValueType2[gAutoPowerOffIndex] ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE006 ){
		dryLevelValue = drylevel5_button_value[gDryLevelValue];
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, dryLevelValue ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, paperGapString[gAbrasionPrevention] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[2].cmd, paperJamString[gPreventPaperJam] ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE007 ){
		if ( gQuietModeType002 == QUIET_TYPE002_TIMER ){
			char timeBuf[CMD_BUF_MAX_SIZE];
			memset( timeBuf, 0, CMD_BUF_MAX_SIZE );

			snprintf( timeBuf, CMD_BUF_MAX_SIZE, "%02d%02d%02d%02d", gQuietModeType002StartHour, gQuietModeType002StartMin,
				gQuietModeType002EndHour, gQuietModeType002EndMin );

			size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, switchString2[gQuietModeType002] ); p += size;
			size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[1].cmd, timeBuf ); p += size;
		}
		else {
			size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, switchString2[gQuietModeType002] ); p += size;
		}
	}
	else if ( type == CMD_SETCONFIG_TYPE008 ){
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[1].cmd, autoPowerOffValueType2[gAutoPowerOffIndex] ); p += size;
	}
	else if ( type == CMD_SETCONFIG_TYPE009 ){
		dryLevelValue = drylevel5_button_value[gDryLevelValue];
		size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[0].cmd, dryLevelValue ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[1].cmd, paperGapString[gAbrasionPrevention] ); p += size;
		size = snprintf( p, CMD_BUF_MAX_SIZE - size, cmdData[2].cmd, paperWFeedString[gPreventPaperDoubleFeed] ); p += size;
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
}

static void InitCreate_SetConfigType001_AutoPower( int uiType )
{
	gAutoPowerOnIndex = 0;
	gCurrentAutoPowerOnIndex = 0;

	if ( uiType == UI_AUTOPOWER_TYPE001 ){
		gAutoPowerOffIndex = 0;
	}
	else if ( (uiType == UI_AUTOPOWER_TYPE002) || (uiType == UI_AUTOPOWER_TYPE003) ){
		gAutoPowerOffIndex = 5;
	}
	gCurrentAutoPowerOffIndex = 0;
}

static void InitCreate_SetConfigType001_PaperSourceSettings( void )
{
	gPaperSourceSettingsValue = PAPERSOURCE_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT;
	gCurrentPaperSourceSettingsValue = 0;
}

static void InitCreate_SetConfigType001_QuietMode( int uiType )
{
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
}

static int GetAutoPowerIndex(const char **Keytbl, int n, char *mode)
{
	int			i;
	
	for (i=0; i < n; i++) {
		if (!strcmp(LookupText(g_keytext_list, Keytbl[i]), mode))	
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
	gUiType = lpWork->uiType = lpRes->uiType;
	lpWork->dialog = lpRes->ptrCreateDialog();


	if ( IsCustomSettings( lpWork->uiType ) ){
		if ( gIsFirstExecCustom ) {
			InitCreate_SetconfigType001_CustomSettings( lpWork->uiType );
			gIsFirstExecCustom = 0;
		}
	}
	else if ( IsAutoPower( lpWork->uiType ) ){
		if ( gIsFirstExecAutoPower ){
			InitCreate_SetConfigType001_AutoPower( lpWork->uiType );
			gIsFirstExecAutoPower = 0;
		}
	}
	else if ( IsPaperSourceSettings( lpWork->uiType ) ) {
		if ( gIsFirstPaperSource ){
			InitCreate_SetConfigType001_PaperSourceSettings();
			gIsFirstPaperSource = 0;
		}
	}
	else if ( IsQuietMode( lpWork->uiType ) ) {
		if ( gIsFirstExecQuiet ){
			InitCreate_SetConfigType001_QuietMode( lpWork->uiType );
			gIsFirstExecQuiet = 0;
		}
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
		button = LookupWidget( dialog,  setconfig_type001_radiobutton_name[CUSTOM_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT] );
	}
	else {
		button = LookupWidget( dialog,  setconfig_type001_radiobutton_name[gDryLevelValue] );
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
	GtkWidget *powerOnCombo, *powerOffCombo;
	short onSize, offSize;

	powerOnCombo = LookupWidget(dialog, "setconfig_type001_combobox201");
	powerOffCombo = LookupWidget(dialog, "setconfig_type001_combobox202");

	if ( uiType == UI_AUTOPOWER_TYPE001 ){
		onSize = sizeof(setconfig_type001_02_onlist)/sizeof(*setconfig_type001_02_onlist) - 1;
		offSize = sizeof(setconfig_type001_02_offlist)/sizeof(*setconfig_type001_02_offlist) - 1;
		
		if ( isDefault ){
			SetComboBoxItems(powerOnCombo, setconfig_type001_02_onlist, onSize, 0 );
			SetComboBoxItems(powerOffCombo, setconfig_type001_02_offlist, offSize ,0 );
		}
		else {
			SetComboBoxItems(powerOnCombo, setconfig_type001_02_onlist, onSize, gAutoPowerOnIndex );
			SetComboBoxItems(powerOffCombo, setconfig_type001_02_offlist, offSize , gAutoPowerOffIndex );
		}
		gtk_widget_show( powerOnCombo );
		gtk_widget_show( powerOffCombo );
	}
	else if ( uiType == UI_AUTOPOWER_TYPE002 ){
		onSize = sizeof(setconfig_type001_02_onlist)/sizeof(*setconfig_type001_02_onlist) - 1;
		offSize = sizeof(setconfig_type001_03list)/sizeof(*setconfig_type001_03list) - 1;

		if ( isDefault ){
			SetComboBoxItems(powerOnCombo, setconfig_type001_02_onlist, onSize, 0 );
			SetComboBoxItems(powerOffCombo, setconfig_type001_03list, offSize , 5 );
		}
		else {
			SetComboBoxItems(powerOnCombo, setconfig_type001_02_onlist, onSize, gAutoPowerOnIndex);
			SetComboBoxItems(powerOffCombo, setconfig_type001_03list, offSize , gAutoPowerOffIndex);
		}
		gtk_widget_show( powerOnCombo );
		gtk_widget_show( powerOffCombo );
	}
	else if ( uiType == UI_AUTOPOWER_TYPE003 ){
		offSize = sizeof(setconfig_type001_03list)/sizeof(*setconfig_type001_03list) - 1;

		if ( isDefault ){
			SetComboBoxItems(powerOffCombo, setconfig_type001_03list, offSize , 5 );
		}
		else {
			SetComboBoxItems(powerOffCombo, setconfig_type001_03list, offSize , gAutoPowerOffIndex);
		}
		gtk_widget_show( powerOffCombo );
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
		button = LookupWidget( dialog, setconfig_type001_ps_radiobutton_name[PAPERSOURCE_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT] );
	}
	else {
		button = LookupWidget( dialog, setconfig_type001_ps_radiobutton_name[gPaperSourceSettingsValue] );
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
			button = LookupWidget( dialog,  setconfig_type001_quiet_type002_radiobutton_name[QUIET_TYPE002_OFF] );
			gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
		}
		else {
			button = LookupWidget( dialog,  setconfig_type001_quiet_type002_radiobutton_name[gQuietModeType002] );
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

	if ( IsCustomSettings( lpWork->uiType ) ){
		InitUISetConfigType001_CustomSettings( lpWork->uiType, lpWork->dialog );
	}
	else if ( IsAutoPower( lpWork->uiType ) ){
		InitUISetConfigType001_AutoPower( lpWork->uiType, lpWork->dialog );
	}
	else if ( IsPaperSourceSettings( lpWork->uiType ) ) {
		InitUISetConfigType001_PaperSourceSettings( lpWork->dialog );
	}
	else if ( IsQuietMode( lpWork->uiType ) ) {
		InitUISetConfigType001_QuietMode( lpWork->uiType, lpWork->dialog );
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
	gCurrentDryLevelValue = (short)GetActiveButtonIndex( window, setconfig_type001_radiobutton_name, CUSTOM_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT );

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
	GtkWidget *onCombo, *offCombo;
	gchar *onStr, *offStr;
	short onSize, offSize;

	onCombo = LookupWidget( GTK_WIDGET(button), "setconfig_type001_combobox201" );
	offCombo = LookupWidget( GTK_WIDGET(button), "setconfig_type001_combobox202" );

	onStr = gtk_combo_box_get_active_text(GTK_COMBO_BOX(onCombo));
	offStr = gtk_combo_box_get_active_text(GTK_COMBO_BOX(offCombo));


	if ( uiType == UI_AUTOPOWER_TYPE001 ){
		onSize = sizeof(setconfig_type001_02_onlist)/sizeof(*setconfig_type001_02_onlist);
		offSize = sizeof(setconfig_type001_02_offlist)/sizeof(*setconfig_type001_02_offlist);

		gCurrentAutoPowerOnIndex = GetAutoPowerIndex( setconfig_type001_02_onlist, onSize, onStr );
		gCurrentAutoPowerOffIndex = GetAutoPowerIndex( setconfig_type001_02_offlist, offSize, offStr );
	}
	else if ( uiType == UI_AUTOPOWER_TYPE002 ){
		onSize = sizeof(setconfig_type001_02_onlist)/sizeof(*setconfig_type001_02_onlist);
		offSize = sizeof(setconfig_type001_03list)/sizeof(*setconfig_type001_03list);

		gCurrentAutoPowerOnIndex = GetAutoPowerIndex( setconfig_type001_02_onlist, onSize, onStr );
		gCurrentAutoPowerOffIndex = GetAutoPowerIndex( setconfig_type001_03list, offSize, offStr );
	}
	else if ( uiType == UI_AUTOPOWER_TYPE003 ){
		offSize = sizeof(setconfig_type001_03list)/sizeof(*setconfig_type001_03list);

		gCurrentAutoPowerOffIndex = GetAutoPowerIndex( setconfig_type001_03list, offSize, offStr );
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

		gCurrentQuietModeType002 = (short)GetActiveButtonIndex( window, setconfig_type001_quiet_type002_radiobutton_name, QUIET_TYPE002_RADIOBUTTON_DEFAULT );
	}
}

static short GetStatusSetConfigType001_AutoPower( int uiType )
{
	short status = US_X;

	switch ( uiType ) {
		case UI_AUTOPOWER_TYPE001:
		case UI_AUTOPOWER_TYPE002:
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
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(widget)));
  return FALSE;
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
			UtilMessageBox(LookupText(g_keytext_list, "LUM_LID_WARNING_PAPER_ABRASION"), g_window_title, MB_ICON_NO | MB_OK);
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
			status = UtilMessageBox(LookupText(g_keytext_list, "LUM_IDS_MNTMSG_PREVENTPAPERGAP_MSG"), g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL);
			if ( (status == US_CANCEL) || (status == US_X) ){
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
			status = UtilMessageBox(LookupText(g_keytext_list, "LUM_IDS_MNTMSG_PREVENTWFEED_MSG"), g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL);
			if ( (status == US_CANCEL) || (status == US_X) ){
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


	if ( IsCustomSettings( lpWk->uiType ) ){
		GetParmSetConfigType001_CustomSettings( lpWk->uiType, button );
	}
	else if ( IsAutoPower( lpWk->uiType ) ){
		GetParmSetConfigType001_AutoPower( lpWk->uiType, button );
		status = GetStatusSetConfigType001_AutoPower( lpWk->uiType );
	}	
	else if ( IsPaperSourceSettings( lpWk->uiType ) ) {
		gCurrentPaperSourceSettingsValue = 
			(short)GetActiveButtonIndex( window, setconfig_type001_ps_radiobutton_name, PAPERSOURCE_SETTINGS_TYPE001_RADIOBUTTON_DEFAULT );
	}
	else if ( IsQuietMode( lpWk->uiType ) ) {
		GetParmSetConfigType001_QuietMode( lpWk->uiType, button );
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

	current = (short)GetActiveButtonIndex( window, setconfig_type001_quiet_type002_radiobutton_name, QUIET_TYPE002_RADIOBUTTON_DEFAULT );

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

	SetLabelCommonUtilDialogForSetConfig( dialogName, lpWork->flag, &lpWork->status );
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

	/* ---- Show Dialog ---- */
	/* init parameter */
	InitParamSetConfigType002( lpRes, gLPSetConfigWork );

	/* show dialog */
	ShowDialogSetConfigType002 ( lpRes, gLPSetConfigWork, dialogName );

	/* ---- Output BJL ---- */
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

/* export functions */
short ExecSetConfigType000_000( char *dialogName ){ return US_F_PAPER_SOURCE_SETTING; }
short ExecSetConfigType000_001( char *dialogName ){ return US_F_INK_CARTRIDGE; }
short ExecSetConfigType000_002( char *dialogName ){ return US_F_POWER_OFF; }
short ExecSetConfigType000_003( char *dialogName ){ return US_F_AUTO_POWER; }
short ExecSetConfigType000_004( char *dialogName ){ return US_F_CUSTOM; }
short ExecSetConfigType000_005( char *dialogName ){ return US_F_QUIET; }
short ExecSetConfigType000_006( char *dialogName ){ return US_F_QUIET_SETTING; } /* Ver.3.60 */
short ExecSetConfigType001_000( char *dialogName ){ return ( ExecSetConfigType001( (void *)&setConfigType001Res[0], dialogName) ); }
short ExecSetConfigType001_001( char *dialogName ){ return ( ExecSetConfigType001( (void *)&setConfigType001Res[1], dialogName) ); }
short ExecSetConfigType001_002( char *dialogName ){ return ( ExecSetConfigType001( (void *)&setConfigType001Res[2], dialogName) ); }
short ExecSetConfigType001_003( char *dialogName ){ return ( ExecSetConfigType001( (void *)&setConfigType001Res[3], dialogName) ); }
short ExecSetConfigType001_004( char *dialogName ){ return ( ExecSetConfigType001( (void *)&setConfigType001Res[4], dialogName) ); } /* Ver.3.50 */
short ExecSetConfigType001_005( char *dialogName ){ return ( ExecSetConfigType001( (void *)&setConfigType001Res[5], dialogName) ); } /* Ver.3.50 */
short ExecSetConfigType001_006( char *dialogName ){ return ( ExecSetConfigType001( (void *)&setConfigType001Res[6], dialogName) ); } /* Ver.3.60 */
short ExecSetConfigType001_007( char *dialogName ){ return ( ExecSetConfigType001( (void *)&setConfigType001Res[7], dialogName) ); } /* Ver.3.60 */
short ExecSetConfigType001_008( char *dialogName ){ return ( ExecSetConfigType001( (void *)&setConfigType001Res[8], dialogName) ); } /* Ver.3.60 */
short ExecSetConfigType002_000( char *dialogName ){ return ( ExecSetConfigType002( (void *)&setConfigType002Res[0], dialogName) ); }
short ExecSetConfigType003_000( char *dialogName ){ return ( ExecSetConfigType003( (void *)&setConfigType003Res[0], dialogName) ); }

