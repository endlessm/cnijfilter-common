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

#ifndef __BJFIMAGE_H__
#define	__BJFIMAGE_H__

#include <tiffio.h>

/*--- image format that support in this module ---*/
#define BJFIMAGE_TIFF		10
#define BJFIMAGE_JPEG		11
#define BJFIMAGE_GIF		12
#define BJFIMAGE_BMP		13
#define BJFIMAGE_PPM		14
/*-- for PNG  --*/
#define BJFIMAGE_PNG		15


/*--- output type ---*/
#define BJFOUTPUT_COLOR		30
#define BJFOUTPUT_GRAY		31
#define BJFOUTPUT_INDEX		32

/*--- image data header discription ---*/
#define TIFFSTART1			"\x49\x49\x2A\x00"
#define TIFFSTART2			"\x4D\x4D\x00\x2A"
#define JPEGSTART			"\xFF\xD8"
#define BMPSTART			"\x42\x4D"
#define PPMRAWSTART			"\x50\x36"			/* "P6" */
/*-- for PNG  --*/
#define PNGSTART			"\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"
#define PNGSTART1			"\x89\x50"
#define PNGSTART2			"\x4E\x47\x0D\x0A\x1A\x0A"
/*-- for PNG  --*/
#define PNGDATAEND			"\x49\x45\x4E\x44\xAE\x42\x60\x82"

/*--- bmp support ---*/
#define MAXBUF	0x00100000

#define CIF_FILE_END (-2)

#define	TOLONG(buffer, off) (buffer[(off)] | buffer[(off)+1]<<8 | buffer[(off)+2]<<16 | buffer[(off)+3]<<24)
#define TOSHORT(buffer, off) (buffer[(off)] | buffer[(off)+1]<<8)

typedef struct BITMAPFILEHEADER{
  short bfType;  			/* ASCII "BM" */
  long bfSize;   			/* file size */
  short bfReserved1;  		/* reserv */
  short bfReserved2;  		/* reserv */
  long bfOffBits;  			/* offset to image */
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER{
  long biSize; 				/* size of header, must be 40 byte */
  long biWidth;  			/* image width */
  long biHeight;  			/* image length */
  short biPlanes;  			/* image plane, must be 1 */
  short biBitCount;  		/* bit per pixel,must be 1,4,8,24 */
  long biCompression;		/* compression type */
  long biSizeImage;  		/* compression image size */
  long biXPelsPerMeter;  	/* xresolutino ( pixels per 1m )*/
  long biYPelsPerMeter;  	/* yresolution ( pixels per 1m )*/
  long biClrUsed;  			/* used color */
  long biClrImportant;  	/* color map */
} BITMAPINFOHEADER;

/*--- work space for image process module ---*/
typedef struct BJF_IMAGEINFO
{
	/* for tiff Parameter */
	TIFF				*tif;
	unsigned char		**jpgraw;
	/* for bmp and ppm Parameter */
	FILE				*bmp;
	unsigned char		**bmpraw;
	short				isfirstcall;
	long				rstep;
	long				top;
	long				readraster;
	/* for png Parameter */
	char				*png_ptr;
	char				*info_ptr;
	/* common Parameter */
	short				imageformat;
	long				width;
	long				length;
	long				rasterlength;
	short				bpp;
	short				outputtype;
	double				xresolution;
	double				yresolution;
} BJF_IMAGEINFO,*LPBJF_IMAGEINFO;

/* export function */
extern short bjf_image_open( LPBJF_IMAGEINFO, char * );
extern short bjf_image_init( LPBJF_IMAGEINFO , short , CPKUInt16 );
extern short bjf_image_read_raster( LPBJF_IMAGEINFO, char *, long, long, long , short , CPKUInt16 );
extern short bjf_image_flush( LPBJF_IMAGEINFO );
extern void  bjf_image_close( LPBJF_IMAGEINFO );
extern short bjf_image_get_imageformat( LPBJF_IMAGEINFO, short * );
extern short bjf_image_get_width( LPBJF_IMAGEINFO, long * );
extern short bjf_image_get_length( LPBJF_IMAGEINFO, long * );
extern short bjf_image_get_bpp( LPBJF_IMAGEINFO, short * );
extern short bjf_image_get_outputtype( LPBJF_IMAGEINFO, short * );
extern short bjf_image_get_resolution( LPBJF_IMAGEINFO, double *, double * );

#endif
