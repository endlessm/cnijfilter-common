/*
 *  Canon Bubble Jet Print Filter for Linux
 *  Copyright CANON INC. 2001-2005 
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

#ifndef __CNCL2DEF_H__
#define __CNCL2DEF_H__

/* Model ID (ModelID) */
#define	CND_BJF360		(1098)	/* BJF360 can use CND_BJINK_BC30/33/34, or CND_BJINK_BK/COLOR/PHOTO */
#define	CND_BJS600		(1104)	
#define	CND_BJS6300		(1113)	
#define	CND_BJS630		(1123)	

#define	CND_BJF900		(1125)
#define	CND_BJF9000		(1127)
#define	CND_BJS300		(1117)
#define	CND_BJS500		(1131)

#define	CND_PIXUS550I	(1154)
#define	CND_PIXUS850I	(1156)
#define	CND_PIXUS950I	(1158)

#define	CND_I250		(1180)
#define	CND_I255		(1182)

#define	CND_PIXUS560I	(1189)
#define	CND_PIXUS860I	(1187)
#define	CND_PIXUS990I	(1191)

#define	CND_PIXMAIP1000        (1230)
#define	CND_PIXMAIP1500        (1214)
#define	CND_PIXUSIP3100         (1218)
#define	CND_PIXUSIP4100         (1221)
#define	CND_PIXUSIP8600         (1238)


/* MediaType (MediaType) */
#define	CND_MEDIA_MATTE		(1028)
#define	CND_MEDIA_SUPER_PHOTO	(1029)
#define	CND_MEDIA_DISC1		(1031)
#define	CND_MEDIA_DISC2		(1032)
#define	CND_MEDIA_OTHER_PHOTO_PAPER	(1036)
#define	CND_MEDIA_DUPLEX_GLOSSY_PAPER	(1037)

/* PaperSize (Paper Size) */
#define CND_SIZE_ENV_10_P	(1046)
#define CND_SIZE_ENV_DL_P	(1047)
#define CND_SIZE_ENV_J4_P	(1048)
#define CND_SIZE_ENV_J6_P	(1049)
#define CND_SIZE_L			(1050)
#define CND_SIZE_2L			(1051)
#define CND_SIZE_4X6		(1052)
#define CND_SIZE_DISCTRAY	(1053)
#define CND_SIZE_PANORAMA	(1056)

#define CND_SIZE_BUSINESSCARD   (1054)
#define CND_SIZE_5X7			(1055)
#define CND_SIZE_POST_DBL      	(1057)
#define CND_SIZE_ENV_CHOU3_P    (1058)
#define CND_SIZE_ENV_CHOU4_P    (1059)
#define CND_SIZE_DISCTRAY3      (1064)
#define CND_SIZE_CREDITCARD     (1065)


/* Intent */
#define CND_INTENT_VIVID	(1003)


#endif
