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
 * mp160tbl.c 
 *
 * The conversion table for s300, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for mp160 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS mp160_dbs2busy[]={
  {"NO"," "},
  {"UK","?"},
//{"WU","S"},
//{"SL","E"},
//{"SD",""},
  {"CL","L"},
  {"CC","C"},
  {"DS","I"},
//{"RS",""},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS mp160_djs2job[]={
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
  {ENDTAG,ENDTAG}
};

/*
 * The kind of cartridge with which the present printer is equipped.
 */
ST_BSCC2STS mp160_chd2type[]={
  {"NO"," "},
  {"NS","?"},
  {"BKH","N"},
  {"CLH","O"},
  {"BK","L"},
  {"CL","M"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS mp160_prname2exchange[]={
  {"MP160","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS mp160_cir2color[]={
  {"BK","B"},
  {"CL","E"},
  {ENDTAG,ENDTAG}
};

/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS mp160_cil2inkchk[]={
  {"ON","Y"},
  {"OF","N"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */
ST_BSCC2STS mp160_lvr2posit[]={
  {"IPG,W"," "},
  {"IPG,N"," "},
  {"IPG,U"," "},
  {ENDTAG,ENDTAG}
};

/*
 * Destination information.
 */
ST_BSCC2STS mp160_hri2destination[]={
  {"JP","J"},
  {"OTH","O"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS mp160_dws2warn[]={
  {"NO"," "},
  {"UK","?"},
  {"1501","B"},
  {"1510","E"},
  {"1900","1900"},
  {"1910","1910"},
  {"9010","9010"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present operator call state.
 */
ST_BSCC2STS mp160_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1000","P"},
  {"1200","O"},
  {"1300","J"},
  {"1401","b"},
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
  {"1485","b"},
  {"1600","B"},
  {"1660","T"},
  {"1682","b"},
  {"1683","z"},
  {"1684","b"},
//  {"1685","W"}, 06 not support
  {"1686","w"},
  {"1687","T"},
  {"1700","x"},
  {"1701","x"},
  {"1710","x"},
  {"1711","x"},
  {"2001","U"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS mp160_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5010","5010"},//add Ver.2.70 beta2
  {"5100","5100"},
  {"5200","5200"},//add Ver.2.70 beta2
  {"5400","5400"},//add Ver.2.70 beta2
  {"5700","5700"},//add Ver.2.70 beta2
  {"5B00","I"},
  {"5B01","J"},
  {"5B10","I"},
  {"5B11","J"},
  {"5C00","5C00"},//add Ver.2.70 beta2
  {"6000","6000"},
  {"6500","6500"},//add Ver.2.70 beta2
  {"6800","6800"},
  {"6A00","6A00"},//add Ver.2.70 beta2
  {"6D00","6D00"},//add Ver.2.70 beta2
  {"9000","9000"},//add Ver.2.70 beta2
  {"B200","B200"}, //add Ver.2.70 beta2
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS mp160_ctk2alert[]={
  {"NO",  "E"},
  {"NS",  "E"},
//{"SET", ""},
  {"SETZ","Z"},
  {"HRD","E"},
  {"IUK1","R"},
  {"IUK2","R"},
  {"REG", "E"},
  {"IO",  "I"},
  {"RUK", "R"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a HCF.
 */
ST_BSCC2STS mp160_hcf2warn[]={
  {"NO", " "},
  {"BK", "Z"},
  {"CL", "Z"},
  {"AL", "Z"},
  {ENDTAG,ENDTAG}
};

/*
 * The function table for mp160.
 */
static const FUNCOFMODELSETPROCESS
 mp160setstsfunctable[] = {
  NULL,
  NULL,
  NULL,
  NULL,
  mp160_setcartridgetype,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  mp160_setink,
  mp160_setinkalert,
  mp160_setwarning,
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_mp160chgtbl[] = {
  NULL,
  mp160_dbs2busy,
  mp160_djs2job,
  mp160_cil2inkchk,
  mp160_chd2type,
  mp160_prname2exchange,
  mp160_hri2destination,
  mp160_dws2warn,
  mp160_doc2operate,
  mp160_dsc2service,
  mp160_cir2color,
  mp160_ctk2alert,
  mp160_hcf2warn,
  mp160_lvr2posit,
};


/*
 * The corresponding function is called one by one.
 */
int processformp160(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
    if( mp160setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_mp160chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*mp160setstsfunctable[i])(p_s+i, p_mp160chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
