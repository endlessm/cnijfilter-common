/*
 *  Canon Inkjet Printer Driver for Linux
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
 */

static const
ST_MSGTBL inkremainunknown[]={
  {'U', ID_STS_MESSAGE_INK_BLACK15},	// iP90
  {'u', ID_STS_MESSAGE_INK_COLOR16},	// iP90
  {ENDTAG, 0}
};


static const
ST_MSGTBL cartridge_type1_ZZZ[]={
  {'U', ID_STS_MESSAGE_INK_BLACK},
  {'V', ID_STS_MESSAGE_INK_COLOR},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK},
  {'O', ID_STS_MESSAGE_INK_COLOR},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type1_JP[]={
  {'U', ID_STS_MESSAGE_INK_BLACK30},
  {'V', ID_STS_MESSAGE_INK_COLOR31},
  {'L', ID_STS_MESSAGE_INK_BLACK70},
  {'M', ID_STS_MESSAGE_INK_COLOR71},
  {'N', ID_STS_MESSAGE_INK_BLACK90},
  {'O', ID_STS_MESSAGE_INK_COLOR91},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type1_OTH[]={
  {'U', ID_STS_MESSAGE_INK_BLACK30},
  {'V', ID_STS_MESSAGE_INK_COLOR31},
  {'L', ID_STS_MESSAGE_INK_BLACK40},
  {'M', ID_STS_MESSAGE_INK_COLOR41},
  {'N', ID_STS_MESSAGE_INK_BLACK50},
  {'O', ID_STS_MESSAGE_INK_COLOR51},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type1_ASI[]={
  {'U', ID_STS_MESSAGE_INK_BLACK830},
  {'V', ID_STS_MESSAGE_INK_COLOR831},
  {'L', ID_STS_MESSAGE_INK_BLACK40},
  {'M', ID_STS_MESSAGE_INK_COLOR41},
  {'N', ID_STS_MESSAGE_INK_BLACK50},
  {'O', ID_STS_MESSAGE_INK_COLOR51},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type1_PAM[]={
  {'U', ID_STS_MESSAGE_INK_BLACK30},
  {'V', ID_STS_MESSAGE_INK_COLOR31},
  {'L', ID_STS_MESSAGE_INK_BLACK40},
  {'M', ID_STS_MESSAGE_INK_COLOR41},
  {'N', ID_STS_MESSAGE_INK_BLACK50},
  {'O', ID_STS_MESSAGE_INK_COLOR51},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type1_EU[]={
  {'U', ID_STS_MESSAGE_INK_BLACK37},
  {'V', ID_STS_MESSAGE_INK_COLOR38},
  {'L', ID_STS_MESSAGE_INK_BLACK40},
  {'M', ID_STS_MESSAGE_INK_COLOR41},
  {'N', ID_STS_MESSAGE_INK_BLACK50},
  {'O', ID_STS_MESSAGE_INK_COLOR51},
  {ENDTAG, 0}
};


static const
ST_MSGTBL cartridge_type2_ZZZ[]={
  {'U', ID_STS_MESSAGE_INK_BLACK},
  {'V', ID_STS_MESSAGE_INK_COLOR},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK},
  {'O', ID_STS_MESSAGE_INK_COLOR},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type2_JP[]={
  {'U', ID_STS_MESSAGE_INK_BLACK310},
  {'V', ID_STS_MESSAGE_INK_COLOR311},
  {'L', ID_STS_MESSAGE_INK_BLACK310},
  {'M', ID_STS_MESSAGE_INK_COLOR311},
  {'N', ID_STS_MESSAGE_INK_BLACK310},
  {'O', ID_STS_MESSAGE_INK_COLOR311},
  {'*', ID_STS_MESSAGE_INK_BLACK},
  {'@', ID_STS_MESSAGE_INK_COLOR},
  {ENDTAG, 0}
};


static const
ST_MSGTBL cartridge_type2_ASI[]={
  {'U', ID_STS_MESSAGE_INK_BLACK810},
  {'V', ID_STS_MESSAGE_INK_COLOR811},
  {'L', ID_STS_MESSAGE_INK_BLACK810XL},
  {'M', ID_STS_MESSAGE_INK_COLOR810XL},
  {'N', ID_STS_MESSAGE_INK_BLACK810},
  {'O', ID_STS_MESSAGE_INK_COLOR811},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type2_PAM[]={
  {'U', ID_STS_MESSAGE_INK_BLACK210},
  {'V', ID_STS_MESSAGE_INK_COLOR211},
  {'L', ID_STS_MESSAGE_INK_BLACK210XL},
  {'M', ID_STS_MESSAGE_INK_COLOR210XL},
  {'N', ID_STS_MESSAGE_INK_BLACK210},
  {'O', ID_STS_MESSAGE_INK_COLOR211},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type2_EU[]={
  {'U', ID_STS_MESSAGE_INK_BLACK510},
  {'V', ID_STS_MESSAGE_INK_COLOR511},
  {'L', ID_STS_MESSAGE_INK_BLACK512},
  {'M', ID_STS_MESSAGE_INK_COLOR513},
  {'N', ID_STS_MESSAGE_INK_BLACK510},
  {'O', ID_STS_MESSAGE_INK_COLOR511},
  {ENDTAG, 0}
};


static const
ST_REGION_TBL cartridge_type1_region_tbl[]={
  {'Z', cartridge_type1_ZZZ}, /* must be top */
  {'J', cartridge_type1_JP},
  {'O', cartridge_type1_OTH},
  {'A', cartridge_type1_ASI},
  {'P', cartridge_type1_PAM},
  {'E', cartridge_type1_EU},
  {ENDTAG, 0}
};

static const
ST_REGION_TBL cartridge_type2_region_tbl[]={
  {'Z', cartridge_type2_ZZZ}, /* must be top */
  {'J', cartridge_type2_JP},
  {'A', cartridge_type2_ASI},
  {'P', cartridge_type2_PAM},
  {'E', cartridge_type2_EU},
  {ENDTAG, 0}
};


static const
ST_MSGTBL ink_type0_JP[]={
  {'l', ID_STS_MESSAGE_INK_BLACK9},
  {'L', ID_STS_MESSAGE_INK_BLACK7e},
  {'C', ID_STS_MESSAGE_INK_CYAN7e},
  {'M', ID_STS_MESSAGE_INK_MAGENTA7e},
  {'Y', ID_STS_MESSAGE_INK_YELLOW7e},
  {'B', ID_STS_MESSAGE_INK_BLACK19},	// iP100
  {'G', ID_STS_MESSAGE_INK_COLOR19},	// iP100
  {'b', ID_STS_MESSAGE_INK_BLACK15},	// iP90
  {'e', ID_STS_MESSAGE_INK_COLOR16},	// iP90
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type0_OTH[]={
  {'l', ID_STS_MESSAGE_INK_BLACK5},
  {'L', ID_STS_MESSAGE_INK_BLACK8},
  {'C', ID_STS_MESSAGE_INK_CYAN8},
  {'M', ID_STS_MESSAGE_INK_MAGENTA8},
  {'Y', ID_STS_MESSAGE_INK_YELLOW8},
  {'B', ID_STS_MESSAGE_INK_BLACK35},	// iP100
  {'G', ID_STS_MESSAGE_INK_COLOR36},	// iP100
  {'b', ID_STS_MESSAGE_INK_BLACK15},	// iP90
  {'e', ID_STS_MESSAGE_INK_COLOR16},	// iP90
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type0_ZZZ[]={
  {'l', ID_STS_MESSAGE_INK_BLACK5},
  {'L', ID_STS_MESSAGE_INK_BLACK8},
  {'C', ID_STS_MESSAGE_INK_CYAN8},
  {'M', ID_STS_MESSAGE_INK_MAGENTA8},
  {'Y', ID_STS_MESSAGE_INK_YELLOW8},
  {'B', ID_STS_MESSAGE_INK_BLACK35},	// iP100
  {'G', ID_STS_MESSAGE_INK_COLOR36},	// iP100
  {'b', ID_STS_MESSAGE_INK_BLACK15},	// iP90
  {'e', ID_STS_MESSAGE_INK_COLOR16},	// iP90
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type1_JP[]={
  {'l', ID_STS_MESSAGE_INK_BLACK320},
  {'L', ID_STS_MESSAGE_INK_BLACK321},
  {'C', ID_STS_MESSAGE_INK_CYAN321},
  {'M', ID_STS_MESSAGE_INK_MAGENTA321},
  {'Y', ID_STS_MESSAGE_INK_YELLOW321},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type1_ASI[]={
  {'l', ID_STS_MESSAGE_INK_BLACK820},
  {'L', ID_STS_MESSAGE_INK_BLACK821},
  {'C', ID_STS_MESSAGE_INK_CYAN821},
  {'M', ID_STS_MESSAGE_INK_MAGENTA821},
  {'Y', ID_STS_MESSAGE_INK_YELLOW821},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type1_PAM[]={
  {'l', ID_STS_MESSAGE_INK_BLACK220},
  {'L', ID_STS_MESSAGE_INK_BLACK221},
  {'C', ID_STS_MESSAGE_INK_CYAN221},
  {'M', ID_STS_MESSAGE_INK_MAGENTA221},
  {'Y', ID_STS_MESSAGE_INK_YELLOW221},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type1_EU[]={
  {'l', ID_STS_MESSAGE_INK_BLACK520},
  {'L', ID_STS_MESSAGE_INK_BLACK521},
  {'C', ID_STS_MESSAGE_INK_CYAN521},
  {'M', ID_STS_MESSAGE_INK_MAGENTA521},
  {'Y', ID_STS_MESSAGE_INK_YELLOW521},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type1_ZZZ[]={
  {'l', ID_STS_MESSAGE_INK_BLACK520},
  {'L', ID_STS_MESSAGE_INK_BLACK521},
  {'C', ID_STS_MESSAGE_INK_CYAN521},
  {'M', ID_STS_MESSAGE_INK_MAGENTA521},
  {'Y', ID_STS_MESSAGE_INK_YELLOW521},
  {ENDTAG, 0}
};

static const
ST_REGION_TBL ink_type0_region_tbl[]={
  {'J', ink_type0_JP},
  {'O', ink_type0_OTH},
  {'Z', ink_type0_ZZZ},
  {ENDTAG, 0}
};

static const
ST_REGION_TBL ink_type1_region_tbl[]={
  {'J', ink_type1_JP},
  {'A', ink_type1_ASI},
  {'P', ink_type1_PAM},
  {'E', ink_type1_EU},
  {'Z', ink_type1_ZZZ},
  {ENDTAG, 0}
};

/* Ver.3.00 for switch model */
static const
ST_INKTYPE_TBL ink_type_tbl[]={
  {"IP3300",  ink_type0_region_tbl},
  {"IP3500",  ink_type0_region_tbl},
  {"MP510",   ink_type0_region_tbl},
  {"MP520",   ink_type0_region_tbl},
  {"IP4300",  ink_type0_region_tbl},
  {"IP4500",  ink_type0_region_tbl},
  {"MP600",   ink_type0_region_tbl},
  {"MP610",   ink_type0_region_tbl},
  {"IP1800",  cartridge_type1_region_tbl},
  {"IP2500",  cartridge_type1_region_tbl},
  {"MP140",   cartridge_type1_region_tbl},
  {"MP210",   cartridge_type1_region_tbl},
  {"IP100",   ink_type0_region_tbl},
  {"IP2600",  cartridge_type1_region_tbl},
  {"IP1900",  cartridge_type1_region_tbl},
  {"MP190",   cartridge_type1_region_tbl},
  {"MP240",   cartridge_type2_region_tbl},
  {"IP4600",  ink_type1_region_tbl},
  {"IP3600",  ink_type1_region_tbl},
  {"MP630",   ink_type1_region_tbl},
  {"MP540",   ink_type1_region_tbl},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_ip2200[]={
  {'B', ID_STS_MESSAGE_COLOR_CARTRIDGE},
  {'E', ID_STS_MESSAGE_COLOR_CARTRIDGE},
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

ST_MSGTBL color_ip100[]={
  {'G', ID_STS_MESSAGE_COLOR_TYPE},
  {'B', ID_STS_MESSAGE_COLOR_TYPE},
  {ENDTAG, 0}
};


static const
ST_DEVCLR_TBL color_tbl_inkout[]={
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
  {"IP2500",  color_ip2200},
  {"IP1800",  color_ip2200},
  {"IP90",    color_ip90},
  {"IP4500",  color_ip4200},
  {"IP3500",  color_ip3300},
  {"MP610",   color_ip4200},
  {"MP520",   color_ip3300},
  {"MP140",   color_ip2200},
  {"MP210",   color_ip2200},
  {"IP2600",  color_ip2200},
  {"IP100",   color_ip100},
  {"IP1900",  color_ip2200},
  {"MP190",   color_ip2200},
  {"MP240",   color_ip2200},
  {"IP4600",  color_ip4200},
  {"IP3600",  color_ip4200},
  {"MP630",   color_ip4200},
  {"MP540",   color_ip4200},
  {ENDTAG, 0}
};

/* ip3300 */
/* Ver.3.00 for ip3300 dbs string pattern table */
static const
ST_MSGTBL ip3300_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3300 djs string pattern table */
static const
ST_MSGTBL ip3300_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN03},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip3300 doc string pattern table */
static const
ST_MSGTBL ip3300_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN06},
  {'p',	OC1003_PAPEROUT_PATTERN08},
  {'q',	OC1300_PAPERJAM_PATTERN03},
  {'n',	OC1303_PAPERJAM_PATTERN08},
  {'i',	OC1304_PAPERJAM_PATTERN01},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN01},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN01},
  {'N', OC2500_HEADALIGNMENT_PATTERN01},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN01},
  {'u', OC1600_INKOUT_TANK_PATTERN01},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN03},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN01},
  {'K', OC1856_CDR_GUIDE_PATTERN01},
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip3300 dsc string pattern table */
static const
ST_MSGTBL ip3300_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3300 dws string pattern table */
static const
ST_MSGTBL ip3300_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3300 doc pict area pattern table */
static const
ST_MSGTBL ip3300_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3300 dbs pict area pattern table */
static const
ST_MSGTBL ip3300_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3300 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip3300_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3300 doc icon delete pattern table */
static const
ST_MSGTBL ip3300_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* ip3500 */
/* Ver.3.00 for ip3500 dbs string pattern table */
static const
ST_MSGTBL ip3500_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3500 djs string pattern table */
static const
ST_MSGTBL ip3500_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN03},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip3500 doc string pattern table */
static const
ST_MSGTBL ip3500_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN03},
  {'p',	OC1003_PAPEROUT_PATTERN07},
  {'q',	OC1300_PAPERJAM_PATTERN03},
  {'n',	OC1303_PAPERJAM_PATTERN07},
  {'i',	OC1304_PAPERJAM_PATTERN01},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN01},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN01},
  {'N', OC2500_HEADALIGNMENT_PATTERN01},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN01},
  {'u', OC1600_INKOUT_TANK_PATTERN01},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN03},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN01},
  {'K', OC1856_CDR_GUIDE_PATTERN01},
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip3500 dsc string pattern table */
static const
ST_MSGTBL ip3500_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3500 dws string pattern table */
static const
ST_MSGTBL ip3500_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3500 doc pict area pattern table */
static const
ST_MSGTBL ip3500_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3500 dbs pict area pattern table */
static const
ST_MSGTBL ip3500_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3500 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip3500_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3500 doc icon delete pattern table */
static const
ST_MSGTBL ip3500_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* mp510 */
/* Ver.3.00 for mp510 dbs string pattern table */
static const
ST_MSGTBL mp510_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp510 djs string pattern table */
static const
ST_MSGTBL mp510_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN02},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp510 doc string pattern table */
static const
ST_MSGTBL mp510_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN05},
  {'p',	OC1003_PAPEROUT_PATTERN06},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN06},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN02},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN02},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN02},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN02},
  {'u', OC1600_INKOUT_TANK_PATTERN02},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN02},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'K', OC1856_CDR_GUIDE_PATTERN02},
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp510 dsc string pattern table */
static const
ST_MSGTBL mp510_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for mp510 dws string pattern table */
static const
ST_MSGTBL mp510_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp510 doc pict area pattern table */
static const
ST_MSGTBL mp510_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp510 dbs pict area pattern table */
static const
ST_MSGTBL mp510_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp510 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp510_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp510 doc icon delete pattern table */
static const
ST_MSGTBL mp510_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};

