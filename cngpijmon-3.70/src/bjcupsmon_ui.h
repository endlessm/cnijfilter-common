/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2012
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License.
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

/*** Macros ***/
#ifndef N_
#define N_(string)			string
#endif

/*** Defines ***/
#ifdef USE_libglade
// Glade file name.
#define GLADE_FILE_NAME		"bjcupsmon.glade"
#endif 

/*** Static function prototypes ***/
PRIVATE void setWindowTitle(const gchar*, const gchar*);
PRIVATE void setLabelString(const gchar*, const gchar*);
PRIVATE void clearTextArea(const gchar*);
PRIVATE void insertStringToText(const gchar*, const gchar*);
PRIVATE void insertStringToText_NoConv(const gchar *, const gchar *);
PRIVATE void freezeText(const gchar*, gboolean);
PRIVATE void showWidget(const gchar*, gboolean);

