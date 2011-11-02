/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2011
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

#include "bjcupsmon_common.h"
#include "bjcupsmon_funcprot.h"
#include "bjcupsmon_transsts.h"

#include <time.h>
#include <sys/timeb.h>
#include <sys/wait.h>
#include <pwd.h>
#include <unistd.h>


#define	CNIJNPR_CMD_BASE_STR				PROG_PATH "/cnijnpr"

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
	//Ver.3.10 for Network
	{ID_ERR__NO_RESPONSE,			ID_ERR_LEVEL_CONTINUE,	ID_OTHER_MESSAGE_NO_RESPONSE},
	{ID_ERR__COLLECTING_STATUS,		ID_ERR_LEVEL_CONTINUE,	ID_OTHER_MESSAGE_COLLECTING_STATUS},
};


/*** Static function prototypes ***/
PRIVATE gint initApplication(gint, gchar**, gchar*);
//for Network Ver.3.10
PRIVATE gboolean updateUI(gchar*);
//PRIVATE gboolean updateUI(void);
PRIVATE void initPrinterStatus(ST_PrinterStatus*);
PRIVATE void SetGtkResourceDefault();
PRIVATE void copy_buf2statusStr( char *, ST_CUPSSTS *);


//for Network Ver.3.10
//atic void cnijnpr_sigterm_handler( int ) ;
static void cnijnpr_sigchild_handler( int ) ;

int     g_pid = -1;							/* fork process id buffer      */
//dont't nessesarry 20071115
//2.30.01.008 delete Ubuntu 8.10 SIGCHLD receive first
//int     g_signal = 0;  						/* 0: not received, 1: received.*/


//static
//void cnijnpr_sigterm_handler(int sig_code)
//{
//	if( g_pid > 0 ){
//		printf("call cnijnpr_sigterm_handler = %d\n", g_pid);
//		kill(g_pid, SIGTERM);
//	}
//	g_signal = 1;
//}

static
void cnijnpr_sigchild_handler(int sig_code)
{
	//printf("killed child process(call cnijnpr_sigchild_handler) sigcode = %d,%d\n", g_pid,sig_code);
	//2.30.01.008 delete Ubuntu 8.10 SIGCHLD receive first
	//g_signal = 1;
}


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
	static gchar	small_modelname[MAX_BUF_SIZE];// smallmodel name.
	//gchar	small_modelname[MAX_BUF_SIZE];// smallmodel name.
	gchar			manufacture[MAX_BUF_SIZE];	// manufacture name.
	gchar			tmp_modelname[MAX_BUF_SIZE];// tmp name.
	gchar			module_name[MAX_BUF_SIZE];	// module name.
//	gint			cnt = 0;					// Counter.
	gint			mismatch_flag = 0;			// Mismatch Flag.
	//Ver.3.10 for Network
	int		pipe_fds[2];
	gchar	deviceURI[MAX_BUF_SIZE];				/* DeviceURI name. */
	gchar	backend_name_net[] = 	"cnijnet:/";	/* Net Backend Name */
	gchar	backend_name_usb[] =	"cnijusb:/";	/* USB Backend Name */
	gchar	macaddress[128];						/* macaddress */
	gint	backend_Is = -1;
	gchar	modelIDstr[5];
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
	memset(deviceURI, 0, sizeof(deviceURI));
	memset(macaddress, 0x00, sizeof(macaddress)) ;
	memset(modelIDstr, 0, sizeof(modelIDstr));

//	strcpy(windowTitle, STR_MANUFACTURER_NAME);		delete V2.3
//	strcat(windowTitle, " ");						delete V2.3

