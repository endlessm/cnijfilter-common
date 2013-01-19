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
#include"bjcupsmon_common.h"
#include"bjcupsmon_transsts.h"
#include"bjcupsmon_data.h"
#include"bjcupsmon_datastrptr.h"

static int processIDcheck(const ST_MSGTBL *p_msgtbl, char *p_status, int status_size );
static int storeMessageID(ST_PrinterStatus *p_sts, int msgID);
static int set_StringPattern(ST_CUPSSTS *p_tbl, char *p_status, int status_size, ST_MODEL_PATTERN_TBL *model_pattern_table);
static int common_storeMessageIDs(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts, char *operator_call, int string_pattern);
//static int set_doc_StringPattern(ST_CUPSSTS *p_tbl, char *p_status, int status_size);
//static int set_djs_StringPattern(ST_CUPSSTS *p_tbl, char *p_status, int status_size);
//static int set_dbs_StringPattern(ST_CUPSSTS *p_tbl, char *p_status, int status_size);
//static int set_dws_StringPattern(ST_CUPSSTS *p_tbl, char *p_status, int status_size);
//static int processstandardmsgcheck(ST_PrinterStatus *p_sts, const ST_MSGTBL *p_msgtbl, char *p_status, int status_size);


/*
 * In a service call, other processings are not performed.
 */
int chk_servicecall(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
	int ret = ID_ERR_ARGUMENT_ERR;
	int string_pattern;

  /* if(p_tbl->service_call[0]==SPACE){  condition change Ver.3.80 */ 
  if(p_tbl->service_call2 == SPACE){
    return(ID_ERR_NO_ERROR);
  }

	//for Ver.3.00 'I' 'J'
	if(p_tbl->service_call[1]==SPACE){
		string_pattern = set_StringPattern(p_tbl, p_tbl->service_call, 1, (ST_MODEL_PATTERN_TBL*)dsc_model_pattern_table);
		//for Other DSC
		if((p_tbl->service_call[0]!=SPACE) && (string_pattern < 0)){
			string_pattern = COMMON_SERIVICE_ERROR_PATTERN;
		}
	
		if( string_pattern == -1 )
			return ID_ERR_NO_ERROR;
	
		ret = common_storeMessageIDs(p_tbl, p_sts, p_tbl->service_call, string_pattern);
		if(ret != ID_ERR_NO_ERROR){
			return(ret);
		}
	}
	//for Ver.3.10 and Ver.3.00 except 'I' 'J'
	else{
		string_pattern = set_StringPattern(p_tbl, &p_tbl->service_call2, 1, (ST_MODEL_PATTERN_TBL*)dsc_model_pattern_table);
		//for Other DSC
		if((p_tbl->service_call[0]!=SPACE) && (string_pattern < 0)){
			string_pattern = COMMON_SERIVICE_ERROR_PATTERN;
		}
	
		if( string_pattern == -1 )
			return ID_ERR_NO_ERROR;
	
		ret = common_storeMessageIDs(p_tbl, p_sts, &p_tbl->service_call2, string_pattern);
		if(ret != ID_ERR_NO_ERROR){
			return(ret);
		}
	}
    return(SERVICECALL);

}


/*
 * The number of what is displayed among the message ID acquired
 * with the following functions is one. (Except ink out)
 *
 * chk_operatorcall_level1();
 * chk_busystatus();
 * chk_jobstatus(); //chk_basestatus();
 */
