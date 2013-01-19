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
#include <unistd.h>
#include <popt.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define BJFTEMPFILE "/tmp/bjtmpXXXXXX"
#define CIFTEMPFILEINPUT "/tmp/ciftmpXXXXXX"

#include "cncl.h"
#include "cncldef.h"
#include "cnclucom.h"
#include "cncludef.h"
#include "cnclcmdutils.h"
#include "bjfimage.h"
#include "bjfoption.h"
#include "bjfrcaccess.h"
#include "bjflist.h"
#include "bjfpos.h"
#include "bjipc.h"
#include "bjfilter.h"
#include "uitypes.h"
#include "bjfpath.h"


/* function prototypes */
extern short GetIPCData(LPIPCU pipc, char *sname);
extern short PsudoGetIPCData(LPIPCU pipc);

extern int ppm_write_tmpfile( LPBJF_IMAGEINFO lpbjfimage, char *filename , char *outfile);

/* local function prototypes */
static short h_extend( CPKByte CPKPTR, CPKByte CPKPTR, int, int, int );
static void outCmd(CPKByte CPKPTR, CPKUInt32, int);
static CPKBoolean whiteLine( CPKByte CPKPTR, CPKUInt32, CPKUInt32, CPKUInt32 CPKPTR, CPKUInt32 CPKPTR );
static void set_cncl_modelIDinfo( CNCLPtr, short ); 
static void set_cncl_timeinfo(  CNCLPtr );
static short set_cncl_bsccinfo( CNCLPtr, char * );	/* set bscc */
static void set_cncl_imginfo( CNCLPtr, long, long, short, short );
static void set_cncl_printerinfo( CNCLPtr, LPBJFLTDEVICE, LPCNCLPAPERSIZE, LPBJFLTCOMSYSTEM );
static void set_position_parameter( LPBJFILTERINFO, LPCNCLPAPERSIZE, LPBJFLTCOMSYSTEM );
static void set_cncl_colorinfo( CNCLPtr, LPBJFLTCOLORSYSTEM ); 
static short MakeBJPrintData( LPBJFILTERINFO, LPBJFLTDEVICE, LPCNCLPAPERSIZE, LPBJFLTCOLORSYSTEM );
static short mirror_raster( CPKByte CPKPTR, long, short );
static void SetPrinterFd( LPBJFILTERINFO lpbjfinfo );
static int createTempfile(LPBJF_ROOT root);
static void removeTempfileCompletely(LPBJF_ROOT root);
static void outCmdPlural( CPKByte CPKPTR buf, unsigned long size, int prn, int fd, LPBJF_ROOT root );
static short dumpPage(LPBJF_NODE node, int prn);
static short dumpPluralPages( LPBJF_ROOT root, int prn );
static short dumpPluralPages_flush( LPBJF_ROOT root, int prn );
static short dumpPluralPages_flush_duplex( LPBJF_ROOT root, int prn );
/* testprint function */
static short exec_testprint( char *command , long cmdslen , char *filename , int prn);
static long get_file_bytes( char *filename );


static int createInputfile( char name );

static short modify_image_form( LPBJFILTERINFO lpbjinfo , int isDuplex, int pageNum );
static short output_blank_page( CNCLPtr , int , int , LPBJF_ROOT );
static short process_raster_data( LPCIFRASTERINFO , LPBJFILTERINFO , LPBJFLTDEVICE , LPBJF_ROOT );
static short flush_raster_data(  CNCLPtr , LPBJFILTERINFO , int , LPBJF_ROOT );


#if DEBUG
static void display_cncl_printerinfo( CNCLPtr );
static void display_position_parameter( LPBJFILTERINFO,  LPCNCLPAPERSIZE );
static void display_pos_info( LPBJF_POSINFO );
static void display_margin_info( LPBJFILTERINFO );
static void display_overmargin_info( LPBJFLTOVERMARGININFO );
#endif

#if DEBUGLOG

#define DEBUGLOGFILE "/var/tmp/bjlogXXXXXX"

char		log_path_name[256];
int			log_fd;
FILE		*log_path = NULL;
char		log_buf[256];
void create_log(void);
void write_log(char *str);
void dispose_log(void);
#endif


/*-------------------------------------------------------------*/
/* main                                                        */
/*-------------------------------------------------------------*/
int main( int argc, char *argv[] )
{
	BJFLTDEVICE			bjfltdevice;
	CNCLPAPERSIZE   	cnclpapersize;
	BJFLTCOLORSYSTEM	bjfltcolor;
	LPBJFILTERINFO		lpbjinfo = NULL;
	IPCU				ipc;
	short				ret;
	char				socketname[256];
	short				modelstrnum,i;
	char				dispname[256];
	char				modelname[256];
	char				tmp_modelname[256],small_modelname[256];
	char				*bsccdata = NULL;
	FILE				*fp = NULL;
	char				confname[256];
	short				id = 0;
	short				testprint_ret;
	DATA_INFO			data_info;
	short				return_code = 1;

#if DEBUGLOG
	create_log( );
#endif
	
	/* allocate new work area */
	if ( (lpbjinfo = (LPBJFILTERINFO)malloc( sizeof(BJFILTERINFO) )) == NULL ) goto onErr;
	
	/* init bjinfo */
	memset( (LPBJFILTERINFO)lpbjinfo, 0, sizeof(BJFILTERINFO) );
	snprintf(socketname, sizeof(socketname), "%s%d",BJSOCKET,getpid());
	memset(tmp_modelname , 0x00 , sizeof(tmp_modelname));


	/*---------
		Analyze command line options.
	---------*/
	if ( (modelstrnum = SetCmdOption( argc, (char **)argv, &lpbjinfo->bjfoption, &bjfltcolor, 
			&bjfltdevice, &cnclpapersize, dispname, lpbjinfo->filename, tmp_modelname )) < 0 ) goto onErr;


	for( i=0; i<sizeof(tmp_modelname); i++ )	modelname[i] = tmp_modelname[i];
	for( i=0; i<sizeof(small_modelname); i++ )	small_modelname[i] = tolower(tmp_modelname[i]);

	/*---------
		Check If bscc_file is required(refer to "cif.conf").
	    If required ;
	     1. Make bscc_file neme (lipjinfo->bsccname).
	     2. Set "lipjinfo->bsccfile_exit"-->1.
	---------*/
	memset(tmp_modelname , 0x00 , sizeof(tmp_modelname));
	memset(confname , 0x00 , sizeof(confname));

	MakeModelnameConfname( argv[0], tmp_modelname, confname, BJFILTERXXXXRCPATH, BJFILTERDOTCONF );

	if ((id = bjf_get_resource_id( confname, "bscc_file", tmp_modelname )) != BJFRCACCESSERROR){

		memset(tmp_modelname , 0x00 , sizeof(tmp_modelname));
		MakeModelnameConfname( argv[0], tmp_modelname, lpbjinfo->bsccname, BJFILTERXXXXRCPATH, BJFILTERDOTBSCC );

		if ( (fp = fopen( lpbjinfo->bsccname, "r" )) != NULL ){

#if DEBUGLOG
			fprintf(stderr, "BSCC File exist = %s\n", lpbjinfo->bsccname);
#endif
			lpbjinfo->bsccfile_exist = 1;
			if( (fclose( fp )) != 0 ) goto onErr;
		}
		else		/* bscc file is required,but not exit --> ERROR! */
		{
			lpbjinfo->bsccfile_exist = 0;
			fprintf(stderr, "Setup file Error\n");
			goto onErr;
		}
	}

	/* set stdout descriptor to prn  */
	SetPrinterFd( lpbjinfo );

	/* check option settings */
	if ( CheckSettings( &bjfltdevice , confname ) < 0 ){
		goto onErr;
	}
	
	/* Make Printing Data */
	if ( MakeBJPrintData( lpbjinfo, &bjfltdevice, &cnclpapersize, &bjfltcolor ) < 0 ){
		fprintf( stderr, "Err in MakeBJPrintData!\n" );	
		goto onErr;
	}
	
	return_code = 0;
	
onErr:
	close( lpbjinfo->prn );	/* Ver.3.00 */
	
	if ( lpbjinfo ) free( lpbjinfo );
	
#if DEBUGLOG
	dispose_log( );
#endif

	return return_code;
}