/* mp520 */
/* Ver.3.00 for mp520 dbs string pattern table */
static const
ST_MSGTBL mp520_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp520 djs string pattern table */
static const
ST_MSGTBL mp520_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN02},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp520 doc string pattern table */
static const
ST_MSGTBL mp520_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN05},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN05},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN02},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN02},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN02},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN02},
  {'u', OC1600_INKOUT_TANK_PATTERN02},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN02},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'K', OC1856_CDR_GUIDE_PATTERN02},
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp520 dsc string pattern table */
static const
ST_MSGTBL mp520_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for mp520 dws string pattern table */
static const
ST_MSGTBL mp520_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp520 doc pict area pattern table */
static const
ST_MSGTBL mp520_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp520 dbs pict area pattern table */
static const
ST_MSGTBL mp520_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp520 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp520_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp520 doc icon delete pattern table */
static const
ST_MSGTBL mp520_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* ip4300 */
/* Ver.3.00 for ip4300 dbs string pattern table */
static const
ST_MSGTBL ip4300_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4300 djs string pattern table */
static const
ST_MSGTBL ip4300_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN03},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip4300 doc string pattern table */
static const
ST_MSGTBL ip4300_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN06},
  {'p',	OC1003_PAPEROUT_PATTERN01},
  {'q',	OC1300_PAPERJAM_PATTERN03},
  {'n',	OC1303_PAPERJAM_PATTERN01},
  {'i',	OC1304_PAPERJAM_PATTERN01},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN01},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN01},
  {'N', OC2500_HEADALIGNMENT_PATTERN01},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN01},
  {'u', OC1600_INKOUT_TANK_PATTERN01},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN03},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN01},
  {'K', OC1856_CDR_GUIDE_PATTERN01},
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip4300 dsc string pattern table */
static const
ST_MSGTBL ip4300_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4300 dws string pattern table */
static const
ST_MSGTBL ip4300_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4300 doc pict area pattern table */
static const
ST_MSGTBL ip4300_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4300 dbs pict area pattern table */
static const
ST_MSGTBL ip4300_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4300 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip4300_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4300 doc icon delete pattern table */
static const
ST_MSGTBL ip4300_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};

