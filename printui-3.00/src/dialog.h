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


#ifndef	_UIDIALOG
#define	_UIDIALOG

#include <gtk/gtk.h>

typedef struct ui_dialog
{
	GtkWidget* window;
	struct ui_dialog* parent;
	int pos_x, pos_y;
	void* save;
	int size;
} UIDialog;

#define	UI_DIALOG(x)	((UIDialog*)x)

UIDialog* CreateDialog(gint size, UIDialog* parent);
void DisposeDialog(UIDialog* dialog);
void SaveDialog(UIDialog* dialog);
void RestoreDialog(UIDialog* dialog);

void ShowDialog(UIDialog* dialog, gchar* default_widget);
void HideDialog(UIDialog* dialog); 
void UpdateDialog(UIDialog* dialog, GdkRectangle* rect);

#endif
