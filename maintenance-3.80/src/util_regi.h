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


#ifndef _UTIL_REGI_H_
#define _UTIL_REGI_H_

short OutputUtilityCommand_CMD_REGI_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum );
short OutputUtilityCommand_CMD_REGI_TYPE002( short index, COMMANDDATA *cmdData, short cmdNum );
extern short ExecRegiType000_000( char *dialogName );
extern short ExecRegiType000_001( char *dialogName );
extern short ExecRegiType000_002( char *dialogName );
extern short ExecRegiType000_003( char *dialogName ); /* Ver.3.80 */
extern short ExecRegiType001_000( char *dialogName );
extern short ExecRegiType001_001( char *dialogName );
extern short ExecRegiType001_002( char *dialogName );
extern short ExecRegiType001_003( char *dialogName );
extern short ExecRegiType001_004( char *dialogName );
extern short ExecRegiType001_005( char *dialogName );
extern short ExecRegiType001_006( char *dialogName ); /* Ver.3.50 */
extern short ExecRegiType001_007( char *dialogName ); /* Ver.3.50 */
extern short ExecRegiType001_008( char *dialogName ); /* Ver.3.60 */
extern short ExecRegiType001_009( char *dialogName ); /* Ver.3.60 */
extern short ExecRegiType001_010( char *dialogName ); /* Ver.3.60 */
extern short ExecRegiType001_011( char *dialogName ); /* Ver.3.70 */
extern short ExecRegiType001_012( char *dialogName ); /* Ver.3.70 */
extern short ExecRegiType001_013( char *dialogName ); /* Ver.3.70 */
extern short ExecRegiType001_014( char *dialogName ); /* Ver.3.80 */
extern short ExecRegiType001_015( char *dialogName ); /* Ver.3.80 */
extern short ExecRegiType001_016( char *dialogName ); /* Ver.3.80 */
extern short ExecRegiType002_000( char *dialogName );
extern short ExecRegiType002_001( char *dialogName );
extern short ExecRegiType002_002( char *dialogName );
extern short ExecRegiType002_003( char *dialogName );
extern short ExecRegiType002_004( char *dialogName );
extern short ExecRegiType002_005( char *dialogName ); /* Ver.3.70 */
extern short ExecRegiType002_006( char *dialogName ); /* Ver.3.70 */
extern short ExecRegiType002_007( char *dialogName ); /* Ver.3.70 */
extern short ExecRegiType002_008( char *dialogName ); /* Ver.3.70 */
extern short ExecRegiType002_009( char *dialogName ); /* Ver.3.80 */
extern short ExecRegiType003_000( char *dialogName );
extern short ExecRegiType003_001( char *dialogName );
extern short ExecRegiType003_002( char *dialogName );
extern short ExecRegiType003_003( char *dialogName );
extern short ExecRegiType003_004( char *dialogName );
extern short ExecRegiType003_005( char *dialogName );

#endif
