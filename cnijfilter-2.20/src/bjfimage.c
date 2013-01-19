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

/*
** The code use "libtiff library"
** 
** Copyright (c) 1988-1997 Sam Leffler
** Copyright (c) 1991-1997 Silicon Graphics, Inc.
*/

/*
** The code use "libpng library"
** 
** Copyright (c) 1998-2001 Glenn Randers-Pehrson
*/

#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include "cpktypes.h"
#include "cncl.h"
#include "cncldef.h"
#include "bjfimage.h"
#include "bjferror.h"


/* function prototypes */
short bjf_image_open( LPBJF_IMAGEINFO, char * );
short bjf_image_init( LPBJF_IMAGEINFO );
short bjf_image_read_raster( LPBJF_IMAGEINFO, char *, long, long, long );
short bjf_image_flush( LPBJF_IMAGEINFO );
void  bjf_image_close( LPBJF_IMAGEINFO );
short bjf_image_get_imageformat( LPBJF_IMAGEINFO, short * );
short bjf_image_get_width( LPBJF_IMAGEINFO, long * );
short bjf_image_get_length( LPBJF_IMAGEINFO, long * );
short bjf_image_get_bpp( LPBJF_IMAGEINFO, short * );
short bjf_image_get_outputtype( LPBJF_IMAGEINFO, short * );
short bjf_image_get_resolution( LPBJF_IMAGEINFO, double *, double * );

static short bufmatch( char *, char *, short );
static short tiff_image_open( LPBJF_IMAGEINFO, char* );
static short tiff_image_init( LPBJF_IMAGEINFO );
static short tiff_image_read_raster( LPBJF_IMAGEINFO, char *, long, long, long );
static short tiff_image_flush( LPBJF_IMAGEINFO );
static short tiff_image_close( LPBJF_IMAGEINFO );
static short bmp_image_open( LPBJF_IMAGEINFO, char * );
static short bmp_image_init( LPBJF_IMAGEINFO );
static short bmp_image_read_raster( LPBJF_IMAGEINFO, char *, long, long, long );
static short bmp_image_flush( LPBJF_IMAGEINFO );
static short bmp_image_close( LPBJF_IMAGEINFO );
static short ppm_image_open( LPBJF_IMAGEINFO, char * );
static short ppm_image_init( LPBJF_IMAGEINFO );
static short ppm_image_read_raster( LPBJF_IMAGEINFO, char *, long, long, long );
static short ppm_image_flush( LPBJF_IMAGEINFO );
static short ppm_image_close( LPBJF_IMAGEINFO );
static void readPPMParam( FILE *, long *, long *, long * );

static short png_image_open( LPBJF_IMAGEINFO, char * );
static short png_image_init( LPBJF_IMAGEINFO );
static short png_image_read_raster( LPBJF_IMAGEINFO, char *, long, long, long );
static short png_image_flush( LPBJF_IMAGEINFO );
static short png_image_close( LPBJF_IMAGEINFO );


