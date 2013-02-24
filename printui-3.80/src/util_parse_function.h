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


#ifndef _UTIL_PARSE_FUNCTION_H_
#define _UTIL_PARSE_FUNCTION_H_

enum {
	FUNCTYPE_CLEANING = 1,
	FUNCTYPE_DEEP_CLEANING,
	FUNCTYPE_ROLLER_CLEANING,
	FUNCTYPE_PLATE_CLEANING,
	FUNCTYPE_NOZZLE_CHECK,
	FUNCTYPE_POWER_OFF,
	FUNCTYPE_AUTOPOWER,
	FUNCTYPE_INK_WARNING,
	FUNCTYPE_INK_RESET,
	FUNCTYPE_INK_CARTRIDGE,
	FUNCTYPE_QUIET,
	FUNCTYPE_HEAD_ALIGNMENT_AUTO,
	FUNCTYPE_HEAD_ALIGNMENT_MANUAL,
	FUNCTYPE_CUSTOM,
	FUNCTYPE_PAPER_SOURCE_SETTING,
};

typedef struct functioncomp{
	short type;
	char *flow;
	struct functioncomp *next;
} FUNCTIONCOMP, *LPFUNCTIONCOMP;

short FreeFunctionCompList( FUNCTIONCOMP *list ) ;
short ParseFunctionListTag( char *fname, char *dialogName, FUNCTIONCOMP **list );

#endif
