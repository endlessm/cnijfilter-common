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
 * ip1000func.c
 *
 * A processing function group peculiar to a model.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

static int ip1000_inklowlevel1chk(char color, char *p_call);

/*
 * The conversion function for CHD commands.
 * The status set changes with existence of an ink check.
 */
int ip1000_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int ret;
//  int i;
//  char *p_tok;

  if( p_s->p_bsccsts == NULL ){
	return(OK);
  }

  ret=commonstssetprocess(p_s->p_bsccsts, &(p_tbl->cartridge[0].type), p_ct);
  if(ret == BADITEM ){
	memset(&(p_tbl->cartridge[0].type), NOITEM, sizeof(p_tbl->cartridge[0].type));
	return(OK);
  }
  if((p_tbl->ink_check=='N') && (p_tbl->cartridge[0].type!=SPACE)){
	p_tbl->cartridge[0].type='F';
  }

  return(OK);
}

/*
 * Ink information is set from warning and an operator call.
 */
int ip1000_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int ret;
  int i=0;
//  int color_num=0;
  char ip1000color[]="BE";
  char *p_temp;

  if( (p_tbl->cartridge[0].type)==UNEQUIP || (p_tbl->cartridge[0].type=='?')
      || (p_tbl->warning[0]==NOITEM) || (p_tbl->operator_call[0]==NOITEM) || (p_bsccbuf+DWS)->p_bsccsts==NULL ){
	return(OK);
  }

  for(i=0; i<MAXip1000COLORNUM; i++){
	p_tbl->ink[i].color=ip1000color[i];
	ret=com_warnoperatechk(p_tbl->warning, p_tbl->ink[i].color, sizeof(p_tbl->warning));
	if(ret == OCCUR){
	  strncpy(p_tbl->ink[i].fill, TENPER, sizeof(p_tbl->ink[i].fill));
	  p_tbl->ink[i].alert=INKLOW;
	} else {
	  p_temp=(char *)malloc( strlen( (p_bsccbuf+DWS)->p_bsccsts ) +1 );
	  if(p_temp == NULL){
	    return(ERR_MEMORY);
	  }
	  strncpy(p_temp, (p_bsccbuf+DWS)->p_bsccsts, strlen((p_bsccbuf+DWS)->p_bsccsts));
	  ret=ip1000_inklowlevel1chk(p_tbl->ink[i].color, p_temp);
	  free(p_temp);
	  if(ret == OCCUR){
		strncpy(p_tbl->ink[i].fill, HARF, sizeof(p_tbl->ink[i].fill));
	  } else {
		strncpy(p_tbl->ink[i].fill, FULL, sizeof(p_tbl->ink[i].fill));
	  }
	  p_tbl->ink[i].alert=NOALERT;
	}
	ret=com_warnoperatechk(p_tbl->warning, tolower(p_tbl->ink[i].color), sizeof(p_tbl->warning));
	if(ret == OCCUR){
	  strncpy(p_tbl->ink[i].fill, ZEROPER, sizeof(p_tbl->ink[i].fill));
	  p_tbl->ink[i].alert=INKUNKNOWN;
	}
  }
  return(OK);
}

/*
 * The ink low warning level 1 is checked. Warning peculiar to ip1000.
 */
int ip1000_inklowlevel1chk(char color, char *p_call)
{

  char *p_tok;
  char level1[5];

  memset (level1, 0, 5);
  
  if(p_call == NULL){
	return(OK);
  }
  if(color == 'B'){
	strncpy(level1, "1561", strlen("1561"));
  } else {
	strncpy(level1, "1562", strlen("1562"));
  }

  p_tok=strtok(p_call, ",");
  if( strcmp(level1, p_tok)==0 ){
	return(OCCUR);
  }
  while( (p_tok = strtok(NULL, ",")) != NULL){
	if( strcmp(level1, p_tok)==0 ){
	  return(OCCUR);
	}
  }
  return(OK);
}
