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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bjfrcaccess.h"
#include "bjfpath.h"

#define MODELLEN		128
#define MODELNUM		2



/* function prototypes */
static short read_tag( FILE **fp, char *objString );
static char *bjf_access_resource( char *rcFname, char *objString, char *rcString, short rcID, short fileflag, char *writeString );


/*-------------------------------------------------------------*/
short bjf_get_resource_id( char *rcFname, char *objString, char *rcString )
/*-------------------------------------------------------------*/
{
	char	*str = NULL;
	short	result = BJFRCACCESSERROR;

	if ( (str = bjf_access_resource( rcFname, objString, rcString, 0, 0, NULL )) == NULL ) goto onErr;

	result = (short)atoi( str );

onErr:
	return result;		
}

/*-------------------------------------------------------------*/
char *bjf_get_resource_string( char *rcFname, char *objString, short rcID )
/*-------------------------------------------------------------*/
{
	char 	*result = NULL;

	if ( (result = bjf_access_resource( rcFname, objString, NULL, rcID, 0, NULL )) == NULL ) goto onErr;

onErr:
	return result;
}


/*-------------------------------------------------------------*/
char *bjf_put_resource_string( char *rcFname, char *objString, short rcID, char *writeString )
/*-------------------------------------------------------------*/
{
	char 	*result = NULL;

	if ( (result = bjf_access_resource( rcFname, objString, NULL, rcID, 1 , writeString)) == NULL ) goto onErr;

onErr:
	return result;
}

static char *bjf_access_resource( char *rcFname, char *objString, char *rcString, short rcID, short fileflag, char *writeString )
{
	FILE		*fp = NULL;
	int			num,str;
	int			isSpace,isObject, strnum;
	short		id = 0;
	short		i = 0;
	char		nambuf[MODELLEN];
	char		*ptr[MODELNUM];
	char		*result = NULL;
	static char tmpbuf[MODELLEN];
	short		flag;


	for( i=0 ; i<MODELNUM ; i++ ) ptr[i] = NULL;

	if ( fileflag == 0 ){
		if ( (fp = fopen( rcFname, "r" )) == NULL ) goto onErr;
	}
	else
	{
		if ( (fp = fopen( rcFname, "r+" )) == NULL ) goto onErr;
	}

	num = str = strnum = 0;
	isSpace = 1; isObject = 0;
	while ( (str = fgetc( fp )) != EOF ){
		
		if ( str == '[' ){
			if ( read_tag( &fp, objString ) == 0 )	isObject = 1; /* hit objString */
			else									isObject = 0; /* not hit objString */
		}
		else{
			if ( isObject == 1 ) {		/* search rcString and rcID */
				if ( num > MODELLEN ) goto onErr;

				if ( str == 0x0A ){
					nambuf[num] = 0x00;	/* string terminate */
					
					/*
						ptr[0] : ptr for parameter string
						ptr[1] : ptr for id string
					*/
					if ( rcString != NULL ){
						if( ptr[0] != NULL ){
							if ( strcmp( rcString, ptr[0]  ) == 0 ){
#if DEBUG
								fprintf( stderr, "Find ModelID !\n" );
								fprintf( stderr, "Printer Model : %s\n", ptr[0] );
#endif
								strncpy( tmpbuf, ptr[1], sizeof(tmpbuf) ); result = tmpbuf;
								tmpbuf[sizeof(tmpbuf) - 1] = '\0';
								goto onErr;
							}
							else {
								/* Re Initialize */
								num = str = strnum = 0;
								isSpace = 1;
							}
						}else{
							/* Re Initialize */
							num = str = strnum = 0;
							isSpace = 1;
						}
					}
					else {
						if( ptr[1] != NULL ){
							id = (short)atoi( ptr[1] );
							if ( id == rcID ){
#if DEBUG
								fprintf( stderr, "Find ModelID !\n" );
								fprintf( stderr, "Printer Model : %s\n", ptr[0] );
#endif
								/* for bjfilterv230 */
								if(fileflag == 1){ 
									if( strlen(ptr[0]) != strlen(writeString) ) goto onErr;
									if( (fseek(fp, -(strlen(ptr[0]) + strlen(ptr[1]) + 2) ,SEEK_CUR) ) == -1 ) goto onErr;
									if( (fputs(writeString, fp) ) == EOF ) goto onErr;
								}
	
								strncpy( tmpbuf, ptr[0], sizeof(tmpbuf) ); result = tmpbuf;
								tmpbuf[sizeof(tmpbuf) - 1] = '\0';
								goto onErr;
							}
							
							else { /* Re Initialize */
								num = str = strnum = 0;
								isSpace = 1;
							}				
						}else{
							/* Re Initialize */
							num = str = strnum = 0;
							isSpace = 1;
						}
					}
					
				}
				else if ( (str == 0x09) || (str == 0x20) ){	/* tab and space */
					isSpace = 1;
					nambuf[num++] = 0x00;
				}
				else if ( str == 0x0D ) continue;
				else if ( str == 0x23 ){ 	/* # <- comment */
					while( (str = fgetc( fp )) != EOF ){
						if ( str == 0x0A ) break;
					}
				}
				else {
					if ( isSpace == 1 ){
						isSpace = 0;
						nambuf[num] = str;
						ptr[strnum++]	= &nambuf[num]; num++;
					
						if ( strnum >= 3 ) {
							fprintf( stderr, "cif.conf file format error!\n" );
							goto onErr;
						}
					}
					else{
						nambuf[num++] = str;
					}
				}
			}
		}	 
	}

onErr:
	if ( fp != NULL ) fclose( fp );
	return result;
}

static short read_tag( FILE **fp, char *objString )
{
	FILE		*tmpfp = NULL;
	int			str;
	char		nambuf[MODELLEN];
	short		num;
	short		result = -1;

	tmpfp = *fp;

	if ( tmpfp == NULL ) goto Exit;

	num = 0;	
	while( (str = fgetc( tmpfp )) != EOF ){
	
		if ( num > MODELLEN ) goto Exit;
		
		if ( str == 0x0A ){
			if ( strcmp( nambuf, objString ) == 0 ){
				result = 0; goto Exit;		/* hit object */
			}
			else{
				result = 1; goto Exit;		/* not hit object */
			}
		}
		else if ( str == ']' ){
			nambuf[num++] = 0x00;		/* add string terminate	*/
		}
		else if ( (str == 0x09) || (str == 0x20) ){
			;
		}
		else if ( str == 0x0D ) continue;
		else {
			nambuf[num++] = str;
		}
		
	}

Exit:
	*fp = tmpfp;	
	return result;
}

