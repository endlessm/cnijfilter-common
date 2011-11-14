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
#include"bjcupsmon_common.h"
#include"bjcupsmon_transsts.h"

static int processIDcheck(const ST_MSGTBL *p_msgtbl, char *p_status, int status_size );
//static int chkoccuroperatorcall(ST_CUPSSTS *p_tbl, char chkchr);
static int chkoccuralert(ST_CUPSSTS *p_tbl, char chkchr);
static int chkoccuralert_inkunknown(ST_CUPSSTS *p_tbl, char chkchr);
static int chkoccuralert_inklow(ST_CUPSSTS *p_tbl, char chkchr, int i );
static int storeMessageID(ST_PrinterStatus *p_sts, int msgID);
static int processstandardmsgcheck(ST_PrinterStatus *p_sts, const ST_MSGTBL *p_msgtbl, char *p_status, int status_size);
static int chk_inkout_DOCEMPTY_CTKIO(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int setButtonID(ST_CUPSSTS *p_tbl);
static int setRearSupplyID(ST_CUPSSTS *p_tbl);
static int setFrontSupplyID(ST_CUPSSTS *p_tbl);
static int setInkRemainSequenceID(ST_CUPSSTS *p_tbl);

static const
ST_MSGTBL service[]={
  {'I', ID_STS_MESSAGE_SC_USEDTANK_FULL},
  {'J', ID_STS_MESSAGE_SC_USEDTANK_FULLJP},
//Ver.2.70 beta02 2.00.01.14   Don't use "0-F"!  ex) 6B00 is NG.
//  {'B', ID_STS_MESSAGE_SC_BATTERY_ERROR},
  {ENDTAG, 0}
};


static const
ST_MSGTBL operatelevel1[]={
  {'U', ID_STS_MESSAGE_OC_USBDEVICE},		// 560i 860i 990i
  {'P', ID_STS_MESSAGE_OC_PAPER_OUT},
  {'V', ID_STS_MESSAGE_OC_PAPER_OUT21},
  {'X', ID_STS_MESSAGE_OC_PAPER_OUT21},
  {'p', ID_STS_MESSAGE_OC_PAPER_OUT22},
  {'a', ID_STS_MESSAGE_OC_PAPER_OUT22},
  {'J', ID_STS_MESSAGE_OC_PAPER_JAM},
  {'q', ID_STS_MESSAGE_OC_PAPER_JAM1},
  {'h', ID_STS_MESSAGE_OC_PAPER_JAM2},
  {'j', ID_STS_MESSAGE_OC_PAPER_JAM03},
  {'n', ID_STS_MESSAGE_OC_PAPER_JAM06},
  {'Q', ID_STS_MESSAGE_OC_PAPER_JAM04},
  {'i', ID_STS_MESSAGE_OC_PAPER_JAM05},
  {'Z', ID_STS_MESSAGE_OC_PAPER_JAM07},
  //Ver.2.80 Change
  {'H', ID_STS_MESSAGE_CARTRIDGE_NONE},	/* B-01 */
  //{'H', ID_STS_MESSAGE_OC_CARTRIDGE_NONE},	/* B-01 */
  {'R', ID_STS_MESSAGE_OC_HEAD_ERROR},
  {'r', ID_STS_MESSAGE_OC_HEAD_ERROR2},
  {ENDTAG, 0}
};


static const
ST_MSGTBL operatelevel2[]={
  {'I', ID_STS_MESSAGE_OC_USEDTANK_ALMOST},
  {'x', ID_STS_MESSAGE_OC_USEDTANK_ALMOST2},
  {'T', ID_STS_MESSAGE_OC_INKTANK_NOTPROPERLY},		// i250/i255
  {'A', ID_STS_MESSAGE_OC_HEADALIGNMENT},		// 860i 990i
  {'N', ID_STS_MESSAGE_OC_HEADALIGNMENT2},
  {'t', ID_STS_MESSAGE_OC_HARDWAREERROR_TANK},	// iP4200 iP6600D iP7500 MP500
  {'D', ID_STS_MESSAGE_OC_BATTERY_OUT},			// iP90
  {ENDTAG, 0}
};


static const
ST_MSGTBL inkout[]={
  {'E', ID_STS_MESSAGE_OC_INKOUT06_TANK},
  {'C', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd},
  {'c', ID_STS_MESSAGE_OC_INKEMPTY0602_TANK_3rd},
  {'u', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP},
  {'B', ID_STS_MESSAGE_OC_INKOUT_CART},
  {ENDTAG, 0}
};


static const
ST_MSGTBL operatelevel3[]={
  {'s', ID_STS_MESSAGE_OC_PLURALERROR_TANK},
  {'e', ID_STS_MESSAGE_OC_DIFFERENT_REGION_TANK},
  {'S', ID_STS_MESSAGE_OC_POSITION_MISMACH_TANK},
  {'d', ID_STS_MESSAGE_OC_UNINSTALLATION_TANK},
  {'f', ID_STS_MESSAGE_OC_REFILL},
  {'z', ID_STS_MESSAGE_OC_REFILL2},
  {'b', ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART},
  {'W', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN1},
  {'w', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2},
  {'M', ID_STS_MESSAGE_OC_TANK_NO_BK},
  {'m', ID_STS_MESSAGE_OC_TANK_NO_CL},
  {ENDTAG, 0}
};


static const
ST_MSGTBL operatelevel4[]={
  {'O', ID_STS_MESSAGE_OC_COVER_OPEN},
  {'v', ID_STS_MESSAGE_OC_COVER_OPEN2},
  {'o', ID_STS_MESSAGE_OC_COVER_CLOSE},
  {'k', ID_STS_MESSAGE_OC_COVER_CLOSE2},
  {'G', ID_STS_MESSAGE_OC_CDR_GUIDE},
  {'g', ID_STS_MESSAGE_OC_CDR_GUIDE2},
  {'F', ID_STS_MESSAGE_CDR_GUIDE_PRINT},
  {'K', ID_STS_MESSAGE_CDR_GUIDE_PRINT2},
  {ENDTAG, 0}
};


static const
ST_MSGTBL busystat[]={
  {'L', ID_STS_MESSAGE_BUSY_CLEANING},			/* A-05 */
  {'C', ID_STS_MESSAGE_BUSY_CARTRIDGE_CHANGE},	/* A-06 Dispo*/
  {'D', ID_STS_MESSAGE_BUSY_CARTRIDGE_CHANGE2},	/* A-06 */
//  {'F', ID_STS_MESSAGE_BUSY_CARTRIDGE_CHANGE3},	//v2.5
  {'T', ID_STS_MESSAGE_BUSY_TEST_PRINTING},		/* A-04 */
  {'I', ID_STS_MESSAGE_BUSY_PRINTER_USED},		/* E-10 */
  {'N', ID_STS_MESSAGE_BUSY_TANK_CHANGE},		/* A-07 */
  {'B', ID_STS_MESSAGE_BUSY_PRINTER},			/* A-09 */
  {ENDTAG, 0}
};

/* for Ver.2.80 */
static const
ST_MSGTBL jobstat[]={
  {'P', ID_STS_MESSAGE_BASE_PRINTING},/* A-04 */
  {'L', ID_STS_MESSAGE_BASE_PRINTING},/* A-04 */
  {'F', ID_STS_MESSAGE_BASE_PRINTING},/* A-04 */
  {'I', ID_STS_MESSAGE_BASE_ONLINE},  /* A-03 */
  {'C', ID_STS_MESSAGE_JOB_JOBCANCEL_RESUME},	/* A-11 */
  {'R', ID_STS_MESSAGE_JOB_JOBCANCEL_STOPRESET},/* A-11 */
  {'W', ID_STS_MESSAGE_JOB_PREPARE},  /* A-18 */
  {'D', ID_STS_MESSAGE_JOB_DELAY},    /* A-19 */
  {'?', ID_STS_MESSAGE_BASE_ONLINE},  /* A-03 for to Ver.270 */ 
  {ENDTAG, 0}
};


static const
ST_MSGTBL cartridge[]={
//  {'2', ID_STS_MESSAGE_OC_CARTRIDGE_SCANNER},
//  {'4', ID_STS_MESSAGE_CARTRIDGE_UNSUPPORTED},
  {ENDTAG, 0}
};


static const
ST_MSGTBL inklowpart1[]={
  {'L', ID_STS_MESSAGE_WAR_INKLOW_BLACK},
  {'l', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_BLACK},
  {'C', ID_STS_MESSAGE_WAR_INKLOW_CYAN},
  {'M', ID_STS_MESSAGE_WAR_INKLOW_MAGENTA},
  {'Y', ID_STS_MESSAGE_WAR_INKLOW_YELLOW},
  {'c', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_CYAN},
  {'m', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_MAGENTA},
  {'b', ID_STS_MESSAGE_WAR_INKLOW_BLACK15},	// iP90
  {'e', ID_STS_MESSAGE_WAR_INKLOW_COLOR16},	// iP90
  {ENDTAG, 0}
};


static const
ST_MSGTBL inklowpart1_type_OTH[]={
  {'L', ID_STS_MESSAGE_WAR_INKLOW_BLACK8},
  {'l', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_BLACK5},
  {'C', ID_STS_MESSAGE_WAR_INKLOW_CYAN8},
  {'M', ID_STS_MESSAGE_WAR_INKLOW_MAGENTA8},
  {'Y', ID_STS_MESSAGE_WAR_INKLOW_YELLOW8},
  {'c', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_CYAN8},
  {'m', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_MAGENTA8},
  {'b', ID_STS_MESSAGE_WAR_INKLOW_BLACK15},	// iP90
  {'e', ID_STS_MESSAGE_WAR_INKLOW_COLOR16},	// iP90
  {ENDTAG, 0}
};

static const
ST_MSGTBL inkremainunknown[]={
  {'U', ID_STS_MESSAGE_WAR_INKLOW_BLACK15},	// iP90
  {'u', ID_STS_MESSAGE_WAR_INKLOW_COLOR16},	// iP90
  {ENDTAG, 0}
};


static const
ST_MSGTBL inklowpart3[]={
  {'T', ID_STS_MESSAGE_COLOR_TYPE},
  {'t', ID_STS_MESSAGE_COLOR_TYPE},
  {ENDTAG, 0}
};


static const
ST_MSGTBL inkoutpart3[]={
  {'F', ID_STS_MESSAGE_WAR_INKLOW_AFTER},
  {'f', ID_STS_MESSAGE_WAR_INKLOW_AFTER},
  {ENDTAG, 0}
};


static const
ST_MSGTBL inklowpart2[]={
  {'B', ID_STS_MESSAGE_WAR_INKLOW_BLACK40},
  {'E', ID_STS_MESSAGE_WAR_INKLOW_COLOR41},
  {ENDTAG, 0}
};


static const
ST_MSGTBL warning[]={
  {'Z', ID_STS_MESSAGE_WAR_REG_NO_ADJUSTMENT},
  {'S', ID_STS_MESSAGE_WAR_BATTERY_LOW},
  {ENDTAG, 0}
};


//Ver.2.80
static const
ST_INKREMAIN_SEQUENCE_TBL inkremain_sequence_tbl[]={
  {"IP2200",  DONOT_CARE},
  {"IP4200",  DONOT_CARE},
  {"IP7500",  DONOT_CARE},
  {"IP6600D", DONOT_CARE},
  {"MP500",   DONOT_CARE},
  {"IP3300",  AUTUMN_06},
  {"IP4300",  AUTUMN_06},
  {"MP510",   AUTUMN_06},
  {"MP600",   AUTUMN_06},
  {"MP160",   DONOT_CARE},
  {"IP2500",  SPRING_07},
  {"IP1800",  SPRING_07},
  {"IP90",    DONOT_CARE},
  {"IP4500",  AUTUMN_06},
  {"IP3500",  AUTUMN_06},
  {"MP610",   AUTUMN_06},
  {"MP520",   AUTUMN_06},
  {"MP140",   SPRING_07},
  {"MP210",   SPRING_07},
  {ENDTAG, 0}
};

//Ver.2.80
static const
ST_REARSUPPLAY_TBL rearsupply_tbl[]={
  {"IP2200",  AUTOSHEET_FEEDER},
  {"IP4200",  AUTOSHEET_FEEDER},
  {"IP7500",  AUTOSHEET_FEEDER},
  {"IP6600D", AUTOSHEET_FEEDER},
  {"MP500",   AUTOSHEET_FEEDER},
  {"IP3300",  AUTOSHEET_FEEDER},
  {"IP4300",  AUTOSHEET_FEEDER},
  {"MP510",   AUTOSHEET_FEEDER},
  {"MP600",   AUTOSHEET_FEEDER},
  {"MP160",   AUTOSHEET_FEEDER},
  {"IP2500",  AUTOSHEET_FEEDER},
  {"IP1800",  AUTOSHEET_FEEDER},
  {"IP90",    AUTOSHEET_FEEDER},
  {"IP4500",  REAR_TRAY},
  {"IP3500",  REAR_TRAY},
  {"MP610",   REAR_TRAY},
  {"MP520",   REAR_TRAY},
  {"MP140",   REAR_TRAY},
  {"MP210",   REAR_TRAY},
  {ENDTAG, 0}
};

//Ver.2.70
static const
ST_FRONTSUPPLAY_TBL frontsupply_tbl[]={
  {"IP2200",  NO_SUPPLY},
  {"IP4200",  CASSEETTE},
  {"IP7500",  CASSEETTE},
  {"IP6600D", CASSEETTE},
  {"MP500",   CASSEETTE},
  {"IP3300",  FRONT_FEEDER},
  {"IP4300",  CASSEETTE},
  {"MP510",   FRONT_FEEDER},
  {"MP600",   CASSEETTE},
  {"MP160",   NO_SUPPLY},
  {"IP2500",  NO_SUPPLY},
  {"IP1800",  NO_SUPPLY},
  {"IP90",    NO_SUPPLY},
  {"IP4500",  CASSEETTE},
  {"IP3500",  FRONT_TRAY},
  {"MP610",   CASSEETTE},
  {"MP520",   FRONT_TRAY},
  {"MP140",   NO_SUPPLY},
  {"MP210",   NO_SUPPLY},
  {ENDTAG, 0}
};

//Ver.2.70
static const
ST_RESUMEBUTTON_TBL rsm_button_tbl[]={
  {"IP2200",  IS_RESUME},
  {"IP4200",  IS_RESUME},
  {"IP7500",  IS_RESUME},
  {"IP6600D", IS_RESUME},
  {"MP500",   IS_OK},
  {"IP3300",  IS_RESUME},
  {"IP4300",  IS_RESUME},
  {"MP510",   IS_OK},
  {"MP600",   IS_OK},
  {"MP160",   IS_START},
  {"IP2500",  IS_RESUME},
  {"IP1800",  IS_RESUME},
  {"IP90",    IS_RESUME},
  {"IP4500",  IS_RESUME},
  {"IP3500",  IS_RESUME},
  {"MP610",   IS_OK},
  {"MP520",   IS_OK},
  {"MP140",   IS_START},
  {"MP210",   IS_START},
  {ENDTAG, 0}
};


static const
ST_MSGTBL cartridge_type[]={
  {'U', ID_STS_MESSAGE_OC_BLACK30},
  {'V', ID_STS_MESSAGE_OC_COLOR31},
  {'L', ID_STS_MESSAGE_OC_BLACK70},
  {'M', ID_STS_MESSAGE_OC_COLOR71},
  {'N', ID_STS_MESSAGE_OC_BLACK90},
  {'O', ID_STS_MESSAGE_OC_COLOR91},
  {ENDTAG, 0}
};

ST_MSGTBL cartridge_type_OTH[]={
  {'U', ID_STS_MESSAGE_OC_BLACK30},
  {'V', ID_STS_MESSAGE_OC_COLOR31},
  {'L', ID_STS_MESSAGE_OC_BLACK40},
  {'M', ID_STS_MESSAGE_OC_COLOR41},
  {'N', ID_STS_MESSAGE_OC_BLACK50},
  {'O', ID_STS_MESSAGE_OC_COLOR51},
  {ENDTAG, 0}
};

ST_MSGTBL cartridge_type_ASI[]={
  {'U', ID_STS_MESSAGE_OC_BLACK830},
  {'V', ID_STS_MESSAGE_OC_COLOR831},
  {'L', ID_STS_MESSAGE_OC_BLACK40},
  {'M', ID_STS_MESSAGE_OC_COLOR41},
  {'N', ID_STS_MESSAGE_OC_BLACK50},
  {'O', ID_STS_MESSAGE_OC_COLOR51},
  {ENDTAG, 0}
};

ST_MSGTBL cartridge_type_PAM[]={
  {'U', ID_STS_MESSAGE_OC_BLACK30},
  {'V', ID_STS_MESSAGE_OC_COLOR31},
  {'L', ID_STS_MESSAGE_OC_BLACK40},
  {'M', ID_STS_MESSAGE_OC_COLOR41},
  {'N', ID_STS_MESSAGE_OC_BLACK50},
  {'O', ID_STS_MESSAGE_OC_COLOR51},
  {ENDTAG, 0}
};

ST_MSGTBL cartridge_type_EU[]={
  {'U', ID_STS_MESSAGE_OC_BLACK37},
  {'V', ID_STS_MESSAGE_OC_COLOR38},
  {'L', ID_STS_MESSAGE_OC_BLACK40},
  {'M', ID_STS_MESSAGE_OC_COLOR41},
  {'N', ID_STS_MESSAGE_OC_BLACK50},
  {'O', ID_STS_MESSAGE_OC_COLOR51},
  {ENDTAG, 0}
};

static const
ST_REGION_TBL cartridge_region_tbl[]={
  {'J', cartridge_type},
  {'O', cartridge_type_OTH},
  {'A', cartridge_type_ASI},
  {'P', cartridge_type_PAM},
  {'E', cartridge_type_EU},
  {ENDTAG, 0}
};


static const
ST_MSGTBL color_ip2200_type[]={
  {'B', ID_STS_MESSAGE_COLOR_CARTRIDGE},
  {'E', ID_STS_MESSAGE_COLOR_CARTRIDGE},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_ip2200[]={
  {'B', ID_STS_MESSAGE_OC_BLACK},
  {'E', ID_STS_MESSAGE_OC_COLOR},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_type_JP[]={
  {'L', ID_STS_MESSAGE_OC_BLACK7e},
  {'l', ID_STS_MESSAGE_OC_PHOTO_BLACK9},
  {'C', ID_STS_MESSAGE_OC_CYAN7e},
  {'M', ID_STS_MESSAGE_OC_MAGENTA7e},
  {'Y', ID_STS_MESSAGE_OC_YELLOW7e},
  {'c', ID_STS_MESSAGE_OC_PHOTO_CYAN7e},
  {'m', ID_STS_MESSAGE_OC_PHOTO_MAGENTA7e},
  {'B', ID_STS_MESSAGE_OC_BLACKyy},
  {'G', ID_STS_MESSAGE_OC_COLORyy},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_type_OTH[]={
  {'L', ID_STS_MESSAGE_OC_BLACK8},
  {'l', ID_STS_MESSAGE_OC_PHOTO_BLACK5},
  {'C', ID_STS_MESSAGE_OC_CYAN8},
  {'M', ID_STS_MESSAGE_OC_MAGENTA8},
  {'Y', ID_STS_MESSAGE_OC_YELLOW8},
  {'c', ID_STS_MESSAGE_OC_PHOTO_CYAN8},
  {'m', ID_STS_MESSAGE_OC_PHOTO_MAGENTA8},
  {'B', ID_STS_MESSAGE_OC_BLACKxx},
  {'G', ID_STS_MESSAGE_OC_COLORxx},
  {ENDTAG, 0}
};

static const
ST_REGION_TBL ink_region_tbl[]={
  {'J', color_type_JP},
  {'O', color_type_OTH},
  {ENDTAG, 0}
};


static const
ST_MSGTBL color_ip4200[]={
  {'L', ID_STS_MESSAGE_COLOR_TYPE},
  {'l', ID_STS_MESSAGE_COLOR_TYPE},
  {'Y', ID_STS_MESSAGE_COLOR_TYPE},
  {'M', ID_STS_MESSAGE_COLOR_TYPE},
  {'C', ID_STS_MESSAGE_COLOR_TYPE},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_ip6600d[]={
  {'L', ID_STS_MESSAGE_COLOR_TYPE},
  {'C', ID_STS_MESSAGE_COLOR_TYPE},
  {'c', ID_STS_MESSAGE_COLOR_TYPE},
  {'M', ID_STS_MESSAGE_COLOR_TYPE},
  {'m', ID_STS_MESSAGE_COLOR_TYPE},
  {'Y', ID_STS_MESSAGE_COLOR_TYPE},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_ip7500[]={
  {'L', ID_STS_MESSAGE_COLOR_TYPE},
  {'c', ID_STS_MESSAGE_COLOR_TYPE},
  {'l', ID_STS_MESSAGE_COLOR_TYPE},
  {'M', ID_STS_MESSAGE_COLOR_TYPE},
  {'C', ID_STS_MESSAGE_COLOR_TYPE},
  {'m', ID_STS_MESSAGE_COLOR_TYPE},
  {'Y', ID_STS_MESSAGE_COLOR_TYPE},
  {ENDTAG, 0}
};
  
ST_MSGTBL color_ip3300[]={
  {'l', ID_STS_MESSAGE_COLOR_TYPE},
  {'C', ID_STS_MESSAGE_COLOR_TYPE},
  {'M', ID_STS_MESSAGE_COLOR_TYPE},
  {'Y', ID_STS_MESSAGE_COLOR_TYPE},
  {ENDTAG, 0}
};

ST_MSGTBL color_ip90[]={
  {'B', ID_STS_MESSAGE_COLOR_TYPE},
  {'G', ID_STS_MESSAGE_COLOR_TYPE},
  {ENDTAG, 0}
};

static const
ST_DEVCLR_TBL color_tbl_inkout[]={
  {"IP2200",  color_ip2200_type},
  {"IP4200",  color_ip4200},
  {"IP7500",  color_ip7500},
  {"IP6600D", color_ip6600d},
  {"MP500",   color_ip4200},
  {"IP3300",  color_ip3300},
  {"IP4300",  color_ip4200},
  {"MP510",   color_ip3300},
  {"MP600",   color_ip4200},
  {"MP160",   color_ip2200_type},
  {"IPxxxx",  color_ip2200},
  {"IP2500",  color_ip2200_type},
  {"IP1800",  color_ip2200_type},
  {"IP90",    color_ip90},
  {"IP4500",  color_ip4200},
  {"IP3500",  color_ip3300},
  {"MP610",   color_ip4200},
  {"MP520",   color_ip3300},
  {"MP140",   color_ip2200_type},
  {"MP210",   color_ip2200_type},
  {ENDTAG, 0}
};

static const
ST_OPMSGTBL msg_tbl_inkout[]={
  {ID_STS_MESSAGE_OC_INKOUT_TANK2,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_INKOUT06_TANK, //don't use, so ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP OK
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'I'}, 

  {ID_STS_MESSAGE_OC_INKEMPTY06_TANK_1st,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, //don't use, so ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP OK
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'Y'}, 

  {ID_STS_MESSAGE_OC_INKEMPTY0602_TANK_1st,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, //don't use, so ID_STS_MESSAGE_OC_INKEMPTY0602_TANK_3rd OK
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'r'}, 

  {ID_STS_MESSAGE_OC_INKOUT_CART,
     {ID_STS_MESSAGE_OC_INKEMPTY06_TANK_1st,
      ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_INKOUT_CART_3rd,
      ID_STS_MESSAGE_NON},
     'I'}, 

  {ID_STS_MESSAGE_OC_INKOUT_CART,
     {ID_STS_MESSAGE_OC_INKEMPTY06_TANK_1st,
      ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_INKOUT_CART_3rd,
      ID_STS_MESSAGE_NON},
     'M'}, 

  {ID_STS_MESSAGE_OC_INKOUT_CART,
     {ID_STS_MESSAGE_OC_INKEMPTY06_TANK_1st,
      ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_INKOUT_CART_3rd,
      ID_STS_MESSAGE_NON},
     'm'}, 

  {ID_STS_MESSAGE_NON,
     {ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     ENDTAG}, 
};


static const
ST_DEVCLR_TBL color_tbl_op3[]={
  {"IP2200",  color_ip2200},
  {"IP4200",  color_ip4200},
  {"IP7500",  color_ip7500},
  {"IP6600D", color_ip6600d},
  {"MP500",   color_ip4200},
  {"IP3300",  color_ip3300},
  {"IP4300",  color_ip4200},
  {"MP510",   color_ip3300},
  {"MP600",   color_ip4200},
  {"MP160",   color_ip2200},
  {"IPxxxx",  color_ip2200},
  {"IP2500",  color_ip2200},
  {"IP1800",  color_ip2200},
  {"IP90",    color_ip2200},
  {"IP4500",  color_ip4200},
  {"IP3500",  color_ip3300},
  {"MP610",   color_ip4200},
  {"MP520",   color_ip3300},
  {"MP140",   color_ip2200},
  {"MP210",   color_ip2200},
  {ENDTAG, 0}
};

static const
ST_OPMSGTBL msg_tbl_op3[]={
  {ID_STS_MESSAGE_OC_PLURALERROR_TANK,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_PLURALERROR_TANK_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'M'}, 

  {ID_STS_MESSAGE_OC_DIFFERENT_REGION_TANK,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_UNINSTALLATION_TANK_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'E'}, 

  {ID_STS_MESSAGE_OC_POSITION_MISMACH_TANK,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'P'}, 

  {ID_STS_MESSAGE_OC_UNINSTALLATION_TANK,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_UNINSTALLATION_TANK_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'E'}, 

  {ID_STS_MESSAGE_INKSTATUS_OFF,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'Z'}, 

  {ID_STS_MESSAGE_OC_REFILL,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_REFILL_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'R'}, 

  {ID_STS_MESSAGE_OC_REFILL2,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_REFILL2_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'R'}, 

  {ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'E'}, 

  {ID_STS_MESSAGE_OC_REMAIN_UNKNOWN1,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_REMAIN_UNKNOWN1_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'R'}, 

  {ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'R'}, 

  {ID_STS_MESSAGE_OC_TANK_NO_BK,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     '*'}, 

  {ID_STS_MESSAGE_OC_TANK_NO_CL,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     '*'}, 

  {ID_STS_MESSAGE_NON,
     {ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     ENDTAG}, 
};

/*
 * The following functions exist in order to set the corresponding message ID.
 */


/*
 * In a service call, other processings are not performed.
 */
int chk_servicecall(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  if(p_tbl->service_call[0]==SPACE){
    return(ID_ERR_NO_ERROR);
  }

  ret=processIDcheck(&service[0], p_tbl->service_call, sizeof(p_tbl->service_call) );
  if(ret == ID_ERR_MEM_ALLOC_FAILED){
    return(ret);
  }
  else if(ret != IDNOTFOUND){
    ret=storeMessageID(p_sts, ret);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
    return(SERVICECALL);
  }
  else{
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_SC_SERVICE_ERROR_PRE);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_SC_SERVICE_ERROR_AFTER);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
    return(SERVICECALL);
  }
  return(ret);
}


/*
 * The number of what is displayed among the message ID acquired
 * with the following functions is one. (Except ink out)
 *
 * chk_operatorcall_level1();
 * chk_operatorcall_cartridge();
 * chk_operatorcall_level2();
 * chk_inkout();
 * chk_operatorcall_level3();
 * chk_operatorcall_level4();
 * chk_busystatus();
 * chk_cartridge();
 * chk_basestatus();
 * chk_warning();
 */
int chk_operatorcall_level1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;
  int msgid;
  int is_rearsupply = ID_ERR_NO_ERROR;
  int is_frontsupply = ID_ERR_NO_ERROR;
  int rsm_button = IS_RESUME;


  // Rear Supply for Ver.2.80
  is_rearsupply = setRearSupplyID(p_tbl);
  if( is_rearsupply == ID_ERR_NO_ERROR )
    return ID_ERR_NO_ERROR;

  // Front Supply for Ver.2.80
  is_frontsupply = setFrontSupplyID(p_tbl);
  if( is_frontsupply == ID_ERR_NO_ERROR )
    return ID_ERR_NO_ERROR;

  // Resume/OK/Start Button for Ver.2.70
  rsm_button = setButtonID(p_tbl);
  if( rsm_button == ID_ERR_NO_ERROR )
    return ID_ERR_NO_ERROR;

  ret=processstandardmsgcheck(p_sts, &operatelevel1[0], p_tbl->operator_call, sizeof(p_tbl->operator_call));
  
  //Ver.2.80 Change
  if( *(p_sts->pMessageID) == ID_STS_MESSAGE_CARTRIDGE_NONE )		// v2.4
  //if( *(p_sts->pMessageID) == ID_STS_MESSAGE_OC_CARTRIDGE_NONE )		// v2.4
  {
    if ( strncmp(p_tbl->dev, DEV_1284,4) )		// v2.4
      *(p_sts->pMessageID)=ID_STS_MESSAGE_CARTRIDGE_NONE;		// v2.4
    //2.00.01.010 NoCartridge:other message doesn't appear except battery low
    return UNIQUESTS;
	//ret = OTHERMESSAGENO;
  }	       
  //Operator Call Error
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_HEAD_ERROR 	|| 
			*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_HEAD_ERROR2 ){
		//Ver.2.70
	  	if( rsm_button == IS_OK )
	  		 *(p_sts->pMessageID)=ID_STS_MESSAGE_OC_HEAD_ERROR2;
	  	else if( rsm_button == IS_START )
	  		 *(p_sts->pMessageID)=ID_STS_MESSAGE_OC_HEAD_ERROR_START;
	  	else
	  		 *(p_sts->pMessageID)=ID_STS_MESSAGE_OC_HEAD_ERROR;
      // *(p_sts->pMessageID)=ID_STS_MESSAGE_OC_HEAD_ERROR_START;
  }

  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_OUT21 	|| 
			*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_OUT22	||
			*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_OUT)
  {
  	msgid = *(p_sts->pMessageID);

	//Ver.2.70
  	if( (is_frontsupply == FRONT_FEEDER) && (msgid == ID_STS_MESSAGE_OC_PAPER_OUT22) )
  		msgid = ID_STS_MESSAGE_OC_PAPER_OUT42;
	//Ver.2.80
  	if( (is_frontsupply == FRONT_TRAY) && (msgid == ID_STS_MESSAGE_OC_PAPER_OUT22) )
  		msgid = ID_STS_MESSAGE_OC_PAPER_OUT42FT;
	//Ver.2.80
  	if( (is_rearsupply == REAR_TRAY) && (msgid == ID_STS_MESSAGE_OC_PAPER_OUT21) )
  		msgid = ID_STS_MESSAGE_OC_PAPER_OUT21RT;

	*p_sts->pMessageID = ID_STS_MESSAGE_OC_PAPER_OUT1;
  	ret = storeMessageID (p_sts, msgid);
	//Ver.2.70
  	if( rsm_button == IS_OK )
  		ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_OUT33);
  	else if( rsm_button == IS_START )
  		ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_OUT_START);
  	else
		ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_OUT3);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM1 || *(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM1_2nd);
	//Ver.2.70
  	if( rsm_button == IS_OK )
  		ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM2_3rd);
  	else if( rsm_button == IS_START )
  		ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM2_START);
  	else
		ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM1_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM03)
  {
	//Ver.2.70
  	if( is_frontsupply == FRONT_FEEDER )
  		ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM03_2ndFF);
	else if( is_frontsupply == FRONT_TRAY)
  		ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM03_2ndFT);
  	else
		ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM03_2nd);

	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM1_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM04)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM04_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM1_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM2)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM1_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM2_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM05)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM05_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM2_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM06)
  {
	//Ver.2.70
  	msgid = ID_STS_MESSAGE_OC_PAPER_JAM03_2nd;
  	if( is_frontsupply == FRONT_FEEDER )
  		msgid = ID_STS_MESSAGE_OC_PAPER_JAM03_2ndFF;
	//Ver.2.80
  	else if( is_frontsupply == FRONT_TRAY )
  		msgid = ID_STS_MESSAGE_OC_PAPER_JAM03_2ndFT;

  	ret = storeMessageID (p_sts, msgid);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM2_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM07)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM04_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM2_3rd);
	ret = UNIQUESTS;
  }

  return(ret);
}


