/*
 *  Canon Inkjet Printer Driver for Linux
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

#include "cncl.h"
#include "cncldef.h"
#include "cncl2def.h"
#include "cnclucom.h"
#include "cncludef.h"
#include "bjfoption.h"
#include "bjfrcaccess.h"
#include "uitypes.h"
#include "bjipc.h"

#define  DEFINE_GLOBALS
#include "psize.h"
#include "bjfversion.h"
#include "bjfpath.h"

short SetCmdOption(int, char **, LPBJF_OPTINFO, LPBJFLTCOLORSYSTEM, LPBJFLTDEVICE, LPCNCLPAPERSIZE, char *, char *, char *);
static void usage( char * );
static void init_optioninfo( LPBJF_OPTINFO lpbjfoption );
static int cmdlinesw(poptContext *, OPT *, LPBJF_OPTINFO, LPBJFLTCOLORSYSTEM, LPBJFLTDEVICE, LPCNCLPAPERSIZE, char *, char *, char *, char *);
void MakeModelnameConfname(  char *, char *, char *, char *, char *);
static short ParseBbox(char *bbox , LPBJF_OPTINFO lpbjf_optinfo);

static long convert_str_to_long(char *);

const char bjlibdir[] = BJLIBPATH;

const char usage_bjfilter[]			= "Usage: cif";
const char usage_switches[]			= " [switches] [file]\n\n";

const char usage_str_ime[]		= "       switches: [ --imageres     1 - 32767               ]\n";
const char usage_str_car[]		= "                 [ --cartridge    cartridgetype           ]\n";
const char usage_str_med[]		= "                 [ --media        mediatype               ]\n";
const char usage_str_hal[]		= "                 [ --halftoning   halftonetype            ]\n";
const char usage_str_qua[]		= "                 [ --quality      1 - 5                   ]\n";
const char usage_str_gra[]		= "                 [ --grayscale                            ]\n";
const char usage_str_pap[]		= "                 [ --papersize    size                    ]\n";
const char usage_str_pal[]		= "                 [ --paperload    position                ]\n";
const char usage_str_bor[]		= "                 [ --borderless                           ]\n";
const char usage_str_ext[]		= "                 [ --extension    0 - 3                   ]\n";
const char usage_str_loc[]		= "                 [ --location     position                ]\n";
const char usage_str_fit[]		= "                 [ --fit                                  ]\n";
const char usage_str_ful[]		= "                 [ --full                                 ]\n";
const char usage_str_per[]		= "                 [ --percent      20 - 400                ]\n";
const char usage_str_cop[]		= "                 [ --copies       1 - 999                 ]\n";
const char usage_str_int[]		= "                 [ --renderintent intent                  ]\n";
const char usage_str_gam[]		= "                 [ --gamma        1.4 / 1.8 /2.2          ]\n";
const char usage_str_bac[]		= "                 [ --balance_c    -50  -   50             ]\n";
const char usage_str_bam[]		= "                 [ --balance_m    -50  -   50             ]\n";
const char usage_str_bay[]		= "                 [ --balance_y    -50  -   50             ]\n";
const char usage_str_bak[]		= "                 [ --balance_k    -50  -   50             ]\n";
const char usage_str_tone[]		= "                 [ --tone         -50  -   50             ]\n";
const char usage_str_contrast[]	= "                 [ --contrast     -50  -   50             ]\n";
const char usage_str_den[]		= "                 [ --density      -50  -   50             ]\n";
const char usage_str_gap[]		= "                 [ --papergap     gaptype                 ]\n";
const char usage_str_bbox[]		= "                 [ --bbox         left,bottom,right,top   ]\n";
const char usage_str_duplex[]	= "                 [ --duplex                               ]\n";
const char usage_str_staple[]	= "                 [ --stapleside   longside / shortside    ]\n";
const char usage_str_ics[]		= "                 [ --inkcartridgesettings   cartridgetype ]\n";

static short tone_support = 0;
static short borderless_support = 0;
static short papergap_support = 0;
static short duplex_support = 0;
static short ics_support = 0;
static short vivid_support = 0;
static short formattype = -1;

/*-------------------------------------------------------------*/
/* Display usage                                               */
/*-------------------------------------------------------------*/
void usage( char *modelname )
{
	char	small_tmpname[64],useagebjfilter[64];
	short	i;

	for( i=0; i<sizeof(small_tmpname); i++)
		small_tmpname[i] = tolower(modelname[i]);

	snprintf(useagebjfilter, sizeof(useagebjfilter),"%s%s%s",usage_bjfilter,small_tmpname,usage_switches);

	fprintf(stderr, "\n%s\n%s\n%s\n\n%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
					VERSION_STR,
					COPYRIGHT_STR0,
					COPYRIGHT_STR1,
					useagebjfilter,
					usage_str_ime,
					usage_str_car,
					usage_str_med,
					(( formattype < CND_FORMATTYPE_12)? usage_str_hal:""),
					usage_str_qua,
					usage_str_gra,
					usage_str_pap,
					usage_str_pal,
					(borderless_support?usage_str_bor:""),
					(borderless_support?usage_str_ext:""),
					usage_str_loc,
					usage_str_fit,
					usage_str_ful,
					usage_str_per,
					usage_str_cop,
					usage_str_int,
					usage_str_gam,
					usage_str_bac,
					usage_str_bam,
					usage_str_bay,
					(tone_support?usage_str_tone:""),
					( ( formattype >= CND_FORMATTYPE_6 ) ? "":usage_str_bak),		/* Ver.2.70 */
					( ( formattype >= CND_FORMATTYPE_6 ) ? usage_str_contrast:""),	/* Ver.2.70 */
					usage_str_den,
					(papergap_support?usage_str_gap:""),
					(duplex_support?usage_str_duplex:""),
					(duplex_support?usage_str_staple:""),
					(ics_support?usage_str_ics:""),
					usage_str_bbox
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

	while ((id != PaperTbl[paper][PSID]) && (PaperTbl[paper][PSID] != -1)) paper++;

	if ( PaperTbl[paper][PSID] == -1 ) goto onErr;

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
/* Look up ID with specified value                             */
/* (give no consideration to "disable flag")                   */
/*-------------------------------------------------------------*/
short FindValue(LPCNCLDB lpdbTop, short dbsize, short id, short value)
{
	LPCNCLDB	lpdb = lpdbTop;
	short		ret = -1;
	short		i;

	/* lookup ID with specified value */
	lpdb = lpdbTop;
	for (i=0; i<dbsize; i++, lpdb++) {
		if (lpdb->nObjectID == id) {
			if ( lpdb->nValue == value ) {
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
				if(lpdb->disable == 1)
					break;
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
/* convert "--extension" value to CNCLID                       */
/*-------------------------------------------------------------*/
static short ConvExtToID( short value )
{
	short		current;
	short		result = -1;

	current = 0;

	while ( ExtensionTbl[current][0] != -1){
		if ( ExtensionTbl[current][0] == value ){
			result = ExtensionTbl[current][1];
			break;
		}else{
		  current++;
		}
	}
	
onErr:
	return result; 

}

/*-------------------------------------------------------------*/
/* Option analization entry function                           */
/*-------------------------------------------------------------*/
short SetCmdOption( 
	int 				cargc,
	char 				*cargv[],
	LPBJF_OPTINFO		lpbjfoption,
	LPBJFLTCOLORSYSTEM	bjcolor,
	LPBJFLTDEVICE		bjdevice,
	LPCNCLPAPERSIZE		psize,
	char 				*dispname,
	char 				*filename,
	char 				*modelname
)
{
	OPT					opt;
	poptContext			optcon;
	char				confname[256];
	short				first_modelstrnum,i;
	short				ret;

	struct poptOption optionsTable[] = {
		{ OPTSTRLOCATION, 		0,		POPT_ARG_STRING,	&opt.location,			OPTLOCATION },
		{ OPTSTRCARTRIDGE,		'c',	POPT_ARG_STRING,	&opt.cartridge,			OPTCARTRIDGE},
		{ OPTSTRMEDIA,			'm',	POPT_ARG_STRING,	&opt.media,				OPTMEDIA	},
		{ OPTSTRQUALITY,		'q',	POPT_ARG_STRING,	&opt.quality,			OPTQUALITY	},
		{ OPTSTRGRAY,			'g',	POPT_ARG_NONE,		&opt.grayscale,			OPTGRAY		},
		{ OPTSTRHALFTONE, 		0,		POPT_ARG_STRING,	&opt.halftoning,		OPTHALFTONE	},
		{ OPTSTRLOAD,			0,		POPT_ARG_STRING,	&opt.paperload,			OPTLOAD		},
		{ OPTSTRCORRECT,		0,		POPT_ARG_STRING,	&opt.correctionmode,	OPTCORRECT	},
		{ OPTSTRRENDER,			0,		POPT_ARG_STRING,	&opt.renderintent,		OPTRENDER	},
		{ OPTSTRGAMMA,			0,		POPT_ARG_STRING,	&opt.gamma,				OPTGAMMA	},
		{ OPTSTRSOURCE,			0,		POPT_ARG_STRING,	&opt.imagesource,		OPTSOURCE	},
		{ OPTSTRBALC,			0,		POPT_ARG_INT,		&opt.balance_c,			OPTBALC		},
		{ OPTSTRBALM,			0,		POPT_ARG_INT,		&opt.balance_m,			OPTBALM		},
		{ OPTSTRBALY,			0,		POPT_ARG_INT,		&opt.balance_y,			OPTBALY		},
		{ OPTSTRBALK,			0,		POPT_ARG_INT,		&opt.balance_k,			OPTBALK		},
		{ OPTSTRDENSITY,		0,		POPT_ARG_INT,		&opt.density,			OPTDENSITY	},
		{ OPTSTRPSIZE,			'p',	POPT_ARG_STRING,	&opt.papersize,			OPTPSIZE	},
		/*   to support 1.) add an option --imageres, to cover with the bug in the bmp filter in           */
		/*                  previous version of ghostscript. (lacking image resolution information)        */
		/*              2.) add --display, to specify X server to show printui/stamon                      */
		{ OPTSTRIMGRES,			0,		POPT_ARG_INT,		&opt.imageres,			OPTIMGRES	},
		{ OPTSTRDISPLAY,		0,		POPT_ARG_STRING,	&opt.display,			OPTDISPLAY	},
		{ OPTSTRFIT,            0,	    POPT_ARG_NONE,      &opt.fit,               OPTFIT      },
		{ OPTSTRINTVER,         0,      POPT_ARG_NONE,      &opt.internalversion,   OPTINTVER   },
		{ OPTSTRBORDERLESS,		0,		POPT_ARG_NONE,		&opt.borderless,		OPTBORDERLESS	},
		{ OPTSTRBBOX,			0,		POPT_ARG_STRING,	&opt.bbox,				OPTBBOX		},
		{ OPTSTREXTENSION,		0,		POPT_ARG_INT,		&opt.extension,			OPTEXTENSION},
		{ OPTSTRPERCENT,		0,		POPT_ARG_INT,		&opt.percent,			OPTPERCENT	},
		{ OPTSTRCOPIES, 		0,		POPT_ARG_INT,		&opt.copies,			OPTCOPIES	},
		{ OPTSTRREVPRINT, 		0,		POPT_ARG_NONE,		&opt.revprint,			OPTREVPRINT	},
		{ OPTSTRCOLLATE, 		0,		POPT_ARG_NONE,		&opt.collate,			OPTCOLLATE	},
		{ OPTSTRFULL,			0,      POPT_ARG_NONE,		&opt.full,				OPTFULL		},
		{ OPTSTRPAPERWIDTH,		0,      POPT_ARG_STRING,	&opt.paperwidth,		OPTPAPERWIDTH	},
		{ OPTSTRPAPERHEIGHT,	0,      POPT_ARG_STRING,	&opt.paperheight,		OPTPAPERHEIGHT	},
		{ OPTSTRPAPERGAP,		0,      POPT_ARG_STRING,	&opt.papergap,			OPTPAPERGAP	},
		{ OPTSTRHELP,			0,      POPT_ARG_NONE	,	&opt.help,				OPTHELP	},
		{ OPTSTRDUPLEX,			0,      POPT_ARG_NONE	,	&opt.duplex,			OPTDUPLEX	},
		{ OPTSTRSTAPLESIDE,		0,      POPT_ARG_STRING	,	&opt.stapleside,			OPTSTAPLESIDE	},
		{ OPTSTRINKCARTRIDGESETTINGS,0, POPT_ARG_STRING	,	&opt.inkcartridgesettings,	OPTINKCARTRIDGESETTINGS	},
		{ OPTSTRCONTRAST,		0,		POPT_ARG_INT,		&opt.contrast,			OPTCONTRAST	},
		{ OPTSTRTONE,			0,		POPT_ARG_INT,		&opt.tone,				OPTTONE	},
		{ OPTSTRROTATE,			0,		POPT_ARG_INT,		&opt.rotate,			OPTROTATE	},
		{ OPTSTRBIDI	,		0,		POPT_ARG_NONE,		&opt.bidi,				OPTBIDI		},
		{ OPTSTRSUPPORTNETWORK,	0,		POPT_ARG_NONE,		&opt.supportnetwork,	OPTSUPPORTNETWORK},
		{ NULL,					0,		0,					NULL,					0 			}
	};


	/*--- Analyze command line ---*/
	init_optioninfo( lpbjfoption );
	
	optcon = poptGetContext( NULL, cargc, (const char **)cargv, optionsTable, 0 );
	
	memset(confname , 0x00 , sizeof(confname));
	MakeModelnameConfname( cargv[0], modelname, confname, BJFILTERXXXXRCPATH, BJFILTERDOTCONF );
	first_modelstrnum = strlen(modelname);

	if ( ( ret = cmdlinesw( &optcon, &opt, lpbjfoption, bjcolor, bjdevice, psize, dispname, filename, confname, modelname ) ) < 0 ){
		if(ret == -1){								/* onErrorHelp */
			usage( modelname );
		}else if(ret < ( OPT_ERR_CODE_MAX -50 ) ){	/* onErrorMessage */
			fprintf(stderr, "%s" , usage_err_mes[ret+50] );
		}
		/* ret == -2 .. onError : No message */

		goto onErr;
	}

	if( optcon ) poptFreeContext( optcon );
	return (first_modelstrnum);
	
onErr:
	if( optcon ) poptFreeContext( optcon );

	return -1;


}	



/*-------------------------------------------------------------*/
/* Set option informations                                     */
/*-------------------------------------------------------------*/
int cmdlinesw(
	poptContext			*optcon,
	OPT					*opt,
	LPBJF_OPTINFO		lpbjf_optinfo,
	LPBJFLTCOLORSYSTEM	bjcolor,
	LPBJFLTDEVICE		bjdevice,
	LPCNCLPAPERSIZE		psize,
	char				*dispname,
	char 				*fname,
	char 				*confname,
	char 				*modelname )
{
	int				rc,setopt[4];
	int				id;
	UIDB			uidb;
	short			DefaultGamma = 0;
	short			DefaultIntent = 0;	/* Default value (PHOTO) */
	short			i,j;
	short			count_switch=0;
	short			ext = -1;
	short			change_paperload = 0;
	short			ret;
	short			is_grayscale_mode = 0;
	short			confirm_return_code = -1;
	
	/* automatic quality selection */
	int 			cur_quality_id;
	int 			def_quality_id;
	int 			opt_quality_direction;
	int 			opt_quality_max;
	int 			opt_quality_min;
	int 			opt_quality_id;
	int				quality_idx_span;
	int 			opt_quality_decided = 0;
	
	
	for(i=0;i<4;i++){
		setopt[i]=0;
	}
	uidb.lpdbTop = NULL;

	/* analize commandline arguments with popt, then set option values into struct opt.*/
	while ((rc = poptGetNextOpt(*optcon)) > 0) {
		setopt[OPTINDEX(rc)] |= OPTBIT(rc);
	}

	if( *modelname == '\0' ){
		fprintf(stderr, "Error: printer model has to be specified\n\n");
		fprintf(stderr, "Usage: cifXXXX\n\tXXXX: Printer Model Name\n");
		/* inappropriate selection error. */
		goto onError;
	}

	if (rc < -1) {
		/* no error when unknown option comes (from Ver.3.80) */
		if(rc != POPT_ERROR_BADOPT){
			fprintf(stderr, "%s: %s\n",
					poptBadOption(*optcon, POPT_BADOPTION_NOALIAS),
					poptStrerror(rc));
			goto onError;
		}
	}

	/* Display Internal Version */
	if (setopt[OPTINDEX(OPTINTVER)] & OPTBIT(OPTINTVER)) {
		internalversion();
		goto onError;
	}
	
	/* Display Support Network */
	if (setopt[OPTINDEX(OPTSUPPORTNETWORK)] & OPTBIT(OPTSUPPORTNETWORK)) {
		if (bjf_get_resource_id( confname, OPTSTRSUPPORTNETWORK, modelname ) == BJFRCACCESSERROR ){
			fprintf( stderr, "%d\n", NETWORK_SUPPORT_NO );
		} else {
			fprintf( stderr, "%d\n", NETWORK_SUPPORT_YES );
		}
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
		strncpy(fname, poptGetArg(*optcon), 255);
		fname[254] = '\0';
	}

	/* ModelID Check is moved here.                                */
	/* because this option must be specified in any operation mode */
	if ((id = bjf_get_resource_id( confname, "model", modelname )) == BJFRCACCESSERROR ){
		fprintf(stderr, "Error: invalid printer model name\n");
		goto onError;
	}

	lpbjf_optinfo->modelid = id;					/* save ModelID to pass to printui */

	/* Specify Image resolution */
	if (setopt[OPTINDEX(OPTIMGRES)] & OPTBIT(OPTIMGRES)) {
		/* resolution limit */
		if ((opt->imageres < 1) || (opt->imageres > 32767)) {
			fprintf(stderr, "Error: invalid image resolution \n");
			ret = OPT_ERR_IME - 50;
			goto onErrorMessage;
		}
		lpbjf_optinfo->imageres = (short)opt->imageres;
	}

	/* -- Check --bbox option */ 
	if (setopt[OPTINDEX(OPTBBOX)] & OPTBIT(OPTBBOX)) {
		if( ParseBbox(opt->bbox , lpbjf_optinfo) < 0){
			fprintf(stderr,"Error:invalid bbox value\n");
			ret = OPT_ERR_BBOX - 50;
			goto onErrorMessage;
		}
		lpbjf_optinfo->bbox.bbox_flag = BBOX_ON;
	}

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

		/* Check errors. */
		if ( CNCL_GetEntries( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop) < 0) {
				fprintf(stderr, "Error: CNCL_GetEntries\n");
				goto onError;
		}
		if ( CNCL_GetDefaults( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize) < 0) {
				fprintf(stderr, "Error: CNCL_GetDefaults\n");
				goto onError;
		}
		if ( CNCL_InitMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize) < 0) {
				fprintf(stderr, "Error: CNCL_InitMenulink\n");
				goto onError;
		}


		/* Check CNCL format (Ver.2.70 : moved here) */
		if( (formattype = CNCL_GetTableFormatType( &uidb.nominfo, (void *)bjlibdir )) <0 ){
			fprintf(stderr, "Error: INTERNAL ERROR(%d)\n", __LINE__);
			/* inappropriate selection error. */
			goto onError;
		}

		/* Initialize bjcolor contents, make it in a function later */
		uidb.bjcolor.bjfltIntent = 0;	/* Default value (PHOTO) */
		/* formattype >= CND_FORMATTYPE_6 ...Get DefaultIntent by "GetCurrentValue" */
		if( formattype >= CND_FORMATTYPE_6 ){
			if ( (DefaultIntent = GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_INTENT)) >= 0 ){
				uidb.bjcolor.bjfltIntent = DefaultIntent;
			}else{
				fprintf(stderr, "Error: INTERNAL ERROR(%d)\n", __LINE__);
				/* inappropriate selection error. */
				goto onError;
			}
		}

		uidb.bjcolor.bjfltGamma = CND_GAMMA_14;
		if ( (DefaultGamma = GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_INPUT_GAMMA)) > 0 ){
			uidb.bjcolor.bjfltGamma = DefaultGamma;
		}
	
		uidb.bjcolor.bjfltBalanceC = 0;
		uidb.bjcolor.bjfltBalanceM = 0;
		uidb.bjcolor.bjfltBalanceY = 0;
		uidb.bjcolor.bjfltBalanceK = 0;
		uidb.bjcolor.bjfltMonochromeTone = 0;
		uidb.bjcolor.bjfltDensity = 0;
		uidb.bjcolor.bjfltContrast = 0;
	}


	/* Check whether following options(or parameters) are supported or not.
	  --  "borderless"  , "papergap" , "duplex" , "inkcartridgesettings" , "renderintent vivid"--
	*/
	if (FindValue(uidb.lpdbTop, uidb.dbsize, CNCL_MARGINTYPE, CND_MARGIN_MINUS) >= 0) {
		borderless_support = 1;
	}

	if (FindValue(uidb.lpdbTop, uidb.dbsize, CNCL_PAPERGAP_COMMAND, CND_PGAP_CMD_AUTO) >= 0) {
		papergap_support = 1;
	}

	if (FindValue(uidb.lpdbTop, uidb.dbsize, CNCL_DUPLEX_PRINTING, CND_DUPLEX_AUTO) >= 0) {
		duplex_support = 1;
	}

	ics_support = 1;
	if (GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_INKCARTRIDGESETTINGS ) < 0) {
		ics_support = 0;
	}else if (FindValue(uidb.lpdbTop, uidb.dbsize, CNCL_INKCARTRIDGESETTINGS, CND_CARTRIDGE_NA ) >= 0) {
		ics_support = 0;
	}

	if (FindValue(uidb.lpdbTop, uidb.dbsize, CNCL_VIVID, CND_VIVID_SUPPORT) >= 0) {	/* Ver.2.70 */
		vivid_support = 1;
	}
	
	if (FindValue(uidb.lpdbTop, uidb.dbsize, CNCL_BLACK_ADJUSTMENT, CND_BLACK_ADJUSTMENT) >= 0) {
		tone_support = 1;
	}
	
	/* Check --help option */
	/* if "--help", then return here */
	if (setopt[OPTINDEX(OPTHELP)] & OPTBIT(OPTHELP)) {
			goto onErrorHelp;
	}


	/* copies */
	if (setopt[OPTINDEX(OPTCOPIES)] & OPTBIT(OPTCOPIES)) {
		if ((opt->copies < 1) || (opt->copies > 999)) {
			fprintf(stderr, "Error: invalid copies value \n");
			ret = OPT_ERR_COP - 50;
			goto onErrorMessage;
		}

		lpbjf_optinfo->copies = opt->copies;
	}
	
	/* revprint */
	if (setopt[OPTINDEX(OPTREVPRINT)] & OPTBIT(OPTREVPRINT)) {
		lpbjf_optinfo->revprint = ON;
	}
	
	/* collate */
	if (setopt[OPTINDEX(OPTCOLLATE)] & OPTBIT(OPTCOLLATE)) {
		lpbjf_optinfo->collate = ON;
	}


	/* -- Check --fit option before location */
	if (setopt[OPTINDEX(OPTFIT)] & OPTBIT(OPTFIT)) {
		lpbjf_optinfo->fit = FIT_SHORT;
		count_switch++;
	}

	/* -- Check --full option before location */
	if (setopt[OPTINDEX(OPTFULL)] & OPTBIT(OPTFULL)) {
		lpbjf_optinfo->fit = FIT_LONG;
		count_switch++;
	}

    /* Location */
	if (setopt[OPTINDEX(OPTLOCATION)] & OPTBIT(OPTLOCATION)) {
		if (strcmp(opt->location, "center") == 0)
			lpbjf_optinfo->location = LOCATION_CENTER;

		else if (strcmp(opt->location, "upperleft") == 0)
			lpbjf_optinfo->location = LOCATION_UPPERLEFT;

		else {
			fprintf(stderr, "Error: invalid location option\n");
			ret = OPT_ERR_LOC - 50;
			goto onErrorMessage;
		}
	}


	/* Specify Image scaling */
	if (setopt[OPTINDEX(OPTPERCENT)] & OPTBIT(OPTPERCENT)) {
		if ((opt->percent < 20) || (opt->percent > 400)) {
			fprintf(stderr, "Error: invalid scaling value\n");
			ret = OPT_ERR_PER - 50;
			goto onErrorMessage;
		}
		lpbjf_optinfo->percent = (short)opt->percent;
		count_switch++;
	}

	if(count_switch > 1){
		fprintf(stderr,"Error: Only one of the following options can be selected.\n");
		fprintf(stderr,"\t--fit / --full / --percent\n");
		goto onError;
	}


	/* Cartridge */
	if (setopt[OPTINDEX(OPTCARTRIDGE)] & OPTBIT(OPTCARTRIDGE)) {

		if ((id = bjf_get_resource_id( confname, OPTSTRCARTRIDGE, opt->cartridge )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid printer cartridge name\n");
			ret = OPT_ERR_CAR - 50;
			goto onErrorMessage;
		}

		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_CARTRIDGE, id) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_CARTRIDGE, id, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			fprintf(stderr, "Error: inappropriate cartridge selection\n");
			/* inappropriate selection error. */
			goto onError;
		}
	}


	/* MediaType */
	if (setopt[OPTINDEX(OPTMEDIA)] & OPTBIT(OPTMEDIA)) {

		if ((id = bjf_get_resource_id( confname, OPTSTRMEDIA, opt->media )) == BJFRCACCESSERROR){
			fprintf(stderr, "Error: invalid printer mediatype name\n");
			ret = OPT_ERR_MED - 50;
			goto onErrorMessage;
		}

		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIATYPE, id) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIATYPE, id, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			fprintf(stderr, "Error: inappropriate mediatype selection\n");
			/* inappropriate selection error. */
			goto onError;
		}
	}


	/* GrayScale */
	if (setopt[OPTINDEX(OPTGRAY)] & OPTBIT(OPTGRAY)) {
		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_GRAYSCALE, CND_BJGRAYSCALE_ON) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_GRAYSCALE, CND_BJGRAYSCALE_ON, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
			
			is_grayscale_mode = 1;
		}
		else {
			fprintf(stderr, "Error: inappropriate grayscale selection\n");
			/* inappropriate selection error. */
			goto onError;
		}
	}


	/* Borderless */
	if (setopt[OPTINDEX(OPTBORDERLESS)] & OPTBIT(OPTBORDERLESS))
	{
		if( borderless_support ){
			if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_MARGINTYPE, CND_MARGIN_MINUS) >= 0) {
				SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_MARGINTYPE, 1, 1);
				CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
			}
			else {
				fprintf(stderr, "Error: inappropriate borderless selection\n");
				/* inappropriate selection error. */
				goto onError;
			}

		}else{	/* not support borderless */
			fprintf(stderr, "Error: \"--borderless\" option is not supported by this printer\n");
			/* inappropriate selection error. */
			goto onError;
		}
	}


	/* -- Check --extension option */ 
	if (setopt[OPTINDEX(OPTEXTENSION)] & OPTBIT(OPTEXTENSION)) {
		if (!(setopt[OPTINDEX(OPTBORDERLESS)] & OPTBIT(OPTBORDERLESS))) {
			fprintf(stderr, "Error: Cannot select \"--extension\" option without \"--borderless\" \n");
			goto onError;
		}

		
		if( formattype == CND_FORMATTYPE_4 ){	/* DB supports extension_level info */
			/* check value and convert value to CNCL_ID */
			opt->extension = ConvExtToID( opt->extension );

			if( opt->extension < 0 ){
				fprintf(stderr, "Error: invalid extension\n");
				ret = OPT_ERR_EXT - 50;
				goto onErrorMessage;
			}

			/* check uidb (by CNCL_ID) */
			if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_OVERMARGIN_LEVEL, opt->extension ) >= 0) {
				lpbjf_optinfo->extension = (short)opt->extension;
			}
			else {
				fprintf(stderr, "Error: inappropriate extension selection\n");
				/* inappropriate selection error. */
				goto onError;
			}

		}else{							/* DB deoes not support extension_level info */
			if( opt->extension >=0 && opt->extension<=3 ){
				lpbjf_optinfo->extension = (short)opt->extension;
			}else{
				fprintf(stderr, "Error: invalid extension\n");
				ret = OPT_ERR_EXT - 50;
				goto onErrorMessage;
			}
		}

	}else{
		/* Set defualt value */
		ext = GetDefaultnValue(uidb.lpdbTop, uidb.dbsize, CNCL_OVERMARGIN_LEVEL);

		if( ext < 0 ){	/* default value of EXTENSION not found */
			if ((id = bjf_get_resource_id( confname, "extension_default", modelname )) == BJFRCACCESSERROR){
				lpbjf_optinfo->extension = 3;	/* Default: Max */
			}else{
				lpbjf_optinfo->extension = id;
			}
		}else{			/* default value of EXTENSION found */
			lpbjf_optinfo->extension = ext;
		}
	}


	/* PrintQuality (change to appropriate quality automatically(from ver.3.80)) */
	if (setopt[OPTINDEX(OPTQUALITY)] & OPTBIT(OPTQUALITY)) {
		
		// high quality
		if ((opt_quality_max = bjf_get_resource_id( confname, OPTSTRQUALITY, "1" )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid print quality\n");
			ret = OPT_ERR_QUA - 50;
			goto onErrorMessage;
		}
		
		// high speed
		if ((opt_quality_min = bjf_get_resource_id( confname, OPTSTRQUALITY, "5" )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid print quality\n");
			ret = OPT_ERR_QUA - 50;
			goto onErrorMessage;
		}
		
		// specified quality
		if ((opt_quality_id = bjf_get_resource_id( confname, OPTSTRQUALITY, opt->quality )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid print quality\n");
			ret = OPT_ERR_QUA - 50;
			goto onErrorMessage;
		}
		
		// default quality
		def_quality_id = GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_PRINTQUALITY);
		
		// direction
		opt_quality_direction = (def_quality_id > opt_quality_id)? 1:-1;
		
		// decide quality
		for (quality_idx_span = 0; quality_idx_span < 5; quality_idx_span++){
			
			// high priority
			cur_quality_id = opt_quality_id + (quality_idx_span * opt_quality_direction);
			if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_PRINTQUALITY, cur_quality_id) >= 0) {
				SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_PRINTQUALITY, cur_quality_id, 1);
				CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
				opt_quality_decided = 1;
				break;
			}
			
			// low priority
			cur_quality_id = opt_quality_id - (quality_idx_span * opt_quality_direction);
			if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_PRINTQUALITY, cur_quality_id) >= 0) {
				SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_PRINTQUALITY, cur_quality_id, 1);
				CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
				opt_quality_decided = 1;
				break;
			}
		}
		if (opt_quality_decided != 1){
			fprintf(stderr, "Error: invalid print quality\n");
			ret = OPT_ERR_QUA - 50;
			goto onErrorMessage;
		}
	}

	/* PaperLoad */
	if (setopt[OPTINDEX(OPTLOAD)] & OPTBIT(OPTLOAD)) {

		if ((id = bjf_get_resource_id( confname, OPTSTRLOAD, opt->paperload )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid paper load\n");
			ret = OPT_ERR_PAL - 50;
			goto onErrorMessage;
		}

		/* Change "frontplain" to "asf" */
		if ( id == CND_SUPPLY_FRONT_FOR_PLAIN ){
			/* Check whether "frontplain"is supported or not.*/
			if ( FindValue(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIASUPPLY, CND_SUPPLY_CASSETTE_04) < 0) {
				fprintf(stderr, "Error: inappropriate paper load selection\n");
				/* inappropriate selection error. */
				goto onError;
			}
			id = CND_SUPPLY_ASF;
			change_paperload = 1;
		}
		
		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIASUPPLY, id) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIASUPPLY, id, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			fprintf(stderr, "Error: inappropriate paper load selection\n");
			/* inappropriate selection error. */
			goto onError;
		}
	}

	/* PaperSize */
	if (setopt[OPTINDEX(OPTPSIZE)] & OPTBIT(OPTPSIZE)) {
		if ((id = bjf_get_resource_id( confname, OPTSTRPSIZE, opt->papersize )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid papersize\n");
			ret = OPT_ERR_PAP - 50;
			goto onErrorMessage;
		}

		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_PAPERSIZE, id) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_PAPERSIZE, id, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			fprintf(stderr, "Error: inappropriate papersize selection\n");
			/* inappropriate selection error. */
			goto onError;
		}
	}


	/* duplex */
	if (setopt[OPTINDEX(OPTDUPLEX)] & OPTBIT(OPTDUPLEX))
	{
		if( duplex_support ){
			if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_DUPLEX_PRINTING, CND_DUPLEX_AUTO) >= 0) {
				SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_DUPLEX_PRINTING, 1, 1);
				CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
			}
			else {
				fprintf(stderr, "Error: inappropriate duplex selection\n");
				/* inappropriate selection error. */
				goto onError;
			}
		
		}else{	/* not support duplex */
			fprintf(stderr, "Error: \"--duplex\" option is not supported by this printer\n");
			/* inappropriate selection error. */
			goto onError;
		}
	}


    /* stapleside */
	if (setopt[OPTINDEX(OPTSTAPLESIDE)] & OPTBIT(OPTSTAPLESIDE)) {
		if (!(setopt[OPTINDEX(OPTDUPLEX)] & OPTBIT(OPTDUPLEX))) {
			fprintf(stderr, "Error: Cannot select \"--stapleside\" option without \"--duplex\" \n");
			goto onError;
		}

		if (strcmp(opt->stapleside, "longside") == 0)
			lpbjf_optinfo->stapleside = STAPLESIDE_LONG;

		else if (strcmp(opt->stapleside, "shortside") == 0)
			lpbjf_optinfo->stapleside = STAPLESIDE_SHORT;

		else {
			fprintf(stderr, "Error: invalid stapleside name\n");
			ret = OPT_ERR_STAPLE - 50;
			goto onErrorMessage;
		}
	}


	/* Dither Pattern */
	if (setopt[OPTINDEX(OPTHALFTONE)] & OPTBIT(OPTHALFTONE)) {
		
		/* halftoning is not supported (from ver.3.60) */
		if ( formattype >= CND_FORMATTYPE_12 ){
			fprintf(stderr, "Error: \"--halftoning\" option is not supported by this printer\n");
			/* inappropriate selection error. */
			goto onError;
		}
		
		if ((id = bjf_get_resource_id( confname, OPTSTRHALFTONE, opt->halftoning )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid halftoning mode\n");
			ret = OPT_ERR_HAL - 50;
			goto onErrorMessage;
		}

		if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_DITHER_PAT, id) >= 0) {
			SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_DITHER_PAT, id, 1);
			CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
		}
		else {
			fprintf(stderr, "Error: inappropriate halftoning mode selection\n");
			/* inappropriate selection error. */
			goto onError;
		}
	}


	/* PaperGap */
	if (setopt[OPTINDEX(OPTPAPERGAP)] & OPTBIT(OPTPAPERGAP)) {

		if( papergap_support ){
			if ((id = bjf_get_resource_id( confname, OPTSTRPAPERGAP, opt->papergap )) == BJFRCACCESSERROR ){
				fprintf(stderr, "Error: invalid papergap\n");
				ret = OPT_ERR_GAP - 50;
				goto onErrorMessage;
			}
	
			if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_PAPERGAP_COMMAND, id) >= 0) {
				SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_PAPERGAP_COMMAND, id, 1);
				CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
			}
			else {
				fprintf(stderr, "Error: inappropriate papergap selection\n");
				/* inappropriate selection error. */
				goto onError;
			}
		
		}else{	/* not support PaperGap */
			fprintf(stderr, "Error: \"--papergap\" option is not supported by this printer\n");
			/* inappropriate selection error. */
			goto onError;
		}
	}

	/* rendering intent */
	if (setopt[OPTINDEX(OPTRENDER)] & OPTBIT(OPTRENDER)) {

		if ((id = bjf_get_resource_id( confname, OPTSTRRENDER, opt->renderintent )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid rendering intent\n");
			ret = OPT_ERR_INT - 50;
			goto onErrorMessage;
		}
		
		if ( id == CND_INTENT_VIVID ){	/* vivid */
			if( !vivid_support ){	/* "vivid support"check */
				fprintf(stderr, "Error: inappropriate rendering intent\n");
				/* inappropriate selection error. */
				goto onError;
			}
		}
		else{	/* photo , graphics , etc.. */
			/* formattype >= CND_FORMATTYPE_6... DB supports intent_type info */
			if( formattype >= CND_FORMATTYPE_6 ){
				if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_INTENT, id) >= 0) {
					/* CNCL_GetMenulink is not necessary */
				}
				else {
					fprintf(stderr, "Error: inappropriate rendering intent\n");
					/* inappropriate selection error. */
					goto onError;
				}
			}
		}

		uidb.bjcolor.bjfltIntent = id;
	}

	/* gamma */
	if (setopt[OPTINDEX(OPTGAMMA)] & OPTBIT(OPTGAMMA)) {

		if ((id = bjf_get_resource_id( confname, OPTSTRGAMMA, opt->gamma )) == BJFRCACCESSERROR ){
			fprintf(stderr, "Error: invalid gamma value\n");
			ret = OPT_ERR_GAM - 50;
			goto onErrorMessage;
		}
		uidb.bjcolor.bjfltGamma = id;
	}

	/* balance CYAN */
	if (setopt[OPTINDEX(OPTBALC)] & OPTBIT(OPTBALC)) {
		if ((opt->balance_c < -50) || (opt->balance_c > 50)) {
			fprintf(stderr, "Error: invalid Cyan balance value \n");
			ret = OPT_ERR_BAC - 50;
			goto onErrorMessage;
		}
		uidb.bjcolor.bjfltBalanceC = opt->balance_c;
	}

	/* balance MAGENTA */
	if (setopt[OPTINDEX(OPTBALM)] & OPTBIT(OPTBALM)) {
		if ((opt->balance_m < -50) || (opt->balance_m > 50)) {
			fprintf(stderr, "Error: invalid Magenta balance value \n");
			ret = OPT_ERR_BAM - 50;
			goto onErrorMessage;
		}
		uidb.bjcolor.bjfltBalanceM = opt->balance_m;
	}

	/* balance YELLOW */
	if (setopt[OPTINDEX(OPTBALY)] & OPTBIT(OPTBALY)) {
		if ((opt->balance_y < -50) || (opt->balance_y > 50)) {
			fprintf(stderr, "Error: invalid Yellow balance value \n");
			ret = OPT_ERR_BAY - 50;
			goto onErrorMessage;
		}
		uidb.bjcolor.bjfltBalanceY = opt->balance_y;
	}

	/* balance BLACK */
	if (setopt[OPTINDEX(OPTBALK)] & OPTBIT(OPTBALK)) {
		if( formattype >= CND_FORMATTYPE_6 ){	/* not support balance_k */
			fprintf(stderr, "Error: \"--balance_k\" option is not supported by this printer\n");
			/* inappropriate selection error. */
			goto onError;

		}else{	/* support balance_k */
			if ((opt->balance_k < -50) || (opt->balance_k > 50)) {
				fprintf(stderr, "Error: invalid Black balance value \n");
				ret = OPT_ERR_BAK - 50;
				goto onErrorMessage;
			}
			uidb.bjcolor.bjfltBalanceK = opt->balance_k;
		}
	}
	
	/* Tone (from ver.3.40) */
	if (setopt[OPTINDEX(OPTTONE)] & OPTBIT(OPTTONE)) {
		if( formattype < CND_FORMATTYPE_11 || !tone_support){	/* not support tone */
			fprintf(stderr, "Error: \"--tone\" option is not supported by this printer\n");
			/* inappropriate selection error. */
			goto onError;
			
		} else if ( CNCL_ConfirmBlackAdjMedia( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize) <= 0){	/* invalid media */
			
			/* ignore error, and tone has no change.(from ver.3.80) */
			
		} else if ( !is_grayscale_mode ){	/* not grayscale mode */
			
			/* ignore error, and tone has no change.(from ver.3.80) */
			
		} else {	/* support tone */
			if ((opt->tone < -50) || (opt->tone > 50)) {
				fprintf(stderr, "Error: invalid tone value \n");
				ret = OPT_ERR_TONE - 50;
				goto onErrorMessage;
			}
			uidb.bjcolor.bjfltMonochromeTone = opt->tone;
		}
	}
	
	/* contrast */
	if (setopt[OPTINDEX(OPTCONTRAST)] & OPTBIT(OPTCONTRAST)) {
		if( formattype >= CND_FORMATTYPE_6 ){	/* support contrast */
			if ((opt->contrast < -50) || (opt->contrast > 50)) {
				fprintf(stderr, "Error: invalid contrast value \n");
				ret = OPT_ERR_CONTRAST - 50;
				goto onErrorMessage;
			}
			uidb.bjcolor.bjfltContrast = opt->contrast;

		}else{	/* not support contrast */
			fprintf(stderr, "Error: \"--contrast\" option is not supported by this printer\n");
			/* inappropriate selection error. */
			goto onError;
		}
	}

	/* density */
	if (setopt[OPTINDEX(OPTDENSITY)] & OPTBIT(OPTDENSITY)) {
		if ((opt->density < -50) || (opt->density > 50)) {
			fprintf(stderr, "Error: invalid density value \n");
			ret = OPT_ERR_DEN - 50;
			goto onErrorMessage;
		}
		uidb.bjcolor.bjfltDensity = opt->density;
	}

	/* support CND_SIZE_USER */
	bjdevice->bjfltPaperSize = GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_PAPERSIZE);
	if(bjdevice->bjfltPaperSize == CND_SIZE_USER) {
		psize->nSelPaperWidth = -1;
		psize->nSelPaperLength = -1;
		
		/* paperwidth */
		if (setopt[OPTINDEX(OPTPAPERWIDTH)] & OPTBIT(OPTPAPERWIDTH)) {
			psize->nSelPaperWidth = convert_str_to_long(opt->paperwidth);
			if(psize->nSelPaperWidth == -2) {
				fprintf(stderr, "%s: invalid numeric value\n",opt->paperwidth);
				goto onError;
			}
		}
		/* paperheight */
		if (setopt[OPTINDEX(OPTPAPERHEIGHT)] & OPTBIT(OPTPAPERHEIGHT)) {
			psize->nSelPaperLength = convert_str_to_long(opt->paperheight);
			if(psize->nSelPaperLength == -2) {
				fprintf(stderr, "%s: invalid numeric value\n",opt->paperheight);
				goto onError;
			}
		}
		
		/* if user is set, need to set both paperwidth and paperheight.  */
		if(psize->nSelPaperWidth == -1 || psize->nSelPaperLength == -1) {
			fprintf(stderr, "Error: if \"--papersize\" is \"user\",\n");
			fprintf(stderr, "       both \"--paperwidth\" and \"--paperheight\" must be set.\n");
			goto onError;
		}
	}
	else {
		/* check paperwidth and paperheight*/
		if ((setopt[OPTINDEX(OPTPAPERWIDTH)] & OPTBIT(OPTPAPERWIDTH)) ||
			(setopt[OPTINDEX(OPTPAPERHEIGHT)] & OPTBIT(OPTPAPERHEIGHT)) ) {
				fprintf(stderr, "Error: Cannot select \"--paperwidth\" and \"--paperheight\" without \"--papersize user\" \n");
				goto onError;
		}
		
		if ( (ret = GetPaperSize( bjdevice->bjfltPaperSize,
			&bjdevice->bjfltPaperWidth, &bjdevice->bjfltPaperHeight) ) < 0 ) goto onError;
	}


	if((ret=CNCL_GetMargin( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, psize, uidb.dbsize)) < 0)
	{
		if(ret < -2) {/* height out of range. */
			fprintf(stderr, "Error: invalid paperheight value. (integer: %5ld - %5ld [1/100mm])\n",
					psize->nMinCustomLength, psize->nMaxCustomLength);
			ret += 2;
		}
		if (ret == -2) {/* width out of range. */
			fprintf(stderr, "Error: invalid paperwidth value.  (integer: %5ld - %5ld [1/100mm])\n",
					psize->nMinCustomWidth, psize->nMaxCustomWidth);
		}
		goto onError;
	}


	/* inkcartridgesettings */
	if (setopt[OPTINDEX(OPTINKCARTRIDGESETTINGS)] & OPTBIT(OPTINKCARTRIDGESETTINGS))
	{
		if( ics_support ){
			if ((id = bjf_get_resource_id( confname, OPTSTRCARTRIDGE, opt->inkcartridgesettings )) == BJFRCACCESSERROR ){
				fprintf(stderr, "Error: invalid inkcartridgesettings name\n");
				ret = OPT_ERR_INKCAR - 50;
				goto onErrorMessage;
			}
			
			if (QueryValue(uidb.lpdbTop, uidb.dbsize, CNCL_INKCARTRIDGESETTINGS, id) >= 0) {
				SetTemporaryFlag(uidb.lpdbTop, uidb.dbsize, CNCL_INKCARTRIDGESETTINGS, id, 1);
				CNCL_GetMenulink( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
			}
			else {
				fprintf(stderr, "Error: inappropriate inkcartridgesettings selection\n");
				/* inappropriate selection error. */
				goto onError;
			}
		
		}else{	/* not support inkcartridgesettings */
			fprintf(stderr, "Error: \"--inkcartridgesettings\" option is not supported by this printer\n");
			/* inappropriate selection error. */
			goto onError;
		}
	}
	
	/* Rotate (Ver.3.80) */
	if (FindValue(uidb.lpdbTop, uidb.dbsize, CNCL_IMG_DIRECTION_CMD, CND_IMG_DIRECTION_CMD_TYPEA) >= 0) {
		if (setopt[OPTINDEX(OPTROTATE)] & OPTBIT(OPTROTATE)) {
			/* printer supports rotate */
			switch (opt->rotate){
				case 0:
					lpbjf_optinfo->rotate = CNCL_IMAGEROTATE_0;
					break;
				case 1:
					lpbjf_optinfo->rotate = CNCL_IMAGEROTATE_90;
					break;
				case 2:
					lpbjf_optinfo->rotate = CNCL_IMAGEROTATE_180;
					break;
				case 3:
					lpbjf_optinfo->rotate = CNCL_IMAGEROTATE_270;
					break;
				default:
					lpbjf_optinfo->rotate = CNCL_IMAGEROTATE_0;
					break;
			}
		} else {
			lpbjf_optinfo->rotate = CNCL_IMAGEROTATE_0;
		}
	} else {
		lpbjf_optinfo->rotate = CNCL_IMAGEROTATE_UNDEFINED;
	}
	
	
	/* bidi (Ver.3.20) */
	lpbjf_optinfo->is_ivec = 0;
	if (formattype >= CND_FORMATTYPE_9){
		if (FindValue(uidb.lpdbTop, uidb.dbsize, CNCL_COMMAND_TYPE, CND_COMMAND_TYPE_01) >= 0) {
			/* printer supports ivec */
			if (setopt[OPTINDEX(OPTBIDI)] & OPTBIT(OPTBIDI)) {
				/* cif does not need to add ivec command */
			} else {
				/* cif needs to add ivec command */
				lpbjf_optinfo->is_ivec = 1;
			}
		} else {
			/* printer does not support ivec */
		}
	}
	
	/* Ver.3.00 */
	if (formattype >= CND_FORMATTYPE_8){
		/* Confirm combination of MediaSupply and PaperSize */
		if ((confirm_return_code = CNCL_ConfirmSupplySize( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize)) == 1){
			/* SupplySize returned OK with these parameters */
		} else if (confirm_return_code == 0){
			/* SupplySize returned NG with these parameters */
			fprintf(stderr, "Error: inappropriate papersize selection\n");
			goto onError;
		} else {
			/* Internal error */
			fprintf(stderr, "Error: INTERNAL ERROR(%d)\n", __LINE__);
			goto onError;
		}
		
		/* Confirm combination of PaperSize and Duplex */
		if( duplex_support ){
			if ((confirm_return_code = CNCL_ConfirmSizeDuplex( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize)) == 1){
				/* SizeDuplex returned OK with these parameters */
			} else if (confirm_return_code == 0){
				/* SizeDuplex returned NG with these parameters */
				fprintf(stderr, "Error: inappropriate duplex selection\n");
				goto onError;
			} else {
				/* Internal error */
				fprintf(stderr, "Error: INTERNAL ERROR(%d)\n", __LINE__);
				goto onError;
			}
		}
	}

	/* Prepare bjdevice structure, to handover main routine */
	bjdevice->bjfltModelID			= uidb.ModelID;
	bjdevice->bjfltMediaType		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIATYPE);
	bjdevice->bjfltPrintQuality 	= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_PRINTQUALITY);
	bjdevice->bjfltMediaSupply		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_MEDIASUPPLY);

	/* Convert "frontplain" to "asf" or "front" */
	if ( change_paperload ) {
		if( ( bjdevice->bjfltMediaType == CND_MEDIA_PLAIN ) && 
			( ( bjdevice->bjfltPaperSize == CND_SIZE_A4 ) || ( bjdevice->bjfltPaperSize == CND_SIZE_LETTER ) || ( bjdevice->bjfltPaperSize == CND_SIZE_B5 ) ) )
		{
			bjdevice->bjfltMediaSupply = CND_SUPPLY_CASSETTE_04;
		}
	}


	bjdevice->bjfltPaperGap			= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_PAPERGAP_COMMAND);
	if( bjdevice->bjfltPaperGap == -1 ) bjdevice->bjfltPaperGap = CND_PGAP_CMD_NA;

	/* bjdevice->bjfltPaperSize is set already. */
	/*bjdevice->bjfltPaperSize		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_PAPERSIZE);*/
	
	bjdevice->bjfltBinMethod		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_DITHER_PAT);
	if ( bjdevice->bjfltBinMethod == CND_UIBIN_PATTERN_HS  )
		bjdevice->bjfltBinMethod = CND_UIBIN_PATTERN;
		
	bjdevice->bjfltBanner			= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_BANNER);
	bjdevice->bjfltInkType			= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_CARTRIDGE);
	bjdevice->bjfltGrayScale		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_GRAYSCALE);

	bjdevice->bjfltMarginType		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_MARGINTYPE);
	if( bjdevice->bjfltMarginType == -1 ) bjdevice->bjfltMarginType = CND_MARGIN_NORMAL;
	
	bjdevice->bjfltDuplex		= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_DUPLEX_PRINTING);
	if( bjdevice->bjfltDuplex == -1 ) bjdevice->bjfltDuplex = CND_DUPLEX_OFF;	/* for models not support duplex */
	
	bjdevice->bjfltInkcartridgesettings	= GetCurrentnValue(uidb.lpdbTop, uidb.dbsize, CNCL_INKCARTRIDGESETTINGS);
	if( bjdevice->bjfltInkcartridgesettings == -1 ) bjdevice->bjfltInkcartridgesettings = CND_CARTRIDGE_NA;	/* for models not support inkcartridgesettings */


	/* then prepare BJCOLORSYSTEM structure */
	*bjcolor = uidb.bjcolor;

	ret = 0;

