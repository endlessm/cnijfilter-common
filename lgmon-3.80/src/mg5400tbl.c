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
 * mg5400tbl.c 
 *
 * The conversion table for s300, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for mg5400 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS mg5400_dbs2busy[]={
  {"WU","B"},
  {"SL","B"},
  {"SD","B"},
  {"RS",""},
  {"CL","L"},
  {"CC","D"},
  {"TC","N"},
  {"TP","T"},
  {"DS","I"},
  {"NO",""},
  {"UK",""},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS mg5400_djs2job[]={
  {"PR","P"},
  {"LD","L"},
  {"EJ","F"},
  {"ID","I"},
  {"CC","S"},
  {"EC","P"},
  {"SC","S"},
  {"WP","W"},
  {"DM","D"},
  {"SD","D"},
  {"DC","W"},
  {"TW","P"},
  {"TC","W"},
  {"TO","D"},
  {"NO","I"},
  {"UK","I"},
  {ENDTAG,ENDTAG}
};

/*
 * The kind of cartridge with which the present printer is equipped.
 */
ST_BSCC2STS mg5400_chd2type[]={
  {"NO"," "},
  {"CL","^"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS mg5400_prname2exchange[]={
  {"MG5400","F"},
  {"IP7200","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS mg5400_cir2color[]={
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
ST_BSCC2STS mg5400_cil2inkchk[]={
//  {"ON","Y"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */
ST_BSCC2STS mg5400_lvr2posit[]={
  {"GAL,AT"," "},
  {"GAL,CW"," "},
  {ENDTAG,ENDTAG}
};

/*
 * Destination information.
 */
ST_BSCC2STS mg5400_hri2destination[]={
  {"0","0"},
  {"1","0"},
  {"2","0"},
  {"3","0"},
  {"4","0"},
  {"7","0"},
  {"8","0"},
  {"D","0"},
  {"E","0"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS mg5400_dws2warn[]={
  {"NO"," "},
  {"UK","?"},
  {"1500","T"},
  {"1570","F"},
  {"1900","P"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present operator call state.
 */
ST_BSCC2STS mg5400_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1001","r"},
  {"1002","r"},
  {"1007","p"},
  {"1008","Q"},
  {"1200","v"},
  {"1253","o"},
  {"1300","q"},
  {"1304","i"},
  {"1310","R"},
  {"1311","j"},
  {"1312","J"},
  {"1313","j"},
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
  {"1710","x"},
  {"1711","k"},
  {"1830","r"},
  {"1850","r"},
  {"1851","g"},
  {"1855","r"},
  {"1856","K"},
  {"1857","r"},
  {"1858","I"},
  {"2500","N"},
  {"2700","Z"},
  {"4100","r"},
  {"4101","L"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS mg5400_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5011","5011"},
  {"5012","5012"},
  {"5100","5100"},
  {"5101","5101"},
  {"5200","5200"},
  {"5400","5400"},
  {"5B00","5B00"},
  {"5B01","5B01"},
  {"5B10","5B10"},
  {"5B11","5B11"},
  {"5C00","5C00"},
  {"5C20","5C20"},
  {"6000","6000"},
  {"6500","6500"},
  {"6502","6502"},
  {"6800","6800"},
  {"6801","6801"},
  {"6900","6900"},
  {"6901","6901"},
  {"6902","6902"},
  {"6910","6910"},
  {"6911","6911"},
  {"6930","6930"},
  {"6931","6931"},
  {"6932","6932"},
  {"6933","6933"},
  {"6934","6934"},
  {"6935","6935"},
  {"6936","6936"},
  {"6937","6937"},
  {"6938","6938"},
  {"6940","6940"},
  {"6941","6941"},
  {"6942","6942"},
  {"6943","6943"},
  {"6944","6944"},
  {"6945","6945"},
  {"6946","6946"},
  {"6A81","6A81"},
  {"6B10","6B10"},
  {"6B20","6B20"},
  {"6C10","6C10"},
  {"B200","B200"},
  {"C000","C000"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS mg5400_dsc2service2[]={
  {"NO"," "},
  {"UK","?"},
  {"5011","M"},
  {"5012","M"},
  {"5100","R"},
  {"5101","M"},
  {"5200","M"},
  {"5400","M"},
  {"5B00","I"},
  {"5B01","J"},
  {"5B10","I"},
  {"5B11","J"},
  {"5C00","M"},
  {"5C20","M"},
  {"6000","M"},
  {"6500","M"},
  {"6502","M"},
  {"6800","M"},
  {"6801","M"},
  {"6900","M"},
  {"6901","M"},
  {"6902","M"},
  {"6910","M"},
  {"6911","M"},
  {"6930","M"},
  {"6931","M"},
  {"6932","M"},
  {"6933","M"},
  {"6934","M"},
  {"6935","M"},
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
  {"6A81","M"},
  {"6B10","M"},
  {"6B20","M"},
  {"6C10","M"},
  {"B200","V"},
  {"C000","M"},
  {ENDTAG,ENDTAG}
};


/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS mg5400_ctk2alert[]={
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
  {"FRM", "F"},
  {ENDTAG,ENDTAG}
};

//Ver.3.00
/*
 * Printer Destination information.
*/
ST_BSCC2STS mg5400_pdr2prnregion[]={
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
 * The function table for mg5400.
 */
static const FUNCOFMODELSETPROCESS
 mg5400setstsfunctable[] = {
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
  mg5400_setink,
  mg5400_setinkalert,
  NULL,
  NULL,
  //Ver.300
  NULL,
  //Ver.3.10
  NULL,
  //Ver.3.80
  NULL,
  NULL,
  mg5400_setinkifnumber,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_mg5400chgtbl[] = {
  NULL,
  mg5400_dbs2busy,
  mg5400_djs2job,
  mg5400_cil2inkchk,
  mg5400_chd2type,
  mg5400_prname2exchange,
  //Ver.2.70
  mg5400_hri2destination,
  mg5400_dws2warn,
  mg5400_doc2operate,
  mg5400_dsc2service,
  mg5400_cir2color,
  mg5400_ctk2alert,
  NULL,
  mg5400_lvr2posit,
  //Ver.300
  mg5400_pdr2prnregion,
  //Ver.3.10
  mg5400_dsc2service2,
  //Ver.3.80
  NULL,
  NULL,
  NULL,
};


/*
 * The corresponding function is called one by one.
 */
int processformg5400(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;
  //int maxfuncnum_mg5400 = 16;
  int maxfuncnum_mg5400 = 19;

  for(i=0; i<maxfuncnum_mg5400; i++ ){
    if( mg5400setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_mg5400chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*mg5400setstsfunctable[i])(p_s+i, p_mg5400chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
