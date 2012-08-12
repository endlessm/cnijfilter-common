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
#include "bjferror.h"

/* function prototypes */
short bjf_error( char *, short );


short bjf_error( char *message, short err_code )
{
	if ( err_code == NO_ERROR ) return 0;
	
	fprintf( stderr, "CIF COMMAND ERROR :" );
	
	switch( err_code ){
		case FILE_ERROR:
			fprintf( stderr, "file access Error!\n" );
			break;
		case MEMORY_ERROR:
			fprintf( stderr, "memory allocate Error!\n" );
			break;
		default:
			break;
	}
	
	
	if ( message != NULL ){
		fprintf( stderr, "%s\n", message );
	}
	
	return 0;
}
