/*
 *  CUPS add-on module for Canon Inkjet Printer.
 *  Copyright CANON INC. 2001-2012
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
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

#if HAVE_CONFIG_H
#include	<config.h>
#endif	// HAVE_CONFIG_H

#define _IPP_PRIVATE_STRUCTURES 1
#include <cups/cups.h>
#include <cups/language.h>
#include <cups/ppd.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <popt.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "mntipc.h"
#include "bjutil.h"

#define	BJCUPS_VERSION	"cngpijmnt Ver.3.80  Copyright CANON INC. 2012\n"
#define BJCUPS_INTVER	"cngpijmnt Internal Version : 3.80.01.003\n"

#define	BJ_SOCKET		"/tmp/ijui"

#define	UI_PATH			PROG_PATH
//#define	UI_PATH			"/usr/local/bin/"
#define	UI_SLASH		"/"
#define	UI_NAME			"maintenance"

#define	UI_OPT_VERSION	1
#define	UI_OPT_PRINTER	2
//#define	UI_OPT_OTHERS	4
#define	UI_OPT_INTVER	8
#define	UI_OPT_CHECKENTRY	16

#define	LINE_BUF_SIZE	1024
#define CNPPD_SETTINGS_SUPPORT_DEVURI_OPT	"EnableDEVURIOption"
#define CNPPD_SETTINGS_SUPPORT_FRONTEND_OPT	"EnableFrontEnd" /* Ver.3.80 */
#define CNPPD_SETTINGS_SUPPORT_CNGPIJMNT_OPT	"EnableCNGPIJMNT" /* Ver.3.80 */
#define TRUE 1
#define FALSE 0

char* g_printer_name = NULL;


extern int GetIPCData(LPIPCU pipc, char *sname);
static short getDeviceURI( const char *pDestName, char *pDeviceURI, short bufSize);

/* Ver.3.20 */
static void char_lower( char *string, short len )
{
	short	count;
	short	dis;
	char	*current_char = string;
	
	dis='a'-'A';
	
	for( count = 0; count < len ; count++ )
	{
		if( (*current_char >= 'A') && (*current_char <= 'Z') ) *current_char += dis;
		current_char++;
	}
}

/* Ver.3.20:check entry exist or not (use cupsGetDests2) */
static short check_entry_name(const char *printer_name)
{
	http_t			*pHTTP = NULL;			// Pointer to HTTP connection.
	int				num = 0;
	int				count;
	cups_dest_t		*dests = NULL;
	cups_dest_t		*current_dests;
	char			target_name[256];
	char			compare_name[256];
	short			target_name_len;
	short			result = 1;				/* not exist */
	char	devURIBuf[10224];

	getDeviceURI( printer_name, devURIBuf, sizeof(devURIBuf) );

	target_name_len = strlen( printer_name );
	if( target_name_len > 255 )
	{
		fputs("ERROR: too long name\n", stderr);
		goto onErr;
	}

	memset( target_name , 0x00 , 256 );
	strncpy( target_name , printer_name , target_name_len );
	char_lower( target_name , target_name_len );

	
	pHTTP = httpConnectEncrypt(cupsServer(), ippPort(), cupsEncryption());
	if( pHTTP == NULL){
		fputs("ERROR: IPP ERROR\n", stderr);
		goto onErr;
	}
	else
	{
		num = cupsGetDests2( pHTTP , &dests );
		current_dests = dests;
		for( count = 0; count < num ; count++ )
		{
			memset( compare_name , 0x00 , 256 );

			if( strlen(current_dests->name) == target_name_len )		/* length compare first */
			{
				strncpy( compare_name , current_dests->name , strlen( current_dests->name ) );
				char_lower( compare_name , strlen( compare_name ) );

	
				if( !strncmp( target_name , compare_name , target_name_len ) )
				{
					result = 0;		/* exist */
					goto onErr;
				}
			}
			else
			{
			}
			current_dests++;
		}
	}
	
onErr:
	if( pHTTP != NULL ) httpClose(pHTTP);
	if( dests != NULL ) cupsFreeDests(num,dests);
	
	return result;
}