Exit:
	if (uidb.lpdbTop)
		free(uidb.lpdbTop);
	return ret;

onErrorHelp:
	ret = -1;
	goto Exit;

onError:
	ret = -2;
	goto Exit;

onErrorMessage:
	goto Exit;

}

void init_optioninfo( LPBJF_OPTINFO lpbjfoption )
{
	/* init option parameter */
	lpbjfoption->location = LOCATION_UPPERLEFT;
	lpbjfoption->stdswitch = 0;
	lpbjfoption->imageres = 0;
	lpbjfoption->modelid = 0;
	lpbjfoption->extension = -1;
	lpbjfoption->fit = FIT_OFF;
	lpbjfoption->bbox.bbox_flag = BBOX_OFF;
	lpbjfoption->percent = 0;
	lpbjfoption->copies = 1;
	lpbjfoption->revprint = REVPRINT_OFF;
	lpbjfoption->collate = COLLATE_OFF;
	lpbjfoption->stapleside = STAPLESIDE_LONG;
	
}



/*-------------------------------------------------------------*/
/* make  modelname, confname                                   */
/*          modelname = ip4200                                 */
/*          confname = /usr/lib/bjlib/cifip4200.conf etc       */
/*-------------------------------------------------------------*/
void MakeModelnameConfname( char *argv0, char *modelname, char *confname, char *path, char *extname )
{
	static char		bjfilter_path[] = "cif";
	char			small_modelname[256],tmpconfilename[256],confilename[256];
	short			bjfiltstrlen = strlen(bjfilter_path);
	short			argv0strlen = strlen(argv0);
	short			i,count;

	if( ( argv0strlen - bjfiltstrlen ) > sizeof(small_modelname)  )
		argv0strlen = sizeof(small_modelname) + bjfiltstrlen -1;

	for( count=argv0strlen; count>0; count-- ){
		if( argv0[count-1] == '/' )
			break;
	}

	for( i=0; i<sizeof(small_modelname); i++)	small_modelname[i] = '\0';

	for( i=0; i<(short)(argv0strlen - count - bjfiltstrlen); i++ )
		small_modelname[i] = (char)(argv0[count + bjfiltstrlen + i]);

	/* modelname = ip4200 etc.. */
	for( i=0; i<sizeof(small_modelname); i++)
		modelname[i] = toupper(small_modelname[i]);

	/* confname = /usr/lib/bjlib/cifip4200.conf etc.. */
	snprintf(tmpconfilename,sizeof(tmpconfilename), "%s%s",path,small_modelname);
	snprintf(confname, 256,"%s%s",tmpconfilename, extname);

}