int chk_operatorcall_level1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
	int ret = ID_ERR_ARGUMENT_ERR;
	int string_pattern,k,q;
	int HeadProtect_Flag = 0;
	int CoverOpen_flag = 0;

	
	/* Ver.3.10 for DOC=1200 & DWS=1900 --> DBS=(A-35) */
	for(k=0; (k<sizeof(p_tbl->warning)) && (*(p_tbl->warning+k)!=SPACE); k++){
		if( p_tbl->warning[k] == 'P' ) {
			HeadProtect_Flag = 1;
		}
	}

	/* Ver.3.60 for check Cover Open */
	for(k=0; (k<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+k)!=SPACE); k++){
		if( p_tbl->operator_call[k] == 'v') {
			if( k == 0 )	CoverOpen_flag = 1;
			else			CoverOpen_flag = 2;
		}
	}

	/* Ver.3.00 for DBS=CC & DOC=1200 => DJS=(A-6) & DBS=NO */
	for(k=0; (k<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+k)!=SPACE); k++){
		/* Ver.3.10 DOC=1200 & DOC=1600 --> delete DOC=1600 but DWS=1570 */
		if( (p_tbl->operator_call[k] != ' ') && (p_tbl->operator_call[k] != 'v') && (CoverOpen_flag == 1) ){
			p_tbl->operator_call[k] = ' ';
		}
		/* Ver.3.60 DOC=1687(1202) & DOC=1200 --> delete DOC=1200 */
		if( (p_tbl->operator_call[k] == 'v') && (CoverOpen_flag == 2) ){
			p_tbl->operator_call[k] = ' ';
		}
		/* Ver.3.10 DOC=1200 & DBS=CC --> DOS=V (A-6) */
		if( (p_tbl->operator_call[k] == 'v') && (p_tbl->busy_stat == 'D') ){
			p_tbl->operator_call[k] = 'V';
		}
		/* Ver.3.80 DOC=1200 & DBS=TC --> DOS=V (A-?) */
		if( (p_tbl->operator_call[k] == 'v') && (p_tbl->busy_stat == 'N') ){
			p_tbl->operator_call[k] = 'G';
		}
		/* Ver.3.10 DOC=1200 & DWS=1900 --> DBS=P (A-35) */
		if( (p_tbl->operator_call[k] == 'v') && (HeadProtect_Flag == 1) ){
			p_tbl->operator_call[k] = 'O';
		}
	}

	//multi DOC care DOC:1200,1600 etc
	for(q=0; (q<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+q)!=SPACE); q++)
	{
		string_pattern = set_StringPattern(p_tbl, p_tbl->operator_call+q, 1, (ST_MODEL_PATTERN_TBL*)doc_model_pattern_table);
		//string_pattern = set_StringPattern(p_tbl, p_tbl->operator_call, sizeof(p_tbl->operator_call), (ST_MODEL_PATTERN_TBL*)doc_model_pattern_table);
		//for Other DOC
		if((p_tbl->operator_call[0]!=SPACE) && (string_pattern < 0)){
			/* add for Error Code Ver.3.80 */
			ret=storeMessageID(p_sts, ID_STS_MESSAGE_ERROR_COMMON_NUMBER);
			ret=storeMessageID(p_sts, ID_STS_MESSAGE_OC_LCDPANEL);
			if(ret != ID_ERR_NO_ERROR){
				return(ret);
			}
			return(UNIQUESTS);
		}
		
		if( string_pattern == -1 )
			return ID_ERR_NO_ERROR;

		ret = common_storeMessageIDs(p_tbl, p_sts, p_tbl->operator_call+q, string_pattern);
	}

	if(ret != ID_ERR_NO_ERROR)
		return(ret);
	else
		return(UNIQUESTS);

}

