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


#ifndef	_GLOBALS
#define	_GLOBALS

#undef	GLOBAL
#ifdef	DEFINE_GLOBALS
#define	GLOBAL
#else
#define	GLOBAL	extern
#endif


#define	PRINTING_TYPE_FIT		1
#define	PRINTING_TYPE_NORMAL	2
#define	PRINTING_TYPE_SCALE		3

#define INTERNAL_VERSION_STR	"3.00.01.020"

/////////////////////////////////////////////////////////
// Initialized variables

#ifdef	DEFINE_GLOBALS

GLOBAL gchar* g_hostname = "localhost";

GLOBAL const gchar* g_quality_button_name[] =
{
	"quality_high_button",
	"quality_standard_button",
	"quality_draft_button",
	"quality_custom_button",
	NULL
};

GLOBAL const int g_mess_map[] = 
{
	CNCL_MESS_Q_MAP1,
	CNCL_MESS_Q_MAP2,
	CNCL_MESS_Q_MAP3,
	0
};

GLOBAL const gchar* g_printing_type_norm_name[] =
{
	"printing_type_normal",
	"printing_type_fit",
	"printing_type_scale",
	NULL
};

GLOBAL const short g_printing_type_norm_value[] =
{
	PRINTING_TYPE_NORMAL,	// Normal.
	PRINTING_TYPE_FIT,		// Fit-page printing.
	PRINTING_TYPE_SCALE,	// Scaling.
	0
};


GLOBAL gchar* g_border_ext_button_name[] =
{
	"border_ext_0_button",
	"border_ext_1_button",
	"border_ext_2_button",
	"border_ext_3_button",
	NULL
};

GLOBAL gchar* g_staple_button_name[] =
{
	"longside_button",
	"shortside_button",
	NULL
};


#else

GLOBAL gchar* g_hostname;

GLOBAL const gchar* g_quality_button_name[];
GLOBAL const int g_mess_map[];
GLOBAL const gchar* g_printing_type_norm_name[];
GLOBAL const short g_printing_type_norm_value[];
GLOBAL const gchar* g_border_ext_button_name[];
GLOBAL const gchar* g_staple_button_name[];


#endif

/////////////////////////////////////////////////////////
// Non initialized variables

#ifdef	USE_LIB_GLADE
GLOBAL GladeXML* g_ui_xml;
#endif

GLOBAL gboolean g_unit_inch;

GLOBAL gchar* g_socketname;
GLOBAL gchar* g_model_name;
GLOBAL gboolean g_cups_mode;

GLOBAL short g_model_id;
GLOBAL char g_window_title[64];

GLOBAL UIDB g_uidb;

GLOBAL GdkFont* g_main_font;
GLOBAL KeyTextList* g_keytext_list;
GLOBAL char* g_bjlibdir;
GLOBAL gboolean	g_valid_signal;

GLOBAL UIMainDialog* g_main_window;
GLOBAL UIVersionDialog* g_version_dialog;
GLOBAL UIQualityDialog* g_quality_dialog;
GLOBAL UIColorDialog* g_color_dialog;
GLOBAL UIColorDialog2* g_color_dialog2;
GLOBAL UIUserSizeDialog* g_user_size_dialog;
GLOBAL UIMediaSizeDialog* g_mediasize_illegal_dialog;
GLOBAL UIMediaSizeDialog* g_mediasize_recommend_dialog;
GLOBAL UIMediaSizeDialog* g_mediasize_illegal_select_dialog;
GLOBAL UIMediaTypeDialog* g_mediatype_dialog;
GLOBAL UIMediaBorderDialog* g_mediaborder_dialog;

GLOBAL CNCLPAPERSIZE g_bj_paper_size;
GLOBAL long g_user_paper_size[3];
GLOBAL gchar* g_printing_type_name[4];
GLOBAL short g_printing_type_value[4];

#endif

