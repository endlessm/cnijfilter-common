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


// Messages conversion table

char *g_model_param[] =
{
	"BJF850",
	"BJF860",
	"BJF870",
	"BJF360",
	"BJS600",
	"BJS630",
	"BJS6300",
	"BJF900",
	"BJF9000",
	"BJS500",
	"BJS300",
	"PIXUS550I",
	"PIXUS850I",
	"PIXUS950I",
	"I250",
	"I255",
	"PIXUS560I",
	"PIXUS860I",
	"PIXUS990I",
	"PIXUSIP3100",
	"PIXUSIP4100",
	"PIXUSIP8600",
	"PIXMAIP1000",
	"PIXMAIP1500",
	"IP2200",
	"IP4200",
	"IP6600D",
	"IP7500",
	"MP500",
	"IP3300",
	"MP510",
	"IP4300",
	"MP600",
	"MP160",
	"IP90",
	"IP2500",
	"IP1800",
	"MP140",
	"MP210",
	"IP3500",
	"IP4500",
	"MP610",
	"MP520",
	"IP100",
	"IP2600",
	"IP3600",
	"IP4600",
	"MP630",
	"MP540",
	"MP240",
	"MP190",
	"IP1900",
	NULL,
};

char *g_model_key[] =
{
	"model_BJF850",
	"model_BJF860",
	"model_BJF870",
	"model_BJF360",
	"model_BJS600",
	"model_BJS630",
	"model_BJS6300",
	"model_BJF900",
	"model_BJF9000",
	"model_BJS500",
	"model_BJS300",
	"model_PIXUS550i",
	"model_PIXUS850i",
	"model_PIXUS950i",
	"model_i250",
	"model_i255",
	"model_PIXUS560i",
	"model_PIXUS860i",
	"model_PIXUS990i",
	"model_PIXUSiP3100",
	"model_PIXUSiP4100",
	"model_PIXUSiP8600",
	"model_PIXMAiP1000",
	"model_PIXMAiP1500",
	"model_iP2200",
	"model_iP4200",
	"model_iP6600d",
	"model_iP7500",
	"model_MP500",
	"model_iP3300",
	"model_MP510",
	"model_iP4300",
	"model_MP600",
	"model_MP160",
	"model_iP90",
	"model_iP2500",
	"model_iP1800",
	"model_MP140",
	"model_MP210",
	"model_iP3500",
	"model_iP4500",
	"model_MP610",
	"model_MP520",
	"model_IP100",
	"model_IP2600",
	"model_IP3600",
	"model_IP4600",
	"model_MP630",
	"model_MP540",
	"model_MP240",
	"model_MP190",
	"model_IP1900",
	NULL,
};

short g_model_value[] = {
	CND_BJF850,
	CND_F860,
	CND_F870,
	CND_BJF360,
	CND_BJS600,
	CND_BJS630,
	CND_BJS6300,
	CND_BJF900,
	CND_BJF9000,
	CND_BJS500,
	CND_BJS300,
	CND_PIXUS550I,
	CND_PIXUS850I,
	CND_PIXUS950I,
	CND_I250,
	CND_I255,
	CND_PIXUS560I,
	CND_PIXUS860I,
	CND_PIXUS990I,
	CND_PIXUSIP3100,
	CND_PIXUSIP4100,
	CND_PIXUSIP8600,
	CND_PIXMAIP1000,
	CND_PIXMAIP1500,
	CND_IP2200,
	CND_IP4200,
	CND_IP6600D,
	CND_IP7500,
	CND_MP500,
	CND_IP3300,
	CND_MP510,
	CND_IP4300,
	CND_MP600,
	CND_MP160,
	CND_IP90,
	CND_IP2500,
	CND_IP1800,
	CND_MP140,
	CND_MP210,
	CND_IP3500,
	CND_IP4500,
	CND_MP610,
	CND_MP520,
	CND_IP100,
	CND_IP2600,
	CND_IP3600,
	CND_IP4600,
	CND_MP630,
	CND_MP540,
	CND_MP240,
	CND_MP190,
	CND_IP1900,
};

