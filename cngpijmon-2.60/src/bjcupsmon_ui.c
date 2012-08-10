/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2007
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

#include "bjcupsmon_common.h"
#include "bjcupsmon_ui.h"
#include "bjcupsmon_funcprot.h"

/*** Global parameters ***/
#ifdef USE_libglade
PRIVATE GladeXML	*gXmlMainWnd = NULL;		// Pointer to glade xml of main window.
#else
PRIVATE GtkWidget	*gMainWnd = NULL;			// Pointer to main window. ver.2.50
#endif

PRIVATE const gchar	*gSTSMessageTable[] = {		// Printer status message table.
//	N_("The used ink tank is full.\nCancel printing and turn the printer off and then back on.\nIf this doesn't clear the error, see the printer manual for more detail.\n"),
	N_("The waste ink absorber is full.\nContact the service center for the replacement of the waste ink absorber."),
	N_("Service error %s.\nCancel printing and turn the printer off and then back on.\nIf this doesn't clear the error, see the printer manual for more detail."),
	"",
	N_("Paper out!\n"),
	N_("Load paper.\n"),
	N_("Load paper in the sheet feeder.\n"),
	N_("Load paper in the cassette.\n"),
	N_("Load paper in the sheet feeder.\n"),
	N_("Load paper in the cassette.\n"),
	N_("Press printer's RESUME button.\n"),
	N_("Press printer's OK button.\n"),
	N_("Paper is jammed.\n"),
	N_("Paper is jammed at the paper output slot.\n"),
	N_("Paper is jammed at the paper output slot.\n"),
	N_("Remove the jammed paper.\n"),
	N_("Press printer's RESUME button. Printing resumes from the next paper.\n"),
	N_("Press printer's OK button. Printing resumes from the next paper.\n"),
	N_("Paper is jammed in the transport unit.\n"),
	N_("Open the rear cover, remove the jammed paper. If the jammed paper cannot be removed, first remove the cassette and remove the paper from the cassette side.\n"),
	N_("Paper is jammed in the duplexing transport unit.\n"),
	N_("Remove the cassette, push the printer over onto its back side, and then open the duplexing transport unit cover. Next, remove the jammed paper, and quickly return the printer to its upright position.\nRefer to the user's guide for details.\n"),
	N_("Paper is jammed in the duplexing transport unit.\n"),
	N_("Remove the cassette, push the printer over onto its side, and then open the duplexing transport unit cover. Next, remove the jammed paper, and quickly return the printer to its upright position.\nRefer to the user's guide for details.\n"),
	N_("Paper is jammed in the transport unit.\n"),
	N_("Paper is jammed in the duplexing transport unit.\n"),
	N_("Correct print head is not installed. Install an appropriate print head and close the cover of the printer.\n"),
	N_("Operator error.\nPress printer's RESUME button.\nIf this doesn't clear the error, cancel printing and turn the printer off and then back on.\n"),
	N_("Operator error.\nPress printer's OK button.\nIf this doesn't clear the error, cancel printing and turn the printer off and then back on.\n"),
	N_("Scanner Cartridge detected!\nChange to appropriate cartridge.\nClick Cancel Printing to cancel operation.\n"),
	N_("The waste ink absorber is almost full.\nPress the printer's RESUME button to restart printing."),
	N_("The waste ink absorber is almost full.\nPress the printer's OK button to restart printing."),
	N_("Protector not installed.\nInstall a protector properly in the printer.\n"),
//	N_("Ink has run out.\nReplace ink tank and close the front cover.\n"),
	N_("Ink has run out.\nReplace ink tank and close the cover. When replacing the ink tank, make sure that the Inner Cover is open.\n\nYou can continue printing under the ink out condition by pressing the RESUME button. Replace the empty ink tank immediately after the printing. The printer may be damaged if printing is continued under the ink out condition.\n"),
	N_(" Black [7]\n"),
	N_(" Photo Black [7]\n"),
	N_(" Photo Cyan [7]\n"),
	N_(" Photo Magenta [7]\n"),
	N_(" Cyan [7]\n"),
	N_(" Magenta [7]\n"),
	N_(" Yellow [7]\n"),
	N_(" Red [7]\n"),
	N_(" Green [7]\n"),
	N_(" Black [3e]\n"),
//	N_("Front cover is open.\nUnable to print until the front cover is closed.\n"),
	N_("The printer's cover is open.\nIf printing is in progress, the cartridge cannot be changed. Close the cover, wait for printing to finish, then open the cover again and change the print head or ink tank.\n"),
	N_("The printer's cover is open.\nIf printing is in progress, the print head or ink tank cannot be changed. Close the cover, wait for printing to finish, then open the cover again and change the print head or ink tank.\n"),
	N_("Document printing cannot be executed because the paper output tray is closed.\nOpen the paper output tray. Printing will restart.\n"),
	N_("Document printing cannot be executed because the paper output tray is closed.\nPress the Open button, and open the paper output tray. Printing will restart.\n"),
	N_("Operator error.\nThe connected printer cannot work correctly.\n"),
	N_("Cleaning.\nPlease wait.\n"),
	N_("The holder is at the replacement position.\nAfter replacing the ink cartridge, close the printer's cover.\n"),
	N_("The holder is at the replacement position.\nAfter replacing the print head or the ink tank, close the cover of the printer. To replace only the ink tanks, do not remove the print head from the printer. Do not touch the locking lever.\n"),
	N_("The holder is at the replacement position.\nIf you need to replace the print head or the ink tank, first open the Inner Cover. After the replacement is completed, close the Inner Cover, and then close the cover of the printer.\nIf you are replacing only the ink tank, leave the print head attached. Do not touch the lock lever.\n"),
	N_("Printing.\n"),
	N_("The printer is performing another operation.\n"),
	N_("Scanner Cartridge detected.\nYou cannot print with this cartridge. Install another BJ Cartridge in your printer.\n"),
	N_("Unsupported cartridge installed.\nChange to appropriate BJ cartridge.\n"),
	N_("Correct print head is not installed. Install an appropriate print head and close the cover of the printer.\n"),
	N_("Printing.\n"),
	N_("Printer is online.\n"),
	N_("\nThe following ink tanks are running low.\n"),
	N_(" Black [7e]\n"),
	N_(" Black [9]\n"),
	N_(" Photo Cyan [7e]\n"),
	N_(" Photo Magenta [7e]\n"),
	N_(" Cyan [7e]\n"),
	N_(" Magenta [7e]\n"),
	N_(" Yellow [7e]\n"),
	N_(" Red [7]\n"),
	N_(" Green [7]\n"),
	N_(" Black [9e]\n"),
	N_(" Black [24]\n"),
	N_(" Color [24]\n"),
	N_("Prepare new ink tanks.\n"),
	N_("\nThe following ink tanks are running low.\n"),
	N_(" Black [40]\n"),
	N_(" Black [50]\n"),
	N_(" Color [41]\n"),
	N_(" Color [51]\n"),
	N_(" Black [8]\n"),
	N_(" Black [5]\n"),
	N_(" Photo Cyan [8]\n"),
	N_(" Photo Magenta [8]\n"),
	N_(" Cyan [8]\n"),
	N_(" Magenta [8]\n"),
	N_(" Yellow [8]\n"),
	N_("Prepare a new ink cartridge.\nIf either black or color ink cartridge has run out, you can set the printer to continue printing with the other cartridge from the Ink Cartridge Settings on the Maintenance tab of the printer driver.\n"),
	N_("\nThe ink cartridge has been installed or replaced.\nIf the printout contains misaligned lines or is not satisfactory after the installation or replacement, refer to the user's guide and carry out the print head alignment.\n"),
	N_("\nThe printer is set not to display a low ink warning.\n"),
	"",
//	N_("The CD-R Tray Feeder is installed in the printer.\nAfter ensuring that the CD-R tray has been removed, remove the CD-R Tray Feeder and then press the RESUME button. Printing will then restart.\n"),
	N_("Printing cannot be executed because the inner cover is open.\n"),
	N_("Close the inner cover.\n"),
	N_("Press printer's RESUME button. Printing will restart.\n"),
	N_("Printing cannot be executed because the inner cover is open.\n"),
	N_("Press printer's OK button. Printing will restart.\n"),
	N_("The printer's front cover is open.\nIf printing is in progress, the print head or ink tank cannot be changed. Close the front cover, wait for printing to finish, then open the cover again and change the print head or ink tank. If the CD-R Tray Feeder is installed, the print head or ink tank cannot be also changed. Close the front cover, remove the CD-R Tray Feeder, open the front cover again, and change the print head or ink tank."),
	N_("During printing, the inner cover of the printer was opened.\n"),
	N_("Close the inner cover.\n"),
	N_("Press printer's RESUME button. Printing resumes from the next paper.\n"),
	N_("During printing, the inner cover of the printer was opened.\n"),
	N_("Press printer's OK button. Printing resumes from the next paper.\n"),
	N_("An ink cartridge is not installed properly.\nOpen the printer's cover, make sure the ink cartridge is installed properly, and close the cover.\n"),
	N_("A digital camera or device that is not supported by the direct printing function is connected to the direct print port. Disconnect the cable from the direct print port.\n"),	// 560i 860i 990i
	N_("An error occurred during automatic print head alignment.\n\nThe print head nozzles may be clogged. Execute cleaning on the Maintenance tab of the printer driver, and reexecute print head alignment.\n\nIf an error still occurs, refer to the user's guide to check the error or carry out manual alignment.\n\nPress the printer's RESUME button to clear the error.\n"), // 860i 990i
	N_("An error occurred during automatic print head alignment.\n\nThe print head nozzles may be clogged. Execute cleaning on the Maintenance tab of the printer driver, and reexecute print head alignment.\n\nIf an error still occurs, refer to the user's guide to check the error or carry out manual alignment.\n\nPress the printer's OK button to clear the error.\n"),
	N_("Ink tank errors have occurred.\nOpen the printer's cover and replace the ink tanks on which ink lamps are off."), 
	N_("More than one ink tank of the following color is installed.\n"),
	N_("The following ink tank cannot be recognized.\n"),
	N_("Some ink tanks are not installed in place.\nConfirm that the following ink tanks are installed in the appropriate positions.\n"),
	N_("The following ink tank cannot be recognized.\n"),
	N_("Ink has run out.\nReplace the ink tank and close the cover. When replacing the ink tank, make sure that the inner cover is open.\n\nIf printing is in progress and you want to continue printing, press the RESUME button with the ink tank installed. Then printing can continue under the ink out condition. Replace the empty ink tank immediately after the printing. The printer may be damaged if printing is continued under the ink out condition.\n"),
	N_("Ink has run out.\nReplace the ink tank and close the cover. When replacing the ink tank, make sure that the inner cover is open.\n\nIf printing is in progress and you want to continue printing, press the printer's OK button with the ink tank installed. Then printing can continue under the ink out condition. Replace the empty ink tank immediately after the printing. The printer may be damaged if printing is continued under the ink out condition.\n"),
	N_("The remaining level of the following ink cannot be correctly detected. Replace the ink tank.\n"),
	N_("The remaining level of the following ink cannot be correctly detected. Replace the ink tank.\n"),
	N_("The following ink cartridge cannot be recognized.\n"),
	N_("The following ink cartridge has previously been used.\n"),
	N_("The following ink cartridge has previously been used.\n"),
	N_("Ink has run out.\nReplace the ink cartridge and close the cover.\n\nIf printing is in progress and you want to continue printing, press the RESUME button with the ink cartridge installed. Then printing can continue under the ink out condition. Replace the empty ink cartridge immediately after the printing. The resulting print quality is not satisfactory, if printing is continued under the ink out condition.\n"),
	N_(" Black [7e]\n"),
	N_(" Black [9]\n"),
	N_(" Photo Cyan [7e]\n"),
	N_(" Photo Magenta [7e]\n"),
	N_(" Cyan [7e]\n"),
	N_(" Magenta [7e]\n"),
	N_(" Yellow [7e]\n"),
	N_(" Black\n"),
	N_(" Color\n"),
	N_(" Black [40]\n"),
	N_(" Black [50]\n"),
	N_(" Color [41]\n"),
	N_(" Color [51]\n"),
	N_(" Black [8]\n"),
	N_(" Black [5]\n"),
	N_(" Photo Cyan [8]\n"),
	N_(" Photo Magenta [8]\n"),
	N_(" Cyan [8]\n"),
	N_(" Magenta [8]\n"),
	N_(" Yellow [8]\n"),
	N_("Use only one ink tank per color at a time.\n"),
	N_("Printing cannot be executed because the ink cartridge may not be installed properly or may not be compatible with this printer.\n\nInstall the appropriate ink cartridge.\n"),
	N_("Printing cannot be executed because the ink tank may not be installed properly or may not be compatible with this printer.\n\nInstall the appropriate ink tank.\n"),
	N_("\nThe following ink tanks have run out.\n"),
	N_("\nPrinting under the current condition may damage the printer. Please be advised that Canon shall not be liable for any printer malfunction or damage caused by refilled ink tanks.\n\nTo continue printing, you need to release the function for detecting the remaining ink level. Press and hold the printer's RESUME button for at least 5 seconds, and then release it. Releasing the function for detecting the remaining ink level is memorized.\nThis operation will release the function for detecting the remaining level of the above ink.\n"),
	N_("\nPrinting under the current condition may damage the printer. Please be advised that Canon shall not be liable for any printer malfunction or damage caused by refilled ink tanks.\n\nTo continue printing, you need to release the function for detecting the remaining ink level. Press and hold the printer's Stop/Reset button for at least 5 seconds, and then release it. Releasing the function for detecting the remaining ink level is memorized.\nThis operation will release the function for detecting the remaining level of the above ink.\n"),
	N_("Printing cannot be executed because the ink cartridge may not be installed properly or may not be compatible with this printer.\n\nInstall the appropriate ink cartridge.\n"),
	N_("\nThe function for detecting the remaining ink level will be disabled since the ink level cannot be correctly detected.\n\nIf you want to continue printing without this function, press the RESUME button.\n"),
	N_("\nThe function for detecting the remaining ink level will be disabled since the ink level cannot be correctly detected.\n\nIf you want to continue printing without this function, press the RESUME button.\n\nCanon recommends to use new genuine Canon cartridges in order to obtain optimum qualities.\n"),
	N_("\nPrepare a new ink cartridge.\nIf either black or color ink cartridge has run out, you can set the printer to continue printing with the other cartridge from the Ink Cartridge Settings on the Maintenance tab of the printer driver.\n"),
};


