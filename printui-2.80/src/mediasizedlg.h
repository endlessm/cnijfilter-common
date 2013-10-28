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

typedef enum {
	UI_MEDIASIZE_DLG_ILLEGAL,
	UI_MEDIASIZE_DLG_RECOMMEND,
	UI_MEDIASIZE_DLG_ILLEGAL_SELECT
} MediaSizeDlgType;

typedef enum {
	UI_MEDIASIZE_CHANGE_MEDIA,
	UI_MEDIASIZE_CHANGE_SIZE
} MediaSizeChange;


#define	RECOMMEND_ITEM_NUM		4
#define	ILLEGAL_SELECT_ITEM_NUM	RECOMMEND_ITEM_NUM


typedef struct
{
	UIDialog dialog;

	char* media;
	char* size;
	void* table;
	MediaSizeChange change;

	gboolean exec;
	gboolean apply;

	int item_count;
	short item_value[RECOMMEND_ITEM_NUM];

} UIMediaSizeDialog;

UIMediaSizeDialog* CreateMediaSizeDialog(
				UIDialog* parent, MediaSizeDlgType type);

int ShowMediaSizeIllegalDialog(UIMediaSizeDialog* dialog, gchar* applied);
int ShowMediaSizeRecommendDialog(UIMediaSizeDialog* dialog, gchar* applied);
int ShowMediaSizeIllegalSelectDialog(UIMediaSizeDialog* dialog, gchar* applied);
gboolean CheckMediaSizeCombination(LPBJFLTDEVICE bjdev, gboolean* change_item);

