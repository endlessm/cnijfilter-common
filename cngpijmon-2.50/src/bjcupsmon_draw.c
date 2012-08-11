/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2005
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License.
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

/*** Includes ***/
#include "bjcupsmon_common.h"
#include "bjcupsmon_draw.h"
#include "bjcupsmon_funcprot.h"


/*** Global parameters ***/
PUBLIC GdkPixmap	*gpPixmap = NULL;		// Pointer to pixmaps.

PRIVATE gint		gDW, gDH;				// Pixmap default dx, dy.

PRIVATE GdkPixmap	*gpInkEL = NULL;		// Cartridge edge left Pixmap.
PRIVATE GdkPixmap	*gpInkER = NULL;		// Cartridge edge right Pixmap.
PRIVATE GdkPixmap	*gpInkBK = NULL;		// Ink black Pixmap.
PRIVATE GdkPixmap	*gpInkPB = NULL;		// Ink photo black Pixmap.
//PRIVATE GdkPixmap	*gpInkSB = NULL;		// Ink photo black Pixmap.
PRIVATE GdkPixmap	*gpInkBB = NULL;		// Ink big black Pixmap.
PRIVATE GdkPixmap	*gpInkPC = NULL;		// Ink photo cyan Pixmap.
PRIVATE GdkPixmap	*gpInkPM = NULL;		// Ink photo magenta Pixmap.
PRIVATE GdkPixmap	*gpInkCY = NULL;		// Ink cyan Pixmap.
PRIVATE GdkPixmap	*gpInkMA = NULL;		// Ink magenta Pixmap.
PRIVATE GdkPixmap	*gpInkYE = NULL;		// Ink yellow Pixmap.
PRIVATE GdkPixmap	*gpInkRE = NULL;		// Ink Red Pixmap.990i
PRIVATE GdkPixmap	*gpInkGR = NULL;		// Ink Green Pixmap.ip8600i
PRIVATE GdkPixmap	*gpInk24B = NULL;		// S300 Black Pixmap.
PRIVATE GdkPixmap	*gpInk24C = NULL;		// S300 Color Pixmap.
PRIVATE GdkPixmap	*gpInkLow = NULL;		// Ink low Fill Pixmap.
PRIVATE GdkPixmap	*gpInkOut = NULL;		// Ink out Fill Pixmap.
PRIVATE GdkPixmap	*gpInkLowBB = NULL;		// Ink low Fill Pixmap (for Big Black).
PRIVATE GdkPixmap	*gpInkOutBB = NULL;		// Ink out Fill Pixmap (for Big Black).
PRIVATE GdkPixmap	*gpInkLow70 = NULL;		// Ink 70% Fill Pixmap.
PRIVATE GdkPixmap	*gpInkLow40 = NULL;		// Ink 40% Fill Pixmap.
PRIVATE GdkPixmap	*gpInkLow10 = NULL;		// Ink 10% Fill Pixmap.
PRIVATE GdkPixmap	*gpInk24B1 = NULL;		// S300 Black Pixmap (Ink low level1).
PRIVATE GdkPixmap	*gpInk24B2 = NULL;		// S300 Black Pixmap (Ink low level2).
PRIVATE GdkPixmap	*gpInk24B3 = NULL;		// S300 Black Pixmap (Ink low level3).
PRIVATE GdkPixmap	*gpInk24C1 = NULL;		// S300 Color Pixmap (Ink low level1).
PRIVATE GdkPixmap	*gpInk24C2 = NULL;		// S300 Color Pixmap (Ink low level2).
PRIVATE GdkPixmap	*gpInk24C3 = NULL;		// S300 Color Pixmap (Ink low level3).
PRIVATE GdkPixmap	*gpInkSP = NULL;		// Ink space for big black Pixmap.

PRIVATE GdkBitmap	*gpMaskEL = NULL;		// Mask for left edge.
PRIVATE GdkBitmap	*gpMaskER = NULL;		// Mask for right edge.
PRIVATE GdkBitmap	*gpMaskLow = NULL;		// Ink low Pixmap Mask.
PRIVATE GdkBitmap	*gpMaskOut = NULL;		// Ink out Pixmap Mask.
PRIVATE GdkBitmap	*gpMaskLowBB = NULL;	// Ink low Pixmap Mask (for Big Black).
PRIVATE GdkBitmap	*gpMaskOutBB = NULL;	// Ink out Pixmap Mask (for Big Black).
PRIVATE GdkBitmap	*gpMaskLow70 = NULL;	// Ink 70% Pixmap Mask.
PRIVATE GdkBitmap	*gpMaskLow40 = NULL;	// Ink 40% Pixmap Mask.
PRIVATE GdkBitmap	*gpMaskLow10 = NULL;	// Ink 10% Pixmap Mask.
PRIVATE GdkBitmap	*gpMask24B = NULL;		// Mask for S300 Black (CIL:OFF).
PRIVATE GdkBitmap	*gpMask24C = NULL;		// Mask for S300 Color (CIL:OFF).
PRIVATE GdkBitmap	*gpMask24B1 = NULL;		// Mask for S300 Black (Ink low level1).
PRIVATE GdkBitmap	*gpMask24B3 = NULL;		// Mask for S300 Black (Ink low level3).
PRIVATE GdkBitmap	*gpMask24C1 = NULL;		// Mask for S300 Color (Ink low level1).
PRIVATE GdkBitmap	*gpMask24C3 = NULL;		// Mask for S300 Color (Ink low level3).
PRIVATE GdkBitmap	*gpMaskSP = NULL;		// Mask for space.
PRIVATE GdkBitmap	*gpMaskNal = NULL;		// Mask nallow.
PRIVATE GdkBitmap	*gpMaskWid = NULL;		// Mask wide (for Big Black).

PRIVATE GdkPixmap	**gpInk[CARTRIDGE_PIXMAP_NUM];	// Set of pixmaps.
PRIVATE GdkBitmap	**gpMask[CARTRIDGE_PIXMAP_NUM];	// Set of masks.

PRIVATE gchar		gPixmapDirectory[MAX_BUF_SIZE];	// Directory path pixmap file exists

PRIVATE guint		gCartridgeWidth[CARTRIGE_TYPE_NUM] = {108, 57, 0, 74, 82, 40, 40, 108, 99, 125, 142 };	// ip8600

