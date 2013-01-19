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
ST_MSGTBL cartridge_type2_CHN[]={
  {'U', ID_STS_MESSAGE_INK_BLACK815},
  {'V', ID_STS_MESSAGE_INK_COLOR816},
  {'L', ID_STS_MESSAGE_INK_BLACK815XL},
  {'M', ID_STS_MESSAGE_INK_COLOR816XL},
  {'N', ID_STS_MESSAGE_INK_BLACK815},
  {'O', ID_STS_MESSAGE_INK_COLOR816},
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
  {'C', cartridge_type2_CHN},
  {ENDTAG, 0}
};


static const
ST_MSGTBL cartridge_type3_0[]={
  {'U', ID_STS_MESSAGE_INK_BLACK},
  {'V', ID_STS_MESSAGE_INK_COLOR},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK},
  {'O', ID_STS_MESSAGE_INK_COLOR},
  {']', ID_STS_MESSAGE_INK_BLACK},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type3_SouthAmerica[]={
  {'U', ID_STS_MESSAGE_INK_BLACK140},
  {'V', ID_STS_MESSAGE_INK_COLOR141},
  {'L', ID_STS_MESSAGE_INK_BLACK140XL},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK},
  {'O', ID_STS_MESSAGE_INK_COLOR141XL},
  {']', ID_STS_MESSAGE_INK_BLACK140XXL},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type3_NorthAmerica[]={
  {'U', ID_STS_MESSAGE_INK_BLACK240},
  {'V', ID_STS_MESSAGE_INK_COLOR241},
  {'L', ID_STS_MESSAGE_INK_BLACK240XL},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK},
  {'O', ID_STS_MESSAGE_INK_COLOR241XL},
  {']', ID_STS_MESSAGE_INK_BLACK240XXL},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type3_Japan[]={
  {'U', ID_STS_MESSAGE_INK_BLACK340},
  {'V', ID_STS_MESSAGE_INK_COLOR341},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK340XL},
  {'O', ID_STS_MESSAGE_INK_COLOR341XL},
  {']', ID_STS_MESSAGE_INK_BLACK},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type3_EMBU[]={
  {'U', ID_STS_MESSAGE_INK_BLACK440},
  {'V', ID_STS_MESSAGE_INK_COLOR441},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK},
  {'O', ID_STS_MESSAGE_INK_COLOR441XL},
  {']', ID_STS_MESSAGE_INK_BLACK440XL},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type3_Europe[]={
  {'U', ID_STS_MESSAGE_INK_BLACK540},
  {'V', ID_STS_MESSAGE_INK_COLOR541},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK},
  {'O', ID_STS_MESSAGE_INK_COLOR541XL},
  {']', ID_STS_MESSAGE_INK_BLACK540XL},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type3_Oceania[]={
  {'U', ID_STS_MESSAGE_INK_BLACK640},
  {'V', ID_STS_MESSAGE_INK_COLOR641},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK640XL},
  {'O', ID_STS_MESSAGE_INK_COLOR641XL},
  {']', ID_STS_MESSAGE_INK_BLACK640XXL},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type3_Asia[]={
  {'U', ID_STS_MESSAGE_INK_BLACK740},
  {'V', ID_STS_MESSAGE_INK_COLOR741},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK740XL},
  {'O', ID_STS_MESSAGE_INK_COLOR741XL},
  {']', ID_STS_MESSAGE_INK_BLACK},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type3_China[]={
  {'U', ID_STS_MESSAGE_INK_BLACK840},
  {'V', ID_STS_MESSAGE_INK_COLOR841},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK840XL},
  {'O', ID_STS_MESSAGE_INK_COLOR841XL},
  {']', ID_STS_MESSAGE_INK_BLACK},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type3_LCPP[]={
  {'U', ID_STS_MESSAGE_INK_BLACK},
  {'V', ID_STS_MESSAGE_INK_COLOR},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK},
  {'O', ID_STS_MESSAGE_INK_COLOR98},
  {']', ID_STS_MESSAGE_INK_BLACK88},
  {ENDTAG, 0}
};

static const
ST_MSGTBL cartridge_type3_ChinaLCPP2[]={
  {'U', ID_STS_MESSAGE_INK_BLACK},
  {'V', ID_STS_MESSAGE_INK_COLOR},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'M', ID_STS_MESSAGE_INK_COLOR},
  {'N', ID_STS_MESSAGE_INK_BLACK},
  {'O', ID_STS_MESSAGE_INK_COLOR93},
  {']', ID_STS_MESSAGE_INK_BLACK83},
  {ENDTAG, 0}
};


static const
ST_REGION_TBL cartridge_type3_region_tbl[]={
  {'0', cartridge_type3_0},
  {'1', cartridge_type3_SouthAmerica},
  {'2', cartridge_type3_NorthAmerica},
  {'3', cartridge_type3_Japan},
  {'4', cartridge_type3_EMBU},
  {'7', cartridge_type3_Asia},
  {'8', cartridge_type3_China},
  {'B', cartridge_type3_LCPP},
  {'D', cartridge_type3_Europe},
  {'E', cartridge_type3_Oceania},
  {'F', cartridge_type3_ChinaLCPP2},
  {'G', cartridge_type3_LCPP},
  {ENDTAG, 0}
};


