/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2004
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
#define STR_PRODUCT_NAME		"Status Monitor"

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
#define CARTRIDGE_COLOR_TYPE_NUM	10	// Number of all color type 

// Max buffer size.
#define MAX_BUF_SIZE				1024

/** Widget name **/
// Window name.
#define STR_WINDOW_NAME_MAIN			"mainWindow"

// Widget name of main window.
#define STR_MAIN_BUTTON_NAME_CONTINUE	"buttonMainContinue"
#define STR_MAIN_BUTTON_NAME_CANCEL		"buttonMainCancel"
#define STR_MAIN_TEXT_STATUS			"textMainStatus"
#define STR_MAIN_LABEL_CARTRIDGE_TYPE	"labelMainCartridgeType"
#define STR_MAIN_LABEL_LEVER_POSITION	"labelMainLeverPosition"
#define STR_MAIN_DRAW_CARTRIDGE			"drawMainCartridge"


/*** Enums ***/
// Cartridge type ID.
typedef enum {
	ID_CARTRIDGE_TYPE_NONE			= 0x20,	// Cartridge not installed
	ID_CARTRIDGE_TYPE_UNKNOWN		= 0x3f,	// Unknown
	ID_CARTRIDGE_TYPE_SCANNER		= 0x32,	// Scanner cartridge
	ID_CARTRIDGE_TYPE_DUMMY_SCANNER,		// Dummy scanner cartridge
	ID_CARTRIDGE_TYPE_UNSUPPORTED,			// Unsupported cartridge
	ID_CARTRIDGE_TYPE_PHOTO			= 0x41,	// F850 type
	ID_CARTRIDGE_TYPE_BLACK,				// F360 type (Black)
	ID_CARTRIDGE_TYPE_PHOTO_COLOR	= 0x44,	// F360 type (Photo)
	ID_CARTRIDGE_TYPE_COLOR_S600,			// S600 type
	ID_CARTRIDGE_TYPE_COLOR_S300,			// S300 type (CIL:OFF)
	ID_CARTRIDGE_TYPE_COLOR_S300_CIL,		// S300 type (CIL:ON)
	ID_CARTRIDGE_TYPE_PHOTO2		= 'H',	// 950i type
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
	ID_STS_MESSAGE_SC_SERVICE_ERROR_PRE,		// Service error pre message. (Service call)
	ID_STS_MESSAGE_SC_SERVICE_ERROR_AFTER,		// Service error after message. (Service call)
	ID_STS_MESSAGE_OC_PAPER_OUT,				// Paper out. (Operator call)
	ID_STS_MESSAGE_OC_PAPER_JAM,				// Paper jam. (Operator call)
	ID_STS_MESSAGE_OC_CARTRIDGE_NONE,			// Cartridge not installed while printing. (Operator call)
	ID_STS_MESSAGE_OC_HEAD_ERROR,				// Head error. (Operator call)
	ID_STS_MESSAGE_OC_CARTRIDGE_SCANNER,		// Scanner cartridge detected in printing. (Operator call)
	ID_STS_MESSAGE_OC_USEDTANK_ALMOST,			// Used tank almost full. (Operator call)
	ID_STS_MESSAGE_OC_PROTECTOR,				// Protector not installed. (Operator call)
	ID_STS_MESSAGE_OC_INKOUT,					// Ink out. (Operator call)
	ID_STS_MESSAGE_OC_INKOUT_BLACK,				// Black ink out. (Operator call)
	ID_STS_MESSAGE_OC_INKOUT_PHOTO_BLACK,		// Photo black ink out. (Operator call)
	ID_STS_MESSAGE_OC_INKOUT_PHOTO_CYAN,		// Photo cyan ink out. (Operator call)
	ID_STS_MESSAGE_OC_INKOUT_PHOTO_MAGENTA,		// Photo magenta ink out. (Operator call)
	ID_STS_MESSAGE_OC_INKOUT_CYAN,				// Cyan ink out. (Operator call)
	ID_STS_MESSAGE_OC_INKOUT_MAGENTA,			// Magenta ink out. (Operator call)
	ID_STS_MESSAGE_OC_INKOUT_YELLOW,			// Yellow ink out. (Operator call)
	ID_STS_MESSAGE_OC_COVER_OPEN,				// Cover open. (Operator call)
	ID_STS_MESSAGE_OC_OTHER,					// Another operator call. (Operator call)
	ID_STS_MESSAGE_BUSY_CLEANING,				// Cleaning. (Busy status)
	ID_STS_MESSAGE_BUSY_CARTRIDGE_CHANGE,		// Cartridge replacement. (Busy status)
	ID_STS_MESSAGE_BUSY_TEST_PRINTING,			// Test printing. (Busy status)
	ID_STS_MESSAGE_BUSY_PRINTER_USED,			// Printer using nother interface. (Busy status)
	ID_STS_MESSAGE_CARTRIDGE_SCANNER,			// Scanner cartridge detected.
	ID_STS_MESSAGE_CARTRIDGE_UNSUPPORTED,		// Unsupported cartridge.
	ID_STS_MESSAGE_CARTRIDGE_NONE,				// Cartridge not installed.
	ID_STS_MESSAGE_BASE_PRINTING,				// Printing.
	ID_STS_MESSAGE_BASE_ONLINE,					// Printer is online.
	ID_STS_MESSAGE_WAR_INKLOW,					// Ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_BLACK,			// Black ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_PHOTO_BLACK,		// Photo black ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_PHOTO_CYAN,		// Photo cyan ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_PHOTO_MAGENTA,	// Photo magenta ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_CYAN,				// Cyan ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_MAGENTA,			// Magenta ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_YELLOW,			// Yellow ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_COLOR,			// Color ink low. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_24PRE,			// S300 ink low level 3 pre message. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_24BLACK3,			// S300 black ink low level 3. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_24COLOR3,			// S300 color ink low level 3. (Warning)
	ID_STS_MESSAGE_WAR_INKLOW_24AFTER,			// S300 ink low level 3 after message. (Warning)
	ID_STS_MESSAGE_CIL_OFF,						// Check ink level off.
	ID_STS_MESSAGE_INVALID,						// Invalid status recieved.
	ID_STS_MESSAGE_OC_CDR_GUIDE,						// CD-R Tray Guide On.
	ID_STS_MESSAGE_CDR_GUIDE,						// CD-R Tray Guide On.
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
	ST_CartridgeClass		cartridgeClass[2];				// Cartridge classification
	ENUM_LeverPositionID		leverPosition;					// Lever position
	gint				messageNum;					// Num of message
	ENUM_STSMessageID		*pMessageID;					// Message ID
	gchar				serviceCallID[8];				// Service call ID
	ST_InkStatus			cartridgeStatus[CARTRIDGE_COLOR_TYPE_NUM];	// Cartridge status.
	gint				printInterface;					// printer interface 1284/usb/1394
} ST_PrinterStatus;

// for error classification table.
typedef struct {
	gint				errorCode;	// Error code
	ENUM_ErrorLevelID	errorLevel;	// Error level
	ENUM_OtherMessageID	messageID;	// Message ID
} ST_ErrorCodeTbl;
