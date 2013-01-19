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
 * ip90func.c
 *
 * A processing function group peculiar to a model.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

static int ip90_inklowlevel1chk(char color, char *p_call);
static int ip90_inkunknownchk(char *p_call, int buf_length);
static int ip90_inkunsetchk(char *p_call, int buf_length);
static void ip90_maskwarning(char *p_call, int pcall_length, char *p_warning, int warning_length);
static void ip90_maskwarning2(char *p_call, int pcall_length, char *p_warning, int warning_length);

/*
 * The conversion function for CHD commands.
 * The status set changes with existence of an ink check.
 */
int ip90_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
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
	p_tbl->cartridge[0].type='X';
	//p_tbl->cartridge[0].type='F';
  }
  
  return(OK);
}

/*
 * Ink information is set from warning and an operator call.
 */
int ip90_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int ret;
  int i=0;
//  int color_num=0;
  char ip90color[]="be";
//  char ip90color[]="BE";
  char *p_temp;

  //if no cartridge , warning mask
  if( (p_tbl->cartridge[0].type)==UNEQUIP ){
	  ip90_maskwarning2(p_tbl->operator_call, sizeof(p_tbl->operator_call), p_tbl->warning, sizeof(p_tbl->warning));
  }

  if( (p_tbl->cartridge[0].type)==UNEQUIP || (p_tbl->cartridge[0].type=='?')
      || (p_tbl->warning[0]==NOITEM) || (p_tbl->operator_call[0]==NOITEM) || (p_bsccbuf+DWS)->p_bsccsts==NULL ){
	return(OK);
  }

  //2.00.01.02
  strncpy(p_tbl->ink[0].fill, FULL, sizeof(p_tbl->ink[0].fill));
  strncpy(p_tbl->ink[1].fill, FULL, sizeof(p_tbl->ink[1].fill));

  for(i=0; i<MAXip90COLORNUM; i++){
	p_tbl->ink[i].color=ip90color[i];
	ret=com_warnoperatechk(p_tbl->warning, p_tbl->ink[i].color, sizeof(p_tbl->warning));
	if(ret == OCCUR){
	  strncpy(p_tbl->ink[i].fill, ZEROPER, sizeof(p_tbl->ink[i].fill));
	  p_tbl->ink[i].alert=INKLOW;
	} else {
	  p_temp=(char *)malloc( strlen( (p_bsccbuf+DWS)->p_bsccsts ) +1 );
	  if(p_temp == NULL){
	    return(ERR_MEMORY);
	  }
	  strncpy(p_temp, (p_bsccbuf+DWS)->p_bsccsts, strlen((p_bsccbuf+DWS)->p_bsccsts));
	  ret=ip90_inklowlevel1chk(p_tbl->ink[i].color, p_temp);
	  free(p_temp);

	  // 2.00.01.02 chage DWS:1561,1510;
	  // warning = " e" ---> warning = "*e" ip90tbl.c
	  if(ret == OCCUR){
		strncpy(p_tbl->ink[i].fill, HARF, sizeof(p_tbl->ink[i].fill));
	  }
	  //if(ret == OCCUR){
	  //	strncpy(p_tbl->ink[i].fill, HARF, sizeof(p_tbl->ink[i].fill));
	  //} else {
	  //	strncpy(p_tbl->ink[i].fill, FULL, sizeof(p_tbl->ink[i].fill));
	  //}
	  p_tbl->ink[i].alert=NOALERT;
	}
	// 2.00.01.02 not tolower be -> be
	ret=com_warnoperatechk(p_tbl->warning, p_tbl->ink[i].color, sizeof(p_tbl->warning));
	//ret=com_warnoperatechk(p_tbl->warning, tolower(p_tbl->ink[i].color), sizeof(p_tbl->warning));
	if(ret == OCCUR){
	  strncpy(p_tbl->ink[i].fill, ZEROPER, sizeof(p_tbl->ink[i].fill));
	  p_tbl->ink[i].alert=INKLOW;
	}
    //for 'U' or 'u' --> UNKNOWNPER:UUU, INKUNKNOWN
	ret=ip90_inkunknownchk(p_tbl->warning, sizeof(p_tbl->warning));
	if(ret == 1){
	  strncpy(p_tbl->ink[0].fill, UNKNOWNPER, sizeof(p_tbl->ink[0].fill));
	  p_tbl->ink[0].alert=INKUNKNOWN;
	}
	else if(ret == 2){
	  strncpy(p_tbl->ink[1].fill, UNKNOWNPER, sizeof(p_tbl->ink[1].fill));
	  p_tbl->ink[1].alert=INKUNKNOWN;
	}
	else if(ret == 3){
	  strncpy(p_tbl->ink[0].fill, UNKNOWNPER, sizeof(p_tbl->ink[0].fill));
	  strncpy(p_tbl->ink[1].fill, UNKNOWNPER, sizeof(p_tbl->ink[1].fill));
	  p_tbl->ink[0].alert=INKUNKNOWN;
	  p_tbl->ink[1].alert=INKUNKNOWN;
	 }
    //for 'M' or 'm' --> UNSETTANK:NNN
	ret=ip90_inkunsetchk(p_tbl->operator_call, sizeof(p_tbl->operator_call));
	if(ret == 1){
	  strncpy(p_tbl->ink[0].fill, UNSETTANK, sizeof(p_tbl->ink[0].fill));
	  p_tbl->ink[0].alert=' ';
	}
	else if(ret == 2){
	  strncpy(p_tbl->ink[1].fill, UNSETTANK, sizeof(p_tbl->ink[1].fill));
	  p_tbl->ink[1].alert=' ';
	}
	else if(ret == 3){
	  strncpy(p_tbl->ink[0].fill, UNSETTANK, sizeof(p_tbl->ink[0].fill));
	  strncpy(p_tbl->ink[1].fill, UNSETTANK, sizeof(p_tbl->ink[1].fill));
	  p_tbl->ink[0].alert=' ';
	  p_tbl->ink[1].alert=' ';
	 }
  }
  //warning mask
  ip90_maskwarning(p_tbl->operator_call, sizeof(p_tbl->operator_call), p_tbl->warning, sizeof(p_tbl->warning));

  return(OK);
}