/*-------------------------------------------------------------*/
/*  MakeBJPrintData                                            */
/*-------------------------------------------------------------*/
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
	long				width, height;
	long				ImageHeight;
	long				topskip;
	long				page_width;
	long				i;
	short				bpp;
	
	CNCLNAMEINFO		cnclnameinfo;
	BJFLTCOMSYSTEM		bjfltcom;
	char 				tblPath[] = BJLIBPATH;
	FILE				*fp=NULL;
	CPKInt16			result;
	char				*tmp_filename = NULL;
	short				rev_flag = 0;
	CIFRASTERINFO		CifRasterInfo;
	int					f_input = -1;
	LPBJF_ROOT			root = NULL;
	int					fd;
	short				dumpp_ret;
	BJFLTOVERMARGININFO	bjfltovermargin;
	char		command_buffer[CNCL_MAKECOMMAND_BUF_LEN];
	char		ssr_command[256];
	short				ssr_command_size = sizeof(ssr_command);
	
#if DEBUGLOG
	fprintf(stderr,"LGMONPATH:%s\n",LGMONPATH);
#endif

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

	CnclData.CommandParamPtr = NULL;
	CnclData.CommandParamSize = 0;
	CnclData.TablePath = tblPath;
	CnclData.ImageRotate = lpbjinfo->bjfoption.rotate;
	
	/*--- 
		If bscc file exists, set bscc info in CnclData.
	---*/
	if( lpbjinfo->bsccfile_exist == 1 ){
		if(set_cncl_bsccinfo( &CnclData, lpbjinfo->bsccname ) == -1){
			fprintf(stderr, "Error: invalid BSCCREG file\n");
			goto finish1;
		}
	}
	
	/****** IVEC Startjob ******/
	if (lpbjinfo->bjfoption.is_ivec == 1){
		/* poweron */
		memset(command_buffer, 0x00, sizeof(command_buffer));
		if (CNCL_MakePrintCommand(CNCL_COMMAND_POWERON, command_buffer, sizeof(command_buffer), NULL, "0") != CNCL_OK) goto finish1;
		outCmd( (unsigned char *)command_buffer, strlen(command_buffer), lpbjinfo->prn );
		
		/* start1 */
		memset(command_buffer, 0x00, sizeof(command_buffer));
		if (CNCL_MakePrintCommand(CNCL_COMMAND_START1, command_buffer, sizeof(command_buffer), NULL, "0") != CNCL_OK) goto finish1;
		outCmd( (unsigned char *)command_buffer, strlen(command_buffer), lpbjinfo->prn );
		
		/* start2 */
		memset(command_buffer, 0x00, sizeof(command_buffer));
		if (CNCL_MakePrintCommand(CNCL_COMMAND_START2, command_buffer, sizeof(command_buffer), NULL, NULL) != CNCL_OK) goto finish1;
		outCmd( (unsigned char *)command_buffer, strlen(command_buffer), lpbjinfo->prn );
	}
	
	/****** CNCL SetSSR ******/
	if ( (cnclerr = CNCL_SetSSRDef(ssr_command, &ssr_command_size)) != CNCL_OK ) goto finish1;
	outCmd( (unsigned char *)ssr_command, ssr_command_size, lpbjinfo->prn );
	
	/****** CNCL Startjob ******/
	if ( (cnclerr = CNCL_StartJob( &CnclData )) != CNCL_OK ) goto finish1;
	outCmd( CnclData.outputBuffer, CnclData.outputSize, lpbjinfo->prn );

	/*--- 
		Input Image open. 
		we deal width only ppm image format as stdin.
	---*/
	if ( lpbjinfo->bjfoption.stdswitch == ON ){
#if DEBUGLOG
		fprintf(stderr,"stdswitch == ON\n");
#endif

		/* set reverse flag (stdin only) */
		if ((lpbjfltdevice->bjfltDuplex == CND_DUPLEX_AUTO) && (lpbjinfo->bjfoption.stapleside == STAPLESIDE_LONG)){
			rev_flag = 1;
		}
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

	/* dump plural pages. */
	if( ( root = bjf_create_root() ) == NULL ) {
		fprintf(stderr, "error : bjf_create_root\n");
		goto finish3;
	}
	bjf_init_root(root, lpbjinfo->bjfoption.copies, lpbjinfo->bjfoption.collate, lpbjinfo->bjfoption.revprint);
	
	/* duplex ON and stdin --> root->isDuplex ON */
	if( ( lpbjinfo->bjfoption.stdswitch == ON ) && (lpbjfltdevice->bjfltDuplex == CND_DUPLEX_AUTO) ){
		root->isDuplex = ON;
	}else{
		root->isDuplex = OFF;
	}
	

	/********************************************************************Make Printing Data */

	/* make temp file to write input data from "stdin" */
	tmp_filename = malloc(1024);
	memset(tmp_filename,0x00,1024);

	/* init page ID */
	CnclData.PageNum = 1;
	
	while ( (cnclerr = bjf_image_init( &lpbjinfo->bjfimage , rev_flag , CnclData.PageNum )) > 0 ) {
		/* The 1st page has not to be written to temp file. */
#if DEBUGLOG
		fprintf(stderr,"bjf_image_init \n CnclData.PageNum = %d\n rev_flag=%d \n",CnclData.PageNum,rev_flag);
#endif
		
		/*---
			copy RGB image data to bjfposimg and bjfposprn
		---*/
		set_position_parameter( lpbjinfo, lpcnclpapersize, &bjfltcom );

		if ( MarginInit( &lpbjinfo->bjfposprn, &lpbjinfo->bjfposinfo, &lpbjinfo->bjfmgninfo) < 0 ) goto finish3;


		/*---------
			if borderless option is selected, prntarea is changed.
		---------*/
		if ( lpbjfltdevice->bjfltMarginType==CND_MARGIN_MINUS )
		{
			SetExtLevel(&lpbjinfo->bjfmgninfo, lpbjinfo->bjfoption.extension);

			bjfltovermargin.extension = lpbjinfo->bjfmgninfo.extension;
			bjfltovermargin.papersize = lpbjfltdevice->bjfltPaperSize;
			bjfltovermargin.overmargin_left = 0;
			bjfltovermargin.overmargin_right = 0;
			bjfltovermargin.overmargin_top = 0;
			bjfltovermargin.overmargin_bottom = 0;
			bjfltovermargin.duplex = lpbjfltdevice->bjfltDuplex;
			
			if( CNCL_GetOverMargin( &cnclnameinfo , (void *)tblPath , &bjfltovermargin ) < 0 ) goto finish3;
			
#if DEBUG
			display_overmargin_info( &bjfltovermargin);
#endif
			SetExtMargin(&lpbjinfo->bjfposprn, &lpbjinfo->bjfposinfo, &lpbjinfo->bjfmgninfo,&bjfltovermargin);
		}

		/*---------
			modify image size , location , etc. (bbox,fit,full,percent,location)
		---------*/
		if( modify_image_form( lpbjinfo , root->isDuplex, CnclData.PageNum ) < 0 ) goto finish3;


#if DEBUG 
		fprintf(stderr,"\n### AFTER CUT ###\n");
		display_pos_info( &lpbjinfo->bjfposinfo );
		display_margin_info( lpbjinfo );
#endif

		/*---------
			get scaling parameter which cif needs.
		---------*/
		width = 0;			height = 0;
		ImageHeight = 0;	topskip = 0;
		page_width = 0;
	
		bjf_pos_mask_width( &lpbjinfo->bjfposinfo, &width );
		bjf_pos_mask_height( &lpbjinfo->bjfposinfo, &height );
		bjf_pos_out_height( &lpbjinfo->bjfposinfo, &ImageHeight );
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
		if ( topskip ) CnclData.length += topskip; /* if topskip is, increase Vposition */
		
		/* Set Infomation ( with BJCOMMON STRUCTRE ) */
		set_cncl_printerinfo( &CnclData, lpbjfltdevice, lpcnclpapersize, &bjfltcom ); 

		/* Set DuplexCommand */
		if( root->isDuplex == ON ){
			CnclData.DuplexCommand = CND_DUPLEX_AUTO;
		}else{
			CnclData.DuplexCommand = CND_DUPLEX_OFF;
		}
	
		/* Set Infomation ( with COLOR STRUCTRE ) */
		set_cncl_colorinfo( &CnclData, lpbjfltcolor );


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
		outCmd( CnclData.outputBuffer, CnclData.outputSize, lpbjinfo->prn );
		
		/* Alloc work2 buf */
		if ( CnclData.Work2Buf == CPKNULL ){
			CnclData.Work2Buf = (CPKVoid CPKPTR)malloc( CnclData.Work2Size );
		}	
		if ( CnclData.Work2Buf == CPKNULL ) goto onErr;
	
		/* dump plural pages. */
		fd = 0;
		if( ( fd = createTempfile(root) ) < 0 ) {
			fprintf(stderr, "error : createTempfile\n");
			goto onErr;
		}
		


		/****** CNCL Start page ******/
		if ( (cnclerr = CNCL_StartPage( &CnclData )) != CNCL_OK ) goto onErr;
		outCmdPlural( CnclData.outputBuffer, CnclData.outputSize, lpbjinfo->prn, fd, root );

		/*---
			process raster data
		---*/
		CnclData.inputBuffer = rgbBuf ;
		CnclData.srcdatatype = CND_ST_RGB24 ;
		CnclData.left_white  = 0 ;
		CnclData.right_white = 0 ;
		if ( topskip ) CnclData.Vpos = topskip;	/* if topskip is, set Vposition to topskip */

		CifRasterInfo.lpCnclData	= &CnclData;
		CifRasterInfo.rgb_buf		= rgbBuf;
		CifRasterInfo.image_height	= ImageHeight;
		CifRasterInfo.page_width	= page_width;
		CifRasterInfo.width			= width;
		CifRasterInfo.height		= height;
		CifRasterInfo.top_skip		= topskip;
		CifRasterInfo.bpp			= bpp;
		CifRasterInfo.rev_flag		= rev_flag;
		CifRasterInfo.page			= CnclData.PageNum;
		CifRasterInfo.fd			= fd;
		
		/* process raster data. */
		if( process_raster_data( &CifRasterInfo , lpbjinfo , lpbjfltdevice , root ) < 0 ) goto onErr;


		/****** CNCL flush data ******/
		if( flush_raster_data( &CnclData, lpbjinfo , fd ,  root ) < 0 ) goto onErr;

		/*--- flush image ---*/
		bjf_image_flush( &lpbjinfo->bjfimage ); 
			
		/****** CNCL End page ******/
		if ( (cnclerr = CNCL_EndPage( &CnclData )) != CNCL_OK ) goto onErr;
		/* dump plural pages. */
		outCmdPlural( CnclData.outputBuffer, CnclData.outputSize, lpbjinfo->prn, fd, root );

		/* dump plural pages. */
		if(fd>0){
			close(fd);
			fd = 0;
		}

		if( ( dumpp_ret = dumpPluralPages(root, lpbjinfo->prn) ) < 0 ) goto onErr;


		/****** dulex ONEstdin ******/
		if ( root->isDuplex == ON ){

			if( !( CnclData.PageNum % 2 ) ){	/* back page(even page) */

				/* if reading temp file , close and remove temp file */
				if( f_input >= 0 ){
					bjf_image_close( &lpbjinfo->bjfimage );
					unlink( lpbjinfo->filename );
					f_input = -1;
					lpbjinfo->bjfimage.bmp = stdin;
				}

				/* flush current page and previous page */
				if( ( dumpp_ret = dumpPluralPages_flush_duplex(root, lpbjinfo->prn) ) < 0 ) goto onErr;
	
				/* init root (again) */
				bjf_init_root(root, lpbjinfo->bjfoption.copies, lpbjinfo->bjfoption.collate, lpbjinfo->bjfoption.revprint);
				root->isDuplex = ON;

			}
			else if( rev_flag ){			/* front page(odd page) and longside-stapling */
	
				/* init temp file name */
				memset(tmp_filename,0,1024);
				strncpy( tmp_filename, CIFTEMPFILEINPUT, 1024 );
				tmp_filename[1024 - 1] = '\0';

				/* If next page exist ,  write next page data to temp file. */
				f_input = ppm_write_tmpfile( &lpbjinfo->bjfimage , NULL , tmp_filename );

				if( f_input == -1 ){
					goto onErr;
				}

				else if( f_input == CIF_FILE_END ){	/* no more input data */

					CnclData.PageNum++;
					break;
				}
				else if( f_input > 0 ){			/* next page(input from stdin) exists */
					strcpy(lpbjinfo->filename , tmp_filename);
					if ( bjf_image_open( &lpbjinfo->bjfimage, lpbjinfo->filename ) < 0 ) goto onErr;
				}
			}
		}
	
		CnclData.PageNum++;
	
		if( lpbjinfo->bjfoption.stdswitch != ON ) break;

	}
	
	CnclData.PageNum--;
	
	/* insert blank page */
	if(  ( CnclData.PageNum % 2 ) && (root->isDuplex == ON) && ( lpbjinfo->bjfoption.copies > 1 ) )
	{
		fd = 0;
		if( ( fd = createTempfile(root) ) < 0 ) {
			fprintf(stderr, "error : createTempfile\n");
			goto onErr;
		}
		CnclData.PageNum++;

		if( output_blank_page( &CnclData , lpbjinfo->prn , fd , root) < 0 ) goto onErr;
	}
	

	
	/***** flush dump pages. *****/
	if ( root->isDuplex == ON ){	/* duplex flush */
		if( ( dumpp_ret = dumpPluralPages_flush_duplex(root, lpbjinfo->prn) ) < 0 ) goto onErr;
	}else{							/* "duplex OFF" or "duplex ON and input is image file" */
		if( ( dumpp_ret = dumpPluralPages_flush(root, lpbjinfo->prn) ) < 0 ) goto onErr;
	}
	
	if ( cnclerr < 0 ) goto onErr;
	
	cnclerr = 0;

onErr:
	if ( CnclData.Work2Buf ) free( CnclData.Work2Buf );
	if ( rgbBuf ) free( rgbBuf );

finish3:
	/*---close image---*/
	bjf_image_close( &lpbjinfo->bjfimage );
	
	/* dump plural pages. */
	if(fd>0)close(fd);
	while(bjf_dispose_root(root) > 0) {
		removeTempfileCompletely(root);
	}

finish2:
	/****** CNCL End job ******/
	if ( (cnclerr = CNCL_EndJob( &CnclData )) == CNCL_OK ) {
		outCmd( CnclData.outputBuffer, CnclData.outputSize, lpbjinfo->prn );
	}

	/****** IVEC End job ******/
	if (lpbjinfo->bjfoption.is_ivec == 1){
		/* end */
		memset(command_buffer, 0x00, sizeof(command_buffer));
		if (CNCL_MakePrintCommand(CNCL_COMMAND_END, command_buffer, sizeof(command_buffer), NULL, NULL) != CNCL_OK) goto finish1;
		outCmd( (unsigned char *)command_buffer, strlen(command_buffer), lpbjinfo->prn );
	}
	
finish1:
	if ( CnclData.Work1Buf ) free( CnclData.Work1Buf );

	/* remove temp file */
	if( f_input >= 0 ) unlink(tmp_filename);
	if( tmp_filename ) free(tmp_filename);
	
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
	

	if ( (src_width < 1) || (dst_width < 0) ) goto onErr; /* Ver.3.60 */

	if ( dst_width == 0 ) {
		goto EXIT;
	}
	else if ( dst_width == 1 ){
		switch ( component ){
			case 1:
				out[0] = in[0];
				break;
			case 3:
				out[0] = in[0]; out[1] = in[1]; out[2] = in[2];
				break;
			case 4:
				out[0] = in[0]; out[1] = in[1]; out[2] = in[2]; out[3] = in[3];
				break;
			case 6:
				out[0] = in[0]; out[1] = in[1]; out[2] = in[2];
				out[3] = in[3]; out[4] = in[4]; out[5] = in[5];
				break;
			case 7:
				out[0] = in[0]; out[1] = in[1]; out[2] = in[2];
				out[3] = in[3]; out[4] = in[4]; out[5] = in[5]; out[6] = in[6];
				break;
		}
		goto EXIT;
	}

	Quotient  = (src_width - 1) / (dst_width - 1);
	Rest      = (src_width - 1) % (dst_width - 1);
	TotalRest = 0;
	PrevPos   = -1;
	CurrPos   = 0;
	K = Y = M = C = y = m = c = 0;	

	for ( x=0; x<dst_width; x++ ){

		/* calculate remainder */
		if ( TotalRest * 2 >= (dst_width -1) ){ /* Ver.3.60 */
		/*if ( (( 2 * TotalRest + Rest ) >> 1) >= dst_width ){*/
			TotalRest -= (dst_width -1);
			CurrPos++;
		}

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
		
	}

EXIT:	
	result = 0;
onErr:
	return result;
}


