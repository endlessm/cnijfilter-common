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
#include <stdlib.h>
#include <stdio.h>
#include <time.h>			
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

#include "callbacks.h"
//#	include "interface.h"
//#	include "support.h"

#include "bjuidefs.h"
#include "utildef.h"
#include "msgicon.h"

static	int	result;

static	int	page_pause_mode;
static	int	scan_pause_mode;
static	gchar	*power_on_mode;
static	gchar	*power_off_mode;	
static	int poweron_index;
static	int poweroff_index;	
static  int current_poweron_index;			// 2006/11/10
static  int current_poweroff_index;			// 2006/11/10
static	int drylevel_value;
static	int current_drylevel_value;
static 	int quiet_mode;			
static 	int current_quiet_mode;				// 2006/11/10
static	int warning_mode = 1;
static	int current_warning_mode;			// 2006/11/10
static 	int black_reset;
static	int color_reset;
static	int papergap_mode;
static	int current_papergap_mode;			// 2006/11/10
static	int manual_head_mode;
static	int current_manual_head_mode;		// 2006/11/10
static	int cartridge_index;
static	int cartridge_cur_index;

static	short config_flag;

static	GdkPixmap	*regi_pixmap;	


static	HOTSPOT		HotSpot[REGI_EDITMAX];	
static	short		ItemValue[REGI_EDITMAX];
static	short		nKindCnt;				
static	u_short		type;					
static	short		nPageNum;
static	LPCTRLITEM	lpCtrlItem;				
static	LPBOXINF	lpBoxInf;				
static	char		**lpBJLtbl;				
static	short		head_type;				
static	short		regi_flag;

static	short		refresh_head_type;	

extern	char	*g_hostname;				
extern	gchar	*g_socketname;				
extern	KeyTextList	*g_keytext_list;		

int getnum(char *ptr);
char *GetParamValue(char **Keytbl, char **Valuetbl, int n, char *mode);	
void SetComboBoxItems(GtkWidget *combo, char **Keytbl, int n, int index);	/* Ver.2.80 */

int GetAutoPowerIndex(char **Keytbl, int n, char *mode);
int nValueToIndex(short *nValuetbl, int n, short nValue);
int KeyToIndex(char **Keytbl, int n, char *type);

static char* GetPatternFileName(short );
static int	CreateRegiBSCC( char*, int*, char*, short*, short );
static int WriteToBSCCFile( char*, char*, short );
static int WriteToPrintFile( char*, char*, int, short );



static gboolean message_box_delete_event
(GtkWidget *widget, GdkEvent *event, gpointer data) 
{
	result = ID_CANCEL;
	gtk_window_set_modal(data,FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));

	return TRUE;
}


static void message_box_destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();						
	gtk_window_set_modal(data, FALSE);
}


static void message_box_ok(GtkWidget *widget, gpointer data)
{
	result = ID_OK;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static void message_box_cancel(GtkWidget *widget, gpointer data)
{
	result = ID_CANCEL;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static void message_box_yes(GtkWidget *widget, gpointer data)
{
	result = ID_YES;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static void message_box_no(GtkWidget *widget, gpointer data)
{
	result = ID_NO;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static void message_box_abort(GtkWidget *widget, gpointer data)
{
  	result = ID_ABORT;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static void message_box_ignore(GtkWidget *widget, gpointer data)
{
  	result = ID_IGNORE;
	gtk_window_set_modal(data, FALSE);
	gtk_widget_destroy(GTK_WIDGET(data));	
}


static int UtilMessageBoxSetDefault(
	char *message,				
	char *title,                
	unsigned int flag,
	unsigned int default_flag)          
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
	
	dialog = gtk_dialog_new();				
	gtk_widget_realize(dialog);				
	gtk_window_set_title(GTK_WINDOW(dialog), title);	
	gtk_window_set_policy(GTK_WINDOW(dialog), FALSE, FALSE, TRUE);	
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);	
	
	gtk_signal_connect(GTK_OBJECT(dialog), "destroy",	
			      GTK_SIGNAL_FUNC(message_box_destroy), dialog);
	gtk_signal_connect (GTK_OBJECT (dialog), "delete_event",
						GTK_SIGNAL_FUNC (message_box_delete_event), dialog);
						
		
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
	}

	pixmap = gtk_pixmap_new(icon, iconMask);			
	gtk_box_pack_start(GTK_BOX(hbox1), pixmap, FALSE, FALSE, 10);	
	gtk_widget_show(pixmap);			

	label = gtk_label_new(message);	
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);		
	gtk_widget_show(label);			
	gtk_box_pack_start(GTK_BOX(hbox1), label, TRUE, TRUE, 10);	


	hbuttonbox1 = gtk_hbutton_box_new();		
	gtk_button_box_set_layout(
		GTK_BUTTON_BOX(hbuttonbox1), GTK_BUTTONBOX_SPREAD);	
	gtk_box_pack_start(
		GTK_BOX(dialog_action_area1), hbuttonbox1, TRUE, FALSE, 0);	
	gtk_widget_show(hbuttonbox1);		
	
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

	gdk_pixmap_unref(icon);		
	return result;				
}


int UtilMessageBox(
	char *message,				
	char *title,                
	unsigned int flag)          
{

	return(UtilMessageBoxSetDefault(message, title, flag, MB_OK|MB_YES));

}

int	SetCurrentTime(char *buf)
{
	time_t	t_time;
	struct	tm		*ltime;
	int		n;
	char	*p = buf;           
	
	memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;								
	memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;					
	memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;			

	memcpy(p, BJLSETTIME, BJLSETTIMELEN); p+=BJLSETTIMELEN;				
	time (&t_time);									
	ltime = localtime(&t_time);						
	n = sprintf(p, "%4d", ltime->tm_year + 1900); p += n;	
	n = sprintf(p, "%02d", ltime->tm_mon + 1); p += n;
	n = sprintf(p, "%02d", ltime->tm_mday);	p += n;
	n = sprintf(p, "%02d", ltime->tm_hour);	p += n;
	n = sprintf(p, "%02d", ltime->tm_min); p += n;
	n = sprintf(p, "%02d\x0a", ltime->tm_sec); p += n;

	memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;		
	
	return (BJLLEN + BJLSTARTLEN + BJLCTRLMODELEN
			+ BJLSETTIMELEN + BJLSETTIMEPARAMLEN + BJLENDLEN);
}	


void
on_pattern_check_dialog_destroy        (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


gboolean
on_pattern_check_dialog_delete_event   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	result = ID_CANCEL;

	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
		
	return TRUE;
}


void
on_pattern_check_exit_button_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	result = ID_CANCEL;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}


void
on_pattern_check_cleaning_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	result = ID_OK;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}


void
on_nozzle_check_dialog_destroy         (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


gboolean
on_nozzle_check_dialog_delete_event    (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	result = ID_CANCEL;

	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
		
	return TRUE;
}


void
on_nozzle_check_execute_button_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	result = ID_OK;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}


void
on_nozzle_check_cancel_button_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
	result = ID_CANCEL;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}


void
on_head_alignment_dialog_destroy       (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


gboolean
on_head_alignment_dialog_delete_event  (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	result = ID_CANCEL;

	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
		
	return TRUE;
}


void
on_head_alignment_execute_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

	result = ID_OK;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}

static void CheckAlignmentSetting(GtkWidget *widget)
{

	char		buf[128];
	char		*p = buf;
	int n;

	if( !strcmp(GetModelName(), "IP4200") || !strcmp(GetModelName(), "MP500") ||
	    !strcmp(GetModelName(), "IP6600D") || !strcmp(GetModelName(), "IP7500") ) {
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_50"),
						  g_window_title, MB_ICON_EXCLAMATION | MB_OK | 
						  MB_CANCEL)==ID_CANCEL)
			return;
	}
	else {
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_44"),
						  g_window_title, MB_ICON_EXCLAMATION | MB_OK | 
						  MB_CANCEL)==ID_CANCEL)
			return;
	}
	
	n = SetCurrentTime(p); p+=n;
	memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
	memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;           
	memcpy(p, BJLREGICHECK, BJLREGICHECKLEN); p+=BJLREGICHECKLEN;
	memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;                 
	*p = 0x00;
	PutPrintData(buf, n+BJLLEN+BJLSTARTLEN+BJLREGICHECKLEN+BJLENDLEN+1);
	
	UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
				   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

}


void
on_head_alignment_check_setting_button_clicked
(GtkButton       *button, gpointer         user_data)
{

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			

	CheckAlignmentSetting(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	result = ID_CANCEL;
}


void
on_head_alignment_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	result = ID_CANCEL;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();

}


void
on_plate_deep_cleaning_dialog_destroy  (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


gboolean
on_deep_cleaning_dialog_delete_event   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	result = ID_CANCEL;

	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
		
	return TRUE;
}


void
on_deep_cleaning_execute_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	result = ID_OK;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}


void
on_deep_cleaning_cancel_button_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	result = ID_CANCEL;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			

}



void
on_plate_cleaning_dialog_destroy       (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


gboolean
on_plate_cleaning_dialog_delete_event  (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	result = ID_CANCEL;

	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
		
	return TRUE;
}


void
on_plate_cleaning_execute_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

	result = ID_OK;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			

}


void
on_plate_cleaning_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

	result = ID_CANCEL;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			

}

static void special_set_default(GtkWidget *widget)
{

	GtkWidget	*page_button;		
	GtkWidget	*scan_button;		

	page_button = LookupWidget(widget, "page_checkbutton");	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(page_button), FALSE);	
	scan_button = LookupWidget(widget, "scan_checkbutton");	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(scan_button), FALSE);	

}


gboolean on_special_dialog_delete_event
(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{

	result = ID_CANCEL;
	
	special_set_default(widget);
	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
		
	return TRUE;
}


void on_special_dialog_destroy(GtkObject *object, gpointer user_data)
{
	gtk_main_quit();			
}


void on_special_send_button_clicked(GtkButton *button, gpointer user_data)
{

	GtkWidget	*page_button;		
	GtkWidget	*scan_button;		
  
	result = ID_OK;

	
	page_button = LookupWidget(GTK_WIDGET(button), "page_checkbutton");	
	page_pause_mode = GTK_TOGGLE_BUTTON(page_button)->active;	
	scan_button = LookupWidget(GTK_WIDGET(button), "scan_checkbutton");	
	scan_pause_mode = GTK_TOGGLE_BUTTON(scan_button)->active;	

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}



void on_special_cancel_button_clicked(GtkButton *button, gpointer user_data)
{
		
	GtkWidget *window = GetTopWidget(GTK_WIDGET(button));

	result = ID_CANCEL;

	special_set_default(window);
	gtk_widget_hide(window);	
	gtk_main_quit();			
}



void on_special_std_button_clicked(GtkButton *button, gpointer user_data)
{
	
	special_set_default(GetTopWidget(GTK_WIDGET(button)));
}




static void InitItemValue(void)
{
		int i;
		for(i=0; i < nKindCnt; i++)
		  ItemValue[i] = 0;
}



void SetPenColor(GdkGC *gc, int red, int green, int blue)
{
  GdkColor  color;

  color.red   = red;
  color.green = green;
  color.blue  = blue;

  gdk_color_alloc(gdk_colormap_get_system(),&color);	
  gdk_gc_set_foreground(gc, &color);					
}




char *GetRegiDialogName(short page)
{
	int		i, index;
	char	*model_name;

	model_name = GetModelName();		
	index = -1;
	for (i=0; i < sizeof(RegiInfo)/sizeof(REGINFO); i++) {		
		if (!strcmp(RegiInfo[i].ModelName, model_name)) {	
			index = i;			
			break;
		}
	}
	index = (index == -1)? 0 : index;	
	
	return (RegiInfo[index].regi[page].DialogName);		
}




char *GetRegiDrawingName(short page)
{
	int		i, index;
	char	*model_name;

	model_name = GetModelName();		
	index = -1;
	for (i=0; i < sizeof(RegiInfo)/sizeof(REGINFO); i++) {		
		if (!strcmp(RegiInfo[i].ModelName, model_name)) {	
			index = i;			
			break;
		}
	}
	index = (index == -1)? 0 : index;	
	
	return (RegiInfo[index].regi[page].DrawingName);	
}



void DrawTestPrintPage(
	GtkWidget *regi_dialog,			
	GdkPixmap *pixmap,              
	HOTSPOT *hotspot,               
	CTRLITEM *ctrlitem,             
	short *items,                   
	short	group,                  
	short kindcnt)                  
{
	int			i;
	int			nStep = 17;			
	int			width, height;      
	short		x, y;               
	GdkGC		*gc;                
	GdkPoint	aPoints[6];         
	GtkWidget	*drawarea;          
	GdkRectangle	update_rect;    
	
	gc = gdk_gc_new(regi_dialog->window);		

	
	gdk_window_get_size(pixmap, &width, &height);		
	gdk_draw_rectangle(pixmap,					
						regi_dialog->style->bg_gc[GTK_STATE_NORMAL],
						TRUE, 0, 0, width, height);
	
	
	aPoints[0].x = 0;			
	aPoints[0].y = 0;
	aPoints[1].x = 0;
	aPoints[1].y = height -1;
	aPoints[2].x = width - nStep;
	aPoints[2].y = height -1;
	aPoints[3].x = width - nStep;
	aPoints[3].y = height - nStep;
	aPoints[4].x = width -1;
	aPoints[4].y = height - nStep;
	aPoints[5].x = width -1;
	aPoints[5].y = 0;
	SetPenColor(gc, 0xffff, 0xffff, 0xffff);	
	gdk_draw_polygon(pixmap, gc, TRUE, aPoints, 6);	
	SetPenColor(gc, 0, 0, 0);		
	gdk_draw_polygon(pixmap, gc, FALSE, aPoints, 6);	
	
	
	aPoints[0].x = width - nStep;
	aPoints[0].y = height -1;
	aPoints[1].x = width - nStep;
	aPoints[1].y = height - nStep;
	aPoints[2].x = width -1;
	aPoints[2].y = height - nStep;
	SetPenColor(gc, 0xc000, 0xc000, 0xc000);		
	gdk_draw_polygon(pixmap, gc, TRUE, aPoints, 3);	
	SetPenColor(gc, 0, 0, 0);				
	gdk_draw_polygon(pixmap, gc, FALSE, aPoints, 3);	

	
	SetPenColor(gc, 0x8000, 0x8000, 0x8000);		
	gdk_draw_line(pixmap, gc, 0, 0, 0, height -1);
	gdk_draw_line(pixmap, gc, 0, 0, width -1, 0);
	gdk_draw_line(pixmap, gc, width - nStep, height-1, width-1, height - nStep);
	
	
	for (i=0; i<kindcnt; i++) {		
		short	nOffsetX, nOffsetY, nStepX, nStepY, j;
		short	dx, dy;
		short	box_width, box_height;
		short	rep;
		
		if (hotspot[i].linedir) {	
			nOffsetX = 0;				
			nOffsetY = hotspot[i].len;	
			dx = hotspot[i].width;		
			dy = 0;
		} else {		
			nOffsetX = hotspot[i].len;	
			nOffsetY = 0;				
			dx = 0;
			dy = hotspot[i].width;		
		}
		
		if (hotspot[i].stepdir) {	
			nStepX = 0;					
			nStepY = hotspot[i].step;	
		} else {					
			nStepX = hotspot[i].step;	
			nStepY = 0;					
		}
		
		if (hotspot[i].repeat) {	
			if (group == i)
				SetPenColor(gc,
					hotspot[i].red, hotspot[i].green, hotspot[i].blue);
			else
				SetPenColor(gc, 0xc000, 0xc000, 0xc000);
				
			for (rep=0; rep < hotspot[i].repeat; rep++) {
				x = hotspot[i].drawx + dx * rep;
				y = hotspot[i].drawy + dy * rep;
				for (j=0; j < hotspot[i].cnt; j++, x+=nStepX, y+=nStepY) {
					gdk_draw_line(pixmap, gc,
						x-nOffsetX, y-nOffsetY, x+nOffsetX, y+nOffsetY);
				}
			}
		} else if (type & ORNAMENT_S600) {	
		 	x = hotspot[i].drawx;		
		 	y = hotspot[i].drawy;
		 	box_width = hotspot[i].width;
		 	box_height =  hotspot[i].len*2 + (i+1);
		 	for (j=0; j<hotspot[i].cnt; j++, x+=nStepX, y+=nStepY) {	
		 		int		startx, starty;
				if (group == i)		
				 	SetPenColor(gc,
						hotspot[i].red, hotspot[i].green, hotspot[i].blue);	
		 		else		
					SetPenColor(gc, 0xc000, 0xc000, 0xc000);	
		 		startx = x - nOffsetX;	
		 		starty = y - nOffsetY; 
		 		gdk_draw_rectangle(pixmap, gc, TRUE, startx, starty,	
		 								box_width, box_height);
		 		
				if (group == i)		
				 	SetPenColor(gc, 0, 0, 0);				
			 	else		
		 			SetPenColor(gc, 0xc000, 0xc000, 0xc000);	

		 		if (i == 0) {		
		 			int		linex, liney;
		 			linex = startx + box_width + 3;
		 			liney = starty + box_height/2;
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+5, liney);
		 			
		 			linex = startx;
		 			gdk_draw_line (pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 		} else {	
		 			int		linex, liney;
		 			linex = startx + box_width + 3;
		 			liney = starty + box_height/3;
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+5, liney);
		 			linex = startx;
		 			gdk_draw_line (pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 			
		 			linex = startx + box_width + 3;
		 			liney += box_height/3 + 1;
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+5, liney);
		 			linex = startx;
		 			gdk_draw_line (pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 		}
			}
			
		} else if ( (type & ORNAMENT_REG) && (lpBoxInf[i].ornament) ) {	
		 	x = hotspot[i].drawx;		
		 	y = hotspot[i].drawy;
		 	box_width = hotspot[i].width;
		 	box_height =  hotspot[i].len*2+1;
		 	for (j=0; j<hotspot[i].cnt; j++, x+=nStepX, y+=nStepY) {	
		 		int		startx, starty;
				if (group == i)		
				 	SetPenColor(gc,
						hotspot[i].red, hotspot[i].green, hotspot[i].blue);	
		 		else		
					SetPenColor(gc, 0xc000, 0xc000, 0xc000);	
		 		startx = x - nOffsetX;	
		 		starty = y - nOffsetY; 
		 		gdk_draw_rectangle(pixmap, gc, TRUE, startx, starty,	
		 								box_width, box_height);
		 		
				if (group == i)		
				 	SetPenColor(gc, 0, 0, 0);				
			 	else		
		 			SetPenColor(gc, 0xc000, 0xc000, 0xc000);	

		 		if (lpBoxInf[i].ornament == 1) {		
		 			int		linex, liney;
		 			linex = startx + box_width + 3;
		 			liney = starty + box_height/2;
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+5, liney);
		 			
		 			linex = startx;
		 			gdk_draw_line (pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 		} else if(lpBoxInf[i].ornament == 2) {	
		 			int		linex, liney;
		 			linex = startx + box_width + 3;
		 			liney = starty + box_height/3;
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+5, liney);
		 			linex = startx;
		 			gdk_draw_line (pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 			
		 			linex = startx + box_width + 3;
		 			liney += box_height/3 + 1;
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (pixmap, gc, linex, liney, linex+5, liney);
		 			linex = startx;
		 			gdk_draw_line (pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 		}
			}
			
		} else {
			if (group == i)		
			 	SetPenColor(gc,
					hotspot[i].red, hotspot[i].green, hotspot[i].blue);	
		 	else		
		 		SetPenColor(gc, 0xc000, 0xc000, 0xc000);	
		 	
		 	x = hotspot[i].drawx;		
		 	y = hotspot[i].drawy;
		 	box_width = hotspot[i].width;
		 	box_height = (!strcmp(GetModelName(), "BJF850"))?
							hotspot[i].len*2-1 : hotspot[i].len*2;
		 	for (j=0; j<hotspot[i].cnt; j++, x+=nStepX, y+=nStepY) {	
		 		int		startx, starty;
		 		startx = x - nOffsetX;	
		 		starty = y - nOffsetY; 
		 		gdk_draw_rectangle(pixmap, gc, TRUE, startx, starty,	
		 								box_width, box_height);
		 	}
		}
	}

	
	
	
	for (i=0; i<kindcnt; i++) {		
		if (i == group) 		
			SetPenColor(gc, 0xffff, 0x0000, 0x0000);	
		else 		
			SetPenColor(gc, 0xc000, 0xc000, 0xc000);	
		
		x = hotspot[i].selbox_x;
		y = hotspot[i].selbox_y;
		if (hotspot[i].stepdir) 	
			y += hotspot[i].step*(lpCtrlItem[i].nMax - items[i]);
		else			
			x += hotspot[i].step*(lpCtrlItem[i].nMax + items[i]);
		
		gdk_draw_rectangle(pixmap, gc, FALSE, x, y,	 		
							hotspot[i].selbox_width, hotspot[i].selbox_height);
	}
	
	
	
	
	drawarea
		= LookupWidget(GTK_WIDGET(regi_dialog), GetRegiDrawingName(nPageNum));
	gdk_window_get_size(drawarea->window, &width, &height);
	update_rect.x      = 0;			
	update_rect.y      = 0;
	update_rect.width  = width;
	update_rect.height = height;
	gtk_widget_draw(drawarea, &update_rect);		
	
	
	gdk_gc_destroy(gc);			
}



void MakeHotSpotTable(
	short page,					
	GtkWidget *dialog)          
{
	int			i, draw_width, draw_height, index;
	GtkWidget	*drawarea;		
	char		*model_name;	
	short		frame_width, frame_height;		
	
	
	model_name = GetModelName();		
	index = -1;
	for (i=0; i < sizeof(RegiInfo)/sizeof(REGINFO); i++) {
		if (!strcmp(RegiInfo[i].ModelName, model_name)) {	
			index = i;			
			break;
		}
	}
	index = (index == -1)? 0 : index;	
	
	
	lpCtrlItem = RegiInfo[index].regi[page].pCtrlItem;		
	lpBJLtbl   = RegiInfo[index].regi[page].pBJLTbl;        
	lpBoxInf   = RegiInfo[index].regi[page].lpBoxInf;       
	nKindCnt   = RegiInfo[index].regi[page].cnt;            
	type	   = RegiInfo[index].regi[page].type;			
	
	
	drawarea = LookupWidget(GTK_WIDGET(dialog), GetRegiDrawingName(nPageNum));	
	gdk_window_get_size(drawarea->window, &draw_width, &draw_height);           
	
	
	for (i=0; i < nKindCnt; i++) {		
		
		HotSpot[i].drawx = HotSpot[i].x = lpBoxInf[i].x;	
		HotSpot[i].drawy = HotSpot[i].y = lpBoxInf[i].y;
		HotSpot[i].width = lpBoxInf[i].width;			
		HotSpot[i].len = lpBoxInf[i].len;               
		HotSpot[i].step = lpBoxInf[i].step;             
		HotSpot[i].stepdir = lpBoxInf[i].stepdir;       
		HotSpot[i].linedir = lpBoxInf[i].linedir;       
		HotSpot[i].repeat = lpBoxInf[i].repeat;
		HotSpot[i].cnt = lpCtrlItem[i].nMax - lpCtrlItem[i].nMin + 1;	

		
		if (type & BIGAREA_TYPE2) {
			frame_width  = PICTURE_WIDTH_BIG2;
			frame_height = PICTURE_HEIGHT_BIG2;
		} else if (type & BIGAREA_TYPE3) {
			frame_width  = PICTURE_WIDTH_BIG3;
			frame_height = PICTURE_HEIGHT_BIG3;
		} else if (type & BIGAREA_TYPE4) {
			frame_width  = PICTURE_WIDTH_BIG4;
			frame_height = PICTURE_HEIGHT_BIG4;
		} else {
			frame_width  = PICTURE_WIDTH;
			frame_height = PICTURE_HEIGHT;
		}
		HotSpot[i].x += (draw_width - frame_width)/2 + lpBoxInf[i].selbox_dx;
		HotSpot[i].y += (draw_height - frame_height)/2 + lpBoxInf[i].selbox_dy;
		
		
		HotSpot[i].selbox_x = HotSpot[i].drawx + lpBoxInf[i].selbox_dx;
		HotSpot[i].selbox_y = HotSpot[i].drawy + lpBoxInf[i].selbox_dy;
		HotSpot[i].selbox_width = lpBoxInf[i].selbox_width;		
		HotSpot[i].selbox_height = lpBoxInf[i].selbox_height;

		
		HotSpot[i].red = lpBoxInf[i].red;			
		HotSpot[i].green = lpBoxInf[i].green;       
		HotSpot[i].blue = lpBoxInf[i].blue;         
	}
}




int UtilRegiDialog(short page)
{

	int			i;
	GtkWidget	*regi_dialog;		
	GtkObject	*adj;               
	short		frame_width, frame_height;		

	
	regi_dialog = LookupWidget(NULL, GetRegiDialogName(page));	

	gtk_widget_realize(regi_dialog);		
	gtk_widget_realize(LookupWidget(regi_dialog, GetRegiDrawingName(page)));  

	gtk_widget_add_events(LookupWidget(regi_dialog, GetRegiDrawingName(page)),
												 GDK_BUTTON_PRESS_MASK);

	
	if (!(strcmp(GetModelName(), "BJF860") & strcmp(GetModelName(), "BJF870"))) {	
		gtk_label_set_text(
			GTK_LABEL(LookupWidget(regi_dialog, "label8")),
				LookupText(g_keytext_list, "regi_bidir"));
		adj = gtk_adjustment_new(0, -5, 5, 1, 0, 0);
		gtk_spin_button_set_adjustment(
			GTK_SPIN_BUTTON(LookupWidget(regi_dialog, "regi_spinbutton6")), 
				GTK_ADJUSTMENT(adj));	
	}

	
	MakeHotSpotTable(page, regi_dialog);			
	InitItemValue();
	
	if (type & BIGAREA_TYPE2) {		
		frame_width  = PICTURE_WIDTH_BIG2;
		frame_height = PICTURE_HEIGHT_BIG2;
	} else if (type & BIGAREA_TYPE3) {
			frame_width  = PICTURE_WIDTH_BIG3;
			frame_height = PICTURE_HEIGHT_BIG3;
	} else if (type & BIGAREA_TYPE4) {
			frame_width  = PICTURE_WIDTH_BIG4;
			frame_height = PICTURE_HEIGHT_BIG4;			
	} else {		
		frame_width  = PICTURE_WIDTH;
		frame_height = PICTURE_HEIGHT;
	}
	regi_pixmap
		= gdk_pixmap_new(regi_dialog->window, frame_width, frame_height, -1);	
		
	DrawTestPrintPage(regi_dialog,
		regi_pixmap, HotSpot, lpCtrlItem, ItemValue, 0, nKindCnt);
	
	
	for(i=0; i < nKindCnt; i++) {
		gtk_spin_button_set_value(
			GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(regi_dialog),
			lpCtrlItem[i].CtrlName)),ItemValue[i]);
	}
	


	gtk_widget_show(regi_dialog);	
	gtk_window_set_transient_for(
		GTK_WINDOW(regi_dialog), GTK_WINDOW(UI_DIALOG(g_main_window)->window));

	gtk_main();						

	gdk_pixmap_unref(regi_pixmap);		
	
	if(result != ID_OK)
	  return(ID_CANCEL);

	return(ID_OK);
}




