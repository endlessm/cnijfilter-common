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
 * ip1000tbl.c
 *
 * The conversion table for ip1000, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for ip1000 conversion table*/
/*
 * The present busy detailed status.
 */
ST_BSCC2STS ip1000_dbs2busy[]={
  {"NO"," "},
  {"UK","?"},
  {"WU","S"},
  {"SL","E"},
  {"CL","L"},
  {"CC","D"},
  {"TP","T"},
  {"TC","N"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS ip1000_djs2job[]={
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
ST_BSCC2STS ip1000_chd2type[]={
  {"NO"," "},
  {"CL","G"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS ip1000_prname2exchange[]={
  {"PIXMAIP1000","F"},
  {"PIXMAIP1500","F"},
  {ENDTAG,ENDTAG}
};


/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS ip1000_cil2inkchk[]={
  {"ON","Y"},
  {"OF","N"},
  {ENDTAG,ENDTAG}
};


/*
 * Position information between papers.
 */
ST_BSCC2STS ip1000_lvr2posit[]={
  {"GAL,W"," "},
  {"GAL,N"," "},
  {ENDTAG,ENDTAG}
};


/*
 * Details of the present warning state.
 */

ST_BSCC2STS ip1000_dws2warn[]={
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
ST_BSCC2STS ip1000_doc2operate[]={
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
ST_BSCC2STS ip1000_dsc2service[]={
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
 * The function table for ip1000.
 */
static const FUNCOFMODELSETPROCESS
ip1000setstsfunctable[] = {
  NULL,
  NULL,
  NULL,
  NULL,
  ip1000_setcartridgetype,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  ip1000_setink,
  NULL,
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_ip1000chgtbl[] = {
  NULL,
  ip1000_dbs2busy,
  ip1000_djs2job,
  ip1000_cil2inkchk,
  ip1000_chd2type,
  ip1000_prname2exchange,
  ip1000_lvr2posit,
  ip1000_dws2warn,
  ip1000_doc2operate,
  ip1000_dsc2service,
  NULL,
  NULL,
  NULL,
};


/*
 * The corresponding function is called one by one.
 */
int processforip1000(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
	if( ip1000setstsfunctable[i] == NULL){
	  ret = selectcommonfunc(p_s+i, p_ip1000chgtbl[i], p_tbl, i);
	  if(ret != OK){
	    break;
	  }
	} else {
	  ret = (*ip1000setstsfunctable[i])(p_s+i, p_ip1000chgtbl[i], p_tbl, p_bsccbuf);
	  if(ret != OK){
	    break;
	  }
	}
  }
  return(ret);
}
