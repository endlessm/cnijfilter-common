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


#define DEFINE_GLOBALS

#include <gtk/gtk.h>
#include "util_cmd.h"
#include "util_com.h"
#include "util_regi.h"
#include "util_setconfig.h"
#include "util_cleaning.h"
#include "util_nozzlecheck.h"

#include "util_cmdlist.h"

/* COMMAND DATA */
/* cleaning */
static const COMMANDDATA cleaningCmdType001[] =
{
	{ BJLCLEAN3LEN, BJLCLEAN3 },
	{ BJLCLEAN5LEN, BJLCLEAN5 },
	{ BJLCLEAN6LEN, BJLCLEAN6 },
};

static const COMMANDDATA deepCleaningCmdType001[] =
{
	{ BJLCLEAN4LEN, BJLCLEAN4 },
	{ BJLCLEAN7LEN, BJLCLEAN7 },
	{ BJLCLEAN8LEN, BJLCLEAN8 },
};

static const COMMANDDATA rollerCleaningCmdType001[] =
{
	{ BJLROLLER4LEN, BJLROLLER4 },
};

static const COMMANDDATA rollerCleaningCmdType002[] =
{
	{ BJLROLLER4BIN1LEN, BJLROLLER4BIN1 },
	{ BJLROLLER4BIN2LEN, BJLROLLER4BIN2 },
};

static const COMMANDDATA plateCleaningCmdType001[] =
{
	{ BJLROLLER3LEN, BJLROLLER3 },
};

/* nozzle check */
static const COMMANDDATA nozzleCheckCmdType001[] =
{
	{ BJLNOZZLECHECKLEN, BJLNOZZLECHECK },
};

static const COMMANDDATA nozzleCheckCmdType002[] =
{
	{ BJLNOZZLECHECKBIN1LEN, BJLNOZZLECHECKBIN1 },
	{ BJLNOZZLECHECKBIN2LEN, BJLNOZZLECHECKBIN2 },
};

/* regi */
static const COMMANDDATA regi1BinCmdType001[] =
{
	{ BJLREGICHECKLEN, BJLREGICHECK },
	{ BJLREGI1LEN, BJLREGI1 },
	{ BJLREGI2LEN, BJLREGI2 },
	{ BJLREGI3LEN, BJLREGI3 },
	{ BJLREGI4LEN, BJLREGI4 },
};

static const COMMANDDATA regi2BinCmdType001[] =
{
	{ BJLREGICHECKBIN1LEN, BJLREGICHECKBIN1 },
	{ BJLREGI1BIN1LEN, BJLREGI1BIN1 },
	{ BJLREGI2BIN1LEN, BJLREGI2BIN1 },
	{ BJLREGI3BIN1LEN, BJLREGI3BIN1 },
	{ BJLREGI4BIN1LEN, BJLREGI4BIN1 },
	{ BJLREGICHECKBIN2LEN, BJLREGICHECKBIN2 },
	{ BJLREGI1BIN2LEN, BJLREGI1BIN2 },
	{ BJLREGI2BIN2LEN, BJLREGI2BIN2 },
	{ BJLREGI3BIN2LEN, BJLREGI3BIN2 },
	{ BJLREGI4BIN2LEN, BJLREGI4BIN2 },
};

static const COMMANDDATA autoRegiCmdType001[] =
{
	{ BJLREGIAUTO1LEN, BJLREGIAUTO1 },
};

/* Ver.3.70 */
static const COMMANDDATA bandRegiCmdType001[] =
{
	{ BJLBANDREGI1LEN, BJLBANDREGI1 },
};

static const COMMANDDATA setRegiCmdType001[] =
{
	{ BJLSETREGLEN, BJLSETREG },
};

static const COMMANDDATA setRegiCmdType002[] =
{
	{ BJLSETREG2LEN, BJLSETREG2 },
};

/* set config */
static const COMMANDDATA customSettingsCmdType001[] =
{
	{ -1, BJLDRYLEVEL },
	{ -1, BJLPAPERGAP },
};

/* Ver.3.50 */
static const COMMANDDATA customSettingsCmdType002[] =
{
	{ -1, BJLDRYLEVEL },
	{ -1, BJLPAPERGAP },
	{ -1, BJLPAPERJAM },
};

