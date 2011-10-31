/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2011
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


//#ifdef HAVE_CONFIG_H
//#  include <config.h>
//#endif

#include <gtk/gtk.h>
#ifdef	USE_LIB_GLADE
#	include <glade/glade.h>
#endif

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "bjuidefs.h"

#define IVEC_BUF_SIZE (1024)

static int ConnectToServer()
{
	int fd;
	struct sockaddr_un addr;

	memset( &addr, 0, sizeof(addr) );

	if( g_socketname == NULL )
		return -1;

	if( (fd = socket(PF_UNIX, SOCK_STREAM, 0)) >= 0 )
	{
		addr.sun_family = AF_UNIX;
		strncpy(addr.sun_path, g_socketname, sizeof(addr.sun_path));
		addr.sun_path[sizeof(addr.sun_path) - 1] = '\0';

		if( connect(fd, (struct sockaddr *)&addr, sizeof(addr)) != -1 )
		{
			return fd;
		}
		close(fd);
	}
	return -1;
}

int PutIPCData(LPIPCU pipc)
{
	int fd;
	char buf[IPCCMDLEN];

	if( (fd = ConnectToServer()) == -1 )
		return -1;

	// Write "PRINT" command first.
	strncpy(buf, "PRINT", IPCCMDLEN);
	buf[IPCCMDLEN -1] = '\0';
	write(fd, buf, IPCCMDLEN);

	// And for the time being, simply just write the contents of pipc.
	write(fd, pipc, sizeof(IPCU));

	close(fd);
	return 0;
}

int PutCancel()
{
	int fd;
	char buf[IPCCMDLEN];

	if( (fd = ConnectToServer()) == -1 )
		return -1;

	// Write "CANCEL" command.
	strncpy(buf, "CANCEL", IPCCMDLEN);
	buf[IPCCMDLEN -1] = '\0';
	write(fd, buf, IPCCMDLEN);

	close(fd);
	return 0;
}

int PutPrintData(char *cmdsbuf, short length)
{
	int fd;
	IPCU ipc;
	char buf[IVEC_BUF_SIZE];
	char *curPtr;
	long cmdLen = 0;
	int retVal = -1;

	if( (fd = ConnectToServer()) == -1 ) goto Err1;

	// Write "PDATA" command first.
	strncpy(buf, "PDATA", IVEC_BUF_SIZE);
	buf[IVEC_BUF_SIZE -1] = '\0';
	write(fd, buf, IPCCMDLEN);

	if ( (IsIVECModel() == TRUE) && (g_bidi_mode == FALSE) ){
		curPtr = ipc.cmds.cmds;

		/* Start job */
		if ( CNCL_MakePrintCommand( CNCL_COMMAND_START1 , buf ,IVEC_BUF_SIZE , NULL , "1" ) != CNCL_OK ) goto Err2;
		if ( (cmdLen = strlen( buf )) > IVEC_BUF_SIZE ) cmdLen = IVEC_BUF_SIZE - 1;
		memcpy( curPtr, buf, cmdLen );
		curPtr += cmdLen;
		
		/* Mode shift */	
		if ( CNCL_MakePrintCommand( CNCL_COMMAND_START2 , buf ,IVEC_BUF_SIZE , NULL , NULL ) != CNCL_OK ) goto Err2;
		if ( (cmdLen = strlen( buf )) > IVEC_BUF_SIZE ) cmdLen = IVEC_BUF_SIZE - 1;
		memcpy( curPtr, buf, cmdLen );
		curPtr += cmdLen;

		/* BJL data */
		/* length -1 : remove 0 data */
		memcpy( curPtr, cmdsbuf, (length-1) );
		curPtr += (length - 1);

		/* End job */
		if ( CNCL_MakePrintCommand( CNCL_COMMAND_END , buf ,IVEC_BUF_SIZE , NULL , NULL ) != CNCL_OK ) goto Err2;
		if ( (cmdLen = strlen( buf )) > IVEC_BUF_SIZE ) cmdLen = IVEC_BUF_SIZE - 1;
		memcpy( curPtr, buf, cmdLen );
		curPtr += cmdLen;

		/* Add terminate */
		*curPtr = 0x00;
		curPtr++;

		ipc.cmds.cmdslen = (long)(curPtr - ipc.cmds.cmds);
	}
	else {
		ipc.cmds.cmdslen = (long)length;
		memcpy(ipc.cmds.cmds, cmdsbuf, length);
	}	

	write(fd, &ipc, sizeof(IPCU));
	retVal = 0;
Err2:
	close(fd);
Err1:
	return retVal;
}

