/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2013
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
#include <sys/stat.h>
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
#include "util_funclist.h"
#include "util_cmdlist.h"


static const char bjl_cmds[]
= {0x1b, '[', 'K', 0x02, 0x00, 0x00, 0x1f };

/* global */
static int gUtilCommonStatus = 0;
static void *gLPCommonWork = NULL;


/* function prototypes */
static short OutputUtilityCommand_CMD_COMMON( short type, short index, COMMANDDATA *cmdData, short cmdNum );
static short CopyFlowName( char (*dstName)[NAME_BUF_MAX_SIZE], char *src, short *dstNameNum );



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
	ShowCommonUtilDialog( dialogName, lpWk->flag, &status );

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

void SetComboBoxItems(GtkWidget *combo, const char **Keytbl, int n, int index)
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
	gUtilCommonStatus = US_CANCEL;
	gtk_window_set_modal(data,FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));

	return TRUE;
}

static gboolean message_box_delete_event_set_ok_status
(GtkWidget *widget, GdkEvent *event, gpointer data) 
{
	gUtilCommonStatus = US_OK;
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


static int UtilMessageBoxSetDefault( char *message, char *title, unsigned int flag, unsigned int default_flag, GtkWidget *parent )
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

	gUtilCommonStatus = US_DEFAULT;
	
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
	else if ( flag & MB_CANCEL ){
		gtk_signal_connect (GTK_OBJECT (dialog), "delete_event",
				GTK_SIGNAL_FUNC (message_box_delete_event), dialog);
	}
	else {
		gtk_signal_connect (GTK_OBJECT (dialog), "delete_event",
				GTK_SIGNAL_FUNC (message_box_delete_event_set_ok_status), dialog);
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

	
	if ( parent == NULL ){
		gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(g_main_window) );
	}
	else {
		gtk_window_set_transient_for(GTK_WINDOW(dialog),
			 GTK_WINDOW(GTK_WINDOW(parent)) );
	}
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
	unsigned int flag,
	GtkWidget *parent )          
{
	return(UtilMessageBoxSetDefault(message, title, flag, MB_OK|MB_YES, parent) );
}


#define CONNECT_DIALOG_DELAY_TIME	1000

typedef struct {
	GtkWidget *dialog;
	int (*callback)(void);
} CONNECTPRINTERWORK;

static gboolean connect_printer( gpointer user_data )
{
	CONNECTPRINTERWORK	*wk = (CONNECTPRINTERWORK *)user_data;

	if ( wk == NULL ) goto onErr;

	if ( (*wk->callback)() != 0 ){
		gUtilCommonStatus = US_NB_CONNECT_NG;
	}
	else {
		gUtilCommonStatus = US_NB_CONNECT_OK;
	}

	gtk_window_set_modal(GTK_WINDOW(wk->dialog), FALSE);
	gtk_widget_hide( GTK_WIDGET(wk->dialog) );
	gtk_widget_destroy(GTK_WIDGET(wk->dialog));	

onErr:
	return TRUE;
}

