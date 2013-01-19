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


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>

#include <string.h>

#include "bjuidefs.h"
#include "msgtable.h"


// BJ library dir
//#define	BJ_LIB_DIR	"/usr/lib/bjlib"
#define	BJ_LIB_DIR	mkpath(XBJLIBPATH)
int ModelNameToID(char* name)
{
	int i = 0;
	gint upname_len = strlen(name) + 1;
	gchar* upname = g_malloc0( upname_len );
	int value = -1;

	strncpy(upname, name, upname_len); /* Ver.3.60 */
	upname[ upname_len -1 ] = '\0';

	// Because the display trouble was found by tr_TR.ISO8859-9, 
	// g_strup() is replaced with UpperAsciiStr(). 
	UpperAsciiStr(upname);	//	g_strup(upname);

	while( g_model_key[i] != NULL )
	{
		if( strcmp(upname, g_model_param[i]) == 0 )
		{
			value = g_model_value[i];
			break;
		}
		i++;
	}

	g_free(upname);
	return value;
}

char* GetModelName()
{
	int i = 0;

	while( g_model_key[i] != NULL )
	{
		if( g_model_value[i] == g_model_id )
			return g_model_param[i];

		i++;
	}
	return NULL;
}

char* GetDispModelName()
{
	int i = 0;

	while( g_model_key[i] != NULL )
	{
		if( g_model_value[i] == g_model_id )
			return LookupText(g_keytext_list, g_model_key[i]);

		i++;
	}
	return NULL;
}

/* Ver.3.20 */
gboolean IsIVECModel()
{
	gboolean result = TRUE;
//onErr:
	return result;
}

short GetCurrentInkCartridgeSettings()
{
	return 0;
}

/* Ver.3.70 */
void ReleaseEditableState( GtkWidget *widget,GtkStateType state )
{
	if ( state != GTK_STATE_INSENSITIVE ) {
		gtk_editable_select_region( GTK_EDITABLE(widget), 0, 0 );
	}
}