/*-------------------------------------------------------------*/
/* outCmd                                                      */
/*-------------------------------------------------------------*/
static void
outCmd ( CPKByte CPKPTR buf, CPKUInt32 size, int prn )	/* to take file pointer */
{
	char *ptr;
	int w_size;
	int r_size;

	if(size == 0) return; /* do nothing. */

	ptr = (char *)buf;
	r_size = size;
	while( 1 ){
		if(r_size == 0) return;
		
		w_size = write( prn, ptr, r_size );

		if ( w_size <= 0 ){
			w_size = 0;
			continue;
		}
		if ( w_size < r_size ){
			r_size -= w_size;
			ptr    += w_size;
		}
		else break;
	}

	return;
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
}
  


static void set_cncl_printerinfo( CNCLPtr lpcncldata, LPBJFLTDEVICE lpbjfltdevice, LPCNCLPAPERSIZE lpcnclpapersize,LPBJFLTCOMSYSTEM lpbjfltcom )
{
	lpcncldata->InkType      = lpbjfltcom->bjfltInkCartridge;
	lpcncldata->InkCartridgeSettings  = lpbjfltcom->bjfltInkCartridgeSettings;
	lpcncldata->MediaType    = lpbjfltdevice->bjfltMediaType;
	lpcncldata->PaperSize    = lpbjfltdevice->bjfltPaperSize;
	lpcncldata->MediaSupply  = lpbjfltdevice->bjfltMediaSupply;
	lpcncldata->PaperGap 	 = lpbjfltdevice->bjfltPaperGap;
	lpcncldata->DuplexPrinting  	 = lpbjfltdevice->bjfltDuplex;

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
	lpcncldata->MarginType   = lpbjfltdevice->bjfltMarginType;

}



