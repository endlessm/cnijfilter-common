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

#ifndef __BJFILTER_H__
#define __BJFILTER_H__

#define ON		1
#define OFF		0


/* structure define */
typedef struct BJFILTERINFO
{
	char			 	filename[255];
	int					prn;
	FILE				*prn_maint;
	FILE				*debug;
	BJF_IMAGEINFO		bjfimage;				/* work for image process module */
	BJF_POS_IMGINFO		bjfposimg;				/* original image infomation */
	BJF_POS_PRNINFO		bjfposprn;				/* printer infomation */
	BJF_POSINFO			bjfposinfo;				/* position infomation */
	BJF_OPTINFO			bjfoption;				/* option infomation */
	BJF_MARGIN_INFO		bjfmgninfo;				/* borderless information */
	int					pipefds[2];				/* File descriptor for pipes */
	int					pid_lgmon;				/* save lgmon process id */
	int					bsccfile_exist;			/* bsccfile flag */
	char			 	bsccname[256];			/* bsccfile name */
} BJFILTERINFO,*LPBJFILTERINFO;


typedef struct CIFRASTERINFO
{
	CNCLPtr				lpCnclData;
	CPKByte CPKPTR		rgb_buf;
	long				image_height;
	long				page_width;
	long				width;
	long				height;
	long				top_skip;
	short				bpp;
	short				rev_flag;
	CPKUInt16			page;
	int					fd;
} CIFRASTERINFO,*LPCIFRASTERINFO;


#endif