int init_option( int argc, char* argv[])
{
	static struct poptOption option_table[] =
	{
		{"version", 'v',               0, NULL, UI_OPT_VERSION},
		{"internalversion", 0,  POPT_ARG_NONE,    NULL,  UI_OPT_INTVER },	/* Ver.2.70 */
		{"checkentryexist", 0,  POPT_ARG_STRING,    NULL,  UI_OPT_CHECKENTRY },	/* Ver.3.20 */
//		{NULL,      'P', POPT_ARG_STRING, NULL, UI_OPT_PRINTER},
//		{NULL,      'o', POPT_ARG_STRING, NULL, UI_OPT_OTHERS },
		{NULL,        0,               0, NULL, 0}
	};

	poptContext context
		= poptGetContext("cngpijmnt", argc, (const char**)argv, option_table, 0);
	int rc;

	while( (rc = poptGetNextOpt(context)) > 0 )
	{
		switch( rc )
		{
		case UI_OPT_VERSION:
			fputs(BJCUPS_VERSION, stderr);
			exit(1);

		case UI_OPT_CHECKENTRY:
		{
			g_printer_name = strdup(poptGetOptArg(context));
			if( check_entry_name(g_printer_name) == 1 )
			{
				fputs("ERROR: Illegal printer name.\n", stderr);
				exit(1);
			}
			else{
				fputs("Exist\n", stderr);
				exit(0);
			}
		}
//		case UI_OPT_PRINTER:
//			g_printer_name = strdup(poptGetOptArg(context));
//			break;

//		case UI_OPT_OTHERS:
//		{
//			const char *option = poptGetOptArg(context);
//			param_list_add(pp_list, "-o", option, strlen(option) + 1);
//			break;
//		}
		case UI_OPT_INTVER:
		{
			fputs(BJCUPS_INTVER, stderr);
			exit(1);
		}
		default:
			break;
		}
	}

	if( rc < -1 )
	{
		fprintf(stderr, "Unknown switch, %s\n",
			poptBadOption(context, POPT_BADOPTION_NOALIAS));

		return rc;
	}
	return 0;
}

static
char *parse_product_name(char *ppd_product, char *product, int len)
{
	char *p_product = product;
	char *p_cc;
	int count = 0;

	memset(product, 0, len);
	p_cc = ppd_product;

	while( *p_cc == '(' )
		p_cc++;

	while( *p_cc != ')' && *p_cc != '\0' && count < len - 1 )
	{
		*p_product++ = *p_cc++;
		count++;
	}
	*p_product = '\0';

	return product;
}

char *get_product_name(const char *printer_name, char *product_name, int len)
{
	const char *ppd_name = cupsGetPPD(printer_name);
	char *p_product = NULL;
	static char product[256];

	if( len < 1 )
		return NULL;

	if( ppd_name != NULL )
	{
		ppd_file_t *p_ppd;

		if( (p_ppd = ppdOpenFile(ppd_name)) != NULL )
		{
			if( !strcmp(p_ppd->manufacturer, "Canon") )
			{
				p_product = parse_product_name(p_ppd->product, product, 256);
				strncpy(product_name, product, len - 1);
			}
			ppdClose(p_ppd);
		}
		unlink( ppd_name );	/* Ver.3.00 : You should remove the copy of the PPD file. */
		
	}
	return p_product;
}