PRIVATE const gchar	*gOtherMessageTable[] = {		// Other message table.
	N_("Ready.\n"),
	N_("Unknown printer.\n"),
	N_("Spooler error.\n"),
	"\n  cngpijmon : fatal error occured.\n",
	"  cngpijmon(2.01.01.006) : argument error.\n  Usage: cngpijmon****** [printer name]\n\n   ex) cngpijmonip3500 IP3500\n\n",
};

PUBLIC	gint	pictDrawFlg = TRUE;		// cartridge pixmap area draw flag.
PRIVATE	gint	updtPictFlg = FALSE;

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
				||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_OUT21		// ver.2.5
				||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_OUT22		// ver.2.5
				||  *pMssageID == ID_STS_MESSAGE_OC_PAPER_JAM
				||  *pMssageID == ID_STS_MESSAGE_OC_PAPER_JAM03			// ver.2.5
				||  *pMssageID == ID_STS_MESSAGE_OC_PAPER_JAM04			// ver.2.5
				||  *pMessageID == ID_STS_MESSAGE_OC_USBDEVICE			// Ver.2.4
				||  *pMessageID == ID_STS_MESSAGE_OC_HEADALIGNMENT		// Ver.2.4
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
				||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_OUT21		// ver.2.5
				||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_OUT22		// ver.2.5
				||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_JAM
				||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_JAM03			// ver.2.5
				||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_JAM04			// ver.2.5
				||  *pMessageID == ID_STS_MESSAGE_OC_USBDEVICE			// Ver.2.4
				||  *pMessageID == ID_STS_MESSAGE_OC_HEADALIGNMENT		// Ver.2.4
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
	gint				updtFlg;
	gint				drawFlg;
	gboolean			flag = FALSE;
	gboolean			unknownFlag = FALSE;
