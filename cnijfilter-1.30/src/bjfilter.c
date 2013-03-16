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
#include <unistd.h>
#include <popt.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>

#include "cncl.h"
#include "cncldef.h"
#include "cnclucom.h"
#include "cncludef.h"
#include "bjfimage.h"
#include "bjfoption.h"
#include "bjfrcaccess.h"
#include "bjfpos.h"
#include "bjipc.h"
#include "bjfilter.h"
#include "uitypes.h"

/* function prototypes */
extern short GetIPCData(LPIPCU pipc, char *sname);

/* local function prototypes */
static short h_extend( CPKByte CPKPTR, CPKByte CPKPTR, int, int, int );
static void outCmd(CPKByte CPKPTR, CPKUInt32, int);
static CPKBoolean whiteLine( CPKByte CPKPTR, CPKUInt32, CPKUInt32, CPKUInt32 CPKPTR, CPKUInt32 CPKPTR );
static void set_cncl_modelIDinfo( CNCLPtr, short ); 
static void set_cncl_timeinfo(  CNCLPtr );
static void set_cncl_imginfo( CNCLPtr, long, long, short, short );
static void set_cncl_printerinfo( CNCLPtr, LPBJFLTDEVICE, LPCNCLPAPERSIZE, LPBJFLTCOMSYSTEM );
static void set_position_parameter( LPBJFILTERINFO, LPCNCLPAPERSIZE, LPBJFLTCOMSYSTEM );
static void set_cncl_colorinfo( CNCLPtr, LPBJFLTCOLORSYSTEM ); 
static void check_lgmon_status(LPBJFILTERINFO, char *, char *);
static short MakeBJPrintData( LPBJFILTERINFO, LPBJFLTDEVICE, LPCNCLPAPERSIZE, LPBJFLTCOLORSYSTEM );
static short mirror_raster( CPKByte CPKPTR, long, short );
/* testprint function */
#if DEBUG
static void display_cncl_printerinfo( CNCLPtr );
static void display_position_parameter( LPBJFILTERINFO,  LPCNCLPAPERSIZE );
static void display_pos_info( LPBJF_POSINFO );
#endif

volatile int ReceiveSignal = 0;
volatile int WriteData = 0;

void Usr1Handler(int signum)
{
	ReceiveSignal = 1;
}


