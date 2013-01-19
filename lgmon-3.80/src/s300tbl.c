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
 * s300tbl.c
 *
 * The conversion table for s300, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for s300 conversion table*/
/*
 * The present busy detailed status.
 */
ST_BSCC2STS s300_dbs2busy[]={
  {"NO"," "},
  {"UK","?"},
  {"WU","S"},
  {"SL","E"},
  {"CL","L"},
  {"CC","C"},
  {"TP","T"},
  {"TC","N"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS s300_djs2job[]={
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
ST_BSCC2STS s300_chd2type[]={
  {"NO"," "},
  {"CL","G"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS s300_prname2exchange[]={
  {"BJS300","F"},
  {ENDTAG,ENDTAG}
};


/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS s300_cil2inkchk[]={
  {"ON","Y"},
  {"OF","N"},
  {ENDTAG,ENDTAG}
};


/*
 * Position information between papers.
 */
ST_BSCC2STS s300_lvr2posit[]={
  {"GAL,W","R"},
  {"GAL,N","L"},
  {ENDTAG,ENDTAG}
};


/*
 * Details of the present warning state.
 */

ST_BSCC2STS s300_dws2warn[]={
  {"NO"," "},
  {"1561"," "},
  {"1562"," "},
  {"UK","?"},
  {"1501","B"},
  {"1510","E"},
  {"1541","b"},
  {"1542","e"},
  {"1900","1900"},
  {"1910","1910"},
  {ENDTAG,ENDTAG}
};


/*
 * Details of the present operator call state.
 */
ST_BSCC2STS s300_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1200","O"},
  {"1000","P"},
  {"1300","J"},
  {"1401","H"},
  {"1403","R"},
  {"1405","R"},
  {"1700","I"},
  {"1710","I"},		/* i250/i255*/
  {"1660","T"},		/* i250/i255*/
  {ENDTAG,ENDTAG}
};


/*
 * Information on a service call.
 */
ST_BSCC2STS s300_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5100","5100"},
  {"5200","5200"},
  {"5400","5400"},
  {"5B00","I"},
  {"5C00","5C00"},
  {"6800","6800"},
  {"6810","6810"},
  {ENDTAG,ENDTAG}
};




/*
 * The function table for s300.
 */
static const FUNCOFMODELSETPROCESS
s300setstsfunctable[] = {
  NULL,
  NULL,
  NULL,
  NULL,
  s300_setcartridgetype,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  s300_setink,
  NULL,
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_s300chgtbl[] = {
  NULL,
  s300_dbs2busy,
  s300_djs2job,
  s300_cil2inkchk,
  s300_chd2type,
  s300_prname2exchange,
  s300_lvr2posit,
  s300_dws2warn,
  s300_doc2operate,
  s300_dsc2service,
  NULL,
  NULL,
  NULL,
};


/*
 * The corresponding function is called one by one.
 */
int processfors300(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
	if( s300setstsfunctable[i] == NULL){
	  ret = selectcommonfunc(p_s+i, p_s300chgtbl[i], p_tbl, i);
	  if(ret != OK){
	    break;
	  }
	} else {
	  ret = (*s300setstsfunctable[i])(p_s+i, p_s300chgtbl[i], p_tbl, p_bsccbuf);
	  if(ret != OK){
	    break;
	  }
	}
  }
  return(ret);
}
