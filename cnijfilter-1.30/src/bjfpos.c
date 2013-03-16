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
#include "bjfpos.h"

/* function prototypes */
void bjf_pos_img_init( LPBJF_POS_IMGINFO );
void bjf_pos_prn_init( LPBJF_POS_PRNINFO );
void bjf_pos_init( LPBJF_POSINFO );
short bjf_pos_imageresolution( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO );
short bjf_pos_imageresolution_fit( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO );
short bjf_pos_imageresolution_center( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO );
short bjf_pos_mask_width( LPBJF_POSINFO, long * );
short bjf_pos_mask_height( LPBJF_POSINFO, long * );
short bjf_pos_width_offset( LPBJF_POSINFO, long * );
short bjf_pos_height_offset( LPBJF_POSINFO, long * );
short bjf_pos_out_width( LPBJF_POSINFO, long * );
short bjf_pos_out_height( LPBJF_POSINFO, long * );
short bjf_pos_leftskip( LPBJF_POSINFO, long * );
short bjf_pos_topskip( LPBJF_POSINFO, long * );
short bjf_pos_scaling( LPBJF_POSINFO, double * );
void disp_bjf_posinfo( LPBJF_POSINFO );
void disp_bjf_posimg( LPBJF_POS_IMGINFO );
void disp_bjf_posprn( LPBJF_POS_PRNINFO );

short bjf_pos_set_imgwidth( LPBJF_POS_IMGINFO, long );
short bjf_pos_set_imgheight( LPBJF_POS_IMGINFO, long );
short bjf_pos_set_imgXres( LPBJF_POS_IMGINFO, double );
short bjf_pos_set_imgYres( LPBJF_POS_IMGINFO, double );
short bjf_pos_set_prntopmargin( LPBJF_POS_PRNINFO, long );
short bjf_pos_set_prnleftmargin( LPBJF_POS_PRNINFO, long );
short bjf_pos_set_prnXres( LPBJF_POS_PRNINFO, double );
short bjf_pos_set_prnYres( LPBJF_POS_PRNINFO, double );
short bjf_pos_set_prnwidth( LPBJF_POS_PRNINFO, long );
short bjf_pos_set_prnheight( LPBJF_POS_PRNINFO, long );

static short check_imagesize( double, double, double, double );

static short check_imagesize( double defwidth, double defheight, double inwidth, double inheight )
{ 
	short result = 0;
	
	if ( inwidth > defwidth )
		result += 1;
	
	if ( inheight > defheight )
		result += 2;
		
	return result;
}



void bjf_pos_img_init( LPBJF_POS_IMGINFO lpimginfo )
{
	lpimginfo->img_width = 0;
	lpimginfo->img_height = 0;
	lpimginfo->xresolution = 0;
	lpimginfo->yresolution = 0;
}


void bjf_pos_prn_init( LPBJF_POS_PRNINFO lpprninfo  )
{
	lpprninfo->topmargin = 0;
	lpprninfo->leftmargin = 0;
	lpprninfo->prn_xresolution = 0.0;
	lpprninfo->prn_yresolution = 0.0;
	lpprninfo->prn_width = 0;
	lpprninfo->prn_height = 0;
}


void bjf_pos_init( LPBJF_POSINFO lpposinfo )
{
	lpposinfo->mask_width = 0.0;
	lpposinfo->mask_height = 0.0;
	lpposinfo->width_offset = 0.0;
	lpposinfo->height_offset = 0.0;
	lpposinfo->out_width = 0.0;
	lpposinfo->out_height = 0.0;
	lpposinfo->leftskip = 0.0;
	lpposinfo->topskip = 0.0;
	lpposinfo->scaling = 0.0;
}

