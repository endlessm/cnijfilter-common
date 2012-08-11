/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2004
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
 */
/*** Includes ***/
#include"bjcupsmon_common.h"
#include"bjcupsmon_transsts.h"

static int processIDcheck(const ST_MSGTBL *p_msgtbl, char *p_status, int status_size );
static int chkoccuroperatorcall(ST_CUPSSTS *p_tbl, char chkchr);
static int storeMessageID(ST_PrinterStatus *p_sts, int msgID);
static int processstandardmsgcheck(ST_PrinterStatus *p_sts, const ST_MSGTBL *p_msgtbl, char *p_status, int status_size);


static const
ST_MSGTBL service[]={
  {'I', ID_STS_MESSAGE_SC_USEDTANK_FULL},
  {ENDTAG, 0}
};


static const
ST_MSGTBL operatelevel1[]={
  {'P', ID_STS_MESSAGE_OC_PAPER_OUT},
  {'J', ID_STS_MESSAGE_OC_PAPER_JAM},
  {'H', ID_STS_MESSAGE_OC_CARTRIDGE_NONE},		// v.2.3 010-1121 V.2.4 003-0105
  {'R', ID_STS_MESSAGE_OC_HEAD_ERROR},
  {ENDTAG, 0}
};


static const
ST_MSGTBL operatelevel2[]={
  {'S', ID_STS_MESSAGE_CARTRIDGE_UNSUPPORTED},
  {'I', ID_STS_MESSAGE_OC_USEDTANK_ALMOST},
  {'D', ID_STS_MESSAGE_OC_PROTECTOR},
  {ENDTAG, 0}
};


static const
ST_MSGTBL inkout[]={
  {'K', ID_STS_MESSAGE_OC_INKOUT_BLACK},
  {'L', ID_STS_MESSAGE_OC_INKOUT_BLACK},
  {'k', ID_STS_MESSAGE_OC_INKOUT_PHOTO_BLACK},
  {'c', ID_STS_MESSAGE_OC_INKOUT_PHOTO_CYAN},
  {'m', ID_STS_MESSAGE_OC_INKOUT_PHOTO_MAGENTA},
  {'C', ID_STS_MESSAGE_OC_INKOUT_CYAN},
  {'M', ID_STS_MESSAGE_OC_INKOUT_MAGENTA},
  {'Y', ID_STS_MESSAGE_OC_INKOUT_YELLOW},
  {ENDTAG, 0}
};


static const
ST_MSGTBL operatelevel3[]={
  {'g', ID_STS_MESSAGE_CDR_GUIDE},
  {'O', ID_STS_MESSAGE_OC_COVER_OPEN},
  {'G', ID_STS_MESSAGE_OC_CDR_GUIDE},
  {ENDTAG, 0}
};


static const
ST_MSGTBL busystat[]={
  {'L', ID_STS_MESSAGE_BUSY_CLEANING},
  {'C', ID_STS_MESSAGE_BUSY_CARTRIDGE_CHANGE},
  {'T', ID_STS_MESSAGE_BUSY_TEST_PRINTING},
  {'I', ID_STS_MESSAGE_BUSY_PRINTER_USED},
  {ENDTAG, 0}
};


static const
ST_MSGTBL cartridge[]={
  {'2', ID_STS_MESSAGE_OC_CARTRIDGE_SCANNER},
  {'4', ID_STS_MESSAGE_CARTRIDGE_UNSUPPORTED},
  {ENDTAG, 0}
};


static const
ST_MSGTBL inklowpart1[]={
  {'K', ID_STS_MESSAGE_WAR_INKLOW_BLACK},
  {'L', ID_STS_MESSAGE_WAR_INKLOW_BLACK},
  {'B', ID_STS_MESSAGE_WAR_INKLOW_BLACK},
  {'k', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_BLACK},
  {'c', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_CYAN},
  {'m', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_MAGENTA},
  {'C', ID_STS_MESSAGE_WAR_INKLOW_CYAN},
  {'M', ID_STS_MESSAGE_WAR_INKLOW_MAGENTA},
  {'Y', ID_STS_MESSAGE_WAR_INKLOW_YELLOW},
  {'E', ID_STS_MESSAGE_WAR_INKLOW_COLOR},
  {ENDTAG, 0}
};


static const
ST_MSGTBL inklowpart2[]={
  {'b', ID_STS_MESSAGE_WAR_INKLOW_24BLACK3},
  {'e', ID_STS_MESSAGE_WAR_INKLOW_24COLOR3},
  {ENDTAG, 0}
};



/*
 * The following functions exist in order to set the corresponding message ID.
 */


/*
 * In a service call, other processings are not performed.
 */
