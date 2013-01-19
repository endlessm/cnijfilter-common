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
 * 550ifunc.c 
 *
 * A processing function group peculiar to a model.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"


/*
 * Ink information is set from warning and an operator call.
 */
int pixus550i_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int ret;
  int i=0;
//  int color_num=0;
  char pixus550icolor[]="CMYL";
//  char *p_tok;

  if( (p_tbl->cartridge[0].type == UNEQUIP)|| (p_tbl->cartridge[0].type == '?')
      || (p_tbl->warning[0]==NOITEM) || (p_tbl->operator_call[0]==NOITEM)
      || (p_bsccbuf+DWS)->p_bsccsts==NULL || (p_bsccbuf+DOC)->p_bsccsts==NULL ){
	return(OK);
  }

  for(i=0; i<MAX550iCOLORNUM; i++){
	p_tbl->ink[i].color=pixus550icolor[i];
	ret=com_warnoperatechk(p_tbl->warning, p_tbl->ink[i].color, sizeof(p_tbl->warning));
	if(ret == OCCUR){
	  strncpy(p_tbl->ink[i].fill, TENPER, sizeof(p_tbl->ink[i].fill));
	  p_tbl->ink[i].alert=INKLOW;
	} else {
	  strncpy(p_tbl->ink[i].fill, FULL, sizeof(p_tbl->ink[i].fill));
	  p_tbl->ink[i].alert=NOALERT;
	}

	p_tbl->ink[i].color=pixus550icolor[i];
	ret=com_warnoperatechk(p_tbl->operator_call, p_tbl->ink[i].color, sizeof(p_tbl->operator_call));
	if(ret == OCCUR){
	  strncpy(p_tbl->ink[i].fill, ZEROPER, sizeof(p_tbl->ink[i].fill));
	  p_tbl->ink[i].alert=INKOUT;
	}
  }
  return(OK);
}
