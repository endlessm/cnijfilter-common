/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2008
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
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


//#ifdef HAVE_CONFIG_H
//#  include <config.h>
//#endif

#include <gtk/gtk.h>
#ifdef	USE_LIB_GLADE
#	include <glade/glade.h>
#endif
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "callbacks.h"
#ifndef	USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"


static const short borderless_media_value[] =		//Ver.3.00:order changed.
{
	CND_MEDIA_PHOTO_PAPER_PLUS_GLOSSY_II,
	CND_MEDIA_PHOTO_PAPER_PRO_II,			//Ver.3.00(Photo Paper Pro II)
	CND_MEDIA_PHOTO_PAPER_PRO_PLATINUM,		//Ver.3.00(Photo Paper Pro Platinum)
	CND_MEDIA_PROPHOTO,
	CND_MEDIA_SUPER_PHOTO,
	CND_MEDIA_DUPLEX_GLOSSY_PAPER,
	CND_MEDIA_PHOTO_PAPER_SEMI_GLOSS,		//Ver.2.90
	CND_MEDIA_GLOSSYPHOTO,
	CND_MEDIA_MATTE,
	CND_MEDIA_INKJET_POST,
	CND_MEDIA_POSTCARD,
	CND_MEDIA_OTHER_PHOTO_PAPER,
	CND_MEDIA_PLAIN,
	-1
};


static void InitBorderlessMedia(UIMediaBorderDialog* dialog)
{
	GList* media_type_list_top = GetComboList(CNCL_MEDIATYPE);
	short media_type_num = GetComboNum(CNCL_MEDIATYPE);
	int i = 0, j;

	dialog->media_list = NULL;

	while( borderless_media_value[i] != -1 )
	{
		GList* media_type_list = media_type_list_top;

		for( j = 0 ; j < media_type_num ; j++ )
		{
			short media_type_value
				= NameToValue(CNCL_MEDIATYPE, (gchar*)media_type_list->data);

			if( borderless_media_value[i] == media_type_value )
			{
				dialog->media_list
					= g_list_append(dialog->media_list, media_type_list->data);
				break;
			}
			media_type_list = media_type_list->next;
		}
		i++;
	}

	g_list_free(media_type_list_top);
}

static void FreeBorderlessMedia(UIMediaBorderDialog* dialog)
{
	g_list_free(dialog->media_list);
}

UIMediaBorderDialog* CreateMediaBorderDialog(UIDialog* parent)
{
	GtkWidget* window;
	// Create dialog.
	UIMediaBorderDialog* dialog
		 = (UIMediaBorderDialog*)CreateDialog(
				sizeof(UIMediaBorderDialog), parent);

	// Create dialog window.
#ifdef	USE_LIB_GLADE
	UI_DIALOG(dialog)->window = window
		= LookupWidget(NULL, "mediaborder_dialog");
#else
	UI_DIALOG(dialog)->window = window = create_mediaborder_dialog();
#endif

	InitBorderlessMedia(dialog);

	return dialog;
}

void DisposeMediaBorderDialog(UIMediaBorderDialog* dialog)
{
	FreeBorderlessMedia(dialog);

	DisposeDialog((UIDialog*)dialog);
}


int ShowMediaBorderDialog(UIMediaBorderDialog* dialog, short media_type)
{
	GtkWidget* message_label
		= LookupWidget(UI_DIALOG(dialog)->window, "mediaborder_dialog_label");
	gchar* dialog_msg
		= LookupText(g_keytext_list, "mediaborder_dialog_message1");
	gchar* media_type_msg = GetCurrentString(CNCL_MEDIATYPE);
	gchar* message = (gchar*)g_malloc(strlen(dialog_msg)
						 + strlen(media_type_msg) +1 );	/* Ver.2.80 "1":\0 */

	GtkWidget* alert_label = LookupWidget(UI_DIALOG(dialog)->window,
									"mediaborder_dialog_alert_label");
	gchar* alert_msg
		= LookupText(g_keytext_list, "LUM_IDD_MEDIA_CHANGE_ETOE_IDC_STT_MEDIA_NOTE_ETOE");	//Ver.3.00(change message)

	sprintf(message, dialog_msg, media_type_msg);
	gtk_label_set_text(GTK_LABEL(message_label), message);
	gtk_label_set_text(GTK_LABEL(alert_label), alert_msg);

	gtk_window_set_title(
		GTK_WINDOW(UI_DIALOG(dialog)->window), g_window_title);	
	gtk_window_set_position(
		GTK_WINDOW(UI_DIALOG(dialog)->window), GTK_WIN_POS_CENTER);	

	g_free(message);

	if( dialog->media_list )
	{
		short	def_media = -1;
		
		def_media = GetCurrentnValue( CNCL_DEFMEDIATYPE_MINUS );
		
		if( def_media < 0 )		/* CNCL_DEFMEDIATYPE_MINUS value is not available */
		{
			SetGListToComboBox(UI_DIALOG(dialog)->window, "mediaborder_dialog_combo",
						dialog->media_list, dialog->media_list->data , CNCL_MEDIATYPE);	/* Set the 1st item to default */
		}
		else					/* Ver.2.90: Set CNCL_DEFMEDIATYPE_MINUS current value to deault */
		{
			SetGListToComboBox(UI_DIALOG(dialog)->window, "mediaborder_dialog_combo",
						dialog->media_list, ValueToName(CNCL_MEDIATYPE, def_media ) , CNCL_MEDIATYPE);
		}
	
	}

	ShowDialog((UIDialog*)dialog, "mediaborder_dialog_ok_button"); 

	return dialog->apply? dialog->selected_media : -1;
}

void HideMediaBorderDialog(UIMediaBorderDialog* dialog, gboolean apply)
{
	if( apply )
	{
		/* Ver.2.80 */
		GtkWidget* combo = LookupWidget( UI_DIALOG(dialog)->window , "mediaborder_dialog_combo" );
		dialog->selected_media = NameToValue(CNCL_MEDIATYPE, 
								(char*)gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo)) );
	}

	dialog->apply = apply;

	HideDialog((UIDialog*)dialog);
}


gboolean IsAvailableMediaBorder(UIMediaBorderDialog* dialog, short media_type)
{
	GList* media_list = dialog->media_list;

	// Return FALSE in case for plain paper.
	if( media_type == CND_MEDIA_PLAIN )
		return FALSE;

	while( media_list )
	{
		gchar* media_name = (gchar*)media_list->data;

		if( media_type == NameToValue(CNCL_MEDIATYPE, media_name) )
			return TRUE;

		media_list = media_list->next;
	}

	return FALSE;
}

gboolean
on_mediaborder_dialog_delete_event       (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	HideMediaBorderDialog(g_mediaborder_dialog, FALSE);
	return TRUE;
}

void
on_mediaborder_dialog_ok_button_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
	HideMediaBorderDialog(g_mediaborder_dialog, TRUE);
}


void
on_mediaborder_dialog_cancel_button_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
	HideMediaBorderDialog(g_mediaborder_dialog, FALSE);
}

