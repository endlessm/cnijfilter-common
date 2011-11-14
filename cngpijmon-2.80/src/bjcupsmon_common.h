/*
 *  Canon Inkjet Printer Driver for Linux
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
 */

/*** Includes ***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include <gtk/gtk.h>

#ifdef 	USE_libglade
#include <glade/glade.h>
#endif

#include "bjcupsmon_err.h"

#if HAVE_CONFIG_H
#include	<config.h>
#endif	// HAVE_CONFIG_H

/*** Defines ***/
#define PUBLIC
#define PRIVATE		static

// Manufacturer name.
#define STR_MANUFACTURER_NAME		"Canon"

// Product name.
#define STR_PRODUCT_BJ			"bj"
#define STR_PRODUCT_PIXUS		"pixus"
#define STR_PRODUCT_Ixx			"i"
#define STR_PRODUCT_NAME		"Status Monitor"

#define STR_SERIES_NAME			"series"

// Module name.
#define STR_APPLICATION_NAME		"cngpijmon"

// Share directory name
//#define STR_SHARE_DIRECTORY_NAME	"/usr/local/share"
#define STR_SHARE_DIRECTORY_NAME	PACKAGE_DATA_DIR

// Header of status string.
#define STR_HEADER_STATUS_STRING	"STS:"

// Time interval for 
#define TIMEOUT_CALL_UPDATE_UI_FUNC	1000

// Num of cartridge color type.
#define CARTRIDGE_COLOR_TYPE_NUM	22	// Number of all color type +2(V2.4 rl) +1(v2.5)
//#define CARTRIDGE_COLOR_TYPE_NUM	20	// Number of all color type +2(V2.4 rl) +1(v2.5)
//#define CARTRIDGE_COLOR_TYPE_NUM	16	// Number of all color type +2(V2.4 rl) +1(v2.5)

// Max buffer size.
#define MAX_BUF_SIZE				1024

/** Widget name **/
// Window name.
#define STR_WINDOW_NAME_MAIN			"mainWindow"

// Widget name of main window.
//#define STR_MAIN_BUTTON_NAME_CONTINUE	"buttonMainContinue"
//#define STR_MAIN_BUTTON_NAME_CANCEL		"buttonMainCancel"
#define STR_MAIN_TEXT_STATUS			"textMainStatus"
//#define STR_MAIN_LABEL_CARTRIDGE_TYPE	"labelMainCartridgeType"
#define STR_MAIN_LABEL_LEVER_POSITION	"labelMainLeverPosition"
#define STR_MAIN_DRAW_CARTRIDGE			"drawMainCartridge"


/*** Enums ***/
// Cartridge type ID.
typedef enum {
	ID_CARTRIDGE_TYPE_NONE				= 0x20,	// Cartridge not installed
	ID_CARTRIDGE_TYPE_UNKNOWN			= 0x3f,	// Unknown
	ID_CARTRIDGE_TYPE_SCANNER			= 0x32,	// Scanner cartridge
	ID_CARTRIDGE_TYPE_DUMMY_SCANNER,			// Dummy scanner cartridge
	ID_CARTRIDGE_TYPE_UNSUPPORTED,				// Unsupported cartridge
	ID_CARTRIDGE_TYPE_PHOTO				= 0x41,	// F850 type
	ID_CARTRIDGE_TYPE_BLACK,					// F360 type (Black)
	ID_CARTRIDGE_TYPE_PHOTO_COLOR		= 0x44,	// F360 type (Photo)
	ID_CARTRIDGE_TYPE_COLOR_S600,				// S600 type
	ID_CARTRIDGE_TYPE_COLOR_S300,				// S300 type (CIL:OFF)
	ID_CARTRIDGE_TYPE_COLOR_S300_CIL,			// S300 type (CIL:ON)
	ID_CARTRIDGE_TYPE_PHOTO2			= 'H',	// 950i type
	ID_CARTRIDGE_TYPE_COLOR_860i		= 'I',	// 860i type
	ID_CARTRIDGE_TYPE_PHOTO_990i		= 'J',	// 990i type
	ID_CARTRIDGE_TYPE_PHOTO_ip8600i		= 'K',	// ip8600i type
	ID_CARTRIDGE_TYPE_BLACK_ip2200		= 'L',	// ip2200 type BLACK
	ID_CARTRIDGE_TYPE_COLOR_ip2200		= 'M',	// ip2200 type COLOR
	ID_CARTRIDGE_TYPE_BLACK_HC_ip2200	= 'N',	// ip2200 type BLACK(High Capa)
	ID_CARTRIDGE_TYPE_COLOR_HC_ip2200	= 'O',	// ip2200 type COLOR(High Capa)
	ID_CARTRIDGE_TYPE_COLOR_ip4200		= 'P',	// ip4200 type
	ID_CARTRIDGE_TYPE_PHOTO_ip6600d		= 'Q',	// ip6600 type
	ID_CARTRIDGE_TYPE_PHOTO_ip7500		= 'R',	// ip7500 type
	ID_CARTRIDGE_TYPE_COLOR_ip3300		= 'S',	// ip3300 type
	ID_CARTRIDGE_TYPE_COLOR_ipxxxx		= 'T',	// ipxxxx type
	ID_CARTRIDGE_TYPE_BLACK_MN_ip2200	= 'U',	// ip2200 type BLACK(Mini)
	ID_CARTRIDGE_TYPE_COLOR_MN_ip2200	= 'V',	// ip2200 type COLOR(Mini)
	ID_CARTRIDGE_TYPE_COLOR_ip90		= 'W',	// ip90 type (CIL:OFF)
	ID_CARTRIDGE_TYPE_COLOR_ip90_CIL	= 'X',	// ip90 type (CIL:ON)
	
	ID_CARTRIDGE_TYPE_INVALID		= 0x2a,	// Invalid value
} ENUM_CartridgeTypeID;