static const
ST_REGION_TBL cartridge_type22_region_tbl[]={
  {'0', cartridge_type2_ZZZ},
  {'3', cartridge_type2_JP},
  {'7', cartridge_type2_ASI},
  {'8', cartridge_type2_CHN},
  {'9', cartridge_type2_PAM},
  {'C', cartridge_type2_EU},
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
ST_MSGTBL ink_type2_Other[]={
  {'H', ID_STS_MESSAGE_INK_GLAY226},
  {'l', ID_STS_MESSAGE_INK_BLACK225},
  {'L', ID_STS_MESSAGE_INK_BLACK226},
  {'C', ID_STS_MESSAGE_INK_CYAN226},
  {'M', ID_STS_MESSAGE_INK_MAGENTA226},
  {'Y', ID_STS_MESSAGE_INK_YELLOW226},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type2_0[]={
  {'H', ID_STS_MESSAGE_INK_GLAY},
  {'l', ID_STS_MESSAGE_INK_BLACK},
  {'L', ID_STS_MESSAGE_INK_BLACK},
  {'C', ID_STS_MESSAGE_INK_CYAN},
  {'M', ID_STS_MESSAGE_INK_MAGENTA},
  {'Y', ID_STS_MESSAGE_INK_YELLOW},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type2_SouthAmerica[]={
  {'H', ID_STS_MESSAGE_INK_GLAY126},
  {'l', ID_STS_MESSAGE_INK_BLACK125},
  {'L', ID_STS_MESSAGE_INK_BLACK126},
  {'C', ID_STS_MESSAGE_INK_CYAN126},
  {'M', ID_STS_MESSAGE_INK_MAGENTA126},
  {'Y', ID_STS_MESSAGE_INK_YELLOW126},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type2_NorthAmerica[]={
  {'H', ID_STS_MESSAGE_INK_GLAY226},
  {'l', ID_STS_MESSAGE_INK_BLACK225},
  {'L', ID_STS_MESSAGE_INK_BLACK226},
  {'C', ID_STS_MESSAGE_INK_CYAN226},
  {'M', ID_STS_MESSAGE_INK_MAGENTA226},
  {'Y', ID_STS_MESSAGE_INK_YELLOW226},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type2_Japan[]={
  {'H', ID_STS_MESSAGE_INK_GLAY326},
  {'l', ID_STS_MESSAGE_INK_BLACK325},
  {'L', ID_STS_MESSAGE_INK_BLACK326},
  {'C', ID_STS_MESSAGE_INK_CYAN326},
  {'M', ID_STS_MESSAGE_INK_MAGENTA326},
  {'Y', ID_STS_MESSAGE_INK_YELLOW326},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type2_EMBU[]={
  {'H', ID_STS_MESSAGE_INK_GLAY426},
  {'l', ID_STS_MESSAGE_INK_BLACK425},
  {'L', ID_STS_MESSAGE_INK_BLACK426},
  {'C', ID_STS_MESSAGE_INK_CYAN426},
  {'M', ID_STS_MESSAGE_INK_MAGENTA426},
  {'Y', ID_STS_MESSAGE_INK_YELLOW426},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type2_Europe[]={
  {'H', ID_STS_MESSAGE_INK_GLAY526},
  {'l', ID_STS_MESSAGE_INK_BLACK525},
  {'L', ID_STS_MESSAGE_INK_BLACK526},
  {'C', ID_STS_MESSAGE_INK_CYAN526},
  {'M', ID_STS_MESSAGE_INK_MAGENTA526},
  {'Y', ID_STS_MESSAGE_INK_YELLOW526},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type2_Asia[]={
  {'H', ID_STS_MESSAGE_INK_GLAY726},
  {'l', ID_STS_MESSAGE_INK_BLACK725},
  {'L', ID_STS_MESSAGE_INK_BLACK726},
  {'C', ID_STS_MESSAGE_INK_CYAN726},
  {'M', ID_STS_MESSAGE_INK_MAGENTA726},
  {'Y', ID_STS_MESSAGE_INK_YELLOW726},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type2_China[]={
  {'H', ID_STS_MESSAGE_INK_GLAY826},
  {'l', ID_STS_MESSAGE_INK_BLACK825},
  {'L', ID_STS_MESSAGE_INK_BLACK826},
  {'C', ID_STS_MESSAGE_INK_CYAN826},
  {'M', ID_STS_MESSAGE_INK_MAGENTA826},
  {'Y', ID_STS_MESSAGE_INK_YELLOW826},
  {ENDTAG, 0}
};

static const
ST_MSGTBL ink_type3_0[]={
  {'H', ID_STS_MESSAGE_INK_GLAY0},
  {'l', ID_STS_MESSAGE_INK_BLACK1},
  {'L', ID_STS_MESSAGE_INK_BLACK0},
  {'C', ID_STS_MESSAGE_INK_CYAN0},
  {'M', ID_STS_MESSAGE_INK_MAGENTA0},
  {'Y', ID_STS_MESSAGE_INK_YELLOW0},
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

static const
ST_REGION_TBL ink_type2_region_tbl[]={
  {'0', ink_type2_0},
  {'1', ink_type2_SouthAmerica},
  {'2', ink_type2_NorthAmerica},
  {'3', ink_type2_Japan},
  {'4', ink_type2_EMBU},
  {'5', ink_type2_Europe},
  {'7', ink_type2_Asia},
  {'8', ink_type2_China},
  {'*', ink_type2_Other},
  {ENDTAG, 0}
};

static const
ST_REGION_TBL ink_type3_region_tbl[]={
  {'0', ink_type3_0},
  {'*', ink_type3_0},
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
  {"MX860",   ink_type1_region_tbl},
  {"MX320",   cartridge_type2_region_tbl},
  {"MX330",   cartridge_type2_region_tbl},
  {"MP250",   cartridge_type2_region_tbl},
  {"MP270",   cartridge_type2_region_tbl},
  {"MP490",   cartridge_type2_region_tbl},
  {"MP550",   ink_type1_region_tbl},
  {"MP560",   ink_type1_region_tbl},
  {"MP640",   ink_type1_region_tbl},
  {"IP4700",  ink_type1_region_tbl},
  {"IP2700",  cartridge_type2_region_tbl},
  {"MX340",   cartridge_type2_region_tbl},
  {"MX350",   cartridge_type2_region_tbl},
  {"MX870",   ink_type1_region_tbl},
  {"MP280",   cartridge_type2_region_tbl},
  {"MP495",   cartridge_type2_region_tbl},
  {"MG5100",  ink_type2_region_tbl},
  {"IP4800",  ink_type2_region_tbl},
  {"MG5200",  ink_type2_region_tbl},
  {"MG6100",  ink_type2_region_tbl},
  {"MG8100",  ink_type2_region_tbl},
  {"MX360",   cartridge_type2_region_tbl},
  {"MX410",   cartridge_type2_region_tbl},
  {"MX420",   cartridge_type2_region_tbl},
  {"MX880",   ink_type2_region_tbl},
  {"IX6500",  ink_type2_region_tbl},
  {"E500",    cartridge_type3_region_tbl},
  {"MG2100",  cartridge_type3_region_tbl},
  {"MG3100",  cartridge_type3_region_tbl},
  {"MG4100",  cartridge_type3_region_tbl},
  {"MG5300",  ink_type2_region_tbl},
  {"IP4900",  ink_type2_region_tbl},
  {"MG6200",  ink_type2_region_tbl},
  {"MG8200",  ink_type2_region_tbl},
  {"E600",    cartridge_type3_region_tbl},
  {"MX370",   cartridge_type3_region_tbl},
  {"MX430",   cartridge_type3_region_tbl},
  {"MX510",   cartridge_type3_region_tbl},
  {"MX710",   ink_type2_region_tbl},
  {"MX890",   ink_type2_region_tbl},
  {"MP230",   cartridge_type22_region_tbl},
  {"E510",    cartridge_type3_region_tbl},
  {"MG2200",  cartridge_type3_region_tbl},
  {"MG3200",  cartridge_type3_region_tbl},
  {"MG4200",  cartridge_type3_region_tbl},
  {"MG5400",  ink_type3_region_tbl},
  {"IP7200",  ink_type3_region_tbl},
  {"MG6300",  ink_type3_region_tbl},
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
  {'H', ID_STS_MESSAGE_COLOR_TYPE},
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
  {"MX860",   color_ip4200},
  {"MX320",   color_ip2200},
  {"MX330",   color_ip2200},
  {"MP250",   color_ip2200},
  {"MP270",   color_ip2200},
  {"MP490",   color_ip2200},
  {"MP550",   color_ip4200},
  {"MP560",   color_ip4200},
  {"MP640",   color_ip4200},
  {"IP4700",  color_ip4200},
  {"IP2700",  color_ip2200},
  {"MX340",   color_ip2200},
  {"MX350",   color_ip2200},
  {"MX870",   color_ip4200},
  {"MP280",   color_ip2200},
  {"MP495",   color_ip2200},
  {"MG5100",  color_ip4200},
  {"IP4800",  color_ip4200},
  {"MG5200",  color_ip4200},
  {"MG6100",  color_ip4200},
  {"MG8100",  color_ip4200},
  {"MX360",   color_ip2200},
  {"MX410",   color_ip2200},
  {"MX420",   color_ip2200},
  {"MX880",   color_ip4200},
  {"IX6500",  color_ip4200},
  {"E500",    color_ip2200},
  {"MG2100",  color_ip2200},
  {"MG3100",  color_ip2200},
  {"MG4100",  color_ip2200},
  {"MG5300",  color_ip4200},
  {"IP4900",  color_ip4200},
  {"MG6200",  color_ip4200},
  {"MG8200",  color_ip4200},
  {"E600",    color_ip2200},
  {"MX370",   color_ip2200},
  {"MX430",   color_ip2200},
  {"MX510",   color_ip2200},
  {"MX710",   color_ip4200},
  {"MX890",   color_ip4200},
  {"MP230",   color_ip2200},
  {"E510",    color_ip2200},
  {"MG2200",  color_ip2200},
  {"MG3200",  color_ip2200},
  {"MG4200",  color_ip2200},
  {"MG5400",  color_ip4200},
  {"IP7200",  color_ip4200},
  {"MG6300",  color_ip4200},
  {ENDTAG, 0}
};

/* ip3300 */
/* Ver.3.00 for ip3300 dbs string pattern table */
static const
ST_MSGTBL ip3300_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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
// {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN01}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN01}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN01}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN03},/* A-06 */
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
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN03}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
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
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
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


/* mx860 */
/* Ver.3.10 for mx860 dbs string pattern table */
static const
ST_MSGTBL mx860_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.10 for mx860 djs string pattern table */
static const
ST_MSGTBL mx860_djs_string_pattern_table[]={
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

/* Ver.3.10 for mx860 doc string pattern table */
static const
ST_MSGTBL mx860_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN04},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'i',	OC1304_PAPERJAM_PATTERN04},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN04},
  {'u', OC1600_INKOUT_TANK_PATTERN03},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.10 for mx860 dsc string pattern table */
static const
ST_MSGTBL mx860_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.10 for mx860 dws string pattern table */
static const
ST_MSGTBL mx860_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.10 for mx860 doc pict area pattern table */
static const
ST_MSGTBL mx860_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.10 for mx860 dbs pict area pattern table */
static const
ST_MSGTBL mx860_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.10 for mx860 doc unknownicon draw pattern table */
static const
ST_MSGTBL mx860_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.10 for mx860 doc icon delete pattern table */
static const
ST_MSGTBL mx860_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* mx320/330 */
/* Ver.3.10 for mx320 dbs string pattern table */
static const
ST_MSGTBL mx320_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.10 for mx320 djs string pattern table */
static const
ST_MSGTBL mx320_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN01},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.10 for mx320 doc string pattern table */
static const
ST_MSGTBL mx320_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN07},
  {'q',	OC1300_PAPERJAM_PATTERN05},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN06},
  /* operator level3 */
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN04},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN01},
  {'o', OC1251_SMARTTRAY_CLOSE_PATTERN01},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN01}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.10 for mx320 dsc string pattern table */
static const
ST_MSGTBL mx320_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.10 for mx320 dws string pattern table */
static const
ST_MSGTBL mx320_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.10 for mx320 doc pict area pattern table */
static const
ST_MSGTBL mx320_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.10 for mx320 dbs pict area pattern table */
static const
ST_MSGTBL mx320_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.10 for mx320 doc unknownicon draw pattern table */
static const
ST_MSGTBL mx320_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.10 for mx320 doc icon delete pattern table */
static const
ST_MSGTBL mx320_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};


/* mp250/mp270 */
/* Ver.3.20 for mp270 dbs string pattern table */
static const
ST_MSGTBL mp270_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp270 djs string pattern table */
static const
ST_MSGTBL mp270_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.20 for mp270 doc string pattern table */
static const
ST_MSGTBL mp270_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN02},
  {'q',	OC1300_PAPERJAM_PATTERN02},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  {'r',	OC1403_CARTRIDGENONE_PATTERN03},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN05},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN05},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN03},
  /* operator level3 */
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN01},
  {'o', OC1251_SMARTTRAY_CLOSE_PATTERN02},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN01}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.20 for mp270 dsc string pattern table */
static const
ST_MSGTBL mp270_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'R', SC5100_CR_POSITIONEROOR_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.20 for mp270 dws string pattern table */
static const
ST_MSGTBL mp270_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.20 for mp270 doc pict area pattern table */
static const
ST_MSGTBL mp270_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp270 dbs pict area pattern table */
static const
ST_MSGTBL mp270_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp270 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp270_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp270 doc icon delete pattern table */
static const
ST_MSGTBL mp270_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};

/* mp490 */
/* Ver.3.20 for mp490 dbs string pattern table */
static const
ST_MSGTBL mp490_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp490 djs string pattern table */
static const
ST_MSGTBL mp490_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.20 for mp490 doc string pattern table */
static const
ST_MSGTBL mp490_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN07},
  {'q',	OC1300_PAPERJAM_PATTERN05},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN06},
  /* operator level3 */
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN04},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN01},
  {'o', OC1251_SMARTTRAY_CLOSE_PATTERN01},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN01}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.20 for mp490 dsc string pattern table */
static const
ST_MSGTBL mp490_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.20 for mp490 dws string pattern table */
static const
ST_MSGTBL mp490_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.20 for mp490 doc pict area pattern table */
static const
ST_MSGTBL mp490_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp490 dbs pict area pattern table */
static const
ST_MSGTBL mp490_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp490 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp490_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp490 doc icon delete pattern table */
static const
ST_MSGTBL mp490_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};


/* mp560 */
/* Ver.3.20 for mp560 dbs string pattern table */
static const
ST_MSGTBL mp560_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp560 djs string pattern table */
static const
ST_MSGTBL mp560_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.20 for mp560 doc string pattern table */
static const
ST_MSGTBL mp560_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN04},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'i',	OC1304_PAPERJAM_PATTERN04},
  {'H',	OC1401_CARTRIDGENONE_PATTERN02},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN02}, /* Ver.3.30 add */
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN03}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.20 for mp560 dsc string pattern table */
static const
ST_MSGTBL mp560_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.20 for mp560 dws string pattern table */
static const
ST_MSGTBL mp560_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp560 doc pict area pattern table */
static const
ST_MSGTBL mp560_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.20 for mp560 dbs pict area pattern table */
static const
ST_MSGTBL mp560_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp560 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp560_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp560 doc icon delete pattern table */
static const
ST_MSGTBL mp560_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};

/* iP4700 */
/* Ver.3.20 for ip4700 dbs string pattern table */
static const
ST_MSGTBL ip4700_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.20 for ip4700 djs string pattern table */
static const
ST_MSGTBL ip4700_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.20 for ip4700 doc string pattern table */
static const
ST_MSGTBL ip4700_doc_string_pattern_table[]={
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
  {'x', OC1700_USEDTANK_ALMOST_PATTERN06},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN06},
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN03},
  {'K', OC1856_CDR_GUIDE_PATTERN03},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.20 for ip4700 dsc string pattern table */
static const
ST_MSGTBL ip4700_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.20 for ip4700 dws string pattern table */
static const
ST_MSGTBL ip4700_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.20 for ip4700 doc pict area pattern table */
static const
ST_MSGTBL ip4700_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.20 for ip4700 dbs pict area pattern table */
static const
ST_MSGTBL ip4700_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.20 for ip4700 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip4700_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.20 for ip4700 doc icon delete pattern table */
static const
ST_MSGTBL ip4700_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* mp640 */
/* Ver.3.20 for mp640 dbs string pattern table */
static const
ST_MSGTBL mp640_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp640 djs string pattern table */
static const
ST_MSGTBL mp640_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.20 for mp640 doc string pattern table */
static const
ST_MSGTBL mp640_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN04},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'i',	OC1304_PAPERJAM_PATTERN04},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
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
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN04},
  {'K', OC1856_CDR_GUIDE_PATTERN04},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.20 for mp640 dsc string pattern table */
static const
ST_MSGTBL mp640_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.20 for mp640 dws string pattern table */
static const
ST_MSGTBL mp640_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp640 doc pict area pattern table */
static const
ST_MSGTBL mp640_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp640 dbs pict area pattern table */
static const
ST_MSGTBL mp640_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp640 doc unknownicon draw pattern table */
static const
ST_MSGTBL mp640_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.20 for mp640 doc icon delete pattern table */
static const
ST_MSGTBL mp640_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* mx870 */
/* Ver.3.30 for mx870 dbs string pattern table */
static const
ST_MSGTBL mx870_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.30 for mx870 djs string pattern table */
static const
ST_MSGTBL mx870_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.30 for mx870 doc string pattern table */
static const
ST_MSGTBL mx870_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN04},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'i',	OC1304_PAPERJAM_PATTERN04},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN02},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN04},
  {'u', OC1600_INKOUT_TANK_PATTERN03},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.30 for mx870 dsc string pattern table */