/********************************************************************/
/*                                                                  */
/*  for Ver.3.10 for Other Operarion                                */
/*  for messeage "The printer is performing another operation.!"    */
/*  Priority 1st                                                    */
/*                                                                  */
/********************************************************************/
int chk_other_operation(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{

	int ret = ID_ERR_ARGUMENT_ERR;
	int dbs_pict_disable_pattern=0;

	dbs_pict_disable_pattern = set_StringPattern(p_tbl, &p_tbl->busy_stat, sizeof(p_tbl->busy_stat), (ST_MODEL_PATTERN_TBL*)dbs_pict_disable_pattern_table);
	if( dbs_pict_disable_pattern > 0 ){
		ret=storeMessageID(p_sts, ID_STS_MESSAGE_BUSY_PRINTER_USED);
		if(ret != ID_ERR_NO_ERROR)
			return(ret);
		else
			return(OTHERMESSAGENO);
	}

  return(ret);

}

/*****************************************/
/*                                       */
/*  for Ver.3.10 for Network             */
/*  for messeage "Other PC Printing!"    */
/*                                       */
/*****************************************/
int chk_otheruser_use(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{

	int ret = ID_ERR_ARGUMENT_ERR;

	if( p_sts->user_otherflag == NETWORK_OTHER_USE ){
		ret=storeMessageID(p_sts, ID_STS_MESSAGE_OTHER_USE);
		if(ret != ID_ERR_NO_ERROR)
			return(ret);
	}

  return(ret);

}


int chk_busystatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{

	int k,ret = ID_ERR_ARGUMENT_ERR;
	int string_pattern,i,j;
	int CoverOpen_Flag = 0;
//	int HeadProtect_Flag = 0;

	/* Ver.3.00 for DBS=CC & DOC!=1200 --> DJS=(A-34) & DBS=NO */
	for(k=0; (k<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+k)!=SPACE); k++){
		if( p_tbl->operator_call[k] == 'v' ) {
			CoverOpen_Flag = 1;
		}
	}

	if( ( p_tbl->busy_stat == 'D' ) && ( CoverOpen_Flag == 0 ) ){
		p_tbl->busy_stat = ' ';
		p_tbl->job_stat = 'w';
	}

//	/* Ver.3.10 for DOC=1200 & DWS=1900 --> DBS=P (A-35) */
//	for(k=0; (k<sizeof(p_tbl->warning)) && (*(p_tbl->warning+k)!=SPACE); k++){
//		if( p_tbl->warning[k] == 'P' ) {
//			HeadProtect_Flag = 1;
//		}
//	}
//	if( ( CoverOpen_Flag == 1 ) && ( HeadProtect_Flag == 1 ) ){
//		p_tbl->busy_stat = 'H';
//	}


	string_pattern = set_StringPattern(p_tbl, &p_tbl->busy_stat, sizeof(p_tbl->busy_stat), (ST_MODEL_PATTERN_TBL*)dbs_model_pattern_table);
	//string_pattern = set_dbs_StringPattern(p_tbl, &p_tbl->busy_stat, sizeof(p_tbl->busy_stat));
	if( string_pattern < 0 )
		return string_pattern;

	for(j=0; string_table[j].pattern_id!=ID_STS_MESSAGE_NON; j++){
		if( string_table[j].pattern_id == string_pattern ){
			for(i=0; string_table[j].message_id[i]!=ID_STS_MESSAGE_NON; i++){
				ret=storeMessageID(p_sts, string_table[j].message_id[i]);
				if(ret != ID_ERR_NO_ERROR){
					return(ret);
				}
				ret = UNIQUESTS;
			}
		}
	}

	//2.00.01.010 another Interface use :other message doesn't appear.
	if( p_tbl->busy_stat == 'I' )
		ret = OTHERMESSAGENO;

  return(ret);

}

/* for Ver.2.80 */
int chk_jobstatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
	int ret = ID_ERR_ARGUMENT_ERR;
	int string_pattern,i,j;


	string_pattern = set_StringPattern(p_tbl, &p_tbl->job_stat, sizeof(p_tbl->job_stat), (ST_MODEL_PATTERN_TBL*)djs_model_pattern_table);
	//string_pattern = set_djs_StringPattern(p_tbl, &p_tbl->job_stat, sizeof(p_tbl->job_stat));
	if( string_pattern < 0 )
		return string_pattern;

	for(j=0; string_table[j].pattern_id!=ID_STS_MESSAGE_NON; j++){
		if( string_table[j].pattern_id == string_pattern ){
			for(i=0; string_table[j].message_id[i]!=ID_STS_MESSAGE_NON; i++){
				ret=storeMessageID(p_sts, string_table[j].message_id[i]);
				if(ret != ID_ERR_NO_ERROR){
					return(ret);
				}
				ret = UNIQUESTS;
			}
		}
	}

  return(ret);

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
 * chk_noinkcheck();
 */
int chk_inklow_part1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
	int Tflag = 0;
	int ret = ID_ERR_ARGUMENT_ERR;
	int string_pattern,i,k,q,x;
	char warning[13];
	char warning1[13];
	char warning2[13];


	for(i=0; i<sizeof(warning); i++)	warning[i] = SPACE;
	for(i=0; i<sizeof(warning1); i++)	warning1[i] = SPACE;
	for(i=0; i<sizeof(warning2); i++)	warning2[i] = SPACE;
	for(i=0; i<sizeof(warning); i++)	warning[i] = p_tbl->warning[i];

	/* Ver.3.00 for DWS=1499 & DWS=1500 */
	for(i=0; i<sizeof(warning); i++){
		if( warning[i] == 't'){
			warning[i] = 'T';
			i++;
		}
	}

	for(i=0,x=0; i<( sizeof(warning)) && ((*(warning+i)!=SPACE)); i++){
		if( ((warning[i] == 'T') && (Tflag == 1)) ){
			Tflag = 1;
		}
		else{
			warning1[x] = warning[i];
			x++;
		}
		if( (warning[i] == 'T') && (Tflag == 0) ){
			Tflag = 1;
		}
	}

	/* Ver.3.00 for DOC=1600(u) & DWS=1570(f) */
	for(k=0; (k<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+k)!=SPACE); k++){
		if( p_tbl->operator_call[k] == 'u' ){
			for(q=0,x=0; (q<sizeof(warning1)) && (*(warning1+q)!=SPACE); q++){
				if( warning1[q] != 'F' ){
					warning2[x] = warning1[q];
					x++;
				}
			}
		}
		else{
			for(i=0; i<sizeof(warning2); i++)
				warning2[i] = warning1[i];
		}
	}
	/* no operator call */
	if( *(p_tbl->operator_call) == SPACE )
	{
		for(i=0; i<sizeof(warning2); i++)
			warning2[i] = warning1[i];
	}

	//multi DWS care DWS:1500,1570 etc
	for(q=0; (q<sizeof(warning2)) && (*(warning2+q)!=SPACE); q++)
	{
		string_pattern = set_StringPattern(p_tbl, warning2+q, 1, (ST_MODEL_PATTERN_TBL*)dws_model_pattern_table);
		//string_pattern = set_StringPattern(p_tbl, tempwarning, sizeof(tempwarning), (ST_MODEL_PATTERN_TBL*)dws_model_pattern_table);
		if( string_pattern == -1 )
			return string_pattern;

		ret = common_storeMessageIDs(p_tbl, p_sts, warning2+q, string_pattern);
	}

	if(ret != ID_ERR_NO_ERROR)
		return(ret);
	else
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

