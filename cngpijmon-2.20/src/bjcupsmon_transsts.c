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
#include "bjcupsmon_common.h"
#include "bjcupsmon_transsts.h"

static int processsetprinterstatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_cartridgeClass(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_leverPosition(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_serviceCall(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_cartridgeStatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_messageID(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_printInterface(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static void set_inkinfo(ST_CUPSSTS *p_tbl, ST_InkStatus *p_storests, int index);


/*** Functions ***/
int translatePrinterStatus(char *pstatusStr, ST_PrinterStatus *pStatus)
{
  int ret;

  ST_CUPSSTS *p_tbl;
  pStatus->pMessageID=(ENUM_STSMessageID *)malloc(sizeof(ENUM_STSMessageID)*STANDARDMSGNUM);
  if(pStatus->pMessageID == NULL){
    return(ID_ERR_MEM_ALLOC_FAILED);
  }

  p_tbl=(ST_CUPSSTS *)pstatusStr;
  ret=processsetprinterstatus(p_tbl, pStatus);
  if(ret != ID_ERR_NO_ERROR){
    return(ret);
  }

  return(ID_ERR_NO_ERROR);
}

static const SETSTATUSFUNC
setstatusfunctable[]={
  set_cartridgeClass,
  set_leverPosition,
  set_serviceCall,
  set_cartridgeStatus,
  set_messageID,
  set_printInterface,
};

static int processsetprinterstatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i;
  int ret = ID_ERR_NO_ERROR;

  for(i=0; i<SETSTATUSNUM; i++){
    ret = (*setstatusfunctable[i])(p_tbl, p_sts);
    if(ret != ID_ERR_NO_ERROR){
      break;
    }
  }
  return(ret);
}


static int  set_cartridgeClass(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i;
  for(i=0; i<MAXCARTRIDGENUM; i++){
    p_sts->cartridgeClass[i].type=(int)(p_tbl->cartridge[i].type);
    p_sts->cartridgeClass[i].exchange=(int)(p_tbl->cartridge[i].exchange);
  }
  return(ID_ERR_NO_ERROR);
}


static int set_leverPosition(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  p_sts->leverPosition=(int)p_tbl->lever_position;
  return(ID_ERR_NO_ERROR);
}


static int set_serviceCall(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  if(p_tbl->service_call[0] != SPACE){
    strncpy(p_sts->serviceCallID, p_tbl->service_call, sizeof(p_tbl->service_call));
  }
  return(ID_ERR_NO_ERROR);
}


static int set_cartridgeStatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i;

  for(i=0; p_tbl->ink[i].color != SPACE && i<MAXINKNUM; i++){
    set_inkinfo(p_tbl, p_sts->cartridgeStatus, i);
  }
  return(ID_ERR_NO_ERROR);
}

static const ST_DEVID_TBL printInterfaceTable[]={
  {DEV_1284, ID_DEV_1284},
  {DEV_USB,  ID_DEV_USB },
  {DEV_1394, ID_DEV_1394},
  {NULL, 0}
};

static int set_printInterface(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  const ST_DEVID_TBL *p_dev_tbl= printInterfaceTable;

  while(p_dev_tbl->dev != NULL){
    if (memcmp(p_tbl->dev, p_dev_tbl->dev, DEV_CHARSIZE) == 0) break;
    p_dev_tbl++;
  }
   
  p_sts->printInterface=p_dev_tbl->id;

  return(ID_ERR_NO_ERROR);
}


static const SETSTATUSFUNC
chkmessagefunctable[]={
  chk_servicecall,
  chk_operatorcall_level1,
  chk_operatorcall_cartridge,
  chk_operatorcall_level2,
  chk_inkout,
  chk_operatorcall_level3,
  chk_busystatus,
  chk_cartridge,
  chk_basestatus,
  chk_inklow_part1,
  chk_inklow_part2,
  chk_noinkcheck,
};

static int set_messageID(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i;
  int ret;

  for(i=0; i<MAXCHKSTS; i++){

    ret=(*chkmessagefunctable[i])(p_tbl, p_sts);

    switch(ret){
    case ID_ERR_MEM_ALLOC_FAILED:
      return(ret);
    case SERVICECALL:
      return(ID_ERR_NO_ERROR);
    case UNIQUESTS:
      i=SKIPCHKFUNC;
    }
  }
  return(ret);
}


static void set_inkinfo(ST_CUPSSTS *p_tbl, ST_InkStatus *p_storests, int index)
{
  int i;
  char temp[4];
  char color[]=ALLCOLORCHAR;


  for(i=0; color[i]!='\0'; i++){
    if(p_tbl->ink[index].color == color[i]){
      strncpy(temp, p_tbl->ink[index].fill, sizeof(p_tbl->ink[index].fill));
      temp[3]='\0';
      (p_storests+i)->level=atoi(temp);
      (p_storests+i)->status=(int)p_tbl->ink[index].alert;

      break;
    }
  }
  return;
}