/*-------------------------------------------------------------*/
/* Check option settings and change settings if necessary.     */
/*-------------------------------------------------------------*/
short CheckSettings( LPBJFLTDEVICE bjdevice , char *confname )
{
	UIDB			uidb;
	short			result = -1;


	uidb.lpdbTop = NULL;

	/* Retrieve Name Information */
	if ( CNCL_GetDBName( &uidb.nominfo, (void *) &bjlibdir, bjdevice->bjfltModelID ) < 0) {
			fprintf(stderr, "Error: Internal Database Name Error\n");
			goto onError;
	}

	/* Allocate Internal DB Area */
	uidb.dbsize = CNCL_GetDBSize( &uidb.nominfo, (void *)bjlibdir);
	uidb.lpdbTop = (LPCNCLDB)malloc(sizeof(CNCLDB) * uidb.dbsize);
	uidb.ModelID = bjdevice->bjfltModelID;

	/* Check errors. */
	if ( CNCL_GetEntries( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop) < 0) {
			fprintf(stderr, "Error: CNCL_GetEntries\n");
			goto onError;
	}
	if ( CNCL_GetDefaults( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize) < 0) {
			fprintf(stderr, "Error: CNCL_GetDefaults\n");
			goto onError;
	}

	/* Ver.2.90 */
	if( formattype < 0 )
	{
		if( (formattype = CNCL_GetTableFormatType( &uidb.nominfo, (void *)bjlibdir )) <0 ){
			fprintf(stderr, "Error: INTERNAL ERROR(%d)\n", __LINE__);
			/* inappropriate selection error. */
			goto onError;
		}
	}

	/* Check inkcartridgesettings and change settings if necessary. */
	if ( bjdevice->bjfltInkcartridgesettings == CND_CARTRIDGE_BK){
		if (formattype >= CND_FORMATTYPE_10){
			if( SetCurrentFlag( uidb.lpdbTop, uidb.dbsize, CNCL_INKCARTRIDGESETTINGS, bjdevice->bjfltInkcartridgesettings) < 0) {
				fprintf(stderr, "Error: INTERNAL ERROR(%d)\n", __LINE__);
				goto onError;
			}
			
			if( SetCurrentFlag( uidb.lpdbTop, uidb.dbsize, CNCL_MEDIATYPE, bjdevice->bjfltMediaType) < 0) {
				fprintf(stderr, "Error: INTERNAL ERROR(%d)\n", __LINE__);
				goto onError;
			}
			
			if( SetCurrentFlag( uidb.lpdbTop, uidb.dbsize, CNCL_MARGINTYPE, bjdevice->bjfltMarginType) < 0) {
				fprintf(stderr, "Error: INTERNAL ERROR(%d)\n", __LINE__);
				goto onError;
			}
			
			short result = CNCL_ConfirmCartrigeMediaMinus( &uidb.nominfo, (void *)bjlibdir, uidb.lpdbTop, uidb.dbsize);
			if (result == 0){
				// not supports BK (changes to default value)
				bjdevice->bjfltInkcartridgesettings = GetDefaultnValue(uidb.lpdbTop, uidb.dbsize, CNCL_INKCARTRIDGESETTINGS);
			} else if (result == 1) {
				// supports BK
			} else {
				fprintf(stderr, "Error: INTERNAL ERROR(%d)\n", __LINE__);
				goto onError;
			}
		} else if (formattype >= CND_FORMATTYPE_9){
			/* Supports Plain Paper, Hagaki, HagakiA and Envelope */
			if( ( bjdevice->bjfltMediaType != CND_MEDIA_PLAIN && bjdevice->bjfltMediaType != CND_MEDIA_POSTCARD && bjdevice->bjfltMediaType != CND_MEDIA_ADDRESS_POSTCARD && bjdevice->bjfltMediaType != CND_MEDIA_ENVELOPE) || ( bjdevice->bjfltMarginType == CND_MARGIN_MINUS ) ){
				bjdevice->bjfltInkcartridgesettings = GetDefaultnValue(uidb.lpdbTop, uidb.dbsize, CNCL_INKCARTRIDGESETTINGS);
			}
		} else if (formattype >= CND_FORMATTYPE_7){
			/* Supports Plain Paper, Hagaki and Envelope */
			if( ( bjdevice->bjfltMediaType != CND_MEDIA_PLAIN && bjdevice->bjfltMediaType != CND_MEDIA_POSTCARD && bjdevice->bjfltMediaType != CND_MEDIA_ENVELOPE) || ( bjdevice->bjfltMarginType == CND_MARGIN_MINUS ) ){
				bjdevice->bjfltInkcartridgesettings = GetDefaultnValue(uidb.lpdbTop, uidb.dbsize, CNCL_INKCARTRIDGESETTINGS);
			}
		} else {
			/* Supports Plain Paper */
			if( ( bjdevice->bjfltMediaType != CND_MEDIA_PLAIN ) || ( bjdevice->bjfltMarginType == CND_MARGIN_MINUS ) ){
				bjdevice->bjfltInkcartridgesettings = GetDefaultnValue(uidb.lpdbTop, uidb.dbsize, CNCL_INKCARTRIDGESETTINGS);
			}
		}
	}
	
	/* Check mismatch between fineart media and size */
	/* for Ver.3.80 fineartsize spec change */
	if( bjdevice->bjfltModelID >= CND_MG6300 ){
		if ( bjdevice->bjfltMediaType == CND_MEDIA_OTHER_FINE_ART_PAPER ){
			if (( bjdevice->bjfltPaperSize != CND_SIZE_A4_ART_35_2 ) && ( bjdevice->bjfltPaperSize != CND_SIZE_LETTER_ART_35_2 )){
				fprintf(stderr, "Error: You cannot print with following combination\n\tmedia: %s\n",
									bjf_get_resource_string( confname, OPTSTRMEDIA, bjdevice->bjfltMediaType ));
				fprintf(stderr, "\tpapersize: %s\n",
									bjf_get_resource_string( confname, OPTSTRPSIZE, bjdevice->bjfltPaperSize ));
				goto onError;
			}
		}
	}
	
	/* to Ver.3.70 */
	else{
		if ( ( bjdevice->bjfltMediaType == CND_MEDIA_FINE_ART_PAPER ) || (  bjdevice->bjfltMediaType == CND_MEDIA_OTHER_FINE_ART_PAPER ) ){
			if (( bjdevice->bjfltPaperSize != CND_SIZE_A4_FINE_ART ) && ( bjdevice->bjfltPaperSize != CND_SIZE_LETTER_FINE_ART )){
				fprintf(stderr, "Error: You cannot print with following combination\n\tmedia: %s\n",
									bjf_get_resource_string( confname, OPTSTRMEDIA, bjdevice->bjfltMediaType ));
				fprintf(stderr, "\tpapersize: %s\n",
									bjf_get_resource_string( confname, OPTSTRPSIZE, bjdevice->bjfltPaperSize ));
				goto onError;
			}
		}
	
		if (( bjdevice->bjfltPaperSize == CND_SIZE_A4_FINE_ART ) || ( bjdevice->bjfltPaperSize == CND_SIZE_LETTER_FINE_ART )){
			if ( ( bjdevice->bjfltMediaType != CND_MEDIA_FINE_ART_PAPER ) && (  bjdevice->bjfltMediaType != CND_MEDIA_OTHER_FINE_ART_PAPER ) ){
				fprintf(stderr, "Error: You cannot print with following combination\n\tpapersize: %s\n",
									bjf_get_resource_string( confname, OPTSTRPSIZE, bjdevice->bjfltPaperSize ));
				fprintf(stderr, "\tmedia: %s\n",
									bjf_get_resource_string( confname, OPTSTRMEDIA, bjdevice->bjfltMediaType ));
				goto onError;
			}
		}
	}
	


	result = 0;

onError:
	if (uidb.lpdbTop){
		free(uidb.lpdbTop);
		uidb.lpdbTop = NULL;
	}

	return result;


}