/* Ver.3.60 */
static const COMMANDDATA customSettingsCmdType003[] =
{
	{ -1, BJLDRYLEVEL },
	{ -1, BJLPAPERGAP },
	{ -1, BJLPAPERWEFEED },
};

static const COMMANDDATA autoPowerCmdType001[] =
{
	{ -1, BJLAUTOPOWERON },
	{ -1, BJLAUTOPOWEROFF },
};

static const COMMANDDATA paperSourceSettingsCmdType001[] =
{
	{ BJLPAPERSOURCESETTING1LEN, BJLPAPERSOURCESETTING1 },
	{ BJLPAPERSOURCESETTING2LEN, BJLPAPERSOURCESETTING2 }
};

static const COMMANDDATA quietCmdType001[] =
{
	{ -1, BJLSILENT },
};

static const COMMANDDATA quietCmdType002[] =
{
	{ -1, BJLSILENT },
	{ -1, BJLSILENTTIME },
};

static const COMMANDDATA powerOffCmdType001[] =
{
	{ BJLPOWEROFFLEN, BJLPOWEROFF },
};

/* COMMAND COMPONENT */
static const COMMANDCOMP cmdCompList[] = 
{
	{ CMD_CLEANING_TYPE001, -1, SIZE_OF_ARRAY(cleaningCmdType001), (COMMANDDATA *)cleaningCmdType001 }, /* LUI_CMD_02_0001 */
	{ CMD_COMMON_TYPE001, 0, SIZE_OF_ARRAY(deepCleaningCmdType001), (COMMANDDATA *)deepCleaningCmdType001 }, /* LUI_CMD_03_0001 */
	{ CMD_COMMON_TYPE001, 1, SIZE_OF_ARRAY(deepCleaningCmdType001), (COMMANDDATA *)deepCleaningCmdType001 }, /* LUI_CMD_03_0002 */
	{ CMD_COMMON_TYPE001, 2, SIZE_OF_ARRAY(deepCleaningCmdType001), (COMMANDDATA *)deepCleaningCmdType001 }, /* LUI_CMD_03_0003 */
	{ CMD_CLEANING_TYPE002, -1, SIZE_OF_ARRAY(rollerCleaningCmdType001), (COMMANDDATA *)rollerCleaningCmdType001 }, /* LUI_CMD_04_0001 */
	{ CMD_COMMON_TYPE001, 0, SIZE_OF_ARRAY(rollerCleaningCmdType002), (COMMANDDATA *)rollerCleaningCmdType002 }, /* LUI_CMD_04_0002 */
	{ CMD_COMMON_TYPE001, 1, SIZE_OF_ARRAY(rollerCleaningCmdType002), (COMMANDDATA *)rollerCleaningCmdType002 }, /* LUI_CMD_04_0003 */
	{ CMD_COMMON_TYPE001, 0, SIZE_OF_ARRAY(plateCleaningCmdType001), (COMMANDDATA *)plateCleaningCmdType001 }, /* LUI_CMD_05_0001 */
	{ CMD_NOZZLECHECK_TYPE001, -1, SIZE_OF_ARRAY(nozzleCheckCmdType002), (COMMANDDATA *)nozzleCheckCmdType002 }, /* LUI_CMD_06_0001 */
	{ CMD_COMMON_TYPE001, 0, SIZE_OF_ARRAY(nozzleCheckCmdType002), (COMMANDDATA *)nozzleCheckCmdType002 }, /* LUI_CMD_06_0002 */
	{ CMD_COMMON_TYPE001, 1, SIZE_OF_ARRAY(nozzleCheckCmdType002), (COMMANDDATA *)nozzleCheckCmdType002 }, /* LUI_CMD_06_0003 */
	{ CMD_COMMON_TYPE001, 0, SIZE_OF_ARRAY(nozzleCheckCmdType001), (COMMANDDATA *)nozzleCheckCmdType001 }, /* LUI_CMD_06_0004 */
	{ CMD_COMMON_TYPE003, 0, SIZE_OF_ARRAY(powerOffCmdType001), (COMMANDDATA *)powerOffCmdType001 }, /* LUI_CMD_07_0001 */
	{ CMD_SETCONFIG_TYPE002, -1, SIZE_OF_ARRAY(autoPowerCmdType001), (COMMANDDATA *)autoPowerCmdType001 }, /* LUI_CMD_08_0001 */
	{ CMD_SETCONFIG_TYPE004, -1, SIZE_OF_ARRAY(quietCmdType001), (COMMANDDATA *)quietCmdType001 }, /* LUI_CMD_13_0001 */
	{ CMD_COMMON_TYPE001, 0, SIZE_OF_ARRAY(regi1BinCmdType001), (COMMANDDATA *)regi1BinCmdType001 }, /* LUI_CMD_14_0001 */
	{ CMD_COMMON_TYPE001, 1, SIZE_OF_ARRAY(regi1BinCmdType001), (COMMANDDATA *)regi1BinCmdType001 }, /* LUI_CMD_14_0002 */
	{ CMD_REGI_TYPE001, 0, SIZE_OF_ARRAY(setRegiCmdType002), (COMMANDDATA *)setRegiCmdType002 }, /* LUI_CMD_14_0003 */
	{ CMD_COMMON_TYPE001, 2, SIZE_OF_ARRAY(regi1BinCmdType001), (COMMANDDATA *)regi1BinCmdType001 }, /* LUI_CMD_14_0004 */
	{ CMD_COMMON_TYPE001, 3, SIZE_OF_ARRAY(regi1BinCmdType001), (COMMANDDATA *)regi1BinCmdType001 }, /* LUI_CMD_14_0005 */
	{ CMD_COMMON_TYPE001, 0, SIZE_OF_ARRAY(regi2BinCmdType001), (COMMANDDATA *)regi2BinCmdType001 }, /* LUI_CMD_14_0006 */
	{ CMD_COMMON_TYPE001, 5, SIZE_OF_ARRAY(regi2BinCmdType001), (COMMANDDATA *)regi2BinCmdType001 }, /* LUI_CMD_14_0007 */
	{ CMD_COMMON_TYPE001, 1, SIZE_OF_ARRAY(regi2BinCmdType001), (COMMANDDATA *)regi2BinCmdType001 }, /* LUI_CMD_14_0008 */
	{ CMD_REGI_TYPE002, 2, SIZE_OF_ARRAY(regi2BinCmdType001), (COMMANDDATA *)regi2BinCmdType001 }, /* LUI_CMD_14_0009 */
	{ CMD_REGI_TYPE002, 3, SIZE_OF_ARRAY(regi2BinCmdType001), (COMMANDDATA *)regi2BinCmdType001 }, /* LUI_CMD_14_0010 */
	{ CMD_COMMON_TYPE001, 6, SIZE_OF_ARRAY(regi2BinCmdType001), (COMMANDDATA *)regi2BinCmdType001 }, /* LUI_CMD_14_0011 */
	{ CMD_COMMON_TYPE001, 0, SIZE_OF_ARRAY(autoRegiCmdType001), (COMMANDDATA *)autoRegiCmdType001 }, /* LUI_CMD_14_0012 */
	{ CMD_SETCONFIG_TYPE001, -1, SIZE_OF_ARRAY(customSettingsCmdType001), (COMMANDDATA *)customSettingsCmdType001 }, /* LUI_CMD_15_0001 */
	{ CMD_SETCONFIG_TYPE003, -1, SIZE_OF_ARRAY(paperSourceSettingsCmdType001), (COMMANDDATA *)paperSourceSettingsCmdType001 }, /* LUI_CMD_16_0001 */
	{ CMD_COMMON_TYPE001, 0, SIZE_OF_ARRAY(rollerCleaningCmdType001), (COMMANDDATA *)rollerCleaningCmdType001 }, /* LUI_CMD_04_0004 */
	{ CMD_SETCONFIG_TYPE005, -1, SIZE_OF_ARRAY(autoPowerCmdType001), (COMMANDDATA *)autoPowerCmdType001 }, /* LUI_CMD_08_0003 *//* Ver.3.50 */
	{ CMD_SETCONFIG_TYPE006, -1, SIZE_OF_ARRAY(customSettingsCmdType002), (COMMANDDATA *)customSettingsCmdType002 }, /* LUI_CMD_15_0001 *//* Ver.3.50 */
	{ CMD_SETCONFIG_TYPE007, -1, SIZE_OF_ARRAY(quietCmdType002), (COMMANDDATA *)quietCmdType002 }, /* LUI_CMD_13_0002 *//* Ver.3.60 */
	{ CMD_SETCONFIG_TYPE008, -1, SIZE_OF_ARRAY(autoPowerCmdType001), (COMMANDDATA *)autoPowerCmdType001 }, /* LUI_CMD_08_0004 *//* Ver.3.60 */
	{ CMD_SETCONFIG_TYPE009, -1, SIZE_OF_ARRAY(customSettingsCmdType003), (COMMANDDATA *)customSettingsCmdType003 }, /* LUI_CMD_15_0003 *//* Ver.3.60 */
	{ CMD_SETCONFIG_TYPE010, -1, SIZE_OF_ARRAY(autoPowerCmdType001), (COMMANDDATA *)autoPowerCmdType001 }, /* LUI_CMD_08_0002 *//* Ver.3.70 */
	{ CMD_SETCONFIG_TYPE011, -1, SIZE_OF_ARRAY(customSettingsCmdType001), (COMMANDDATA *)customSettingsCmdType001 }, /* LUI_CMD_15_0004 */
	{ CMD_SETCONFIG_TYPE012, -1, SIZE_OF_ARRAY(quietCmdType001), (COMMANDDATA *)quietCmdType001 }, /* LUI_CMD_15_0004 */
	{ CMD_COMMON_TYPE001, 0, SIZE_OF_ARRAY(bandRegiCmdType001), (COMMANDDATA *)bandRegiCmdType001 }, /* LUI_CMD_14_0013 */
};