static short set_cncl_bsccinfo( CNCLPtr lpcncldata, char *bsccname )
{
	FILE	*fp = NULL;
	char	*bsccdata = NULL;
	short	ret = -1;
	short	length = 0;


	if( bsccname == NULL )  goto process01;

	if ( (fp = fopen( bsccname, "r" )) != NULL ){
		if( (fclose( fp )) != 0 ) goto process01;
		if( (bsccdata = bjf_get_resource_string( bsccname, "bscc", BSCCREG )) == NULL )	goto process01;
		length = strlen(bsccdata);
	}
	ret = 0;

process01:

	lpcncldata->CommandParamPtr = bsccdata;
	lpcncldata->CommandParamSize = length;

	return ret; 

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
    bjf_margin_init( &lpbjinfo->bjfmgninfo );

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
		if ( lpbjinfo->bjfimage.xresolution == 0 ){
			bjf_pos_set_imgXres( &lpbjinfo->bjfposimg, XDEFAULTRESOLUTION );
		}
		else{
			bjf_pos_set_imgXres( &lpbjinfo->bjfposimg, lpbjinfo->bjfimage.xresolution );
		}

		/* set yresolution */
		if ( lpbjinfo->bjfimage.yresolution == 0 ){
			bjf_pos_set_imgYres( &lpbjinfo->bjfposimg, YDEFAULTRESOLUTION );
		}
		else{	/* use xresolution */
			bjf_pos_set_imgYres( &lpbjinfo->bjfposimg, lpbjinfo->bjfimage.xresolution );
		}
	}
	/* set printer parameter */
	bjf_pos_set_prntopmargin( &lpbjinfo->bjfposprn,lpcnclpapersize->nTopMargin );
	bjf_pos_set_prnleftmargin( &lpbjinfo->bjfposprn, lpcnclpapersize->nLeftMargin );
	bjf_pos_set_prnXres( &lpbjinfo->bjfposprn, (double)lpbjfcom->bjfltInputHResolution  );
	bjf_pos_set_prnYres( &lpbjinfo->bjfposprn, (double)lpbjfcom->bjfltInputVResolution  );
	bjf_pos_set_prnwidth( &lpbjinfo->bjfposprn,lpcnclpapersize->nWidthPrintArea );
	bjf_pos_set_prnheight( &lpbjinfo->bjfposprn,lpcnclpapersize->nLengthPrintArea  );

	/* set paper size */
	bjf_pos_set_paperwidth( &lpbjinfo->bjfmgninfo , lpcnclpapersize->nSelPaperWidth );
	bjf_pos_set_paperlength( &lpbjinfo->bjfmgninfo , lpcnclpapersize->nSelPaperLength );
} 