int chk_operatorcall_cartridge(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
#if 0
  int i;
  int ret;
  int msg=-1;

  for(i=0; i<sizeof(p_tbl->operator_call); i++){
    if(*(p_tbl->operator_call+i) == SCANNERDETECT){
      if(p_tbl->busy_stat != TESTPRINTNOW){
		msg=ID_STS_MESSAGE_OC_CARTRIDGE_SCANNER;
      }
      else{
		msg=ID_STS_MESSAGE_CARTRIDGE_SCANNER;
      }
      ret=storeMessageID(p_sts, msg);
      if(ret != ID_ERR_NO_ERROR){
		return(ret);
      }
      return(UNIQUESTS);
    }
  }
#endif
  return(ID_ERR_NO_ERROR);
}


int chk_operatorcall_level2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;
  int rsm_button = IS_RESUME;
  int color;

  ret=processstandardmsgcheck(p_sts, &operatelevel2[0], p_tbl->operator_call, sizeof(p_tbl->operator_call));

   // The corresponding color is acquired.
   for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
     if( !strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
       break;
   if(color_tbl_inkout[color].pr_name == ENDTAG)
   {
     p_sts->messageNum = 0;
     *(p_sts->pMessageID) = 0;
     return ID_ERR_NO_ERROR;
   }

   if( color_tbl_inkout[color].color[0].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE
    && *(p_sts->pMessageID) == ID_STS_MESSAGE_OC_INKTANK_NOTPROPERLY )
		*p_sts->pMessageID = ID_STS_MESSAGE_OC_CARTRIDGE_NOTPROPERLY;

  // Resume/OK/Start Button for Ver.2.70
  rsm_button = setButtonID(p_tbl);
  if( rsm_button == ID_ERR_NO_ERROR )
    return ID_ERR_NO_ERROR;
    
  if( *(p_sts->pMessageID) == ID_STS_MESSAGE_OC_USEDTANK_ALMOST
   || *(p_sts->pMessageID) == ID_STS_MESSAGE_OC_USEDTANK_ALMOST2 )
  {
	  switch( rsm_button ){
	  	case IS_OK:
			if( p_tbl->destination == ID_HRI_JPN )
				*p_sts->pMessageID = ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP2;
			//else
			//	*p_sts->pMessageID = *p_sts->pMessageID;
	  	break;
	  	
	  	case IS_START:
			if( p_tbl->destination == ID_HRI_JPN )
				*p_sts->pMessageID = ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP_START;
			else
				*p_sts->pMessageID = ID_STS_MESSAGE_OC_USEDTANK_ALMOST_START;
	  	break;
	  	
	  	case IS_RESUME:
			if( p_tbl->destination == ID_HRI_JPN )
				*p_sts->pMessageID = ID_STS_MESSAGE_OC_USEDTANK_ALMOSTJP;
			//else
			//	*p_sts->pMessageID = *p_sts->pMessageID;
	  	break;
	  
	  	default:
	  	break;
	  }
  }

  return(ret);
}