char *g_media_name[] =
{
	"media_plain",
	"media_ohp",
	"media_bpf",
	"media_bjcloth",
	"media_higlossfilm",
	"media_postcard",
	"media_envelope",
	"media_glossy_postcard",
	"media_hires",
	"media_tshirt",
	"media_thick",
	"media_higloss_photo_film",
	"media_glossy_photo",
	"media_glossy_photocard",
	"media_pro_photo",
	"media_inkjet_postcard",
	"media_matte_photo",
	"media_photo_plus_glossy",
	"media_other",
	"media_other_photo",
	"media_duplex_glossy",
	"media_fine_art_paper",
	"media_other_fine_art_paper",
	"media_photo_paper_plus_glossy_ii",
	"media_photo_paper_plus_semi_gloss",
	"media_photo_paper_pro_platinum",
	"media_photo_paper_pro_ii",
	"media_na",
};

short g_media_value[] = {
	CND_MEDIA_PLAIN,				// Plain Paper
	CND_MEDIA_OHP,					// OHP
	CND_MEDIA_BPF,					// Back Print Film (BF-102)
	CND_MEDIA_BJCLOTH,				// BJ Cloth (FS-101)
	CND_MEDIA_HIGLOSSFILM,			// High Glossy Film (HG-101)
	CND_MEDIA_POSTCARD,				// Postcard
	CND_MEDIA_ENVELOPE,				// Envelope
	CND_MEDIA_GLOSSYPOSTCARD,		// Glossy Postcard (KH-101)
	CND_MEDIA_HIRES,				// High Resolution Paper (HR-101)
	CND_MEDIA_TSHIRT,				// T-shirt Transfer
	CND_MEDIA_THICK,				// Thick Paper
	CND_MEDIA_HIGLOSSPHTFILM,		// High Gloss Photo Film (HG-201)
	CND_MEDIA_GLOSSYPHOTO,			// Glossy Photo Paper (GP-201)
	CND_MEDIA_GLOSSYPHOTOCARD,		// Glossy Photo Cards (FM-101)
	CND_MEDIA_PROPHOTO,				// Professional Photo Paper
	CND_MEDIA_INKJET_POST,			// Inkjet Postcard
	CND_MEDIA_MATTE,				// Matte Photo Paper
	CND_MEDIA_SUPER_PHOTO,			// Super Photo Paper
	CND_MEDIA_OTHER,				// Other Media
	CND_MEDIA_OTHER_PHOTO_PAPER,	// Other Photo Paper
	CND_MEDIA_DUPLEX_GLOSSY_PAPER,	// Other Photo Paper
	CND_MEDIA_FINE_ART_PAPER,		// Fine Art Photo Rag
	CND_MEDIA_OTHER_FINE_ART_PAPER,	// Other Fine Art Photo Rag
	CND_MEDIA_PHOTO_PAPER_PLUS_GLOSSY_II,	//Photo Paper Plus Glossy II
	CND_MEDIA_PHOTO_PAPER_SEMI_GLOSS,		//Photo Paper Semi-gloss
	CND_MEDIA_PHOTO_PAPER_PRO_PLATINUM,		//Photo Paper Pro Platinum
	CND_MEDIA_PHOTO_PAPER_PRO_II,			//Photo Paper Pro II
	CND_MEDIA_NA,					// Not Applicable
};

char *g_supply_name[] =
{
	"supply_manual",
	"supply_asf",
	"supply_asf2",
	"supply_cassette",
	"supply_cassette2",
	"supply_consecutive",
	"supply_consecutive2",
	"supply_tractor",
	"supply_cassette_02",
	"supply_printer_sw_select",
	"supply_cassette_04",
	"supply_front_for_plain",
	"supply_auto_continuous_feed",
	"supply_auto_select",
	"supply_na",
};

