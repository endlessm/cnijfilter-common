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
 * commonfunc.h
 *
 * A common header required for the module used in a bscc2sts library.
 *
 */

/*
 * include necessary headers ...
 */
#include "bsccstruct.h"

/*
 * macros ...
 */
#define BADITEM        -10
#define OCCUR          -11
#define ENDTAG         NULL

#define OPERATE        4
#define NOITEM         '*'
#define UNEQUIP        0x20

#define NOALERT        0x20
#define INKUNKNOWN     '?'
#define INKLOW         'L'
#define INKOUT         'O'
#define INKIO          'I'	// v2.6
#define INKRFL         'R'	// v2.6
#define INKWAR         'W'	// v2.6
#define INKERR         'E'	// v2.6

#define CTUNKOWN       '?'	// v2.6
#define FULL           "100"
#define HARF           "040"
#define TENPER         "010"
#define ZEROPER        "000"
#define UNKNOWNPER     "UUU"
#define UNSETTANK      "NNN"

//#define MAXFUNCNUM     16 	//from Ver.3.10 each model
#define MAXFUNCNUM     15 	//Ver.3.00
//#define MAXFUNCNUM     14 	//Ver.2.70
//#define MAXFUNCNUM     13
#define MAXCARTRIDGENUM 2
#define MAXS500COLORNUM 4
#define MAXS300COLORNUM 2
#define MAX550iCOLORNUM 4
#define MAX850iCOLORNUM 4
#define MAX560iCOLORNUM 4
#define MAX860iCOLORNUM 5
#define MAX990iCOLORNUM 7
#define MAXip1000COLORNUM 2
#define MAXip3100COLORNUM 4
#define MAXip4100COLORNUM 5
#define MAXip8600COLORNUM 8
#define MAXip2200COLORNUM 2
#define MAXip4200COLORNUM 5
#define MAXip6600dCOLORNUM 6
#define MAXip7500COLORNUM 7
#define MAXmp500COLORNUM 5
#define MAXmp510COLORNUM 4
#define MAXmp600COLORNUM 5
#define MAXmp160COLORNUM 2
#define MAXip2500COLORNUM 2
#define MAXip90COLORNUM 2
#define MAXmp210COLORNUM 2
#define MAXip100COLORNUM 2
#define MAXmp240COLORNUM 2
#define MAXmp630COLORNUM 5
#define MAXmp540COLORNUM 5
#define MAXmg8100COLORNUM 6
#define MAXmg4100COLORNUM 2
#define MAXmg5400COLORNUM 5
#define MAXmg6300COLORNUM 6



/*
 * prototypes ...
 */
int processforf9xx(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processfors300(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processfors500(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processfor550i(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processfor850i(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processfor950i(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processfor560i(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processfor860i(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processfor990i(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processforip1000(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processforip3100(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processforip4100(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processforip8600(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processforip2200(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processforip4200(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processforip6600d(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processforip7500(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformp500(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformp510(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformp600(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformp160(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processforip2500(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processforip90(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformp210(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processforip100(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformp240(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformp630(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformp540(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformg8100(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformg4100(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformg5400(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int processformg6300(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int selectcommonfunc(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, int f_num);

int commonstssetprocess(char *p_bsccsts, char *p_storetbl, ST_BSCC2STS *p_chgtbl);
int com_setbasests(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl);
int com_setstdsts(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl);
int com_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl);
int com_setexchange(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl);
int com_setwarn(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl);
int com_setoperate(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl);
int com_setoperatecode(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl);
int com_setservicecallcode(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl);

int com_warnoperatechk(char *p_call, char p_color, int buf_length);

int f9xx_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int s300_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int s300_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int s500_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixus950i_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixus850i_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixusip8600_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixus990i_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixus860i_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixus560i_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixusip3100_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixusip4100_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixus550i_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixus950i_setoperate(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixus850i_setoperate(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixusip8600_setoperate(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixus990i_setoperate(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixus860i_setoperate(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixus560i_setoperate(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixusip4100_setoperate(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int pixusip3100_setoperate(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip1000_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip1000_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip2200_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip2200_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip2200_setwarning(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip2200_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip4200_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip4200_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip6600d_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip6600d_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip7500_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip7500_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp500_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp500_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp510_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp510_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp600_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp600_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp160_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp160_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp160_setwarning(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp160_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip2500_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip2500_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip2500_setwarning(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip2500_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip90_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip90_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp210_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp210_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp210_setwarning(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp210_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip100_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip100_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip100_setwarning(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int ip100_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp240_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp240_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp240_setwarning(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp240_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp630_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp630_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp540_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mp540_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg8100_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg8100_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg4100_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg4100_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg4100_setwarning(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg4100_setcartridgetype(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg5400_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg5400_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg5400_setinkifnumber(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg6300_setink(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg6300_setinkalert(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
int mg6300_setinkifnumber(ST_STORESET *p_s, ST_BSCC2STS *p_ct, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);


