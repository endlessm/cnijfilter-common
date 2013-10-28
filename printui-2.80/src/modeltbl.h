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
	char *applied_title;
} MediaSizeTable;

typedef struct {
	short model_id;
	short util_flag;
	MediaSizeTable* media_size_table;
	MediaSizeTable* media_size_table_japanese;
	short ext_border;
} ModelTable;

/* Ver.2.80 : Treat the string ID related to "lever position" as "CNCL value" */
/* of CNCL Object"CNUI_OBJECT_LEVER". */
#define CNUI_OBJECT_LEVER			(1000)
#define CNUI_VALUE_LEVER_LABEL		(0)
#define CNUI_VALUE_LEVER_ALERT		(1)


// Utility button flag.
#define	UF_CLEANING			1
#define	UF_DEEP_CLEANING	2
#define	UF_ROLLER_CLEANING	4
#define UF_PLATE_CLEANING	8
#define	UF_NOZZLE_CHECK		0x10
#define	UF_HEAD_ALIGNMENT	0x20
#define	UF_INK_RESET		0x100
#define	UF_INK_WARNING		0x200
#define	UF_INK_CARTRIDGE	0x400
#define	UF_POWER_OFF		0x1000
#define	UF_AUTO_POWER		0x2000
#define	UF_CUSTOM			0x4000
#define	UF_QUIET			0x8000

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

#define	UF_I250	(UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_INK_RESET | UF_INK_WARNING \
	| UF_POWER_OFF | UF_CUSTOM | UF_QUIET)

#define UF_IP3100 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_CUSTOM | UF_QUIET)

#define UF_IP1500 (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT \
	| UF_INK_RESET | UF_INK_WARNING | UF_POWER_OFF | UF_CUSTOM | UF_QUIET)

#define UF_IP2200 (UF_CLEANING | UF_DEEP_CLEANING | UF_HEAD_ALIGNMENT \
	| UF_NOZZLE_CHECK | UF_INK_CARTRIDGE | UF_PLATE_CLEANING \
	| UF_ROLLER_CLEANING | UF_POWER_OFF | UF_QUIET | UF_CUSTOM)

#define UF_IP4200 (UF_CLEANING | UF_DEEP_CLEANING | UF_HEAD_ALIGNMENT \
	| UF_NOZZLE_CHECK | UF_PLATE_CLEANING | UF_POWER_OFF \
	| UF_AUTO_POWER | UF_QUIET | UF_CUSTOM)

#define UF_IP7500 (UF_CLEANING | UF_DEEP_CLEANING | UF_HEAD_ALIGNMENT \
	| UF_NOZZLE_CHECK | UF_PLATE_CLEANING | UF_POWER_OFF \
	| UF_AUTO_POWER | UF_QUIET | UF_CUSTOM)

#define UF_IP6600D (UF_CLEANING | UF_DEEP_CLEANING | UF_HEAD_ALIGNMENT \
	| UF_NOZZLE_CHECK | UF_PLATE_CLEANING | UF_POWER_OFF \
	| UF_QUIET | UF_CUSTOM)

#define UF_MP500 (UF_CLEANING | UF_DEEP_CLEANING | UF_HEAD_ALIGNMENT \
	| UF_NOZZLE_CHECK | UF_PLATE_CLEANING | UF_POWER_OFF \
	| UF_QUIET | UF_CUSTOM)

// 2006/05/30
#define UF_MP160 (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_INK_CARTRIDGE | UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_IP3300 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_MP510 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_IP4300 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_MP600 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_IP90 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_POWER_OFF | UF_AUTO_POWER | UF_INK_RESET | UF_INK_WARNING \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_IP2500 (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_INK_CARTRIDGE | UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

// 2007/06/28
#define UF_07_TYPE_A (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_07_TYPE_B (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)




// Media Size table.

#ifdef	DEFINE_GLOBALS

