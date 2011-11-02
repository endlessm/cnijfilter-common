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


#ifndef _UTIL_SETCONFIG_H_
#define _UTIL_SETCONFIG_H_

/* Set Config Type */
gboolean IsManualHeadMode( void );
short OutputUtilityCommand_CMD_SETCONFIG_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_SETCONFIG_TYPE002( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_SETCONFIG_TYPE003( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_SETCONFIG_TYPE004( short index, COMMANDDATA *cmdData, short cmdNum );
void InitCreate_SetconfigType001_CustomSettings( void );
void InitCreate_SetConfigType001_AutoPower( void );
void InitCreate_SetConfigType001_PaperSourceSettings( void );
void InitCreate_SetConfigType001_QuietMode( void );
short ExecSetConfigType000_000( char *dialogName );
short ExecSetConfigType000_001( char *dialogName );
short ExecSetConfigType000_002( char *dialogName );
short ExecSetConfigType000_003( char *dialogName );
short ExecSetConfigType000_004( char *dialogName );
short ExecSetConfigType000_005( char *dialogName );
short ExecSetConfigType001_000( char *dialogName );
short ExecSetConfigType001_001( char *dialogName );
short ExecSetConfigType001_002( char *dialogName );
short ExecSetConfigType001_003( char *dialogName );
unsigned int GetFlagSetConfigType002( void );
short ExecSetConfigType002_000( char *dialogName );
short ExecSetConfigType003_000( char *dialogName );
#endif
