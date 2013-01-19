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
#include "util_nozzlecheck.h" /* Ver.3.80 */



/* UI type */
enum {
	UI_CLEANING_TYPE001 = 1,
	UI_DEEPCLEANING_TYPE001,
	UI_DEEPCLEANING_TYPE002,
	UI_ROLLERCLEANING_TYPE001,
	UI_ROLLERCLEANING_TYPE002,
	UI_ROLLERCLEANING_TYPE003,		/* Ver.3.80 */
	UI_PLATECLEANING_TYPE001,
};

/* Each Type Function Resource */
enum {
	RES_CLEANING_COMPTYPE001=1,
};

/* CLEANING COMPTYPE001 */
typedef struct {
	long	resType;
	int		uiType;
	GtkWidget *(*ptrCreateDialog)( void );
} CLEANINGCOMPTYPE001RES, *LPCLEANINGCOMPTYPE001RES;

CLEANINGCOMPTYPE001RES cleaningType001Res[] = {
	{ RES_CLEANING_COMPTYPE001, UI_CLEANING_TYPE001, create_cleaning_type001_dialog }, 
	{ RES_CLEANING_COMPTYPE001, UI_DEEPCLEANING_TYPE001, create_cleaning_type001_dialog }, 
	{ RES_CLEANING_COMPTYPE001, UI_ROLLERCLEANING_TYPE001, create_cleaning_type001_dialog }, 
	{ RES_CLEANING_COMPTYPE001, UI_ROLLERCLEANING_TYPE002, create_cleaning_type001_dialog }, 
	{ RES_CLEANING_COMPTYPE001, UI_PLATECLEANING_TYPE001, create_cleaning_type001_dialog }, 
	{ RES_CLEANING_COMPTYPE001, UI_DEEPCLEANING_TYPE002, create_cleaning_type001_dialog }, 
	{ RES_CLEANING_COMPTYPE001, UI_ROLLERCLEANING_TYPE003, create_cleaning_type001_dialog }, 
};


/* Each Type Function Work */
enum {
	WORK_CLEANING_COMPTYPE001=1,
};

/* CLEANING COMPTYPE001 */
typedef struct {
	long	workType;
	int	uiType;
	GtkWidget *dialog;
//	COMMANDCOMP	*lpCmdComp;
	short status;
} CLEANINGCOMPTYPE001WORK, *LPCLEANINGCOMPTYPE001WORK;


/* const table */
static const gchar *buttonname_cleaning_type001[] =
{
	"cleaning_type001_radiobutton001",
	"cleaning_type001_radiobutton002",
	"cleaning_type001_radiobutton003",
	NULL
};
static const int status_table_cleaning_type001[] =
{
	US_EXECUTE_ALL_COLOR,
	US_EXECUTE_BLACK,
	US_EXECUTE_COLOR,
};

static const gchar *buttonname_cleaning_type002[] =
{
	"cleaning_type001_radiobutton101",
	"cleaning_type001_radiobutton102",
	NULL
};
static const int status_table_cleaning_type002[] =
{
	US_OK_REARTRAY,
	US_OK_CASETTE,
};

/* Ver.3.80 */
static const gchar *buttonname_cleaning_type003[] =
{
	"cleaning_type001_radiobutton101",
	"cleaning_type001_radiobutton102",
	NULL
};
static const int status_table_cleaning_type003[] =
{
	US_OK_FRONT2_UPPER,
	US_OK_FRONT2_LOWER,
};


/* global */
static void *gLPCleaningWork = NULL;
static int gCleaningIndex;
//static int gDeepCleaningIndex;
static int gRollerCleaningIndex;

/*** COMMON **************************************************************************************************/
static short OutputUtilityCommand_CMD_CLEANING( short type, short index, COMMANDDATA *cmdData, short cmdNum )
{
	char buf[CMD_BUF_MAX_SIZE];
	char *p;
	long size;
	short result = -1;

	if ( cmdData == NULL ) goto Err;
	if ( index > (cmdNum -1 ) ) goto Err;

	p = buf;
	size = 0;
	if ( type == CMD_CLEANING_TYPE001 ){
		size = cmdData[gCleaningIndex].len;
		memcpy( p, cmdData[gCleaningIndex].cmd, size ); p += size;
		*p = 0x00; p++;
		size = (long)(p -buf);

		OutputCmdType001( buf, size );
	}
	else if ( type == CMD_CLEANING_TYPE002 ){
		size = cmdData[0].len;
		memcpy( p, cmdData[0].cmd, size ); p += size;
		size = (long)(p -buf);
		
		OutputCmdType004( buf, size, 3 );
	}

	result = 0;
Err:
	return result;
}

short OutputUtilityCommand_CMD_CLEANING_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return  OutputUtilityCommand_CMD_CLEANING( CMD_CLEANING_TYPE001, index, cmdData, cmdNum );
}
short OutputUtilityCommand_CMD_CLEANING_TYPE002( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return  OutputUtilityCommand_CMD_CLEANING( CMD_CLEANING_TYPE002, index, cmdData, cmdNum );
}

