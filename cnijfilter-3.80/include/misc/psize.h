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

#define PSID	0
#define	YOKO	1
#define	TATE	2

#ifdef	DEFINE_GLOBALS

const long PaperTbl[][3] = 
{
	{0, 14800, 21000},		/* A5 (148mm x 210mm) */
	{1, 21000, 14800},		/* A5-L (210mm x 148mm) */
	{2, 21000, 29700},		/* A4 (210mm x 297mm) */
	{3, 29700, 21000},		/* A4-L (297mm x 210mm) */
	{4, 29700, 42000},		/* A3 (297mm x 420mm) */
	{5, 42000, 29700},		/* A3-L (420mm x 297mm) */
	{6, 42000, 59400},		/* A2 (420mm x 594mm) */
	{7, 18200, 25700},		/* B5 (182mm x 257mm) */
	{8, 25700, 18200},		/* B5-L (257mm x 182mm) */
	{9, 25700, 36400},		/* B4 (257mm x 364mm) */
	{10, 36400, 25700},		/* B4-L (364mm x 257mm) */
	{11, 36400, 51500},		/* B3 (364mm x 515mm) */
	{12, 21590, 27940},		/* Letter (8.5x 11inch) */
	{13, 27940, 21590},		/* Letter-L (11inch x 8.5inch) */
	{14, 21590, 35560},		/* Legal (8.5inch x 14inch) */
	{15, 35560, 21590},		/* Legal-L (14inch x 8.5inch) */
	{16, 27940, 43180},		/* Ledger  (11inch x 17inch) */
	{17, 43180, 27940},		/* Ledger-L (17inch x 11inch) */
	{18, 43180, 55800},		/* C size (17 x 22inch) */
	{19, 10000, 14800},		/* Postcard (10mm 0x 148mm) */
	{20, 14800, 10000},		/* Postcard-L (14mm 8x 100mm) */
	{21, 24130, 10477},		/* #10 Envelope (9.5inch x 4.125inch) */
	{22, 22000, 11000},		/* DL Envelope (220mm x 110mm) */
	{23, 34290, 43180},		/* Foolscap (13.5inch x 17inch) */
	{24, 21590, 27940},		/* Fanfold (8.5inch x 11inch) */
	{25, 24130, 27940},		/* Fanfold (9.5inch x 11inch) */
	{26, 25400, 27940},		/* Fanfold (10inch x 11inch) */
	{27, 25400, 30480},		/* Fanfold (10inch x 12inch) */
	{28, 30480, 21590},		/* Fanfold (12inch x 8.5inch) */
	{29, 36830, 27940},		/* Fanfold (14.5inch x 11inch) */
	{30, 38100, 27940},		/* Fanfold (15inch x 11inch) */
	{31, 38100, 30480},		/* Fanfold (15inch x 12inch) */
	{32, 37782, 27940},		/* Fanfold (14.875inch x 11inch) */
	{33, 23500, 10500},		/* Envelope-J4 */
	{34, 19000,  9800},		/* Envelope-J6 */
	{35, 22860, 33782},		/* Letter full-bleed */
	{36, 22350, 35560},		/* A4 full-bleed */
	{37, 32900, 48300},		/* A3 plus */
	{38, 11860, 21390},		/* Photocard (FM-101) */
	{39, 0,0},				/* User define */
	{40, 0,0},				/* Not Applicable */
	{1046, 10477, 24130},	/* #10 Envelope Tate (4.125inch x 9.5inch) */
	{1047, 11000, 22000},	/* DL Envelope Tate ( 110mm x 220mm ) */
	{1048, 10500, 23500},	/* Envelope-J4 Tate ( 105mm x 235mm ) */
	{1049,  9800, 19000},	/* Envelope-J6 Tate (  98mm x 190mm ) */
	{1050,  8900, 12700},	/* Actual Size L ( 89mm x 127mm ) */
	{1051, 12700, 17800},	/* Actual Size 2L ( 127mm x 178mm ) */
	{1052, 10160, 15240},	/* Actual Size 4x6 ( 101.6mm x 152.4mm ) */
	{1054, 5500, 9100},	/* Business card ( 55mm x 91mm ) */
	{1055, 12700, 17780},	/* Actual Size 5x7 ( 127mm x 177.8mm ) */
	{1056,  8900, 25400},	/* Panorama or L x 2 ( 89mm x 254mm ) */
	{1057, 20000, 14800},	/* Double postal card ( 200mm x 148mm ) */
	{1058, 12000, 23500},	/* Long Env #3( 120mm x 235mm ) */
	{1059, 9000, 20500},	/* Long Env #4 ( 90mm x 205mm ) */
	{1065, 5400, 8600},	/* Credit card ( 54mm x 86mm ) */
	{1066, 21000, 29700},	/* A4 Fine Art */
	{1069, 21590, 27940},	/* Letter Fine Art */
	{1070, 10160, 20320},	/* 4x8 (101.6x203.2mm) */
	{1072, 25400, 30480},	/* 10x12 (254.0x304.8mm) */
	{1073, 20320, 25400},	/* 8x10 (203.2x254.0mm) */
	{1082, 10160, 18062},	/* wide */
	{1088, 21000, 29700},	/* A4 Art(35mm margin) */
	{1090, 21590, 27940},	/* Letter Art(35mm margin) */
	{-1, -1, -1}			/* Max indicator */	
};

#else

extern const long PaperTbl[][3];

#endif