static void set_cncl_colorinfo( CNCLPtr lpcncldata, LPBJFLTCOLORSYSTEM lpbjfltcolor )
{
	lpcncldata->Intent		= lpbjfltcolor->bjfltIntent;
	lpcncldata->Gamma		= lpbjfltcolor->bjfltGamma;
	lpcncldata->BalanceC	= lpbjfltcolor->bjfltBalanceC;
	lpcncldata->BalanceM	= lpbjfltcolor->bjfltBalanceM;
	lpcncldata->BalanceY 	= lpbjfltcolor->bjfltBalanceY;
	lpcncldata->BalanceK	= lpbjfltcolor->bjfltBalanceK;
	lpcncldata->MonochromeTone	= lpbjfltcolor->bjfltMonochromeTone;
	lpcncldata->Contrast	= lpbjfltcolor->bjfltContrast;
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
	fprintf( stderr, "lpcncldata->PaperGap:%d\n", lpcncldata->PaperGap);
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
	fprintf( stderr, "lpcncldata->MonochromeTone:%d\n", lpcncldata->MonochromeTone);
	fprintf( stderr, "lpcncldata->Density:%d\n", lpcncldata->Density);

	fprintf( stderr, "lpcncldata->CommandParamPtr:%s\n", lpcncldata->CommandParamPtr);
	fprintf( stderr, "lpcncldata->CommandParamSize:%d\n", lpcncldata->CommandParamSize);

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
	fprintf( stderr, "mask_width:%f\n", lpbjfpos->mask_width );
	fprintf( stderr, "mask_height:%f\n", lpbjfpos->mask_height );
	fprintf( stderr, "width_offset:%f\n", lpbjfpos->width_offset );
	fprintf( stderr, "height_offset:%f\n", lpbjfpos->height_offset );
	fprintf( stderr, "out_width:%f\n", lpbjfpos->out_width );
	fprintf( stderr, "out_height:%f\n", lpbjfpos->out_height );
	fprintf( stderr, "leftskip:%f\n", lpbjfpos->leftskip );
	fprintf( stderr, "topskip:%f\n", lpbjfpos->topskip );
	fprintf( stderr, "page_width:%f\n",lpbjfpos->page_width );
}

static void display_margin_info( LPBJFILTERINFO lpbjinfo )
{
	fprintf( stderr, "\n" );
	fprintf( stderr, "< Print Margin Info >\n" );
	fprintf(stderr,"TopMargin:%ld\n",lpbjinfo->bjfposprn.topmargin);
	fprintf(stderr,"LeftMargin:%ld\n",lpbjinfo->bjfposprn.leftmargin);
	fprintf(stderr,"CurTopMargin[1/100mm]:%f\n",lpbjinfo->bjfmgninfo.curtopmargin);
	fprintf(stderr,"CurLeftMargin[1/100mm]:%f\n",lpbjinfo->bjfmgninfo.curleftmargin);
	fprintf(stderr,"CurPrnWidth[1/100mm]:%f\n",lpbjinfo->bjfmgninfo.curprn_width);
	fprintf(stderr,"CurPrnHeight[1/100mm]:%f\n",lpbjinfo->bjfmgninfo.curprn_height);

}


static void display_overmargin_info( LPBJFLTOVERMARGININFO lpbjfltovermargin)
{
	fprintf(stderr,"\n### OVERMARGIN ###\n");
	fprintf(stderr,"overmargin_left = %d\n",lpbjfltovermargin->overmargin_left);
	fprintf(stderr,"overmargin_top = %d\n",lpbjfltovermargin->overmargin_top);
	fprintf(stderr,"overmargin_right = %d\n",lpbjfltovermargin->overmargin_right);
	fprintf(stderr,"overmargin_bottom = %d\n",lpbjfltovermargin->overmargin_bottom);
}


#endif

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


static void SetPrinterFd( LPBJFILTERINFO lpbjfinfo )
{
	lpbjfinfo->prn = 1;
}


/***************************************/
/*   dump plural pages functions       */
/***************************************/
/*-------------------------------------------------------------*/
/* write command to prn and fd.                            */
/*-------------------------------------------------------------*/
static void outCmdPlural( CPKByte CPKPTR buf, unsigned long size, int prn, int fd, LPBJF_ROOT root )
{
	if(root->isRPrint == REVPRINT_OFF)
		outCmd( buf, size, prn ); /* write to prn. */

	if(root->Copies > 1 || root->isRPrint == REVPRINT_ON)
		if(fd>0)outCmd( buf, size, fd ); /* write to tempfile. */
}


/*-------------------------------------------------------------*/
/* create tempfile and put queue if necessary.                 */
/*-------------------------------------------------------------*/
static int createTempfile(LPBJF_ROOT root)
{
	char name[32];
	int fd = -1;
	LPBJF_NODE	node = NULL;

	if(root->Copies > 1 || root->isRPrint == REVPRINT_ON) {
		/* create and open tempfile. */
		memset(name,0,sizeof(name));
		strncpy( name, BJFTEMPFILE, sizeof(name) );
		name[sizeof(name) - 1] = '\0';
		if( ( fd = mkstemp(name) ) < 0 ) return -1; /* tempfile open error. */

		/* create and put queue. */
		if( ( node = bjf_new_q( name ) ) == NULL ) goto onErr;
		if( ( node = bjf_put_q( root, node ) ) == NULL ) goto onErr;
	}
	else
		fd = 0;
	
	/* no error */
	return fd;
	
onErr:
	/* queue error */
	if(fd>0)close(fd);
	return -2;
}


