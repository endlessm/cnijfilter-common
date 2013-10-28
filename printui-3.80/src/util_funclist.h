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


#ifndef _UTIL_FUNCLIST_H_
#define _UTIL_FUNCLIST_H_

typedef struct {
	char *name;
	short (*proc)( char * );
} DIALOGCOMPTABLE;

#ifdef DEFINE_GLOBALS
DIALOGCOMPTABLE utilDialogTable[] ={
	{ "LUI_UTD_01_0001",  ExecCommonDialogType001_000 },
	{ "LUI_UTD_01_0002",  ExecSetConfigType002_000 },
	{ "LUI_UTD_01_0003",  ExecSetConfigType004_000 }, /* Ver.3.70 */
	{ "LUI_UTD_01_0004",  ExecCommonDialogType001_000 }, /* Ver.3.70 */
	{ "LUI_UTL_02_0000",  ExecCleaningType000_000 },
	{ "LUI_UTL_02_0001",  ExecCleaningType000_004 }, /* Ver.3.80 */
	{ "LUI_UTD_02_0001",  ExecCommonDialogType001_000 },
	{ "LUI_UTD_02_0002b", ExecCleaningType001_000 },
	{ "LUI_UTD_02_0002d", ExecCleaningType001_000 },
	{ "LUI_UTD_02_0002e", ExecCleaningType001_000 },
	{ "LUI_UTL_03_0000",  ExecCleaningType000_001 },
	{ "LUI_UTL_03_0001",  ExecCleaningType000_005 }, /* Ver.3.80 */
	{ "LUI_UTD_03_0002",  ExecCommonDialogType001_001 },
	{ "LUI_UTD_03_0003b", ExecCleaningType001_001 },
	{ "LUI_UTD_03_0003d", ExecCleaningType001_001 },
	{ "LUI_UTD_03_0004",  ExecCommonDialogType001_001 },
	{ "LUI_UTD_03_0005",  ExecCommonDialogType001_001 },
	{ "LUI_UTD_03_0006",  ExecCleaningType001_001 },
	{ "LUI_UTD_03_0007",  ExecCommonDialogType001_000 },
	{ "LUI_UTD_03_0008",  ExecCleaningType001_005 }, /* Ver.3.50 */
	{ "LUI_UTL_04_0000",  ExecCleaningType000_002 },
	{ "LUI_UTD_04_0003",  ExecCommonDialogType001_003 },
	{ "LUI_UTD_04_0004a", ExecCommonDialogType001_001 },
	{ "LUI_UTD_04_0005a", ExecCommonDialogType001_000 },
	{ "LUI_UTD_04_0005b", ExecCommonDialogType001_000 },
	{ "LUI_UTD_04_0006",  ExecCleaningType001_003 },
	{ "LUI_UTD_04_0007a", ExecCommonDialogType001_001 },
	{ "LUI_UTD_04_0007b", ExecCommonDialogType001_001 },
	{ "LUI_UTD_04_0008a", ExecCommonDialogType001_001 },
	{ "LUI_UTD_04_0008b", ExecCommonDialogType001_001 },
	{ "LUI_UTD_04_0009",  ExecCommonDialogType001_000 },
	{ "LUI_UTD_04_0010",  ExecCommonDialogType001_001 }, /* Ver.3.50 */
	{ "LUI_UTD_04_0011",  ExecCommonDialogType001_001 }, /* Ver.3.60 */
	{ "LUI_UTD_04_0012",  ExecCommonDialogType001_000 }, /* Ver.3.60 */
	{ "LUI_UTD_04_0013",  ExecCleaningType001_006 }, /* Ver.3.80 */
	{ "LUI_UTD_04_0014",  ExecCommonDialogType001_001 }, /* Ver.3.80 */
	{ "LUI_UTD_04_0015",  ExecCommonDialogType001_000 }, /* Ver.3.80 */
	{ "LUI_UTD_04_0016",  ExecCommonDialogType001_001 }, /* Ver.3.80 */
	{ "LUI_UTD_04_0017",  ExecCommonDialogType001_000 }, /* Ver.3.80 */
	{ "LUI_UTL_05_0000",  ExecCleaningType000_003 },
	{ "LUI_UTD_05_0001b", ExecCleaningType001_004 },
	{ "LUI_UTD_05_0001c", ExecCleaningType001_004 },
	{ "LUI_UTD_05_0002",  ExecCleaningType001_004 }, /* Ver.3.50 */
	{ "LUI_UTD_05_0003",  ExecCleaningType001_004 }, /* Ver.3.60 */
	{ "LUI_UTD_05_0004",  ExecCleaningType001_004 }, /* Ver.3.80 */
	{ "LUI_UTL_06_0000",  ExecNozzleCheckType000_000 },
	{ "LUI_UTL_06_0000a", ExecNozzleCheckType000_001 },
	{ "LUI_UTL_06_0001",  ExecNozzleCheckType000_002 },
	{ "LUI_UTL_06_0002",  ExecNozzleCheckType000_003 },
	{ "LUI_UTL_06_0003",  ExecNozzleCheckType000_004 }, /* Ver.3.80 */
	{ "LUI_UTD_06_0001f", ExecNozzleCheckType002_000 },
	{ "LUI_UTD_06_0001g", ExecNozzleCheckType002_000 },
	{ "LUI_UTD_06_0001h", ExecNozzleCheckType002_000 },
	{ "LUI_UTD_06_0002b", ExecNozzleCheckType001_000 },
	{ "LUI_UTD_06_0003",  ExecNozzleCheckType002_001 },
	{ "LUI_UTD_06_0004",  ExecNozzleCheckType002_000 },
	{ "LUI_UTD_06_0005",  ExecNozzleCheckType002_000 }, /* Ver.3.70 */
	{ "LUI_UTD_06_0006",  ExecNozzleCheckType002_000 }, /* Ver.3.80 */
	{ "LUI_UTL_07_0000",  ExecSetConfigType000_002 },
	{ "LUI_UTD_07_0001",  ExecCommonDialogType001_001 },
	{ "LUI_UTL_08_0000",  ExecSetConfigType000_003 },
	{ "LUI_UTL_08_0001",  ExecSetConfigType000_010 }, /* Ver.3.70 */
	{ "LUI_UTL_08_0002",  ExecSetConfigType000_011 }, /* Ver.3.70 */
	{ "LUI_UTL_08_0003",  ExecSetConfigType000_012 }, /* Ver.3.70 */
	{ "LUI_UTL_08_0004",  ExecSetConfigType000_016 }, /* Ver.3.70 */
	{ "LUI_UTL_08_0005",  ExecSetConfigType000_017 }, /* Ver.3.80 */
	{ "LUI_UTL_08_0006",  ExecSetConfigType000_018 }, /* Ver.3.80 */
	{ "LUI_UTD_08_0001",  ExecSetConfigType001_000 },
	{ "LUI_UTD_08_0002",  ExecSetConfigType001_000 },
	{ "LUI_UTD_08_0003",  ExecSetConfigType001_000 }, /* Ver.3.50 */
	{ "LUI_UTD_08_0004",  ExecSetConfigType001_000 }, /* Ver.3.60 */
	{ "LUI_UTD_08_0005",  ExecSetConfigType002_000 }, /* Ver.3.60 */
	{ "LUI_UTL_12_0000",  ExecSetConfigType000_001 },
	{ "LUI_UTD_12_0002c", ExecSetConfigType003_000 },
	{ "LUI_UTL_13_0000",  ExecSetConfigType000_005 }, /* Ver.3.60 */
	{ "LUI_UTL_13_0001",  ExecSetConfigType000_014 }, /* Ver.3.70 */
	{ "LUI_UTL_13_0002",  ExecSetConfigType000_015 }, /* Ver.3.70 */
	{ "LUI_UTL_13_1000",  ExecSetConfigType000_006 },
	{ "LUI_UTD_13_0001",  ExecSetConfigType001_000 },
	{ "LUI_UTD_13_0002",  ExecSetConfigType001_000 }, /* Ver.3.60 */
	{ "LUI_UTD_13_0003",  ExecSetConfigType001_000 }, /* Ver.3.60 */
	{ "LUI_UTL_14_0000",  ExecRegiType000_000 }, 
	{ "LUI_UTL_14_0001",  ExecRegiType000_001 }, 
	{ "LUI_UTL_14_0002",  ExecRegiType000_002 }, 
	{ "LUI_UTL_14_0003",  ExecRegiType000_003 },  /* Ver.3.80 */
	{ "LUI_UTD_14M_0002", ExecCommonDialogType001_002 },
	{ "LUI_UTD_14M_0003", ExecCommonDialogType001_000 },
	{ "LUI_UTD_14M_0005", ExecCommonDialogType001_003 },
	{ "LUI_UTD_14M_0010c", ExecCommonDialogType001_001 },
	{ "LUI_UTD_14M_0014", ExecCommonDialogType001_000 },
	{ "LUI_UTD_14M_0016", ExecCommonDialogType001_000 },
	{ "LUI_UTD_14M_0021", ExecCommonDialogType001_001 },
	{ "LUI_UTD_14M_0029", ExecRegiType002_000 },
	{ "LUI_UTD_14M_0030", ExecRegiType001_011 },
	{ "LUI_UTD_14M_0031", ExecRegiType001_012 },
	{ "LUI_UTD_14M_0032", ExecRegiType001_013 },
	{ "LUI_UTD_14M_0033", ExecRegiType002_001 },
	{ "LUI_UTD_14M_0034", ExecCommonDialogType001_001 },
	{ "LUI_UTD_14M_0035", ExecCommonDialogType001_001 },
	{ "LUI_UTD_14M_0036", ExecCommonDialogType001_001 },
	{ "LUI_UTD_14M_0037", ExecCommonDialogType001_001 },
	{ "LUI_UTD_14M_0039", ExecRegiType001_004 },
	{ "LUI_UTD_14M_0040", ExecRegiType001_005 },
	{ "LUI_UTD_14M_0045", ExecRegiType002_000 },
	{ "LUI_UTD_14M_0046", ExecRegiType001_000 },
	{ "LUI_UTD_14M_0047", ExecRegiType001_001 },
	{ "LUI_UTD_14M_0048", ExecRegiType001_002 },
	{ "LUI_UTD_14M_0049", ExecRegiType001_003 },
	{ "LUI_UTD_14M_0050", ExecRegiType002_000 },
	{ "LUI_UTD_14M_0051", ExecRegiType001_006 }, /* Ver.3.50 */
	{ "LUI_UTD_14M_0052", ExecRegiType001_007 }, /* Ver.3.50 */
	{ "LUI_UTD_14M_0053", ExecRegiType001_008 }, /* Ver.3.60 */
	{ "LUI_UTD_14M_0054", ExecRegiType001_009 }, /* Ver.3.60 */
	{ "LUI_UTD_14M_0055", ExecRegiType001_010 }, /* Ver.3.60 */
	{ "LUI_UTD_14M_0056", ExecRegiType002_000 }, /* Ver.3.70 */
	{ "LUI_UTD_14M_0057", ExecRegiType002_000 }, /* Ver.3.70 */
	{ "LUI_UTD_14M_0058", ExecRegiType002_005 }, /* Ver.3.70 */
	{ "LUI_UTD_14M_0059", ExecRegiType002_000 }, /* Ver.3.80 */
	{ "LUI_UTD_14M_0060", ExecRegiType001_014 }, /* Ver.3.80 */
	{ "LUI_UTD_14M_0061", ExecRegiType001_015 }, /* Ver.3.80 */
	{ "LUI_UTD_14M_0062", ExecRegiType001_016 }, /* Ver.3.80 */
	{ "LUI_UTD_14A_0001c", ExecRegiType002_002 },
	{ "LUI_UTD_14A_0003a", ExecCommonDialogType001_000 },
	{ "LUI_UTD_14A_0005", ExecRegiType002_004 },
	{ "LUI_UTD_14A_0006", ExecCommonDialogType001_001 },
	{ "LUI_UTD_14A_0007", ExecRegiType002_002 },
	{ "LUI_UTD_14A_0008", ExecRegiType002_003 },
	{ "LUI_UTD_14A_0009", ExecRegiType002_003 }, /* Ver.3.50 */
	{ "LUI_UTD_14A_0010", ExecCommonDialogType001_001 }, /* Ver.3.70 */
	{ "LUI_UTD_14A_0011", ExecCommonDialogType001_001 }, /* Ver.3.70 */
	{ "LUI_UTD_14A_0012", ExecCommonDialogType001_001 }, /* Ver.3.70 */
	{ "LUI_UTD_14A_0013", ExecCommonDialogType001_001 }, /* Ver.3.70 */
	{ "LUI_UTD_14A_0014", ExecRegiType002_006 }, /* Ver.3.70 */
	{ "LUI_UTD_14A_0015", ExecRegiType002_007 }, /* Ver.3.70 */
	{ "LUI_UTD_14A_0016", ExecRegiType002_008 }, /* Ver.3.70 */
	{ "LUI_UTD_14A_0017", ExecRegiType002_009 }, /* Ver.3.80 */
	{ "LUI_UTD_14A_0018", ExecCommonDialogType001_001 }, /* Ver.3.80 */
	{ "LUI_UTD_14A_0019", ExecRegiType002_006 }, /* Ver.3.80 */
	{ "LUI_UTL_15_0000",  ExecSetConfigType000_004 },
	{ "LUI_UTL_15_0001",  ExecSetConfigType000_007 }, /* Ver.3.70 */
	{ "LUI_UTL_15_0002",  ExecSetConfigType000_008 }, /* Ver.3.70 */
	{ "LUI_UTL_15_0003",  ExecSetConfigType000_009 }, /* Ver.3.70 */
	{ "LUI_UTD_15_0001a", ExecSetConfigType001_000 },
	{ "LUI_UTD_15_0001c", ExecSetConfigType001_000 },
	{ "LUI_UTD_15_0003",  ExecSetConfigType001_000 }, /* Ver.3.50 */
	{ "LUI_UTD_15_0005",  ExecSetConfigType001_000 }, /* Ver.3.60 */
	{ "LUI_UTL_16_0000",  ExecSetConfigType000_000 },
	{ "LUI_UTL_16_0001",  ExecSetConfigType000_013 }, /* Ver.3.70 */
	{ "LUI_UTD_16_0001",  ExecSetConfigType001_000 },
	{ NULL, NULL },
};
#else
extern DIALOGCOMPTABLE utilDialogTable[];
#endif


#endif