/*-------------------------------------------------------------*/
/* main                                                        */
/*-------------------------------------------------------------*/
int main( int argc, char *argv[] )
{
	OPT					opt;
	poptContext			optcon; 
	BJFLTDEVICE			bjfltdevice;
	CNCLPAPERSIZE   	cnclpapersize;
	BJFLTCOLORSYSTEM	bjfltcolor;
	LPBJFILTERINFO		lpbjinfo = NULL;
	IPCU				ipc;
	short				isprint = 0;
	short				ret;
	char				socketname[256];
	char				dispname[256];
	char				modelname[256];
	char				*tmpargv[] = { PRINTUIPATH, "--display", dispname, "-s", socketname, "--model", modelname, NULL};
	struct sigaction	sigact;

	struct poptOption optionsTable[] = {
		{ OPTSTRGUI, 			'u',	POPT_ARG_NONE,		&opt.gui,				'u' 		},
		{ OPTSTRLOCATION, 		'l',	POPT_ARG_STRING,	&opt.location,			OPTLOCATION },
		{ OPTSTRMODEL, 			'M',	POPT_ARG_STRING,	&opt.model,				OPTMODEL	},
		{ OPTSTRCARTRIDGE,		'c',	POPT_ARG_STRING,	&opt.cartridge,			OPTCARTRIDGE},
		{ OPTSTRMEDIA,			'm',	POPT_ARG_STRING,	&opt.media,				OPTMEDIA	},
		{ OPTSTRQUALITY,		'q',	POPT_ARG_STRING,	&opt.quality,			OPTQUALITY	},
		{ OPTSTRGRAY,			'G',	POPT_ARG_NONE,		&opt.grayscale,			OPTGRAY		},
		{ OPTSTRHALFTONE, 		'H',	POPT_ARG_STRING,	&opt.halftoning,		OPTHALFTONE	},
		{ OPTSTRBANNER,			'b',	POPT_ARG_NONE,		&opt.banner,			OPTBANNER	},
		{ OPTSTRLOAD,			'L',	POPT_ARG_STRING,	&opt.paperload,			OPTLOAD		},
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
		/*   to support 1.) add a switch --lgmon to invoke Language monitor (and output data thru a pipe). */
		/*              2.) add an option --imageres, to cover with the bug in the bmp filter in           */
		/*                  previous version of ghostscript. (lacking image resolution information)        */
		/*              3.) add --display, to specify X server to show printui/stamon                      */
		{ OPTSTRLGMON,			0,		POPT_ARG_NONE,		&opt.lgmon,				OPTLGMON	},
		{ OPTSTRIMGRES,			0,		POPT_ARG_INT,		&opt.imageres,			OPTIMGRES	},
		{ OPTSTRDISPLAY,		0,		POPT_ARG_STRING,	&opt.display,			OPTDISPLAY	},
		{ OPTSTRFIT,            'F',    POPT_ARG_NONE,      &opt.fit,               OPTFIT      },
		{ OPTSTRINTVER,         0,      POPT_ARG_NONE,      &opt.internalversion,   OPTINTVER   },
		{ NULL,					0,		0,					NULL,					0 			}
	};


	/* allocate new work area */
	if ( (lpbjinfo = (LPBJFILTERINFO)malloc( sizeof(BJFILTERINFO) )) == NULL ) goto onErr;
	
	/* init bjinfo */
	memset( (LPBJFILTERINFO)lpbjinfo, 0, sizeof(BJFILTERINFO) );

	/* init signal action structure, then assign signal handler. */
	memset(&sigact, 0, sizeof(sigact));
	sigact.sa_handler = Usr1Handler;
	if (sigaction(SIGUSR1, &sigact, NULL)) perror("sigaction");

	snprintf(socketname, sizeof(socketname), "%s%d",BJSOCKET,getpid());


	/*---------
		Analyze command line options.
	---------*/
	init_optioninfo( &lpbjinfo->bjfoption );
	
	/* optcon = poptGetContext( "bjfilter", argc, argv, optionsTable, 0 ); */
	optcon = poptGetContext( "bjfilter", argc, (const char **)argv, optionsTable, 0 );
	
	if ( cmdlinesw( &optcon, &opt, &lpbjinfo->bjfoption, &bjfltcolor, &bjfltdevice,
			&cnclpapersize, dispname, lpbjinfo->filename ) < 0 ){
		usage();
		poptFreeContext( optcon );
		goto onErr;
	}
	
	poptFreeContext( optcon );

	/* prepare communication pipe between lgmon & bjfilter */
	if ( lpbjinfo->bjfoption.lgmon == ON ) {
		/* open pipe */
		if ( pipe( lpbjinfo->pipefds ) ) {
			fprintf(stderr, "bjfilter: pipe failed\n");
			goto onErr;
		}

		/* then prepare for file pointer */
		lpbjinfo->prn = lpbjinfo->pipefds[1];
	}
	else
		lpbjinfo->prn = 1;
#if 0
	if (strcpy(modelname, convID2Name(lpbjinfo->bjfoption.modelid, (NOMID *)nomidTable)) == 0) {
		fprintf(stderr, "bjfilter: invalid modelid - internal error\n");
		goto onErr;
	}
#endif
	if ( strcpy(modelname, bjf_get_resource_string( BJFILTERRCPATH, 
						OPTSTRMODEL, lpbjinfo->bjfoption.modelid)) == 0) {
		fprintf(stderr, "bjfilter: invalid modelid - internal error\n");
		goto onErr;
	}

	isprint = 0;
	if ( lpbjinfo->bjfoption.ui == ON ){				/* UI command mode */
		/* make new process */
		/* pid = fork(); */
		lpbjinfo->pid_printui = fork();
		
		if ( lpbjinfo->pid_printui == 0 ){
			if ( execv( PRINTUIPATH, tmpargv ) ) {
				perror("invoke printui:");
				goto onErr;
			}
		}
		else{
			while( 1 ){
				/* communicate to PrintUI Program */
				ret = GetIPCData( &ipc , socketname );

				if ( ret == RET_PRINT ){
					check_lgmon_status(lpbjinfo, dispname, modelname);
					/* copy data from ui */
					bjfltdevice = ipc.parm.bjfltdev;
					cnclpapersize = ipc.parm.papersize;
					bjfltcolor = ipc.parm.bjfltcolor;
					isprint = 1;
					break;
				}
				else if ( ret == RET_CANCEL ){
					break;
				}
				else if ( ret == RET_PDATA ){
					check_lgmon_status(lpbjinfo, dispname, modelname);
					outCmd( (CPKByte CPKPTR)ipc.cmds.cmds, (CPKUInt32)ipc.cmds.cmdslen, lpbjinfo->prn );
				}
				else if ( ret == RET_EXECLM ){
					check_lgmon_status(lpbjinfo, dispname, modelname);
				}
				else if ( ret == RET_ERROR ){
					break;
				}
				else{
					fprintf( stderr, "GetIPCData return value Error\n" );
					goto onErr;
				}
			}
		}
	}
	else{												/* command line mode */
		isprint = 1;
	}

	/* error check */
	if ( isprint == 0 ) goto onErr;

	/* Make Printing Data */
	if ( MakeBJPrintData( lpbjinfo, &bjfltdevice, &cnclpapersize, &bjfltcolor ) < 0 ){
		fprintf( stderr, "Err in MakeBJPrintData!\n" );	
		goto onErr;
	}

onErr:

	/* and at last, send quitting SIGNAL to lgmon */
	if (lpbjinfo->pid_lgmon != 0) {
		int *status = 0;
		int sigcode;

		if( isprint && WriteData )
			sigcode = SIGUSR1;	/* Cancel in printing		*/
		else
			sigcode = SIGTERM;	/* Cancel before printing	*/

		kill(lpbjinfo->pid_lgmon, sigcode);			/* Send signal to lgmon */
		/* 20001005 tora, modified to here */

		waitpid(lpbjinfo->pid_lgmon, status, 0);	/* wait until lgmon is terminated */
	}

	if (lpbjinfo->bjfoption.lgmon == ON)
		close(lpbjinfo->prn);

	if ( lpbjinfo ) free( lpbjinfo );
	
	return 0;
}


