/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2004
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
#include <config.h>
#include <libintl.h>
#include <signal.h>

#ifndef USE_libglade 
	#include  "support.h"
#endif

#include "interface.h"
#include "bjcupsmon_common.h"
#include "bjcupsmon_ui.h"
#include "bjcupsmon_funcprot.h"

/*** Global parameters ***/
#ifdef USE_libglade
PRIVATE GladeXML	*gXmlMainWnd = NULL;		// Pointer to glade xml of main window.
#else
PRIVATE GtkWidget	*gMainWnd = NULL;			// Pointer to main window. ver.2.50
GtkWidget* create_mainWindow (void);
#endif

PRIVATE const gchar	*gSTSMessageTable[] = {		// Printer status message table.
	N_("The used ink tank is full.\nCancel printing and turn the printer off and then back on.\nIf this doesn't clear the error, see the printer manual for details.\n"),
	N_("Service error "),
	N_(".\nCancel printing and turn the printer off and then back on.\nIf this doesn't clear the error, see the printer manual for details.\n"),
	N_("Paper out.\nLoad paper and press printer's RESUME button.\n"),
	N_("Paper jammed.\nRemove jammed paper and press printer's RESUME button.\n"),
	N_("Cartridge not installed.\nInstall appropriate BJ cartridge in the printer.\nor\nClick Cancel Printing if no cartridge avairable.\n"),
	N_("Operator error.\nPress printer's RESUME button.\nIf this doesn't clear the error, cancel printing and turn the printer off and then back on.\n"),
	N_("Scanner Cartridge detected.\nChange to appropriate cartridge.\nClick Cancel Printing to cancel operation.\n"),
	N_("The used ink tank is almost full.\nPress the printer's RESUME button to restart printing.\n"),
	N_("Protector not installed.\nInstall a protector properly in the printer.\n"),
	N_("Ink has run out.\nReplace ink tank and close the front cover.\n"),
	N_(" Black\n"),
	N_(" Photo Black\n"),
	N_(" Photo Cyan\n"),
	N_(" Photo Magenta\n"),
	N_(" Cyan\n"),
	N_(" Magenta\n"),
	N_(" Yellow\n"),
	N_("Front cover is open.\nUnable to print until the front cover is closed.\n"),
	N_("Operator error.\nThe connected printer cannot work correctry.\n"),
	N_("Cleaning.\nPlease wait.\n"),
	N_("Cartridge replacement is in progress.\nClose the front cover after replacement is completed.\n"),
	N_("Printing.\n"),
	N_("Printer is in use via another interface.\nPlease wait.\n"),
	N_("Scanner Cartridge detected.\nYou cannot print with this cartridge.\nChange to appropriate BJ cartridge.\n"),
	N_("Unsupported cartridge installed.\nChange to appropraite BJ cartridge.\n"),
	N_("Cartridge not installed.\nInstall appropriate BJ cartridge in the printer.\n"),
	N_("Printing.\n"),
	N_("Printer is online.\n"),
	N_("\nThe following Ink tank are running low.\n"),
	N_(" Black\n"),
	N_(" Photo Black\n"),
	N_(" Photo Cyan\n"),
	N_(" Photo Magenta\n"),
	N_(" Cyan\n"),
	N_(" Magenta\n"),
	N_(" Yellow\n"),
	N_(" Color\n"),
	N_("\nThe remaininig level of the following ink is unknown:\n"),
	N_(" Black\n"),
	N_(" Color\n"),
	N_("\nThere is a possibility that the printer cannot detect the remaining ink level properly.\nReset the ink counter using the Maintenance tab of the printer driver properties whenever you have replaced any ink tank with new one.\n"),
	N_("\nThe printer is set not to display a low ink warning.\n"),
	"",
	N_("The CD-R tray guide is installed in the printer.\nAfter ensuring that the CD-R tray has been removed, remove the CD-R tray guide and then press the RESUME button. Printing will restart.\n"),
	N_("The printer's front cover is open.\nIf printing is progress, the print head or ink tank cannot be changed. Close the front cover, wait for printing to finish, then open the cover again and change the print head or ink tank. If the CD-R tray guide is installed, the print head or ink tank cannot be also changed. Close the front cover, remove the CD-R tray guide, open the front cover again, and change the print head or ink tank."),
};