/* ip4500 */
/* Ver.3.00 for ip4500 dbs string pattern table */
static const
ST_MSGTBL ip4500_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4500 djs string pattern table */
static const
ST_MSGTBL ip4500_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN03},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip4500 doc string pattern table */
static const
ST_MSGTBL ip4500_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN03},
  {'p',	OC1003_PAPEROUT_PATTERN01},
  {'q',	OC1300_PAPERJAM_PATTERN03},
  {'n',	OC1303_PAPERJAM_PATTERN01},
  {'i',	OC1304_PAPERJAM_PATTERN01},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN01},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN01},
  {'N', OC2500_HEADALIGNMENT_PATTERN01},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN01},
  {'u', OC1600_INKOUT_TANK_PATTERN01},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN03},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN01},
  {'K', OC1856_CDR_GUIDE_PATTERN01},
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip4500 dsc string pattern table */
static const
ST_MSGTBL ip4500_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4500 dws string pattern table */
static const
ST_MSGTBL ip4500_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4500 doc pict area pattern table */
static const
ST_MSGTBL ip4500_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4500 dbs pict area pattern table */
static const
ST_MSGTBL ip4500_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4500 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip4500_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4500 doc icon delete pattern table */
static const
ST_MSGTBL ip4500_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* mp600 */
/* Ver.3.00 for mp600 dbs string pattern table */
static const
ST_MSGTBL mp600_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp600 djs string pattern table */
static const
ST_MSGTBL mp600_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN02},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp600 doc string pattern table */
static const
ST_MSGTBL mp600_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN05},
  {'p',	OC1003_PAPEROUT_PATTERN02},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN02},
  {'i',	OC1304_PAPERJAM_PATTERN02},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN02},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN02},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN02},
  {'N', OC2500_HEADALIGNMENT_PATTERN02},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN02},
  {'u', OC1600_INKOUT_TANK_PATTERN02},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN02},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN02},
  {'K', OC1856_CDR_GUIDE_PATTERN02},
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp600 dsc string pattern table */
static const
ST_MSGTBL mp600_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for mp600 dws string pattern table */
static const
ST_MSGTBL mp600_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp600 doc pict area pattern table */
static const
ST_MSGTBL mp600_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp600 dbs pict area pattern table */
static const
ST_MSGTBL mp600_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp600 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp600_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp600 doc icon delete pattern table */
static const
ST_MSGTBL mp600_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* mp610 */
/* Ver.3.00 for mp610 dbs string pattern table */
static const
ST_MSGTBL mp610_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp610 djs string pattern table */
static const
ST_MSGTBL mp610_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN02},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp610 doc string pattern table */
static const
ST_MSGTBL mp610_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN02},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN02},
  {'i',	OC1304_PAPERJAM_PATTERN02},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN02},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN02},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN02},
  {'N', OC2500_HEADALIGNMENT_PATTERN02},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN02},
  {'u', OC1600_INKOUT_TANK_PATTERN02},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN02},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN02},
  {'K', OC1856_CDR_GUIDE_PATTERN02},
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp610 dsc string pattern table */
static const
ST_MSGTBL mp610_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for mp610 dws string pattern table */
static const
ST_MSGTBL mp610_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp610 doc pict area pattern table */
static const
ST_MSGTBL mp610_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp610 dbs pict area pattern table */
static const
ST_MSGTBL mp610_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp610 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp610_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp610 doc icon delete pattern table */
static const
ST_MSGTBL mp610_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* iP100 */
/* Ver.3.00 for ip100 dbs string pattern table */
static const
ST_MSGTBL ip100_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip100 djs string pattern table */
static const
ST_MSGTBL ip100_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN03},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip100 doc string pattern table */
static const
ST_MSGTBL ip100_doc_string_pattern_table[]={
  /* operator level1 */
  {'U',	OC2001_USBDEVICE_PATTERN02},
  {'X',	OC1000_PAPEROUT_PATTERN01},
  {'q',	OC1300_PAPERJAM_PATTERN01},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN01},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN01},
  {'N', OC2500_HEADALIGNMENT_PATTERN01},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN03},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN01},
  {'u', OC1600_INKOUT_TANK_PATTERN01},
  /* operator level3 */
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN03},
  {'z', OC1689_REMAIN_UNKNOWN_PATTERN01},
  /* operator level4 */
  {'o', OC1250_COVER_OPEN_PATTERN02},
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'D', OC1810_BATTERY_ERROR_PATTERN01},
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip100 dsc string pattern table */
static const
ST_MSGTBL ip100_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {'G', SCA100_BATTERY_TROUBLE_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for ip100 dws string pattern table */
static const
ST_MSGTBL ip100_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'S', WR1800_DWS_BATTERYLOW_PATTERN01},		/* D-02 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip100 doc pict area pattern table */
static const
ST_MSGTBL ip100_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip100 dbs pict area pattern table */
static const
ST_MSGTBL ip100_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip100 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip100_doc_unknownicon_draw_pattern_table[]={
  {'z', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip100 doc icon delete pattern table */
static const
ST_MSGTBL ip100_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* iP1900 */
/* Ver.3.00 for ip1900 dbs string pattern table */
static const
ST_MSGTBL ip1900_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip1900 djs string pattern table */
static const
ST_MSGTBL ip1900_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN03},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip1900 doc string pattern table */
static const
ST_MSGTBL ip1900_doc_string_pattern_table[]={
  /* operator level1 */
  {'X',	OC1000_PAPEROUT_PATTERN01},
  {'q',	OC1300_PAPERJAM_PATTERN01},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN01},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN01},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN02},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN05},
  /* operator level3 */
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN03},
  /* operator level4 */
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'v', OC1200_COVER_OPEN_PATTERN01},
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip1900 dsc string pattern table */
static const
ST_MSGTBL ip1900_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for ip1900 dws string pattern table */
static const
ST_MSGTBL ip1900_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip1900 doc pict area pattern table */
static const
ST_MSGTBL ip1900_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip1900 dbs pict area pattern table */
static const
ST_MSGTBL ip1900_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip1900 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip1900_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip1900 doc icon delete pattern table */
static const
ST_MSGTBL ip1900_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};