int chk_inkout(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int 		ret;
  int 		msgid,third_msgid,fourth_msgid=ID_STS_MESSAGE_NON;
  int 		color;
  int  		i, j, k, m, x;
  int		EMPTYIO_flag = 0;
  int		tmpMessageID;
  int		rsm_button = IS_RESUME;

  // The first message is inserted.
  ret=processstandardmsgcheck(p_sts, inkout, p_tbl->operator_call, sizeof(p_tbl->operator_call));
    if(ret==ID_ERR_NO_ERROR)
    return ID_ERR_NO_ERROR;

  // Resume/OK/Start Button for Ver.2.70
  rsm_button = setButtonID(p_tbl);
  if( rsm_button == ID_ERR_NO_ERROR )
    return ID_ERR_NO_ERROR;

  //for Ver.2.70
  for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
    if(	!strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
      break;

  //for independent ink
  if ( (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_INKOUT06_TANK) ||
      (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP) ||
      (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_INKEMPTY0602_TANK_3rd) ||
      (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd) ) {

	third_msgid = *(p_sts->pMessageID);

    //Ver.2.70  
    if( (rsm_button == IS_OK) && (third_msgid  == ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd) && ( color_tbl_inkout[color].color[0].msgid != ID_STS_MESSAGE_COLOR_CARTRIDGE ) )
    	third_msgid = ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP;
    //for MP140/210
    //not support for MP160
    else if( (rsm_button == IS_START) && (third_msgid  == ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd) && ( color_tbl_inkout[color].color[0].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE ) ){
		/* Ver.2.80 for B-53 Stop/Reset */
    	third_msgid = ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET;
    	//third_msgid = ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_START;
    	/* not support Ver.2.80 */
    	/* fourth_msgid = ID_STS_MESSAGE_OC_INKOUT_CART_3rd; */
    }
    //for iP2500
    else if( (rsm_button == IS_RESUME) && (third_msgid  == ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd) && ( color_tbl_inkout[color].color[0].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE ) ){
    	third_msgid = ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE;
    	/* not support Ver.2.80 */
    	/* fourth_msgid = ID_STS_MESSAGE_OC_INKOUT_CART_3rd; */
    }


	//first message is may have run out
	if( (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_INKOUT06_TANK) || 	//INK OUT
        (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP) ){
		*p_sts->pMessageID = ID_STS_MESSAGE_OC_INKOUT_TANK2;
	}
	else if( (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd) ){
		*p_sts->pMessageID = ID_STS_MESSAGE_OC_INKEMPTY06_TANK_1st;
	}
	else if( (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_INKEMPTY0602_TANK_3rd) ){
		*p_sts->pMessageID = ID_STS_MESSAGE_OC_INKEMPTY0602_TANK_1st;
	}

	msgid = *(p_sts->pMessageID);

   // The corresponding color is acquired.
   for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
     if( !strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
       break;
   if(color_tbl_inkout[color].pr_name == ENDTAG)
   {
     p_sts->messageNum = 0;
     *(p_sts->pMessageID) = 0;
     return ID_ERR_NO_ERROR;
   }

	//second message is color
	  // The corresponding message is acquired.
	  for(msgid=0; msg_tbl_inkout[msgid].msgid!=ID_STS_MESSAGE_NON; msgid++)
	    if(*(p_sts->pMessageID)==msg_tbl_inkout[msgid].msgid)
	      break;
	  if(msg_tbl_inkout[msgid].msgid == ID_STS_MESSAGE_NON)
	  {
	    p_sts->messageNum = 0;
	    *(p_sts->pMessageID) = 0;
	    return ID_ERR_NO_ERROR;
	  }
	
	  // The corresponding color is acquired.
	  for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
	    if(	!strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
	      break;
	  if(color_tbl_inkout[color].pr_name == ENDTAG)
	  {
	    p_sts->messageNum = 0;
	    *(p_sts->pMessageID) = 0;
	    return ID_ERR_NO_ERROR;
	  }
	
	  for(i=0; msg_tbl_inkout[msgid].id[i]!=ID_STS_MESSAGE_NON; i++)
	  {
	    if(msg_tbl_inkout[msgid].id[i] == ID_STS_MESSAGE_COLOR)
	    {
	      // The message since the second (color) is inserted.
	      for(j=0; j<MAXINKNUM; j++)
	      {
			//printf("p_tbl->ink[j].alert = %s\n", &p_tbl->ink[j].alert);
			//printf("msg_tbl_inkout[msgid].status = %s\n", &msg_tbl_inkout[msgid].status);
	        //check EMPTY && Inkout
	        if( msg_tbl_inkout[msgid].status == 'Y' && p_tbl->ink[j].alert == 'I' )
	        	EMPTYIO_flag = 1;
	        
	        if(p_tbl->ink[j].alert == msg_tbl_inkout[msgid].status)
	        {
	          for(k=0; color_tbl_inkout[color].color[k].status!=ENDTAG; k++)
	            if(p_tbl->ink[j].color == color_tbl_inkout[color].color[k].status)
	              break;

	          if(color_tbl_inkout[color].color[k].status==ENDTAG)
	          {
	            p_sts->messageNum = 0;
	            *(p_sts->pMessageID) = 0;
	            return ID_ERR_NO_ERROR;
	          }
	
	          if(color_tbl_inkout[color].color[k].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE)
	          {
	            for(k=0; cartridge_type[k].status!=ENDTAG; k++)
	              if(p_tbl->cartridge[j].type == cartridge_type[k].status)
	                break;

				//Ver.2.70
	            for(m=0; cartridge_region_tbl[m].region[k].status!=ENDTAG; m++){
					if( cartridge_region_tbl[m].status == p_tbl->destination ){
					break;
					}
				}
				
				ret=storeMessageID(p_sts, cartridge_region_tbl[m].region[k].msgid);

	            if(ret != ID_ERR_NO_ERROR)
		          return(ret);
	          }
	          else if(color_tbl_inkout[color].color[k].msgid == ID_STS_MESSAGE_COLOR_TYPE)
	          {
				//deciede x : color
		        for(x=0; ink_region_tbl[0].region[x].status!=ENDTAG; x++){
					if( ink_region_tbl[0].region[x].status == color_tbl_inkout[color].color[k].status )
						break;
				}
				//deciede m : region
		        for(m=0; ink_region_tbl[m].region[x].status!=ENDTAG; m++){
		        //for(m=0; ink_region_tbl[m].region[k].status!=ENDTAG; m++){
					if( ink_region_tbl[m].status == p_tbl->destination )
						break;
				}
				ret=storeMessageID(p_sts, ink_region_tbl[m].region[x].msgid);
		          if(ret != ID_ERR_NO_ERROR)
	                return ret;
	          }
	          else
	          {
	  	        ret=storeMessageID(p_sts, color_tbl_inkout[color].color[k].msgid);
		        if(ret != ID_ERR_NO_ERROR)
	              return ret;
	          }
	        }
	      }
	    }
	    else
	    {
	      //third message is Inkout
	      // The message since the second (Excluding the color) is inserted.
		  ret = storeMessageID (p_sts, third_msgid);
		  if(ret != ID_ERR_NO_ERROR)
	        return ret;
		  //for Ver.2.70
		  ret = storeMessageID (p_sts, fourth_msgid);
		  if(ret != ID_ERR_NO_ERROR)
	        return ret;
	    }
	  }
  } 
  //for independent ink


  //for Dispo Ink
  else {

	  // The corresponding message is acquired.
	  for(msgid=0; msg_tbl_inkout[msgid].msgid!=ID_STS_MESSAGE_NON; msgid++)
	    if(*(p_sts->pMessageID)==msg_tbl_inkout[msgid].msgid)
	      break;
	  if(msg_tbl_inkout[msgid].msgid == ID_STS_MESSAGE_NON)
	  {
	    p_sts->messageNum = 0;
	    *(p_sts->pMessageID) = 0;
	    return ID_ERR_NO_ERROR;
	  }
	 
	  //MFP : OK button
	  if( rsm_button == IS_OK )
	  {
	  	*(p_sts->pMessageID) = ID_STS_MESSAGE_OC_INKOUT_CART_MFP;
	  }
	  else if( rsm_button == IS_START )
	  {
	  	*(p_sts->pMessageID) = ID_STS_MESSAGE_OC_INKOUT_CART_START;
	  }
	  
	  // The corresponding color is acquired.
	  for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
	    if(	!strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
	      break;
	  if(color_tbl_inkout[color].pr_name == ENDTAG)
	  {
	    p_sts->messageNum = 0;
	    *(p_sts->pMessageID) = 0;
	    return ID_ERR_NO_ERROR;
	  }
	
	  for(i=0; msg_tbl_inkout[msgid].id[i]!=ID_STS_MESSAGE_NON; i++)
	  {
	    if(msg_tbl_inkout[msgid].id[i] == ID_STS_MESSAGE_COLOR)
	    {
	      // The message since the second (color) is inserted.
	      for(j=0; j<MAXINKNUM; j++)
	      {
			//printf("p_tbl->ink[j].alert = %s\n", &p_tbl->ink[j].alert);
			//printf("msg_tbl_inkout[msgid].status = %s\n", &msg_tbl_inkout[msgid].status);
	        //check EMPTY && Inkout
	        if( msg_tbl_inkout[msgid].status == 'Y' && p_tbl->ink[j].alert == 'I' )
	        	EMPTYIO_flag = 1;
	        
	        if(p_tbl->ink[j].alert == msg_tbl_inkout[msgid].status)
	        {
	          for(k=0; color_tbl_inkout[color].color[k].status!=ENDTAG; k++)
	            if(p_tbl->ink[j].color == color_tbl_inkout[color].color[k].status)
	              break;
	          if(color_tbl_inkout[color].color[k].status==ENDTAG)
	          {
	            p_sts->messageNum = 0;
	            *(p_sts->pMessageID) = 0;
	            return ID_ERR_NO_ERROR;
	          }
	
	          if(color_tbl_inkout[color].color[k].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE)
	          {
	            for(k=0; cartridge_type[k].status!=ENDTAG; k++)
	              if(p_tbl->cartridge[j].type == cartridge_type[k].status)
	                break;

				//Ver.2.70
	            for(m=0; cartridge_region_tbl[m].region[k].status!=ENDTAG; m++){
					if( cartridge_region_tbl[m].status == p_tbl->destination )
					break;
				}
				
				ret=storeMessageID(p_sts, cartridge_region_tbl[m].region[k].msgid);

		        if(ret != ID_ERR_NO_ERROR)
	              return ret;
	          }
	          else if(color_tbl_inkout[color].color[k].msgid == ID_STS_MESSAGE_COLOR_TYPE)
	          {
				//Ver.2.70
		        for(m=0; ink_region_tbl[m].region[k].status!=ENDTAG; m++){
					if( ink_region_tbl[m].status == p_tbl->destination )
						break;
				}
				ret=storeMessageID(p_sts, ink_region_tbl[m].region[k].msgid);
		          if(ret != ID_ERR_NO_ERROR)
	                return ret;
	          }
	          else
	          {
	  	        ret=storeMessageID(p_sts, color_tbl_inkout[color].color[k].msgid);
		        if(ret != ID_ERR_NO_ERROR)
	              return ret;
	          }
	        }
	      }
	    }
	    else
	    {
	      // The message since the second (Excluding the color) is inserted.
		  //for 1 cartridge
		  //if( (msg_tbl_inkout[msgid].id[i] == ID_STS_MESSAGE_OC_INKOUT_CART_3rd) && (p_tbl->cartridge[0].type == SPACE) )
		  //	ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_PREPARE_NEW_CARTRIDGE);
		  //else
		  ret=storeMessageID(p_sts, msg_tbl_inkout[msgid].id[i]);
		  
		  if(ret != ID_ERR_NO_ERROR)
	        return ret;
	    }
	  }
   }
   //for set Ink

	//Ver.2.70
	tmpMessageID = *(p_sts->pMessageID);

	if(EMPTYIO_flag == 1){
		ret = chk_inkout_DOCEMPTY_CTKIO(p_tbl, p_sts);
		*(p_sts->pMessageID) = tmpMessageID;
	}

	if(ret != ID_ERR_NO_ERROR)
		return ret;

  return UNIQUESTS;
}


//for Ver.2.70
//DOC 1688(EMPTY) && CTK:IO
//Operator Call 'C' only
int chk_inkout_DOCEMPTY_CTKIO(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int 		ret;
  int 		msgid,third_msgid;
  int 		color;
  int  		i, j, k, m, x;
  int		IO_Flag = 0;
  //2.00.01.12 FIX
  int rsm_button = IS_RESUME;

    //2.00.01.010 search 'C' because (Inkout && Cover Open) ---> 'vC'
    for(k=0; (k<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+k)!=SPACE); k++){
		if( p_tbl->operator_call[k] == 'C' ){
	    	IO_Flag = 1;
	    }
    }

   //2.00.01.12 FIX
   // Resume/OK/Start Button for Ver.2.70
   rsm_button = setButtonID(p_tbl);
   if( rsm_button == ID_ERR_NO_ERROR )
     return ID_ERR_NO_ERROR;

    //2.00.01.12 FIX
	if( IO_Flag == 1 ){
    	if( rsm_button == IS_OK )
	        *(p_sts->pMessageID) = ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP;
		else
	        *(p_sts->pMessageID) = ID_STS_MESSAGE_OC_INKOUT06_TANK;
    }
    //2.00.01.010
	//if( IO_Flag == 1 )
    //    *(p_sts->pMessageID) = ID_STS_MESSAGE_OC_INKOUT06_TANK;

  // The first message is inserted.
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_INKOUT_TANK2);
	if(ret != ID_ERR_NO_ERROR)
		return ret;

	third_msgid = *(p_sts->pMessageID);
	*(p_sts->pMessageID) = ID_STS_MESSAGE_OC_INKOUT_TANK2;

	msgid = *(p_sts->pMessageID);

   // The corresponding color is acquired.
   for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
     if( !strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
       break;
   if(color_tbl_inkout[color].pr_name == ENDTAG)
   {
     p_sts->messageNum = 0;
     *(p_sts->pMessageID) = 0;
     return ID_ERR_NO_ERROR;
   }

	//second message is color
	  // The corresponding message is acquired.
	  for(msgid=0; msg_tbl_inkout[msgid].msgid!=ID_STS_MESSAGE_NON; msgid++)
	    if(*(p_sts->pMessageID)==msg_tbl_inkout[msgid].msgid)
	      break;
	  if(msg_tbl_inkout[msgid].msgid == ID_STS_MESSAGE_NON)
	  {
	    p_sts->messageNum = 0;
	    *(p_sts->pMessageID) = 0;
	    return ID_ERR_NO_ERROR;
	  }

	  // The corresponding color is acquired.
	  for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
	    if(	!strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
	      break;
	  if(color_tbl_inkout[color].pr_name == ENDTAG)
	  {
	    p_sts->messageNum = 0;
	    *(p_sts->pMessageID) = 0;
	    return ID_ERR_NO_ERROR;
	  }
	
	  for(i=0; msg_tbl_inkout[msgid].id[i]!=ID_STS_MESSAGE_NON; i++)
	  {
	    if(msg_tbl_inkout[msgid].id[i] == ID_STS_MESSAGE_COLOR)
	    {
	      // The message since the second (color) is inserted.
	      for(j=0; j<MAXINKNUM; j++)
	      {
			//printf("p_tbl->ink[j].alert = %s\n", &p_tbl->ink[j].alert);
			//printf("msg_tbl_inkout[msgid].status = %s\n", &msg_tbl_inkout[msgid].status);
	        if(p_tbl->ink[j].alert == msg_tbl_inkout[msgid].status)
	        {
	          for(k=0; color_tbl_inkout[color].color[k].status!=ENDTAG; k++)
	            if(p_tbl->ink[j].color == color_tbl_inkout[color].color[k].status)
	              break;
	          if(color_tbl_inkout[color].color[k].status==ENDTAG)
	          {
	            p_sts->messageNum = 0;
	            *(p_sts->pMessageID) = 0;
	            return ID_ERR_NO_ERROR;
	          }
	
	          if(color_tbl_inkout[color].color[k].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE)
	          {
	            for(k=0; cartridge_type[k].status!=ENDTAG; k++)
	              if(p_tbl->cartridge[j].type == cartridge_type[k].status)
	                break;

				//Ver.2.70
	            for(m=0; cartridge_region_tbl[m].region[k].status!=ENDTAG; m++){
					if( cartridge_region_tbl[m].status == p_tbl->destination )
					break;
				}
				
				ret=storeMessageID(p_sts, cartridge_region_tbl[m].region[k].msgid);

		        if(ret != ID_ERR_NO_ERROR)
	              return ret;
	          }
	          else if(color_tbl_inkout[color].color[k].msgid == ID_STS_MESSAGE_COLOR_TYPE)
	          {
				//deciede x : color
		        for(x=0; ink_region_tbl[0].region[x].status!=ENDTAG; x++){
					if( ink_region_tbl[0].region[x].status == color_tbl_inkout[color].color[k].status )
						break;
				}
				//deciede m : region
		        for(m=0; ink_region_tbl[m].region[x].status!=ENDTAG; m++){
		        //for(m=0; ink_region_tbl[m].region[k].status!=ENDTAG; m++){
					if( ink_region_tbl[m].status == p_tbl->destination )
						break;
				}
				ret=storeMessageID(p_sts, ink_region_tbl[m].region[x].msgid);
				//ret=storeMessageID(p_sts, ink_region_tbl[m].region[k].msgid);
		          if(ret != ID_ERR_NO_ERROR)
	                return ret;
	          }
	          else
	          {
	  	        ret=storeMessageID(p_sts, color_tbl_inkout[color].color[k].msgid);
		        if(ret != ID_ERR_NO_ERROR)
	              return ret;
	          }
	        }
	      }
	    }
	    else
	    {
	      //third message is Inkout
		  ret = storeMessageID (p_sts, third_msgid);
		  if(ret != ID_ERR_NO_ERROR)
	        return ret;
	    }
	  }
	  
  return UNIQUESTS;

}
//for Ver.2.70


int chk_operatorcall_level3(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;
  int msgid;
  int color;
  int i, j, k, m, x;
  int rsm_button = IS_RESUME;
  int is_inkremain_sequence = ID_ERR_NO_ERROR;

  // The first message is inserted.
  ret=processstandardmsgcheck(p_sts, operatelevel3, p_tbl->operator_call, sizeof(p_tbl->operator_call));
  if(ret==ID_ERR_NO_ERROR)
    return ID_ERR_NO_ERROR;

  // The corresponding message is acquired.
  for(msgid=0; msg_tbl_op3[msgid].msgid!=ID_STS_MESSAGE_NON; msgid++)
    if(*(p_sts->pMessageID)==msg_tbl_op3[msgid].msgid)
      break;
  if(msg_tbl_op3[msgid].msgid == ID_STS_MESSAGE_NON)
  {
    p_sts->messageNum = 0;
    *(p_sts->pMessageID) = 0;
    return ID_ERR_NO_ERROR;
  }

  // The corresponding color is acquired.
  for(color=0; color_tbl_op3[color].pr_name!=ENDTAG; color++)
    if(	!strncmp(p_tbl->pr_name, color_tbl_op3[color].pr_name, strlen(color_tbl_op3[color].pr_name)) ) 
      break;
  if(color_tbl_op3[color].pr_name == ENDTAG)
  {
    p_sts->messageNum = 0;
    *(p_sts->pMessageID) = 0;
    return ID_ERR_NO_ERROR;
  }

  //Ver.2.70
  // Resume/OK/Start Button for Ver.2.70
  rsm_button = setButtonID(p_tbl);
  if( rsm_button == ID_ERR_NO_ERROR )
    return ID_ERR_NO_ERROR;

  // Ink Remain Sequence for Ver.2.80
  is_inkremain_sequence = setInkRemainSequenceID(p_tbl);
  if( is_inkremain_sequence == ID_ERR_NO_ERROR )
    return ID_ERR_NO_ERROR;

  for(i=0; msg_tbl_op3[msgid].id[i]!=ID_STS_MESSAGE_NON; i++)
  {
    if(msg_tbl_op3[msgid].id[i] == ID_STS_MESSAGE_COLOR)
    {
      // The message since the second (color) is inserted.
      for(j=0; j<MAXINKNUM; j++)
      {
        if(p_tbl->ink[j].alert == msg_tbl_op3[msgid].status)
        {
          for(k=0; color_tbl_op3[color].color[k].status!=ENDTAG; k++)
            if(p_tbl->ink[j].color == color_tbl_op3[color].color[k].status)
              break;
          if(color_tbl_op3[color].color[k].status==ENDTAG)
          {
            p_sts->messageNum = 0;
            *(p_sts->pMessageID) = 0;
            return ID_ERR_NO_ERROR;
          }
          if(color_tbl_op3[color].color[k].msgid == ID_STS_MESSAGE_COLOR_TYPE)
          {
			//deciede x : color
	        for(x=0; ink_region_tbl[0].region[x].status!=ENDTAG; x++){
				if( ink_region_tbl[0].region[x].status == color_tbl_inkout[color].color[k].status )
					break;
			}

			//deciede m : region
	        for(m=0; ink_region_tbl[m].region[x].status!=ENDTAG; m++){
	        //for(m=0; ink_region_tbl[m].region[k].status!=ENDTAG; m++){
				if( ink_region_tbl[m].status == p_tbl->destination )
					break;
			}

			ret=storeMessageID(p_sts, ink_region_tbl[m].region[x].msgid);
	          if(ret != ID_ERR_NO_ERROR)
                return ret;
          }
          else
          {
	       //Initialize ret but one cartridge conditon is nessesary
	       //for 1 cartridge
	       //ret = ID_ERR_NO_ERROR;
	       //if( !((p_tbl->cartridge[k].type == SPACE) && (k == 0)) )
		    ret=storeMessageID(p_sts, color_tbl_op3[color].color[k].msgid);

	        if(ret != ID_ERR_NO_ERROR)
              return ret;
          }
       }
      }//End MAXINKNUM
      
      //Ver.2.70 for iP90 DOC:1661,1662
      //2.00.01.010 search 'M' and 'm' because (Tankout && Cover Open) ---> 'vMm'
      for(k=0; (k<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+k)!=SPACE); k++){
 	 	if( p_tbl->operator_call[k] == 'M' ){
		    ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_BLACKTANK);
	        if(ret != ID_ERR_NO_ERROR)
              return ret;
 	     }
	 	if( p_tbl->operator_call[k] == 'm' ){
		    ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_COLORTANK);
	        if(ret != ID_ERR_NO_ERROR)
              return ret;
 	     }
      }
      //Ver.2.70 for iP90 DOC:1661,1662
      
    }
    else
    {
      // The message since the second (Excluding the color) is inserted.
      //Ver.2.70  
      if( (rsm_button == IS_OK) && (msg_tbl_op3[msgid].id[i]  == ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd) )
         ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_MFP);
      else if( (rsm_button == IS_START) && (msg_tbl_op3[msgid].id[i]  == ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd) ){
         //for Ver.2.80
         if( is_inkremain_sequence == SPRING_07 )
         	ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING);
         else
         	ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START);
         //ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START);
         }
      else
 	     ret=storeMessageID(p_sts, msg_tbl_op3[msgid].id[i]);
	  if(ret != ID_ERR_NO_ERROR)
        return ret;
    }
  }
  return UNIQUESTS;
}