int chk_servicecall(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  if(p_tbl->service_call[0]==SPACE){
    return(ID_ERR_NO_ERROR);
  }

  ret=processIDcheck(&service[0], p_tbl->service_call, sizeof(p_tbl->service_call) );
  if(ret == ID_ERR_MEM_ALLOC_FAILED){
    return(ret);
  }
  else if(ret != IDNOTFOUND){
    ret=storeMessageID(p_sts, ret);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
    return(SERVICECALL);
  }
  else{
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_SC_SERVICE_ERROR_PRE);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_SC_SERVICE_ERROR_AFTER);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
    return(SERVICECALL);
  }
  return(ret);
}


/*
 * The number of what is displayed among the message ID acquired
 * with the following functions is one. (Except ink out)
 *
 * chk_operatorcall_level1();
 * chk_operatorcall_cartridge();
 * chk_operatorcall_level2();
 * chk_inkout();
 * chk_operatorcall_level3();
 * chk_busystatus();
 * chk_cartridge();
 * chk_basestatus();
 *
 */
int chk_operatorcall_level1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  ret=processstandardmsgcheck(p_sts, &operatelevel1[0], p_tbl->operator_call, sizeof(p_tbl->operator_call));
  return(ret);
}


int chk_operatorcall_cartridge(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i;
  int ret;
  int msg=-1;

  for(i=0; i<sizeof(p_tbl->operator_call); i++){
    if(*(p_tbl->operator_call+i) == SCANNERDETECT){
      if(p_tbl->busy_stat != TESTPRINTNOW){
		msg=ID_STS_MESSAGE_OC_CARTRIDGE_SCANNER;
      }
      else{
		msg=ID_STS_MESSAGE_CARTRIDGE_SCANNER;
      }
      ret=storeMessageID(p_sts, msg);
      if(ret != ID_ERR_NO_ERROR){
		return(ret);
      }
      return(UNIQUESTS);
    }
  }
  return(ID_ERR_NO_ERROR);
}


int chk_operatorcall_level2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  ret=processstandardmsgcheck(p_sts, &operatelevel2[0], p_tbl->operator_call, sizeof(p_tbl->operator_call));
  return(ret);
}


int chk_inkout(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i,k;
  int ret;
  int inkout_storeposit;

  inkout_storeposit=p_sts->messageNum;
  p_sts->messageNum++;
  for(i=0; inkout[i].status!=ENDTAG; i++){
    for(k=0; (k<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+k)!=SPACE); k++){
      if(inkout[i].status == *(p_tbl->operator_call+k)){
	ret=storeMessageID(p_sts, inkout[i].msgid);
	if(ret != ID_ERR_NO_ERROR){
	  return(ret);
	}
      }
    }
  }
  if(p_sts->messageNum != (inkout_storeposit+1)){
    *(p_sts->pMessageID+inkout_storeposit)=ID_STS_MESSAGE_OC_INKOUT;
    return(UNIQUESTS);
  }
  else {
    p_sts->messageNum--;
    return(ID_ERR_NO_ERROR);
  }
}


int chk_operatorcall_level3(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;
  if((p_tbl->operator_call[0]==SPACE) || (p_tbl->operator_call[0]==UNJUSTVALUE)){
    return(ID_ERR_NO_ERROR);
  }
  ret=processstandardmsgcheck(p_sts, &operatelevel3[0], p_tbl->operator_call, sizeof(p_tbl->operator_call));
  if(ret == ID_ERR_NO_ERROR){
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_OTHER);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
    return(UNIQUESTS);
  }
  return(ret);
}


int chk_busystatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  ret=processstandardmsgcheck(p_sts, &busystat[0], &p_tbl->busy_stat, sizeof(p_tbl->busy_stat));
  return(ret);
}


int chk_cartridge(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;
  int i;

  for(i=0; i<MAXCARTRIDGENUM; i++){
    ret=processstandardmsgcheck(p_sts, &cartridge[0], &p_tbl->cartridge[i].type, sizeof(p_tbl->cartridge[i].type));
    if(ret!=ID_ERR_NO_ERROR){
      return(ret);
    }
    if(p_tbl->cartridge[i].type != DUMMYSCANNER && p_tbl->cartridge[i].type != SPACE 
       && p_tbl->cartridge[i].type != UNJUSTVALUE){
      return(ret);
    }
  }
  ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_CARTRIDGE_NONE);
  if(ret != ID_ERR_NO_ERROR){
    return(ret);
  }
  return(UNIQUESTS);
}


int chk_basestatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  unsigned int bst;
  char strbst[3];
  int ret;

  if(p_tbl->base_stat[0] == UNJUSTVALUE){
    return(ID_ERR_NO_ERROR);
  }
  strncpy(strbst, p_tbl->base_stat, sizeof(p_tbl->base_stat));
  bst=strtoul(strbst, NULL, 16);
  if(bst & 0x80){
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_BASE_PRINTING);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  else{
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_BASE_ONLINE);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  return(UNIQUESTS);
}

