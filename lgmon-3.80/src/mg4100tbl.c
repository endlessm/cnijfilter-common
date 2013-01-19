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
 * mg4100tbl.c 
 *
 * The conversion table for mg4100, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for mg4100 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS mg4100_dbs2busy[]={
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
ST_BSCC2STS mg4100_djs2job[]={
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
  {"TW","P"},
  {"TC","W"},
  {"TO","D"},
  {"DC","W"},
  {"NO","I"},
  {"UK","I"},
  {ENDTAG,ENDTAG}
};

/*
 * The kind of cartridge with which the present printer is equipped.
 */
ST_BSCC2STS mg4100_chd2type[]={
  {"NO", " "},
  {"NS", "?"},
  {"BKX","]"},
  {"CLH","O"},
  {"CLM","V"},
  {"BKH","N"},
  {"BKM","U"},
  {"CL", "M"},
  {"BK", "L"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS mg4100_prname2exchange[]={
  {"E500","F"},
  {"MG2100","F"},
  {"MG3100","F"},
  {"MG4100","F"},
  {"E600","F"},
  {"MX370","F"},
  {"MX430","F"},
  {"MX510","F"},
  {"E510","F"},
  {"MG2200","F"},
  {"MG3200","F"},
  {"MG4200","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS mg4100_cir2color[]={
  {"BK","B"},
  {"CL","E"},
  {ENDTAG,ENDTAG}
};

/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS mg4100_cil2inkchk[]={
//  {"ON","Y"},
//  {"OF","N"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */
ST_BSCC2STS mg4100_lvr2posit[]={
  {"GAL,AT"," "},
  {"GAL,CW"," "},
  {ENDTAG,ENDTAG}
};

/*
 * Destination information.
 */
ST_BSCC2STS mg4100_hri2destination[]={
  {"10","G"}, /* must be 10 > 1 */
  {"0","0"},
  {"1","1"},
  {"2","2"},
  {"3","3"},
  {"4","4"},
  {"7","7"},
  {"8","8"},
  {"B","B"},
  {"D","D"},
  {"E","E"},
  {"F","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS mg4100_dws2warn[]={
  {"NO"," "},
  {"UK","?"},
  {"1499","t"},
  {"1500","T"},
  {"1900","P"},
//  {"1900","1900"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present operator call state.
 */
ST_BSCC2STS mg4100_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1003","p"},
  {"1200","v"},
  {"1202","P"},
  {"1250","o"},
  {"1300","q"},
  {"1303","n"},
  {"1304","i"},
  {"1310","R"},
  {"1401","H"},
  {"1403","r"},
  {"1485","h"},
  {"1486","S"},
  {"1487","s"},
  {"1682","e"},
  {"1684","e"},
  {"1686","w"},
  {"1687","T"},
  {"1688","C"},
  {"1702","x"},
  {"1703","k"},
  {"1704","x"},
  {"1705","k"},
  {"1712","x"},
  {"1713","k"},
  {"1714","x"},
  {"1715","k"},
  {"1890","Z"}, /* c--Z for Ver.3.80 */
  {"2001","U"},
  {"2002","U"},
  {"2700","Z"},
  {"2801","Z"},
  {"2802","Z"},
  {"2803","Z"},
  {"4100","r"},
  {ENDTAG,ENDTAG}
};


/*
 * Information on a service call.
 */
ST_BSCC2STS mg4100_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5011","5011"},
  {"5012","5012"},
  {"5040","5040"},
  {"5100","5100"},
  {"5200","5200"},
  {"5400","5400"},
  {"5B02","5B02"},
  {"5B03","5B03"},
  {"5B04","5B04"},
  {"5B05","5B05"},
  {"5B12","5B12"},
  {"5B13","5B13"},
  {"5B14","5B14"},
  {"5B15","5B15"},
  {"6000","6000"},
  {"6500","6500"},
  {"6800","6800"},
  {"6801","6801"},
  {"6900","6900"},
  {"6901","6901"},
  {"6902","6902"},
  {"6910","6910"},
  {"6911","6911"},
  {"6920","6920"},
  {"6921","6921"},
  {"6930","6930"},
  {"6931","6931"},
  {"6932","6932"},
  {"6933","6933"},
  {"6934","6934"},
  {"6935","6935"},
  {"6936","6936"},
  {"6937","6937"},
  {"6938","6938"},
  {"6939","6939"},
  {"693A","693A"},
  {"6940","6940"},
  {"6941","6941"},
  {"6942","6942"},
  {"6943","6943"},
  {"6944","6944"},
  {"6945","6945"},
  {"6946","6946"},
  {"6B10","6B10"},
  {"9000","9000"},
  {"B200","B200"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS mg4100_dsc2service2[]={
  {"NO"," "},
  {"UK","?"},
  {"5011","M"},
  {"5012","M"},
  {"5040","M"},
  {"5100","R"}, /* Ver.3.80 M-->R */
  {"5200","M"},
  {"5400","M"},
  {"5B02","I"},
  {"5B03","J"},
  {"5B04","I"},
  {"5B05","J"},
  {"5B12","I"},
  {"5B13","J"},
  {"5B14","I"},
  {"5B15","J"},
  {"6000","M"},
  {"6500","M"},
  {"6800","M"},
  {"6801","M"},
  {"6900","M"},
  {"6901","M"},
  {"6902","M"},
  {"6910","M"},
  {"6911","M"},
  {"6920","M"},
  {"6921","M"},
  {"6930","M"},
  {"6931","M"},
  {"6932","M"},
  {"6933","M"},
  {"6934","M"},
  {"6935","M"},
  {"6936","M"},
  {"6937","M"},
  {"6938","M"},
  {"6939","M"},
  {"693A","M"},
  {"6940","M"},
  {"6941","M"},
  {"6942","M"},
  {"6943","M"},
  {"6944","M"},
  {"6945","M"},
  {"6946","M"},
  {"6B10","M"},
  {"9000","M"},
  {"B200","V"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS mg4100_ctk2alert[]={
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
ST_BSCC2STS mg4100_hcf2warn[]={
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
ST_BSCC2STS mg4100_pdr2prnregion[]={
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
 * The function table for mg4100.
 */
static const FUNCOFMODELSETPROCESS
 mg4100setstsfunctable[] = {
  NULL,
  NULL,
  NULL,
  NULL,
  mg4100_setcartridgetype,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  mg4100_setink,
  mg4100_setinkalert,
  mg4100_setwarning,
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
ST_BSCC2STS *p_mg4100chgtbl[] = {
  NULL,
  mg4100_dbs2busy,
  mg4100_djs2job,
  mg4100_cil2inkchk,
  mg4100_chd2type,
  mg4100_prname2exchange,
  mg4100_hri2destination,
  mg4100_dws2warn,
  mg4100_doc2operate,
  mg4100_dsc2service,
  mg4100_cir2color,
  mg4100_ctk2alert,
  mg4100_hcf2warn,
  mg4100_lvr2posit,
  //Ver.300
  mg4100_pdr2prnregion,
  //Ver.3.10
  mg4100_dsc2service2,
  //Ver.3.80
  NULL,
  NULL,
  //mg4100_doc2operate2,
};


/*
 * The corresponding function is called one by one.
 */
int processformg4100(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;
  int maxfuncnum_mg4100 = 18;
  //int maxfuncnum_mg4100 = 16;

  for(i=0; i<maxfuncnum_mg4100; i++ ){
    if( mg4100setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_mg4100chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*mg4100setstsfunctable[i])(p_s+i, p_mg4100chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
