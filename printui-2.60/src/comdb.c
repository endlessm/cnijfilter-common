/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2010
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
#define	BJ_LIB_DIR	mkpath(XBJLIBPATH)


int InitDataBase(char* model_name)
{
	if( model_name )
		g_model_id = ModelNameToID(model_name);
	else
		g_model_id = ModelNameToID(PACKAGE_PRINTER_MODEL);

	g_bjlibdir = BJ_LIB_DIR;

	// Retrieve name information.
	if( CNCL_GetDBName(&g_uidb.nominfo, (void *)g_bjlibdir, g_model_id) < 0 )
	{
		printf("Error: CNCL_GetDBName\n");
		return -1;
	}

	// Obtain the size of Internal Database.
	g_uidb.dbsize = CNCL_GetDBSize(&g_uidb.nominfo, (void*)g_bjlibdir);

	// Allocate Internal DB Area.
	g_uidb.lpdbTop = (LPCNCLDB)g_malloc(sizeof(CNCLDB) * g_uidb.dbsize);
	g_uidb.ModelID = g_model_id;

	// Initialize database values with CNCL.
	CNCL_GetEntries(&g_uidb.nominfo, (void*)g_bjlibdir, g_uidb.lpdbTop);

	// Then get Defaults.
	CNCL_GetDefaults(&g_uidb.nominfo,
				(void*)g_bjlibdir, g_uidb.lpdbTop, g_uidb.dbsize);

	// At last, call MODESET.
	CNCL_InitMenulink(&g_uidb.nominfo,
				(void*)g_bjlibdir, g_uidb.lpdbTop, g_uidb.dbsize);

	// Get min and max paper size.
	CNCL_GetMargin(&g_uidb.nominfo,
		(void*)g_bjlibdir, g_uidb.lpdbTop, &g_bj_paper_size, g_uidb.dbsize);

	// If the default unit is "inch", change the media size to "letter".
	if( g_unit_inch == TRUE )
		UpdateMenuLink(CNCL_PAPERSIZE, CND_SIZE_LETTER);
	else
		UpdateMenuLink(CNCL_PAPERSIZE, CND_SIZE_A4);

	// Set the user paper size into globals.
	InitUserPaperSize();

#ifdef	DEBUG_DUMP_DATABASE
	DumpDataBase(-1);
#endif

	return 0;
}

void FreeDataBase()
{
	g_free(g_uidb.lpdbTop);
}

static
long GetPaperSizeIndex(short value)
{
	int index = 0;

	while( PaperTbl[index][PSID] != -1 )
	{
		if( PaperTbl[index][PSID] == value )
			return index;

		index++;
	}
	return 0;
}

void InitUserPaperSize()
{
	// Set the user paper size into globals.
	short size_value = GetCurrentnValue(CNCL_PAPERSIZE);

	g_user_paper_size[YOKO] = GetPaperWidth(size_value);
	g_user_paper_size[TATE] = GetPaperHeight(size_value);
}

long GetPaperWidth(short value)
{
	if( value == CND_SIZE_USER )
		return g_user_paper_size[YOKO];
	else
		return PaperTbl[GetPaperSizeIndex(value)][YOKO];
}

long GetPaperHeight(short value)
{
	if( value == CND_SIZE_USER )
		return g_user_paper_size[TATE];
	else
		return PaperTbl[GetPaperSizeIndex(value)][TATE];
}

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

gboolean IsAvailableBorderless()
{
	int type = CNCL_GetTableFormatType(&g_uidb.nominfo, (void *)g_bjlibdir);
	if( type >= 2 )
	{
		return TRUE;
	}
	else if( type < 0 )
	{
		LPCNCLDB lpdb = g_uidb.lpdbTop;
		short i;

		CNCL_InitMenulink(&g_uidb.nominfo,
				(void*)g_bjlibdir, g_uidb.lpdbTop, g_uidb.dbsize);
		for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
		{
			if( lpdb->nObjectID == CNCL_MARGINTYPE
			 && lpdb->nValue == CND_MARGIN_MINUS )
					return TRUE;
		}
	}
	return FALSE;
}

