/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2007
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * NOTE:
 *  - As a special exception, this program is permissible to link with the
 *    libraries released as the binary modules.
 *  - If you write modifications of your own for these programs, it is your
 *    choice whether to permit this exception to apply to your modifications.
 *    If you do not wish that, delete this exception.
 */


#include "cncl.h"
#include "cncl2def.h"
#include "cncldef.h"
#include "cncludef.h"
#include "cnclucom.h"

#include "psize.h"
#include "keytext.h"

#include "uitypes.h"
#include "bjipc.h"

#include "loadres.h"
#include "comdb.h"
#include "ipcproc.h"
#include "gdktool.h"
#include "widgets.h"
#include "utility.h"
#include "xpmproc.h"

#include "dialog.h"
#include "uimain.h"
#include "qualitydlg.h"
#include "colordlg.h"
#include "colordlg2.h"
#include "usrsizedlg.h"
#include "versiondlg.h"
#include "mediasizedlg.h"
#include "mediatypedlg.h"
#include "mediaborderdlg.h"
#include "pagesizedlg.h"

#include "modeltbl.h"
#include "globals.h"

