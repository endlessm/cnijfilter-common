/*
 *  Canon Bubble Jet Print Filter for Linux
 *  Copyright CANON INC. 2001 
 *  All Right Reserved.
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

#include <stdio.h>
#include <stdlib.h>
#include <popt.h>
#include <string.h>
#include <ctype.h>

#include "cncl.h"
#include "cncldef.h"
#include "cnclucom.h"
#include "cncludef.h"
#include "bjfoption.h"
#include "bjfrcaccess.h"
#include "uitypes.h"

#define  DEFINE_GLOBALS
#include "psize.h"
#include "bjfversion.h"

const char bjlibdir[] = BJLIBPATH;

const char usage_str0[]		= "Usage: bjfilter --gui --model modelname   (gui mode)\n";
const char usage_str1[]		= "       bjfilter --model modelname [switches] [file]\n\n";

const char usage_str2[]		= "       switches: [ --cartridge   cartridge  ]\n";
const char usage_str3[]		= "                 [ --location    location   ]\n";
const char usage_str4[]		= "                 [ --media       mediatype  ]\n";
const char usage_str5[]		= "                 [ --halftoning  halftoning ]\n";
const char usage_str6[]		= "                 [ --paperload   cartridge  ]\n";
const char usage_str7[]		= "                 [ --quality     1 - 5      ]\n";
const char usage_str8[]		= "                 [ --grayscale              ]\n";
const char usage_str9[]		= "                 [ --banner                 ]\n";

/*-------------------------------------------------------------*/
/* Display usage                                               */
/*-------------------------------------------------------------*/
void usage( void )
{
	fprintf(stderr, "\n%s\n%s\n%s\n\n%s%s%s%s%s%s%s%s",
					VERSION_STR,
					COPYRIGHT_STR0,
					COPYRIGHT_STR1,
					usage_str0,
					usage_str1,
					usage_str2,
					usage_str3,
					usage_str4,
					usage_str5,
					usage_str6,
					usage_str7
//					usage_str8,
//					usage_str9
	);
}



static void internalversion( void )
{
	fprintf( stderr, "Internal Version : %s\n", INTERNAL_VERSION_STR );
}

static short GetPaperSize( short, long *, long * );


/*-------------------------------------------------------------*/
/* Get Papersize from Papersize ID static                      */
/*-------------------------------------------------------------*/
static short GetPaperSize( short id, long *width, long *height )
{
	short paper = 0;
	short result = -1;

	while( (id != PaperTbl[paper][PSID]) && (id != -1) ) paper++;

	if ( id == -1 ) goto onErr;

	*width = PaperTbl[paper][YOKO];
	*height = PaperTbl[paper][TATE];

	result = 0;
onErr:
	return result;	
}


/*-------------------------------------------------------------*/
/* Look up ID with specified value                             */
/*-------------------------------------------------------------*/
short QueryValue(LPCNCLDB lpdbTop, short dbsize, short id, short value)
{
	LPCNCLDB	lpdb = lpdbTop;
	short		ret = -1;
	short		i;

	/* lookup ID with specified value */
	lpdb = lpdbTop;
	for (i=0; i<dbsize; i++, lpdb++) {
		if (lpdb->nObjectID == id) {
			if ((lpdb->nValue == value) && (lpdb->disable == 0)) {
				ret = i;
				break;
			}

			if ((lpdb+1)->nObjectID != lpdb->nObjectID)
				break;
		}
	}
	return ret;
}



/*-------------------------------------------------------------*/
/* retrieve the nValue of the member in ObjectID,              */
/*           begin curset flag is set                          */
/*-------------------------------------------------------------*/
short GetCurrentnValue(LPCNCLDB lpdbTop, short dbsize, short ObjectID)
{
	LPCNCLDB	lpdb = lpdbTop;
	short		ret = -1;
	short		i;

	for (i=0; i<dbsize; i++, lpdb++) {
		if ((lpdb->nObjectID == ObjectID) && (lpdb->curset == 1)) {
				ret = lpdb->nValue;
				break;
		}
	}
	return ret;
}


/*-------------------------------------------------------------*/
/* retrieve the nValue of the member in ObjectID,              */
/*                        begin default flag is set            */
/*-------------------------------------------------------------*/
short GetDefaultnValue(LPCNCLDB lpdbTop, short dbsize, short ObjectID)
{
	LPCNCLDB	lpdb = lpdbTop;
	short		ret = -1;
	short		i;

	for (i=0; i<dbsize; i++, lpdb++) {
		if ((lpdb->nObjectID == ObjectID) && (lpdb->defset == 1)) {
				ret = lpdb->nValue;
				break;
		}
	}
	return ret;
}