static short MakeBJPrintData
(
	LPBJFILTERINFO		lpbjinfo,
	LPBJFLTDEVICE		lpbjfltdevice,
	LPCNCLPAPERSIZE		lpcnclpapersize,
	LPBJFLTCOLORSYSTEM	lpbjfltcolor
)
{
	CNCLData			CnclData;
	CNCLErr				cnclerr = -1;
	CPKByte CPKPTR		rgbBuf = CPKNULL;
	CPKByte CPKPTR		srcBuf = CPKNULL;
	long				width, height;
	long				width_offset, height_offset;
	long				ImageWidth, ImageHeight;
	long				leftskip, topskip;
	long				y;
	long				left=0, right=0;
	long				Rest, TotalRest, PrevPos, CurrPos, Quotient;
	long				restLines, tmpRestLines;
	long				page_width;
	long				i,h;
	short				bpp;
	
	CNCLNAMEINFO		cnclnameinfo;
	BJFLTCOMSYSTEM		bjfltcom;
	char 				tblPath[] = "/usr/lib/bjlib";


	/****** CNCLInit ******/
	memset( (CNCLData CPKPTR)&CnclData, 0, sizeof(CNCLData) );
	if ( (cnclerr = CNCL_Init( &CnclData )) != CNCL_OK ) goto finish1;

	CnclData.Work1Buf = (CPKVoid CPKPTR)malloc( CnclData.Work1Size );
	if ( CnclData.Work1Buf == CPKNULL ) goto finish1;
	memset( (CPKVoid CPKPTR)CnclData.Work1Buf, 0, CnclData.Work1Size );

	/* Set Infomation ( MODELID ) */
	set_cncl_modelIDinfo( &CnclData, lpbjfltdevice->bjfltModelID );
	
	/* Set Infomation ( Date, Time ) */
	set_cncl_timeinfo( &CnclData );


	/****** CNCL Startjob ******/
	if ( (cnclerr = CNCL_StartJob( &CnclData )) != CNCL_OK ) goto finish1;
	outCmd( CnclData.outputBuffer, CnclData.outputSize, lpbjinfo->prn );

	/*--- 
		Input Image open. 
		we deal width only ppm image format as stdin.
	---*/
	if ( lpbjinfo->bjfoption.stdswitch == ON ){
		if ( bjf_image_open( &lpbjinfo->bjfimage, NULL ) < 0 ) goto finish2;

	}else{
		if ( bjf_image_open( &lpbjinfo->bjfimage, lpbjinfo->filename ) < 0 ) goto finish2;
	}

	/*---
		Get DataBaseName, and BJFLTCOM structure, which has printer infomation( wMediaType,
			wPrintQuality, wSmoothing etc...
	---*/
	memset( (char *)&cnclnameinfo, 0, sizeof(CNCLNAMEINFO) );
	memset( (char *)&bjfltcom, 0, sizeof(BJFLTCOMSYSTEM) );

	cnclerr = CNCL_GetDBName( &cnclnameinfo, (void *)tblPath, lpbjfltdevice->bjfltModelID );
	if( cnclerr < 0 ) goto finish3;

	cnclerr = CNCL_GetComSystem( &cnclnameinfo, (void *)tblPath, lpbjfltdevice, &bjfltcom );
	if( cnclerr < 0 ) goto finish3;


	/********************************************************************Make Printing Data */

	while ( (cnclerr = bjf_image_init( &lpbjinfo->bjfimage )) > 0 ) {

		/*---
			copy RGB image data to bjfposimg and bjfposprn
		---*/
		set_position_parameter( lpbjinfo, lpcnclpapersize, &bjfltcom );

		/*---------
			if fit option is selected, output image is fit for current media size
				if not, output image is fit for size reached by using resolution of its image
		---------*/
		if ( lpbjinfo->bjfoption.fit == ON ){
			if ( bjf_pos_imageresolution_fit( &lpbjinfo->bjfposimg,
				&lpbjinfo->bjfposprn, &lpbjinfo->bjfposinfo ) < 0 ) goto finish3;
		}
		else {
			if ( bjf_pos_imageresolution( &lpbjinfo->bjfposimg,
				&lpbjinfo->bjfposprn,&lpbjinfo->bjfposinfo ) < 0 ) goto finish3;
		}

		/*---------
			if center option is selected, two parameter is culcurated, these are leftskip and topskip
		---------*/
		if ( lpbjinfo->bjfoption.location == OPTLOC_CENTER ){
			if ( bjf_pos_imageresolution_center( &lpbjinfo->bjfposimg,
				&lpbjinfo->bjfposprn, &lpbjinfo->bjfposinfo ) < 0 ) goto finish3;
		}


		/*---------
			get scaling parameter which bjfilter needs.
		---------*/
		width = 0;			height = 0;
		width_offset = 0;	height_offset = 0;
		ImageWidth = 0;		ImageHeight = 0;
		leftskip = 0;		topskip = 0;
		page_width = 0;
	
		bjf_pos_mask_width( &lpbjinfo->bjfposinfo, &width );
		bjf_pos_mask_height( &lpbjinfo->bjfposinfo, &height );
		bjf_pos_width_offset( &lpbjinfo->bjfposinfo, &width_offset );
		bjf_pos_height_offset( &lpbjinfo->bjfposinfo, &height_offset );
		bjf_pos_out_width( &lpbjinfo->bjfposinfo, &ImageWidth );
		bjf_pos_out_height( &lpbjinfo->bjfposinfo, &ImageHeight );
		bjf_pos_leftskip( &lpbjinfo->bjfposinfo, &leftskip );
		bjf_pos_topskip( &lpbjinfo->bjfposinfo, &topskip );
		bjf_pos_page_width ( &lpbjinfo->bjfposinfo, &page_width );

		/*---
			get bytes per pixel
		---*/
		bpp = 0;
		bjf_image_get_bpp( &lpbjinfo->bjfimage, &bpp );				/* Byte per Pixel of original Image */
		
		/*---
			set cncl_parameter
		---*/
		/* Set Infomation ( width, length, srcdataType, pageno, bpp ) */
		set_cncl_imginfo( &CnclData, page_width, ImageHeight, CND_ST_RGB24, 1 );
		
		/* Set Infomation ( with BJCOMMON STRUCTRE ) */
		set_cncl_printerinfo( &CnclData, lpbjfltdevice, lpcnclpapersize, &bjfltcom ); 
	
		/* Set Infomation ( with COLOR STRUCTRE ) */
		set_cncl_colorinfo( &CnclData, lpbjfltcolor );

		/* raster data before scaling */
		if ( srcBuf == CPKNULL ){
			srcBuf = (CPKByte CPKPTR)malloc( width * bpp );	
		}
		if ( srcBuf == CPKNULL ) goto onErr; 

		/* raster data after scalign */
		if ( rgbBuf == CPKNULL ) {
			rgbBuf = (CPKByte CPKPTR)malloc( page_width * bpp );
		}
		if ( rgbBuf == CPKNULL ) goto onErr;
		memset( rgbBuf, 0xFF, page_width * bpp );

#if DEBUG 
		/* display parameters */	
		display_position_parameter( lpbjinfo, lpcnclpapersize );
		display_cncl_printerinfo( &CnclData );
		display_pos_info( &lpbjinfo->bjfposinfo );
#endif
		
		/****** CNCL Set param ******/
		if ( (cnclerr = CNCL_SetParam( &CnclData )) != CNCL_OK ){
#if DEBUG
			fprintf( stderr, "Error: CNCL_SetParam\n" );
#endif
			goto onErr;
		}
		
		/* Alloc work2 buf */
		if ( CnclData.Work2Buf == CPKNULL ){
			CnclData.Work2Buf = (CPKVoid CPKPTR)malloc( CnclData.Work2Size );
		}	
		if ( CnclData.Work2Buf == CPKNULL ) goto onErr;
	
	
		/****** CNCL Start page ******/
		if ( (cnclerr = CNCL_StartPage( &CnclData )) != CNCL_OK ) goto onErr;
		outCmd( CnclData.outputBuffer, CnclData.outputSize, lpbjinfo->prn );


		/*---
			if topskip is, increase Vposition
		---*/
		if ( topskip ){
			CnclData.Vpos    = topskip;
			CnclData.length += topskip;
		}
				
		/*---
			data roop
		---*/
		CnclData.inputBuffer = rgbBuf ;
		CnclData.srcdatatype = CND_ST_RGB24 ;
		CnclData.left_white  = 0 ;
		CnclData.right_white = 0 ;

		/* set scaling parameter */
		Quotient  = height / ImageHeight;
		Rest 	  = height % ImageHeight;
		TotalRest = 0;
		PrevPos   = -1;
		CurrPos   = 0;

		for ( y=0; y<ImageHeight; y++ ){

#if DEBUG
			fprintf( stderr, "y:%ld\tCurrPos:%ld\r",y,CurrPos );
#endif	

			if (ReceiveSignal == 1)									/* Abort from lgmon */
				goto onErr;

			if ( CurrPos != PrevPos ){
				PrevPos = CurrPos;
				if ( bjf_image_read_raster( &lpbjinfo->bjfimage, (char *)srcBuf, (long)width_offset, 
							(long)(CurrPos + height_offset), (long)width ) < 0 ){
					fprintf( stderr, "err in bjf_image_read_raster\n" );	
					goto onErr;
				}
								
				memset( rgbBuf, 0xFF, page_width * bpp );
				if ( h_extend( srcBuf, rgbBuf+(leftskip*bpp), width, ImageWidth, bpp ) < 0 ) goto onErr;

				/*---
					if Media is BackPrintFilm and Thirts, mirror raster
				---*/
				switch ( lpbjfltdevice->bjfltMediaType ){
					case CND_MEDIA_BPF:
					case CND_MEDIA_TSHIRT:
						mirror_raster( rgbBuf, page_width, bpp );
						break;	
				} 

			}
			
			/* Check white line */
			if ( whiteLine( rgbBuf, CnclData.width*bpp, bpp, (CPKUInt32 *)&left, (CPKUInt32 *)&right ) ){
				CnclData.WhiteLine = CND_WL_WHITE;
				CnclData.left_white = left;
				CnclData.right_white = right;
			}
			else{
				CnclData.WhiteLine = CND_WL_NOTWHITE;
				CnclData.left_white = left;
				CnclData.right_white = right;
			}
		
			/****** CNCL Source data ******/
			restLines = CNCL_SourceData( &CnclData );
			if ( restLines < 0 ){
				goto onErr;
			}
			else if ( restLines == 0 ){
				goto next;
			}

			for ( h=0; h<restLines; h++ ){
				/****** CNCL Raster data ******/
				tmpRestLines = CNCL_RasterData( &CnclData );
				if ( tmpRestLines < 0 ) goto onErr;

				for ( i=0; i<CnclData.numBuf; i++ ){
					//use rasterDataPtr.	2000/12/09
					outCmd( CnclData.rasterDataPtr[i].buf, CnclData.rasterDataPtr[i].size, lpbjinfo->prn );
					//outCmd( CnclData.RasterDatas[i].buf, CnclData.RasterDatas[i].size, lpbjinfo->prn );
				}
			
				/****** CNCL Complete data ******/
				if ( (cnclerr = CNCL_CompleteData( &CnclData)) != CNCL_OK ) goto onErr;
			}
next:
			CnclData.Vpos += 1 ;

			TotalRest += Rest;
			CurrPos += Quotient;
			
			if ( TotalRest >= ImageHeight ){
				TotalRest -= ImageHeight;
				CurrPos++;
			}
		}

		/*--- Flush ---*/
		/* CNCL flush data */
		restLines = 1;
		do {
			/****** Data out ******/
			restLines = CNCL_FlushData( &CnclData );
			if ( restLines < 0 ) goto onErr;

			/*--- Data ---*/
			for ( i=0; i<CnclData.numBuf; i++ ){
				//use rasterDataPtr.	2000/12/09
				outCmd( CnclData.rasterDataPtr[i].buf, CnclData.rasterDataPtr[i].size, lpbjinfo->prn );
				//outCmd( CnclData.RasterDatas[i].buf, CnclData.RasterDatas[i].size, lpbjinfo->prn );
			}
		
			/****** CNCL Complete data ******/
			if ( (cnclerr = CNCL_CompleteData( &CnclData )) != CNCL_OK ) goto onErr;
			outCmd( CnclData.outputBuffer, CnclData.outputSize, lpbjinfo->prn );

			CnclData.PageNum += 1;
		}while( restLines );

		/*--- flush image ---*/
		bjf_image_flush( &lpbjinfo->bjfimage ); 
			
		/****** CNCL End page ******/
		if ( (cnclerr = CNCL_EndPage( &CnclData )) != CNCL_OK ) goto onErr;
		outCmd( CnclData.outputBuffer, CnclData.outputSize, lpbjinfo->prn );

		CnclData.PageNum += 1;
	}

	if ( cnclerr < 0 ) goto onErr;
	
	cnclerr = 0;

onErr:
	if ( CnclData.Work2Buf ) free( CnclData.Work2Buf );
	if ( rgbBuf ) free( rgbBuf );
	if ( srcBuf ) free( srcBuf );

finish3:
	/*---close image---*/
	bjf_image_close( &lpbjinfo->bjfimage );

finish2:
	/****** CNCL End job ******/
	if ( (cnclerr = CNCL_EndJob( &CnclData )) == CNCL_OK ) {
		outCmd( CnclData.outputBuffer, CnclData.outputSize, lpbjinfo->prn );
	}

finish1:	
	if ( CnclData.Work1Buf ) free( CnclData.Work1Buf );

	return cnclerr; 
}



