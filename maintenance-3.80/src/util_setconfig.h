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


#ifndef _UTIL_SETCONFIG_H_
#define _UTIL_SETCONFIG_H_

/* Set Config Type */
gboolean IsManualHeadMode( void );
int GetMSIPaperSourceSettings01( int *paperSource );
int SetMSIPaperSourceSettings( void );
int GetMSIPaperSourceSettingsCurrentValue( void );
short OutputUtilityCommand_CMD_SETCONFIG_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_SETCONFIG_TYPE002( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_SETCONFIG_TYPE003( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_SETCONFIG_TYPE004( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_SETCONFIG_TYPE005( short index, COMMANDDATA *cmdData, short cmdNum ); /* Ver.3.50 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE006( short index, COMMANDDATA *cmdData, short cmdNum ); /* Ver.3.50 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE007( short index, COMMANDDATA *cmdData, short cmdNum ); /* Ver.3.60 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE008( short index, COMMANDDATA *cmdData, short cmdNum ); /* Ver.3.60 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE009( short index, COMMANDDATA *cmdData, short cmdNum ); /* Ver.3.60 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE010( short index, COMMANDDATA *cmdData, short cmdNum ); /* Ver.3.70 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE011( short index, COMMANDDATA *cmdData, short cmdNum ); /* Ver.3.70 */
short OutputUtilityCommand_CMD_SETCONFIG_TYPE012( short index, COMMANDDATA *cmdData, short cmdNum ); /* Ver.3.70 */
short ExecSetConfigType000_000( char *dialogName );
short ExecSetConfigType000_001( char *dialogName );
short ExecSetConfigType000_002( char *dialogName );
short ExecSetConfigType000_003( char *dialogName );
short ExecSetConfigType000_004( char *dialogName );
short ExecSetConfigType000_005( char *dialogName ); /* Ver.3.60 */
short ExecSetConfigType000_006( char *dialogName );
short ExecSetConfigType000_007( char *dialogName ); /* Ver.3.70 */
short ExecSetConfigType000_008( char *dialogName ); /* Ver.3.70 */
short ExecSetConfigType000_009( char *dialogName ); /* Ver.3.70 */
short ExecSetConfigType000_010( char *dialogName ); /* Ver.3.70 */
short ExecSetConfigType000_011( char *dialogName ); /* Ver.3.70 */
short ExecSetConfigType000_012( char *dialogName ); /* Ver.3.70 */
short ExecSetConfigType000_013( char *dialogName ); /* Ver.3.70 */
short ExecSetConfigType000_014( char *dialogName ); /* Ver.3.70 */
short ExecSetConfigType000_015( char *dialogName ); /* Ver.3.70 */
short ExecSetConfigType000_016( char *dialogName ); /* Ver.3.70 */
short ExecSetConfigType000_017( char *dialogName ); /* Ver.3.80 */
short ExecSetConfigType000_018( char *dialogName ); /* Ver.3.80 */
short ExecSetConfigType001_000( char *dialogName );
//short ExecSetConfigType001_001( char *dialogName );
//short ExecSetConfigType001_002( char *dialogName );
//short ExecSetConfigType001_003( char *dialogName );
//short ExecSetConfigType001_004( char *dialogName ); /* Ver.3.50 */
//short ExecSetConfigType001_005( char *dialogName ); /* Ver.3.50 */
//short ExecSetConfigType001_006( char *dialogName ); /* Ver.3.60 */
//short ExecSetConfigType001_007( char *dialogName ); /* Ver.3.60 */
//short ExecSetConfigType001_008( char *dialogName ); /* Ver.3.60 */
//unsigned int GetFlagSetConfigType002( void );
short ExecSetConfigType002_000( char *dialogName );
short ExecSetConfigType003_000( char *dialogName );
short ExecSetConfigType004_000( char *dialogName );
#endif