static const
ST_MSGTBL mx870_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.30 for mx870 dws string pattern table */
static const
ST_MSGTBL mx870_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.30 for mx870 doc pict area pattern table */
static const
ST_MSGTBL mx870_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.30 for mx870 dbs pict area pattern table */
static const
ST_MSGTBL mx870_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.30 for mx870 doc unknownicon draw pattern table */
static const
ST_MSGTBL mx870_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.30 for mx870 doc icon delete pattern table */
static const
ST_MSGTBL mx870_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {ENDTAG, 0}
};


/* mx340/350 */
/* Ver.3.30 for mx340 dbs string pattern table */
static const
ST_MSGTBL mx340_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.30 for mx340 djs string pattern table */
static const
ST_MSGTBL mx340_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.30 for mx340 doc string pattern table */
static const
ST_MSGTBL mx340_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN07},
  {'q',	OC1300_PAPERJAM_PATTERN05},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN06},
  /* operator level3 */
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN04},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN01},
  {'o', OC1251_SMARTTRAY_CLOSE_PATTERN01},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN01}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.30 for mx340 dsc string pattern table */
static const
ST_MSGTBL mx340_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.30 for mx340 dws string pattern table */
static const
ST_MSGTBL mx340_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.30 for mx340 doc pict area pattern table */
static const
ST_MSGTBL mx340_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.30 for mx340 dbs pict area pattern table */
static const
ST_MSGTBL mx340_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.30 for mx340 doc unknownicon draw pattern table */
static const
ST_MSGTBL mx340_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.30 for mx340 doc icon delete pattern table */
static const
ST_MSGTBL mx340_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};

/* ip2700 */
/* Ver.3.30 for ip2700 dbs string pattern table */
static const
ST_MSGTBL ip2700_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
//  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.30 for ip2700 djs string pattern table */
static const
ST_MSGTBL ip2700_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.30 for ip2700 doc string pattern table */
static const
ST_MSGTBL ip2700_doc_string_pattern_table[]={
  /* operator level1 */
  {'X',	OC1000_PAPEROUT_PATTERN01},
  {'q',	OC1300_PAPERJAM_PATTERN01},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN01},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN01},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN05},
  /* operator level3 */
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN03},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN01},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN01}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.30 for ip2700 dsc string pattern table */
static const
ST_MSGTBL ip2700_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.30 for ip2700 dws string pattern table */
static const
ST_MSGTBL ip2700_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.30 for ip2700 doc pict area pattern table */
static const
ST_MSGTBL ip2700_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.30 for ip2700 dbs pict area pattern table */
static const
ST_MSGTBL ip2700_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.30 for ip2700 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip2700_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.30 for ip2700 doc icon delete pattern table */
static const
ST_MSGTBL ip2700_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};

/* iP4800 */
/* Ver.3.30 for ip4800 dbs string pattern table */
static const
ST_MSGTBL ip4800_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.40 for ip4800 djs string pattern table */
static const
ST_MSGTBL ip4800_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.40 for ip4800 doc string pattern table */
static const
ST_MSGTBL ip4800_doc_string_pattern_table[]={
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
  {'x', OC1700_USEDTANK_ALMOST_PATTERN06},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN06},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN01}, /* Ver.3.30 add */
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
  {'F', OC1750_OLDINKTANK_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN03},
  {'K', OC1856_CDR_GUIDE_PATTERN03},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.40 for ip4800 dsc string pattern table */
static const
ST_MSGTBL ip4800_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.40 for ip4800 dws string pattern table */
static const
ST_MSGTBL ip4800_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.40 for ip4800 doc pict area pattern table */
static const
ST_MSGTBL ip4800_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.40 for ip4800 dbs pict area pattern table */
static const
ST_MSGTBL ip4800_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.40 for ip4800 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip4800_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.40 for ip4800 doc icon delete pattern table */
static const
ST_MSGTBL ip4800_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
  {ENDTAG, 0}
};


/* mg5200 */
/* Ver.3.40 for mg5200 dbs string pattern table */
static const
ST_MSGTBL mg5200_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.40 for mg5200 djs string pattern table */
static const
ST_MSGTBL mg5200_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.40 for mg5200 doc string pattern table */
static const
ST_MSGTBL mg5200_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN04},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'i',	OC1304_PAPERJAM_PATTERN04},
  {'H',	OC1401_CARTRIDGENONE_PATTERN02},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN02}, /* Ver.3.30 add */
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
  {'F', OC1750_OLDINKTANK_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN03},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN03}, /* DOC:1200 && DBC:CC   A-06 */
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN04},
  {'K', OC1856_CDR_GUIDE_PATTERN04},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.40 for mg5200 dsc string pattern table */
static const
ST_MSGTBL mg5200_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.40 for mg5200 dws string pattern table */
static const
ST_MSGTBL mg5200_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.40 for mg5200 doc pict area pattern table */
static const
ST_MSGTBL mg5200_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.40 for mg5200 dbs pict area pattern table */
static const
ST_MSGTBL mg5200_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.40 for mg5200 doc unknownicon draw pattern table */
static const
ST_MSGTBL mg5200_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.40 for mg5200 doc icon delete pattern table */
static const
ST_MSGTBL mg5200_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
  {ENDTAG, 0}
};


/* mg8100 */
/* Ver.3.40 for mg8100 dbs string pattern table */
static const
ST_MSGTBL mg8100_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.40 for mg8100 djs string pattern table */
static const
ST_MSGTBL mg8100_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.40 for mg8100 doc string pattern table */
static const
ST_MSGTBL mg8100_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN08},
  {'p',	OC1003_PAPEROUT_PATTERN09},
  {'q',	OC1300_PAPERJAM_PATTERN06},
  {'n',	OC1303_PAPERJAM_PATTERN09},
  {'i',	OC1304_PAPERJAM_PATTERN05},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN07},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN07},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN06},
  {'N', OC2500_HEADALIGNMENT_PATTERN03},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN07},
  {'u', OC1600_INKOUT_TANK_PATTERN04},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN01},
  {'F', OC1750_OLDINKTANK_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN08},
  {'K', OC1856_CDR_GUIDE_PATTERN05},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.40 for mg8100 dsc string pattern table */
static const
ST_MSGTBL mg8100_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'C', SC5101_CARRIAGEPOSITION_PATTERN01},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.40 for mg8100 dws string pattern table */
static const
ST_MSGTBL mg8100_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.40 for mg8100 doc pict area pattern table */
static const
ST_MSGTBL mg8100_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.40 for mg8100 dbs pict area pattern table */
static const
ST_MSGTBL mg8100_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.40 for mg8100 doc unknownicon draw pattern table */
static const
ST_MSGTBL mg8100_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.40 for mg8100 doc icon delete pattern table */
static const
ST_MSGTBL mg8100_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
  {ENDTAG, 0}
};


/* mx880 */
/* Ver.3.50 for mx880 dbs string pattern table */
static const
ST_MSGTBL mx880_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.50 for mx880 djs string pattern table */
static const
ST_MSGTBL mx880_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.50 for mx880 doc string pattern table */
static const
ST_MSGTBL mx880_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN04},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'i',	OC1304_PAPERJAM_PATTERN04},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN02},
  {'N', OC2500_HEADALIGNMENT_PATTERN02},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN04},
  {'u', OC1600_INKOUT_TANK_PATTERN03},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN01},
  {'F', OC1750_OLDINKTANK_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.50 for mx880 dsc string pattern table */
static const
ST_MSGTBL mx880_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.50 for mx880 dws string pattern table */
static const
ST_MSGTBL mx880_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.50 for mx880 doc pict area pattern table */
static const
ST_MSGTBL mx880_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.50 for mx880 dbs pict area pattern table */
static const
ST_MSGTBL mx880_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.50 for mx880 doc unknownicon draw pattern table */
static const
ST_MSGTBL mx880_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.50 for mx880 doc icon delete pattern table */
static const
ST_MSGTBL mx880_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
  {ENDTAG, 0}
};

/* iX6500 */
/* Ver.3.50 for ix6500 dbs string pattern table */
static const
ST_MSGTBL ix6500_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.50 for ix6500 djs string pattern table */
static const
ST_MSGTBL ix6500_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.50 for ix6500 doc string pattern table */
static const
ST_MSGTBL ix6500_doc_string_pattern_table[]={
  /* operator level1 */
  {'X',	OC1000_PAPEROUT_PATTERN03},
  {'q',	OC1300_PAPERJAM_PATTERN03},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN06},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN06},
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
  {'F', OC1750_OLDINKTANK_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'o', OC1250_COVER_CLOSE_PATTERN03},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.50 for ix6500 dsc string pattern table */
static const
ST_MSGTBL ix6500_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.50 for ix6500 dws string pattern table */
static const
ST_MSGTBL ix6500_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.50 for ix6500 doc pict area pattern table */
static const
ST_MSGTBL ix6500_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.50 for ix6500 dbs pict area pattern table */
static const
ST_MSGTBL ix6500_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.50 for ix6500 doc unknownicon draw pattern table */
static const
ST_MSGTBL ix6500_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.50 for ix6500 doc icon delete pattern table */
static const
ST_MSGTBL ix6500_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
  {ENDTAG, 0}
};


/* e500/mg2100/mg3100 */
/* Ver.3.60 for mg2100 dbs string pattern table */
static const
ST_MSGTBL mg2100_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg2100 djs string pattern table */
static const
ST_MSGTBL mg2100_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.60 for mg2100 doc string pattern table */
static const
ST_MSGTBL mg2100_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'p',	OC1003_PAPEROUT_PATTERN11},
  {'q',	OC1300_PAPERJAM_PATTERN02},
  {'n',	OC1303_PAPERJAM_PATTERN11},
  {'i',	OC1304_PAPERJAM_PATTERN07},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  {'h',	OC1485_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  {'c',	OC1890_PROTECTIVEMATERIAL_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN05},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN05},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN07},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN04},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN08},
  /* operator level3 */
  {'S', OC1486_POSITION_MISMACH_CART_PATTERN01},
  {'s', OC1487_PLURALERROR_CART_PATTERN01},
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN04},
  {'P', OC1202_HEADCOVER_OPEN_PATTERN01},
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN04}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN02}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.60 for mg2100 dsc string pattern table */
static const
ST_MSGTBL mg2100_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {'R', SC5100_CR_POSITIONEROOR_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {ENDTAG, 0}
};

/* Ver.3.60 for mg2100 dws string pattern table */
static const
ST_MSGTBL mg2100_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.60 for mg2100 doc pict area pattern table */
static const
ST_MSGTBL mg2100_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg2100 dbs pict area pattern table */
static const
ST_MSGTBL mg2100_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg2100 doc unknownicon draw pattern table */
static const
ST_MSGTBL mg2100_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg2100 doc icon delete pattern table */
static const
ST_MSGTBL mg2100_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};


