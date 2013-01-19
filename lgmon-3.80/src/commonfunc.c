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
 * commonfunc.c
 *
 * The common module group used in a bscc2sts library.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/*
 * The function table which it is common and is used.
 */
static const FUNCOFSETPROCESS
commonsetstsfunctable[] = {
  com_setbasests,
  com_setstdsts,
  com_setstdsts,
  com_setstdsts,
  com_setcartridgetype,
  com_setexchange,
  com_setstdsts,
  com_setwarn,
  com_setoperate,
  com_setstdsts,
  NULL,
  NULL,
  NULL,
  com_setstdsts, //for Ver.2.70
  com_setstdsts, //for Ver.3.00
  com_setstdsts, //for Ver.3.10
  com_setoperatecode,     /* for Ver.3.80 */
  com_setservicecallcode, /* for Ver.3.80 */
  NULL, /* for Ver.3.80 */
};

int selectcommonfunc(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl,  int f_num)
{
  int ret=OK;

  if(commonsetstsfunctable[f_num] != NULL){
    ret = (*commonsetstsfunctable[f_num])(p_s, p_ct, p_tbl);
  }
  return(ret);
}

/*
 * A common status set function.
 * return :   
 *        Usual             --The length of status written in the table.
 *        no conversion item--BADITEM macros.
 */
int commonstssetprocess(char *p_bsccsts, char *p_storetbl, ST_BSCC2STS *p_chgtbl)
{
  int i;
  int length;

  /* When Relevance bscc is found, it stores in a table. */
  for(i=0; (p_chgtbl+i)->bscc!=ENDTAG; i++){
	if( strncmp(p_bsccsts, (p_chgtbl+i)->bscc, strlen((p_chgtbl+i)->bscc)) == 0 ){
	  length=strlen((p_chgtbl+i)->sts);
	  strncpy(p_storetbl, (p_chgtbl+i)->sts, length);
	  return(length);
	}
  }
  /* When there is no corresponding item. */
  return(BADITEM);
}


/*
 * The conversion function for BST commands.
 */
int com_setbasests(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl)
{
  int i;

  if( p_s->p_bsccsts == NULL ){
	return(ERR_BSTNON);
  }
  for(i=0; i<strlen(p_s->p_bsccsts); i++){
    if(*(p_s->p_bsccsts+i) > 'F'){
      memset(p_s->p_storetbl, NOITEM, p_s->size);
      return(OK);
    }
  }
  strncpy(p_s->p_storetbl, p_s->p_bsccsts, p_s->size);
  return(OK);
}


/*
 * The standard function for BSCC command conversion.
 * (DBS/DJS/CIL/LVR/DSC)
 */
int com_setstdsts(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl)
{
  int ret;

  if( p_s->p_bsccsts == NULL ){
	return(OK);
  }

  ret=commonstssetprocess(p_s->p_bsccsts, p_s->p_storetbl, p_ct);
  if(ret == BADITEM){
	memset(p_s->p_storetbl, NOITEM, p_s->size);
  }
  return(OK);
}


/*
 * The conversion function for CHD commands.
 */
int com_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl)
{
  int ret;
  int i;
  char *p_tok;
  char *p_temp;

  if( p_s->p_bsccsts == NULL ){
	return(OK);
  }
  p_temp=(char *)malloc( strlen(p_s->p_bsccsts) + 1 );
  if(p_temp == NULL){
    return(ERR_MEMORY);
  }
  memset (p_temp, 0, strlen(p_s->p_bsccsts) + 1);
  strncpy(p_temp, p_s->p_bsccsts, strlen(p_s->p_bsccsts));
  p_tok=strtok(p_temp,",");

  for(i=0; (i<MAXCARTRIDGENUM) && (p_tok!=NULL); i++){
    ret=commonstssetprocess(p_tok,&(p_tbl->cartridge[i].type), p_ct);
    if(ret == BADITEM ){
      memset(&(p_tbl->cartridge[i].type), NOITEM, sizeof(p_tbl->cartridge[i].type));
    }
    p_tok=strtok(NULL,",");
  }
  free(p_temp);
  return(OK);
}


/*
 * The conversion function for user exchange of a cartridge.
 */
int com_setexchange(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl)
{
  int ret;
  int i;
  char type;

  for(i=0; i<MAXCARTRIDGENUM; i++){
	type=p_tbl->cartridge[i].type;
	if( (type != SPACE)  && (type != INIT) && (type != '?') && (type != NOITEM) ){
	  ret=commonstssetprocess(p_s->p_bsccsts, &(p_tbl->cartridge[i].exchange), p_ct);
	  if(ret==BADITEM){
		memset(&(p_tbl->cartridge[i].exchange), NOITEM, sizeof(p_tbl->cartridge[i].exchange));
	  }
	}
  }
  return(OK);
}


/*
 * The conversion function for DWS commands.
 */
int com_setwarn(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl)
{
  int ret;
  int length=0;
  char *p_temp;
  char *p_tok;

  if( p_s->p_bsccsts == NULL ){
	return(OK);
  }
  p_temp=(char *)malloc( strlen(p_s->p_bsccsts)+1 );
  if(p_temp == NULL){
    return(ERR_MEMORY);
  }
  memset (p_temp, 0, strlen(p_s->p_bsccsts)+1);
  strncpy(p_temp, p_s->p_bsccsts, strlen(p_s->p_bsccsts));
  p_tok=strtok(p_temp, "," );
  ret=commonstssetprocess(p_tok, p_s->p_storetbl, p_ct);
  if(ret == BADITEM ){
	memset(p_s->p_storetbl, NOITEM, p_s->size);
	free(p_temp);
	return(OK);
  }
  length+=ret;


  while( (p_tok = strtok(NULL,",")) != NULL ){
	ret=commonstssetprocess(p_tok, (p_s->p_storetbl)+length, p_ct);
	if(ret == BADITEM ){
	  memset(p_s->p_storetbl, NOITEM, p_s->size);
	  free(p_temp);
	  return(OK);
	}
	length+=ret;
  }
  free(p_temp);
  return(OK);
}

