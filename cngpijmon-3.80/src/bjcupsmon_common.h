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

#define STR_USB_NAME			"USB"

// Module name.
#define STR_APPLICATION_NAME		"cngpijmon"

// Share directory name
//#define STR_SHARE_DIRECTORY_NAME	"/usr/local/share"
#define STR_SHARE_DIRECTORY_NAME	PACKAGE_DATA_DIR

// Header of status string.
#define STR_HEADER_STATUS_STRING	"STS:"

// Time interval for 
#define TIMEOUT_CALL_UPDATE_UI_FUNC	1000

/* for Network Ver.3.10 */
#define CANON_USB_BACKEND_CNIJ_USB	1
#define CANON_BJNP_BACKEND_CNIJ_NET	2
#define USB_BACKEND_NORMAL	3

/* for Network Ver.3.10 */
#define NETWORK_OTHER_USE		1

// Num of cartridge color type.
#define CARTRIDGE_COLOR_TYPE_NUM	27	// add MG5400 & MG6300
/* #define CARTRIDGE_COLOR_TYPE_NUM	25	// add MG8100 */
//#define CARTRIDGE_COLOR_TYPE_NUM	24	// add iP4600 & iP3600
//#define CARTRIDGE_COLOR_TYPE_NUM	22	// Number of all color type +2(V2.4 rl) +1(v2.5)

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
	ID_CARTRIDGE_TYPE_COLOR_ip100		= 'T',	// ip100 type
	ID_CARTRIDGE_TYPE_BLACK_MN_ip2200	= 'U',	// ip2200 type BLACK(Mini)
	ID_CARTRIDGE_TYPE_COLOR_MN_ip2200	= 'V',	// ip2200 type COLOR(Mini)
	ID_CARTRIDGE_TYPE_COLOR_ip90		= 'W',	// ip90 type (CIL:OFF)
	ID_CARTRIDGE_TYPE_COLOR_ip90_CIL	= 'X',	// ip90 type (CIL:ON)
	ID_CARTRIDGE_TYPE_COLOR_ip4600		= 'Y',	// iP4600 type
	ID_CARTRIDGE_TYPE_COLOR_ip3600		= 'Z',	// iP3600 type
	ID_CARTRIDGE_TYPE_COLOR_mg8100		= '[',	// MG8100 type
	ID_CARTRIDGE_TYPE_DUMMY,					// Dummy scanner cartridge
	ID_CARTRIDGE_TYPE_BLACK_EX_ip2200	= ']',	// MG4100 type Black(extra)
	ID_CARTRIDGE_TYPE_COLOR_mg5400		= '^',	// MG5400 type
	ID_CARTRIDGE_TYPE_COLOR_mg6300		= '_',	// MG6300 type
	
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
	ID_INK_STS_FRM		= 0x46,	// FRM				'F'

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