// Cartridge exchange ID.
typedef enum {
	ID_CARTRIDGE_EXCHANGE_YES		= 0x45,	// Cartridge exchange possible (Background = Green)
	ID_CARTRIDGE_EXCHANGE_NO,				// Cartridge exchange inpossible (Background = Black)
	ID_CARTRIDGE_EXCHANGE_INVALID	= 0x2a,	// Invalid value
} ENUM_CartridgeExchangeID;

// Ink level ID.
typedef enum {
	ID_INK_LEVEL_UNSETTNK = -3,		// Ink Tank Unset
	ID_INK_LEVEL_UK	  = -2,		// Ink remain unkown
	ID_INK_LEVEL_NONE = -1,		// Ink is not contained in this cartridge
	ID_INK_LEVEL_0    = 0,		// Ink 0%
	ID_INK_LEVEL_10   = 10,		// Ink 10%
	ID_INK_LEVEL_40   = 40,		// Ink 40%
	ID_INK_LEVEL_70   = 70,		// Ink 70%
	ID_INK_LEVEL_100  = 100,	// Ink 100%
} ENUM_InkLevelID;

// Ink status ID.
typedef enum {
	ID_INK_STS_NONE		= -1,	// Ink is not contained in this cartridge
	ID_INK_STS_FULL		= 0x20,	// Full				' '
	ID_INK_STS_LOW		= 0x4c,	// Low				'L'
	ID_INK_STS_OUT		= 0x4f,	// Out				'O'
	ID_INK_STS_UNKNOWN	= 0x3f,	// Unknown			'?'
	ID_INK_STS_INVALID	= 0x2a,	// Invalid value	'*'

	ID_INK_STS_LOW2		= 0x57,	// Low				'W'
	ID_INK_STS_OUT2		= 0x49,	// Out2				'I'
	ID_INK_STS_RFL		= 0x52,	// RFL				'R'
	ID_INK_STS_MUL		= 0x4d,	// MUL				'M'
	ID_INK_STS_REG		= 0x45,	// REG				'E'
	ID_INK_STS_NO		= 0x4e,	// NO				'N'
	ID_INK_STS_POSN		= 0x50,	// POSN				'P'
	ID_INK_STS_EMPTY	= 0x59,	// Empty			'Y'
	ID_INK_STS_IUK		= 0x72,	// IUK				'r'
	ID_INK_STS_LLOW		= 0x6c,	// LLow				'l'

} ENUM_InkStatusID;

// Paper thickness lever position ID.
typedef enum {
	ID_LEVER_POSITION_UP		= 0x55,	// Up
	ID_LEVER_POSITION_DOWN		= 0x44,	// Down
	ID_LEVER_POSITION_LEFT		= 0x4c,	// Left
	ID_LEVER_POSITION_RIGHT		= 0x52,	// Right
	ID_LEVER_POSITION_INVALID	= 0x2a,	// Invalid value
	ID_LEVER_POSITION_NONE		= 0x20,	// Invalid value
} ENUM_LeverPositionID;