/*-------------------------------------------------------------*/
/* externd raster data for horizon                             */
/*-------------------------------------------------------------*/
static short h_extend( 
					CPKByte CPKPTR		in,
					CPKByte CPKPTR		out,
					int			src_width,
					int			dst_width,
					int			component 
				)
{
	int Quotient;
	int	Rest;
	int	TotalRest;
	int PrevPos;
	int CurrPos;
	int	x;
	unsigned char K,Y,M,C,y,m,c;
	CPKByte CPKPTR src_in;
	short result = -1;
	
	src_in = in;

	K = Y = M = C = y = m = c = 0;	
	Quotient  = src_width / dst_width;
	Rest      = src_width % dst_width;
	TotalRest = 0;
	PrevPos   = -1;
	CurrPos   = 0;
	
	for ( x=0; x<dst_width; x++ ){
		
		if ( CurrPos != PrevPos ){
			PrevPos = CurrPos;
			src_in = in + ( component * CurrPos );

			switch ( component ){
				case 1:
					K = src_in[0];
					break;
				case 3:
					Y = src_in[0]; M = src_in[1];
					C = src_in[2];
					break;
				case 4:
					K = src_in[0]; Y = src_in[1];
					M = src_in[2]; C = src_in[3];
					break;
				case 6:
					K = src_in[0]; Y = src_in[1];
					M = src_in[2]; C = src_in[3];
					m = src_in[4]; c = src_in[5];
					break;
				case 7:
					K = src_in[0]; Y = src_in[1];
					M = src_in[2]; C = src_in[3];
					y = src_in[4]; m = src_in[5]; c = src_in[6];
					break;
			}
		}
		
		switch ( component ){
			case 1:
				out[0] = K;
				break;
			case 3:
				out[0] = Y; out[1] = M; out[2] = C;
				break;
			case 4:
				out[0] = K; out[1] = Y; out[2] = M; out[3] = C;
				break;
			case 6:
				out[0] = K; out[1] = Y; out[2] = M;
				out[3] = C; out[4] = m; out[5] = c;
				break;
			case 7:
				out[0] = K; out[1] = Y; out[2] = M;
				out[3] = C; out[4] = y; out[5] = m; out[6] = c;
				break;
		}
		
		out += component;
		
		TotalRest += Rest;
		CurrPos += Quotient;
		
		if ( TotalRest >= dst_width ){
			TotalRest -= dst_width;
			CurrPos++;
		}
	}
	
	result = 0;
	return result;
}


