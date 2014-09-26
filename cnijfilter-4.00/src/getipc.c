/*
 *  Canon Inkjet Printer Driver for Linux
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

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "cnclucom.h"
#include "bjipc.h"
#include "cncldef.h"


short GetIPCData( LPIPCU , char *);


short GetIPCData(LPIPCU pipc, char *sname)
{
	struct sockaddr_un		sun;
	int						s, c;
	char					buf[128];
	size_t					adrlen;
	short					ret = RET_ERROR;

	if ((s = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
		return RET_ERROR;

	unlink(sname);

	sun.sun_family = AF_UNIX;
	strncpy(sun.sun_path, sname, sizeof(sun.sun_path) );
	sun.sun_path[sizeof(sun.sun_path) - 1] = '\0';

	adrlen = sizeof(sun.sun_family) + strlen(sun.sun_path);

	if (bind(s, (struct sockaddr *)&sun, adrlen))
		return RET_ERROR;

	if (listen(s, 5))
		return RET_ERROR;

	while ((c = accept(s, (struct sockaddr *)&sun, &adrlen)) >= 0) {
		/* read command first */
		read(c, buf, IPCCMDLEN);

		if (strcmp(buf, "PRINT") == 0) {			/* PRINT command */
			read(c, pipc, sizeof(IPCU));
			close(c);
			ret = RET_PRINT;
			break;
		}
		else if (strcmp(buf, "CANCEL") == 0) {		/* CANCEL command */
			close(c);
			ret = RET_CANCEL;
			break;
		}
		else if (strcmp(buf, "PDATA") == 0) {		/* PDATA command (for maintenance) */
			read(c, pipc, sizeof(IPCU));
			close(c);
			ret = RET_PDATA;
			break;
		}
		else if (strcmp(buf, "FDATA") == 0) {		/* FDATA command (to print testpattern) */
			read(c, pipc, sizeof(IPCU));
			close(c);
			ret = RET_FDATA;
			break;
		}
		else if (strcmp(buf, "EXECLM") == 0) {		/* EXECLM command (to invoke Language Manager) */
			close(c);
			ret = RET_EXECLM;
			break;
		}
		else {
			close(c);
			ret = RET_ERROR;
			break;
		}
	}

	if (c < 0)
		return RET_ERROR;

	close(s);
	unlink(sname);
	return ret;
}


