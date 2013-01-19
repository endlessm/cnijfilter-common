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

#define CND_IP100        (1303)
#define CND_IP2600        (1331)

#define CND_IP3600        (1333)
#define CND_IP4600        (1334)
#define CND_MP630         (1336)
#define CND_MP540         (1338)
#define CND_MP240         (1341)
#define CND_MP190         (1342)
#define CND_IP1900        (1346)

#define CND_MX860         (1347)
#define CND_MX320         (1348)
#define CND_MX330         (1349)

#define CND_MP250         (1356)
#define CND_MP270         (1357)
#define CND_MP490         (1358)
#define CND_MP550         (1359)
#define CND_MP560         (1360)
#define CND_IP4700        (1361)
#define CND_MP640         (1362)

#define CND_IP2700        (1364)
#define CND_MX340         (1365)
#define CND_MX350         (1366)
#define CND_MX870         (1367)

#define CND_MP280         (1370)
#define CND_MP495         (1369)
#define CND_MG5100        (1373)
#define CND_MG5200        (1374)
#define CND_IP4800        (1375)
#define CND_MG6100        (1376)
#define CND_MG8100        (1377)

#define CND_MX360         (1380)
#define CND_MX410         (1381)
#define CND_MX420         (1382)
#define CND_MX880         (1383)
#define CND_IX6500        (1384)

#define CND_MG2100        (1386)
#define CND_MG3100        (1387)
#define CND_MG4100        (1388)
#define CND_MG5300        (1389)
#define CND_MG6200        (1390)
#define CND_MG8200        (1391)
#define CND_IP4900        (1392)
#define CND_E500          (1393)

#define CND_MX710         (1394)
#define CND_MX890         (1395)
#define CND_MX370         (1396)
#define CND_MX430         (1397)
#define CND_MX510         (1398)
#define CND_E600          (1399)

#define CND_MP230         (1401)
#define CND_MG2200        (1402)
#define CND_E510          (1403)
#define CND_MG3200        (1404)
#define CND_MG4200        (1405)
#define CND_IP7200        (1406)
#define CND_MG5400        (1407)
#define CND_MG6300        (1408)

/* MediaType (MediaType) */
#define	CND_MEDIA_MATTE		(1028)
#define	CND_MEDIA_SUPER_PHOTO	(1029)
#define	CND_MEDIA_DISC1		(1031)
#define	CND_MEDIA_DISC2		(1032)
#define	CND_MEDIA_OTHER_PHOTO_PAPER	(1036)
#define	CND_MEDIA_DUPLEX_GLOSSY_PAPER	(1037)
#define	CND_MEDIA_FINE_ART_PAPER		(1040)
#define	CND_MEDIA_OTHER_FINE_ART_PAPER	(1041)
#define CND_MEDIA_PHOTO_PAPER_SEMI_GLOSS	(1042)
#define CND_MEDIA_PHOTO_PAPER_PLUS_GLOSSY_II	(1050)
#define CND_MEDIA_PHOTO_PAPER_PRO_PLATINUM		(1051)
#define CND_MEDIA_PHOTO_PAPER_PRO_II			(1052)
#define CND_MEDIA_CONTENTS_GLOSSY				(1054)
#define CND_MEDIA_CONTENTS_PROPHOTO				(1055)
#define CND_MEDIA_ADDRESS_POSTCARD				(1056)
#define CND_MEDIA_PHOTO_PAPER_PRO_LUSTER		(1063)

  /* !!!!  When add, increase CND_MEDIA_MAX  !!!!  */
#define CND_MEDIA_MAX (18+16) /* media num(cncldef.h + this file) */


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
#define CND_SIZE_4GIRI          (1072)
#define CND_SIZE_6GIRI          (1073)
#define CND_SIZE_DISCTRAY4      (1074)
#define CND_SIZE_DISCTRAY5      (1075)
#define CND_SIZE_A4_FINE_ART    (1066)
#define CND_SIZE_LETTER_FINE_ART (1069)

#define CND_SIZE_A4_ART_35_2    (1088)
#define CND_SIZE_LETTER_ART_35_2 (1090)

#define CND_SIZE_HIVISION       (1082)

/* Intent */
#define CND_INTENT_VIVID	(1003)

/* BLACK_ADJUSTMENT ver.3.5.0 */
#define CND_BLACK_ADJUSTMENT    (1001)
#define CND_BLACK_ADJUSTMENT_NA (1010)

/* ImageRotate ver.3.8.0 */
#define CND_IMG_DIRECTION_CMD_NA	(1000)
#define CND_IMG_DIRECTION_CMD_TYPEA	(1001)



#endif
