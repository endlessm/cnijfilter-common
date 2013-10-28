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


//#ifdef HAVE_CONFIG_H
//#  include <config.h>
//#endif

#include <gtk/gtk.h>
#ifdef	USE_LIB_GLADE
#	include <glade/glade.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#ifndef	USE_LIB_GLADE
#	include "support.h"
#endif
#include "bjuidefs.h"


static char* g_pixmapdir = NULL;

void SetPixmapDir(gchar* dirname)
{
#ifndef	USE_LIB_GLADE
	if( g_pixmapdir != NULL )
		g_free(g_pixmapdir);

	g_pixmapdir = g_strdup(dirname);

	// Set the pixmaps directory path for create_pixmap() in support.c
	add_pixmap_directory(dirname);
#endif
}


GdkPixmap* LoadPixmap(GtkWidget* window,
				 GdkBitmap** mask_bitmap, const gchar* filename)
{
	GdkPixmap* pixmap;
	gchar* pathname = NULL;

	if( !g_pixmapdir || !filename )
		return NULL;

	if( (pathname = CheckFileExists(g_pixmapdir, filename)) == NULL )
		if( (pathname = CheckFileExists("pixmaps", filename)) == NULL )
			return NULL;

	pixmap = gdk_pixmap_create_from_xpm(
					window->window,
					mask_bitmap,
					NULL,
					pathname);

	g_free(pathname);
	return pixmap;
}

void FreePixmap(GdkPixmap* pixmap, GdkBitmap* mask)
{
	if( pixmap != NULL )
		gdk_pixmap_unref(pixmap);
	if( mask != NULL )
		gdk_bitmap_unref(mask);
}

// Samme as the check_file_exists() in support.c, but NOT static.
gchar* CheckFileExists(const gchar *dirname, const gchar *filename)
{
	gchar *full_filename;
	struct stat s;
	gint status;

	full_filename = (gchar*)g_malloc(strlen (dirname) + 1
                                   + strlen (filename) + 1);
	strcpy(full_filename, dirname);
	strcat(full_filename, G_DIR_SEPARATOR_S);
	strcat(full_filename, filename);

	status = stat(full_filename, &s);
	if( status == 0 && S_ISREG(s.st_mode) )
		return full_filename;

	g_free(full_filename);
	return NULL;
}