short g_supply_value[] =
{
	CND_SUPPLY_MANUAL,				// Manual Feed
	CND_SUPPLY_ASF,					// Auto Sheet Feeder
	CND_SUPPLY_ASF2,				// Auto Sheet Feeder 2
	CND_SUPPLY_CASSETTE,			// Cassette 1
	CND_SUPPLY_CASSETTE2,			// Cassette 2
	CND_SUPPLY_CONSECUTIVE,			// Consecutive Feeder
	CND_SUPPLY_CONSECUTIVE2,		// Consecutive Feeder 2
	CND_SUPPLY_TRACTOR,				// Tractor Feeder
	CND_SUPPLY_CASSETTE_02,			// Cassette iP4100 type
	CND_SUPPLY_PRINTER_SW_SELECT,	// Paper Feed Switch
	CND_SUPPLY_CASSETTE_04,		/* Front Feeder */
	CND_SUPPLY_FRONT_FOR_PLAIN,		/* Front for plain(original) */
	CND_SUPPLY_AUTO_CONTINUOUS_FEED,//Continuous Autofeed
	CND_SUPPLY_AUTO_SELECT,			//Automatically Select
	CND_SUPPLY_NA,					// Not Applicable
};

char *g_bkenh_name[] =
{
	"bkenh_not",
	"bkenh_enh",
	"bkenh_na",
};

short g_bkenh_value[] =
{
	CND_ENH_NOT,	// Bk enhance off
	CND_ENH_ENH,	// Bk enhance on
	CND_ENH_NA,		// Not Applicable
};

char *g_size_name[] =
{
	"size_a5",
	"size_a4",
	"size_a3",
	"size_b5",
	"size_b4",
	"size_letter",
	"size_legal",
	"size_ledger",
	"size_csize",
	"size_post",
	"size_env_10",
	"size_env_dl",
	"size_fools",
	"size_env_j4",
	"size_env_j6",
	"size_letter_bleed",
	"size_a4_bleed",
	"size_a3_plus",
	"size_photocard",
	"size_user",
	"size_env_10_p",
	"size_env_dl_p",
	"size_env_j4_p",
	"size_env_j6_p",
	"size_l",
	"size_2l",
	"size_4x6",
	"size_panorama",
	"size_5x7",
	"size_post_dbl",
	"size_businesscard",
	"size_creditcard",
	"size_a4_fine_art",
	"size_4X8",
	"size_6giri",
	"size_wide",
	"size_na",
};

short g_size_value[] =
{
	CND_SIZE_A5,			// A5 (148mm x 210mm)
	CND_SIZE_A4,			// A4 (210mm x 297mm)
	CND_SIZE_A3,			// A3 (297mm x 420mm)
	CND_SIZE_B5,			// B5 (182mm x 257mm)
	CND_SIZE_B4,			// B4 (257mm x 364mm)
	CND_SIZE_LETTER,		// Letter (8.5x 11inch)
	CND_SIZE_LEGAL,			// Legal (8.5inch x 14inch)
	CND_SIZE_LEDGER,		// Ledger  (11inch x 17inch)
	CND_SIZE_CSIZE,			// C size (17 x 22inch)
	CND_SIZE_POST,			// Postcard (10mm 0x 148mm)
	CND_SIZE_ENV_10,		// #10 Envelope (9.5inch x 4.125inch)
	CND_SIZE_ENV_DL,		// DL Envelope (220mm x 110mm)
	CND_SIZE_FOOLS,			// Foolscap (13.5inch x 17inch)
	CND_SIZE_ENV_J4,		// Envelope-J4
	CND_SIZE_ENV_J6,		// Envelope-J6
	CND_SIZE_LETTER_BLEED,	// Letter full-bleed
	CND_SIZE_A4_BLEED,		// A4 full-bleed
	CND_SIZE_A3_PLUS,		// A3 plus
	CND_SIZE_PHOTOCARD,		// Photocard (FM-101)
	CND_SIZE_USER,			// User define
	CND_SIZE_ENV_10_P,		// #10 Envelope (Portrait)
	CND_SIZE_ENV_DL_P,		// DL Envelope (Portrait)
	CND_SIZE_ENV_J4_P,		// Envelope-J4 (Portrait)
	CND_SIZE_ENV_J6_P,		// Envelope-J6 (Portrait)
	CND_SIZE_L,				// L size
	CND_SIZE_2L,			// L size
	CND_SIZE_4X6,			// L size
	CND_SIZE_PANORAMA,		// Panorama
	CND_SIZE_5X7,			// Actual Size 5x7 ( 127mm x 177.8mm )
	CND_SIZE_POST_DBL,		// Double postal card ( 200mm x 148mm )
	CND_SIZE_BUSINESSCARD,	// Business card
	CND_SIZE_CREDITCARD,	// Credit card
	CND_SIZE_A4_FINE_ART,	// Fine Art A4 ( 210.0mm x 297.0 mm )
	CND_SIZE_4X8,			// 4x8in ( 101.6mm x 203.2mm )
	CND_SIZE_6GIRI,			// 8x10in ( 203.2mm x 254.0mm )
	CND_SIZE_HIVISION,		// Wide
	CND_SIZE_NA,			// Not Applicable
};