int chk_operatorcall_level4(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;
  
  if((p_tbl->operator_call[0]==SPACE) || (p_tbl->operator_call[0]==UNJUSTVALUE)){
    return(ID_ERR_NO_ERROR);
  }

  ret=processstandardmsgcheck(p_sts, &operatelevel4[0], p_tbl->operator_call, sizeof(p_tbl->operator_call));

  if(ret == ID_ERR_NO_ERROR){
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_OTHER);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
    return(UNIQUESTS);
  }
  if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_CDR_GUIDE)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_CDR_GUIDE_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_CDR_GUIDE_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_CDR_GUIDE2)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_CDR_GUIDE_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_CDR_GUIDE2_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_CDR_GUIDE_PRINT)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_CDR_GUIDE_PRINT_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_CDR_GUIDE_PRINT_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_CDR_GUIDE_PRINT2)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_CDR_GUIDE_PRINT_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_CDR_GUIDE_PRINT2_3rd);
	ret = UNIQUESTS;
  }

  return(ret);
}

int chk_busystatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  ret=processstandardmsgcheck(p_sts, &busystat[0], &p_tbl->busy_stat, sizeof(p_tbl->busy_stat));

  //2.00.01.010 another Interface use :other message doesn't appear.
  if( p_tbl->busy_stat == 'I' )
   		ret = OTHERMESSAGENO;

  return(ret);
}

