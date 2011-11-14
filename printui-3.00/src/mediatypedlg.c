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


static void InitCartridgeMedia(UIMediaTypeDialog* dialog)
{
	GList* cartridge_list_top = GetComboList(CNCL_CARTRIDGE);
	GList* cartridge_list = cartridge_list_top;
	short cartridge_num = GetComboNum(CNCL_CARTRIDGE);
	short save_cartridge_type = GetCurrentnValue(CNCL_CARTRIDGE);
	int i;

	for( i = 0 ; i < CND_CARTRIDGE_MAX ; i++ )
		dialog->media_list[i] = NULL;

	for( i = 0 ; i < cartridge_num ; i++ )
	{
		short cartridge_type
			= NameToValue(CNCL_CARTRIDGE, (gchar*)cartridge_list->data);

		UpdateMenuLink(CNCL_CARTRIDGE, cartridge_type);

		dialog->media_list[cartridge_type] = GetComboList(CNCL_MEDIATYPE);
		cartridge_list = cartridge_list->next;
	}
	g_list_free(cartridge_list_top);

	UpdateMenuLink(CNCL_CARTRIDGE, save_cartridge_type);
}

static void FreeCartridgeMedia(UIMediaTypeDialog* dialog)
{
	int i;

	for( i = 0 ; i < CND_CARTRIDGE_MAX ; i++ )
	{
		if( dialog->media_list[i] )
			g_list_free(dialog->media_list[i]);
	}
}

UIMediaTypeDialog* CreateMediaTypeDialog(UIDialog* parent)
{
	GtkWidget* window;
	// Create dialog.
	UIMediaTypeDialog* dialog
		 = (UIMediaTypeDialog*)CreateDialog(sizeof(UIMediaTypeDialog), parent);

	// Create dialog window.
#ifdef	USE_LIB_GLADE
	UI_DIALOG(dialog)->window = window = LookupWidget(NULL, "mediatype_dialog");
#else
	UI_DIALOG(dialog)->window = window = create_mediatype_dialog();
#endif

	InitCartridgeMedia(dialog);

	return dialog;
}

void DisposeMediaTypeDialog(UIMediaTypeDialog* dialog)
{
	FreeCartridgeMedia(dialog);

	DisposeDialog((UIDialog*)dialog);
}

int ShowMediaTypeDialog(UIMediaTypeDialog* dialog,
					short media_type, short new_cartridge)
{
	GList* media_list = dialog->media_list[new_cartridge];

	if( media_list )
	{
		GtkWidget* message_label
			= LookupWidget(UI_DIALOG(dialog)->window, "mediatype_dialog_label");
		gchar* dialog_msg
			 = LookupText(g_keytext_list, "mediatype_dialog_message");
		gchar* media_type_msg = GetCurrentString(CNCL_MEDIATYPE);

		gchar* message = (gchar*)g_malloc(strlen(dialog_msg)
								 + strlen(media_type_msg) +1 );	/* Ver.2.80 "1":\0 */

		sprintf(message, dialog_msg, media_type_msg);
		gtk_label_set_text(GTK_LABEL(message_label), message);

		g_free(message);

		/* Ver.2.80*/
		SetGListToComboBox(UI_DIALOG(dialog)->window, "mediatype_dialog_combo",
						media_list, media_list->data , CNCL_MEDIATYPE);
		
	}

	ShowDialog((UIDialog*)dialog, "mediatype_dialog_ok_button"); 

	return dialog->apply? dialog->selected_media : -1;
}

void HideMediaTypeDialog(UIMediaTypeDialog* dialog, gboolean apply)
{
	if( apply )
	{
		/* Ver.2.80 */
		GtkWidget* combo = LookupWidget( UI_DIALOG(dialog)->window , "mediatype_dialog_combo" );
		dialog->selected_media = NameToValue(CNCL_MEDIATYPE, 
								(char*)gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo)) );
	}

	dialog->apply = apply;

	HideDialog((UIDialog*)dialog);
}


gboolean IsAvailableMedia(UIMediaTypeDialog* dialog,
					short media_type, short new_cartridge)
{
	GList* media_list = dialog->media_list[new_cartridge];

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
on_mediatype_dialog_delete_event       (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	HideMediaTypeDialog(g_mediatype_dialog, FALSE);
	return TRUE;
}

void
on_mediatype_dialog_ok_button_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
	HideMediaTypeDialog(g_mediatype_dialog, TRUE);
}


void
on_mediatype_dialog_cancel_button_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
	HideMediaTypeDialog(g_mediatype_dialog, FALSE);
}


