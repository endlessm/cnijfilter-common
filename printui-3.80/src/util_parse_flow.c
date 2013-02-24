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


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>

#include "util_parse_flow.h"

static short NewFlowComp(  FLOWCOMP **flowComp, short id, short action, short next_id, char *funcName, char *flowName, char *cmdName )
{
	short result = -1;
	LPFLOWCOMP lpFlowComp = NULL;

	if ( flowComp == NULL ) goto Err1;
	if ( (lpFlowComp = (FLOWCOMP *)malloc(sizeof(FLOWCOMP))) == NULL ) goto Err1;

	lpFlowComp->id = id;
	lpFlowComp->action = action;
	lpFlowComp->next_id = next_id;

	lpFlowComp->funcName = NULL;
	lpFlowComp->flowName = NULL;
	lpFlowComp->cmdName = NULL;
	if ( funcName != NULL ){
		if ( (lpFlowComp->funcName = (char *)malloc(strlen(funcName) + 1)) == NULL ) goto Err2;
		strncpy( lpFlowComp->funcName, funcName, strlen(funcName) + 1 );
		lpFlowComp->funcName[ strlen(funcName)] = '\0';
	}

	if ( flowName != NULL ){
		if ( (lpFlowComp->flowName = (char *)malloc(strlen(flowName) + 1))== NULL ) goto Err3;
		strncpy( lpFlowComp->flowName, flowName, strlen(flowName) + 1 );
		lpFlowComp->flowName[ strlen(flowName) ] = '\0';
	}

	if ( cmdName != NULL ){
		if ( (lpFlowComp->cmdName = (char *)malloc(strlen(cmdName) + 1))== NULL ) goto Err4;
		strncpy( lpFlowComp->cmdName, cmdName, strlen(cmdName) + 1 );
		lpFlowComp->cmdName[ strlen(cmdName) ] = '\0';
	}

	lpFlowComp->next = NULL;

	result = 0;
	*flowComp = lpFlowComp;
EXIT:
	return result;

Err4:
	if ( lpFlowComp->flowName != NULL ) free( lpFlowComp->flowName );
Err3:
	if ( lpFlowComp->funcName != NULL ) free( lpFlowComp->funcName );
Err2:
	if ( lpFlowComp != NULL ) free( lpFlowComp );
Err1:
	goto EXIT;
}


static short AppendFlowComp( FLOWCOMP *root, FLOWCOMP *append )
{
	short result = -1;
	FLOWCOMP *current = root;

	if ( (root == NULL) || (append == NULL) ) goto Err;

	while( current->next != NULL ){
		current = current->next;
	}
	current->next = append;

	result = 0;
Err:
	return result;
}


static short FreeFlowComp( FLOWCOMP *current )
{
	short result = -1;

	if ( current == NULL ) goto Err;
	
	if ( current->funcName != NULL ){
		free( current->funcName );
		current->funcName = NULL;
	}
	if ( current->flowName != NULL ){
		free( current->flowName );
		current->flowName = NULL;
	}
	free( current );

	result = 0;
Err:
	return result;	
}


short FreeFlowCompList( void *list )
{
	FLOWCOMP *current, *prev;
	short result = -1;

	if ( list == NULL ) goto Err;
	current = (FLOWCOMP *)list;
	if ( current == NULL ) goto Err;

	current = NULL;
	prev = NULL;
	while ( 1 ){
		current = (FLOWCOMP *)list;
		if ( current->next == NULL ) {
			if ( FreeFlowComp( current ) != 0 ) goto Err;
			break;
		}

		while( current->next != NULL ){
			prev = current;
			current = current->next;
		}
		if ( FreeFlowComp( current ) != 0 ) goto Err;
		prev->next = NULL;
	}

	result = 0;
Err:
	return result;
}


static short ParseStatusTag( xmlNodePtr ptr, char *flowName, LPFLOWCOMP lpRootComp )
{
	xmlNodePtr current = ptr;
	LPFLOWCOMP	lpFlowComp;
	char *funcName, *cmdName;
	short id, action, next_id;
	char *xmlData;
	short result = -1;

	if ( (ptr == NULL) || (lpRootComp == NULL) ) goto Err;

	id = -1;
	action = -1;
	next_id = -1;
	lpFlowComp = NULL;
	while( current != NULL ){
		if ( !xmlStrcmp( current->name, (const xmlChar *)"status" ) ){
			xmlData = (char *)xmlGetProp( current, (const xmlChar *)"id" );
			if ( xmlData != NULL ){
				id = (short)atoi( xmlData );
			}

			xmlData = (char *)xmlGetProp( current, (const xmlChar *)"action" );
			if ( xmlData != NULL ){
				action = (short)atoi( (char *)xmlGetProp( current, (const xmlChar *)"action" ) );
			}

			xmlData = (char *)xmlGetProp( current, (const xmlChar *)"next" );
			if ( xmlData != NULL ){
				next_id = (short)atoi( (char *)xmlGetProp( current, (const xmlChar *)"next" ) );
			}

			funcName = (char *)xmlGetProp( current, (const xmlChar *)"dialog" );
			cmdName = (char *)xmlGetProp( current, (const xmlChar *)"command" );

			if ( NewFlowComp( &lpFlowComp, id, action, next_id, funcName, flowName, cmdName ) != 0 ) goto Err;
			AppendFlowComp( lpRootComp, lpFlowComp );
		}
		current = current->next;
	}

	result = 0;
Err:
	return result;
}