gboolean on_regi_dialog_delete_event(
	GtkWidget *widget, GdkEvent *event, gpointer user_data)
{

	result = ID_CANCEL;

	gtk_widget_hide(GTK_WIDGET(widget));	
	gtk_main_quit();
	
	return TRUE;
}

// 2007/08/09
gboolean on_regi_dialog_delete_event_no_destroy(
	GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	result = ID_CANCEL;
	return TRUE;
}


void on_regi_dialog_destroy(GtkObject *object, gpointer user_data)
{
  gtk_main_quit();
}




gboolean on_regi_drawingarea_button_press_event(
	GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
	int		xPos, yPos, hit, i, j, current;
	short	items[REGI_EDITMAX];	
	GtkWidget	*dialog;
	
	xPos = event->x;		
	yPos = event->y;
	hit = FALSE;

	current = 0;
	for (i=0; i<nKindCnt && !hit; i++) {	
		if (HotSpot[i].stepdir) {		
			if(HotSpot[i].x <= xPos
			   && xPos <= HotSpot[i].x + HotSpot[i].selbox_width) {	
				for(j=0; j<HotSpot[i].cnt; j++) {	
					if(HotSpot[i].y + HotSpot[i].step*j <= yPos &&
					   yPos <= (HotSpot[i].y + HotSpot[i].step*j
											 + HotSpot[i].selbox_height))
					{
						hit = TRUE;			
						current= i;		
						gtk_spin_button_set_value(
							GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(widget),
								lpCtrlItem[i].CtrlName)),
									lpCtrlItem[i].nMax - j);	
						break;
					}
				}
			}
		} else {		
			if (HotSpot[i].y <=yPos
			 && yPos<=(HotSpot[i].y + HotSpot[i].selbox_height)) {
				for(j=0; j<HotSpot[i].cnt; j++) {
					if ((HotSpot[i].x + HotSpot[i].step*j)<=xPos
					  && xPos<=(HotSpot[i].x + HotSpot[i].step*j
											 + HotSpot[i].selbox_width))
					{
						hit = TRUE;
						current = i;
						gtk_spin_button_set_value(
							GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(widget),
								lpCtrlItem[i].CtrlName)),
									j + lpCtrlItem[i].nMin);
						break;
					}
				}
			}
		}
	}
	if (!hit)			
		return FALSE;			
	
	
	for (i=0; i<nKindCnt; i++)
		items[i] = gtk_spin_button_get_value_as_int(
			GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(widget),
				lpCtrlItem[i].CtrlName)));

	
	dialog = LookupWidget(GTK_WIDGET(widget), GetRegiDialogName(nPageNum));	
	DrawTestPrintPage(dialog, regi_pixmap,
		HotSpot, lpCtrlItem, items, current, nKindCnt);
	
	return FALSE;
}




gboolean on_regi_drawingarea_expose_event(
	GtkWidget *widget, GdkEventExpose *event, gpointer user_data)
{
	int	width, height, pix_width, pix_height;
	
	
	gdk_window_get_size(widget->window, &width, &height);	
	gdk_window_get_size(regi_pixmap, &pix_width, &pix_height);	
	
	gdk_draw_pixmap(widget->window,									
					widget->style->fg_gc[GTK_WIDGET_STATE(widget)],	
					regi_pixmap,                                    
					event->area.x-(width - pix_width)/2,            
					event->area.y-(height - pix_height)/2,          
					event->area.x,                                  
					event->area.y,                                  
					event->area.width, event->area.height);         
	
	return FALSE;
}




void on_regi_spinbutton_changed(GtkSpinButton *spinbutton, gpointer user_data)
{
	int		current, i;
	short	items[REGI_EDITMAX];
	GtkWidget	*dialog;
	
	current = getnum(user_data);
	dialog = LookupWidget(GTK_WIDGET(spinbutton), GetRegiDialogName(nPageNum));
	
	for (i=0; i<nKindCnt; i++)
		items[i] = gtk_spin_button_get_value_as_int(
			GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(spinbutton),
				lpCtrlItem[i].CtrlName)));

	DrawTestPrintPage(dialog, regi_pixmap, HotSpot, lpCtrlItem,
		items, current, nKindCnt);
}




gboolean on_regi_spinbutton_focus_in_event(
	GtkWidget *widget, GdkEventFocus *event, gpointer user_data)
{
	GtkWidget	*dialog;
	int			current, i;
	short	items[REGI_EDITMAX];
	
	current = getnum(user_data);
	dialog = LookupWidget(GTK_WIDGET(widget), GetRegiDialogName(nPageNum));
	
	for (i=0; i<nKindCnt; i++)
		items[i] = gtk_spin_button_get_value_as_int(
			GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(widget),
				lpCtrlItem[i].CtrlName)));

	DrawTestPrintPage(dialog, regi_pixmap, HotSpot, lpCtrlItem,
		items, current, nKindCnt);
	
	return FALSE;
}




int getnum(char *ptr)
{
	char num_buf[32];
	int num_size = 0;

	while(*ptr != '\0'){
		if( *ptr >= 0x30 && *ptr <= 0x39){
    		num_size++;
			break;
		}
		ptr++;
	}

	if( num_size == 0 )
		return 0;

	while( ptr[num_size] != '\0' ){
		if( ptr[num_size] < 0x30 || ptr[num_size] > 0x39 )
			break;
		num_size++;
	}
	if( num_size > 31 )
		num_size = 31;

	memset(num_buf, 0, 32);
	strncpy(num_buf, ptr, num_size);

	return (atoi(num_buf));
}


void
on_regi_cancel_button_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

	result = ID_CANCEL;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	gtk_main_quit();

}

void on_regi_ok_button_clicked(GtkButton *button, gpointer user_data)
{
	int	i;
	
	result = ID_OK;

	for (i=0; i<nKindCnt; i++)
		ItemValue[i] = gtk_spin_button_get_value_as_int(
			GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(button),
				lpCtrlItem[i].CtrlName)));
	regi_flag++;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	gtk_main_quit();
}


static void cleaning_set_default(GtkWidget *widget)
{

	GtkWidget	*radio_button;

	radio_button
	  = LookupWidget(GTK_WIDGET(widget), "cleaning_radiobutton1");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button), TRUE);	
	radio_button
	  = LookupWidget(GTK_WIDGET(widget), "cleaning_radiobutton2");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button), FALSE);	
	radio_button
	  = LookupWidget(GTK_WIDGET(widget), "cleaning_radiobutton3");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button), FALSE);	
}	


gboolean on_cleaning_dialog_delete_event
(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{

	result = ID_CANCEL;			

	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
		
	return TRUE;
}


void on_cleaning_dialog_destroy(GtkObject *object, gpointer user_data)
{
	gtk_main_quit();			
}




void on_cleaning_execute_button_clicked(GtkButton *button, gpointer user_data)
{
	result = ID_OK;
	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}



void on_cleaning_cancel_button_clicked(GtkButton *button, gpointer user_data)
{
	
	result = ID_CANCEL;			

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}


void on_cleaning_radiobutton_toggled(
	GtkToggleButton *togglebutton, gpointer user_data)
{
	if (GTK_TOGGLE_BUTTON(togglebutton)->active)	
		head_type = getnum(user_data);		
}


static void refreshing_set_default(GtkWidget *widget)
{

	GtkWidget	*radio_button;

	radio_button
	  = LookupWidget(GTK_WIDGET(widget), "refreshing_radiobutton1");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button), TRUE);	
	radio_button
	  = LookupWidget(GTK_WIDGET(widget), "refreshing_radiobutton2");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button), FALSE);	
	radio_button
	  = LookupWidget(GTK_WIDGET(widget), "refreshing_radiobutton3");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button), FALSE);	

	refresh_head_type = 0;
}


gboolean
on_refreshing_dialog_delete_event      (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{

	result = ID_CANCEL;			

	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
		
	return TRUE;

}


void
on_refreshing_dialog_destroy           (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();		
}


void
on_refreshing_execute_button_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	result = ID_OK;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			

}



void
on_refreshing_cancel_button_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

	result = ID_CANCEL;			

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			

}



void
on_refreshing_radiobutton_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if (GTK_TOGGLE_BUTTON(togglebutton)->active)	
		refresh_head_type = getnum(user_data);
}


static void autopower_set_default(void)
{
	current_poweron_index = 0;
	current_poweroff_index = 0;
	poweron_index = 0;
	poweroff_index = 0;
}

gboolean on_autopower_dialog_delete_event
(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	result = ID_CANCEL;
	
	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
	autopower_set_default();
	
	return TRUE;
}

void on_autopower_dialog_destroy(GtkObject *object, gpointer user_data)
{
	gtk_main_quit();			
}

void on_autopower_send_button_clicked(GtkButton *button, gpointer user_data)
{
	GtkWidget	*power_on_combo;		
	GtkWidget	*power_off_combo;		


	result = ID_OK;

	power_on_combo = LookupWidget(GTK_WIDGET(button), "autopower_combo1");	
	power_off_combo = LookupWidget(GTK_WIDGET(button), "autopower_combo2");	

	/* Ver.2.80 */
	power_on_mode = gtk_combo_box_get_active_text(GTK_COMBO_BOX(power_on_combo));
	power_off_mode = gtk_combo_box_get_active_text(GTK_COMBO_BOX(power_off_combo));

	current_poweron_index = GetAutoPowerIndex(AutoPowerOnKey, 2, power_on_mode);
	current_poweroff_index = GetAutoPowerIndex(AutoPowerOffKey, 6, power_off_mode);

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}

void on_autopower_cancel_button_clicked(GtkButton *button, gpointer user_data)
{
	result = ID_CANCEL;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
	autopower_set_default();
}



static void drylevel_set_default(GtkWidget *widget)
{
 
	GtkWidget	*radio_button = NULL;
	char		*model_name = GetModelName();
   
	if( !strcmp(model_name,"BJF900") || !strcmp(model_name,"BJF9000") || 
		!strcmp(model_name,"PIXUS950I") || !strcmp(model_name,"PIXUS990I") ||
		!strcmp(model_name, "PIXUSIP8600") ){
		radio_button = LookupWidget(GTK_WIDGET(widget),
									"drylevel3_radiobutton1");
	
	}else{
		radio_button =  LookupWidget(GTK_WIDGET(widget),
									"drylevel5_radiobutton3");
	}
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button), TRUE);  

	if( config_flag & SETCONFIG_ABRASION ){
		GtkWidget *check_button = NULL;
		if( config_flag & SETCONFIG_DRY_3 )
			check_button = LookupWidget(
						GTK_WIDGET(widget), "drylevel3_abrasion_checkbutton");
		else if( config_flag & SETCONFIG_DRY_5 )
			check_button =  LookupWidget(
						GTK_WIDGET(widget), "drylevel5_abrasion_checkbutton");
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button), FALSE); 
	}

	if( config_flag & SETCONFIG_MANHEAD ){
		GtkWidget *check_button = NULL;
		if( config_flag & SETCONFIG_DRY_3 )
			check_button = LookupWidget(
					   GTK_WIDGET(widget), "drylevel3_manhead_checkbutton");
		else if( config_flag & SETCONFIG_DRY_5 )
			check_button = LookupWidget(
					   GTK_WIDGET(widget), "drylevel5_manhead_checkbutton");
	
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button), FALSE); 
	}
}


gboolean
on_drylevel_dialog_delete_event
(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{

	result = ID_CANCEL;

	drylevel_set_default(widget);
	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
		
//	papergap_mode = 0;
//	manual_head_mode = 0;
//	drylevel_value = 0;

	return TRUE;

}

void on_drylevel_dialog_destroy(GtkObject *object, gpointer user_data)
{
	gtk_main_quit();			
}


void on_drylevel_send_button_clicked(GtkButton *button, gpointer user_data)
{

	GtkWidget* check_button = NULL;

	result = ID_OK;

	if( config_flag & SETCONFIG_ABRASION ){
		if( config_flag & SETCONFIG_DRY_3 )
			check_button = LookupWidget(
						GTK_WIDGET(button), "drylevel3_abrasion_checkbutton");
		else if( config_flag & SETCONFIG_DRY_5 )
			check_button =  LookupWidget(
						GTK_WIDGET(button), "drylevel5_abrasion_checkbutton");
		current_papergap_mode = GTK_TOGGLE_BUTTON(check_button)->active;
	}
	if( config_flag & SETCONFIG_MANHEAD ){
		if( config_flag & SETCONFIG_DRY_3 )
			check_button = LookupWidget(
						GTK_WIDGET(button), "drylevel3_manhead_checkbutton");
		else if( config_flag & SETCONFIG_DRY_5 )
			check_button =  LookupWidget(
						GTK_WIDGET(button), "drylevel5_manhead_checkbutton");
		current_manual_head_mode = GTK_TOGGLE_BUTTON(check_button)->active;
	}

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			

}



void on_drylevel_cancel_button_clicked
				(GtkButton *button, gpointer user_data)
{

	GtkWidget	*window = GetTopWidget(GTK_WIDGET(button));

	result = ID_CANCEL;

	drylevel_set_default(window);
	gtk_widget_hide(window);	
	gtk_main_quit();			
//	papergap_mode = 0;
//	manual_head_mode = 0;
//	drylevel_value = 0;
}



void on_drylevel_std_button_clicked(GtkButton *button, gpointer user_data)
{
	drylevel_set_default(GetTopWidget(GTK_WIDGET(button)));
}

void on_drylevel_radiobutton_toggled(GtkToggleButton *togglebutton,
									 gpointer user_data)
{

	if (GTK_TOGGLE_BUTTON(togglebutton)->active)
	  drylevel_value = getnum(user_data);

}




/*****************************************************************
 *
 *	 Quiet Mode Signal Handler 
 *			    Added '01.11.05
 *****************************************************************/
void init_quiet_settings( void )
{
	current_quiet_mode = 0;
	quiet_mode = 0;
}

static void quiet_set_default(GtkWidget *widget)
{

	GtkWidget *quiet_button = 
			LookupWidget(GTK_WIDGET(widget), "quiet_checkbutton");

	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(quiet_button), FALSE);  
}


void on_quiet_dialog_destroy(GtkObject *object, gpointer user_data)
{
	gtk_main_quit();			
}


gboolean
on_quiet_dialog_delete_event 
(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{

	
	result = ID_CANCEL;

	quiet_set_default(GTK_WIDGET(widget));
	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
	return TRUE;

//	quiet_mode = 0;
}




void on_quiet_send_button_clicked(GtkButton *button, gpointer user_data)
{

	GtkWidget	*quiet_button;

	result = ID_OK;

	quiet_button = LookupWidget(GTK_WIDGET(button), "quiet_checkbutton");	
	current_quiet_mode = GTK_TOGGLE_BUTTON(quiet_button)->active;


	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}




void on_quiet_cancel_button_clicked
				(GtkButton *button, gpointer user_data)
{

	GtkWidget *window = GetTopWidget(GTK_WIDGET(button));

	result = ID_CANCEL;

	quiet_set_default(window);
	gtk_widget_hide(window);	
	gtk_main_quit();			
//	quiet_mode = 0;

}



void on_quiet_std_button_clicked(GtkButton *button, gpointer user_data)
{
		
	quiet_set_default(GetTopWidget(GTK_WIDGET(button)));

}






/*****************************************************************
 *
 *	 Ink Warning Signal Handler 
 *			    Added '01.11.16
 *****************************************************************/

//  2006/11/10
void init_inkwarning_settings( void )
{
	current_warning_mode = 1;
	warning_mode = 1;
}

static void ink_warning_set_default(GtkWidget *widget)
{

	GtkWidget *warning_button = 
			LookupWidget(widget, "ink_warning_checkbutton");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(warning_button), TRUE);
	
}