// HRI
#define	ID_HRI_JPN	'J'
#define	ID_HRI_OTH	'O'

// Status message ID.
typedef enum {
	ID_STS_MESSAGE_SC_USEDTANK_FULL,			// Used tank full. (Service call)
	ID_STS_MESSAGE_SC_USEDTANK_FULLJP,			// Used tank full. (Service call) for Ver.2.70
	ID_STS_MESSAGE_SC_SERVICE_ERROR_PRE,		// Service error pre message. (Service call)
	ID_STS_MESSAGE_SC_SERVICE_ERROR_AFTER,		// Service error after message. (Service call)
	ID_STS_MESSAGE_OC_PAPER_OUT1,				// Paper out. (Operator call)	v2.5
	ID_STS_MESSAGE_OC_PAPER_OUT,				// Paper out. (Operator call)
	ID_STS_MESSAGE_OC_PAPER_OUT21,				// Paper out. (Operator call)	v2.5
	ID_STS_MESSAGE_OC_PAPER_OUT22,				// Paper out. (Operator call)	v2.5
	ID_STS_MESSAGE_OC_PAPER_OUT42,				// Paper out. (Operator call)	v2.5
	ID_STS_MESSAGE_OC_PAPER_OUT3,				// Paper out. (Operator call)	v2.5
	ID_STS_MESSAGE_OC_PAPER_OUT33,				// Paper out. (Operator call)	v2.7
	ID_STS_MESSAGE_OC_PAPER_OUT_START,			// Paper out. (Operator call)	v2.7
	ID_STS_MESSAGE_OC_PAPER_JAM,				// Paper jam. (Operator call)
	ID_STS_MESSAGE_OC_PAPER_JAM1,				// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM2,				// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM1_2nd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM1_3rd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM2_3rd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM2_START,			// Paper jam. (Operator call)	v2.7
	ID_STS_MESSAGE_OC_PAPER_JAM03,				// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM03_2nd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM03_2ndFF,		// Paper jam. (Operator call)	v2.7
	ID_STS_MESSAGE_OC_PAPER_JAM04,				// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM04_2nd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM05,				// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM05_2nd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM06,				// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM07,				// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_HEAD_ERROR,				// Head error. (Operator call)
	ID_STS_MESSAGE_OC_HEAD_ERROR2,				// Head error. (Operator call)
	ID_STS_MESSAGE_OC_HEAD_ERROR_START,			// Head error. (Operator call)
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST,			// Used tank almost full. (Operator call)
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST2,			// Used tank almost full. (Operator call)
	ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP,		// Used tank almost full. (Operator call) for Ver.2.70
	ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP2,		// Used tank almost full. (Operator call) for Ver.2.70
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST_START,	// Used tank almost full. (Operator call) for Ver.2.70
	ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP_START,	// Used tank almost full. (Operator call) for Ver.2.70
	ID_STS_MESSAGE_OC_INKOUT,					// Ink out. (Operator call)
	ID_STS_MESSAGE_OC_COVER_OPEN,				// Cover open. (Operator call)
	ID_STS_MESSAGE_OC_COVER_OPEN2,				// Cover open. (Operator call)	v2.5
	ID_STS_MESSAGE_OC_COVER_CLOSE,				// Cover close. (Operator call)	v2.5 
	ID_STS_MESSAGE_OC_COVER_CLOSE2,				// Cover close. (Operator call)	v2.5 
	ID_STS_MESSAGE_OC_OTHER,					// Another operator call. (Operator call)
	ID_STS_MESSAGE_BUSY_CLEANING,				// Cleaning. (Busy status)
	ID_STS_MESSAGE_BUSY_CARTRIDGE_CHANGE,		// Cartridge replacement. (Busy status) Dispo
	ID_STS_MESSAGE_BUSY_CARTRIDGE_CHANGE2,		// Cartridge replacement. (Busy status) 
	ID_STS_MESSAGE_BUSY_TEST_PRINTING,			// Test printing. (Busy status)
	ID_STS_MESSAGE_BUSY_PRINTER_USED,			// Printer using nother interface. (Busy status)
	ID_STS_MESSAGE_BUSY_TANK_CHANGE,			// Tank Change. (Busy status)
	ID_STS_MESSAGE_CARTRIDGE_NONE,				// Cartridge not installed.
	ID_STS_MESSAGE_BASE_PRINTING,				// Printing.
	ID_STS_MESSAGE_BASE_ONLINE,					// Printer is online.
	ID_STS_MESSAGE_WAR_INKLOW_PRE,				// Ink low pre message. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_40_PRE,			// Ink low pre message. (Warning) Dispo
	ID_STS_MESSAGE_WAR_INKLOW_BLACK,			// Black ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_PHOTO_BLACK,		// Photo black ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_PHOTO_CYAN,		// Photo cyan ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_PHOTO_MAGENTA,	// Photo magenta ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_CYAN,				// Cyan ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_MAGENTA,			// Magenta ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_YELLOW,			// Yellow ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_RED,				// Red ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_GREEN,			// Green ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_BLACK3e,			// Black [3e] ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_BLACK15,			// Black [15] ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_COLOR16,			// Color [16] ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_BLACKxx,			// Black [xx] ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_COLORxx,			// Color [xx] ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_BLACKyy,			// Black [yy] ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_COLORyy,			// Color [yy] ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_BLACK24,			// Black [24] ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_COLOR24,			// Color [24] ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_AFTER,			// Ink low after message. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_BLACK40,			// black ink low level 3. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_COLOR41,			// color ink low level 3. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_BLACK8,			// Black ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_PHOTO_BLACK5,		// Photo black ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_PHOTO_CYAN8,		// Photo cyan ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_PHOTO_MAGENTA8,	// Photo magenta ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_CYAN8,			// Cyan ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_MAGENTA8,			// Magenta ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_YELLOW8,			// Yellow ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_40_AFTER,			// ink low level 3 after message. (Warning)
	ID_STS_MESSAGE_WAR_REG_NO_ADJUSTMENT,		// No adjustment message. (HCF)
	ID_STS_MESSAGE_CIL_OFF,						// Check ink level off.
	ID_STS_MESSAGE_INVALID,						// Invalid status recieved.
	ID_STS_MESSAGE_OC_CDR_GUIDE,				// CD-R Tray Guide On.
	ID_STS_MESSAGE_OC_CDR_GUIDE_2nd,			// CD-R Tray Guide On.
	ID_STS_MESSAGE_OC_CDR_GUIDE_3rd,			// CD-R Tray Guide On.
	ID_STS_MESSAGE_OC_CDR_GUIDE2,				// CD-R Tray Guide On.
	ID_STS_MESSAGE_OC_CDR_GUIDE2_3rd,			// CD-R Tray Guide On.
	ID_STS_MESSAGE_CDR_GUIDE_PRINT,				// CD-R Tray Guide On.	v2.5
	ID_STS_MESSAGE_CDR_GUIDE_PRINT_2nd,			// CD-R Tray Guide On.	v2.5
	ID_STS_MESSAGE_CDR_GUIDE_PRINT_3rd,			// CD-R Tray Guide On.	v2.5
	ID_STS_MESSAGE_CDR_GUIDE_PRINT2,			// CD-R Tray Guide On.	v2.5
	ID_STS_MESSAGE_CDR_GUIDE_PRINT2_3rd,		// CD-R Tray Guide On.	v2.5
	ID_STS_MESSAGE_OC_INKTANK_NOTPROPERLY,		// Ink tank nothing. iP90
	ID_STS_MESSAGE_OC_CARTRIDGE_NOTPROPERLY,	// Ink cartridge not properly. i250/i255
	ID_STS_MESSAGE_OC_USBDEVICE,				// USB Device 560i 860i 990i
	ID_STS_MESSAGE_OC_HEADALIGNMENT,			// Head Alignment 860i 990i
	ID_STS_MESSAGE_OC_HEADALIGNMENT2,			// Head Alignment 860i 990i
	ID_STS_MESSAGE_OC_HARDWAREERROR_TANK,		// Hardware error (ink tank)
	ID_STS_MESSAGE_OC_PLURALERROR_TANK,			// Plural error (ink tank) 1st messeage.
	ID_STS_MESSAGE_OC_DIFFERENT_REGION_TANK,	// No Recognize error (ink cartridge) 1st messeage.
	ID_STS_MESSAGE_OC_POSITION_MISMACH_TANK,	// Position Mismatch error (ink tank) 1st messeage.
	ID_STS_MESSAGE_OC_UNINSTALLATION_TANK,		// Uninstallation (ink tank) 1st messeage.
	ID_STS_MESSAGE_OC_INKOUT_TANK,				// Ink Out error (ink tank) 1st messeage.
	ID_STS_MESSAGE_OC_INKOUT_TANK2,				// Ink Out error (ink tank) 1st messeage.
	ID_STS_MESSAGE_OC_INKOUT06_TANK,			// Ink Out06 error (ink tank) 2th messeage.
	ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP,		// Ink Out06 error (ink tank) 2th messeage.
	ID_STS_MESSAGE_OC_REFILL,					// Rifel error 1st messeage.
	ID_STS_MESSAGE_OC_REFILL2,					// Rifel error 1st messeage.
	ID_STS_MESSAGE_OC_TANK_NO_BK,				// Bk Tank error 1st messeage.(for iP90)
	ID_STS_MESSAGE_OC_TANK_NO_CL,				// Cl Tank error 1st messeage.(for iP90)
	ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART,		// No Recognize error (ink cartridge) 1st messeage.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN1,			// Remain unknown error 1st messeage.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2,			// Remain unknown error 1st messeage.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN3,			// Remain unknown error 1st messeage.(for iP90)
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN3_3rd,		// Remain unknown error 3rd messeage.(for iP90)
	ID_STS_MESSAGE_OC_INKOUT_CART,				// Ink Out error (ink cartridge) 1st messeage.
	ID_STS_MESSAGE_OC_INKOUT_CART_MFP,			// Ink Out error (ink cartridge) 1st messeage for MFP.
	ID_STS_MESSAGE_OC_INKOUT_CART_START,		// Ink Out error (ink cartridge) 1st messeage for MFP.(START Button)
	ID_STS_MESSAGE_OC_BLACK7e,					// Black [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_PHOTO_BLACK9,				// Photo black [9] ink error. (Operator call)
	ID_STS_MESSAGE_OC_PHOTO_CYAN7e,				// Photo Cyan [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_PHOTO_MAGENTA7e,			// Photo Magenta [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_CYAN7e,					// Cyan [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_MAGENTA7e,				// Magenta [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_YELLOW7e,					// Yellow [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACK,					// Balck ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLOR,					// Color ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACK30,					// Balck [30] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACK830,					// Balck [830] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACK37,					// Balck [37] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACK40,					// Balck [40] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACK50,					// Balck [50] ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLOR31,					// Color [31] ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLOR831,					// Color [831] ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLOR38,					// Color [38] ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLOR41,					// Color [41] ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLOR51,					// Color [51] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACK70,					// Balck [70] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACK90,					// Balck [90] ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLOR71,					// Color [71] ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLOR91,					// Color [91] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACK8,					// Black [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_PHOTO_BLACK5,				// Photo black [9] ink error. (Operator call)
	ID_STS_MESSAGE_OC_PHOTO_CYAN8,				// Photo Cyan [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_PHOTO_MAGENTA8,			// Photo Magenta [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_CYAN8,					// Cyan [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_MAGENTA8,					// Magenta [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_YELLOW8,					// Yellow [7e] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACKxx,					// Black [xx] ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLORxx,					// Color [xx] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACKyy,					// Black [yy] ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLORyy,					// Color [yy] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACK15,					// Black [15] ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLOR16,					// Color [16] ink error. (Operator call)
	ID_STS_MESSAGE_OC_BLACKTANK,				// Black Tank ink error. (Operator call)
	ID_STS_MESSAGE_OC_COLORTANK,				// Color Tank ink error. (Operator call)
	ID_STS_MESSAGE_OC_PLURALERROR_TANK_3rd,	 	// Plural error (ink tank) 3rd message.
	ID_STS_MESSAGE_OC_DIFFERENT_REGION_TANK_3rd,// No Recognize error (ink cartridge) 3rd message.
	ID_STS_MESSAGE_OC_UNINSTALLATION_TANK_3rd,	// Uninstallation (ink tank) 3rd message.
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_1st,		// Ink Out error (ink tank) 2nd messeage.
	ID_STS_MESSAGE_OC_INKEMPTY0602_TANK_1st,	// Ink Out error (ink tank) 2nd messeage.
	ID_STS_MESSAGE_OC_REFILL_3rd,				// Rifel error 3rd messeage.
	ID_STS_MESSAGE_OC_REFILL2_3rd,				// Rifel error 3rd messeage.
	ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART_3rd,	// No Recognize error (ink cartridge) 3rd messeage.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN1_3rd,		// Remain unknown error 3rd messeage.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd,		// Remain unknown error 3rd messeage.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_MFP,	// Remain unknown error 3rd messeage for MFP.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START,	// Remain unknown error 3rd messeage for MFP.(START Button)
	ID_STS_MESSAGE_OC_INKOUT_CART_3rd,			// Ink Out error (ink cartridge) 3rd messeage.
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd,		// Ink Empty error 3rd messeage.
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP,	// Ink Empty error 3rd messeage.
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE,	// Cartridge Empty error 3rd messeage.
/* Ver.2.80 for B-53 Stop/Reset */
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET,	// Cartridge Empty error 3rd messeage.
	ID_STS_MESSAGE_OC_INKEMPTY0602_TANK_3rd,	// Ink Empty error 3rd messeage.
	ID_STS_MESSAGE_INKSTATUS_OFF,				// Ink Check OFF.
	ID_STS_MESSAGE_OC_BATTERY_OUT,				// Battery Out error
	ID_STS_MESSAGE_SC_BATTERY_ERROR,			// Battery error
	ID_STS_MESSAGE_WAR_BATTERY_LOW,				// Battery low
	ID_STS_MESSAGE_JOB_JOBCANCEL_RESUME,		// Job Cancel
	ID_STS_MESSAGE_JOB_JOBCANCEL_STOPRESET,		// Job Cancel
	ID_STS_MESSAGE_JOB_PREPARE,					// Prepare for Printing
	ID_STS_MESSAGE_JOB_DELAY,					// Print Delay 
	ID_STS_MESSAGE_BUSY_PRINTER,				// Printer Busy 
	ID_STS_MESSAGE_OC_PAPER_OUT21RT,			// Paper out. (Operator call)	v2.8
	ID_STS_MESSAGE_OC_PAPER_OUT42FT,			// Paper out. (Operator call)	v2.8
	ID_STS_MESSAGE_OC_PAPER_JAM03_2ndFT,		// Paper jam. (Operator call)	v2.8
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING,	// Remain unknown error 3rd messeage for 07-MFP.(START Button)

		
	ID_STS_MESSAGE_NON = -1,
	ID_STS_MESSAGE_COLOR,
	ID_STS_MESSAGE_COLOR_CARTRIDGE,
	ID_STS_MESSAGE_COLOR_TYPE,
} ENUM_STSMessageID;