/*-------------------------------------------------------------*/
short bjf_pos_imageresolution(
/*-------------------------------------------------------------*/
	LPBJF_POS_IMGINFO	lpimginfo,
	LPBJF_POS_PRNINFO	lpprninfo,
	LPBJF_POSINFO		lpposinfo
)
{
	long				img_width,img_height;
	double				img_xresolution, img_yresolution;
	double				topmargin, leftmargin;
	double				prn_xresolution, prn_yresolution;
	double				imgarea_width, imgarea_height;
	double				prnarea_width, prnarea_height;
	long				mask_width, mask_height;
	long				width_offset, height_offset;
	long				out_width, out_height;
	short				areacheck;
	short				result = -1;
	
	/*--- image data ---*/
	img_width = lpimginfo->img_width;
	img_height = lpimginfo->img_height;
	img_xresolution = lpimginfo->xresolution;
	img_yresolution = lpimginfo->yresolution;
	
	/*--- printer data ---*/
	prn_xresolution = lpprninfo->prn_xresolution;
	prn_yresolution = lpprninfo->prn_yresolution;

	/*--- area size which image has ---*/
	imgarea_width = (double)img_width / img_xresolution;
	imgarea_height = (double)img_height / img_yresolution;

	/*--- area size which priner can print ( 1/1000[mm] to dpi ) ---*/
	prnarea_width = (double)((double)lpprninfo->prn_width / 2540.0);
	prnarea_height = (double)((double)lpprninfo->prn_height / 2540.0);
	
	/*--- printer margin size ( 1/1000[mm] to dpi ) ---*/
	topmargin = (double) ((double)lpprninfo->topmargin / 2540.0 );
	leftmargin = (double) ((double)lpprninfo->leftmargin / 2540.0 );
	
	/*--- output pixel ---*/
	out_width = (long) ( prn_xresolution * imgarea_width );
	out_height = (long) ( prn_yresolution * imgarea_height );
	
	/*--- set mask and offset ---*/
	mask_width = img_width;
	mask_height = img_height;
	width_offset = 0;
	height_offset = 0;
	
	
	/*
		in this position define mode,
			when out_width or out_height is bigger than prnarea,
				we cut off top or left area
	*/
	
	if ( (areacheck = check_imagesize( prnarea_width, prnarea_height,
		imgarea_width, imgarea_height )) > 0 ){
		
		switch( areacheck ){
			case 1:		/* width is over */
				width_offset = (long)( leftmargin * img_xresolution );
				out_width = (long)( prnarea_width * prn_xresolution );

				if ( (imgarea_width - prnarea_width - leftmargin) > 0 ){
					mask_width = (long)( prnarea_width * img_xresolution + 0.5 );	
				}
				else{
					mask_width = img_width - width_offset;
				}
				break;

			case 2:		/* height is over */
				height_offset = (long)( topmargin * img_yresolution );
				out_height = (long)( prnarea_height * prn_yresolution );

				if ( (imgarea_height - prnarea_height - topmargin) > 0 ){	
					mask_height = (long)( prnarea_height * img_yresolution + 0.5 );
				}
				else{
					mask_height = img_height - height_offset;
				}
				break;
			case 3:		/* width and height is over */
				width_offset = (long)( leftmargin * img_xresolution );
				out_width = (long)( prnarea_width * prn_xresolution );

				if ( (imgarea_width - prnarea_width - leftmargin) > 0 ){
					mask_width = (long)( prnarea_width * img_xresolution + 0.5 );	
				}
				else{
					mask_width = img_width - width_offset;
				}
				
				height_offset = (long)( topmargin * img_yresolution + 0.5 );
				out_height = (long)( prnarea_height * prn_yresolution + 0.5 );

				if ( (imgarea_height - prnarea_height - topmargin) > 0 ){	
					mask_height = (long)( prnarea_height * img_yresolution + 0.5 );
				}
				else{
					mask_height = img_height - height_offset;
				}
				break;
			default:
				goto onErr;
		}
	}

	/*--- set parameter ---*/
	lpposinfo->mask_width = mask_width;
	lpposinfo->mask_height = mask_height;
	lpposinfo->width_offset = width_offset;
	lpposinfo->height_offset = height_offset;
	lpposinfo->out_width = out_width;
	lpposinfo->out_height = out_height;
	lpposinfo->page_width = prn_xresolution * prnarea_width; 


	result = 0;
onErr:
	return result;

}

/*-------------------------------------------------------------*/
short bjf_pos_imageresolution_fit(
/*-------------------------------------------------------------*/
 	LPBJF_POS_IMGINFO	lpimginfo,
	LPBJF_POS_PRNINFO	lpprninfo,
	LPBJF_POSINFO		lpposinfo
)
{
	long				img_width,img_height;
	double				img_xresolution, img_yresolution;
	double				prn_xresolution, prn_yresolution;
	double				prnarea_width, prnarea_height;
	double				alpha;									/* scaling parameter for fit */
	long				tmp_height,tmp_width;
	long				out_width, out_height;
	short				result = -1;

	/*--- image data [pixel] ---*/
	img_width = lpimginfo->img_width;
	img_height = lpimginfo->img_height;
	img_xresolution = lpimginfo->xresolution;
	img_yresolution = lpimginfo->yresolution;
	
	/*--- printer data [dpi] ---*/
	prn_xresolution = lpprninfo->prn_xresolution;
	prn_yresolution = lpprninfo->prn_yresolution;

	/*--- area size which priner can print ( 1/1000[mm] to dpi ) [inch] ---*/
	prnarea_width = (double)((double)lpprninfo->prn_width / 2540.0);
	prnarea_height = (double)((double)lpprninfo->prn_height / 2540.0);

	/*--- determine X scaling ---*/
	
	/*
		printable area [pixel]
	*/
	out_width = (long)( prnarea_width * prn_xresolution );
	out_height = (long)( prnarea_height * prn_yresolution );
	
	/*
		at first, make print image width prn_X_area
	*/
	tmp_height = 0; tmp_width =0;
	alpha = ( prnarea_width * prn_xresolution ) / (long)img_width;
	tmp_height = (long)( alpha * img_height );
	
	if ( tmp_height > out_height ){	/* height is over */
		/*
			if Height is over, make print image height prn_Y_area
		*/
		alpha = ( prnarea_height * prn_yresolution ) / (long)img_height;
		tmp_width = (long)( alpha * img_width );
		
		out_width = tmp_width;
	}
	else{								/* height is OK */
		out_height = tmp_height;
	}
	
	/*--- set parameter ---*/
	lpposinfo->mask_width = img_width;
	lpposinfo->mask_height = img_height;
	lpposinfo->width_offset = 0;
	lpposinfo->height_offset = 0;
	lpposinfo->out_width = out_width;
	lpposinfo->out_height = out_height;
	lpposinfo->page_width = prn_xresolution * prnarea_width; 
	
	result = 0;
	return result;
}