void on_ink_warning_dialog_destroy(GtkObject *object, gpointer user_data)
{
	gtk_main_quit();			
}


gboolean
on_ink_warning_dialog_delete_event 
(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{

	result = ID_CANCEL;


	ink_warning_set_default(widget);
	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
//	warning_mode = 1;
	return TRUE;

}




void on_ink_warning_send_button_clicked(GtkButton *button, gpointer user_data)
{

	GtkWidget	*warning_button;

	result = ID_OK;

	warning_button = LookupWidget(GTK_WIDGET(button),
								  "ink_warning_checkbutton");	
	current_warning_mode = GTK_TOGGLE_BUTTON(warning_button)->active;


	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}



void on_ink_warning_cancel_button_clicked
				(GtkButton *button, gpointer user_data)
{

	GtkWidget *window = GetTopWidget(GTK_WIDGET(button));
	result = ID_CANCEL;

	ink_warning_set_default(window);
	gtk_widget_hide(window);	
	gtk_main_quit();			
//	warning_mode = 1;
}



void on_ink_warning_std_button_clicked(GtkButton *button, gpointer user_data)
{
	
	ink_warning_set_default(GetTopWidget(GTK_WIDGET(button)));
}




/*****************************************************************
 *
 *	 Ink Reset Signal Handler 
 *			    Added '01.11.16
 *****************************************************************/


void
on_ink_reset_button_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	GtkWidget*	window;
	GtkWidget*	black_button;
	GtkWidget*	color_button;
	GtkWidget*	excute_button;
	
	window = GetTopWidget(GTK_WIDGET(togglebutton));
	excute_button = LookupWidget(window, "ink_reset_excute_button");

	black_button = LookupWidget(window, "black_reset_checkbutton");
	color_button = LookupWidget(window, "color_reset_checkbutton");
	
	if( !(GTK_TOGGLE_BUTTON(black_button)->active) &&
		!(GTK_TOGGLE_BUTTON(color_button)->active) ){
		gtk_widget_grab_default( LookupWidget(window,
									"ink_reset_cancel_button"));
		gtk_widget_set_sensitive(excute_button, FALSE);
	}
	else{
		gtk_widget_set_sensitive(excute_button, TRUE);
		gtk_widget_grab_default(excute_button);
  }

}



void on_ink_reset_dialog_destroy(GtkObject *object, gpointer user_data)
{
	gtk_main_quit();			
}


gboolean
on_ink_reset_dialog_delete_event 
(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{

	result = ID_CANCEL;

		GtkWidget	*black_button;
		GtkWidget	*color_button;

		black_button = LookupWidget(GTK_WIDGET(widget),
									"black_reset_checkbutton");	
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(black_button), FALSE);  
		color_button = LookupWidget(GTK_WIDGET(widget),
									"color_reset_checkbutton");
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(color_button), FALSE);  
		gtk_widget_hide(GTK_WIDGET(widget));
		gtk_main_quit();
	return TRUE;

}



void on_ink_reset_execute_button_clicked(GtkButton *button, gpointer user_data)
{

	GtkWidget	*black_button;
	GtkWidget	*color_button;
	
	result = ID_OK;

	black_button = LookupWidget(GTK_WIDGET(button),
								"black_reset_checkbutton");	
	black_reset= GTK_TOGGLE_BUTTON(black_button)->active;
	color_button = LookupWidget(GTK_WIDGET(button),
								"color_reset_checkbutton");	
	color_reset = GTK_TOGGLE_BUTTON(color_button)->active;

	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(black_button), FALSE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(color_button), FALSE);
	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
	gtk_main_quit();			
}




void on_ink_reset_cancel_button_clicked
				(GtkButton *button, gpointer user_data)
{
	result = ID_CANCEL;

		GtkWidget	*black_button;
		GtkWidget	*color_button;

		black_button = LookupWidget(GTK_WIDGET(button),
									"black_reset_checkbutton");	
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(black_button), FALSE);  
		color_button = LookupWidget(GTK_WIDGET(button),
									"color_reset_checkbutton");
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(color_button), FALSE);  
		gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));	
		gtk_main_quit();			

}


int UtilInkCartrigeDialog()
{
	GtkWidget*	dialog;
//	GtkWidget*	entry;
	GtkWidget*	combo;
	GtkWidget*	label;
	gchar* 		msg;
	int   		index_num = InkCartridgeInfo.index_num;

	dialog = LookupWidget(NULL, "ink_cartridge_dialog");
	gtk_widget_realize(dialog);

	cartridge_cur_index = nValueToIndex(InkCartridgeInfo.nValue, index_num, 
								GetCurrentnValue(CNCL_INKCARTRIDGESETTINGS) );

	combo = LookupWidget(dialog, "ink_cartridge_dialog_combo");
	
	/* Ver.2.80 */
	//SetComboBox(combo, InkCartridgeInfo.type, index_num, cartridge_cur_index);
	if( DisableSignal() )
	{
		SetComboBoxItems(combo, InkCartridgeInfo.type, index_num, cartridge_cur_index);
	}
	EnableSignal();

	msg = LookupText(g_keytext_list, InkCartridgeInfo.info[cartridge_cur_index]);
	label = LookupWidget(dialog, "ink_cartridge_dialog_label3");
	gtk_label_set_text(GTK_LABEL(label), msg);

	gtk_widget_show(dialog);
	gtk_window_set_transient_for(GTK_WINDOW(dialog),
		GTK_WINDOW(UI_DIALOG(g_main_window)->window));

	/* Ver.2.80 */
	//gtk_widget_grab_focus(entry);
//	gtk_widget_grab_focus(combo);

	gtk_main();

	if(result != ID_OK)
	  return ID_CANCEL;

	return ID_OK;
}

gboolean
on_ink_cartridge_dialog_delete_event   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	result = ID_CANCEL;
	
	gtk_widget_hide(GTK_WIDGET(widget));
	gtk_main_quit();
	cartridge_cur_index = cartridge_index;
	return TRUE;
}

void
on_ink_cartridge_dialog_destroy        (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


/* Ver.2.80 */
void
on_ink_cartridge_dialog_combo_changed  (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	GtkWidget*	label;
	char*		type;
	gchar* 		msg;

	if( DisableSignal() )
	{
		type = (char*)gtk_combo_box_get_active_text( combobox );
	
		cartridge_cur_index = KeyToIndex(InkCartridgeInfo.type, 
											InkCartridgeInfo.index_num, type);
	
		msg = LookupText(g_keytext_list, InkCartridgeInfo.info[cartridge_cur_index]);
		label = LookupWidget(GTK_WIDGET(combobox), "ink_cartridge_dialog_label3");
		gtk_label_set_text(GTK_LABEL(label), msg);
	}
	EnableSignal();
}


void
on_ink_cartridge_dialog_ok_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*combo;
  	char		*type;

	result = ID_OK;

	combo = LookupWidget(GTK_WIDGET(button), "ink_cartridge_dialog_combo");
	type = (char*)gtk_combo_box_get_active_text( GTK_COMBO_BOX(combo) );	/* Ver.2.80 */

	cartridge_cur_index = KeyToIndex(InkCartridgeInfo.type, 
										InkCartridgeInfo.index_num, type);

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	gtk_main_quit();			
	cartridge_index = cartridge_cur_index;
}

void
on_ink_cartridge_dialog_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	result = ID_CANCEL;

	gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	gtk_main_quit();

	cartridge_cur_index = cartridge_index;
}


void
on_ink_cartridge_dialog_defaults_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget*	combo;
	GtkWidget*	label;
	gchar* 		msg;

	cartridge_cur_index = InkCartridgeInfo.index_default;
	combo = LookupWidget(GTK_WIDGET(button), "ink_cartridge_dialog_combo");

	/* Ver.2.80 */
	if( DisableSignal() )
	{
		SetComboBoxItems(combo, InkCartridgeInfo.type, InkCartridgeInfo.index_num, cartridge_cur_index);
	}
	EnableSignal();

	msg = LookupText(g_keytext_list, InkCartridgeInfo.info[cartridge_cur_index]);
	label = LookupWidget(GTK_WIDGET(button), "ink_cartridge_dialog_label3");
	gtk_label_set_text(GTK_LABEL(label), msg);
}

static void SetDryLevel(void)
{

	GtkWidget*	drylevel_dialog = NULL;
	char 		buf[128];
	char		*p=buf;
	char 		temp[32];
	char		*model_name;
	GtkWidget	*button=NULL;
	GtkWidget*	send_button=NULL;
	int i;
	int total_bytes = 0;
	int temp_bytes = 0;
	int cmd_bytes = 0;

	model_name = GetModelName();

	for (i=0; i < sizeof(SetConfigInfo)/sizeof(SETCONFIGINFO); i++) {		
		if (!strcmp(SetConfigInfo[i].ModelName, model_name)) {	
			config_flag = SetConfigInfo[i].ConfigFlag;
			break;
		}
	}

	if( !strcmp(model_name, "BJF900") || !strcmp(model_name, "BJF9000") || 
		!strcmp(model_name,"PIXUS950I") || !strcmp(model_name,"PIXUS990I") ||
		!strcmp(model_name, "PIXUSIP8600") ){

		drylevel_dialog = LookupWidget(NULL, "drylevel3_dialog");
		button = LookupWidget(drylevel_dialog, 
							  DryLevel3NameList[drylevel_value]);
		send_button = LookupWidget(drylevel_dialog, "drylevel3_send_button");
	}else{
		drylevel_dialog = LookupWidget(NULL, "drylevel5_dialog");
		button = LookupWidget(drylevel_dialog, 
							  DryLevel5NameList[drylevel_value]);
		send_button = LookupWidget(drylevel_dialog, "drylevel5_send_button");
	}

	/* Manual Head Alignment */
	if( !(config_flag&SETCONFIG_MANHEAD) ){
		if( config_flag & SETCONFIG_DRY_3 )
			gtk_widget_hide(
			  LookupWidget(drylevel_dialog, "drylevel3_manhead_checkbutton"));
		else if( config_flag & SETCONFIG_DRY_5 )
		  gtk_widget_hide(
			  LookupWidget(drylevel_dialog, "drylevel5_manhead_checkbutton"));
	}else{
		if( manual_head_mode && (config_flag&SETCONFIG_DRY_3) ){
			gtk_toggle_button_set_active(
				GTK_TOGGLE_BUTTON(LookupWidget(drylevel_dialog, 
					   "drylevel3_manhead_checkbutton")), TRUE);
		}
		else if( manual_head_mode && (config_flag&SETCONFIG_DRY_5) ){
			gtk_toggle_button_set_active(
				GTK_TOGGLE_BUTTON(LookupWidget(drylevel_dialog, 
					   "drylevel5_manhead_checkbutton")), TRUE);
		}
	}

	/* Abrasion Prevention  */
	if( !(config_flag&SETCONFIG_ABRASION) ){
		if( config_flag & SETCONFIG_DRY_3 )
			gtk_widget_hide(
			  LookupWidget(drylevel_dialog, "drylevel3_abrasion_checkbutton"));
		else if( config_flag & SETCONFIG_DRY_5 )
		  gtk_widget_hide(
			  LookupWidget(drylevel_dialog, "drylevel5_abrasion_checkbutton"));
	}else{
		if( papergap_mode &&(config_flag&SETCONFIG_DRY_3) ){
			gtk_toggle_button_set_active(
				GTK_TOGGLE_BUTTON(LookupWidget(drylevel_dialog, 
					   "drylevel3_abrasion_checkbutton")), TRUE);
		}
		else if( papergap_mode && (config_flag&SETCONFIG_DRY_5) ){
			gtk_toggle_button_set_active(
				GTK_TOGGLE_BUTTON(LookupWidget(drylevel_dialog, 
					   "drylevel5_abrasion_checkbutton")), TRUE);
		}
	}
	
	gtk_widget_realize(drylevel_dialog);
	gtk_widget_show(drylevel_dialog);
	gtk_window_set_transient_for(GTK_WINDOW(drylevel_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
	gtk_widget_grab_focus(send_button);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);	
	gtk_signal_emit_by_name(GTK_OBJECT(button), "toggled", NULL);

	gtk_main();
	
	if(result != ID_OK)
	  return;
	
	 	
	if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_9"),
					  g_window_title, MB_ICON_EXCLAMATION | MB_OK | 
					  MB_CANCEL)==ID_CANCEL){
//		papergap_mode = 0;
//		manual_head_mode = 0;
//		drylevel_value = 0;
		return ;
	}

	// preserve setting
	papergap_mode = current_papergap_mode;
	manual_head_mode = current_manual_head_mode;
	drylevel_value = current_drylevel_value;
	
		
	memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
	memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
	memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;
	cmd_bytes = sprintf(temp, BJLDRYLEVEL, drylevel_value);
	memcpy(p, temp, cmd_bytes); p+=cmd_bytes;

	if( config_flag & SETCONFIG_ABRASION ){
		temp_bytes = snprintf(temp, 31, BJLPAPERGAP, 
							  PaperGapString[papergap_mode]);
		memcpy(p, temp, temp_bytes); p+=temp_bytes;
	}
	memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
	*p = 0x00;
	total_bytes = BJLLEN + BJLSTARTLEN + BJLCTRLMODELEN 
	  + cmd_bytes + temp_bytes + BJLENDLEN+1;
	
	PutPrintData(buf, total_bytes);
}




void UtilCleaning(LPUIDB uidb)
{
	char		buf[128];			
	char		*p = buf;           
	char		*model_name;		
	GtkWidget*	cleaning_dialog;	
	int index = -1;

	if (g_socketname == NULL)			
		return ;                        

	model_name = GetModelName();

	if( !strcmp(model_name,"BJS600") || !strcmp(model_name,"BJS630")
		|| !strcmp(model_name,"BJS6300") || !strcmp(model_name, "BJS500")
		|| !strcmp(model_name,"BJS300") || !strcmp(model_name, "PIXUS550I")
		|| !strcmp(model_name, "PIXUS850I")
		|| !strcmp(model_name,"PIXUS560I") || !strcmp(model_name,"PIXUS860I")
		|| !strcmp(model_name,"PIXUS990I") ){
		
		GtkWidget *excute_button;
		GtkWidget *radio_button;
		int i;
		
		cleaning_dialog = LookupWidget(NULL, "cleaning_dialog");	
		gtk_widget_realize(cleaning_dialog);			
		cleaning_set_default(cleaning_dialog);

		for (i=0; i < sizeof(InkMsgInfo)/sizeof(INKMSGINFO); i++) {
			if (!strcmp(InkMsgInfo[i].ModelName, model_name)) {	
			index = i;			
			break;
			}
		}
		index = (index == -1)? 0 : index;	

		/* All Ink */
		radio_button = 
		  LookupWidget(cleaning_dialog, "cleaning_radiobutton1");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[0]));

		/* Black Ink */
		radio_button = 
		  LookupWidget(cleaning_dialog, "cleaning_radiobutton2");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[1]));

		/* Color Ink */
		radio_button = 
			LookupWidget(cleaning_dialog, "cleaning_radiobutton3");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[2]));

		if( InkMsgInfo[index].GroupFlag )
			gtk_label_set_text(
				GTK_LABEL(LookupWidget(cleaning_dialog, "cleaning_label1")),
				LookupText(g_keytext_list, "utility_message_33"));

		gtk_widget_show(cleaning_dialog);			
		gtk_window_set_transient_for(GTK_WINDOW(cleaning_dialog),
			GTK_WINDOW(UI_DIALOG(g_main_window)->window));

		excute_button = LookupWidget(cleaning_dialog, "cleaning_button1");
		gtk_widget_grab_focus(excute_button);

		gtk_main();									
  		
  		if (result != ID_OK)		
			return ;				
	}
	else if(!strcmp(model_name, "PIXUSIP3100") || 
			!strcmp(model_name, "PIXUSIP4100") ||
			!strcmp(model_name, "PIXUSIP8600") ){
		
		GtkWidget *excute_button;
		GtkWidget *radio_button;
		int i;
		
		cleaning_dialog = LookupWidget(NULL, "cleaning_dialog");	
		gtk_widget_realize(cleaning_dialog);			
		cleaning_set_default(cleaning_dialog);

		for (i=0; i < sizeof(InkMsgInfo)/sizeof(INKMSGINFO); i++) {
			if (!strcmp(InkMsgInfo[i].ModelName, model_name)) {	
			index = i;			
			break;
			}
		}
		index = (index == -1)? 0 : index;	

		gtk_label_set_text(
			GTK_LABEL(LookupWidget(cleaning_dialog, "cleaning_label1")),
			LookupText(g_keytext_list, "utility_message_39"));
		
		gtk_label_set_text(
			GTK_LABEL(LookupWidget(cleaning_dialog, "cleaning_label2")),
			LookupText(g_keytext_list, "utility_message_41"));

		gtk_label_set_text(
			GTK_LABEL(LookupWidget(cleaning_dialog, "cleaning_label3")),
			LookupText(g_keytext_list, "utility_message_43"));

		/* All Ink */
		radio_button = 
		  LookupWidget(cleaning_dialog, "cleaning_radiobutton1");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[0]));

		/* Black Ink */
		radio_button = 
		  LookupWidget(cleaning_dialog, "cleaning_radiobutton2");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[1]));

		/* Color Ink */
		radio_button = 
			LookupWidget(cleaning_dialog, "cleaning_radiobutton3");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[2]));


		gtk_widget_show(cleaning_dialog);			
		gtk_window_set_transient_for(GTK_WINDOW(cleaning_dialog),
			GTK_WINDOW(UI_DIALOG(g_main_window)->window));

		excute_button = LookupWidget(cleaning_dialog, 
									 "cleaning_button1");
		gtk_widget_grab_focus(excute_button);

		gtk_main();									
  		
  		if (result != ID_OK)		
			return ;
	}
	else if(!strcmp(model_name, "IP4200") || 
			!strcmp(model_name, "IP7500") ||
			!strcmp(model_name, "MP500") ){
		
		GtkWidget *excute_button;
		GtkWidget *radio_button;
		int i;
		
		cleaning_dialog = LookupWidget(NULL, "cleaning_dialog");	
		gtk_widget_realize(cleaning_dialog);			
		cleaning_set_default(cleaning_dialog);

		for (i=0; i < sizeof(InkMsgInfo)/sizeof(INKMSGINFO); i++) {
			if (!strcmp(InkMsgInfo[i].ModelName, model_name)) {	
			index = i;			
			break;
			}
		}
		index = (index == -1)? 0 : index;	

		gtk_label_set_text(
			GTK_LABEL(LookupWidget(cleaning_dialog, "cleaning_label1")),
			LookupText(g_keytext_list, "utility_message_39"));
		
		gtk_label_set_text(
			GTK_LABEL(LookupWidget(cleaning_dialog, "cleaning_label2")),
			LookupText(g_keytext_list, "utility_message_41"));

		gtk_label_set_text(
			GTK_LABEL(LookupWidget(cleaning_dialog, "cleaning_label3")),
			LookupText(g_keytext_list, "utility_message_43"));

		/* All Ink */
		radio_button = 
		  LookupWidget(cleaning_dialog, "cleaning_radiobutton1");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[0]));

		/* Black Ink */
		radio_button = 
		  LookupWidget(cleaning_dialog, "cleaning_radiobutton2");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[1]));

		/* Color Ink */
		radio_button = 
			LookupWidget(cleaning_dialog, "cleaning_radiobutton3");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[2]));


		gtk_widget_show(cleaning_dialog);			
		gtk_window_set_transient_for(GTK_WINDOW(cleaning_dialog),
			GTK_WINDOW(UI_DIALOG(g_main_window)->window));

		excute_button = LookupWidget(cleaning_dialog, 
									 "cleaning_button1");
		gtk_widget_grab_focus(excute_button);

		gtk_main();									
  		
  		if (result != ID_OK)		
			return ;
	}
		
	
	if (!strcmp(model_name, "BJF850") | !strcmp(model_name, "BJF860") |
					 !strcmp(model_name, "BJF870")) {	
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;           
		memcpy(p, BJLCLEAN1, BJLCLEAN1LEN); p+=BJLCLEAN1LEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;                 
		*p = 0x00;
		PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLCLEAN1LEN+BJLENDLEN+1);

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

	} else if (!strcmp(model_name, "BJF360")) {
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, BJLCLEAN3, BJLCLEAN3LEN); p+=BJLCLEAN3LEN;        
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
		*p = 0x00;
		PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLCLEAN3LEN+BJLENDLEN+1);
	} else if( !strcmp( model_name, "BJF900") || !strcmp(model_name, "BJF9000")
			|| !strcmp(model_name, "PIXUS950I") || !strcmp(model_name,"I250")
		   || !strcmp(model_name, "I255") ){
		int		n;
		n = SetCurrentTime(p); p+=n;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, BJLCLEAN3, BJLCLEAN3LEN); p+=BJLCLEAN3LEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;        
		*p = 0x00;
		PutPrintData(buf,
			n+BJLLEN+BJLSTARTLEN+BJLCLEAN3LEN+BJLENDLEN+1);
		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

	} else if( !strcmp(model_name, "PIXUSIP3100") || 
			   !strcmp(model_name, "PIXUSIP4100") || 
			   !strcmp(model_name, "PIXUSIP8600") ){
		int		n;
		CLEANCMD* clean_cmd;
		
		if( InkMsgInfo[index].GroupFlag ) 
			clean_cmd = GroupCleanCommand;
		else
			clean_cmd = S600CleanCommand;

		n = SetCurrentTime(p); p+=n;	
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, clean_cmd[head_type].cmd,
			clean_cmd[head_type].len);
		p+=clean_cmd[head_type].len;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
		*p = 0x00;
		PutPrintData(buf,
			n+BJLLEN+BJLSTARTLEN+clean_cmd[head_type].len+BJLENDLEN+1);

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_38"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		UtilNozzleCheck(uidb);

	} else if( !strcmp(model_name, "PIXMAIP1000") || 
			 !strcmp(model_name, "PIXMAIP1500")	){
		int		n;
		n = SetCurrentTime(p); p+=n;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, BJLCLEAN3, BJLCLEAN3LEN); p+=BJLCLEAN3LEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;        
		*p = 0x00;
		PutPrintData(buf,
			n+BJLLEN+BJLSTARTLEN+BJLCLEAN3LEN+BJLENDLEN+1);
		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_38"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		UtilNozzleCheck(uidb);
	} else if( !strcmp(model_name, "IP2200") || 
			 !strcmp(model_name, "IP6600D")	){
		int		n;
		n = SetCurrentTime(p); p+=n;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, BJLCLEAN3, BJLCLEAN3LEN); p+=BJLCLEAN3LEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;        
		*p = 0x00;
		PutPrintData(buf,
			n+BJLLEN+BJLSTARTLEN+BJLCLEAN3LEN+BJLENDLEN+1);
		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_38"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		UtilNozzleCheck(uidb);
	} else if( !strcmp(model_name, "IP4200") || 
			   !strcmp(model_name, "IP7500") ||
			   !strcmp(model_name, "MP500") ){
		int		n;
		CLEANCMD* clean_cmd;
		
		if( InkMsgInfo[index].GroupFlag ) 
			clean_cmd = GroupCleanCommand;
		else
			clean_cmd = S600CleanCommand;

		n = SetCurrentTime(p); p+=n;	
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, clean_cmd[head_type].cmd,
			clean_cmd[head_type].len);
		p+=clean_cmd[head_type].len;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
		*p = 0x00;
		PutPrintData(buf,
			n+BJLLEN+BJLSTARTLEN+clean_cmd[head_type].len+BJLENDLEN+1);

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_38"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		UtilNozzleCheck(uidb);
	}
	else {
		int		n;
		CLEANCMD* clean_cmd;
		
		if( InkMsgInfo[index].GroupFlag ) 
			clean_cmd = GroupCleanCommand;
		else
			clean_cmd = S600CleanCommand;

		n = SetCurrentTime(p); p+=n;	
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, clean_cmd[head_type].cmd,
			clean_cmd[head_type].len);
		p+=clean_cmd[head_type].len;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
		*p = 0x00;
		PutPrintData(buf,
			n+BJLLEN+BJLSTARTLEN+clean_cmd[head_type].len+BJLENDLEN+1);

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
	}
	
}