PRIVATE const gchar	*gOtherMessageTable[] = {		// Other message table.
	N_("Ready.\n"),
	N_("Unknown printer.\n"),
	N_("Spooler error.\n"),
	"bjcupsmon: fatal error occured.\n",
	"bjcupsmon: argument error.\nUsage: bjcupsmon [printer name]\n",
};


/*** Functions ***/
///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC void initUI(gchar *pWindowTitle, ST_PrinterStatus *pPrinterStatus, gboolean isPrinting, ENUM_OtherMessageID otherMsg)
// IN     : gchar *pWindowTitle : Window title string.
//          ST_PrinterStatus *pPrinterStatus : Information of printer status.
//          gboolean isPrinting : TRUE : Printing.
//                                FALSE : Not printing.
//          ENUM_OtherMessageID otherMsg : Message ID except printer status message.
// OUT    : None.
// RETURN : None.
// 
PUBLIC void initUI(gchar *pWindowTitle, ST_PrinterStatus *pPrinterStatus, gboolean isPrinting, ENUM_OtherMessageID otherMsg)
{
#ifdef USE_libglade
/*** Parameters start ***/
	gchar				gladeFileName[MAX_BUF_SIZE];	// Buffer for glade file name.
	ENUM_STSMessageID	*pMessageID;					// Pointer to array of message ID.
	gint				i;								// Counter.
/*** Parameters end ***/
	
	// Create full path of glade file name.
	memset (gladeFileName, 0, MAX_BUF_SIZE);
	strncpy(gladeFileName, STR_SHARE_DIRECTORY_NAME, 
		(MAX_BUF_SIZE<(strlen(STR_SHARE_DIRECTORY_NAME)+strlen(GLADE_FILE_NAME)+1))? MAX_BUF_SIZE<(strlen(STR_SHARE_DIRECTORY_NAME)+strlen(GLADE_FILE_NAME)+1));
	strcat(gladeFileName, "/");
	strcat(gladeFileName, GLADE_FILE_NAME);
	
	// Show window.
	gXmlMainWnd = glade_xml_new(gladeFileName, STR_WINDOW_NAME_MAIN);
	
	// Set window title.
	setWindowTitle(STR_WINDOW_NAME_MAIN, pWindowTitle);
	
	// Initialize related cartridge area drawing handling.
	initDrawing();
	
	// Disable [Cancel Printing] button.
	activateWidget(STR_MAIN_BUTTON_NAME_CANCEL, FALSE);
		
	if (isPrinting == FALSE) {	// Not printing.
		// Initialize UI settings. (Without printer status.)
		updateUISettings(NULL, otherMsg, TRUE, TRUE, TRUE, TRUE);
	}
	else {	// Printing.
		// Enable [Cancel Printing] button.
		if (pPrinterStatus->printInterface == ID_DEV_1284 )
			activateWidget(STR_MAIN_BUTTON_NAME_CANCEL, TRUE);
		
		// Check messages.
		pMessageID = pPrinterStatus->pMessageID;
		for (i = 0; i < pPrinterStatus->messageNum; i++) {
			if (*pMessageID == ID_STS_MESSAGE_CARTRIDGE_UNSUPPORTED
			||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_OUT
			||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_JAM) {
				// Disable [Cancel Printing] button.
				activateWidget(STR_MAIN_BUTTON_NAME_CANCEL, FALSE);
				break;
			}
			pMessageID++;
		}
		
		// Initialize UI settings related with printer status.
		updateUISettings(pPrinterStatus, ID_OTHER_MESSAGE_NONE, TRUE, TRUE, TRUE, TRUE);
	}
	
	// Hide [Continue] button.
	showWidget(STR_MAIN_BUTTON_NAME_CONTINUE, FALSE);
	
	// Signal connect.
	glade_xml_signal_autoconnect(gXmlMainWnd);
	
	return;
	
#else	// use Gtk+-1.2

/*** Parameters start ***/
	ENUM_STSMessageID	*pMessageID;					// Pointer to array of message ID.
	gint				i;								// Counter.
//	struct	sigaction	sa;
/*** Parameters end ***/

	// Show window.
	gMainWnd 	= create_mainWindow();

	// Initialize related cartridge area drawing handling.
	initDrawing();
	
	// Set window title.
	setWindowTitle(STR_WINDOW_NAME_MAIN, pWindowTitle);

	// Disable [Cancel Printing] button.
	activateWidget(STR_MAIN_BUTTON_NAME_CANCEL, FALSE);
		
	if (isPrinting == FALSE) {	// Not printing.
		// Initialize UI settings. (Without printer status.)
		updateUISettings(NULL, otherMsg, TRUE, TRUE, TRUE, TRUE);
	}
	else {	// Printing.
		// Enable [Cancel Printing] button.
		if (pPrinterStatus->printInterface == ID_DEV_1284 )
			activateWidget(STR_MAIN_BUTTON_NAME_CANCEL, TRUE);
		
		// Check messages.
		pMessageID = pPrinterStatus->pMessageID;
		for (i = 0; i < pPrinterStatus->messageNum; i++) {
			if (*pMessageID == ID_STS_MESSAGE_CARTRIDGE_UNSUPPORTED
			||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_OUT
			||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_JAM
				) {
				// Disable [Cancel Printing] button.
				activateWidget(STR_MAIN_BUTTON_NAME_CANCEL, FALSE);
				break;
			}
			pMessageID++;
		}
		
		// Initialize UI settings related with printer status.
		updateUISettings(pPrinterStatus, ID_OTHER_MESSAGE_NONE, TRUE, TRUE, TRUE, TRUE);
	}
	// Hide [Continue] button.
	showWidget(STR_MAIN_BUTTON_NAME_CONTINUE, FALSE);
	
	// Show
	showWidget(STR_WINDOW_NAME_MAIN, TRUE);

	// Signal connect.
//	memset( &sa, 0, sizeof(sa));
//	sa.sa_handler = sighand_term;
//	if( sigaction( SIGTERM, &sa, NULL) ) perror("sigaction");
	
	return;
#endif 	// USE_libglade

}// End initUI


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC void updateUISettings(ST_PrinterStatus *pPrinterStatus, ENUM_OtherMessageID otherMsg, gboolean updateCT, gboolean updateLP, gboolean updateMSG, gboolean updateCHD)
// IN     : ST_PrinterStatus *pPrinterStatus : Information of printer status.
//          ENUM_OtherMessageID otherMsg : Message ID except printer status message.
//          gboolean updateCT : Update cartridge type area or not.
//          gboolean updateLP : Update lever position area or not.
//          gboolean updateMSG : Update message area or not.
//          gboolean updateCHD : Update cartridge pictures area or not.
// OUT    : None.
// RETURN : None.
// 
PUBLIC void updateUISettings(ST_PrinterStatus *pPrinterStatus, ENUM_OtherMessageID otherMsg, gboolean updateCT, gboolean updateLP, gboolean updateMSG, gboolean updateCHD)
{
/*** Parameters start ***/
	ENUM_STSMessageID	*pMessageID;			// Pointer to array of message ID.
	gchar				tempBuf[MAX_BUF_SIZE];	// Temporary buffer.
	gint				i;						// Counter.
	gboolean			flag = FALSE;
	gboolean			unknownFlag = FALSE;
/*** Parameters end ***/
	
//	printf("updateUI ct:%d chd:%d\n",updateCT,updateCHD);

	if (updateCT == TRUE) {
		// Set cartridge type string.
		memset(tempBuf, 0, sizeof(tempBuf));
		strncpy(tempBuf, dgettext(PACKAGE, N_("Cartridge Type : ")), MAX_BUF_SIZE-1);
		if (pPrinterStatus != NULL) {
			for (i = 0; i < 2; i++) {
				switch (pPrinterStatus->cartridgeClass[i].type) {
					case ID_CARTRIDGE_TYPE_SCANNER:			// Scanner cartridge.
						if (i == 0) {
							strcat(tempBuf, dgettext(PACKAGE, N_("Scanner")));
							flag = TRUE;
						}
						else if (pPrinterStatus->cartridgeClass[0].type != pPrinterStatus->cartridgeClass[1].type) {
							if (flag == TRUE) {
								strcat(tempBuf, "/");
							}
							strcat(tempBuf, dgettext(PACKAGE, N_("Scanner")));
						}
						break;
						
					case ID_CARTRIDGE_TYPE_UNSUPPORTED:		// Unsupported cartridge.
						if (i == 0) {
							strcat(tempBuf, dgettext(PACKAGE, N_("Unsupported")));
							flag = TRUE;
						}
						else if (pPrinterStatus->cartridgeClass[0].type != pPrinterStatus->cartridgeClass[1].type) {
							if (flag == TRUE) {
								strcat(tempBuf, "/");
							}
							strcat(tempBuf, dgettext(PACKAGE, N_("Unsupported")));
						}
						break;
						
					case ID_CARTRIDGE_TYPE_PHOTO:			// F850 type.
					case ID_CARTRIDGE_TYPE_PHOTO2:			// 950i type.
					case ID_CARTRIDGE_TYPE_PHOTO_COLOR:		// F360 type (Photo).
						if (i == 0) {
							strcat(tempBuf, dgettext(PACKAGE, N_("Photo")));
							flag = TRUE;
						}
						else if (pPrinterStatus->cartridgeClass[0].type != pPrinterStatus->cartridgeClass[1].type) {
							if (flag == TRUE) {
								strcat(tempBuf, "/");
							}
							strcat(tempBuf, dgettext(PACKAGE, N_("Photo")));
						}
						break;
						
					case ID_CARTRIDGE_TYPE_BLACK:			// F360 type (Black).
						if (i == 0) {
							strcat(tempBuf, dgettext(PACKAGE, N_("Black")));
							flag = TRUE;
						}
						else if (pPrinterStatus->cartridgeClass[0].type != pPrinterStatus->cartridgeClass[1].type) {
							if (flag == TRUE) {
								strcat(tempBuf, "/");
							}
							strcat(tempBuf, dgettext(PACKAGE, N_("Black")));
						}
						break;
						
					case ID_CARTRIDGE_TYPE_COLOR_S600:		// S600 type.
					case ID_CARTRIDGE_TYPE_COLOR_S300:		// S300 type (CIL:OFF).
					case ID_CARTRIDGE_TYPE_COLOR_S300_CIL:	// S300 type (CIL:ON).
						if (i == 0) {
							strcat(tempBuf, dgettext(PACKAGE, N_("Color")));
							flag = TRUE;
						}
						else if (pPrinterStatus->cartridgeClass[0].type != pPrinterStatus->cartridgeClass[1].type) {
							if (flag == TRUE) {
								strcat(tempBuf, "/");
							}
							strcat(tempBuf, dgettext(PACKAGE, N_("Color")));
						}
						break;
						
					default:	// Another value.
						if (i == 0) {
							unknownFlag = TRUE;
						}
						else if (unknownFlag == TRUE) {
							strcat(tempBuf, dgettext(PACKAGE, N_("Unknown")));
						}
						break;
				}
			}
		}
		setLabelString(STR_MAIN_LABEL_CARTRIDGE_TYPE, tempBuf);
	}
	
	if (updateLP == TRUE) {
		// Set paper thickness position string.
		if (pPrinterStatus != NULL) {
			memset(tempBuf, 0, sizeof(tempBuf));
			
			if( pPrinterStatus->leverPosition != ID_LEVER_POSITION_INVALID 
			  && pPrinterStatus->leverPosition != ID_LEVER_POSITION_NONE ) 
				strncpy(tempBuf, dgettext(PACKAGE, N_("Paper thickness lever position : ")), MAX_BUF_SIZE-1);
			else
				strncpy(tempBuf, dgettext(PACKAGE, "                                                "), MAX_BUF_SIZE-1);
			switch (pPrinterStatus->leverPosition) {
				case ID_LEVER_POSITION_UP:		// Up.
					strcat(tempBuf, dgettext(PACKAGE, N_("up")));
					break;
				
				case ID_LEVER_POSITION_DOWN:	// Down.
					strcat(tempBuf, dgettext(PACKAGE, N_("down")));
					break;
				
				case ID_LEVER_POSITION_LEFT:	// Left.
					strcat(tempBuf, dgettext(PACKAGE, N_("left")));
					break;
				
				case ID_LEVER_POSITION_RIGHT:	// Right.
					strcat(tempBuf, dgettext(PACKAGE, N_("right")));
					break;
				
				default:
					break;
			}
			setLabelString(STR_MAIN_LABEL_LEVER_POSITION, tempBuf);
		}
	}
	
	if (updateMSG == TRUE) {
		// Set message string.
		freezeText(STR_MAIN_TEXT_STATUS, TRUE);
		clearTextArea(STR_MAIN_TEXT_STATUS);
		if (otherMsg != ID_OTHER_MESSAGE_NONE) {
			insertStringToText(STR_MAIN_TEXT_STATUS, gOtherMessageTable[otherMsg]);
		}
		else {
			if (pPrinterStatus != NULL) {
				pMessageID = pPrinterStatus->pMessageID;
				for (i = 0; i < pPrinterStatus->messageNum; i++) {
					insertStringToText(STR_MAIN_TEXT_STATUS, gSTSMessageTable[*pMessageID]);
					if (*pMessageID == ID_STS_MESSAGE_SC_SERVICE_ERROR_PRE) {
						insertStringToText(STR_MAIN_TEXT_STATUS, pPrinterStatus->serviceCallID);
					}
					pMessageID++;
				}
			}
		}
		freezeText(STR_MAIN_TEXT_STATUS, FALSE);
	}

	if (updateCT == TRUE || updateCHD == TRUE) {
		if (pPrinterStatus != NULL) {
			// Check cartridge class is printer cartridge or not.
			if (pPrinterStatus->cartridgeClass[0].type >= ID_CARTRIDGE_TYPE_PHOTO
			||  pPrinterStatus->cartridgeClass[1].type >= ID_CARTRIDGE_TYPE_PHOTO) {
				// Printer cartridge.
				for (i = 0; i < CARTRIDGE_COLOR_TYPE_NUM; i++) {
					if (pPrinterStatus->cartridgeStatus[i].level != ID_INK_LEVEL_NONE
					&&  pPrinterStatus->cartridgeStatus[i].status != ID_INK_STS_NONE) {
						break;
					}
				}
				if (i == CARTRIDGE_COLOR_TYPE_NUM) {
					clearCartridgePictArea();
				}
				else {
					updateCartridgePictArea(pPrinterStatus, TRUE);
				}
			}
			else {
				// Not printer cartridge. Clear cartridge pixmap area.
				clearCartridgePictArea();
			}
		}
		else {
			clearCartridgePictArea();
		}
	}
	
	return;
}// End updateUISettings


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE void setWindowTitle(const gchar *pWidgetName, const gchar *pWindowTitle)
// IN     : const gchar *pWidgetName : Widget name.
//          const gchar *pWindowTitle : Window title string.
// OUT    : None.
// RETURN : None.
// 
PRIVATE void setWindowTitle(const gchar *pWidgetName, const gchar *pWindowTitle)
{
/*** Parameters start ***/
	GtkWidget	*widget = NULL;		// Temporary pointer to widget.
/*** Parameters end ***/
	
	widget = lookupWidget(pWidgetName);
	gtk_window_set_title(GTK_WINDOW(widget), (const gchar*)pWindowTitle);
	
	return;
}// End setWindowTitle


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE void setLabelString(const gchar *pWidgetName, const gchar *pString)
// IN     : const gchar *pWidgetName : Widget name.
//          const gchar *pString : Label string.
// OUT    : None.
// RETURN : None.
// 
PRIVATE void setLabelString(const gchar *pWidgetName, const gchar *pString)
{
/*** Parameters start ***/
	GtkWidget	*widget = NULL;		// Temporary pointer to widget.
/*** Parameters end ***/
	
	widget = lookupWidget(pWidgetName);
	gtk_label_set_text(GTK_LABEL(widget), pString);
	
	return;
}// End setLabelString