/*-------------------------------------------------------------*/
/* outCmd                                                      */
/*-------------------------------------------------------------*/
static void
outCmd ( CPKByte CPKPTR buf, CPKUInt32 size, int prn )	/* to take file pointer */
{
	if ( size && !ReceiveSignal ) { 
		if( write ( prn, buf, size ) > 0 )
			WriteData = 1;
	}
	return ;
}



/*-------------------------------------------------------------*/
/* whiteLine                                                   */
/*-------------------------------------------------------------*/
static CPKBoolean
whiteLine ( CPKByte CPKPTR buf, CPKUInt32 size, CPKUInt32 bpp, CPKUInt32 CPKPTR left, CPKUInt32 CPKPTR right )
{
	CPKUInt32 i ;
	CPKUInt32 width = size / bpp ;
	CPKByte CPKPTR src = buf ;

	*left  = 0 ;
	*right = 0 ;
	/* Check from left */
	for ( i = 0 ; i < width ; i++, src += bpp )
	{
		if ( *src != 0xff || *(src+1) != 0xff || *(src+2) != 0xff )
		{
			*left = i ;
			goto from_right ;
		}
	}
	*left = width ;
	return CPKTrue ;

from_right :
	/* Check from right */
	src = buf + size - 1 ;
	for ( i = 0 ; i < width ; i++, src -= bpp )
	{
		if ( *src != 0xff || *(src-1) != 0xff || *(src-2) != 0xff )
		{
			*right = i ;
			break ;
		}
	}

	return CPKFalse ;
}



