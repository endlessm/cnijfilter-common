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

#ifndef _CNCLUDEF_H_
#define _CNCLUDEF_H_

/************************************************************/
/* Parameter ID not defined in cncldef.h					*/
/************************************************************/
/* Object ID */
enum
{
	CNCL_MEDIATYPE,			
/*	CNCL_PRINTCOLOR,		*/
	CNCL_PRINTQUALITY,		
	CNCL_SMOOTHING,			
	CNCL_MEDIASUPPLY,		
	CNCL_QUALITYLEVEL,		
	CNCL_RESOLUTION_APP_V,	
	CNCL_RESOLUTION_APP_H,	
	CNCL_ENHBK,				
	CNCL_PAPERSIZE,			
	CNCL_MESS_QUALITY,		
	CNCL_MESS_THICK,		
	CNCL_MESS_PAPERLOAD,	
	CNCL_MESS_RESOLUTION,	
	CNCL_MESS_SMLIB,		
/*	CNCL_INKSYSTEM,	 */
	CNCL_DITHER_PAT,		
	CNCL_COLOR_COLLECTION,	
	CNCL_BANNER,			
	CNCL_CARTRIDGE,			
	CNCL_GRAYSCALE,			
/*	CNCL_BIN_METHOD, */		
/*	CNCL_NATIVE_VER, */		
/*	CNCL_COUNTRY,	 */		
	CNCL_MESS_Q_MAP1,		
	CNCL_MESS_Q_MAP2,		
	CNCL_MESS_Q_MAP3,		
	CNCL_MESS_AUTO_HT_ED,	
	CNCL_MESS_AUTO_HT_PAT,	
	CNCL_INPUT_GAMMA,		
	CNCL_MARGINTYPE,
	CNCL_VIVID,
	CNCL_PAPERGAP_COMMAND,
	CNCL_OVERMARGIN_LEVEL,
	CNCL_DUPLEX_PRINTING,
	CNCL_INKCARTRIDGESETTINGS,
	CNCL_INTENT,
	CNCL_DEFMEDIATYPE_MINUS,	  /* Ver.2.90 */
	CNCL_COMMAND_TYPE,			  /* Ver.3.20 */
	CNCL_LOWER_PAPERSUPPORT_SIZE, /* Ver.3.50 */
    CNCL_BLACK_ADJUSTMENT,        /* Ver.3.60 */
    CNCL_IMG_DIRECTION_CMD        /* Ver.3.80 */
};

/* Media Type */
/* defined in cncl.h */

/* Print Quality */
/* this parameter is not used */

/* Smoothing */
/* defined in cncl.h */

/* Media Supply */
/* defined in cncl.h */

/* Quality Level */
enum
{
	CND_LEVEL_5,		/* 5 level */	
	CND_LEVEL_4,		/* 4 level */
	CND_LEVEL_3,		/* 3 level */
	CND_LEVEL_2,		/* 2 level */	
	CND_LEVEL_1,		/* 1 level */
	CND_LEVEL_NA,		/* Not Applicable */
};

/* Verticality Resolution */
enum
{
	CND_RESAPP_V_NA,	/* Not Applicable */
};

/* Horizontally Resolution */
enum
{
	CND_RESAPP_H_NA,	/* Not Applicable */
};

/* emphasis black */
enum
{
	CND_ENH_NOT,
	CND_ENH_ENH,
	CND_ENH_NA,			/* Not Applicable */
	CND_ENH_MAX,		/* Max Indicator */
};

/* Paper Size */
/* defined in cncl.h */

/* Print Quality Message */
enum
{
	CND_QMESSAGE_FINE,		/* FINE */
	CND_QMESSAGE_FINE2,		/* FINE2 */
	CND_QMESSAGE_CP,		/* CP */
	CND_QMESSAGE_HQ,		/* HQ */
	CND_QMESSAGE_NORMAL,	/* NORMAL */
	CND_QMESSAGE_HS,		/* HS */
	CND_QMESSAGE_ECONOMY,	/* ECONOMY */
	CND_QMESSAGE_PHOTO0,	/* PHOTO0 */
	CND_QMESSAGE_PHOTO,		/* PHOTO */
	CND_QMESSAGE_PHOTO2,	/* PHOTO2 */
	CND_QMESSAGE_DRAFT,	
	CND_QMESSAGE_Q1,
	CND_QMESSAGE_Q2,
	CND_QMESSAGE_Q3,
	CND_QMESSAGE_Q4,
	CND_QMESSAGE_Q2_STD,
	CND_QMESSAGE_NA,		/* Not Applicable */
	CND_QMESSAGE_MAX,		/* Max Indicator */
}; 