///////////////////////////////////////////////////////////////////////////////////////////
// 
// PRIVATE void clearTextArea(const gchar *pWidgetName)
// IN     : const gchar *pWidgetName : Widget name.
// OUT    : None.
// RETURN : None.
// 
PRIVATE void clearTextArea(const gchar *pWidgetName)
{
/*** Parameters start ***/
	GtkWidget	*widget = NULL;		// Temporary pointer to widget.
#ifndef USE_GTK12
	GtkTextIter start;
	GtkTextIter end;
	GtkTextBuffer *buffer;
#endif
/*** Parameters end ***/
	
	widget = lookupWidget(pWidgetName);
#ifdef USE_GTK12
	gtk_editable_delete_text(GTK_EDITABLE(widget), 0, -1);
#else
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
	gtk_text_buffer_get_start_iter(buffer, &start);
	gtk_text_buffer_get_end_iter(buffer, &end);

	gtk_text_buffer_delete(buffer, &start, &end);
#endif	  
	
	return;
}// End clearTextArea


///////////////////////////////////////////////////////////////////////////////////////////
// 
// PRIVATE void insertStringToText(const gchar *pWidgetName, const gchar *pString)
// IN     : const gchar *pWidgetName : Widget name.
//          const gchar *pString : Text string.
// OUT    : None.
// RETURN : None.
// 
PRIVATE void insertStringToText(const gchar *pWidgetName, const gchar *pString)
{
/*** Parameters start ***/
	GtkWidget	*widget = NULL;		// Temporary pointer to widget.
#ifndef USE_GTK12
	GtkTextBuffer *buffer = NULL;
	GtkTextIter start, end;
#endif
/*** Parameters end ***/
	
	widget = lookupWidget(pWidgetName);
#ifdef USE_GTK12
	gtk_text_insert(GTK_TEXT(widget), NULL, NULL, NULL, dgettext(PACKAGE, pString), -1);
#else	/* for GTK2 */
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
	gtk_text_buffer_get_start_iter(buffer, &start);
	gtk_text_buffer_get_end_iter(buffer, &end);
	if( pString != NULL )
		gtk_text_buffer_insert(buffer, &end,   dgettext(PACKAGE, pString), -1);
#endif

	return;
}// End insertStringToText


