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

/*** Global function prototypes ***/
// bjcupsmon_main.c
extern void closeApplication(void);
extern void getErrorCodeInfo(gint, ST_ErrorCodeTbl*);

// bjcupsmon_ui.c
extern void initUI(gchar*, ST_PrinterStatus*, gboolean, ENUM_OtherMessageID);
extern void updateUISettings(ST_PrinterStatus*, ENUM_OtherMessageID, gboolean, gboolean, gboolean, gboolean);
extern void activateWidget(const gchar*, gboolean);
extern GtkWidget* lookupWidget(const gchar*);
extern void outputCommandLineMessage(ENUM_OtherMessageID);

// bjcupsmon_draw.c
extern void initDrawing(void);
extern void updateCartridgePictArea(ST_PrinterStatus*, gboolean);
extern void clearCartridgePictArea(void);
extern void freePixmaps(void);

// bjcupsmon_cups.c
extern gint getDefaultPrinterName(gchar*, gint);
extern gint getProductName(gchar*, gchar*, gchar*);
//extern gint getProductName(gchar*, gchar*);
extern gint checkPrinterAndJobState(gchar*, gboolean*, gboolean*);
extern gint getPrinterStatus(gchar*, gchar*, gint);
extern gint removeJob(gchar*);
/* for Network Ver.3.10 */
extern gint getDeviceURI(gchar*, gchar*, gint);

// bjcupsmon_transsts.c
extern int translatePrinterStatus(char*, ST_PrinterStatus*);
