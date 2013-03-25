/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2013
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
#include <stdlib.h>
#include <string.h>

#include "callbacks.h"
//#	include "interface.h"
//#	include "support.h"

#include "bjuidefs.h"


static int ReadLine(FILE* fp, char* buf, int size)
{
	int cc;
	int count = 0;

	if( size < 1 )
		return -1;

	while( (cc = fgetc(fp)) != EOF )
	{
		if( count >= size - 1 )
			break;
		else if( cc == '\n' )
			break;
		*buf++ = cc;
		count++;
	}

	*buf = '\0';

	if( cc == EOF && count == 0 )
		return -1;
	else
		return count;
}

#define	READ_MAX_BUF			1024
#define	DEFAULT_UI_FILE		"printui.ui"
#define	DEFAULT_GLADE_FILE		"printui.glade"
#define	DEFAULT_KEYTEXT_FILE	"printui.res"
#define	DEFAULT_UNIT_MM			"mm"	// "mm" or "inch"


int LoadResources()
{
	FILE* fp = fopen(PACKAGE_DATA_DIR G_DIR_SEPARATOR_S "locale-table", "r");

	char* env_locale;
	char* __attribute__ ((unused)) glade_name;
	char* keytext_name;
	char* unit_name;
	gboolean last = 0;
	char buf[READ_MAX_BUF];
	char locale[READ_MAX_BUF / 4];
	char glade[READ_MAX_BUF / 4];
	char keytext[READ_MAX_BUF / 4];
	char unit[READ_MAX_BUF / 4];
	int bytes;

#ifdef USE_PO_LOCALE
	env_locale = _("Locale");
#else
	if( (env_locale = getenv("LANG")) == NULL )
		env_locale = "";
	env_locale = strsep(&env_locale, ".");
#endif

	while( 1 )
	{
		if( fp == NULL || env_locale == NULL )
		{
			glade_name   = DEFAULT_GLADE_FILE;
			keytext_name = DEFAULT_KEYTEXT_FILE;
			unit_name    = DEFAULT_UNIT_MM;
			last = TRUE;
		}
		else
		{
			while( (bytes = ReadLine(fp, buf, READ_MAX_BUF)) >= 0 )
			{
				sscanf(buf, "%s %s %s %s", locale, glade, keytext, unit);

				if( locale[0] == '#' )	// If comments, ignore this line.
				{
					continue;
				}
				else if( !strcasecmp(env_locale, locale) )
				{
					if( strlen(glade) > 0 && strlen(keytext) > 0 )
					{
						glade_name   = glade;
						keytext_name = keytext;
						unit_name    = unit;
						break;
					}
				}
			}
			if( bytes < 0 )
			{
				glade_name   = DEFAULT_GLADE_FILE;
				keytext_name = DEFAULT_KEYTEXT_FILE;
				unit_name    = DEFAULT_UNIT_MM;
				last = TRUE;
			}
		}
		// Load text resource.
			return 0;
	}
	g_keytext_list = LoadKeyTextList(keytext_name);

		glade_name   = DEFAULT_UI_FILE;
		char* glade_path = g_malloc(strlen(PACKAGE_DATA_DIR) + 1 + strlen(glade_name) + 1);

		strcpy(glade_path, PACKAGE_DATA_DIR);
		strcat(glade_path, G_DIR_SEPARATOR_S);
		strcat(glade_path, glade_name);

		GError* error = NULL;
		GtkBuilder* builder = gtk_builder_new ();
		if (!gtk_builder_add_from_file (builder, glade_path, &error))
		  {
		    g_warning ("Couldn't load builder file: %s", error->message);
		    g_error_free (error);
		  }

	g_unit_inch = (strcmp(unit_name, DEFAULT_UNIT_MM))? TRUE : FALSE; 

	gtk_builder_connect_signals (builder, NULL);

	return 1;
}

void FreeResources()
{
	// Free text resource.
	FreeKeyTextList(g_keytext_list);
}

