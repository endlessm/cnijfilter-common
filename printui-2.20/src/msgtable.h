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
	"supply_na",
};

short g_supply_value[] =
{
	CND_SUPPLY_MANUAL,			// Manual Feed
	CND_SUPPLY_ASF,				// Auto Sheet Feeder
	CND_SUPPLY_ASF2,			// Auto Sheet Feeder 2
	CND_SUPPLY_CASSETTE,		// Cassette 1
	CND_SUPPLY_CASSETTE2,		// Cassette 2
	CND_SUPPLY_CONSECUTIVE,		// Consecutive Feeder
	CND_SUPPLY_CONSECUTIVE2,	// Consecutive Feeder 2
	CND_SUPPLY_TRACTOR,			// Tractor Feeder
	CND_SUPPLY_NA,				// Not Applicable
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
	"size_a5_l",
	"size_a4",
	"size_a4_l",
	"size_a3",
	"size_a3_l",
	"size_a2",
	"size_b5",
	"size_b5_l",
	"size_b4",
	"size_b4_l",
	"size_b3",
	"size_letter",
	"size_letter_l",
	"size_legal",
	"size_legal_l",
	"size_ledger",
	"size_ledger_l",
	"size_csize",
	"size_post",
	"size_post_l",
	"size_env_10",
	"size_env_dl",
	"size_fools",
	"size_fan8_11",
	"size_fan9_11",
	"size_fan10_11",
	"size_fan10_12",
	"size_fan12_8",
	"size_fan14_11",
	"size_fan15_11",
	"size_fan15_12",
	"size_fan_us",
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
//	"size_disctray",
	"size_panorama",
	"size_na",
};

short g_size_value[] =
{
	CND_SIZE_A5,			// A5 (148mm x 210mm)
	CND_SIZE_A5_L,			// A5-L (210mm x 148mm)
	CND_SIZE_A4,			// A4 (210mm x 297mm)
	CND_SIZE_A4_L,			// A4-L (297mm x 210mm)
	CND_SIZE_A3,			// A3 (297mm x 420mm)
	CND_SIZE_A3_L,			// A3-L (420mm x 297mm)
	CND_SIZE_A2,			// A2 (420mm x 594mm)
	CND_SIZE_B5,			// B5 (182mm x 257mm)
	CND_SIZE_B5_L,			// B5-L (257mm x 182mm)
	CND_SIZE_B4,			// B4 (257mm x 364mm)
	CND_SIZE_B4_L,			// B4-L (364mm x 257mm)
	CND_SIZE_B3,			// B3 (364mm x 515mm)
	CND_SIZE_LETTER,		// Letter (8.5x 11inch)
	CND_SIZE_LETTER_L,		// Letter-L (11inch x 8.5inch)
	CND_SIZE_LEGAL,			// Legal (8.5inch x 14inch)
	CND_SIZE_LEGAL_L,		// Legal-L (14inch x 8.5inch)
	CND_SIZE_LEDGER,		// Ledger  (11inch x 17inch)
	CND_SIZE_LEDGER_L,		// Ledger-L (17inch x 11inch)
	CND_SIZE_CSIZE,			// C size (17 x 22inch)
	CND_SIZE_POST,			// Postcard (10mm 0x 148mm)
	CND_SIZE_POST_L,		// Postcard-L (14mm 8x 100mm)
	CND_SIZE_ENV_10,		// #10 Envelope (9.5inch x 4.125inch)
	CND_SIZE_ENV_DL,		// DL Envelope (220mm x 110mm)
	CND_SIZE_FOOLS,			// Foolscap (13.5inch x 17inch)
	CND_SIZE_FAN8_11,		// Fanfold (8.5inch x 11inch)
	CND_SIZE_FAN9_11,		// Fanfold (9.5inch x 11inch)
	CND_SIZE_FAN10_11,		// Fanfold (10inch x 11inch)
	CND_SIZE_FAN10_12,		// Fanfold (10inch x 12inch)
	CND_SIZE_FAN12_8,		// Fanfold (12inch x 8.5inch)
	CND_SIZE_FAN14_11,		// Fanfold (14.5inch x 11inch)
	CND_SIZE_FAN15_11,		// Fanfold (15inch x 11inch)
	CND_SIZE_FAN15_12,		// Fanfold (15inch x 12inch)
	CND_SIZE_FAN_US,		// Fanfold (14.875inch x 11inch)
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
//	CND_SIZE_DISCTRAY,		// Disc tray
	CND_SIZE_PANORAMA,		// Panorama
	CND_SIZE_NA,			// Not Applicable
};

char *g_quality_msg_name[] =
{
	"qmessage_fine",
	"qmessage_fine2",
	"qmessage_cp",
	"qmessage_hq",
	"qmessage_normal",
	"qmessage_hs",
	"qmessage_economy",
	"qmessage_photo0",
	"qmessage_photo",
	"qmessage_photo2",
	"qmessage_draft",
	"qmessage_q1",
	"qmessage_q2",
	"qmessage_q3",
	"qmessage_q4",
	"qmessage_q2_std",
	"qmessage_na",
};

short g_quality_msg_value[] =
{
	CND_QMESSAGE_FINE,		// Fine
	CND_QMESSAGE_FINE2,		// Super fine
	CND_QMESSAGE_CP,		// CP
	CND_QMESSAGE_HQ,		// HQ
	CND_QMESSAGE_NORMAL,	// Normal
	CND_QMESSAGE_HS,		// HS
	CND_QMESSAGE_ECONOMY,	// Economy
	CND_QMESSAGE_PHOTO0,	// Photo 0
	CND_QMESSAGE_PHOTO,		// Photo
	CND_QMESSAGE_PHOTO2,	// Photo fine
	CND_QMESSAGE_DRAFT,		// Draft
	CND_QMESSAGE_Q1,		// Standard (Speed oriented)
	CND_QMESSAGE_Q2,		// Standard (Quality oriented)
	CND_QMESSAGE_Q3,		// High quality
	CND_QMESSAGE_Q4,		// Special
	CND_QMESSAGE_Q2_STD,	// Standard (If mode Q1 is not supported)
	CND_QMESSAGE_NA,		// Not Applicable */
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

char *g_resolution_msg_name[] =
{
	"resmess_180_180",
	"resmess_360_360",
	"resmess_720_360",
	"resmess_720_720",
	"resmess_300_300",
	"resmess_600_600",
	"resmess_1200_600",
	"resmess_1200_1200",
	"resmess_1440_720",
	"resmess_1440_1440",
	"resmess_space",
	"resmess_na",
};

short g_resolution_msg_value[] =
{
	CND_RESMESS_180_180,	// 180x180dpi
	CND_RESMESS_360_360,	// 360x360dpi
	CND_RESMESS_720_360,	// 720x360dpi
	CND_RESMESS_720_720,	// 720x720dpi
	CND_RESMESS_300_300,	// 300x300dpi
	CND_RESMESS_600_600,	// 600x600dpi
	CND_RESMESS_1200_600,	// 1200x600dpi
	CND_RESMESS_1200_1200,	// 1200x1200dpi
	CND_RESMESS_1440_720,	// 1440x720dpi
	CND_RESMESS_1440_1440,	// 1440x1440dpi
	CND_RESMESS_SPACE,		// Not display 
	CND_RESMESS_NA,			// Not Applicable
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

