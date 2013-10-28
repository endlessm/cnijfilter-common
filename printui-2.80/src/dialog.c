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

#include "callbacks.h"
#ifndef	USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include <string.h>

#include "bjuidefs.h"


UIDialog* CreateDialog(gint size, UIDialog* parent)
{
	// Create dialog window.
	UIDialog* dialog = g_malloc(size);

	dialog->window = NULL;
	dialog->parent = (void*)parent;

	dialog->pos_x = 0;
	dialog->pos_y = 0;

	dialog->save = NULL;
	dialog->size = size;

	return dialog;
}

void DisposeDialog(UIDialog* dialog)
{
// Because unrefed these widgets in infterface.c, comment out them.
/*	if( dialog->window != NULL )
 *		gtk_widget_unref(dialog->window);
 */
	if( dialog->save != NULL )
		g_free(dialog->save);

	g_free(dialog);
}

void SaveDialog(UIDialog* dialog)
{
	void* save;
	if( dialog->save != NULL )
	{
		g_free(dialog->save);
		dialog->save = NULL;
	}

	save = g_malloc(dialog->size);
	memcpy(save, dialog, dialog->size);
	dialog->save = save;
}

void RestoreDialog(UIDialog* dialog)
{
	if( dialog->save != NULL )
		memcpy(dialog, dialog->save, dialog->size);
}

void ShowDialog(UIDialog* dialog, gchar* default_widget) 
{
	gint sw, sh;
	gint px, py;
	gint pw, ph;
	gint cw, ch;
	gint ox, oy;

	if( dialog->parent != NULL )
	{
		sw = gdk_screen_width();
		sh = gdk_screen_height();

		gtk_widget_realize(dialog->window);
		gtk_window_set_transient_for(GTK_WINDOW(dialog->window),
									GTK_WINDOW(dialog->parent->window));

		gdk_window_get_root_origin(dialog->parent->window->window, &px, &py);
		gdk_window_get_size(dialog->parent->window->window, &pw, &ph);
		gdk_window_get_size(dialog->window->window, &cw, &ch);

		ox = (pw - cw) / 2;
		if( ox < 20 )	ox = 20;

		oy = (ph - ch) / 2;
		if( oy < 20 )	oy = 20;

		if( px + ox + cw > sw ) 
			ox = sw - cw - px - 20;

		if( py + oy + ch > sh )
			oy = sh - ch - py - 20;

		if( dialog->pos_x == 0 )
			dialog->pos_x = px + ox;
		if( dialog->pos_y == 0 )
			dialog->pos_y = py + oy;
	}

	gtk_widget_set_uposition(dialog->window, dialog->pos_x, dialog->pos_y);

	if( default_widget )
	{
		GtkWidget* widget = LookupWidget(dialog->window, default_widget);

		if( widget )
		{
			gtk_widget_grab_focus(widget);
			gtk_widget_grab_default(widget);
		}
	}

	gtk_widget_show(dialog->window);
	gtk_main();
}

void HideDialog(UIDialog* dialog) 
{
	gint pos_x, pos_y;
	gdk_window_get_root_origin(dialog->window->window, &pos_x, &pos_y);

	dialog->pos_x = pos_x;
	dialog->pos_y = pos_y;

	gtk_widget_hide(GetTopWidget(dialog->window));
	gtk_main_quit();
}

void UpdateDialog(UIDialog* dialog, GdkRectangle* rect)
{
	gint window_w, window_h;
	GdkRectangle window_rect;

	if( dialog->window->window != NULL )
	{
		if( rect == NULL )
		{
			gdk_window_get_size(dialog->window->window, &window_w, &window_h);
			window_rect.x = 0;
			window_rect.y = 0;
			window_rect.width = window_w;
			window_rect.height = window_h;
			rect = &window_rect;
		}
		gtk_widget_draw(dialog->window, rect);
	}
}

