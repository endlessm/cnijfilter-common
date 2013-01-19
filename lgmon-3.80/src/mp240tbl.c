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
 * mp240tbl.c 
 *
 * The conversion table for mp240, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for mp240 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS mp240_dbs2busy[]={
  {"WU","B"},
  {"SL","B"},
  {"SD","B"},
  {"RS",""},
  {"CL","L"},
  {"CC","D"},
  {"TP","T"},
  {"DS","I"},
  {"NO",""},
  {"UK",""},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS mp240_djs2job[]={
  {"PR","P"},
  {"LD","L"},
  {"EJ","F"},
  {"ID","I"},
  {"CC","S"},
  {"EC","P"},  /* Ver.3.00 New */
  {"SC","S"},  /* Ver.3.20 */
  {"WP","W"},
  {"DM","D"},
  {"SD","D"},
  {"DC","W"},
  {"NO","I"},
  {"UK","I"},
  {ENDTAG,ENDTAG}
};

/*
 * The kind of cartridge with which the present printer is equipped.
 */
ST_BSCC2STS mp240_chd2type[]={
  {"NO"," "},
  {"NS","?"},
  {"BKM","U"},
  {"CLM","V"},
  {"BK","L"},
  {"CL","M"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS mp240_prname2exchange[]={
  {"MP240","F"},
  {"MX320","F"},
  {"MX330","F"},
  {"MP250","F"},
  {"MP270","F"},
  {"MP490","F"},
  {"IP2700","F"},
  {"MX340","F"},
  {"MX350","F"},
  {"MP280","F"},
  {"MP495","F"},
  {"MX360","F"},
  {"MX410","F"},
  {"MX420","F"},
  {"MP230","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS mp240_cir2color[]={
  {"BK","B"},
  {"CL","E"},
  {ENDTAG,ENDTAG}
};

/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS mp240_cil2inkchk[]={
//  {"ON","Y"},
//  {"OF","N"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */
ST_BSCC2STS mp240_lvr2posit[]={
  {"GAL,AT"," "},
  {"GAL,CW"," "},
  {ENDTAG,ENDTAG}
};

/*
 * Destination information.
 */
ST_BSCC2STS mp240_hri2destination[]={
  {"JP","J"},
  {"ASI","A"},
  {"PAM","P"},
  {"EU","E"},
  {"CHN","C"},/* Ver.3.30 */
  {"ZZZ","Z"},
  {"0","0"},
  {"3","3"},
  {"7","7"},
  {"8","8"},
  {"9","9"},
  {"C","C"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS mp240_dws2warn[]={
  {"NO"," "},
  {"UK","?"},
  {"1499","t"},
  {"1500","T"},
  {"1900","P"}, /* MX320 */
//  {"1900","1900"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present operator call state.
 */
ST_BSCC2STS mp240_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1000","X"},
  {"1200","v"},
  {"1251","o"}, /* MX320 */
  {"1300","q"},
  {"1401","H"},
  {"1403","r"},
  {"1485","H"},
  {"1486","S"}, /* MP230 */
  {"1487","s"}, /* MP230 */
  {"1682","e"},
  {"1684","e"},
  {"1686","w"},
  {"1687","T"},
  {"1688","C"},
  {"1700","x"},
  {"1701","k"},
  {"2001","U"},
  {"2002","U"},
  {"2700","Z"}, /* MX320 */
  {"2801","Z"}, /* MX340 */
  {"2802","Z"}, /* MX340 */
  {"2803","Z"}, /* MX340 */
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS mp240_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5011","5011"},
  {"5012","5012"},
  {"5100","5100"},
  {"5110","5110"},
  {"5200","5200"},
  {"5400","5400"},
  {"5700","5700"},
  {"5B00","5B00"},
  {"5B01","5B01"},
  {"6000","6000"},
  {"6500","6500"},
  {"6800","6800"},
  {"6801","6801"},
  {"6930","6930"}, /* MP230 */
  {"6931","6931"}, /* MP230 */
  {"6932","6932"}, /* MP230 */
  {"6933","6933"}, /* MP230 */
  {"6936","6936"}, /* MP230 */
  {"6937","6937"}, /* MP230 */
  {"6938","6938"}, /* MP230 */
  {"6940","6940"}, /* MP230 */
  {"6941","6941"}, /* MP230 */
  {"6942","6942"}, /* MP230 */
  {"6943","6943"}, /* MP230 */
  {"6944","6944"}, /* MP230 */
  {"6945","6945"}, /* MP230 */
  {"6946","6946"}, /* MP230 */
  {"9000","9000"},
  {"B200","B200"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS mp240_dsc2service2[]={
  {"NO"," "},
  {"UK","?"},
  {"5011","M"},
  {"5012","M"},
  {"5100","R"},/* Ver.3.80 M-->R */
  {"5200","M"},
  {"5400","M"},
  {"5700","M"},
  {"5B00","I"},
  {"5B01","J"},
  {"6000","M"},
  {"6500","M"},
  {"6800","M"},
  {"6801","M"},
  {"6930","M"},
  {"6931","M"},
  {"6932","M"},
  {"6933","M"},
  {"6936","M"},
  {"6937","M"},
  {"6938","M"},
  {"6940","M"},
  {"6941","M"},
  {"6942","M"},
  {"6943","M"},
  {"6944","M"},
  {"6945","M"},
  {"6946","M"},
  {"9000","M"},
  {"B200","V"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS mp240_ctk2alert[]={
//{"SET", ""},
  {"SETZ","Z"},
  {"NO",  "E"},
  {"NS",  "E"},
  {"POS1","P"},
  {"POS2","P"},
  {"MUL", "M"},
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
ST_BSCC2STS mp240_hcf2warn[]={
  {"NO", " "},
  {"NO", " "},
  {"BK", " "},
  {"CL", " "},
  {"AL", " "},
/*  {"BK", "z"}, not support Ver.3.80 */
/*  {"CL", "z"}, not support Ver.3.80 */
/*  {"AL", "z"}, not support Ver.3.80 */
  {ENDTAG,ENDTAG}
};

//Ver.3.00
/*
 * Printer Destination information.
*/
ST_BSCC2STS mp240_pdr2prnregion[]={
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
  {"C", "C"}, /*EMB*/
  {ENDTAG,ENDTAG}
};

/*
 * The function table for mp240.
 */
static const FUNCOFMODELSETPROCESS
 mp240setstsfunctable[] = {
  NULL,
  NULL,
  NULL,
  NULL,
  mp240_setcartridgetype,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  mp240_setink,
  mp240_setinkalert,
  mp240_setwarning,
  NULL,
  //Ver.300
  NULL,
  //Ver.3.10
  NULL,
  //Ver.3.80
  NULL,
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_mp240chgtbl[] = {
  NULL,
  mp240_dbs2busy,
  mp240_djs2job,
  mp240_cil2inkchk,
  mp240_chd2type,
  mp240_prname2exchange,
  mp240_hri2destination,
  mp240_dws2warn,
  mp240_doc2operate,
  mp240_dsc2service,
  mp240_cir2color,
  mp240_ctk2alert,
  mp240_hcf2warn,
  mp240_lvr2posit,
  //Ver.300
  mp240_pdr2prnregion,
  //Ver.3.10
  mp240_dsc2service2,
  //Ver.3.80
  NULL,
  NULL,
  NULL,
};


/*
 * The corresponding function is called one by one.
 */
int processformp240(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;
  int maxfuncnum_mp240 = 18;

  for(i=0; i<maxfuncnum_mp240; i++ ){
    if( mp240setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_mp240chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*mp240setstsfunctable[i])(p_s+i, p_mp240chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