//for Ver.2.70
//decide with CTK:SETZ and CIR:UK 
int chk_noinkcheck2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
	int ret = ID_ERR_ARGUMENT_ERR;
	int string_pattern,i,q;
	int msg_flag = 0;
	char warning[12];


	for(i=0; i<sizeof(warning); i++)	warning[i] = SPACE;

	//DOC:1683 CTK:M,RUK,/,C,SETZ CIR:M,UK,/,C,UK
	///* operator_call nothing --> return */
	//for(k=0; (k<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+k)!=SPACE); k++){
	//	return ID_ERR_NO_ERROR;
	//}

	for(i=0; i<8; i++){
		if( (p_tbl->ink[i].alert == 'Z') && (p_tbl->ink[i].fill[0] == 'U') && (p_tbl->ink[i].fill[1] == 'K') ){
			msg_flag = 1;
			warning[0] = 'Z';
		}
	}
	if( msg_flag == 0 )
		return(ID_ERR_NO_ERROR);

	//multi DWS
	for(q=0; (q<sizeof(warning)) && (*(warning+q)!=SPACE); q++)
	{
		string_pattern = set_StringPattern(p_tbl, warning+q, 1, (ST_MODEL_PATTERN_TBL*)dws_model_pattern_table);
		//string_pattern = set_StringPattern(p_tbl, warning, sizeof(warning), (ST_MODEL_PATTERN_TBL*)dws_model_pattern_table);
		if( string_pattern == -1 )
			return string_pattern;

		ret = common_storeMessageIDs(p_tbl, p_sts, warning+q, string_pattern);
	}

	if(ret != ID_ERR_NO_ERROR)
		return(ret);
	else
		return(ID_ERR_NO_ERROR);

}

