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
	bjflist.c
----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bjflist.h"


/*---------------------------------------------------------------
	bjf_create_root
		create root data structure.
---------------------------------------------------------------*/
LPBJF_ROOT bjf_create_root(void)
{
	LPBJF_ROOT root = NULL;
	
	if( ( root = (LPBJF_ROOT)malloc( sizeof( BJF_ROOT ) ) ) == NULL )
		goto onErr;

	root->Copies		= -1;
	root->isCollate		= -1;
	root->isRPrint		= -1;

	root->head = NULL;
	root->tail = NULL;
onErr:
	return root;
}

/*---------------------------------------------------------------
	bjf_init_root
		set parameter to root.
---------------------------------------------------------------*/
short bjf_init_root( LPBJF_ROOT root, short copies, short collate, short reverse )
{
	short ret = -1;

	if( root == NULL )
		goto onErr;
	
	root->Copies = copies;
	root->isCollate = collate;
	root->isRPrint = reverse;
	
	ret = 0;

onErr:
	return ret;
}

/*---------------------------------------------------------------
	bjf_dispose_root
		dispose root data structure.
		if some nodes remain, must dispose nodes until return 0.
---------------------------------------------------------------*/
short bjf_dispose_root( LPBJF_ROOT root )
{
	if(root == NULL) return -1;
	if(root->tail != NULL ) return 1;

	free(root);
	return 0;
}

/*---------------------------------------------------------------
	bjf_new_q
		create queue.
---------------------------------------------------------------*/
LPBJF_NODE bjf_new_q( char *fileName )
{
	LPBJF_NODE	node = NULL;

	if (fileName == NULL) goto onErr;

	if ( (node = (LPBJF_NODE)malloc( sizeof(BJF_NODE) )) == NULL )
		goto onErr;

	strncpy( node->fileName, fileName, sizeof(node->fileName));
	node->fileName[sizeof(node->fileName) - 1] = '\0';
	node->curCopies = -1;
	node->prev = NULL;
	node->next = NULL;

onErr:
	return node;
}

/*---------------------------------------------------------------
	bjf_new_q
		put queue to root and set copies to node.
---------------------------------------------------------------*/
LPBJF_NODE bjf_put_q( LPBJF_ROOT root, LPBJF_NODE node )
{
	LPBJF_NODE ret = NULL;

	if ( root == NULL || node == NULL  )
		goto onErr;

	if( root->head == NULL )
		root->head = node; /* first node */
	
	if( root->tail != NULL ) {
		node->prev = root->tail;
		root->tail->next = node;
	}
	root->tail = node;
	node->curCopies = root->Copies;

	ret = node;

onErr:
	return ret;
}

/*---------------------------------------------------------------
	bjf_dispose_q
		dispose queue. 
		before call this function, must unlink tempfile.
---------------------------------------------------------------*/
short bjf_dispose_q( LPBJF_ROOT root, short type )
{
	short	ret = -1;
	LPBJF_NODE node = NULL;
	
	if ( root == NULL )
		goto onErr;
	
	if ( root->tail == NULL || root->head == NULL )
		goto onErr; /* no node */
	
	switch(type)
	{
		case BJF_TAIL_NODE :
			/* remove node. */
			node = root->tail;
			root->tail = node->prev;
			
			if( node->prev == NULL)
				root->head = NULL; /* removed last node. */
			else
				node->prev->next = NULL;

			break;
			
		case BJF_HEAD_NODE :
			/* remove node. */
			node = root->head;
			root->head = node->next;
			
			if( node->next == NULL)
				root->tail = NULL; /* removed last node. */
			else
				node->next->prev = NULL;

			break;
	}

	free(node);
	ret = 0;
	
onErr:
	return ret;
}

