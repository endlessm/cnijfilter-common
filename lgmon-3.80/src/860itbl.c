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
 * pixus860itbl.c 
 *
 * The conversion table for s300, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for pixus860i conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS pixus860i_dbs2busy[]={
  {"NO"," "},
  {"UK","?"},
  {"WU","S"},
  {"SL","E"},
  {"CL","L"},
  {"CC","C"},
  {"TP","T"},
  {"DS","I"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS pixus860i_djs2job[]={
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
ST_BSCC2STS pixus860i_chd2type[]={
  {"NO"," "},
  {"CL","I"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS pixus860i_prname2exchange[]={
  {"PIXUS860I","F"},
  {ENDTAG,ENDTAG}
};


/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS pixus860i_cil2inkchk[]={
  {"ON","Y"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */

ST_BSCC2STS pixus860i_lvr2posit[]={
  {"GAL,W"," "},
  {"GAL,N"," "},
  {ENDTAG,ENDTAG}
};


/*
 * Details of the present warning state.
 */
ST_BSCC2STS pixus860i_dws2warn[]={
  {"NO"," "},
  {"UK","?"},
  {"1513","C"},
  {"1512","M"},
  {"1511","Y"},
  {"1501","L"},
  {"1502","l"},
  {"1852","g"},
  {"1900","1900"},
  {"1910","1910"},
  {ENDTAG,ENDTAG}
};


/*
 * Details of the present operator call state.
 */
ST_BSCC2STS pixus860i_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1200","O"},
  {"1000","P"},
  {"1300","J"},
  {"1401","H"},
  {"1613","C"},
  {"1612","M"},
  {"1611","Y"},
  {"1601","L"},
  {"1602","l"},
  {"1403","R"},
  {"1405","R"},
  {"1700","I"},
  {"1851","G"},	//
  {"2001","U"},	// 860i 990i
  {"2500","A"},	// 860i 990i
  {ENDTAG,ENDTAG}
};


/*
 * Information on a service call.
 */
ST_BSCC2STS pixus860i_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5100","5100"},
  {"5200","5200"},
  {"5400","5400"},
  {"5B00","I"},
  {"5C00","5C00"},
  {"6800","6800"},
  {ENDTAG,ENDTAG}
};


/*
 * The function table for pixus860i.
 */
static const FUNCOFMODELSETPROCESS
 pixus860isetstsfunctable[] = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  pixus860i_setoperate,
  NULL,
  pixus860i_setink,
  NULL,
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_860ichgtbl[] = {
  NULL,
  pixus860i_dbs2busy,
  pixus860i_djs2job,
  pixus860i_cil2inkchk,
  pixus860i_chd2type,
  pixus860i_prname2exchange,
  pixus860i_lvr2posit,
  pixus860i_dws2warn,
  pixus860i_doc2operate,
  pixus860i_dsc2service,
  NULL,
  NULL,
  NULL,
};


/*
 * The corresponding function is called one by one.
 */
int processfor860i(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
    if( pixus860isetstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_860ichgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*pixus860isetstsfunctable[i])(p_s+i, p_860ichgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