//	signal( SIGTERM, cnijnpr_sigterm_handler );
	signal( SIGCHLD, cnijnpr_sigchild_handler );
	
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

	/* Ver.3.20 for small_modelname */
	retVal = getProductName(gDestName, productName, modelIDstr);
	//retVal = getProductName(gDestName, productName);
	if (retVal == ID_ERR_NO_ERROR) {

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
	}
	/* Ver.3.20 for small_modelname */

	/* for Network Ver.3.10 */
	retVal = getDeviceURI( gDestName, deviceURI, sizeof(deviceURI) );
	if (retVal != ID_ERR_NO_ERROR){
		exit(0) ;
	}
	/* get Mac Address */
	/* When cnij_net is Backend */
	if (strncmp(deviceURI, backend_name_net, strlen(backend_name_net)) != 0){
		/* When cnij_usb is Backend */
		//20090202 backend: IPP:ipp://198.168.1.23... cnijusb
		backend_Is = CANON_USB_BACKEND_CNIJ_USB;
		pPrinterName = NULL;
		//20090202 backend: IPP:ipp://198.168.1.23... cnijusb
		if (strncmp(deviceURI, backend_name_usb, strlen(backend_name_usb)) == 0){
			strncpy(macaddress, deviceURI + strlen(backend_name_usb), (strlen(deviceURI)-strlen(backend_name_usb)) );
			backend_Is = CANON_USB_BACKEND_CNIJ_USB;
			pPrinterName = NULL;
		}
	} else {
		strncpy(macaddress, deviceURI + strlen(backend_name_net), (strlen(deviceURI)-strlen(backend_name_net)) );
		backend_Is = CANON_BJNP_BACKEND_CNIJ_NET;
	}
	/* for Network Ver.3.00 */

	/* pipe create */
	if( backend_Is == CANON_BJNP_BACKEND_CNIJ_NET ){
		/* pipe create */
		if( pipe(pipe_fds) < 0 )	return( -1 );
	
		g_pid = fork();
	}
	else{
		g_pid = -2;
		//g_pid = 1;
	}
	
	if( g_pid  ==  -1 ){
		return( -1 ) ;
	}
	
	/* child process */
	else if( g_pid == 0 ){

		static	char	str_msg[128];				/* message buffer */
		char	argv_pipe[128];						/* new pipe */
		char	argv_uri[128];						/* argv URI */
		char	hostname[256];						/* hostname */
		char	username[256];						/* username(loginnamae) */
		int		rtn = 0;
		struct passwd	usrpasswd;
		struct passwd	*lpusrpasswd = NULL;
		static	int		cmd_argv_cnt = 0 ;			/* argument counter			*/
		static	char	*cmd_argv[16] ;				/* command argument beffer	*/

		lpusrpasswd = &usrpasswd;

		memset( str_msg, 0x00, sizeof(str_msg) ) ;
		memset( argv_pipe, 0x00, sizeof(argv_pipe) ) ;
		memset( argv_uri, 0x00, sizeof(argv_uri) ) ;
		memset( username, 0x00, sizeof(username) ) ;
		//printf("Child --%d\n", getpid());	

		sprintf( argv_pipe, "%d", pipe_fds[1] );

		//close( 0 );
		//dup2( pipe_fds[0], 0 );
		close( pipe_fds[0] );

		sprintf( argv_uri, "%s", macaddress );

		if (gethostname(hostname, sizeof(hostname)-1) != 0) exit(0);
		//if( getlogin() == NULL ) exit(0);
		lpusrpasswd = getpwuid(getuid());
		if( lpusrpasswd == NULL ) exit(0);
		if( lpusrpasswd->pw_name == NULL ) exit(0);
		strncpy(username, lpusrpasswd->pw_name, sizeof(username)-1);
		//strncpy(username,  getlogin(), sizeof(username)-1);

		cmd_argv[cmd_argv_cnt++] = "cnijnpr";
		cmd_argv[cmd_argv_cnt++] = argv_pipe;
		cmd_argv[cmd_argv_cnt++] = argv_uri;
		cmd_argv[cmd_argv_cnt++] = hostname;
		cmd_argv[cmd_argv_cnt++] = username;
		/* Ver.3.20 for bscc2sts */
		cmd_argv[cmd_argv_cnt++] = small_modelname;
		cmd_argv[cmd_argv_cnt++] = modelIDstr;
		cmd_argv[cmd_argv_cnt++] = NULL;

   		rtn = execvp ( CNIJNPR_CMD_BASE_STR, cmd_argv );
		//rtn = execlp("cnijnpr", "cnijnpr", argv_pipe, argv_uri, hostname, username, NULL);

		if( rtn < 0 ){
			exit(0) ;
		}
		close( pipe_fds[1] );

	} /* parents process */
	else {
		//for bscc
		output_dev __attribute__ ((unused)) Odev;
	    char			buf[4096];

		memset( buf, 0x00, sizeof(buf) ) ;

		Odev.status = 0;
		Odev.dev = 0;//device_type;	

		if( backend_Is == CANON_BJNP_BACKEND_CNIJ_NET ){
			//printf("parents process : --%d\n", getpid());
			close( 0 );
			dup2( pipe_fds[0], 0 );
			close( pipe_fds[0] );
			close( pipe_fds[1] );
		}

		// Initialize printer status area.
		initPrinterStatus(&gPrinterStatus);
		/* for Network Ver.3.10 */
		
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
			retVal = getProductName(gDestName, productName, modelIDstr);
			//retVal = getProductName(gDestName, productName);
			if (retVal == ID_ERR_NO_ERROR) {
	
/* Ver.3.20 move up */
//				// check cngpijmonip4300 and ppd productName
//				strncat(manufacture, STR_MANUFACTURER_NAME, strlen(STR_MANUFACTURER_NAME) );
//				for( i=0,j=0; i<(sizeof(productName) - 1) ; i++){
//					if(manufacture[i] != productName[i]){
//						tmp_modelname[j] = tolower(productName[i+1]);
//						j++;
//					}
//					tmp_modelname[j] = '\0';
//				}
//		
//				for( i=0,j=0; i<(sizeof(tmp_modelname) - 1) ; i++){
//					if(tmp_modelname[i] == ' ') 
//						break;
//					else{
//						small_modelname[j] = tmp_modelname[i];
//						j++;
//					}
//					small_modelname[j] = '\0';
//				}
		
				snprintf(module_name, sizeof(module_name), "%s%s",STR_APPLICATION_NAME, small_modelname);
		
				for( i=0; i<strlen(module_name) ; i++){
					if( module_name[i] != *(argv[0]+i) ){
						memset(productName, 0, sizeof(productName));
						snprintf(productName, sizeof(productName), "%s%s", STR_MANUFACTURER_NAME, "");
						mismatch_flag = 1;
					}
				}
				// check cngpijmonip4300 and ppd productName
	
				/* for Network Ver.3.10 */
				if( (backend_Is == CANON_BJNP_BACKEND_CNIJ_NET) && (mismatch_flag != 1) ){
					strncpy(windowTitle, productName, sizeof(windowTitle)-strlen(macaddress)-1 );
					strncat(windowTitle, " ", strlen(" "));
					strncat(windowTitle, macaddress, strlen(macaddress));
				}
				else if( (backend_Is == CANON_USB_BACKEND_CNIJ_USB) && (mismatch_flag != 1) ){
					strncpy(windowTitle, productName, sizeof(windowTitle)-strlen(STR_USB_NAME)-1 );
					strncat(windowTitle, " ", strlen(" "));
					strncat(windowTitle, STR_USB_NAME, strlen(STR_USB_NAME));
				}
				/* Canon iPxxx series Status Monitor */
				/* when mismatch_flag == 1 */
				else {
					strncpy(windowTitle, productName, sizeof(windowTitle)-strlen(STR_PRODUCT_NAME)-1 );		// V2.3 strcat->strcpy
					strncat(windowTitle, " ", strlen(" "));
					strncat(windowTitle, STR_PRODUCT_NAME, strlen(STR_PRODUCT_NAME));
				}
	
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
						if ( (jobExist == FALSE) && (backend_Is == CANON_USB_BACKEND_CNIJ_USB) ) {
							// Print job not exist.
							retVal = ID_ERR_PRINT_JOB_NOT_EXIST;
						}
						else {
							// Print job exist. Get printer status string.
							getPrinterStatus(gDestName, statusStr, sizeof(statusStr));
							retVal = getPrinterStatus(gDestName, statusStr, sizeof(statusStr));
							retVal = ID_ERR_PRINT_JOB_NOT_EXIST;
	
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
									//for Network Ver.3.10
									gTimeoutFuncTag = gtk_timeout_add(TIMEOUT_CALL_UPDATE_UI_FUNC, (GtkFunction)updateUI, small_modelname);
									//gTimeoutFuncTag = gtk_timeout_add(TIMEOUT_CALL_UPDATE_UI_FUNC, (GtkFunction)updateUI, NULL);
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
					//for Network Ver.3.10
					if(backend_Is == CANON_USB_BACKEND_CNIJ_USB) 
						memset(small_modelname, 0, sizeof(small_modelname));
					gTimeoutFuncTag = gtk_timeout_add(TIMEOUT_CALL_UPDATE_UI_FUNC, (GtkFunction)updateUI, small_modelname);
					//gTimeoutFuncTag = gtk_timeout_add(TIMEOUT_CALL_UPDATE_UI_FUNC, (GtkFunction)updateUI, NULL);
				}
				retVal = ID_ERR_NO_ERROR;
			}
		}

	}/* parents process end */

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
	//printf("g_pid = %d\n", g_pid);
	if( g_pid > 0 ){
		//printf("g_signal = %d\n",g_signal);
		//2.30.01.008 delete Ubuntu 8.10 SIGCHLD receive first
		//if( g_signal == 0 ){
			kill(g_pid, SIGTERM);
			//printf("send child SIGTERM = %d\n",kill(g_pid, SIGTERM));
		//}
		waitpid( g_pid, NULL, 0 );
		//printf("***waitpid child SIGTERM\n");
	}
	//dont't nessesarry 20071115
	//g_signal = 1;

		gtk_main_quit();
	
	return;
}// End closeApplication