/* mg4100 */
/* Ver.3.60 for mg4100 dbs string pattern table */
static const
ST_MSGTBL mg4100_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg4100 djs string pattern table */
static const
ST_MSGTBL mg4100_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.60 for mg4100 doc string pattern table */
static const
ST_MSGTBL mg4100_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'p',	OC1003_PAPEROUT_PATTERN10},
  {'q',	OC1300_PAPERJAM_PATTERN05},
  {'n',	OC1303_PAPERJAM_PATTERN10},
  {'i',	OC1304_PAPERJAM_PATTERN06},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  {'h',	OC1485_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  {'c',	OC1890_PROTECTIVEMATERIAL_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN04},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN04},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN09},
  /* operator level3 */
  {'S', OC1486_POSITION_MISMACH_CART_PATTERN01},
  {'s', OC1487_PLURALERROR_CART_PATTERN01},
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN04},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN04},
  {'P', OC1202_HEADCOVER_OPEN_PATTERN01},
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN04}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN02}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.60 for mg4100 dsc string pattern table */
static const
ST_MSGTBL mg4100_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'R', SC5100_CR_POSITIONEROOR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {ENDTAG, 0}
};

/* Ver.3.60 for mg4100 dws string pattern table */
static const
ST_MSGTBL mg4100_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.60 for mg4100 doc pict area pattern table */
static const
ST_MSGTBL mg4100_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg4100 dbs pict area pattern table */
static const
ST_MSGTBL mg4100_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg4100 doc unknownicon draw pattern table */
static const
ST_MSGTBL mg4100_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg4100 doc icon delete pattern table */
static const
ST_MSGTBL mg4100_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};


/* mg8200 */
/* Ver.3.60 for mg8200 dbs string pattern table */
static const
ST_MSGTBL mg8200_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg8200 djs string pattern table */
static const
ST_MSGTBL mg8200_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.60 for mg8200 doc string pattern table */
static const
ST_MSGTBL mg8200_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN08},
  {'p',	OC1003_PAPEROUT_PATTERN09},
  {'q',	OC1300_PAPERJAM_PATTERN06},
  {'n',	OC1303_PAPERJAM_PATTERN09},
  {'i',	OC1304_PAPERJAM_PATTERN05},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN07},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN07},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN03},
  {'N', OC2500_HEADALIGNMENT_PATTERN03},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN07},
  {'u', OC1600_INKOUT_TANK_PATTERN04},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN01},
  {'F', OC1750_OLDINKTANK_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN07},
  {'K', OC1856_CDR_GUIDE_PATTERN05},
  {'I', OC1858_CDR_GUIDE_PATTERN03},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.60 for mg8200 dsc string pattern table */
static const
ST_MSGTBL mg8200_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'C', SC5101_CARRIAGEPOSITION_PATTERN01},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {'S', SC5020_SCANNER_LOCK_ERROR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.60 for mg8200 dws string pattern table */
static const
ST_MSGTBL mg8200_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg8200 doc pict area pattern table */
static const
ST_MSGTBL mg8200_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.60 for mg8200 dbs pict area pattern table */
static const
ST_MSGTBL mg8200_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg8200 doc unknownicon draw pattern table */
static const
ST_MSGTBL mg8200_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg8200 doc icon delete pattern table */
static const
ST_MSGTBL mg8200_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
  {ENDTAG, 0}
};

/* mg5300 */
/* Ver.3.60 for mg5300 dbs string pattern table */
static const
ST_MSGTBL mg5300_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg5300 djs string pattern table */
static const
ST_MSGTBL mg5300_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.60 for mg5300 doc string pattern table */
static const
ST_MSGTBL mg5300_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN04},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'i',	OC1304_PAPERJAM_PATTERN04},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN04},
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
  {'F', OC1750_OLDINKTANK_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN06},
  {'K', OC1856_CDR_GUIDE_PATTERN04},
  {'I', OC1858_CDR_GUIDE_PATTERN02},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.60 for mg5300 dsc string pattern table */
static const
ST_MSGTBL mg5300_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'C', SC5101_CARRIAGEPOSITION_PATTERN01},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.60 for mg5300 dws string pattern table */
static const
ST_MSGTBL mg5300_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg5300 doc pict area pattern table */
static const
ST_MSGTBL mg5300_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.60 for mg5300 dbs pict area pattern table */
static const
ST_MSGTBL mg5300_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg5300 doc unknownicon draw pattern table */
static const
ST_MSGTBL mg5300_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.60 for mg5300 doc icon delete pattern table */
static const
ST_MSGTBL mg5300_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
  {ENDTAG, 0}
};

/* iP4900 */
/* Ver.3.60 for ip4900 dbs string pattern table */
static const
ST_MSGTBL ip4900_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.60 for ip4900 djs string pattern table */
static const
ST_MSGTBL ip4900_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.60 for ip4900 doc string pattern table */
static const
ST_MSGTBL ip4900_doc_string_pattern_table[]={
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
  {'x', OC1700_USEDTANK_ALMOST_PATTERN06},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN06},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN05}, /* Ver.3.60 add */
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
  {'F', OC1750_OLDINKTANK_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN05},
  {'K', OC1856_CDR_GUIDE_PATTERN03},
  {'I', OC1858_CDR_GUIDE_PATTERN01},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.60 for ip4900 dsc string pattern table */
static const
ST_MSGTBL ip4900_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'C', SC5101_CARRIAGEPOSITION_PATTERN01},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.60 for ip4900 dws string pattern table */
static const
ST_MSGTBL ip4900_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.60 for ip4900 doc pict area pattern table */
static const
ST_MSGTBL ip4900_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.60 for ip4900 dbs pict area pattern table */
static const
ST_MSGTBL ip4900_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.60 for ip4900 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip4900_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.60 for ip4900 doc icon delete pattern table */
static const
ST_MSGTBL ip4900_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
  {ENDTAG, 0}
};


/* mx430 */
/* Ver.3.70 for mx430 dbs string pattern table */
static const
ST_MSGTBL mx430_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx430 djs string pattern table */
static const
ST_MSGTBL mx430_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.70 for mx430 doc string pattern table */
static const
ST_MSGTBL mx430_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'p',	OC1003_PAPEROUT_PATTERN10},
  {'q',	OC1300_PAPERJAM_PATTERN05},
  {'n',	OC1303_PAPERJAM_PATTERN13},
  //{'i',	OC1304_PAPERJAM_PATTERN06},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  {'h',	OC1485_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  {'c',	OC2700_PANELCHK_PATTERN01}, /* change Ver.3.70 */
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN04},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN04},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN09},
  /* operator level3 */
  {'S', OC1486_POSITION_MISMACH_CART_PATTERN01},
  {'s', OC1487_PLURALERROR_CART_PATTERN01},
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN04},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN04},
  {'P', OC1202_HEADCOVER_OPEN_PATTERN01},
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN04}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN02}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.70 for mx430 dsc string pattern table */
static const
ST_MSGTBL mx430_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.70 for mx430 dws string pattern table */
static const
ST_MSGTBL mx430_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.70 for mx430 doc pict area pattern table */
static const
ST_MSGTBL mx430_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx430 dbs pict area pattern table */
static const
ST_MSGTBL mx430_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx430 doc unknownicon draw pattern table */
static const
ST_MSGTBL mx430_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx430 doc icon delete pattern table */
static const
ST_MSGTBL mx430_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};


/* mx510 */
/* Ver.3.70 for mx510 dbs string pattern table */
static const
ST_MSGTBL mx510_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN01},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx510 djs string pattern table */
static const
ST_MSGTBL mx510_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},	/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},		/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},		/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},			/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},		/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},		/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.70 for mx510 doc string pattern table */
static const
ST_MSGTBL mx510_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'p',	OC1003_PAPEROUT_PATTERN10},
  {'q',	OC1300_PAPERJAM_PATTERN05},
  {'n',	OC1303_PAPERJAM_PATTERN14},
  {'i',	OC1304_PAPERJAM_PATTERN08},
  {'H',	OC1401_CARTRIDGENONE_PATTERN03},
  {'h',	OC1485_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  {'c',	OC2700_PANELCHK_PATTERN01}, /* change Ver.3.70 */
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN04},
  {'T', OC1687_INKTANK_NOTPROPERLY_PATTERN04},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN09},
  /* operator level3 */
  {'S', OC1486_POSITION_MISMACH_CART_PATTERN01},
  {'s', OC1487_PLURALERROR_CART_PATTERN01},
  {'e', OC1401_CARTRIDGENONE_PATTERN03},
  {'w', OC1686_REMAIN_UNKNOWN2_PATTERN04},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN04},
  {'P', OC1202_HEADCOVER_OPEN_PATTERN01},
  {'o', OC1250_COVER_CLOSE_PATTERN01},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN04}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN02}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.70 for mx510 dsc string pattern table */
static const
ST_MSGTBL mx510_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.70 for mx510 dws string pattern table */
static const
ST_MSGTBL mx510_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'t', WR1500_DWS_INKLOW_PATTERN02},			/* D-01 */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-4R */
  {'z', WAR_HCF_PATTERN01},						/* R-1  */
  {ENDTAG, 	0}
};

/* Ver.3.70 for mx510 doc pict area pattern table */
static const
ST_MSGTBL mx510_doc_pict_disable_pattern_table[]={
  //{'H', 1},		/* B-01 */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx510 dbs pict area pattern table */
static const
ST_MSGTBL mx510_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx510 doc unknownicon draw pattern table */
static const
ST_MSGTBL mx510_doc_unknownicon_draw_pattern_table[]={
  {'w', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx510 doc icon delete pattern table */
static const
ST_MSGTBL mx510_doc_icon_delete_pattern_table[]={
  {'T', 1},		/* B-21 */
  {ENDTAG, 0}
};

/* mx890 */
/* Ver.3.70 for mx890 dbs string pattern table */
static const
ST_MSGTBL mx890_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
//  {'D', DBS_CARTRIDGE_CHANGE_PATTERN02},/* A-06 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'N', DBS_TANK_CHANGE_PATTERN01},		/* A-07 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
//  {'H', DBS_HEADPROTECT_PATTERN01},		/* A-35 */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx890 djs string pattern table */
static const
ST_MSGTBL mx890_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.70 for mx890 doc string pattern table */
static const
ST_MSGTBL mx890_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN04},
  {'p',	OC1003_PAPEROUT_PATTERN04},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'i',	OC1304_PAPERJAM_PATTERN04},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN02},
  {'N', OC2500_HEADALIGNMENT_PATTERN02},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN04},
  {'u', OC1600_INKOUT_TANK_PATTERN03},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN01},
  {'F', OC1750_OLDINKTANK_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN02},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN02}, /* DOC:1200 && DBC:CC   A-06 */
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.70 for mx890 dsc string pattern table */
static const
ST_MSGTBL mx890_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'C', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {ENDTAG, 0}
};

/* Ver.3.70 for mx890 dws string pattern table */
static const
ST_MSGTBL mx890_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx890 doc pict area pattern table */
static const
ST_MSGTBL mx890_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.70 for mx890 dbs pict area pattern table */
static const
ST_MSGTBL mx890_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx890 doc unknownicon draw pattern table */
static const
ST_MSGTBL mx890_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.70 for mx890 doc icon delete pattern table */
static const
ST_MSGTBL mx890_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
  {ENDTAG, 0}
};


