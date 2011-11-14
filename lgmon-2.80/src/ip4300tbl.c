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
 * ip4300tbl.c 
 *
 * The conversion table for s300, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for ip4300 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS ip4300_dbs2busy[]={
  {"WU","B"},
  {"SL","B"},
  {"SD","B"},
  {"CL","L"},
  {"CC","D"},
  {"TP","T"},
  {"DS","I"},
  {"RS",""},
  {"OB","B"},
  {"NO",""},
  {"UK",""},
//  {"NO"," "},
//  {"UK","?"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS ip4300_djs2job[]={
  {"PR","P"},
  {"LD","L"},
  {"EJ","F"},
  {"ID","I"},
  {"CC","C"},
  {"WP","W"},
  {"DM","D"},
  {"SD","D"},
  {"DC","W"},
//Ver.2.80 a02 bug fix for MP140
  {"TW","P"},
//{"TW",""},
  {"TC","W"},
  {"TO","D"},
  {"NO","I"},
  {"UK","I"},
  {ENDTAG,ENDTAG}
};

/*
 * The kind of cartridge with which the present printer is equipped.
 */
ST_BSCC2STS ip4300_chd2type[]={
  {"NO"," "},
  {"CL","P"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS ip4300_prname2exchange[]={
  {"IP4300","F"},
  {"IP4500","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS ip4300_cir2color[]={
  {"BK","l"},
  {"PBK","L"},
  {"C","C"},
  {"M","M"},
  {"Y","Y"},
  {ENDTAG,ENDTAG}
};

/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS ip4300_cil2inkchk[]={
//  {"ON","Y"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */
ST_BSCC2STS ip4300_lvr2posit[]={
  {"GAL,AT"," "},
  {"GAL,CW"," "},
  {ENDTAG,ENDTAG}
};

/*
 * Destination information.
 */
ST_BSCC2STS ip4300_hri2destination[]={
  {"JP","J"},
  {"OTH","O"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS ip4300_dws2warn[]={
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
ST_BSCC2STS ip4300_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1000","V"},
  {"1001","R"},
  {"1002","R"},
  {"1003","p"},
  {"1200","v"},
  {"1250","o"},
  {"1300","q"},
  {"1303","j"},
  {"1304","Q"},
  {"1310","R"},
  {"1401","H"},
  {"1403","R"},
  {"1405","R"},
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
  {"1600","E"},
  {"1660","d"},
  {"1680","S"},
  {"1681","s"},
  {"1683","f"},
  {"1684","e"},
  {"1688","C"},
  {"1700","I"},
  {"1701","I"},
  //Ver.2.80 fix
  {"1841","G"}, //{"1841","R"},
  //Ver.2.80 fix
  {"1846","F"}, //{"1846","R"},
  {"1850","R"},
  {"1851","G"},
  {"1855","R"},
  {"1856","F"},
  {"2001","U"},
  {"2002","U"},
  {"2500","A"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS ip4300_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5100","5100"},
  {"5110","5110"},
  {"5200","5200"},
  {"5400","5400"},
  {"5700","5700"},
  {"5B00","I"},
  {"5B01","J"},
  {"5C00","5C00"},
  {"5C10","5C10"},//add Ver.2.80 for iP4500
  {"5C20","5C20"},//add Ver.2.70 beta2
  {"6000","6000"},
  {"6010","6010"},//add Ver.2.80 for iP4500
  {"6500","6500"},
  {"6502","6502"},
  {"6800","6800"},
  {"6801","6801"},//add Ver.2.80 for iP4500
  {"6A00","6A00"},
  {"6B00","6B00"},
  {"6B10","6B10"},
  {"6C00","6C00"},//not support iP4500
  {"6D00","6D00"},//not support iP4500
  {"9000","9000"},
  {"B200","B200"}, //add Ver.2.70 beta2
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS ip4300_ctk2alert[]={
//{"SET", ""},
  {"SETZ","Z"},
  {"NO",  "E"},
  {"UK",  "?"},
//{"POS0",""},
  {"POS1","P"},
  {"POS2","P"},
  {"POS3","P"},
  {"POS4","P"},
  {"POS5","P"},
  {"MUL", "M"},
  {"RUK", "R"},
  {"REG", "E"},
  {"IO",  "I"},
  {"EMP", "Y"},
  {"LOW", "L"},
  {ENDTAG,ENDTAG}
};

/*
 * The function table for ip4300.
 */
static const FUNCOFMODELSETPROCESS
 ip4300setstsfunctable[] = {
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
  ip4300_setink,
  ip4300_setinkalert,
  NULL,
  //Ver.2.70
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_ip4300chgtbl[] = {
  NULL,
  ip4300_dbs2busy,
  ip4300_djs2job,
  ip4300_cil2inkchk,
  ip4300_chd2type,
  ip4300_prname2exchange,
  //Ver.2.70
  ip4300_hri2destination,
  ip4300_dws2warn,
  ip4300_doc2operate,
  ip4300_dsc2service,
  ip4300_cir2color,
  ip4300_ctk2alert,
  NULL,
  //Ver.2.70
  ip4300_lvr2posit,
};


/*
 * The corresponding function is called one by one.
 */
int processforip4300(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
    if( ip4300setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_ip4300chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*ip4300setstsfunctable[i])(p_s+i, p_ip4300chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