// Status message ID.
typedef enum {
	ID_STS_MESSAGE_SC_USEDTANK_FULL,			// Used tank full. (Service call)
	ID_STS_MESSAGE_SC_USEDTANK_FULLJP,			// Used tank full. (Service call) for Ver.2.70
	ID_STS_MESSAGE_ERROR_COMMON_NUMBER,			// Error Number.   (Service call or Operator call)
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
	ID_STS_MESSAGE_OC_PAPER_JAM1_2nd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM1_3rd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM2_3rd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM2_START,			// Paper jam. (Operator call)	v2.7
	ID_STS_MESSAGE_OC_PAPER_JAM03,				// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM03_2nd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM03_2ndFF,		// Paper jam. (Operator call)	v2.7
	ID_STS_MESSAGE_OC_PAPER_JAM04,				// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM04_2nd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_PAPER_JAM05_2nd,			// Paper jam. (Operator call)	v2.6
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST,			// Used tank almost full. (Operator call)
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST2,			// Used tank almost full. (Operator call)
	ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP,		// Used tank almost full. (Operator call) for Ver.2.70
	ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP2,		// Used tank almost full. (Operator call) for Ver.2.70
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST_START,	// Used tank almost full. (Operator call) for Ver.2.70
	ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP_START,	// Used tank almost full. (Operator call) for Ver.2.70
	ID_STS_MESSAGE_OC_COVER_OPEN,				// Cover open. (Operator call)
	ID_STS_MESSAGE_OC_COVER_OPEN2,				// Cover open. (Operator call)	v2.5
	ID_STS_MESSAGE_OC_COVER_CLOSE,				// Cover close. (Operator call)	v2.5 
	ID_STS_MESSAGE_OC_COVER_CLOSE2,				// Cover close. (Operator call)	v2.5 
	ID_STS_MESSAGE_OC_COVER_CLOSE3,				// Cover close. (Operator call)	v3.5 
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
	ID_STS_MESSAGE_WAR_INKLOW_AFTER,			// Ink low after message. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_40_AFTER,			// ink low level 3 after message. (Warning)
	ID_STS_MESSAGE_WAR_REG_NO_ADJUSTMENT,		// No adjustment message. (HCF)
	ID_STS_MESSAGE_CIL_OFF,						// Check ink level off.
	ID_STS_MESSAGE_INVALID,						// Invalid status recieved.
	ID_STS_MESSAGE_OC_CDR_GUIDE,				// CD-R Tray Guide On.
	ID_STS_MESSAGE_OC_CDR_GUIDE_2nd,			// CD-R Tray Guide On.
	ID_STS_MESSAGE_OC_CDR_GUIDE_3rd,			// CD-R Tray Guide On.
	ID_STS_MESSAGE_OC_CDR_GUIDE2_3rd,			// CD-R Tray Guide On.
	ID_STS_MESSAGE_CDR_GUIDE_PRINT,				// CD-R Tray Guide On.	v2.5
	ID_STS_MESSAGE_CDR_GUIDE_PRINT_2nd,			// CD-R Tray Guide On.	v2.5
	ID_STS_MESSAGE_CDR_GUIDE_PRINT_3rd,			// CD-R Tray Guide On.	v2.5
	ID_STS_MESSAGE_CDR_GUIDE_PRINT2,			// CD-R Tray Guide On.	v2.5
	ID_STS_MESSAGE_CDR_GUIDE_PRINT2_3rd,		// CD-R Tray Guide On.	v2.5
	ID_STS_MESSAGE_OC_INKTANK_NOTPROPERLY,		// Ink tank nothing. iP90
	ID_STS_MESSAGE_OC_INKTANK_NOTPROPERLY_LOCKLEVER_01,		// ##B-21## Ink tank nothing. iP100
	ID_STS_MESSAGE_OC_INKTANK_NOTPROPERLY_LOCKLEVER_02,		// ##B-21## Ink tank nothing. iP100
	ID_STS_MESSAGE_OC_INKTANK_NOTPROPERLY_LOCKLEVER_03,		// ##B-21## Ink tank nothing. iP100
	ID_STS_MESSAGE_OC_CARTRIDGE_NOTPROPERLY,	// Ink cartridge not properly. i250/i255
	ID_STS_MESSAGE_OC_USBDEVICE,				// ##B-20## USB Device 560i 860i 990i
	ID_STS_MESSAGE_OC_USBDEVICE_BLUETOOTH,		// ##B-20## USB and Bluetooth Device iP100
	ID_STS_MESSAGE_OC_HEADALIGNMENT,			// Head Alignment 860i 990i
	ID_STS_MESSAGE_OC_HEADALIGNMENT2,			// Head Alignment 860i 990i
	ID_STS_MESSAGE_OC_HARDWAREERROR_TANK,		// Hardware error (ink tank)
	ID_STS_MESSAGE_OC_PLURALERROR_TANK,			// Plural error (ink tank) 1st messeage.
	ID_STS_MESSAGE_OC_DIFFERENT_REGION_TANK,	// No Recognize error (ink cartridge) 1st messeage.
	ID_STS_MESSAGE_OC_POSITION_MISMACH_TANK,	// Position Mismatch error (ink tank) 1st messeage.
	ID_STS_MESSAGE_OC_UNINSTALLATION_TANK,		// Uninstallation (ink tank) 1st messeage.
	ID_STS_MESSAGE_OC_INKOUT_TANK2,				// Ink Out error (ink tank) 1st messeage.
	ID_STS_MESSAGE_OC_INKOUT_TANK2_4R,			// Ink Out error (ink tank) 1st messeage.(4-R)
	ID_STS_MESSAGE_OC_INKOUT06_TANK,			// Ink Out06 error (ink tank) 2th messeage.
	ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP,		// Ink Out06 error (ink tank) 2th messeage.
	ID_STS_MESSAGE_OC_REFILL_LONG,				// Rifel error 1st messeage.
	ID_STS_MESSAGE_OC_REFILL,					// Rifel error 1st messeage.
	ID_STS_MESSAGE_OC_TANK_NO,					// Bk/Cl Tank error 1st messeage.(for iP90)
	ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART,		// No Recognize error (ink cartridge) 1st messeage.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2,			// Remain unknown error 1st messeage.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN3,			// Remain unknown error 1st messeage.(for iP90)
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN3_3rd,		// Remain unknown error 3rd messeage.(for iP90)
	ID_STS_MESSAGE_OC_INKOUT_CART,				// Ink Out error (ink cartridge) 1st messeage.
	ID_STS_MESSAGE_OC_INKOUT_CART_START,		// Ink Out error (ink cartridge) 1st messeage for MFP.(START Button)
	ID_STS_MESSAGE_INK_BLACK7e,					// Black [7e] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK9,					// Photo black [9] ink error. (Operator call)
	ID_STS_MESSAGE_INK_PHOTO_CYAN7e,			// Photo Cyan [7e] ink error. (Operator call)
	ID_STS_MESSAGE_INK_PHOTO_MAGENTA7e,			// Photo Magenta [7e] ink error. (Operator call)
	ID_STS_MESSAGE_INK_CYAN7e,					// Cyan [7e] ink error. (Operator call)
	ID_STS_MESSAGE_INK_MAGENTA7e,				// Magenta [7e] ink error. (Operator call)
	ID_STS_MESSAGE_INK_YELLOW7e,				// Yellow [7e] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK,					// Balck ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLOR,					// Color ink error. (Operator call)
	ID_STS_MESSAGE_INK_MAGENTA,					// Magenta ink error. (Operator call)
	ID_STS_MESSAGE_INK_YELLOW,					// Yellow ink error. (Operator call)
	ID_STS_MESSAGE_INK_CYAN,					// Cyan ink error. (Operator call)
	ID_STS_MESSAGE_INK_GLAY,					// Gray ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK30,					// Balck [30] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK830,				// Balck [830] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK37,					// Balck [37] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK40,					// Balck [40] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK50,					// Balck [50] ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLOR31,					// Color [31] ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLOR831,				// Color [831] ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLOR38,					// Color [38] ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLOR41,					// Color [41] ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLOR51,					// Color [51] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK70,					// Balck [70] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK90,					// Balck [90] ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLOR71,					// Color [71] ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLOR91,					// Color [91] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK8,					// Black [8] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK5,					// black [5] ink error. (Operator call)
	ID_STS_MESSAGE_INK_PHOTO_CYAN8,				// Photo Cyan [8] ink error. (Operator call)
	ID_STS_MESSAGE_INK_PHOTO_MAGENTA8,			// Photo Magenta [8] ink error. (Operator call)
	ID_STS_MESSAGE_INK_CYAN8,					// Cyan [8] ink error. (Operator call)
	ID_STS_MESSAGE_INK_MAGENTA8,				// Magenta [8] ink error. (Operator call)
	ID_STS_MESSAGE_INK_YELLOW8,					// Yellow [8] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK19,					// Black [19] ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLOR19,					// Color [19] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK35,					// Black [35] ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLOR36,					// Color [36] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACK15,					// Black [15] ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLOR16,					// Color [16] ink error. (Operator call)
	ID_STS_MESSAGE_INK_BLACKTANK,				// Black Tank ink error. (Operator call)
	ID_STS_MESSAGE_INK_COLORTANK,				// Color Tank ink error. (Operator call)
	ID_STS_MESSAGE_OC_PLURALERROR_TANK_3rd,	 	// Plural error (ink tank) 3rd message.
	ID_STS_MESSAGE_OC_UNINSTALLATION_TANK_3rd,	// Uninstallation (ink tank) 3rd message.
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_1st,		// Ink Out error (ink tank) 2nd messeage.
	ID_STS_MESSAGE_OC_INKEMPTY0602_TANK_1st,	// Ink Out error (ink tank) 2nd messeage.
	ID_STS_MESSAGE_OC_REFILL_3rd_LONG,			// Rifel error 3rd messeage.
	ID_STS_MESSAGE_OC_REFILL2_3rd_LONG,			// Rifel error 3rd messeage.
	ID_STS_MESSAGE_OC_REFILL_3rd,				// Rifel error 3rd messeage.
	ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART_3rd,	// No Recognize error (ink cartridge) 3rd messeage.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd,		// Remain unknown error 3rd messeage.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_MFP,	// Remain unknown error 3rd messeage for MFP.
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START,	// Remain unknown error 3rd messeage for MFP.(START Button)
	ID_STS_MESSAGE_OC_INKOUT_CART_3rd,			// Ink Out error (ink cartridge) 3rd messeage.
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd,		// Ink Empty error 3rd messeage.
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP,	// Ink Empty error 3rd messeage.
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE,	// Cartridge Empty error 3rd messeage.
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET,	// Cartridge Empty error 3rd messeage.
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
	ID_STS_MESSAGE_INK_BLACK310,
	ID_STS_MESSAGE_INK_COLOR311,
	ID_STS_MESSAGE_INK_BLACK815,
	ID_STS_MESSAGE_INK_COLOR816,
	ID_STS_MESSAGE_INK_BLACK815XL,
	ID_STS_MESSAGE_INK_COLOR816XL,
	ID_STS_MESSAGE_INK_BLACK810,
	ID_STS_MESSAGE_INK_COLOR811,
	ID_STS_MESSAGE_INK_BLACK810XL,
	ID_STS_MESSAGE_INK_COLOR810XL,
	ID_STS_MESSAGE_INK_BLACK210,
	ID_STS_MESSAGE_INK_COLOR211,
	ID_STS_MESSAGE_INK_BLACK210XL,
	ID_STS_MESSAGE_INK_COLOR210XL,
	ID_STS_MESSAGE_INK_BLACK510,
	ID_STS_MESSAGE_INK_COLOR511,
	ID_STS_MESSAGE_INK_BLACK512,
	ID_STS_MESSAGE_INK_COLOR513,
	ID_STS_MESSAGE_INK_BLACK320,
	ID_STS_MESSAGE_INK_BLACK321,
	ID_STS_MESSAGE_INK_CYAN321,
	ID_STS_MESSAGE_INK_MAGENTA321,
	ID_STS_MESSAGE_INK_YELLOW321,
	ID_STS_MESSAGE_INK_BLACK820,
	ID_STS_MESSAGE_INK_BLACK821,
	ID_STS_MESSAGE_INK_CYAN821,
	ID_STS_MESSAGE_INK_MAGENTA821,
	ID_STS_MESSAGE_INK_YELLOW821,
	ID_STS_MESSAGE_INK_BLACK220,
	ID_STS_MESSAGE_INK_BLACK221,
	ID_STS_MESSAGE_INK_CYAN221,
	ID_STS_MESSAGE_INK_MAGENTA221,
	ID_STS_MESSAGE_INK_YELLOW221,
	ID_STS_MESSAGE_INK_BLACK520,
	ID_STS_MESSAGE_INK_BLACK521,
	ID_STS_MESSAGE_INK_CYAN521,
	ID_STS_MESSAGE_INK_MAGENTA521,
	ID_STS_MESSAGE_INK_YELLOW521,
	ID_STS_MESSAGE_INK_BLACK125,
	ID_STS_MESSAGE_INK_BLACK126,
	ID_STS_MESSAGE_INK_MAGENTA126,
	ID_STS_MESSAGE_INK_YELLOW126,
	ID_STS_MESSAGE_INK_CYAN126,
	ID_STS_MESSAGE_INK_GLAY126,
	ID_STS_MESSAGE_INK_BLACK225,
	ID_STS_MESSAGE_INK_BLACK226,
	ID_STS_MESSAGE_INK_MAGENTA226,
	ID_STS_MESSAGE_INK_YELLOW226,
	ID_STS_MESSAGE_INK_CYAN226,
	ID_STS_MESSAGE_INK_GLAY226,
	ID_STS_MESSAGE_INK_BLACK325,
	ID_STS_MESSAGE_INK_BLACK326,
	ID_STS_MESSAGE_INK_MAGENTA326,
	ID_STS_MESSAGE_INK_YELLOW326,
	ID_STS_MESSAGE_INK_CYAN326,
	ID_STS_MESSAGE_INK_GLAY326,
	ID_STS_MESSAGE_INK_BLACK425,
	ID_STS_MESSAGE_INK_BLACK426,
	ID_STS_MESSAGE_INK_MAGENTA426,
	ID_STS_MESSAGE_INK_YELLOW426,
	ID_STS_MESSAGE_INK_CYAN426,
	ID_STS_MESSAGE_INK_GLAY426,
	ID_STS_MESSAGE_INK_BLACK525,
	ID_STS_MESSAGE_INK_BLACK526,
	ID_STS_MESSAGE_INK_MAGENTA526,
	ID_STS_MESSAGE_INK_YELLOW526,
	ID_STS_MESSAGE_INK_CYAN526,
	ID_STS_MESSAGE_INK_GLAY526,
	ID_STS_MESSAGE_INK_BLACK725,
	ID_STS_MESSAGE_INK_BLACK726,
	ID_STS_MESSAGE_INK_MAGENTA726,
	ID_STS_MESSAGE_INK_YELLOW726,
	ID_STS_MESSAGE_INK_CYAN726,
	ID_STS_MESSAGE_INK_GLAY726,
	ID_STS_MESSAGE_INK_BLACK825,
	ID_STS_MESSAGE_INK_BLACK826,
	ID_STS_MESSAGE_INK_MAGENTA826,
	ID_STS_MESSAGE_INK_YELLOW826,
	ID_STS_MESSAGE_INK_CYAN826,
	ID_STS_MESSAGE_INK_GLAY826,
	ID_STS_MESSAGE_INK_COLOR141XL,
	ID_STS_MESSAGE_INK_COLOR141,
	ID_STS_MESSAGE_INK_COLOR241XL,
	ID_STS_MESSAGE_INK_COLOR241,
	ID_STS_MESSAGE_INK_COLOR341XL,
	ID_STS_MESSAGE_INK_COLOR341,
	ID_STS_MESSAGE_INK_COLOR441XL,
	ID_STS_MESSAGE_INK_COLOR441,
	ID_STS_MESSAGE_INK_COLOR541XL,
	ID_STS_MESSAGE_INK_COLOR541,
	ID_STS_MESSAGE_INK_COLOR641XL,
	ID_STS_MESSAGE_INK_COLOR641,
	ID_STS_MESSAGE_INK_COLOR741XL,
	ID_STS_MESSAGE_INK_COLOR741,
	ID_STS_MESSAGE_INK_COLOR841XL,
	ID_STS_MESSAGE_INK_COLOR841,
	ID_STS_MESSAGE_INK_COLOR93,
	ID_STS_MESSAGE_INK_COLOR98,
	ID_STS_MESSAGE_INK_BLACK140XXL,
	ID_STS_MESSAGE_INK_BLACK140XL,
	ID_STS_MESSAGE_INK_BLACK140,
	ID_STS_MESSAGE_INK_BLACK240XXL,
	ID_STS_MESSAGE_INK_BLACK240XL,
	ID_STS_MESSAGE_INK_BLACK240,
	ID_STS_MESSAGE_INK_BLACK340XL,
	ID_STS_MESSAGE_INK_BLACK340,
	ID_STS_MESSAGE_INK_BLACK440XL,
	ID_STS_MESSAGE_INK_BLACK440,
	ID_STS_MESSAGE_INK_BLACK540XL,
	ID_STS_MESSAGE_INK_BLACK540,
	ID_STS_MESSAGE_INK_BLACK640XXL,
	ID_STS_MESSAGE_INK_BLACK640XL,
	ID_STS_MESSAGE_INK_BLACK640,
	ID_STS_MESSAGE_INK_BLACK740XL,
	ID_STS_MESSAGE_INK_BLACK740,
	ID_STS_MESSAGE_INK_BLACK840XL,
	ID_STS_MESSAGE_INK_BLACK840,
	ID_STS_MESSAGE_INK_BLACK83,
	ID_STS_MESSAGE_INK_BLACK88,
	ID_STS_MESSAGE_PREPARE,
	ID_STS_MESSAGE_OC_PAPER_JAM04_2nd_NOT_ONTOSIDE,
	ID_STS_MESSAGE_OC_PAPER_JAM05_2nd_NOT_ONTOSIDE,
	ID_STS_MESSAGE_COVERCLOSE_SLOWY,
	ID_STS_MESSAGE_OC_MEDIA,
	ID_STS_MESSAGE_OC_PLAINPAPER,
	ID_STS_MESSAGE_OC_DETAILS,
	ID_STS_MESSAGE_JOB_JOBCANCEL_STOP,
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP,
	ID_STS_MESSAGE_OC_PAPER_JAM03_02SFP_2nd,
	ID_STS_MESSAGE_OC_PAPER_JAM03_02MFP_2nd,
	ID_STS_MESSAGE_OC_LCDPANEL,
	ID_STS_MESSAGE_OC_INKTANK_NOTPROPERLY_LOCKLEVER_PUSH,
	ID_STS_MESSAGE_OTHER_USE,
	ID_STS_MESSAGE_SC_SERVICE_ERROR_09COMMON_NUMBER,
	ID_STS_MESSAGE_SC_SERVICE_ERROR_09COMMON,
	ID_STS_MESSAGE_SC_SERVICE_ERROR_09VHMONITOR,
	ID_STS_MESSAGE_SC_USEDTANK_FULL_09,
	ID_STS_MESSAGE_SC_USEDTANK_FULLJP_09,
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST_OK2,
	ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP_OK2,
	ID_STS_MESSAGE_OC_INKOUT06_FAX,
	ID_STS_MESSAGE_BUSY_HEADPROTECT,
	ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_OK_07SPRING,
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP,
	ID_STS_MESSAGE_OC_SMARTTRAY_CLOSE1,
	ID_STS_MESSAGE_OC_SMARTTRAY_CLOSE2,
	ID_STS_MESSAGE_JOB_JOBCANCEL_NOKEY,
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST_START2,
	ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP_START2,
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST_RESUME2,
	ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP_RESUME2,
	ID_STS_MESSAGE_OC_CDR_GUIDE3,
	ID_STS_MESSAGE_CDR_GUIDE_PRINT3,
	ID_STS_MESSAGE_CDR_GUIDE_PRINT2_2nd,
	ID_STS_MESSAGE_PAPERTHICKNESS_LEVERPOSITION,
	ID_STS_MESSAGE_LEFT,
	ID_STS_MESSAGE_RIGHT,
	ID_STS_MESSAGE_OC_DUPLEX_STOPPAGE_RESUME,
	ID_STS_MESSAGE_OC_DUPLEX_STOPPAGE_OK,
	ID_STS_MESSAGE_OC_OLDINK,
	ID_STS_MESSAGE_OC_OLDINK02,
	ID_STS_MESSAGE_OC_CDR_GUIDE4,
	ID_STS_MESSAGE_OC_CDR_GUIDE3_3rd,
	ID_STS_MESSAGE_OC_CDR_GUIDE5,
	ID_STS_MESSAGE_SMMSG_TOUCH,
	ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH,
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST_TOUCH,
	ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP_TOUCH,
	ID_STS_MESSAGE_CDR_GUIDE_PRINT_3rd_TOUCH,
	ID_STS_MESSAGE_OC_DUPLEX_STOPPAGE2_TOUCH,
	ID_STS_MESSAGE_OC_DUPLEX_STOPPAGE2_OK,
	ID_STS_MESSAGE_OC_DUPLEX_STOPPAGE2_RESUME,
	ID_STS_MESSAGE_OC_DUPLEX_STOPPAGE2_START,
	ID_STS_MESSAGE_OC_HEADALIGNMENT_TOUCH,
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH,
	ID_STS_MESSAGE_SC_SERVICE_CARRIAGEPOSITION_ERROR,
	ID_STS_MESSAGE_OC_PROTECTIVEMATERIAL,
	ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART2,
	ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART2_3rd,
	ID_STS_MESSAGE_OC_PAPER_OUTFR2,
	ID_STS_MESSAGE_OC_HEADCOVER_OPEN,
	ID_STS_MESSAGE_OC_INKTANK_NOTPROPERLY_LOCKLEVER_PUSHUP,
	ID_STS_MESSAGE_OC_PAPER_JAM03_FRONTCOVERCLOSE_IFMEM,
	ID_STS_MESSAGE_OC_PAPER_JAM03_RIGHTSIDEDOWN,
	ID_STS_MESSAGE_BUSY_CARTRIDGE_CHANGE_FRONT,
	ID_STS_MESSAGE_BUSY_HEADPROTECT_FRONT,
	ID_STS_MESSAGE_OC_COVER_OPEN_OUTPUTCOVER,
	ID_STS_MESSAGE_OC_PAPER_JAM03_FRONTCOVERCLOSE,
	ID_STS_MESSAGE_SC_SERVICE_SCANNER_LOCK_ERROR,
	ID_STS_MESSAGE_OC_DUPLEX_STOPPAGE_TOUCH,
	ID_STS_MESSAGE_OC_POSITION_MISMACH_CARTRIDGE,
	ID_STS_MESSAGE_OC_PLURALERROR_CARTRIDGE,
	ID_STS_MESSAGE_OC_PLURALERROR_CARTRIDGE_3rd,
	ID_STS_MESSAGE_OC_PAPER_JAM2_3rd_TOUCH,
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER,
	ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER,
	ID_STS_MESSAGE_OC_PAPER_JAM03_FRONTCOVERCLOSE2,
	ID_STS_MESSAGE_OC_PAPER_JAM03_FRONTCOVERCLOSE_IFMEM2,
	ID_STS_MESSAGE_INK_BLACK0,
	ID_STS_MESSAGE_INK_BLACK1,
	ID_STS_MESSAGE_INK_MAGENTA0,
	ID_STS_MESSAGE_INK_YELLOW0,
	ID_STS_MESSAGE_INK_CYAN0,
	ID_STS_MESSAGE_INK_GLAY0,
	ID_STS_MESSAGE_SC_SERVICE_ERROR_CARRIAGEPOS,
	ID_STS_MESSAGE_OC_FITPAPER_CASSETUP,
	ID_STS_MESSAGE_OC_FITPAPER_CASSETLOWER,
	ID_STS_MESSAGE_SMMSG_TAP,
	ID_STS_MESSAGE_OC_USERSIZE_RESUME,
	ID_STS_MESSAGE_OC_USERSIZE_STOP,
	ID_STS_MESSAGE_OC_USERSIZE_STOP_TOUCH,
	ID_STS_MESSAGE_OC_EJECTCOVERCLOSE12_1_BTN,
	ID_STS_MESSAGE_OC_EJECTCOVERCLOSE12_1,
	ID_STS_MESSAGE_OC_PAPER_JAM_BACK12_1,
	ID_STS_MESSAGE_OC_PAPER_JAM_BACK12_1_2,
	ID_STS_MESSAGE_OC_PAPER_JAM_BACK12_2,
	ID_STS_MESSAGE_OC_PAPER_JAM2_3rd_TAP,
	ID_STS_MESSAGE_BUSY_HEADCHANGING,
	ID_STS_MESSAGE_OC_COVER_OPEN3,
	ID_STS_MESSAGE_SC_SERVICE_ERROR_CARRIAGEPOS_DISPO,
	ID_STS_MESSAGE_OC_INKOUT06_TANK_TAP,
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST_TAP,
	ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP_TAP,
	ID_STS_MESSAGE_OC_DUPLEX_STOPPAGE2_TAP,
	ID_STS_MESSAGE_OC_HEADALIGNMENT_TAP,
	ID_STS_MESSAGE_CDR_GUIDE_PRINT_3rd_TAP,
	ID_STS_MESSAGE_OC_EJECTCOVERCLOSE12,
	
	ID_STS_MESSAGE_NON = -1000,
	ID_STS_MESSAGE_COLOR,
	ID_STS_MESSAGE_COLOR_CARTRIDGE,
	ID_STS_MESSAGE_COLOR_TYPE,
	ID_STS_MESSAGE_UNKNOWN_COLOR,
} ENUM_STSMessageID;


