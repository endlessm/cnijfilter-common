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
 * ip2500tbl.c 
 *
 * The conversion table for s300, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for ip2500 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS ip2500_dbs2busy[]={
  {"WU","B"},
  {"SL","B"},
  {"SD","B"},
  {"RS",""},
  {"CL","L"},
  {"CC","D"},
  {"TP","T"},
  {"NO",""},
  {"UK",""},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS ip2500_djs2job[]={
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
//{"TC","W"},
//{"TO","D"},
  {"NO","I"},
  {"UK","I"},
  {ENDTAG,ENDTAG}
};

/*
 * The kind of cartridge with which the present printer is equipped.
 */
ST_BSCC2STS ip2500_chd2type[]={
  {"NO"," "},
  {"NS","?"},
  {"BKM","U"},
  {"CLM","V"},
  {"BKH","N"},
  {"CLH","O"},
  {"BK","L"},
  {"CL","M"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS ip2500_prname2exchange[]={
  {"IP2500","F"},
  {"IP1800","F"},
  {"IP2600","F"},
  {"IP1900","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS ip2500_cir2color[]={
  {"BK","B"},
  {"CL","E"},
  {ENDTAG,ENDTAG}
};

/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS ip2500_cil2inkchk[]={
  {"ON","Y"},
  {"OF","N"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */
ST_BSCC2STS ip2500_lvr2posit[]={
  {"IPG,W"," "},
  {"IPG,N"," "},
  {"IPG,U"," "},
  {ENDTAG,ENDTAG}
};

/*
 * Destination information.
 */
ST_BSCC2STS ip2500_hri2destination[]={
  {"JP","J"},
  {"OTH","O"},
  {"ASI","A"},
  {"PAM","P"},
  {"EU","E"},
  {"ZZZ","Z"}, //Ver.2.90 
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS ip2500_dws2warn[]={
  {"NO"," "},
  {"UK","?"},
  {"1499","t"},
  {"1500","T"},
  {"1900","1900"},
  {"1910","1910"},
  {"9010","9010"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present operator call state.
 */
ST_BSCC2STS ip2500_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1000","X"},
  {"1200","v"},
  {"1250","o"},
  {"1300","q"},
  {"1401","H"},
  {"1485","H"},
  {"1682","e"},
  {"1684","e"},
  {"1686","w"},
  {"1687","T"}, //06 1660 --> 1687
  {"1688","C"}, 
  {"1700","x"},
  {"1701","k"},
  {"1710","x"},
  {"1711","k"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS ip2500_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5100","5100"},
  {"5201","5201"},
  {"5202","5202"},
  {"5600","5600"},
  {"5B00","I"},
  {"5B01","J"},
  {"5B10","I"},
  {"5B11","J"},
  {"6000","6000"},
  {"6800","6800"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS ip2500_ctk2alert[]={
  {"NO",  "E"},
  {"NS",  "E"},
//{"SET", ""},
  {"SETZ","Z"},
  {"HRD","E"},
  {"IUK2","R"},
  {"REG", "E"},
  {"EMP", "Y"},
  {"LLOW", "l"},
  {"LOW", "L"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a HCF.
 */
ST_BSCC2STS ip2500_hcf2warn[]={
  {"NO", " "},
  {"BK", "z"},
  {"CL", "z"},
  {"AL", "z"},
  {ENDTAG,ENDTAG}
};

//Ver.3.00
/*
 * Printer Destination information.
*/
ST_BSCC2STS ip2500_pdr2prnregion[]={
  {"1", "1"}, /*Japan*/
  {"2", "2"}, /*Korea*/
  {"3", "3"}, /*America*/
  {"4", "4"}, /*Europe*/
  {"5", "5"}, /*Australia*/
  {"6", "6"}, /*Asia*/
  {"7", "7"}, /*S.Chinese*/
  {"8", "8"}, /*T.Chinese*/
  {"9", "9"}, /*Laten America*/
  {"A", "A"}, /*Brazil*/
  {"B", "B"}, /*Canada*/
  {ENDTAG,ENDTAG}
};

/*
 * The function table for ip2500.
 */
static const FUNCOFMODELSETPROCESS
 ip2500setstsfunctable[] = {
  NULL,
  NULL,
  NULL,
  NULL,
  ip2500_setcartridgetype,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  ip2500_setink,
  ip2500_setinkalert,
  ip2500_setwarning,
  NULL,
//Ver.300
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_ip2500chgtbl[] = {
  NULL,
  ip2500_dbs2busy,
  ip2500_djs2job,
  ip2500_cil2inkchk,
  ip2500_chd2type,
  ip2500_prname2exchange,
  ip2500_hri2destination,
  ip2500_dws2warn,
  ip2500_doc2operate,
  ip2500_dsc2service,
  ip2500_cir2color,
  ip2500_ctk2alert,
  ip2500_hcf2warn,
  ip2500_lvr2posit,
//Ver.300
  ip2500_pdr2prnregion,
};


/*
 * The corresponding function is called one by one.
 */
int processforip2500(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
    if( ip2500setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_ip2500chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*ip2500setstsfunctable[i])(p_s+i, p_ip2500chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
