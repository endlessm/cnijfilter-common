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

#include "callbacks.h"
#ifndef USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"

#include "util_cmd.h"
#include "util_com.h"
#include "util_setconfig.h"




/* UI type */
enum {
	UI_CONFIRM_PATTERN_TYPE001 = 1,
	UI_NOZZLECHECK_START_TYPE001,
	UI_NOZZLECHECK_START_TYPE002,
};

/* Each Type Function Resource */
enum {
	RES_NOZZLECHECK_COMPTYPE001=1,
	RES_NOZZLECHECK_COMPTYPE002,
};

/* NOZZLECHECK COMPTYPE001 */
typedef struct {
	long	resType;
	int		uiType;
	GtkWidget *(*ptrCreateDialog)( void );
} NOZZLECHECKCOMPTYPE001RES, *LPNOZZLECHECKCOMPTYPE001RES;

NOZZLECHECKCOMPTYPE001RES nozzleCheckType001Res[] = {
	{ RES_NOZZLECHECK_COMPTYPE001, UI_CONFIRM_PATTERN_TYPE001, create_nozzle_check_type001_dialog }, 
};

/* NOZZLECHECK COMPTYPE002 */
typedef struct {
	long	resType;
	int		uiType;
	GtkWidget *(*ptrCreateDialog)( void );
} NOZZLECHECKCOMPTYPE002RES, *LPNOZZLECHECKCOMPTYPE002RES;

NOZZLECHECKCOMPTYPE002RES nozzleCheckType002Res[] = {
	{ RES_NOZZLECHECK_COMPTYPE002, UI_NOZZLECHECK_START_TYPE001, create_nozzle_check_type002_dialog }, 
	{ RES_NOZZLECHECK_COMPTYPE002, UI_NOZZLECHECK_START_TYPE002, create_nozzle_check_type002_dialog }, 
};


/* Each Type Function Work */
enum {
	WORK_NOZZLECHECK_COMPTYPE001=1,
	WORK_NOZZLECHECK_COMPTYPE002,
};

/* NOZZLECHECK COMPTYPE001 */
typedef struct {
	long	workType;
	int	uiType;
	GtkWidget *dialog;
	short status;
} NOZZLECHECKCOMPTYPE001WORK, *LPNOZZLECHECKCOMPTYPE001WORK;

/* NOZZLECHECK COMPTYPE002 */
typedef struct {
	long	workType;
	int	uiType;
	GtkWidget *dialog;
	short status;
} NOZZLECHECKCOMPTYPE002WORK, *LPNOZZLECHECKCOMPTYPE002WORK;




/* nozzlecheck info */
#define OK_CHECK_PATTERN	0
#define NG_CHECK_PATTERN	1
#define OK_CHECK_PATTERN_TEMPLATE	"okptn_%s.xpm"
#define NG_CHECK_PATTERN_TEMPLATE	"ngptn_%s.xpm"

#define CHECKPATTERNPATH PACKAGE_DATA_DIR

static const char *pattern_file_template[64] =
{
	OK_CHECK_PATTERN_TEMPLATE,
	NG_CHECK_PATTERN_TEMPLATE,
};

/* bin info */
#define NOZZLECHECK_TYPE002_BINVALUE_MAX	3
#define NOZZLECHECK_TYPE002_BINVALUE_REARTRAY	0
#define NOZZLECHECK_TYPE002_BINVALUE_CASETTE	1
#define NOZZLECHECK_TYPE002_BINVALUE_CASETTE_AUTO	2
#define NOZZLECHECK_TYPE002_BINVALUE_NA			128
static const gchar* nozzlecheck_type002_radiobutton_name[] = {
	"nozzle_check_type002_radiobutton001",
	"nozzle_check_type002_radiobutton002",
	NULL
};

/* global */
static void *gLPNozzleCheckWork = NULL;
static int gBinValueNozzleCheck;
static int gIsFirst = 1;


/*** Output *************************************************************************************************/
static short OutputUtilityCommand_CMD_NozzleCheck( short type, short index, COMMANDDATA *cmdData, short cmdNum )
{
	char buf[CMD_BUF_MAX_SIZE];
	char *p;
	long size;
	short result = -1;

	if ( cmdData == NULL ) goto Err;
	if ( index > (cmdNum -1 ) ) goto Err;

	p = buf;
	size = 0;

	if ( type == CMD_NOZZLECHECK_TYPE001 ){
		size = cmdData[gBinValueNozzleCheck].len;
		memcpy( p, cmdData[gBinValueNozzleCheck].cmd, size ); p += size;
	}

	if ( size != 0 ){
		*p = 0x00; p++;
		size = (long)(p -buf);
		OutputCmdType001( buf, size );
	}

	result = 0;
Err:
	return result;
}