char *g_thickness_msg_name[] =
{
	"tmessage_position1",
	"tmessage_position2",
	"tmessage_position3",
	"tmessage_left",
	"tmessage_center",
	"tmessage_right",
	"tmessage_lower",
	"tmessage_upper",
	"tmessage_lower2",
	"tmessage_upper2",
	"tmessage_left2",
	"tmessage_right2",
	"tmessage_na",
};

short g_thickness_msg_value[] =
{
	CND_TMESSAGE_POSITION1,	// Position 1 (narrow)
	CND_TMESSAGE_POSITION2, // Position 2 (mid)
	CND_TMESSAGE_POSITION3,	// Position 3 (wide)
	CND_TMESSAGE_LEFT,		// Left       (narrow)
	CND_TMESSAGE_CENTER,	// Center     (mid)
	CND_TMESSAGE_RIGHT,		// Right      (wide)
	CND_TMESSAGE_LOWER,		// Lower      (narrow)
	CND_TMESSAGE_UPPER,		// Upper      (wide)
	CND_TMESSAGE_LOWER2,	// Lower 2    (wide)
	CND_TMESSAGE_UPPER2,	// Upper 2    (narrow)
	CND_TMESSAGE_LEFT2,		/* Right      (narrow)(Ver.2.70) */
	CND_TMESSAGE_RIGHT2,	/* Left       (wide)(Ver.2.70) */
	CND_TMESSAGE_NA,		// Not Applicable
};

char *g_preload_msg_name[] =
{
	"plmessage_foward",
	"plmessage_backword",
	"plmessage_lower",
	"plmessage_upper",
	"plmessage_na",
};

short g_preload_msg_value[] =
{
	CND_PLMESSAGE_FORWARD,	// Forward
	CND_PLMESSAGE_BACKWARD,	// Backward
	CND_PLMESSAGE_LOWER,	// Lower
	CND_PLMESSAGE_UPPER,	// Upper
	CND_PLMESSAGE_NA,		// Not Applicable */
};

char *g_smoothing_msg_name[] =
{
	"slmess_not",
	"slmess_smooth",
	"slmess_mystcut",
	"slmess_na",
};

short g_smoothing_msg_value[] =
{
	CND_SLMESS_NOT,			// Disable smoothing
	CND_SLMESS_SMOOTH,		// Enable smoothing
	CND_SLMESS_MYSTCUT,		// Enable smoothing and myst cut
	CND_SLMESS_NA,			// Not Applicable
};

char *g_halftoning_name[] =
{
	"bin_pattern",
	"bin_pattern_hs",
	"bin_v_pattern",
	"bin_ed",
	"bin_na",

};

short g_halftoning_value[] =
{
	CND_UIBIN_PATTERN,		// Pattern
	CND_UIBIN_PATTERN_HS,	// Pattern (High speed)
	CND_UIBIN_V_PATTERN,	// V-Pattern
	CND_UIBIN_ED,			// ED
	CND_UIBIN_NA,			// Not Applicable
};