COMMANDCOMPTABLE utilCommandCompTable[] =
{
	{ "LUI_CMD_02_0001", (COMMANDCOMP *)&cmdCompList[0] },
	{ "LUI_CMD_03_0001", (COMMANDCOMP *)&cmdCompList[1] },
	{ "LUI_CMD_03_0002", (COMMANDCOMP *)&cmdCompList[2] },
	{ "LUI_CMD_03_0003", (COMMANDCOMP *)&cmdCompList[3] },
	{ "LUI_CMD_04_0001", (COMMANDCOMP *)&cmdCompList[4] },
	{ "LUI_CMD_04_0002", (COMMANDCOMP *)&cmdCompList[5] },
	{ "LUI_CMD_04_0003", (COMMANDCOMP *)&cmdCompList[6] },
	{ "LUI_CMD_05_0001", (COMMANDCOMP *)&cmdCompList[7] },
	{ "LUI_CMD_06_0001", (COMMANDCOMP *)&cmdCompList[8] },
	{ "LUI_CMD_06_0002", (COMMANDCOMP *)&cmdCompList[9] },
	{ "LUI_CMD_06_0003", (COMMANDCOMP *)&cmdCompList[10] },
	{ "LUI_CMD_06_0004", (COMMANDCOMP *)&cmdCompList[11] },
	{ "LUI_CMD_07_0001", (COMMANDCOMP *)&cmdCompList[12] },
	{ "LUI_CMD_08_0001", (COMMANDCOMP *)&cmdCompList[13] },
	{ "LUI_CMD_13_0001", (COMMANDCOMP *)&cmdCompList[14] },
	{ "LUI_CMD_14_0001", (COMMANDCOMP *)&cmdCompList[15] },
	{ "LUI_CMD_14_0002", (COMMANDCOMP *)&cmdCompList[16] },
	{ "LUI_CMD_14_0003", (COMMANDCOMP *)&cmdCompList[17] },
	{ "LUI_CMD_14_0004", (COMMANDCOMP *)&cmdCompList[18] },
	{ "LUI_CMD_14_0005", (COMMANDCOMP *)&cmdCompList[19] },
	{ "LUI_CMD_14_0006", (COMMANDCOMP *)&cmdCompList[20] },
	{ "LUI_CMD_14_0007", (COMMANDCOMP *)&cmdCompList[21] },
	{ "LUI_CMD_14_0008", (COMMANDCOMP *)&cmdCompList[22] },
	{ "LUI_CMD_14_0009", (COMMANDCOMP *)&cmdCompList[23] },
	{ "LUI_CMD_14_0010", (COMMANDCOMP *)&cmdCompList[24] },
	{ "LUI_CMD_14_0011", (COMMANDCOMP *)&cmdCompList[25] },
	{ "LUI_CMD_14_0012", (COMMANDCOMP *)&cmdCompList[26] },
	{ "LUI_CMD_15_0001", (COMMANDCOMP *)&cmdCompList[27] },
	{ "LUI_CMD_16_0001", (COMMANDCOMP *)&cmdCompList[28] },
	{ "LUI_CMD_04_0004", (COMMANDCOMP *)&cmdCompList[29] },
	{ "LUI_CMD_08_0003", (COMMANDCOMP *)&cmdCompList[30] }, /* Ver.3.50 */
	{ "LUI_CMD_15_0002", (COMMANDCOMP *)&cmdCompList[31] }, /* Ver.3.50 */
	{ "LUI_CMD_13_0002", (COMMANDCOMP *)&cmdCompList[32] }, /* Ver.3.60 */
	{ "LUI_CMD_08_0004", (COMMANDCOMP *)&cmdCompList[33] }, /* Ver.3.60 */
	{ "LUI_CMD_15_0003", (COMMANDCOMP *)&cmdCompList[34] }, /* Ver.3.60 */
	{ "LUI_CMD_15_0003", (COMMANDCOMP *)&cmdCompList[34] }, /* Ver.3.60 */
	{ "LUI_CMD_08_0002", (COMMANDCOMP *)&cmdCompList[35] }, /* Ver.3.70 */
	{ "LUI_CMD_15_0004", (COMMANDCOMP *)&cmdCompList[36] }, /* Ver.3.70 */
	{ "LUI_CMD_13_0003", (COMMANDCOMP *)&cmdCompList[37] }, /* Ver.3.70 */
	{ "LUI_CMD_14_0013", (COMMANDCOMP *)&cmdCompList[38] }, /* Ver.3.70 */
	{ NULL, NULL },
};