/*-------------------------------------------------------------*/
/* remove tempfile and dispose queue completely.               */
/*-------------------------------------------------------------*/
static void removeTempfileCompletely(LPBJF_ROOT root)
{
	while(root->head != NULL)
	{
		unlink(root->head->fileName);
		bjf_dispose_q(root,BJF_HEAD_NODE);
	}
}



/*-------------------------------------------------------------*/
/* dump singular page. page data read from tempfile.           */
/*-------------------------------------------------------------*/
static short dumpPage(LPBJF_NODE node, int prn)
{
	CPKByte	buf[BUFSIZ];
	int		fd = 0;
	int		r_size = 0;
	short	ret = -1;
	
	if(node==NULL)return 0;
	
	if( node->curCopies > 0 ){
		if ( (fd = open( node->fileName, O_RDONLY )) < 0 ){
			/* perror( "open" ); */
			return -2;	
		}
		
		while ( (r_size = read( fd, buf, BUFSIZ)) > 0 ){
			outCmd( buf, r_size, prn );  /* write( prn, buf, r_size ); */
		}
		node->curCopies--;
	}
	ret = node->curCopies;
	
onErr:
	if(fd>0)close(fd);
	return ret;
}


/*-------------------------------------------------------------*/
/* dump plural pages.                                          */
/*-------------------------------------------------------------*/
static short dumpPluralPages( LPBJF_ROOT root, int prn )
{
	short ret = 0;
	
	if(!bjf_exist_q(root))
		return ret; /* do nothing. */
	
	if(root->isRPrint == REVPRINT_ON)
		return ret; /* do nothing. */

	if(root->isCollate == COLLATE_ON)
		return ret; /* do nothing. */

	if(root->isDuplex == ON)
		return ret; /* do nothing. */

	/* in the case of "copies>1". <-- In this case, there is only "head" in the list */
	/* 1 page written to prn already. */
	root->head->curCopies--;
	
	while( ( ret = dumpPage(root->head, prn) ) != 0 ) {
		if(ret < 0)goto onErr;
	}
	
onErr:
	/* remove tempfile and dispose head-queue. */
	if( bjf_exist_q(root) ) {
		unlink(root->head->fileName);
		bjf_dispose_q(root,BJF_HEAD_NODE);
	}
	
	return ret;
}


/*-------------------------------------------------------------*/
/* flush and dump plural pages.                                */
/*-------------------------------------------------------------*/
static short dumpPluralPages_flush( LPBJF_ROOT root, int prn )
{
	LPBJF_NODE	node = NULL, next_node = NULL;
	short	ret = 0;

	/* tail -> head */
	if(root->isRPrint == REVPRINT_ON) { 
		if(root->isCollate == COLLATE_ON) {
			while( bjf_exist_q(root) ) {
				
				node = root->tail;
				while( node != NULL ) {
					next_node = node->prev;
					
					if( (ret = dumpPage(node, prn)) == 0 ) {
						/* remove tempfile and dispose tail-queue. */
						unlink(node->fileName);
						bjf_dispose_q(root,BJF_TAIL_NODE);
					}
					else if (ret < 0) goto onErr;
					
					node = next_node;
				}
			}
		}
		else {
			while( bjf_exist_q(root) ) {
				node = root->tail;
				while( (ret = dumpPage(node, prn)) != 0 ) {
					if (ret < 0) goto onErr;
				}
				/* remove tempfile and dispose tail-queue. */
				unlink(node->fileName);
				bjf_dispose_q(root,BJF_TAIL_NODE);
			}
		}
	}
	/* head -> tail */
	else {
		/* 1 page written to prn already. */
		for(node = root->head; node != NULL; node = node->next) node->curCopies--;

		if(root->isCollate == COLLATE_ON) {
			while( bjf_exist_q(root) ) {
			
				node = root->head;
				while( node != NULL ) {
					next_node = node->next;
					
					if( (ret = dumpPage(node, prn)) == 0 ) {
						/* remove tempfile and dispose head-queue. */
						unlink(node->fileName);
						bjf_dispose_q(root,BJF_HEAD_NODE);
					}
					else if (ret < 0) goto onErr;
					
					node = next_node;
				}
			}
		}
		else {
			while( bjf_exist_q(root) ) {	/* root is not NULL */
				node = root->head;
				while( (ret = dumpPage(node, prn)) != 0 ) {
					if (ret < 0) goto onErr;
				}
				/* remove tempfile and dispose head-queue. */
				unlink(node->fileName);
				bjf_dispose_q(root,BJF_HEAD_NODE);
			}
		}
	}
	ret = 0;

onErr:
	return ret;
}


/*-------------------------------------------------------------*/
/* flush and dump plural pages for duplex printing.            */
/*-------------------------------------------------------------*/
static short dumpPluralPages_flush_duplex( LPBJF_ROOT root, int prn )
{
	LPBJF_NODE	node = NULL, next_node = NULL;
	short	ret = 0;


	/* REVPRINT or COLLATE is not allowed.  */
	if(root->isRPrint == REVPRINT_ON) { 
		ret = -1;
		goto onErr;
	}
	if(root->isCollate == COLLATE_ON) {
		ret = -1;
		goto onErr;
	}

	/* 1 page written to prn already. */
	for(node = root->head; node != NULL; node = node->next) node->curCopies--;

	while( bjf_exist_q(root) ) {
		
		node = root->head;
		while( node != NULL ) {
			next_node = node->next;
			if( (ret = dumpPage(node, prn)) == 0 ) {
				/* remove tempfile and dispose head-queue. */
				unlink(node->fileName);
				bjf_dispose_q(root,BJF_HEAD_NODE);	
			}
			else if (ret < 0) goto onErr;
			
			node = next_node;
		}
	}
		
	ret = 0;

onErr:
	return ret;
}


/*-------------------------------------------------------------*/
/* write testprint pattern.                                    */
/*-------------------------------------------------------------*/
static short exec_testprint( char *command , long cmdslen , char *filename , int prn)
{
	CPKByte	buf[BUFSIZ];
	int		fd = 0;
	int		r_size = 0;
	short	ret = -1;
	
	
	/* open testpattern file */
	if ( (fd = open( filename, O_RDONLY )) < 0 ){
		/* perror( "open" ); */
		return -2;	
	}

	/* send BJL to LM */
	outCmd( (CPKByte CPKPTR)command, (CPKUInt32)cmdslen, prn );

	/* read testpattern file and write to LM */
	while ( (r_size = read( fd, buf, BUFSIZ)) > 0 ){

		outCmd( buf, r_size, prn );  /* write( prn, buf, r_size ); */
	}

	ret = 0;
	
onErr:
	if(fd>0)close(fd);
	return ret;
	
	
}



