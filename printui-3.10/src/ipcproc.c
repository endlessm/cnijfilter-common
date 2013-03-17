/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2013
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

static int ConnectToServer()
{
	int fd;
	struct sockaddr_un addr;

	if( g_socketname == NULL )
		return -1;

	if( (fd = socket(PF_UNIX, SOCK_STREAM, 0)) >= 0 )
	{
		addr.sun_family = AF_UNIX;
		strcpy(addr.sun_path, g_socketname);

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
	int fd, __attribute__ ((unused)) result2;
	char buf[IPCCMDLEN];

	if( (fd = ConnectToServer()) == -1 )
		return -1;

	// Write "PRINT" command first.
	strcpy(buf, "PRINT");
	result2 = write(fd, buf, IPCCMDLEN);

	// And for the time being, simply just write the contents of pipc.
	result2 = write(fd, pipc, sizeof(IPCU));

	close(fd);
	return 0;
}

int PutCancel()
{
	int fd, __attribute__ ((unused)) result2;
	char buf[IPCCMDLEN];

	if( (fd = ConnectToServer()) == -1 )
		return -1;

	// Write "CANCEL" command.
	strcpy(buf, "CANCEL");
	result2 = write(fd, buf, IPCCMDLEN);

	close(fd);
	return 0;
}

int PutPrintData(char *cmdsbuf, short length)
{
	int fd, __attribute__ ((unused)) result2;
	char buf[IPCCMDLEN];
	IPCU ipc;

	if( (fd = ConnectToServer()) == -1 )
		return -1;

	// Write "PDATA" command first.
	strcpy(buf, "PDATA");
	result2 = write(fd, buf, IPCCMDLEN);

	// Prepare for ipc union, then copy buffer data.
	ipc.cmds.cmdslen = (long)length;
	memcpy(ipc.cmds.cmds, cmdsbuf, length);
	result2 = write(fd, &ipc, sizeof(IPCU));

	close(fd);
	return 0;
}

int PutFileData(char *cmdsbuf, short cmds_length, 
				char *fnamebuf, short fname_length)
{

	int fd, __attribute__ ((unused)) result2;
	char buf[IPCCMDLEN];
	IPCU ipc;

	if( (fd = ConnectToServer()) == -1 )
		return -1;

	// Write "FDATA" command first.
	strcpy(buf, "FDATA");
	result2 = write(fd, buf, IPCCMDLEN);

	// Prepare for ipc union, then copy buffer data.
	ipc.fncmds.cmdslen = (long)cmds_length;
	ipc.fncmds.filenamelen = (long)fname_length;
	memcpy(ipc.fncmds.cmds, cmdsbuf, cmds_length);
	memcpy(ipc.fncmds.filename, fnamebuf, fname_length);
	result2 = write(fd, &ipc, sizeof(IPCU));

	close(fd);
	return 0;
}

int PutDoubleData(char *cmdsbuf, short cmds_length, 
				  char *fnamebuf, short fname_length)
{

	int fd, __attribute__ ((unused)) result2;
	char buf[IPCCMDLEN];
	IPCU ipc;

	if( (fd = ConnectToServer()) == -1 )
		return -1;

	// Write "FDATA" command first.
	strcpy(buf, "WDATA");
	result2 = write(fd, buf, IPCCMDLEN);

	// Prepare for ipc union, then copy buffer data.
	ipc.fncmds.cmdslen = (long)cmds_length;
	ipc.fncmds.filenamelen = (long)fname_length;
	memcpy(ipc.fncmds.cmds, cmdsbuf, cmds_length);
	memcpy(ipc.fncmds.filename, fnamebuf, fname_length);
	result2 = write(fd, &ipc, sizeof(IPCU));

	close(fd);
	return 0;
}

int PutExecLM()
{
	int fd, __attribute__ ((unused)) result2;
	char buf[IPCCMDLEN];

	if( (fd = ConnectToServer()) == -1 )
		return -1;

	// Write "EXECLM" command.
	strcpy(buf, "EXECLM");
	result2 = write(fd, buf, IPCCMDLEN);

	close(fd);
	return 0;
}

