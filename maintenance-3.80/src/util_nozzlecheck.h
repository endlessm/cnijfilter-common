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


#ifndef _UTIL_NOZZLECHECK_H_
#define _UTIL_NOZZLECHECK_H_

void InitExec_NozzleCheck( void );
short OutputUtilityCommand_CMD_NozzleCheck_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum );
short ExecNozzleCheckType000_000( char *dialogName );
short ExecNozzleCheckType000_001( char *dialogName );
short ExecNozzleCheckType000_002( char *dialogName );
short ExecNozzleCheckType000_003( char *dialogName );
short ExecNozzleCheckType000_004( char *dialogName );
short ExecNozzleCheckType001_000( char *dialogName );
short ExecNozzleCheckType002_000( char *dialogName );
short ExecNozzleCheckType002_001( char *dialogName );
void SetPaperSourceInfoType000_004( void );

#endif
