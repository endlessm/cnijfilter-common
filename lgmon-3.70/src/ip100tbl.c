/*  Canon Inkjet Print Filter.
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
 * ip100tbl.c 
 *
 * The conversion table for s300, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for ip100 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS ip100_dbs2busy[]={
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
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS ip100_djs2job[]={
  {"PR","P"},
  {"LD","L"},
  {"EJ","F"},
  {"ID","I"},
  {"CC","S"},
  {"WP","W"},
  {"DM","D"},
  {"SD","D"},
  {"DC","W"},
//{"TW",""},
  {"TC","W"},
//  {"TO","D"},
  {"NO","I"},
  {"UK","I"},
  {ENDTAG,ENDTAG}
};

/*
 * The kind of cartridge with which the present printer is equipped.
 */
ST_BSCC2STS ip100_chd2type[]={
  {"NO"," "},
  {"CL","T"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS ip100_prname2exchange[]={
  {"IP100","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS ip100_cir2color[]={
  {"BK","B"},
  {"CL","G"},
  {ENDTAG,ENDTAG}
};

/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS ip100_cil2inkchk[]={
  {"ON","Y"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */
ST_BSCC2STS ip100_lvr2posit[]={
  {"GAL,N","R"},
  {"GAL,W","L"},
  {ENDTAG,ENDTAG}
};

/*
 * Destination information.
 */
ST_BSCC2STS ip100_hri2destination[]={
  {"JP","J"},
  {"OTH","O"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS ip100_dws2warn[]={
  {"NO"," "},
  {"UK","?"},
  {"1500","T"},
  {"1570","F"},
  {"1800","S"},
  {"1801","s"},
  {"1900","1900"},
  {"1910","1910"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present operator call state.
 */
ST_BSCC2STS ip100_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
//Ver.2.90 alpha03 bug fix
  {"1000","X"},
//  {"1000","V"},
  {"1200","v"},
  {"1300","q"},
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
  {"1684","e"},
  {"1687","T"},
  {"1688","C"},
  {"1689","z"},
  {"1700","x"},
  {"1701","k"},
  {"1810","D"},
  {"2001","U"}, 
  {"2500","N"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS ip100_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5100","5100"},
  {"5200","5200"},
  {"5400","5400"},
  {"5B00","5B00"},
  {"5B01","5B01"},
//  {"5B00","I"},
//  {"5B01","J"},
  {"5C00","5C00"},
  {"5700","5700"},
  {"6000","6000"},
  {"6500","6500"},
  {"6800","6800"},
  {"6801","6801"},
  {"6A00","6A00"},
  {"6D00","6D00"},
  {"9000","9000"},
  {"A000","A000"},
  {"A100","A100"},    //Ver.2.90 don't use 0-9,A-F
//  {"A100","G"},    //Ver.2.90 don't use 0-9,A-F
  {"B200","B200"},
  {ENDTAG,ENDTAG}
};


/*
 * Information on a service call.
 */
ST_BSCC2STS ip100_dsc2service2[]={
  {"NO"," "},
  {"UK","?"},
  {"5100","M"},
  {"5200","M"},
  {"5400","M"},
  {"5B00","I"},
  {"5B01","J"},
  {"5C00","M"},
  {"5700","M"},
  {"6000","M"},
  {"6500","M"},
  {"6800","M"},
  {"6801","M"},
  {"6A00","M"},
  {"6D00","M"},
  {"9000","M"},
  {"A000","M"},
  {"A100","G"},    //Ver.2.90 don't use 0-9,A-F
  {"B200","M"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS ip100_ctk2alert[]={
//{"SET", ""},
  {"SETZ","Z"},
  {"NO",  "E"},
  {"UK",  "?"},
  {"IO",  "I"},
  {"EMP", "Y"},
  {"REG", "E"},
  {"IUK", "r"},
  {"LOW", "L"},
  {ENDTAG,ENDTAG}
};

/*
 * The function table for ip100.
 */
static const FUNCOFMODELSETPROCESS
 ip100setstsfunctable[] = {
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
  ip100_setink,
  ip100_setinkalert,
  NULL,
  NULL,
  //Ver.300
  NULL,
  //Ver.3.10
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_ip100chgtbl[] = {
  NULL,
  ip100_dbs2busy,
  ip100_djs2job,
  ip100_cil2inkchk,
  ip100_chd2type,
  ip100_prname2exchange,
  ip100_hri2destination,
  ip100_dws2warn,
  ip100_doc2operate,
  ip100_dsc2service,
  ip100_cir2color,
  ip100_ctk2alert,
  NULL,
  ip100_lvr2posit,
  //Ver.300
  NULL,
  //Ver.3.10
  ip100_dsc2service2,
};


/*
 * The corresponding function is called one by one.
 */
int processforip100(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;
  int maxfuncnum_ip100 = 16;

  for(i=0; i<maxfuncnum_ip100; i++ ){
  //for(i=0; i<MAXFUNCNUM; i++ ){
    if( ip100setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_ip100chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*ip100setstsfunctable[i])(p_s+i, p_ip100chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