void UtilRefreshing(LPUIDB uidb)
{
	char		buf[128];
	char		*p = buf;
	char		*model_name;
	char*		msg=NULL;
	int index = -1;
	GtkWidget* refreshing_dialog = NULL;

	if (g_socketname == NULL)			
		return ;                        

	model_name = GetModelName();
	
	if( !strcmp(model_name,"PIXUS550I") || !strcmp(model_name,"PIXUS850I") ||
		!strcmp(model_name,"PIXUS560I") || !strcmp(model_name,"PIXUS860I") ||
		!strcmp(model_name,"PIXUS990I") ){
				
		GtkWidget *excute_button = NULL;
		GtkWidget *radio_button;
		int i;

		refreshing_dialog = LookupWidget(NULL, "refreshing_dialog");
		gtk_widget_realize( refreshing_dialog);
		
		for (i=0; i < sizeof(InkMsgInfo)/sizeof(INKMSGINFO); i++) {
			if (!strcmp(InkMsgInfo[i].ModelName, model_name)) {	
				index = i;			
				break;
			}
		}
		index = (index == -1)? 0 : index;

		/* All Ink */
		radio_button = 
		  LookupWidget(refreshing_dialog, "refreshing_radiobutton1");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[0]));

		/* Black Ink */
		radio_button = 
		  LookupWidget(refreshing_dialog, "refreshing_radiobutton2");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
			   LookupText(g_keytext_list, InkMsgInfo[index].InkName[1]));

		/* Color Ink */
		radio_button = 
		  LookupWidget(refreshing_dialog, "refreshing_radiobutton3");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),
			   LookupText(g_keytext_list, InkMsgInfo[index].InkName[2]));

		if( InkMsgInfo[index].GroupFlag )
			gtk_label_set_text(
			GTK_LABEL(LookupWidget(refreshing_dialog, "refreshing_label1")),
			LookupText(g_keytext_list, "utility_message_34"));


		refreshing_set_default(refreshing_dialog);
		gtk_widget_show(refreshing_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(refreshing_dialog),
			GTK_WINDOW(UI_DIALOG(g_main_window)->window));

		excute_button = 
			LookupWidget(refreshing_dialog, "refreshing_execute_button");
		gtk_widget_grab_focus(excute_button);

		gtk_main();
  		
  		if (result != ID_OK)
			return ;
		
		msg = LookupText(g_keytext_list, 
						 InkMsgInfo[index].RefMsg[refresh_head_type]);

	}
	if( !strcmp(model_name,"PIXUSIP3100") || 
		!strcmp(model_name,"PIXUSIP4100") ||
		!strcmp(model_name,"PIXUSIP8600") ){				

		GtkWidget *excute_button = NULL;
		GtkWidget *radio_button;
		int i;

		refreshing_dialog = LookupWidget(NULL, "refreshing_dialog");
		gtk_widget_realize(refreshing_dialog);
		
		gtk_label_set_text(
			GTK_LABEL(LookupWidget(refreshing_dialog, "refreshing_label1")),
			LookupText(g_keytext_list, "utility_message_40"));

		gtk_label_set_text(
			GTK_LABEL(LookupWidget(refreshing_dialog, "refreshing_label2")),
			LookupText(g_keytext_list, "utility_message_41"));
		
		
		gtk_label_set_text(
			GTK_LABEL(LookupWidget(refreshing_dialog, "refreshing_label3")),
			LookupText(g_keytext_list, "utility_message_42"));
		

		
		for (i=0; i < sizeof(InkMsgInfo)/sizeof(INKMSGINFO); i++) {
			if (!strcmp(InkMsgInfo[i].ModelName, model_name)) {	
				index = i;			
				break;
			}
		}
		index = (index == -1)? 0 : index;

		/* All Ink */
		radio_button = 
		  LookupWidget(refreshing_dialog, "refreshing_radiobutton1");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[0]));

		/* Black Ink */
		radio_button = 
		  LookupWidget(refreshing_dialog, "refreshing_radiobutton2");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
			   LookupText(g_keytext_list, InkMsgInfo[index].InkName[1]));

		/* Color Ink */
		radio_button = 
		  LookupWidget(refreshing_dialog, "refreshing_radiobutton3");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),
			   LookupText(g_keytext_list, InkMsgInfo[index].InkName[2]));

		refreshing_set_default(refreshing_dialog);
		gtk_widget_show(refreshing_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(refreshing_dialog),
			GTK_WINDOW(UI_DIALOG(g_main_window)->window));

		excute_button = 
			LookupWidget(refreshing_dialog, "refreshing_execute_button");
		gtk_widget_grab_focus(excute_button);

		gtk_main();
  		
  		if (result != ID_OK)
			return ;
		
		msg = LookupText(g_keytext_list, 
						 InkMsgInfo[index].RefMsg[refresh_head_type]);

	}
	else if( !strcmp(model_name, "PIXMAIP1000") || 
			 !strcmp(model_name,"PIXMAIP1500") ){
		
		GtkWidget *excute_button = NULL;

		refreshing_dialog = LookupWidget(NULL, "deep_cleaning_dialog");
		gtk_widget_realize(refreshing_dialog);
		gtk_widget_show(refreshing_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(refreshing_dialog),
			GTK_WINDOW(UI_DIALOG(g_main_window)->window));
		excute_button = 
			LookupWidget(refreshing_dialog, "deep_cleaning_execute_button");
		gtk_widget_grab_focus(excute_button);

		gtk_main();
  		
  		if (result != ID_OK)
			return ;
		
		msg = LookupText(g_keytext_list, "utility_message_12");

	}
	else if( !strcmp(model_name, "PIXUS950I") || !strcmp(model_name, "I250")
			|| !strcmp(model_name,"I255") ){

		msg = LookupText(g_keytext_list, "utility_message_22");
	}
	else if( !strcmp(model_name, "IP2200") ||
			 !strcmp(model_name,"IP6600D") ){
		
		GtkWidget *excute_button = NULL;

		refreshing_dialog = LookupWidget(NULL, "deep_cleaning_dialog");
		gtk_widget_realize(refreshing_dialog);
		gtk_widget_show(refreshing_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(refreshing_dialog),
			GTK_WINDOW(UI_DIALOG(g_main_window)->window));
		excute_button = 
			LookupWidget(refreshing_dialog, "deep_cleaning_execute_button");
		gtk_widget_grab_focus(excute_button);

		gtk_main();
  		
  		if (result != ID_OK)
			return ;
		
		msg = LookupText(g_keytext_list, "utility_message_12");

	}
	else if( !strcmp(model_name,"IP4200") ||
			 !strcmp(model_name,"IP7500") ||
			 !strcmp(model_name,"MP500") ){

		GtkWidget *excute_button = NULL;
		GtkWidget *radio_button;
		int i;

		refreshing_dialog = LookupWidget(NULL, "refreshing_dialog");
		gtk_widget_realize(refreshing_dialog);
		
		gtk_label_set_text(
			GTK_LABEL(LookupWidget(refreshing_dialog, "refreshing_label1")),
			LookupText(g_keytext_list, "utility_message_40"));

		gtk_label_set_text(
			GTK_LABEL(LookupWidget(refreshing_dialog, "refreshing_label2")),
			LookupText(g_keytext_list, "utility_message_41"));
		
		
		gtk_label_set_text(
			GTK_LABEL(LookupWidget(refreshing_dialog, "refreshing_label3")),
			LookupText(g_keytext_list, "utility_message_42"));
		

		
		for (i=0; i < sizeof(InkMsgInfo)/sizeof(INKMSGINFO); i++) {
			if (!strcmp(InkMsgInfo[i].ModelName, model_name)) {	
				index = i;			
				break;
			}
		}
		index = (index == -1)? 0 : index;

		/* All Ink */
		radio_button = 
		  LookupWidget(refreshing_dialog, "refreshing_radiobutton1");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
				LookupText(g_keytext_list, InkMsgInfo[index].InkName[0]));

		/* Black Ink */
		radio_button = 
		  LookupWidget(refreshing_dialog, "refreshing_radiobutton2");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),	
			   LookupText(g_keytext_list, InkMsgInfo[index].InkName[1]));

		/* Color Ink */
		radio_button = 
		  LookupWidget(refreshing_dialog, "refreshing_radiobutton3");
		gtk_label_set_text(GTK_LABEL((GTK_BIN(radio_button))->child),
			   LookupText(g_keytext_list, InkMsgInfo[index].InkName[2]));

		refreshing_set_default(refreshing_dialog);
		gtk_widget_show(refreshing_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(refreshing_dialog),
			GTK_WINDOW(UI_DIALOG(g_main_window)->window));

		excute_button = 
			LookupWidget(refreshing_dialog, "refreshing_execute_button");
		gtk_widget_grab_focus(excute_button);

		gtk_main();
  		
  		if (result != ID_OK)
			return ;
		
		msg = LookupText(g_keytext_list, 
						 InkMsgInfo[index].RefMsg[refresh_head_type]);

	}
	else{
		msg = LookupText(g_keytext_list, "utility_message_12");
	}

	if (UtilMessageBox( msg, g_window_title, 
						MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
		return;
	
	if (!strcmp(model_name, "BJF850") | !strcmp(model_name, "BJF860") |
					!strcmp(model_name, "BJF870")) {	
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, BJLCLEAN2, BJLCLEAN2LEN); p+=BJLCLEAN2LEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
		*p = 0x00;
		PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLCLEAN2LEN+BJLENDLEN+1);
	} else if (!strcmp(model_name, "BJF360")) {
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, BJLCLEAN4, BJLCLEAN4LEN); p+=BJLCLEAN4LEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
		*p = 0x00;
		PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLCLEAN4LEN+BJLENDLEN+1);

	}
	else if( !strcmp(model_name,"PIXUS550I") ||
			 !strcmp(model_name,"PIXUS850I") ||
			 !strcmp(model_name,"PIXUS560I") ||
			 !strcmp(model_name,"PIXUS860I") ||
			 !strcmp(model_name,"PIXUS990I") ||
			 !strcmp(model_name,"PIXUSIP3100") ||
			 !strcmp(model_name,"PIXUSIP4100") ||
			 !strcmp(model_name,"PIXUSIP8600") ){

		int n;
		CLEANCMD *refreshing_cmd;

		if( InkMsgInfo[index].GroupFlag ) 
			refreshing_cmd = GroupRefreshingCommand;
		else
			refreshing_cmd = RefreshingCommand;

		n = SetCurrentTime(p); p+=n;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;				
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, refreshing_cmd[refresh_head_type].cmd,
			   refreshing_cmd[refresh_head_type].len);
		p+=refreshing_cmd[refresh_head_type].len;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;              
		*p = 0x00;
		PutPrintData(buf, n+BJLLEN+BJLSTARTLEN+
					 refreshing_cmd[refresh_head_type].len+BJLENDLEN+1);
	}
	else if( !strcmp(model_name,"IP2200") ||
			 !strcmp(model_name,"IP6600D") ){

		int		n;
		
		n = SetCurrentTime(p); p+=n;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, BJLCLEAN4, BJLCLEAN4LEN); p+=BJLCLEAN4LEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;    
		*p = 0x00;
		PutPrintData(buf, n+BJLLEN+BJLSTARTLEN+BJLCLEAN4LEN+BJLENDLEN+1);
	}
	else if( !strcmp(model_name,"IP4200") ||
			 !strcmp(model_name,"IP7500") ||
			 !strcmp(model_name,"MP500") ){

		int n;
		CLEANCMD *refreshing_cmd;

		if( InkMsgInfo[index].GroupFlag ) 
			refreshing_cmd = GroupRefreshingCommand;
		else
			refreshing_cmd = RefreshingCommand;

		n = SetCurrentTime(p); p+=n;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;				
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, refreshing_cmd[refresh_head_type].cmd,
			   refreshing_cmd[refresh_head_type].len);
		p+=refreshing_cmd[refresh_head_type].len;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;              
		*p = 0x00;
		PutPrintData(buf, n+BJLLEN+BJLSTARTLEN+
					 refreshing_cmd[refresh_head_type].len+BJLENDLEN+1);
	}
	else {
		int		n;
		
		n = SetCurrentTime(p); p+=n;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, BJLCLEAN4, BJLCLEAN4LEN); p+=BJLCLEAN4LEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;    
		*p = 0x00;
		PutPrintData(buf, n+BJLLEN+BJLSTARTLEN+BJLCLEAN4LEN+BJLENDLEN+1);
	}

	UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
		g_window_title, MB_ICON_EXCLAMATION | MB_OK);
}


static char* GetCheckPattnFile(char* model_name, int pattn_flag)
{

	int i;

	for (i=0; i < sizeof(PatternCheckInfo)/sizeof(PATTERNCHECKINFO); i++) {
		if (!strcmp(PatternCheckInfo[i].ModelName, model_name)){
			return PatternCheckInfo[i].pattn_filename[pattn_flag];
		}
	}	
	return NULL;
}


