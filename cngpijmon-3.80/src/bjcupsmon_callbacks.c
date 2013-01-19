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

/*** Includes ***/
#include "bjcupsmon_common.h"
#include "bjcupsmon_funcprot.h"


/*** External global parameters ***/
extern gchar			gDestName[1024];	// Destination printer name.
extern ST_PrinterStatus	gPrinterStatus;		// Printer status.
extern GdkPixmap		*gpPixmap;			// Pointer to pixmaps.


/*** Functions ***/
// Callback functions for Main Window.
///////////////////////////////////////////////////////////////////////////////////////////
//

gboolean on_mainWindow_delete_event(void)
//void on_mainWindow_delete_event(void)
{
	//closeApplication();
	
	return (FALSE);
//	return;
}// End on_mainWindow_delete_event


///////////////////////////////////////////////////////////////////////////////////////////
//
void on_mainWindow_destroy(void)
{
	closeApplication();
	
	return;
}// End on_mainWindow_destroy


///////////////////////////////////////////////////////////////////////////////////////////
//
//void on_buttonMainContinue_clicked(void)
//{
//	return;
//}// End on_buttonMainContinue_clicked


///////////////////////////////////////////////////////////////////////////////////////////
//
//void on_buttonMainCancel_clicked(void)
//{
///*** Parameters start ***/
//	ST_ErrorCodeTbl		errorInfo;					// Error info.
//	gint				retVal = ID_ERR_NO_ERROR;	// Return value.
///*** Parameters end ***/
//	
//	// Remove active print job.
//	retVal = removeJob(gDestName);
//	if (retVal != ID_ERR_NO_ERROR) {
//		memset(&errorInfo, 0, sizeof(ST_ErrorCodeTbl));
//		getErrorCodeInfo(retVal, &errorInfo);
//		if (errorInfo.errorLevel == ID_ERR_LEVEL_FATAL) {
//			// Show error message on command line.
//			outputCommandLineMessage(errorInfo.messageID);
//			// Close application.
//			closeApplication();
//		}
//	}
//	
//	return;
//}// End on_buttonMainCancel_clicked


///////////////////////////////////////////////////////////////////////////////////////////
//
gboolean on_drawMainCartridge_configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer user_data)
{
	// Update drawing area.
//	updateCartridgePictArea(&gPrinterStatus, TRUE);
	updateCartridgePictArea(&gPrinterStatus, FALSE);
	
	return(TRUE);
}// End on_drawMainCartridge_configure_event


///////////////////////////////////////////////////////////////////////////////////////////
//
gboolean on_drawMainCartridge_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer user_data)
{
	// Re-draw drawing area.
	if( gpPixmap == NULL ) return(FALSE);
	
	gdk_draw_pixmap(widget->window,
					widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
					gpPixmap,
					event->area.x,
					event->area.y,
					event->area.x,
					event->area.y,
					event->area.width,
					event->area.height);
	
	return(FALSE);
}// End on_drawMainCartrigePictArea_expose_event

///////////////////////////////////////////////////////////////////////////////////////////
//
void sighand_term ()
{
//	flag_term = 1;
}