int PutDeviceData(char *cmdsbuf, short length, char *devMode )
{
	int fd;
	IPCU ipc;
	char buf[IVEC_BUF_SIZE];
	long cmdLen = 0;
	short cmdType;
	int retVal = -1;
	char *curPtr;
	char *model_name;

	model_name = GetModelName();

	if ( (devMode == NULL) || (devMode == NULL) ) goto Err1;

	if ( strcmp( devMode, "POWEROFF" ) == 0 ){
		cmdType = CNCL_COMMAND_POWEROFF;
	}
	else {
		goto Err1;
	}
	
	if( (fd = ConnectToServer()) == -1 ) goto Err1;

	// Write "POWEROFF" command first.
	strncpy(buf, devMode, IVEC_BUF_SIZE);
	buf[IVEC_BUF_SIZE-1] = '\0';
	write(fd, buf, IPCCMDLEN);

	if ( (IsIVECModel() == TRUE) ){
		curPtr = ipc.cmds.cmds;

#if 0
		if ( isAllOutputSetTime( model_name ) ){

			/* Start job */
			if ( CNCL_MakePrintCommand( CNCL_COMMAND_START1 , buf ,IVEC_BUF_SIZE , NULL , "1" ) != CNCL_OK ) goto Err2;
			if ( (cmdLen = strlen( buf )) > IVEC_BUF_SIZE ) cmdLen = IVEC_BUF_SIZE - 1;
			memcpy( curPtr, buf, cmdLen );
			curPtr += cmdLen;

			/* Mode shift */	
			if ( CNCL_MakePrintCommand( CNCL_COMMAND_START2 , buf ,IVEC_BUF_SIZE , NULL , NULL ) != CNCL_OK ) goto Err2;
			if ( (cmdLen = strlen( buf )) > IVEC_BUF_SIZE ) cmdLen = IVEC_BUF_SIZE - 1;
			memcpy( curPtr, buf, cmdLen );
			curPtr += cmdLen;

			cmdLen = WriteSetTime2Buf( curPtr ); curPtr += cmdLen;

			/* End job */
			if ( CNCL_MakePrintCommand( CNCL_COMMAND_END , buf ,IVEC_BUF_SIZE , NULL , NULL ) != CNCL_OK ) goto Err2;
			if ( (cmdLen = strlen( buf )) > IVEC_BUF_SIZE ) cmdLen = IVEC_BUF_SIZE - 1;
			memcpy( curPtr, buf, cmdLen );
			curPtr += cmdLen;
		
		}
#endif
		if ( CNCL_MakeDeviceCommand( cmdType, buf ,IVEC_BUF_SIZE ) != CNCL_OK ) goto Err2;
		if ( (cmdLen = strlen( buf )) > IVEC_BUF_SIZE ) cmdLen = IVEC_BUF_SIZE - 1;
		memcpy( curPtr, buf, cmdLen );
		curPtr += cmdLen;

		/* Add terminate */
		*curPtr = 0x00;
		curPtr++;

		ipc.cmds.cmdslen = (long)(curPtr - ipc.cmds.cmds);
	}
	else {
		ipc.cmds.cmdslen = (long)length;
		memcpy( ipc.cmds.cmds, cmdsbuf, length );
	}

	write(fd, &ipc, sizeof(IPCU));
	retVal = 0;
Err2:
	close(fd);
Err1:
	return retVal;

}

int PutFileData(char *cmdsbuf, short cmds_length, 
				char *fnamebuf, short fname_length)
{

	int fd;
	char buf[IPCCMDLEN];
	IPCU ipc;

	if( (fd = ConnectToServer()) == -1 )
		return -1;

	// Write "FDATA" command first.
	strncpy(buf, "FDATA", IPCCMDLEN);
	buf[IPCCMDLEN -1] = '\0';
	write(fd, buf, IPCCMDLEN);

	// Prepare for ipc union, then copy buffer data.
	ipc.fncmds.cmdslen = (long)cmds_length;
	ipc.fncmds.filenamelen = (long)fname_length;
	memcpy(ipc.fncmds.cmds, cmdsbuf, cmds_length);
	memcpy(ipc.fncmds.filename, fnamebuf, fname_length);
	write(fd, &ipc, sizeof(IPCU));

	close(fd);
	return 0;
}

int PutDoubleData(char *cmdsbuf, short cmds_length, 
				  char *fnamebuf, short fname_length)
{

	int fd;
	char buf[IPCCMDLEN];
	IPCU ipc;

	if( (fd = ConnectToServer()) == -1 )
		return -1;

	// Write "FDATA" command first.
	strncpy(buf, "WDATA", IPCCMDLEN);
	buf[IPCCMDLEN -1] = '\0';
	write(fd, buf, IPCCMDLEN);

	// Prepare for ipc union, then copy buffer data.
	ipc.fncmds.cmdslen = (long)cmds_length;
	ipc.fncmds.filenamelen = (long)fname_length;
	memcpy(ipc.fncmds.cmds, cmdsbuf, cmds_length);
	memcpy(ipc.fncmds.filename, fnamebuf, fname_length);
	write(fd, &ipc, sizeof(IPCU));

	close(fd);
	return 0;
}

int PutExecLM()
{
	int fd;
	char buf[IPCCMDLEN];

	if( (fd = ConnectToServer()) == -1 )
		return -1;

	// Write "EXECLM" command.
	strncpy(buf, "EXECLM", IPCCMDLEN);
	buf[IPCCMDLEN -1] = '\0';
	write(fd, buf, IPCCMDLEN);

	close(fd);
	return 0;
}

