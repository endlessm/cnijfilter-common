/*
 *  Canon Inkjet Printer Driver for Linux
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
 */

/*** Includes ***/
#include <config.h>
#include <libintl.h>

#include "bjcupsmon_common.h"
#include "bjcupsmon_funcprot.h"

#include <time.h>
#include <sys/timeb.h>


/*** Global parameters ***/
PUBLIC ST_PrinterStatus	gPrinterStatus;			// Printer status.
PUBLIC gchar			gDestName[1024];		// Destination printer name.
PUBLIC gint				gTimeoutFuncTag = 0;	// Return value from gtk_timeout_add().

PRIVATE ST_ErrorCodeTbl	gErrorCodeTbl[] = {	// Error code table.
	{ID_ERR_NO_ERROR,				ID_ERR_LEVEL_NO_ERROR,	ID_OTHER_MESSAGE_NONE},
	{ID_ERR_ARGUMENT_ERR,			ID_ERR_LEVEL_FATAL,		ID_OTHER_MESSAGE_ARGUMENT_ERROR},
	{ID_ERR_MEM_ALLOC_FAILED,		ID_ERR_LEVEL_FATAL,		ID_OTHER_MESSAGE_FATAL_ERROR},
	{ID_ERR_LOAD_PIXMAP_FAILED,		ID_ERR_LEVEL_CONTINUE,	ID_OTHER_MESSAGE_NONE},
	{ID_ERR_CUPS_API_FAILED,		ID_ERR_LEVEL_CONTINUE,	ID_OTHER_MESSAGE_SPOOLER_ERROR},
	{ID_ERR_NO_PRINTER_ADDED,		ID_ERR_LEVEL_CONTINUE,	ID_OTHER_MESSAGE_UNKNOWN_PRINTER},
	{ID_ERR_UNKNOWN_PRINTER,		ID_ERR_LEVEL_CONTINUE,	ID_OTHER_MESSAGE_UNKNOWN_PRINTER},
	{ID_ERR_PRINT_JOB_NOT_EXIST,	ID_ERR_LEVEL_CONTINUE,	ID_OTHER_MESSAGE_PRINTER_IS_READY},
};


/*** Static function prototypes ***/
PRIVATE gint initApplication(gint, gchar**, gchar*);
PRIVATE gboolean updateUI(void);
PRIVATE void initPrinterStatus(ST_PrinterStatus*);
PRIVATE void SetGtkResourceDefault();