GLOBAL MediaSizeTable g_media_size_table_f850[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
					"media_postcard media_glossy_postcard media_pro_photo",
					"media_postcard media_glossy_postcard media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4 size_env_j6", "size_env_j4 size_env_j6"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_f860[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_postcard media_pro_photo",
		"media_postcard media_inkjet_postcard \
		 media_glossy_postcard media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4 size_env_j6", "size_env_j4 size_env_j6"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_f360[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard media_glossy_postcard",
		"media_postcard media_inkjet_postcard media_glossy_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_l",
		"media_postcard media_inkjet_postcard media_glossy_postcard",
		"media_postcard media_inkjet_postcard media_glossy_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4 size_env_j6", "size_env_j4 size_env_j6"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_l", "size_post size_post_l"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post size_post_l", "size_post size_post_l"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post size_post_l", "size_post size_post_l"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_s600[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_postcard media_pro_photo",
		"media_postcard media_inkjet_postcard \
		 media_glossy_postcard media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4_p size_env_j6_p", "size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_f900[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4_p size_env_j6_p", "size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_s300[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4_p size_env_j6_p", "size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_i250[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_10_p size_env_dl_p", "size_env_10_p size_env_dl_p"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_pixus560i[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4_p size_env_j6_p", "size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip4200[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip4200_japanese[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip7500[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_a4_fine_art", "media_fine_art_paper media_other_fine_art_paper"
											 , "media_fine_art_paper media_other_fine_art_paper"},
	{UI_MEDIASIZE_ILLEGAL, "media_fine_art_paper", "size_a4_fine_art", "size_a4_fine_art"},
	{UI_MEDIASIZE_ILLEGAL, "media_other_fine_art_paper", "size_a4_fine_art", "size_a4_fine_art"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip7500_japanese[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_a4_fine_art", "media_fine_art_paper media_other_fine_art_paper"
											 , "media_fine_art_paper media_other_fine_art_paper"},
	{UI_MEDIASIZE_ILLEGAL, "media_fine_art_paper", "size_a4_fine_art", "size_a4_fine_art"},
	{UI_MEDIASIZE_ILLEGAL, "media_other_fine_art_paper", "size_a4_fine_art", "size_a4_fine_art"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};


GLOBAL MediaSizeTable g_media_size_table_ip4300[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p",
		"size_env_10_p size_env_dl_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip4300_japanese[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};


GLOBAL MediaSizeTable g_media_size_table_ip90[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},

	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p",
		"size_env_10_p size_env_dl_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip90_japanese[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},

	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};


GLOBAL MediaSizeTable g_media_size_table_ip4500[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy media_photo_paper_plus_glossy_ii",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p",
		"size_env_10_p size_env_dl_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip4500_japanese[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy media_photo_paper_plus_glossy_ii",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};


GLOBAL ModelTable g_model_table[] =
{
//	{CND_BJF850,      UF_F860,    g_media_size_table_f850,     	g_media_size_table_f850,			-1},	// old ink.
	{CND_BJF850,      UF_F860,    g_media_size_table_f860,     	g_media_size_table_f860,			-1},	// new ink.
	{CND_F860,        UF_F860,    g_media_size_table_f860,     	g_media_size_table_f860,			-1},
	{CND_F870,        UF_F860,    g_media_size_table_f860,     	g_media_size_table_f860,			-1},
	{CND_BJF360,      UF_F360,    g_media_size_table_f360,     	g_media_size_table_f360,			-1},
	{CND_BJS600,      UF_S600,    g_media_size_table_s600,     	g_media_size_table_s600,			-1},
	{CND_BJS630,      UF_S600,    g_media_size_table_s600,     	g_media_size_table_s600,			-1},
	{CND_BJS6300,     UF_S600,    g_media_size_table_s600,     	g_media_size_table_s600,			-1},
	{CND_BJF900,      UF_F900,    g_media_size_table_f900,     	g_media_size_table_f900,			-1},
	{CND_BJF9000,     UF_F900,    g_media_size_table_f900,     	g_media_size_table_f900,			-1},
	{CND_BJS500,      UF_S600,    g_media_size_table_f900,     	g_media_size_table_f900,			-1},
	{CND_BJS300,      UF_S300,    g_media_size_table_s300,     	g_media_size_table_s300,			-1},
	{CND_PIXUS550I,   UF_F900,    g_media_size_table_f900,     	g_media_size_table_f900,			-1},
	{CND_PIXUS850I,   UF_F900,    g_media_size_table_f900,     	g_media_size_table_f900,			 2},
	{CND_PIXUS950I,   UF_F900,    g_media_size_table_f900,     	g_media_size_table_f900,			 2},
	{CND_I250,        UF_I250,    g_media_size_table_i250,     	g_media_size_table_i250,			-1},
  	{CND_I255,        UF_I250,    g_media_size_table_i250,     	g_media_size_table_i250,			-1},
  	{CND_PIXUS560I,   UF_F900,    g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		 2},
  	{CND_PIXUS860I,   UF_F900,    g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		 2},
  	{CND_PIXUS990I,   UF_F900,    g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		 2},
	{CND_PIXMAIP1000, UF_I250,    g_media_size_table_i250,     	g_media_size_table_i250,			-1}, // Format 4
	{CND_PIXMAIP1500, UF_IP1500,  g_media_size_table_i250,     	g_media_size_table_i250,			-1}, // Format 4
  	{CND_PIXUSIP3100, UF_IP3100,  g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		-1}, // Format 4
 	{CND_PIXUSIP4100, UF_IP3100,  g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		-1}, // Format 4
  	{CND_PIXUSIP8600, UF_IP3100,  g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		-1}, // Format 4
  	{CND_IP2200,      UF_IP2200,  g_media_size_table_ip4200,   	g_media_size_table_ip4200_japanese,	-1},
  	{CND_IP4200,      UF_IP4200,  g_media_size_table_ip4200,   	g_media_size_table_ip4200_japanese,	-1},
  	{CND_IP6600D,     UF_IP6600D, g_media_size_table_ip4200,   	g_media_size_table_ip4200_japanese,	-1}, 
  	{CND_IP7500,      UF_IP7500,  g_media_size_table_ip7500,   	g_media_size_table_ip7500_japanese,	-1},	
  	{CND_MP500,       UF_MP500,   g_media_size_table_ip4200,   	g_media_size_table_ip4200_japanese,	-1},	
  	{CND_IP3300,      UF_IP3300,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_japanese,	-1},	
  	{CND_MP510,       UF_MP510,   g_media_size_table_ip4300,   	g_media_size_table_ip4300_japanese,	-1},	
  	{CND_IP4300,      UF_IP4300,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_japanese,	-1},	
  	{CND_MP600,       UF_MP600,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_japanese,	-1},	
  	{CND_MP160,       UF_MP160,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_japanese,	-1},	//2006_0616
  	{CND_IP90,        UF_IP90,   g_media_size_table_ip90,   	g_media_size_table_ip90_japanese,	-1},	//2006_1020
  	{CND_IP2500,      UF_IP2500,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_japanese,	-1},	//2006_0706 
  	{CND_IP1800,      UF_IP2500,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_japanese,	-1},	//2006_0706
  	{CND_MP140,       UF_MP160,   g_media_size_table_ip4500,   	g_media_size_table_ip4500_japanese,	-1},
  	{CND_MP210,       UF_MP160,   g_media_size_table_ip4500,   	g_media_size_table_ip4500_japanese,	-1},
  	{CND_IP3500,      UF_07_TYPE_A, g_media_size_table_ip4500,   	g_media_size_table_ip4500_japanese,	-1},
  	{CND_IP4500,      UF_07_TYPE_A, g_media_size_table_ip4500,   	g_media_size_table_ip4500_japanese,	-1},
  	{CND_MP610,       UF_07_TYPE_B, g_media_size_table_ip4500,   	g_media_size_table_ip4500_japanese,	-1},
  	{CND_MP520,       UF_07_TYPE_B, g_media_size_table_ip4500,   	g_media_size_table_ip4500_japanese,	-1},
	{0,0,NULL}
};

#else

GLOBAL ModelTable g_model_table[];

#endif



short GetUtilFlag(short model_id);
MediaSizeTable* GetMediaSizeTable(short model_id);
short GetDefaultExtBorderTable(short model_id);

#endif

