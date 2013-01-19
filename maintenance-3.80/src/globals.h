/*  Canon Inkjet Printer Driver for Linux
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


#ifndef	_GLOBALS
#define	_GLOBALS

#undef	GLOBAL
#ifdef	DEFINE_GLOBALS
#define	GLOBAL
#else
#define	GLOBAL	extern
#endif

// 2009/11/13
#define catpath2(dir,name)	dir name
#define catpath(dir,name)	catpath2(dir , name)
#define mkpath2(path)		#path
#define mkpath(path)		mkpath2(path)


#define INTERNAL_VERSION_STR	"3.80.01.013"


/////////////////////////////////////////////////////////
// Initialized variables

#ifdef	DEFINE_GLOBALS

GLOBAL gchar* g_hostname = "localhost";
GLOBAL gchar* g_socketname = NULL;

#else

GLOBAL gchar* g_hostname;
GLOBAL gchar* g_socketname;

#endif

/////////////////////////////////////////////////////////
// Non initialized variables

GLOBAL gboolean g_bidi_mode;	/* Ver.3.20 */
GLOBAL gchar* g_device_uri;		/* Ver.3.70 */

GLOBAL short g_model_id;
GLOBAL char g_window_title[64];

GLOBAL GdkFont* g_main_font;
GLOBAL KeyTextList* g_keytext_list;
GLOBAL char* g_bjlibdir;
GLOBAL gboolean	g_valid_signal;

GLOBAL GtkWidget* g_main_window;

#endif

