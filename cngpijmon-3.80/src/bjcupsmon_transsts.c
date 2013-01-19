/*
 *  Canon Inkjet Printer Driver for Linux
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
 */
/*** Includes ***/
#include "bjcupsmon_common.h"
#include "bjcupsmon_transsts.h"

static int processsetprinterstatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_cartridgeClass(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_leverPosition(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_Destination(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_serviceCall(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_cartridgeStatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_messageID(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static int set_printInterface(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
static void set_inkinfo(ST_CUPSSTS *p_tbl, ST_InkStatus *p_storests, int index);
/* for Ver.3.80 */
static int set_inkifnumber(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);

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
  set_Destination,  
  set_leverPosition,
  set_serviceCall,
  set_cartridgeStatus,
  set_messageID,
  set_printInterface,
  /* for Ver.3.80 */
  set_inkifnumber,};

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


static int set_Destination(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  p_sts->destination=(int)p_tbl->destination;
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

/* for Ver3.80 */
static int set_inkifnumber(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i,j;

  for(i=0; i<MAXINKNUM; i++){
  	if( p_tbl->ink[i].color == ' ') break;
  	if( p_tbl->ink2[i].ifnumber[0] == ' ' ) break;
  	p_sts->status_ifnumber[i].colorstr =  p_tbl->ink[i].color;
   	for(j=0; ;j++){
  		 if( p_tbl->ink2[i].ifnumber[j] == ' ' ) break;
  		 p_sts->status_ifnumber[i].ifnumberstr[j] = p_tbl->ink2[i].ifnumber[j];
  		 //if( p_tbl->ink2[i].ifnumber[j] == '>' ) break;
  	}
  }

  return(ID_ERR_NO_ERROR);
}


static const SETSTATUSFUNC
chkmessagefunctable[]={
  chk_other_operation, /* other operation Priority 1st */
  chk_otheruser_use,
  chk_servicecall,
  chk_operatorcall_level1,
  chk_busystatus,
  chk_jobstatus,
  chk_inklow_part1,
  chk_noinkcheck,
  chk_noinkcheck2,
};


//#define _CHECK_ST_CUPSSTS_

#ifdef _CHECK_ST_CUPSSTS_
static void check_ST_PrinterStatus(ST_CUPSSTS *p_tbl)
{
  int i,j;
  
  char header[5];
  char dev[5];
  char pr_name[17];
  char base_stat[3];
  char busy_stat[2];
  char job_stat[2];
  struct {
	char type;
	char exchange;
	char dummy;
  }cartridge[2];
  struct {
	char color;
	char alert;
	char fill[4];
	char resv;
  }ink[8];
  char ink_check[2];
  char destination[2];
  char warning[13];
  char operator_call[13];
  char service_call[5];
  char lever_position[2];
//Ver.3.00
  char prnregion[2];
//Ver.3.10
  char service_call2[2];
  /* for Ver.3.80 */
  struct {
	char ifnumber[33];
	char resv[8];
  }ink2[8];
  /* for Ver.3.80 */


  for(i=0; i<sizeof(header); i++)	header[i] = '\0';
  for(i=0; i<sizeof(dev); i++)	dev[i] = '\0';
  for(i=0; i<sizeof(pr_name); i++)	pr_name[i] = '\0';
  for(i=0; i<sizeof(base_stat); i++)	base_stat[i] = '\0';
  for(i=0; i<sizeof(busy_stat); i++)	busy_stat[i] = '\0';
  for(i=0; i<sizeof(job_stat); i++)	job_stat[i] = '\0';
  for(i=0; i<2; i++)	cartridge[i].dummy = '\0';
  for(j=0; j<8; j++)	
	  for(i=0; i<4; i++)	
	  	ink[j].fill[i] = '\0';
  for(i=0; i<sizeof(ink_check); i++)	ink_check[i] = '\0';
  for(i=0; i<sizeof(destination); i++)	destination[i] = '\0';
  for(i=0; i<sizeof(lever_position); i++)	lever_position[i] = '\0';
//Ver.3.00
  for(i=0; i<sizeof(prnregion); i++)	prnregion[i] = '\0';

  for(i=0; i<sizeof(warning); i++)	warning[i] = '\0';
  for(i=0; i<sizeof(operator_call); i++)	operator_call[i] = '\0';
  for(i=0; i<sizeof(service_call); i++)	service_call[i] = '\0';

//Ver.3.10
  for(i=0; i<sizeof(service_call2); i++)	service_call2[i] = '\0';
  /* Ver.3.80 */
  for(j=0; j<8; j++)	
	  memset(ink2[j].ifnumber, 0, sizeof(ink2[j].ifnumber));

  strncpy( header, p_tbl->header, sizeof(p_tbl->header) );
  strncpy( dev, p_tbl->dev, sizeof(p_tbl->dev) );
  strncpy( pr_name, p_tbl->pr_name, sizeof(p_tbl->pr_name) );
  strncpy( base_stat, p_tbl->base_stat, sizeof(p_tbl->base_stat) );
  busy_stat[0] = p_tbl->busy_stat;
  job_stat[0] = p_tbl->job_stat;
  for(j=0; j<2; j++){
	  cartridge[j].type = p_tbl->cartridge[j].type;
	  cartridge[j].exchange = p_tbl->cartridge[j].exchange;
  }
  for(j=0; j<8; j++){
	  ink[j].color = p_tbl->ink[j].color;
	  ink[j].alert = p_tbl->ink[j].alert;
	  strncpy( ink[j].fill, p_tbl->ink[j].fill, sizeof(p_tbl->ink[j].fill) );
  }

  ink_check[0] = p_tbl->ink_check;
  lever_position[0] = p_tbl->lever_position;
  destination[0] = p_tbl->destination;
//Ver.3.00
  prnregion[0] = p_tbl->prnregion;
  strncpy( warning, p_tbl->warning, sizeof(p_tbl->warning) );
  strncpy( operator_call, p_tbl->operator_call, sizeof(p_tbl->operator_call) );
  strncpy( service_call, p_tbl->service_call, sizeof(p_tbl->service_call) );
//Ver.3.10
  service_call2[0] = p_tbl->service_call2;
  /* for Ver.3.80 */
  for(j=0; j<8; j++){
	  strncpy( ink2[j].ifnumber, p_tbl->ink2[j].ifnumber, sizeof(p_tbl->ink2[j].ifnumber) );
  }



  printf("\n###Check ST_CUPSSTS data .....\n");
  printf("##################################\n");

  printf("header      = %s\n", header);
  printf("dev         = %s\n", dev);
  printf("pr_name     = %s\n", pr_name);
  printf("base_stat   = %s\n", base_stat);
  printf("busy_stat   = %s\n", busy_stat);
  printf("job_stat   = %s\n", job_stat);
  for(j=0; j<2; j++)
	  printf("cartridge[%d]: type exchange  = %s\n", j,&(cartridge[j].type));
  for(j=0; j<8; j++)
	  printf("color alert fill[%d]   = %s\n", j,&(ink[j].color));
  printf("ink_check     = %s\n", ink_check);
  printf("destination     = %s\n", destination);
  printf("warning[12]     = %s\n", warning);
  printf("operator[12]    = %s\n", operator_call);
  printf("service[5]     = %s\n", service_call);
  printf("lever_position     = %s\n", lever_position);
//Ver.3.00
  printf("prnregion     = %s\n", prnregion);
//Ver.3.10
  printf("service2     = %s\n", service_call2);
  /* for Ver.3.80 */
  for(j=0; j<8; j++)
	  printf("ifnumber[%d]   = %s\n", j,&(ink2[j].ifnumber[0]));

}
#endif

static int set_messageID(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int i;
  int ret;
  
#ifdef _CHECK_ST_CUPSSTS_
  check_ST_PrinterStatus(p_tbl);
#endif


  //Ver.3.00 set pictarea
  ret=set_pictareaInfo(p_tbl, p_sts);

  for(i=0; i<MAXCHKSTS; i++){

    ret=(*chkmessagefunctable[i])(p_tbl, p_sts);

    switch(ret){
    case ID_ERR_MEM_ALLOC_FAILED:
      return(ret);
    //case SERVICECALL:
    //  return(ID_ERR_NO_ERROR);
    //2.00.01.010 NoCartridge:other message doesn't appear.
    case OTHERMESSAGENO:
      return(ID_ERR_NO_ERROR);
    /* serivice call and warning */
    case SERVICECALL:
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

      if( !strncmp( p_tbl->ink[index].fill, INKLVL_UNKOWN, strlen(INKLVL_UNKOWN) ) ) {
		(p_storests+i)->level = ID_INK_LEVEL_UK;
	  }
      //for Ver.2.70 UUU
      else if(!strncmp( p_tbl->ink[index].fill, INKLVL_UNKOWNUUU, strlen(INKLVL_UNKOWNUUU) ) ) {
		(p_storests+i)->level = ID_INK_LEVEL_UK;
	  }
      //for Ver.2.70 NNN
      else if(!strncmp( p_tbl->ink[index].fill, INKLVL_UNSETTANK, strlen(INKLVL_UNSETTANK) ) ) {
		(p_storests+i)->level = ID_INK_LEVEL_UNSETTNK;
	  }
	  else {
	      strncpy(temp, p_tbl->ink[index].fill, sizeof(p_tbl->ink[index].fill));
	      temp[3]='\0';
	      (p_storests+i)->level=atoi(temp);
	  }

      (p_storests+i)->status=(int)p_tbl->ink[index].alert;

      break;
    }
  }
  return;
}