/*
 * The message ID acquired with the following functions 
 * can be displayed with other messages.
 *
 * chk_inklow_part1();
 * chk_inklow_part2();
 * chk_noinkcheck();
 */
int chk_inklow_part1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i,k;
  int ret;
  int inklow_storeposit;

  inklow_storeposit=p_sts->messageNum;
  p_sts->messageNum++;

  for(i=0; inklowpart1[i].status!=ENDTAG; i++){
    for(k=0; (k<sizeof(p_tbl->warning)) && (*(p_tbl->warning+k)!=SPACE); k++){
      if(inklowpart1[i].status == *(p_tbl->warning+k)){
	ret=chkoccuroperatorcall(p_tbl, *(p_tbl->warning+k));
	if(ret != OCCUR){
	  ret=storeMessageID(p_sts, inklowpart1[i].msgid);
	  if(ret != ID_ERR_NO_ERROR){
	    return(ret);
	  }
	}
      }
    }
  }
  if(p_sts->messageNum != (inklow_storeposit+1)){
    *((p_sts->pMessageID)+inklow_storeposit)=ID_STS_MESSAGE_WAR_INKLOW;
  }
  else {
    p_sts->messageNum--;
  }
  return(ID_ERR_NO_ERROR);
}


int chk_inklow_part2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i,k;
  int ret;
  int inklow_storeposit;

  inklow_storeposit=p_sts->messageNum;
  p_sts->messageNum++;

  for(i=0; inklowpart2[i].status!=ENDTAG; i++){
    for(k=0; (k<sizeof(p_tbl->warning)) && (*(p_tbl->warning+k)!=SPACE); k++){
      if(inklowpart2[i].status == *(p_tbl->warning+k)){
	ret=storeMessageID(p_sts, inklowpart2[i].msgid);
	if(ret != ID_ERR_NO_ERROR){
	  return(ret);
	}
      }
    }
  }

  if(p_sts->messageNum != (inklow_storeposit+1)){
    *((p_sts->pMessageID)+inklow_storeposit)=ID_STS_MESSAGE_WAR_INKLOW_24PRE;
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_WAR_INKLOW_24AFTER);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  else {
    p_sts->messageNum--;
  }
  return(ID_ERR_NO_ERROR);
}


int chk_noinkcheck(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  ret=ID_ERR_NO_ERROR;
  if(p_tbl->ink_check == 'N'){
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_CIL_OFF);
  }
  return(ret);
}


/*
 * The following is a static processing function.
 */
static int processIDcheck(const ST_MSGTBL *p_msgtbl, char *p_status, int status_size )
{
  int i;
  int ret;

  char *p_temp;
  char *p_callchr;

  ret=IDNOTFOUND;
  p_temp=(char *)malloc(status_size+1);
  if(p_temp == NULL){
    return(ID_ERR_MEM_ALLOC_FAILED);
  }
  strncpy(p_temp, p_status, status_size);
  *(p_temp+status_size)='\0';

  for(i=0; (p_msgtbl+i)->status!=ENDTAG; i++){
    p_callchr=strchr(p_temp, (p_msgtbl+i)->status);
    if(p_callchr!=NULL ){
      ret=(p_msgtbl+i)->msgid;
      break;
    }
  }
  free(p_temp);
  return(ret);
}


static int chkoccuroperatorcall(ST_CUPSSTS *p_tbl, char chkchr)
{
  int i;

  for(i=0; (i<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+i)!=SPACE); i++){
    if(*(p_tbl->operator_call+i) == chkchr){
      return(OCCUR);
    }
  }
  return(NOTINKOUT);
}


static int storeMessageID(ST_PrinterStatus *p_sts, int msgID)
{
  if(p_sts->messageNum >= STANDARDMSGNUM){
    p_sts->pMessageID=(ENUM_STSMessageID *)realloc(p_sts->pMessageID, sizeof(ENUM_STSMessageID)*((p_sts->messageNum)+1) );
    if(p_sts->pMessageID == NULL){
      return(ID_ERR_MEM_ALLOC_FAILED);
    }
  }
  *((p_sts->pMessageID)+(p_sts->messageNum))=msgID;
  (p_sts->messageNum)++;
  return(ID_ERR_NO_ERROR);
} 


static int processstandardmsgcheck(ST_PrinterStatus *p_sts, const ST_MSGTBL *p_msgtbl, char *p_status, int status_size)
{
  int ret;

  ret=processIDcheck(p_msgtbl, p_status, status_size);
  if(ret != IDNOTFOUND){
    ret=storeMessageID(p_sts, ret);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
    return(UNIQUESTS);
  }
  return(ID_ERR_NO_ERROR);
}
