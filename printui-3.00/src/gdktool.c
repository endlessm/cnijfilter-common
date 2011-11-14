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


#include <gtk/gtk.h>
#ifdef	USE_LIB_GLADE
#	include <glade/glade.h>
#endif

#include <string.h>

#ifndef	USE_LIB_GLADE
#	include "support.h"
#endif
#include "bjuidefs.h"


GdkFont* LoadFontSet()
{
	// NOT check LOCALE now. Always return fontset.
	return gdk_fontset_load(
				"-*-helvetica-medium-r-normal--14-*-*-*-*-*-*-*,\
				-misc-fixed-medium-r-normal--14-*-*-*-*-*-jisx0208.1983-*");
}

void DrawPixmap(GdkWindow* window, GdkGC* gc,
			 gint dstx, gint dsty, GdkPixmap* pixmap, GdkBitmap* mask)
{
	gint map_w, map_h;

	gdk_window_get_size(pixmap, &map_w, &map_h);

	gdk_gc_set_clip_mask(gc, mask);
	gdk_gc_set_clip_origin(gc, dstx, dsty);

	gdk_draw_pixmap(window, gc, pixmap,
					0,0,			// srcx, srcy
					dstx, dsty,
					map_w, map_h);

	gdk_gc_set_clip_mask(gc, NULL);
}

void DrawString(GdkWindow* window, GdkFont* font, GdkGC* gc,
			 gint dstx, gint dsty, gchar* str)
{
	GdkColor color;
	color.red   = 0;
	color.green = 0;
	color.blue  = 0;
	gdk_color_alloc(gdk_colormap_get_system(), &color);

	gdk_gc_set_fill(gc, GDK_SOLID);
	gdk_gc_set_foreground(gc, &color);
	gdk_draw_string(window, font, gc, dstx, dsty, str);
}

// Ver2.60
// Because g_strup() cannot be used by the version of GTK, 
// it originally makes it. 
void UpperAsciiStr(char *str)
{
	gint i;

	for( i = 0; i < strlen(str); i++ )
		if( 'a' <= str[i] && str[i] <= 'z' )
			str[i] -= 0x20;
}

// Ver2.60
// Because tolower() cannot be used by the version of GTK 
// in the Turkish environment, it originally makes it. 
int LowerAsciiCode( int c )
{
	if( c >= 'A' && c <= 'Z' ) return (c + 0x20);
	return c;
}
