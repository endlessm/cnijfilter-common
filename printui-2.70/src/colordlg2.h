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


#include "dialog.h"

typedef struct
{
	UIDialog dialog;

	GtkAdjustment* cyan_adjust;
	GtkAdjustment* magenta_adjust;
	GtkAdjustment* yellow_adjust;
	GtkAdjustment* density_adjust;
	GtkAdjustment* contrast_adjust;

	short cyan_balance;
	short magenta_balance;
	short yellow_balance;
	short density_balance;
	short contrast_balance;

	short vivid;
	short color_correct;
	short gamma;
	short default_gamma;
	short default_intent;
//	short intent_num;

	GList* gamma_list;
	GList* intent_list;
} UIColorDialog2;


UIColorDialog2* CreateColorDialog2(UIDialog* parent);
void ShowColorDialog2(UIColorDialog2* dialog);
void HideColorDialog2(UIColorDialog2* dialog, gboolean apply);
UIColorDialog2* ReCreateColorDialog2(UIColorDialog2* dialog, UIDialog* parent);

void on_color_dialog_cyan_adjust_value_changed2(
		GtkAdjustment* adjust, gpointer* user_data);

void on_color_dialog_magenta_adjust_value_changed2(
		GtkAdjustment* adjust, gpointer* user_data);

void on_color_dialog_yellow_adjust_value_changed2(
		GtkAdjustment* adjust, gpointer* user_data);

void on_color_dialog_contrast_adjust_value_changed2(
		GtkAdjustment* adjust, gpointer* user_data);

void on_color_dialog_density_adjust_value_changed2(
		GtkAdjustment* adjust, gpointer* user_data);

