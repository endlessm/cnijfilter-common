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

#ifndef __BJFPATH_H__
#define __BJFPATH_H__

#ifdef HAVE_CONFIG_H
#include  <config.h>
#endif

#define BJFILTERRC			"/cif"
#define LGMON				"/lgmon"

#define catpath2(dir,name)	dir name
#define catpath(dir,name)	catpath2(dir , name)
#define mkpath2(path)		#path
#define mkpath(path)		mkpath2(path)

/* data base file path */
#define	BJLIBPATH			mkpath(XBJLIBPATH)

/* #define BJFILTERXXXXRCPATH */
#define BJFILTERXXXXRCPATH			catpath(mkpath(XBJLIBPATH),BJFILTERRC)

/* program file path */
#define LGMONPATH			catpath(mkpath(XBINPATH),LGMON)

#define BJFILTERDOTCONF		".conf"
#define BJFILTERDOTREGI		".regi"
#define BJFILTERDOTNOZL		".nozl"
#define BJFILTERDOTBSCC		".bscc"



#define BJSOCKET			"/tmp/bjui"



#endif