/*** Parameters end ***/
	
//	printf("updateUI ct:%d chd:%d\n",updateCT,updateCHD);

	if (updateCT == TRUE) {
		// Set cartridge type string.
		memset(tempBuf, 0, sizeof(tempBuf));
		strncpy(tempBuf, dgettext(PACKAGE, N_("Cartridge Type:")), MAX_BUF_SIZE-1);
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
					case ID_CARTRIDGE_TYPE_PHOTO_990i:		// 990i type.
					case ID_CARTRIDGE_TYPE_PHOTO_ip8600i:	// ip8600i type.
					case ID_CARTRIDGE_TYPE_PHOTO_COLOR:		// F360 type (Photo).
					case ID_CARTRIDGE_TYPE_PHOTO_ip6600d:	// iP6600D type.
					case ID_CARTRIDGE_TYPE_PHOTO_ip7500:	// iP7500 type.
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
					case ID_CARTRIDGE_TYPE_BLACK_ip2200:	// iP2200 type (Black)
					case ID_CARTRIDGE_TYPE_BLACK_HC_ip2200:	// iP2200 type (Black High Capa)
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
					case ID_CARTRIDGE_TYPE_COLOR_860i:		// 860i type.
					case ID_CARTRIDGE_TYPE_COLOR_S300:		// S300 type (CIL:OFF).
					case ID_CARTRIDGE_TYPE_COLOR_S300_CIL:	// S300 type (CIL:ON).
					case ID_CARTRIDGE_TYPE_COLOR_ip2200:	// iP2200 type (Color)
					case ID_CARTRIDGE_TYPE_COLOR_HC_ip2200:	// iP2200 type (Color High Capa)
					case ID_CARTRIDGE_TYPE_COLOR_ip4200:	// iP4200 type 
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
				strncpy(tempBuf, dgettext(PACKAGE, N_("Paper Thickness Lever Position:")), MAX_BUF_SIZE-1);
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
					if (*pMessageID == ID_STS_MESSAGE_SC_SERVICE_ERROR_PRE) {
						gchar * msgPtr = dgettext(PACKAGE, gSTSMessageTable[*pMessageID]);
						gchar * message1
							= (gchar*)g_malloc(strlen(msgPtr) + strlen(pPrinterStatus->serviceCallID) + 1);
						gchar * message2
							= (gchar*)g_malloc(strlen(msgPtr) + strlen(pPrinterStatus->serviceCallID) + 1);
						sprintf( message1, "%s", msgPtr );
						sprintf( message2, message1, pPrinterStatus->serviceCallID );
						insertStringToText_NoConv(STR_MAIN_TEXT_STATUS, message2);
						g_free(message1);
						g_free(message2);
						break;
					}
					else{
						insertStringToText(STR_MAIN_TEXT_STATUS, gSTSMessageTable[*pMessageID]);
					}
					pMessageID++;
				}
			}
		}
		freezeText(STR_MAIN_TEXT_STATUS, FALSE);
	}

	if( pPrinterStatus != NULL) {
		drawFlg = pictDrawFlg;	pictDrawFlg = TRUE;
		updtFlg = updtPictFlg;	updtPictFlg = FALSE;
		pMessageID = pPrinterStatus->pMessageID;
		for (i = 0; i < pPrinterStatus->messageNum; i++) {
			if( (*pMessageID == ID_STS_MESSAGE_OC_OTHER )
			 || (*pMessageID == ID_STS_MESSAGE_BUSY_PRINTER_USED ) ) {
				pictDrawFlg = FALSE;	// disable draw pict area
			}
			else if((*pMessageID == ID_STS_MESSAGE_OC_REFILL ) 
				 || (*pMessageID == ID_STS_MESSAGE_OC_REFILL2 )
				 || (*pMessageID == ID_STS_MESSAGE_OC_REMAIN_UNKNOWN1 )
				 || (*pMessageID == ID_STS_MESSAGE_OC_REMAIN_UNKNOWN2 ) ) {
				updtPictFlg = TRUE;
			}
			pMessageID++;
		}

		if( drawFlg != pictDrawFlg ) {
			if( pictDrawFlg == FALSE ) {
				// Clear cartridge pixmap area 
				clearCartridgePictArea();
			}
			else {
				// Draw cartridge pixmap area again forcibly
				updateCT = TRUE;
				updateCHD = TRUE;
			}
		}
		else if( updtFlg != updtPictFlg && updtPictFlg ) {
				updateCT = TRUE;
				updateCHD = TRUE;
		}
	}

	if ((updateCT == TRUE || updateCHD == TRUE) && pictDrawFlg) {
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

PRIVATE void insertStringToText_NoConv(const gchar *pWidgetName, const gchar *pString)
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
	gtk_text_insert(GTK_TEXT(widget), NULL, NULL, NULL, pString, -1);
#else	/* for GTK2 */
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
	gtk_text_buffer_get_start_iter(buffer, &start);
	gtk_text_buffer_get_end_iter(buffer, &end);
	if( pString != NULL )
	gtk_text_buffer_insert(buffer, &end, pString, -1);
#endif

	return;
}// End insertStringToText_NoConv

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
	GtkWidget	*widget = NULL;		// Temporary pointer to widget.
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
		fprintf(stderr, gOtherMessageTable[messageID]);
	}
	
	return;
}// End outputCommandLineMessage

