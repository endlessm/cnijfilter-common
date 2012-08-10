/*
 *  CUPS add-on module for Canon Inkjet Printer.
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
 */


#define	EXT_CNCL_INTENT		10000
#define	EXT_CNCL_LOCATION	10001
#define	EXT_CNCL_STAPLESIDE	10002


char *g_media_param[] =
{
	"plain",
	"ohp",
	"bpf",
	"cloth",
	"higloss",
	"postcard",
	"envelope",
	"glossycard",
	"highres",
	"tshirt",
	"thick",
	"higloss2",
	"glossypaper",
	"photocard",
	"prophoto",
	"ijpostcard",
	"matte",
	"superphoto",
	"other",
	"otherphoto",
	"doublesidephoto",
	"fineartphotorag",
	"otherfineart",
	"glossygold",
	"semigloss",
	"proplatinum",
	"prophoto2",
	"glossypost",
	"prophotopost",
	"postcardaddress",
	"__na",
};

short g_media_value[] = {
	CND_MEDIA_PLAIN,			// Plain Paper
	CND_MEDIA_OHP,				// OHP
	CND_MEDIA_BPF,				// Back Print Film (BF-102)
	CND_MEDIA_BJCLOTH,			// BJ Cloth (FS-101)
	CND_MEDIA_HIGLOSSFILM,		// High Glossy Film (HG-101)
	CND_MEDIA_POSTCARD,			// Postcard
	CND_MEDIA_ENVELOPE,			// Envelope
	CND_MEDIA_GLOSSYPOSTCARD,	// Glossy Postcard (KH-101)
	CND_MEDIA_HIRES,			// High Resolution Paper (HR-101)
	CND_MEDIA_TSHIRT,			// T-shirt Transfer
	CND_MEDIA_THICK,			// Thick Paper
	CND_MEDIA_HIGLOSSPHTFILM,	// High Gloss Photo Film (HG-201)
	CND_MEDIA_GLOSSYPHOTO,		// Glossy Photo Paper (GP-201)
	CND_MEDIA_GLOSSYPHOTOCARD,	// Glossy Photo Cards (FM-101)
	CND_MEDIA_PROPHOTO,			// Professional Photo Paper
	CND_MEDIA_INKJET_POST,		// Inkjet Postcard
	CND_MEDIA_MATTE,			// Matte Photo Paper
	CND_MEDIA_SUPER_PHOTO,		// Super Photo Paper
	CND_MEDIA_OTHER,			// Other Media
	CND_MEDIA_OTHER_PHOTO_PAPER,
	CND_MEDIA_DUPLEX_GLOSSY_PAPER,
	CND_MEDIA_FINE_ART_PAPER,		// Fine Art Photo Rag
	CND_MEDIA_OTHER_FINE_ART_PAPER,	// Other Fine Art Paper
	CND_MEDIA_PHOTO_PAPER_PLUS_GLOSSY_II,	//Photo Paper Plus Glossy II
	CND_MEDIA_PHOTO_PAPER_SEMI_GLOSS,	//Photo Paper Plus Semi-gloss
	CND_MEDIA_PHOTO_PAPER_PRO_PLATINUM,		//Photo Paper Pro Platinum
	CND_MEDIA_PHOTO_PAPER_PRO_II,			//Photo Paper Pro II
	CND_MEDIA_CONTENTS_GLOSSY,
	CND_MEDIA_CONTENTS_PROPHOTO,
	CND_MEDIA_ADDRESS_POSTCARD,
	CND_MEDIA_NA,					// Not Applicable
};

char *g_supply_param[] =
{
	"manual",
	"asf",
	"__asf2",
	"cassette1",
	"cassette2",
	"__consecutive",
	"__consecutive2",
	"tractor",
	"cassette",
	"switch",
	"front",
	"frontplain",
	"continuous",
	"auto",
	"__na",
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
    CND_SUPPLY_CASSETTE_02,			// Cassette iP4100 type
    CND_SUPPLY_PRINTER_SW_SELECT,	// Paper Feed Switch
	CND_SUPPLY_CASSETTE_04,		/* Front Feeder */
	CND_SUPPLY_FRONT_FOR_PLAIN,		/* Front for plain(original) */
	CND_SUPPLY_AUTO_CONTINUOUS_FEED,//Continuous Autofeed
	CND_SUPPLY_AUTO_SELECT,			//Automatically Select
	CND_SUPPLY_NA,					// Not Applicable
};