short OutputUtilityCommand_CMD_NozzleCheck_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_NozzleCheck( CMD_NOZZLECHECK_TYPE001, index, cmdData, cmdNum );
}


/*** COMMON **************************************************************************************************/
void InitExec_NozzleCheck( void )
{
	/* init global */
	gIsFirst = 1;
	gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_CASETTE;
}

/*** COMPTYPE000 *********************************************************************************************/
short ExecNozzleCheckType000_000( char *dialogName )
{
	return US_F_NOZZLE_CHECK;
}

short ExecNozzleCheckType000_001( char *dialogName )
{
	if ( gIsFirst ){
		return US_F_NOZZLE_CHECK_ONECE;
		gIsFirst = 0;
	}
	else {
		if ( gBinValueNozzleCheck == NOZZLECHECK_TYPE002_BINVALUE_REARTRAY ){
			return US_F_NOZZLE_CHECK_TWICE_REARTRAY;
		}
		else {
			return US_F_NOZZLE_CHECK_TWICE_CASETTE;
		}
	}
}

short ExecNozzleCheckType000_002( char *dialogName )
{
	int paperSource;
	short result = US_F_NOZZLE_CHECK_UNKNOWWN;

	if ( gIsFirst ){
		if ( GetMSIPaperSourceSettings01( &paperSource ) != -1 ){ 
			if ( paperSource == CND_SUPPLY_CASSETTE ){
				result = US_F_NOZZLE_CHECK_FSF;
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_CASETTE;
			}
			else {
				result = US_F_NOZZLE_CHECK_UNKNOWWN;
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_NA;
			}
		}
		else {
			result = US_F_NOZZLE_CHECK_UNKNOWWN;
			gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_NA;
		}
		gIsFirst = 0;
	}
	else {
		if ( gBinValueNozzleCheck == NOZZLECHECK_TYPE002_BINVALUE_CASETTE ){
			result = US_F_NOZZLE_CHECK_FSF;
		}
		else {
			result = US_F_NOZZLE_CHECK_UNKNOWWN;
		}
	}

	return result;
}

short ExecNozzleCheckType000_003( char *dialogName )
{
	int paperSource;
	short result = US_F_NOZZLE_CHECK_SELECT_BIN;

	if ( gIsFirst ){
		if ( GetMSIPaperSourceSettings01( &paperSource ) != -1 ){ 
			if ( paperSource == CND_SUPPLY_CASSETTE ){
				result = US_F_NOZZLE_CHECK_FSF;
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_CASETTE;
			}
			else if ( paperSource == CND_SUPPLY_ASF ){
				result = US_F_NOZZLE_CHECK_ASF;
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_REARTRAY;
			}
			else {
				result = US_F_NOZZLE_CHECK_SELECT_BIN;
			}
		}
		else {
			result = US_F_NOZZLE_CHECK_SELECT_BIN;
		}
		gIsFirst = 0;
	}
	else {
		if ( gBinValueNozzleCheck == NOZZLECHECK_TYPE002_BINVALUE_REARTRAY ){
			result =  US_F_NOZZLE_CHECK_ASF;
		}
		else {
			result = US_F_NOZZLE_CHECK_FSF;
		}
	}

	return result;	
}