/* mg6300 */
/* Ver.3.80 for mg6300 dbs string pattern table */
static const
ST_MSGTBL mg6300_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.80 for mg6300 djs string pattern table */
static const
ST_MSGTBL mg6300_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.80 for mg6300 doc string pattern table */
static const
ST_MSGTBL mg6300_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'X',	OC1000_PAPEROUT_PATTERN08},
  {'p',	OC1007_PAPEROUT_PATTERN03},
  {'Q',	OC1008_PAPEROUT_PATTERN03},
  {'q',	OC1300_PAPERJAM_PATTERN07},
  {'n',	OC1303_PAPERJAM_PATTERN09},
  {'i',	OC1304_PAPERJAM_PATTERN11},
  {'j',	OC1311_PAPERJAM_PATTERN03},
  {'J',	OC1312_PAPERJAM_PATTERN03},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  {'L',	OC4101_USERSIZE_PATTERN03},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN08},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN08},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN08},
  {'N', OC2500_HEADALIGNMENT_PATTERN04},
  {'t', OC141X_HARDWARE_PATTERN01},
  /*ink out*/
  {'C', OC1688_INKEMPTY_TANK_PATTERN07},
  {'u', OC1600_INKOUT_TANK_PATTERN05},
  /* operator level3 */
  {'s', OC1681_PLURALERROR_TANK_PATTERN01},
  {'e', OC1684_DIFFERENT_REGION_TANK_PATTERN02},
  {'S', OC1680_POSITION_MISMACH_TANK_PATTERN01},
  {'d', OC1660_UNINSTALLATION_TANK_PATTERN01},
  {'f', OC1683_REMAIN_UNKNOWN_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN05},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN05}, /* DOC:1200 && DBS:CC   A-06 */
  {'G', DBS_TANK_CHANGE_PATTERN02},      /* DOC:1200 && DBS:TC   A-07 */
  {'o', OC1253_SMARTCOVER_OPEN_PATTERN03},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN09},
  {'K', OC1856_CDR_GUIDE_PATTERN06},
  {'I', OC1858_CDR_GUIDE_PATTERN04},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.80 for mg6300 dsc string pattern table */
static const
ST_MSGTBL mg6300_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'R', SC5100_CR_POSITIONEROOR_PATTERN01},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {ENDTAG, 0}
};

/* Ver.3.80 for mg6300 dws string pattern table */
static const
ST_MSGTBL mg6300_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.80 for mg6300 doc pict area pattern table */
static const
ST_MSGTBL mg6300_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.80 for mg6300 dbs pict area pattern table */
static const
ST_MSGTBL mg6300_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.80 for mg6300 doc unknownicon draw pattern table */
static const
ST_MSGTBL mg6300_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.80 for mg6300 doc icon delete pattern table */
static const
ST_MSGTBL mg6300_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
  {ENDTAG, 0}
};

/* mg5400 */
/* Ver.3.80 for mg5400 dbs string pattern table */
static const
ST_MSGTBL mg5400_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.80 for mg5400 djs string pattern table */
static const
ST_MSGTBL mg5400_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.80 for mg5400 doc string pattern table */
static const
ST_MSGTBL mg5400_doc_string_pattern_table[]={
  /* operator level1 */
  {'Z',	OC2700_PANELCHK_PATTERN01},
  {'U',	OC2001_USBDEVICE_PATTERN01},
  {'p',	OC1007_PAPEROUT_PATTERN02},
  {'Q',	OC1008_PAPEROUT_PATTERN02},
  {'q',	OC1300_PAPERJAM_PATTERN04},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'i',	OC1304_PAPERJAM_PATTERN10},
  {'j',	OC1311_PAPERJAM_PATTERN02},
  {'J',	OC1312_PAPERJAM_PATTERN02},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  {'L',	OC4101_USERSIZE_PATTERN02},
  /* operator level2 */
  {'x', OC1700_USEDTANK_ALMOST_PATTERN04},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN04},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN04},
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
  {'F', OC1750_OLDINKTANK_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN05},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN05}, /* DOC:1200 && DBS:CC   A-06 */
  {'G', DBS_TANK_CHANGE_PATTERN02},      /* DOC:1200 && DBS:TC   A-07 */
  {'o', OC1253_SMARTCOVER_OPEN_PATTERN02},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN10},
  {'K', OC1856_CDR_GUIDE_PATTERN04},
  {'I', OC1858_CDR_GUIDE_PATTERN02},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.80 for mg5400 dsc string pattern table */
static const
ST_MSGTBL mg5400_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'C', SC5101_CARRIAGEPOSITION_PATTERN01},
  {'R', SC5100_CR_POSITIONEROOR_PATTERN01},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {ENDTAG, 0}
};

/* Ver.3.80 for mg5400 dws string pattern table */
static const
ST_MSGTBL mg5400_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.80 for mg5400 doc pict area pattern table */
static const
ST_MSGTBL mg5400_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.80 for mg5400 dbs pict area pattern table */
static const
ST_MSGTBL mg5400_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.80 for mg5400 doc unknownicon draw pattern table */
static const
ST_MSGTBL mg5400_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.80 for mg5400 doc icon delete pattern table */
static const
ST_MSGTBL mg5400_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
  {ENDTAG, 0}
};

/* iP7200 */
/* Ver.3.80 for ip7200 dbs string pattern table */
static const
ST_MSGTBL ip7200_dbs_string_pattern_table[]={
  {'L', DBS_CLEANING_PATTERN01},		/* A-05 */
  {'T', DBS_TEST_PRINTING_PATTERN01},	/* A-04 */
  {'I', DBS_PRINTER_USED_PATTERN01},	/* E-10 */
  {'B', DBS_PRINTER_PATTERN01},			/* A-09 */
  {ENDTAG, 0}
};

