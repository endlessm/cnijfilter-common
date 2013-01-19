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
#include "cncl.h"
#include "cncldef.h"
#include "cnclucom.h"
#include "cncludef.h"
#include "bjfoption.h"
#include "bjfpos.h"
#include "bjipc.h"

/* function prototypes */
void bjf_pos_img_init( LPBJF_POS_IMGINFO );
void bjf_pos_prn_init( LPBJF_POS_PRNINFO );
void bjf_pos_init( LPBJF_POSINFO );
void bjf_margin_init( LPBJF_MARGIN_INFO );
short bjf_pos_imageresolution( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO );
short bjf_pos_imageresolution_fit( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO );
short bjf_pos_imageresolution_center( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO );
short bjf_pos_set_paperwidth( LPBJF_MARGIN_INFO , long );
short bjf_pos_set_paperlength( LPBJF_MARGIN_INFO , long );
short SetExtLevel( LPBJF_MARGIN_INFO, short);
short SetExtMargin(LPBJF_POS_PRNINFO, LPBJF_POSINFO, LPBJF_MARGIN_INFO, LPBJFLTOVERMARGININFO);
short SetBbox(LPBJF_OPTINFO , LPBJF_POS_IMGINFO , LPBJF_POSINFO , LPBJF_MARGIN_INFO , int , int);
short ImageFitShort( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO,LPBJF_MARGIN_INFO  );
short ImageFitLong( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO, LPBJF_MARGIN_INFO );
short SetImageSize( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO);
short ImageScaling(LPBJF_POS_PRNINFO, LPBJF_POSINFO,short);
short ImageCenter( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO, LPBJF_MARGIN_INFO );
short ImageCut( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO, LPBJF_MARGIN_INFO );
short MarginInit(LPBJF_POS_PRNINFO, LPBJF_POSINFO, LPBJF_MARGIN_INFO);
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
static long round_up( double );



static short check_imagesize( double defwidth, double defheight, double inwidth, double inheight )
{ 
	short result = 0;
	
	if ( inwidth > defwidth )
		result += 1;
	
	if ( inheight > defheight )
		result += 2;
		
	return result;
}