short ExecNozzleCheckType000_004( char *dialogName )
{
	int paperSource;
	short result = US_F_NOZZLE_CHECK_UNKNOWWN;

	if ( gIsFirst ){
		if ( GetMSIPaperSourceSettings01( &paperSource ) != -1 ){ 
			if ( paperSource == CND_SUPPLY_CASSETTE ){
				result = US_F_NOZZLE_CHECK_FSF;
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_CASETTE;
			}
			else if ( paperSource == CND_SUPPLY_ASF ){
				result = US_F_NOZZLE_CHECK_ASF;
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_REARTRAY;
			}
			else if ( paperSource == CND_SUPPLY_CASSETTE_AUTO ){
				result = US_NOZZLE_CHECK_FRONT2;
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_CASETTE_AUTO;
			}
			else {
				result = US_F_NOZZLE_CHECK_UNKNOWWN;
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_NA;
			}
		}
		else {
			result = US_F_NOZZLE_CHECK_UNKNOWWN;
			gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_NA;
		}
		gIsFirst = 0;
	}
	else {
		if ( gBinValueNozzleCheck == NOZZLECHECK_TYPE002_BINVALUE_CASETTE ){
			result = US_F_NOZZLE_CHECK_FSF;
		}
		else if ( gBinValueNozzleCheck == NOZZLECHECK_TYPE002_BINVALUE_REARTRAY ){
			result = US_F_NOZZLE_CHECK_ASF;
		}
		else if ( gBinValueNozzleCheck == NOZZLECHECK_TYPE002_BINVALUE_CASETTE_AUTO ){
			result = US_NOZZLE_CHECK_FRONT2;
		}
		else if ( gBinValueNozzleCheck == NOZZLECHECK_TYPE002_BINVALUE_NA ){
			result = US_F_NOZZLE_CHECK_UNKNOWWN;
		}
		else {
			result = US_F_NOZZLE_CHECK_UNKNOWWN;
		}
	}

	return result;
}

void SetPaperSourceInfoType000_004( void )
{
	int paperSource;

	if ( gIsFirst ){
		if ( GetMSIPaperSourceSettings01( &paperSource ) != -1 ){ 
			if ( paperSource == CND_SUPPLY_CASSETTE ){
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_CASETTE;
			}
			else if ( paperSource == CND_SUPPLY_ASF ){
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_REARTRAY;
			}
			else if ( paperSource == CND_SUPPLY_CASSETTE_AUTO ){
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_CASETTE_AUTO;
			}
			else {
				gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_NA;
			}
		}
		else {
			gBinValueNozzleCheck = NOZZLECHECK_TYPE002_BINVALUE_NA;
		}
		gIsFirst = 0;
	}
}




/*** COMPTYPE001 *********************************************************************************************/

static short GetNozzleCheckDataPath( char *inBuf, short inSize, short index, char *modelName )
{
	char buf[CMD_BUF_MAX_SIZE];
	char modelBuf[64];
	char *p;
	long size, remainder;
	int i;
	short result = -1;

	if ( modelName == NULL ) goto Err; 

	for ( i	= 0; i<strlen(modelName); i++ ){
		modelBuf[i] = LowerAsciiCode( modelName[i] );
	}
	modelBuf[i] = 0x00;

	p = buf;
	remainder = CMD_BUF_MAX_SIZE;
	size = snprintf( p, remainder, "%s", CHECKPATTERNPATH ); p += size; remainder -= size;
	size = snprintf( p, remainder, "%s", "/" ); p += size; remainder -= size;
	size = snprintf( p, remainder, pattern_file_template[index], modelBuf );  p += size; remainder -= size;
	*p = 0x00; p++;

	size = (long)(p - buf);
	if ( size > inSize ) goto Err;
	memcpy( inBuf, buf, size ); 

	result = 0;
Err:	
	return result;
}

static short SetPixMapNozzleCheckType000( GtkWidget *dialog )
{
	char *modelName;
	char buf[CMD_BUF_MAX_SIZE];
	GtkWidget *pixmap, *frame;
	//GtkPixmap *map, *iconMask;
	GdkBitmap *iconMask;
	GdkPixmap *map;
	GtkStyle *style;
	short result = -1;

	modelName = GetModelName();

	gtk_widget_realize( dialog );
	style = gtk_widget_get_style( dialog );
	
	/* draw ok pixmap */
	if ( GetNozzleCheckDataPath( buf, CMD_BUF_MAX_SIZE, OK_CHECK_PATTERN, modelName ) != 0 ) goto Err;
	map = gdk_pixmap_create_from_xpm( dialog->window, &iconMask, &style->bg[GTK_STATE_NORMAL], buf );
	pixmap = gtk_pixmap_new( map, iconMask );
	gtk_widget_ref( pixmap );
	gtk_widget_show( pixmap );
	frame = LookupWidget( GTK_WIDGET( dialog ), "nozzle_check_type001_frame001" );
	gtk_container_add( GTK_CONTAINER( frame ), pixmap );

	/* draw ng pixmap */
	if ( GetNozzleCheckDataPath( buf, CMD_BUF_MAX_SIZE, NG_CHECK_PATTERN, modelName ) != 0 ) goto Err;
	map = gdk_pixmap_create_from_xpm( dialog->window, &iconMask, &style->bg[GTK_STATE_NORMAL], buf );
	pixmap = gtk_pixmap_new( map, iconMask );
	gtk_widget_ref( pixmap );
	gtk_widget_show( pixmap );
	frame = LookupWidget( GTK_WIDGET( dialog ), "nozzle_check_type001_frame002" );
	gtk_container_add( GTK_CONTAINER( frame ), pixmap );

	result = 0;
Err:
	return result;
}