PRIVATE ST_CartridgePattern	gPatternTable[CARTRIGE_TYPE_NUM][MAX_PIXMAP_NUM] = {
	{{ID_PIXMAP_EL, 3},		// for F850 type.
	 {ID_PIXMAP_BK, 17},
	 {ID_PIXMAP_PC, 17},
	 {ID_PIXMAP_PM, 17},
	 {ID_PIXMAP_CY, 17},
	 {ID_PIXMAP_MA, 17},
	 {ID_PIXMAP_YE, 17},
	 {ID_PIXMAP_ER,  3},
	 {-1, 0},
	 {-1, 0}},
	{{ID_PIXMAP_EL,  3},		// for F360 type (Black).
	 {ID_PIXMAP_SP, 13},
	 {ID_PIXMAP_BB, 25},
	 {ID_PIXMAP_SP, 13},
	 {ID_PIXMAP_ER,  3},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0}},
	{{-1, 0},				// (for F360 type (Color)).
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0}},
	{{ID_PIXMAP_EL,  3},		// for F360 type (Photo).
	 {ID_PIXMAP_PB, 17},
	 {ID_PIXMAP_PC, 17},
	 {ID_PIXMAP_PM, 17},
	 {ID_PIXMAP_YE, 17},
	 {ID_PIXMAP_ER,  3},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0}},
	{{ID_PIXMAP_EL,  3},		// for S600 type.
	 {ID_PIXMAP_BB, 25},
	 {ID_PIXMAP_CY, 17},
	 {ID_PIXMAP_MA, 17},
	 {ID_PIXMAP_YE, 17},
	 {ID_PIXMAP_ER,  3},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0}},
	{{ID_PIXMAP_C, 20},		// for S300 type (CIL:OFF).
	 {ID_PIXMAP_B, 20},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0}},
	{{ID_PIXMAP_C, 20},		// for S300 type (CIL:ON).
	 {ID_PIXMAP_B, 20},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0}},
	{{ID_PIXMAP_EL,  3},		// for 950i type.
	 {ID_PIXMAP_CY, 17},
	 {ID_PIXMAP_PC, 17},
	 {ID_PIXMAP_BK, 17},
	 {ID_PIXMAP_YE, 17},
	 {ID_PIXMAP_PM, 17},
	 {ID_PIXMAP_MA, 17},
	 {ID_PIXMAP_ER,  3},
	 {-1, 0},
	 {-1, 0}},
	{{ID_PIXMAP_EL,  3},		// for 860i type.
	 {ID_PIXMAP_SB, 17},
	 {ID_PIXMAP_BB, 25},
	 {ID_PIXMAP_CY, 17},
	 {ID_PIXMAP_MA, 17},
	 {ID_PIXMAP_YE, 17},
	 {ID_PIXMAP_ER,  3},
	 {-1, 0},
	 {-1, 0},
	 {-1, 0}},
	{{ID_PIXMAP_EL,  3},		// for 990i type.
	 {ID_PIXMAP_PM, 17},
	 {ID_PIXMAP_RE, 17},
	 {ID_PIXMAP_BK, 17},
	 {ID_PIXMAP_PC, 17},
	 {ID_PIXMAP_CY, 17},
	 {ID_PIXMAP_MA, 17},
	 {ID_PIXMAP_YE, 17},
	 {ID_PIXMAP_ER,  3},
	 {-1, 0}},
	{{ID_PIXMAP_EL,  3},		// for ip8600i type.
	 {ID_PIXMAP_GR, 17},
	 {ID_PIXMAP_RE, 17},
	 {ID_PIXMAP_PM, 17},
	 {ID_PIXMAP_BK, 17},
	 {ID_PIXMAP_PC, 17},
	 {ID_PIXMAP_CY, 17},
	 {ID_PIXMAP_MA, 17},
	 {ID_PIXMAP_YE, 17},
	 {ID_PIXMAP_ER,  3}}
};

