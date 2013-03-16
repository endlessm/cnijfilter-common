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

#ifndef __BJFPOS_H__
#define	__BJFPOS_H__


#define XDEFAULTRESOLUTION 120
#define YDEFAULTRESOLUTION 120

typedef struct BJF_POS_IMGINFO			/* original image infomation */
{
	long	img_width;					/* original image width */
	long	img_height;					/* original image height */
	double	xresolution;				/* original iamge x resolution */
	double	yresolution;				/* original image y resolution */
} BJF_POS_IMGINFO, *LPBJF_POS_IMGINFO;

typedef struct BJF_POS_PRNINFO			/* printer infomation */
{
	long	topmargin;					/* printer top margin */
	long	leftmargin;					/* printer left margin */
	double  prn_xresolution;			/* printer x resolution */
	double	prn_yresolution;			/* printer y resolution */
	long	prn_width;					/* printer available width */
	long	prn_height;					/* printer available height */
} BJF_POS_PRNINFO, *LPBJF_POS_PRNINFO;

typedef struct BJF_POSINFO				/* scaling and position infomation */
{
	long	mask_width;					/* actual image width */
	long	mask_height;				/* actual image height */
	long	width_offset;				/* x offset when output pixel is over printer available width */
	long	height_offset;				/* y offset when output pixel is over printer available heigth */
	long	out_width;					/* output width */
	long	out_height;					/* otuput height */
	long	leftskip;					/* left skip ( pixel ) */
	long	topskip;					/* top skip ( pixel ) */
	long	page_width;					/* page width ( pixel ) */
	double	scaling;					/* scaling parameter */
} BJF_POSINFO, *LPBJF_POSINFO;

/* function prototypes */
extern void bjf_pos_img_init( LPBJF_POS_IMGINFO lpimginfo );
extern void bjf_pos_prn_init( LPBJF_POS_PRNINFO lpprninfo );
extern void bjf_pos_init( LPBJF_POSINFO lpposinfo );
extern short bjf_pos_imageresolution( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO );
extern short bjf_pos_imageresolution_fit( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO );
extern short bjf_pos_imageresolution_center( LPBJF_POS_IMGINFO, LPBJF_POS_PRNINFO, LPBJF_POSINFO );

extern short bjf_pos_mask_width( LPBJF_POSINFO, long * );
extern short bjf_pos_mask_height( LPBJF_POSINFO, long * );
extern short bjf_pos_width_offset( LPBJF_POSINFO, long * );
extern short bjf_pos_height_offset( LPBJF_POSINFO, long * );
extern short bjf_pos_out_width( LPBJF_POSINFO, long * );
extern short bjf_pos_out_height( LPBJF_POSINFO, long * );
extern short bjf_pos_leftskip( LPBJF_POSINFO, long * );
extern short bjf_pos_topskip( LPBJF_POSINFO, long * );
extern short bjf_pos_page_width( LPBJF_POSINFO , long *);
extern short bjf_pos_scaling( LPBJF_POSINFO, double * );
extern void disp_bjf_posinfo( LPBJF_POSINFO );
extern void disp_bjf_posimg( LPBJF_POS_IMGINFO );
extern void disp_bjf_posprn( LPBJF_POS_PRNINFO );

extern short bjf_pos_set_imgwidth( LPBJF_POS_IMGINFO, long );
extern short bjf_pos_set_imgheight( LPBJF_POS_IMGINFO, long );
extern short bjf_pos_set_imgXres( LPBJF_POS_IMGINFO, double );
extern short bjf_pos_set_imgYres( LPBJF_POS_IMGINFO, double );
extern short bjf_pos_set_prntopmargin( LPBJF_POS_PRNINFO, long );
extern short bjf_pos_set_prnleftmargin( LPBJF_POS_PRNINFO, long );
extern short bjf_pos_set_prnXres( LPBJF_POS_PRNINFO, double );
extern short bjf_pos_set_prnYres( LPBJF_POS_PRNINFO, double );
extern short bjf_pos_set_prnwidth( LPBJF_POS_PRNINFO, long );
extern short bjf_pos_set_prnheight( LPBJF_POS_PRNINFO, long );

#endif