/*-------------------------------------------------------------*/
/* set cncl informations                                       */
/*-------------------------------------------------------------*/
static void set_cncl_modelIDinfo( CNCLPtr lpcncldata, short modelID )
{
	lpcncldata->ModelID = modelID;
}



static void set_cncl_timeinfo(  CNCLPtr lpcncldata )
{	
	char		time_para[7][20];
	char		time_buf[100];
	char		*ptr1 = NULL;
	char		*ptr2 = NULL;
	short		par = 0;
	short		mon;
	time_t		BJTime;
	static char month[][4] = {	"Dum", "Jan", "Feb", "Mar", "Apr",
								"May", "Jun", "Jul", "Aug", "Sep",
								"Oct", "Nov", "Dec" };
	/* get Time Info */
	time( &BJTime );
	strncpy( time_buf, ctime( &BJTime ), sizeof(time_buf) );
	time_buf[sizeof(time_buf) - 1] = '\0';

	ptr1 = time_para[par++];
	ptr2 = time_buf;
	while( *ptr2 != 0x0a ){
		*ptr1++ = *ptr2++;
		if ( (*ptr2 == ' ') || (*ptr2 == ':') ){
			*ptr1 = 0x00;
			ptr1 = time_para[par++];
			ptr2++;
		}
	}
	*ptr1 = 0x00;

	/* get Month */
	for ( mon=0; mon<13; mon++ ){
		if ( !strcmp( month[mon], time_para[1] )) break;
	}

	
	lpcncldata->CurrentTime.TimeInfo	= CND_TIME_CORRECT;
	lpcncldata->CurrentTime.Year		= atoi( time_para[6] );
	lpcncldata->CurrentTime.Month		= mon;
	lpcncldata->CurrentTime.Day			= atoi( time_para[2] );
	lpcncldata->CurrentTime.Hour		= atoi( time_para[3] );
	lpcncldata->CurrentTime.Min			= atoi( time_para[4] );
	lpcncldata->CurrentTime.Sec			= atoi( time_para[5] );
}



static void set_cncl_imginfo( CNCLPtr lpcncldata, long width, long length, short rgbtype, short page )
{
	lpcncldata->width		= width;
	lpcncldata->length		= length;
	lpcncldata->srcdatatype	= rgbtype;
	lpcncldata->PageNum		= 1;
}
  


static void set_cncl_printerinfo( CNCLPtr lpcncldata, LPBJFLTDEVICE lpbjfltdevice, LPCNCLPAPERSIZE lpcnclpapersize,LPBJFLTCOMSYSTEM lpbjfltcom )
{
	lpcncldata->InkType      = lpbjfltcom->bjfltInkCartridge;
	lpcncldata->MediaType    = lpbjfltdevice->bjfltMediaType;
	lpcncldata->PaperSize    = lpbjfltdevice->bjfltPaperSize;
	lpcncldata->MediaSupply  = lpbjfltdevice->bjfltMediaSupply;

	switch( lpbjfltdevice->bjfltBinMethod ){
		case CND_UIBIN_PATTERN:
		case CND_UIBIN_PATTERN_HS:
		case CND_UIBIN_V_PATTERN:
			lpcncldata->BinMethod		= CND_BIN_DITHER;
		break;

		case CND_UIBIN_ED:
			lpcncldata->BinMethod		= CND_BIN_ED;
		break;

		case CND_UIBIN_NA:
			lpcncldata->BinMethod		= CND_BIN_NA;
		break;

		case CND_UIBIN_MAX:
			lpcncldata->BinMethod		= CND_BIN_MAX;
		break;
	}

	lpcncldata->Grayscale    = lpbjfltdevice->bjfltGrayScale;
	lpcncldata->PrintQuality = lpbjfltdevice->bjfltPrintQuality;
	lpcncldata->Banner       = lpbjfltdevice->bjfltBanner;
	lpcncldata->PaperWidth   = lpcnclpapersize->nSelPaperWidth;
	lpcncldata->PaperHeight  = lpcnclpapersize->nSelPaperLength;
	lpcncldata->Smoothing    = CND_SMOOTH_NA ;
}



