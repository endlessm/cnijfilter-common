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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>
#ifdef	USE_LIB_GLADE
#	include <glade/glade.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>			
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

#include "callbacks.h"
#ifndef USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"
#include "msgicon.h"


#include "util_cmd.h"
#include "util_com.h"
#include "util_parse_flow.h"
#include "util_parse_dialogstr.h"
#include "util_parse_function.h"
#include "util_regi.h"
#include "util_setconfig.h"
#include "util_cleaning.h"
#include "util_nozzlecheck.h"
#include "util_funclist.h"
#include "util_cmdlist.h"

static const char bjl_cmds[]
= {0x1b, '[', 'K', 0x02, 0x00, 0x00, 0x1f };

/* global */
static int gUtilCommonStatus = 0;
static void *gLPCommonWork = NULL;


/* function prototypes */
static short OutputUtilityCommand_CMD_COMMON( short type, short index, COMMANDDATA *cmdData, short cmdNum );



/* ExecCommonDialogType001 */
enum {
	RES_COMMONDIALOG_COMPTYPE001=1,
};

typedef struct {
	long resType;
	unsigned int flag;
} COMMONDIALOGTYPE001RES, *LPCOMMONDIALOGTYPE001RES;

COMMONDIALOGTYPE001RES commonDialogType001[] =
{
	{ RES_COMMONDIALOG_COMPTYPE001, MB_ICON_EXCLAMATION | MB_OK },
	{ RES_COMMONDIALOG_COMPTYPE001, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL },
	{ RES_COMMONDIALOG_COMPTYPE001, MB_ICON_QUESTION | MB_YES | MB_NO },
	{ RES_COMMONDIALOG_COMPTYPE001, MB_ICON_INFORMATION | MB_OK },
};


enum {
	WORK_COMMONDIALOG_COMPTYPE001=1,
};

typedef struct {
	unsigned int flag;
//	short status;
} COMMONDIALOGTYPE001WORK, *LPCOMMONDIALOGTYPE001WORK;


/* function prototypes */
static short ExecCommonDialogType001( void *lpWork, char *dialogName );

/* export functions */
short ExecCommonDialogType001_000( char *dialogName ){ return ExecCommonDialogType001( (void *)&commonDialogType001[0], dialogName ); }
short ExecCommonDialogType001_001( char *dialogName ){ return ExecCommonDialogType001( (void *)&commonDialogType001[1], dialogName ); }
short ExecCommonDialogType001_002( char *dialogName ){ return ExecCommonDialogType001( (void *)&commonDialogType001[2], dialogName ); }
short ExecCommonDialogType001_003( char *dialogName ){ return ExecCommonDialogType001( (void *)&commonDialogType001[3], dialogName ); }


/* 
	short ExecCommonDialogType001( void *lpWork, char *dialogName )
*/
static short ExecCommonDialogType001( void *lpWork, char *dialogName )
{
	LPCOMMONDIALOGTYPE001RES lpRes = (LPCOMMONDIALOGTYPE001RES)lpWork;
	LPCOMMONDIALOGTYPE001WORK lpWk = NULL;
	short status;
	
	short result = -1;

	/* confirm data type */
	if ( lpRes->resType != RES_COMMONDIALOG_COMPTYPE001 ) goto Err;

	/* allocate  work */
	if ( (gLPCommonWork = g_malloc0(sizeof(COMMONDIALOGTYPE001WORK))) == NULL ) goto Err;

	/* init parameter */
	lpWk = (LPCOMMONDIALOGTYPE001WORK)gLPCommonWork;
	lpWk->flag = lpRes->flag;

	/* show dialog */
	SetLabelCommonUtilDialog( dialogName, lpWk->flag, &status );

	result = status;
Err:
	g_free( lpWk );
	gLPCommonWork = NULL;
	return result;
}

int KeyToIndex(char **Keytbl, int n, char *type)
{
	int			i;
	
	for (i=0; i < n; i++) {
		if (!strcmp(LookupText(g_keytext_list, Keytbl[i]), type))
			return i;		
	}
	return 0;		
}