void exec_lpr(char **lpr_param)
{
	int pid = fork();

	if( pid == -1 )
		return;

	if( pid == 0 )
	{
		execv("/usr/bin/lpr", lpr_param);
		fputs("ERROR: Can't execute lpr command.\n", stderr);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}



static cups_lang_t * bjcupsLangDefault( )
{
	cups_lang_t	*pLanguage;
	char		*tLang;	
	
	if( (tLang = getenv("LC_ALL"))==NULL)
			tLang = getenv("LANG");
	
	pLanguage = cupsLangDefault();
	setlocale(LC_ALL,tLang);
	
	return pLanguage;
}



static short getDeviceURI( const char *pDestName, char *pDeviceURI, short bufSize)
{
/*** Parameters start ***/
	http_t			*pHTTP;						// Pointer to HTTP connection.
	ipp_t			*pRequest,					// Pointer to CUPS IPP request.
					*pResponse;					// Pointer to CUPS IPP response.
	ipp_attribute_t	*pAttribute;				// Pointer to CUPS attributes.
	cups_lang_t		*pLanguage;					// Pointer to language.
	char			*pPrinter = NULL;			// Pointer to printer name.
	char			*pDUri = NULL;				// Pointer to Device uri.
	short			retVal = -1;	// Return value.
/*** Parameters end ***/
	
	// CUPS http connect.
	if ((pHTTP = httpConnectEncrypt(cupsServer(), ippPort(), cupsEncryption())) == NULL) {
		fputs("ERROR: IPP ERROR\n", stderr);
		goto onErr;
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
				fputs("ERROR: IPP ERROR\n", stderr);
				goto onErr;
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
			goto onErr;
		}
		
		cupsLangFree(pLanguage);
		httpClose(pHTTP);
	}
	
onErr:
	return(retVal);
}// End getDeviceURI


static int read_line(FILE *fp, char *buf, int buf_size)
{
	int cc = EOF;
	int i = 0;

	if( buf != NULL && buf_size > 0 )
	{
		while( (cc = fgetc(fp)) != EOF )
		{
			if( cc == 0x0d || cc == 0x0a )
				break;
			if( i < buf_size - 1 )
				buf[i++] = cc;
		}
		buf[i] = 0;
	}

	return (cc == EOF)? -1 : i;
}


static int ParseCNPpdOption( int *value, char *key )
{
	const char *p_ppd_name = cupsGetPPD( g_printer_name );
	char *keyStr;
	FILE *fp = NULL;
	char line_buf[LINE_BUF_SIZE];
	int result = -1;

	if ( (value == NULL) || (key == NULL) ) goto onErr1;
	*value = 0;	

	if ( (fp = fopen( p_ppd_name, "r" )) == NULL ) goto onErr1;

	while( read_line( fp, line_buf, LINE_BUF_SIZE ) >= 0 ){
		if( line_buf[0] == '*' && line_buf[1] == '%' ){
			keyStr = strtok(line_buf, " ");
			if ( (keyStr != NULL) && (!strcmp(keyStr, "*%CNPpdOptions")) ){
				keyStr = strtok(NULL, " ");
				while ( keyStr != NULL ){
					if ( !strcmp(keyStr, key) ){
						*value = 1;
						break;
					}								
					keyStr = strtok(NULL, " ");
				}
			}
		}
	}

	result = 0;
	if ( fp != NULL ) fclose( fp );
onErr1:
	return result;
}

static int isSupportMSI( void )
{
	int value;
	int result = FALSE;

	if ( ParseCNPpdOption( &value, CNPPD_SETTINGS_SUPPORT_DEVURI_OPT ) < 0 ) goto onErr;

	if ( value == 1 ) {
		result = TRUE;
	}
	else {
		result = FALSE;
	}

onErr:
	return result;
}

/* Ver.3.80 */
static int isSupportFrontEnd( void )
{
	int value;
	int result = FALSE;

	if ( ParseCNPpdOption( &value, CNPPD_SETTINGS_SUPPORT_FRONTEND_OPT ) < 0 ) goto onErr;

	if ( value == 1 ) {
		result = TRUE;
	}
	else {
		result = FALSE;
	}

onErr:
	return result;
}