/*
 * The ink low warning level 1 is checked. Warning peculiar to ip90.
 */
int ip90_inklowlevel1chk(char color, char *p_call)
{

  char *p_tok;
  char level1[5];

  memset (level1, 0, 5);
  
  if(p_call == NULL){
	return(OK);
  }
  if(color == 'b'){
//  if(color == 'B'){
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

/*
 * The ink remain unknown is checked. Warning peculiar to ip90.
 */

int ip90_inkunknownchk(char *p_call, int buf_length)
{
  int i;
  int flag = 0;

  for(i=0; i < buf_length; i++){
	if( (p_call[i] == 'U') )
	  flag += 1;
	else if( (p_call[i] == 'u') )
	  flag += 2;
  }
  
  if( flag != 0 )
  	return(flag);

  else
  return(OK);

}

/*
 * The ink set is checked.
 */

int ip90_inkunsetchk(char *p_call, int buf_length)
{
  int i;
  int flag = 0;
  
  for(i=0; i < buf_length; i++){
	if( (p_call[i] == 'M') )
	  flag += 1;
	else if( (p_call[i] == 'm') )
	  flag += 2;
  }
  
  if( flag != 0 )
  	return(flag);

  else
  	return(OK);
}

/*
 * warning delete 
 *
 * 1. NoTank_Bk & InkLow_Warning_Bk -> p_warning[i] = '*'
 * 2. NoTank_Cl & InkLow_Warning_Cl -> p_warning[i] = '*'
 * 3. NoBattery & BatteryLow_Warning -> p_warning[i] = '*'
 */

void ip90_maskwarning(char *p_call, int pcall_length, char *p_warning, int warning_length)
{
  int i;
  int inkunsetbk_flag = 0;
  int inkunsetcl_flag = 0;
  int batteryno_flag = 0;

  for( i=0; i < pcall_length; i++ ){
	if( p_call[i] == 'M' )
	  inkunsetbk_flag = 1;
	if( p_call[i] == 'm' )
	  inkunsetcl_flag = 1;
	if( p_call[i] == 'D' )
	  batteryno_flag = 1;
  }

  for( i=0; i < warning_length; i++ ){
	if( ( p_warning[i] == 'b' && inkunsetbk_flag == 1 )
	 || ( p_warning[i] == 'e' && inkunsetcl_flag == 1 )
	 || ( p_warning[i] == 'S' && batteryno_flag  == 1 ))
	  p_warning[i] = '#';
  }

  return;
}

void ip90_maskwarning2(char *p_call, int pcall_length, char *p_warning, int warning_length)
{
  int i;

  for( i=0; i < warning_length; i++ ){
	if( ( p_warning[i] == 'b' )
	 || ( p_warning[i] == 'e' )
	 || ( p_warning[i] == 'U' )
	 || ( p_warning[i] == 'u' ) )
	  p_warning[i] = '#';
  }

  return;
}