static LPNOZZLECHECKCOMPTYPE001WORK CreateWorkNozzleCheckType001( LPNOZZLECHECKCOMPTYPE001RES lpRes )
{
	LPNOZZLECHECKCOMPTYPE001WORK lpWork = NULL;

	if ( lpRes == NULL ) goto Err;
	if ( (lpWork = g_malloc0(sizeof(NOZZLECHECKCOMPTYPE001WORK))) == NULL ) goto Err;

	lpWork->workType = WORK_NOZZLECHECK_COMPTYPE001;
Err:
	return lpWork;
}

static void InitParamNozzleCheckType001( LPNOZZLECHECKCOMPTYPE001RES lpRes, void *lpGWork )
{
	LPNOZZLECHECKCOMPTYPE001WORK lpWork = (LPNOZZLECHECKCOMPTYPE001WORK)lpGWork;

	lpWork->status = US_DEFAULT;
	lpWork->uiType = lpRes->uiType;
	lpWork->dialog = lpRes->ptrCreateDialog();
}

static void SetLabelNozzleCheckType001( LPNOZZLECHECKCOMPTYPE001RES lpRes, void *lpGWork, char *dialogName )
{
	LPNOZZLECHECKCOMPTYPE001WORK lpWork = (LPNOZZLECHECKCOMPTYPE001WORK)lpGWork;
	SetLabelUtilDialog( lpWork->dialog, dialogName );
}

static void SetDefaultNozzleCheckType001( LPNOZZLECHECKCOMPTYPE001RES lpRes, void *lpGWork )
{
	LPNOZZLECHECKCOMPTYPE001WORK lpWork = (LPNOZZLECHECKCOMPTYPE001WORK)lpGWork;

	if ( lpWork->uiType == UI_CONFIRM_PATTERN_TYPE001 ){
		/* set pixmap */
		SetPixMapNozzleCheckType000( lpWork->dialog );
	}

}

static void ShowDialogNozzleCheckType001( LPNOZZLECHECKCOMPTYPE001RES lpRes, void *lpGWork )
{
	LPNOZZLECHECKCOMPTYPE001WORK lpWork = (LPNOZZLECHECKCOMPTYPE001WORK)lpGWork;

	gtk_widget_show( lpWork->dialog );
	gtk_window_set_transient_for( GTK_WINDOW(lpWork->dialog), GTK_WINDOW(g_main_window) );
	gtk_main();
}

static void DisposeWorkNozzleCheckType001( LPNOZZLECHECKCOMPTYPE001WORK lpWork )
{
	if ( lpWork == NULL ) goto Err;

	g_free( lpWork );
Err:
	return;
}

static short CheckWorkType001( void )
{
	LPNOZZLECHECKCOMPTYPE001WORK lpWork = (LPNOZZLECHECKCOMPTYPE001WORK)gLPNozzleCheckWork;
	short result = -1;

	if ( lpWork == NULL ) goto Err;
	if ( lpWork->workType !=  WORK_NOZZLECHECK_COMPTYPE001 ) goto Err;

	result = 0;
Err:
	return result;
}

static short GetStatusNozzleCheckType001( void *lpGWork )
{
	LPNOZZLECHECKCOMPTYPE001WORK lpWork = (LPNOZZLECHECKCOMPTYPE001WORK)lpGWork;
	return lpWork->status;
}