/*-------------------------------------------------------------*/
/* Parse --bbox option                                         */
/*-------------------------------------------------------------*/
static short ParseBbox(char *bbox , LPBJF_OPTINFO lpbjf_optinfo)
{

	short			i=0,j=0;
	char			param[24];
	short			result=-1;
	
	
	if(!bbox) return result;
	
	do{
		j=0;

		while( (*bbox=='-') || ((*bbox>='0') && (*bbox<='9')) ){
			if(j > (sizeof(param)-1) ) return result;
			param[j]=*bbox++;
			j++;
		}

		if( (*bbox!=',') && (*bbox!='\0')){
			return result;
		}
		
		if( i > 3 ) return result;
		param[j]=0x00;
		lpbjf_optinfo->bbox.value[i] = atol(param);
		
		if( (lpbjf_optinfo->bbox.value[i]) < 0) return result;
		
		i++;
	}while( *bbox++ );
	
	if( i !=4 ) return result;
	
	return 0;
		
}


/*-------------------------------------------------------------*/
/* convert str to long value                                   */
/*-------------------------------------------------------------*/
static long convert_str_to_long(char *str)
{
	long	value = 0L;
	char	c;
	
	while(c = *str)
	{
		if(c < '0' || '9' < c)
			return -2; /* invalid value */
		
		value = value * 10 + ( c - '0' );
		str++;
	}
	return value;
}

