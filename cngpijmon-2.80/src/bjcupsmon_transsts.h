/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2007
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * macro...
 */
#define SETSTATUSNUM    6
#define STANDARDMSGNUM  16
#define MAXCHKSTS       17
//#define MAXCHKSTS       16
//#define MAXCHKSTS       14
#define MAXCOLORNUM     10
#define MAXINKNUM       8		// V2.3 6->8
#define MAXCARTRIDGENUM 2

#define SKIPCHKFUNC     9

#define UNIQUESTS       -10
#define SERVICECALL     -11
#define IDNOTFOUND      -12
#define OCCUR           -13
#define NOTINKOUT       -14
#define INKLOW          -15
#define INKOUT          -16
#define INKUNKNOWN      -17
#define OTHERMESSAGENO  -18


#define SPACE           0x20
#define UNJUSTVALUE     '*'
#define ENDTAG          '\0'
#define SCANNERDETECT   '2'
#define TESTPRINTNOW    'T'
#define DUMMYSCANNER    '3'
#define ALLCOLORCHAR    "KkLlcmCMYrNBEGbe"	//  add 'l' 'r'(2.4) 'N'(2.5) 'Gbg'(2.7)

#define DEV_1284	"PAR "
#define DEV_USB		"USB "
#define DEV_1394	"1394"
#define DEV_CHARSIZE	4

#define	OPMSGTBL_ID_MAX		4
#define	INKLVL_UNKOWN	"UK"
#define	INKLVL_UNKOWNUUU	"UUU"
#define	INKLVL_UNSETTANK	"NNN"


//Ver.2.80
#define	DONOT_CARE		1
#define	AUTUMN_06		2
#define	SPRING_07		3

//Ver.2.80
#define	AUTOSHEET_FEEDER		1
#define	REAR_TRAY				2

//Ver.2.80
#define	NO_SUPPLY		1
#define	FRONT_FEEDER	2
#define	CASSEETTE		3
#define	FRONT_TRAY		4

//Ver.2.70
#define	IS_RESUME		1
#define	IS_OK			2
#define	IS_START		3

/*
 * struct...
 */
typedef struct {
  char header[4];
  char dev[4];
  char pr_name[16];
  char base_stat[2];
  char busy_stat;
  char job_stat;
  struct {
	char type;
	char exchange;
  }cartridge[2];
  struct {
	char color;
	char alert;
	char fill[3];
	char resv;
  }ink[8];
  char ink_check;
//Ver.2.70
  char destination;
//  char lever_position;
  char warning[12];
  char operator_call[12];
  char service_call[4];
//Ver.2.70
  char lever_position;
  char reserve[2];
  char cr;
}ST_CUPSSTS;

typedef struct{
  char* dev;
  gint id;
}ST_DEVID_TBL;

typedef struct{
  char status;
  int msgid;
}ST_MSGTBL;

typedef struct{
  char status;
  const ST_MSGTBL *region;
}ST_REGION_TBL;

typedef struct{
  char*           pr_name;
  const ST_MSGTBL *color;
}ST_DEVCLR_TBL;

typedef struct{
  int  msgid;
  int  id[OPMSGTBL_ID_MAX];
  char status;
}ST_OPMSGTBL;

typedef struct{
  char*	pr_name;
  int 	is_rsm_button;
}ST_RESUMEBUTTON_TBL;

typedef struct{
  char*	pr_name;
  int 	is_frontsupply;
}ST_FRONTSUPPLAY_TBL;

typedef struct{
  char*	pr_name;
  int 	is_rearsupply;
}ST_REARSUPPLAY_TBL;

typedef struct{
  char*	pr_name;
  int 	is_inkremain_sequence;
}ST_INKREMAIN_SEQUENCE_TBL;


typedef int (*SETSTATUSFUNC) (ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);


/*
 * prototype...
 */
int chk_servicecall(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_operatorcall_level1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_operatorcall_cartridge(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_operatorcall_level2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_inkout(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_operatorcall_level3(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_operatorcall_level4(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_busystatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_cartridge(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
/* Ver.2.80 */
int chk_jobstatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_basestatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_warning(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_inklow_part1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_inkunknow(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_inkoutwar_part1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_inklow_part2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_noinkcheck(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_noinkcheck2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
