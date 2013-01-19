/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2012
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

/*** Defines ***/
// Cartridge pixmap directory name.
#define STR_PIXMAP_DIRECTORY_NAME	"/pixmaps"

// Pixmap file name.
#define STR_PIXMAP_FILE_NAME_GREEN_EL			"Ink_el.xpm"		// Edge left (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_ER			"Ink_er.xpm"		// Edge right (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_BK			"Ink_bk.xpm"		// Black (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_PB			"Ink_pb.xpm"		// Photo Black (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_SB			"Ink_pb.xpm"		// Senryo Black (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_BB			"Ink_bb.xpm"		// Big Black (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_PC			"Ink_pc.xpm"		// Photo Cyan (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_PM			"Ink_pm.xpm"		// Photo Magenta (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_CY			"Ink_cy.xpm"		// Cyan (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_MA			"Ink_ma.xpm"		// Magenta (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_YE			"Ink_ye.xpm"		// Yellow (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_RE			"Ink_re.xpm"		// Red (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_GR			"Ink_gr.xpm"		// Green (Background = Green)
#define STR_PIXMAP_FILE_NAME_GREEN_SP			"Ink_sp.xpm"		// Space (Background = Green)
#define STR_PIXMAP_FILE_NAME_BLACK_EL			"Inkg_el.xpm"		// Edge left (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_ER			"Inkg_er.xpm"		// Edge right (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_BK			"Inkg_bk.xpm"		// Black (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_PB			"Inkg_pb.xpm"		// Photo Black (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_SB			"Inkg_pb.xpm"		// Senryo Black (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_BB			"Inkg_bb.xpm"		// Big Black (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_PC			"Inkg_pc.xpm"		// Photo Cyan (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_PM			"Inkg_pm.xpm"		// Photo Magenta (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_CY			"Inkg_cy.xpm"		// Cyan (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_MA			"Inkg_ma.xpm"		// Magenta (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_YE			"Inkg_ye.xpm"		// Yellow (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_RE			"Inkg_re.xpm"		// Red (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_GR			"Inkg_gr.xpm"		// Green (Background = Black)
#define STR_PIXMAP_FILE_NAME_BLACK_SP			"Inkg_sp.xpm"		// Space (Background = Black)
#define STR_PIXMAP_FILE_NAME_24B				"Ink_24b.xpm"		// S300 Black (CIL:OFF)
#define STR_PIXMAP_FILE_NAME_24C				"Ink_24c.xpm"		// S300 Color (CIL:OFF)
#define STR_PIXMAP_FILE_NAME_24BF				"Ink_24bf.xpm"		// S300 Black (CIL:ON)
#define STR_PIXMAP_FILE_NAME_24CF				"Ink_24cf.xpm"		// S300 Color (CIL:ON)

#define STR_PIXMAP_FILE_NAME_GREEN_SB_26		"Ink26sb.xpm"
#define STR_PIXMAP_FILE_NAME_GREEN_BB_26		"Ink26bb.xpm"
#define STR_PIXMAP_FILE_NAME_GREEN_CY_26		"Ink26cy.xpm"
#define STR_PIXMAP_FILE_NAME_GREEN_MA_26		"Ink26ma.xpm"
#define STR_PIXMAP_FILE_NAME_GREEN_YE_26		"Ink26ye.xpm"
#define STR_PIXMAP_FILE_NAME_GREEN_PC_26		"Ink26pc.xpm"
#define STR_PIXMAP_FILE_NAME_GREEN_PM_26		"Ink26pm.xpm"
#define STR_PIXMAP_FILE_NAME_GREEN_C_26			"Ink26c.xpm"
#define STR_PIXMAP_FILE_NAME_GREEN_B_26			"Ink26b.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_SB_26		"Inkg26sb.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_BB_26		"Inkg26bb.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_CY_26		"Inkg26cy.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_GY_26		"Inkg26gy.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_MA_26		"Inkg26ma.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_YE_26		"Inkg26ye.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_PC_26		"Inkg26pc.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_PM_26		"Inkg26pm.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_C_26			"Inkg26c.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_B_26			"Inkg26b.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_C_27			"Inkg27c.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_INK15		"Ink_15.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_INK16		"Ink_16.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_INK15UNDER	"Ink_15_Under.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_INK16UNDER	"Ink_16_Under.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_UNSET_INK15	"Ink_15_Unset.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_UNSET_INK16	"Ink_16_Unset.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_NTDIS_INK15	"Ink_15_Notdisplay.xpm"
#define STR_PIXMAP_FILE_NAME_BLACK_NTDIS_INK16	"Ink_16_Notdisplay.xpm"

