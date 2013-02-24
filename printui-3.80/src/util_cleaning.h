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


#ifndef _UTIL_CLEANING_H_
#define _UTIL_CLEANING_H_

short OutputUtilityCommand_CMD_CLEANING_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_CLEANING_TYPE002( short index, COMMANDDATA *cmdData, short cmdNum );
short ExecCleaningType000_000( char *dialogName );
short ExecCleaningType000_001( char *dialogName );
short ExecCleaningType000_002( char *dialogName );
short ExecCleaningType000_003( char *dialogName );
short ExecCleaningType000_004( char *dialogName ); /* Ver.3.80 */
short ExecCleaningType000_005( char *dialogName ); /* Ver.3.80 */
short ExecCleaningType001_000( char *dialogName );
short ExecCleaningType001_001( char *dialogName );
short ExecCleaningType001_002( char *dialogName );
short ExecCleaningType001_003( char *dialogName );
short ExecCleaningType001_004( char *dialogName );
short ExecCleaningType002_000( char *dialogName );
short ExecCleaningType002_001( char *dialogName );
short ExecCleaningType002_002( char *dialogName );
short ExecCleaningType002_003( char *dialogName );
short ExecCleaningType002_004( char *dialogName );
short ExecCleaningType001_005( char *dialogName );/* Ver.3.50 */
short ExecCleaningType001_006( char *dialogName );/* Ver.3.80 */

#endif