/*-------------------------------------------------------------*/
/* Set position parameters                                     */
/*-------------------------------------------------------------*/
static void set_position_parameter( LPBJFILTERINFO lpbjinfo, LPCNCLPAPERSIZE lpcnclpapersize, LPBJFLTCOMSYSTEM lpbjfcom )
{
	long	img_width, img_height;
	double	img_xres, img_yres;

	/* init positon parameter */
	bjf_pos_img_init( &lpbjinfo->bjfposimg );
	bjf_pos_prn_init( &lpbjinfo->bjfposprn );
	bjf_pos_init( &lpbjinfo->bjfposinfo );

	/* get original image parameter */
	bjf_image_get_width( &lpbjinfo->bjfimage, &img_width );
	bjf_image_get_length( &lpbjinfo->bjfimage, &img_height );
	bjf_image_get_resolution( &lpbjinfo->bjfimage, &img_xres, &img_yres );

	/* set original image parameter */
	bjf_pos_set_imgwidth( &lpbjinfo->bjfposimg,img_width );
	bjf_pos_set_imgheight( &lpbjinfo->bjfposimg,img_height );

	if ( lpbjinfo->bjfoption.imageres ){
		bjf_pos_set_imgXres( &lpbjinfo->bjfposimg, lpbjinfo->bjfoption.imageres );
		bjf_pos_set_imgYres( &lpbjinfo->bjfposimg, lpbjinfo->bjfoption.imageres );
	}
	else{
		/* set xresolution */
		if ( lpbjinfo->bjfimage.xresolution < XDEFAULTRESOLUTION ){
			bjf_pos_set_imgXres( &lpbjinfo->bjfposimg, XDEFAULTRESOLUTION );
		}
		else{
			bjf_pos_set_imgXres( &lpbjinfo->bjfposimg, lpbjinfo->bjfimage.xresolution );
		}

		/* set yresolution */
		if ( lpbjinfo->bjfimage.yresolution < YDEFAULTRESOLUTION ){
			bjf_pos_set_imgYres( &lpbjinfo->bjfposimg, YDEFAULTRESOLUTION );
		}
		else{	/* use xresolution */
			bjf_pos_set_imgYres( &lpbjinfo->bjfposimg, lpbjinfo->bjfimage.yresolution );
		}
	}
	/* set printer parameter */
	bjf_pos_set_prntopmargin( &lpbjinfo->bjfposprn,lpcnclpapersize->nTopMargin );
	bjf_pos_set_prnleftmargin( &lpbjinfo->bjfposprn, lpcnclpapersize->nLeftMargin );
	bjf_pos_set_prnXres( &lpbjinfo->bjfposprn, (double)lpbjfcom->bjfltInputHResolution  );
	bjf_pos_set_prnYres( &lpbjinfo->bjfposprn, (double)lpbjfcom->bjfltInputVResolution  );
	bjf_pos_set_prnwidth( &lpbjinfo->bjfposprn,lpcnclpapersize->nWidthPrintArea );
	bjf_pos_set_prnheight( &lpbjinfo->bjfposprn,lpcnclpapersize->nLengthPrintArea  );
} 

static void set_cncl_colorinfo( CNCLPtr lpcncldata, LPBJFLTCOLORSYSTEM lpbjfltcolor )
{
	lpcncldata->Intent		= lpbjfltcolor->bjfltIntent;
	lpcncldata->Gamma		= lpbjfltcolor->bjfltGamma;
	lpcncldata->BalanceC	= lpbjfltcolor->bjfltBalanceC;
	lpcncldata->BalanceM	= lpbjfltcolor->bjfltBalanceM;
	lpcncldata->BalanceY 	= lpbjfltcolor->bjfltBalanceY;
	lpcncldata->BalanceK	= lpbjfltcolor->bjfltBalanceK;
	lpcncldata->Density		= lpbjfltcolor->bjfltDensity;
}