/* Ver.3.80 */
static int isSupportCNGPIJMNT( void )
{
	int value;
	int result = FALSE;

	if ( ParseCNPpdOption( &value, CNPPD_SETTINGS_SUPPORT_CNGPIJMNT_OPT ) < 0 ) goto onErr;

	if ( value == 1 ) {
		result = TRUE;
	}
	else {
		result = FALSE;
	}

onErr:
	return result;
}




int main(int argc, char* argv[])
{
//	ParamList *p_list = NULL;
	int ui_pid;
//	char *print_file = NULL;
	char product_name[64];
//	char ui_path[256];
	char *ui_path = NULL;
	char ui_name[256];
	char socket_name[64];
	char *ui_arg[8];

	/* Ver.3.20 */
	short		ret=-1;
	char		device_uri_buf[1024];
	short		device_uri_buf_len = 1024;
	char		*canon_usb_backend_str = "cnijusb:";
	char		*canon_net_backend_str = "cnijnet:";
	short		canon_backend_flag = 0;
	short		add_bidi = 0;
	short		add_direct = 0;
	const char 		*p_ppd_name;
	ppd_file_t	*p_ppd;

	/* Ver.3.70 */
	int arg_num;	

	if( argc > 2 )
	{
		fputs(BJCUPS_VERSION, stderr);
		fputs("Usage: cngpijmnt [printer name]\n", stderr);
		exit(1);
	}

	if ( argc == 2 ) {
		g_printer_name = strdup(argv[argc - 1]);
	}

//	if( init_option(&p_list, argc, argv) < 0 )
	if( init_option( argc, argv) < 0 )
		exit(1);

	if( g_printer_name == NULL )
	{
		const char *printer_name;

		if( (printer_name = cupsGetDefault()) != NULL )
			g_printer_name = strdup(printer_name);
		else
		{
			fputs("ERROR: Can't get default printer name.\n", stderr);
			exit(1);
		}
	}

	if( get_product_name(g_printer_name, product_name, 64) == NULL )
	{
		fputs("ERROR: Illegal printer name.\n", stderr);
		exit(1);
	}

	/* Ver.3.80 */
	if( (isSupportFrontEnd() == FALSE) || (isSupportCNGPIJMNT() == FALSE) )
	{
		fputs("ERROR: The specified printer is not supported.\n", stderr);
		exit(1);
	}

	/* Ver.3.20: Set canon_backend_flag. */
	{
		memset( device_uri_buf , 0x00 , device_uri_buf_len );
		ret = getDeviceURI( g_printer_name , device_uri_buf , device_uri_buf_len );
		if( ret < -1 )
		{
			fputs("ERROR: Can't get device URI.\n", stderr);
			exit(1);
		}
		
		if( !strncmp( device_uri_buf , canon_usb_backend_str , strlen( canon_usb_backend_str ) ) ) canon_backend_flag = 1;
		else if( !strncmp( device_uri_buf , canon_net_backend_str , strlen( canon_net_backend_str ) ) ) canon_backend_flag = 1;
		
		
		/* PPD open and check cupsModelNumber */
		p_ppd_name = cupsGetPPD( g_printer_name );
		if( p_ppd_name ==NULL ){
			fputs("ERROR: Can't get PPD name.\n", stderr);
			exit(1);
		}
		p_ppd = ppdOpenFile(p_ppd_name);
		if( p_ppd ==NULL ){
			fputs("ERROR: Can't open PPD file.\n", stderr);
			unlink( p_ppd_name );	/* You should remove the copy of the PPD file. */
			exit(1);
		}
		
		add_bidi = canon_backend_flag;
		if( p_ppd->model_number < 356 ) add_bidi = 0;
		
		ppdClose(p_ppd);
		unlink( p_ppd_name );	/* You should remove the copy of the PPD file. */
		
	}

	
	ui_path = (char *)malloc(strlen(UI_PATH) + strlen(UI_SLASH) + strlen(UI_NAME) + strlen(product_name) + 1);
	strcpy(ui_path, UI_PATH);
	strcat(ui_path, UI_SLASH);
	strcat(ui_path, UI_NAME);
	strcat(ui_path, product_name);

	strcpy(ui_name, UI_NAME);
	strcat(ui_name, product_name);

	snprintf(socket_name, 63, "%s%d", BJ_SOCKET, getpid());


	for ( arg_num=0; arg_num<sizeof(ui_arg)/sizeof(char*); arg_num++ ) {
		ui_arg[arg_num] = NULL;
	}

	arg_num = 0;
	ui_arg[arg_num] = ui_name; arg_num++;
	ui_arg[arg_num] = "-s"; arg_num++;
	ui_arg[arg_num] = socket_name; arg_num++;
	//ui_arg[arg_num] = "--cups"; arg_num++;

	/* Ver.3.20 */
	if( add_bidi ) {
		ui_arg[arg_num] = "--bidi"; arg_num++;
	}

	/* Ver.3.70 */
	if ( canon_backend_flag ) {
		if ( isSupportMSI() == 1 ) {
			ui_arg[arg_num] = "--devuri"; arg_num++;
			ui_arg[arg_num] = device_uri_buf; arg_num++;
		}
	}



#if 0
	/* for debug */
	{
		short i=0;
		while( ui_arg[i]!=NULL )
		{
			fprintf(stderr,"ui_arg[%d]=%s\n",i,ui_arg[i]);
			i++;
		}
	}
#endif

	ui_pid = fork();

	if( ui_pid == 0 )
	{
		execv(ui_path, ui_arg);
	}
	else
	{		
		while(1){
			IPCU ipc;
			int ret;
			memset(&ipc, 0, sizeof(IPCU));
			
			ret = GetIPCData(&ipc, socket_name);

#if 0			
			if( ret == RET_PRINT )
			{
				char **lpr_param
				= make_lpr_param(&p_list, g_printer_name, &ipc, print_file);
				if( lpr_param )
				{
					exec_lpr(lpr_param);
					free(lpr_param);
				}
				break;
			}
#endif
			if( ret == RET_PDATA ){	// For Maintenance
				char **lpr_param;
				/* Ver.3.20 */
				/* If canon backend is NOT used, add "CNBjDirect" */
				if( canon_backend_flag ) add_direct = 0;
				else add_direct = 1;

				lpr_param = make_pdata_lpr_param( g_printer_name, &ipc, add_direct );
					
				if( lpr_param )
				{
					exec_lpr(lpr_param);
					free_util_cmd_param( lpr_param );
				}

			}
			else if( ret == RET_FDATA ){	// For Maintenance i250/i255
				char **lpr_param
						= make_fdata_lpr_param( g_printer_name, &ipc );	

				if( lpr_param )
				{
					exec_lpr(lpr_param);
					free_util_cmd_param(lpr_param); 
					lpr_param = NULL;
				}
			}
			else if( ret == RET_WDATA ){	// For Maintenance i250/i255
				char **lpr_param
				= make_wdata_lpr_param( g_printer_name, &ipc);
				if( lpr_param )
				{
					exec_lpr(lpr_param);
					free_util_cmd_param(lpr_param); 
					lpr_param = NULL;
				}
			}
			/* Ver.3.20 for PowerOFF */
			else if( ret == RET_POWEROFF ){
				char **lpr_param
						= make_pdata_lpr_param( g_printer_name, &ipc, 1);	/* PowerOFF -> always add "--CNBjDirect" */
					
				if( lpr_param )
				{
					exec_lpr(lpr_param);
					free_util_cmd_param( lpr_param );
				}
			}
			else if( ret == RET_CANCEL ){
				break;	
	
			}
			else if ( ret == RET_ERROR ){
				break;
			}
		}

#if 0	
		if( p_list != NULL )
			param_list_free(p_list);
#endif

		waitpid(ui_pid, NULL, 0);
	}

	if ( g_printer_name != NULL ) {
		free(g_printer_name);
	}
	return 0;
}