/* Paper Position Message */
enum
{
	CND_TMESSAGE_POSITION1,
	CND_TMESSAGE_POSITION2,
	CND_TMESSAGE_POSITION3,
	CND_TMESSAGE_LEFT,	
	CND_TMESSAGE_CENTER,
	CND_TMESSAGE_RIGHT,	
	CND_TMESSAGE_LOWER,	
	CND_TMESSAGE_UPPER,	
	CND_TMESSAGE_LOWER2,
	CND_TMESSAGE_UPPER2,
	CND_TMESSAGE_LEFT2,		/* (Ver.2.70) */
	CND_TMESSAGE_RIGHT2,	/* (Ver.2.70) */
	CND_TMESSAGE_NA,		/* Not Applicable */
	CND_TMESSAGE_MAX,		/* Max Indicator */
};

/* Supplied Paper Position Message */
enum
{
	CND_PLMESSAGE_FORWARD,	
	CND_PLMESSAGE_BACKWARD,	
	CND_PLMESSAGE_LOWER,	
	CND_PLMESSAGE_UPPER,	
	CND_PLMESSAGE_NA,		/* Not Applicable */
	CND_PLMESSAGE_MAX,		/* Max Indicator */
};

/* Resolutoin displayed */
enum
{
	CND_RESMESS_180_180,	/* 180x180dpi */
	CND_RESMESS_360_360,	/* 360x360dpi */
	CND_RESMESS_720_360,	/* 720x360dpi */
	CND_RESMESS_720_720,	/* 720x720dpi */
	CND_RESMESS_300_300,	/* 300x300dpi */
	CND_RESMESS_600_600,	/* 600x600dpi */
	CND_RESMESS_1200_600,	/* 1200x600dpi */
	CND_RESMESS_1200_1200,	/* 1200x1200dpi */
	CND_RESMESS_1440_720,	/* 1440x720dpi */
	CND_RESMESS_1440_1440,	/* 1440x1440dpi */
	CND_RESMESS_NA,			/* Not Applicable */
	CND_RESMESS_SPACE,
	CND_RESMESS_MAX,		/* Max Indicator */
};

/* Smoothing library */
enum
{
	CND_SLMESS_NOT,		
	CND_SLMESS_SMOOTH,	
	CND_SLMESS_MYSTCUT,	
	CND_SLMESS_NA,			/* Not Applicable */
	CND_SLMESS_MAX,			/* Max Indicator */
};

/* Dither Pattern  */
enum
{
	CND_UIBIN_PATTERN,		
	CND_UIBIN_PATTERN_HS,	
	CND_UIBIN_V_PATTERN,	
	CND_UIBIN_ED,			
	CND_UIBIN_NA,				/* Not Applicable */
	CND_UIBIN_MAX,				/* Max Indicator */
};



/* Color Correction */
enum
{
	CND_COLLECTION_4,	
	CND_COLLECTION_3,	
	CND_COLLECTION_NA,		/* Not Applicable */
};

/* banner */
/* defiend in cncl.h */

/* Cartridge */
enum
{
	CND_CARTRIDGE_COLOR,		
	CND_CARTRIDGE_BK,			
	CND_CARTRIDGE_PHOTO,		
	CND_CARTRIDGE_BK_COLOR,		
	CND_CARTRIDGE_BK_PHOTO,		
	CND_CARTRIDGE_PHOTO_COLOR,	
	CND_CARTRIDGE_NA,			
	CND_CARTRIDGE_MAX,			/* Max Indicator */
};

/* Gray Scale */
/* defined in cncl.h */

/* Margin Type */
/* defined in cncldef.h */

/* Vivid support */
enum {
	CND_VIVID_SUPPORT,
	CND_VIVID_NA,
	CND_VIVID_MAX,
};

/* Paper Gap */
/* defined in cncldef.h */

/* Over Margin Level */
enum{
	CND_OVERMARGINLEVEL_00,
	CND_OVERMARGINLEVEL_01,
	CND_OVERMARGINLEVEL_02,
	CND_OVERMARGINLEVEL_03,
	CND_OVERMARGINLEVEL_NA,
	CND_OVERMARGINLEVEL_MAX,
};

/* Duplex Printing */
/* defined in cncldef.h */

/* Command Type */
enum{
	CND_COMMAND_TYPE_00,
	CND_COMMAND_TYPE_01,
	CND_COMMAND_TYPE_MAX,
};

/* Table Format Type */
#define	CND_FORMATTYPE_1	(1)
#define	CND_FORMATTYPE_2	(2)
#define	CND_FORMATTYPE_3	(3)
#define	CND_FORMATTYPE_4	(4)
#define	CND_FORMATTYPE_5	(5)
#define	CND_FORMATTYPE_6	(6)
#define	CND_FORMATTYPE_7	(7)	/* add 20071113 */
#define	CND_FORMATTYPE_8	(8)	/* add 20080318 */
#define	CND_FORMATTYPE_9	(9)	/* add 20090410 */
#define	CND_FORMATTYPE_10	(10) /* add 20090903 */
#define	CND_FORMATTYPE_11	(11) /* add 20100222 */
#define	CND_FORMATTYPE_12	(11) /* add Driver Versionn Ver.3.60 */

#endif