/*-------------------------------------------------------------*/
/* display  informations                                       */
/*-------------------------------------------------------------*/
#if DEBUG
static void display_cncl_printerinfo( CNCLPtr lpcncldata )
{
	
	fprintf( stderr, "\n" );
	fprintf( stderr, "< Cncl Paramter >\n" );
	
	fprintf( stderr, "lpcncldata->ModelID:%d\n", lpcncldata->ModelID);
	fprintf( stderr, "lpcncldata->InkType:%d\n", lpcncldata->InkType);
	fprintf( stderr, "lpcncldata->MediaType:%d\n", lpcncldata->MediaType);
	fprintf( stderr, "lpcncldata->PaperSize:%d\n", lpcncldata->PaperSize);
	fprintf( stderr, "lpcncldata->MediaSupply:%d\n", lpcncldata->MediaSupply);
	fprintf( stderr, "lpcncldata->BinMethod:%d\n", lpcncldata->BinMethod);
	fprintf( stderr, "lpcncldata->Grayscale:%d\n", lpcncldata->Grayscale);
	fprintf( stderr, "lpcncldata->PrintQuality:%d\n", lpcncldata->PrintQuality);
	fprintf( stderr, "lpcncldata->Banner:%d\n", lpcncldata->Banner);
	fprintf( stderr, "lpcncldata->PaperWidth:%ld\n", lpcncldata->PaperWidth);
	fprintf( stderr, "lpcncldata->PaperHeight:%ld\n", lpcncldata->PaperHeight);
	
	fprintf( stderr, "lpcncldata->Intet:%d\n", lpcncldata->Intent);
	fprintf( stderr, "lpcncldata->Gamma:%d\n", lpcncldata->Gamma);
	fprintf( stderr, "lpcncldata->BalanceC:%d\n", lpcncldata->BalanceC);
	fprintf( stderr, "lpcncldata->BalanceM:%d\n", lpcncldata->BalanceM);
	fprintf( stderr, "lpcncldata->BalanceY:%d\n", lpcncldata->BalanceY);
	fprintf( stderr, "lpcncldata->BalanceK:%d\n", lpcncldata->BalanceK);
	fprintf( stderr, "lpcncldata->Density:%d\n", lpcncldata->Density);
}


static void display_position_parameter( LPBJFILTERINFO lpbjinfo, LPCNCLPAPERSIZE lpcnclpapersize )
{
	fprintf( stderr, "\n" );
	fprintf( stderr, "< Print Image Position Paramter >\n" );

	fprintf( stderr, "img_width:%ld\n", lpbjinfo->bjfposimg.img_width );
	fprintf( stderr, "img_height:%ld\n", lpbjinfo->bjfposimg.img_height );
	fprintf( stderr, "img_xres:%f\n", lpbjinfo->bjfposimg.xresolution );
	fprintf( stderr, "img_yres:%f\n", lpbjinfo->bjfposimg.yresolution );
	fprintf( stderr, "topmargin:%ld\n",	lpcnclpapersize->nTopMargin );
	fprintf( stderr, "leftmargin:%ld\n",lpcnclpapersize->nLeftMargin );
	fprintf( stderr, "prn_widht:%ld\n",	lpcnclpapersize->nWidthPrintArea );
	fprintf( stderr, "prn_height:%ld\n",lpcnclpapersize->nLengthPrintArea );
}


static void display_pos_info( LPBJF_POSINFO lpbjfpos )
{
	fprintf( stderr, "\n" );
	fprintf( stderr, "< Print Position Paramter >\n" );
	fprintf( stderr, "mask_width:%ld\n", lpbjfpos->mask_width );
	fprintf( stderr, "mask_height:%ld\n", lpbjfpos->mask_height );
	fprintf( stderr, "width_offset:%ld\n", lpbjfpos->width_offset );
	fprintf( stderr, "height_offset:%ld\n", lpbjfpos->height_offset );
	fprintf( stderr, "out_width:%ld\n", lpbjfpos->out_width );
	fprintf( stderr, "out_height:%ld\n", lpbjfpos->out_height );
	fprintf( stderr, "leftskip:%ld\n", lpbjfpos->leftskip );
	fprintf( stderr, "topskip:%ld\n", lpbjfpos->topskip );
	fprintf( stderr, "page_width:%ld\n",lpbjfpos->page_width );
}
#endif

static void check_lgmon_status(LPBJFILTERINFO bjfinfo, char *dispname, char *modelname)
{
	char *arg_noui[] = { LGMONPATH, "--model", modelname, NULL };
	char *arg_ui[] = { LGMONPATH, "--gui", "--display", dispname, "--model", modelname, NULL };

	if ( bjfinfo->bjfoption.lgmon == ON ) {
		if  ( bjfinfo->pid_lgmon == 0 ) {			/* lgmon is not invoked yet */
			bjfinfo->pid_lgmon = fork();

			if (bjfinfo->pid_lgmon == 0) {			/* child process */
				close( 0 );
				dup( bjfinfo->pipefds[0] );			/* duplicate input fd to stdin */
				close( bjfinfo->pipefds[0] );		/* close input and output fd */
				close( bjfinfo->pipefds[1] );

				if ( bjfinfo->bjfoption.ui == ON )
					execv( LGMONPATH, arg_ui );
				else
					execv( LGMONPATH, arg_noui );
			}
			else {									/* parent process */
				close( bjfinfo->pipefds[0] );		/* close input fd */
				return;
			}
		}
		else {										/* lgmon is already invoked */
			kill(bjfinfo->pid_lgmon, SIGUSR2);
		}
	}
}

static short mirror_raster( CPKByte CPKPTR buf, long width, short bpp )
{
	CPKByte CPKPTR		topbuf;
	CPKByte CPKPTR		tailbuf;	
	char				pixel[4];
	long				i,j;
	long				pixcount;
	short				result = -1;

	if ( bpp > 4 ) goto onErr;

	pixcount = width >> 1;

	topbuf  = buf;
	tailbuf = buf + ( width - 1 ) * bpp;
	
	for ( i=0; i<pixcount; i++ ){
		for( j=0; j<bpp; j++ ){
			pixel[j]    = topbuf[j];
			topbuf[j]   = tailbuf[j];
			tailbuf[j]  = pixel[j]; 
		}
		topbuf  += bpp;
		tailbuf -= bpp;
	}	

	result = 0;
onErr:
	return result;	
}

