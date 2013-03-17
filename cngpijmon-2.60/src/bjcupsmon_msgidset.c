/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2006
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
//static int chkoccuroperatorcall(ST_CUPSSTS *p_tbl, char chkchr);
static int chkoccuralert(ST_CUPSSTS *p_tbl, char chkchr);
static int storeMessageID(ST_PrinterStatus *p_sts, int msgID);
static int processstandardmsgcheck(ST_PrinterStatus *p_sts, const ST_MSGTBL *p_msgtbl, char *p_status, int status_size);


static const
ST_MSGTBL service[]={
  {'I', ID_STS_MESSAGE_SC_USEDTANK_FULL},
  {ENDTAG, 0}
};


static const
ST_MSGTBL operatelevel1[]={
  {'U', ID_STS_MESSAGE_OC_USBDEVICE},		// 560i 860i 990i
  {'P', ID_STS_MESSAGE_OC_PAPER_OUT},
  {'V', ID_STS_MESSAGE_OC_PAPER_OUT21},
  {'X', ID_STS_MESSAGE_OC_PAPER_OUT23},
  {'p', ID_STS_MESSAGE_OC_PAPER_OUT22},
  {'a', ID_STS_MESSAGE_OC_PAPER_OUT24},
  {'J', ID_STS_MESSAGE_OC_PAPER_JAM},
  {'q', ID_STS_MESSAGE_OC_PAPER_JAM1},
  {'h', ID_STS_MESSAGE_OC_PAPER_JAM2},
  {'j', ID_STS_MESSAGE_OC_PAPER_JAM03},
  {'n', ID_STS_MESSAGE_OC_PAPER_JAM06},
  {'Q', ID_STS_MESSAGE_OC_PAPER_JAM04},
  {'i', ID_STS_MESSAGE_OC_PAPER_JAM05},
  {'Z', ID_STS_MESSAGE_OC_PAPER_JAM07},
  {'H', ID_STS_MESSAGE_OC_CARTRIDGE_NONE},		// v.2.3 010-1121 V.2.4 003-0105
  {'R', ID_STS_MESSAGE_OC_HEAD_ERROR},
  {'r', ID_STS_MESSAGE_OC_HEAD_ERROR2},
  {ENDTAG, 0}
};


static const
ST_MSGTBL operatelevel2[]={
//{'S', ID_STS_MESSAGE_CARTRIDGE_UNSUPPORTED},
  {'I', ID_STS_MESSAGE_OC_USEDTANK_ALMOST},
  {'x', ID_STS_MESSAGE_OC_USEDTANK_ALMOST2},
  {'D', ID_STS_MESSAGE_OC_PROTECTOR},
  {'T', ID_STS_MESSAGE_OC_INKTANK_NONE},		// i250/i255
  {'A', ID_STS_MESSAGE_OC_HEADALIGNMENT},		// 860i 990i
  {'N', ID_STS_MESSAGE_OC_HEADALIGNMENT2},
  {'t', ID_STS_MESSAGE_OC_HARDWAREERROR_TANK},	// iP4200 iP6600D iP7500 MP500
  {ENDTAG, 0}
};


static const
ST_MSGTBL inkout[]={
  {'E', ID_STS_MESSAGE_OC_INKOUT_TANK},
  {'u', ID_STS_MESSAGE_OC_INKOUT_TANK2},
  {'B', ID_STS_MESSAGE_OC_INKOUT_CART},
//{'K', ID_STS_MESSAGE_OC_INKOUT_BLACK},
  {'l', ID_STS_MESSAGE_OC_INKOUT_PHOTO_BLACK},
  {'L', ID_STS_MESSAGE_OC_INKOUT_BLACK},
//{'k', ID_STS_MESSAGE_OC_INKOUT_PHOTO_BLACK},
  {'c', ID_STS_MESSAGE_OC_INKOUT_PHOTO_CYAN},
  {'m', ID_STS_MESSAGE_OC_INKOUT_PHOTO_MAGENTA},
  {'C', ID_STS_MESSAGE_OC_INKOUT_CYAN},
  {'M', ID_STS_MESSAGE_OC_INKOUT_MAGENTA},
  {'Y', ID_STS_MESSAGE_OC_INKOUT_YELLOW},
//{'B', ID_STS_MESSAGE_OC_INKOUT_BLACK},
//{'r', ID_STS_MESSAGE_OC_INKOUT_RED},
//{'N', ID_STS_MESSAGE_OC_INKOUT_GREEN},	// ip8600
  {ENDTAG, 0}
};


