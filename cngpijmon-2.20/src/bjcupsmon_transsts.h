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

/*
 * macro...
 */
#define SETSTATUSNUM    6
#define STANDARDMSGNUM  16
#define MAXCHKSTS       12
#define MAXCOLORNUM     10
#define MAXINKNUM       6
#define MAXCARTRIDGENUM 2

#define SKIPCHKFUNC     8

#define UNIQUESTS       -10
#define SERVICECALL     -11
#define IDNOTFOUND      -12
#define OCCUR           -13
#define NOTINKOUT       -14

#define SPACE           0x20
#define UNJUSTVALUE     '*'
#define ENDTAG          '\0'
#define SCANNERDETECT   '2'
#define TESTPRINTNOW    'T'
#define DUMMYSCANNER    '3'
#define ALLCOLORCHAR    "KkLcmCMYBE"

#define DEV_1284	"PAR "
#define DEV_USB		"USB "
#define DEV_1394	"1394"
#define DEV_CHARSIZE	4

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
  }ink[6];
  char ink_check;
  char lever_position;
  char warning[12];
  char operator_call[12];
  char service_call[4];
  char reserve;
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
int chk_busystatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_cartridge(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_basestatus(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_inklow_part1(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_inklow_part2(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
int chk_noinkcheck(ST_CUPSSTS *p_tbl, ST_PrinterStatus *p_sts);