/*** Functions ***/
///////////////////////////////////////////////////////////////////////////////////////////
// 
// main function
// 
int main(gint argc, gchar *argv[])
{
/*** Parameters start ***/
	ST_ErrorCodeTbl	errorInfo;					// Error info.
	gchar			*pPrinterName = NULL;		// Printer name.
	gint			retVal = ID_ERR_NO_ERROR;	// Return value.
/*** Parameters end ***/
	
	// Argument check.
	if (argc > 2) {
		getErrorCodeInfo(ID_ERR_ARGUMENT_ERR, &errorInfo);
		outputCommandLineMessage(errorInfo.messageID);
	}
	else {
		if (argc == 2) {
			// Get specified printer name.
			pPrinterName = argv[1];
		}
		
		// Init UI and more.
		retVal = initApplication(argc, argv, pPrinterName);
		if (retVal == ID_ERR_NO_ERROR) {
			// Start main loop.
			gtk_main();
		}
		else {
			// Output error string on command line.
			getErrorCodeInfo(retVal, &errorInfo);
			outputCommandLineMessage(errorInfo.messageID);
		}
	}
	
	return(0);
}// End main


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE gint initApplication(gint argc, gchar *argv[], gchar *pPrinterName)
// IN     : gint argc : Number of arguments.
//          gchar *argv[] : Arguments.
//          gchar *pPrinterName : Printer name.
// OUT    : None.
// RETURN : ID_ERR_NO_ERROR : No error.
//          other : Error occured.
// 
PRIVATE gint initApplication(gint argc, gchar *argv[], gchar *pPrinterName)
{
/*** Parameters start ***/
	ST_ErrorCodeTbl	errorInfo;					// Error info.
	gchar			productName[MAX_BUF_SIZE];	// Product name.
	gchar			windowTitle[MAX_BUF_SIZE];	// Window title.
	gchar			statusStr[MAX_BUF_SIZE];	// Buffer for printer status message.
	gboolean		printerReady = FALSE;		// Flag for printer is ready or not.
	gboolean		jobExist = FALSE;			// Flag for active job exist or not.
	gint			i = 0, j = 0;				// Counter.
	gint			retVal = ID_ERR_NO_ERROR;	// Return value.
	gchar			small_modelname[MAX_BUF_SIZE];// smallmodel name.
	gchar			manufacture[MAX_BUF_SIZE];	// manufacture name.
	gchar			tmp_modelname[MAX_BUF_SIZE];// tmp name.
	gchar			module_name[MAX_BUF_SIZE];	// module name.
//	gint			cnt = 0;					// Counter.
	gint			mismatch_flag = 0;			// Mismatch Flag.
/*** Parameters end ***/
	
	// Initialize buffer.
	memset(gDestName, 0, sizeof(gDestName));
	memset(productName, 0, sizeof(productName));
	memset(windowTitle, 0, sizeof(windowTitle));
	memset(statusStr, 0, sizeof(statusStr));
	memset(small_modelname, 0, sizeof(small_modelname));
	memset(tmp_modelname, 0, sizeof(small_modelname));
	memset(manufacture, 0, sizeof(manufacture));
	memset(module_name, 0, sizeof(module_name));

//	strcpy(windowTitle, STR_MANUFACTURER_NAME);		delete V2.3
//	strcat(windowTitle, " ");						delete V2.3
	
	// Initialize printer status area.
	initPrinterStatus(&gPrinterStatus);
	
	if (pPrinterName == NULL) {
		// Printer name is not input. Get default printer name.
		retVal = getDefaultPrinterName(gDestName, sizeof(gDestName));
		if (retVal != ID_ERR_NO_ERROR) {
			memset(&errorInfo, 0, sizeof(ST_ErrorCodeTbl));
			getErrorCodeInfo(retVal, &errorInfo);
			if (errorInfo.errorLevel != ID_ERR_LEVEL_FATAL) {
				retVal = ID_ERR_NO_ERROR;
			}
		}
	}
	else {
		strncpy(gDestName, pPrinterName, sizeof(gDestName));
	}
	
	if (retVal == ID_ERR_NO_ERROR) {
		// Init GTK, Glade, etc.
		bindtextdomain(PACKAGE, PACKAGE_LOCALE_DIR);
		/* for GTK 2.X */
		bind_textdomain_codeset (PACKAGE, "UTF-8");
		textdomain(PACKAGE);


#ifndef USE_libglade
		SetGtkResourceDefault();
#endif 
		gtk_set_locale();
		gtk_init(&argc, &argv);

#ifdef USE_libglade
		glade_init();
#endif // USE_libglade

		// Get printer product name. (for create window title string)
		retVal = getProductName(gDestName, productName);
		if (retVal == ID_ERR_NO_ERROR) {
//			while (productName[i] != 0) {
//				productName[i] = toupper(productName[i]);
//				i++;
//			}

			// check cngpijmonip4300 and ppd productName
			strncat(manufacture, STR_MANUFACTURER_NAME, strlen(STR_MANUFACTURER_NAME) );
			for( i=0,j=0; i<(sizeof(productName) - 1) ; i++){
				if(manufacture[i] != productName[i]){
					tmp_modelname[j] = tolower(productName[i+1]);
					j++;
				}
				tmp_modelname[j] = '\0';
			}
	
			for( i=0,j=0; i<(sizeof(tmp_modelname) - 1) ; i++){
				if(tmp_modelname[i] == ' ') 
					break;
				else{
					small_modelname[j] = tmp_modelname[i];
					j++;
				}
				small_modelname[j] = '\0';
			}
	
			snprintf(module_name, sizeof(module_name), "%s%s",STR_APPLICATION_NAME, small_modelname);
	
			for( i=0; i<strlen(module_name) ; i++){
				if( module_name[i] != *(argv[0]+i) ){
					memset(productName, 0, sizeof(productName));
					snprintf(productName, sizeof(productName), "%s%s", STR_MANUFACTURER_NAME, "");
					mismatch_flag = 1;
				}
			}
			// check cngpijmonip4300 and ppd productName

			strncpy(windowTitle, productName, sizeof(windowTitle)-strlen(STR_PRODUCT_NAME)-1 );		// V2.3 strcat->strcpy
			strncat(windowTitle, " ", strlen(" "));
			strncat(windowTitle, STR_PRODUCT_NAME, strlen(STR_PRODUCT_NAME));

			// Check printer and job.
			retVal = checkPrinterAndJobState(gDestName, &printerReady, &jobExist);
			if (retVal == ID_ERR_NO_ERROR) {

				if ( (printerReady == FALSE) || (mismatch_flag == 1) ) {
				//if (printerReady == FALSE) {
					// Printer is not registerd in CUPS.
					retVal = ID_ERR_UNKNOWN_PRINTER;
				}
				else {
					// Printer is registerd in CUPS.
					if (jobExist == FALSE) {
						// Print job not exist.
						retVal = ID_ERR_PRINT_JOB_NOT_EXIST;
					}
					else {
						// Print job exist. Get printer status string.
						getPrinterStatus(gDestName, statusStr, sizeof(statusStr));
						retVal = getPrinterStatus(gDestName, statusStr, sizeof(statusStr));
						if (retVal == ID_ERR_NO_ERROR) {
							// Check status string.
							if (strncmp(statusStr, STR_HEADER_STATUS_STRING, strlen(STR_HEADER_STATUS_STRING)) == 0) {
								// Get printer status information.
								retVal = translatePrinterStatus(statusStr, &gPrinterStatus);
							}
							
							if (retVal == ID_ERR_NO_ERROR) {
								// Init UI.
								initUI(windowTitle, &gPrinterStatus, TRUE, -1);
								
								// Set calling timeout function.
								gTimeoutFuncTag = gtk_timeout_add(TIMEOUT_CALL_UPDATE_UI_FUNC, (GtkFunction)updateUI, NULL);
							}
						}
					}
				}
			}
		}
		else {
			strncpy(windowTitle, STR_MANUFACTURER_NAME, sizeof(windowTitle)-strlen(STR_PRODUCT_NAME)-1 );		// V2.3 add
			strncat(windowTitle, " ", strlen(" "));						// V2.3 add
			strncat(windowTitle, STR_PRODUCT_NAME, strlen(STR_PRODUCT_NAME));
		}
	}
	
	if (retVal != ID_ERR_NO_ERROR) {
		// Check error.
		memset(&errorInfo, 0, sizeof(ST_ErrorCodeTbl));
		getErrorCodeInfo(retVal, &errorInfo);
		if (errorInfo.errorLevel != ID_ERR_LEVEL_FATAL) {
			// Process continuing is possible. Init UI.
			initUI(windowTitle, NULL, FALSE, errorInfo.messageID);
			if (retVal != ID_ERR_UNKNOWN_PRINTER) {
				// Set calling timeout function.
				gTimeoutFuncTag = gtk_timeout_add(TIMEOUT_CALL_UPDATE_UI_FUNC, (GtkFunction)updateUI, NULL);
			}
			retVal = ID_ERR_NO_ERROR;
		}
	}

	return(retVal);
}// End initApplication


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC void closeApplication(void)
// IN     : None.
// OUT    : None.
// RETURN : None.
// 
PUBLIC void closeApplication(void)
{
	// Free message ID area.
	if (gPrinterStatus.pMessageID != NULL) {
		free(gPrinterStatus.pMessageID);
		/* for GTK2 ver280 */
		gPrinterStatus.pMessageID = NULL;
	}
	
	// Free pixmaps of cartridge.
	freePixmaps();
	
	// Stop calling timeout function.
	if (gTimeoutFuncTag != 0) {
		gtk_timeout_remove(gTimeoutFuncTag);
	}
	
	// Close application.
	gtk_main_quit();
	
	return;
}// End closeApplication


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE gboolean updateUI(void)
// IN     : None.
// OUT    : None.
// RETURN : Always TRUE.
// 
PRIVATE gboolean updateUI(void)
{
/*** Parameters start ***/
	ST_PrinterStatus	printerStatus;				// Printer status.
	ST_ErrorCodeTbl		errorInfo;					// Error info.
	gboolean			jobExist = FALSE;			// Flag for active job exist or not.
	gchar				statusStr[1024];			// Buffer for printer status message.
	gboolean			ctChanged = FALSE;			// Flag for cartridge type changed or not.
	gboolean			lpChanged = FALSE;			// Flag for lever position changed or not.
	gboolean			msgChanged = FALSE;			// Flag for status messages changed or not.
	gboolean			chdChanged = FALSE;			// Flag for cartridge status changed or not.
	ENUM_STSMessageID	*pMessageID;				// Pointer to array of message ID.
	gint				i;							// Counter.
	gint				retVal = ID_ERR_NO_ERROR;	// Return value.
	struct timeb		curTime;
	static struct timeb	prevTime;
	static gboolean		initTime = FALSE;
/*** Parameters end ***/

	if (initTime == FALSE) {
		initTime = TRUE;
	}
	else {
		double diffSec;
		unsigned long diffMilliSec;

		ftime(&curTime);
		diffSec = difftime(curTime.time, prevTime.time);
		diffMilliSec = (unsigned long)(diffSec * 1000.0) + curTime.millitm - prevTime.millitm;

		if (diffMilliSec < TIMEOUT_CALL_UPDATE_UI_FUNC / 2) {
			return(TRUE);
		}
	}

	// Check printer and job.
	retVal = checkPrinterAndJobState(gDestName, NULL, &jobExist);
	if (retVal == ID_ERR_NO_ERROR) {

		//// Disable [Cancel Printing] button.
		//activateWidget(STR_MAIN_BUTTON_NAME_CANCEL, FALSE);
			
		if (jobExist == FALSE) {
			retVal = ID_ERR_PRINT_JOB_NOT_EXIST;
		}
		else {
			// Get printer status string.
			getPrinterStatus(gDestName, statusStr, sizeof(statusStr));
			retVal = getPrinterStatus(gDestName, statusStr, sizeof(statusStr));
			if (retVal == ID_ERR_NO_ERROR) {
				// Check status string.
				if (strncmp(statusStr, STR_HEADER_STATUS_STRING, strlen(STR_HEADER_STATUS_STRING)) == 0) {
					// Initialize printer status area.
					initPrinterStatus(&printerStatus);
					
					// Get printer status information.
					retVal = translatePrinterStatus(statusStr, &printerStatus);
					if (retVal == ID_ERR_NO_ERROR) {

						// Enable [Cancel Printing] button.
						//if (gPrinterStatus.printInterface == ID_DEV_1284 )
						//	activateWidget(STR_MAIN_BUTTON_NAME_CANCEL, TRUE);
			
						// Check status changed or not.
						
						// Check cartridge class.
						if (memcmp(printerStatus.cartridgeClass, gPrinterStatus.cartridgeClass, sizeof(ST_CartridgeClass) * 2) != 0) {
							// Cartridge class changed. Update cartridge class area of UI.
							ctChanged = TRUE;
						}
						
						// Check lever position.
						if (printerStatus.leverPosition != gPrinterStatus.leverPosition) {
							// Lever position changed. Update lever position area of UI.
							lpChanged = TRUE;
						}
						
						// Check cartridge status.
						if (memcmp(printerStatus.cartridgeStatus, gPrinterStatus.cartridgeStatus, sizeof(ST_InkStatus) * CARTRIDGE_COLOR_TYPE_NUM) != 0) {
							// Cartridge status changed. Update cartridge pixmap area of UI.
							chdChanged = TRUE;
						}
						
						// Check number of messages.
						if (printerStatus.messageNum != gPrinterStatus.messageNum) {
							// Number of messages changed, then messages changed. Update messages area of UI.
							msgChanged = TRUE;
						}
						else if (printerStatus.messageNum > 0) {
							// Check messages and service call ID.
							if (memcmp(printerStatus.pMessageID, gPrinterStatus.pMessageID, sizeof(ENUM_STSMessageID) * printerStatus.messageNum) != 0) {
								// Messages changed. Update messages area of UI.
								msgChanged = TRUE;
							}
							else if (memcmp(printerStatus.serviceCallID, gPrinterStatus.serviceCallID, 4) != 0) {
								// Service call ID changed. Update messaegs area of UI.
								msgChanged = TRUE;
							}
						}
						
						// Update UI.
						updateUISettings(&printerStatus, ID_OTHER_MESSAGE_NONE, ctChanged, lpChanged, msgChanged, chdChanged);
						
						// Check messages.
						pMessageID = printerStatus.pMessageID;
						for (i = 0; i < printerStatus.messageNum; i++) {
							//Ver.2.80 Delete old massage
							if (*pMessageID == ID_STS_MESSAGE_OC_PAPER_OUT
							//if (*pMessageID == ID_STS_MESSAGE_CARTRIDGE_UNSUPPORTED
							//||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_OUT
							||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_OUT21		// ver.2.5
							||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_OUT22		// ver.2.5
							||  *pMessageID == ID_STS_MESSAGE_OC_PAPER_JAM
							||  *pMessageID == ID_STS_MESSAGE_OC_USBDEVICE			// Ver.2.4
							||  *pMessageID == ID_STS_MESSAGE_OC_HEADALIGNMENT		// Ver.2.4
							) {
								// Disable [Cancel Printing] button.
								//activateWidget(STR_MAIN_BUTTON_NAME_CANCEL, FALSE);
								break;
							}
							pMessageID++;
						}
						
						if (gPrinterStatus.pMessageID != NULL) {
							free(gPrinterStatus.pMessageID);
							gPrinterStatus.pMessageID = NULL;
						}
						memcpy(&gPrinterStatus, &printerStatus, sizeof(ST_PrinterStatus));
					}
				}
			}
		}
	}
	
	if (retVal != ID_ERR_NO_ERROR) {
		// Check error.
		memset(&errorInfo, 0, sizeof(ST_ErrorCodeTbl));
		getErrorCodeInfo(retVal, &errorInfo);
		if (errorInfo.errorLevel != ID_ERR_LEVEL_FATAL) {
			// Process continuing is possible.
			// Initialize printer status area.
			if (gPrinterStatus.pMessageID != NULL) {
				free(gPrinterStatus.pMessageID);
			}
			initPrinterStatus(&gPrinterStatus);
			// Update UI.
			updateUISettings(NULL, errorInfo.messageID, TRUE, TRUE, TRUE, TRUE);
		}
		else {
			// Show error message on command line.
			outputCommandLineMessage(errorInfo.messageID);
			// Close application.
			closeApplication();
		}
	}

	ftime(&prevTime);

	return(TRUE);
}// End updateUI


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE void initPrinterStatus(ST_PrinterStatus *pPrinterStatus)
// IN     : ST_PrinterStatus *pPrinterStatus : Structure for printer status.
// OUT    : None.
// RETURN : None.
// 
PRIVATE void initPrinterStatus(ST_PrinterStatus *pPrinterStatus)
{
	// Initialize printer status area.
	memset(pPrinterStatus, 0, sizeof(ST_PrinterStatus));
	memset(pPrinterStatus->cartridgeStatus, -1, sizeof(ST_InkStatus) * CARTRIDGE_COLOR_TYPE_NUM);
	
	return;
}// End initPrinterStatus


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC void getErrorCodeInfo(gint errorCode, ST_ErrorCodeTbl *pErrorInfo)
// IN     : gint errorCode : Error code.
// OUT    : ST_ErrorCodeTbl *pErrorInfo : Information of error code.
// RETURN : None.
// 
PUBLIC void getErrorCodeInfo(gint errorCode, ST_ErrorCodeTbl *pErrorInfo)
{
/*** Parameters start ***/
	guint	tableSize = sizeof(gErrorCodeTbl) / sizeof(ST_ErrorCodeTbl);	// Size of error code table.
	guint	i = 0;		// Counter.
/*** Parameters end ***/
	
	if (pErrorInfo != NULL) {
		// Search error code table.
		while (i < tableSize) {
			if (gErrorCodeTbl[i].errorCode == errorCode) {
				// Found.
				memcpy(pErrorInfo, &(gErrorCodeTbl[i]), sizeof(ST_ErrorCodeTbl));
				break;
			}
			i++;
		}
	}
	
	return;
}// End getErrorCodeInfo


///////////////////////////////////////////////////////////////////////////////////////////
// 
// PUBLIC void SetGtkResourceDefault()
// IN     : None.
// OUT    : None.
// RETURN : pointer to default Resource file path 
// 
PUBLIC void SetGtkResourceDefault()
{
//	gchar* home_dir = NULL;
	gchar* rc_path = NULL;

//	home_dir = g_get_home_dir();
//	rc_path = g_strdup_printf("%s/.gtkrc",home_dir);
	rc_path = g_strdup_printf("%s/.gtkrc",g_get_home_dir());
	gtk_rc_add_default_file(rc_path);
	g_free(rc_path);
}

