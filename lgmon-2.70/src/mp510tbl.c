/*  Canon Inkjet Printer Driver for Linux
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

/*
 * mp510tbl.c 
 *
 * The conversion table for xxx, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for mp510 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS mp510_dbs2busy[]={
  {"NO"," "},
  {"UK","?"},
//{"WU","S"},
//{"SL","E"},
//{"SD",""},
  {"CL","L"},
  {"CC","D"},
//{"TP","T"},
  {"DS","I"},
//{"RS",""},
//{"OB",""},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS mp510_djs2job[]={
  {"NO"," "},
  {"UK","?"},
  {"ID","I"},
  {"PR","P"},
  {"LD","L"},
  {"EJ","F"},
  {"CC","C"},
//{"WP",""},
//{"DM",""},
//{"SD",""},
//{"DC",""},
//{"TW",""},
//{"TC",""},
//{"TO",""},
  {ENDTAG,ENDTAG}
};

/*
 * The kind of cartridge with which the present printer is equipped.
 */
ST_BSCC2STS mp510_chd2type[]={
  {"NO"," "},
  {"CL","S"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS mp510_prname2exchange[]={
  {"MP510","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS mp510_cir2color[]={
  {"BK","l"},
  {"C","C"},
  {"M","M"},
  {"Y","Y"},
  {ENDTAG,ENDTAG}
};

/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS mp510_cil2inkchk[]={
  {"ON","Y"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */
ST_BSCC2STS mp510_lvr2posit[]={
  {"GAL,AT"," "},
  {"GAL,CW"," "},
  {ENDTAG,ENDTAG}
};

/*
 * Destination information.
 */
ST_BSCC2STS mp510_hri2destination[]={
  {"JP","J"},
  {"OTH","O"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS mp510_dws2warn[]={
  {"NO"," "},
  {"UK","?"},
  {"1500","T"},
  {"1570","F"},
  {"1900","1900"},
  {"1910","1910"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present operator call state.
 */
ST_BSCC2STS mp510_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1000","X"},
  {"1001","r"},
  {"1002","r"},
  {"1003","a"},
  {"1200","v"},
//  {"1250","k"}, not suppport
  {"1300","h"},
  {"1303","n"},
  {"1310","r"},
  {"1401","H"},
  {"1403","r"},
  {"1405","r"},
  {"1410","t"},
  {"1411","t"},
  {"1412","t"},
  {"1413","t"},
  {"1414","t"},
  {"1415","t"},
  {"1416","t"},
  {"1417","t"},
  {"1418","t"},
  {"1419","t"},
  {"1600","u"},
  {"1660","d"},
  {"1680","S"},
  {"1681","s"},
  {"1683","z"},
  {"1684","e"},
  {"1688","C"},
  {"1700","x"},
  {"1701","x"},
  {"1710","x"},
  {"1711","x"},
  {"2001","U"},
  {"2500","A"}, //not support?
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS mp510_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5010","5010"},//add Ver.2.70 beta2
  {"5100","5100"},
  {"5110","5110"},
  {"5200","5200"},
  {"5400","5400"},
  {"5700","5700"},
  {"5710","5710"}, //add Ver.2.70 beta2
  {"5750","5750"}, //add Ver.2.70 beta2
  {"5B00","I"},
  {"5B01","J"},
  {"5B10","I"},
  {"5B11","J"},
  {"5C00","5C00"},
  {"5C10","5C10"}, //add Ver.2.70 beta2
  {"6000","6000"},
  {"6500","6500"},
  {"6502","6502"},
  {"6800","6800"},
  {"6A00","6A00"},
  {"6B00","6B00"},
  {"6B10","6B10"},
  {"6C00","6C00"},
  {"6D00","6D00"},
  {"9000","9000"},
  {"B200","B200"}, //add Ver.2.70 beta2
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS mp510_ctk2alert[]={
  {"NO",  "E"},
  {"UK",  "?"},
//{"SET", ""},
  {"SETZ","Z"},
//{"POS0",""},
  {"POS1","P"},
  {"POS2","P"},
  {"POS3","P"},
  {"POS4","P"},
  {"MUL", "M"},
  {"RFL", "R"},
  {"REG", "E"},
  {"IO",  "I"},
  {"LOW", "L"},
  {"EMP", "Y"},
  {"RUK", "R"},
  {ENDTAG,ENDTAG}
};

/*
 * The function table for mp510.
 */
static const FUNCOFMODELSETPROCESS
 mp510setstsfunctable[] = {
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
  mp510_setink,
  mp510_setinkalert,
  NULL,
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_mp510chgtbl[] = {
  NULL,
  mp510_dbs2busy,
  mp510_djs2job,
  mp510_cil2inkchk,
  mp510_chd2type,
  mp510_prname2exchange,
  mp510_hri2destination,
  mp510_dws2warn,
  mp510_doc2operate,
  mp510_dsc2service,
  mp510_cir2color,
  mp510_ctk2alert,
  NULL,
  mp510_lvr2posit,
};


/*
 * The corresponding function is called one by one.
 */
int processformp510(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
    if( mp510setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_mp510chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*mp510setstsfunctable[i])(p_s+i, p_mp510chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