// Printer Interface 
#define ID_DEV_1284	1
#define ID_DEV_USB	2
#define ID_DEV_1394	3


// Other message ID.
typedef enum {
	ID_OTHER_MESSAGE_NONE = -1,				// None.
	ID_OTHER_MESSAGE_PRINTER_IS_READY = 0,	// Printer is ready.
	ID_OTHER_MESSAGE_UNKNOWN_PRINTER,		// Unknown printer.
	ID_OTHER_MESSAGE_SPOOLER_ERROR,			// Spooler error.
	ID_OTHER_MESSAGE_FATAL_ERROR,			// Fatal error.
	ID_OTHER_MESSAGE_ARGUMENT_ERROR,		// Argument error.
} ENUM_OtherMessageID;


/*** Structures ***/
// for cartridge classification.
typedef struct {
	ENUM_CartridgeTypeID		type;		// Type
	ENUM_CartridgeExchangeID	exchange;	// Exchange
} ST_CartridgeClass;

// for ink status
typedef struct {
	ENUM_InkLevelID		level;		// Ink level
	ENUM_InkStatusID	status;		// Ink status
} ST_InkStatus;

// for printer status.
typedef struct {
	ST_CartridgeClass		cartridgeClass[2];		// Cartridge classification
	ENUM_LeverPositionID	leverPosition;			// Lever position
	gint					destination;			// for Ver.2.70 Destination
	gint				messageNum;					// Num of message
	ENUM_STSMessageID		*pMessageID;			// Message ID
	gchar				serviceCallID[8];			// Service call ID
	ST_InkStatus			cartridgeStatus[CARTRIDGE_COLOR_TYPE_NUM];	// Cartridge status.
	gint				printInterface;					// printer interface 1284/usb/1394
} ST_PrinterStatus;

// for error classification table.
typedef struct {
	gint				errorCode;	// Error code
	ENUM_ErrorLevelID	errorLevel;	// Error level
	ENUM_OtherMessageID	messageID;	// Message ID
} ST_ErrorCodeTbl;
