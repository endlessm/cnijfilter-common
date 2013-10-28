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

#include "util_parse_function.h"

static short NewFunctionComp( FUNCTIONCOMP **functionComp, short type, char *flow )
{
	LPFUNCTIONCOMP lpComp;
	short result = -1;

	if ( functionComp == NULL ) goto Err1;
	if ((lpComp = (LPFUNCTIONCOMP)malloc(sizeof(FUNCTIONCOMP))) == NULL) goto Err1;

	lpComp->type = type;

	if ( (lpComp->flow = (char *)malloc(strlen(flow) + 1)) == NULL ) goto Err2;
	strncpy( lpComp->flow, flow, strlen(flow) + 1 );
	lpComp->flow[strlen(flow)] = '\0';

	lpComp->next = NULL;
	*functionComp = lpComp;

	result = 0;
EXIT:
	return result;

Err2:
	if ( lpComp != NULL ) free( lpComp );
Err1:
	goto EXIT;
}

static short AppendFunctionComp( FUNCTIONCOMP *root, FUNCTIONCOMP *append )
{
	short result = -1;
	FUNCTIONCOMP *current;

	if ( (root == NULL) || (append == NULL) ) goto Err;
	current = root;

	while( current->next != NULL ){
		current = current->next;
	}
	current->next = append;

	result = 0;
Err:
	return result;
}

static short FreeFunctionComp( FUNCTIONCOMP *current )
{
	short result = -1;
	if ( current == NULL ) goto Err;

	if ( current->flow != NULL ){
		free( current->flow );
		current->flow = NULL;
	}
	free( current );

	result = 0;
Err:
	return result;	
}

short FreeFunctionCompList( FUNCTIONCOMP *list ) 
{
	FUNCTIONCOMP *current, *prev = NULL;
	short result = -1;

	if ( list == NULL ) goto Err;
	current = (FUNCTIONCOMP *)list;
	if ( current == NULL ) goto Err;

	while ( 1 ){
		current = (FUNCTIONCOMP *)list;
		if ( current->next == NULL ) {
			if ( FreeFunctionComp( current ) != 0 ) goto Err;
			break;
		}

		while( current->next != NULL ){
			prev = current;
			current = current->next;
		}
		if ( FreeFunctionComp( current ) != 0 ) goto Err;
		prev->next = NULL;
	}

	result = 0;
Err:
	return result;
}

static short ParseFunctionTag( xmlNodePtr ptr, char *modelName, LPFUNCTIONCOMP lpRootComp )
{
	xmlNodePtr current = ptr;
	LPFUNCTIONCOMP lpComp;
	short type;
	char *flow;
	short result = -1;

	if ( (ptr == NULL) || (lpRootComp == NULL) ) goto Err;

	lpComp = NULL;
	while( current != NULL ) {
		if ( !xmlStrcmp( current->name, (const xmlChar *)"function" ) ){
			type = (short)atoi( (char *)xmlGetProp( current, (const xmlChar *)"type" ) );
			flow = (char *)xmlGetProp( current, (const xmlChar *)"flow" );
			
			if ( NewFunctionComp( &lpComp, type, flow ) != 0 ) goto Err;
			AppendFunctionComp( lpRootComp, lpComp );
		}
		current = current->next;
	}

	result = 0;
Err:
	return result;
}

static short ParseFunctionsTag( xmlNodePtr ptr, char *modelName, LPFUNCTIONCOMP lpRootComp )
{
	xmlNodePtr current = ptr;
	char *data;
	short result = -1;

	if ( (ptr == NULL) || (lpRootComp == NULL) ) goto Err;

	while( current != NULL ){
		if ( !xmlStrcmp( current->name, (const xmlChar *)"functions" ) ){
			data = (char *)xmlGetProp( current, (const xmlChar *)"model" );
			if ( data == NULL ) goto Err;

			if ( !xmlStrcmp( (const xmlChar *)data, (const xmlChar *)modelName ) ){
				if ( ParseFunctionTag( current->xmlChildrenNode, modelName, lpRootComp ) != 0 ) goto Err;
				break;
			}
		}
		current = current->next;
	}

	result = 0;
Err:
	return result;
}

short ParseFunctionListTag( char *fname, char *dialogName, FUNCTIONCOMP **list )
{
	xmlDocPtr doc = NULL;
	xmlNodePtr current;
	FUNCTIONCOMP rootComp;
	short result = -1;

	if ( list == NULL ) goto Err1;

	if ( (doc = xmlParseFile( fname )) == NULL ) goto Err1;
	current = xmlDocGetRootElement( doc );
	if ( (current == NULL) || xmlStrcmp( current->name, (const xmlChar *)"maintenance-resource" ) ){
		goto Err2;
	}

	memset( &rootComp, 0, sizeof(FUNCTIONCOMP) );
	current = current->xmlChildrenNode;
	while ( current != NULL ){
		if ( (!xmlStrcmp( current->name, (const xmlChar *)"functionlist" )) ){
			if ( ParseFunctionsTag( current->xmlChildrenNode, dialogName, &rootComp ) != 0 ) goto Err2;
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
	FreeFunctionCompList( rootComp.next );	
Err1:
	goto EXIT;
}

