/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2007
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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


UIPageSizeDialog* CreatePageSizeDialog(UIDialog* parent)
{
	GtkWidget* window;
	// Create dialog.
	UIPageSizeDialog* dialog
		 = (UIPageSizeDialog*)CreateDialog(
				sizeof(UIPageSizeDialog), parent);

	// Create dialog window.
#ifdef	USE_LIB_GLADE
	UI_DIALOG(dialog)->window = window
		= LookupWidget(NULL, "pagesize_dialog");
#else
	UI_DIALOG(dialog)->window = window = create_pagesize_dialog();
#endif

	return dialog;
}

void DisposePageSizeDialog(UIPageSizeDialog* dialog)
{
	DisposeDialog((UIDialog*)dialog);
}

gboolean ShowPageSizeDialog(UIPageSizeDialog* dialog)
{
	/* Ve.2.80 */
	GtkWidget* message_label;
	gchar* dialog_msg;
	gchar* message;
	gchar* change_to;

	message_label = LookupWidget(UI_DIALOG(dialog)->window, "change_papersource_message_label");
	
	/* Create message */
	dialog_msg = LookupText(g_keytext_list, "supply_change_mes");
	change_to = (gchar*)ValueToName( CNCL_MEDIASUPPLY , CND_SUPPLY_ASF );
	message = (gchar*)g_malloc( strlen(dialog_msg) + strlen(change_to) +1 );	/* Ver.2.80 "1":\0 */
	sprintf( message , dialog_msg , change_to );
	
	/* Set message */
	gtk_label_set_text(GTK_LABEL(message_label), message);
	

	gtk_window_set_position(
		GTK_WINDOW(UI_DIALOG(dialog)->window), GTK_WIN_POS_CENTER);	

	ShowDialog((UIDialog*)dialog, "pagesize_dialog_cancel_button"); 
	return dialog->apply;
}

void HidePageSizeDialog(UIPageSizeDialog* dialog, gboolean apply)
{
	dialog->apply = apply;

	HideDialog((UIDialog*)dialog);
}

gboolean IsAvailablePageSize(UIPageSizeDialog* dialog, short page_size)
{
	GList* paper_size_list = GetComboList(CNCL_PAPERSIZE);
	gchar* paper_size_name;

	while( paper_size_list )
	{
		paper_size_name = (gchar*)paper_size_list->data;

		if( page_size == NameToValue(CNCL_PAPERSIZE, paper_size_name) )
			return TRUE;

		paper_size_list = paper_size_list->next;
	}

	return FALSE;
}

gboolean
on_pagesize_dialog_delete_event       (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	HidePageSizeDialog(g_pagesize_dialog, FALSE);
	return TRUE;
}

void
on_pagesize_dialog_ok_button_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
	HidePageSizeDialog(g_pagesize_dialog, TRUE);
}

void
on_pagesize_dialog_cancel_button_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
	HidePageSizeDialog(g_pagesize_dialog, FALSE);
}

