/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2009-2012
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define OPTION_STRING_MACADDR			"--macaddr"
#define OPTION_STRING_USERNAME			"--user"
#define OPTION_STRING_JOBNAME			"--job"
#define OPTION_STRING_MODELNUM			"--model"
#define OPTION_STRING_DIRECT			"--direct"
#define OPTION_STRING_SEARCH			"--search"
#define OPTION_STRING_INSTALLER			"--installer"

#define SEND_IVEC				(0)
#define SEND_PRINT_DATA			(1)

typedef struct _OPTIONTABLE{
	char key[128];
	char value[128];
	struct _OPTIONTABLE *next;
} OPTIONTABLE;

typedef struct _PACKETSIZE_TABLE{
	int model;
	int packet_size;
} PACKETSIZE_TABLE;

unsigned long get_packet_size(CNNLHANDLE h, int model);
int  parse_options(OPTIONTABLE *start, int argc, char **argv);
int  get_options(OPTIONTABLE *start, const char *key, char *val, const int size);
void release_options(OPTIONTABLE *start);
int  dispatchCommandIVEC(CNNLHANDLE hnd, int type);
int sendData(CNNLHANDLE hnd, void *buffer, unsigned long size, int sendmode, FILE *fp);

int CheckStartPrint(CNNLHANDLE h, const int retry, const unsigned long timeout);
int CheckEndPrint(CNNLHANDLE h, const int retry, const unsigned long timeout);
int CheckExecutePrint(CNNLHANDLE h, const int retry, const unsigned long timeout);
int CheckParentProcess(CNNLHANDLE h);


