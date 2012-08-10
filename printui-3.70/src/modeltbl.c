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
#include "util_parse_function.h"

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

/* Ver.3.40 */
static ModelTable2* GetModelTableEntry2(short model_id)
{
	int i = 0;
	while( g_model_table2[i].model_id != 0 ){
		if ( g_model_table2[i].model_id == model_id ) return &g_model_table2[i];
		i++;
	}
	return NULL;
}

short GetUtilFlag(short model_id)
{
	LPFUNCTIONCOMP lpComp;
	char resName[NAME_BUF_MAX_SIZE];
	char *modelName = GetModelName();
	short flag = 0;

	snprintf( resName, NAME_BUF_MAX_SIZE, "%s/%s", MAINTENANCE_RESPATH, MAINTENANCE_RESFILE );
	if ( ParseFunctionListTag( resName, modelName, &lpComp  ) != 0 ) goto Err;
	while( lpComp != NULL ){
		if ( lpComp->type == FUNCTYPE_CLEANING ) flag |= UF_CLEANING;
		else if ( lpComp->type == FUNCTYPE_DEEP_CLEANING ) flag |= UF_DEEP_CLEANING;
		else if ( lpComp->type == FUNCTYPE_ROLLER_CLEANING ) flag |= UF_ROLLER_CLEANING;
		else if ( lpComp->type == FUNCTYPE_PLATE_CLEANING ) flag |= UF_PLATE_CLEANING;
		else if ( lpComp->type == FUNCTYPE_NOZZLE_CHECK ) flag |= UF_NOZZLE_CHECK;
		else if ( lpComp->type == FUNCTYPE_POWER_OFF ) flag |= UF_POWER_OFF;
		else if ( lpComp->type == FUNCTYPE_AUTOPOWER ) flag |= UF_AUTO_POWER;
		else if ( lpComp->type == FUNCTYPE_INK_WARNING ) flag |= UF_INK_WARNING;
		else if ( lpComp->type == FUNCTYPE_INK_RESET ) flag |= UF_INK_RESET;
		else if ( lpComp->type == FUNCTYPE_INK_CARTRIDGE ) flag |= UF_INK_CARTRIDGE;
		else if ( lpComp->type == FUNCTYPE_QUIET ) flag |= UF_QUIET;
		else if ( lpComp->type == FUNCTYPE_HEAD_ALIGNMENT_AUTO ) flag |= UF_HEAD_ALIGNMENT;
		else if ( lpComp->type == FUNCTYPE_HEAD_ALIGNMENT_MANUAL ) flag |= UF_HEAD_ALIGNMENT;
		else if ( lpComp->type == FUNCTYPE_CUSTOM ) flag |= UF_CUSTOM;
		else if ( lpComp->type == FUNCTYPE_PAPER_SOURCE_SETTING ) flag |= UI_PAPER_SOURCE_SETTING;
		lpComp = lpComp->next;
	}
	FreeFunctionCompList( lpComp );
#if 0
	ModelTable* model_table;

	if( (model_table = GetModelTableEntry(model_id)) != NULL )
		return model_table->util_flag;

#endif
Err:
	return flag;
}

MediaSizeTable* GetMediaSizeTable(short model_id)
{
	ModelTable* model_table;
	ModelTable2* model_table2;

	if( (model_table = GetModelTableEntry(model_id)) != NULL )
	{
		if( CheckLocaleJP() ) {	// Japanese
			return model_table->media_size_table_jp;
		}
		else {					// except Japanese
			return model_table->media_size_table;
		}
	}
	/* Ver.3.40 */
	if ( (model_table2 = GetModelTableEntry2( model_id )) != NULL ){
		if ( g_unit_inch == TRUE ){
			return model_table2->media_size_table_us;
		}
		else {
			if ( CheckLocaleJP() ){
				return model_table2->media_size_table_jp;
			}
			else {
				return model_table2->media_size_table;
			}
		}
	}
	return NULL;
}

short GetDefaultExtBorderTable(short model_id)
{
	ModelTable* model_table;
	ModelTable2* model_table2;

	if( (model_table = GetModelTableEntry(model_id)) != NULL ){
		if( model_table->ext_border != -1 ){
			return model_table->ext_border;
		}
	}
	if ( (model_table2 = GetModelTableEntry2( model_id )) != NULL ){
		if( model_table2->ext_border != -1 ){
			return model_table2->ext_border;
		}
	}
	return 3; // Return max extension value.
}