static gboolean IsStrEmpty( char *str )
{
	if ( str == NULL ) return TRUE;

	if ( *str == '\0' ){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void SetComboBoxItems(GtkWidget *combo, char **Keytbl, int n, int index)
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


	/* Add items in "Keytbl" */
	for (i=0; i < n; i++)
	{
		gtk_combo_box_append_text( GTK_COMBO_BOX( combo ), LookupText(g_keytext_list, Keytbl[i]) );
	}

	if( index >= n ) index = 0;
	gtk_combo_box_set_active( GTK_COMBO_BOX( combo ), index );

}




static gboolean message_box_delete_event
(GtkWidget *widget, GdkEvent *event, gpointer data) 
{
	gtk_window_set_modal(data,FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));

	return TRUE;
}

static gboolean message_box_delete_event_with_status_common
(GtkWidget *widget, GdkEvent *event, gpointer data) 
{
	LPCOMMONDIALOGTYPE001WORK lpWk = (LPCOMMONDIALOGTYPE001WORK)gLPCommonWork;

	if ( lpWk == NULL ) goto EXIT;

	if ( !(lpWk->flag & MB_CANCEL) ){ /* not exist cancel button */
		gUtilCommonStatus = US_OK;
	}
EXIT:
	gtk_window_set_modal(data,FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));

	return TRUE;
}

static gboolean message_box_delete_event_with_status_setconfig
(GtkWidget *widget, GdkEvent *event, gpointer data) 
{
	unsigned int flag;

	flag = GetFlagSetConfigType002();

	if ( !(flag & MB_CANCEL) ){ /* not exist cancel button */
		gUtilCommonStatus = US_OK;
	}
	gtk_window_set_modal(data,FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));

	return TRUE;
}

static gboolean message_box_delete_event_no_destroy
(GtkWidget *widget, GdkEvent *event, gpointer data) 
{
	return TRUE;
}

static void message_box_destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();						
	gtk_window_set_modal(data, FALSE);
}