/* Ver.3.80 for ip7200 djs string pattern table */
static const
ST_MSGTBL ip7200_djs_string_pattern_table[]={
  {'P', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'L', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'F', DJS_BASE_PRINTING_PATTERN01},		/* A-04 */
  {'I', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {'S', DJS_JOBCANCEL_PATTERN04},			/* A-11 */
  {'W', DJS_JOB_PREPARE_PATTERN01},			/* A-18 */
  {'w', DJS_PREPARE_PATTERN01},				/* A-34 */
  {'D', DJS_JOB_DELAY_PATTERN01},			/* A-19 */
  {'?', DJS_BASE_ONLINE_PATTERN01},			/* A-03 */
  {ENDTAG, 	0}
};

/* Ver.3.80 for ip7200 doc string pattern table */
static const
ST_MSGTBL ip7200_doc_string_pattern_table[]={
  /* operator level1 */
  {'X',	OC1000_PAPEROUT_PATTERN03},
  {'p',	OC1007_PAPEROUT_PATTERN01},
  {'Q',	OC1008_PAPEROUT_PATTERN01},
  {'q',	OC1300_PAPERJAM_PATTERN03},
  {'n',	OC1303_PAPERJAM_PATTERN04},
  {'i',	OC1304_PAPERJAM_PATTERN09},
  {'j',	OC1311_PAPERJAM_PATTERN01},
  {'J',	OC1312_PAPERJAM_PATTERN01},
  {'H',	OC1401_CARTRIDGENONE_PATTERN01},
  {'r',	OC1403_CARTRIDGENONE_PATTERN01},
  /* operator level2 */
  {'L',	OC4101_USERSIZE_PATTERN01},
  {'x', OC1700_USEDTANK_ALMOST_PATTERN06},
  {'k', OC1701_USEDTANK_ALMOST_PATTERN06},
  {'R', OC1310_DUPLEX_STOPPAGE_PATTERN05}, /* Ver.3.80 add */
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
  {'F', OC1750_OLDINKTANK_PATTERN01},
  /* operator level4 */
  {'v', OC1200_COVER_OPEN_PATTERN05},
  {'V', DBS_CARTRIDGE_CHANGE_PATTERN05}, /* DOC:1200 && DBS:CC   A-06 */
  {'G', DBS_TANK_CHANGE_PATTERN02},      /* DOC:1200 && DBS:TC   A-07 */
  {'o', OC1253_SMARTCOVER_OPEN_PATTERN01},
  {'g', OC1851_CDR_GUIDE_PRINT_PATTERN11},
  {'K', OC1856_CDR_GUIDE_PATTERN03},
  {'I', OC1858_CDR_GUIDE_PATTERN01},
  {'O', DBS_HEADPROTECT_PATTERN01}, 	 /* DOC:1200 && DWS:1900 A-35 */
  {ENDTAG, 	0}
};

/* Ver.3.80 for ip7200 dsc string pattern table */
static const
ST_MSGTBL ip7200_dsc_string_pattern_table[]={
  {'I', SC5B00_USEDTANK_FULL_PATTERN02},
  {'J', SC5B01_USEDTANK_FULL_PATTERN02},
  {'R', SC5100_CR_POSITIONEROOR_PATTERN01},
  {'V', SCB200_VH_MONITOR_EROOR_PATTERN01},
  {'M', SCOTHER_COMMON_SERIVICE_ERROR_PATTERN02},
  {ENDTAG, 0}
};

/* Ver.3.80 for ip7200 dws string pattern table */
static const
ST_MSGTBL ip7200_dws_string_pattern_table[]={
  {'T', WR1500_DWS_INKLOW_PATTERN01},			/* D-01 */
  {'F', WR1570_DWS_INKOUT_PATTERN02},			/* B-4R */
  {'Z', WR1600_DWS_INKSTATUS_OFF_PATTERN01},	/* B-36R */
  {ENDTAG, 0}
};

/* Ver.3.80 for ip7200 doc pict area pattern table */
static const
ST_MSGTBL ip7200_doc_pict_disable_pattern_table[]={
  {'H', 1},		/* B-01 */
  {ENDTAG, 0}
};


/* Ver.3.80 for ip7200 dbs pict area pattern table */
static const
ST_MSGTBL ip7200_dbs_pict_disable_pattern_table[]={
  {'I', 1},		/* E-10 */
  {ENDTAG, 0}
};

/* Ver.3.80 for ip7200 doc unknownicon draw pattern table */
static const
ST_MSGTBL ip7200_doc_unknownicon_draw_pattern_table[]={
  {'f', 1},		/* B-36 */
  {ENDTAG, 0}
};

/* Ver.3.80 for ip7200 doc icon delete pattern table */
static const
ST_MSGTBL ip7200_doc_icon_delete_pattern_table[]={
  {'s', 1},		/* B-31 */
  {'e', 1},		/* B-32 */
  {'S', 1},		/* B-35 */
  {'t', 1},		/* B-40 */
  {'d', 1},		/* B-42 */
  {'F', 1},		/* B-68 */
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
  {"MX860",		mx860_dbs_string_pattern_table	},
  {"MX320",		mx320_dbs_string_pattern_table	},
  {"MX330",		mx320_dbs_string_pattern_table	},
  {"MP250",		mp270_dbs_string_pattern_table	},
  {"MP270",		mp270_dbs_string_pattern_table	},
  {"MP490",		mp490_dbs_string_pattern_table	},
  {"MP550",		mp560_dbs_string_pattern_table	},
  {"MP560",		mp560_dbs_string_pattern_table	},
  {"MP640",		mp640_dbs_string_pattern_table	},
  {"IP4700",	ip4700_dbs_string_pattern_table	},
  {"IP2700",	ip2700_dbs_string_pattern_table	},
  {"MX340",		mx340_dbs_string_pattern_table	},
  {"MX350",		mx340_dbs_string_pattern_table	},
  {"MX870",		mx870_dbs_string_pattern_table	},
  {"MP280",		mp270_dbs_string_pattern_table	},
  {"MP495",		mp270_dbs_string_pattern_table	},
  {"MG5100",	mg5200_dbs_string_pattern_table	},
  {"IP4800",	ip4800_dbs_string_pattern_table	},
  {"MG5200",	mg5200_dbs_string_pattern_table	},
  {"MG6100",	mg8100_dbs_string_pattern_table	},
  {"MG8100",	mg8100_dbs_string_pattern_table	},
  {"MX360",		mx340_dbs_string_pattern_table	},
  {"MX410",		mx340_dbs_string_pattern_table	},
  {"MX420",		mx340_dbs_string_pattern_table	},
  {"MX880",		mx880_dbs_string_pattern_table	},
  {"IX6500",	ix6500_dbs_string_pattern_table	},
  {"E500",		mg2100_dbs_string_pattern_table	},
  {"MG2100",	mg2100_dbs_string_pattern_table	},
  {"MG3100",	mg2100_dbs_string_pattern_table	},
  {"MG4100",	mg4100_dbs_string_pattern_table	},
  {"MG5300",	mg5300_dbs_string_pattern_table	},
  {"IP4900",	ip4900_dbs_string_pattern_table	},
  {"MG6200",	mg8200_dbs_string_pattern_table	},
  {"MG8200",	mg8200_dbs_string_pattern_table	},
  {"E600",		mx430_dbs_string_pattern_table	},
  {"MX370",		mx430_dbs_string_pattern_table	},
  {"MX430",		mx430_dbs_string_pattern_table	},
  {"MX510",		mx510_dbs_string_pattern_table	},
  {"MX710",		mx890_dbs_string_pattern_table	},
  {"MX890",		mx890_dbs_string_pattern_table	},
  {"MP230",		mp270_dbs_string_pattern_table	},
  {"E510",		mg2100_dbs_string_pattern_table	},
  {"MG2200",	mg2100_dbs_string_pattern_table	},
  {"MG3200",	mg2100_dbs_string_pattern_table	},
  {"MG4200",	mg4100_dbs_string_pattern_table	},
  {"MG5400",	mg5400_dbs_string_pattern_table	},
  {"IP7200",	ip7200_dbs_string_pattern_table	},
  {"MG6300",	mg6300_dbs_string_pattern_table	},
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
  {"MX860",		mx860_djs_string_pattern_table	},
  {"MX320",		mx320_djs_string_pattern_table	},
  {"MX330",		mx320_djs_string_pattern_table	},
  {"MP250",		mp270_djs_string_pattern_table	},
  {"MP270",		mp270_djs_string_pattern_table	},
  {"MP490",		mp490_djs_string_pattern_table	},
  {"MP550",		mp560_djs_string_pattern_table	},
  {"MP560",		mp560_djs_string_pattern_table	},
  {"MP640",		mp640_djs_string_pattern_table	},
  {"IP4700",	ip4700_djs_string_pattern_table	},
  {"IP2700",	ip2700_djs_string_pattern_table	},
  {"MX340",		mx340_djs_string_pattern_table	},
  {"MX350",		mx340_djs_string_pattern_table	},
  {"MX870",		mx870_djs_string_pattern_table	},
  {"MP280",		mp270_djs_string_pattern_table	},
  {"MP495",		mp270_djs_string_pattern_table	},
  {"MG5100",	mg5200_djs_string_pattern_table	},
  {"IP4800",	ip4800_djs_string_pattern_table	},
  {"MG5200",	mg5200_djs_string_pattern_table	},
  {"MG6100",	mg8100_djs_string_pattern_table	},
  {"MG8100",	mg8100_djs_string_pattern_table	},
  {"MX360",		mx340_djs_string_pattern_table	},
  {"MX410",		mx340_djs_string_pattern_table	},
  {"MX420",		mx340_djs_string_pattern_table	},
  {"MX880",		mx880_djs_string_pattern_table	},
  {"IX6500",	ix6500_djs_string_pattern_table	},
  {"E500",		mg2100_djs_string_pattern_table	},
  {"MG2100",	mg2100_djs_string_pattern_table	},
  {"MG3100",	mg2100_djs_string_pattern_table	},
  {"MG4100",	mg4100_djs_string_pattern_table	},
  {"MG5300",	mg5300_djs_string_pattern_table	},
  {"IP4900",	ip4900_djs_string_pattern_table	},
  {"MG6200",	mg8200_djs_string_pattern_table	},
  {"MG8200",	mg8200_djs_string_pattern_table	},
  {"E600",		mx430_djs_string_pattern_table	},
  {"MX370",		mx430_djs_string_pattern_table	},
  {"MX430",		mx430_djs_string_pattern_table	},
  {"MX510",		mx510_djs_string_pattern_table	},
  {"MX710",		mx890_djs_string_pattern_table	},
  {"MX890",		mx890_djs_string_pattern_table	},
  {"MP230",		mp270_djs_string_pattern_table	},
  {"E510",		mg2100_djs_string_pattern_table	},
  {"MG2200",	mg2100_djs_string_pattern_table	},
  {"MG3200",	mg2100_djs_string_pattern_table	},
  {"MG4200",	mg4100_djs_string_pattern_table	},
  {"MG5400",	mg5400_djs_string_pattern_table	},
  {"IP7200",	ip7200_djs_string_pattern_table	},
  {"MG6300",	mg6300_djs_string_pattern_table	},
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
  {"MX860",		mx860_doc_string_pattern_table	},
  {"MX320",		mx320_doc_string_pattern_table	},
  {"MX330",		mx320_doc_string_pattern_table	},
  {"MP250",		mp270_doc_string_pattern_table	},
  {"MP270",		mp270_doc_string_pattern_table	},
  {"MP490",		mp490_doc_string_pattern_table	},
  {"MP550",		mp560_doc_string_pattern_table	},
  {"MP560",		mp560_doc_string_pattern_table	},
  {"MP640",		mp640_doc_string_pattern_table	},
  {"IP4700",	ip4700_doc_string_pattern_table	},
  {"IP2700",	ip2700_doc_string_pattern_table	},
  {"MX340",		mx340_doc_string_pattern_table	},
  {"MX350",		mx340_doc_string_pattern_table	},
  {"MX870",		mx870_doc_string_pattern_table	},
  {"MP280",		mp270_doc_string_pattern_table	},
  {"MP495",		mp270_doc_string_pattern_table	},
  {"MG5100",	mg5200_doc_string_pattern_table	},
  {"IP4800",	ip4800_doc_string_pattern_table	},
  {"MG5200",	mg5200_doc_string_pattern_table	},
  {"MG6100",	mg8100_doc_string_pattern_table	},
  {"MG8100",	mg8100_doc_string_pattern_table	},
  {"MX360",		mx340_doc_string_pattern_table	},
  {"MX410",		mx340_doc_string_pattern_table	},
  {"MX420",		mx340_doc_string_pattern_table	},
  {"MX880",		mx880_doc_string_pattern_table	},
  {"IX6500",	ix6500_doc_string_pattern_table	},
  {"E500",		mg2100_doc_string_pattern_table	},
  {"MG2100",	mg2100_doc_string_pattern_table	},
  {"MG3100",	mg2100_doc_string_pattern_table	},
  {"MG4100",	mg4100_doc_string_pattern_table	},
  {"MG5300",	mg5300_doc_string_pattern_table	},
  {"IP4900",	ip4900_doc_string_pattern_table	},
  {"MG6200",	mg8200_doc_string_pattern_table	},
  {"MG8200",	mg8200_doc_string_pattern_table	},
  {"E600",		mx430_doc_string_pattern_table	},
  {"MX370",		mx430_doc_string_pattern_table	},
  {"MX430",		mx430_doc_string_pattern_table	},
  {"MX510",		mx510_doc_string_pattern_table	},
  {"MX710",		mx890_doc_string_pattern_table	},
  {"MX890",		mx890_doc_string_pattern_table	},
  {"MP230",		mp270_doc_string_pattern_table	},
  {"E510",		mg2100_doc_string_pattern_table	},
  {"MG2200",	mg2100_doc_string_pattern_table	},
  {"MG3200",	mg2100_doc_string_pattern_table	},
  {"MG4200",	mg4100_doc_string_pattern_table	},
  {"MG5400",	mg5400_doc_string_pattern_table	},
  {"IP7200",	ip7200_doc_string_pattern_table	},
  {"MG6300",	mg6300_doc_string_pattern_table	},
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
  {"MX860",		mx860_dsc_string_pattern_table	},
  {"MX320",		mx320_dsc_string_pattern_table	},
  {"MX330",		mx320_dsc_string_pattern_table	},
  {"MP250",		mp270_dsc_string_pattern_table	},
  {"MP270",		mp270_dsc_string_pattern_table	},
  {"MP490",		mp490_dsc_string_pattern_table	},
  {"MP550",		mp560_dsc_string_pattern_table	},
  {"MP560",		mp560_dsc_string_pattern_table	},
  {"MP640",		mp640_dsc_string_pattern_table	},
  {"IP4700",	ip4700_dsc_string_pattern_table	},
  {"IP2700",	ip2700_dsc_string_pattern_table	},
  {"MX340",		mx340_dsc_string_pattern_table	},
  {"MX350",		mx340_dsc_string_pattern_table	},
  {"MX870",		mx870_dsc_string_pattern_table	},
  {"MP280",		mp270_dsc_string_pattern_table	},
  {"MP495",		mp270_dsc_string_pattern_table	},
  {"MG5100",	mg5200_dsc_string_pattern_table	},
  {"IP4800",	ip4800_dsc_string_pattern_table	},
  {"MG5200",	mg5200_dsc_string_pattern_table	},
  {"MG6100",	mg8100_dsc_string_pattern_table	},
  {"MG8100",	mg8100_dsc_string_pattern_table	},
  {"MX360",		mx340_dsc_string_pattern_table	},
  {"MX410",		mx340_dsc_string_pattern_table	},
  {"MX420",		mx340_dsc_string_pattern_table	},
  {"MX880",		mx880_dsc_string_pattern_table	},
  {"IX6500",	ix6500_dsc_string_pattern_table	},
  {"E500",		mg2100_dsc_string_pattern_table	},
  {"MG2100",	mg2100_dsc_string_pattern_table	},
  {"MG3100",	mg2100_dsc_string_pattern_table	},
  {"MG4100",	mg4100_dsc_string_pattern_table	},
  {"MG5300",	mg5300_dsc_string_pattern_table	},
  {"IP4900",	ip4900_dsc_string_pattern_table	},
  {"MG6200",	mg8200_dsc_string_pattern_table	},
  {"MG8200",	mg8200_dsc_string_pattern_table	},
  {"E600",		mx430_dsc_string_pattern_table	},
  {"MX370",		mx430_dsc_string_pattern_table	},
  {"MX430",		mx430_dsc_string_pattern_table	},
  {"MX510",		mx510_dsc_string_pattern_table	},
  {"MX710",		mx890_dsc_string_pattern_table	},
  {"MX890",		mx890_dsc_string_pattern_table	},
  {"MP230",		mp270_dsc_string_pattern_table	},
  {"E510",		mg2100_dsc_string_pattern_table	},
  {"MG2200",	mg2100_dsc_string_pattern_table	},
  {"MG3200",	mg2100_dsc_string_pattern_table	},
  {"MG4200",	mg4100_dsc_string_pattern_table	},
  {"MG5400",	mg5400_dsc_string_pattern_table	},
  {"IP7200",	ip7200_dsc_string_pattern_table	},
  {"MG6300",	mg6300_dsc_string_pattern_table	},
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
  {"MX860",		mx860_dws_string_pattern_table	},
  {"MX320",		mx320_dws_string_pattern_table	},
  {"MX330",		mx320_dws_string_pattern_table	},
  {"MP250",		mp270_dws_string_pattern_table	},
  {"MP270",		mp270_dws_string_pattern_table	},
  {"MP490",		mp490_dws_string_pattern_table	},
  {"MP550",		mp560_dws_string_pattern_table	},
  {"MP560",		mp560_dws_string_pattern_table	},
  {"MP640",		mp640_dws_string_pattern_table	},
  {"IP4700",	ip4700_dws_string_pattern_table	},
  {"IP2700",	ip2700_dws_string_pattern_table	},
  {"MX340",		mx340_dws_string_pattern_table	},
  {"MX350",		mx340_dws_string_pattern_table	},
  {"MX870",		mx870_dws_string_pattern_table	},
  {"MP280",		mp270_dws_string_pattern_table	},
  {"MP495",		mp270_dws_string_pattern_table	},
  {"MG5100",	mg5200_dws_string_pattern_table	},
  {"IP4800",	ip4800_dws_string_pattern_table	},
  {"MG5200",	mg5200_dws_string_pattern_table	},
  {"MG6100",	mg8100_dws_string_pattern_table	},
  {"MG8100",	mg8100_dws_string_pattern_table	},
  {"MX360",		mx340_dws_string_pattern_table	},
  {"MX410",		mx340_dws_string_pattern_table	},
  {"MX420",		mx340_dws_string_pattern_table	},
  {"MX880",		mx880_dws_string_pattern_table	},
  {"IX6500",	ix6500_dws_string_pattern_table	},
  {"E500",		mg2100_dws_string_pattern_table	},
  {"MG2100",	mg2100_dws_string_pattern_table	},
  {"MG3100",	mg2100_dws_string_pattern_table	},
  {"MG4100",	mg4100_dws_string_pattern_table	},
  {"MG5300",	mg5300_dws_string_pattern_table	},
  {"IP4900",	ip4900_dws_string_pattern_table	},
  {"MG6200",	mg8200_dws_string_pattern_table	},
  {"MG8200",	mg8200_dws_string_pattern_table	},
  {"E600",		mx430_dws_string_pattern_table	},
  {"MX370",		mx430_dws_string_pattern_table	},
  {"MX430",		mx430_dws_string_pattern_table	},
  {"MX510",		mx510_dws_string_pattern_table	},
  {"MX710",		mx890_dws_string_pattern_table	},
  {"MX890",		mx890_dws_string_pattern_table	},
  {"MP230",		mp270_dws_string_pattern_table	},
  {"E510",		mg2100_dws_string_pattern_table	},
  {"MG2200",	mg2100_dws_string_pattern_table	},
  {"MG3200",	mg2100_dws_string_pattern_table	},
  {"MG4200",	mg4100_dws_string_pattern_table	},
  {"MG5400",	mg5400_dws_string_pattern_table	},
  {"IP7200",	ip7200_dws_string_pattern_table	},
  {"MG6300",	mg6300_dws_string_pattern_table	},
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
  {"MX860",		mx860_doc_pict_disable_pattern_table	},
  {"MX320",		mx320_doc_pict_disable_pattern_table	},
  {"MX330",		mx320_doc_pict_disable_pattern_table	},
  {"MP250",		mp270_doc_pict_disable_pattern_table	},
  {"MP270",		mp270_doc_pict_disable_pattern_table	},
  {"MP490",		mp490_doc_pict_disable_pattern_table	},
  {"MP550",		mp560_doc_pict_disable_pattern_table	},
  {"MP560",		mp560_doc_pict_disable_pattern_table	},
  {"MP640",		mp640_doc_pict_disable_pattern_table	},
  {"IP4700",	ip4700_doc_pict_disable_pattern_table	},
  {"IP2700",	ip2700_doc_pict_disable_pattern_table	},
  {"MX340",		mx340_doc_pict_disable_pattern_table	},
  {"MX350",		mx340_doc_pict_disable_pattern_table	},
  {"MX870",		mx870_doc_pict_disable_pattern_table	},
  {"MP280",		mp270_doc_pict_disable_pattern_table	},
  {"MP495",		mp270_doc_pict_disable_pattern_table	},
  {"MG5100",	mg5200_doc_pict_disable_pattern_table	},
  {"IP4800",	ip4800_doc_pict_disable_pattern_table	},
  {"MG5200",	mg5200_doc_pict_disable_pattern_table	},
  {"MG6100",	mg8100_doc_pict_disable_pattern_table	},
  {"MG8100",	mg8100_doc_pict_disable_pattern_table	},
  {"MX360",		mx340_doc_pict_disable_pattern_table	},
  {"MX410",		mx340_doc_pict_disable_pattern_table	},
  {"MX420",		mx340_doc_pict_disable_pattern_table	},
  {"MX880",		mx880_doc_pict_disable_pattern_table	},
  {"IX6500",	ix6500_doc_pict_disable_pattern_table	},
  {"E500",		mg2100_doc_pict_disable_pattern_table	},
  {"MG2100",	mg2100_doc_pict_disable_pattern_table	},
  {"MG3100",	mg2100_doc_pict_disable_pattern_table	},
  {"MG4100",	mg4100_doc_pict_disable_pattern_table	},
  {"MG5300",	mg5300_doc_pict_disable_pattern_table	},
  {"IP4900",	ip4900_doc_pict_disable_pattern_table	},
  {"MG6200",	mg8200_doc_pict_disable_pattern_table	},
  {"MG8200",	mg8200_doc_pict_disable_pattern_table	},
  {"E600",		mx430_doc_pict_disable_pattern_table	},
  {"MX370",		mx430_doc_pict_disable_pattern_table	},
  {"MX430",		mx430_doc_pict_disable_pattern_table	},
  {"MX510",		mx510_doc_pict_disable_pattern_table	},
  {"MX710",		mx890_doc_pict_disable_pattern_table	},
  {"MX890",		mx890_doc_pict_disable_pattern_table	},
  {"MP230",		mp270_doc_pict_disable_pattern_table	},
  {"E510",		mg2100_doc_pict_disable_pattern_table	},
  {"MG2200",	mg2100_doc_pict_disable_pattern_table	},
  {"MG3200",	mg2100_doc_pict_disable_pattern_table	},
  {"MG4200",	mg4100_doc_pict_disable_pattern_table	},
  {"MG5400",	mg5400_doc_pict_disable_pattern_table	},
  {"IP7200",	ip7200_doc_pict_disable_pattern_table	},
  {"MG6300",	mg6300_doc_pict_disable_pattern_table	},
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
  {"MX860",		mx860_dbs_pict_disable_pattern_table	},
  {"MX320",		mx320_dbs_pict_disable_pattern_table	},
  {"MX330",		mx320_dbs_pict_disable_pattern_table	},
  {"MP250",		mp270_dbs_pict_disable_pattern_table	},
  {"MP270",		mp270_dbs_pict_disable_pattern_table	},
  {"MP490",		mp490_dbs_pict_disable_pattern_table	},
  {"MP550",		mp560_dbs_pict_disable_pattern_table	},
  {"MP560",		mp560_dbs_pict_disable_pattern_table	},
  {"MP640",		mp640_dbs_pict_disable_pattern_table	},
  {"IP4700",	ip4700_dbs_pict_disable_pattern_table	},
  {"IP2700",	ip2700_dbs_pict_disable_pattern_table	},
  {"MX340",		mx340_dbs_pict_disable_pattern_table	},
  {"MX350",		mx340_dbs_pict_disable_pattern_table	},
  {"MX870",		mx870_dbs_pict_disable_pattern_table	},
  {"MP280",		mp270_dbs_pict_disable_pattern_table	},
  {"MP495",		mp270_dbs_pict_disable_pattern_table	},
  {"MG5100",	mg5200_dbs_pict_disable_pattern_table	},
  {"IP4800",	ip4800_dbs_pict_disable_pattern_table	},
  {"MG5200",	mg5200_dbs_pict_disable_pattern_table	},
  {"MG6100",	mg8100_dbs_pict_disable_pattern_table	},
  {"MG8100",	mg8100_dbs_pict_disable_pattern_table	},
  {"MX360",		mx340_dbs_pict_disable_pattern_table	},
  {"MX410",		mx340_dbs_pict_disable_pattern_table	},
  {"MX420",		mx340_dbs_pict_disable_pattern_table	},
  {"MX880",		mx880_dbs_pict_disable_pattern_table	},
  {"IX6500",	ix6500_dbs_pict_disable_pattern_table	},
  {"E500",		mg2100_dbs_pict_disable_pattern_table	},
  {"MG2100",	mg2100_dbs_pict_disable_pattern_table	},
  {"MG3100",	mg2100_dbs_pict_disable_pattern_table	},
  {"MG4100",	mg4100_dbs_pict_disable_pattern_table	},
  {"MG5300",	mg5300_dbs_pict_disable_pattern_table	},
  {"IP4900",	ip4900_dbs_pict_disable_pattern_table	},
  {"MG6200",	mg8200_dbs_pict_disable_pattern_table	},
  {"MG8200",	mg8200_dbs_pict_disable_pattern_table	},
  {"E600",		mx430_dbs_pict_disable_pattern_table	},
  {"MX370",		mx430_dbs_pict_disable_pattern_table	},
  {"MX430",		mx430_dbs_pict_disable_pattern_table	},
  {"MX510",		mx510_dbs_pict_disable_pattern_table	},
  {"MX710",		mx890_dbs_pict_disable_pattern_table	},
  {"MX890",		mx890_dbs_pict_disable_pattern_table	},
  {"MP230",		mp270_dbs_pict_disable_pattern_table	},
  {"E510",		mg2100_dbs_pict_disable_pattern_table	},
  {"MG2200",	mg2100_dbs_pict_disable_pattern_table	},
  {"MG3200",	mg2100_dbs_pict_disable_pattern_table	},
  {"MG4200",	mg4100_dbs_pict_disable_pattern_table	},
  {"MG5400",	mg5400_dbs_pict_disable_pattern_table	},
  {"IP7200",	ip7200_dbs_pict_disable_pattern_table	},
  {"MG6300",	mg6300_dbs_pict_disable_pattern_table	},
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
  {"MX860",		mx860_doc_unknownicon_draw_pattern_table	},
  {"MX320",		mx320_doc_unknownicon_draw_pattern_table	},
  {"MX330",		mx320_doc_unknownicon_draw_pattern_table	},
  {"MP250",		mp270_doc_unknownicon_draw_pattern_table	},
  {"MP270",		mp270_doc_unknownicon_draw_pattern_table	},
  {"MP490",		mp490_doc_unknownicon_draw_pattern_table	},
  {"MP550",		mp560_doc_unknownicon_draw_pattern_table	},
  {"MP560",		mp560_doc_unknownicon_draw_pattern_table	},
  {"MP640",		mp640_doc_unknownicon_draw_pattern_table	},
  {"IP4700",	ip4700_doc_unknownicon_draw_pattern_table	},
  {"IP2700",	ip2700_doc_unknownicon_draw_pattern_table	},
  {"MX340",		mx340_doc_unknownicon_draw_pattern_table	},
  {"MX350",		mx340_doc_unknownicon_draw_pattern_table	},
  {"MX870",		mx870_doc_unknownicon_draw_pattern_table	},
  {"MP280",		mp270_doc_unknownicon_draw_pattern_table	},
  {"MP495",		mp270_doc_unknownicon_draw_pattern_table	},
  {"MG5100",	mg5200_doc_unknownicon_draw_pattern_table	},
  {"IP4800",	ip4800_doc_unknownicon_draw_pattern_table	},
  {"MG5200",	mg5200_doc_unknownicon_draw_pattern_table	},
  {"MG6100",	mg8100_doc_unknownicon_draw_pattern_table	},
  {"MG8100",	mg8100_doc_unknownicon_draw_pattern_table	},
  {"MX360",		mx340_doc_unknownicon_draw_pattern_table	},
  {"MX410",		mx340_doc_unknownicon_draw_pattern_table	},
  {"MX420",		mx340_doc_unknownicon_draw_pattern_table	},
  {"MX880",		mx880_doc_unknownicon_draw_pattern_table	},
  {"IX6500",	ix6500_doc_unknownicon_draw_pattern_table	},
  {"E500",		mg2100_doc_unknownicon_draw_pattern_table	},
  {"MG2100",	mg2100_doc_unknownicon_draw_pattern_table	},
  {"MG3100",	mg2100_doc_unknownicon_draw_pattern_table	},
  {"MG4100",	mg4100_doc_unknownicon_draw_pattern_table	},
  {"MG5300",	mg5300_doc_unknownicon_draw_pattern_table	},
  {"IP4900",	ip4900_doc_unknownicon_draw_pattern_table	},
  {"MG6200",	mg8200_doc_unknownicon_draw_pattern_table	},
  {"MG8200",	mg8200_doc_unknownicon_draw_pattern_table	},
  {"E600",		mx430_doc_unknownicon_draw_pattern_table	},
  {"MX370",		mx430_doc_unknownicon_draw_pattern_table	},
  {"MX430",		mx430_doc_unknownicon_draw_pattern_table	},
  {"MX510",		mx510_doc_unknownicon_draw_pattern_table	},
  {"MX710",		mx890_doc_unknownicon_draw_pattern_table	},
  {"MX890",		mx890_doc_unknownicon_draw_pattern_table	},
  {"MP230",		mp270_doc_unknownicon_draw_pattern_table	},
  {"E510",		mg2100_doc_unknownicon_draw_pattern_table	},
  {"MG2200",	mg2100_doc_unknownicon_draw_pattern_table	},
  {"MG3200",	mg2100_doc_unknownicon_draw_pattern_table	},
  {"MG4200",	mg4100_doc_unknownicon_draw_pattern_table	},
  {"MG5400",	mg5400_doc_unknownicon_draw_pattern_table	},
  {"IP7200",	ip7200_doc_unknownicon_draw_pattern_table	},
  {"MG6300",	mg6300_doc_unknownicon_draw_pattern_table	},
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
  {"MX860",		mx860_doc_icon_delete_pattern_table		},
  {"MX320",		mx320_doc_icon_delete_pattern_table		},
  {"MX330",		mx320_doc_icon_delete_pattern_table		},
  {"MP250",		mp270_doc_icon_delete_pattern_table		},
  {"MP270",		mp270_doc_icon_delete_pattern_table		},
  {"MP490",		mp490_doc_icon_delete_pattern_table		},
  {"MP550",		mp560_doc_icon_delete_pattern_table		},
  {"MP560",		mp560_doc_icon_delete_pattern_table		},
  {"MP640",		mp640_doc_icon_delete_pattern_table		},
  {"IP4700",	ip4700_doc_icon_delete_pattern_table	},
  {"IP2700",	ip2700_doc_icon_delete_pattern_table	},
  {"MX340",		mx340_doc_icon_delete_pattern_table		},
  {"MX350",		mx340_doc_icon_delete_pattern_table		},
  {"MX870",		mx870_doc_icon_delete_pattern_table		},
  {"MP280",		mp270_doc_icon_delete_pattern_table		},
  {"MP495",		mp270_doc_icon_delete_pattern_table		},
  {"MG5100",	mg5200_doc_icon_delete_pattern_table	},
  {"IP4800",	ip4800_doc_icon_delete_pattern_table	},
  {"MG5200",	mg5200_doc_icon_delete_pattern_table	},
  {"MG6100",	mg8100_doc_icon_delete_pattern_table	},
  {"MG8100",	mg8100_doc_icon_delete_pattern_table	},
  {"MX360",		mx340_doc_icon_delete_pattern_table		},
  {"MX410",		mx340_doc_icon_delete_pattern_table		},
  {"MX420",		mx340_doc_icon_delete_pattern_table		},
  {"MX880",		mx880_doc_icon_delete_pattern_table		},
  {"IX6500",	ix6500_doc_icon_delete_pattern_table	},
  {"E500",		mg2100_doc_icon_delete_pattern_table	},
  {"MG2100",	mg2100_doc_icon_delete_pattern_table	},
  {"MG3100",	mg2100_doc_icon_delete_pattern_table	},
  {"MG4100",	mg4100_doc_icon_delete_pattern_table	},
  {"MG5300",	mg5300_doc_icon_delete_pattern_table	},
  {"IP4900",	ip4900_doc_icon_delete_pattern_table	},
  {"MG6200",	mg8200_doc_icon_delete_pattern_table	},
  {"MG8200",	mg8200_doc_icon_delete_pattern_table	},
  {"E600",		mx430_doc_icon_delete_pattern_table		},
  {"MX370",		mx430_doc_icon_delete_pattern_table		},
  {"MX430",		mx430_doc_icon_delete_pattern_table		},
  {"MX510",		mx510_doc_icon_delete_pattern_table		},
  {"MX710",		mx890_doc_icon_delete_pattern_table		},
  {"MX890",		mx890_doc_icon_delete_pattern_table		},
  {"MP230",		mp270_doc_icon_delete_pattern_table		},
  {"E510",		mg2100_doc_icon_delete_pattern_table	},
  {"MG2200",	mg2100_doc_icon_delete_pattern_table	},
  {"MG3200",	mg2100_doc_icon_delete_pattern_table	},
  {"MG4200",	mg4100_doc_icon_delete_pattern_table	},
  {"MG5400",	mg5400_doc_icon_delete_pattern_table	},
  {"IP7200",	ip7200_doc_icon_delete_pattern_table	},
  {"MG6300",	mg6300_doc_icon_delete_pattern_table	},
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
  { 'h', 'E'}, /* (B-34 ) DOC:1485 */
  { 'S', 'P'}, /* (B-35 ) DOC:1680 */
  { 'f', 'R'}, /* (B-36 ) DOC:1683 */
  { 'z', 'R'}, /* (B-36 ) DOC:1689 */
  { 'w', 'R'}, /* (B-38 ) DOC:1686 */
  { 'F', 'F'}, /* (B-68 ) DOC:1750 */
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
  {'C', ID_STS_MESSAGE_WAR_INKLOW_AFTER, ID_STS_MESSAGE_WAR_INKLOW_AFTER}, /*EMB*/
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
  {'C', ID_STS_MESSAGE_WAR_INKLOW_PRE, ID_STS_MESSAGE_WAR_INKLOW_PRE}, /*EMB*/
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
  {'C', ID_STS_MESSAGE_OC_REFILL, ID_STS_MESSAGE_OC_REFILL}, /*EMB*/
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
  {'C', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_REFILL_3rd, ID_STS_MESSAGE_OC_REFILL_3rd}, /*PDR No Region*/
  //InkUnknown 1st B-38(STID_C_004_003_001)
  {'1', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*America*/
  {'4', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*Canada*/
  {'C', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2}, /*PDR No Region*/
  //InkUnknown 3rd B-38(STID_C_004_003_001)
  {'1', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*America*/
  {'4', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*Canada*/
  {'C', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING, ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd_START_07SPRING}, /*PDR No Region*/
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
  {'C', ID_STS_MESSAGE_OC_INKOUT06_TANK, ID_STS_MESSAGE_OC_INKOUT06_TANK}, /*EMB*/
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
  {'C', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP, ID_STS_MESSAGE_OC_INKOUT06_TANK_MFP}, /*PDR No Region*/
  //InkOut OK B-4(STID_C_004_001_001)
  {'1', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*Canada*/
  {'C', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH, ID_STS_MESSAGE_OC_INKOUT06_TANK_TOUCH}, /*PDR No Region*/
  //Dispo
  //InkLow 1st D-1(STID_B_001_001_001)
  {'1', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*Japan*/
  {'2', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*Korea*/
  {'3', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*America*/
  {'4', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*Europe*/
  {'5', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*Australia*/
  {'6', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*Asia*/
  {'7', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*Laten America*/
  {'A', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*Brazil*/
  {'B', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*Canada*/
  {'C', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*EMB*/
  {' ', ID_STS_MESSAGE_WAR_INKLOW_40_PRE, ID_STS_MESSAGE_WAR_INKLOW_40_PRE}, /*PDR No Region*/
  //InkLow 3rd D-1(STID_B_001_001_001)
  {'1', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*Japan*/
  {'2', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*Korea*/
  {'3', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*America*/
  {'4', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*Europe*/
  {'5', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*Australia*/
  {'6', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*Asia*/
  {'7', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*Laten America*/
  {'A', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*Brazil*/
  {'B', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*Canada*/
  {'C', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*EMB*/
  {' ', ID_STS_MESSAGE_WAR_INKLOW_40_AFTER, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER}, /*PDR No Region*/
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
  {'C', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd}, /*EMB*/
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
  {'C', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP}, /*EMB*/
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
  {'C', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP}, /*PDR No Region*/
  //InkEmpty STOP TOUCH
  {'1', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*Canada*/
  {'C', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_TOUCH}, /*PDR No Region*/
  //InkEmpty RESUME B-53(STID_C_004_006_001)
  {'1', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*Canada*/
  {'C', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE}, /*PDR No Region*/
  //InkEmpty STOP/RESET1 B-53(STID_C_004_006_001)
  {'1', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*Canada*/
  {'C', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET_OUTPUTCOVER}, /*PDR No Region*/
  //InkEmpty STOP/RESET2 B-53(STID_C_004_006_001)
  {'1', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*Canada*/
  {'C', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOPRESET}, /*PDR No Region*/
  //InkEmpty STOP1 B-53(STID_C_004_006_001)
  {'1', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*Canada*/
  {'C', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP}, /*PDR No Region*/
  //InkEmpty STOP2 B-53(STID_C_004_006_001)
  {'1', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*Japan*/
  {'2', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*Korea*/
  {'3', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*America*/
  {'4', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*Europe*/
  {'5', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*Australia*/
  {'6', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*Asia*/
  {'7', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*S.Chinese*/
  {'8', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*T.Chinese*/
  {'9', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*Laten America*/
  {'A', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*Brazil*/
  {'B', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*Canada*/
  {'C', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*EMB*/
  {' ', ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_CARTRIDGE_STOP_OUTPUTCOVER}, /*PDR No Region*/

  {ENDTAG, ID_STS_MESSAGE_OC_INKEMPTY06_TANK_3rd_MFP_STOP, 0} /*default*/
};

