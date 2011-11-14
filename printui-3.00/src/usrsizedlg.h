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


#include "dialog.h"

typedef struct
{
	UIDialog dialog;

	short scale;
	short old_scale;
	double width;
	double height;

	double min_mm_w, max_mm_w;
	double min_mm_h, max_mm_h;
	double min_in_w, max_in_w;
	double min_in_h, max_in_h;

} UIUserSizeDialog;

UIUserSizeDialog* CreateUserSizeDialog(UIDialog* parent, gboolean unit_inch);
UIUserSizeDialog* ReCreateUserSizeDialog(UIUserSizeDialog* dialog,
									 UIDialog* parent, gboolean unit_inch);
void ShowUserSizeDialog(UIUserSizeDialog* dialog);
void HideUserSizeDialog(UIUserSizeDialog* dialog, gboolean apply);
void ApplyUserSizeDialog(UIUserSizeDialog* dialog);
void UpdateUserSizeWidgets(UIUserSizeDialog* dialog, gboolean init_flag);

