/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2007 
 *  All Rights Reserved.
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

#define	CND_IP2200        (1256)
#define	CND_IP4200        (1260)
#define	CND_IP6600D       (1265)
#define	CND_IP7500        (1266)
#define	CND_MP500         (1273)

#define	CND_IP3300        (1292)
#define	CND_MP510         (1293)
#define	CND_IP4300        (1294)
#define	CND_MP600         (1295)
#define	CND_MP160         (1291)
#define	CND_IP90          (1253)
#define	CND_IP2500        (1311)
#define	CND_IP1800        (1312)

#define CND_MP140         (1315)
#define CND_MP210         (1316)
#define CND_IP3500        (1319)
#define CND_IP4500        (1326)
#define CND_MP610         (1327)
#define CND_MP520         (1328)

/* MediaType (MediaType) */
#define	CND_MEDIA_MATTE		(1028)
#define	CND_MEDIA_SUPER_PHOTO	(1029)
#define	CND_MEDIA_DISC1		(1031)
#define	CND_MEDIA_DISC2		(1032)
#define	CND_MEDIA_OTHER_PHOTO_PAPER	(1036)
#define	CND_MEDIA_DUPLEX_GLOSSY_PAPER	(1037)
#define	CND_MEDIA_FINE_ART_PAPER		(1040)
#define	CND_MEDIA_OTHER_FINE_ART_PAPER	(1041)
#define CND_MEDIA_PHOTO_PAPER_PLUS_GLOSSY_II	(1050)

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

#define CND_SIZE_4X8            (1070)
#define CND_SIZE_6GIRI          (1073)
#define CND_SIZE_DISCTRAY4      (1074)
#define CND_SIZE_DISCTRAY5      (1075)
#define CND_SIZE_A4_FINE_ART    (1066)

#define CND_SIZE_HIVISION       (1082)

/* Intent */
#define CND_INTENT_VIVID	(1003)


#endif
