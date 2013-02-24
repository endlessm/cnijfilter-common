/*
 *  CUPS add-on module for Canon Inkjet Printer.
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
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "cncl.h"
#include "cncldef.h"
#include "cncludef.h"
#include "cnclucom.h"

#include "bjipc.h"


int GetIPCData(LPIPCU pipc, char *sname)
{
	struct sockaddr_un sun;
	int server_fd;
	int client_fd;
	int __attribute__ ((unused)) result2;
	char buf[128];
	size_t len;
	short ret = RET_ERROR;

	if( (server_fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0 )
		return RET_ERROR;

	unlink(sname);

	sun.sun_family = AF_UNIX;
	strcpy(sun.sun_path, sname);

	len = sizeof(sun.sun_family) + strlen(sun.sun_path);

	if( bind(server_fd, (struct sockaddr *)&sun, len) )
		return RET_ERROR;

	if( listen(server_fd, 5) )
		return RET_ERROR;

	while( (client_fd = accept(server_fd, (struct sockaddr *)&sun, (socklen_t *)&len)) >= 0 )
	{
		/* read command first */
		result2 = read(client_fd, buf, IPCCMDLEN);

		if( strcmp(buf, "PRINT") == 0 )
		{											/* PRINT command */
			result2 = read(client_fd, pipc, sizeof(IPCU));
			close(client_fd);
			ret = RET_PRINT;
			break;
		}
		else if( strcmp(buf, "CANCEL") == 0 )
		{											/* CANCEL command */
			close(client_fd);
			ret = RET_CANCEL;
			break;
		}
		else if( strcmp(buf, "PDATA") == 0 )
		{											/* PDATA command (for maintenance) */
			result2 = read(client_fd, pipc, sizeof(IPCU));
			close(client_fd);
			ret = RET_PDATA;
			break;
		}
		else if( strcmp(buf, "POWEROFF") == 0 )
		{											/* POWEROFF (for maintenance. added in 09_2h) */
			result2 = read(client_fd, pipc, sizeof(IPCU));
			close(client_fd);
			ret = RET_POWEROFF;
			break;
		}
		else if( strcmp(buf, "FDATA") == 0 )
		{											/* FDATA command (for maintenance) */
			result2 = read(client_fd, pipc, sizeof(IPCU));
			close(client_fd);
			ret = RET_FDATA;
			break;
		}
		else if( strcmp(buf, "WDATA") == 0 )
		{											/* WDATA command (for maintenance) */
			result2 = read(client_fd, pipc, sizeof(IPCU));
			close(client_fd);
			ret = RET_WDATA;
			break;
		}
		else if( strcmp(buf, "EXECLM") == 0 )
		{											/* EXECLM command (to invoke Language Manager) */
			close(client_fd);
			ret = RET_EXECLM;
			break;
		}
		else
		{
			close(client_fd);
			ret = RET_ERROR;
			break;
		}
	}

	if(client_fd < 0)
		return RET_ERROR;

	close(server_fd);
	unlink(sname);
	return ret;
}