/*-------------------------------------------------------------------------------
	short ExecNozzleCheckType001( void *lpWork, char *dialogName )
-------------------------------------------------------------------------------*/
static short ExecNozzleCheckType001( void *lpWork, char *dialogName )
{
	LPNOZZLECHECKCOMPTYPE001RES lpRes = (LPNOZZLECHECKCOMPTYPE001RES)lpWork;
	short	result = -1;

	/* confirm data type */
	if ( lpRes->resType != RES_NOZZLECHECK_COMPTYPE001 ) goto Err;

	/* allocate  work */
	if ( (gLPNozzleCheckWork = CreateWorkNozzleCheckType001( lpRes )) == NULL ) goto Err;

	/* ---- Show Dialog ---- */
	/* init parameter */
	InitParamNozzleCheckType001( lpRes, gLPNozzleCheckWork );
	
	/* show labels */
	SetLabelNozzleCheckType001( lpRes, gLPNozzleCheckWork, dialogName );

	/* set default */
	SetDefaultNozzleCheckType001( lpRes, gLPNozzleCheckWork );

	/* show dialog */
	ShowDialogNozzleCheckType001( lpRes, gLPNozzleCheckWork );

	result = GetStatusNozzleCheckType001( gLPNozzleCheckWork );

	DisposeWorkNozzleCheckType001( gLPNozzleCheckWork );

Err:
	gLPNozzleCheckWork = NULL;
	return result;
}

/* callback functions */
gboolean
on_nozzle_check_type001_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(widget)));
  	return FALSE;
}


void
on_nozzle_check_type001_dialog_destroy (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


/*  Exit button */
void
on_nozzle_check_type001_button001_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	LPNOZZLECHECKCOMPTYPE001WORK lpWk = (LPNOZZLECHECKCOMPTYPE001WORK)gLPNozzleCheckWork;

	if ( CheckWorkType001() != 0 ) goto Err;

	lpWk->status = US_EXIT;
Err:
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
}

/* Cleaning button */
void
on_nozzle_check_type001_button002_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	LPNOZZLECHECKCOMPTYPE001WORK lpWk = (LPNOZZLECHECKCOMPTYPE001WORK)gLPNozzleCheckWork;

	if ( CheckWorkType001() != 0 ) goto Err;

	lpWk->status = US_F_CLEANING;
Err:
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
}


/*** COMPTYPE002 *********************************************************************************************/
static LPNOZZLECHECKCOMPTYPE002WORK CreateWorkNozzleCheckType002( LPNOZZLECHECKCOMPTYPE002RES lpRes )
{
	LPNOZZLECHECKCOMPTYPE002WORK lpWork = NULL;

	if ( lpRes == NULL ) goto Err;
	if ( (lpWork = g_malloc0(sizeof(NOZZLECHECKCOMPTYPE002WORK))) == NULL ) goto Err;

	lpWork->workType = WORK_NOZZLECHECK_COMPTYPE002;
Err:
	return lpWork;
}

static void InitParamNozzleCheckType002( LPNOZZLECHECKCOMPTYPE002RES lpRes, void *lpGWork )
{
	LPNOZZLECHECKCOMPTYPE002WORK lpWork = (LPNOZZLECHECKCOMPTYPE002WORK)lpGWork;

	lpWork->status = US_DEFAULT;
	lpWork->uiType = lpRes->uiType;
	lpWork->dialog = lpRes->ptrCreateDialog();

}

static void SetLabelNozzleCheckType002( LPNOZZLECHECKCOMPTYPE002RES lpRes, void *lpGWork, char *dialogName )
{
	LPNOZZLECHECKCOMPTYPE002WORK lpWork = (LPNOZZLECHECKCOMPTYPE002WORK)lpGWork;
	SetLabelUtilDialog( lpWork->dialog, dialogName );
}

static void SetDefaultNozzleCheckType002( LPNOZZLECHECKCOMPTYPE002RES lpRes, void *lpGWork )
{
	LPNOZZLECHECKCOMPTYPE002WORK lpWork = (LPNOZZLECHECKCOMPTYPE002WORK)lpGWork;
	GtkWidget *button;

	if ( lpWork->uiType == UI_NOZZLECHECK_START_TYPE001 ){
	}
	else if ( lpWork->uiType == UI_NOZZLECHECK_START_TYPE002 ){
		button = LookupWidget( lpWork->dialog, nozzlecheck_type002_radiobutton_name[gBinValueNozzleCheck] );
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
	}
}

static void ShowDialogNozzleCheckType002( LPNOZZLECHECKCOMPTYPE002RES lpRes, void *lpGWork )
{
	LPNOZZLECHECKCOMPTYPE002WORK lpWork = (LPNOZZLECHECKCOMPTYPE002WORK)lpGWork;

	gtk_widget_show( lpWork->dialog );
	gtk_window_set_transient_for( GTK_WINDOW(lpWork->dialog), GTK_WINDOW(g_main_window) );
	gtk_main();
}