/*-------------------------------------------------------------*/
/* check if temporary flag is set or not                       */
/*-------------------------------------------------------------*/
short GetTemporarynValue(LPCNCLDB lpdbTop, short dbsize, short ObjectID)
{
	LPCNCLDB	lpdb = lpdbTop;
	short		ret = -1;
	short		i;

	for (i=0; i<dbsize; i++, lpdb++) {
		if (lpdb->nObjectID == ObjectID) {
			if (lpdb->tmpset == 1) {
				ret = lpdb->nValue;
				break;
			}
			else if ((lpdb+1)->nObjectID != ObjectID)
				break;
		}
	}
	return ret;
}


/*-------------------------------------------------------------*/
/* set current flag to specified member of internal database   */
/*-------------------------------------------------------------*/
short SetCurrentFlag(LPCNCLDB lpdbTop, short dbsize, short id, short value)
{
	LPCNCLDB	lpdb = lpdbTop;
	short		ret = -1;
	short		i;

	/* reset current flag */
	for (i=0; i<dbsize; i++, lpdb++) {
		if (lpdb->nObjectID == id) {
			if (lpdb->curset == 1)
				lpdb->curset = 0;
			if ((lpdb+1)->nObjectID != lpdb->nObjectID)
				break;
		}
	}

	/* set current flag */
	lpdb = lpdbTop;
	for (i=0; i<dbsize; i++, lpdb++) {
		if (lpdb->nObjectID == id) {
			if (lpdb->nValue == value) {
				lpdb->curset = 1;
				ret = i;
				/* printf("nObjectID %d, nValue %d\n", id, value); */
				break;
			}
			if ((lpdb+1)->nObjectID != lpdb->nObjectID) {
				lpdb->nValue = value;
				lpdb->curset = 1;
				break;
			}
		}
	}
	return ret;
}



/*-------------------------------------------------------------*/
/* set delete flag to specified member of internal database    */
/*-------------------------------------------------------------*/
short SetDisableFlag(LPCNCLDB lpdbTop, short dbsize, short id, short value, short flag)
{
	LPCNCLDB	lpdb = lpdbTop;
	short		ret = -1;
	short		i;

	/* set disable flag */
	lpdb = lpdbTop;
	for (i=0; i<dbsize; i++, lpdb++) {
		if (lpdb->nObjectID == id) {
			if (lpdb->nValue == value) {
				lpdb->disable = flag;
				ret = i;
				break;
			}

			if ((lpdb+1)->nObjectID != lpdb->nObjectID)
				break;
		}
	}
	return ret;
}



/*-------------------------------------------------------------*/
/* set temporary flag to specified member of internal database */
/*-------------------------------------------------------------*/
short SetTemporaryFlag(LPCNCLDB lpdbTop, short dbsize, short id, short value, short flag)
{
	LPCNCLDB	lpdb = lpdbTop;
	short		ret = -1;
	short		i;

	/* set temporary flag */
	lpdb = lpdbTop;
	for (i=0; i<dbsize; i++, lpdb++) {
		if (lpdb->nObjectID == id) {
			if (lpdb->nValue == value) {
				lpdb->tmpset = flag;
				ret = i;
				break;
			}

			if ((lpdb+1)->nObjectID != lpdb->nObjectID)
				break;
		}
	}
	return ret;
}


/*-------------------------------------------------------------*/
/* clear temporary flags                                       */
/*-------------------------------------------------------------*/
short ClearTemporaryFlag(LPCNCLDB lpdbTop, short dbsize)
{
	LPCNCLDB	lpdb = lpdbTop;
	short		i;

	/* set temporary flag */
	for (i=0; i<dbsize; i++, lpdb++) {
		if (lpdb->tmpset == 1) {
			SetCurrentFlag(lpdbTop, dbsize, lpdb->nObjectID, lpdb->nValue);
			lpdb->tmpset = 0;
		}

	}
	return 0;
}



/*-------------------------------------------------------------*/
/* get current flag status                                     */
/*-------------------------------------------------------------*/
short GetAllFlags(LPCNCLDB lpdbTop, short dbsize, short id, short value)
{
	LPCNCLDB	lpdb = lpdbTop;
	short		ret = -1;
	short		i;

	/* get all flag status */
	for (i=0; i<dbsize; i++, lpdb++) {
		if (lpdb->nObjectID == id) {
			if (lpdb->nValue == value) {
				ret = 0;
				if (lpdb->defset)
					ret |= DEFAULT_FLAG;
				if (lpdb->curset)
					ret |= CURRENT_FLAG;
				if (lpdb->tmpset)
					ret |= TEMPSET_FLAG;
				if (lpdb->disable)
					ret |= DISABLE_FLAG;
				break;
			}

			if ((lpdb+1)->nObjectID != lpdb->nObjectID)
				break;
		}
	}
	/* printf("AllFlags ID: %d value: %d ret: %d\n", id, value, ret); */
	return ret;
}