static const
ST_MSGTBL operatelevel3[]={
  {'s', ID_STS_MESSAGE_OC_PLURALERROR_TANK},
  {'e', ID_STS_MESSAGE_OC_DIFFERENT_REGION_TANK},
  {'S', ID_STS_MESSAGE_OC_POSITION_MISMACH_TANK},
  {'d', ID_STS_MESSAGE_OC_UNINSTALLATION_TANK},
  {'f', ID_STS_MESSAGE_OC_REFILL},
  {'z', ID_STS_MESSAGE_OC_REFILL2},
  {'b', ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART},
  {'W', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN1},
  {'w', ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2},
  {ENDTAG, 0}
};


static const
ST_MSGTBL operatelevel4[]={
//{'g', ID_STS_MESSAGE_CDR_GUIDE},
  {'O', ID_STS_MESSAGE_OC_COVER_OPEN},
  {'v', ID_STS_MESSAGE_OC_COVER_OPEN2},
  {'o', ID_STS_MESSAGE_OC_COVER_CLOSE},
  {'k', ID_STS_MESSAGE_OC_COVER_CLOSE2},
  {'G', ID_STS_MESSAGE_OC_CDR_GUIDE},
  {'g', ID_STS_MESSAGE_OC_CDR_GUIDE2},
  {'F', ID_STS_MESSAGE_CDR_GUIDE_PRINT},
  {'K', ID_STS_MESSAGE_CDR_GUIDE_PRINT2},
  {ENDTAG, 0}
};


static const
ST_MSGTBL busystat[]={
  {'L', ID_STS_MESSAGE_BUSY_CLEANING},
  {'C', ID_STS_MESSAGE_BUSY_CARTRIDGE_CHANGE},
  {'D', ID_STS_MESSAGE_BUSY_CARTRIDGE_CHANGE2},	//v2.5
  {'F', ID_STS_MESSAGE_BUSY_CARTRIDGE_CHANGE3},	//v2.5
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
  {'L', ID_STS_MESSAGE_WAR_INKLOW_BLACK},
  {'l', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_BLACK},
  {'C', ID_STS_MESSAGE_WAR_INKLOW_CYAN},
  {'M', ID_STS_MESSAGE_WAR_INKLOW_MAGENTA},
  {'Y', ID_STS_MESSAGE_WAR_INKLOW_YELLOW},
  {'c', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_CYAN},
  {'m', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_MAGENTA},
//{'K', ID_STS_MESSAGE_WAR_INKLOW_BLACK},
//{'B', ID_STS_MESSAGE_WAR_INKLOW_BLACK24},	// S300
//{'k', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_BLACK},
//{'E', ID_STS_MESSAGE_WAR_INKLOW_COLOR24},
//{'r', ID_STS_MESSAGE_WAR_INKLOW_RED},
//{'N', ID_STS_MESSAGE_WAR_INKLOW_GREEN},	// ip8600
  {ENDTAG, 0}
};


static const
ST_MSGTBL inklowpart1_type_OTH[]={
  {'L', ID_STS_MESSAGE_WAR_INKLOW_BLACK8},
  {'l', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_BLACK5},
  {'C', ID_STS_MESSAGE_WAR_INKLOW_CYAN8},
  {'M', ID_STS_MESSAGE_WAR_INKLOW_MAGENTA8},
  {'Y', ID_STS_MESSAGE_WAR_INKLOW_YELLOW8},
  {'c', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_CYAN8},
  {'m', ID_STS_MESSAGE_WAR_INKLOW_PHOTO_MAGENTA8},
  {ENDTAG, 0}
};


static const
ST_MSGTBL inklowpart2[]={
  {'B', ID_STS_MESSAGE_WAR_INKLOW_BLACK40},
  {'E', ID_STS_MESSAGE_WAR_INKLOW_COLOR41},
  {ENDTAG, 0}
};


