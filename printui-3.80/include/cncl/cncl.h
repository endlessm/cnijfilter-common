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

#ifndef __CNCL_H__
#define __CNCL_H__

#if defined(__cplusplus)
extern "C"
{
#endif	/* __cplusplus */


#include "cpktypes.h"


/*
 *  Interface Data
 */
typedef struct		
{
	CPKByte CPKPTR		buf ;
	CPKUInt32			size ;
} RasterDataStr, CPKPTR RasterDataPtr ;

typedef struct
{
	CPKByte			TimeInfo ;		/* See cncldef.h for the valid values */
	CPKInt16		Year ;			/* Year, like 1999, 2000 */
	CPKByte			Month ;			/* Month, 1 - 12 */
	CPKByte			Day ;			/* Day, 1 - 31 */
	CPKByte			Hour ;			/* Hour in 24, 0 - 23 */
	CPKByte			Min ;			/* Minutes, 0 - 59 */
	CPKByte			Sec ;			/* Seconds, 0 - 59 */
} CNCL_Time, CPKPTR CNCL_TimePtr ;

typedef struct		
{
	/* The following information has to be set before calling CNCL_StartJob */
	CPKInt16			ModelID ;
	CNCL_Time			CurrentTime ;

	/* The following information has to be set before calling CNCL_SetParam */
	/* Print method information */
	CPKInt16			InkType ;
	CPKInt16			MediaType ;
	CPKInt16			PaperSize ;
	CPKInt16			MediaSupply ;
	CPKInt16			BinMethod ;
	CPKInt16			Grayscale ;
	CPKInt16			PrintQuality ;
	CPKInt16			Intent ;
	CPKInt16			Gamma ;
	CPKInt16			BalanceC ;
	CPKInt16			BalanceM ;
	CPKInt16			BalanceY ;
	CPKInt16			BalanceK ;
	CPKInt16			Density ;
	CPKInt16			Smoothing ;
	CPKInt16			Banner ;
	CPKInt32			PaperWidth ;
	CPKInt32			PaperHeight ;

	/* Source image data information */
	/* The following information has to be set before calling CNCL_SetParam */
	CPKInt32			width ;
	CPKInt32			length ;
	CPKInt16			srcdatatype ;	/* See cncldef.h for the valid values */

	/* The following information has to be set before calling CNCL_SourceData */
	/* The value should be updated each line */
	CPKByte				WhiteLine ;		/* See cncldef.h for the valid values */
	CPKInt32			left_white ;
	CPKInt32			right_white ;
	CPKUInt16			PageNum ;
	CPKInt32			Vpos ;


	/* Input area */
	CPKByte CPKPTR		inputBuffer ;

	/* Command Output area */
	CPKByte CPKPTR		outputBuffer ;
	CPKUInt32			outputSize ;

	/* Raster data output area */
	CPKInt16			numBuf ;
	RasterDataStr		RasterDatas[7] ; /* This member can't use. */
										 /* Please use "rasterDataPtr". */

	/* Work buffer 1 */
	CPKUInt32			Work1Size ;
	CPKVoid CPKPTR		Work1Buf ;

	/* Work buffer 2 */
	CPKUInt32			Work2Size ;
	CPKVoid CPKPTR		Work2Buf ;

	/* File path of Database and Name table */
	CPKChar CPKPTR		TablePath ;

	/* Internal use */
	CPKInt16			ierr ;

	/* Pointer to raster data output area */
	RasterDataPtr		rasterDataPtr ;
	
	CPKInt16			MarginType ;
	CPKInt16			PaperGap ;
	
	CPKChar CPKPTR		CommandParamPtr ;
	CPKInt32			CommandParamSize ;
	
	CPKInt32			ierr2;
	
	CPKInt16			DuplexPrinting ;
	CPKInt16			InkCartridgeSettings ;
	CPKInt16			DuplexCommand ;

	CPKInt16			Contrast ;
	
	CPKInt16			MonochromeTone ;
	
	CPKInt16			ImageRotate;


	CPKInt8				reserved[24] ;
} CNCLData, CPKPTR CNCLPtr ;



/*
 *   Return values ( CNCLErr types)
 *    See cncldef.h for the actual error code.
 */
typedef CPKInt16		CNCLErr ;



/*
 *  CNCL API functions
 */
extern CNCLErr  CNCL_Init ( CNCLPtr lpCnclData ) ;
extern CNCLErr  CNCL_StartJob ( CNCLPtr lpCnclData ) ;
extern CNCLErr  CNCL_EndJob ( CNCLPtr lpCnclData ) ;
extern CNCLErr  CNCL_SetParam ( CNCLPtr lpCnclData ) ;
extern CNCLErr  CNCL_StartPage ( CNCLPtr lpCnclData ) ;
extern CNCLErr  CNCL_EndPage ( CNCLPtr lpCnclData ) ;
extern CPKInt16 CNCL_SourceData ( CNCLPtr lpCnclData ) ;
extern CPKInt16 CNCL_RasterData ( CNCLPtr lpCnclData ) ;
extern CPKInt16 CNCL_FlushData ( CNCLPtr lpCnclData ) ;
extern CNCLErr  CNCL_CompleteData ( CNCLPtr lpCnclData ) ;




#if defined(__cplusplus)
}
#endif	/* __cplusplus */

#endif	/* __CNCL_H__ */
