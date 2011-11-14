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
#include <stdlib.h>

#include "callbacks.h"
#ifndef	USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"

#define		LOCALE_JP	"ja_JP"

static int CheckLocaleJP()
{
	char* env_locale;

#ifdef USE_PO_LOCALE
	env_locale = _("Locale");
#else
	if( (env_locale = getenv("LANG")) == NULL )
		env_locale = "";
	env_locale = strsep(&env_locale, ".");
#endif

	if( !strcasecmp(env_locale, LOCALE_JP) ) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

static
ModelTable* GetModelTableEntry(short model_id)
{
	int i = 0;
	while( g_model_table[i].model_id != 0 )
	{
		if( g_model_table[i].model_id == model_id )
			return &g_model_table[i];
		i++;
	}
	return NULL;
}

short GetUtilFlag(short model_id)
{
	ModelTable* model_table;

	if( (model_table = GetModelTableEntry(model_id)) != NULL )
		return model_table->util_flag;

	return 0;
}

MediaSizeTable* GetMediaSizeTable(short model_id)
{
	ModelTable* model_table;

	if( (model_table = GetModelTableEntry(model_id)) != NULL )
	{
		if( CheckLocaleJP() ) {	// Japanese
			return model_table->media_size_table_japanese;
		}
		else {					// except Japanese
			return model_table->media_size_table;
		}
	}
	return NULL;
}

short GetDefaultExtBorderTable(short model_id)
{
	ModelTable* model_table;

	if( (model_table = GetModelTableEntry(model_id)) != NULL )
		if( model_table->ext_border != -1 )
			return model_table->ext_border;

	return 3; // Return max extension value.
}
