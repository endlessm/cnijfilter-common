/*
 *  Canon Inkjet Printer Driver for Linux
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

/*----------------------------------------------------------
	bjflist.h
----------------------------------------------------------*/

#ifndef __BJFLIST_H__
#define __BJFLIST_H__

#define	BJF_TAIL_NODE	(0)
#define	BJF_HEAD_NODE	(1)

/* structure define */
typedef struct mynode
{
	short			curCopies;
	short			dummy;
	struct mynode	*prev;
	struct mynode	*next;
	char			fileName[32];
} BJF_NODE, *LPBJF_NODE;

/* structure define */
typedef struct
{
	short		Copies;
	short		isCollate;
	short		isRPrint;
	short		isDuplex;

	LPBJF_NODE	head;
	LPBJF_NODE	tail;
} BJF_ROOT, *LPBJF_ROOT;

#define	bjf_exist_q(x)		( (x)->head != NULL )

extern LPBJF_ROOT bjf_create_root(void);
extern short bjf_init_root( LPBJF_ROOT root, short copies, short collate, short reverse );
extern short bjf_dispose_root( LPBJF_ROOT root );

extern LPBJF_NODE bjf_new_q( char *fileName );
extern LPBJF_NODE bjf_put_q( LPBJF_ROOT root, LPBJF_NODE node );
extern short bjf_dispose_q( LPBJF_ROOT root, short type );

#endif
