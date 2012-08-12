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
#include <cups/cups.h>
#include <cups/ppd.h>
#include <cups/language.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>


#include "bjcupsmon_common.h"
#include "bjcupsmon_cups.h"

//////////////////////////////////////////////////////////////
// 
// CS     :	PRIVATE cups_lang_t * bjcupsLangDefault()
// IN     : none
// OUT    : LC_ALL(locale)
// RETURN : pointer to cupa_lang_t structure
//
// This routine written for cups-1.1.19 Turbolinux10(Suzuka)
// Replace to cupsLangDefault()
//
PRIVATE cups_lang_t * bjcupsLangDefault( )
{
	cups_lang_t	*pLanguage;
	char		*tLang;	
	
	if( (tLang = getenv("LC_ALL"))==NULL)
			tLang = getenv("LANG");
	
	pLanguage = cupsLangDefault();
	setlocale(LC_ALL,tLang);
	
	return pLanguage;
}


/*** Functions ***/
///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC gint getDefaultPrinterName(gchar *pDestName, gint bufSize)
// IN     : gint bufSize : Size of buffer for default printer name.
// OUT    : gchar *pDestName : Default printer name of CUPS.
// RETURN : ID_ERR_NO_ERROR : No error.
//          ID_ERR_CUPS_API_FAILED : Error occured in CUPS API.
//          ID_ERR_NO_PRINTER_ADDED : No printer registered into CUPS.
// 
PUBLIC gint getDefaultPrinterName(gchar *pDestName, gint bufSize)
{
/*** Parameters start ***/
	cups_dest_t	*pDests;							// Destinations.
	gint		numDests;							// Number of destinations.
	gint		i;									// Counter.
	gint		retVal = ID_ERR_NO_PRINTER_ADDED;	// Return value.
/*** Parameters end ***/
	
	// Get all dests.
	numDests = cupsGetDests(&pDests);
	
	for (i = 0; i < numDests; i++) {
		if (pDests[i].is_default != 0) {
			// Default printer found.
			strncpy(pDestName, pDests[i].name, bufSize);
			retVal = ID_ERR_NO_ERROR;
			break;
		}
	}
	
	cupsFreeDests(numDests, pDests);
	
	return(retVal);
}// End getDefaultPrinterName


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC gint getProductName(gchar *pDestName, gchar *pProductName)
// IN     : gchar *pDestName : Printer name.
// OUT    : gchar *pProductName : Product name. ( ModelName )
// RETURN : ID_ERR_NO_ERROR : No error.
//          ID_ERR_UNKNOWN_PRINTER : Getting product name failed.
// 
PUBLIC gint getProductName(gchar *pDestName, gchar *pProductName, gchar *pModelIDstr)
//PUBLIC gint getProductName(gchar *pDestName, gchar *pProductName)
{
/*** Parameters start ***/
	const gchar	*pPPDName = NULL;					// Pointer to PPD file name.
	ppd_file_t	*pPPD;								// Pointer to PPD file.
	gint		retVal = ID_ERR_UNKNOWN_PRINTER;	// Return value.
	ipp_status_t status;
/*** Parameters start ***/

	// Get PPD file name.
	pPPDName = cupsGetPPD(pDestName);
	if (pPPDName != NULL) {
		if ((pPPD = ppdOpenFile(pPPDName)) != NULL) {
			if (strcmp(pPPD->manufacturer, STR_MANUFACTURER_NAME) == 0) {
				strncpy(pProductName, pPPD->modelname, strlen(pPPD->modelname));	// use modelname from 22th Jan.'03
				/* Ver.3.20 for modelID to cnijnpr */
				snprintf(pModelIDstr, sizeof(pModelIDstr), "%d", pPPD->model_number);
				retVal = ID_ERR_NO_ERROR;
			}
			ppdClose(pPPD);
		}
		unlink(pPPDName);	// Tora 020418: You should remove the copy of the PPD file.
	}
	else {
		status = cupsLastError();
		if( status == IPP_SERVICE_UNAVAILABLE )	// cupsd stop status
			retVal = ID_ERR_CUPS_API_FAILED;
	}
	
	return(retVal);
}// End getProductName


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC gint checkPrinterAndJobState(gchar *pDestName, gboolean *pPrinterReady, gboolean *pJobExist)
// IN     : gchar *pDestName : Printer name.
// OUT    : gboolean *pPrinterReady : Any printers registered into CUPS or not.
//          gboolean *pJobExist : Active job exists or not.
// RETURN : ID_ERR_NO_ERROR : No error.
//          ID_ERR_CUPS_API_FAILED : Error occured in CUPS API.
// 
PUBLIC gint checkPrinterAndJobState(gchar *pDestName, gboolean *pPrinterReady, gboolean *pJobExist)
{
/*** Parameters start ***/
	gchar	printerURI[HTTP_MAX_URI];	// Printer URI.
	gchar	serverName[HTTP_MAX_URI];	// CUPS server name.
	gint	retVal = ID_ERR_NO_ERROR;	// Return value.
/*** Parameters end ***/
	
	snprintf(printerURI, sizeof(printerURI), "ipp://localhost/printers/%s", pDestName);
	strncpy(serverName, "localhost", HTTP_MAX_URI-1);
	
	// Check printer state.
	retVal = checkPrinterState(pDestName, printerURI, serverName);
	if (retVal == ID_ERR_NO_ERROR) {
		if (pPrinterReady != NULL) {
			*pPrinterReady = TRUE;
		}
	}
	else {
		if (pPrinterReady != NULL) {
			*pPrinterReady = FALSE;
		}
	}
	
	if (retVal == ID_ERR_NO_ERROR && pJobExist != NULL) {
		// Check active job exist.
		retVal = getJobID(pDestName, printerURI, serverName, NULL);
		if (retVal == ID_ERR_NO_ERROR) {
			*pJobExist = TRUE;
		}
		else {
			*pJobExist = FALSE;
		}
	}
	
	if (retVal == ID_ERR_UNKNOWN_PRINTER || retVal == ID_ERR_PRINT_JOB_NOT_EXIST) {
		retVal = ID_ERR_NO_ERROR;
	}
	
	return(retVal);
}// End getPrinterAndJobState


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE gint checkPrinterState(gchar *pDestName, gchar *pURI, gchar *pServerName)
// IN     : gchar *pDestName : Printer name.
//          gchar *pURI : Printer URI.
//          gchar *pServerName : CUPS server name.
// OUT    : None.
// RETURN : ID_ERR_NO_ERROR : No error.
//          ID_ERR_UNKNOWN_PRINTER : No printer registerd in CUPS.
//          ID_ERR_CUPS_API_FAILED : Error occured in CUPS API.
// 
PRIVATE gint checkPrinterState(gchar *pDestName, gchar *pURI, gchar *pServerName)
{
/*** Parameters start ***/
	http_t			*pHTTP;								// Pointer to HTTP connection.
	ipp_t			*pRequest,							// Pointer to CUPS IPP request.
					*pResponse;							// Pointer to CUPS IPP response.
	ipp_attribute_t	*pAttribute;						// Pointer to CUPS attributes.
	cups_lang_t		*pLanguage;							// Pointer to language.
	ipp_pstate_t	printerState = IPP_PRINTER_STOPPED;	// Pointer to printer state.
	gint			retVal = ID_ERR_UNKNOWN_PRINTER;	// Return value.
/*** Parameters end ***/
	
	// CUPS http connect.
	if ((pHTTP = httpConnectEncrypt(pServerName, ippPort(), cupsEncryption())) == NULL) {
		retVal = ID_ERR_CUPS_API_FAILED;
	}
	else {
		pRequest = ippNew();
		
		pRequest->request.op.operation_id = IPP_GET_PRINTER_ATTRIBUTES;
		pRequest->request.op.request_id   = 1;
		
		pLanguage = bjcupsLangDefault();			// cupsLangDefault() -> bjcupsLangDefault() for cups-1.1.19 
				
		ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_CHARSET, "attributes-charset", NULL, cupsLangEncoding(pLanguage));
		ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_LANGUAGE, "attributes-natural-language", NULL, pLanguage->language);
		ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri", NULL, pURI);

		if ((pResponse = cupsDoRequest(pHTTP, pRequest, "/")) != NULL) {
			if (pResponse->request.status.status_code > IPP_OK_CONFLICT) {
				retVal = ID_ERR_CUPS_API_FAILED;
			}
			else {
				if ((pAttribute = ippFindAttribute(pResponse, "printer-state", IPP_TAG_ENUM)) != NULL) {
					printerState = (ipp_state_t)pAttribute->values[0].integer;
				}
			}
			
			ippDelete(pResponse);
		}
		else {
			retVal = ID_ERR_CUPS_API_FAILED;
		}
		
		cupsLangFree(pLanguage);
		httpClose(pHTTP);
	}
	
	if (printerState == IPP_PRINTER_IDLE || printerState == IPP_PRINTER_PROCESSING) {
		retVal = ID_ERR_NO_ERROR;
	}
	
	return(retVal);
}// End checkPrinterState


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC gint getPrinterStatus(gchar *pDestName, gchar *pStatus, gint bufSize)
// IN     : gchar *pDestName : Printer name.
//          gint bufSize : Size of output buffer.
// OUT    : gchar *pStatus : Printer status string.
// RETURN : ID_ERR_NO_ERROR : No error.
//          ID_ERR_CUPS_API_FAILED : Error occured in CUPS API.
// 
PUBLIC gint getPrinterStatus(gchar *pDestName, gchar *pStatus, gint bufSize)
{
/*** Parameters start ***/
	http_t			*pHTTP;						// Pointer to HTTP connection.
	ipp_t			*pRequest,					// Pointer to CUPS IPP request.
					*pResponse;					// Pointer to CUPS IPP response.
	ipp_attribute_t	*pAttribute;				// Pointer to CUPS attributes.
	cups_lang_t		*pLanguage;					// Pointer to language.
	gchar			printerURI[HTTP_MAX_URI];	// Printer URI.
	gchar			serverName[HTTP_MAX_URI];	// CUPS server name.
	gint			retVal = ID_ERR_NO_ERROR;	// Return value.
/*** Parameters end ***/
	
	// Initialize buffer.
	memset(printerURI, 0, sizeof(printerURI));
	memset(serverName, 0, sizeof(serverName));
	
	// Get printer URI and CUPS server name.
	retVal = getPrinterURI(pDestName, printerURI, serverName, HTTP_MAX_URI);
	if (retVal == ID_ERR_NO_ERROR) {
		// CUPS http connect.
		if ((pHTTP = httpConnectEncrypt(serverName, ippPort(), cupsEncryption())) == NULL) {
			retVal = ID_ERR_CUPS_API_FAILED;
		}
		else {
			pRequest = ippNew();
			
			pRequest->request.op.operation_id = IPP_GET_PRINTER_ATTRIBUTES;
			pRequest->request.op.request_id   = 1;
			
			pLanguage = bjcupsLangDefault();		// cupsLangDefault() -> bjcupsLangDefault() for cups-1.1.19
			
			ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_CHARSET, "attributes-charset", NULL, cupsLangEncoding(pLanguage));
			ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_LANGUAGE, "attributes-natural-language", NULL, pLanguage->language);
			ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri", NULL, printerURI);
			
			if ((pResponse = cupsDoRequest(pHTTP, pRequest, "/")) != NULL) {
				if (pResponse->request.status.status_code > IPP_OK_CONFLICT) {
					retVal = ID_ERR_CUPS_API_FAILED;
				}
				else {
					/* for Network Ver.3.10 */
					//pAttribute = ippFindAttribute(pResponse, "device-uri", IPP_TAG_URI);
					//if (pAttribute != NULL) {
					//	strncpy(pStatus, pAttribute->values[0].string.text, bufSize);
					//	printf("DeviceURI = %s\n",pAttribute->values[0].string.text);
					//}
					pAttribute = ippFindAttribute(pResponse, "printer-state-message", IPP_TAG_TEXT);
					if (pAttribute != NULL) {
						strncpy(pStatus, pAttribute->values[0].string.text, bufSize);
					}
				}
				ippDelete(pResponse);
			}
			else {
				retVal = ID_ERR_CUPS_API_FAILED;
			}
			
			cupsLangFree(pLanguage);
			httpClose(pHTTP);
		}
	}
	
	return(retVal);
}// End getPrinterStatus


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC gint removeJob(gchar *pDestName)
// IN     : gchar *pDestName : Printer name.
// OUT    : None.
// RETURN : ID_ERR_NO_ERROR : No error.
//          ID_ERR_CUPS_API_FAILED : Error occured in CUPS API.
// 
PUBLIC gint removeJob(gchar *pDestName)
{
/*** Parameters start ***/
	http_t			*pHTTP;						// Pointer to HTTP connection.
	ipp_t			*pRequest,					// Pointer to CUPS IPP request.
					*pResponse;					// Pointer to CUPS IPP response.
	cups_lang_t		*pLanguage;					// Pointer to language.
	gchar			printerURI[HTTP_MAX_URI];	// Printer URI.
	gchar			serverName[HTTP_MAX_URI];	// CUPS server name.
	gint			jobID = 0;					// Job ID.
	gint			retVal = ID_ERR_NO_ERROR;	// Return value.
/*** Parameters end ***/
	
	// Initialize buffer.
	memset(printerURI, 0, sizeof(printerURI));
	memset(serverName, 0, sizeof(serverName));
	
	// Get printer URI and CUPS server name.
	retVal = getPrinterURI(pDestName, printerURI, serverName, HTTP_MAX_URI);
	if (retVal == ID_ERR_NO_ERROR) {
		retVal = getJobID(pDestName, printerURI, serverName, &jobID);
		if (retVal == ID_ERR_PRINT_JOB_NOT_EXIST) {
			retVal = ID_ERR_NO_ERROR;
		}
		
		if (retVal == ID_ERR_NO_ERROR) {
			// CUPS http connect.
			if ((pHTTP = httpConnectEncrypt(serverName, ippPort(), cupsEncryption())) == NULL) {
				retVal = ID_ERR_CUPS_API_FAILED;
			}
			else {
				pRequest = ippNew();
				
				pRequest->request.op.operation_id = IPP_CANCEL_JOB;
				pRequest->request.op.request_id   = 1;
				
				pLanguage = bjcupsLangDefault();		// cupsLangDefault() -> bjcupsLangDefault() for cups-1.1.19
				
				ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_CHARSET, "attributes-charset", NULL, cupsLangEncoding(pLanguage));
				ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_LANGUAGE, "attributes-natural-language", NULL, pLanguage->language);
				ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri", NULL, printerURI);
				ippAddInteger(pRequest, IPP_TAG_OPERATION, IPP_TAG_INTEGER, "job-id", jobID);
				ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_NAME, "requesting-user-name", NULL, cupsUser());
				
				if ((pResponse = cupsDoRequest(pHTTP, pRequest, "/jobs/")) != NULL) {
					if (pResponse->request.status.status_code > IPP_OK_CONFLICT) {
						retVal = ID_ERR_CUPS_API_FAILED;
					}
					ippDelete(pResponse);
				}
				else {
					retVal = ID_ERR_CUPS_API_FAILED;
				}
				
				cupsLangFree(pLanguage);
				httpClose(pHTTP);
			}
		}
	}
	
	return(retVal);
}// End removeJob


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE gint getJobID(gchar *pDestName, gchar *pURI, gchar *pServerName, gint *pJobID)
// IN     : gchar *pDestName : Printer name.
//          gchar *pURI : Printer URI.
//          gchar *pServerName : CUPS server name.
// OUT    : gint *pJobID : Job ID.
// RETURN : ID_ERR_NO_ERROR : No error.
//          ID_ERR_CUPS_API_FAILED : Error occured in CUPS API.
// 
PRIVATE gint getJobID(gchar *pDestName, gchar *pURI, gchar *pServerName, gint *pJobID)
{
/*** Parameters start ***/
	http_t			*pHTTP;									// Pointer to HTTP connection.
	ipp_t			*pRequest,								// Pointer to CUPS IPP request.
					*pResponse;								// Pointer to CUPS IPP response.
	ipp_attribute_t	*pAttribute;							// Pointer to CUPS attributes.
	cups_lang_t		*pLanguage;								// Pointer to language.
	ipp_jstate_t	jobState = 0;							// Job state.
	gint			jobID = 0;								// Job ID.
	gchar			*pJobUserName = NULL;					// User name of print job.
	uid_t			userID;									// User ID.
	struct passwd	*pPasswd;								// Pointer to password structure.
	gint			retVal = ID_ERR_PRINT_JOB_NOT_EXIST;	// Return value.
	//for CUPS 1.4.3 STR #3383
	static const char * const jobattrs[] =					// Job attributes
 		{
		  "job-id",
		  "job-originating-user-name",
		  "job-state"
		};
/*** Parameters end ***/
	
	// Get login name.
	userID = getuid();
	pPasswd = getpwuid(userID);
	
	// CUPS http connect.
	if ((pHTTP = httpConnectEncrypt(pServerName, ippPort(), cupsEncryption())) == NULL) {
		retVal = ID_ERR_CUPS_API_FAILED;
	}
	else {
		pRequest = ippNew();
		
		pRequest->request.op.operation_id = IPP_GET_JOBS;
		pRequest->request.op.request_id   = 1;
		
		pLanguage = bjcupsLangDefault();	// cupsLangDefault() -> bjcupsLangDefault() for cups-1.1.19
		
		ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_CHARSET, "attributes-charset", NULL, cupsLangEncoding(pLanguage));
		ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_LANGUAGE, "attributes-natural-language", NULL, pLanguage->language);
		ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri", NULL, pURI);
		//for CUPS 1.4.3 STR #3383
		ippAddStrings(pRequest, IPP_TAG_OPERATION, IPP_TAG_KEYWORD, "requested-attributes",(int)(sizeof(jobattrs) / sizeof(jobattrs[0])), NULL, jobattrs);
		
		if ((pResponse = cupsDoRequest(pHTTP, pRequest, "/")) != NULL) {
			if (pResponse->request.status.status_code > IPP_OK_CONFLICT) {
				retVal = ID_ERR_CUPS_API_FAILED;
			}
			else {
				pAttribute = pResponse->attrs;

				while (pAttribute != NULL) {
					while (pAttribute != NULL && pAttribute->group_tag != IPP_TAG_JOB) {
						pAttribute = pAttribute->next;
					}
					if (pAttribute == NULL) {
						break;
					}
					
					while (pAttribute != NULL && pAttribute->group_tag == IPP_TAG_JOB) {
						if (strcmp(pAttribute->name, "job-id") == 0 && pAttribute->value_tag == IPP_TAG_INTEGER) {
							jobID = pAttribute->values[0].integer;
						}
						if (strcmp(pAttribute->name, "job-state") == 0 && pAttribute->value_tag == IPP_TAG_ENUM) {
							jobState = (ipp_jstate_t)pAttribute->values[0].integer;
						}
						if (strcmp(pAttribute->name, "job-originating-user-name") == 0 && pAttribute->value_tag == IPP_TAG_NAME) {
							pJobUserName = pAttribute->values[0].string.text;
						}
						pAttribute = pAttribute->next;
					}
					if (jobState == IPP_JOB_PROCESSING) {
						if (pJobUserName != NULL) {
							if (strcmp(pPasswd->pw_name, pJobUserName) == 0) {
								retVal = ID_ERR_NO_ERROR;
							}
							//v.2.00.01.010 for CUPS 1.2 test Print is "guest", but CUPS 1.1 is ""
							else if( (pJobUserName[0] == '\0') || (strcmp(pJobUserName, "guest") == 0) ){
							//else if (pJobUserName[0] == '\0') {
								retVal = ID_ERR_NO_ERROR;
							}
						}
						break;
					}

					if (pAttribute != NULL)
						pAttribute = pAttribute->next;
				}
			}
			
			ippDelete(pResponse);
		}
		else {
			retVal = ID_ERR_CUPS_API_FAILED;
		}
		
		cupsLangFree(pLanguage);
		httpClose(pHTTP);
	}
	
	if (retVal == ID_ERR_NO_ERROR && pJobID != NULL) {
		*pJobID = jobID;
	}

	return(retVal);
}// End getJobID


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE gint getPrinterURI(gchar *pDestName, gchar *pURI, gchar *pServerName, gint bufSize)
// IN     : gchar *pDestName : Printer name.
//          gint bufSize : Size of output buffer.
// OUT    : gchar *pURI : Printer URI.
//          gchar *pServerName : Server name.
// RETURN : ID_ERR_NO_ERROR : No error.
//          ID_ERR_CUPS_API_FAILED : Error occured in CUPS API.
// 
PRIVATE gint getPrinterURI(gchar *pDestName, gchar *pURI, gchar *pServerName, gint bufSize)
{
/*** Parameters start ***/
	http_t			*pHTTP;						// Pointer to HTTP connection.
	ipp_t			*pRequest,					// Pointer to CUPS IPP request.
					*pResponse;					// Pointer to CUPS IPP response.
	ipp_attribute_t	*pAttribute;				// Pointer to CUPS attributes.
	cups_lang_t		*pLanguage;					// Pointer to language.
	gchar			*pPrinter = NULL;			// Pointer to printer name.
	gchar			*pUri = NULL;				// Pointer to printer uri.
	gchar			*pTemp = NULL;				// Temporary pointer.
	gint			i;							// Counter.
	gint			retVal = ID_ERR_NO_ERROR;	// Return value.
	const char		*attributes[] = {			// Attributes name set.
						"printer-name",
						"printer-uri-supported",
					};
/*** Parameters end ***/
	
	// CUPS http connect.
	if ((pHTTP = httpConnectEncrypt(cupsServer(), ippPort(), cupsEncryption())) == NULL) {
		retVal = ID_ERR_CUPS_API_FAILED;
	}
	else {
		pRequest = ippNew();
		
		pRequest->request.op.operation_id = CUPS_GET_PRINTERS;
		pRequest->request.op.request_id   = 1;
		
		pLanguage = bjcupsLangDefault();	// cupsLangDefault() -> bjcupsLangDefault() for cups-1.1.19
		
		ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_CHARSET, "attributes-charset", NULL, cupsLangEncoding(pLanguage));
		ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_LANGUAGE, "attributes-natural-language", NULL, pLanguage->language);
		ippAddStrings(pRequest, IPP_TAG_OPERATION, IPP_TAG_KEYWORD, "requested-attributes", sizeof(attributes) / sizeof(attributes[0]), NULL, attributes);
		
		if ((pResponse = cupsDoRequest(pHTTP, pRequest, "/")) != NULL) {
			if (pResponse->request.status.status_code > IPP_OK_CONFLICT) {
				retVal = ID_ERR_CUPS_API_FAILED;
			}
			else {
				pAttribute = pResponse->attrs;

				while (pAttribute != NULL) {
					while (pAttribute != NULL && pAttribute->group_tag != IPP_TAG_PRINTER) {
						pAttribute = pAttribute->next;
					}
					if (pAttribute == NULL) {
						break;
					}
					
					while (pAttribute != NULL && pAttribute->group_tag == IPP_TAG_PRINTER) {
						if (strcmp(pAttribute->name, "printer-name") == 0 && pAttribute->value_tag == IPP_TAG_NAME) {
							pPrinter = pAttribute->values[0].string.text;
						}
						if (strcmp(pAttribute->name, "printer-uri-supported") == 0 && pAttribute->value_tag == IPP_TAG_URI) {
							pUri = pAttribute->values[0].string.text;
						}
						pAttribute = pAttribute->next;
					}
					
					// Tora 020418: Compare two printer names ignoring the character case.
					if (strcasecmp(pDestName, pPrinter) == 0) {
						strncpy(pURI, pUri, bufSize);
						
						pTemp = strstr(pURI, "//");
						pTemp += 2;
						for (i = 0; *pTemp != '/' && *pTemp != ':'; i++, pTemp++) {
							pServerName[i] = *pTemp;
						}
						
						break;
					}

					if (pAttribute != NULL)
						 pAttribute = pAttribute->next;
				}
			}
			
			ippDelete(pResponse);
		}
		else {
			retVal = ID_ERR_CUPS_API_FAILED;
		}
		
		cupsLangFree(pLanguage);
		httpClose(pHTTP);
	}
	
	if (pURI[0] == '\0') {
		snprintf(pURI, bufSize, "ipp://localhost/printers/%s", pDestName);
	}
	if (pServerName[0] == '\0') {
		strncpy(pServerName, "localhost", strlen("localhost"));
	}
	
	return(retVal);
}// End getPrinterURI