#define STR_PIXMAP_FILE_NAME_LOW				"Ink_low.xpm"		// Ink low (Normal)
#define STR_PIXMAP_FILE_NAME_LOW_BB				"Ink_low_bb.xpm"	// Ink low (for Big Black)
#define STR_PIXMAP_FILE_NAME_OUT				"Ink_out.xpm"		// Ink out (Normal)
#define STR_PIXMAP_FILE_NAME_OUT_BB				"Ink_out_bb.xpm"	// Ink out (for Big Black)
#define STR_PIXMAP_FILE_NAME_LOW_10				"Ink_low010.xpm"	// Ink 10%
#define STR_PIXMAP_FILE_NAME_LOW_40				"Ink_low040.xpm"	// Ink 40%
#define STR_PIXMAP_FILE_NAME_LOW_70				"Ink_low070.xpm"	// Ink 70%
#define STR_PIXMAP_FILE_NAME_24B1				"Ink_24b1.xpm"		// S300 Black ink low level1
#define STR_PIXMAP_FILE_NAME_24B2				"Ink_24b2.xpm"		// S300 Black ink low level2
#define STR_PIXMAP_FILE_NAME_24B3				"Ink_24b3.xpm"		// S300 Black ink low level3
#define STR_PIXMAP_FILE_NAME_24C1				"Ink_24c1.xpm"		// S300 Color ink low level1
#define STR_PIXMAP_FILE_NAME_24C2				"Ink_24c2.xpm"		// S300 Color ink low level2
#define STR_PIXMAP_FILE_NAME_24C3				"Ink_24c3.xpm"		// S300 Color ink low level3

#define STR_PIXMAP_FILE_NAME_LVL_00				"Ink_Level_00.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_10				"Ink_Level_10.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_40				"Ink_Level_40.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_70				"Ink_Level_70.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_UK				"Ink_Level_uk.xpm"

#define STR_PIXMAP_FILE_NAME_LVL_00_WIDE		"Inkw_Level_00.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_10_WIDE		"Inkw_Level_10.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_40_WIDE		"Inkw_Level_40.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_70_WIDE		"Inkw_Level_70.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_UK_WIDE		"Inkw_Level_uk.xpm"

#define STR_PIXMAP_FILE_NAME_LVL_00_D			"Inkd_Level_00.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_10_D			"Inkd_Level_10.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_40_D			"Inkd_Level_40.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_70_D			"Inkd_Level_70.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_UK_D			"Inkd_Level_uk.xpm"

#define STR_PIXMAP_FILE_NAME_LVL_00_D2			"Inkd2_Level_00.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_10_D2			"Inkd2_Level_10.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_40_D2			"Inkd2_Level_40.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_70_D2			"Inkd2_Level_70.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_UK_D2			"Inkd2_Level_uk.xpm"

#define STR_PIXMAP_FILE_NAME_LVL_40_15			"Ink_15_Level40.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_40_16			"Ink_16_Level40.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_LOW_15			"Ink_15_Low.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_LOW_16			"Ink_16_Low.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_UK_15			"Ink_15_Unknown.xpm"
#define STR_PIXMAP_FILE_NAME_LVL_UK_16			"Ink_16_Unknown.xpm"


#define STR_PIXMAP_FILE_NAME_ICON_LOW			"Icon_Low.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_OUT			"Icon_Out.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_REFILL		"Icon_Refill.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_LOW_WIDE		"Iconw_Low.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_OUT_WIDE		"Iconw_Out.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_REFILL_WIDE	"Iconw_Refill.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_LOW_D			"Icond_Low.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_OUT_D			"Icond_Out.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_LOW_D2		"Icond2_Low.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_OUT_D2		"Icond2_Out.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_REFILL_D		"Icond_Refill.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_LOW_15		"Icon_15_Low.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_LOW_16		"Icon_16_Low.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_UNKNOWN_15	"Icon_15_Unknown.xpm"
#define STR_PIXMAP_FILE_NAME_ICON_UNKNOWN_16	"Icon_16_Unknown.xpm"


// Num of cartridge type.
#define CARTRIGE_TYPE_NUM	31		// add MG5400 and MG6300
/* #define CARTRIGE_TYPE_NUM	29		// add dummy and MG4100 BK Extra */
//#define CARTRIGE_TYPE_NUM	27		// add MG8100
//#define CARTRIGE_TYPE_NUM	26		// add iP4600 and iP3600
//#define CARTRIGE_TYPE_NUM	24		// add ip3300 and iP100 and Mini*2 and iP90*2