/*** COMPTYPE001 *********************************************************************************************/
static LPCLEANINGCOMPTYPE001WORK CreateWorkCleaningType001( LPCLEANINGCOMPTYPE001RES lpRes )
{
	LPCLEANINGCOMPTYPE001WORK lpWork = NULL;

	if ( lpRes == NULL ) goto Err;
	if ( (lpWork = g_malloc0(sizeof(CLEANINGCOMPTYPE001WORK))) == NULL ) goto Err;

	lpWork->workType = WORK_CLEANING_COMPTYPE001;
Err:
	return lpWork;
}

static void InitParamCleaningType001( LPCLEANINGCOMPTYPE001RES lpRes, void *lpGWork )
{
	LPCLEANINGCOMPTYPE001WORK lpWork = (LPCLEANINGCOMPTYPE001WORK)lpGWork;

	lpWork->status = US_DEFAULT;
	lpWork->uiType = lpRes->uiType;
	lpWork->dialog = lpRes->ptrCreateDialog();

	if ( (lpWork->uiType == UI_CLEANING_TYPE001) || (lpWork->uiType == UI_DEEPCLEANING_TYPE001) ){
		gCleaningIndex = 0;
	}
	else if ( lpWork->uiType == UI_DEEPCLEANING_TYPE002 ){ /* Ver.3.50 */
		gCleaningIndex = 1;
	}
	else if ( lpWork->uiType == UI_ROLLERCLEANING_TYPE002 ){
		gRollerCleaningIndex = 0;
	}
	else if ( lpWork->uiType == UI_ROLLERCLEANING_TYPE003 ){ /* Ver.3.80 */
		gRollerCleaningIndex = 1;
	}
}

static void SetLabelCleaningType001( LPCLEANINGCOMPTYPE001RES lpRes, void *lpGWork, char *dialogName )
{
	LPCLEANINGCOMPTYPE001WORK lpWork = (LPCLEANINGCOMPTYPE001WORK)lpGWork;
	SetLabelUtilDialog( lpWork->dialog, dialogName );
}

static void SetDefaultCleaningType001( LPCLEANINGCOMPTYPE001RES lpRes, void *lpGWork )
{
	LPCLEANINGCOMPTYPE001WORK lpWork = (LPCLEANINGCOMPTYPE001WORK)lpGWork;
	GtkWidget *button;

	if ( (lpWork->uiType == UI_CLEANING_TYPE001) || (lpWork->uiType == UI_DEEPCLEANING_TYPE001) ){
		/* radio button */
		button = LookupWidget( lpWork->dialog,  buttonname_cleaning_type001[gCleaningIndex] );
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
	}
	else if ( lpWork->uiType == UI_DEEPCLEANING_TYPE002 ){
		/* radio button */
		button = LookupWidget( lpWork->dialog,  buttonname_cleaning_type001[gCleaningIndex] );
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
	}
	else if ( lpWork->uiType == UI_ROLLERCLEANING_TYPE002 ) {
		button = LookupWidget( lpWork->dialog,  buttonname_cleaning_type002[gRollerCleaningIndex] );
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
	}
	else if ( lpWork->uiType == UI_ROLLERCLEANING_TYPE003 ) { /* Ver.3.80 */
		button = LookupWidget( lpWork->dialog,  buttonname_cleaning_type003[gRollerCleaningIndex] );
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
	}
}

static void ShowDialogCleaningType001( LPCLEANINGCOMPTYPE001RES lpRes, void *lpGWork )
{
	LPCLEANINGCOMPTYPE001WORK lpWork = (LPCLEANINGCOMPTYPE001WORK)lpGWork;

	gtk_widget_show( lpWork->dialog );
	gtk_window_set_transient_for( GTK_WINDOW(lpWork->dialog), GTK_WINDOW(g_main_window) );
	gtk_main();
}

static void DisposeWorkCleaningType001( LPCLEANINGCOMPTYPE001WORK lpWork )
{
	if ( lpWork == NULL ) goto Err;

	g_free( lpWork );
Err:
	return;
}

static short CheckWorkType001( void )
{
	LPCLEANINGCOMPTYPE001WORK lpWork = (LPCLEANINGCOMPTYPE001WORK)gLPCleaningWork;
	short result = -1;

	if ( lpWork == NULL ) goto Err;
	if ( lpWork->workType !=  WORK_CLEANING_COMPTYPE001 ) goto Err;

	result = 0;
Err:
	return result;
}

static short GetStatusCleaningType001( void *lpGWork )
{
	LPCLEANINGCOMPTYPE001WORK lpWork = (LPCLEANINGCOMPTYPE001WORK)lpGWork;
	return lpWork->status;
}