/*-------------------------------------------------------------*/
/* modify image size and location.                             */
/*-------------------------------------------------------------*/
static short modify_image_form( LPBJFILTERINFO lpbjinfo , int isDuplex, int pageNum )
{
	short	ret = -1;

	/*---------
		if bbox option is selected, 
	---------*/

	if ( lpbjinfo->bjfoption.bbox.bbox_flag == BBOX_ON ){
		if ( SetBbox(	&lpbjinfo->bjfoption ,
						&lpbjinfo->bjfposimg ,
						&lpbjinfo->bjfposinfo,
						&lpbjinfo->bjfmgninfo,
						isDuplex,
						pageNum ) < 0 ) goto onErr;
	}

	/*** Change image size <- "fit" & "percent" ***/

	/*---------
		if fitshort option is selected, output image is fit for current media size
	---------*/
	if ( lpbjinfo->bjfoption.fit == FIT_SHORT ){
		if ( ImageFitShort( &lpbjinfo->bjfposimg,
			&lpbjinfo->bjfposprn, &lpbjinfo->bjfposinfo,&lpbjinfo->bjfmgninfo ) < 0 ) goto onErr;
	}
	else if ( lpbjinfo->bjfoption.fit == FIT_LONG ){
		if ( ImageFitLong( &lpbjinfo->bjfposimg,
			&lpbjinfo->bjfposprn, &lpbjinfo->bjfposinfo,&lpbjinfo->bjfmgninfo ) < 0 ) goto onErr;
	}
	else{
		if ( SetImageSize( &lpbjinfo->bjfposimg,
			&lpbjinfo->bjfposprn, &lpbjinfo->bjfposinfo) < 0 ) goto onErr;
	}

	/*---------
		if percent option is selected, output image is scaled 
	---------*/
	if ( lpbjinfo->bjfoption.percent){
	  if ( ImageScaling(&lpbjinfo->bjfposprn, &lpbjinfo->bjfposinfo,lpbjinfo->bjfoption.percent ) < 0 ) goto onErr;
	}


	/*** Change image location <- "center" ***/

	/*---------
		if center option is selected, two parameter is culcurated, these are leftskip and topskip
	---------*/
	if ( lpbjinfo->bjfoption.location == LOCATION_CENTER ){
		if ( ImageCenter( &lpbjinfo->bjfposimg,
			&lpbjinfo->bjfposprn, &lpbjinfo->bjfposinfo,&lpbjinfo->bjfmgninfo ) < 0 ) goto onErr;

	}


	/*** Cut image <- always ***/
	/* Extract the image to be printed. */
	if ( ImageCut( &lpbjinfo->bjfposimg,
			  &lpbjinfo->bjfposprn, &lpbjinfo->bjfposinfo,&lpbjinfo->bjfmgninfo ) < 0 ) goto onErr;



	ret = 0;
	
onErr:
	return ret;


}


/*-------------------------------------------------------------*/
/* insert blank page.                                          */
/*-------------------------------------------------------------*/
static short output_blank_page( CNCLPtr lpCnclData , int prn , int fd , LPBJF_ROOT root)
{
	short		ret = -1;
	CNCLErr		cnclerr = -1;


	/* CNCL Set param */
	if ( ( cnclerr = CNCL_SetParam ( lpCnclData ) ) != CNCL_OK ) goto onErr ;
	outCmd( lpCnclData->outputBuffer, lpCnclData->outputSize, prn );

	/* CNCL Start page */
	if ( ( cnclerr = CNCL_StartPage ( lpCnclData ) ) != CNCL_OK ) goto onErr ;

	outCmdPlural( lpCnclData->outputBuffer, lpCnclData->outputSize, prn, fd, root );

	/* CNCL End page */
	if ( ( cnclerr = CNCL_EndPage ( lpCnclData ) ) != CNCL_OK ) goto onErr ;

	outCmdPlural( lpCnclData->outputBuffer, lpCnclData->outputSize, prn, fd, root );


	ret = 0;
	
onErr:
	return ret;

}


