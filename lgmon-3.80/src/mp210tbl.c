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
 * mp210tbl.c 
 *
 * The conversion table for s300, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for mp210 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS mp210_dbs2busy[]={
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
ST_BSCC2STS mp210_djs2job[]={
  {"PR","P"},
  {"LD","L"},
  {"EJ","F"},
  {"ID","I"},
  {"CC","S"},
  {"WP","W"},
  {"DM","D"},
  {"SD","D"},
  {"DC","W"},
  {"TC","W"},
  {"NO","I"},
  {"UK","I"},
  {ENDTAG,ENDTAG}
};

/*
 * The kind of cartridge with which the present printer is equipped.
 */
ST_BSCC2STS mp210_chd2type[]={
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

ST_BSCC2STS mp210_prname2exchange[]={
  {"MP140","F"},
  {"MP210","F"},
  {"MP190","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS mp210_cir2color[]={
  {"BK","B"},
  {"CL","E"},
  {ENDTAG,ENDTAG}
};

/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS mp210_cil2inkchk[]={
//  {"ON","Y"},
//  {"OF","N"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */
ST_BSCC2STS mp210_lvr2posit[]={
  {"IPG,W"," "},
  {"IPG,N"," "},
  {"IPG,U"," "},
  {ENDTAG,ENDTAG}
};

/*
 * Destination information.
 */
ST_BSCC2STS mp210_hri2destination[]={
  {"JP","J"},
  {"OTH","O"},
  {"ASI","A"},
  {"PAM","P"},
  {"EU","E"},
  {"ZZZ","Z"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS mp210_dws2warn[]={
  {"NO"," "},
  {"UK","?"},
  {"1499","t"},
  {"1500","T"},
  {"1900","1900"},
  {"1910","1910"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present operator call state.
 */
ST_BSCC2STS mp210_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1000","X"},
  {"1200","v"},
  {"1250","o"},
  {"1300","q"},
  {"1401","H"},
  {"1403","r"},
  {"1485","H"},
  {"1682","e"},
  {"1684","e"},
  {"1686","w"},
  {"1687","T"},
  {"1688","C"}, 
  {"1700","x"},
  {"1701","k"},
  {"1710","x"},
  {"1711","k"},
  {"2001","U"},
  {"2002","U"}, //not support MP140
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS mp210_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5010","5010"},
  {"5100","5100"},
  {"5200","5200"},
  {"5400","5400"},
  {"5700","5700"},
  {"5B00","I"},
  {"5B01","J"},
  {"5B10","I"},
  {"5B11","J"},
  {"5C00","5C00"},
  {"6000","6000"},
  {"6500","6500"},
  {"6800","6800"},
  {"6801","6801"}, //not support MP140
  {"6A00","6A00"},
  {"6D00","6D00"}, //not support MP210
  {"9000","9000"},
  {"B200","B200"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS mp210_ctk2alert[]={
//{"SET", ""},
  {"SETZ","Z"},
  {"NO",  "E"},
  {"NS",  "E"},
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
ST_BSCC2STS mp210_hcf2warn[]={
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
ST_BSCC2STS mp210_pdr2prnregion[]={
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
 * The function table for mp210.
 */
static const FUNCOFMODELSETPROCESS
 mp210setstsfunctable[] = {
  NULL,
  NULL,
  NULL,
  NULL,
  mp210_setcartridgetype,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  mp210_setink,
  mp210_setinkalert,
  mp210_setwarning,
  NULL,
//Ver.300
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_mp210chgtbl[] = {
  NULL,
  mp210_dbs2busy,
  mp210_djs2job,
  mp210_cil2inkchk,
  mp210_chd2type,
  mp210_prname2exchange,
  mp210_hri2destination,
  mp210_dws2warn,
  mp210_doc2operate,
  mp210_dsc2service,
  mp210_cir2color,
  mp210_ctk2alert,
  mp210_hcf2warn,
  mp210_lvr2posit,
//Ver.300
  mp210_pdr2prnregion,
};


/*
 * The corresponding function is called one by one.
 */
int processformp210(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
    if( mp210setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_mp210chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*mp210setstsfunctable[i])(p_s+i, p_mp210chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