// Other message ID.
typedef enum {
	ID_OTHER_MESSAGE_NONE = -1,				// None.
	ID_OTHER_MESSAGE_PRINTER_IS_READY,		// Printer is ready.
	ID_OTHER_MESSAGE_UNKNOWN_PRINTER,		// Unknown printer.
	ID_OTHER_MESSAGE_SPOOLER_ERROR,			// Spooler error.
	ID_OTHER_MESSAGE_NO_RESPONSE,			// No Response error.
	ID_OTHER_MESSAGE_COLLECTING_STATUS,		// Collecting Status.
	ID_OTHER_MESSAGE_SLEEP,					// Sleep.
	ID_OTHER_MESSAGE_BUSY,					// Busy.
	ID_OTHER_MESSAGE_FIRMUP,				// Firmup.
	ID_OTHER_MESSAGE_OTHEROPERATION,		// Other Operation.
	ID_OTHER_MESSAGE_OFFLINE,				// Off Line.
	ID_OTHER_MESSAGE_USB_BACKEND_NORMAL,	// USB Backend Normal.
	ID_OTHER_MESSAGE_FATAL_ERROR,			// Fatal error.
	ID_OTHER_MESSAGE_ARGUMENT_ERROR,		// Argument error.
} ENUM_OtherMessageID;

// Printer Interface 
#define ID_DEV_1284	1
#define ID_DEV_USB	2
#define ID_DEV_1394	3



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

/* for ink ifnumber */
typedef struct {
	char	colorstr;				/* LM Color String "C,M,Y,L,l,B,E..." */
	char	ifnumberstr[32];		/* Ink IFNumber */
} ST_InkIFNumber;

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
	//Ver.300 set pictarea
	gint				disablepictarea_drawflag;	// Disable Pict Area
	gint				unknownicon_drawflag;		// "?" draw flag only DOC:1683/1689
	gint				icon_deleteflag;			// icon draw flag
	//Ver.3.10 for Network
	gint				user_otherflag;			// Other User flag
	/* Ver.3.80 for Ifnumber */
	ST_InkIFNumber		status_ifnumber[8];
} ST_PrinterStatus;

// for error classification table.
typedef struct {
	gint				errorCode;	// Error code
	ENUM_ErrorLevelID	errorLevel;	// Error level
	ENUM_OtherMessageID	messageID;	// Message ID
} ST_ErrorCodeTbl;
