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


#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>

#include "util_parse_dialogstr.h"

static short NewDialogStrComp( DIALOGSTRCOMP **dialogStrComp, short type, char *label, char *strid )
{
	LPDIALOGSTRCOMP lpDialogStrComp;
	short result = -1;

	if ( dialogStrComp == NULL ) goto Err1;
	if ((lpDialogStrComp = (LPDIALOGSTRCOMP)malloc(sizeof(DIALOGSTRCOMP))) == NULL) goto Err1;

	lpDialogStrComp->type = type;

	if ( (lpDialogStrComp->label = (char *)malloc(strlen(label) + 1)) == NULL ) goto Err2;
	strncpy( lpDialogStrComp->label, label, strlen(label) + 1 );
	lpDialogStrComp->label[strlen(label)] = '\0';
	
	if ( (lpDialogStrComp->strid = (char *)malloc(strlen(strid) + 1)) == NULL ) goto Err3;	
	strncpy( lpDialogStrComp->strid, strid, strlen(strid) + 1 );
	lpDialogStrComp->strid[strlen(strid)] = '\0';
	
	lpDialogStrComp->next = NULL;
	*dialogStrComp = lpDialogStrComp;

	result = 0;
EXIT:
	return result;

Err3:
	if ( lpDialogStrComp->label != NULL ) free( lpDialogStrComp->label );
Err2:
	if ( lpDialogStrComp != NULL ) free( lpDialogStrComp );
Err1:
	goto EXIT;
}

static short AppendDialogStrComp( DIALOGSTRCOMP *root, DIALOGSTRCOMP *append )
{
	short result = -1;
	DIALOGSTRCOMP *current;

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

static short FreeDialogStrComp( DIALOGSTRCOMP *current )
{
	short result = -1;
	if ( current == NULL ) goto Err;

	if ( current->label != NULL ){
		free( current->label );
		current->label = NULL;
	}
	if ( current->strid != NULL ){
		free( current->strid );
		current->strid= NULL;
	}
	free( current );

	result = 0;
Err:
	return result;	
}

short FreeDialogStrCompList( DIALOGSTRCOMP *list ) 
{
	DIALOGSTRCOMP *current, *prev = NULL;
	short result = -1;

	if ( list == NULL ) goto Err;
	current = (DIALOGSTRCOMP *)list;
	if ( current == NULL ) goto Err;

	while ( 1 ){
		current = (DIALOGSTRCOMP *)list;
		if ( current->next == NULL ) {
			if ( FreeDialogStrComp( current ) != 0 ) goto Err;
			break;
		}

		while( current->next != NULL ){
			prev = current;
			current = current->next;
		}
		if ( FreeDialogStrComp( current ) != 0 ) goto Err;
		prev->next = NULL;
	}

	result = 0;
Err:
	return result;
}

static short ParseStringTag( xmlNodePtr ptr, char *dialogName, LPDIALOGSTRCOMP lpRootComp )
{
	xmlNodePtr current = ptr;
	LPDIALOGSTRCOMP lpDialogStrComp;
	short type;
	char *label, *strid;
	short result = -1;

	if ( (ptr == NULL) || (lpRootComp == NULL) ) goto Err;

	lpDialogStrComp = NULL;
	while( current != NULL ) {
		if ( !xmlStrcmp( current->name, (const xmlChar *)"string" ) ){
			type = (short)atoi( (char *)xmlGetProp( current, (const xmlChar *)"type" ) );
			label = (char *)xmlGetProp( current, (const xmlChar *)"label" );
			strid = (char *)xmlGetProp( current, (const xmlChar *)"strid" );
			
			if ( NewDialogStrComp( &lpDialogStrComp, type, label, strid ) != 0 ) goto Err;
			AppendDialogStrComp( lpRootComp, lpDialogStrComp );
		}
		current = current->next;
	}

	result = 0;
Err:
	return result;
}

static short ParseDialogStringTag( xmlNodePtr ptr, char *dialogName, LPDIALOGSTRCOMP lpRootComp )
{
	xmlNodePtr current = ptr;
	char *data;
	short result = -1;

	if ( (ptr == NULL) || (lpRootComp == NULL) ) goto Err;

	while( current != NULL ){
		if ( !xmlStrcmp( current->name, (const xmlChar *)"dialogstring" ) ){
			data = (char *)xmlGetProp( current, (const xmlChar *)"id" );
			if ( data == NULL ) goto Err;

			if ( !xmlStrcmp( (const xmlChar *)data, (const xmlChar *)dialogName ) ){
				if ( ParseStringTag( current->xmlChildrenNode, dialogName, lpRootComp ) != 0 ) goto Err;
				break;
			}
		}
		current = current->next;
	}

	result = 0;
Err:
	return result;
}


short ParseDialogStringListTag( char *fname, char *dialogName, DIALOGSTRCOMP **list )
{
	xmlDocPtr doc = NULL;
	xmlNodePtr current;
	DIALOGSTRCOMP rootComp;
	short result = -1;

	if ( list == NULL ) goto Err1;

	if ( (doc = xmlParseFile( fname )) == NULL ) goto Err1;
	current = xmlDocGetRootElement( doc );
	if ( (current == NULL) || xmlStrcmp( current->name, (const xmlChar *)"maintenance-resource" ) ){
		goto Err2;
	}

	memset( &rootComp, 0, sizeof(DIALOGSTRCOMP) );
	current = current->xmlChildrenNode;
	while ( current != NULL ){
		if ( (!xmlStrcmp( current->name, (const xmlChar *)"dialogstringlist" )) ){
			if ( ParseDialogStringTag( current->xmlChildrenNode, dialogName, &rootComp ) != 0 ) goto Err2;
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
	FreeDialogStrCompList( rootComp.next );	
Err1:
	goto EXIT;
}