/* for Ver.2.80 */
int chk_jobstatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  ret=processstandardmsgcheck(p_sts, &jobstat[0], &p_tbl->job_stat, sizeof(p_tbl->job_stat));

  return(ret);
}


int chk_cartridge(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;
  int i;

  for(i=0; i<MAXCARTRIDGENUM; i++){
    ret=processstandardmsgcheck(p_sts, &cartridge[0], &p_tbl->cartridge[i].type, sizeof(p_tbl->cartridge[i].type));
    if(ret!=ID_ERR_NO_ERROR){
      return(ret);
    }
    if(p_tbl->cartridge[i].type != DUMMYSCANNER && p_tbl->cartridge[i].type != SPACE 
       && p_tbl->cartridge[i].type != UNJUSTVALUE){
      return(ret);
    }
  }
  //Ver.2.80 Change
  ret=storeMessageID(p_sts, ID_STS_MESSAGE_CARTRIDGE_NONE);// v2.4 003-0105
  //if ( !strncmp(p_tbl->dev, DEV_1284,4) )		// v2.4
  //  ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_CARTRIDGE_NONE);// v2.4 003-0105
  //else
  //  ret=storeMessageID(p_sts, ID_STS_MESSAGE_CARTRIDGE_NONE);	// v.2.3 010-1121 
  if(ret != ID_ERR_NO_ERROR){
    return(ret);
  }
  return(UNIQUESTS);
}