/*-------------------------------------------------------------*/
short bjf_pos_imageresolution_center(
/*-------------------------------------------------------------*/
	LPBJF_POS_IMGINFO	lpimginfo,
	LPBJF_POS_PRNINFO	lpprninfo,
	LPBJF_POSINFO		lpposinfo
)
{
	long				img_width,img_height;
	double				img_xresolution, img_yresolution;
	double				prn_xresolution, prn_yresolution;
	double				prnarea_width, prnarea_height;
	double				prn_width, prn_height;
	long				out_width, out_height;
	long				width_blnk, height_blnk;
	short				result = -1;
	
	/*--- image data [pixel] ---*/
	img_width = lpimginfo->img_width;
	img_height = lpimginfo->img_height;
	img_xresolution = lpimginfo->xresolution;
	img_yresolution = lpimginfo->yresolution;
	
	/*--- printer data [dpi] ---*/
	prn_xresolution = lpprninfo->prn_xresolution;
	prn_yresolution = lpprninfo->prn_yresolution;

	/*--- area size which priner can print ( 1/1000[mm] to dpi ) [inch] ---*/
	prnarea_width = (double)((double)lpprninfo->prn_width / 2540.0);
	prnarea_height = (double)((double)lpprninfo->prn_height / 2540.0);
	
	/* printable area [pixel] */
	prn_width = (long)( prnarea_width * prn_xresolution );
	prn_height = (long)( prnarea_height * prn_yresolution );
	
	/*--- now print out image size ---*/
	out_width  = lpposinfo->out_width;
	out_height = lpposinfo->out_height;
	
	/*--- calucurate blank ---*/
	width_blnk  = prn_width - out_width;
	height_blnk = prn_height - out_height;
	
	/*--- parameter check ---*/
	if ( ( width_blnk < 0 ) || ( height_blnk < 0 ) ) goto onErr;
	
	/*--- set parameter ---*/
	lpposinfo->leftskip = (long)( width_blnk / 2 );
	lpposinfo->topskip  = (long)( height_blnk / 2 );
	
	result = 0;
onErr:
	return result;

}

/*-------------------------------------------------------------*/
/*	provide position parameter                                 */
/*-------------------------------------------------------------*/
short bjf_pos_mask_width( LPBJF_POSINFO lpposinfo, long *mask_width )
{
	*mask_width = lpposinfo->mask_width;

	return 0;
}


short bjf_pos_mask_height( LPBJF_POSINFO lpposinfo, long *mask_height )
{
	*mask_height = lpposinfo->mask_height;
	return 0;
}


short bjf_pos_width_offset( LPBJF_POSINFO lpposinfo, long *width_offset )
{
	*width_offset = lpposinfo->width_offset;
	return 0;
}


short bjf_pos_height_offset( LPBJF_POSINFO lpposinfo, long	*height_offset )
{
	*height_offset = lpposinfo->height_offset;
	return 0;
}


short bjf_pos_out_width( LPBJF_POSINFO lpposinfo, long *out_width )
{
	*out_width = lpposinfo->out_width;
	return 0;
}


short bjf_pos_out_height( LPBJF_POSINFO	lpposinfo, long *out_height)
{
	*out_height = lpposinfo->out_height;
	return 0;
}


short bjf_pos_leftskip( LPBJF_POSINFO lpposinfo, long *leftskip )
{
	*leftskip = lpposinfo->leftskip;
	return 0;
}


short bjf_pos_topskip( LPBJF_POSINFO lpposinfo, long *topskip )
{
	*topskip = lpposinfo->topskip;
	return 0;
}


