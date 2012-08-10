/*
 *  CUPS add-on module for Canon Inkjet Printer.
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
 */

#define BJ_UTILFILE	"/tmp/bjutil"

char **make_util_cmd_param( char *printer,	char* cmds, long cmdslen );
void free_util_cmd_param( char** cmd_param );
char **make_util_file_param( char *printer,	char* filename );
char **make_pdata_lpr_param( char *printer,	IPCU* p_ipc ,short direct_flag);	/* Ver.3.20 add parameter */
char **make_wdata_lpr_param( char *printer, IPCU *p_ipc );
char **make_fdata_lpr_param( char *printer, IPCU *p_ipc );