static const
ST_MSGTBL warning[]={
  {'Z', ID_STS_MESSAGE_WAR_REG_NO_ADJUSTMENT},
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
 * chk_operatorcall_level4();
 * chk_busystatus();
 * chk_cartridge();
 * chk_basestatus();
 * chk_warning();
 */
int chk_operatorcall_level1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;
  int msgid;
  
  ret=processstandardmsgcheck(p_sts, &operatelevel1[0], p_tbl->operator_call, sizeof(p_tbl->operator_call));
  
  if( *(p_sts->pMessageID) == ID_STS_MESSAGE_OC_CARTRIDGE_NONE )		// v2.4
  {
    if ( strncmp(p_tbl->dev, DEV_1284,4) )		// v2.4
      *(p_sts->pMessageID)=ID_STS_MESSAGE_CARTRIDGE_NONE;		// v2.4
  }	       
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_OUT21 	|| 
			*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_OUT22	||
			*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_OUT)
  {
  	msgid = *(p_sts->pMessageID);
	*p_sts->pMessageID = ID_STS_MESSAGE_OC_PAPER_OUT1;
  	ret = storeMessageID (p_sts, msgid);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_OUT3);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_OUT23 	|| 
			*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_OUT24)
  {
  	msgid = *(p_sts->pMessageID);
	*p_sts->pMessageID = ID_STS_MESSAGE_OC_PAPER_OUT1;
  	ret = storeMessageID (p_sts, msgid);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_OUT33);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM1 || *(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM1_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM1_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM03)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM03_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM1_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM04)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM04_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM1_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM2)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM1_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM2_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM05)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM05_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM2_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM06)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM03_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM2_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_PAPER_JAM07)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM04_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_PAPER_JAM2_3rd);
	ret = UNIQUESTS;
  }

  return(ret);
}


int chk_operatorcall_cartridge(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
#if 0
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
#endif
  return(ID_ERR_NO_ERROR);
}


int chk_operatorcall_level2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  ret=processstandardmsgcheck(p_sts, &operatelevel2[0], p_tbl->operator_call, sizeof(p_tbl->operator_call));
  return(ret);
}