void UtilNozzleCheck(LPUIDB uidb)
{
	char		buf[128];
	char		*p = buf;
	char		*model_name;
	
	if (g_socketname == NULL)			
		return ;                        

	model_name = GetModelName();

	if( !strcmp(model_name, "PIXUSIP3100") || 
		!strcmp(model_name, "PIXUSIP4100") || 
		!strcmp(model_name, "PIXUSIP8600") ){

		GtkWidget* nozzle_check_dialog = NULL;
		GtkWidget* pattern_check_dialog = NULL;
		GtkWidget *execute_button = NULL;
		GtkWidget *ok_pixmap, *ng_pixmap;
		GtkWidget *ok_frame, *ng_frame;
		GtkStyle *style;
		GdkPixmap *ok_map, *ng_map, *iconMask;
		int	i,n;
		char ok_buf[256], ng_buf[256];
		char bufModelName[64];

		nozzle_check_dialog = LookupWidget(NULL, "nozzle_check_dialog");
		gtk_widget_realize(nozzle_check_dialog);
		gtk_widget_show(nozzle_check_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(nozzle_check_dialog),
							 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
		execute_button = 
			LookupWidget(nozzle_check_dialog, "nozzle_check_execute_button");
		gtk_widget_grab_focus(execute_button);

		gtk_main();

		if (result != ID_OK)
			return ;

		n = SetCurrentTime(p); p+=n; 
		memcpy(p, bjl_cmds, BJLLEN);p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN);p+=BJLSTARTLEN;
		memcpy(p, BJLNOZZLECHECK, BJLNOZZLECHECKLEN);
		p+=BJLNOZZLECHECKLEN;
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
		*p = 0x00;
		PutPrintData(buf,
					 n+BJLLEN+BJLSTARTLEN+BJLNOZZLECHECKLEN+BJLENDLEN+1);

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		pattern_check_dialog = LookupWidget(NULL, "pattern_check_dialog");
		gtk_widget_realize(pattern_check_dialog);

		style = gtk_widget_get_style(pattern_check_dialog);

		memset(ok_buf, 0, 256);
		strncpy(ok_buf, CHECKPATTERNPATH, strlen(CHECKPATTERNPATH)+1);
		memset(bufModelName, 0, 64);
		for( i=0; i<=strlen(model_name)||i<64; i++)
			bufModelName[i] = LowerAsciiCode(model_name[i]);

		strncat(ok_buf, bufModelName, 63);
		strncat(ok_buf, "/", 1);
		strncat(ok_buf, GetCheckPattnFile(model_name,OK_CHECK_PATTN),
				190-strlen(CHECKPATTERNPATH));
		ok_map = gdk_pixmap_create_from_xpm(pattern_check_dialog->window,
								&iconMask, &style->bg[GTK_STATE_NORMAL],
								ok_buf);
		ok_pixmap = gtk_pixmap_new(ok_map, iconMask);	
		gtk_widget_ref(ok_pixmap);
		gtk_widget_show(ok_pixmap);
		ok_frame = LookupWidget(GTK_WIDGET(pattern_check_dialog), 
								"pattern_check_frame1");
		gtk_container_add(GTK_CONTAINER(ok_frame), ok_pixmap);
		
		memset(ng_buf, 0, 256);
		strncpy(ng_buf, CHECKPATTERNPATH, strlen(CHECKPATTERNPATH)+1);
		strncat(ng_buf, bufModelName, 63);
		strncat(ng_buf, "/", 1);
		strncat(ng_buf, GetCheckPattnFile(model_name,NG_CHECK_PATTN),
				190-strlen(CHECKPATTERNPATH));
		ng_map = gdk_pixmap_create_from_xpm(pattern_check_dialog->window, 
								&iconMask, &style->bg[GTK_STATE_NORMAL],
								ng_buf);
		ng_pixmap = gtk_pixmap_new(ng_map, iconMask);	
		gtk_widget_ref(ng_pixmap);
		gtk_widget_show(ng_pixmap);
		ng_frame = LookupWidget(GTK_WIDGET(pattern_check_dialog),
								"pattern_check_frame2");
		gtk_container_add(GTK_CONTAINER(ng_frame), ng_pixmap);

		if( !strcmp(model_name, "PIXUSIP8600") ){
			gtk_label_set_text(GTK_LABEL(LookupWidget(
							pattern_check_dialog, "pattern_check_label3")),
							LookupText(g_keytext_list, "utility_message_48"));
		}

		gtk_widget_show(pattern_check_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(pattern_check_dialog),
							 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
		execute_button = 
			LookupWidget(pattern_check_dialog, "pattern_check_exit_button");
		gtk_widget_grab_focus(execute_button);

		gtk_main();

		gtk_widget_unref(ok_pixmap);
		gtk_widget_unref(ng_pixmap);
		
		if (result != ID_CANCEL)
			UtilCleaning(uidb);

	}
	else if( !strcmp(model_name, "PIXMAIP1000") || 
			 !strcmp(model_name, "PIXMAIP1500") ){

		GtkWidget* nozzle_check_dialog = NULL;
		GtkWidget* pattern_check_dialog = NULL;
		GtkWidget *execute_button = NULL;
		GtkWidget *ok_pixmap, *ng_pixmap;
		GtkWidget *ok_frame, *ng_frame;
		GtkStyle *style;
		GdkPixmap *ok_map, *ng_map, *iconMask;
		int i,n;
		int fname_length;
		char fnamebuf[256];
		char bufModelName[64];
		char ok_buf[256], ng_buf[256];

		nozzle_check_dialog = LookupWidget(NULL, "nozzle_check_dialog");
		gtk_widget_realize(nozzle_check_dialog);
		gtk_label_set_text(
			GTK_LABEL(LookupWidget(nozzle_check_dialog, "nozzle_check_label1")),
			LookupText(g_keytext_list, "utility_message_46"));
		gtk_widget_show(nozzle_check_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(nozzle_check_dialog),
							 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
		execute_button = 
			LookupWidget(nozzle_check_dialog, "nozzle_check_execute_button");
		gtk_widget_grab_focus(execute_button);

		gtk_main();

		if (result != ID_OK)
			return ;
		
		n = SetCurrentTime(p); p+=n;	
		*p = 0x00;
		
		memset(fnamebuf, 0, 256);
		strncpy(fnamebuf, BJTESTFILEPATH, strlen(BJTESTFILEPATH)+1);
		memset(bufModelName, 0, 63);
		for( i=0; i<=strlen(model_name)||i<64; i++)
			bufModelName[i] = LowerAsciiCode(model_name[i]);	

		strncat(fnamebuf, bufModelName, 63);
		strncat(fnamebuf, "/", 1);
		strncat(fnamebuf, GetPatternFileName(NOZZLEPATTERN),
				190-strlen(BJTESTFILEPATH));
		fname_length = strlen(fnamebuf) +1;
		PutFileData(buf, n+1, fnamebuf, fname_length);
		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		pattern_check_dialog = LookupWidget(NULL, "pattern_check_dialog");
		gtk_widget_realize(pattern_check_dialog);

		style = gtk_widget_get_style(pattern_check_dialog);
		
		memset(ok_buf, 0, 256);
		strncpy(ok_buf, CHECKPATTERNPATH, strlen(CHECKPATTERNPATH)+1);
		strncat(ok_buf, bufModelName, 63);
		strncat(ok_buf, "/", 1);
		strncat(ok_buf, GetCheckPattnFile(model_name,OK_CHECK_PATTN),
				190-strlen(CHECKPATTERNPATH));
		ok_map = gdk_pixmap_create_from_xpm(pattern_check_dialog->window,
								&iconMask, &style->bg[GTK_STATE_NORMAL],
								ok_buf);
		ok_pixmap = gtk_pixmap_new(ok_map, iconMask);	
		gtk_widget_ref(ok_pixmap);
		gtk_widget_show(ok_pixmap);
		ok_frame = LookupWidget(GTK_WIDGET(pattern_check_dialog), 
								"pattern_check_frame1");
		gtk_container_add(GTK_CONTAINER(ok_frame), ok_pixmap);
		

		memset(ng_buf, 0, 256);
		strncpy(ng_buf, CHECKPATTERNPATH, strlen(CHECKPATTERNPATH)+1);
		strncat(ng_buf, bufModelName, 63);
		strncat(ng_buf, "/", 1);
		strncat(ng_buf, GetCheckPattnFile(model_name,NG_CHECK_PATTN),
				190-strlen(CHECKPATTERNPATH));
		ng_map = gdk_pixmap_create_from_xpm(pattern_check_dialog->window,
								&iconMask, &style->bg[GTK_STATE_NORMAL],
								ng_buf);
		ng_pixmap = gtk_pixmap_new(ng_map, iconMask);	
		gtk_widget_ref(ng_pixmap);
		gtk_widget_show(ng_pixmap);
		ng_frame = LookupWidget(GTK_WIDGET(pattern_check_dialog), 
								"pattern_check_frame2");
		gtk_container_add(GTK_CONTAINER(ng_frame), ng_pixmap);

		gtk_widget_show(pattern_check_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(pattern_check_dialog),
							 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
		execute_button = 
			LookupWidget(pattern_check_dialog, "pattern_check_exit_button");
		gtk_widget_grab_focus(execute_button);

		gtk_main();

		gtk_widget_unref(ok_pixmap);
		gtk_widget_unref(ng_pixmap);
		
		if (result != ID_CANCEL)
			UtilCleaning(uidb);
	}
	else if( !strcmp(model_name, "IP2200")  ){

		GtkWidget* nozzle_check_dialog = NULL;
		GtkWidget* pattern_check_dialog = NULL;
		GtkWidget *execute_button = NULL;
		GtkWidget *ok_pixmap, *ng_pixmap;
		GtkWidget *ok_frame, *ng_frame;
		GtkStyle *style;
		GdkPixmap *ok_map, *ng_map, *iconMask;
		int i,n;
		int fname_length;
		char fnamebuf[256];
		char bufModelName[64];
		char ok_buf[256], ng_buf[256];

		nozzle_check_dialog = LookupWidget(NULL, "nozzle_check_dialog");
		gtk_widget_realize(nozzle_check_dialog);
		gtk_label_set_text(
			GTK_LABEL(LookupWidget(nozzle_check_dialog, "nozzle_check_label1")),
			LookupText(g_keytext_list, "utility_message_54"));
		gtk_widget_show(nozzle_check_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(nozzle_check_dialog),
							 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
		execute_button = 
			LookupWidget(nozzle_check_dialog, "nozzle_check_execute_button");
		gtk_widget_grab_focus(execute_button);

		gtk_main();

		if (result != ID_OK)
			return ;
		
		n = SetCurrentTime(p); p+=n;	
		*p = 0x00;
		
		memset(fnamebuf, 0, 256);
		strncpy(fnamebuf, BJTESTFILEPATH, strlen(BJTESTFILEPATH)+1);
		memset(bufModelName, 0, 63);
		for( i=0; i<=strlen(model_name)||i<64; i++)
			bufModelName[i] = LowerAsciiCode(model_name[i]);	

		strncat(fnamebuf, bufModelName, 63);
		strncat(fnamebuf, "/", 1);
		strncat(fnamebuf, GetPatternFileName(NOZZLEPATTERN),
				190-strlen(BJTESTFILEPATH));
		fname_length = strlen(fnamebuf) +1;
		PutFileData(buf, n+1, fnamebuf, fname_length);
		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		pattern_check_dialog = LookupWidget(NULL, "pattern_check_dialog");
		gtk_widget_realize(pattern_check_dialog);

		style = gtk_widget_get_style(pattern_check_dialog);

		memset(ok_buf, 0, 256);
		strncpy(ok_buf, CHECKPATTERNPATH, strlen(CHECKPATTERNPATH)+1);
		strncat(ok_buf, bufModelName, 63);
		strncat(ok_buf, "/", 1);
		strncat(ok_buf, GetCheckPattnFile(model_name,OK_CHECK_PATTN),
				190-strlen(CHECKPATTERNPATH));
		ok_map = gdk_pixmap_create_from_xpm(pattern_check_dialog->window,
								&iconMask, &style->bg[GTK_STATE_NORMAL],
								ok_buf);
		ok_pixmap = gtk_pixmap_new(ok_map, iconMask);	
		gtk_widget_ref(ok_pixmap);
		gtk_widget_show(ok_pixmap);
		ok_frame = LookupWidget(GTK_WIDGET(pattern_check_dialog), 
								"pattern_check_frame1");
		gtk_container_add(GTK_CONTAINER(ok_frame), ok_pixmap);
		
		memset(ng_buf, 0, 256);
		strncpy(ng_buf, CHECKPATTERNPATH, strlen(CHECKPATTERNPATH)+1);
		strncat(ng_buf, bufModelName, 63);
		strncat(ng_buf, "/", 1);
		strncat(ng_buf, GetCheckPattnFile(model_name,NG_CHECK_PATTN),
				190-strlen(CHECKPATTERNPATH));
		ng_map = gdk_pixmap_create_from_xpm(pattern_check_dialog->window,
								&iconMask, &style->bg[GTK_STATE_NORMAL],
								ng_buf);
		ng_pixmap = gtk_pixmap_new(ng_map, iconMask);	
		gtk_widget_ref(ng_pixmap);
		gtk_widget_show(ng_pixmap);
		ng_frame = LookupWidget(GTK_WIDGET(pattern_check_dialog), 
								"pattern_check_frame2");
		gtk_container_add(GTK_CONTAINER(ng_frame), ng_pixmap);

		gtk_label_set_text(GTK_LABEL(LookupWidget(
							pattern_check_dialog, "pattern_check_label3")),
							LookupText(g_keytext_list, "utility_message_48"));

		gtk_widget_show(pattern_check_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(pattern_check_dialog),
							 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
		execute_button = 
			LookupWidget(pattern_check_dialog, "pattern_check_exit_button");
		gtk_widget_grab_focus(execute_button);

		gtk_main();

		gtk_widget_unref(ok_pixmap);
		gtk_widget_unref(ng_pixmap);
		
		if (result != ID_CANCEL)
			UtilCleaning(uidb);

	}
	else if( !strcmp(model_name, "IP4200") ||
			 !strcmp(model_name, "IP6600D") ||
			 !strcmp(model_name, "IP7500") ||
			 !strcmp(model_name, "MP500") ){

		GtkWidget* nozzle_check_dialog = NULL;
		GtkWidget* pattern_check_dialog = NULL;
		GtkWidget *execute_button = NULL;
		GtkWidget *ok_pixmap, *ng_pixmap;
		GtkWidget *ok_frame, *ng_frame;
		GtkStyle *style;
		GdkPixmap *ok_map, *ng_map, *iconMask;
		int	i,n;
		char ok_buf[256], ng_buf[256];
		char bufModelName[64];

		nozzle_check_dialog = LookupWidget(NULL, "nozzle_check_dialog");
		gtk_widget_realize(nozzle_check_dialog);
		gtk_widget_show(nozzle_check_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(nozzle_check_dialog),
							 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
		execute_button = 
			LookupWidget(nozzle_check_dialog, "nozzle_check_execute_button");
		gtk_widget_grab_focus(execute_button);

		gtk_main();

		if (result != ID_OK)
			return ;

		n = SetCurrentTime(p); p+=n; 
		memcpy(p, bjl_cmds, BJLLEN);p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN);p+=BJLSTARTLEN;
		memcpy(p, BJLNOZZLECHECK, BJLNOZZLECHECKLEN);
		p+=BJLNOZZLECHECKLEN;
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
		*p = 0x00;
		PutPrintData(buf,
					 n+BJLLEN+BJLSTARTLEN+BJLNOZZLECHECKLEN+BJLENDLEN+1);

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		pattern_check_dialog = LookupWidget(NULL, "pattern_check_dialog");
		gtk_widget_realize(pattern_check_dialog);

		style = gtk_widget_get_style(pattern_check_dialog);

		memset(ok_buf, 0, 256);
		strncpy(ok_buf, CHECKPATTERNPATH, strlen(CHECKPATTERNPATH)+1);
		memset(bufModelName, 0, 64);
		for( i=0; i<=strlen(model_name)||i<64; i++)
			bufModelName[i] = LowerAsciiCode(model_name[i]);

		strncat(ok_buf, bufModelName, 63);
		strncat(ok_buf, "/", 1);
		strncat(ok_buf, GetCheckPattnFile(model_name,OK_CHECK_PATTN),
				190-strlen(CHECKPATTERNPATH));
		ok_map = gdk_pixmap_create_from_xpm(pattern_check_dialog->window,
								&iconMask, &style->bg[GTK_STATE_NORMAL],
								ok_buf);
		ok_pixmap = gtk_pixmap_new(ok_map, iconMask);	
		gtk_widget_ref(ok_pixmap);
		gtk_widget_show(ok_pixmap);
		ok_frame = LookupWidget(GTK_WIDGET(pattern_check_dialog), 
								"pattern_check_frame1");
		if( !strcmp(model_name, "IP6600D") || !strcmp(model_name, "IP7500") )
			gtk_widget_set_usize(ok_frame, 285, 285);	// iP4200 285, 185
		gtk_container_add(GTK_CONTAINER(ok_frame), ok_pixmap);
		
		memset(ng_buf, 0, 256);
		strncpy(ng_buf, CHECKPATTERNPATH, strlen(CHECKPATTERNPATH)+1);
		strncat(ng_buf, bufModelName, 63);
		strncat(ng_buf, "/", 1);
		strncat(ng_buf, GetCheckPattnFile(model_name,NG_CHECK_PATTN),
				190-strlen(CHECKPATTERNPATH));
		ng_map = gdk_pixmap_create_from_xpm(pattern_check_dialog->window, 
								&iconMask, &style->bg[GTK_STATE_NORMAL],
								ng_buf);
		ng_pixmap = gtk_pixmap_new(ng_map, iconMask);	
		gtk_widget_ref(ng_pixmap);
		gtk_widget_show(ng_pixmap);
		ng_frame = LookupWidget(GTK_WIDGET(pattern_check_dialog),
								"pattern_check_frame2");
		if( !strcmp(model_name, "IP6600D") || !strcmp(model_name, "IP7500") )
			gtk_widget_set_usize(ng_frame, 285, 285);	// iP4200 285, 185
		gtk_container_add(GTK_CONTAINER(ng_frame), ng_pixmap);

		gtk_label_set_text(GTK_LABEL(LookupWidget(
							pattern_check_dialog, "pattern_check_label3")),
							LookupText(g_keytext_list, "utility_message_48"));

		gtk_widget_show(pattern_check_dialog);
		gtk_window_set_transient_for(GTK_WINDOW(pattern_check_dialog),
							 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
		execute_button = 
			LookupWidget(pattern_check_dialog, "pattern_check_exit_button");
		gtk_widget_grab_focus(execute_button);

		gtk_main();

		gtk_widget_unref(ok_pixmap);
		gtk_widget_unref(ng_pixmap);
		
		if (result != ID_CANCEL)
			UtilCleaning(uidb);

	}
	else{

		if (UtilMessageBox(LookupText(g_keytext_list, "utility_message_7"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_OK){

			if (!strcmp(model_name, "BJS600") || !strcmp(model_name, "BJS630")
				|| !strcmp(model_name, "BJS6300")
				|| !strcmp(model_name, "BJF900")
				|| !strcmp(model_name, "BJF9000")
				|| !strcmp(model_name, "BJS300")
				|| !strcmp(model_name, "BJS500")
				|| !strcmp(model_name, "PIXUS550I")
				|| !strcmp(model_name,"PIXUS850I")
				|| !strcmp(model_name,"PIXUS950I")
				|| !strcmp(model_name,"PIXUS560I")
				|| !strcmp(model_name,"PIXUS860I")
				|| !strcmp(model_name,"PIXUS990I") ){
				int		n;
		
				n = SetCurrentTime(p); p+=n; 
				memcpy(p, bjl_cmds, BJLLEN);p+=BJLLEN;
				memcpy(p, BJLSTART, BJLSTARTLEN);p+=BJLSTARTLEN;
				memcpy(p, BJLNOZZLECHECK, BJLNOZZLECHECKLEN);
				p+=BJLNOZZLECHECKLEN;
				memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
				*p = 0x00;
				PutPrintData(buf,
					 n+BJLLEN+BJLSTARTLEN+BJLNOZZLECHECKLEN+BJLENDLEN+1);
			} else if( !strcmp(model_name,"I250") || 
					   !strcmp(model_name,"I255") ){

				int		i,n;
				int fname_length;
				char fnamebuf[256];
				char bufModelName[64];
				
				n = SetCurrentTime(p); p+=n;	
				*p = 0x00;
				
				memset(fnamebuf, 0, 256);
				strncpy(fnamebuf, BJTESTFILEPATH, strlen(BJTESTFILEPATH)+1);
				for( i=0; i<=strlen(model_name)||i<64; i++)
					bufModelName[i] = LowerAsciiCode(model_name[i]);	
				strncat(fnamebuf, bufModelName, 63);
				strncat(fnamebuf, "/", 1);
				strncat(fnamebuf, GetPatternFileName(NOZZLEPATTERN),
						190-strlen(BJTESTFILEPATH));
				fname_length = strlen(fnamebuf) +1;
				PutFileData(buf, n+1, fnamebuf, fname_length);
				
			} else {
				memcpy(p, bjl_cmds, BJLLEN);p+=BJLLEN;
				memcpy(p, BJLSTART, BJLSTARTLEN);p+=BJLSTARTLEN;
				memcpy(p, BJLNOZZLECHECK, BJLNOZZLECHECKLEN);
				p+=BJLNOZZLECHECKLEN;
				memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
				*p = 0x00;
				PutPrintData(buf, 
						 BJLLEN+BJLSTARTLEN+BJLNOZZLECHECKLEN+BJLENDLEN+1);
			}
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
		}
	}

}


void UtilHeadAdjust(LPUIDB uidb)
{
	int			i;
	char		buf[REGI_BUF_SIZE];			
	char		temp[REGI_TMP_SIZE];        
	char		*p = buf;                   
	char		*msg;                       
	int			nValue;
	short		nKindCntValue;
	char		*model_name;				

	if (g_socketname == NULL)			
		return ;                        

	model_name = GetModelName();		

	
	if (!strcmp(model_name,"BJF850") || !strcmp(model_name,"BJF860")
	 || !strcmp(model_name,"BJF870")) {
		if (!strcmp(GetModelName(), "BJF850"))	
			msg = LookupText(g_keytext_list, "utility_message_1");
		else		
			msg = LookupText(g_keytext_list, "utility_message_16");
		
		
		if (UtilMessageBox(msg, g_window_title,		
				MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return ;			

		
		if (!strcmp(GetModelName(), "BJF850")) {	
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;				
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;	
			memcpy(p, BJLMANUAL, BJLMANUALLEN); p+=BJLMANUALLEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;			
			*p = 0x00;
			PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLMANUALLEN+BJLENDLEN+1);	
		} else {	
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;				
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;   
			memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;   
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;          
			*p = 0x00;
			PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLREGI1LEN+BJLENDLEN+1);	
		}
		
		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_EXCLAMATION | MB_YES | MB_NO) == ID_NO) {	
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
  
		
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
			return ;						
	
		
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
  		for (i=0; i<nKindCnt; i++) {	
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETREG,
				lpBJLtbl[i], nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
  		}
  		
  		nValue = ItemValue[2];
  		sprintf(temp, BJLSETREG,
			lpBJLtbl[6], nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
  		
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;			
		PutPrintData(buf,
			BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
			+(BJLSETREGLEN*(nKindCnt+1))+BJLENDLEN+1);
  	
		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
			g_window_title, MB_ICON_INFORMATION | MB_OK);

	
	
	
	} else if (!strcmp(model_name, "BJF360")) {	
		
		msg = LookupText(g_keytext_list, "utility_message_18");
		if (UtilMessageBox(msg, g_window_title,
				MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return ;			

		
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
		memcpy(p, BJLMANUAL1, BJLMANUAL1LEN); p+=BJLMANUAL1LEN;	
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
		*p = 0x00;
		PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLMANUAL1LEN+BJLENDLEN+1);	

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_EXCLAMATION | MB_YES | MB_NO) == ID_NO) {	
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
  
		
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
			return ;						
	
		
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
  		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETREG, lpBJLtbl[i],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
  		}
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;			
		PutPrintData(buf,
			BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
			+(BJLSETREGLEN*nKindCnt)+BJLENDLEN+1);	
  		
		msg = LookupText(g_keytext_list, "utility_message_19");
		UtilMessageBox(msg, g_window_title,	MB_ICON_EXCLAMATION | MB_OK);
  		
		
		p = buf;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;       
		memcpy(p, BJLMANUAL2, BJLMANUAL2LEN); p+=BJLMANUAL2LEN; 
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;              
		*p = 0x00;
		PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLMANUALLEN+BJLENDLEN+1);	

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		nPageNum = 1;
		if (UtilRegiDialog(nPageNum) != ID_OK)
			return ;						
  		
		
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;           
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;  
		
  		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETREG, lpBJLtbl[i],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
  		}
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;			
		PutPrintData(buf,
			BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
			+(BJLSETREGLEN*nKindCnt)+BJLENDLEN+1);	

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
			g_window_title, MB_ICON_INFORMATION | MB_OK);

	
	
	} else if (!strcmp(model_name,"BJF900") || !strcmp(model_name,"BJF9000")||
			   !strcmp(model_name,"BJS300") || !strcmp(model_name,"BJS500") ||
			   !strcmp( model_name, "PIXUS550I") ){
												
		int 	n;
		
		msg = LookupText(g_keytext_list, "utility_message_20");

		if (UtilMessageBox(msg, g_window_title,
				MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return ;			

		
		p = buf;
		n = SetCurrentTime(p); p += n;		
		
		
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
		memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;		
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
		*p = 0x00;
		PutPrintData(buf,
			n + BJLLEN + BJLSTARTLEN + BJLREGI1LEN + BJLENDLEN + 1);	

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_EXCLAMATION | MB_YES | MB_NO) == ID_NO) { 
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
  
		
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
			return ;						
	
		
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
  		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETREG, lpBJLtbl[i],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
  		}

		nValue = ItemValue[2];
  		sprintf(temp, BJLSETREG, lpBJLtbl[6],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;			
		PutPrintData(buf,
			BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
			+(BJLSETREGLEN*(nKindCnt+1))+BJLENDLEN+1);
	
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
			g_window_title, MB_ICON_INFORMATION | MB_OK);
  		
		
		  
	} 
	else if (!strcmp(model_name,"PIXUS950I") ){
		
		int 	n;

		msg = LookupText(g_keytext_list, "utility_message_25");
		if (UtilMessageBox(msg, g_window_title,
				MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return ;			

		
		p = buf;
		n = SetCurrentTime(p); p += n;		
		
		
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
		memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;		
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
		*p = 0x00;
		PutPrintData(buf,
			n + BJLLEN + BJLSTARTLEN + BJLREGI1LEN + BJLENDLEN + 1);	

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_EXCLAMATION | MB_YES | MB_NO) == ID_NO) { 
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
  
		
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
			return ;						
	
		
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		


  		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETREG, lpBJLtbl[i],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
  		}
				
		// Yellow
		nValue = ItemValue[0];
		sprintf(temp, BJLSETREG, lpBJLtbl[8],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		
		// Yellow Bi
		nValue = ItemValue[5];
		sprintf(temp, BJLSETREG, lpBJLtbl[9],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

		// LC Bi
		nValue = ItemValue[6];
		sprintf(temp, BJLSETREG, lpBJLtbl[10],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

		// LM Bi
		nValue = ItemValue[7];
		sprintf(temp, BJLSETREG, lpBJLtbl[11],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;


		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;			
		PutPrintData(buf,
					 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
					 +(BJLSETREGLEN*(nKindCnt+4))+BJLENDLEN+1);


		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
			g_window_title, MB_ICON_INFORMATION | MB_OK);
  		
		
		  
	} 
	else if( !strcmp(model_name,"PIXUS850I") || 
			!strcmp(model_name,"PIXUS560I")  ){
		
		int 	n;
		
		msg = LookupText(g_keytext_list, "utility_message_25");
		if (UtilMessageBox(msg, g_window_title,
				MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return ;			

		
		p = buf;
		n = SetCurrentTime(p); p += n;		
		
		
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
		memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;		
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
		*p = 0x00;
		PutPrintData(buf,
			n + BJLLEN + BJLSTARTLEN + BJLREGI1LEN + BJLENDLEN + 1);	

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_EXCLAMATION | MB_YES | MB_NO) == ID_NO) { 
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
  
		
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
			return ;						
	
		
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
  		
		
		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETREG, lpBJLtbl[i],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			
		}
		
		nValue = ItemValue[2];
		sprintf(temp, BJLSETREG, lpBJLtbl[11],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		
		nValue = ItemValue[8];
		sprintf(temp, BJLSETREG, lpBJLtbl[12],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		
		
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;			
		PutPrintData(buf,
					 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
					 +(BJLSETREGLEN*(nKindCnt+2))+BJLENDLEN+1);
		
		

		if( UtilMessageBoxSetDefault(
			LookupText(g_keytext_list, "utility_message_26"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL, MB_CANCEL)
			==ID_CANCEL ){
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
					   g_window_title, MB_ICON_INFORMATION | MB_OK);
			return;
		}  		
		
		p = buf;
		n = SetCurrentTime(p); p += n;		

		
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;       
		memcpy(p, BJLBANDREGI1, BJLBANDREGI1LEN); p+=BJLBANDREGI1LEN; 
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;              
		*p = 0x00;
		PutPrintData(buf,
			 n + BJLLEN + BJLSTARTLEN + BJLBANDREGI1LEN + BJLENDLEN + 1);	

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		nPageNum = 1;
		if (UtilRegiDialog(nPageNum) != ID_OK)
			return ;						
  		
		
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;           
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;  
		
  		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETBANDREG, lpBJLtbl[i],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETBANDREGLEN); p += BJLSETBANDREGLEN;
  		}
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;			
		PutPrintData(buf,
					 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
					 +(BJLSETBANDREGLEN*nKindCnt)+BJLENDLEN+1);
		
		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
					   g_window_title, MB_ICON_INFORMATION | MB_OK);
		
	}
	else if (!strcmp(model_name,"I250") ||
			 !strcmp(model_name, "I255") ){
		
		int 	n;
		int fname_length;
		char fnamebuf[256];
		char bscc_buf[256];
		char bscc_file[256];
		int bscc_len;
		char bufModelName[64];
		char print_file[256];

		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_25"),
		g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return;

		n = SetCurrentTime(p); p+=n;	
		*p = 0x00;
			
		memset(fnamebuf, 0, 256);
		strncpy(fnamebuf, BJTESTFILEPATH, strlen(BJTESTFILEPATH)+1);
		for( i=0; i<=strlen(model_name)|| i<64; i++)
			bufModelName[i] = LowerAsciiCode(model_name[i]);
		strncat(fnamebuf, bufModelName, 63);
		strncat(fnamebuf, "/",1);
		strncat(fnamebuf, GetPatternFileName(REGIPATTERN1),
			   190-strlen(BJTESTFILEPATH));
		fname_length = strlen(fnamebuf) + 1;
		PutFileData(buf, n+1, fnamebuf, fname_length);

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
		
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
		g_window_title, MB_ICON_EXCLAMATION | MB_YES | MB_NO) == ID_NO) { 
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
		
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
			return ;						
		
		/* BJL Command */
		p = buf;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
		for (i=0; i<nKindCnt; i++) {	
			int		nValue;
  		
			nValue = ItemValue[i];		
			sprintf(temp, BJLSETREG, lpBJLtbl[i],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		}

		nValue = ItemValue[2];
  		sprintf(temp, BJLSETREG, lpBJLtbl[6],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;

		/* Creation of BSCC Command */
		CreateRegiBSCC(bscc_buf, &bscc_len, bscc_file, ItemValue, nPageNum);

		if( g_cups_mode == FALSE ){
			PutPrintData(buf,
					 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
					 +(BJLSETREGLEN*(nKindCnt+1))+BJLENDLEN+1);

			/* Write To File : REG */
			if( WriteToBSCCFile(bscc_file, bscc_buf, BSCCID_REG) )
				fprintf(stderr,"Error: Bscc file Error!\n");
		}
		else {
			if( WriteToPrintFile(print_file, bscc_buf, bscc_len, BSCCID_REG))
				fprintf(stderr,"Error: Bscc Error!\n");

			fname_length = strlen(print_file) + 1;
			PutDoubleData(buf, BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN+
					  (BJLSETREGLEN*(nKindCnt+1))+BJLENDLEN+1, 
					  print_file, fname_length);
		}

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
					   g_window_title, MB_ICON_INFORMATION | MB_OK);
	}
	else if( !strcmp(model_name,"PIXMAIP1000"))
	{
		int 	n;
		int fname_length;
		char fnamebuf[256];
		char bufModelName[64];

		if (UtilMessageBox(LookupText(g_keytext_list, "utility_message_25"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return ;			

		n = SetCurrentTime(p); p+=n;	
		*p = 0x00;
			
		memset(fnamebuf, 0, 256);
		strncpy(fnamebuf, BJTESTFILEPATH, strlen(BJTESTFILEPATH)+1);
		for( i=0; i<=strlen(model_name)|| i<64; i++)
			bufModelName[i] = LowerAsciiCode(model_name[i]);	
		strncat(fnamebuf, bufModelName, 63);
		strncat(fnamebuf, "/", 1);
		strncat(fnamebuf, GetPatternFileName(REGIPATTERN1),
				190-strlen(BJTESTFILEPATH));
		fname_length = strlen(fnamebuf) + 1;
		PutFileData(buf, n+1, fnamebuf, fname_length);

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_INFORMATION | MB_YES | MB_NO) == ID_NO) { 
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
  
		
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
			return ;						

		/* BJL Command */
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
  		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETREG, lpBJLtbl[i],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
  		}

		nValue = ItemValue[2];
  		sprintf(temp, BJLSETREG, lpBJLtbl[6],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;
		PutPrintData(buf,
					 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
					 +(BJLSETREGLEN*(nKindCnt+1))+BJLENDLEN+1);

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
			g_window_title, MB_ICON_INFORMATION | MB_OK);
  			
		  
	}
	else if (!strcmp(model_name,"PIXMAIP1500")){
				
		int 	n;
		int fname_length;
		char fnamebuf[256];
		char bufModelName[64];

		if (UtilMessageBox(LookupText(g_keytext_list, "utility_message_25"),
		g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return ;			

		n = SetCurrentTime(p); p+=n;	
		*p = 0x00;
			
		memset(fnamebuf, 0, 256);
		strncpy(fnamebuf, BJTESTFILEPATH, strlen(BJTESTFILEPATH)+1);
		for( i=0; i<=strlen(model_name)|| i<64; i++)
			bufModelName[i] = LowerAsciiCode(model_name[i]);	
		strncat(fnamebuf, bufModelName, 63);
		strncat(fnamebuf, "/",1);
		strncat(fnamebuf, GetPatternFileName(REGIPATTERN1),
			   190-strlen(BJTESTFILEPATH));
		fname_length = strlen(fnamebuf) + 1;
		PutFileData(buf, n+1, fnamebuf, fname_length);

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_INFORMATION | MB_YES | MB_NO) == ID_NO) { 
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
		
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
			return ;						
		
		/* BJL Command */
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
  		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETREG, lpBJLtbl[i],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
  		}

		nValue = ItemValue[2];
  		sprintf(temp, BJLSETREG, lpBJLtbl[11],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

		nValue = ItemValue[4];
  		sprintf(temp, BJLSETREG, lpBJLtbl[12],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

		nValue = ItemValue[8];
  		sprintf(temp, BJLSETREG, lpBJLtbl[13],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
  		sprintf(temp, BJLSETREG, lpBJLtbl[14],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

		nValue = ItemValue[10];
  		sprintf(temp, BJLSETREG, lpBJLtbl[15],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;
		PutPrintData(buf,
					 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
					 +(BJLSETREGLEN*(nKindCnt+5))+BJLENDLEN+1);

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
			g_window_title, MB_ICON_INFORMATION | MB_OK);
  			
	} 
	else if( !strcmp(model_name,"PIXUS860I") ){

		int 	n;

		/* Auto Head Alignment */
		if( !manual_head_mode ){
			msg = LookupText(g_keytext_list, "utility_message_35");
			if (UtilMessageBox(msg, g_window_title,
					   MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
				return ;			

			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGIAUTO1, BJLREGIAUTO1LEN); p+=BJLREGIAUTO1LEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGIAUTO1LEN + BJLENDLEN + 1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}

		/* Manual Head Alignment */
		msg = LookupText(g_keytext_list, "utility_message_25");
		if (UtilMessageBox(msg, g_window_title,
				MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return ;			
		
		p = buf;
		n = SetCurrentTime(p); p += n;		

		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
		memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;		
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
		*p = 0x00;
		PutPrintData(buf,
			n + BJLLEN + BJLSTARTLEN + BJLREGI1LEN + BJLENDLEN + 1);	
		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_EXCLAMATION | MB_YES | MB_NO) == ID_NO) { 
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
		
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
			return ;						
		
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETREG, lpBJLtbl[i],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		}
		
		nValue = ItemValue[2];
		sprintf(temp, BJLSETREG, lpBJLtbl[12],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		
		nValue = ItemValue[9];
		sprintf(temp, BJLSETREG, lpBJLtbl[13],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;			
		PutPrintData(buf,
					 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
					 +(BJLSETREGLEN*(nKindCnt+2))+BJLENDLEN+1);
		
		if(UtilMessageBoxSetDefault(
			LookupText(g_keytext_list, "utility_message_26"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL, MB_CANCEL)
			==ID_CANCEL ){
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
						   g_window_title, MB_ICON_INFORMATION | MB_OK);
			return;
		}
		
		p = buf;
		n = SetCurrentTime(p); p += n;		

		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;       
		memcpy(p, BJLBANDREGI1, BJLBANDREGI1LEN); p+=BJLBANDREGI1LEN; 
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;              
		*p = 0x00;
		PutPrintData(buf,
			 n + BJLLEN + BJLSTARTLEN + BJLBANDREGI1LEN + BJLENDLEN + 1);	

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		nPageNum = 1;
		if (UtilRegiDialog(nPageNum) != ID_OK)
			return ;						
  		
		
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;           
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;  
		
  		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETBANDREG, lpBJLtbl[i],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETBANDREGLEN); p += BJLSETBANDREGLEN;
  		}
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;			
		PutPrintData(buf,
					 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
					 +(BJLSETBANDREGLEN*nKindCnt)+BJLENDLEN+1);
				
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
					   g_window_title, MB_ICON_INFORMATION | MB_OK);

	}
	else if( !strcmp(model_name,"PIXUS990I") ){
		int 	n;
		
		/* Auto Head Alignment */
		if( !manual_head_mode ){

			msg = LookupText(g_keytext_list, "utility_message_36");
			if (UtilMessageBox(msg, g_window_title,
					MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			  return ;			
		
			p = buf;
			n = SetCurrentTime(p); p += n;		

			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;		
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGI1LEN + BJLENDLEN + 1);	
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

			if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			  g_window_title, MB_ICON_EXCLAMATION | MB_YES | MB_NO) == ID_NO) {
				UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
				return;
			}
			
			nPageNum = 2;
			if (UtilRegiDialog(nPageNum) != ID_OK)		
			  return ;						
		
			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
			for (i=0; i<nKindCnt; i++) {	
				int		nValue;
				
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			}
				
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETREGLEN*nKindCnt)+BJLENDLEN+1);

			UtilMessageBox(LookupText(g_keytext_list, "utility_message_37"),
						   g_window_title, MB_ICON_INFORMATION | MB_OK);

			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGIAUTO1, BJLREGIAUTO1LEN); p+=BJLREGIAUTO1LEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGIAUTO1LEN + BJLENDLEN + 1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

			return;
		}

		/* Manual Head Alignment */
		msg = LookupText(g_keytext_list, "utility_message_20");
		
		if (UtilMessageBox(msg, g_window_title,
					MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return ;			
		
		p = buf;
		n = SetCurrentTime(p); p += n;		

		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
		memcpy(p, BJLREGI2, BJLREGI2LEN); p+=BJLREGI2LEN;		
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
		*p = 0x00;
		PutPrintData(buf,
				n + BJLLEN + BJLSTARTLEN + BJLREGI2LEN + BJLENDLEN + 1);	
			
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_EXCLAMATION | MB_YES | MB_NO) == ID_NO) { 
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
			
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
		  return ;						
		
		p = buf;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
		for (i=0; i<nKindCnt; i++) {	
			int		nValue;
			
			nValue = ItemValue[i];		
			sprintf(temp, BJLSETREG, lpBJLtbl[i],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		}
				
		*p = 0x00;			
		PutPrintData(buf,
					 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
					 +(BJLSETREGLEN*nKindCnt)+BJLENDLEN+1);
		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
					   g_window_title, MB_ICON_INFORMATION | MB_OK);
	
	}
	else if( !strcmp(model_name,"PIXUSIP3100") ){

		GtkWidget *head_alignment_dialog;
		GtkWidget *execute_button;
		int 	n;

		/* Auto Head Alignment */
		if( !manual_head_mode ){

			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);
			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;
		
			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGIAUTO1, BJLREGIAUTO1LEN); p+=BJLREGIAUTO1LEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGIAUTO1LEN + BJLENDLEN + 1);
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
		else{		/* Manual Head Alignment */

			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);

			gtk_label_set_text(
				GTK_LABEL(LookupWidget(head_alignment_dialog, 
									   "head_alignment_label1")),
				LookupText(g_keytext_list, "utility_message_45"));


			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;

			p = buf;
			n = SetCurrentTime(p); p += n;		
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;		
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGI1LEN + BJLENDLEN + 1);	
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
		
			if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_INFORMATION | MB_YES | MB_NO) == ID_NO) { 
			
				UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
							   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
				return;
			}
		
			nPageNum = 0;
			if (UtilRegiDialog(nPageNum) != ID_OK)		
				return ;						

			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
			for (i=0; i<nKindCnt; i++) {	
				int		nValue;
  		
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			}

			nValue = ItemValue[2];
			sprintf(temp, BJLSETREG, lpBJLtbl[11],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			
			nValue = ItemValue[8];
			sprintf(temp, BJLSETREG, lpBJLtbl[12],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			
			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETREGLEN*(nKindCnt+2))+BJLENDLEN+1);
			
			if( UtilMessageBoxSetDefault(
				LookupText(g_keytext_list, "utility_message_49"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL, MB_CANCEL)
				==ID_CANCEL ){
				UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
							   g_window_title, MB_ICON_INFORMATION | MB_OK);
				return;
			}
			
			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;       
			memcpy(p, BJLBANDREGI1, BJLBANDREGI1LEN); p+=BJLBANDREGI1LEN; 
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;              
			*p = 0x00;
			PutPrintData(buf,
						 n + BJLLEN + BJLSTARTLEN + BJLBANDREGI1LEN + BJLENDLEN + 1);	
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			
			
			nPageNum = 1;
			if (UtilRegiDialog(nPageNum) != ID_OK)
				return ;						
			
			
			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;           
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;  
			
			for (i=0; i<nKindCnt; i++) {	
				int		nValue;
				
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETBANDREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETBANDREGLEN); p += BJLSETBANDREGLEN;
			}
			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETBANDREGLEN*nKindCnt)+BJLENDLEN+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
						   g_window_title, MB_ICON_INFORMATION | MB_OK);
			
			
		}
	}
	else if( !strcmp(model_name,"PIXUSIP4100") ){

		GtkWidget *head_alignment_dialog;
		GtkWidget *execute_button;
		int 	n;

		/* Auto Head Alignment */
		if( !manual_head_mode ){

			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);
			gtk_label_set_text( GTK_LABEL(LookupWidget(head_alignment_dialog, "head_alignment_label1")),
				LookupText(g_keytext_list, "LUM_IDS_MNTMSG_PHA_START_AUTOMATIC")); 	// 2007/06/27
			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;
		
			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGIAUTO1, BJLREGIAUTO1LEN); p+=BJLREGIAUTO1LEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGIAUTO1LEN + BJLENDLEN + 1);
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
		else{		/* Manual Head Alignment */

			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);

			gtk_label_set_text(
				GTK_LABEL(LookupWidget(head_alignment_dialog, 
									   "head_alignment_label1")),
				LookupText(g_keytext_list, "utility_message_45"));


			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;

			p = buf;
			n = SetCurrentTime(p); p += n;		
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;		
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGI1LEN + BJLENDLEN + 1);	
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
		
			if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_INFORMATION | MB_YES | MB_NO) == ID_NO) { 
			
				UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
							   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
				return;
			}
		
			nPageNum = 0;
			if (UtilRegiDialog(nPageNum) != ID_OK)		
				return ;						
		
			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
			for (i=0; i<nKindCnt; i++) {	
				int		nValue;
  		
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			}
		
			nValue = ItemValue[2];
			sprintf(temp, BJLSETREG, lpBJLtbl[12],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			
			nValue = ItemValue[9];
			sprintf(temp, BJLSETREG, lpBJLtbl[13],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			
			
			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETREGLEN*(nKindCnt+2))+BJLENDLEN+1);
			
			if( UtilMessageBoxSetDefault(
				LookupText(g_keytext_list, "utility_message_49"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL, MB_CANCEL)
				==ID_CANCEL ){
				UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
							   g_window_title, MB_ICON_INFORMATION | MB_OK);
				return;
			}
			
			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;       
			memcpy(p, BJLBANDREGI1, BJLBANDREGI1LEN); p+=BJLBANDREGI1LEN; 
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;              
			*p = 0x00;
			PutPrintData(buf,
						 n + BJLLEN + BJLSTARTLEN + BJLBANDREGI1LEN + BJLENDLEN + 1);	
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			
			
			nPageNum = 1;
			if (UtilRegiDialog(nPageNum) != ID_OK)
				return ;						
			
			
			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;           
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;  
			
			for (i=0; i<nKindCnt; i++) {	
				int		nValue;
				
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETBANDREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETBANDREGLEN); p += BJLSETBANDREGLEN;
			}
			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETBANDREGLEN*nKindCnt)+BJLENDLEN+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
						   g_window_title, MB_ICON_INFORMATION | MB_OK);
			
			
		}
	}
	else if( !strcmp(model_name,"PIXUSIP8600") ){

		GtkWidget *head_alignment_dialog;
		GtkWidget *execute_button;
		int 	n;

		/* Auto Head Alignment */
		if( !manual_head_mode ){

			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);
			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;
		
			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGIAUTO1, BJLREGIAUTO1LEN); p+=BJLREGIAUTO1LEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGIAUTO1LEN + BJLENDLEN + 1);
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
		else{		/* Manual Head Alignment */

			
			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);

			gtk_label_set_text(
				GTK_LABEL(LookupWidget(head_alignment_dialog, 
									   "head_alignment_label1")),
				LookupText(g_keytext_list, "utility_message_45"));


			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;

			p = buf;
			n = SetCurrentTime(p); p += n;		
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGI2, BJLREGI2LEN); p+=BJLREGI2LEN;		
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGI2LEN + BJLENDLEN + 1);	
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
		
			if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_INFORMATION | MB_YES | MB_NO) == ID_NO) { 
			
				UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
							   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
				return;
			}
		
			nPageNum = 0;
			if (UtilRegiDialog(nPageNum) != ID_OK)		
				return ;						
		
			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
			for (i=0; i<nKindCnt; i++) {	
				int		nValue;
  		
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			}
			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETREGLEN* nKindCnt)+BJLENDLEN+1);

			UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
						   g_window_title, MB_ICON_INFORMATION | MB_OK);
		}
	}
	else if( !strcmp(model_name,"IP2200") )
	{
		int 	n;
		int fname_length;
		char fnamebuf[256];
		char bufModelName[64];

		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_53"),
		g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return;

		n = SetCurrentTime(p); p+=n;	
		*p = 0x00;
			
		memset(fnamebuf, 0, 256);
		strncpy(fnamebuf, BJTESTFILEPATH, strlen(BJTESTFILEPATH)+1);
		for( i=0; i<=strlen(model_name)|| i<64; i++)
			bufModelName[i] = LowerAsciiCode(model_name[i]);
		strncat(fnamebuf, bufModelName, 63);
		strncat(fnamebuf, "/",1);
		strncat(fnamebuf, GetPatternFileName(REGIPATTERN1),
			   190-strlen(BJTESTFILEPATH));
		fname_length = strlen(fnamebuf) + 1;
		PutFileData(buf, n+1, fnamebuf, fname_length);

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
		
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
		g_window_title, MB_ICON_INFORMATION | MB_YES | MB_NO) == ID_NO) { 
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
		
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
			return ;						
		
		/* BJL Command */
		p = buf;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
		for (i=0; i<nKindCnt; i++) {	
			int		nValue;
  		
			nValue = ItemValue[i];		
			sprintf(temp, BJLSETREG, lpBJLtbl[i],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		}

		nValue = ItemValue[9];
  		sprintf(temp, BJLSETREG, lpBJLtbl[12],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

		nValue = ItemValue[10];
  		sprintf(temp, BJLSETREG, lpBJLtbl[13],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

		nValue = ItemValue[11];
  		sprintf(temp, BJLSETREG, lpBJLtbl[14],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;
		PutPrintData(buf,
					 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
					 +(BJLSETREGLEN*(nKindCnt+3))+BJLENDLEN+1);
		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
					   g_window_title, MB_ICON_INFORMATION | MB_OK);
	}
	else if( !strcmp(model_name,"IP4200") || !strcmp(model_name,"MP500") )
	{
		GtkWidget *head_alignment_dialog;
		GtkWidget *execute_button;
		int 	n;

		/* Auto Head Alignment */
		if( !manual_head_mode ){

			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);
			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;
		
			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGIAUTO1, BJLREGIAUTO1LEN); p+=BJLREGIAUTO1LEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGIAUTO1LEN + BJLENDLEN + 1);
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
		else{		/* Manual Head Alignment */
			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);
			gtk_label_set_text(
				GTK_LABEL(LookupWidget(head_alignment_dialog, 
									   "head_alignment_label1")),
				LookupText(g_keytext_list, "utility_message_52"));
			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;

			p = buf;
			n = SetCurrentTime(p); p += n;		
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;		
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGI1LEN + BJLENDLEN + 1);	
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
		
			if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_INFORMATION | MB_YES | MB_NO) == ID_NO) { 
			
				UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
							   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
				return;
			}
		
			nPageNum = 0;
			if (UtilRegiDialog(nPageNum) != ID_OK)		
				return ;						
		
			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
			for (i=0; i<nKindCnt; i++) {	
				int		nValue;
  		
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			}

			nValue = ItemValue[2];
  			sprintf(temp, BJLSETREG, lpBJLtbl[10],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

			nValue = ItemValue[7];
  			sprintf(temp, BJLSETREG, lpBJLtbl[11],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETREGLEN*(nKindCnt+2))+BJLENDLEN+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_51"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;       
			memcpy(p, BJLREGI2, BJLREGI2LEN); p+=BJLREGI2LEN; 
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;              
			*p = 0x00;
			PutPrintData(buf,
						 n + BJLLEN + BJLSTARTLEN + BJLREGI2LEN + BJLENDLEN + 1);	

			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			
			
			nPageNum = 1;
			if (UtilRegiDialog(nPageNum) != ID_OK)
				return ;						

			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
			nKindCntValue = 4;
			for (i=0; i<nKindCntValue; i++) {	
				int		nValue;
  		
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			}

			nValue = ItemValue[3];
  			sprintf(temp, BJLSETREG, lpBJLtbl[6],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

			for (i=0; i<nKindCnt-nKindCntValue; i++) {	
				int		nValue;
				
				nValue = ItemValue[nKindCntValue+i];		
				sprintf(temp, BJLSETBANDREG, lpBJLtbl[nKindCntValue+i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETBANDREGLEN); p += BJLSETBANDREGLEN;
			}

			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETREGLEN*(nKindCntValue+1))
						 +(BJLSETBANDREGLEN*(nKindCnt-nKindCntValue))+BJLENDLEN+1);

			UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
						   g_window_title, MB_ICON_INFORMATION | MB_OK);
		}
	}
	else if( !strcmp(model_name,"IP7500") )
	{
		GtkWidget *head_alignment_dialog;
		GtkWidget *execute_button;
		int 	n;

		/* Auto Head Alignment */
		if( !manual_head_mode ){
			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);
			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;
		
			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGIAUTO1, BJLREGIAUTO1LEN); p+=BJLREGIAUTO1LEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGIAUTO1LEN + BJLENDLEN + 1);
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
		else{		/* Manual Head Alignment */
			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);
			gtk_label_set_text(
				GTK_LABEL(LookupWidget(head_alignment_dialog, 
									   "head_alignment_label1")),
				LookupText(g_keytext_list, "utility_message_52"));
			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;

			p = buf;
			n = SetCurrentTime(p); p += n;		
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;		
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGI1LEN + BJLENDLEN + 1);	
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
		
			if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_INFORMATION | MB_YES | MB_NO) == ID_NO) { 
			
				UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
							   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
				return;
			}
		
			nPageNum = 0;
			if (UtilRegiDialog(nPageNum) != ID_OK)		
				return ;						

			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
			for (i=0; i<nKindCnt; i++) {	
				int		nValue;
  		
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			}

			nValue = ItemValue[5];
  			sprintf(temp, BJLSETREG, lpBJLtbl[8],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

			nValue = ItemValue[7];
  			sprintf(temp, BJLSETREG, lpBJLtbl[9],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETREGLEN*(nKindCnt+2))+BJLENDLEN+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_51"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;       
			memcpy(p, BJLREGI2, BJLREGI2LEN); p+=BJLREGI2LEN; 
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;              
			*p = 0x00;
			PutPrintData(buf,
						 n + BJLLEN + BJLSTARTLEN + BJLREGI2LEN + BJLENDLEN + 1);	

			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			
			
			nPageNum = 1;
			if (UtilRegiDialog(nPageNum) != ID_OK)
				return ;						

			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	

			nKindCntValue = 4;
			for (i=0; i<nKindCntValue; i++) {	
				int		nValue;
  		
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			}

			nValue = ItemValue[3];
  			sprintf(temp, BJLSETREG, lpBJLtbl[5],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

			for (i=0; i<nKindCnt-nKindCntValue; i++) {	
				int		nValue;
				
				nValue = ItemValue[nKindCntValue+i];		
				sprintf(temp, BJLSETBANDREG, lpBJLtbl[nKindCntValue+i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETBANDREGLEN); p += BJLSETBANDREGLEN;
			}
			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETREGLEN*(nKindCntValue+1))
						 +(BJLSETBANDREGLEN*(nKindCnt-nKindCntValue))+BJLENDLEN+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
						   g_window_title, MB_ICON_INFORMATION | MB_OK);
		}
	}
	else if( !strcmp(model_name,"IP6600D") )
	{
		GtkWidget *head_alignment_dialog;
		GtkWidget *execute_button;
		int 	n;

		/* Auto Head Alignment */
		if( !manual_head_mode ){

			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);
			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;
		
			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGIAUTO1, BJLREGIAUTO1LEN); p+=BJLREGIAUTO1LEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGIAUTO1LEN + BJLENDLEN + 1);
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
		else{		/* Manual Head Alignment */
			head_alignment_dialog = LookupWidget(NULL, 
												 "head_alignment_dialog");
			gtk_widget_realize(head_alignment_dialog);
			gtk_label_set_text(
				GTK_LABEL(LookupWidget(head_alignment_dialog, 
									   "head_alignment_label1")),
				LookupText(g_keytext_list, "utility_message_52"));
			gtk_widget_show(head_alignment_dialog);
			gtk_window_set_transient_for(GTK_WINDOW(head_alignment_dialog),
								 GTK_WINDOW(UI_DIALOG(g_main_window)->window));
			execute_button = LookupWidget(head_alignment_dialog, 
										  "head_alignment_execute_button");
			gtk_widget_grab_focus(execute_button);
			
			gtk_main();
			
			if (result != ID_OK)
				return ;

			p = buf;
			n = SetCurrentTime(p); p += n;		
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
			memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;		
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
			*p = 0x00;
			PutPrintData(buf,
				 n + BJLLEN + BJLSTARTLEN + BJLREGI1LEN + BJLENDLEN + 1);	
		
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
		
			if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_INFORMATION | MB_YES | MB_NO) == ID_NO) { 
			
				UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
							   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
				return;
			}
		
			nPageNum = 0;
			if (UtilRegiDialog(nPageNum) != ID_OK)		
				return ;						
		
			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
			for (i=0; i<nKindCnt; i++) {	
				int		nValue;
  		
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			}

			nValue = ItemValue[0];
  			sprintf(temp, BJLSETREG, lpBJLtbl[7],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

			nValue = ItemValue[6];
  			sprintf(temp, BJLSETREG, lpBJLtbl[8],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETREGLEN*(nKindCnt+2))+BJLENDLEN+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_51"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

			p = buf;
			n = SetCurrentTime(p); p += n;		
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;       
			memcpy(p, BJLREGI2, BJLREGI2LEN); p+=BJLREGI2LEN; 
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;              
			*p = 0x00;
			PutPrintData(buf,
						 n + BJLLEN + BJLSTARTLEN + BJLREGI2LEN + BJLENDLEN + 1);	
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
						   g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			
			
			nPageNum = 1;
			if (UtilRegiDialog(nPageNum) != ID_OK)
				return ;						
			
			
			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	

			nKindCntValue = 2;
			for (i=0; i<nKindCntValue; i++) {	
				int		nValue;
  		
				nValue = ItemValue[i];		
				sprintf(temp, BJLSETREG, lpBJLtbl[i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
			}

			nValue = ItemValue[1];
  			sprintf(temp, BJLSETREG, lpBJLtbl[3],
					nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;

			for (i=0; i<nKindCnt-nKindCntValue; i++) {	
				int		nValue;
				
				nValue = ItemValue[nKindCntValue+i];		
				sprintf(temp, BJLSETBANDREG, lpBJLtbl[nKindCntValue+i],
						nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
				memcpy(p, temp, BJLSETBANDREGLEN); p += BJLSETBANDREGLEN;
			}
			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
			*p = 0x00;			
			PutPrintData(buf,
						 BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
						 +(BJLSETREGLEN*(nKindCntValue+1))
						 +(BJLSETBANDREGLEN*nKindCnt)+BJLENDLEN+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
						   g_window_title, MB_ICON_INFORMATION | MB_OK);
		}
	}
	else {			// For BJS600
		int		n;
		
		msg = LookupText(g_keytext_list, "utility_message_20");
		if (UtilMessageBox(msg, g_window_title,
				MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_CANCEL)
			return ;			

		
		p = buf;
		n = SetCurrentTime(p); p += n;		
		
		
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
		memcpy(p, BJLREGI1, BJLREGI1LEN); p+=BJLREGI1LEN;		
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;				
		*p = 0x00;
		PutPrintData(buf,
			n + BJLLEN + BJLSTARTLEN + BJLREGI1LEN + BJLENDLEN + 1);	

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_3"),
			g_window_title, MB_ICON_EXCLAMATION | MB_YES | MB_NO) == ID_NO) {	
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_4"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			return;
		}
  
		
		nPageNum = 0;
		if (UtilRegiDialog(nPageNum) != ID_OK)		
			return ;						
	
		
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;			
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
		
  		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETREG, lpBJLtbl[i],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
  		}

  		
  		nValue = ItemValue[2];
  		sprintf(temp, BJLSETREG, lpBJLtbl[6],
			nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  		memcpy(p, temp, BJLSETREGLEN); p += BJLSETREGLEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;			
		PutPrintData(buf,
			BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
			+(BJLSETREGLEN*(nKindCnt+1))+BJLENDLEN+1);
  		
  		
		msg = LookupText(g_keytext_list, "utility_message_21");
		UtilMessageBox(msg, g_window_title,	MB_ICON_EXCLAMATION | MB_OK);
  		
		
		p = buf;
		n = SetCurrentTime(p); p += n;		

		
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;					
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;       
		memcpy(p, BJLBANDREGI1, BJLBANDREGI1LEN); p+=BJLBANDREGI1LEN; 
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;              
		*p = 0x00;
		PutPrintData(buf,
			n + BJLLEN + BJLSTARTLEN + BJLBANDREGI1LEN + BJLENDLEN + 1);	

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK);

		
		nPageNum = 1;
		if (UtilRegiDialog(nPageNum) != ID_OK)
			return ;						
  		
		
		p = buf;
  		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;						
  		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;           
		memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;  
		
  		for (i=0; i<nKindCnt; i++) {	
  			int		nValue;
  		
  			nValue = ItemValue[i];		
  			sprintf(temp, BJLSETBANDREG, lpBJLtbl[i],
				nValue<0? '-':(nValue>0? '+':'0'), abs(nValue));
  			memcpy(p, temp, BJLSETBANDREGLEN); p += BJLSETBANDREGLEN;
  		}
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;	
		*p = 0x00;			
		PutPrintData(buf,
			BJLLEN+BJLSTARTLEN+BJLCTRLMODELEN
			+(BJLSETBANDREGLEN*nKindCnt)+BJLENDLEN+1);

		
		UtilMessageBox(LookupText(g_keytext_list, "utility_message_5"),
			g_window_title, MB_ICON_INFORMATION | MB_OK);
	}
}