char *g_size_param[] =
{
	"a5",
	"a5l",
	"a4",
	"a4l",
	"a3",
	"a3l",
	"a2",
	"b5",
	"b5l",
	"b4",
	"b4l",
	"b3",
	"letter",
	"letterl",
	"legal",
	"legall",
	"ledger",
	"ledgerl",
	"csheet",
	"postcard",
	"postcardl",
	"envelop10",
	"envelopdl",
	"foolscap",
	"__fan8_11",
	"__fan9_11",
	"__fan10_11",
	"__fan10_12",
	"__fan12_8",
	"__fan14_11",
	"__fan15_11",
	"__fan15_12",
	"__fan_us",
	"envj4",
	"envj6",
	"letterbleed",
	"a4bleed",
	"a3plus",
	"photocard",
	"user",
	"envelop10p",
	"envelopdlp",
	"envj4p",
	"envj6p",
	"l",
	"2l",
	"4X6",
//	"disctray",
	"panorama",
	"5X7",
	"postdbl",
//	"envchou3p",
//	"envchou4p",
	"businesscard",
	"creditcard",
	"4X8",
	"10X12",
	"8X10",
	"fineartletter",
	"finearta4",
	"wide",
	"__na",
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
	CND_SIZE_5X7,			// Actual Size 5x7 ( 127mm x 177.8mm )
	CND_SIZE_POST_DBL,		// Double postal card ( 200mm x 148mm )
//	CND_SIZE_ENV_CHOU3_P,	// Long Env #3( 120mm x 235mm )
//	CND_SIZE_ENV_CHOU4_P,	// Long Env #4 ( 90mm x 205mm ) 
	CND_SIZE_BUSINESSCARD,
	CND_SIZE_CREDITCARD,
	CND_SIZE_4X8,
	CND_SIZE_4GIRI,
	CND_SIZE_6GIRI,
	CND_SIZE_LETTER_FINE_ART, // Fine Art Letter (8.5x 11inch)
	CND_SIZE_A4_FINE_ART,
	CND_SIZE_HIVISION,
	CND_SIZE_NA,			// Not Applicable
};

char *g_halftoning_param[] =
{
	"pattern",
	"pattern",
	"pattern",
	"ed",
	"__na",
};

short g_halftoning_value[] =
{
	CND_UIBIN_PATTERN,		// Pattern
	CND_UIBIN_PATTERN_HS,	// Pattern (High speed)
	CND_UIBIN_V_PATTERN,	// V-Pattern
	CND_UIBIN_ED,			// ED
	CND_UIBIN_NA,			// Not Applicable
};

char *g_cartridge_param[] =
{
	"color",
	"bk",
	"photo",
	"bkcolor",
	"bkphoto",
	"photocolor",
	"__na",
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

char *g_quality_param[] =
{
	"1",
	"2",
	"3",
	"4",
	"5",
	"__na",
};

short g_quality_value[] =
{
	CND_QUALITY_ABSOLUTE_SPECIAL,
	CND_QUALITY_ABSOLUTE_HQ,
	CND_QUALITY_ABSOLUTE_MQ,
	CND_QUALITY_ABSOLUTE_NORMAL,
	CND_QUALITY_ABSOLUTE_HS,
	CND_QUALITY_ABSOLUTE_NA,
};

char *g_input_gamma_param[] =
{
	"1.0",
	"1.4",
	"1.8",
	"2.2",
	"__na",
};

short g_input_gamma_value[] =
{
	CND_GAMMA_10,				// Gamma 1.0
	CND_GAMMA_14,				// Gamma 1.4
	CND_GAMMA_18,				// Gamma 1.8
	CND_GAMMA_22,				// Gamma 2.2
	CND_GAMMA_NA,				// Not Applicable
};

char *g_intent_param[] =
{
	"photo",
	"graphics",
	"vivid",
	"__na",
};

short g_intent_value[] =
{
	CND_INTENT_PHOTO,
	CND_INTENT_GRAPHICS,
	CND_INTENT_VIVID,
	CND_INTENT_NA,
};

char *g_grayscale_param[] =
{
	"true",
	"false",
	"false",
	"__na",
};

short g_grayscale_value[] =
{
	CND_BJGRAYSCALE_ON,
	CND_BJGRAYSCALE_OFF,
	CND_BJGRAYSCALE_GRAY,
	CND_BJGRAYSCALE_NA,
};


/* Ver.3.00 */
char *g_location_param_lpr[] =
{
	"top-left",
	"center",
	"__na",
};

short g_location_value[] =
{
	LOCATION_UPPERLEFT,
	LOCATION_CENTER,
	-1,
};

char *g_paper_gap_param[] =
{
	"auto",
	"wide",
	"narrow",
	"__na",
};

short g_paper_gap_value[] =
{
	CND_PGAP_CMD_AUTO,			// Auto
	CND_PGAP_CMD_WIDE,			// Wide
	CND_PGAP_CMD_NARROW,		// Narrow
	CND_PGAP_CMD_NA,			// Not Applicable
};

char *g_duplex_param[] =
{
	"false",
	"true",
	"__na",
};

short g_duplex_value[] =
{
	CND_DUPLEX_OFF,
	CND_DUPLEX_AUTO,
	CND_DUPLEX_NA,
};

char *g_staple_side_param[] =
{
	"longside",
	"shortside",
	"__na",
};

short g_staple_side_value[] =
{
	STAPLESIDE_LONG,
	STAPLESIDE_SHORT,
	-1,
};

