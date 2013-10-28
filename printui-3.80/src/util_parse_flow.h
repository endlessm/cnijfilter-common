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


#ifndef _UTIL_PARSE_FLOW_H_
#define _UTIL_PARSE_FLOW_H_

typedef struct flowcomp{
	short	id;
	short	action;
	short	next_id;
	char	*funcName;
	char	*flowName;
	char	*cmdName;
	struct flowcomp *next;
} FLOWCOMP, *LPFLOWCOMP;

// function prototypes
short ParseFlowListTag( char *fname, void **list );
short FreeFlowCompList( void *list );
short GetFuncNameFromFlowList( void *list, char *flowName, short id, char **funcName );
short GetNextIdFromFlowList( void *list, char *flowName, short id, short action, short *next_id );
short GetCommandNameFromFLowList( void *list, char *flowName, short id, short action, char **cmdName );

#endif
