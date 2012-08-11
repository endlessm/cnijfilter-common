/*  Canon Bubble Jet Print Filter.
 *  Copyright CANON INC. 2001-2003
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


#ifndef	_MODELTBL
#define	_MODELTBL

#undef	GLOBAL
#ifdef	DEFINE_GLOBALS
#define	GLOBAL
#else
#define	GLOBAL	extern
#endif

typedef enum {
	UI_MEDIASIZE_ILLEGAL,
	UI_MEDIASIZE_RECOMMEND
} MediaSizeType;

typedef struct {
	MediaSizeType type;
	char *base;
	char *applied;
} MediaSizeTable;

typedef struct {
	short model_id;
	short util_flag;
	MediaSizeTable* media_size_table;
	short ext_border;
} ModelTable;


// Utility button flag.
#define	UF_CLEANING			1
#define	UF_DEEP_CLEANING	2
#define	UF_ROLLER_CLEANING	4
#define	UF_NOZZLE_CHECK		0x10
#define	UF_HEAD_ALIGNMENT	0x20
#define	UF_INK_RESET		0x40
#define	UF_INK_WARNING		0x80
#define	UF_POWER_OFF		0x100
#define	UF_AUTO_POWER		0x200
#define	UF_CUSTOM			0x1000
#define	UF_QUIET			0x2000


#define	UF_F860	(UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_POWER_OFF)

#define	UF_F360	(UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_POWER_OFF | UF_CUSTOM)

#define	UF_S600	(UF_CLEANING | UF_DEEP_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_CUSTOM)

#define	UF_F900	(UF_CLEANING | UF_DEEP_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_CUSTOM | UF_QUIET)

#define	UF_S300	(UF_CLEANING | UF_DEEP_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_INK_RESET | UF_INK_WARNING \
	| UF_POWER_OFF | UF_AUTO_POWER | UF_CUSTOM)


// Media Size table.

#ifdef	DEFINE_GLOBALS

GLOBAL MediaSizeTable g_media_size_table_f850[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
					"media_postcard media_glossy_postcard media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4 size_env_j6"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_f860[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_postcard media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4 size_env_j6"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_f360[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard media_glossy_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_l",
		"media_postcard media_inkjet_postcard media_glossy_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4 size_env_j6"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_l"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post size_post_l"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post size_post_l"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_s600[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_postcard media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_f900[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_s300[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post"},
	{0,NULL,NULL}
};

GLOBAL ModelTable g_model_table[] =
{
//	{CND_BJF850,    UF_F860, g_media_size_table_f850, -1},	// old ink.
	{CND_BJF850,    UF_F860, g_media_size_table_f860, -1},	// new ink.
	{CND_F860,      UF_F860, g_media_size_table_f860, -1},
	{CND_F870,      UF_F860, g_media_size_table_f860, -1},
	{CND_BJF360,    UF_F360, g_media_size_table_f360, -1},
	{CND_BJS600,    UF_S600, g_media_size_table_s600, -1},
	{CND_BJS630,    UF_S600, g_media_size_table_s600, -1},
	{CND_BJS6300,   UF_S600, g_media_size_table_s600, -1},
	{CND_BJF900,    UF_F900, g_media_size_table_f900, -1},
	{CND_BJF9000,   UF_F900, g_media_size_table_f900, -1},
	{CND_BJS500,    UF_S600, g_media_size_table_f900, -1},
	{CND_BJS300,    UF_S300, g_media_size_table_s300, -1},
	{CND_PIXUS550I, UF_F900, g_media_size_table_f900, -1},
	{CND_PIXUS850I, UF_F900, g_media_size_table_f900,  2},
	{CND_PIXUS950I, UF_F900, g_media_size_table_f900,  2},
	{0,0,NULL}
};

#else

GLOBAL MediaSizeTable g_media_size_table_f850[];
GLOBAL MediaSizeTable g_media_size_table_f860[];
GLOBAL MediaSizeTable g_media_size_table_f360[];
GLOBAL MediaSizeTable g_media_size_table_s600[];
GLOBAL ModelTable g_model_table[];

#endif



short GetUtilFlag(short model_id);
MediaSizeTable* GetMediaSizeTable(short model_id);
short GetDefaultExtBorder(short model_id);

#endif

