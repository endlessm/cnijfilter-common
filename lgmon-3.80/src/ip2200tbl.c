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
 * ip2200tbl.c 
 *
 * The conversion table for s300, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for ip2200 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS ip2200_dbs2busy[]={
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
ST_BSCC2STS ip2200_djs2job[]={
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
ST_BSCC2STS ip2200_chd2type[]={
  {"NO"," "},
  {"NS","?"},
  {"BKH","N"},
  {"CLH","O"},
  {"BK","L"},
  {"CL","M"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS ip2200_prname2exchange[]={
  {"IP2200","F"},
  {ENDTAG,ENDTAG}
};

/*
 * Ink residual quantity information.
 * color
 */
ST_BSCC2STS ip2200_cir2color[]={
  {"BK","B"},
  {"CL","E"},
  {ENDTAG,ENDTAG}
};

/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS ip2200_cil2inkchk[]={
  {"ON","Y"},
  {"OF","N"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */
ST_BSCC2STS ip2200_lvr2posit[]={
  {"IPG,W"," "},
  {"IPG,N"," "},
  {"IPG,U"," "},
  {ENDTAG,ENDTAG}
};

/*
 * Destination information.
 */
ST_BSCC2STS ip2200_hri2destination[]={
  {"JP","J"},
  {"OTH","O"},
  {ENDTAG,ENDTAG}
};

/*
 * Details of the present warning state.
 */
ST_BSCC2STS ip2200_dws2warn[]={
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
ST_BSCC2STS ip2200_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1000","P"},
  {"1200","O"},
  {"1300","J"},
  {"1401","b"},
  {"1405","R"},
  {"1485","b"},
  {"1600","B"},
  {"1660","T"},
  {"1682","b"},
  {"1684","b"},
  {"1685","W"},
  {"1686","w"},
  {"1700","I"},
  {"1710","I"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a service call.
 */
ST_BSCC2STS ip2200_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5100","5100"},
  {"5201","5201"},
  {"5202","5202"},
  {"5600","5600"},
  {"5B00","I"},
  {"5B10","I"},
  {"6000","6000"},
  {"6800","6800"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of ink tank.
 */
ST_BSCC2STS ip2200_ctk2alert[]={
  {"NO",  "E"},
  {"NS",  "E"},
//{"SET", ""},
//{"SETZ",""},
  {"HRD","E"},
  {"IUK1","R"},
  {"IUK2","R"},
  {"REG", "E"},
  {"IO",  "I"},
  {ENDTAG,ENDTAG}
};

/*
 * Information on a HCF.
 */
ST_BSCC2STS ip2200_hcf2warn[]={
  {"NO", " "},
  {"BK", "Z"},
  {"CL", "Z"},
  {"AL", "Z"},
  {ENDTAG,ENDTAG}
};

/*
 * The function table for ip2200.
 */
static const FUNCOFMODELSETPROCESS
 ip2200setstsfunctable[] = {
  NULL,
  NULL,
  NULL,
  NULL,
  ip2200_setcartridgetype,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  ip2200_setink,
  ip2200_setinkalert,
  ip2200_setwarning,
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_ip2200chgtbl[] = {
  NULL,
  ip2200_dbs2busy,
  ip2200_djs2job,
  ip2200_cil2inkchk,
  ip2200_chd2type,
  ip2200_prname2exchange,
  ip2200_hri2destination,
  ip2200_dws2warn,
  ip2200_doc2operate,
  ip2200_dsc2service,
  ip2200_cir2color,
  ip2200_ctk2alert,
  ip2200_hcf2warn,
  ip2200_lvr2posit,
};


/*
 * The corresponding function is called one by one.
 */
int processforip2200(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
    if( ip2200setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_ip2200chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*ip2200setstsfunctable[i])(p_s+i, p_ip2200chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