void UtilRollerCleaning(LPUIDB uidb)
{
	char		buf[256];
	char		*p = buf;
	char		*model_name;

	if (g_socketname == NULL)			
		return ;                        

	model_name = GetModelName();		

	if ( !strcmp(model_name, "BJF360")) {
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_17"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL)==ID_OK) {
			
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
			memcpy(p, BJLROLLER2, BJLROLLER2LEN); p+=BJLROLLER2LEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
			*p = 0x00;
			PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLROLLER2LEN+BJLENDLEN+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
		}
	} 
	else if( !strcmp(model_name, "PIXMAIP1000") || 
			 !strcmp(model_name, "PIXMAIP1500") ){

		int i,n;	
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_27"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL)==ID_OK) {

			n = SetCurrentTime(p); p+=n;	
			
			for( i=0; i<3; i++){
				memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
				memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
				memcpy(p, BJLROLLER4, BJLROLLER4LEN); p+=BJLROLLER4LEN;
				memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
			}
			*p = 0x00;
			PutPrintData(buf, n+3*(BJLLEN+BJLSTARTLEN
						 +BJLROLLER4LEN+BJLENDLEN)+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_28"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);

			p = buf;
			n = SetCurrentTime(p); p+=n;
			for( i=0; i<3; i++){
				memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
				memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
				memcpy(p, BJLROLLER4, BJLROLLER4LEN); p+=BJLROLLER4LEN;
				memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
			}
			*p = 0x00;
			PutPrintData(buf, n+3*(BJLLEN+BJLSTARTLEN+BJLROLLER4LEN+
						BJLENDLEN)+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
						
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_30"),
				g_window_title, MB_ICON_INFORMATION | MB_OK);
		}
	}
	else if( !strcmp(model_name,"I250") || !strcmp(model_name, "I255")){

		int i,n;	
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_27"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL)==ID_OK) {

			n = SetCurrentTime(p); p+=n;	
			
			for( i=0; i<3; i++){
				memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
				memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
				memcpy(p, BJLROLLER2, BJLROLLER2LEN); p+=BJLROLLER2LEN;
				memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
			}
			*p = 0x00;
			PutPrintData(buf, n+3*(BJLLEN+BJLSTARTLEN
						 +BJLROLLER2LEN+BJLENDLEN)+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_28"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);

			p = buf;
			n = SetCurrentTime(p); p+=n;
			for( i=0; i<3; i++){
				memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
				memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
				memcpy(p, BJLROLLER2, BJLROLLER2LEN); p+=BJLROLLER2LEN;
				memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
			}
			*p = 0x00;
			PutPrintData(buf, n+3*(BJLLEN+BJLSTARTLEN+BJLROLLER2LEN+
						BJLENDLEN)+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
						
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_30"),
				g_window_title, MB_ICON_INFORMATION | MB_OK);
		}
	}
	else if( !strcmp(model_name, "IP2200") ){

		int i,n;	
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_27"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL)==ID_OK) {

			n = SetCurrentTime(p); p+=n;	
			
			for( i=0; i<3; i++){
				memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
				memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
				memcpy(p, BJLROLLER4, BJLROLLER4LEN); p+=BJLROLLER4LEN;
				memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
			}
			*p = 0x00;
			PutPrintData(buf, n+3*(BJLLEN+BJLSTARTLEN
						 +BJLROLLER4LEN+BJLENDLEN)+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_28"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);

			p = buf;
			n = SetCurrentTime(p); p+=n;
			for( i=0; i<3; i++){
				memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
				memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
				memcpy(p, BJLROLLER4, BJLROLLER4LEN); p+=BJLROLLER4LEN;
				memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
			}
			*p = 0x00;
			PutPrintData(buf, n+3*(BJLLEN+BJLSTARTLEN+BJLROLLER4LEN+
						BJLENDLEN)+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
						
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_30"),
				g_window_title, MB_ICON_INFORMATION | MB_OK);
		}
	}
	else {
		if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_10"),
			g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL)==ID_OK) {

			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
			memcpy(p, BJLROLLER1, BJLROLLER1LEN); p+=BJLROLLER1LEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
			*p = 0x00;
			PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLROLLER1LEN+BJLENDLEN+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_13"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);

			p = buf;
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
			memcpy(p, BJLROLLER2, BJLROLLER2LEN); p+=BJLROLLER2LEN;
			memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
			*p = 0x00;
			PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLROLLER2LEN+BJLENDLEN+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_14"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);

			PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLROLLER2LEN+BJLENDLEN+1);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
				g_window_title, MB_ICON_EXCLAMATION | MB_OK);
			
			UtilMessageBox(LookupText(g_keytext_list, "utility_message_15"),
				g_window_title, MB_ICON_INFORMATION | MB_OK);
		}
	}
}