static void DisposeWorkNozzleCheckType002( LPNOZZLECHECKCOMPTYPE002WORK lpWork )
{
	if ( lpWork == NULL ) goto Err;

	g_free( lpWork );
Err:
	return;
}

static short CheckWorkType002( void )
{
	LPNOZZLECHECKCOMPTYPE002WORK lpWork = (LPNOZZLECHECKCOMPTYPE002WORK)gLPNozzleCheckWork;
	short result = -1;

	if ( lpWork == NULL ) goto Err;
	if ( lpWork->workType !=  WORK_NOZZLECHECK_COMPTYPE002 ) goto Err;

	result = 0;
Err:
	return result;
}

static short GetStatusNozzleCheckType002( void *lpGWork )
{
	LPNOZZLECHECKCOMPTYPE002WORK lpWork = (LPNOZZLECHECKCOMPTYPE002WORK)lpGWork;
	return lpWork->status;
}

/*-------------------------------------------------------------------------------
	short ExecNozzleCheckType002( void *lpWork, char *dialogName )
-------------------------------------------------------------------------------*/
static short ExecNozzleCheckType002( void *lpWork, char *dialogName )
{
	LPNOZZLECHECKCOMPTYPE002RES lpRes = (LPNOZZLECHECKCOMPTYPE002RES)lpWork;
	short	result = -1;

	/* confirm data type */
	if ( lpRes->resType != RES_NOZZLECHECK_COMPTYPE002 ) goto Err;

	/* allocate  work */
	if ( (gLPNozzleCheckWork = CreateWorkNozzleCheckType002( lpRes )) == NULL ) goto Err;

	/* ---- Show Dialog ---- */
	/* init parameter */
	InitParamNozzleCheckType002( lpRes, gLPNozzleCheckWork );
	
	/* show labels */
	SetLabelNozzleCheckType002( lpRes, gLPNozzleCheckWork, dialogName );

	/* set default */
	SetDefaultNozzleCheckType002( lpRes, gLPNozzleCheckWork );

	/* show dialog */
	ShowDialogNozzleCheckType002( lpRes, gLPNozzleCheckWork );

	result = GetStatusNozzleCheckType002( gLPNozzleCheckWork );

	DisposeWorkNozzleCheckType002( gLPNozzleCheckWork );

Err:
	gLPNozzleCheckWork = NULL;
	return result;
}

/* callback functions */
void
on_nozzle_check_type002_dialog_destroy (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


gboolean
on_nozzle_check_type002_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(widget)));
  	return FALSE;
}

/* Print Check Pattern button */
void
on_nozzle_check_type002_button001_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	LPNOZZLECHECKCOMPTYPE002WORK lpWk = (LPNOZZLECHECKCOMPTYPE002WORK)gLPNozzleCheckWork;
	GtkWidget* window = GetTopWidget(GTK_WIDGET(button));	

	if ( CheckWorkType002() != 0 ) goto Err;

	if ( lpWk->uiType == UI_NOZZLECHECK_START_TYPE001 ){
		lpWk->status = US_PRINT_CHECK_PATTERN;		
	}
	else if ( lpWk->uiType == UI_NOZZLECHECK_START_TYPE002 ){
		gBinValueNozzleCheck = (short)GetActiveButtonIndex( window, nozzlecheck_type002_radiobutton_name, NOZZLECHECK_TYPE002_BINVALUE_CASETTE );
		lpWk->status = US_PRINT_CHECK_PATTERN;
		/*if ( gIsFirst ){*/ /* Ver.3.70 */
		/*	gIsFirst = 0;*/
		/*}*/
	}
Err:
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	return;
}

/* Cancel button */
void
on_nozzle_check_type002_button002_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	LPNOZZLECHECKCOMPTYPE002WORK lpWk = (LPNOZZLECHECKCOMPTYPE002WORK)gLPNozzleCheckWork;

	if ( CheckWorkType002() != 0 ) goto Err;

	lpWk->status = US_CANCEL;
Err:
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	return;
}

/* export functions */
short ExecNozzleCheckType001_000( char *dialogName ){ return ExecNozzleCheckType001( (void*)&nozzleCheckType001Res[0], dialogName );}
short ExecNozzleCheckType002_000( char *dialogName ){ return ExecNozzleCheckType002( (void*)&nozzleCheckType002Res[0], dialogName );}
short ExecNozzleCheckType002_001( char *dialogName ){ return ExecNozzleCheckType002( (void*)&nozzleCheckType002Res[1], dialogName );}

