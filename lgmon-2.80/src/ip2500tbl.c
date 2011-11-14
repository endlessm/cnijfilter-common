/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2007
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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
ST_BSCC2STS ip2500_djs2job[]={
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
  {"1000","P"},
  {"1200","O"},
  {"1300","J"},
  {"1401","b"},
//  {"1403","R"},
//  {"1405","R"},
  {"1485","b"},
//  {"1600","B"}, 06 not support
  {"1682","b"},
  {"1684","b"},
//  {"1685","W"}, 06 not support
  {"1686","w"},
  {"1687","T"}, //06 1660 --> 1687
  {"1688","C"}, 
  {"1700","I"},
  {"1701","I"},
  {"1710","I"},
  {"1711","I"},
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
  {"BK", "Z"},
  {"CL", "Z"},
  {"AL", "Z"},
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