void UtilPowerOff(LPUIDB uidb)
{
	char		buf[128];
	char		*p = buf;

	if (g_socketname == NULL)			
		return ;                        

	if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_8"),
		g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL) == ID_OK) {

		memcpy(p, bjl_cmds, BJLLEN);p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN);p+=BJLSTARTLEN;
		memcpy(p, BJLPOWEROFF, BJLPOWEROFFLEN);p+=BJLPOWEROFFLEN;
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
		*p = 0x00;
		PutPrintData(buf, BJLLEN+BJLSTARTLEN+BJLPOWEROFFLEN+BJLENDLEN+1);
	}
}


void UtilSetConfig(LPUIDB uidb)
{
	char		buf[128];
	char		*p = buf;
	int			cmd_bytes;			
	GtkWidget*	special_dialog;
	GtkWidget*	send_button;
	char		*model_name;
	
	if (g_socketname == NULL)		
		return;						

	model_name = GetModelName();
	
	if (!strcmp(model_name, "BJF900") || !strcmp(model_name, "BJF9000") ||
		!strcmp(model_name, "BJS500") || !strcmp(model_name, "PIXUS550I") ||
		!strcmp(model_name, "PIXUS850I") || !strcmp(model_name, "PIXUS950I")||
		!strcmp(model_name, "I250") || !strcmp(model_name, "I255") ||
		!strcmp(model_name,"PIXUS560I") || !strcmp(model_name,"PIXUS860I") ||
		!strcmp(model_name,"PIXUS990I") ||
		!strcmp(model_name, "PIXUSIP3100") || 
		!strcmp(model_name, "PIXUSIP4100") ||
		!strcmp(model_name, "PIXUSIP8600") ||
		!strcmp(model_name, "PIXMAIP1000") ||
		!strcmp(model_name, "PIXMAIP1500") ||
		!strcmp(model_name, "IP2200") ||
		!strcmp(model_name, "IP4200") || !strcmp(model_name, "MP500") ||
		!strcmp(model_name, "IP7500") ||
		!strcmp(model_name, "IP6600D")){
		SetDryLevel();
		return;
	}

	special_dialog = LookupWidget(NULL, "special_dialog");	
	gtk_widget_realize(special_dialog);			
	gtk_widget_show(special_dialog);			
	gtk_window_set_transient_for(GTK_WINDOW(special_dialog),
		GTK_WINDOW(UI_DIALOG(g_main_window)->window));
	send_button = LookupWidget(special_dialog, "special_send_button");
	gtk_widget_grab_focus(send_button);


	gtk_main();									
  
  	if (result != ID_OK)		
		return ;				

 	if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_9"),
		g_window_title,	MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL)==ID_CANCEL){
 		special_set_default(special_dialog);
		return ;		
	}


	if (!strcmp(model_name, "BJF360")) {		
		
		if (page_pause_mode) {		
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;
			memcpy(p, BJLPAGEDELAY, BJLPAGEDELAYLEN); p+=BJLPAGEDELAYLEN;
			cmd_bytes = BJLLEN + BJLSTARTLEN
						+ BJLCTRLMODELEN + BJLPAGEDELAYLEN;
		} else {		
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;
			memcpy(p, BJLNOPAGEDELAY, BJLNOPAGEDELAYLEN); p+=BJLNOPAGEDELAYLEN;
			cmd_bytes = BJLLEN + BJLSTARTLEN
						+ BJLCTRLMODELEN + BJLNOPAGEDELAYLEN;
		}

		if (scan_pause_mode) {	
			memcpy(p, BJLSCANDELAY, BJLSCANDELAYLEN); p+=BJLSCANDELAYLEN;
			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
			*p = 0x00;
			cmd_bytes += BJLSCANDELAYLEN + BJLENDLEN + 1;
		} else {		
			memcpy(p, BJLNOSCANDELAY, BJLNOSCANDELAYLEN); p+=BJLNOSCANDELAYLEN;
			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
			*p = 0x00;
			cmd_bytes += BJLNOSCANDELAYLEN + BJLENDLEN + 1;
		}
	
	} else if (!strcmp(model_name, "BJS600") | !strcmp(model_name, "BJS630") |
			   !strcmp(model_name, "BJS6300") | !strcmp(model_name, "BJS300"))
		{	
		
		if (page_pause_mode) {		
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;
			memcpy(p, BJLPAGEDELAY1, BJLPAGEDELAYLEN1); p+=BJLPAGEDELAYLEN1;
			cmd_bytes = BJLLEN + BJLSTARTLEN
						+ BJLCTRLMODELEN + BJLPAGEDELAYLEN1;
		} else {		
			memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
			memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
			memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;
			memcpy(p, BJLNOPAGEDELAY1, BJLNOPAGEDELAYLEN1);
			p+=BJLNOPAGEDELAYLEN1;
			cmd_bytes = BJLLEN + BJLSTARTLEN
						+ BJLCTRLMODELEN + BJLNOPAGEDELAYLEN1;
		}

		if (scan_pause_mode) {	
			memcpy(p, BJLSCANDELAY1, BJLSCANDELAYLEN1); p+=BJLSCANDELAYLEN1;
			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
			*p = 0x00;
			cmd_bytes += BJLSCANDELAYLEN1 + BJLENDLEN + 1;
		} else {		
			memcpy(p, BJLNOSCANDELAY1, BJLNOSCANDELAYLEN1);
			p+=BJLNOSCANDELAYLEN1;
			memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
			*p = 0x00;
			cmd_bytes += BJLNOSCANDELAYLEN1 + BJLENDLEN + 1;
		}
	} else {	
		return;						
	}
	
	PutPrintData(buf, cmd_bytes);	
}