/* mp190 */
/* Ver.3.00 for mp190 dbs string pattern table */
static const
ST_MSGTBL mp190_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp190 djs string pattern table */
static const
ST_MSGTBL mp190_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN02},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp190 doc string pattern table */
static const
ST_MSGTBL mp190_doc_string_pattern_table[]={
  /* operator level1 */
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN02},
  {'q',	OC1300_PAPERJAM_PATTERN02},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  {'r',	OC1403_CARTRIDGENONE_PATTERN03},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN03},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN03},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN02},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN03},
  /* operator level3 */
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN01},
  /* operator level4 */
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'v', OC1200_COVER_OPEN_PATTERN01},
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp190 dsc string pattern table */
static const
ST_MSGTBL mp190_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for mp190 dws string pattern table */
static const
ST_MSGTBL mp190_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp190 doc pict area pattern table */
static const
ST_MSGTBL mp190_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp190 dbs pict area pattern table */
static const
ST_MSGTBL mp190_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp190 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp190_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp190 doc icon delete pattern table */
static const
ST_MSGTBL mp190_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};

/* mp240 */
/* Ver.3.00 for mp240 dbs string pattern table */
static const
ST_MSGTBL mp240_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp240 djs string pattern table */
static const
ST_MSGTBL mp240_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN02},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp240 doc string pattern table */
static const
ST_MSGTBL mp240_doc_string_pattern_table[]={
  /* operator level1 */
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN02},
  {'q',	OC1300_PAPERJAM_PATTERN02},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  {'r',	OC1403_CARTRIDGENONE_PATTERN03},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN03},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN03},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN03},
  /* operator level3 */
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN01},
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp240 dsc string pattern table */
static const
ST_MSGTBL mp240_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for mp240 dws string pattern table */
static const
ST_MSGTBL mp240_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp240 doc pict area pattern table */
static const
ST_MSGTBL mp240_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp240 dbs pict area pattern table */
static const
ST_MSGTBL mp240_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp240 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp240_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp240 doc icon delete pattern table */
static const
ST_MSGTBL mp240_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};