//Ver.3.00
int set_pictareaInfo(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts)
{
	int doc_unknownicon_draw_pattern=0;
	int doc_pict_disable_pattern=0;
	int dbs_pict_disable_pattern=0;
	int doc_icon_delete_pattern=0;
	int string_pattern=0,q;

	//initialize
	p_sts->disablepictarea_drawflag = 0;
	p_sts->icon_deleteflag = 0;
	p_sts->disablepictarea_drawflag = 0;

	//multi DOC care DOC:1200,1600 etc
	for(q=0; (q<sizeof(p_tbl->operator_call)) && (*(p_tbl->operator_call+q)!=SPACE); q++)
	{
		//for pict area disable
		doc_pict_disable_pattern = set_StringPattern(p_tbl, p_tbl->operator_call+q, 1, (ST_MODEL_PATTERN_TBL*)doc_pict_disable_pattern_table);
		string_pattern = set_StringPattern(p_tbl, p_tbl->operator_call+q, 1, (ST_MODEL_PATTERN_TBL*)doc_model_pattern_table);
		//for Other DOC B-1(H:independent) or L-4
		if( (doc_pict_disable_pattern > 0) || (string_pattern == IDNOTFOUND) )
			p_sts->disablepictarea_drawflag = 1;

		//for icon delete
		doc_icon_delete_pattern = set_StringPattern(p_tbl, p_tbl->operator_call+q, 1, (ST_MODEL_PATTERN_TBL*)doc_icon_delete_pattern_table);
		if( doc_icon_delete_pattern > 0 )
			p_sts->icon_deleteflag = 1;

		//for unknown icon
		doc_unknownicon_draw_pattern = set_StringPattern(p_tbl, p_tbl->operator_call+q, 1, (ST_MODEL_PATTERN_TBL*)doc_unknownicon_draw_pattern_table);
		//for Other DOC B-36(f)/B-38(w)
		if( doc_unknownicon_draw_pattern > 0 )
			p_sts->unknownicon_drawflag = 1;
	}

	dbs_pict_disable_pattern = set_StringPattern(p_tbl, &p_tbl->busy_stat, sizeof(p_tbl->busy_stat), (ST_MODEL_PATTERN_TBL*)dbs_pict_disable_pattern_table);
	if( dbs_pict_disable_pattern > 0 )
		p_sts->disablepictarea_drawflag = 1;


  return(ID_ERR_NO_ERROR);
}


