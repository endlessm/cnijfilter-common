/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2008
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
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
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "callbacks.h"
#ifndef	USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"


/* Ver.3.00 */
gboolean IsAvailableSupplySize()
{
	short ret;
	gboolean result = FALSE;
	ret = CNCL_ConfirmSupplySize(&g_uidb.nominfo,(void*)g_bjlibdir, g_uidb.lpdbTop, g_uidb.dbsize);
#ifdef _PRINTUI_DEBUG_
	fprintf(stderr,"CNCL_ConfirmSupplySize=%d\n",ret);
#endif	

	if( ret ) result = TRUE;
	return result;

}


/* Ver.3.00 */
gboolean IsAvailableSizeDuplex()
{

	short ret;
	gboolean result = FALSE;
	ret = CNCL_ConfirmSizeDuplex(&g_uidb.nominfo,(void*)g_bjlibdir, g_uidb.lpdbTop, g_uidb.dbsize);
#ifdef _PRINTUI_DEBUG_
	fprintf(stderr,"CNCL_ConfirmSizeDuplex=%d\n",ret);
#endif
	
	if( ret ) result = TRUE;
	return result;

}