///////////////////////////////////////////////////////////////////////////////////////////
// 
// CS     : PRIVATE gboolean updateUI(pPrinterName)
// IN     : None.
// OUT    : None.
// RETURN : Always TRUE.
// 
//for Network Ver.3.00
PRIVATE gboolean updateUI(gchar *small_name)
//PRIVATE gboolean updateUI(void)
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
	//ENUM_STSMessageID	*pMessageID;				// Pointer to array of message ID.
	gint				retVal = ID_ERR_NO_ERROR;	// Return value.
	struct timeb		curTime;
	static struct timeb	prevTime;
	static gboolean		initTime = FALSE;
	//Ver.3.10 for Network
	output_dev __attribute__ ((unused)) Odev;
    char			buf[4096];
/*** Parameters end ***/
	int __attribute__ ((unused)) result2;
	//Ver.3.10 for Network
	memset( buf, 0x00, sizeof(buf) ) ;
	//20090202 inistialize
	memset( statusStr, 0x00, sizeof(statusStr) ) ;
	Odev.status = 0;
	Odev.dev = 0;//device_type;	

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

		//Ver.3.10 for Network
		//Child Process killed!
		//printf("jobExist %d\n",jobExist);
		if ( (jobExist == FALSE) && (*small_name == '\0') ) {
			retVal = ID_ERR_PRINT_JOB_NOT_EXIST;
		}
		else {
			// Get printer status string.
			getPrinterStatus(gDestName, statusStr, sizeof(statusStr));
			retVal = getPrinterStatus(gDestName, statusStr, sizeof(statusStr));

			// Ver.3.10 for Network
			if( *small_name != '\0' ){
				//read from stdin
				//check stdin
				{
					fd_set rfds;
					struct timeval tv;
					int retval;

					/* 1s watch */
					tv.tv_sec = 1;
					tv.tv_usec = 0;
					/* set fd=stdin (fd 0) */
					FD_ZERO(&rfds);
					FD_SET(0, &rfds);

					/* stdin (fd 0) OK? */
					retval = select(1, &rfds, NULL, NULL, &tv);
					if (retval > 0)
						result2 = read( 0, buf, sizeof(buf));
				}
				//read( 0, buf, sizeof(buf));

				if( buf[0] == '@' ){
					retVal = ID_ERR__NO_RESPONSE;
				}
				else if( buf[0] == '*' ){
					retVal = ID_ERR__COLLECTING_STATUS;
				}
				copy_buf2statusStr(&buf[1], (St_cupssts)&statusStr);
				//bscc2sts(small_name, &buf[1], &Odev, (Bscc2sts_tbl)&statusStr);
			}

			if (retVal == ID_ERR_NO_ERROR) {
				// Check status string.
				if (strncmp(statusStr, STR_HEADER_STATUS_STRING, strlen(STR_HEADER_STATUS_STRING)) == 0) {
					// Initialize printer status area.
					initPrinterStatus(&printerStatus);
					
					/* for Network Ver.3.10 */
					if( buf[0] == '#' )
						printerStatus.user_otherflag = NETWORK_OTHER_USE;

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

///////////////////////////////////////////////////////////////////////////////////////////
// 
// PRIVATE void copy_buf2statusStr()
// RETURN : OK or -1 
//
PRIVATE void copy_buf2statusStr( char *bscc, ST_CUPSSTS *Pr_sts)
{
  int i=0;
  char *psts = NULL;

	/* don't parse bscc->sts, only copy */
	if( (bscc[0] == 'S') && (bscc[1] == 'T') && (bscc[2] == 'S') ){
		psts = (char *)Pr_sts;
		while(1){
			psts[i] = bscc[i];
			if( bscc[i] == '\n' ) break;
			i++;
		}
	}
}