///////////////////////////////////////////////////////////////////////////////////////////
// 
// PRIVATE void freezeText(const gchar *pWidgetName, gboolean freeze)
// IN     : const gchar *pWidgetName : Widget name.
//          gboolean freeze : TRUE : Freeze widget.
//                            FALSE : Thaw widget.
// OUT    : None.
// RETURN : None.
// 
PRIVATE void freezeText(const gchar *pWidgetName, gboolean freeze)
{
/*** Parameters start ***/
	GtkWidget __attribute__ ((unused))	*widget = NULL;		// Temporary pointer to widget.
/*** Parameters end ***/
	
	widget = lookupWidget(pWidgetName);

#ifdef USE_GTK12
	if (freeze == TRUE) {
		gtk_text_freeze(GTK_TEXT(widget));
	}
	else {
		gtk_text_freeze(GTK_TEXT(widget));
	}
#endif
	
	return;
}// End freezeText


///////////////////////////////////////////////////////////////////////////////////////////
// 
// PRIVATE void freezeText(const gchar *pWidgetName, gboolean freeze)
// IN     : const gchar *pWidgetName : Widget name.
//          gboolean freeze : TRUE : Freeze widget.
//                            FALSE : Thaw widget.
// OUT    : None.
// RETURN : None.
// 
PUBLIC void activateWidget(const gchar *pWidgetName, gboolean activate)
{
/*** Parameters start ***/
	GtkWidget	*widget = NULL;		// Temporary pointer to widget.
/*** Parameters end ***/
	
	widget = lookupWidget(pWidgetName);
	gtk_widget_set_sensitive(GTK_WIDGET(widget), activate);
	
	return;
}// End activateWidget


