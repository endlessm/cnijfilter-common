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
 * ip90tbl.c
 *
 * The conversion table for ip90, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for ip90 conversion table*/
/*
 * The present busy detailed status.
 */
ST_BSCC2STS ip90_dbs2busy[]={
  {"NO"," "},
  {"UK","?"},
  {"WU","S"},
  {"SL","E"},
  {"CL","L"},
  {"CC","D"},
  {"TP","T"},
  {"DS","I"},
  {"TC","N"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS ip90_djs2job[]={
  {"NO"," "},
  {"UK","?"},
  {"ID","I"},
  {"PR","P"},
  {"LD","L"},
  {"EJ","F"},
  {"CC","C"},
  {ENDTAG,ENDTAG}
};


/*
 * The kind of cartridge with which the present printer is equipped.
 */
ST_BSCC2STS ip90_chd2type[]={
  {"NO"," "},
  {"CL","W"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS ip90_prname2exchange[]={
  {"IP90","F"},
  {ENDTAG,ENDTAG}
};


/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS ip90_cil2inkchk[]={
  {"ON","Y"},
  {"OF","N"},
  {ENDTAG,ENDTAG}
};


/*
 * Position information between papers.
 */
ST_BSCC2STS ip90_lvr2posit[]={
  {"IPG,W"," "},
  {"IPG,N"," "},
  {"IPG,U"," "},
  {ENDTAG,ENDTAG}
};


/*
 * Details of the present warning state.
 */

ST_BSCC2STS ip90_dws2warn[]={
  {"NO"," "},
  {"1561","#"},
  {"1562","#"},
  {"UK","?"},
  {"1501","b"},
  {"1510","e"},
  {"1541","U"},
  {"1542","u"},
  {"1800","S"},
  {"1900","1900"},
  {"1910","1910"},
  {ENDTAG,ENDTAG}
};


/*
 * Details of the present operator call state.
 */
ST_BSCC2STS ip90_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1401","H"},
  {"1000","P"},
  {"1300","J"},
  {"1200","v"},
  {"1810","D"},
  {"1700","I"},
  {"1403","R"},
  {"1405","R"},
  {"1661","M"},
  {"1662","m"},
//  {"1660","T"},//delete Ver.2.70 beta2
  {"2001","U"},
  {ENDTAG,ENDTAG}
};


/*
 * Information on a service call.
 */
ST_BSCC2STS ip90_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5100","5100"},
  {"5200","5200"},
  {"5400","5400"},
  {"5B00","I"},
  {"5C00","5C00"},
  {"6000","6000"},//add Ver.2.70 beta2
  {"6800","6800"},
  {"9000","9000"},//add Ver.2.70 beta2
  {ENDTAG,ENDTAG}
};




/*
 * The function table for ip1000.
 */
static const FUNCOFMODELSETPROCESS
ip90setstsfunctable[] = {
  NULL,
  NULL,
  NULL,
  NULL,
  ip90_setcartridgetype,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  ip90_setink,
  NULL,
  NULL,
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_ip90chgtbl[] = {
  NULL,
  ip90_dbs2busy,
  ip90_djs2job,
  ip90_cil2inkchk,
  ip90_chd2type,
  ip90_prname2exchange,
  NULL,
  ip90_dws2warn,
  ip90_doc2operate,
  ip90_dsc2service,
  NULL,
  NULL,
  NULL,
  ip90_lvr2posit,
};


/*
 * The corresponding function is called one by one.
 */
int processforip90(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
	if( ip90setstsfunctable[i] == NULL){
	  ret = selectcommonfunc(p_s+i, p_ip90chgtbl[i], p_tbl, i);
	  if(ret != OK){
	    break;
	  }
	} else {
	  ret = (*ip90setstsfunctable[i])(p_s+i, p_ip90chgtbl[i], p_tbl, p_bsccbuf);
	  if(ret != OK){
	    break;
	  }
	}
  }
  return(ret);
}