/*-------------------------------------------------------------*/
/* process raster by raster.                                   */
/*-------------------------------------------------------------*/
static short process_raster_data( LPCIFRASTERINFO lpCifRasterInfo , LPBJFILTERINFO lpbjinfo , LPBJFLTDEVICE lpbjfltdevice , LPBJF_ROOT root )
{
	long				Quotient , Rest;
	long				TotalRest = 0;
	long				PrevPos   = -1;
	long				CurrPos   = 0;
	long				left = 0;
	long				right = 0;
	long				width_offset = 0;
	long				height_offset = 0;
	long				ImageWidth;
	long				leftskip = 0;
	long				y;
	long				i;
	short				result;
	short				ret = -1;
	CNCLErr				cnclerr = -1;

	/* data from CIFRASTERINFO */
	CPKByte CPKPTR		rgbBuf = CPKNULL;
	CPKByte CPKPTR		srcBuf = CPKNULL;
	long				ImageHeight;
	long				width, height;
	short				rev_flag = 0;
	CPKUInt16			current_page = 0;
	long				page_width;
	short				bpp;
	long				topskip = 0;
	CNCLPtr				lpCnclData;
	int					fd;


	lpCnclData		= lpCifRasterInfo->lpCnclData;
	rgbBuf			= lpCifRasterInfo->rgb_buf;
	ImageHeight		= lpCifRasterInfo->image_height;
	page_width		= lpCifRasterInfo->page_width;
	width			= lpCifRasterInfo->width;
	height			= lpCifRasterInfo->height;
	topskip			= lpCifRasterInfo->top_skip;
	bpp				= lpCifRasterInfo->bpp;
	rev_flag		= lpCifRasterInfo->rev_flag;
	current_page	= lpCifRasterInfo->page;
	fd				= lpCifRasterInfo->fd;

	bjf_pos_out_width( &lpbjinfo->bjfposinfo, &ImageWidth );
	bjf_pos_width_offset( &lpbjinfo->bjfposinfo, &width_offset );
	bjf_pos_height_offset( &lpbjinfo->bjfposinfo, &height_offset );
	bjf_pos_leftskip( &lpbjinfo->bjfposinfo, &leftskip );

	/* raster data before scaling */
	if ( srcBuf == CPKNULL ){
		srcBuf = (CPKByte CPKPTR)malloc( width * bpp );	
	}
	if ( srcBuf == CPKNULL ) goto onErr; 

		
	/* set scaling parameter */
	if ( (height < 1) || (ImageHeight < 0) ) goto onErr; /* Ver.3.60 */

	if ( ImageHeight == 0 ) { /* Ver.3.60 */
		goto EXIT;
	}
	else if ( ImageHeight == 1 ) { /* Ver.3.60 */
		if ( bjf_image_read_raster( &lpbjinfo->bjfimage, (char *)srcBuf, (long)width_offset, 
					(long)(CurrPos + height_offset), (long)width , rev_flag , current_page ) < 0 ){
			fprintf( stderr, "err in bjf_image_read_raster\n" );	
			goto onErr;
		}

		memset( rgbBuf, 0xFF, page_width * bpp );

		if ( h_extend( srcBuf, rgbBuf+(leftskip*bpp), width, ImageWidth, bpp ) < 0 ) goto onErr;

		/* if Media is BackPrintFilm and Thirts, mirror raster */
		switch ( lpbjfltdevice->bjfltMediaType ){
			case CND_MEDIA_BPF:
			case CND_MEDIA_TSHIRT:
				mirror_raster( rgbBuf, page_width, bpp );
				break;	
		}
 
		/* if duplex ON and longside-stapling and back page(even page), mirror raster */
		if ( ( !( current_page % 2 ) ) && rev_flag && ( root->isDuplex == ON ) ) mirror_raster( rgbBuf, page_width, bpp );

		/* Check white line */
		if ( whiteLine( rgbBuf, lpCnclData->width*bpp, bpp, (CPKUInt32 CPKPTR)&left, (CPKUInt32 CPKPTR)&right ) ){
			lpCnclData->WhiteLine = CND_WL_WHITE;
			lpCnclData->left_white = left;
			lpCnclData->right_white = right;
		}
		else{
			lpCnclData->WhiteLine = CND_WL_NOTWHITE;
			lpCnclData->left_white = left;
			lpCnclData->right_white = right;
		}
		
		/****** CNCL Source data ******/
		if ( CNCL_SourceData( lpCnclData ) < 0 ) goto onErr;

		do {
			/****** CNCL Raster data ******/
			if ( CNCL_RasterData( lpCnclData ) < 0 ) goto onErr;

			for ( i=0; i<lpCnclData->numBuf; i++ ){
				/* dump plural pages. */
				outCmdPlural( lpCnclData->rasterDataPtr[i].buf, lpCnclData->rasterDataPtr[i].size, lpbjinfo->prn, fd, root );
			}
			
			/****** CNCL Complete data ******/
			cnclerr = CNCL_CompleteData( lpCnclData );
			if ( cnclerr != 1 && cnclerr != 0 ){
				goto onErr;
			}
		} while ( cnclerr == 1 );
		lpCnclData->Vpos += 1 ;

		goto EXIT;
	}

	Quotient  = (height - 1) / (ImageHeight - 1);
	Rest 	  = (height - 1) % (ImageHeight - 1);
	TotalRest = 0;

	for ( y=0; y<ImageHeight; y++ ){

#if DEBUG
		fprintf( stderr, "y:%ld\tCurrPos:%ld\r",y,CurrPos );
#endif	

		/* calculate remainder */
		if ( TotalRest  * 2 >= (ImageHeight - 1) ){ /* Ver.3.60 */
		/* if ( (( 2 * TotalRest + Rest ) >> 1) >= ImageHeight ){ */
			TotalRest -= (ImageHeight - 1); /* Ver.3.60 */
			CurrPos++;
		}

		if ( CurrPos != PrevPos ){
			PrevPos = CurrPos;
			if ( bjf_image_read_raster( &lpbjinfo->bjfimage, (char *)srcBuf, (long)width_offset, 
						(long)(CurrPos + height_offset), (long)width , rev_flag , current_page ) < 0 ){
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

			/*---
				if duplex ON and longside-stapling and back page(even page), mirror raster
			---*/
			if ( ( !( current_page % 2 ) ) && rev_flag && ( root->isDuplex == ON ) ) mirror_raster( rgbBuf, page_width, bpp );
		}
			
		/* Check white line */
		if ( whiteLine( rgbBuf, lpCnclData->width*bpp, bpp, (CPKUInt32 CPKPTR)&left, (CPKUInt32 CPKPTR)&right ) ){
			lpCnclData->WhiteLine = CND_WL_WHITE;
			lpCnclData->left_white = left;
			lpCnclData->right_white = right;
		}
		else{
			lpCnclData->WhiteLine = CND_WL_NOTWHITE;
			lpCnclData->left_white = left;
			lpCnclData->right_white = right;
		}
		
		/****** CNCL Source data ******/
		result = CNCL_SourceData( lpCnclData );
		if ( result < 0 ){
			goto onErr;
		}

		do {
			/****** CNCL Raster data ******/
			result = CNCL_RasterData( lpCnclData );
			if ( result < 0 ) goto onErr;

			for ( i=0; i<lpCnclData->numBuf; i++ ){
				/* dump plural pages. */
				outCmdPlural( lpCnclData->rasterDataPtr[i].buf, lpCnclData->rasterDataPtr[i].size, lpbjinfo->prn, fd, root );
			}
			
			/****** CNCL Complete data ******/
			cnclerr = CNCL_CompleteData( lpCnclData );
			if ( cnclerr != 1 && cnclerr != 0 ){
				goto onErr;
			}
		} while ( cnclerr == 1 );
		lpCnclData->Vpos += 1 ;

		TotalRest += Rest;
		CurrPos += Quotient;
		
	}

EXIT:
	ret = 0;
	
onErr:
	if ( srcBuf ) free( srcBuf );
	return ret;

}



/*-------------------------------------------------------------*/
/* CNCL Flush                                                  */
/*-------------------------------------------------------------*/
static short flush_raster_data( CNCLPtr lpCnclData , LPBJFILTERINFO lpbjinfo , int fd , LPBJF_ROOT root )
{
	long				restLines, tmpRestLines;
	short				result;
	long				i;
	CNCLErr				cnclerr = -1;
	short				ret = -1;

	restLines = 1;
	do {
		/****** Data out ******/
		result = CNCL_FlushData( lpCnclData );
		if ( result < 0 ) goto onErr;

		/*--- Data ---*/
		for ( i=0; i<lpCnclData->numBuf; i++ ){
			/* use rasterDataPtr. */
			/* dump plural pages. */
			outCmdPlural( lpCnclData->rasterDataPtr[i].buf, lpCnclData->rasterDataPtr[i].size, lpbjinfo->prn, fd, root );
		}
		
		/****** CNCL Complete data ******/
		cnclerr = CNCL_CompleteData( lpCnclData );
		if ( cnclerr != 1 && cnclerr != 0 ){
			goto onErr;
		}

	} while ( cnclerr == 1 );
	
	ret = 0;
	
onErr:
	return ret;

	
}

/*-------------------------------------------------------------*/
/* obtain the total file byte size.                            */
/*-------------------------------------------------------------*/
static long get_file_bytes( char *filename )
{
	struct stat stat_buf;

	if( stat( filename, &stat_buf ) == 0 )
		return (long)stat_buf.st_size;
	else
		return -1;
}



#if DEBUGLOG

void create_log(void)
{
    FILE *path;
    int fd;

	strncpy(log_path_name, DEBUGLOGFILE, sizeof(log_path_name));
	log_path_name[sizeof(log_path_name)-1] = '\0';
	fd = mkstemp(log_path_name);
	if (fd < 0) return;
	close(fd);

	path = fopen(log_path_name, "r+");

	log_path = path;
	write_log("**********  LOG start  ***********\n");
}

void write_log(char *str)
{
	if(log_path == 0)
		return ;

	fwrite(str, 1, strlen(str), log_path);
	fflush(log_path);
}

void dispose_log(void)
{
	if(log_path == 0)
		return ;
	
	fclose(log_path);
	unlink(log_path_name);
}

#endif