static long round_up( double target )
{
	long	tmp_down,tmp_up;
	
	tmp_down = (long)target;
	
	if( target == (double)tmp_down ){
		tmp_up = tmp_down;
	}else{
		tmp_up = (long)(target + 1 );
	}
	
	return tmp_up;
	
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



void bjf_margin_init( LPBJF_MARGIN_INFO lpmgninfo )
{
	lpmgninfo->curtopmargin = 0.0;
	lpmgninfo->curleftmargin = 0.0;
	lpmgninfo->curprn_width = 0.0;
	lpmgninfo->curprn_height = 0.0;
	lpmgninfo->PaperWidth = 0.0;
	lpmgninfo->PaperLength = 0.0;
}



/*-------------------------------------------------------------*/
/* Set --extension information                                  */
/*-------------------------------------------------------------*/
short SetExtLevel(
	LPBJF_MARGIN_INFO	lpmargininfo,
	short				extension
)
{
	lpmargininfo->extension = extension;
	return 0;
}


/*-------------------------------------------------------------*/
/* Init cur_margin information                                 */
/*-------------------------------------------------------------*/
short MarginInit(
	LPBJF_POS_PRNINFO	lpprninfo,
	LPBJF_POSINFO		lpposinfo,
	LPBJF_MARGIN_INFO	lpmargininfo
)
{
	long				rightmargin,bottommargin;
	short				result = -1;
	
	rightmargin = lpmargininfo->PaperWidth - lpprninfo->prn_width - lpprninfo->leftmargin;
	bottommargin = lpmargininfo->PaperLength - lpprninfo->prn_height - lpprninfo->topmargin;


	/*--- set parameter ---*/
	lpmargininfo->curbottommargin = (double)bottommargin;
	lpmargininfo->currightmargin = (double)rightmargin;
	lpmargininfo->curtopmargin = (double)lpprninfo->topmargin;
	lpmargininfo->curleftmargin = (double)lpprninfo->leftmargin;
	lpmargininfo->curprn_width = (double)lpprninfo->prn_width;
	lpmargininfo->curprn_height = (double)lpprninfo->prn_height;

	result = 0;

	return result;

}


/*-------------------------------------------------------------*/
/* Modify ext_margin according to the extension                */
/*-------------------------------------------------------------*/
short SetExtMargin(
	LPBJF_POS_PRNINFO		lpprninfo,
	LPBJF_POSINFO			lpposinfo,
	LPBJF_MARGIN_INFO		lpmargininfo,
	LPBJFLTOVERMARGININFO	lpbjfltovermargin
)
{
	double				curprn_width,curprn_height;
	double				topmargin,leftmargin,rightmargin,bottommargin;
	double				mgn_leftskip,mgn_topskip;
	double				paperwidth,paperlength;
	short				extension;

	short				result = -1;
	
	
	extension = lpmargininfo->extension;

	/*--- current margin [1/100mm] ---*/
	topmargin = lpmargininfo->curtopmargin;
	leftmargin = lpmargininfo->curleftmargin;
	rightmargin = lpmargininfo->currightmargin;
	bottommargin = lpmargininfo->curbottommargin;

	paperwidth = (double)lpmargininfo->PaperWidth;
	paperlength = (double)lpmargininfo->PaperLength;

	/*--- Modify margin according to extension. ---*/
	if( lpbjfltovermargin->overmargin_left < 0 ){	/* BJFLTOVERMARGININFO has no value */
		topmargin = topmargin * (double)extension / 3.0;
		leftmargin = leftmargin * (double)extension / 3.0;
		bottommargin = bottommargin * (double)extension / 3.0;
		rightmargin = rightmargin * (double)extension / 3.0;
	}else{											/* Use BJFLTOVERMARGININFO value */

		topmargin = (double)(lpbjfltovermargin->overmargin_top * -1);
		leftmargin = (double)(lpbjfltovermargin->overmargin_left * -1);
		bottommargin = (double)(lpbjfltovermargin->overmargin_bottom * -1);
		rightmargin = (double)(lpbjfltovermargin->overmargin_right * -1);
	}

	/*--- Calculate printable area according to extension. ---*/
	curprn_width = paperwidth - leftmargin - rightmargin;
	curprn_height = paperlength - topmargin - bottommargin;

	/*--- add topskip,leftskip[pixel] ---*/
	mgn_topskip = (topmargin - (double)lpprninfo->topmargin) * lpprninfo->prn_xresolution / 2540.0;
	mgn_leftskip =(leftmargin - (double)lpprninfo->leftmargin) * lpprninfo->prn_yresolution / 2540.0;


	lpposinfo->topskip += mgn_topskip;
	lpposinfo->leftskip += mgn_leftskip;


	/*--- set parameter ---*/
	lpmargininfo->curtopmargin = topmargin;
	lpmargininfo->curleftmargin = leftmargin;
	lpmargininfo->currightmargin = rightmargin;
	lpmargininfo->curbottommargin = bottommargin;
	lpmargininfo->curprn_width = curprn_width;
	lpmargininfo->curprn_height = curprn_height;

	result = 0;

	return result;

}




/*-------------------------------------------------------------*/
/* Constract image area based on bbox data                    */
/*-------------------------------------------------------------*/
short SetBbox(
	LPBJF_OPTINFO		lpbjfoption,
	LPBJF_POS_IMGINFO	lpimginfo,
	LPBJF_POSINFO		lpposinfo,
	LPBJF_MARGIN_INFO	lpmargininfo,
	int					isDuplex,
	int					pageNum
)
{
	long				img_width,img_height;
	double				img_xresolution, img_yresolution;
	double				tmp_left,tmp_bottom,tmp_right,tmp_top;
	long				left,bottom,right,top;
	long				height,width;
	short				result = -1;

	long				*bbox = lpbjfoption->bbox.value;
	/*--- input image data [pixel] ---*/
	img_width = lpimginfo->img_width;
	img_height = lpimginfo->img_height;
	img_xresolution = lpimginfo->xresolution;
	img_yresolution = lpimginfo->yresolution;

	lpmargininfo->bbox[0] = bbox[0];
	lpmargininfo->bbox[1] = bbox[1];
	lpmargininfo->bbox[2] = bbox[2];
	lpmargininfo->bbox[3] = bbox[3];
	
	/*--- bbox data [pixel(72dpi) -> pixel(image resolution)] ---*/
	tmp_left = (double)(lpmargininfo->bbox[0] * img_xresolution / 72.0);
	tmp_bottom = (double)(lpmargininfo->bbox[1] * img_yresolution / 72.0);
	tmp_right = (double)(lpmargininfo->bbox[2] * img_xresolution / 72.0);
	tmp_top = (double)(lpmargininfo->bbox[3] * img_yresolution / 72.0);
	
	/* in */
	left = round_up(tmp_left);
	bottom = round_up(tmp_bottom);
	right = (long)tmp_right;
	top = (long)tmp_top;

	/* extracted area size */
	width = right - left;
	height = top - bottom;
	

	if( (width <=0)||(height <=0) ){
	  result=0;
	  goto onErr;
	}

	/* Check if the extracted area is within the input data. */
	if( (right > img_width ) || (top > img_height) ){	
	  /* continue */
	  result=0;
	  goto onErr;
	}
	
	/* Exchange top margin and bottom margin when duplex is ON, stapleside is LONG and page number is even.  */
	if (lpbjfoption->stapleside == STAPLESIDE_LONG && isDuplex == ON && pageNum % 2 == 0){
		double tmp = top;
		top = img_height - bottom;
		bottom = img_height - tmp;
	}
	
	/*--- set parameter ---*/
	lpposinfo->width_offset = (double)left;
	lpposinfo->height_offset = (double)(img_height - top);

	lpimginfo->img_width = width;
	lpimginfo->img_height = height;

	
	result = 0;

 onErr:

	return result;
}



/*-------------------------------------------------------------*/
/* Fit image to the printable area without lacking image data. */
/*-------------------------------------------------------------*/
short ImageFitShort(
 	LPBJF_POS_IMGINFO	lpimginfo,
	LPBJF_POS_PRNINFO	lpprninfo,
	LPBJF_POSINFO		lpposinfo,
	LPBJF_MARGIN_INFO	lpmargininfo
)
{
	long				img_width,img_height;
	double				prn_xresolution, prn_yresolution;
	double				prnarea_width, prnarea_height;
	double				alpha;
	double				tmp_height,tmp_width;
	double				out_width, out_height;
	short				result = -1;


	/*--- target image data [pixel] ---*/
	img_width = lpimginfo->img_width;
	img_height = lpimginfo->img_height;
	
	/*--- printer resolution [dpi] ---*/
	prn_xresolution = lpprninfo->prn_xresolution;
	prn_yresolution = lpprninfo->prn_yresolution;

	/*--- current printable area ( 1/100[mm] to inch ) [inch] ---*/
	prnarea_width = lpmargininfo->curprn_width / 2540.0;
	prnarea_height = lpmargininfo->curprn_height / 2540.0;

	/*--- Set output image size Max [pixel] ---*/
	out_width = prnarea_width * prn_xresolution;
	out_height = prnarea_height * prn_yresolution;
	
	
	/* --- At first, expand image so as to fit to printable area width.[pixel] ---*/
	tmp_height = 0.0; tmp_width =0.0;

	alpha =out_width / (double)img_width;
	tmp_height = alpha * (double)img_height;
	
	/*--- If height exceeds the printable area, 
		expand image so as to fit to printable area height ---*/
	if ( tmp_height > out_height ){	 	/* height is over */
		alpha = out_height / (double)img_height;
		tmp_width = alpha * (double)img_width;
		out_width = tmp_width;
	}
	else{								/*--- height is within the printable area ---*/
		out_height = tmp_height;
	}

	
	/*--- set parameter ---*/
	lpposinfo->out_width = out_width;
	lpposinfo->out_height = out_height;
	
	result = 0;
	return result;
}


/*-------------------------------------------------------------*/
/* Fill image to the printable area without blank              */
/*-------------------------------------------------------------*/
short ImageFitLong(
 	LPBJF_POS_IMGINFO	lpimginfo,
	LPBJF_POS_PRNINFO	lpprninfo,
	LPBJF_POSINFO		lpposinfo,
	LPBJF_MARGIN_INFO	lpmargininfo
)
{
	long				img_width,img_height;
	double				prn_xresolution, prn_yresolution;
	double				prnarea_width, prnarea_height;
	double				alpha;
	double				tmp_height,tmp_width;
	double				out_width, out_height;
	short				result = -1;

	/*--- target image data [pixel] ---*/
	img_width = lpimginfo->img_width;
	img_height = lpimginfo->img_height;
	
	/*--- printer resolution [dpi] ---*/
	prn_xresolution = lpprninfo->prn_xresolution;
	prn_yresolution = lpprninfo->prn_yresolution;

	/*--- current printable area ( 1/100[mm] to inch ) [inch] ---*/
	prnarea_width = lpmargininfo->curprn_width / 2540.0;
	prnarea_height = lpmargininfo->curprn_height / 2540.0;

	/*--- Set output image size Max [pixel] ---*/
	out_width = prnarea_width * prn_xresolution;
	out_height = prnarea_height * prn_yresolution;
	
	
	/* --- At first, expand image so as to fit to printable area width. ---*/
	tmp_height = 0.0; tmp_width =0.0;
	alpha = out_width / (double)img_width;
	tmp_height = alpha * (double)img_height;
	
	/*--- If height doesn't exceed the printable area, 
		expand image so as to fit to printable area height ---*/
	if ( tmp_height < out_height ){
		alpha = out_height / (double)img_height;
		tmp_width = alpha * (double)img_width;
		out_width = tmp_width;
	}
	else{
		out_height = tmp_height;		
	}
	
	/*--- set parameter ---*/
	lpposinfo->out_width = out_width;
	lpposinfo->out_height = out_height;
	
	result = 0;
	return result;

}


/*-------------------------------------------------------------*/
/* Calculate output image size(without --fit/--fit2 option)    */
/*-------------------------------------------------------------*/
short SetImageSize(
	LPBJF_POS_IMGINFO	lpimginfo,
	LPBJF_POS_PRNINFO	lpprninfo,
	LPBJF_POSINFO		lpposinfo
)
{
	long				img_width,img_height;
	double				img_xresolution, img_yresolution;
	double				prn_xresolution, prn_yresolution;
	double				out_width, out_height;
	short				result = -1;
	

	/*--- image data ---*/
	img_width = lpimginfo->img_width;
	img_height = lpimginfo->img_height;
	img_xresolution = lpimginfo->xresolution;
	img_yresolution = lpimginfo->yresolution;
	
	/*--- printer data ---*/
	prn_xresolution = lpprninfo->prn_xresolution;
	prn_yresolution = lpprninfo->prn_yresolution;

	/*--- output image size [pixel] ---*/
	out_width = (double)img_width / img_xresolution * prn_xresolution;
	out_height = (double)img_height / img_yresolution * prn_yresolution;

	/*--- set parameter ---*/
	lpposinfo->out_width = out_width;
	lpposinfo->out_height = out_height;

	result = 0;

	return result;
}




/*-------------------------------------------------------------*/
/* Resize image based on --percent option                      */
/*-------------------------------------------------------------*/
short ImageScaling(
	LPBJF_POS_PRNINFO	lpprninfo,
	LPBJF_POSINFO		lpposinfo,
	short				scale
)
{
	double				out_width, out_height;
	short				result = -1;


	out_width = 	lpposinfo->out_width ;
	out_height = 	lpposinfo->out_height;

	out_width = out_width * (double)scale / 100.0;
	out_height = out_height * (double)scale / 100.0;
	
	/*--- set parameter ---*/
	lpposinfo->out_width = out_width;
	lpposinfo->out_height = out_height;
	
	result = 0;
	return result;
}


/*-------------------------------------------------------------*/
/* Move image to the center of the printable area              */
/*-------------------------------------------------------------*/
short ImageCenter(
	LPBJF_POS_IMGINFO	lpimginfo,
	LPBJF_POS_PRNINFO	lpprninfo,
	LPBJF_POSINFO		lpposinfo,
	LPBJF_MARGIN_INFO	lpmargininfo
)
{
	long				img_width,img_height;
	double				img_xresolution, img_yresolution;
	double				prn_xresolution, prn_yresolution;
	double				prnarea_width, prnarea_height;
	double				prn_width, prn_height;
	double				out_width, out_height;
	double				width_blnk, height_blnk;
	double 				tmp_leftskip,tmp_topskip;
	short				result = -1;

	
	/*--- target image data [pixel] ---*/
	img_width = lpimginfo->img_width;
	img_height = lpimginfo->img_height;

	/*--- image resolution [dpi] ---*/
	img_xresolution = lpimginfo->xresolution;
	img_yresolution = lpimginfo->yresolution;
	
	/*--- printer resolution [dpi] ---*/
	prn_xresolution = lpprninfo->prn_xresolution;
	prn_yresolution = lpprninfo->prn_yresolution;

	/*--- current printable area ( 1/100[mm] to inch ) [inch] ---*/
	prnarea_width = lpmargininfo->curprn_width / 2540.0;
	prnarea_height = lpmargininfo->curprn_height / 2540.0;
	
	/*--- current printable area [ pixel (printer resolution) ] ---*/
	prn_width = prnarea_width * prn_xresolution;
	prn_height = prnarea_height * prn_yresolution;
	
	/*--- output image size [ pixel (printer resolution) ] ---*/
	out_width  = lpposinfo->out_width;
	out_height = lpposinfo->out_height;
	
	
	/*--- calculate blank ---*/
	width_blnk  = prn_width - out_width;
	height_blnk = prn_height - out_height;
	tmp_leftskip =width_blnk / (double)2.0;
	tmp_topskip  =height_blnk / (double)2.0;


	if( tmp_leftskip < 0.0 ){		/* out_width > prn_width */
	  lpposinfo->width_offset += tmp_leftskip / out_width * (double)img_width * (-1.0);
	}else{
	  lpposinfo->leftskip += tmp_leftskip ;
	}

	if( tmp_topskip < 0.0 ){		/* out_height > prn_height */
	  lpposinfo->height_offset += tmp_topskip / out_height * (double)img_height * (-1.0);

	}else{
	  lpposinfo->topskip += tmp_topskip;
	}
	
	result = 0;

	return result;

}



/*-------------------------------------------------------------*/
/* Extract the image to be printed                             */
/*-------------------------------------------------------------*/
short ImageCut(
	LPBJF_POS_IMGINFO	lpimginfo,
	LPBJF_POS_PRNINFO	lpprninfo,
	LPBJF_POSINFO		lpposinfo,
	LPBJF_MARGIN_INFO	lpmargininfo
)
{
	long				img_width,img_height;
	double				prn_xresolution, prn_yresolution;
	double				prnarea_width, prnarea_height;
	double				prnarea_width_org;
	double				prn_width, prn_height;
	double				mask_width, mask_height;
	double				out_width, out_height;
	short				result = -1;
	

	/*--- target image data [pixel] ---*/
	img_width = lpimginfo->img_width;
	img_height = lpimginfo->img_height;
	
	/*--- printer resolution [dpi] ---*/
	prn_xresolution = lpprninfo->prn_xresolution;
	prn_yresolution = lpprninfo->prn_yresolution;

	/*--- original printable area [inch] ---*/
	prnarea_width_org = lpprninfo->prn_width / 2540.0;

	/*--- current printable area ( 1/100[mm] to inch ) [inch] ---*/
	prnarea_width = lpmargininfo->curprn_width / 2540.0;
	prnarea_height = lpmargininfo->curprn_height / 2540.0;
	
	/*--- current printable area [pixel] (with printer resolution)---*/
	prn_width = prnarea_width * prn_xresolution;
	prn_height = prnarea_height * prn_yresolution;

	/*--- output image size [pixel](with printer resolution) ---*/
	out_width = 	lpposinfo->out_width ;
	out_height = 	lpposinfo->out_height;

	
	/*--- Init mask with whole target image ---*/
	/*--- [pixel] with image resolution ---*/
	mask_width = (double)img_width;
	mask_height = (double)img_height;


	if( out_width > prn_width ){	/* width is over */
		mask_width = (double)img_width * prn_width / out_width;
		out_width = prn_width;
	}

	if( out_height > prn_height ){	/* height is over */
		mask_height = (double)img_height * prn_height / out_height;
		out_height = prn_height;
	}
		
		
	/*--- set parameter ---*/
	lpposinfo->mask_width = mask_width;
	lpposinfo->mask_height = mask_height;
	lpposinfo->out_width = out_width;
	lpposinfo->out_height = out_height;
	lpposinfo->page_width = prn_xresolution * prnarea_width_org; 


	result = 0;

	return result;

}


/* Functions used by ver1.3 */
#if 0
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
#endif



/*-------------------------------------------------------------*/
/*	provide position parameter                                 */
/*-------------------------------------------------------------*/
short bjf_pos_mask_width( LPBJF_POSINFO lpposinfo, long *mask_width )
{
	/* round up */
	*mask_width = round_up(lpposinfo->mask_width);

	return 0;
}


short bjf_pos_mask_height( LPBJF_POSINFO lpposinfo, long *mask_height )
{
	/* round up */
	*mask_height = round_up(lpposinfo->mask_height);
	return 0;
}


short bjf_pos_width_offset( LPBJF_POSINFO lpposinfo, long *width_offset )
{
	/* round down */
	*width_offset = (long)lpposinfo->width_offset;
	return 0;
}


short bjf_pos_height_offset( LPBJF_POSINFO lpposinfo, long	*height_offset )
{
	/* round down */
	*height_offset = (long)lpposinfo->height_offset;
	return 0;
}


short bjf_pos_out_width( LPBJF_POSINFO lpposinfo, long *out_width )
{
	long	tmp_out_width;
	
	/* round up */
	tmp_out_width = round_up(lpposinfo->out_width);
	
	if( (tmp_out_width + (long)lpposinfo->leftskip) > (long)lpposinfo->page_width ){
		*out_width = (long)lpposinfo->page_width - (long)lpposinfo->leftskip;
	}else{
		*out_width = tmp_out_width;
	}
	
	return 0;
}


short bjf_pos_out_height( LPBJF_POSINFO	lpposinfo, long *out_height)
{
	/* round up */
	*out_height = round_up(lpposinfo->out_height);
	return 0;
}


short bjf_pos_leftskip( LPBJF_POSINFO lpposinfo, long *leftskip )
{
	/* round down */
	*leftskip = (long)lpposinfo->leftskip;
	return 0;
}


short bjf_pos_topskip( LPBJF_POSINFO lpposinfo, long *topskip )
{
	/* round down */
	*topskip = (long)lpposinfo->topskip;
	return 0;
}


short bjf_pos_scaling( LPBJF_POSINFO lpposinfo, double *scaling )
{
	*scaling = lpposinfo->scaling;
	return 0;
}


short bjf_pos_page_width( LPBJF_POSINFO lpposinfo, long *page_width )
{
	/* round down */
	*page_width = (long)lpposinfo->page_width;
	return 0;
}



/*-------------------------------------------------------------*/
/*	display position parameter                                 */
/*-------------------------------------------------------------*/
void disp_bjf_posinfo( LPBJF_POSINFO lpposinfo )
{
	fprintf( stderr, "< BJF_POSINFO >\n" );
	fprintf( stderr, "mask_width:%f\n", lpposinfo->mask_width );
	fprintf( stderr, "mask_height:%f\n", lpposinfo->mask_height );
	fprintf( stderr, "width_offset:%f\n", lpposinfo->width_offset );
	fprintf( stderr, "height_offset:%f\n", lpposinfo->height_offset );
	fprintf( stderr, "out_width:%f\n", lpposinfo->out_width );
	fprintf( stderr, "out_height:%f\n", lpposinfo->out_height );
	fprintf( stderr, "leftskip:%f\n", lpposinfo->leftskip );
	fprintf( stderr, "topskip:%f\n", lpposinfo->topskip );
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


short bjf_pos_set_paperwidth( LPBJF_MARGIN_INFO lpmargininfo, long paperwidth )
{
	lpmargininfo->PaperWidth = paperwidth;
	return 1;
}


short bjf_pos_set_paperlength( LPBJF_MARGIN_INFO lpmargininfo, long paperlength )
{
	lpmargininfo->PaperLength = paperlength;
	return 1;
}