/*-------------------------------------------------------------------------------
	short ExecCleaningType001( void *lpWork, char *dialogName )
-------------------------------------------------------------------------------*/
short ExecCleaningType001( void *lpWork, char *dialogName )
{
	LPCLEANINGCOMPTYPE001RES lpRes = (LPCLEANINGCOMPTYPE001RES)lpWork;
	short	result = -1;

	/* confirm data type */
	if ( lpRes->resType != RES_CLEANING_COMPTYPE001 ) goto Err;

	/* allocate  work */
	if ( (gLPCleaningWork = CreateWorkCleaningType001( lpRes )) == NULL ) goto Err;

	/* ---- Show Dialog ---- */
	/* init parameter */
	InitParamCleaningType001( lpRes, gLPCleaningWork );
	
	/* show labels */
	SetLabelCleaningType001( lpRes, gLPCleaningWork, dialogName );

	/* set default */
	SetDefaultCleaningType001( lpRes, gLPCleaningWork );

	/* show dialog */
	ShowDialogCleaningType001( lpRes, gLPCleaningWork );

	result = GetStatusCleaningType001( gLPCleaningWork );

	DisposeWorkCleaningType001( gLPCleaningWork );

Err:
	gLPCleaningWork = NULL;
	return result;
}

/*-------------------------------------------------------------------------------
	CleaningType001 callback functions
-------------------------------------------------------------------------------*/
gboolean
on_cleaning_type001_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(widget)));
  	return FALSE;
}


void
on_cleaning_type001_dialog_destroy     (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}

/* Execute button */
void
on_cleaning_type001_button001_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
	LPCLEANINGCOMPTYPE001WORK lpWk = (LPCLEANINGCOMPTYPE001WORK)gLPCleaningWork;
	GtkWidget* window = GetTopWidget(GTK_WIDGET(button));	
	//COMMANDCOMP *lpComp = lpWk->lpCmdComp;
	int index;

	if ( CheckWorkType001() != 0 ) goto Err;

	/* set status */
	if ( (lpWk->uiType == UI_DEEPCLEANING_TYPE001) || (lpWk->uiType == UI_DEEPCLEANING_TYPE002) ){
		index = (short)GetActiveButtonIndex( window, buttonname_cleaning_type001, 0 );
		lpWk->status = status_table_cleaning_type001[index];
	}
	else if ( lpWk->uiType == UI_ROLLERCLEANING_TYPE002 ){
		index = (short)GetActiveButtonIndex( window, buttonname_cleaning_type002, 0 );
		lpWk->status = status_table_cleaning_type002[index];
	}
	else if ( lpWk->uiType == UI_ROLLERCLEANING_TYPE003 ){ /* Ver.3.80 */
		index = (short)GetActiveButtonIndex( window, buttonname_cleaning_type003, 0 );
		lpWk->status = status_table_cleaning_type003[index];
	}
	else if ( (lpWk->uiType == UI_CLEANING_TYPE001) || (lpWk->uiType == UI_PLATECLEANING_TYPE001) ){
		lpWk->status = US_EXECUTE;
		gCleaningIndex = (short)GetActiveButtonIndex( window, buttonname_cleaning_type001, 0 );
	}
	else if ( lpWk->uiType == UI_ROLLERCLEANING_TYPE001 ){
		lpWk->status = US_OK;
	}

Err:
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
}


void
on_cleaning_type001_button002_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
	LPCLEANINGCOMPTYPE001WORK lpWk = (LPCLEANINGCOMPTYPE001WORK)gLPCleaningWork;
	lpWk->status = US_CANCEL;
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
}

/* export functions */
short ExecCleaningType000_000( char *dialogName ){ return US_F_CLEANING; }
short ExecCleaningType000_001( char *dialogName ){ return US_F_DEEP_CLEANING; }
short ExecCleaningType000_002( char *dialogName ){ return US_F_ROLLER_CLEANING; }
short ExecCleaningType000_003( char *dialogName ){ return US_F_PLATE_CLEANING; }
short ExecCleaningType000_004( char *dialogName ){ SetPaperSourceInfoType000_004(); return US_F_CLEANING; } /* Ver.3.80 */
short ExecCleaningType000_005( char *dialogName ){ SetPaperSourceInfoType000_004(); return US_F_DEEP_CLEANING; } /* Ver.3.80 */
short ExecCleaningType001_000( char *dialogName ){ return ( ExecCleaningType001( (void *)&cleaningType001Res[0], dialogName) ); }
short ExecCleaningType001_001( char *dialogName ){ return ( ExecCleaningType001( (void *)&cleaningType001Res[1], dialogName) ); }
short ExecCleaningType001_002( char *dialogName ){ return ( ExecCleaningType001( (void *)&cleaningType001Res[2], dialogName) ); }
short ExecCleaningType001_003( char *dialogName ){ return ( ExecCleaningType001( (void *)&cleaningType001Res[3], dialogName) ); }
short ExecCleaningType001_004( char *dialogName ){ return ( ExecCleaningType001( (void *)&cleaningType001Res[4], dialogName) ); }
short ExecCleaningType001_005( char *dialogName ){ return ( ExecCleaningType001( (void *)&cleaningType001Res[5], dialogName) ); } /* Ver.3.50 */
short ExecCleaningType001_006( char *dialogName ){ return ( ExecCleaningType001( (void *)&cleaningType001Res[6], dialogName) ); } /* Ver.3.80 */