void UtilAutoPower(LPUIDB uidb)
{
	GtkWidget*	autopower_dialog;	
	GtkWidget*	send_button;
	char		*param;				
	char		buf[128];
	char		temp[32];
	int			cmd_bytes, total_bytes;
	char		*p = buf;
	GtkWidget	*poweron_combo, *poweroff_combo;
	
	if (g_socketname == NULL)			
		return ;                        
	
	autopower_dialog = LookupWidget(NULL, "autopower_dialog");	
	gtk_widget_realize(autopower_dialog);			
	
	poweron_combo = LookupWidget(autopower_dialog, "autopower_combo1");	
	SetComboBox(poweron_combo, AutoPowerOnKey, 2, poweron_index);		
	poweroff_combo = LookupWidget(autopower_dialog, "autopower_combo2");	
	SetComboBox(poweroff_combo, AutoPowerOffKey, 6, poweroff_index);
	
	gtk_widget_show(autopower_dialog);				
	gtk_window_set_transient_for(GTK_WINDOW(autopower_dialog),
		GTK_WINDOW(UI_DIALOG(g_main_window)->window));
	send_button = LookupWidget(autopower_dialog, "autopower_button1");
	gtk_widget_grab_focus(send_button);

	gtk_main();									
  
  	if (result != ID_OK)		
		return ;				
	
	
 	if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_9"),
		g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL)==ID_CANCEL){
		autopower_set_default();
 		return ;
	}
	
	param = AutoPowerOnValue[ poweron_index ];	
	memcpy (p, bjl_cmds, BJLLEN); p+=BJLLEN;				
	memcpy (p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
	memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
	cmd_bytes = sprintf(temp, BJLAUTOPOWERON, param);		
	memcpy (p, temp, cmd_bytes); p+=cmd_bytes;
	total_bytes = BJLLEN + BJLSTARTLEN + BJLCTRLMODELEN + cmd_bytes;
	
	param = AutoPowerOffValue[ poweroff_index ];	
	cmd_bytes = sprintf(temp, BJLAUTOPOWEROFF, param);		
	memcpy (p, temp, cmd_bytes); p+=cmd_bytes;
	memcpy (p, BJLEND, BJLENDLEN); p+=BJLENDLEN;			
	*p = 0x00;							
	total_bytes += cmd_bytes + BJLENDLEN + 1;
	
	PutPrintData(buf, total_bytes);		
	
}



void UtilInkReset(LPUIDB uidb)
{

	GtkWidget*	reset_dialog;	
	char		buf[128];
	char		*p = buf;
	char __attribute__ ((unused)) *model_name;
	int			total_bytes=0;
	GtkWidget*	cancel_button;
	
	if (g_socketname == NULL)		
		return;						

	model_name = GetModelName();

	reset_dialog = LookupWidget(NULL, "ink_reset_dialog");	
	gtk_widget_realize(reset_dialog);			
	gtk_widget_show(reset_dialog);				
	gtk_window_set_transient_for(GTK_WINDOW(reset_dialog),
		GTK_WINDOW(UI_DIALOG(g_main_window)->window));
	
	cancel_button = LookupWidget(reset_dialog, "ink_reset_cancel_button");
	gtk_widget_grab_focus(cancel_button);
	gtk_widget_grab_default(cancel_button);
	gtk_widget_set_sensitive( 
				LookupWidget(reset_dialog, "ink_reset_excute_button"), FALSE);
	

	gtk_main();									
  
  	if (result != ID_OK)		
		return ;				
	
	
	if(black_reset==0 && color_reset==0)
		return;
	
	if(black_reset){
		memcpy (p, bjl_cmds, BJLLEN); p+=BJLLEN;				
		memcpy (p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
		memcpy (p, BJLRESETBLACK, BJLRESETBLACKLEN); p+=BJLRESETBLACKLEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;		
		*p = 0x00;
		total_bytes = BJLLEN + BJLSTARTLEN + BJLRESETBLACKLEN + BJLENDLEN + 1;
	}

	if(color_reset){
		memcpy (p, bjl_cmds, BJLLEN); p+=BJLLEN;				
		memcpy (p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
		memcpy (p, BJLRESETCMY, BJLRESETCMYLEN); p+=BJLRESETCMYLEN;
		memcpy(p, BJLEND, BJLENDLEN); p+=BJLENDLEN;		
		*p = 0x00;
		total_bytes += BJLLEN + BJLSTARTLEN + BJLRESETCMYLEN + BJLENDLEN + 1;
	}
	
	PutPrintData(buf, total_bytes);

}


void UtilInkWarning(LPUIDB uidb)
{

	GtkWidget*	warning_dialog;	
	char		buf[128];
	int			cmd_bytes;
	char		*p = buf;
	char 		temp[32];
	char __attribute__ ((unused)) *model_name;
	int 		total_bytes;
	GtkWidget*	send_button;
	
	if (g_socketname == NULL)		
		return;						

	model_name = GetModelName();

	
	warning_dialog = LookupWidget(NULL, "ink_warning_dialog");	
	gtk_widget_realize(warning_dialog);			
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(LookupWidget(warning_dialog,
			   "ink_warning_checkbutton")),	warning_mode);

	gtk_widget_show(warning_dialog);				
	gtk_window_set_transient_for(GTK_WINDOW(warning_dialog),
		GTK_WINDOW(UI_DIALOG(g_main_window)->window));
	send_button = LookupWidget(warning_dialog, "ink_warning_send_button");
	gtk_widget_grab_focus(send_button);


	gtk_main();									
  
  	if (result != ID_OK)		
		return ;				
	

 	if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_9"),
		g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL)==ID_CANCEL){
		warning_mode = 0;
 		return ;
	}

	memcpy (p, bjl_cmds, BJLLEN); p+=BJLLEN;				
	memcpy (p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
	memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
	

	cmd_bytes = sprintf(temp, BJLINKDETECTION, SwitchString[warning_mode]);	
	memcpy (p, temp, cmd_bytes); p+=cmd_bytes;
	memcpy (p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
	*p = 0x00;							
	total_bytes = BJLLEN + BJLSTARTLEN + BJLCTRLMODELEN + 
					cmd_bytes + BJLENDLEN + 1;
	
	PutPrintData(buf, total_bytes);		


}


void UtilQuietMode(LPUIDB uidb)
{

	GtkWidget*	quiet_dialog;	
	char		buf[128];
	int			cmd_bytes;
	char		*p = buf;
	char 		temp[32];
	char __attribute__ ((unused)) *model_name;
	int 		total_bytes;
	GtkWidget*	send_button;
	
	if (g_socketname == NULL)			
		return ;                        

	model_name = GetModelName();

	quiet_dialog = LookupWidget(NULL, "quiet_dialog");	
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(LookupWidget(quiet_dialog, "quiet_checkbutton")),
		quiet_mode);
	gtk_widget_realize(quiet_dialog);			
	gtk_widget_show(quiet_dialog);				
	gtk_window_set_transient_for(GTK_WINDOW(quiet_dialog),
		GTK_WINDOW(UI_DIALOG(g_main_window)->window));
	send_button = LookupWidget(quiet_dialog, "quiet_send_button");
	gtk_widget_grab_focus(send_button);

	gtk_main();									
  
  	if (result != ID_OK)		
		return ;				

 	if(UtilMessageBox(LookupText(g_keytext_list, "utility_message_9"),
		g_window_title, MB_ICON_EXCLAMATION | MB_OK | MB_CANCEL)==ID_CANCEL){
		quiet_mode = 0;
 		return ;
	}

	memcpy (p, bjl_cmds, BJLLEN); p+=BJLLEN;				
	memcpy (p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;		
	memcpy(p, BJLCTRLMODE, BJLCTRLMODELEN); p+=BJLCTRLMODELEN;	
	

	cmd_bytes = sprintf(temp, BJLSILENT, SwitchString[quiet_mode]);		
	memcpy (p, temp, cmd_bytes); p+=cmd_bytes;
	memcpy (p, BJLEND, BJLENDLEN); p+=BJLENDLEN;
	*p = 0x00;							
	total_bytes = BJLLEN + BJLSTARTLEN + BJLCTRLMODELEN + 
					cmd_bytes + BJLENDLEN + 1;
	
	PutPrintData(buf, total_bytes);		

}

void UtilPlateCleaning(LPUIDB uidb)
{
	GtkWidget*	plate_dialog;
	GtkWidget*	execute_button;
	char		buf[128];
	char		*p = buf;
	char 		*model_name;

	if (g_socketname == NULL)			
		return ;                        

	model_name = GetModelName();

	if ( !strcmp(model_name, "PIXUSIP3100") ||
		 !strcmp(model_name, "PIXUSIP4100") ||
		 !strcmp(model_name, "PIXUSIP8600") ||
		 !strcmp(model_name, "PIXMAIP1500") ||
		 !strcmp(model_name, "IP2200") ||
		 !strcmp(model_name, "IP4200") ||
		 !strcmp(model_name, "IP6600D") ||
		 !strcmp(model_name, "IP7500") ||
		 !strcmp(model_name, "MP500") ){
		int n;

		plate_dialog = LookupWidget(NULL, "plate_cleaning_dialog");	
		gtk_widget_realize(plate_dialog);	
		gtk_widget_show(plate_dialog);				
		gtk_window_set_transient_for(GTK_WINDOW(plate_dialog),
						GTK_WINDOW(UI_DIALOG(g_main_window)->window));
		execute_button = LookupWidget(plate_dialog, 
									  "plate_cleaning_execute_button");
		gtk_widget_grab_focus(execute_button);
		
		gtk_main();									
		
		if (result != ID_OK)		
			return ;				

		n = SetCurrentTime(p); p+=n;
		memcpy(p, bjl_cmds, BJLLEN); p+=BJLLEN;
		memcpy(p, BJLSTART, BJLSTARTLEN); p+=BJLSTARTLEN;
		memcpy(p, BJLROLLER3, BJLROLLER3LEN); p+=BJLROLLER3LEN;
		memcpy(p, BJLEND, BJLENDLEN);p+=BJLENDLEN;
		*p = 0x00;
		
		PutPrintData(buf, n+BJLLEN+BJLSTARTLEN+BJLROLLER3LEN+BJLENDLEN+1);

		UtilMessageBox(LookupText(g_keytext_list, "utility_message_6"),
					   g_window_title, MB_ICON_EXCLAMATION | MB_OK);

	}
	else{
		return;
	}

}

void UtilInkCartridgeSet( LPUIDB uidb )
{
	char 		*model_name;

	if (g_socketname == NULL)
		return ;

	model_name = GetModelName();

	if ( !strcmp(model_name, "IP2200") ){

		if (UtilInkCartrigeDialog() != ID_OK)
			return ;

		UpdateMenuLink(CNCL_INKCARTRIDGESETTINGS, cartridge_index);
	}
}



/* Ver.2.80 GtkComboBox */
/* Set UI string list corresponding to "keytbl" to "combo" and select index item */
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



char	*GetParamValue(char **Keytbl, char **Valuetbl, int n, char *mode)
{
	int			i;
	
	for (i=0; i < n; i++) {
		if (!strcmp(LookupText(g_keytext_list, Keytbl[i]), mode))	
			return Valuetbl[i];		
	}
	
	return Valuetbl[0];		
}


int GetAutoPowerIndex(char **Keytbl, int n, char *mode)
{
	int			i;
	
	for (i=0; i < n; i++) {
		if (!strcmp(LookupText(g_keytext_list, Keytbl[i]), mode))	
			return i;		
	}
	return 0;		
}

int nValueToIndex(short *nValuetbl, int n, short nValue)
{
	int	i;

	for (i=0; i < n; i++) {
		if ( nValuetbl[i] == nValue )
			return i;
	}
	return 0;
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


static char* GetPatternFileName(short pattern_type )
{
	int		i, index;
	char	*model_name;

	model_name = GetModelName();		
	index = -1;
	for (i=0; i < sizeof(TestPatternInfo)/sizeof(TESTPATTERNINFO); i++) {		
		if (!strcmp(TestPatternInfo[i].ModelName, model_name)) {	
			index = i;			
			break;
		}
	}
	index = (index == -1)? 0 : index;	
	
	return (TestPatternInfo[index].TestPatternTbl[pattern_type]);		
}

static int	CreateRegiBSCC( char* bscc_buf, int* bscc_len, char* bscc_file,
							short *ItemValue, short page )
{

	char* model_name;	
	int index, i;
	int reg_value;
	char temp[REGI_TMP_SIZE];
	PBSCCREGTBL pRegTbl;
	

	model_name = GetModelName();
	index = -1;
	
	for (i=0; i < sizeof(BsccRegInfo)/sizeof(BSCCREGINFO); i++) {		
		if (!strcmp(BsccRegInfo[i].ModelName, model_name)) {	
			index = i;			
			break;
		}
	}
	index = (index == -1)? 0 : index;	

	/* Bscc File Name */
	memset(bscc_file, 0, 256);
	strncpy(bscc_file, BSCCFILEPATH, 255);
	strncat(bscc_file, BsccRegInfo[index].bscc_file, 254-strlen(bscc_file)); 

	pRegTbl = &BsccRegInfo->tBsccRegTbl[page];

	/* Create BSCC REG Command */
	memset(bscc_buf, 0, 256);
	strncpy(bscc_buf, BSCCREGTAG, 255);
	
	for( i=0; i< pRegTbl->reg_num; i++ ){

		int reg_value_index = pRegTbl->reg_value_index[i];
		int reg_str_index = pRegTbl->reg_str_index[i];
		reg_value =	ItemValue[reg_value_index];

		sprintf(temp, BSCCREGFORMAT,pRegTbl->pBJLTbl[reg_str_index],
				reg_value<0? '-': '+', abs(reg_value));
		strncat(bscc_buf, temp, BSCCREGLEN);
	}
	*bscc_len = pRegTbl->reg_num*BSCCREGLEN + 5;

	return 0;
}

static int IsBsccTag( FILE** fp )
{

	FILE* fpTmp = NULL;
	int cc;
	char bufTmp[128];
	int pos = 0;
	int result = 1;

	fpTmp = *fp;

	while( (cc=fgetc(fpTmp)) != EOF ){
		if( cc == ']' )
			bufTmp[pos] = 0x00;	
		else if( cc == 0x09 || cc == 0x20 )
			;
		else if( cc == 0x0A ){
			result = strcmp( bufTmp, BSCC_TAG) ? 0 : 1;
			break;
		}	
		else
			bufTmp[pos++] = cc;	
	}
		
	*fp = fpTmp;
	return result;
		
}

static int WriteToBSCCFile( char* bscc_file, char* bscc_buf, short bscc_id )
{

	FILE* fp = NULL;	
	int cc;
	char bufTmp[128];
	char *pStr[2];
	short id;

	int isBscc, isFirst;
	int index = 0;
	int pos = 0;
	int result = 1;
	
	/* Open BSCC File */
	if( (fp = fopen( bscc_file, "r+")) == NULL )
		return -1;	
		
	isFirst = 0;
	isBscc = 0;
	while( (cc = fgetc(fp)) != EOF ){

		if( cc == '#' ){		// Comment
			while( (cc = fgetc(fp)) != EOF )
				if( cc == 0x0A )
					break;
		}
		else if( cc == '[' ){
			isBscc = IsBsccTag(&fp) ? 1:0;
			if( isBscc )
				isFirst = 1;	
		}
		else{
			if( isBscc ){
				if( cc == 0x0A ){	// End Of Command Line
					bufTmp[pos] = 0x00;	
					id = (short)atoi(pStr[1] );
					if( id == bscc_id ){
						if(	strlen(pStr[0] ) == strlen(bscc_buf) ){
							fseek(fp, -(strlen(pStr[0])+strlen(pStr[1])+2),
								   SEEK_CUR);
							if( (fputs(bscc_buf,fp)) != EOF )
								result = 0;	
							break;
						}
					}
					else{
						isFirst = 1; 
						index = 0;
						pos = 0;
					}
				}
				else if( cc == 0x09 || cc == 0x20 ){	// Space or Tab
					isFirst = 1;	
					bufTmp[pos++] = 0x00;
				}
				else{			// Command string or Id string
					if( isFirst ){
						bufTmp[pos] = cc;
						pStr[index++] = &bufTmp[pos];
						pos++;
						isFirst = 0;
					}
					else
						bufTmp[pos++] = cc;
				}
			}
		}
	}
			
	
	if(fp != NULL)
		fclose(fp);	
	return result;

}



static int WriteToPrintFile( char* print_file, char* bscc_buf, int bscc_len,
							 short bscc_id )
{

	int fdTmp;
	char* ptr;
	int total_size, w_size;


	/* CreateBsccTmpFile */
	sprintf(print_file, "/tmp/%02dutl%d", bscc_id, getpid());
	if( (fdTmp=open(print_file, O_WRONLY|O_CREAT|O_TRUNC, 0644)) 
		== -1 )
		goto open_error;

	ptr = bscc_buf;
	total_size = bscc_len;
	while( 1 ){
		w_size = write(fdTmp, ptr, total_size);

		if ( w_size == -1 ){
			goto write_error;
		}
		
		if ( w_size < total_size ){
			total_size -= w_size;
			ptr    += w_size;
		}
		else break;
	}

	close(fdTmp);
	return 0;

 write_error:
	close(fdTmp);
	unlink(print_file);
 open_error:
	return -1;


}