static int UtilMessageBoxWithConnection(
	char *message,				
	char *title,                
	unsigned int flag,
	int (*callback)(void)
)
{
	GtkWidget	*dialog;				
	GtkWidget __attribute__ ((unused)) 	*dialog_action_area1;   
	GtkWidget	*dialog_vbox1;          
	GtkWidget	*hbox1;                 
	GtkWidget	*pixmap;                
	GtkWidget	*label;
	GdkPixmap	*icon = NULL;
	GdkPixmap	*iconMask = NULL;
	GtkStyle	*style;
	short		icon_exist = 1;
	guint id;
	CONNECTPRINTERWORK connectWork;


	gUtilCommonStatus = US_DEFAULT;

	if ( (message == NULL) || (title == NULL) || (callback == NULL) ) goto onErr;

	/* create dialog */
	dialog = gtk_dialog_new();				
	gtk_widget_realize(dialog);				
	gtk_window_set_title(GTK_WINDOW(dialog), title);	
	gtk_window_set_policy(GTK_WINDOW(dialog), FALSE, FALSE, TRUE);	
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);	

	gtk_signal_connect(GTK_OBJECT(dialog), "destroy",	GTK_SIGNAL_FUNC(message_box_destroy), dialog);
	//gtk_signal_connect (GTK_OBJECT (dialog), "delete_event", GTK_SIGNAL_FUNC (message_box_delete_event), dialog);
	gtk_signal_connect (GTK_OBJECT (dialog), "delete_event", GTK_SIGNAL_FUNC (message_box_delete_event_no_destroy), dialog);

	dialog_action_area1 = GTK_DIALOG(dialog)->action_area;	
	dialog_vbox1 = GTK_DIALOG(dialog)->vbox;	

	hbox1 = gtk_hbox_new(FALSE, 0);	
	gtk_widget_show(hbox1);			
	gtk_box_pack_start(GTK_BOX(dialog_vbox1), hbox1, TRUE, TRUE, 5);	

  	style = gtk_widget_get_style(dialog);
	switch (flag & 0x0000000f) {	
		case MB_ICON_INFORMATION:	
 			icon = gdk_pixmap_create_from_xpm_d(dialog->window, &iconMask, &style->bg[GTK_STATE_NORMAL], info_xpm);
  			break;
		
		case MB_ICON_EXCLAMATION:	
 			icon = gdk_pixmap_create_from_xpm_d(dialog->window, &iconMask, &style->bg[GTK_STATE_NORMAL], exclam_xpm);
			break;

		case MB_ICON_SYSERR:	
 			icon = gdk_pixmap_create_from_xpm_d(dialog->window, &iconMask, &style->bg[GTK_STATE_NORMAL], syserr_xpm);
			break;

		case MB_ICON_QUESTION:	/* Ver.2.90 */
 			icon = gdk_pixmap_create_from_xpm_d(dialog->window, &iconMask, &style->bg[GTK_STATE_NORMAL], question_xpm);
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

	label = gtk_label_new(message);	
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);		
	gtk_widget_show(label);			
	gtk_box_pack_start(GTK_BOX(hbox1), label, TRUE, TRUE, 10);	

	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(g_main_window) );
	gtk_widget_show(dialog);
	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);	

	connectWork.dialog = dialog;
	connectWork.callback = callback;

	id = gtk_timeout_add( CONNECT_DIALOG_DELAY_TIME, (GtkFunction)connect_printer, (gpointer)&connectWork );
	gtk_main();
	gtk_timeout_remove( id );

onErr:
	if( icon_exist ){
		gdk_pixmap_unref(icon);
	}
	return gUtilCommonStatus;				
}