gboolean IsAvailableVivid()
{
	LPCNCLDB lpdb = g_uidb.lpdbTop;
	short i;

	for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
	{
		if( lpdb->nObjectID == CNCL_VIVID
		 && lpdb->nValue == CND_VIVID_SUPPORT && !lpdb->disable )
				return TRUE;
	}
	return FALSE;
}

gboolean IsAvailableDuplex()
{
	LPCNCLDB lpdb = g_uidb.lpdbTop;
	short i;

	for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
	{
		if( lpdb->nObjectID == CNCL_DUPLEX_PRINTING
		 && lpdb->nValue == CND_DUPLEX_AUTO )
				return TRUE;
	}
	return FALSE;
}

short GetCurrentPaperGap()
{
	int value = GetCurrentnValue(CNCL_PAPERGAP_COMMAND);

	if( value == -1 )
		value = CND_PGAP_CMD_NA;

	return value;
}

short GetCurrentInkCartridgeSettings()
{
	int cartridge = GetCurrentnValue(CNCL_INKCARTRIDGESETTINGS);
	int media_type = GetCurrentnValue(CNCL_MEDIATYPE);
	int margin_type = GetCurrentnValue(CNCL_MARGINTYPE);

	if( cartridge != CND_CARTRIDGE_BK )
		return cartridge;
	if( media_type == CND_MEDIA_PLAIN && margin_type == CND_MARGIN_NORMAL )
		return cartridge;
	return CND_CARTRIDGE_BK_COLOR;
}

short GetDefaultExtBorder(int model_id)
{
	int type = CNCL_GetTableFormatType(&g_uidb.nominfo, (void *)g_bjlibdir);
	if( type >= 4 )
	{
		int value = GetCurrentnValue(CNCL_OVERMARGIN_LEVEL);
		if( value >= 0 )
			return value;	// 0 .. 3
	}
	return GetDefaultExtBorderTable(model_id);
}

int GetValueAndNameArray(short id, short** value, char*** name)
{
	int count;

	switch( id )
	{
	case CNCL_MEDIATYPE:	// Media Type.
		*value = g_media_value;
		*name  = g_media_name;
		count = sizeof(g_media_value) / sizeof(short);
		break;

	case CNCL_MEDIASUPPLY:	// Media Supply.
		*value = g_supply_value;
		*name  = g_supply_name;
		count = sizeof(g_supply_value) / sizeof(short);
		break;

	case CNCL_ENHBK:		// Black Enhancement.
		*value = g_bkenh_value;
		*name  = g_bkenh_name;
		count = sizeof(g_bkenh_value) / sizeof(short);
		break;

	case CNCL_PAPERSIZE:	// Paper Size.
		*value = g_size_value;
		*name  = g_size_name;
		count = sizeof(g_size_value) / sizeof(short);
		break;

	case CNCL_MESS_QUALITY:	// Message for Quality.
		*value = g_quality_msg_value;
		*name  = g_quality_msg_name;
		count = sizeof(g_quality_msg_value) / sizeof(short);
		break;

	case CNCL_MESS_THICK:	// Message for Thickness.
		*value = g_thickness_msg_value;
		*name  = g_thickness_msg_name;
		count = sizeof(g_thickness_msg_value) / sizeof(short);
		break;

	case CNCL_MESS_PAPERLOAD:	// Message for Preload.
		*value = g_preload_msg_value;
		*name  = g_preload_msg_name;
		count = sizeof(g_preload_msg_value) / sizeof(short);
		break;

	case CNCL_MESS_RESOLUTION:	// Message for Resolution.
		*value = g_resolution_msg_value;
		*name  = g_resolution_msg_name;
		count = sizeof(g_resolution_msg_value) / sizeof(short);
		break;

	case CNCL_MESS_SMLIB:		// Message for Smoothing.
		*value = g_smoothing_msg_value;
		*name  = g_smoothing_msg_name;
		count = sizeof(g_smoothing_msg_value) / sizeof(short);
		break;

	case CNCL_DITHER_PAT:		// Halftoning.
		*value = g_halftoning_value;
		*name  = g_halftoning_name;
		count = sizeof(g_halftoning_value) / sizeof(short);
		break;

	case CNCL_BANNER:			// Banner.
		*value = g_banner_value;
		*name  = g_banner_name;
		count = sizeof(g_banner_value) / sizeof(short);
		break;

	case CNCL_CARTRIDGE:		// Cartridge.
		*value = g_cartridge_value;
		*name  = g_cartridge_name;
		count = sizeof(g_cartridge_value) / sizeof(short);
		break;

	case CNCL_INPUT_GAMMA:		// Input gamma.
		*value = g_input_gamma_value;
		*name  = g_input_gamma_name;
		count = sizeof(g_input_gamma_value) / sizeof(short);
		break;

	case CNCL_PAPERGAP_COMMAND:	// Paper gap command.
		*value = g_paper_gap_value;
		*name  = g_paper_gap_name;
		count = sizeof(g_paper_gap_value) / sizeof(short);
		break;

	default:
		*value = NULL;
		*name  = NULL;
		count = 0;
		break;
	}

	return count;
}