// Num of cartridge class.
#define CARTRIGE_CLASS_NUM	64		// add (MG5400 + MG6300) *2
/* #define CARTRIGE_CLASS_NUM	60		// add (dummy + MG4100 BK Extra) *2 */
//#define CARTRIGE_CLASS_NUM	56		// add (MG8100) *2
//#define CARTRIGE_CLASS_NUM	54		// add (iP4600 + iP3600) *2
//#define CARTRIGE_CLASS_NUM	50		// add (ip3300 + iP100 + Mini*2+ ip90*2) *2

// Num of cartridge pixmap.
#define CARTRIDGE_PIXMAP_NUM	20	// +1(Gray)+2(Red+SenryoB)+1(Green)+Color(iP100)+Color/Black(iP90)
//#define CARTRIDGE_PIXMAP_NUM	19	// +2(Red+SenryoB)+1(Green)+Color(iP100)+Color/Black(iP90)

// Num of cartridge XPM set.
#define CARTRIDGE_XPM_SET_NUM	25	// +2(Red+yobi)+1(Green)

// Max height pixmap drawing area.
#define MAX_PIXMAP_HEIGHT	66

// Max num of pixmap.
#define MAX_PIXMAP_NUM		23		// add 2(Red+Green)  // add ip4200(+2:ip7500 PC&PM)

// Y offset of pixmap.
#define PIXMAP_Y_OFFSET		18


/*** Enums ***/
// Pixmap ID for cartridge.(CARTRIDGE_PIXMAP_NUM)
typedef enum {
	ID_PIXMAP_BK,	// Black
	ID_PIXMAP_PB,	// Photo Black
	ID_PIXMAP_SB,	// Senryo Black
	ID_PIXMAP_BB,	// Big Black
	ID_PIXMAP_PC,	// Photo Cyan
	ID_PIXMAP_PM,	// Photo Magenta
	ID_PIXMAP_CY,	// Cyan
	ID_PIXMAP_MA,	// Magenta
	ID_PIXMAP_YE,	// Yellow
	ID_PIXMAP_RE,	// Red (990i)
	ID_PIXMAP_GR,	// Green (ip8600i)
	ID_PIXMAP_B,	// Black (S300)
	ID_PIXMAP_C,	// Color (S300)
	ID_PIXMAP_C2,	// Color (iP100)
	ID_PIXMAP_B0,	// Black (iP90)
	ID_PIXMAP_C0,	// Color (iP90)
	ID_PIXMAP_GY,	// Gray
	ID_PIXMAP_EL,	// Edge Left
	ID_PIXMAP_ER,	// Edge Right
	ID_PIXMAP_SP,	// Space
} ENUM_CartridgePixmapID;


/*** Structures ***/
// for cartridge pattern.
typedef struct {
	ENUM_CartridgePixmapID	pixmapID;	// Pixmap ID
	gshort					width;		// Width of pixmap.
} ST_CartridgePattern;

// for cartridge XPM file info.
typedef struct {
	gchar		*pXPMFileName;		// XPM file name.
	GdkPixmap	**pPixmap;			// Pointer to pixmap.
	GdkBitmap	**pMask;			// Pointer to mask.
} ST_CartridgeXPMFileInfo;


/*** Static function prototypes ***/
PRIVATE void drawPixmaps(GtkWidget*, ST_PrinterStatus*);
PRIVATE void drawInkLevelPixmap(GtkWidget*, ST_CartridgeClass*, ENUM_CartridgePixmapID, ENUM_InkLevelID, guint, guint);
PRIVATE void drawIconPixmap(GtkWidget *, ST_CartridgeClass *, ENUM_CartridgePixmapID, ENUM_InkStatusID, ENUM_STSMessageID *, gint, ST_PrinterStatus*, guint , guint );
PRIVATE void drawBottomPixmap(GtkWidget *, ST_CartridgeClass *, ENUM_CartridgePixmapID, ENUM_InkLevelID, guint , guint );
PRIVATE gchar* checkFileExists(const gchar*, const gchar*);
PRIVATE gint loadPixmap(GdkPixmap**, GtkWidget*, GdkBitmap**, const gchar*, const gchar*);
PRIVATE void loadPixmaps(GtkWidget*, ST_CartridgeClass*);
PRIVATE void getXPMFileInfo(gchar*, ST_CartridgeXPMFileInfo*);
PRIVATE void freePixmap(GdkPixmap**, GdkBitmap**);

