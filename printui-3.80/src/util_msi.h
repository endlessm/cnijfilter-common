/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2012
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
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


#ifndef _UTIL_MSI_H_
#define _UTIL_MSI_H_

typedef struct {
	short type;
	char id;
} MSICOMP;

/* MSI Type */
enum {
	MSI_TYPE_AUTOPOWERON = 0,
	MSI_TYPE_AUTOPOWEROFF,
	MSI_TYPE_AUTOPOWERBTOFF,
	MSI_TYPE_PAPERGAP,
	MSI_TYPE_DRYLEVEL,
	MSI_TYPE_PAGESIZEDETECTION,
	MSI_TYPE_G,
	MSI_TYPE_PLAINPAPERFEEDER,
	MSI_TYPE_I,
	MSI_TYPE_SILENT,
	MSI_TYPE_SILENT_TIME,
	MSI_TYPE_WFEED,
};

/* MSI Component */
MSICOMP msiCompTable[] = {
	{ MSI_TYPE_AUTOPOWERON, 'A' },
	{ MSI_TYPE_AUTOPOWEROFF, 'B' },
	{ MSI_TYPE_AUTOPOWERBTOFF, 'C' },
	{ MSI_TYPE_PAPERGAP, 'D' },
	{ MSI_TYPE_DRYLEVEL, 'E' },
	{ MSI_TYPE_PAGESIZEDETECTION, 'F' },
	{ MSI_TYPE_G, 'G' },
	{ MSI_TYPE_PLAINPAPERFEEDER, 'H' },
	{ MSI_TYPE_I, 'I' },
	{ MSI_TYPE_SILENT, 'J' }, 
	{ MSI_TYPE_SILENT_TIME, 'K' }, 
	{ MSI_TYPE_WFEED, 'L' }, 
	{ -1, -1 }
};

#define DEVID_BUF_SIZE	1024
#define MSI_STR_SIZE	32

#define MSI_STR_ON		"ON"
#define MSI_STR_OFF		"OFF"
#define MSI_STR_CW		"CW"
#define MSI_STR_AT		"AT"
#define MSI_STR_ASF		"ASF"
#define MSI_STR_FSF		"FSF"
#define MSI_STR_2FSF	"2FSF"	/* Ver.3.80 */
#define MSI_STR_TIME	"TIME"
#define MSI_STR_VAL_1	"1"
#define MSI_STR_VAL_2	"2"
#define MSI_STR_VAL_3	"3"
#define MSI_STR_VAL_4	"4"
#define MSI_STR_VAL_5	"5"
#define MSI_STR_05_MIN	"05"
#define MSI_STR_005_MIN	"005"
#define MSI_STR_10_MIN	"10"
#define MSI_STR_010_MIN	"010"
#define MSI_STR_15_MIN	"15"
#define MSI_STR_015_MIN	"015"
#define MSI_STR_30_MIN	"30"
#define MSI_STR_030_MIN	"030"
#define MSI_STR_60_MIN	"60"
#define MSI_STR_060_MIN	"060"
#define MSI_STR_120_MIN	"120"
#define MSI_STR_240_MIN	"240"

#endif