COMMANDOUTFUNCTABLE utilCommandProcFuncTable[] =
{
	{ CMD_COMMON_TYPE001, OutputUtilityCommand_CMD_COMMON_TYPE001 },	
	{ CMD_COMMON_TYPE002, OutputUtilityCommand_CMD_COMMON_TYPE002 },	
	{ CMD_COMMON_TYPE003, OutputUtilityCommand_CMD_COMMON_TYPE003 },	
	{ CMD_CLEANING_TYPE001, OutputUtilityCommand_CMD_CLEANING_TYPE001 },	
	{ CMD_CLEANING_TYPE002, OutputUtilityCommand_CMD_CLEANING_TYPE002 },	
	{ CMD_NOZZLECHECK_TYPE001, OutputUtilityCommand_CMD_NozzleCheck_TYPE001 },
	{ CMD_REGI_TYPE001, OutputUtilityCommand_CMD_REGI_TYPE001 },	
	{ CMD_REGI_TYPE002, OutputUtilityCommand_CMD_REGI_TYPE002 },	
	{ CMD_SETCONFIG_TYPE001, OutputUtilityCommand_CMD_SETCONFIG_TYPE001 },	
	{ CMD_SETCONFIG_TYPE002, OutputUtilityCommand_CMD_SETCONFIG_TYPE002 },	
	{ CMD_SETCONFIG_TYPE003, OutputUtilityCommand_CMD_SETCONFIG_TYPE003 },	
	{ CMD_SETCONFIG_TYPE004, OutputUtilityCommand_CMD_SETCONFIG_TYPE004 },	
	{ CMD_SETCONFIG_TYPE005, OutputUtilityCommand_CMD_SETCONFIG_TYPE005 },	/* Ver.3.50 */
	{ CMD_SETCONFIG_TYPE006, OutputUtilityCommand_CMD_SETCONFIG_TYPE006 },	/* Ver.3.50 */
	{ CMD_SETCONFIG_TYPE007, OutputUtilityCommand_CMD_SETCONFIG_TYPE007 },	/* Ver.3.60 */
	{ CMD_SETCONFIG_TYPE008, OutputUtilityCommand_CMD_SETCONFIG_TYPE008 },	/* Ver.3.60 */
	{ CMD_SETCONFIG_TYPE009, OutputUtilityCommand_CMD_SETCONFIG_TYPE009 },	/* Ver.3.60 */
	{ CMD_SETCONFIG_TYPE010, OutputUtilityCommand_CMD_SETCONFIG_TYPE010 },	/* Ver.3.70 */
	{ CMD_SETCONFIG_TYPE011, OutputUtilityCommand_CMD_SETCONFIG_TYPE011 },	/* Ver.3.70 */
	{ CMD_SETCONFIG_TYPE012, OutputUtilityCommand_CMD_SETCONFIG_TYPE012 },	/* Ver.3.70 */
	{ -1, NULL }
};
