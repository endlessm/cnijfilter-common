/*  Canon Inkjet Printer Driver for Linux
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
 *
 * NOTE:
 *  - As a special exception, this program is permissible to link with the
 *    libraries released as the binary modules.
 *  - If you write modifications of your own for these programs, it is your
 *    choice whether to permit this exception to apply to your modifications.
 *    If you do not wish that, delete this exception.
 */


/*
 * mp600tbl.c 
 *
 * The conversion table for xxx, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for mp600 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS mp600_dbs2busy[]={
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
ST_BSCC2STS mp600_djs2job[]={
  {"PR","P"},
  {"LD","L"},
  {"EJ","F"},
  {"ID","I"},
  {"CC","S"},
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
ST_BSCC2STS mp600_chd2type[]={
  {"NO"," "},
  {"CL","P"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS mp600_prname2exchange[]={
  {"MP600","F"},
  {"MP610","F"},
  {"IP4500","F"},
  {"IP4300","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS mp600_cir2color[]={
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
ST_BSCC2STS mp600_cil2inkchk[]={
//  {"ON","Y"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */
ST_BSCC2STS mp600_lvr2posit[]={
  {"GAL,AT"," "},
  {"GAL,CW"," "},
  {ENDTAG,ENDTAG}
};

/*
 * Destination information.
 */
ST_BSCC2STS mp600_hri2destination[]={
  {"JP","J"},
  {"OTH","O"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS mp600_dws2warn[]={
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
ST_BSCC2STS mp600_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1000","X"},
  {"1001","r"},
  {"1002","r"},
  {"1003","p"},
  {"1200","v"},
  {"1250","o"},
  {"1300","q"},
  {"1303","n"},
  {"1304","i"},
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
  {"1683","f"},
  {"1684","e"},
  {"1688","C"},
  {"1700","x"},
  {"1701","k"},
  //Ver.2.80 fix
  {"1841","g"},  //{"1841","r"},
  //Ver.2.80 fix
  {"1846","K"},  //{"1846","r"},
  {"1850","r"},
  {"1851","g"},
  {"1855","r"},
  {"1856","K"},
  {"2001","U"},
  {"2002","U"}, //not support MP600
  {"2500","N"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS mp600_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5010","5010"},//add Ver.2.70 beta2
  {"5100","5100"},
  {"5110","5110"},
  {"5200","5200"},
  {"5400","5400"},
  {"5700","5700"},
  {"5B00","I"},
  {"5B01","J"},
  {"5C00","5C00"},
  {"5C10","5C10"},//add Ver.2.80 for MP610
  {"5C20","5C20"},//add Ver.2.70 beta2
  {"6000","6000"},
  {"6010","6010"},//add Ver.2.70 beta2
  {"6500","6500"},
  {"6502","6502"},
  {"6800","6800"},
  {"6801","6801"},//add Ver.2.80 for MP610
  {"6A00","6A00"},
  {"6B00","6B00"},
  {"6B10","6B10"},
  {"6C00","6C00"},//not support MP610
  {"6D00","6D00"},//not support MP610
  {"9000","9000"},
  {"B200","B200"}, //add Ver.2.70 beta2
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS mp600_ctk2alert[]={
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
 * The function table for mp600.
 */
static const FUNCOFMODELSETPROCESS
 mp600setstsfunctable[] = {
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
  mp600_setink,
  mp600_setinkalert,
  NULL,
  NULL,
  //Ver.300
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_mp600chgtbl[] = {
  NULL,
  mp600_dbs2busy,
  mp600_djs2job,
  mp600_cil2inkchk,
  mp600_chd2type,
  mp600_prname2exchange,
  mp600_hri2destination,
  mp600_dws2warn,
  mp600_doc2operate,
  mp600_dsc2service,
  mp600_cir2color,
  mp600_ctk2alert,
  NULL,
  mp600_lvr2posit,
  //Ver.300
  NULL,
};


/*
 * The corresponding function is called one by one.
 */
int processformp600(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
    if( mp600setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_mp600chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*mp600setstsfunctable[i])(p_s+i, p_mp600chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