// for common_storeMessageIDs for Ver.3.00
static int common_storeMessageIDs(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts, char *operator_call, int string_pattern)
{
	int i,j,k,m,docstr,color,type;
	int ret = ID_ERR_ARGUMENT_ERR;


	// The corresponding color is acquired.
	for(color=0; color_tbl_inkout[color].pr_name!=ENDTAG; color++){
		if(	!strncmp(p_tbl->pr_name, color_tbl_inkout[color].pr_name, strlen(color_tbl_inkout[color].pr_name)) ) 
			break;
	}
	if(color_tbl_inkout[color].pr_name == ENDTAG)
		return ret;

	// The corresponding type is acquired.
	for(type=0; ink_type_tbl[type].pr_name!=ENDTAG; type++){
		if( !strncmp(p_tbl->pr_name, ink_type_tbl[type].pr_name, strlen(ink_type_tbl[type].pr_name)) ) 
			break;
	}
	if(ink_type_tbl[type].pr_name == ENDTAG)
		return ret;


	for(m=0; string_table[m].pattern_id!=ID_STS_MESSAGE_NON; m++){
		if( string_table[m].pattern_id == string_pattern ){
			for(i=0; string_table[m].message_id[i]!=ID_STS_MESSAGE_NON; i++){
				// The message since the second (color) is inserted.
				if( (string_table[m].message_id[i]==ID_STS_MESSAGE_COLOR) || (string_table[m].message_id[i]==ID_STS_MESSAGE_UNKNOWN_COLOR) ){
					for(j=0; j<MAXINKNUM; j++)
					{
						int x,n;

						for(docstr=0; ctk_tbl[docstr].status!=ENDTAG; docstr++)
						{
							if(ctk_tbl[docstr].status == *operator_call)
							//if(ctk_tbl[docstr].status == p_tbl->operator_call[q])
							{
								//printf("p_tbl->ink[j].alert = %s\n", &p_tbl->ink[j].alert);
								//printf("msg_tbl_inkout[msgid].status = %s\n", &msg_tbl_inkout[msgid].status);
								//CTK check --> decide ink
								if(p_tbl->ink[j].alert == ctk_tbl[docstr].status_ctk)
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

									//for Dispo
									if(color_tbl_inkout[color].color[k].msgid == ID_STS_MESSAGE_COLOR_CARTRIDGE)
									{
										for(x=0; ink_type_tbl[type].inktype[0].region[x].status!=ENDTAG; x++){
											if(p_tbl->cartridge[j].type == ink_type_tbl[type].inktype[0].region[x].status)
												break;
										}
										//Ver.3.40 error check
										if( ink_type_tbl[type].inktype[0].region[x].status == ENDTAG )
											return ID_ERR_ARGUMENT_ERR;

										/* Ver.3.00 for model switch */
										for(n=0; ink_type_tbl[type].inktype[n].region[x].status!=ENDTAG; n++){
											if( ink_type_tbl[type].inktype[n].status == p_tbl->destination )
												break;
										}
										//Ver.3.40 error check
										if( ink_type_tbl[type].inktype[n].region[x].status == ENDTAG )
											return ID_ERR_ARGUMENT_ERR;

										if( string_table[m].message_id[i]==ID_STS_MESSAGE_UNKNOWN_COLOR )
											n = 0;	//cartridge_type1_ZZZ
									}
									//for Independent Ink
									else
									{
										//Decide n : region  for Ver.3.00
										for(n=0; ink_type_tbl[type].inktype[n].status != ENDTAG; n++){
											if( ink_type_tbl[type].inktype[n].status == p_tbl->destination )
												break;
										}
										//Ver.3.40 error check
										if( ink_type_tbl[type].inktype[n].status == ENDTAG )
											return ID_ERR_ARGUMENT_ERR;

										//Decide x : ink  for Ver.3.00
										for(x=0; ink_type_tbl[type].inktype[n].region[x].status != ENDTAG; x++){
											if( ink_type_tbl[type].inktype[n].region[x].status == color_tbl_inkout[color].color[k].status )
												break;
										}
										//Ver.3.40 error check
										if( ink_type_tbl[type].inktype[n].region[x].status == ENDTAG )
											return ID_ERR_ARGUMENT_ERR;

									}
									//for not Independent Ink

									ret=storeMessageID(p_sts, ink_type_tbl[type].inktype[n].region[x].msgid);
									if(ret != ID_ERR_NO_ERROR)
										return ret;
								}
							}
						}
					}
				}
				else{
					int r,tmp_msgid = -1;
					
					//message change for Printer Region(PDR)
					for(r=0; msg_cnv_pdr[r].status!=ENDTAG ;r++){
						if( (p_tbl->prnregion == msg_cnv_pdr[r].status) && ( string_table[m].message_id[i] == msg_cnv_pdr[r].before_msgid ) ){
							tmp_msgid = msg_cnv_pdr[r].after_msgid;
							break;
						}
						tmp_msgid = string_table[m].message_id[i];
					}
					ret=storeMessageID(p_sts, tmp_msgid);
				}
			}
		}
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


// for String Pattern for Ver.3.00
static int set_StringPattern(ST_CUPSSTS *p_tbl, char *p_status, int status_size, ST_MODEL_PATTERN_TBL *model_pattern_table)

{
  int i=0,j=0;
  int str_pattern = -1;


	for(i=0; model_pattern_table[i].pr_name!=ENDTAG; i++){
		if(	strncmp(p_tbl->pr_name, model_pattern_table[i].pr_name, strlen(model_pattern_table[i].pr_name)) == 0 ) {
			for(j=0; model_pattern_table[i].model_pattern[j].status!=ENDTAG; j++){
				str_pattern=processIDcheck(&(model_pattern_table[i].model_pattern[j]), p_status, status_size);
				//printf("set_StringPattern@ i, j, str_pattern : %d %d %d\n",i,j,str_pattern);
				break;
			}
		}
	}

	return(str_pattern);
} 


#if 0
// for DOC String Pattern for Ver.3.00
static int set_doc_StringPattern(ST_CUPSSTS *p_tbl, char *p_status, int status_size)

{
  int i=0,j=0;
  int str_pattern = -1;

	for(i=0; doc_model_pattern_table[i].pr_name!=ENDTAG; i++){
		if(	strncmp(p_tbl->pr_name, doc_model_pattern_table[i].pr_name, strlen(doc_model_pattern_table[i].pr_name)) == 0 ) {
			for(j=0; doc_model_pattern_table[i].model_pattern[j].status!=ENDTAG; j++){
				str_pattern=processIDcheck(&(doc_model_pattern_table[i].model_pattern[j]), p_status, status_size);
				//printf("i, j, str_pattern : %d %d %d\n",i,j,str_pattern);
				break;
			}
		}
	}

	return(str_pattern);
} 

// for DJS String Pattern for Ver.3.00
static int set_djs_StringPattern(ST_CUPSSTS *p_tbl, char *p_status, int status_size)

{
  int i=0,j=0;
  int str_pattern = -1;

	for(i=0; djs_model_pattern_table[i].pr_name!=ENDTAG; i++){
		if(	strncmp(p_tbl->pr_name, djs_model_pattern_table[i].pr_name, strlen(djs_model_pattern_table[i].pr_name)) == 0 ) {
			for(j=0; djs_model_pattern_table[i].model_pattern[j].status!=ENDTAG; j++){
				str_pattern=processIDcheck(&(djs_model_pattern_table[i].model_pattern[j]), p_status, status_size);
				//printf("set_djs_StringPattern : i, j, str_pattern : %d %d %d\n",i,j,str_pattern);
				break;
			}
		}
	}

	return(str_pattern);
} 

// for DBS String Pattern for Ver.3.00
static int set_dbs_StringPattern(ST_CUPSSTS *p_tbl, char *p_status, int status_size)

{
  int i=0,j=0;
  int str_pattern = -1;

	for(i=0; dbs_model_pattern_table[i].pr_name!=ENDTAG; i++){
		if(	strncmp(p_tbl->pr_name, dbs_model_pattern_table[i].pr_name, strlen(dbs_model_pattern_table[i].pr_name)) == 0 ) {
			for(j=0; dbs_model_pattern_table[i].model_pattern[j].status!=ENDTAG; j++){
				str_pattern=processIDcheck(&(dbs_model_pattern_table[i].model_pattern[j]), p_status, status_size);
				//printf("set_dbs_StringPattern : i, j, str_pattern : %d %d %d\n",i,j,str_pattern);
				break;
			}
		}
	}

	return(str_pattern);
} 

// for DWS String Pattern for Ver.3.00
static int set_dws_StringPattern(ST_CUPSSTS *p_tbl, char *p_status, int status_size)

{
  int i=0,j=0;
  int str_pattern = -1;

	for(i=0; dws_model_pattern_table[i].pr_name!=ENDTAG; i++){
		if(	strncmp(p_tbl->pr_name, dws_model_pattern_table[i].pr_name, strlen(dws_model_pattern_table[i].pr_name)) == 0 ) {
			for(j=0; dws_model_pattern_table[i].model_pattern[j].status!=ENDTAG; j++){
				str_pattern=processIDcheck(&(dws_model_pattern_table[i].model_pattern[j]), p_status, status_size);
				//printf("i, j, dws_str_pattern : %d %d %d\n",i,j,str_pattern);
				break;
			}
		}
	}

	return(str_pattern);
} 
#endif

//static int processstandardmsgcheck(ST_PrinterStatus *p_sts, const ST_MSGTBL *p_msgtbl, char *p_status, int status_size)
//{
//  int ret;
//
//  ret=processIDcheck(p_msgtbl, p_status, status_size);
//  if(ret != IDNOTFOUND){
//    ret=storeMessageID(p_sts, ret);
//    if(ret != ID_ERR_NO_ERROR){
//      return(ret);
//    }
//    return(UNIQUESTS);
//  }
//  return(ID_ERR_NO_ERROR);
//}

