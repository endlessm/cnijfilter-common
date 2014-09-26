/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2013
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
#include <string.h>

#include "cpktypes.h"
#include "cncl.h"
#include "cncldef.h"
#include "bjfimage.h"
#include "bjferror.h"


/* function prototypes */
short bjf_image_open( LPBJF_IMAGEINFO, char * );
short bjf_image_init( LPBJF_IMAGEINFO , short , CPKUInt16 );
short bjf_image_read_raster( LPBJF_IMAGEINFO, char *, long, long, long , short , CPKUInt16 );
short bjf_image_flush( LPBJF_IMAGEINFO );
void  bjf_image_close( LPBJF_IMAGEINFO );
short bjf_image_get_imageformat( LPBJF_IMAGEINFO, short * );
short bjf_image_get_width( LPBJF_IMAGEINFO, long * );
short bjf_image_get_length( LPBJF_IMAGEINFO, long * );
short bjf_image_get_bpp( LPBJF_IMAGEINFO, short * );
short bjf_image_get_outputtype( LPBJF_IMAGEINFO, short * );
short bjf_image_get_resolution( LPBJF_IMAGEINFO, double *, double * );

static short bufmatch( char *, char *, short );

static short ppm_image_open( LPBJF_IMAGEINFO, char * );
static short ppm_image_init( LPBJF_IMAGEINFO );
static short ppm_image_read_raster( LPBJF_IMAGEINFO, char *, long, long, long );
static short ppm_image_flush( LPBJF_IMAGEINFO );
static short ppm_image_close( LPBJF_IMAGEINFO );
static short ppm_image_init_rev( LPBJF_IMAGEINFO );
static short ppm_image_read_raster_rev( LPBJF_IMAGEINFO, char *, long, long, long );
static void readPPMParam( FILE *, long *, long *, long * );
static long readwritePPMParam( FILE *, long *, long *, long * , int );

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
		else {
			fprintf( stderr, "Error : not support this image format\n");
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
	
		if ( bufmatch( (char*)PPMRAWSTART, (char *)tbuf, 2 ) > 0 )
			lpbjfimage->imageformat = BJFIMAGE_PPM;
		else{
			fprintf( stderr, "Error : not support this image format\n");
			goto onErr;
		}
	}

	/*--------------------------*/
	/*		Open Read Image		*/
	/*--------------------------*/
	switch( lpbjfimage->imageformat ){
		case BJFIMAGE_PPM:
			if ( ppm_image_open( lpbjfimage, filename  ) < 0 ) goto onErr;
			break;
		default:
			fprintf( stderr, "Error : not support this image format\n");
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
short bjf_image_init( LPBJF_IMAGEINFO lpbjfimage , short rev_flag , CPKUInt16 bjf_page )
/*-------------------------------------------------------------*/
{
	short				result = -1;
	
	switch( lpbjfimage->imageformat ){
		case BJFIMAGE_PPM:
			if( rev_flag && ( !( bjf_page%2 ) ) ){
				if ( (result = ppm_image_init_rev( lpbjfimage )) < 0 ) goto onErr;
			}else{
				if ( (result = ppm_image_init( lpbjfimage )) < 0 ) goto onErr;
			}
			break;
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
			long width,
			short rev_flag,
			CPKUInt16 bjf_page)
{
	short				result = -1;

	/*---------------------------*/
	/*	Supply raw raster data 	 */
	/*---------------------------*/
	switch ( lpbjfimage->imageformat ){
		case BJFIMAGE_PPM:
			if( rev_flag && ( !( bjf_page%2 ) ) ){
				if ( ppm_image_read_raster_rev( lpbjfimage, buf, x, y, width ) < 0 ) goto onErr;
			}else{
				if ( ppm_image_read_raster( lpbjfimage, buf, x, y, width ) < 0 ) goto onErr;
			}
			break;
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
		case BJFIMAGE_PPM:
			if ( ppm_image_flush( lpbjfimage ) < 0 ) goto onErr;
			break;
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
		case BJFIMAGE_PPM:
			ppm_image_close( lpbjfimage );
			break;
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
	char *tmp1;
	char *tmp2;
	
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
/*		ppm functions 											 */
/*---------------------------------------------------------------*/
static short ppm_image_open( LPBJF_IMAGEINFO lpbjfimage, char *filename )
{
	FILE			*readfp = NULL;
	unsigned char	buffer[5];
	short			result = -1;

	
	/* firstcall flg on for plural document */
	lpbjfimage->isfirstcall = 1;

	if ( filename != NULL ){
		if ( (readfp = fopen( filename, "rb" )) == NULL ) goto onErr;
		fread( buffer, 2, 1, readfp );
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

	if ( rstep > length ){
		rstep = length;
	}

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
				fread( rawbuf[0], RasterLength, rstep, readfp );
				lpbjfimage->readraster += rstep;			 
			}
			fread( rawbuf[0], RasterLength, laststep, readfp );
			lpbjfimage->readraster += laststep; 
		}
		else{
			for ( i=0; i<block; i++ ){
				fread( rawbuf[0], RasterLength, rstep, readfp );
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
	long			length, width, top;
	long			readraster, remain;
	long			RasterLength;
	short			bpp;
	unsigned char	*tmp = NULL;
	FILE			*readfp = NULL;
	short			result = -1;

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
		fread( tmp, RasterLength, remain, readfp );
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
		if ( lpbjfimage->bmp != stdin ){
			fclose( lpbjfimage->bmp );
			lpbjfimage->bmp = NULL;
		}
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

static short ppm_image_init_rev( LPBJF_IMAGEINFO lpbjfimage )
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
	long			fp_offset;

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

		if ( bufmatch( (char *)PPMRAWSTART, (char*)buffer, 2 ) < 0 ) goto onErr;
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

	if ( rstep > length ){
		rstep = length;
	}

	if ( (buf = (unsigned char *)malloc( MAXBUF )) == NULL ) goto onErr;

	rawbuf = (unsigned char **)calloc( sizeof(unsigned char *), rstep );
	if ( rawbuf == NULL ) goto onErr;

	for( i=0; i<rstep; i++ ){
		rawbuf[i] = buf + RasterLength * i;
	} 

	fp_offset = RasterLength * ( length - rstep );
	
	if ( fseek( readfp, fp_offset, SEEK_CUR ) != 0 ){
		goto onErr;
	}
	if ( !fread( buf, RasterLength, rstep,  readfp ) ){
		goto onErr;
	}
	lpbjfimage->readraster += rstep;

	/* go back to read start point */
	if ( fseek( readfp, -( RasterLength * rstep ) , SEEK_CUR ) != 0 ){
		goto onErr;
	}


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


static short ppm_image_read_raster_rev
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
			/* move to read start point */
			for ( i=0; i<(block-1); i++ ){
				if ( fseek( readfp, -(RasterLength * rstep), SEEK_CUR ) != 0 ){
					goto onErr;
				}
				lpbjfimage->readraster += rstep;
			}
			if ( fseek( readfp, -( RasterLength * laststep), SEEK_CUR ) != 0 ){
				goto onErr;
			}
			/* read last data */
			if ( !fread( rawbuf[rstep - laststep], RasterLength, laststep, readfp ) ){
				goto onErr;
			}
			/* go back to read start point */
			if ( fseek( readfp, -( RasterLength * laststep) , SEEK_CUR ) != 0 ){
				goto onErr;
			}
			lpbjfimage->readraster += laststep;
		}
		else{
			/* move to read start point */
			for ( i=0; i<block; i++ ){
				if ( fseek( readfp, -(RasterLength * rstep), SEEK_CUR ) != 0 ){
					goto onErr;
				}
				lpbjfimage->readraster += rstep;
			}
			/* read new data */
			if ( !fread( rawbuf[0], RasterLength, rstep, readfp ) ){
				goto onErr;
			}
			/* go back to read start point */
			if ( fseek( readfp, -(RasterLength * rstep), SEEK_CUR ) != 0 ){
				goto onErr;
			}
			lpbjfimage->readraster += rstep;
		}
	}	

	/* CurrentPosition */
	currentpos = ( rstep - 1 ) - ( y - top );

	/* Renew Top Positoin */
	lpbjfimage->top = top;

	/* Raster Data */
	in = rawbuf[currentpos] + ( width_offset * img_bpp );
	memcpy( buf, in, width*img_bpp );

	result = 0;
onErr:
	return result;
	
}


/*---------------------------------------------------------------*/
/* read ppm(one page) from stdin and write to tempfile.          */
/*---------------------------------------------------------------*/
int ppm_write_tmpfile( LPBJF_IMAGEINFO lpbjfimage, char *filename , char *outfile)
{
	FILE			*readfp = NULL;
	unsigned char	buffer[5];
	long			width = 0;
	long			length = 0;
	long			maxvalue = 0;
	short			bpp = 3;
	long			RasterLength = 0;	/* width of a raster */
	long			read_len = 0;
	long			imagesize = 0;
	short			retbyte;
	char			ch;
	unsigned char	*buf = NULL;
	long			parm_len = 0;
	int				fd = -1;
	int				w_size;
	long			block_num = 0;
	long			lastblock_size = 0;
	short			i;
	
	
	if ( filename != NULL ){
		if ( (readfp = fopen( filename, "rb" )) == NULL ) goto onErr;
		fread( buffer, 2, 1, readfp );
	}
	else {
		readfp = stdin;
	}

	
	/* check header */
	retbyte = fread( buffer, 2, 1, readfp );

	if ( !retbyte ){	/* end document */
		return CIF_FILE_END;	/* end document --> return */
	}

	if ( bufmatch( (char *)PPMRAWSTART, (char*)buffer, 2 ) < 0 ) goto onErr;

	/* make tempfile to output */
	fd = mkstemp(outfile);
	if(  fd  < 0 ){
		goto onErr;
	}

	/* write "P6" */
	w_size = write( fd , PPMRAWSTART , 2 );

	/* skip "0x0A" after "P6" */
	if ( (ch = fgetc( readfp )) == EOF ) goto onErr;	
	w_size = write( fd , &ch , 1 );


	/* read and write PPM parameter */
	parm_len = readwritePPMParam( readfp, &width, &length, &maxvalue , fd );

	if ( (!width) || (!length) ) goto onErr;
	
	/* parameter check */
	if ( maxvalue != 255 ) goto onErr;

	RasterLength = width * bpp;
	imagesize = RasterLength * length;

	/* allocate read buffer */
	if ( (buf = (unsigned char *)malloc( MAXBUF )) == NULL ) goto onErr;
	block_num = imagesize / MAXBUF;
	lastblock_size = imagesize % MAXBUF;

	/* read and write image raw data ( by MAXBUFSIZE unit ) */
	for( i=0 ; i<block_num ; i++ ){
		if ( !(read_len = fread( buf, 1, MAXBUF, readfp ) )){
			goto onErr;
		}
		w_size = write( fd , buf , MAXBUF );
	}
	
	if( lastblock_size > 0 ){
		if ( !(read_len = fread( buf, 1, lastblock_size, readfp ) )){
			goto onErr;
		}
		w_size = write( fd , buf , lastblock_size );
	}
	
	if( buf ) free(buf);
	close( fd );
	return fd;


onErr:
	if( fd >= 0 ){
		close( fd );
		unlink(outfile);
	}
	if( buf ) free(buf);
	return -1;
}


static long readwritePPMParam( FILE *fp, long *width, long *height, long *maxvalue , int fd )
{
	char	ch;
	char	wid_buf[25];
	char	len_buf[25];
	char	max_buf[25];
	char	*ptr = NULL;
	long	count = 0;
	int		w_size;

	ch = (char)fgetc( fp );

	/*  Skip comment */
	if ( ch == '#' ){
		while( (ch = (char)fgetc( fp )) != EOF ){
			ptr = wid_buf;
			if ( ch == 0x0A ) break;
		}	
	}
	else {
		w_size = write( fd , &ch , 1 );
		count++;
		wid_buf[0] = ch;
		ptr = wid_buf + 1;
	}

	/* Width and Length */
	while( (ch = (char)fgetc( fp )) != EOF ){
		w_size = write( fd , &ch , 1 );
		count++;
		
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
		w_size = write( fd , &ch , 1 );
		count++;
		
		if ( ch == 0x0A ) break;
		*ptr++ = ch;	
	}
	*ptr = 0x00;

	*maxvalue = atol( max_buf );
	
	return count; 
}