char *ValueToKey(short id, short value)
{
	short *value_array;
	char **key_array;
	int count;
	int i;

	count = GetValueAndNameArray(id, &value_array, &key_array);

	for( i = 0 ; i < count ; i++ )
	{
		if( value_array[i] == value )
			break;
	}
	return (i < count)? key_array[i] :  "";
}

short KeyToValue(short id, char* name)
{
	short *value_array;
	char **key_array;
	int count;
	int i;

	count = GetValueAndNameArray(id, &value_array, &key_array);

	for( i = 0 ; i < count ; i++ )
	{
		if( strcmp(key_array[i], name) == 0 )
			break;
	}
	return (i < count)? value_array[i] : -1;
}

char *ValueToName(short id, short value)
{
	char *name = ValueToKey(id, value);

	if( name != '\0' )
		name = LookupText(g_keytext_list, name);

	return name;
}

short NameToValue(short id, char* name)
{
	short *value_array;
	char **key_array;
	int count;
	int i;

	count = GetValueAndNameArray(id, &value_array, &key_array);

	for( i = 0 ; i < count ; i++ )
	{
		if( strcmp(LookupText(g_keytext_list, key_array[i]), name) == 0 )
			break;
	}
	return (i < count)? value_array[i] : -1;
}

gboolean IsAvailableValue(short id, short value)
{
	LPCNCLDB lpdb = g_uidb.lpdbTop;
	short i;

	for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
	{
		if( lpdb->nObjectID == id )
		{
			if( lpdb->nValue == value && lpdb->disable == 0 )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

GList *GetComboList(short id)
{
	LPCNCLDB lpdb = g_uidb.lpdbTop;
	GList *glist = NULL;
	char *str;
	short i;

	for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
	{
		if( lpdb->nObjectID == id )
		{
			str = ValueToName(lpdb->nObjectID, lpdb->nValue);

			if( str != NULL )
			{
				if( *str != '\0' && lpdb->disable == 0 )
					glist = g_list_append(glist, str);
			}
		}
	}
	return glist;
}

short GetComboNum(short id)
{
	LPCNCLDB lpdb = g_uidb.lpdbTop;
	char *str;
	short i;
	short num = 0;

	for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
	{
		if( lpdb->nObjectID == id )
		{
			str = ValueToName(lpdb->nObjectID, lpdb->nValue);

			if( str != NULL )
			{
				if( *str != '\0' && lpdb->disable == 0 )
					num++;
			}
		}
	}
	return num;
}

char *GetCurrentString(short id)
{
	LPCNCLDB lpdb = g_uidb.lpdbTop;
	char *str = NULL;
	short i;

	for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
	{
		if( (lpdb->nObjectID == id) && (lpdb->curset == 1) )
		{
			str = ValueToName(lpdb->nObjectID, lpdb->nValue);
			break;
		}
	}
	return str;
}

short GetCurrentnValue(short id)
{
	LPCNCLDB lpdb = g_uidb.lpdbTop;
	short ret = -1;
	short i;

	for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
	{
		if( (lpdb->nObjectID == id) && (lpdb->curset == 1) )
		{
			ret = lpdb->nValue;
			break;
		}
	}
	return ret;
}

short GetDefaultnValue(short id)
{
	LPCNCLDB lpdb = g_uidb.lpdbTop;
	short ret = -1;
	short i;

	for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
	{
		if( (lpdb->nObjectID == id) && (lpdb->defset == 1) )
		{
			ret = lpdb->nValue;
			break;
		}
	}
	return ret;
}

short SetTemporaryFlag(short id, short value, short flag)
{
	LPCNCLDB lpdb = g_uidb.lpdbTop;
	short ret = -1;
	short i;

	// Set temporary flag.
	for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
	{
		if( lpdb->nObjectID == id && lpdb->nValue == value )
		{
			lpdb->tmpset = flag;
			ret = i;
			break;
		}
	}
	return ret;
}

short GetAllFlags(short id, short value)
{
	LPCNCLDB lpdb = g_uidb.lpdbTop;
	short ret = -1;
	short i;

	// Get all flag status.
	for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
	{
		if( lpdb->nObjectID == id )
		{
			if( lpdb->nValue == value )
			{
				ret = 0;
				if( lpdb->defset )
					ret |= DEFAULT_FLAG;
				if( lpdb->curset )
					ret |= CURRENT_FLAG;
				if( lpdb->tmpset )
					ret |= TEMPSET_FLAG;
				if( lpdb->disable )
					ret |= DISABLE_FLAG;
				break;
			}
		}
	}
	return ret;
}

// CNCL ID level.
typedef struct
{
	short id;
	short level;
} CnclIDLevel;

static CnclIDLevel cncl_id_level[] =
{
	// High
	{CNCL_CARTRIDGE,        1},	// In case of cartridge
	{CNCL_MEDIATYPE,        2},	// or media type change,
	{CNCL_GRAYSCALE,        2},	//    |
	{CNCL_MARGINTYPE,       3},	//    |
//	{CNCL_PAPERSIZE,        4},	//    |
	{CNCL_PRINTQUALITY,     4},	//    V
	{CNCL_MEDIASUPPLY,      4},	// all low level values must be saved
	{CNCL_PAPERGAP_COMMAND, 4},	// except print quailty.
	{CNCL_DITHER_PAT,       5},
	{CNCL_PAPERSIZE,        5},
	{CNCL_DUPLEX_PRINTING,  6},
	// Low
	{-1, -1}
};

static
int GetIDLevel(short id)
{
	int i = 0;
	while( cncl_id_level[i].id != -1 )
	{
		if( id == cncl_id_level[i].id )
			return cncl_id_level[i].level;
		i++;
	}
	return -1;
}

static
void SaveIDValue(short change_id, short save_id, short* save_value)
{
	if( GetIDLevel(change_id) < GetIDLevel(save_id) )
		*save_value = GetCurrentnValue(save_id);
}

static
void RestoreIDValue(short change_id, short save_id, short save_value)
{
	if( GetIDLevel(change_id) < GetIDLevel(save_id) )
	{
		short current_value = GetCurrentnValue(save_id);

		if( current_value != save_value )
		{
			if( !(GetAllFlags(save_id, save_value) & DISABLE_FLAG) )
			{
				SetTemporaryFlag(save_id, save_value, 1);

				CNCL_GetMenulink(&g_uidb.nominfo,
					(void*)g_bjlibdir, g_uidb.lpdbTop, g_uidb.dbsize);
			}
		}
	}
}

#define CALLBACK_TABLE_MAX 2

typedef struct
{
	short	id;
	void	(*func)(void *arg);
	void	*func_data;
	short	old_value;

}CallbackTable;


static CallbackTable callback_table[ CALLBACK_TABLE_MAX+1 ] =
{
	{ 0, NULL, NULL, 0 },
	{ 0, NULL, NULL, 0 },
	{ 0, NULL, NULL, 0 }
};


static int GetCallbackTableNum(void)
{
	int i;

	for(i=0; i < CALLBACK_TABLE_MAX; i++){
		if( callback_table[i].func == NULL )
			return i;
	}
	return -1;

}

static void SetCallbackTableOldValue(void)
{
	int i;
	
	for(i=0; callback_table[i].func != NULL; i++ ){
		callback_table[i].old_value = 
			GetCurrentnValue(callback_table[i].id);
	   
	}

}

static void CompCallbackTableValue(void)
{
	int i;
		
	for(i=0; callback_table[i].func != NULL; i++ ){
		if(callback_table[i].old_value != 
					GetCurrentnValue(callback_table[i].id) ){
			callback_table[i].func(callback_table[i].func_data);
		}
	}
}



int SetCallbackTableFunc(short id, void (*func)(void *arg), void* func_data)
{

	int table_num;
	
	if( (table_num=GetCallbackTableNum()) != -1){
		callback_table[table_num].id = id;
		callback_table[table_num].func = func;
		callback_table[table_num].func_data = func_data;
		
		return 0;
	}
		
	return -1;
}



int UpdateMenuLink(short id, short value)
{
	int ret;
	short media_type;
	short gray_scale;
	short margin_type;
	short paper_size;
	short print_quality;
	short media_supply;
	short dither_pat;
	short __attribute__ ((unused)) auto_duplex;

	short select_paper_size;		// paper size combo selected paper size
	short changed_paper_size;		// CNCL_GetMenulink(1st) selected paper size

	select_paper_size = GetCurrentnValue(CNCL_PAPERSIZE);

	if( GetCallbackTableNum() )
		SetCallbackTableOldValue();
	
	// Save all low level values.
	SaveIDValue(id, CNCL_MEDIATYPE, &media_type);
	SaveIDValue(id, CNCL_GRAYSCALE, &gray_scale);

//	if( id != CNCL_MEDIATYPE )
//		SaveIDValue(id, CNCL_MARGINTYPE, &margin_type);

	SaveIDValue(id, CNCL_MARGINTYPE, &margin_type);

	if( id != CNCL_CARTRIDGE && id != CNCL_MEDIATYPE )
		SaveIDValue(id, CNCL_PRINTQUALITY, &print_quality);

	SaveIDValue(id, CNCL_MEDIASUPPLY, &media_supply);

	SaveIDValue(id, CNCL_PAPERSIZE, &paper_size);
	SaveIDValue(id, CNCL_DITHER_PAT, &dither_pat);

//	SaveIDValue(id, CNCL_DUPLEX_PRINTING, &auto_duplex);

	// Set new value.
	SetTemporaryFlag(id, value, 1);

	ret = CNCL_GetMenulink(&g_uidb.nominfo,
			(void*)g_bjlibdir, g_uidb.lpdbTop, g_uidb.dbsize);

	// Restore all low level values.
	RestoreIDValue(id, CNCL_MEDIATYPE, media_type);
	RestoreIDValue(id, CNCL_GRAYSCALE, gray_scale);

//	if( id != CNCL_MEDIATYPE )
//		RestoreIDValue(id, CNCL_MARGINTYPE, margin_type);

	RestoreIDValue(id, CNCL_MARGINTYPE, margin_type);

	if( id != CNCL_CARTRIDGE && id != CNCL_MEDIATYPE )
		RestoreIDValue(id, CNCL_PRINTQUALITY, print_quality);

	RestoreIDValue(id, CNCL_MEDIASUPPLY, media_supply);

	RestoreIDValue(id, CNCL_PAPERSIZE, paper_size);
	RestoreIDValue(id, CNCL_DITHER_PAT, dither_pat);

//	RestoreIDValue(id, CNCL_DUPLEX_PRINTING, auto_duplex);
	RestoreIDValue(id, CNCL_DUPLEX_PRINTING, g_duplex_value);

	if( g_unit_inch == TRUE && id != CNCL_PAPERSIZE ){

		changed_paper_size = GetCurrentnValue(CNCL_PAPERSIZE);

		if( (changed_paper_size == CND_SIZE_A4) && (select_paper_size != changed_paper_size) ) {

			// Save all low level values.
			SaveIDValue(CNCL_PAPERSIZE, CNCL_MEDIATYPE, &media_type);
			SaveIDValue(CNCL_PAPERSIZE, CNCL_GRAYSCALE, &gray_scale);
			SaveIDValue(CNCL_PAPERSIZE, CNCL_MARGINTYPE, &margin_type);
			SaveIDValue(CNCL_PAPERSIZE, CNCL_PRINTQUALITY, &print_quality);
			SaveIDValue(CNCL_PAPERSIZE, CNCL_MEDIASUPPLY, &media_supply);
			// SaveIDValue(CNCL_PAPERSIZE, CNCL_PAPERSIZE, &paper_size);
			SaveIDValue(CNCL_PAPERSIZE, CNCL_DITHER_PAT, &dither_pat);
//			SaveIDValue(CNCL_PAPERSIZE, CNCL_DUPLEX_PRINTING, &auto_duplex);

			SetTemporaryFlag(CNCL_PAPERSIZE, CND_SIZE_LETTER, 1);

			ret = CNCL_GetMenulink(&g_uidb.nominfo,
					(void*)g_bjlibdir, g_uidb.lpdbTop, g_uidb.dbsize);

			// Restore all low level values.
			RestoreIDValue(CNCL_PAPERSIZE, CNCL_MEDIATYPE, media_type);
			RestoreIDValue(CNCL_PAPERSIZE, CNCL_GRAYSCALE, gray_scale);
			RestoreIDValue(CNCL_PAPERSIZE, CNCL_MARGINTYPE, margin_type);
			RestoreIDValue(CNCL_PAPERSIZE, CNCL_PRINTQUALITY, print_quality);
			RestoreIDValue(CNCL_PAPERSIZE, CNCL_MEDIASUPPLY, media_supply);
			// RestoreIDValue(CNCL_PAPERSIZE, CNCL_PAPERSIZE, paper_size);
			RestoreIDValue(CNCL_PAPERSIZE, CNCL_DITHER_PAT, dither_pat);
//			RestoreIDValue(CNCL_PAPERSIZE, CNCL_DUPLEX_PRINTING, auto_duplex);
			RestoreIDValue(CNCL_PAPERSIZE, CNCL_DUPLEX_PRINTING, g_duplex_value);
		}
	}

	if( GetCallbackTableNum() )
		CompCallbackTableValue();

#ifdef DEBUG_UPDATE_MENU_LINK
	printf(">>> UpdateMenuLink >>>\n");
	printf("id = %d, value = %d, ret = %d\n", id, value, ret);
#endif

	return ret;
}

void DumpDataBase(int id)
{
	LPCNCLDB lpdb = g_uidb.lpdbTop;
	short i;
	static int count = 0;

	printf("%d >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", count++);

	for( i = 0 ; i < g_uidb.dbsize ; i++, lpdb++ )
	{
		if( id == -1 || id == lpdb->nObjectID )
		{
			printf("dbsize:%d-----------------------------------\n", i);
			printf("nObjectID (CNCLID): %d\n", lpdb->nObjectID);
			printf("nValue    (CNCLID): %d\n", lpdb->nValue);
			printf("defset  : %d\n", lpdb->defset);
			printf("curset  : %d\n", lpdb->curset);
			printf("tmpset  : %d\n", lpdb->tmpset);
			printf("disable : %d\n", lpdb->disable);
		}
	}
}

