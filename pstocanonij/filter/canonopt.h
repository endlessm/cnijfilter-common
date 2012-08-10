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

#ifndef _canonopt_
#define _canonopt_


typedef struct ppd_to_opt_key_s
{
	char *ppd_key;
	char *opt_key;
} PpdToOptKey;


char *ppd_to_opt_key(PpdToOptKey *p_table, char *ppd_key);
PpdToOptKey *alloc_opt_key_table(char *ppd_name);
void free_opt_key_table(PpdToOptKey *p_opt_key_table);

#endif