static short ParseFlowTag( xmlNodePtr ptr, LPFLOWCOMP lpRootComp )
{
	xmlNodePtr current = ptr;
	char *flowName;
	short result = -1;

	if ( (ptr == NULL) || (lpRootComp == NULL) ) goto Err;

	while( current != NULL ){
		if ( !xmlStrcmp( current->name, (const xmlChar *)"flow" ) ){
			flowName = (char *)xmlGetProp( current, (const xmlChar *)"id" );
			if ( flowName == NULL ) goto Err;

			if ( ParseStatusTag( current->xmlChildrenNode, flowName, lpRootComp ) != 0 ) goto Err;
		}
		current = current->next;
	}

	result = 0;
Err:
	return result;
}


short ParseFlowListTag( char *fname, void **list )
{
	xmlDocPtr doc = NULL;
	xmlNodePtr current;
	FLOWCOMP rootComp;
	short result = -1;

	if ( list == NULL ) goto Err1;

	if ( (doc = xmlParseFile( fname )) == NULL ) goto Err1;
	current = xmlDocGetRootElement( doc );
	if ( (current == NULL) || xmlStrcmp( current->name, (const xmlChar *)"maintenance-resource" ) ){
		goto Err2;
	}

	memset( &rootComp, 0, sizeof(FLOWCOMP) );
	current = current->xmlChildrenNode;
	while ( current != NULL ){
		if ( (!xmlStrcmp( current->name, (const xmlChar *)"flowlist" )) ){
			if ( ParseFlowTag( current->xmlChildrenNode, &rootComp ) != 0 ) goto Err2;
			break;
		}
		current = current->next;
	}

	*list = rootComp.next;
	result = 0;
EXIT:
	xmlFreeDoc( doc );
	return result;

Err2:
	FreeFlowCompList( rootComp.next );	
Err1:
	goto EXIT;
}


short GetFuncNameFromFlowList( void *list, char *flowName, short id, char **funcName )
{
	LPFLOWCOMP lpFlowComp;
	short result = -1;

	lpFlowComp = (LPFLOWCOMP)list;

	while( lpFlowComp != NULL ){
		if ( (!strcmp( lpFlowComp->flowName, flowName )) && (lpFlowComp->id == id) ){
			*funcName = lpFlowComp->funcName;
			break;
		}
		lpFlowComp = lpFlowComp->next;
	}
	if ( lpFlowComp == NULL ) goto Err;

	result = 0;
Err:
	return result;
}

short GetNextIdFromFlowList( void *list, char *flowName, short id, short action, short *next_id )
{
	LPFLOWCOMP lpFlowComp;
	short result = -1;

	lpFlowComp = (LPFLOWCOMP)list;
	while( lpFlowComp != NULL ){
		if ( (!strcmp( lpFlowComp->flowName, flowName )) && (lpFlowComp->id == id) 
			&& (lpFlowComp->action == action) ){
			*next_id = lpFlowComp->next_id;
			break;	
		}
		lpFlowComp = lpFlowComp->next;
	}
	if ( lpFlowComp == NULL ) goto Err;

	result = 0;
Err:
	return result;
}

short GetCommandNameFromFLowList( void *list, char *flowName, short id, short action, char **cmdName )
{
	LPFLOWCOMP lpFlowComp;
	short result = -1;

	lpFlowComp = (LPFLOWCOMP)list;
	while( lpFlowComp != NULL ){
		if ( (!strcmp( lpFlowComp->flowName, flowName )) && (lpFlowComp->id == id) && (lpFlowComp->action == action) ){
			*cmdName = lpFlowComp->cmdName;
			break;	
		}
		lpFlowComp = lpFlowComp->next;
	}
	if ( lpFlowComp == NULL ) goto Err;

	result = 0;
Err:
	return result;
}

