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

#ifndef __BJFIMAGE_H__
#define	__BJFIMAGE_H__

/*--- image format that support in this module ---*/
#define BJFIMAGE_PPM		14

/*--- output type ---*/
#define BJFOUTPUT_COLOR		30
#define BJFOUTPUT_GRAY		31
#define BJFOUTPUT_INDEX		32

/*--- image data header discription ---*/
#define PPMRAWSTART			"\x50\x36"			/* "P6" */

#define MAXBUF	0x00100000
#define CIF_FILE_END (-2)
#define	TOLONG(buffer, off) (buffer[(off)] | buffer[(off)+1]<<8 | buffer[(off)+2]<<16 | buffer[(off)+3]<<24)
#define TOSHORT(buffer, off) (buffer[(off)] | buffer[(off)+1]<<8)

/*--- work space for image process module ---*/
typedef struct BJF_IMAGEINFO
{
	/* for bmp and ppm Parameter */
	FILE				*bmp;
	unsigned char		**bmpraw;
	short				isfirstcall;
	long				rstep;
	long				top;
	long				readraster;
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