PRIVATE gchar *gCartridgeXPMFileSet[CARTRIGE_CLASS_NUM][CARTRIDGE_XPM_SET_NUM] = {
	{STR_PIXMAP_FILE_NAME_GREEN_EL,		// for F850 type (exchange:yes).
	 STR_PIXMAP_FILE_NAME_GREEN_ER,
	 STR_PIXMAP_FILE_NAME_GREEN_BK,
	 STR_PIXMAP_FILE_NAME_GREEN_PC,
	 STR_PIXMAP_FILE_NAME_GREEN_PM,
	 STR_PIXMAP_FILE_NAME_GREEN_CY,
	 STR_PIXMAP_FILE_NAME_GREEN_MA,
	 STR_PIXMAP_FILE_NAME_GREEN_YE,
	 STR_PIXMAP_FILE_NAME_LOW,
	 STR_PIXMAP_FILE_NAME_OUT,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_BLACK_EL,		// for F850 type (exchange:no).
	 STR_PIXMAP_FILE_NAME_BLACK_ER,
	 STR_PIXMAP_FILE_NAME_BLACK_BK,
	 STR_PIXMAP_FILE_NAME_BLACK_PC,
	 STR_PIXMAP_FILE_NAME_BLACK_PM,
	 STR_PIXMAP_FILE_NAME_BLACK_CY,
	 STR_PIXMAP_FILE_NAME_BLACK_MA,
	 STR_PIXMAP_FILE_NAME_BLACK_YE,
	 STR_PIXMAP_FILE_NAME_LOW_10,
	 STR_PIXMAP_FILE_NAME_LOW_40,
	 STR_PIXMAP_FILE_NAME_LOW_70,
	 STR_PIXMAP_FILE_NAME_OUT,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_GREEN_EL,		// for F360 type (Black, exchange:yes).
	 STR_PIXMAP_FILE_NAME_GREEN_ER,
	 STR_PIXMAP_FILE_NAME_GREEN_BB,
	 STR_PIXMAP_FILE_NAME_GREEN_SP,
	 STR_PIXMAP_FILE_NAME_LOW_BB,
	 STR_PIXMAP_FILE_NAME_OUT_BB,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_BLACK_EL,		// for F360 type (Black, exchange:no).
	 STR_PIXMAP_FILE_NAME_BLACK_ER,
	 STR_PIXMAP_FILE_NAME_BLACK_BB,
	 STR_PIXMAP_FILE_NAME_BLACK_SP,
	 STR_PIXMAP_FILE_NAME_LOW_BB,
	 STR_PIXMAP_FILE_NAME_OUT_BB,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{NULL,								// (for F360 type (Color, exchange:yes)).
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{NULL,								// (for F360 type (Color, exchange:no)).
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_GREEN_EL,		// for F360 type (Photo, exchange:yes).
	 STR_PIXMAP_FILE_NAME_GREEN_ER,
	 STR_PIXMAP_FILE_NAME_GREEN_PB,
	 STR_PIXMAP_FILE_NAME_GREEN_PC,
	 STR_PIXMAP_FILE_NAME_GREEN_PM,
	 STR_PIXMAP_FILE_NAME_GREEN_YE,
	 STR_PIXMAP_FILE_NAME_LOW,
	 STR_PIXMAP_FILE_NAME_OUT,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_BLACK_EL,		// for F360 type (Photo, exchange:no).
	 STR_PIXMAP_FILE_NAME_BLACK_ER,
	 STR_PIXMAP_FILE_NAME_BLACK_PB,
	 STR_PIXMAP_FILE_NAME_BLACK_PC,
	 STR_PIXMAP_FILE_NAME_BLACK_PM,
	 STR_PIXMAP_FILE_NAME_BLACK_YE,
	 STR_PIXMAP_FILE_NAME_LOW,
	 STR_PIXMAP_FILE_NAME_OUT,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_GREEN_EL,			// for S600 type (exchange:yes).
	 STR_PIXMAP_FILE_NAME_GREEN_ER,
	 STR_PIXMAP_FILE_NAME_GREEN_BB,
	 STR_PIXMAP_FILE_NAME_GREEN_CY,
	 STR_PIXMAP_FILE_NAME_GREEN_MA,
	 STR_PIXMAP_FILE_NAME_GREEN_YE,
	 STR_PIXMAP_FILE_NAME_LOW,
	 STR_PIXMAP_FILE_NAME_OUT,
	 STR_PIXMAP_FILE_NAME_LOW_BB,
	 STR_PIXMAP_FILE_NAME_OUT_BB,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_BLACK_EL,			// for S600 type (exchange:no).
	 STR_PIXMAP_FILE_NAME_BLACK_ER,
	 STR_PIXMAP_FILE_NAME_BLACK_BB,
	 STR_PIXMAP_FILE_NAME_BLACK_CY,
	 STR_PIXMAP_FILE_NAME_BLACK_MA,
	 STR_PIXMAP_FILE_NAME_BLACK_YE,
	 STR_PIXMAP_FILE_NAME_LOW,
	 STR_PIXMAP_FILE_NAME_OUT,
	 STR_PIXMAP_FILE_NAME_LOW_BB,
	 STR_PIXMAP_FILE_NAME_OUT_BB,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_24B,			// for S300 type (CIL:OFF).
	 STR_PIXMAP_FILE_NAME_24C,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_24BF,			// for S300 type (CIL:ON).
	 STR_PIXMAP_FILE_NAME_24CF,
	 STR_PIXMAP_FILE_NAME_24B1,
	 STR_PIXMAP_FILE_NAME_24B2,
	 STR_PIXMAP_FILE_NAME_24B3,
	 STR_PIXMAP_FILE_NAME_24C1,
	 STR_PIXMAP_FILE_NAME_24C2,
	 STR_PIXMAP_FILE_NAME_24C3,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{NULL,								// Dummy
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{NULL,								// Dummy.
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_GREEN_EL,		// for 950i type (exchange:yes).
	 STR_PIXMAP_FILE_NAME_GREEN_ER,
	 STR_PIXMAP_FILE_NAME_GREEN_BK,
	 STR_PIXMAP_FILE_NAME_GREEN_PC,
	 STR_PIXMAP_FILE_NAME_GREEN_PM,
	 STR_PIXMAP_FILE_NAME_GREEN_CY,
	 STR_PIXMAP_FILE_NAME_GREEN_MA,
	 STR_PIXMAP_FILE_NAME_GREEN_YE,
	 STR_PIXMAP_FILE_NAME_LOW_10,
	 STR_PIXMAP_FILE_NAME_LOW_40,
	 STR_PIXMAP_FILE_NAME_LOW_70,
	 STR_PIXMAP_FILE_NAME_OUT,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_BLACK_EL,		// for 950i type (exchange:no).
	 STR_PIXMAP_FILE_NAME_BLACK_ER,
	 STR_PIXMAP_FILE_NAME_BLACK_BK,
	 STR_PIXMAP_FILE_NAME_BLACK_PC,
	 STR_PIXMAP_FILE_NAME_BLACK_PM,
	 STR_PIXMAP_FILE_NAME_BLACK_CY,
	 STR_PIXMAP_FILE_NAME_BLACK_MA,
	 STR_PIXMAP_FILE_NAME_BLACK_YE,
	 STR_PIXMAP_FILE_NAME_LOW_10,
	 STR_PIXMAP_FILE_NAME_LOW_40,
	 STR_PIXMAP_FILE_NAME_LOW_70,
	 STR_PIXMAP_FILE_NAME_OUT,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_GREEN_EL,			// for 860i type (exchange:yes).
	 STR_PIXMAP_FILE_NAME_GREEN_ER,
	 STR_PIXMAP_FILE_NAME_GREEN_PB,
	 STR_PIXMAP_FILE_NAME_GREEN_BB,
	 STR_PIXMAP_FILE_NAME_GREEN_CY,
	 STR_PIXMAP_FILE_NAME_GREEN_MA,
	 STR_PIXMAP_FILE_NAME_GREEN_YE,
	 STR_PIXMAP_FILE_NAME_LOW,
	 STR_PIXMAP_FILE_NAME_OUT,
	 STR_PIXMAP_FILE_NAME_LOW_BB,
	 STR_PIXMAP_FILE_NAME_OUT_BB,
	 NULL,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_BLACK_EL,			// for 860i type (exchange:no).
	 STR_PIXMAP_FILE_NAME_BLACK_ER,
	 STR_PIXMAP_FILE_NAME_BLACK_PB,
	 STR_PIXMAP_FILE_NAME_BLACK_BB,
	 STR_PIXMAP_FILE_NAME_BLACK_CY,
	 STR_PIXMAP_FILE_NAME_BLACK_MA,
	 STR_PIXMAP_FILE_NAME_BLACK_YE,
	 STR_PIXMAP_FILE_NAME_LOW,
	 STR_PIXMAP_FILE_NAME_OUT,
	 STR_PIXMAP_FILE_NAME_LOW_BB,
	 STR_PIXMAP_FILE_NAME_OUT_BB,
	 NULL,
	 NULL,
	 NULL},
	{STR_PIXMAP_FILE_NAME_GREEN_EL,		// for 990i type (exchange:yes).
	 STR_PIXMAP_FILE_NAME_GREEN_ER,
	 STR_PIXMAP_FILE_NAME_GREEN_BK,
	 STR_PIXMAP_FILE_NAME_GREEN_PC,
	 STR_PIXMAP_FILE_NAME_GREEN_PM,
	 STR_PIXMAP_FILE_NAME_GREEN_CY,
	 STR_PIXMAP_FILE_NAME_GREEN_MA,
	 STR_PIXMAP_FILE_NAME_GREEN_YE,
	 STR_PIXMAP_FILE_NAME_GREEN_RE,
	 STR_PIXMAP_FILE_NAME_LOW_10,
	 STR_PIXMAP_FILE_NAME_LOW_40,
	 STR_PIXMAP_FILE_NAME_LOW_70,
	 STR_PIXMAP_FILE_NAME_OUT,
	 NULL},
	{STR_PIXMAP_FILE_NAME_BLACK_EL,		// for 990i type (exchange:no).
	 STR_PIXMAP_FILE_NAME_BLACK_ER,
	 STR_PIXMAP_FILE_NAME_BLACK_BK,
	 STR_PIXMAP_FILE_NAME_BLACK_PC,
	 STR_PIXMAP_FILE_NAME_BLACK_PM,
	 STR_PIXMAP_FILE_NAME_BLACK_CY,
	 STR_PIXMAP_FILE_NAME_BLACK_MA,
	 STR_PIXMAP_FILE_NAME_BLACK_YE,
	 STR_PIXMAP_FILE_NAME_BLACK_RE,
	 STR_PIXMAP_FILE_NAME_LOW_10,
	 STR_PIXMAP_FILE_NAME_LOW_40,
	 STR_PIXMAP_FILE_NAME_LOW_70,
	 STR_PIXMAP_FILE_NAME_OUT,
	 NULL},
	{STR_PIXMAP_FILE_NAME_GREEN_EL,		// for ip8600i type (exchange:yes).
	 STR_PIXMAP_FILE_NAME_GREEN_ER,
	 STR_PIXMAP_FILE_NAME_GREEN_BK,
	 STR_PIXMAP_FILE_NAME_GREEN_PC,
	 STR_PIXMAP_FILE_NAME_GREEN_PM,
	 STR_PIXMAP_FILE_NAME_GREEN_CY,
	 STR_PIXMAP_FILE_NAME_GREEN_MA,
	 STR_PIXMAP_FILE_NAME_GREEN_YE,
	 STR_PIXMAP_FILE_NAME_GREEN_RE,
	 STR_PIXMAP_FILE_NAME_GREEN_GR,
	 STR_PIXMAP_FILE_NAME_LOW_10,
	 STR_PIXMAP_FILE_NAME_LOW_40,
	 STR_PIXMAP_FILE_NAME_LOW_70,
	 STR_PIXMAP_FILE_NAME_OUT
	 },
	{STR_PIXMAP_FILE_NAME_BLACK_EL,		// for ip8600i type (exchange:no).
	 STR_PIXMAP_FILE_NAME_BLACK_ER,
	 STR_PIXMAP_FILE_NAME_BLACK_BK,
	 STR_PIXMAP_FILE_NAME_BLACK_PC,
	 STR_PIXMAP_FILE_NAME_BLACK_PM,
	 STR_PIXMAP_FILE_NAME_BLACK_CY,
	 STR_PIXMAP_FILE_NAME_BLACK_MA,
	 STR_PIXMAP_FILE_NAME_BLACK_YE,
	 STR_PIXMAP_FILE_NAME_BLACK_RE,
	 STR_PIXMAP_FILE_NAME_BLACK_GR,
	 STR_PIXMAP_FILE_NAME_LOW_10,
	 STR_PIXMAP_FILE_NAME_LOW_40,
	 STR_PIXMAP_FILE_NAME_LOW_70,
	 STR_PIXMAP_FILE_NAME_OUT},
};

PRIVATE ST_CartridgeXPMFileInfo	gCartridgeXPMFileInfo[] = {
	{STR_PIXMAP_FILE_NAME_GREEN_EL,	&gpInkEL,		&gpMaskEL},		// Edge left (Background = Green)
	{STR_PIXMAP_FILE_NAME_GREEN_ER,	&gpInkER,		&gpMaskER},		// Edge right (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_EL,	&gpInkEL,		&gpMaskEL},		// Edge left (Background = Black)
	{STR_PIXMAP_FILE_NAME_BLACK_ER,	&gpInkER,		&gpMaskER},		// Edge right (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_BK,	&gpInkBK,		NULL},			// Black (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_BK,	&gpInkBK,		&gpMaskNal /*NULL*/},			// Black (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_PB,	&gpInkPB,		NULL},			// Photo Black (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_PB,	&gpInkPB,		NULL},			// Photo Black (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_BB,	&gpInkBB,		&gpMaskWid},	// Big Black (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_BB,	&gpInkBB,		&gpMaskWid},	// Big Black (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_SB,	&gpInkPB,		NULL},			// Photo Black (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_SB,	&gpInkPB,		NULL},			// Photo Black (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_PC,	&gpInkPC,		NULL},			// Photo Cyan (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_PC,	&gpInkPC,		&gpMaskNal /*NULL*/},			// Photo Cyan (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_PM,	&gpInkPM,		NULL},			// Photo Magenta (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_PM,	&gpInkPM,		&gpMaskNal /*NULL*/},			// Photo Magenta (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_CY,	&gpInkCY,		NULL},			// Cyan (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_CY,	&gpInkCY,		&gpMaskNal /*NULL*/},			// Cyan (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_MA,	&gpInkMA,		NULL},			// Magenta (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_MA,	&gpInkMA,		&gpMaskNal /*NULL*/},			// Magenta (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_YE,	&gpInkYE,		&gpMaskNal},	// Yellow (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_YE,	&gpInkYE,		&gpMaskNal},	// Yellow (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_RE,	&gpInkRE,		&gpMaskNal},	// Red (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_RE,	&gpInkRE,		&gpMaskNal},	// Red (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_GR,	&gpInkGR,		&gpMaskNal},	// Green (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_GR,	&gpInkGR,		&gpMaskNal},	// Green (Background = Black)
	{STR_PIXMAP_FILE_NAME_GREEN_SP,	&gpInkSP,		&gpMaskSP},		// Space (Background = Green)
	{STR_PIXMAP_FILE_NAME_BLACK_SP,	&gpInkSP,		&gpMaskSP},		// Space (Background = Black)
	{STR_PIXMAP_FILE_NAME_24B,		&gpInk24B,		&gpMask24B},	// S300 Black (CIL:OFF)
	{STR_PIXMAP_FILE_NAME_24C,		&gpInk24C,		&gpMask24C},	// S300 Color (CIL:OFF)
	{STR_PIXMAP_FILE_NAME_24BF,		&gpInk24B,		&gpMask24B},	// S300 Black (CIL:ON)
	{STR_PIXMAP_FILE_NAME_24CF,		&gpInk24C,		&gpMask24C},	// S300 Color (CIL:ON)
	{STR_PIXMAP_FILE_NAME_LOW,		&gpInkLow,		&gpMaskLow},	// Ink low (Normal)
	{STR_PIXMAP_FILE_NAME_LOW_BB,	&gpInkLowBB,	&gpMaskLowBB},	// Ink low (for Big Black)
	{STR_PIXMAP_FILE_NAME_LOW_10,	&gpInkLow10,	&gpMaskLow10},	// Ink 10%
	{STR_PIXMAP_FILE_NAME_LOW_40,	&gpInkLow40,	&gpMaskLow40},	// Ink 40%
	{STR_PIXMAP_FILE_NAME_LOW_70,	&gpInkLow70,	&gpMaskLow70},	// Ink 70%
	{STR_PIXMAP_FILE_NAME_OUT,		&gpInkOut,		&gpMaskOut},	// Ink out (Normal)
	{STR_PIXMAP_FILE_NAME_OUT_BB,	&gpInkOutBB,	&gpMaskOutBB},	// Ink out (for Big Black)
	{STR_PIXMAP_FILE_NAME_24B1,		&gpInk24B1,		&gpMask24B1},	// S300 Black ink low level1
	{STR_PIXMAP_FILE_NAME_24B2,		&gpInk24B2,		NULL},			// S300 Black ink low level2
	{STR_PIXMAP_FILE_NAME_24B3,		&gpInk24B3,		&gpMask24B3},	// S300 Black ink low level3
	{STR_PIXMAP_FILE_NAME_24C1,		&gpInk24C1,		&gpMask24C1},	// S300 Color ink low level1
	{STR_PIXMAP_FILE_NAME_24C2,		&gpInk24C2,		NULL},			// S300 Color ink low level2
	{STR_PIXMAP_FILE_NAME_24C3,		&gpInk24C3,		&gpMask24C3},	// S300 Color ink low level3
};


/*** Functions ***/
///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC void initDrawing(void)
// IN     : None.
// OUT    : None.
// RETURN : None.
// 
PUBLIC void initDrawing(void)
{
	gpInk[ID_PIXMAP_BK] = &gpInkBK;
	gpInk[ID_PIXMAP_PB] = &gpInkPB;
	gpInk[ID_PIXMAP_BB] = &gpInkBB;
	gpInk[ID_PIXMAP_SB] = &gpInkPB;
	gpInk[ID_PIXMAP_PC] = &gpInkPC;
	gpInk[ID_PIXMAP_PM] = &gpInkPM;
	gpInk[ID_PIXMAP_CY] = &gpInkCY;
	gpInk[ID_PIXMAP_MA] = &gpInkMA;
	gpInk[ID_PIXMAP_YE] = &gpInkYE;
	gpInk[ID_PIXMAP_RE] = &gpInkRE;
	gpInk[ID_PIXMAP_GR] = &gpInkGR;
	gpInk[ID_PIXMAP_B]  = &gpInk24B;
	gpInk[ID_PIXMAP_C]  = &gpInk24C;
	gpInk[ID_PIXMAP_EL] = &gpInkEL;
	gpInk[ID_PIXMAP_ER] = &gpInkER;
	gpInk[ID_PIXMAP_SP] = &gpInkSP;
	
	gpMask[ID_PIXMAP_BK] = &gpMaskNal;
	gpMask[ID_PIXMAP_PB] = &gpMaskNal;
	gpMask[ID_PIXMAP_BB] = &gpMaskWid;
	gpMask[ID_PIXMAP_SB] = &gpMaskNal;
	gpMask[ID_PIXMAP_PC] = &gpMaskNal;
	gpMask[ID_PIXMAP_PM] = &gpMaskNal;
	gpMask[ID_PIXMAP_CY] = &gpMaskNal;
	gpMask[ID_PIXMAP_MA] = &gpMaskNal;
	gpMask[ID_PIXMAP_YE] = &gpMaskNal;
	gpMask[ID_PIXMAP_RE] = &gpMaskNal;
	gpMask[ID_PIXMAP_GR] = &gpMaskNal;
	gpMask[ID_PIXMAP_B]  = &gpMask24B;
	gpMask[ID_PIXMAP_C]  = &gpMask24C;
	gpMask[ID_PIXMAP_EL] = &gpMaskEL;
	gpMask[ID_PIXMAP_ER] = &gpMaskER;
	gpMask[ID_PIXMAP_SP] = &gpMaskSP;
	
	// Get pixmap directory.
	memset(gPixmapDirectory,0,MAX_BUF_SIZE);
	strncpy(gPixmapDirectory, STR_SHARE_DIRECTORY_NAME, 
	(MAX_BUF_SIZE<(strlen(STR_SHARE_DIRECTORY_NAME)+strlen(STR_PIXMAP_DIRECTORY_NAME)+1))? MAX_BUF_SIZE:strlen(STR_SHARE_DIRECTORY_NAME)+strlen(STR_PIXMAP_DIRECTORY_NAME)+1);
	strcat(gPixmapDirectory, "/");
	strncat(gPixmapDirectory, STR_PIXMAP_DIRECTORY_NAME, strlen(STR_PIXMAP_DIRECTORY_NAME));
	
	return;
}// End initDrawing


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC void updateCartridgePictArea(ST_PrinterStatus *pPrinterStatus, gboolean draw)
// IN     : ST_PrinterStatus *pPrinterStatus : Information of printer status.
//          gboolean draw : Re-draw pictures of cartridge drawing area or not.
// OUT    : None.
// RETURN : None.
// 
PUBLIC void updateCartridgePictArea(ST_PrinterStatus *pPrinterStatus, gboolean draw)
{
/*** Parameters start ***/
	GtkWidget		*widget = NULL;	// Temporary pointer to widget.
	GdkRectangle	updateRect;		// Area to re-draw,
/*** Parameters end ***/

//	printf("updatePictArea\n");
		
	if (pPrinterStatus != NULL) {
		widget = lookupWidget((const gchar*)STR_MAIN_DRAW_CARTRIDGE);
		
		if (!(widget->window))
			return;
		
		drawPixmaps(widget, pPrinterStatus);

//		printf("draw : %d \n",draw);
		
		if (draw == TRUE) {
			updateRect.x = 0;
			updateRect.y = 0;
			updateRect.width = widget->allocation.width;
			updateRect.height = widget->allocation.height;
			gtk_widget_draw(widget, &updateRect);
		}
	}
	
	return;
}// End updateCartrigePictArea


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC void clearCartridgePictArea(void)
// IN     : None.
// OUT    : None.
// RETURN : None.
// 
PUBLIC void clearCartridgePictArea(void)
{
/*** Parameters start ***/
	GtkWidget		*widget = NULL;	// Temporary pointer to widget.
	GdkRectangle	updateRect;		// Area to re-draw,
/*** Parameters end ***/
	
	freePixmaps();
	
	widget = lookupWidget((gchar*)STR_MAIN_DRAW_CARTRIDGE);

	if (!widget->window)
		return;
	
	gpPixmap = gdk_pixmap_new(widget->window, widget->allocation.width, widget->allocation.height, -1);
	gdk_draw_rectangle(gpPixmap, widget->style->bg_gc[GTK_WIDGET_STATE(widget)], TRUE, 0, 0, widget->allocation.width, widget->allocation.height);
	
	updateRect.x = 0;
	updateRect.y = 0;
	updateRect.width = widget->allocation.width;
	updateRect.height = widget->allocation.height;
	gtk_widget_draw(widget, &updateRect);
	
	return;
}// End clearCartrigePictArea


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE void drawPixmaps(GtkWidget *widget, ST_PrinterStatus *pPrinterStatus)
// IN     : GtkWidget *widget : Pointer to widget of drawing area.
//          ST_PrinterStatus *pPrinterStatus : Information of printer status.
// OUT    : None.
// RETURN : None.
// 
PRIVATE void drawPixmaps(GtkWidget *widget, ST_PrinterStatus *pPrinterStatus)
{
/*** Parameters start ***/
	guint	totalWidth = 0;	// Total width of cartridge pixmaps.
	guint	xoffset = 0;	// X offset of pixmap.
	gint	index[2];		// Cartridge index.
	gint	i, j;			// Counter.
/*** Parameters end ***/
	
	freePixmaps();
	
	gpPixmap = gdk_pixmap_new(widget->window, widget->allocation.width, widget->allocation.height, -1);
	gdk_draw_rectangle(gpPixmap, widget->style->bg_gc[GTK_WIDGET_STATE(widget)], TRUE, 0, 0, widget->allocation.width, widget->allocation.height);
	
	for (i = 0; i < 2; i++) {
		if (pPrinterStatus->cartridgeClass[i].type >= ID_CARTRIDGE_TYPE_PHOTO ) {
			index[i] = pPrinterStatus->cartridgeClass[i].type - ID_CARTRIDGE_TYPE_PHOTO;
			totalWidth += gCartridgeWidth[index[i]];
			if (i == 0) {
				totalWidth += 6;
			}
		}
		else {
			index[i] = -1;
		}
	}
	
	gDW = (widget->allocation.width - totalWidth) >> 1;
	gDH = (widget->allocation.height - MAX_PIXMAP_HEIGHT) >> 1;
	
	for (i = 0; i < 2; i++) {
		if (index[i] != -1) {
			loadPixmaps(widget, &(pPrinterStatus->cartridgeClass[i]));
			
			for (j = 0; j < MAX_PIXMAP_NUM; j++) {
				if (gPatternTable[index[i]][j].pixmapID == -1) {
					break;
				}

				gdk_gc_set_clip_mask(widget->style->bg_gc[GTK_WIDGET_STATE(widget)], *gpMask[gPatternTable[index[i]][j].pixmapID]);
				
				gdk_gc_set_clip_origin(widget->style->bg_gc[GTK_WIDGET_STATE(widget)], gDW + xoffset, gDH + PIXMAP_Y_OFFSET);
				
				gdk_draw_pixmap(gpPixmap,
								widget->style->bg_gc[GTK_WIDGET_STATE(widget)],
								*gpInk[gPatternTable[index[i]][j].pixmapID],
								0,
								0,
								gDW + xoffset,
								gDH + PIXMAP_Y_OFFSET,
								widget->allocation.width,
								widget->allocation.height);

				gdk_gc_set_clip_mask(widget->style->bg_gc[GTK_WIDGET_STATE(widget)], NULL);
				
				if (gPatternTable[index[i]][j].pixmapID < ID_PIXMAP_EL) {
					drawInkLevelPixmap(widget, &(pPrinterStatus->cartridgeClass[i]), gPatternTable[index[i]][j].pixmapID, pPrinterStatus->cartridgeStatus[gPatternTable[index[i]][j].pixmapID].level, xoffset);
				}
				
				xoffset += gPatternTable[index[i]][j].width;
			}
			
			xoffset += 6;
		}
	}
	
	return;
}// End drawPixmaps


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE void drawInkLevelPixmap(GtkWidget *widget, ST_CartridgeClass *pCartridgeClass, ENUM_CartridgePixmapID colorID, ENUM_InkLevelID inkLevel, guint xoffset)
// IN     : GtkWidget *widget : Pointer to widget of drawing area.
//          ST_PrinterStatus *pPrinterStatus : Information of printer status.
//          ENUM_CartridgePixmapID colorID : ID of cartridge pixmap.
//          ENUM_InkLevelID inkLevel : ID of ink level.
//          guint xoffset : X offset.
// OUT    : None.
// RETURN : None.
// 
PRIVATE void drawInkLevelPixmap(GtkWidget *widget, ST_CartridgeClass *pCartridgeClass, ENUM_CartridgePixmapID colorID, ENUM_InkLevelID inkLevel, guint xoffset)
{
/*** Parameters start ***/
	GdkPixmap 	**pix = NULL;	// Pointer to pixmap.
	GdkBitmap 	**bmp = NULL;	// Pointer to mask.
/*** Parameters end ***/
	if (colorID == ID_PIXMAP_BB) {
		if (inkLevel == ID_INK_LEVEL_10) {
			pix = &gpInkLowBB;
			bmp = &gpMaskLowBB;
		}
		else if (inkLevel == ID_INK_LEVEL_0) {
			pix = &gpInkOutBB;
			bmp = &gpMaskOutBB;
		}
	}
	else if (colorID == ID_PIXMAP_B) {
		if (inkLevel == ID_INK_LEVEL_40) {
			pix = &gpInk24B1;
			bmp = &gpMask24B1;
		}
		else if (inkLevel == ID_INK_LEVEL_10) {
			pix = &gpInk24B2;
			bmp = &gpMask24B3;
		}
		else if (inkLevel == ID_INK_LEVEL_0) {
			pix = &gpInk24B3;
			bmp = &gpMask24B3;
		}
	}
	else if (colorID == ID_PIXMAP_C) {
		if (inkLevel == ID_INK_LEVEL_40) {
			pix = &gpInk24C1;
			bmp = &gpMask24C1;
		}
		else if (inkLevel == ID_INK_LEVEL_10) {
			pix = &gpInk24C2;
			bmp = &gpMask24C3;
		}
		else if (inkLevel == ID_INK_LEVEL_0) {
			pix = &gpInk24C3;
			bmp = &gpMask24C3;
		}
	}
	else if ((pCartridgeClass->type == ID_CARTRIDGE_TYPE_PHOTO 
			  || pCartridgeClass->type == ID_CARTRIDGE_TYPE_PHOTO2
			  || pCartridgeClass->type == ID_CARTRIDGE_TYPE_PHOTO_990i
			  || pCartridgeClass->type == ID_CARTRIDGE_TYPE_PHOTO_ip8600i)
			 && pCartridgeClass->exchange == ID_CARTRIDGE_EXCHANGE_NO) {
		if (inkLevel == ID_INK_LEVEL_70) {
			pix = &gpInkLow70;
			bmp = &gpMaskLow70;
		}
		else if (inkLevel == ID_INK_LEVEL_40) {
			pix = &gpInkLow40;
			bmp = &gpMaskLow40;
		}
		else if (inkLevel == ID_INK_LEVEL_10) {
			pix = &gpInkLow10;
			bmp = &gpMaskLow10;
		}
		else if (inkLevel == ID_INK_LEVEL_0) {
			pix = &gpInkOut;
			bmp = &gpMaskOut;
		}
	}
	else {
		if (inkLevel == ID_INK_LEVEL_10) {
			pix = &gpInkLow;
			bmp = &gpMaskLow;
		}
		else if (inkLevel == ID_INK_LEVEL_0) {
			pix = &gpInkOut;
			bmp = &gpMaskOut;
		}
	}
	
	if (pix != NULL && bmp != NULL) {
		gdk_gc_set_clip_mask(widget->style->bg_gc[GTK_WIDGET_STATE(widget)], *bmp);
		gdk_gc_set_clip_origin(widget->style->bg_gc[GTK_WIDGET_STATE(widget)], gDW + xoffset, gDH);
		
		gdk_draw_pixmap(gpPixmap,
						widget->style->bg_gc[GTK_WIDGET_STATE(widget)],
						*pix,
						0,
						0,
						gDW + xoffset,
						gDH,
						widget->allocation.width,
						widget->allocation.height);
		
		gdk_gc_set_clip_mask(widget->style->bg_gc[GTK_WIDGET_STATE(widget)], NULL);
	}
	
	return;
}// End drawInkLevelPixmap


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE gchar* checkFileExists(const gchar *pDirectory, const gchar *pFileName)
// IN     : const gchar *pDirectory : Directory name of XPM file exists.
//          const gchar *pFileName : XPM file name.
// OUT    : None.
// RETURN : Full pathname of XPM file. If NULL, XPM file not exist.
// 
PRIVATE gchar* checkFileExists(const gchar *pDirectory, const gchar *pFileName)
{
/*** Parameters start ***/
	gchar		*pFullFileName = NULL;	// Pointer to full file name.
	struct stat	fileInfo;				// File information.
	gint		retVal;					// Return value.
/*** Parameters start ***/
	
	pFullFileName = (gchar*)g_malloc(strlen(pDirectory) + 1 + strlen(pFileName) + 1);
	memset(pFullFileName, 0, (strlen(pDirectory) + 1 + strlen(pFileName) + 1));
	if (pFullFileName != NULL) {
		strncpy(pFullFileName, pDirectory, strlen(pDirectory));
		strcat(pFullFileName, "/");
		strncat(pFullFileName, pFileName, strlen(pFileName));
		
		retVal = stat(pFullFileName, &fileInfo);
		if (retVal != 0 || S_ISREG(fileInfo.st_mode) == 0) {
			g_free(pFullFileName);
			pFullFileName = NULL;
		}
	}
	
	return(pFullFileName);
}// End checkFileExists


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE gint loadPixmap(GdkPixmap **gdkpixmap, GtkWidget *widget, GdkBitmap **mask, const gchar *pDirectory, const gchar *pFileName)
// IN     : GtkWidget *widget : Pointer to widget of drawing area.
//          const gchar *pDirectory : Directory name of XPM file exists.
//          const gchar *pFileName : XPM file name.
// OUT    : GdkPixmap **gdkpixmap : Pointer to pixmap.
//          GdkBitmap **mask : Pointer to mask.
// RETURN : ID_ERR_NO_ERROR : No error.
//          ID_ERR_LOAD_PIXMAP_FAILED : Load pixmap failed.
// 
PRIVATE gint loadPixmap(GdkPixmap **gdkpixmap, GtkWidget *widget, GdkBitmap **mask, const gchar *pDirectory, const gchar *pFileName)
{
/*** Parameters start ***/
	gchar	*pFullFileName = NULL;		// Pointer to full file name.
	gint	retVal = ID_ERR_NO_ERROR;	// Return value.
/*** Parameters end ***/
	
	if (*gdkpixmap == NULL) {
		// Check file exists.
		pFullFileName = checkFileExists(pDirectory, pFileName);
		if (pFullFileName != NULL) {
			// Create pixmap.
			*gdkpixmap = gdk_pixmap_create_from_xpm(widget->window, &(*mask), NULL, pFullFileName);
			if (gdkpixmap == NULL) {
				retVal = ID_ERR_LOAD_PIXMAP_FAILED;
			}
			g_free(pFullFileName);
		}
		else {
			retVal = ID_ERR_LOAD_PIXMAP_FAILED;
		}
	}
	
	return(retVal);
}// End loadPixmap


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE void loadPixmaps(GtkWidget *widget, ST_CartridgeClass *pCartridge)
// IN     : GtkWidget *widget : Pointer to widget of drawing area.
//          ST_CartridgeClass *pCartridge : Information of cartridge classfication.
// OUT    : None.
// RETURN : None.
// 
PRIVATE void loadPixmaps(GtkWidget *widget, ST_CartridgeClass *pCartridge)
{
/*** Parameters start ***/
	ST_CartridgeXPMFileInfo	XPMFileInfo;	// XPM file info.
	gint					XPMFileID = -1;	// XPM file ID.
	gint					i = 0;			// Counter.
/*** Parameters end ***/
	
	if (pCartridge->type >= ID_CARTRIDGE_TYPE_PHOTO) {
		if (pCartridge->type == ID_CARTRIDGE_TYPE_COLOR_S300) {
			XPMFileID = (pCartridge->type - ID_CARTRIDGE_TYPE_PHOTO) * 2;
		}
		else if (pCartridge->type == ID_CARTRIDGE_TYPE_COLOR_S300_CIL) {
			XPMFileID = (pCartridge->type - ID_CARTRIDGE_TYPE_PHOTO) * 2 - 1;
		}
		else {
			XPMFileID = (pCartridge->type - ID_CARTRIDGE_TYPE_PHOTO) * 2;
			if (pCartridge->exchange == ID_CARTRIDGE_EXCHANGE_NO) {
				XPMFileID++;
			}
		}
	}
	
	if (XPMFileID > -1) {
		while (gCartridgeXPMFileSet[XPMFileID][i] != NULL && i < CARTRIDGE_XPM_SET_NUM) {
			memset(&XPMFileInfo, 0, sizeof(ST_CartridgeXPMFileInfo));
			getXPMFileInfo(gCartridgeXPMFileSet[XPMFileID][i], &XPMFileInfo);
			if (XPMFileInfo.pXPMFileName != NULL) {
				loadPixmap(XPMFileInfo.pPixmap, widget, XPMFileInfo.pMask, gPixmapDirectory, XPMFileInfo.pXPMFileName);
			}
			i++;
		}
	}
	
	return;
}// End loadPixmaps


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE void getXPMFileInfo(gchar *pXPMFileName, ST_CartridgeXPMFileInfo *pXPMFileInfo)
// IN     : gchar *pXPMFileName : XPM file name.
// OUT    : ST_CartridgeXPMFileInfo *pXPMFileInfo : XPM file information.
// RETURN : None.
// 
PRIVATE void getXPMFileInfo(gchar *pXPMFileName, ST_CartridgeXPMFileInfo *pXPMFileInfo)
{
/*** Parameters start ***/
	gint	tableSize = sizeof(gCartridgeXPMFileInfo) / sizeof(ST_CartridgeXPMFileInfo);	// Size of XPM file info table.
	gint	i = 0;		// Counter.
/*** Parameters start ***/
	
	if (pXPMFileInfo != NULL) {
		while (i < tableSize) {
			if (strcmp(gCartridgeXPMFileInfo[i].pXPMFileName, pXPMFileName) == 0) {
				memcpy(pXPMFileInfo, &(gCartridgeXPMFileInfo[i]), sizeof(ST_CartridgeXPMFileInfo));
				break;
			}
			i++;
		}
	}
	
	return;
}// End getXPMFileInfo


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE void freePixmap(GdkPixmap **gdkpixmap, GdkBitmap **mask)
// IN     : GdkPixmap **gdkpixmap : Pointer to pixmap.
//          GdkBitmap **mask : Pointer to mask.
// OUT    : None.
// RETURN : None.
// 
PRIVATE void freePixmap(GdkPixmap **gdkpixmap, GdkBitmap **mask)
{
	if (gdkpixmap != NULL) {
		if (*gdkpixmap != NULL) {
			gdk_pixmap_unref(*gdkpixmap);
			*gdkpixmap = NULL;
		}
	}
	if (mask != NULL) {
		if (*mask != NULL) {
			gdk_bitmap_unref(*mask);
			*mask = NULL;
		}
	}
}// End freePixmap


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC void freePixmaps(void)
// IN     : None.
// OUT    : None.
// RETURN : None.
// 
PUBLIC void freePixmaps(void)
{
/*** Parameters start ***/
	gint	tableSize = sizeof(gCartridgeXPMFileInfo) / sizeof(ST_CartridgeXPMFileInfo);	// Size of XPM file info table.
	gint	i = 0;		// Counter.
/*** Parameters end ***/
	
	freePixmap(&gpPixmap, NULL);
	
	while (i < tableSize) {
		freePixmap(gCartridgeXPMFileInfo[i].pPixmap, gCartridgeXPMFileInfo[i].pMask);
		i++;
	}
	
	return;
}// End freePixmaps