static const
ST_MSGTBL cartridge_type[]={
  {'L', ID_STS_MESSAGE_OC_BLACK40},
  {'M', ID_STS_MESSAGE_OC_COLOR41},
  {'N', ID_STS_MESSAGE_OC_BLACK50},
  {'O', ID_STS_MESSAGE_OC_COLOR51},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_ip2200_type[]={
  {'B', ID_STS_MESSAGE_COLOR_CARTRIDGE},
  {'E', ID_STS_MESSAGE_COLOR_CARTRIDGE},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_ip2200[]={
  {'B', ID_STS_MESSAGE_OC_BLACK},
  {'E', ID_STS_MESSAGE_OC_COLOR},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_type_JP[]={
  {'L', ID_STS_MESSAGE_OC_BLACK7e},
  {'l', ID_STS_MESSAGE_OC_PHOTO_BLACK9},
  {'C', ID_STS_MESSAGE_OC_CYAN7e},
  {'M', ID_STS_MESSAGE_OC_MAGENTA7e},
  {'Y', ID_STS_MESSAGE_OC_YELLOW7e},
  {'c', ID_STS_MESSAGE_OC_PHOTO_CYAN7e},
  {'m', ID_STS_MESSAGE_OC_PHOTO_MAGENTA7e},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_type_OTH[]={
  {'L', ID_STS_MESSAGE_OC_BLACK8},
  {'l', ID_STS_MESSAGE_OC_PHOTO_BLACK5},
  {'C', ID_STS_MESSAGE_OC_CYAN8},
  {'M', ID_STS_MESSAGE_OC_MAGENTA8},
  {'Y', ID_STS_MESSAGE_OC_YELLOW8},
  {'c', ID_STS_MESSAGE_OC_PHOTO_CYAN8},
  {'m', ID_STS_MESSAGE_OC_PHOTO_MAGENTA8},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_ip4200[]={
  {'L', ID_STS_MESSAGE_COLOR_TYPE},
  {'l', ID_STS_MESSAGE_COLOR_TYPE},
  {'C', ID_STS_MESSAGE_COLOR_TYPE},
  {'M', ID_STS_MESSAGE_COLOR_TYPE},
  {'Y', ID_STS_MESSAGE_COLOR_TYPE},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_ip6600d[]={
  {'L', ID_STS_MESSAGE_COLOR_TYPE},
  {'C', ID_STS_MESSAGE_COLOR_TYPE},
  {'c', ID_STS_MESSAGE_COLOR_TYPE},
  {'M', ID_STS_MESSAGE_COLOR_TYPE},
  {'m', ID_STS_MESSAGE_COLOR_TYPE},
  {'Y', ID_STS_MESSAGE_COLOR_TYPE},
  {ENDTAG, 0}
};

static const
ST_MSGTBL color_ip7500[]={
  {'L', ID_STS_MESSAGE_COLOR_TYPE},
  {'c', ID_STS_MESSAGE_COLOR_TYPE},
  {'l', ID_STS_MESSAGE_COLOR_TYPE},
  {'M', ID_STS_MESSAGE_COLOR_TYPE},
  {'C', ID_STS_MESSAGE_COLOR_TYPE},
  {'m', ID_STS_MESSAGE_COLOR_TYPE},
  {'Y', ID_STS_MESSAGE_COLOR_TYPE},
  {ENDTAG, 0}
};

static const
ST_DEVCLR_TBL color_tbl_inkout[]={
  {"IP2200",  color_ip2200_type},
  {"IP4200",  color_ip4200},
  {"IP7500",  color_ip7500},
  {"IP6600D", color_ip6600d},
  {"MP500",   color_ip4200},
  {ENDTAG, 0}
};

static const
ST_OPMSGTBL msg_tbl_inkout[]={
  {ID_STS_MESSAGE_OC_INKOUT_TANK,
     {ID_STS_MESSAGE_OC_INKOUT_TANK_2nd,
      ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'I'}, 

  {ID_STS_MESSAGE_OC_INKOUT_TANK2,
     {ID_STS_MESSAGE_OC_INKOUT_TANK_2nd,
      ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'I'}, 

  {ID_STS_MESSAGE_OC_INKOUT_CART,
     {ID_STS_MESSAGE_OC_INKOUT_TANK_2nd,
      ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_INKOUT_CART_3rd,
      ID_STS_MESSAGE_NON},
     'I'}, 

  {ID_STS_MESSAGE_NON,
     {ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     ENDTAG}, 
};

static const
ST_DEVCLR_TBL color_tbl_op3[]={
  {"IP2200",  color_ip2200},
  {"IP4200",  color_ip4200},
  {"IP7500",  color_ip7500},
  {"IP6600D", color_ip6600d},
  {"MP500",   color_ip4200},
  {ENDTAG, 0}
};

static const
ST_OPMSGTBL msg_tbl_op3[]={
  {ID_STS_MESSAGE_OC_PLURALERROR_TANK,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_PLURALERROR_TANK_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'M'}, 

  {ID_STS_MESSAGE_OC_DIFFERENT_REGION_TANK,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_DIFFERENT_REGION_TANK_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'E'}, 

  {ID_STS_MESSAGE_OC_POSITION_MISMACH_TANK,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'P'}, 

  {ID_STS_MESSAGE_OC_UNINSTALLATION_TANK,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_UNINSTALLATION_TANK_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'E'}, 

  {ID_STS_MESSAGE_OC_REFILL,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_REFILL_3rd,
      ID_STS_MESSAGE_NON,	//fix 20070806
      //ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_NON},
     'R'}, 

  {ID_STS_MESSAGE_OC_REFILL2,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_REFILL2_3rd,
      ID_STS_MESSAGE_NON,	//fix 20070806
      //ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_NON},
     'R'}, 

  {ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_NO_RECOGNIZE_CART_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'E'}, 

  {ID_STS_MESSAGE_OC_REMAIN_UNKNOWN1,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_REMAIN_UNKNOWN1_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'R'}, 

  {ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2,
     {ID_STS_MESSAGE_COLOR,
      ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2_3rd,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     'R'}, 

  {ID_STS_MESSAGE_NON,
     {ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON,
      ID_STS_MESSAGE_NON},
     ENDTAG}, 
};


int chk_inkout(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int 		ret;
  int 		msgid;
  int 		color;
  int  		i, j, k;

  // The first message is inserted.
  ret=processstandardmsgcheck(p_sts, inkout, p_tbl->operator_call, sizeof(p_tbl->operator_call));
  if(ret==ID_ERR_NO_ERROR)
    return ID_ERR_NO_ERROR;

  // The corresponding message is acquired.
  for(msgid=0; msg_tbl_inkout[msgid].msgid!=ID_STS_MESSAGE_NON; msgid++)
    if(*(p_sts->pMessageID)==msg_tbl_inkout[msgid].msgid)
      break;
  if(msg_tbl_inkout[msgid].msgid == ID_STS_MESSAGE_NON)
  {
    p_sts->messageNum = 0;
    *(p_sts->pMessageID) = 0;
    return ID_ERR_NO_ERROR;
  }

  // The corresponding color is acquired.
  for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++)
    if(	!strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
      break;
  if(color_tbl_inkout[color].pr_name == ENDTAG)
  {
    p_sts->messageNum = 0;
    *(p_sts->pMessageID) = 0;
    return ID_ERR_NO_ERROR;
  }

  for(i=0; msg_tbl_inkout[msgid].id[i]!=ID_STS_MESSAGE_NON; i++)
  {
    if(msg_tbl_inkout[msgid].id[i] == ID_STS_MESSAGE_COLOR)
    {
      // The message since the second (color) is inserted.
      for(j=0; j<MAXINKNUM; j++)
      {
        if(p_tbl->ink[j].alert == msg_tbl_inkout[msgid].status)
        {
          for(k=0; color_tbl_inkout[color].color[k].status!=ENDTAG; k++)
            if(p_tbl->ink[j].color == color_tbl_inkout[color].color[k].status)
              break;
          if(color_tbl_inkout[color].color[k].status==ENDTAG)
          {
            p_sts->messageNum = 0;
            *(p_sts->pMessageID) = 0;
            return ID_ERR_NO_ERROR;
          }

          if(color_tbl_inkout[color].color[k].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE)
          {
            for(k=0; cartridge_type[k].status!=ENDTAG; k++)
              if(p_tbl->cartridge[j].type == cartridge_type[k].status)
                break;
  	        ret=storeMessageID(p_sts, cartridge_type[k].msgid);
	        if(ret != ID_ERR_NO_ERROR)
              return ret;
          }
          else if(color_tbl_inkout[color].color[k].msgid == ID_STS_MESSAGE_COLOR_TYPE)
          {
			//	v2.60
 			// The value of HRI is inserted in Lever_position. 
 			// Because the display of Lever position was deleted, it substitutes it. 
            if( p_tbl->lever_position == ID_HRI_JPN )
			{
              for(k=0; color_type_JP[k].status!=ENDTAG; k++)
                if(p_tbl->ink[j].color == color_type_JP[k].status)
                  break;
  	          ret=storeMessageID(p_sts, color_type_JP[k].msgid);
	          if(ret != ID_ERR_NO_ERROR)
                return ret;
			}
			else
			{
              for(k=0; color_type_OTH[k].status!=ENDTAG; k++)
                if(p_tbl->ink[j].color == color_type_OTH[k].status)
                  break;
  	          ret=storeMessageID(p_sts, color_type_OTH[k].msgid);
	          if(ret != ID_ERR_NO_ERROR)
                return ret;
			}
          }
          else
          {
  	        ret=storeMessageID(p_sts, color_tbl_inkout[color].color[k].msgid);
	        if(ret != ID_ERR_NO_ERROR)
              return ret;
          }
        }
      }
    }
    else
    {
      // The message since the second (Excluding the color) is inserted.
	  ret=storeMessageID(p_sts, msg_tbl_inkout[msgid].id[i]);
	  if(ret != ID_ERR_NO_ERROR)
        return ret;
    }
  }
  return UNIQUESTS;
}


int chk_operatorcall_level3(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;
  int msgid;
  int color;
  int i, j, k;

  // The first message is inserted.
  ret=processstandardmsgcheck(p_sts, operatelevel3, p_tbl->operator_call, sizeof(p_tbl->operator_call));
  if(ret==ID_ERR_NO_ERROR)
    return ID_ERR_NO_ERROR;

  // The corresponding message is acquired.
  for(msgid=0; msg_tbl_op3[msgid].msgid!=ID_STS_MESSAGE_NON; msgid++)
    if(*(p_sts->pMessageID)==msg_tbl_op3[msgid].msgid)
      break;
  if(msg_tbl_op3[msgid].msgid == ID_STS_MESSAGE_NON)
  {
    p_sts->messageNum = 0;
    *(p_sts->pMessageID) = 0;
    return ID_ERR_NO_ERROR;
  }

  // The corresponding color is acquired.
  for(color=0; color_tbl_op3[color].pr_name!=ENDTAG; color++)
    if(	!strncmp(p_tbl->pr_name, color_tbl_op3[color].pr_name, strlen(color_tbl_op3[color].pr_name)) ) 
      break;
  if(color_tbl_op3[color].pr_name == ENDTAG)
  {
    p_sts->messageNum = 0;
    *(p_sts->pMessageID) = 0;
    return ID_ERR_NO_ERROR;
  }

  for(i=0; msg_tbl_op3[msgid].id[i]!=ID_STS_MESSAGE_NON; i++)
  {
    if(msg_tbl_op3[msgid].id[i] == ID_STS_MESSAGE_COLOR)
    {
      // The message since the second (color) is inserted.
      for(j=0; j<MAXINKNUM; j++)
      {
        if(p_tbl->ink[j].alert == msg_tbl_op3[msgid].status)
        {
          for(k=0; color_tbl_op3[color].color[k].status!=ENDTAG; k++)
            if(p_tbl->ink[j].color == color_tbl_op3[color].color[k].status)
              break;
          if(color_tbl_op3[color].color[k].status==ENDTAG)
          {
            p_sts->messageNum = 0;
            *(p_sts->pMessageID) = 0;
            return ID_ERR_NO_ERROR;
          }
          if(color_tbl_op3[color].color[k].msgid == ID_STS_MESSAGE_COLOR_TYPE)
          {
			//	v2.60
 			// The value of HRI is inserted in Lever_position. 
 			// Because the display of Lever position was deleted, it substitutes it. 
            if( p_tbl->lever_position == ID_HRI_JPN )
			{
              for(k=0; color_type_JP[k].status!=ENDTAG; k++)
                if(p_tbl->ink[j].color == color_type_JP[k].status)
                  break;
  	          ret=storeMessageID(p_sts, color_type_JP[k].msgid);
	          if(ret != ID_ERR_NO_ERROR)
                return ret;
			}
			else
			{
              for(k=0; color_type_OTH[k].status!=ENDTAG; k++)
                if(p_tbl->ink[j].color == color_type_OTH[k].status)
                  break;
  	          ret=storeMessageID(p_sts, color_type_OTH[k].msgid);
	          if(ret != ID_ERR_NO_ERROR)
                return ret;
			}
          }
          else
          {
	        ret=storeMessageID(p_sts, color_tbl_op3[color].color[k].msgid);
	        if(ret != ID_ERR_NO_ERROR)
              return ret;
          }
       }
      }
    }
    else
    {
      // The message since the second (Excluding the color) is inserted.
	  ret=storeMessageID(p_sts, msg_tbl_op3[msgid].id[i]);
	  if(ret != ID_ERR_NO_ERROR)
        return ret;
    }
  }
  return UNIQUESTS;
}


int chk_operatorcall_level4(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;
  if((p_tbl->operator_call[0]==SPACE) || (p_tbl->operator_call[0]==UNJUSTVALUE)){
    return(ID_ERR_NO_ERROR);
  }
  ret=processstandardmsgcheck(p_sts, &operatelevel4[0], p_tbl->operator_call, sizeof(p_tbl->operator_call));
  if(ret == ID_ERR_NO_ERROR){
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_OTHER);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
    return(UNIQUESTS);
  }
  if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_CDR_GUIDE)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_CDR_GUIDE_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_CDR_GUIDE_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_OC_CDR_GUIDE2)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_CDR_GUIDE_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_OC_CDR_GUIDE2_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_CDR_GUIDE_PRINT)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_CDR_GUIDE_PRINT_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_CDR_GUIDE_PRINT_3rd);
	ret = UNIQUESTS;
  }
  else if (*(p_sts->pMessageID) == ID_STS_MESSAGE_CDR_GUIDE_PRINT2)
  {
  	ret = storeMessageID (p_sts, ID_STS_MESSAGE_CDR_GUIDE_PRINT_2nd);
	ret = storeMessageID (p_sts, ID_STS_MESSAGE_CDR_GUIDE_PRINT2_3rd);
	ret = UNIQUESTS;
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
  if ( !strncmp(p_tbl->dev, DEV_1284,4) )		// v2.4
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_CARTRIDGE_NONE);// v2.4 003-0105
  else
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_CARTRIDGE_NONE);	// v.2.3 010-1121 
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


int chk_warning(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int ret;

  ret=processIDcheck(warning, p_tbl->warning, sizeof(p_tbl->warning));
  if(ret != IDNOTFOUND){
    ret=storeMessageID(p_sts, ret);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  return(ID_ERR_NO_ERROR);
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
	    ret=chkoccuralert(p_tbl, *(p_tbl->warning+k));
	    if(ret != OCCUR){
          if( p_tbl->lever_position == ID_HRI_JPN )
	        ret=storeMessageID(p_sts, inklowpart1[i].msgid);
          else
	        ret=storeMessageID(p_sts, inklowpart1_type_OTH[i].msgid);
	      if(ret != ID_ERR_NO_ERROR){
	        return(ret);
	      }
	    }
      }
    }
  }
  if(p_sts->messageNum != (inklow_storeposit+1)){
    *((p_sts->pMessageID)+inklow_storeposit)=ID_STS_MESSAGE_WAR_INKLOW_PRE;
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_WAR_INKLOW_AFTER);
    if(ret != ID_ERR_NO_ERROR){
      return(ret);
    }
  }
  else {
    p_sts->messageNum--;
  }
  return(ID_ERR_NO_ERROR);
}


static const
ST_MSGTBL inklow_cartridge_type[]={
  {'L', ID_STS_MESSAGE_WAR_INKLOW_BLACK40},
  {'M', ID_STS_MESSAGE_WAR_INKLOW_COLOR41},
  {'N', ID_STS_MESSAGE_WAR_INKLOW_BLACK50},
  {'O', ID_STS_MESSAGE_WAR_INKLOW_COLOR51},
  {ENDTAG, 0}
};

int chk_inklow_part2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
  int  i,j,k;
  int  ret;
  int  inklow_storeposit;
  char cartridge_type;

  inklow_storeposit=p_sts->messageNum;
  p_sts->messageNum++;

  for(i=0; inklowpart2[i].status!=ENDTAG; i++){
    for(k=0; (k<sizeof(p_tbl->warning)) && (*(p_tbl->warning+k)!=SPACE); k++){
      if(inklowpart2[i].status == *(p_tbl->warning+k)){
        if(inklowpart2[i].msgid == ID_STS_MESSAGE_WAR_INKLOW_BLACK40 )
          cartridge_type = p_tbl->cartridge[0].type;
        else
          cartridge_type = p_tbl->cartridge[1].type;

        for(j=0; inklow_cartridge_type[j].status!=ENDTAG; j++)
          if(cartridge_type == inklow_cartridge_type[j].status)
            break;
        ret=storeMessageID(p_sts, inklow_cartridge_type[j].msgid);
	    if(ret != ID_ERR_NO_ERROR){
	      return(ret);
        }
      }
    }
  }

  if(p_sts->messageNum != (inklow_storeposit+1)){
    *((p_sts->pMessageID)+inklow_storeposit)=ID_STS_MESSAGE_WAR_INKLOW_40_PRE;
    ret=storeMessageID(p_sts, ID_STS_MESSAGE_WAR_INKLOW_40_AFTER);
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

/*
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
*/

static int chkoccuralert(ST_CUPSSTS *p_tbl, char chkchr)
{
  int i;

  for(i=0; i<MAXINKNUM; i++){
	if( p_tbl->ink[i].color == chkchr && p_tbl->ink[i].alert == 'I' ){
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