int chk_basestatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  unsigned int bst;
  char strbst[3];
  int ret;

  if(p_tbl->base_stat[0] == UNJUSTVALUE){
    return(ID_ERR_NO_ERROR);
  }
  strncpy(strbst, p_tbl->base_stat, sizeof(p_tbl->base_stat));
  bst=strtoul(strbst, NULL, 16);

  if(bst & 0x80){
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_BASE_PRINTING);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  else{
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_BASE_ONLINE);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  return(UNIQUESTS);
}


int chk_warning(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  ret=processIDcheck(warning, p_tbl->warning, sizeof(p_tbl->warning));
  if(ret != IDNOTFOUND){
    ret=storeMessageID(p_sts, ret);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  return(ID_ERR_NO_ERROR);
}


/*
 * The message ID acquired with the following functions 
 * can be displayed with other messages.
 *
 * chk_inklow_part1();
 * chk_inklow_part2();
 * chk_noinkcheck();
 */
int chk_inklow_part1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i,k,color,l,m,j,n;
  int ret;
  int inklow_storeposit;
  int first_color;


  //for Ver.2.70
  for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
    if(	!strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
      break;

  inklow_storeposit=p_sts->messageNum;
  p_sts->messageNum++;


  //for Ver.2.70 Dispo
  if( color_tbl_inkout[color].color[0].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE ){

	  for(j=0; j<MAXINKNUM; j++){
		  //for p_tbl->ink[j].alert == 'L' and 'l' two times output
		  first_color = 0;
		  for(i=0; inklowpart3[i].status!=ENDTAG; i++){
		    for(k=0; (k<sizeof(p_tbl->warning)) && (*(p_tbl->warning+k)!=SPACE); k++){
		   
		      if(inklowpart3[i].status == *(p_tbl->warning+k)){
	
		       if( (p_tbl->ink[j].alert == 'L') || (p_tbl->ink[j].alert == 'l') ){
	
				    ret=chkoccuralert_inklow(p_tbl, *(p_tbl->warning+k), j);
				    if( ret == INKLOW ){
						//Decide n : cartridge
			            for(n=0; cartridge_type[n].status!=ENDTAG; n++)
			              if(p_tbl->cartridge[j].type == cartridge_type[n].status)
			                break;
						//Decide j : locale
				        for(m=0; cartridge_region_tbl[m].region[j].status!=ENDTAG; m++){
						  if( cartridge_region_tbl[m].status == p_tbl->destination )
							break;
						}
						//for p_tbl->ink[j].alert == 'L' and 'l' two times output
						if( first_color ==  0 ){
							ret=storeMessageID(p_sts, cartridge_region_tbl[m].region[n].msgid);
							first_color = 1;
					          if(ret != ID_ERR_NO_ERROR)
				                return ret;
			            }
				    }
				 }
		      }
		    }
		  }
	  }
  }
  //for Ver.2.70 independent ink
  else{
	  for(i=0; inklowpart3[i].status!=ENDTAG; i++){
	    for(k=0; (k<sizeof(p_tbl->warning)) && (*(p_tbl->warning+k)!=SPACE); k++){
	
	      if(inklowpart3[i].status == *(p_tbl->warning+k)){
	
			//for Ver.2.70
			for(l=0; color_tbl_inkout[color].color[l].status!=ENDTAG; l++){
			    ret=chkoccuralert_inklow(p_tbl, *(p_tbl->warning+k), l);
	
		        for(m=0; inklowpart1[m].status!=ENDTAG; m++){
		        	if(inklowpart1[m].status == color_tbl_inkout[color].color[l].status)
		        		break;
		        }
	
			    if( ret == INKLOW ){
		          if( p_tbl->destination == ID_HRI_JPN ){
			        ret=storeMessageID(p_sts, inklowpart1[m].msgid);
			        }
		          else
			        ret=storeMessageID(p_sts, inklowpart1_type_OTH[m].msgid);
			      if(ret != ID_ERR_NO_ERROR){
			        return(ret);
			      }
			    }
			 }
	      }
	    }
	  }
  }
  
  //for Ver.2.60
  for(i=0; inklowpart1[i].status!=ENDTAG; i++){
    for(k=0; (k<sizeof(p_tbl->warning)) && (*(p_tbl->warning+k)!=SPACE); k++){
      if(inklowpart1[i].status == *(p_tbl->warning+k)){
	    ret=chkoccuralert(p_tbl, *(p_tbl->warning+k));
	    if(ret != OCCUR){
          if( p_tbl->destination == ID_HRI_JPN )
	        ret=storeMessageID(p_sts, inklowpart1[i].msgid);
          else
	        ret=storeMessageID(p_sts, inklowpart1_type_OTH[i].msgid);
	      if(ret != ID_ERR_NO_ERROR){
	        return(ret);
	      }
	    }
      }
    }
  }

  if(p_sts->messageNum != (inklow_storeposit+1)){
  		if( color_tbl_inkout[color].color[0].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE ){
		    *((p_sts->pMessageID)+inklow_storeposit)=ID_STS_MESSAGE_WAR_INKLOW_40_PRE;
        	ret=storeMessageID(p_sts, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER);
    	}
    	else{
		    *((p_sts->pMessageID)+inklow_storeposit)=ID_STS_MESSAGE_WAR_INKLOW_PRE;
    		ret=storeMessageID(p_sts, ID_STS_MESSAGE_WAR_INKLOW_AFTER);
		}
//    *((p_sts->pMessageID)+inklow_storeposit)=ID_STS_MESSAGE_WAR_INKLOW_PRE;
//  		if( color_tbl_inkout[color].color[0].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE )
//        	ret=storeMessageID(p_sts, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER);
//    else
//    	ret=storeMessageID(p_sts, ID_STS_MESSAGE_WAR_INKLOW_AFTER);

    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  else {
    p_sts->messageNum--;
  }
  return(ID_ERR_NO_ERROR);
}

//Ver.2.70 for iP90 remain unknown 
int chk_inkunknow(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i,k,color;
  int ret;
  int inklow_storeposit;

  for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
    if(	!strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
      break;

  inklow_storeposit=p_sts->messageNum;
  p_sts->messageNum++;

  for(i=0; inkremainunknown[i].status!=ENDTAG; i++){
    for(k=0; (k<sizeof(p_tbl->warning)) && (*(p_tbl->warning+k)!=SPACE); k++){
      if(inkremainunknown[i].status == *(p_tbl->warning+k)){
	    ret=chkoccuralert_inkunknown(p_tbl, *(p_tbl->warning+k));
	    if(ret == INKUNKNOWN){
		    ret=storeMessageID(p_sts, inkremainunknown[i].msgid);
		    if(ret != ID_ERR_NO_ERROR){
		      return(ret);
		    }
	    }
      }
    }
  }

  if(p_sts->messageNum != (inklow_storeposit+1)){
    *((p_sts->pMessageID)+inklow_storeposit)=ID_STS_MESSAGE_OC_REMAIN_UNKNOWN3;
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN3_3rd);

    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  else {
    p_sts->messageNum--;
  }
  return(ID_ERR_NO_ERROR);
}


int chk_inkoutwar_part1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i,k,color,l,m;
  int ret;
  int inklow_storeposit;
  int third_msgid = 0;


  //for Ver.2.70
  for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
    if(	!strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
      break;

  //Dispo
  if( color_tbl_inkout[color].color[0].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE )
    return(ID_ERR_NO_ERROR);

  inklow_storeposit=p_sts->messageNum;
  p_sts->messageNum++;

  for(i=0; inkoutpart3[i].status!=ENDTAG; i++){
    for(k=0; (k<sizeof(p_tbl->warning)) && (*(p_tbl->warning+k)!=SPACE); k++){

      if(inkoutpart3[i].status == *(p_tbl->warning+k)){

		//for Ver.2.70
		third_msgid = inkoutpart3[i].msgid;

		for(l=0; color_tbl_inkout[color].color[l].status!=ENDTAG; l++){
		    ret=chkoccuralert_inklow(p_tbl, *(p_tbl->warning+k), l);

	        for(m=0; inklowpart1[m].status!=ENDTAG; m++){
	        	if(inklowpart1[m].status == color_tbl_inkout[color].color[l].status)
	        		break;
	        }

		    if(ret == INKOUT){
	          if( p_tbl->destination == ID_HRI_JPN )
		        ret=storeMessageID(p_sts, inklowpart1[m].msgid);
	          else
		        ret=storeMessageID(p_sts, inklowpart1_type_OTH[m].msgid);
		      if(ret != ID_ERR_NO_ERROR){
		        return(ret);
		      }
		    }
		 }
      }
    }
  }
  if(p_sts->messageNum != (inklow_storeposit+1)){
    //Ver.2.70
    *((p_sts->pMessageID)+inklow_storeposit)=ID_STS_MESSAGE_OC_INKOUT_TANK2;
    ret=storeMessageID(p_sts, third_msgid);
    
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  else {
    p_sts->messageNum--;
  }
  return(ID_ERR_NO_ERROR);
}



int chk_inklow_part2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int  i,j,k,m;
  int  ret;
  int  inklow_storeposit;
  char cartridge_type_BE;

  inklow_storeposit=p_sts->messageNum;
  p_sts->messageNum++;


  for(i=0; inklowpart2[i].status!=ENDTAG; i++){
    for(k=0; (k<sizeof(p_tbl->warning)) && (*(p_tbl->warning+k)!=SPACE); k++){
      if(inklowpart2[i].status == *(p_tbl->warning+k)){
        if(inklowpart2[i].msgid == ID_STS_MESSAGE_WAR_INKLOW_BLACK40 )
          cartridge_type_BE = p_tbl->cartridge[0].type;
        else
          cartridge_type_BE = p_tbl->cartridge[1].type;

        for(j=0; cartridge_type[j].status!=ENDTAG; j++)
          if(cartridge_type_BE == cartridge_type[j].status)
            break;
            
			//Ver.2.70
	        for(m=0; cartridge_region_tbl[m].region[j].status!=ENDTAG; m++){
				if( cartridge_region_tbl[m].status == p_tbl->destination )
					break;
			}
			ret=storeMessageID(p_sts, cartridge_region_tbl[m].region[j].msgid);

	    if(ret != ID_ERR_NO_ERROR){
	      return(ret);
        }
      }
    }
  }

  if(p_sts->messageNum != (inklow_storeposit+1)){
    *((p_sts->pMessageID)+inklow_storeposit)=ID_STS_MESSAGE_WAR_INKLOW_40_PRE;

	//for 1 cartridge
	//if( (p_tbl->cartridge[0].type == SPACE) )
	//    ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_PREPARE_NEW_CARTRIDGE);
	//else
    //	ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_INKOUT_CART_3rd);
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  else {
    p_sts->messageNum--;
  }
  return(ID_ERR_NO_ERROR);

}


int chk_noinkcheck(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  ret=ID_ERR_NO_ERROR;
  if(p_tbl->ink_check == 'N'){
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_CIL_OFF);
  }
  return(ret);
}

//for Ver.2.70
//decide with CTK:SETZ and CIR:UK 
int chk_noinkcheck2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret=ID_ERR_NO_ERROR;
  int color;
  int i, j,l, m;
  int inklow_storeposit;
  int msg_flag = 0;
  int cartridge_type_BE = 0;

//remove 20061106
//  if( !( (p_tbl->operator_call[0]==SPACE) 
//      || (p_tbl->operator_call[0]=='E')
//      || (p_tbl->operator_call[0]=='u')
//      || (p_tbl->operator_call[0]=='B')) )
//	  return(ID_ERR_NO_ERROR);

  for(i=0; i<8; i++){
   if( (p_tbl->ink[i].alert == 'Z') && (p_tbl->ink[i].fill[0] == 'U') && (p_tbl->ink[i].fill[1] == 'K') ){
		msg_flag = 1;
	}
  }

  if( msg_flag == 0 )
    return(ID_ERR_NO_ERROR);

  inklow_storeposit=p_sts->messageNum;
  p_sts->messageNum++;

  for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
    if(	!strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
      break;

	for(l=0; color_tbl_inkout[color].color[l].status!=ENDTAG; l++){

        if( (p_tbl->ink[l].alert == 'Z') && (p_tbl->ink[l].fill[0] == 'U') && (p_tbl->ink[l].fill[1] == 'K') ){
        
        	//Dispo
        	if( color_tbl_inkout[color].color[l].msgid != ID_STS_MESSAGE_COLOR_TYPE ){
        	//if( (color_tbl_inkout[color].color[l].status == 'B') || (color_tbl_inkout[color].color[l].status == 'E') ){
        	
		        for(m=0; inklowpart2[m].status!=ENDTAG; m++)
		        	if(inklowpart2[m].status == color_tbl_inkout[color].color[l].status)
		        		break;
	
				if(inklowpart2[m].status == ENDTAG)
					return(ID_ERR_NO_ERROR);
	
				if( color_tbl_inkout[color].color[l].status == 'B' )
					cartridge_type_BE = p_tbl->cartridge[0].type;
				else if( color_tbl_inkout[color].color[l].status == 'E' )
					cartridge_type_BE = p_tbl->cartridge[1].type;
	
		        for(j=0; cartridge_type[j].status!=ENDTAG; j++)
		          if(cartridge_type_BE == cartridge_type[j].status)
		            break;

				//Ver.2.70
	            for(m=0; cartridge_region_tbl[m].region[j].status!=ENDTAG; m++){
					if( cartridge_region_tbl[m].status == p_tbl->destination )
					break;
				}
				
				ret=storeMessageID(p_sts, cartridge_region_tbl[m].region[j].msgid);

			    if(ret != ID_ERR_NO_ERROR)
			      return(ret);
        	}
        	//not Dispo
        	else{
		        for(m=0; inklowpart1[m].status!=ENDTAG; m++)
		        	if(inklowpart1[m].status == color_tbl_inkout[color].color[l].status)
		        		break;
		
				if(inklowpart1[m].status == ENDTAG)
					return(ID_ERR_NO_ERROR);
		
		        if( p_tbl->destination == ID_HRI_JPN )
			      ret=storeMessageID(p_sts, inklowpart1[m].msgid);
		        else
			      ret=storeMessageID(p_sts, inklowpart1_type_OTH[m].msgid);
			    if(ret != ID_ERR_NO_ERROR)
			      return(ret);
        	}
		 }
	 }
  
  if(p_sts->messageNum != (inklow_storeposit+1)){
     *((p_sts->pMessageID)+inklow_storeposit)=ID_STS_MESSAGE_INKSTATUS_OFF;

    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  else {
    p_sts->messageNum--;
  }
  
  return(ID_ERR_NO_ERROR);

}


/*
 * The following is a static processing function.
 */
static int processIDcheck(const ST_MSGTBL *p_msgtbl, char *p_status, int status_size )
{
  int i;
  int ret;

  char *p_temp;
  char *p_callchr;

  ret=IDNOTFOUND;
  p_temp=(char *)malloc(status_size+1);
  if(p_temp == NULL){
    return(ID_ERR_MEM_ALLOC_FAILED);
  }
  strncpy(p_temp, p_status, status_size);
  *(p_temp+status_size)='\0';

  for(i=0; (p_msgtbl+i)->status!=ENDTAG; i++){
    p_callchr=strchr(p_temp, (p_msgtbl+i)->status);
    if(p_callchr!=NULL ){
      ret=(p_msgtbl+i)->msgid;
      break;
    }
  }
  free(p_temp);
  return(ret);
}

/*
static int chkoccuroperatorcall(ST_CUPSSTS *p_tbl, char chkchr)
{
  int i;

  for(i=0; (i<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+i)!=SPACE); i++){
    if(*(p_tbl->operator_call+i) == chkchr){
      return(OCCUR);
    }
  }
  return(NOTINKOUT);
}
*/


static int chkoccuralert_inkunknown(ST_CUPSSTS *p_tbl, char chkchr)
{
  int i;

  for(i=0; i<MAXINKNUM; i++){
	if( p_tbl->ink[i].alert == '?' ){
      return(INKUNKNOWN);
	}
  }

  return(OCCUR);
}


static int chkoccuralert_inklow(ST_CUPSSTS *p_tbl, char chkchr, int i)
{

	int k;
	int IO_Flag = 0;

    for(k=0; (k<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+k)!=SPACE); k++){
		if(  ( (p_tbl->operator_call[k] == 'E')
	        || (p_tbl->operator_call[k] == 'C') 
	        || (p_tbl->operator_call[k] == 'c') 
	        || (p_tbl->operator_call[k] == 'u') 
	        || (p_tbl->operator_call[k] == 'B') ) ){
	    	IO_Flag = 1;
	    }
    }

	if( p_tbl->ink[i].alert == 'I' && IO_Flag == 0) {
      return(INKOUT);
	}
	else if( (p_tbl->ink[i].alert == 'L') || (p_tbl->ink[i].alert == 'l') ){
//	else if( p_tbl->ink[i].alert == 'L' ){
      return(INKLOW);
	}
	else

  return(OCCUR);
}


static int chkoccuralert(ST_CUPSSTS *p_tbl, char chkchr)
{
  int i;

  for(i=0; i<MAXINKNUM; i++){
	if( p_tbl->ink[i].color == chkchr && p_tbl->ink[i].alert == 'I' ){
      return(OCCUR);
	}
  }

  return(NOTINKOUT);
}


static int storeMessageID(ST_PrinterStatus *p_sts, int msgID)
{
  if(p_sts->messageNum >= STANDARDMSGNUM){
    p_sts->pMessageID=(ENUM_STSMessageID *)realloc(p_sts->pMessageID, sizeof(ENUM_STSMessageID)*((p_sts->messageNum)+1) );
    if(p_sts->pMessageID == NULL){
      return(ID_ERR_MEM_ALLOC_FAILED);
    }
  }
  *((p_sts->pMessageID)+(p_sts->messageNum))=msgID;
  (p_sts->messageNum)++;
  return(ID_ERR_NO_ERROR);
} 


static int processstandardmsgcheck(ST_PrinterStatus *p_sts, const ST_MSGTBL *p_msgtbl, char *p_status, int status_size)
{
  int ret;

  ret=processIDcheck(p_msgtbl, p_status, status_size);
  if(ret != IDNOTFOUND){
    ret=storeMessageID(p_sts, ret);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
    return(UNIQUESTS);
  }
  return(ID_ERR_NO_ERROR);
}


// Resume/OK/Start Button for Ver.2.70
static int setButtonID(ST_CUPSSTS *p_tbl)
{
  int i;
  int rsm_button = ID_ERR_NO_ERROR;

	for(i=0; rsm_button_tbl[i].pr_name!=ENDTAG; i++){
		if(	strncmp(p_tbl->pr_name, rsm_button_tbl[i].pr_name, strlen(rsm_button_tbl[i].pr_name)) == 0 ) {
			rsm_button = rsm_button_tbl[i].is_rsm_button;
			break;
		}
	}
	rsm_button = rsm_button_tbl[i].is_rsm_button;

	return(rsm_button);
} 


// rearsupply for Ver.2.80
static int setRearSupplyID(ST_CUPSSTS *p_tbl)
{
  int i;
  int is_rearsupply = ID_ERR_NO_ERROR;

	for(i=0; rearsupply_tbl[i].pr_name!=ENDTAG; i++){
		if(	strncmp(p_tbl->pr_name, rearsupply_tbl[i].pr_name, strlen(rearsupply_tbl[i].pr_name)) == 0 ) {
			is_rearsupply = rearsupply_tbl[i].is_rearsupply;
			break;
		}
    }
	is_rearsupply = rearsupply_tbl[i].is_rearsupply;
	
	return(is_rearsupply);
} 

// frontsupply for Ver.2.80
static int setFrontSupplyID(ST_CUPSSTS *p_tbl)
{
  int i;
  int is_frontsupply = ID_ERR_NO_ERROR;

	for(i=0; frontsupply_tbl[i].pr_name!=ENDTAG; i++){
		if(	strncmp(p_tbl->pr_name, frontsupply_tbl[i].pr_name, strlen(frontsupply_tbl[i].pr_name)) == 0 ) {
			is_frontsupply = frontsupply_tbl[i].is_frontsupply;
			break;
		}
    }
	is_frontsupply = frontsupply_tbl[i].is_frontsupply;
	
	return(is_frontsupply);
} 

// Ink Remain Suequence for Ver.2.80
static int setInkRemainSequenceID(ST_CUPSSTS *p_tbl)
{
  int i;
  int is_inkremain_sequence = ID_ERR_NO_ERROR;

	for(i=0; inkremain_sequence_tbl[i].pr_name!=ENDTAG; i++){
		if(	strncmp(p_tbl->pr_name, inkremain_sequence_tbl[i].pr_name, strlen(inkremain_sequence_tbl[i].pr_name)) == 0 ) {
			is_inkremain_sequence = inkremain_sequence_tbl[i].is_inkremain_sequence;
			break;
		}
    }
	is_inkremain_sequence = inkremain_sequence_tbl[i].is_inkremain_sequence;
	
	return(is_inkremain_sequence);
} 