static int SetBJLStart( char *buf )
{
	char *p = buf;
	int size;

	memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
	memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;

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
	char 	localBuf[CMD_BUF_MAX_SIZE];
	
	memcpy(p, BJLSETTIME, BJLSETTIMELEN); p+=BJLSETTIMELEN;				
	time (&t_time);									
	ltime = localtime(&t_time);

	/* Ver.3.60 */
	n = snprintf(localBuf, CMD_BUF_MAX_SIZE, "%4d", ltime->tm_year + 1900);
	memcpy(p, localBuf, n); p += n;
	n = snprintf(localBuf, CMD_BUF_MAX_SIZE, "%02d", ltime->tm_mon + 1);
	memcpy(p, localBuf, n); p += n;
	n = snprintf(localBuf, CMD_BUF_MAX_SIZE, "%02d", ltime->tm_mday);
	memcpy(p, localBuf, n); p += n;
	n = snprintf(localBuf, CMD_BUF_MAX_SIZE, "%02d", ltime->tm_hour);
	memcpy(p, localBuf, n); p += n;
	n = snprintf(localBuf, CMD_BUF_MAX_SIZE, "%02d", ltime->tm_min);
	memcpy(p, localBuf, n); p += n;
	n = snprintf(localBuf, CMD_BUF_MAX_SIZE, "%02d\x0a", ltime->tm_sec);
	memcpy(p, localBuf, n); p += n;

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

/*
	Output command ntimes
*/
void OutputCmdType004( char *cmdPtr, long cmdLen, short num )
{
	int n, i;
	long len;
	char buf[CMD_BUF_MAX_SIZE];
	char *p = buf;

	/* Output SetTime */
	n = SetBJLStart(p); p += n;
	n = SetControlMode(p); p += n;
	n = SetCurrentTime(p); p+=n; 
	n = SetBJLEnd(p); p += n;

	/* Output Command */
	for ( i=0; i<num; i++ ) {
		n = SetBJLStart(p); p += n;
		memcpy( p, cmdPtr, cmdLen ); p += cmdLen;
		n = SetBJLEnd(p); p += n;
	}

	*p = 0x00; p++;
	len = (long)(p - buf);
	PutPrintData( buf, len );
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
			if ( !strcmp( lpDialogStrComp->strid, CAPTION_ID ) ){
				gtk_window_set_title( GTK_WINDOW(dialog),  g_window_title );
			}
			else {
				gtk_window_set_title( GTK_WINDOW(dialog), LookupText(g_keytext_list, lpDialogStrComp->strid) );
			}
		}
		else if ( (lpDialogStrComp->type == MSGTYPE_BUTTON) || (lpDialogStrComp->type == MSGTYPE_RADIOBUTTON) ||
			(lpDialogStrComp->type == MSGTYPE_CHECKBUTTON) ){
			gtk_button_set_label( GTK_BUTTON(LookupWidget(dialog, lpDialogStrComp->label )),
				LookupText(g_keytext_list, lpDialogStrComp->strid));
			gtk_widget_show( LookupWidget(dialog, lpDialogStrComp->label ) );
		}
		else if ( lpDialogStrComp->type == MSGTYPE_SPINBUTTON ){
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

short ShowCommonUtilDialog( char *dialogName, unsigned int flag, short *retVal ) 
{
	LPDIALOGSTRCOMP lpDialogStrComp = NULL;
	char resName[NAME_BUF_MAX_SIZE];
	short result = -1;

	*retVal = 0;

	snprintf( resName, NAME_BUF_MAX_SIZE, "%s/%s", MAINTENANCE_RESPATH, MAINTENANCE_RESFILE );
	if ( ParseDialogStringListTag( resName, dialogName, &lpDialogStrComp ) != 0 ) goto Err;

	while ( lpDialogStrComp != NULL ){
		if ( lpDialogStrComp->type == MSGTYPE_LABEL ){
			*retVal = UtilMessageBox(LookupText(g_keytext_list, lpDialogStrComp->strid), g_window_title, flag, NULL );
		}
		lpDialogStrComp = lpDialogStrComp->next;
	}
		
	FreeDialogStrCompList( lpDialogStrComp );
	result = 0;
Err:
	return result;
}

short ShowCommonUtilDialogWithConnection( char *dialogName, unsigned int flag, short *retVal, int (*callback)(void) ) 
{
	LPDIALOGSTRCOMP lpDialogStrComp = NULL;
	char resName[NAME_BUF_MAX_SIZE];
	short result = -1;

	*retVal = 0;

	snprintf( resName, NAME_BUF_MAX_SIZE, "%s/%s", MAINTENANCE_RESPATH, MAINTENANCE_RESFILE );
	if ( ParseDialogStringListTag( resName, dialogName, &lpDialogStrComp ) != 0 ) goto Err;

	while ( lpDialogStrComp != NULL ){
		if ( lpDialogStrComp->type == MSGTYPE_LABEL ){
			*retVal = UtilMessageBoxWithConnection(LookupText(g_keytext_list, lpDialogStrComp->strid), g_window_title, flag, callback );
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
	char flowidNameTable[3][NAME_BUF_MAX_SIZE];
	short flowNum = 0;
	short current;
	short result = -1;
	LPFUNCTIONCOMP lpComp;

	modelName = GetModelName();

	for ( current = 0; current < 3; current++ ){
		memset( flowidNameTable[current], 0, NAME_BUF_MAX_SIZE );	
	}

	snprintf( resName, NAME_BUF_MAX_SIZE, "%s/%s", MAINTENANCE_RESPATH, MAINTENANCE_RESFILE );
	if ( ParseFunctionListTag( resName, modelName, &lpComp  ) != 0 ) goto Err1;
	while( lpComp != NULL ) {
		if ( lpComp->type == funcType ){
			if ( CopyFlowName( flowidNameTable, lpComp->flow, &flowNum ) != 0 ) goto Err1;
			break;
		}
		lpComp = lpComp->next;
	}
	if 	( lpComp == NULL ) goto Err1;

	if ( ParseFlowListTag( resName, &list ) != 0 )  goto Err1;

	/* sensitive false in main dialog */
	//DisableSensitiveDialog( (GtkWidget *)(UI_DIALOG(g_main_window)->window) );
	DisableSensitiveDialog( g_main_window );

	current = 0;
	while ( strcmp( flowidNameTable[current], "END" ) ){

		status = 1;
		while ( status != U_STATUS_END ) {
#ifdef _PRINTUI_DEBUG_
			printf( "[start]------------------------>\n" );
#endif
			/* Get function name */
			if ( GetFuncNameFromFlowList( list, flowidNameTable[current], status, &dialogName ) != 0 ) goto Err2;
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
			if ( lpDialogCompTbl->name == NULL ) goto Err2;

			/* Exec function */
			if ( (action = (*execFunc)( dialogName )) < 0 ) goto Err2;
#ifdef _PRINTUI_DEBUG_
			printf( "action : %d\n", action );
#endif
			if ( action == US_DEFAULT ) goto EXIT;

			/* Get Command */
			if ( GetCommandNameFromFLowList( list, flowidNameTable[current], status, action,  &cmdName ) != 0 )  goto Err2;
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
				if ( OutputUtilityCommand( cmdName ) != 0 ) goto Err2;
			}

			/* Get next status */	
			if ( GetNextIdFromFlowList( list, flowidNameTable[current], status, action, &next ) != 0 ) goto Err2;
#ifdef _PRINTUI_DEBUG_
			printf( "next : %d\n", next );
			printf( "------------------------>[end]\n" );
#endif

			if ( next == U_STATUS_EXIT ) goto EXIT;
			/* over write status */
			status = next;
		}

		current++;
		if ( !strcmp( flowidNameTable[current], "NEXT" ) ){
			current = 0;
		}
	}

EXIT:
	result = 0;
Err2:
	/* sentive true in main dialog */
	//EnableSensitiveDialog( (GtkWidget *)(UI_DIALOG(g_main_window)->window) );
	EnableSensitiveDialog( g_main_window );

	FreeFlowCompList( list );
Err1:
	FreeFunctionCompList( lpComp );
	return result;
}

/*
	CopyFlowName
*/
static short CopyFlowName( char (*dstName)[NAME_BUF_MAX_SIZE], char *src, short *dstNameNum )
{
	char *charStr, *wrtPtr;
	const char terminateStr[][NAME_BUF_MAX_SIZE] = { "END", "NEXT" };
	short cnt, current, index;
	short result = -1;
	
	if (  (dstName == NULL) || (src == NULL) || (dstNameNum == NULL) ) goto Err;

	index = 0;
	current = 0;
	charStr = src;
	wrtPtr = dstName[current];
	while ( *charStr != 0x00 ){
		if ( (*charStr == '+') || (*charStr == '*') ){
			*wrtPtr = 0x00;
			current++;	/* next dstName */
			wrtPtr = dstName[current]; /* move next write buf */

			if ( *charStr == '*' ){
				index = 1;
			}

			charStr++;  /* skip '+', '*' charactor */
		}
		*wrtPtr = *charStr;
		charStr++;
		wrtPtr++;
	}
	*wrtPtr = 0x00;
	current++;

	/* copy  terminate str */
	if ( (cnt = strlen(terminateStr[index])) >= NAME_BUF_MAX_SIZE ) cnt = NAME_BUF_MAX_SIZE - 1;
	memcpy( dstName[current], terminateStr[index], cnt );
	*(dstName[current] + cnt + 1 ) = 0x00;
	current++;

	*dstNameNum = current;

	result = 0;
Err:
	return result;
}


gchar *GetMaintenanceFuncName( short type )
{
	char *modelName;
	char buf[NAME_BUF_MAX_SIZE];
	char flowidNameTable[3][NAME_BUF_MAX_SIZE];
	short flowNum;
	char *dialogName;
	LPFUNCTIONCOMP lpFuncComp;
	LPDIALOGSTRCOMP lpDialogComp;
	void *list;
	gchar *retPtr = NULL;

	/* Get FlowList */
	modelName = GetModelName();
	snprintf( buf, NAME_BUF_MAX_SIZE, "%s/%s", MAINTENANCE_RESPATH, MAINTENANCE_RESFILE );
	if ( ParseFunctionListTag( buf, modelName, &lpFuncComp  ) != 0 ) goto Err1;
	while( lpFuncComp != NULL ) {
		if ( lpFuncComp->type == type ){
			if ( CopyFlowName( flowidNameTable, lpFuncComp->flow, &flowNum ) != 0 ) goto Err2;
			break;
		}
		lpFuncComp = lpFuncComp->next;
	}
	if ( lpFuncComp == NULL ) goto Err2;

	/* Get dialogName */
	if ( ParseFlowListTag( buf, &list ) != 0 )  goto Err2;
	if ( GetFuncNameFromFlowList( list, flowidNameTable[0], 1, &dialogName ) != 0 ) goto Err3;

	/* Get Maintenance Function Name */
	if ( ParseDialogStringListTag( buf, dialogName, &lpDialogComp ) != 0 ) goto Err3;
	retPtr = LookupText( g_keytext_list, lpDialogComp->strid );
	
	FreeDialogStrCompList( lpDialogComp );
Err3:
	FreeFlowCompList( list );
Err2:	
	FreeFunctionCompList( lpFuncComp );
Err1:
	return retPtr;
}

/* Ver.3.70 */
void EnableSensitiveDialog( GtkWidget *widget )
{
	if( GTK_WIDGET_SENSITIVE( widget ) == 0 ){
		gtk_widget_set_sensitive( widget, TRUE );
	}
}

/* Ver.3.70 */
void DisableSensitiveDialog( GtkWidget *widget )
{
	if( GTK_WIDGET_SENSITIVE( widget ) != 0 ){
		gtk_widget_set_sensitive( widget, FALSE );
	}
}

/* Ver.1.00 */
gchar* CheckFileExists(const gchar *dirname, const gchar *filename)
{
	gchar *full_filename;
	struct stat s;
	gint status;
	gint full_filename_len;

	full_filename_len = strlen (dirname) + 1 + strlen (filename) + 1;
	full_filename = (gchar*)g_malloc0( full_filename_len );

	strncpy(full_filename, dirname, full_filename_len); /* Ver.3.60 */
	full_filename[ full_filename_len -1 ] = '\0';
	strcat(full_filename, G_DIR_SEPARATOR_S);
	strcat(full_filename, filename);

	status = stat(full_filename, &s);
	if( status == 0 && S_ISREG(s.st_mode) )
		return full_filename;

	g_free(full_filename);
	return NULL;
}

/* Ver.1.00 */
static
void ShowUtilButton(GtkWidget* main_window, char* button_name)
{
	GtkWidget* button
		= LookupWidget(main_window, button_name);
	gtk_widget_show(button);
}

/* Ver.1.00 */
static 
void ShowUtilButtonLabel(GtkWidget* main_window, char* label_name, short util_type )
{
	GtkWidget* label = LookupWidget(main_window, label_name);
	if ( label == NULL ) return;

	gtk_label_set_text( GTK_LABEL(label), GetMaintenanceFuncName(util_type) );
}

/* Ver.1.00 */
void ShowUtilButtons(GtkWidget* main_window)
{
	short util_flag = GetUtilFlag(g_model_id);
	GtkWidget* label;

	/* display "maintenance tab" */
	label = LookupWidget(main_window, "maintenance_label");
	gtk_label_set_text( GTK_LABEL(label), LookupText(g_keytext_list, "LUM_IDD_PAG_MAINTENANCE" ) );

	/* Cleaning */
	if( util_flag & UF_CLEANING ) {
		ShowUtilButtonLabel(main_window, "util_clean_label", FUNCTYPE_CLEANING);
		ShowUtilButton(main_window, "util_clean_button");
	}

	/* Deep Cleaning */
	if( util_flag & UF_DEEP_CLEANING ) {
		ShowUtilButtonLabel(main_window, "util_refresh_label", FUNCTYPE_DEEP_CLEANING);
		ShowUtilButton(main_window, "util_refresh_button");
	}

	/* Bottom Plate Cleaning */
	if( util_flag & UF_PLATE_CLEANING ) {
		ShowUtilButtonLabel(main_window, "util_plate_clean_label", FUNCTYPE_PLATE_CLEANING);
		ShowUtilButton(main_window, "util_plate_clean_button");
	}

	/* Roller Cleaning */
	if( util_flag & UF_ROLLER_CLEANING ){
		ShowUtilButtonLabel(main_window, "util_roller_clean_label", FUNCTYPE_ROLLER_CLEANING);
		ShowUtilButton(main_window, "util_roller_clean_button" );
	}

	/* Nozzle Check Pattern */
	if( util_flag & UF_NOZZLE_CHECK ) {
		ShowUtilButtonLabel(main_window, "util_nozzle_check_label", FUNCTYPE_NOZZLE_CHECK);
		ShowUtilButton(main_window, "util_nozzle_check_button");
	}

	/* Print Head Alignment */
	if( util_flag & UF_HEAD_ALIGNMENT ) {
		ShowUtilButtonLabel(main_window, "util_head_adjust_label", FUNCTYPE_HEAD_ALIGNMENT_MANUAL);
		ShowUtilButton(main_window, "util_head_adjust_button");
	}

	/* Ink Counter Reset */
	if( util_flag & UF_INK_RESET ) {
		ShowUtilButtonLabel(main_window, "util_ink_reset_label", FUNCTYPE_INK_RESET);
		ShowUtilButton(main_window, "util_ink_reset_button");
	}

	/* Ink Warning */
	if( util_flag & UF_INK_WARNING ){
		ShowUtilButtonLabel(main_window, "util_ink_warning_label", FUNCTYPE_INK_WARNING);
		ShowUtilButton(main_window, "util_ink_warning_button");
	}

	/* Power Off */
	if( util_flag & UF_POWER_OFF ) {
		ShowUtilButtonLabel(main_window, "util_power_off_label", FUNCTYPE_POWER_OFF);
		ShowUtilButton(main_window, "util_power_off_button");
	}

	/* Auto Power */
	if( util_flag & UF_AUTO_POWER ){
		ShowUtilButtonLabel(main_window, "util_auto_power_label", FUNCTYPE_AUTOPOWER);
		ShowUtilButton(main_window, "util_auto_power_button");
	}

	/* Custom Settings */
	if( util_flag & UF_CUSTOM ){
		ShowUtilButtonLabel(main_window, "util_config_label", FUNCTYPE_CUSTOM);
		ShowUtilButton(main_window, "util_config_button");
	}

	/* Quiet Settings */
	if( util_flag & UF_QUIET ){
		ShowUtilButtonLabel(main_window, "util_quiet_label", FUNCTYPE_QUIET);
		ShowUtilButton(main_window, "util_quiet_button");
	}

	/* Ink Cartridge */
	//if( util_flag & UF_INK_CARTRIDGE ) {
//		ShowUtilButton(main_window, "util_ink_cartridge_button");
//	}

	/* Papser Source Settings */
	if( util_flag &  UI_PAPER_SOURCE_SETTING){
		ShowUtilButtonLabel(main_window, "util_paper_source_setting_label", FUNCTYPE_PAPER_SOURCE_SETTING);
		ShowUtilButton(main_window, "util_paper_source_setting_button");
	}
}


/* Ver.1.00 */
void UpperAsciiStr(char *str)
{
	gint i;

	for( i = 0; i < strlen(str); i++ )
		if( 'a' <= str[i] && str[i] <= 'z' )
			str[i] -= 0x20;
}

/* Ver.1.00 */
int LowerAsciiCode( int c )
{
	if( c >= 'A' && c <= 'Z' ) return (c + 0x20);
	return c;
}

/* Ver.1.00 */
gboolean SameName(gchar* name1, gchar* name2)
{
	if( name1 != NULL && name2 != NULL )
		return strcmp(name1, name2)? FALSE : TRUE;
	else
		return FALSE;
}

/* Ver.1.00 */
GtkWidget* LookupWidget(GtkWidget* window, const gchar* name)
{
	return lookup_widget(window, name);
}

/* Ver.1.00 */
GtkWidget* GetTopWidget(GtkWidget* widget) 
{
	return gtk_widget_get_toplevel(widget);
}

/* Ver.1.00 */
int GetActiveButtonIndex(GtkWidget* window,
			 const gchar* button_name[], int default_index)
{
	GtkWidget* button;
	int index = 0;

	while( button_name[index] )
	{
		if( (button = LookupWidget(window, button_name[index])) != NULL )
		{
			if( GTK_TOGGLE_BUTTON(button)->active )
				return index;
		}
		index++;
	}
	return default_index;
}

/* Ver.1.00 */
short GetUtilFlag(short model_id)
{
	LPFUNCTIONCOMP lpComp;
	char resName[NAME_BUF_MAX_SIZE];
	char *modelName = GetModelName();
	short flag = 0;

	snprintf( resName, NAME_BUF_MAX_SIZE, "%s/%s", MAINTENANCE_RESPATH, MAINTENANCE_RESFILE );
	if ( ParseFunctionListTag( resName, modelName, &lpComp  ) != 0 ) goto Err;
	while( lpComp != NULL ){
		if ( lpComp->type == FUNCTYPE_CLEANING ) flag |= UF_CLEANING;
		else if ( lpComp->type == FUNCTYPE_DEEP_CLEANING ) flag |= UF_DEEP_CLEANING;
		else if ( lpComp->type == FUNCTYPE_ROLLER_CLEANING ) flag |= UF_ROLLER_CLEANING;
		else if ( lpComp->type == FUNCTYPE_PLATE_CLEANING ) flag |= UF_PLATE_CLEANING;
		else if ( lpComp->type == FUNCTYPE_NOZZLE_CHECK ) flag |= UF_NOZZLE_CHECK;
		else if ( lpComp->type == FUNCTYPE_POWER_OFF ) flag |= UF_POWER_OFF;
		else if ( lpComp->type == FUNCTYPE_AUTOPOWER ) flag |= UF_AUTO_POWER;
		else if ( lpComp->type == FUNCTYPE_INK_WARNING ) flag |= UF_INK_WARNING;
		else if ( lpComp->type == FUNCTYPE_INK_RESET ) flag |= UF_INK_RESET;
		else if ( lpComp->type == FUNCTYPE_INK_CARTRIDGE ) flag |= UF_INK_CARTRIDGE;
		else if ( lpComp->type == FUNCTYPE_QUIET ) flag |= UF_QUIET;
		else if ( lpComp->type == FUNCTYPE_HEAD_ALIGNMENT_AUTO ) flag |= UF_HEAD_ALIGNMENT;
		else if ( lpComp->type == FUNCTYPE_HEAD_ALIGNMENT_MANUAL ) flag |= UF_HEAD_ALIGNMENT;
		else if ( lpComp->type == FUNCTYPE_CUSTOM ) flag |= UF_CUSTOM;
		else if ( lpComp->type == FUNCTYPE_PAPER_SOURCE_SETTING ) flag |= UI_PAPER_SOURCE_SETTING;
		lpComp = lpComp->next;
	}
	FreeFunctionCompList( lpComp );
#if 0
	ModelTable* model_table;

	if( (model_table = GetModelTableEntry(model_id)) != NULL )
		return model_table->util_flag;

#endif
Err:
	return flag;
}