/*-------------------------------------------------------------*/
short bjf_image_open( LPBJF_IMAGEINFO lpbjfimage, char *filename )
/*-------------------------------------------------------------*/
{
	FILE				*tf = NULL;
	unsigned char		tbuf[10];
	short				result = -1;
	
	/*--- initialize image work parameter ---*/
	memset( (LPBJF_IMAGEINFO)lpbjfimage, 0, sizeof(BJF_IMAGEINFO) );
	
	/*-------------------------------*/
	/*		Select Image Format		 */
	/*-------------------------------*/
	/*---- in case input is stdin ---*/
	if ( filename == NULL ){
		if ( !fread( tbuf, 2, 1, stdin ) ) goto onErr;

		/*-- support ppm stdin --*/
		if ( bufmatch( (char *)PPMRAWSTART, (char *)tbuf, 2 ) > 0 ){
			lpbjfimage->imageformat = BJFIMAGE_PPM;
		}
		else if ( bufmatch( PNGSTART1, (char *)tbuf, 2 ) > 0 ){
				if ( !fread( tbuf, 6, 1, stdin ) ) goto onErr;
				if ( bufmatch( PNGSTART2, (char *)tbuf, 6 ) > 0 ){
					lpbjfimage->imageformat = BJFIMAGE_PNG;
				}
				else {
					bjf_error( "not support this image format", FILE_ERROR );
					goto onErr;
				}
		}
		else {
			bjf_error( "not support this image format", FILE_ERROR );
			goto onErr;
		}
	}
	/*--- in case input is file ---*/
	else{
		if ( (tf=fopen( filename, "rb" )) == NULL ) goto onErr; 

		/* top 4 byte of file */
		if ( !fread( tbuf, 8, 1, tf ) ) goto onErr;
		
		if ( tf != NULL ){
			fclose( tf );
			tf = NULL;
		}
	
		if ( ( bufmatch( (char*)TIFFSTART1, (char *)tbuf, 2 ) > 0 ) | ( bufmatch( (char*)TIFFSTART2, (char *)tbuf, 2 ) > 0 ) )
			lpbjfimage->imageformat = BJFIMAGE_TIFF;
		else if ( bufmatch( (char*)BMPSTART, (char *)tbuf, 2 ) > 0 )
			lpbjfimage->imageformat = BJFIMAGE_BMP;
		else if ( bufmatch( (char*)PPMRAWSTART, (char *)tbuf, 2 ) > 0 )
			lpbjfimage->imageformat = BJFIMAGE_PPM;
		else if ( bufmatch( (char*)PNGSTART, (char *)tbuf, 8 ) > 0 )
			lpbjfimage->imageformat = BJFIMAGE_PNG;
		else{
			bjf_error( "not support this image format", FILE_ERROR );
			goto onErr;
		}
	}

	/*--------------------------*/
	/*		Open Read Image		*/
	/*--------------------------*/
	switch( lpbjfimage->imageformat ){
		case BJFIMAGE_TIFF:
			if ( tiff_image_open( lpbjfimage, filename ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_BMP:
			if ( bmp_image_open( lpbjfimage, filename  ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_PPM:
			if ( ppm_image_open( lpbjfimage, filename  ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_PNG:
			if ( png_image_open( lpbjfimage, filename  ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_JPEG:
		default:
			bjf_error( "not support this image format", FILE_ERROR );
			goto onErr;
	}


	result = 0;
	return result;
	
onErr:
	if ( tf != NULL ) fclose( tf );
	return result;
}

/*--------------------------------------------------------
	bjf_image_init
		this function return value means
			Return Value	:		Mean
				1			:		page is
				0			:		no page
				-1			:		error
--------------------------------------------------------*/
/*-------------------------------------------------------------*/
short bjf_image_init( LPBJF_IMAGEINFO lpbjfimage )
/*-------------------------------------------------------------*/
{
	short				result = -1;
	
	switch( lpbjfimage->imageformat ){
		case BJFIMAGE_TIFF:
			if ( (result = tiff_image_init( lpbjfimage )) < 0 ) goto onErr;
			break;
		case BJFIMAGE_BMP:
			if ( (result = bmp_image_init( lpbjfimage )) < 0 ) goto onErr;
			break;
		case BJFIMAGE_PPM:
			if ( (result = ppm_image_init( lpbjfimage )) < 0 ) goto onErr;
			break;
		case BJFIMAGE_PNG:
			if ( (result = png_image_init( lpbjfimage )) < 0 ) goto onErr;
			break;
		case BJFIMAGE_JPEG:
		default:
			goto onErr;
	}

onErr:
	return result;
}

/*-------------------------------------------------------------*/
short bjf_image_read_raster( 
/*-------------------------------------------------------------*/
			LPBJF_IMAGEINFO lpbjfimage,
			char * buf,
			long x,
			long y,
			long width)
{
	short				result = -1;

	/*---------------------------*/
	/*	Supply raw raster data 	 */
	/*---------------------------*/
	switch ( lpbjfimage->imageformat ){
		case BJFIMAGE_TIFF:
			if ( tiff_image_read_raster( lpbjfimage, buf, x, y, width ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_BMP:
			if ( bmp_image_read_raster( lpbjfimage, buf, x, y, width ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_PPM:
			if ( ppm_image_read_raster( lpbjfimage, buf, x, y, width ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_PNG:
			if ( png_image_read_raster( lpbjfimage, buf, x, y, width ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_JPEG:
		default:
			goto onErr;
	}
	
	result = 0;
onErr:
	return result;
}


/*-------------------------------------------------------------*/
short bjf_image_flush( LPBJF_IMAGEINFO lpbjfimage )
/*-------------------------------------------------------------*/
{
	short				result = -1;

	/*---------------------------*/
	/*	Supply raw raster data   */ 
	/*---------------------------*/
	switch ( lpbjfimage->imageformat ){
		case BJFIMAGE_TIFF:
			if (  tiff_image_flush( lpbjfimage ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_BMP:
			if ( bmp_image_flush( lpbjfimage ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_PPM:
			if ( ppm_image_flush( lpbjfimage ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_PNG:
			if ( png_image_flush( lpbjfimage ) < 0 ) goto onErr;
			break;
		case BJFIMAGE_JPEG:
		default:
			goto onErr;
	}
	
	result = 0;
onErr:
	return result;
}


/*-------------------------------------------------------------*/
void bjf_image_close( LPBJF_IMAGEINFO lpbjfimage )
/*-------------------------------------------------------------*/
{
	/*------------------------*/
	/* 	 Close Read Image	  */
	/*------------------------*/
	switch ( lpbjfimage->imageformat ){
		case BJFIMAGE_TIFF:
			tiff_image_close( lpbjfimage );
			break;
		case BJFIMAGE_BMP:
			bmp_image_close( lpbjfimage );
			break;
		case BJFIMAGE_PPM:
			ppm_image_close( lpbjfimage );
			break;
		case BJFIMAGE_PNG:
			png_image_close( lpbjfimage );
			break;
		case BJFIMAGE_JPEG:
		default: break;
	}

}

/*-------------------------------------------------------------*/
short bjf_image_get_imageformat( LPBJF_IMAGEINFO lpbjfimage, short *imageformat )
/*-------------------------------------------------------------*/
{
	*imageformat = lpbjfimage->imageformat;
	return 0;
}

/*-------------------------------------------------------------*/
short bjf_image_get_width( LPBJF_IMAGEINFO lpbjfimage, long *width )
/*-------------------------------------------------------------*/
{
	*width = lpbjfimage->width;
	return 0;
}

/*-------------------------------------------------------------*/
short bjf_image_get_length( LPBJF_IMAGEINFO lpbjfimage, long *length )
/*-------------------------------------------------------------*/
{
	*length = lpbjfimage->length;
	return 0;
}

/*-------------------------------------------------------------*/
short bjf_image_get_rasterlength( LPBJF_IMAGEINFO lpbjfimage, long *rasterlength )
/*-------------------------------------------------------------*/
{
	*rasterlength = lpbjfimage->rasterlength;
	return 0;
}

/*-------------------------------------------------------------*/
short bjf_image_get_bpp( LPBJF_IMAGEINFO lpbjfimage, short *bpp )
/*-------------------------------------------------------------*/
{
	*bpp = lpbjfimage->bpp;
	return 0;
}

/*-------------------------------------------------------------*/
short bjf_image_get_outputtype( LPBJF_IMAGEINFO lpbjfimage, short *outputtype )
/*-------------------------------------------------------------*/
{
	*outputtype = lpbjfimage->outputtype;
	return 0;
}

/*-------------------------------------------------------------*/
short bjf_image_get_resolution( LPBJF_IMAGEINFO lpbjfimage, double *xresol, double *yresol )
/*-------------------------------------------------------------*/
{
	*xresol = lpbjfimage->xresolution;
	*yresol = lpbjfimage->yresolution;
	return 0;
}



static short bufmatch( char *buf1, char *buf2, short length )
{
	short i = 0;
	short result = -1;
	char __attribute__ ((unused)) *tmp1;
	char __attribute__ ((unused)) *tmp2;
	
	tmp1 = buf1;
	tmp2 = buf2;
	
	while( *buf1++ == *buf2++ ){
		i++;
		if ( i == length ){
			result = 1;
			break;
		}
	}
	
	return result;
}

/*---------------------------------------------------------------*/
/*		tiff functions 											 */
/*---------------------------------------------------------------*/
static short tiff_image_open( LPBJF_IMAGEINFO lpbjfimage, char *filename )
{
	TIFF				*tif = NULL;
	short				result = -1;
	
	if ( (tif = TIFFOpen( filename, "r" )) == NULL ) goto onErr;
	
	lpbjfimage->tif = tif;
	
	result = 0;
onErr:
	return result;
}

static short tiff_image_init( LPBJF_IMAGEINFO lpbjfimage )
{
	TIFF				*tif = NULL;
	uint32				width = 0;
	uint32				length = 0;
	unsigned short		bpp = 1;
	unsigned short		photometric = PHOTOMETRIC_RGB;
	float				x_resolution = 0;
	float				y_resolution = 0;
	short				outputtype;
	uint16				config;
	uint16				compress;
	short				result = -1;
	static short		flg = 0;
	short				resolution_unit = RESUNIT_INCH;

	/*---
		Tiff format do not support plural document.
		At first this api call, return 1, after second call return 0.
	---*/
	if ( flg == 0 ){
		flg = 1;
		result = 1;
	}
	else 
		return 0;
	
	/* copy global to local */
	tif = lpbjfimage->tif;
	
	if ( !TIFFGetField( tif, TIFFTAG_SAMPLESPERPIXEL, &bpp ) ){
		bpp = 1;
	}
	
	if ( !TIFFGetField( tif, TIFFTAG_IMAGELENGTH, &length ) ){
		bjf_error( "TIFF Cannnot get image length", FILE_ERROR );
		goto onErr;
	}
	if ( !TIFFGetField( tif, TIFFTAG_IMAGEWIDTH, &width ) ){
		bjf_error(  "TIFF Cannot get image width", FILE_ERROR );
		goto onErr;
	}
	
	if ( !TIFFGetField( tif, TIFFTAG_PHOTOMETRIC, &photometric ) ){
		bjf_error( "TIFF Cannot get photometric", FILE_ERROR );
		goto onErr;
	}
	
	if ( !TIFFGetField( tif, TIFFTAG_RESOLUTIONUNIT, &resolution_unit ) ){
		bjf_error( "TIFF Cannot get resolutionunit", FILE_ERROR );
	}

	if ( !TIFFGetField( tif, TIFFTAG_XRESOLUTION, &x_resolution ) ){
		bjf_error( "TIFF Cannot get x_resolution", FILE_ERROR );
	}
	
	if ( !TIFFGetField( tif, TIFFTAG_YRESOLUTION, &y_resolution ) ){
		bjf_error( "TIFF Cannot get y_resolution", FILE_ERROR );
	}

	/* support RESUNIT_CENTIMETER */
	switch( resolution_unit ){
		case RESUNIT_NONE:
			x_resolution = 0;
			y_resolution = 0;
			break;

		case RESUNIT_INCH:
			break;

		case RESUNIT_CENTIMETER:
			x_resolution *= 2.54;
			y_resolution *= 2.54;
			break;

		default:
			bjf_error( "TIFF Unknown resolutionunit", FILE_ERROR );
			goto onErr;
	}

	if ( !TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &config) ){
		bjf_error( "TIFF Cannot get config", FILE_ERROR );
		goto onErr;
	}

	if ( !TIFFGetField( tif, TIFFTAG_COMPRESSION, &compress ) ) ;
	else{
		/* COMPRESSION_NONE only */
		if ( compress != COMPRESSION_NONE )
		{
			bjf_error( "Cannot open this compressed image", FILE_ERROR );
			goto onErr;
		}
	}
			
	switch( photometric ){
		case PHOTOMETRIC_MINISBLACK:
		case PHOTOMETRIC_MINISWHITE:
			outputtype = BJFOUTPUT_GRAY;
			break;

		case PHOTOMETRIC_RGB:
			outputtype = BJFOUTPUT_COLOR;
			break;
			
		default:
			bjf_error( "TIFF Unknown photometric", FILE_ERROR );
			goto onErr;
	}
	
	lpbjfimage->width				= width;
	lpbjfimage->length				= length;
	lpbjfimage->bpp					= bpp;
	lpbjfimage->rasterlength		= width * bpp;
	lpbjfimage->outputtype 			= outputtype;
	lpbjfimage->xresolution = (double)x_resolution;
	lpbjfimage->yresolution = (double)y_resolution;

	return result;
onErr:
	result = -1;
	return result;

}

static short tiff_image_read_raster( LPBJF_IMAGEINFO lpbjfimage, char *buf, long x, long y, long width )
{
	char				*localbuf = NULL;
	long __attribute__ ((unused))	RasterLength;
	short				bpp;
	short				result = -1;
	
	
	/*
		here argment width do not use.
		because argment width is not real image width
		whose is defined by positon define module.
	*/
	bpp = lpbjfimage->bpp;
	RasterLength = lpbjfimage->rasterlength;
	
	localbuf = (char *)_TIFFmalloc( TIFFScanlineSize( lpbjfimage->tif ) );
	
	if ( localbuf == NULL ) goto onErr;
	
	if ( !TIFFReadScanline( lpbjfimage->tif, localbuf, y, 0 ) ){
		bjf_error( "Error in tiff_image_read_raster", FILE_ERROR );
		goto onErr;
	}

	memcpy( (char *)buf, (char *)localbuf + ( bpp * x ), (width * bpp) );
	
	_TIFFfree( localbuf );
		
	result = 0;
onErr:
	return result;
}

static short tiff_image_flush( LPBJF_IMAGEINFO lpbjfimage )
{
	return 0;
}

static short tiff_image_close( LPBJF_IMAGEINFO lpbjfimage )
{
	short				result = -1;
	
	if ( lpbjfimage->tif ){
		TIFFClose( lpbjfimage->tif );
		lpbjfimage->tif = NULL;
	}

	result = 0;
	return result;
}


/*---------------------------------------------------------------*/
/*		bmp functions 											 */
/*---------------------------------------------------------------*/
static short bmp_image_open( LPBJF_IMAGEINFO lpbjfimage, char *filename )
{
	FILE				*readfp = NULL;
	unsigned char		buffer[5];
	short				result = -1;
	size_t __attribute__ ((unused)) result1;

	/* firstcall flg on for plural document */
	lpbjfimage->isfirstcall = 1;

	if ( filename != NULL ){
		if ( (readfp = fopen( filename, "rb" )) == NULL ) goto onErr;
		result1 = fread( buffer, 2, 1, readfp );
	}
	else
		readfp = stdin;
		
	/* copy local to global */
	lpbjfimage->bmp = readfp;
	
	result = 0;
onErr:
	return result;
}

static short bmp_image_init( LPBJF_IMAGEINFO lpbjfimage )
{
	BITMAPFILEHEADER	bmpfile;
	BITMAPINFOHEADER	bmpinfo;
	long				i;
	long				rastLength;
	long				rawImage;
	FILE				*readfp = NULL;
	unsigned char		buffer[50];
	unsigned char		**rawbuf = NULL;
	unsigned char		*buf = NULL;
	long				rstep = 0;
	short __attribute__ ((unused))	retbyte;
	short				tmpflg;
	short				tmpformat;
	FILE				*tmpfp;
	short				result = -1;
	long				fp_offset;

	/*---
		we must init global parameters again, without isfirstcall and bmp,
			imageformat is inited in bmp_image_open. 
	---*/
	tmpflg    = lpbjfimage->isfirstcall;
	tmpformat = lpbjfimage->imageformat;
	tmpfp     = lpbjfimage->bmp;

	memset( (LPBJF_IMAGEINFO)lpbjfimage, 0, sizeof(BJF_IMAGEINFO) );

	lpbjfimage->isfirstcall = tmpflg;
	lpbjfimage->imageformat = tmpformat;
	lpbjfimage->bmp         = tmpfp;


	/* copy global to local */
	readfp = lpbjfimage->bmp;


	/* check plural page */
	if ( lpbjfimage->isfirstcall ){
		lpbjfimage->isfirstcall = 0;
	}
	else{
		/*-- not support plural document --*/
		return 0;
	}
	
	if ( !fread( buffer, 12, 1, readfp ) ) goto onErr;
	bmpfile.bfSize = TOLONG( buffer, 0 );				/* file size */
	bmpfile.bfOffBits = TOLONG( buffer, 8 );			/* offset till image data */


	if ( !fread( buffer, 40, 1, readfp ) ) goto onErr;
	bmpinfo.biSize = TOLONG( buffer,0x00  );			/* size of header, must be 40 byte */
	bmpinfo.biWidth = TOLONG( buffer, 0x04 );			/* image width */
	bmpinfo.biHeight = TOLONG( buffer, 0x08 );			/* image length */
	bmpinfo.biPlanes = TOSHORT( buffer, 0x0C );			/* image plane, must be 1 */
	bmpinfo.biBitCount = TOSHORT( buffer, 0x0E );		/* bit per pixel,must be 1,4,8,24 */
	bmpinfo.biCompression = TOLONG( buffer, 0x10 );		/* compression type */
	bmpinfo.biSizeImage = TOLONG( buffer, 0x14 );		/* compression image size */
	bmpinfo.biXPelsPerMeter = TOLONG( buffer, 0x18 );	/* xresolutino ( pixels per 1m )*/
	bmpinfo.biYPelsPerMeter = TOLONG( buffer, 0x1C );	/* yresolution ( pixels per 1m )*/
	bmpinfo.biClrUsed = TOLONG( buffer, 0x20 );			/* used color */
	bmpinfo.biClrImportant = TOLONG( buffer, 0x24 );	/* color map */

	if ( (bmpinfo.biBitCount != 24) || (bmpfile.bfOffBits != 54) ){
		fprintf( stderr, "can not suport this bmp file\n");
		goto onErr;
	}
	
	/*--- get image raw data (by MAXBUFSIZE unit) ---*/
	rawImage = bmpfile.bfSize - bmpfile.bfOffBits;
	rastLength = rawImage / bmpinfo.biHeight;

	rstep = MAXBUF / rastLength;

	if ( rstep == 0 ){
		bjf_error( "Error in bmp_image_init", FILE_ERROR );
	} 
	
	if ( (buf = (unsigned char *)malloc( MAXBUF )) == NULL ) goto onErr;
	
	rawbuf = (unsigned char **)calloc(sizeof(unsigned char *), rstep );
	if ( rawbuf == NULL ) goto onErr;

	for( i=0; i<rstep; i++ ){
		rawbuf[i] = buf + rastLength * i;
	}
	
	/*--- read reverse ---*/
	fp_offset = rastLength * ( bmpinfo.biHeight - rstep );
	if( ( bmpinfo.biHeight - rstep ) < 0 )
		fp_offset = 0;

	if ( fseek( readfp, fp_offset, SEEK_CUR ) != 0 ) goto onErr;

	if ( !fread( buf, rastLength, rstep,  readfp ) ) goto onErr;
	lpbjfimage->readraster += rstep;


	/*--- set cif parameter ---*/
	lpbjfimage->width = bmpinfo.biWidth;
	lpbjfimage->length = bmpinfo.biHeight;
	lpbjfimage->rasterlength = rastLength;
	lpbjfimage->bpp = 3;
	lpbjfimage->outputtype = BJFOUTPUT_COLOR;
	lpbjfimage->xresolution = (double)bmpinfo.biXPelsPerMeter * 0.0254;
	lpbjfimage->yresolution = (double)bmpinfo.biYPelsPerMeter * 0.0254;
	lpbjfimage->bmpraw = rawbuf;
	lpbjfimage->rstep = rstep;
	lpbjfimage->top = 0;

	result = 1;
onErr:
	return result;
}

static short bmp_image_read_raster( LPBJF_IMAGEINFO lpbjfimage, char *buf, long width_offset, long y, long width )
{
	unsigned char 		*in = NULL;
	short				img_bpp;
	long				i;
	long				img_width;
	long				img_height;
	long				rasterlength;
	long				top=0;
	long				skip=0;
	long				rstep=0;
	long				laststep=0;
	long				currentmax=0;
	long				currentpos=0;
	short				block=0;
	short				isfinalblock=0;
	unsigned char 		**rawbuf=NULL;
	FILE				*readfp= NULL;
	short				result = -1;
	size_t __attribute__ ((unused)) result1;

	/*--- current area check ---*/
	img_bpp = lpbjfimage->bpp;
	img_width = lpbjfimage->width;
	img_height = lpbjfimage->length;
	rasterlength = lpbjfimage->rasterlength;
	
	if ( y > img_height ){
		bjf_error( "Error in bmp_image_read_raster:img_height_over", MEMORY_ERROR );
		goto onErr;
	}
	
	if ( width > img_width ){
		bjf_error( "Error in bmp_image_read_raster:img_width_over", MEMORY_ERROR );
		goto onErr;
	}

	/*
		if we must renew current allocate memory, do it.
	*/
	
	/*--- copy global to local ---*/
	top = lpbjfimage->top;
	rstep = lpbjfimage->rstep;
	readfp = lpbjfimage->bmp;
	rawbuf = lpbjfimage->bmpraw;

	if ( y < top ) goto onErr;

	currentmax = top + rstep;
	skip = y - currentmax;

	/*--- load new data from file or stdin ---*/
	if ( skip >= 0 ){
		block = skip/rstep + 1;
		top += (block * rstep);
		currentmax = top + rstep;

		if ( currentmax > img_height ){
			isfinalblock = 1;
			laststep = img_height - top;
		}
		
		if ( isfinalblock == 1 ){
			for ( i=0; i<(block-1); i++ ){
				result1 = fread( rawbuf[0], rasterlength, rstep, readfp );
				lpbjfimage->readraster += rstep;
			}
			/*--- read reverse ---*/
			fseek( readfp, 54L, SEEK_SET );
			result1 = fread( rawbuf[rstep-laststep], rasterlength, laststep, readfp );
			lpbjfimage->readraster += laststep;
		}
		else{
			/*--- read reverse ---*/
			fseek( readfp, ( rasterlength * (img_height - rstep - top) + 54L ), SEEK_SET );
			result1 = fread( rawbuf[0], rasterlength, rstep, readfp );
			lpbjfimage->readraster += rstep;
		}	
	}

	/*--- currentposition ---*/
	/*--- read reverse ---*/
	if( img_height < rstep )
		currentpos = img_height - y + top -1 ;
	else
		currentpos = rstep - y + top -1 ;

	/*--- renew top position ---*/
	lpbjfimage->top = top;

	/*--- change bgr to rgb ---*/
	/*--- read reverse ---*/
	in = rawbuf[currentpos] + ( width_offset * img_bpp );
	
	for ( i=0; i<width; i++ ){
		buf[0] = in[2];
		buf[1] = in[1];
		buf[2] = in[0];
		
		/*--- read reverse ---*/
		in += img_bpp;
		buf += img_bpp;
	}
	
	
	result = 0;
onErr:
	return result;

}

static short bmp_image_flush( LPBJF_IMAGEINFO lpbjfimage )
{
	long				length = 0;
	long __attribute__ ((unused))	top = 0;
	long				readraster = 0;
	long				rasterlength = 0;
	long				remain = 0;
	unsigned char		*tmp;
	FILE				*readfp = NULL;
	short				result = -1;
	size_t __attribute__ ((unused)) result1;
	

	/* copy global to local */
	top = lpbjfimage->top;
	length = lpbjfimage->length;
	readraster = lpbjfimage->readraster;
	rasterlength = lpbjfimage->rasterlength;
	readfp = lpbjfimage->bmp;

	remain = length - readraster;

	if ( remain > 0 ){
		if ( (tmp = malloc( remain * rasterlength )) == NULL ) goto onErr;
	
		result1 = fread( tmp, rasterlength, remain, readfp );
		
		lpbjfimage->readraster = 0;

	}
	
	if ( lpbjfimage->bmpraw ){
		if ( lpbjfimage->bmpraw[0] ){
			free( lpbjfimage->bmpraw[0] );
			lpbjfimage->bmpraw[0] = NULL;
		}
		free( lpbjfimage->bmpraw );
		lpbjfimage->bmpraw = NULL;
	}
	
	result = 0;
onErr:
	return result;
}

static short bmp_image_close( LPBJF_IMAGEINFO lpbjfimage )
{
	short				result = -1;
	
	if ( lpbjfimage->bmp ){
		fclose( lpbjfimage->bmp );
		lpbjfimage->bmp = NULL;
	}
	
	result = 0;
	return result;
}


/*---------------------------------------------------------------*/
/*		ppm functions 											 */
/*---------------------------------------------------------------*/
static short ppm_image_open( LPBJF_IMAGEINFO lpbjfimage, char *filename )
{
	FILE			*readfp = NULL;
	unsigned char	buffer[5];
	short			result = -1;
	size_t __attribute__ ((unused)) result1;

	
	/* firstcall flg on for plural document */
	lpbjfimage->isfirstcall = 1;

	if ( filename != NULL ){
		if ( (readfp = fopen( filename, "rb" )) == NULL ) goto onErr;
		result1 = fread( buffer, 2, 1, readfp );
	}
	else {
		readfp = stdin;
	}
	
	lpbjfimage->bmp = readfp;

	result = 0;
onErr:
	return result;
}


static short ppm_image_init( LPBJF_IMAGEINFO lpbjfimage )
{
	FILE			*readfp;
	FILE			*tmpfp;
	unsigned char	buffer[50];
	unsigned char	*buf = NULL;
	unsigned char	**rawbuf = NULL;
	short			tmpflg;
	short			tmpformat;
	short			retbyte = 0;
	short			bpp = 3;
	long			width = 0;
	long			length = 0;
	long			maxvalue = 0;
	long			rstep = 0;
	long			RasterLength = 0;
	long			i;
	short			result = -1;
	char			ch;

	/*---
		We must init global parameters again, without isfirstcall and 
			ppm imageformat is inited in ppmraw_image_open
	---*/
	tmpflg    = lpbjfimage->isfirstcall;
	tmpformat = lpbjfimage->imageformat;
	tmpfp     = lpbjfimage->bmp;

	memset( (LPBJF_IMAGEINFO)lpbjfimage, 0, sizeof(BJF_IMAGEINFO) );

	lpbjfimage->isfirstcall = tmpflg;
	lpbjfimage->imageformat = tmpformat;
	lpbjfimage->bmp			= tmpfp;

	
	readfp = lpbjfimage->bmp;

	/*--- 
		when second page,
	---*/
	if ( lpbjfimage->isfirstcall ){
		lpbjfimage->isfirstcall = 0;
	}
	else{
		retbyte = fread( buffer, 2, 1, readfp );

		if ( !retbyte ){	/* end document */
			result = 0;
			goto onErr;
		}

		if ( bufmatch( (char*)PPMRAWSTART, (char*)buffer, 2 ) < 0 ) goto onErr;
	}

	/* skip "0x0A" after "P6" */
	if ( (ch = fgetc( readfp )) == EOF ) goto onErr;	

	readPPMParam( readfp, &width, &length, &maxvalue );
	
	if ( (!width) || (!length) ) goto onErr;
	
	RasterLength = width * bpp;
	
	/* parameter check */
	if ( maxvalue != 255 ) goto onErr;

	/*--- Get image raw data ( by MAXBUFSIZE unit ) ---*/
	rstep = MAXBUF / RasterLength;

	if ( (buf = (unsigned char *)malloc( MAXBUF )) == NULL ) goto onErr;

	rawbuf = (unsigned char **)calloc( sizeof(unsigned char *), rstep );
	if ( rawbuf == NULL ) goto onErr;

	for( i=0; i<rstep; i++ ){
		rawbuf[i] = buf + RasterLength * i;
	} 

	if ( !fread( buf, (width*bpp), rstep, readfp ) ) goto onErr;
	lpbjfimage->readraster += rstep;

	/*--- Set cif Parameter ---*/
	lpbjfimage->width        = width;
	lpbjfimage->length       = length;
	lpbjfimage->bpp          = bpp;
	lpbjfimage->rasterlength = width * bpp;
	lpbjfimage->outputtype   = BJFOUTPUT_COLOR;
	lpbjfimage->xresolution  = 0;
	lpbjfimage->yresolution  = 0;
	lpbjfimage->bmpraw       = rawbuf;
	lpbjfimage->rstep        = rstep;
	lpbjfimage->top          = 0;

	result = 1;
onErr:
	return result;	
}	


static short ppm_image_read_raster
( 
	LPBJF_IMAGEINFO lpbjfimage,
	char			*buf,
	long			width_offset,
	long			y,
	long			width 
)
{
	unsigned char	*in = NULL;
	unsigned char	**rawbuf = NULL;
	short			img_bpp, img_width, img_length;
	short			block, isfinalblock;
	long			i;
	long			top, skip, rstep, laststep;
	long			currentmax, currentpos;
	long			RasterLength = 0;
	FILE			*readfp = NULL;
	short			result = -1;
	size_t __attribute__ ((unused)) result1;


	/*---
		Current Aread Check 
	---*/
	img_bpp		 = lpbjfimage->bpp;
	img_width    = lpbjfimage->width;
	img_length   = lpbjfimage->length;
	RasterLength = lpbjfimage->rasterlength;

	/*	Parameter Error Check */
	if ( (y>img_length) || (width>img_width) ){
		bjf_error( "Error in ppm_image_raster", MEMORY_ERROR );
		goto onErr;
	}

	/*---
		If We must renew current allocate memory, do it.
	---*/
	top          = lpbjfimage->top;
	rstep        = lpbjfimage->rstep;
	readfp       = lpbjfimage->bmp;
	rawbuf	     = lpbjfimage->bmpraw;
	currentmax   = top + rstep;
	skip         = y - currentmax;
	
	block    = isfinalblock = 0;
	laststep = currentpos   = 0;

	/* Parameter Error Check */
	if ( y < top ) goto onErr;
	

	/*	load new data from file or stdin */
	if ( skip >=0 ){
		block      = ( skip/rstep ) + 1;
		top       += ( block * rstep );
		currentmax = top + rstep;

		if ( currentmax > img_length ){
			isfinalblock = 1;
			laststep     = img_length - top;
		}

		if ( isfinalblock == 1 ){
			for ( i=0; i<(block-1); i++ ){
				result1 = fread( rawbuf[0], RasterLength, rstep, readfp );
				lpbjfimage->readraster += rstep;			 
			}
			result1 = fread( rawbuf[0], RasterLength, laststep, readfp );
			lpbjfimage->readraster += laststep; 
		}
		else{
			for ( i=0; i<block; i++ ){
				result1 = fread( rawbuf[0], RasterLength, rstep, readfp );
				lpbjfimage->readraster += rstep;
			}
		}
	}	

	/* CurrentPosition */
	currentpos = y - top;

	/* Renew Top Positoin */
	lpbjfimage->top = top;

	/* Raster Data */
	in = rawbuf[currentpos] + ( width_offset * img_bpp );
	memcpy( buf, in, width*img_bpp );

	result = 0;
onErr:
	return result;
	
}

static short ppm_image_flush( LPBJF_IMAGEINFO lpbjfimage )
{
	long			length, width, __attribute__ ((unused))  top;
	long			readraster, remain;
	long			RasterLength;
	short			bpp;
	unsigned char	*tmp = NULL;
	FILE			*readfp = NULL;
	short			result = -1;
	size_t __attribute__ ((unused)) result1;

	top        = lpbjfimage->top;
	width	   = lpbjfimage->width;
	length     = lpbjfimage->length;
	bpp	       = lpbjfimage->bpp;
	readraster = lpbjfimage->readraster;
	readfp     = lpbjfimage->bmp;
	RasterLength = lpbjfimage->rasterlength;

	/* Remain Raster */
	remain = length - readraster;

	if ( remain > 0 ){
		if ( (tmp = malloc( remain * (width*bpp))) == NULL ) goto onErr;
		result1 = fread( tmp, RasterLength, remain, readfp );
		lpbjfimage->readraster = 0;
	}

	if ( lpbjfimage->bmpraw ){
		if ( lpbjfimage->bmpraw[0] ){
			free( lpbjfimage->bmpraw[0] );
			lpbjfimage->bmpraw[0] = NULL;
		}
		free( lpbjfimage->bmpraw );
		lpbjfimage->bmpraw = NULL;	
	}

	result = 0;
onErr:
	return result;	
}

static short ppm_image_close( LPBJF_IMAGEINFO lpbjfimage )
{
	short			result = -1;


	if ( lpbjfimage->bmp ){
		fclose( lpbjfimage->bmp );
		lpbjfimage->bmp = NULL;
	}
	
	result = 0;
	return result;
}

static void readPPMParam( FILE *fp, long *width, long *height, long *maxvalue )
{
	char ch;
	char wid_buf[25];
	char len_buf[25];
	char max_buf[25];
	char *ptr = NULL;

	ch = (char)fgetc( fp );

	/*  Skip comment */
	if ( ch == '#' ){
		while( (ch = (char)fgetc( fp )) != EOF ){
			ptr = wid_buf;
			if ( ch == 0x0A ) break;
		}	
	}
	else {
		wid_buf[0] = ch;
		ptr = wid_buf + 1;
	}

	/* Width and Length */
	while( (ch = (char)fgetc( fp )) != EOF ){
		if ( ch == 0x0A ) break;
		else if ( ch == ' ' ){
			*ptr = 0x00;
			ptr = len_buf;
			continue;
		}
		*ptr++ = ch;
	}
	*ptr = 0x00;

	*width  = atol( wid_buf );
	*height = atol( len_buf );

	/* Max Value */
	ptr = max_buf;
	while( (ch = (char)fgetc( fp )) != EOF ){
		if ( ch == 0x0A ) break;
		*ptr++ = ch;	
	}
	*ptr = 0x00;

	*maxvalue = atol( max_buf );
	
	return ; 
}


/*---------------------------------------------------------------*/
/*		png functions 											 */
/*---------------------------------------------------------------*/
static short png_image_open( LPBJF_IMAGEINFO lpbjfimage, char *filename )
{
	FILE			*readfp = NULL;
	unsigned char	buffer[10];
	short			result = -1;
	size_t __attribute__ ((unused)) result1;


	/* firstcall flg on for plural document */
	lpbjfimage->isfirstcall = 1;

	if ( filename != NULL ){
		if ( (readfp = fopen( filename, "rb" )) == NULL ) goto onErr;
		result1 = fread( buffer, 8, 1, readfp );
	}
	else {
		readfp = stdin;
	}
	
	lpbjfimage->bmp = readfp;

	result = 0;

onErr:
	return result;
}


static short png_image_init( LPBJF_IMAGEINFO lpbjfimage )
{
	FILE			*readfp;
	FILE			*tmpfp;
	unsigned char __attribute__ ((unused)) buffer[50];
	unsigned char	*buf = NULL;
	unsigned char	**rawbuf = NULL;
	short			tmpflg;
	short			tmpformat;
	short __attribute__ ((unused)) retbyte = 0;
	short			bpp = 3;
	/* Modifications to fit the new libpng interface. */
	png_uint_32		width = 0;
	png_uint_32		length = 0;
//	long			width = 0;
//	long			length = 0;
	long			rstep = 0;
	long			RasterLength = 0;
	long			i;
	short			result = -1;
	char __attribute__ ((unused)) ch;
	png_structp		png_p;
	png_infop		info_p;
	int				bit_depth, color_type, interlace_type;
	long			rstep2 = 0;

	png_color_16 __attribute__ ((unused)) my_background, *image_background;
	int __attribute__ ((unused)) intent,screen_gamma;


	/*---
		We must init global parameters again, without isfirstcall and 
			png imageformat is inited in png_image_open
	---*/
	tmpflg    = lpbjfimage->isfirstcall;
	tmpformat = lpbjfimage->imageformat;
	tmpfp     = lpbjfimage->bmp;

	memset( (LPBJF_IMAGEINFO)lpbjfimage, 0, sizeof(BJF_IMAGEINFO) );

	lpbjfimage->isfirstcall = tmpflg;
	lpbjfimage->imageformat = tmpformat;
	lpbjfimage->bmp			= tmpfp;

	readfp = lpbjfimage->bmp;

	/*---
		png format do not support plural document.
		At first this api call, return 1, after second call return 0.
	---*/
	if ( lpbjfimage->isfirstcall ){
		lpbjfimage->isfirstcall = 0;
	}
	else{
		return 0;
	}

	/*-- call pnglib function --*/
	png_p = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_p == NULL){
		goto onErr;
	}

	info_p = png_create_info_struct (png_p);
	if (info_p==NULL){
		png_destroy_read_struct(&png_p, (png_infopp)NULL, (png_infopp)NULL);
		goto onErr;
	}

	/* Modifications to fit the new libpng interface. */
	//if (setjmp (png_p->jmpbuf))
	if (setjmp(png_jmpbuf(png_p)))
	{
		png_destroy_read_struct(&png_p, &info_p, (png_infopp)NULL);
		goto onErr;
	}

	png_init_io(png_p, readfp);
	png_set_sig_bytes(png_p, 8);

	png_read_info( png_p, info_p );

	png_get_IHDR( png_p, info_p, (unsigned long *)&width, (unsigned long *)&length, &bit_depth,
	              &color_type, &interlace_type, NULL, NULL);

	/* not support Interlace */
	if ( interlace_type ){
		bjf_error( "Cannot open this interlace_type", FILE_ERROR );
		goto onErr;
	}

	/* 16 bit/color */
	png_set_strip_16(png_p);

	/* alpha */
	png_set_strip_alpha(png_p);

	/* packing */
	png_set_packing(png_p);

	/* paletted colors */
	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_expand(png_p);

	/* grayscale */
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand(png_p);

	/* full alpha channels */
	if (png_get_valid(png_p, info_p, PNG_INFO_tRNS))
		png_set_expand(png_p);

	if ( color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA ){
		png_set_gray_to_rgb(png_p);
	}

	png_read_update_info(png_p, info_p);

	if ( (!width) || (!length) ) goto onErr;

	RasterLength = width * bpp;

	/*--- Get image raw data ( by MAXBUFSIZE unit ) ---*/
	rstep = MAXBUF / RasterLength;

	if ( (buf = (unsigned char *)malloc( MAXBUF )) == NULL ) goto onErr;

	rawbuf = (unsigned char **)calloc( sizeof(unsigned char *), rstep );
	if ( rawbuf == NULL ) goto onErr;

	for( i=0; i<rstep; i++ )
		rawbuf[i] = buf + RasterLength * i;

	/*-- all Data read --*/
	/* png_read_image(png_p, rawbuf); */

	if( rstep < length )
		rstep2 = rstep;
	else
		rstep2 = length;

	/*-- some rasters read --*/
	png_read_rows(png_p, &rawbuf[0], NULL, rstep2);

	lpbjfimage->readraster += rstep2;

	/* copy */
	lpbjfimage->png_ptr = (char*)png_p;
	lpbjfimage->info_ptr = (char*)info_p;

	/*--- Set cif Parameter ---*/
	lpbjfimage->width        = width;
	lpbjfimage->length       = length;
	lpbjfimage->bpp          = bpp;
	lpbjfimage->rasterlength = width * bpp;
	lpbjfimage->outputtype   = BJFOUTPUT_COLOR;
	lpbjfimage->xresolution  = 0;
	lpbjfimage->yresolution  = 0;
	lpbjfimage->bmpraw       = rawbuf;
	lpbjfimage->rstep        = rstep;
	lpbjfimage->top          = 0;

	result = 1;

onErr:
	return result;	
}	


static short png_image_read_raster
( 
	LPBJF_IMAGEINFO lpbjfimage,
	char			*buf,
	long			width_offset,
	long			y,
	long			width 
)
{
	unsigned char	*in = NULL;
	unsigned char	**rawbuf = NULL;
	short			img_bpp, img_width, img_length;
	short			block, isfinalblock;
	long			i;
	long			top, skip, rstep, laststep;
	long			currentmax, currentpos;
	long __attribute__ ((unused)) RasterLength = 0;
	FILE __attribute__ ((unused)) *readfp = NULL;
	short			result = -1;
	png_structp		png_ptr;

	/*---
		Current Aread Check 
	---*/
	img_bpp		 = lpbjfimage->bpp;
	img_width    = lpbjfimage->width;
	img_length   = lpbjfimage->length;
	RasterLength = lpbjfimage->rasterlength;

	/* copy */
	png_ptr = (png_structp)lpbjfimage->png_ptr;

	/*	Parameter Error Check */
	if ( (y>img_length) || (width>img_width) ){
		bjf_error( "Error in png_image_raster", MEMORY_ERROR );
		goto onErr;
	}

	/*---
		If We must renew current allocate memory, do it.
	---*/
	top          = lpbjfimage->top;
	rstep        = lpbjfimage->rstep;
	readfp       = lpbjfimage->bmp;
	rawbuf	     = lpbjfimage->bmpraw;
	currentmax   = top + rstep;
	skip         = y - currentmax;
	
	block    = isfinalblock = 0;
	laststep = currentpos   = 0;

	/* Parameter Error Check */
	if ( y < top ) goto onErr;

	/*	load new data from file or stdin */
	if ( skip >=0 ){
		block      = ( skip/rstep ) + 1;
		top       += ( block * rstep );
		currentmax = top + rstep;

		if ( currentmax > img_length ){
			isfinalblock = 1;
			laststep     = img_length - top;
		}

		if ( isfinalblock == 1 ){
			for ( i=0; i<(block-1); i++ ){
				png_read_rows(png_ptr, &rawbuf[0], NULL, rstep);
				lpbjfimage->readraster += rstep;
			}
			png_read_rows(png_ptr, &rawbuf[0], NULL, laststep);
			lpbjfimage->readraster += laststep;
		}
		else{
			for ( i=0; i<block; i++ ){
				png_read_rows(png_ptr, &rawbuf[0], NULL, rstep);
				lpbjfimage->readraster += rstep;
			}
		}
	}	

	/* CurrentPosition */
	currentpos = y - top;

	/* Renew Top Positoin */
	lpbjfimage->top = top;

	/* Raster Data */
	in = rawbuf[currentpos] + ( width_offset * img_bpp );
	memcpy( buf, in, width*img_bpp );

	result = 0;
onErr:
	return result;
	
}

static short png_image_flush( LPBJF_IMAGEINFO lpbjfimage )
{
	png_structp		png_ptr;
	png_infop		info_ptr;
	FILE __attribute__ ((unused)) *readfp;
	short			result = -1;

	png_ptr = (png_structp)lpbjfimage->png_ptr;
	info_ptr = (png_infop)lpbjfimage->info_ptr;

/* for second page and large data */
/*	png_read_end(png_ptr, info_ptr); */
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
	lpbjfimage->png_ptr = NULL;	
	lpbjfimage->info_ptr = NULL;

	return 0;
//onErr:
	return result;	

}

static short png_image_close( LPBJF_IMAGEINFO lpbjfimage )
{
	short			result = -1;

	if ( lpbjfimage->png_ptr )
		lpbjfimage->png_ptr = NULL;
	if ( lpbjfimage->info_ptr )
		lpbjfimage->info_ptr = NULL;

	if ( lpbjfimage->bmp ){
		fclose( lpbjfimage->bmp );
		lpbjfimage->bmp = NULL;
	}
	
	result = 0;
	return result;
}