#if 1
///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PUBLIC gint getDeviceURI(gchar *pDestName, gchar *pDeviceURI)
// IN     : gchar *pDestNameI : Printer name..
//          gint bufSize : Size of output buffer.
// OUT    : gchar *pDeviceURI : Device URI.
// RETURN : ID_ERR_NO_ERROR : No error.
//          ID_ERR_CUPS_API_FAILED : Error occured in CUPS API.
// 
PUBLIC gint getDeviceURI(gchar *pDestName, gchar *pDeviceURI, gint bufSize)
{
/*** Parameters start ***/
	http_t			*pHTTP;						// Pointer to HTTP connection.
	ipp_t			*pRequest,					// Pointer to CUPS IPP request.
					*pResponse;					// Pointer to CUPS IPP response.
	ipp_attribute_t	*pAttribute;				// Pointer to CUPS attributes.
	cups_lang_t		*pLanguage;					// Pointer to language.
	gchar			*pPrinter = NULL;			// Pointer to printer name.
	gchar			*pDUri = NULL;				// Pointer to Device uri.
	gint			retVal = ID_ERR_NO_ERROR;	// Return value.
/*** Parameters end ***/
	
	// CUPS http connect.
	if ((pHTTP = httpConnectEncrypt(cupsServer(), ippPort(), cupsEncryption())) == NULL) {
		retVal = ID_ERR_CUPS_API_FAILED;
	}
	else {
		pRequest = ippNew();
		
		pRequest->request.op.operation_id = CUPS_GET_PRINTERS;
		pRequest->request.op.request_id   = 1;
		
		pLanguage = bjcupsLangDefault();	// cupsLangDefault() -> bjcupsLangDefault() for cups-1.1.19
		
		ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_CHARSET, "attributes-charset", NULL, cupsLangEncoding(pLanguage));
		ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_LANGUAGE, "attributes-natural-language", NULL, pLanguage->language);
		ippAddString(pRequest, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri", NULL, NULL);
		
		if ((pResponse = cupsDoRequest(pHTTP, pRequest, "/")) != NULL) {
			if (pResponse->request.status.status_code > IPP_OK_CONFLICT) {
				retVal = ID_ERR_CUPS_API_FAILED;
			}
			else {
				pAttribute = pResponse->attrs;

				while (pAttribute != NULL) {
					while (pAttribute != NULL && pAttribute->group_tag != IPP_TAG_PRINTER) {
						pAttribute = pAttribute->next;
					}
					if (pAttribute == NULL) {
						break;
					}
					
					while (pAttribute != NULL && pAttribute->group_tag == IPP_TAG_PRINTER) {
						if (strcmp(pAttribute->name, "printer-name") == 0 && pAttribute->value_tag == IPP_TAG_NAME) {
							pPrinter = pAttribute->values[0].string.text;
						}
						if (strcmp(pAttribute->name, "device-uri") == 0 && pAttribute->value_tag == IPP_TAG_URI) {
							pDUri = pAttribute->values[0].string.text;
						}
						pAttribute = pAttribute->next;
					}

					if (strcasecmp(pDestName, pPrinter) == 0) {
						strncpy(pDeviceURI, pDUri, bufSize);
						break;
					}
					
					if (pAttribute != NULL)
						 pAttribute = pAttribute->next;
				}
			}
			
			ippDelete(pResponse);
		}
		else {
			pDeviceURI = '\0';
			retVal = ID_ERR_CUPS_API_FAILED;
		}
		
		cupsLangFree(pLanguage);
		httpClose(pHTTP);
	}
	
	return(retVal);
}// End getDeviceURI
#endif