/*-------------------------------------------------------------*/
/* Option analization entry function                           */
/*-------------------------------------------------------------*/
int cmdlinesw(
	poptContext			*optcon,
	OPT					*opt,
	LPBJF_OPTINFO		lpbjf_optinfo,
	LPBJFLTCOLORSYSTEM	bjcolor,
	LPBJFLTDEVICE		bjdevice,
	LPCNCLPAPERSIZE		psize,
	char				*dispname,
	char 				*fname )
{
	int				rc, setopt;
	int				id;
	UIDB			uidb;
	short			DefaultGamma = 0;

	setopt = 0;
	lpbjf_optinfo->ui = OFF;
	uidb.lpdbTop = NULL;

	/* analize commandline arguments with popt, then set option values into struct opt.*/
	while ((rc = poptGetNextOpt(*optcon)) > 0) {
		switch (rc) {
			case 'u':
				// set ui flag to invoke GUI here.
				lpbjf_optinfo->ui = ON;
				break;
			default:
				setopt |= rc;
				break;
		}
	}

	if (rc < -1) {
		fprintf(stderr, "%s: %s\n",
				poptBadOption(*optcon, POPT_BADOPTION_NOALIAS),
				poptStrerror(rc));
		goto onError;
	}

	/* Display Internal Version */
	if ( setopt & OPTINTVER ){
		internalversion();
		goto onError;
	}

	/* check if filename is specified, or not (stdin mode) */
	if (poptPeekArg(*optcon) == 0) {
		lpbjf_optinfo->stdswitch = ON;
		*fname = '\0';
	}
	else {
		lpbjf_optinfo->stdswitch = OFF;

		/* filename should not be restricted to one.
			 so I should consider the way to pass the filename string array, later.*/
		strcpy(fname, poptGetArg(*optcon));
	}

	/*----
	  Options commonly used in GUI/command mode
	----*/

	/* ModelID Check is moved here.                                */
	/* because this option must be specified in any operation mode */
	if (setopt & OPTMODEL) {
		if ((id = bjf_get_resource_id( BJFILTERRCPATH, OPTSTRMODEL, opt->model )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid printer model name\n");
			goto onError;
		}
	}
	else {
		fprintf(stderr, "Error: printer model has to be specified with --model option\n");
		goto onError;
	}

	lpbjf_optinfo->modelid = id;					/* save ModelID to pass to printui */

	/* Specify Image resolution */
	if (setopt & OPTIMGRES) {
		lpbjf_optinfo->imageres = (short)opt->imageres;
	}

    /* Invoke Language Monitor ? */
	if (setopt & OPTLGMON) {
		lpbjf_optinfo->lgmon = ON;
	}

	/* -- Check --fit / -F option before location */
	if (setopt & OPTFIT) {
		lpbjf_optinfo->fit = ON;
	}

	/* -- changed the place of code to work in gui mode, and work with --fit option */
    /* Location */
	if (setopt & OPTLOCATION) {
		if (strcmp(opt->location, "center") == 0)
			lpbjf_optinfo->location = OPTLOC_CENTER;

		else if (strcmp(opt->location, "upperleft") == 0)
			lpbjf_optinfo->location = OPTLOC_UPPERLEFT;

		else {
			fprintf(stderr, "Error: invalid location option\n");
			goto onError;
		}
	}

	/* if GUI mode, then return here */
	if (lpbjf_optinfo->ui == ON) {

		/* if --display option is set, then pass the argument to dispname */
		/* and if not, set "locahost:0.0", by default                     */
		if (setopt & OPTDISPLAY) {
			strcpy(dispname, opt->display);
		}
		else {
			strcpy(dispname, "localhost:0.0");
		}
		return 0;
	}

	/*----
	  Options only used in command mode
	----*/

	/* Database access Init code */
	{
		/* Retrieve Name Information */
		if ( CNCL_GetDBName( &uidb.nominfo, (void *) &bjlibdir, id ) < 0) {
				fprintf(stderr, "Error: Internal Database Name Error\n");
				goto onError;
		}

		/* Allocate Internal DB Area */
		uidb.dbsize = CNCL_GetDBSize( &uidb.nominfo, (void *)bjlibdir);
		uidb.lpdbTop = (LPCNCLDB)malloc(sizeof(CNCLDB) * uidb.dbsize);
		uidb.ModelID = id;

		CNCL_GetEntries( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop);
		CNCL_GetDefaults( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);

		SetCurrentFlag( uidb.lpdbTop, uidb.dbsize, CNCL_DITHER_PAT, CND_UIBIN_ED );
		CNCL_InitMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);

		/* Initialize bjcolor contents, make it in a function later */
		uidb.bjcolor.bjfltIntent = 0;
		uidb.bjcolor.bjfltGamma = CND_GAMMA_14;
		if ( (DefaultGamma = GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_INPUT_GAMMA)) > 0 ){
			uidb.bjcolor.bjfltGamma = DefaultGamma;
		}
	
		uidb.bjcolor.bjfltBalanceC = 0;
		uidb.bjcolor.bjfltBalanceM = 0;
		uidb.bjcolor.bjfltBalanceY = 0;
		uidb.bjcolor.bjfltBalanceK = 0;
		uidb.bjcolor.bjfltDensity = 0;
	}

	/* Cartridge */
	if (setopt & OPTCARTRIDGE) {

		if ((id = bjf_get_resource_id( BJFILTERRCPATH, OPTSTRCARTRIDGE, opt->cartridge )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid printer cartridge name\n");
			goto onError;
		}

		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_CARTRIDGE, id) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_CARTRIDGE, id, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			// tolerant mode
			// strict mode
				// simple mode
				fprintf(stderr, "Error: inappropriate cartridge selection\n");
				goto onError;
				// verbose mode
		}
	}

	/* MediaType */
	if (setopt & OPTMEDIA) {

		if ((id = bjf_get_resource_id( BJFILTERRCPATH, OPTSTRMEDIA, opt->media )) == BJFRCACCESSERROR){
			fprintf(stderr, "Error: invalid printer mediatype name\n");
			goto onError;
		}

		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIATYPE, id) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIATYPE, id, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			// tolerant mode
			// strict mode
				// simple mode
				fprintf(stderr, "Error: inappropriate medium selection\n");
				goto onError;
				// verbose mode
		}
	}

	/* PrintQuality */
	if (setopt & OPTQUALITY) {
		// 
		if ((id = bjf_get_resource_id( BJFILTERRCPATH, OPTSTRQUALITY, opt->quality )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid printer quality\n");
			goto onError;
		}

		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_PRINTQUALITY, id) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_PRINTQUALITY, id, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			// tolerant mode
			// strict mode
				// simple mode
				fprintf(stderr, "Error: inappropriate print quality selection\n");
				goto onError;
				// verbose mode
		}
	}

	/* GrayScale */
	if (setopt & OPTGRAY) {
		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_GRAYSCALE, CND_BJGRAYSCALE_ON) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_GRAYSCALE, CND_BJGRAYSCALE_ON, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			fprintf(stderr, "Error: inappropriate grayscale selection\n");
		}
	}

	/* Dither Pattern */
	if (setopt & OPTHALFTONE) {

		if ((id = bjf_get_resource_id( BJFILTERRCPATH, OPTSTRHALFTONE, opt->halftoning )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid halftoning mode\n");
			goto onError;
		}

		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_DITHER_PAT, id) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_DITHER_PAT, id, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			// tolerant mode
			// strict mode
				// simple mode
				fprintf(stderr, "Error: inappropriate halftoning mode selection\n");
				goto onError;
				// verbose mode
		}
	}

	/* Banner */
	if (setopt & OPTBANNER) {
		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_BANNER, CND_BANNER_ON) >= 0) {
			SetTemporaryFlag( uidb.lpdbTop, uidb.dbsize, CNCL_BANNER, id, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			fprintf(stderr, "Error: inappropriate banner selection\n");
		}
	}

	/* PaperLoad */
	if (setopt & OPTLOAD) {

		if ((id = bjf_get_resource_id( BJFILTERRCPATH, OPTSTRLOAD, opt->paperload )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid paper load mode\n");
			goto onError;
		}

		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIASUPPLY, id) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIASUPPLY, id, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			// tolerant mode
			// strict mode
				// simple mode
				fprintf(stderr, "Error: inappropriate paper load selection\n");
				goto onError;
				// verbose mode
		}
	}

	/* rendering intent */
	if (setopt & OPTRENDER) {

		if ((id = bjf_get_resource_id( BJFILTERRCPATH, OPTSTRRENDER, opt->renderintent )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid paper load mode\n");
			goto onError;
		}
		uidb.bjcolor.bjfltIntent = id;
	}

	/* gamma */
	if (setopt & OPTGAMMA) {

		if ((id = bjf_get_resource_id( BJFILTERRCPATH, OPTSTRGAMMA, opt->gamma )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid gamma value\n");
			goto onError;
		}
		uidb.bjcolor.bjfltGamma = id;
	}

	/* balance CYAN */
	if (setopt & OPTBALC) {
		if ((opt->balance_c < -50) || (opt->balance_c > 50)) {
			fprintf(stderr, "Error: invalid Cyan balance value \n");
			goto onError;
		}
		uidb.bjcolor.bjfltBalanceC = opt->balance_c;
	}

	/* balance MAGENTA */
	if (setopt & OPTBALM) {
		if ((opt->balance_m < -50) || (opt->balance_m > 50)) {
			fprintf(stderr, "Error: invalid Magenta balance value \n");
			goto onError;
		}
		uidb.bjcolor.bjfltBalanceM = opt->balance_m;
	}

	/* balance YELLOW */
	if (setopt & OPTBALY) {
		if ((opt->balance_y < -50) || (opt->balance_y > 50)) {
			fprintf(stderr, "Error: invalid Yellow balance value \n");
			goto onError;
		}
		uidb.bjcolor.bjfltBalanceY = opt->balance_y;
	}

	/* balance BLACK */
	if (setopt & OPTBALK) {
		if ((opt->balance_k < -50) || (opt->balance_k > 50)) {
			fprintf(stderr, "Error: invalid Black balance value \n");
			goto onError;
		}
		uidb.bjcolor.bjfltBalanceK = opt->balance_k;
	}

	if (setopt & OPTDENSITY) {
		if ((opt->density < -50) || (opt->density > 50)) {
			fprintf(stderr, "Error: invalid density value \n");
			goto onError;
		}
		uidb.bjcolor.bjfltDensity = opt->density;
	}

	/* PaperSize */
	if (setopt & OPTPSIZE) {

		if ((id = bjf_get_resource_id( BJFILTERRCPATH, OPTSTRPSIZE, opt->papersize )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid papersize\n");
			goto onError;
		}

		if (SetCurrentFlag(uidb.lpdbTop, uidb.dbsize, CNCL_PAPERSIZE, id) < 0)
			fprintf(stderr, "Error: Papersize flag set error\n");
	}

	CNCL_GetMargin( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, psize, uidb.dbsize);

	/* Prepare bjdevice structure, to handover main routine */
	bjdevice->bjfltModelID			= uidb.ModelID;
	bjdevice->bjfltMediaType		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIATYPE);
	bjdevice->bjfltPrintQuality 	= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_PRINTQUALITY);
	bjdevice->bjfltMediaSupply		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIASUPPLY);
	bjdevice->bjfltPaperSize		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_PAPERSIZE);
	
	bjdevice->bjfltBinMethod		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_DITHER_PAT);
	if ( bjdevice->bjfltBinMethod == CND_UIBIN_PATTERN_HS  )
		bjdevice->bjfltBinMethod = CND_UIBIN_PATTERN;
		
	bjdevice->bjfltBanner			= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_BANNER);
	bjdevice->bjfltInkType			= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_CARTRIDGE);
	bjdevice->bjfltGrayScale		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_GRAYSCALE);

	//bjdevice->bjfltPaperWidth	    = PaperTbl[bjdevice->bjfltPaperSize][YOKO];
	//bjdevice->bjfltPaperHeight	    = PaperTbl[bjdevice->bjfltPaperSize][TATE];

	// add 2001/05/06
	if ( GetPaperSize( bjdevice->bjfltPaperSize, &bjdevice->bjfltPaperWidth,
		&bjdevice->bjfltPaperHeight	) < 0 ) goto onError;

	/* then prepare BJCOLORSYSTEM structure */
	*bjcolor = uidb.bjcolor;

	if (uidb.lpdbTop)
		free(uidb.lpdbTop);
	return 0;

onError:
	if (uidb.lpdbTop)
		free(uidb.lpdbTop);

	return -1;
}

void init_optioninfo( LPBJF_OPTINFO lpbjfoption )
{
	/* init option parameter */
	lpbjfoption->location = OPTLOC_UPPERLEFT;
	lpbjfoption->fit	= 0;
	lpbjfoption->ui		= 0;
	lpbjfoption->stdswitch = 0;
	lpbjfoption->imageres = 0;
	lpbjfoption->modelid = 0;
	lpbjfoption->lgmon = 0;
}
