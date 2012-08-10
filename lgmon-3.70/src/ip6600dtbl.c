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
 * ip6600dtbl.c 
 *
 * The conversion table for s300, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for ip6600d conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS ip6600d_dbs2busy[]={
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
ST_BSCC2STS ip6600d_djs2job[]={
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
ST_BSCC2STS ip6600d_chd2type[]={
  {"NO"," "},
  {"LS","Q"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS ip6600d_prname2exchange[]={
  {"IP6600D","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS ip6600d_cir2color[]={
  {"PBK","L"},
  {"C","C"},
  {"M","M"},
  {"Y","Y"},
  {"LC","c"},
  {"LM","m"},
  {ENDTAG,ENDTAG}
};

/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS ip6600d_cil2inkchk[]={
  {"ON","Y"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 *
 *	v2.60
 *	The value of HRI is inserted in Lever_position. 
 *	Because the display of Lever position was deleted, it substitutes it. 
 *
 */
ST_BSCC2STS ip6600d_lvr2posit[]={
//  {"GAL,AT"," "},
//  {"GAL,CW"," "},
  {"JP","J"},
  {"OTH","O"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS ip6600d_dws2warn[]={
  {"NO"," "},
  {"UK","?"},
  {"1501","L"},
  {"1511","Y"},
  {"1512","M"},
  {"1513","C"},
  {"1534","m"},
  {"1535","c"},
  {"1900","1900"},
  {"1910","1910"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present operator call state.
 */
ST_BSCC2STS ip6600d_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1000","X"},
  {"1001","r"},
  {"1002","r"},
  {"1003","a"},
  {"1200","v"},
  {"1250","o"},
  {"1300","h"},
  {"1303","n"},
  {"1304","Z"},
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
  {"1700","x"},
  {"1841","r"},
  {"1846","r"},
  {"1850","r"},
  {"1851","g"},
  {"1855","r"},
  {"1856","K"},
  {"2001","U"},
  {"2500","N"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS ip6600d_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5100","5100"},
  {"5110","5110"},
  {"5200","5200"},
  {"5400","5400"},
  {"5700","5700"},
  {"5B00","I"},
  {"5C00","5C00"},
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
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS ip6600d_ctk2alert[]={
  {"NO",  "E"},
  {"UK",  "?"},
//{"SET", ""},
//{"SETZ",""},
//{"POS0",""},
  {"POS1","P"},
  {"POS2","P"},
  {"POS3","P"},
  {"POS4","P"},
  {"POS5","P"},
  {"POS6","P"},
  {"MUL", "M"},
  {"RFL", "R"},
  {"REG", "E"},
  {"IO",  "I"},
  {ENDTAG,ENDTAG}
};

/*
 * The function table for ip6600d.
 */
static const FUNCOFMODELSETPROCESS
 ip6600dsetstsfunctable[] = {
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
  ip6600d_setink,
  ip6600d_setinkalert,
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_ip6600dchgtbl[] = {
  NULL,
  ip6600d_dbs2busy,
  ip6600d_djs2job,
  ip6600d_cil2inkchk,
  ip6600d_chd2type,
  ip6600d_prname2exchange,
  ip6600d_lvr2posit,
  ip6600d_dws2warn,
  ip6600d_doc2operate,
  ip6600d_dsc2service,
  ip6600d_cir2color,
  ip6600d_ctk2alert,
  NULL,
};


/*
 * The corresponding function is called one by one.
 */
int processforip6600d(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
    if( ip6600dsetstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_ip6600dchgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*ip6600dsetstsfunctable[i])(p_s+i, p_ip6600dchgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