char *g_banner_name[] =
{
	"banner_on",
	"banner_off",
	"banner_na",
};

short g_banner_value[] =
{
	CND_BANNER_ON,			// Enable banner mode
	CND_BANNER_OFF,			// Disable banner mode
	CND_BANNER_NA,			// Not Applicble
};

char *g_cartridge_name[] =
{
	"cartridge_color",
	"cartridge_bk",
	"cartridge_photo",
	"cartridge_bk_color",
	"cartridge_bk_photo",
	"cartridge_photo_color",
	"cartridge_na",
};

short g_cartridge_value[] =
{
	CND_CARTRIDGE_COLOR,		// Color cartridge
	CND_CARTRIDGE_BK,			// Black cartridge
	CND_CARTRIDGE_PHOTO,		// Photo cartridge
	CND_CARTRIDGE_BK_COLOR,		// Black and Color cartridge
	CND_CARTRIDGE_BK_PHOTO,		// Black and Photo cartridge
	CND_CARTRIDGE_PHOTO_COLOR,	// Photo and Color cartridge
	CND_CARTRIDGE_NA,			// Not Applicable
};


/* for NEW ColorDialog(colordialog2) */
char *g_correct_name[] =
{
	"color_correct_photo2",
	"color_correct_graphics",
//	"color_correct_maching",
	"color_correct_natural",
	NULL
};

short g_correct_value[] =
{
	CND_INTENT_PHOTO,		/* Photo */
	CND_INTENT_GRAPHICS,	/* Graphics */
//	CND_INTENT_MATCHING,	/* Matching */
	CND_INTENT_NATURAL,		/* Natural */
	CND_INTENT_NA,			/* Not Applicable */
};

/* for OLD ColorDialog(colordialog) */
/* not used... */
char *g_correct_name_old[] =
{
	"color_correct_photo",
	"color_correct_graphics",
	NULL
};

short g_correct_value_old[] =
{
	CND_INTENT_PHOTO,		/* Photo */
	CND_INTENT_GRAPHICS,	/* Graphics */
	CND_INTENT_NA,			/* Not Applicable */
};




char *g_input_gamma_name[] =
{
	"input_gamma_default",
	"input_gamma_1.0",
	"input_gamma_1.4",
	"input_gamma_1.8",
	"input_gamma_2.2",
	"input_gamma_na",
};

short g_input_gamma_value[] =
{
	CND_GAMMA_DEFAULT,			// Default Gamma
	CND_GAMMA_10,				// Gamma 1.0
	CND_GAMMA_14,				// Gamma 1.4
	CND_GAMMA_18,				// Gamma 1.8
	CND_GAMMA_22,				// Gamma 2.2
	CND_GAMMA_NA,				// Not Applicable
};

char *g_paper_gap_name[] =
{
	"paper_gap_auto",
	"paper_gap_wide",
	"paper_gap_narrow",
	"paper_gap_na",
};

short g_paper_gap_value[] =
{
	CND_PGAP_CMD_AUTO,			// Auto
	CND_PGAP_CMD_WIDE,			// Wide
	CND_PGAP_CMD_NARROW,		// Narrow
	CND_PGAP_CMD_NA,			// Not Applicable
};

/* Ver.2.80 : Treat the string ID related to "lever position" as "CNCL value" */
short g_lever_name_value[] =
{
	CNUI_VALUE_LEVER_LABEL,			// label
	CNUI_VALUE_LEVER_ALERT,			// message
};




/****************************************************************/
/* Ver.2.80 : Model-specific res_name (for same ID)              */
/****************************************************************/
char *g_supply_name_4500type[] =
{
	"supply_manual",
	"supply_asf_reartray",
	"supply_asf2",
	"supply_cassette",
	"supply_cassette2",
	"supply_consecutive",
	"supply_consecutive2",
	"supply_tractor",
	"supply_cassette_02",
	"supply_printer_sw_select",
	"supply_cassette_04_fronttray",
	"supply_front_for_plain_maetray",
	"supply_auto_continuous_feed",		//Ver.3.00
	"supply_auto_select",				//Ver.3.00
	"supply_na",
};