/*
 * The conversion function for DOC commands.
 */
int com_setoperate(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl)
{
  int ret;
  int length=0;
  int parameter_num=1;
  char *p_tok;
  char *p_temp;

  if( p_s->p_bsccsts == NULL ){
	return(OK);
  }
  p_temp=(char *)malloc( strlen(p_s->p_bsccsts) + 1 );
  if(p_temp == NULL){
    return(ERR_MEMORY);
  }
  memset (p_temp, 0, strlen(p_s->p_bsccsts) + 1);
  strncpy(p_temp, p_s->p_bsccsts, strlen(p_s->p_bsccsts));
  p_tok=strtok(p_temp, "," );
  parameter_num++;

  while( (p_tok = strtok(NULL,",")) != NULL ){
	parameter_num++;
	//for DOC multi Ver.2.70 DOC:4,01,1000,/,4,01,1200; 4*X appear
	if((parameter_num%4) == 0){
	//if(parameter_num >= OPERATE){
	//if(parameter_num == OPERATE){
	  ret=commonstssetprocess(p_tok, (p_s->p_storetbl)+length, p_ct);
	  if(ret == BADITEM ){
		strncpy(p_s->p_storetbl, p_tok, strlen(p_tok));	// v2.5
		free(p_temp);
		return(OK);
	  }
	  length+=ret;
	  //for DOC multi Ver.2.70 
	  //parameter_num=0;
	}
  }
  free(p_temp);
  return(OK);
}


/*
 * The conversion function for DOC Code. (Overwrite DSC Code)
 */
int com_setoperatecode(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl)
{
  //int ret;
  //int length=0;
  int parameter_num=1;
  char *p_tok;
  char *p_temp;

  if( p_s->p_bsccsts == NULL ){
	return(OK);
  }

  p_temp=(char *)malloc( strlen(p_s->p_bsccsts) + 1 );
  if(p_temp == NULL){
    return(ERR_MEMORY);
  }
  memset (p_temp, 0, strlen(p_s->p_bsccsts) + 1);
  strncpy(p_temp, p_s->p_bsccsts, strlen(p_s->p_bsccsts));
  p_tok=strtok(p_temp, "," );
  parameter_num++;

  while( (p_tok = strtok(NULL,",")) != NULL ){
	parameter_num++;
	//for DOC multi Ver.2.70 DOC:4,01,1000,/,4,01,1200; 4*X appear
	if((parameter_num%4) == 0){
	  if( strncmp(p_tok, "NO", strlen(p_tok) ) == 0 )  break;
	  if( strncmp(p_tok, "UK", strlen(p_tok) ) == 0 )  break;

	  //printf("com_setoperatecode p_tok = %s\n",p_tok);
	  strncpy(p_tbl->service_call, p_tok, strlen(p_tok));	// v2.5

	  //ret=commonstssetprocess(p_tok, (p_s->p_storetbl)+length, p_ct);
	  //if(ret == BADITEM ){
		strncpy(p_s->p_storetbl, p_tok, strlen(p_tok));	// v2.5
		free(p_temp);
		return(OK);
	  //}
	  //length+=ret;
	  /* must 1times */
	  break;
	}
  }
  free(p_temp);
  return(OK);
}

/*
 * The conversion function for DSC Code.
 */
int com_setservicecallcode(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl)
{
//  int ret;
//  int length=0;
//  int parameter_num=1;
  char *p_tok;
  char *p_temp;


  if( p_s->p_bsccsts == NULL ){
	return(OK);
  }

  p_temp=(char *)malloc( strlen(p_s->p_bsccsts) + 1 );
  if(p_temp == NULL){
    return(ERR_MEMORY);
  }
  memset (p_temp, 0, strlen(p_s->p_bsccsts) + 1);
  strncpy(p_temp, p_s->p_bsccsts, strlen(p_s->p_bsccsts));
  p_tok=strtok(p_temp, "," );
//  printf("com_setservicecallcode p_tok = %s\n",p_tok);
//  parameter_num++;

//  while( (p_tok = strtok(NULL,",")) != NULL ){
//	parameter_num++;
	//for DOC multi Ver.2.70 DOC:4,01,1000,/,4,01,1200; 4*X appear
//	if((parameter_num%4) == 0){

	  if( strncmp(p_tok, "NO", strlen(p_tok) ) == 0 )  goto err01;
	  if( strncmp(p_tok, "UK", strlen(p_tok) ) == 0 )  goto err01;

	  strncpy(p_tbl->service_call, p_tok, strlen(p_tok));	// v2.5

	  //ret=commonstssetprocess(p_tok, (p_s->p_storetbl)+length, p_ct);
	  //if(ret == BADITEM ){
	//	strncpy(p_s->p_storetbl, p_tok, strlen(p_tok));	// v2.5
	//	free(p_temp);
	//	return(OK);
	//  }
//	  length+=ret;
	  /* must 1times */
//	  break;
//	}
//  }

err01:

  free(p_temp);
  return(OK);
}



/*
 * It investigates whether ink low and ink out have occurred.
 * return:
 *       When having generated -- OCCUR macros. 
 */
int com_warnoperatechk(char *p_call, char color, int buf_length)
{
  int i;

  for(i=0; p_call[i] != SPACE && i < buf_length; i++){
	if(color == p_call[i]){
	  return(OCCUR);
	}
  }
  return(OK);
}
