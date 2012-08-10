/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2012
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

UIVersionDialog* CreateVersionDialog(UIDialog* parent)
{
	UIVersionDialog* dialog
		 = (UIVersionDialog*)CreateDialog(sizeof(UIVersionDialog), parent);
	int strSize = 0;
	gchar *str1Ptr = NULL, *str2Ptr = NULL;
	GtkWidget* widget;

#ifdef	USE_LIB_GLADE
	UI_DIALOG(dialog)->window = widget = LookupWidget(NULL, "version_dialog");
#else
	UI_DIALOG(dialog)->window = widget = create_version_dialog();
#endif

	/* string length */
	strSize = strlen(GetProductName()) + strlen(PRINTUI_VERSION_COMMAND_STR); /* product name */
	strSize += strlen(GetVersion()) + strlen(PRINTUI_VERSION_VER_STR); /* version */
	strSize += strlen(GetCopyright1()) + strlen(PRINTUI_VERSION_FROM_STR) + strlen(PRINTUI_VERSION_TO_STR); /* copyright1 */
	strSize += strlen(GetCopyright2()); /* copyright2 */
	strSize += 4; /* LF */

	if ( (str1Ptr = g_malloc0( strSize )) == NULL ) goto onErr1;
	if ( (str2Ptr = g_malloc0( strSize )) == NULL ) goto onErr2;

	snprintf( str1Ptr, strSize, "%s%s\n%s\n%s\n%s", GetProductName(), PRINTUI_VERSION_COMMAND_STR, GetVersion(), GetCopyright1(), GetCopyright2() );
	snprintf( str2Ptr, strSize, str1Ptr, PRINTUI_VERSION_VER_STR, PRINTUI_VERSION_FROM_STR, PRINTUI_VERSION_TO_STR );

	gtk_label_set_text( GTK_LABEL(LookupWidget( widget, "version_dialog_label01" )), str2Ptr );

	g_free( str2Ptr );
onErr2:
	g_free( str1Ptr );
onErr1:
	return dialog;
}