static void message_box_ok(GtkWidget *widget, gpointer data)
{
	gUtilCommonStatus = US_OK;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static void message_box_cancel(GtkWidget *widget, gpointer data)
{
	gUtilCommonStatus = US_CANCEL;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static void message_box_yes(GtkWidget *widget, gpointer data)
{
	gUtilCommonStatus = US_YES;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static void message_box_no(GtkWidget *widget, gpointer data)
{
	gUtilCommonStatus = US_NO;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static void message_box_abort(GtkWidget *widget, gpointer data)
{
  	gUtilCommonStatus = US_ABORT;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static void message_box_ignore(GtkWidget *widget, gpointer data)
{
  	gUtilCommonStatus = US_IGNORE;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static int UtilMessageBoxSetDefault(
	char *message,				
	char *title,                
	unsigned int flag,
	unsigned int default_flag, 
	short isWithStatus )          
{
	GtkWidget	*dialog;				
	GtkWidget	*dialog_action_area1;   
	GtkWidget	*dialog_vbox1;          
	GtkWidget	*hbox1;                 
	GtkWidget	*pixmap;                
	GtkWidget	*label;                 
	GtkWidget	*hbuttonbox1;           
	GtkWidget	*button;                
	GdkPixmap	*icon = NULL;
	GdkPixmap	*iconMask = NULL;
	GtkStyle	*style;
	int		i;
	short		icon_exist = 1;	//Ver.3.00

	gUtilCommonStatus = US_MAINTENANCE_EXIT;
	
	dialog = gtk_dialog_new();				
	gtk_widget_realize(dialog);				
	gtk_window_set_title(GTK_WINDOW(dialog), title);	
	gtk_window_set_policy(GTK_WINDOW(dialog), FALSE, FALSE, TRUE);	
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);	
	
	gtk_signal_connect(GTK_OBJECT(dialog), "destroy",	
			      GTK_SIGNAL_FUNC(message_box_destroy), dialog);
	// If dialog has YSE and  NO button, disable close button.
	if ( (flag & MB_YES) && (flag & MB_NO) ){
		gtk_signal_connect (GTK_OBJECT (dialog), "delete_event",
				GTK_SIGNAL_FUNC (message_box_delete_event_no_destroy), dialog);
	}
	else {
		if ( isWithStatus == 1 ){
			gtk_signal_connect (GTK_OBJECT (dialog), "delete_event",
				GTK_SIGNAL_FUNC (message_box_delete_event_with_status_common), dialog);
		}
		else if ( isWithStatus == 2 ){
			gtk_signal_connect (GTK_OBJECT (dialog), "delete_event",
				GTK_SIGNAL_FUNC (message_box_delete_event_with_status_setconfig), dialog);
		}
		else {
			gtk_signal_connect (GTK_OBJECT (dialog), "delete_event",
				GTK_SIGNAL_FUNC (message_box_delete_event), dialog);
		}
	}
						
		
	dialog_action_area1 = GTK_DIALOG(dialog)->action_area;	
	dialog_vbox1 = GTK_DIALOG(dialog)->vbox;	

	
	hbox1 = gtk_hbox_new(FALSE, 0);	
	gtk_widget_show(hbox1);			
	gtk_box_pack_start(GTK_BOX(dialog_vbox1), hbox1, TRUE, TRUE, 5);	
  
	
	style = gtk_widget_get_style(dialog);
	switch (flag & 0x0000000f) {	
		case MB_ICON_INFORMATION:	
 			icon = gdk_pixmap_create_from_xpm_d(dialog->window,
  										  &iconMask,
  										  &style->bg[GTK_STATE_NORMAL],
  										  info_xpm);
  			break;
		
		case MB_ICON_EXCLAMATION:	
 			icon = gdk_pixmap_create_from_xpm_d(dialog->window,
  										  &iconMask,
  										  &style->bg[GTK_STATE_NORMAL],
  										  exclam_xpm);
			break;

		case MB_ICON_SYSERR:	
 			icon = gdk_pixmap_create_from_xpm_d(dialog->window,
  										  &iconMask,
  										  &style->bg[GTK_STATE_NORMAL],
  										  syserr_xpm);
			break;

		case MB_ICON_QUESTION:	/* Ver.2.90 */
 			icon = gdk_pixmap_create_from_xpm_d(dialog->window,
  										  &iconMask,
  										  &style->bg[GTK_STATE_NORMAL],
  										  question_xpm);
			break;

		default:	/* Ver.3.00 */
			icon_exist = 0;
			break;
			
	}

	if( icon_exist ){
		pixmap = gtk_pixmap_new(icon, iconMask);			
		gtk_box_pack_start(GTK_BOX(hbox1), pixmap, FALSE, FALSE, 10);	
		if( icon_exist ) gtk_widget_show(pixmap);			
	}
	//else gtk_widget_hide(pixmap);

	label = gtk_label_new(message);	
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);		
	gtk_widget_show(label);			
	gtk_box_pack_start(GTK_BOX(hbox1), label, TRUE, TRUE, 10);	


	hbuttonbox1 = gtk_hbutton_box_new();		
	gtk_box_pack_start(
		GTK_BOX(dialog_action_area1), hbuttonbox1, TRUE, FALSE, 0);	
	gtk_widget_show(hbuttonbox1);		
	
	/* Ver.2.80 */
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_SPREAD);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (hbuttonbox1), GTK_BUTTONBOX_SPREAD);
	gtk_box_set_spacing (GTK_BOX (hbuttonbox1), 7);
	
	
	i = 0;			
	
	if (flag & MB_OK) {		
		button = gtk_button_new_with_label(
					LookupText(g_keytext_list, "message_button_ok"));	
		gtk_widget_show(button);					
		gtk_container_add(GTK_CONTAINER(hbuttonbox1), button);	
		GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
		
  		gtk_signal_connect(GTK_OBJECT(button), "clicked",	
					     GTK_SIGNAL_FUNC(message_box_ok),
					     dialog);
		if( default_flag & MB_OK ){
			gtk_widget_grab_focus(button);
			gtk_widget_grab_default(button);
		}
		i++;
	}
	
	if (flag & MB_CANCEL) {		
		button = gtk_button_new_with_label(
					LookupText(g_keytext_list, "message_button_cancel"));	
		gtk_widget_show(button);					
		gtk_container_add(GTK_CONTAINER(hbuttonbox1), button);	
		GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
  		gtk_signal_connect(GTK_OBJECT(button), "clicked",	
					     GTK_SIGNAL_FUNC(message_box_cancel),
					     dialog);
		if( default_flag & MB_CANCEL ){
			gtk_widget_grab_focus(button);
			gtk_widget_grab_default(button);
		}
		
		i++;
	}
	
	if (flag & MB_YES) {		
		button = gtk_button_new_with_label(
					LookupText(g_keytext_list, "message_button_yes"));	
		gtk_widget_show(button);					
		gtk_container_add(GTK_CONTAINER(hbuttonbox1), button);
		GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
  		gtk_signal_connect(GTK_OBJECT(button), "clicked",	
					     GTK_SIGNAL_FUNC(message_box_yes),
					     dialog);
		if( default_flag & MB_YES ){
			gtk_widget_grab_focus(button);
			gtk_widget_grab_default(button);
		}
		i++;
	}
	
	if (flag & MB_NO) {		
		button = gtk_button_new_with_label(
					LookupText(g_keytext_list, "message_button_no"));	
		gtk_widget_show(button);					
		gtk_container_add(GTK_CONTAINER(hbuttonbox1), button);
		GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
  		gtk_signal_connect(GTK_OBJECT(button), "clicked",	
					     GTK_SIGNAL_FUNC(message_box_no),
					     dialog);
		if( default_flag & MB_NO ){
			gtk_widget_grab_focus(button);
			gtk_widget_grab_default(button);
		}

		i++;
	}

	if (flag & MB_ABORT) {		
		button = gtk_button_new_with_label(
					LookupText(g_keytext_list, "message_button_abort"));	
		gtk_widget_show(button);					
		gtk_container_add(GTK_CONTAINER(hbuttonbox1), button);	
		GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
  		gtk_signal_connect(GTK_OBJECT(button), "clicked",	
					     GTK_SIGNAL_FUNC(message_box_abort),
					     dialog);
		if( default_flag & MB_ABORT ){
			gtk_widget_grab_focus(button);
			gtk_widget_grab_default(button);
		}
		i++;
	}

	if (flag & MB_IGNORE) {		
		button = gtk_button_new_with_label(
					LookupText(g_keytext_list, "message_button_ignore"));	
		gtk_widget_show(button);					
		gtk_container_add(GTK_CONTAINER(hbuttonbox1), button);	
		GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
  		gtk_signal_connect(GTK_OBJECT(button), "clicked",	
					     GTK_SIGNAL_FUNC(message_box_ignore),
					     dialog);
		if( default_flag & MB_IGNORE ){
			gtk_widget_grab_focus(button);
			gtk_widget_grab_default(button);
		}
		i++;
	}

	
	gtk_window_set_transient_for(GTK_WINDOW(dialog),
		 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
	gtk_widget_show(dialog);				
	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);	

	
	gtk_main();

	if( icon_exist ){
		gdk_pixmap_unref(icon);
	}		
	return gUtilCommonStatus;				
}


int UtilMessageBox(
	char *message,				
	char *title,                
	unsigned int flag)          
{

	return(UtilMessageBoxSetDefault(message, title, flag, MB_OK|MB_YES, 0) );

}

int UtilMessageBoxWithStatusCommon(
	char *message,				
	char *title,                
	unsigned int flag)          
{

	return(UtilMessageBoxSetDefault(message, title, flag, MB_OK|MB_YES, 1) );

}

int UtilMessageBoxWithStatusSetConfig(
	char *message,				
	char *title,                
	unsigned int flag)          
{

	return(UtilMessageBoxSetDefault(message, title, flag, MB_OK|MB_YES, 2) );

}

int UtilMessageBoxDefaultNo(
	char *message,				
	char *title,                
	unsigned int flag)          
{

	return(UtilMessageBoxSetDefault(message, title, flag, MB_OK|MB_YES, 0) );

}


static int SetBJLStart( char *buf )
{
	char *p = buf;
	int size;

	memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
	memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
//	memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;

	size = (int)( p - buf );
	return size;
}

static int SetBJLEnd( char *buf )
{
	char *p = buf;
	int size;

	memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;

	size = (int)( p - buf );
	return size;
}

static int SetControlMode( char *buf )
{
	char *p = buf;
	int size;

	memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;

	size = (int)( p - buf );
	return size;
}

static int	SetCurrentTime(char *buf)
{
	time_t	t_time;
	struct	tm		*ltime;
	int		n;
	char	*p = buf;
	
	//memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;								
	//memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;					
	//memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;
//	n = SetBJLStart( p ); p += n;
	
	memcpy(p, BJLSETTIME, BJLSETTIMELEN); p+=BJLSETTIMELEN;				
	time (&t_time);									
	ltime = localtime(&t_time);						
	n = sprintf(p, "%4d", ltime->tm_year + 1900); p += n;	
	n = sprintf(p, "%02d", ltime->tm_mon + 1); p += n;
	n = sprintf(p, "%02d", ltime->tm_mday);	p += n;
	n = sprintf(p, "%02d", ltime->tm_hour);	p += n;
	n = sprintf(p, "%02d", ltime->tm_min); p += n;
	n = sprintf(p, "%02d\x0a", ltime->tm_sec); p += n;

	//memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;		
//	n = SetBJLEnd( p ); p += n;
	
	return (int)(p - buf);
}

/*
	Output command
*/
void OutputCmdType001( char *cmdPtr, long cmdLen )
{
	int n;
	long len;
	char buf[CMD_BUF_MAX_SIZE];
	char *p = buf;

	/* Output SetTime */
	n = SetBJLStart(p); p += n;
	n = SetControlMode(p); p += n;
	n = SetCurrentTime(p); p+=n; 
	n = SetBJLEnd(p); p += n;

	/* Output Command */
	n = SetBJLStart(p); p += n;
	memcpy( p, cmdPtr, cmdLen ); p += cmdLen;
	n = SetBJLEnd(p); p += n;
	*p = 0x00; p++;

	len = (long)(p - buf);
	PutPrintData( buf, len );
}

/*
	Output command with controlmode
*/
void OutputCmdType002( char *cmdPtr, long cmdLen, short isSetTime )
{
	int n;
	long len;
	char buf[CMD_BUF_MAX_SIZE];
	char *p = buf;

	n = SetBJLStart(p); p += n;
	n = SetControlMode(p); p += n;

	if ( isSetTime ) {
		n = SetCurrentTime(p); p+=n; 
	}

	memcpy( p, cmdPtr, cmdLen ); p += cmdLen;
	n = SetBJLEnd(p); p += n;
	*p = 0x00; p++;

	len = (long)(p - buf);
	PutPrintData( buf, len );
}

/*
	Output devicedata
*/
void OutputCmdType003( char *cmdPtr, long cmdLen, char *devMode )
{
	int n;
	long len;
	char buf[CMD_BUF_MAX_SIZE];
	char *p = buf;

	/* Output devicedata */
	n = SetBJLStart(p); p += n;
	memcpy( p, cmdPtr, cmdLen ); p += cmdLen;
	n = SetBJLEnd(p); p += n;
	*p = 0x00; p++;

	len = (long)(p - buf);
	PutDeviceData( buf, len, devMode );
}


short SetLabelUtilDialog( GtkWidget *dialog, char *dialogName )
{
	LPDIALOGSTRCOMP lpDialogStrComp = NULL;
	char resName[NAME_BUF_MAX_SIZE];
	short result = -1;

	snprintf( resName, NAME_BUF_MAX_SIZE, "%s/%s", MAINTENANCE_RESPATH, MAINTENANCE_RESFILE );
	if ( ParseDialogStringListTag( resName, dialogName, &lpDialogStrComp ) != 0 ){
		goto Err;
	}

	while( lpDialogStrComp != NULL ){

		if ( lpDialogStrComp->type == MSGTYPE_CAPTION ){
			gtk_window_set_title( GTK_WINDOW(dialog), LookupText(g_keytext_list, lpDialogStrComp->strid) );
		}
		else if ( (lpDialogStrComp->type == MSGTYPE_BUTTON) || (lpDialogStrComp->type == MSGTYPE_RADIOBUTTON) ||
			(lpDialogStrComp->type == MSGTYPE_CHECKBUTTON) ){
			gtk_button_set_label( GTK_BUTTON(LookupWidget(dialog, lpDialogStrComp->label )),
				LookupText(g_keytext_list, lpDialogStrComp->strid));
			gtk_widget_show( LookupWidget(dialog, lpDialogStrComp->label ) );
		}
		else if ( lpDialogStrComp->type == MSGTYPE_LABEL ){
			gtk_label_set_text( GTK_LABEL(LookupWidget(dialog, lpDialogStrComp->label )),
				LookupText(g_keytext_list, lpDialogStrComp->strid));
			gtk_widget_show( LookupWidget(dialog, lpDialogStrComp->label ) );
		}
		else if ( lpDialogStrComp->type == MSGTYPE_SEPARATOR ) {
			gtk_widget_show( LookupWidget(dialog, lpDialogStrComp->label ) );
		}

		lpDialogStrComp = lpDialogStrComp->next;
	}


	FreeDialogStrCompList( lpDialogStrComp );
	result = 0;
Err:
	return result;
}

short SetLabelCommonUtilDialog( char *dialogName, unsigned int flag, short *retVal ) 
{
	LPDIALOGSTRCOMP lpDialogStrComp = NULL;
	char resName[NAME_BUF_MAX_SIZE];
	short result = -1;

	*retVal = 0;

	snprintf( resName, NAME_BUF_MAX_SIZE, "%s/%s", MAINTENANCE_RESPATH, MAINTENANCE_RESFILE );
	if ( ParseDialogStringListTag( resName, dialogName, &lpDialogStrComp ) != 0 ) goto Err;

	while ( lpDialogStrComp != NULL ){
		if ( lpDialogStrComp->type == MSGTYPE_LABEL ){
			*retVal = UtilMessageBoxWithStatusCommon(LookupText(g_keytext_list, lpDialogStrComp->strid), g_window_title, flag );
		}
		lpDialogStrComp = lpDialogStrComp->next;
	}
		
	FreeDialogStrCompList( lpDialogStrComp );
	result = 0;
Err:
	return result;
}

short SetLabelCommonUtilDialogForSetConfig( char *dialogName, unsigned int flag, short *retVal ) 
{
	LPDIALOGSTRCOMP lpDialogStrComp = NULL;
	char resName[NAME_BUF_MAX_SIZE];
	short result = -1;

	*retVal = 0;

	snprintf( resName, NAME_BUF_MAX_SIZE, "%s/%s", MAINTENANCE_RESPATH, MAINTENANCE_RESFILE );
	if ( ParseDialogStringListTag( resName, dialogName, &lpDialogStrComp ) != 0 ) goto Err;

	while ( lpDialogStrComp != NULL ){
		if ( lpDialogStrComp->type == MSGTYPE_LABEL ){
			*retVal = UtilMessageBoxWithStatusSetConfig(LookupText(g_keytext_list, lpDialogStrComp->strid), g_window_title, flag );
		}
		lpDialogStrComp = lpDialogStrComp->next;
	}
		
	FreeDialogStrCompList( lpDialogStrComp );
	result = 0;
Err:
	return result;
}

/* output command */
short OutputUtilityCommand_CMD_COMMON_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_COMMON( CMD_COMMON_TYPE001, index, cmdData, cmdNum );
}

short OutputUtilityCommand_CMD_COMMON_TYPE002( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_COMMON( CMD_COMMON_TYPE002, index, cmdData, cmdNum );
}

short OutputUtilityCommand_CMD_COMMON_TYPE003( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_COMMON( CMD_COMMON_TYPE003, index, cmdData, cmdNum );
}

static short OutputUtilityCommand_CMD_COMMON( short type, short index, COMMANDDATA *cmdData, short cmdNum )
{
	char buf[CMD_BUF_MAX_SIZE];
	char *p;
	long size;
	short isSetTime;
	short result = -1;

	if ( cmdData == NULL ) goto Err;
	if ( index > (cmdNum -1) ) goto Err;

	p = buf;
	size = cmdData[index].len;
	memcpy( p, cmdData[index].cmd, size ); p+= size;
	*p = 0x00; p++;
	size = (long)(p - buf);

	isSetTime = 1;
	if ( type == CMD_COMMON_TYPE001 ){
		OutputCmdType001( buf, size );
	}
	else if ( type == CMD_COMMON_TYPE002 ){
		OutputCmdType002( buf, size, isSetTime );
	}
	else if ( type == CMD_COMMON_TYPE003 ){
		OutputCmdType003( buf, size, "POWEROFF" );
	}
	else {
		goto Err;
	}
	result = 0;
Err:
	return result;
}

static short OutputUtilityCommand( char *cmdName )
{
	COMMANDCOMPTABLE *pCurrentTbl = utilCommandCompTable;
	COMMANDCOMP	*pCurrentCmdComp;
	COMMANDOUTFUNCTABLE *pCurrentOutFuncTbl;
	short (*execFunc)( short, COMMANDDATA *, short );
	short result = -1;

	if ( cmdName == NULL ) goto Err;

	/* search command */
	pCurrentTbl = utilCommandCompTable;
	pCurrentCmdComp = NULL;
	while ( pCurrentTbl->name != NULL ){
		if ( !strcmp( pCurrentTbl->name, cmdName ) ){
			pCurrentCmdComp = pCurrentTbl->lpCommandComp;
			break;
		}
		pCurrentTbl++;
	}	
	if ( pCurrentTbl->name == NULL ) goto Err;

	/* search proc function */
	pCurrentOutFuncTbl = utilCommandProcFuncTable;
	while ( pCurrentOutFuncTbl->type != -1 ){
		if( pCurrentOutFuncTbl->type == pCurrentCmdComp->type ){
			execFunc = pCurrentOutFuncTbl->proc;
			break;
		}
		pCurrentOutFuncTbl++;
	}
	if ( pCurrentOutFuncTbl->type == -1 ) goto Err;

	/* output command */
	if ( (*execFunc)(pCurrentCmdComp->index, pCurrentCmdComp->lpCmdData, pCurrentCmdComp->cmdNum) < 0 ) goto Err;

	result = 0;
Err:
	return result;
}

short ExecMaintenance( short funcType )
{
	DIALOGCOMPTABLE *lpDialogCompTbl = utilDialogTable;
	char *dialogName;
	char *modelName;
	char resName[NAME_BUF_MAX_SIZE];
	char *cmdName;
	void *list;
	short status, action, next;
	short (*execFunc)( char * );
	static char funcName[NAME_BUF_MAX_SIZE];
	short result = -1;
	LPFUNCTIONCOMP lpComp;

	modelName = GetModelName();

	snprintf( resName, NAME_BUF_MAX_SIZE, "%s/%s", MAINTENANCE_RESPATH, MAINTENANCE_RESFILE );
	if ( ParseFunctionListTag( resName, modelName, &lpComp  ) != 0 ) goto Err;
	while( lpComp != NULL ) {
		if ( lpComp->type == funcType ){
			strncpy( funcName, lpComp->flow, NAME_BUF_MAX_SIZE );
			break;
		}
		lpComp = lpComp->next;
	}
	FreeFunctionCompList( lpComp );
	if 	( lpComp == NULL ) goto Err;

	if ( ParseFlowListTag( resName, &list ) != 0 )  goto Err;

	status = 1;
	while ( status != -1 ) {
#ifdef _PRINTUI_DEBUG_
		printf( "[start]------------------------>\n" );
#endif
		/* Get function name */
		if ( GetFuncNameFromFlowList( list, funcName, status, &dialogName ) != 0 ) goto Err;
#ifdef _PRINTUI_DEBUG_
		printf( "function name : %s\n", dialogName );
#endif

		lpDialogCompTbl = utilDialogTable;
		while( lpDialogCompTbl->name != NULL ) {
			if ( !strcmp( lpDialogCompTbl->name, dialogName ) ){
				execFunc = lpDialogCompTbl->proc;
				break;
			}
			lpDialogCompTbl++;
		}
		if ( lpDialogCompTbl->name == NULL ) goto Err;

		/* Exec function */
		if ( (action = (*execFunc)( dialogName )) < 0 ) goto Err;
#ifdef _PRINTUI_DEBUG_
		printf( "action : %d\n", action );
#endif
		if ( action == US_MAINTENANCE_EXIT ) goto Err;

		/* Get Command */
		if ( GetCommandNameFromFLowList( list, funcName, status, action,  &cmdName ) != 0 )  goto Err;
#ifdef _PRINTUI_DEBUG_
		if ( cmdName != NULL ){
			printf( "cmdName : %s\n", cmdName );
		}
		else {
			printf( "cmdName : Nothing\n" );
		}
#endif

		/* Output Command */
		if ( IsStrEmpty( cmdName ) != TRUE ){
			if ( OutputUtilityCommand( cmdName ) != 0 ) goto Err;
		}

		/* Get next status */	
		if ( GetNextIdFromFlowList( list, funcName, status, action, &next ) != 0 ) goto Err;
#ifdef _PRINTUI_DEBUG_
		printf( "next : %d\n", next );
		printf( "------------------------>[end]\n" );
#endif

		/* over write status */
		status = next;
	}

	result = 0;
Err:
	return result;
}