short bjf_pos_scaling( LPBJF_POSINFO lpposinfo, double *scaling )
{
	*scaling = lpposinfo->scaling;
	return 0;
}


short bjf_pos_page_width( LPBJF_POSINFO lpposinfo, long *page_width )
{
	*page_width = lpposinfo->page_width;
	return 0;
}



/*-------------------------------------------------------------*/
/*	display position parameter                                 */
/*-------------------------------------------------------------*/
void disp_bjf_posinfo( LPBJF_POSINFO lpposinfo )
{
	fprintf( stderr, "< BJF_POSINFO >\n" );
	fprintf( stderr, "mask_width:%ld\n", lpposinfo->mask_width );
	fprintf( stderr, "mask_height:%ld\n", lpposinfo->mask_height );
	fprintf( stderr, "width_offset:%ld\n", lpposinfo->width_offset );
	fprintf( stderr, "height_offset:%ld\n", lpposinfo->height_offset );
	fprintf( stderr, "out_width:%ld\n", lpposinfo->out_width );
	fprintf( stderr, "out_height:%ld\n", lpposinfo->out_height );
	fprintf( stderr, "leftskip:%ld\n", lpposinfo->leftskip );
	fprintf( stderr, "topskip:%ld\n", lpposinfo->topskip );
	fprintf( stderr, "scaling:%f\n", lpposinfo->scaling );
}


void disp_bjf_posimg( LPBJF_POS_IMGINFO	lpimginfo )
{
	fprintf( stderr, "< BJF_POS_IMG >\n" );
	fprintf( stderr, "img_width:%ld\n", lpimginfo->img_width );
	fprintf( stderr, "img_height:%ld\n", lpimginfo->img_height );
	fprintf( stderr, "xresolution:%f\n", lpimginfo->xresolution );
	fprintf( stderr, "yresolution:%f\n", lpimginfo->yresolution );
}


void disp_bjf_posprn( LPBJF_POS_PRNINFO lpprninfo )
{
	fprintf( stderr, "< BJF_POS_PRN >\n" );
	fprintf( stderr, "topmargin:%ld\n", lpprninfo->topmargin );
	fprintf( stderr, "leftmargin:%ld\n", lpprninfo->leftmargin );
	fprintf( stderr, "prn_xresolution:%f\n", lpprninfo->prn_xresolution );
	fprintf( stderr, "prn_yresolution:%f\n", lpprninfo->prn_yresolution );
	fprintf( stderr, "prn_width:%ld\n", lpprninfo->prn_width );
	fprintf( stderr, "prn_height:%ld\n", lpprninfo->prn_height );
}


/*-------------------------------------------------------------*/
/*	set original image parameter                               */
/*-------------------------------------------------------------*/
short bjf_pos_set_imgwidth( LPBJF_POS_IMGINFO lpimginfo, long width )
{
	lpimginfo->img_width = width;
	return 1;
}


short bjf_pos_set_imgheight( LPBJF_POS_IMGINFO lpimginfo, long height )
{
	lpimginfo->img_height = height;
	return 1;
}


short bjf_pos_set_imgXres( LPBJF_POS_IMGINFO lpimginfo, double xresolution )
{
	lpimginfo->xresolution = xresolution;
	return 1;
}


short bjf_pos_set_imgYres( LPBJF_POS_IMGINFO lpimginfo, double yresolution )
{
	lpimginfo->yresolution = yresolution;
	return 1;
}



/*-------------------------------------------------------------*/
/*	set printer parmeter                                       */
/*-------------------------------------------------------------*/
short bjf_pos_set_prntopmargin( LPBJF_POS_PRNINFO lpprninfo, long topmargin )
{
	lpprninfo->topmargin = topmargin;
	return 1;
}


short bjf_pos_set_prnleftmargin( LPBJF_POS_PRNINFO lpprninfo, long leftmargin )
{
	lpprninfo->leftmargin = leftmargin;
	return 1;
}


short bjf_pos_set_prnXres( LPBJF_POS_PRNINFO lpprninfo, double prn_xresolution )
{
	lpprninfo->prn_xresolution = prn_xresolution;
	return 1;
}


short bjf_pos_set_prnYres( LPBJF_POS_PRNINFO lpprninfo, double prn_yresolution )
{
	lpprninfo->prn_yresolution = prn_yresolution;
	return 1;
}


short bjf_pos_set_prnwidth( LPBJF_POS_PRNINFO lpprninfo, long prn_width )
{
	lpprninfo->prn_width = prn_width;
	return 1;
}


short bjf_pos_set_prnheight( LPBJF_POS_PRNINFO lpprninfo, long prn_height )
{
	lpprninfo->prn_height = prn_height;
	return 1;
}
