/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2010
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


DIALOGCOMPTABLE utilDialogTable[] ={
	{ "LUI_UTD_01_0001",  ExecCommonDialogType001_000 },
	{ "LUI_UTD_01_0002",  ExecSetConfigType002_000 },
	{ "LUI_UTL_02_0000",  ExecCleaningType000_000 },
	{ "LUI_UTD_02_0001",  ExecCommonDialogType001_000 },
	{ "LUI_UTD_02_0002b", ExecCleaningType001_000 },
	{ "LUI_UTD_02_0002d", ExecCleaningType001_000 },
	{ "LUI_UTD_02_0002e", ExecCleaningType001_000 },
	{ "LUI_UTL_03_0000",  ExecCleaningType000_001 },
	{ "LUI_UTD_03_0002",  ExecCommonDialogType001_001 },
	{ "LUI_UTD_03_0003b", ExecCleaningType001_001 },
	{ "LUI_UTD_03_0003d", ExecCleaningType001_001 },
	{ "LUI_UTD_03_0004",  ExecCommonDialogType001_001 },
	{ "LUI_UTD_03_0005",  ExecCommonDialogType001_001 },
	{ "LUI_UTD_03_0006",  ExecCleaningType001_001 },
	{ "LUI_UTD_03_0007",  ExecCommonDialogType001_000 },
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
	{ "LUI_UTL_05_0000",  ExecCleaningType000_003 },
	{ "LUI_UTD_05_0001b", ExecCleaningType001_004 },
	{ "LUI_UTL_06_0000",  ExecNozzleCheckType000_000 },
	{ "LUI_UTL_06_0000a", ExecNozzleCheckType000_001 },
	{ "LUI_UTD_06_0001g", ExecNozzleCheckType002_000 },
	{ "LUI_UTD_06_0001h", ExecNozzleCheckType002_000 },
	{ "LUI_UTD_06_0002b", ExecNozzleCheckType001_000 },
	{ "LUI_UTD_06_0003",  ExecNozzleCheckType002_001 },
	{ "LUI_UTD_06_0004",  ExecNozzleCheckType002_000 },
	{ "LUI_UTL_07_0000",  ExecSetConfigType000_002 },
	{ "LUI_UTD_07_0001",  ExecCommonDialogType001_001 },
	{ "LUI_UTL_08_0000",  ExecSetConfigType000_003 },
	{ "LUI_UTD_08_0001",  ExecSetConfigType001_001 },
	{ "LUI_UTL_12_0000",  ExecSetConfigType000_001 },
	{ "LUI_UTD_12_0002c", ExecSetConfigType003_000 },
	{ "LUI_UTL_13_0000",  ExecSetConfigType000_005 },
	{ "LUI_UTD_13_0001",  ExecSetConfigType001_003 },
	{ "LUI_UTL_14_0000",  ExecRegiType000_000 }, 
	{ "LUI_UTD_14M_0002", ExecCommonDialogType001_002 },
	{ "LUI_UTD_14M_0003", ExecCommonDialogType001_000 },
	{ "LUI_UTD_14M_0005", ExecCommonDialogType001_003 },
	{ "LUI_UTD_14M_0014", ExecCommonDialogType001_000 },
	{ "LUI_UTD_14M_0016", ExecCommonDialogType001_000 },
	{ "LUI_UTD_14M_0021", ExecCommonDialogType001_001 },
	{ "LUI_UTD_14M_0033", ExecRegiType002_001 },
	{ "LUI_UTD_14M_0034", ExecCommonDialogType001_001 },
	{ "LUI_UTD_14M_0035", ExecCommonDialogType001_000 },
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
	{ "LUI_UTD_14A_0003a", ExecCommonDialogType001_000 },
	{ "LUI_UTD_14A_0005", ExecRegiType002_004 },
	{ "LUI_UTD_14A_0006", ExecCommonDialogType001_001 },
	{ "LUI_UTD_14A_0007", ExecRegiType002_002 },
	{ "LUI_UTD_14A_0008", ExecRegiType002_003 },
	{ "LUI_UTL_15_0000",  ExecSetConfigType000_004 },
	{ "LUI_UTD_15_0001a", ExecSetConfigType001_000 },
	{ "LUI_UTL_16_0000",  ExecSetConfigType000_000 },
	{ "LUI_UTD_16_0001",  ExecSetConfigType001_002 },
	{ NULL, NULL },
};

#endif