/* Treat the string ID related to "lever position" as "CNCL value" */
char *g_lever_name_mp140[] =
{
	"lever_position_label",
	"move_lever_position_alert",
};

char *g_lever_name_2007[] =
{
	"lever_position_label_2007",
	"move_lever_position_alert_2007",
};



/* { Object , res_name arrays } */
typedef struct {
	short object_id;
	char **res_name_array;
} ResArrayTable;


/* { model , res_name arrays set } */
typedef struct {
	short model_id;
	ResArrayTable *res_array_set;
} ResSetTable;


/* Default sets of res_name arrays table */
/* Model that's not included in "ResSetTable" uses arrays in this table. */
ResArrayTable g_res_arrays_default[] =
{
	{CNCL_MEDIATYPE			, g_media_name},
	{CNCL_MEDIASUPPLY		, g_supply_name},
	{CNCL_ENHBK				, g_bkenh_name},
	{CNCL_PAPERSIZE			, g_size_name},
	{CNCL_MESS_THICK		, g_thickness_msg_name},
	{CNCL_MESS_PAPERLOAD	, g_preload_msg_name},
	{CNCL_MESS_SMLIB		, g_smoothing_msg_name},
	{CNCL_DITHER_PAT		, g_halftoning_name},
	{CNCL_BANNER			, g_banner_name},
	{CNCL_CARTRIDGE			, g_cartridge_name},
	{CNCL_INPUT_GAMMA		, g_input_gamma_name},
	{CNCL_PAPERGAP_COMMAND	, g_paper_gap_name},
	{CNCL_INTENT			, g_correct_name},
	{CNUI_OBJECT_LEVER		, g_lever_name_mp140},/* Treat the string ID related to "lever position" as "CNCL value" */
	{-1						, NULL},
};



ResArrayTable g_res_arrays_ip4500type[] =
{
	{CNCL_MEDIATYPE			, NULL},	//NULL:use g_res_arrays_default
	{CNCL_MEDIASUPPLY		, g_supply_name_4500type},
	{CNCL_ENHBK				, NULL},
	{CNCL_PAPERSIZE			, NULL},
	{CNCL_MESS_THICK		, NULL},
	{CNCL_MESS_PAPERLOAD	, NULL},
	{CNCL_MESS_SMLIB		, NULL},
	{CNCL_DITHER_PAT		, NULL},
	{CNCL_BANNER			, NULL},
	{CNCL_CARTRIDGE			, NULL},
	{CNCL_INPUT_GAMMA		, NULL},
	{CNCL_PAPERGAP_COMMAND	, NULL},
	{CNCL_INTENT			, NULL},
	{CNUI_OBJECT_LEVER		, g_lever_name_2007},/* Treat the string ID related to "lever position" as "CNCL value" */
	{-1						, NULL},
};


/* { model , res_name arrays set } table */
/* Models that use the default sets are not included in this table. */
ResSetTable g_res_set_table[] =					//MP140:use default set
{
	{CND_MP210		, g_res_arrays_ip4500type},
	{CND_IP3500		, g_res_arrays_ip4500type},
	{CND_MP520		, g_res_arrays_ip4500type},
	{CND_IP4500		, g_res_arrays_ip4500type},
	{CND_MP610		, g_res_arrays_ip4500type},
	{CND_IP100		, g_res_arrays_ip4500type},
	{CND_IP2600		, g_res_arrays_ip4500type},
	{CND_IP3600		, g_res_arrays_ip4500type},
	{CND_IP4600		, g_res_arrays_ip4500type},
	{CND_MP630		, g_res_arrays_ip4500type},
	{CND_MP540		, g_res_arrays_ip4500type},
	{CND_MP240		, g_res_arrays_ip4500type},
	{CND_MP190		, g_res_arrays_ip4500type},
	{CND_IP1900		, g_res_arrays_ip4500type},
	{-1				, NULL},
};


