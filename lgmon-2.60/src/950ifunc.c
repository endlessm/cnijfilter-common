/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2010
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
 * 950ifunc.c
 * A processing function group peculiar to a model.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"
#ifdef DEBUG
#include "lm.h"
#endif

static int pixus950i_setalert(bscc2sts_tbl *p_tbl, int color_num);

ST_BSCC2STS pixus950i_cir2fill[]={
  {"100", "100"},
  {"070", "070"},
  {"040", "040"},
  {"010", "010"},
  {"000", "000"},
  {ENDTAG, ENDTAG}
};

/*
 * The conversion function for CIL commands.
 * An alert domain is set from warning and an operator call.
 */
int pixus950i_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int ret;
  int i=0;
  int color_num=0;
  char *p_tok;

  if( (p_s->p_bsccsts == NULL) || (p_tbl->cartridge[0].type == UNEQUIP) || (p_tbl->cartridge[0].type =='?')	// 950i cartridge[0] not [1]
      || (p_tbl->warning[0]==NOITEM) || (p_tbl->operator_call[0]==NOITEM)
      || (p_bsccbuf+DWS)->p_bsccsts==NULL || (p_bsccbuf+DOC)->p_bsccsts==NULL ){
	return(OK);
  }
  p_tok=strtok(p_s->p_bsccsts, "=");
  ret=commonstssetprocess(p_tok, &(p_tbl->ink[i].color), p_ct);
  if(ret == BADITEM ){
	memset(&p_tbl->ink[0], NOITEM, p_s->size);
	return(OK);
  }
  color_num++;


  while( (p_tok=strtok(NULL, ",")) != NULL ){
	ret=commonstssetprocess(p_tok,p_tbl->ink[i].fill, &pixus950i_cir2fill[0]);
	if(ret == BADITEM ){
	  memset(&p_tbl->ink[0], NOITEM, p_s->size);
	  return(OK);
	}
	i++;
	if((p_tok=strtok(NULL, "=")) == NULL){
	  break;
	}
	ret=commonstssetprocess(p_tok,&(p_tbl->ink[i].color), p_ct);
	if(ret == BADITEM ){
	  memset(&p_tbl->ink[0], NOITEM, p_s->size);
	  return(OK);
	}
	color_num++;
  }
  ret=pixus950i_setalert(p_tbl, color_num);
  return(OK);
}


int pixus950i_setalert(bscc2sts_tbl *p_tbl, int color_num)
{
  int i,ret;

  for(i=0; i<color_num; i++){
	ret=com_warnoperatechk(p_tbl->warning, p_tbl->ink[i].color, sizeof(p_tbl->warning));
	if( ret == OCCUR ){
	  p_tbl->ink[i].alert = INKLOW;
	} else {
	  p_tbl->ink[i].alert = NOALERT;
	}
  }
  for(i=0; i<color_num; i++){
	ret=com_warnoperatechk(p_tbl->operator_call, p_tbl->ink[i].color, sizeof(p_tbl->operator_call));
	if( ret == OCCUR ){
	  p_tbl->ink[i].alert = INKOUT;
	}
  }
  return(OK);
}

/*
 * CD-R Gude alert convert.
 * .
 */
int pixus950i_setoperate(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int ret;
  int i=0;

  if( (p_s->p_bsccsts == NULL) ){
	return(OK);
  }

  ret = com_setoperate( p_s, p_ct, p_tbl);

  for(i=0;i<12;i++){
  	if( p_tbl->warning[i] == 'g' ) break;
  }
  if( i<12 ){
	for(i=0;i<12;i++){
  		if( p_tbl->operator_call[i] == 'O' ){
			p_tbl->operator_call[i] = 'g';
			break;
		}
  	}
  	
  }
  return(OK);
}