/* ip3600 */
/* Ver.3.00 for ip3600 dbs string pattern table */
static const
ST_MSGTBL ip3600_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3600 djs string pattern table */
static const
ST_MSGTBL ip3600_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN03},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip3600 doc string pattern table */
static const
ST_MSGTBL ip3600_doc_string_pattern_table[]={
  /* operator level1 */
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN03},
  {'p',	OC1003_PAPEROUT_PATTERN03},
  {'q',	OC1300_PAPERJAM_PATTERN03},
  {'n',	OC1303_PAPERJAM_PATTERN03},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN01},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN01},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN01},
  {'u', OC1600_INKOUT_TANK_PATTERN01},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip3600 dsc string pattern table */
static const
ST_MSGTBL ip3600_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3600 dws string pattern table */
static const
ST_MSGTBL ip3600_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3600 doc pict area pattern table */
static const
ST_MSGTBL ip3600_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.00 for ip3600 dbs pict area pattern table */
static const
ST_MSGTBL ip3600_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3600 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip3600_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip3600 doc icon delete pattern table */
static const
ST_MSGTBL ip3600_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* mp540 */
/* Ver.3.00 for mp540 dbs string pattern table */
static const
ST_MSGTBL mp540_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN03},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp540 djs string pattern table */
static const
ST_MSGTBL mp540_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN01},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp540 doc string pattern table */
static const
ST_MSGTBL mp540_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN04},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'H',	OC1401_CARTRIDGENONE_PATTERN02},
  {'r',	OC1403_CARTRIDGENONE_PATTERN02},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN02},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN02},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN04},
  {'u', OC1600_INKOUT_TANK_PATTERN02},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN03},
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp540 dsc string pattern table */
static const
ST_MSGTBL mp540_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for mp540 dws string pattern table */
static const
ST_MSGTBL mp540_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp540 doc pict area pattern table */
static const
ST_MSGTBL mp540_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.00 for mp540 dbs pict area pattern table */
static const
ST_MSGTBL mp540_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp540 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp540_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp540 doc icon delete pattern table */
static const
ST_MSGTBL mp540_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* iP4600 */
/* Ver.3.00 for ip4600 dbs string pattern table */
static const
ST_MSGTBL ip4600_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4600 djs string pattern table */
static const
ST_MSGTBL ip4600_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN03},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip4600 doc string pattern table */
static const
ST_MSGTBL ip4600_doc_string_pattern_table[]={
  /* operator level1 */
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN03},
  {'p',	OC1003_PAPEROUT_PATTERN03},
  {'q',	OC1300_PAPERJAM_PATTERN03},
  {'n',	OC1303_PAPERJAM_PATTERN03},
  {'i',	OC1304_PAPERJAM_PATTERN03},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN01},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN01},
  {'N', OC2500_HEADALIGNMENT_PATTERN01},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN01},
  {'u', OC1600_INKOUT_TANK_PATTERN01},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN01},
  {'K', OC1856_CDR_GUIDE_PATTERN01},
  {ENDTAG, 	0}
};

/* Ver.3.00 for ip4600 dsc string pattern table */
static const
ST_MSGTBL ip4600_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4600 dws string pattern table */
static const
ST_MSGTBL ip4600_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4600 doc pict area pattern table */
static const
ST_MSGTBL ip4600_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.00 for ip4600 dbs pict area pattern table */
static const
ST_MSGTBL ip4600_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4600 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip4600_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for ip4600 doc icon delete pattern table */
static const
ST_MSGTBL ip4600_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* mp630 */
/* Ver.3.00 for mp630 dbs string pattern table */
static const
ST_MSGTBL mp630_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp630 djs string pattern table */
static const
ST_MSGTBL mp630_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN01},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp630 doc string pattern table */
static const
ST_MSGTBL mp630_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN04},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'i',	OC1304_PAPERJAM_PATTERN04},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN02},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN02},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN02},
  {'N', OC2500_HEADALIGNMENT_PATTERN02},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN04},
  {'u', OC1600_INKOUT_TANK_PATTERN02},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN02},
  {'K', OC1856_CDR_GUIDE_PATTERN02},
  {ENDTAG, 	0}
};