///////////////////////////////////////////////////////////////////////////////////////////
// 
// PRIVATE void showWidget(const gchar *pWidgetName, gboolean show)
// IN     : const gchar *pWidgetName : Widget name.
//          gboolean freeze : TRUE : Show widget.
//                            FALSE : Hide widget.
// OUT    : None.
// RETURN : None.
// 
PRIVATE void showWidget(const gchar *pWidgetName, gboolean show)
{
/*** Parameters start ***/
	GtkWidget	*widget = NULL;		// Temporary pointer to widget.
/*** Parameters end ***/
	
	widget = lookupWidget(pWidgetName);
	if (show == TRUE) {
		gtk_widget_show(GTK_WIDGET(widget));
	}
	else {
		gtk_widget_hide(GTK_WIDGET(widget));
	}
	
	return;
}// End activateWidget


///////////////////////////////////////////////////////////////////////////////////////////
// 
// PUBLIC GtkWidget* lookupWidget(const gchar *pWidgetName)
// IN     : const gchar *pWidgetName : Widget name.
// OUT    : None.
// RETURN : Pointer to widget.
// 
PUBLIC GtkWidget* lookupWidget(const gchar *pWidgetName)
{
#ifdef USE_libglade
	return(glade_xml_get_widget(gXmlMainWnd, pWidgetName));
#else
	return (lookup_widget (gMainWnd, pWidgetName));
#endif
}// End lookupWidget


///////////////////////////////////////////////////////////////////////////////////////////
// 
// PUBLIC void outputCommandLineMessage(ENUM_OtherMessageID messageID)
// IN     : ENUM_OtherMessageID messageID : ID of other (except printer status) message
// OUT    : None.
// RETURN : None.
// 
PUBLIC void outputCommandLineMessage(ENUM_OtherMessageID messageID)
{
	if (messageID > ID_OTHER_MESSAGE_NONE) {
		fprintf(stderr, "%s",gOtherMessageTable[messageID]);
	}
	
	return;
}// End outputCommandLineMessage