/* Ver.3.00 for mp630 dsc string pattern table */
static const
ST_MSGTBL mp630_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN01},
  {'J', SC5B01_USEDTANK_FULL_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.00 for mp630 dws string pattern table */
static const
ST_MSGTBL mp630_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp630 doc pict area pattern table */
static const
ST_MSGTBL mp630_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp630 dbs pict area pattern table */
static const
ST_MSGTBL mp630_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp630 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp630_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.00 for mp630 doc icon delete pattern table */
static const
ST_MSGTBL mp630_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* Ver.3.00 for all model dbs pattern table */
static const
ST_MODEL_PATTERN_TBL dbs_model_pattern_table[]={
  {"IP3300",	ip3300_dbs_string_pattern_table	},
  {"IP3500",	ip3500_dbs_string_pattern_table	},
  {"MP510",		mp510_dbs_string_pattern_table	},
  {"MP520",		mp520_dbs_string_pattern_table	},
  {"IP4300",	ip4300_dbs_string_pattern_table	},
  {"IP4500",	ip4500_dbs_string_pattern_table	},
  {"MP600",		mp600_dbs_string_pattern_table	},
  {"MP610",		mp610_dbs_string_pattern_table	},
  {"IP1800",	ip1900_dbs_string_pattern_table	},
  {"IP2500",	ip1900_dbs_string_pattern_table	},
  {"MP140",		mp190_dbs_string_pattern_table	},
  {"MP210",		mp190_dbs_string_pattern_table	},
  {"IP100",		ip100_dbs_string_pattern_table	},
  {"IP2600",	ip1900_dbs_string_pattern_table	},
  {"IP1900",	ip1900_dbs_string_pattern_table	},
  {"MP190",		mp190_dbs_string_pattern_table	},
  {"MP240",		mp240_dbs_string_pattern_table	},
  {"IP4600",	ip4600_dbs_string_pattern_table	},
  {"IP3600",	ip3600_dbs_string_pattern_table	},
  {"MP630",		mp630_dbs_string_pattern_table	},
  {"MP540",		mp540_dbs_string_pattern_table	},
  {ENDTAG, 		0}
};


/* Ver.3.00 for all model djs pattern table */
static const
ST_MODEL_PATTERN_TBL djs_model_pattern_table[]={
  {"IP3300",	ip3300_djs_string_pattern_table	},
  {"IP3500",	ip3500_djs_string_pattern_table	},
  {"MP510",		mp510_djs_string_pattern_table	},
  {"MP520",		mp520_djs_string_pattern_table	},
  {"IP4300",	ip4300_djs_string_pattern_table	},
  {"IP4500",	ip4500_djs_string_pattern_table	},
  {"MP600",		mp600_djs_string_pattern_table	},
  {"MP610",		mp610_djs_string_pattern_table	},
  {"IP1800",	ip1900_djs_string_pattern_table	},
  {"IP2500",	ip1900_djs_string_pattern_table	},
  {"MP140",		mp190_djs_string_pattern_table	},
  {"MP210",		mp190_djs_string_pattern_table	},
  {"IP100",		ip100_djs_string_pattern_table	},
  {"IP2600",	ip1900_djs_string_pattern_table	},
  {"IP1900",	ip1900_djs_string_pattern_table	},
  {"MP190",		mp190_djs_string_pattern_table	},
  {"MP240",		mp240_djs_string_pattern_table	},
  {"IP4600",	ip4600_djs_string_pattern_table	},
  {"IP3600",	ip3600_djs_string_pattern_table	},
  {"MP630",		mp630_djs_string_pattern_table	},
  {"MP540",		mp540_djs_string_pattern_table	},
  {ENDTAG, 		0}
};


/* Ver.3.00 for all model doc pattern table */
static const
ST_MODEL_PATTERN_TBL doc_model_pattern_table[]={
  {"IP3300",	ip3300_doc_string_pattern_table	},
  {"IP3500",	ip3500_doc_string_pattern_table	},
  {"MP510",		mp510_doc_string_pattern_table	},
  {"MP520",		mp520_doc_string_pattern_table	},
  {"IP4300",	ip4300_doc_string_pattern_table	},
  {"IP4500",	ip4500_doc_string_pattern_table	},
  {"MP600",		mp600_doc_string_pattern_table	},
  {"MP610",		mp610_doc_string_pattern_table	},
  {"IP1800",	ip1900_doc_string_pattern_table	},
  {"IP2500",	ip1900_doc_string_pattern_table	},
  {"MP140",		mp190_doc_string_pattern_table	},
  {"MP210",		mp190_doc_string_pattern_table	},
  {"IP100",		ip100_doc_string_pattern_table	},
  {"IP2600",	ip1900_doc_string_pattern_table	},
  {"IP1900",	ip1900_doc_string_pattern_table	},
  {"MP190",		mp190_doc_string_pattern_table	},
  {"MP240",		mp240_doc_string_pattern_table	},
  {"IP4600",	ip4600_doc_string_pattern_table	},
  {"IP3600",	ip3600_doc_string_pattern_table	},
  {"MP630",		mp630_doc_string_pattern_table	},
  {"MP540",		mp540_doc_string_pattern_table	},
  {ENDTAG, 		0}
};

/* Ver.3.00 for all model dsc pattern table */
static const
ST_MODEL_PATTERN_TBL dsc_model_pattern_table[]={
  {"IP3300",	ip3300_dsc_string_pattern_table	},
  {"IP3500",	ip3500_dsc_string_pattern_table	},
  {"MP510",		mp510_dsc_string_pattern_table	},
  {"MP520",		mp520_dsc_string_pattern_table	},
  {"IP4300",	ip4300_dsc_string_pattern_table	},
  {"IP4500",	ip4500_dsc_string_pattern_table	},
  {"MP600",		mp600_dsc_string_pattern_table	},
  {"MP610",		mp610_dsc_string_pattern_table	},
  {"IP1800",	ip1900_dsc_string_pattern_table	},
  {"IP2500",	ip1900_dsc_string_pattern_table	},
  {"MP140",		mp190_dsc_string_pattern_table	},
  {"MP210",		mp190_dsc_string_pattern_table	},
  {"IP100",		ip100_dsc_string_pattern_table	},
  {"IP2600",	ip1900_dsc_string_pattern_table	},
  {"IP1900",	ip1900_dsc_string_pattern_table	},
  {"MP190",		mp190_dsc_string_pattern_table	},
  {"MP240",		mp240_dsc_string_pattern_table	},
  {"IP4600",	ip4600_dsc_string_pattern_table	},
  {"IP3600",	ip3600_dsc_string_pattern_table	},
  {"MP630",		mp630_dsc_string_pattern_table	},
  {"MP540",		mp540_dsc_string_pattern_table	},
  {ENDTAG, 		0}
};


/* Ver.3.00 for all model dws pattern table */
static const
ST_MODEL_PATTERN_TBL dws_model_pattern_table[]={
  {"IP3300",	ip3300_dws_string_pattern_table	},
  {"IP3500",	ip3500_dws_string_pattern_table	},
  {"MP510",		mp510_dws_string_pattern_table	},
  {"MP520",		mp520_dws_string_pattern_table	},
  {"IP4300",	ip4300_dws_string_pattern_table	},
  {"IP4500",	ip4500_dws_string_pattern_table	},
  {"MP600",		mp600_dws_string_pattern_table	},
  {"MP610",		mp610_dws_string_pattern_table	},
  {"IP1800",	ip1900_dws_string_pattern_table	},
  {"IP2500",	ip1900_dws_string_pattern_table	},
  {"MP140",		mp190_dws_string_pattern_table	},
  {"MP210",		mp190_dws_string_pattern_table	},
  {"IP100",		ip100_dws_string_pattern_table	},
  {"IP2600",	ip1900_dws_string_pattern_table	},
  {"IP1900",	ip1900_dws_string_pattern_table	},
  {"MP190",		mp190_dws_string_pattern_table	},
  {"MP240",		mp240_dws_string_pattern_table	},
  {"IP4600",	ip4600_dws_string_pattern_table	},
  {"IP3600",	ip3600_dws_string_pattern_table	},
  {"MP630",		mp630_dws_string_pattern_table	},
  {"MP540",		mp540_dws_string_pattern_table	},
  {ENDTAG, 		0}
};

/* Ver.3.00 for all model doc pictdisable pattern table */
static const
ST_MODEL_PATTERN_TBL doc_pict_disable_pattern_table[]={
  {"IP3300",	ip3300_doc_pict_disable_pattern_table	},
  {"IP3500",	ip3500_doc_pict_disable_pattern_table	},
  {"MP510",		mp510_doc_pict_disable_pattern_table	},
  {"MP520",		mp520_doc_pict_disable_pattern_table	},
  {"IP4300",	ip4300_doc_pict_disable_pattern_table	},
  {"IP4500",	ip4500_doc_pict_disable_pattern_table	},
  {"MP600",		mp600_doc_pict_disable_pattern_table	},
  {"MP610",		mp610_doc_pict_disable_pattern_table	},
  {"IP1800",	ip1900_doc_pict_disable_pattern_table	},
  {"IP2500",	ip1900_doc_pict_disable_pattern_table	},
  {"MP140",		mp190_doc_pict_disable_pattern_table	},
  {"MP210",		mp190_doc_pict_disable_pattern_table	},
  {"IP100",		ip100_doc_pict_disable_pattern_table	},
  {"IP2600",	ip1900_doc_pict_disable_pattern_table	},
  {"IP1900",	ip1900_doc_pict_disable_pattern_table	},
  {"MP190",		mp190_doc_pict_disable_pattern_table	},
  {"MP240",		mp240_doc_pict_disable_pattern_table	},
  {"IP3600",	ip3600_doc_pict_disable_pattern_table	},
  {"MP540",		mp540_doc_pict_disable_pattern_table	},
  {"IP4600",	ip4600_doc_pict_disable_pattern_table	},
  {"MP630",		mp630_doc_pict_disable_pattern_table	},
  {ENDTAG, 		0}
};

/* Ver.3.00 for all model dbs pictdisable pattern table */
static const
ST_MODEL_PATTERN_TBL dbs_pict_disable_pattern_table[]={
  {"IP3300",	ip3300_dbs_pict_disable_pattern_table	},
  {"IP3500",	ip3500_dbs_pict_disable_pattern_table	},
  {"MP510",		mp510_dbs_pict_disable_pattern_table	},
  {"MP520",		mp520_dbs_pict_disable_pattern_table	},
  {"IP4300",	ip4300_dbs_pict_disable_pattern_table	},
  {"IP4500",	ip4500_dbs_pict_disable_pattern_table	},
  {"MP600",		mp600_dbs_pict_disable_pattern_table	},
  {"MP610",		mp610_dbs_pict_disable_pattern_table	},
  {"IP4300",	ip4300_dbs_pict_disable_pattern_table	},
  {"IP4500",	ip4500_dbs_pict_disable_pattern_table	},
  {"MP600",		mp600_dbs_pict_disable_pattern_table	},
  {"MP610",		mp610_dbs_pict_disable_pattern_table	},
  {"IP1800",	ip1900_dbs_pict_disable_pattern_table	},
  {"IP2500",	ip1900_dbs_pict_disable_pattern_table	},
  {"MP140",		mp190_dbs_pict_disable_pattern_table	},
  {"MP210",		mp190_dbs_pict_disable_pattern_table	},
  {"IP100",		ip100_dbs_pict_disable_pattern_table	},
  {"IP2600",	ip1900_dbs_pict_disable_pattern_table	},
  {"IP1900",	ip1900_dbs_pict_disable_pattern_table	},
  {"MP190",		mp190_dbs_pict_disable_pattern_table	},
  {"MP240",		mp240_dbs_pict_disable_pattern_table	},
  {"IP3600",	ip3600_dbs_pict_disable_pattern_table	},
  {"MP540",		mp540_dbs_pict_disable_pattern_table	},
  {"IP4600",	ip4600_dbs_pict_disable_pattern_table	},
  {"MP630",		mp630_dbs_pict_disable_pattern_table	},
  {ENDTAG, 		0}
};

/* Ver.3.00 for all model doc unknownicon draw table */
static const
ST_MODEL_PATTERN_TBL doc_unknownicon_draw_pattern_table[]={
  {"IP3300",	ip3300_doc_unknownicon_draw_pattern_table	},
  {"IP3500",	ip3500_doc_unknownicon_draw_pattern_table	},
  {"MP510",		mp510_doc_unknownicon_draw_pattern_table	},
  {"MP520",		mp520_doc_unknownicon_draw_pattern_table	},
  {"IP4300",	ip4300_doc_unknownicon_draw_pattern_table	},
  {"IP4500",	ip4500_doc_unknownicon_draw_pattern_table	},
  {"MP600",		mp600_doc_unknownicon_draw_pattern_table	},
  {"MP610",		mp610_doc_unknownicon_draw_pattern_table	},
  {"IP1800",	ip1900_doc_unknownicon_draw_pattern_table	},
  {"IP2500",	ip1900_doc_unknownicon_draw_pattern_table	},
  {"MP140",		mp190_doc_unknownicon_draw_pattern_table	},
  {"MP210",		mp190_doc_unknownicon_draw_pattern_table	},
  {"IP100",		ip100_doc_unknownicon_draw_pattern_table	},
  {"IP2600",	ip1900_doc_unknownicon_draw_pattern_table	},
  {"IP1900",	ip1900_doc_unknownicon_draw_pattern_table	},
  {"MP190",		mp190_doc_unknownicon_draw_pattern_table	},
  {"MP240",		mp240_doc_unknownicon_draw_pattern_table	},
  {"IP3600",	ip3600_doc_unknownicon_draw_pattern_table	},
  {"MP540",		mp540_doc_unknownicon_draw_pattern_table	},
  {"IP4600",	ip4600_doc_unknownicon_draw_pattern_table	},
  {"MP630",		mp630_doc_unknownicon_draw_pattern_table	},
  {ENDTAG, 		0}
};

/* Ver.3.00 for all model doc icon delete table */
static const
ST_MODEL_PATTERN_TBL doc_icon_delete_pattern_table[]={
  {"IP3300",	ip3300_doc_icon_delete_pattern_table	},
  {"IP3500",	ip3500_doc_icon_delete_pattern_table	},
  {"MP510",		mp510_doc_icon_delete_pattern_table		},
  {"MP520",		mp520_doc_icon_delete_pattern_table		},
  {"IP4300",	ip4300_doc_icon_delete_pattern_table	},
  {"IP4500",	ip4500_doc_icon_delete_pattern_table	},
  {"MP600",		mp600_doc_icon_delete_pattern_table		},
  {"MP610",		mp610_doc_icon_delete_pattern_table		},
  {"IP1800",	ip1900_doc_icon_delete_pattern_table	},
  {"IP2500",	ip1900_doc_icon_delete_pattern_table	},
  {"MP140",		mp190_doc_icon_delete_pattern_table		},
  {"MP210",		mp190_doc_icon_delete_pattern_table		},
  {"IP100",		ip100_doc_icon_delete_pattern_table		},
  {"IP2600",	ip1900_doc_icon_delete_pattern_table	},
  {"IP1900",	ip1900_doc_icon_delete_pattern_table	},
  {"MP190",		mp190_doc_icon_delete_pattern_table		},
  {"MP240",		mp240_doc_icon_delete_pattern_table		},
  {"IP3600",	ip3600_doc_icon_delete_pattern_table	},
  {"MP540",		mp540_doc_icon_delete_pattern_table		},
  {"IP4600",	ip4600_doc_icon_delete_pattern_table	},
  {"MP630",		mp630_doc_icon_delete_pattern_table		},
  {ENDTAG, 		0}
};


static const
ST_DOCCTKTBL ctk_tbl[]={
  // DOC, CTK
  //inkout inkempty
  { 'u', 'I'}, /* (B-4  ) DOC:1600 */
  { 'C', 'Y'}, /* (B-53 ) DOC:1688 */
  //{ 'C', 'r'}, /* (B-36 ) DOC:1689 */
  //other
  { 'H', 'E'}, /* (B-1  ) DOC:1401 */
  { 'd', 'E'}, /* (B-21 ) DOC:1660 */
  { 's', 'M'}, /* (B-31 ) DOC:1681 */
  { 'e', 'E'}, /* (B-32 ) DOC:1684 */
  { 'S', 'P'}, /* (B-35 ) DOC:1680 */
  { 'f', 'R'}, /* (B-36 ) DOC:1683 */
  { 'z', 'R'}, /* (B-36 ) DOC:1689 */
  { 'w', 'R'}, /* (B-38 ) DOC:1686 */
  // DWS, CTK
  { 'T', 'L'}, /* (D-1  ) DWS:1500 */
  { 'T', 'l'}, /* (D-1  ) DWS:1499 */
  { 'F', 'I'}, /* (B-4R ) DWS:1570 */
  { 'Z', 'Z'}, /* (B-36R) DWS:NO(temp Z) */
  { 'z', 'r'}, /* (B-36R) DWS:NO(temp z) */
  {ENDTAG, 	0}
};


/* Ver.3.00 for PDR */
static const
ST_MSGCNVPDRTBL msg_cnv_pdr[]={
  //InkLow 1st
  {'1', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*Japan*/
  {'2', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*Korea*/
  {'3', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*America*/
  {'4', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*Europe*/
  {'5', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*Australia*/
  {'6', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*Asia*/
  {'7', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*Laten America*/
  {'A', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*Brazil*/
  {'B', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*Canada*/
  {' ', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*PDR No Region*/
  //InkLow 3rd
  {'1', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*Japan*/
  {'2', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*Korea*/
  {'3', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*America*/
  {'4', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*Europe*/
  {'5', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*Australia*/
  {'6', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*Asia*/
  {'7', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*Laten America*/
  {'A', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*Brazil*/
  {'B', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*Canada*/
  {' ', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*PDR No Region*/
  //InkUnknown 1st
  {'1', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*America*/
  {'4', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*Canada*/
  {' ', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*PDR No Region*/
  //InkUnknown 3rd
  {'1', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*America*/
  {'4', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*Canada*/
  {' ', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*PDR No Region*/
  //InkOut RESUME
  {'1', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*Canada*/
  {' ', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*PDR No Region*/
  //InkOut OK
  {'1', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*Canada*/
  {' ', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*PDR No Region*/
  //InkEmpty RESUME
  {'1', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*Canada*/
  {' ', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*PDR No Region*/
  //InkEmpty STOP/RESET
  {'1', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*Canada*/
  {' ', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*PDR No Region*/
  //InkEmpty STOP
  {'1', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*Canada*/
  {' ', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*PDR No Region*/

  {ENDTAG, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, 0} /*default*/
};

