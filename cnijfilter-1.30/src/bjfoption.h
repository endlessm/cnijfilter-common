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

#ifndef __BJFOPTION_H__
#define __BJFOPTION_H__

#define ON  1
#define OFF 0

#define OPTLOCATION		0x00000001
#define OPTMODEL		0x00000002
#define OPTCARTRIDGE	0x00000004
#define OPTMEDIA		0x00000008
#define OPTQUALITY		0x00000010
#define OPTGRAY			0x00000020
#define OPTHALFTONE		0x00000040
#define OPTBANNER		0x00000080
#define OPTLOAD			0x00000100
#define OPTCORRECT		0x00000200
#define OPTRENDER		0x00000400
#define OPTSOURCE		0x00000800
#define OPTBALC			0x00001000
#define OPTBALM			0x00002000
#define OPTBALY			0x00004000
#define OPTBALK			0x00008000
#define OPTGAMMA		0x00010000
#define OPTDENSITY		0x00020000
#define OPTPSIZE		0x00040000
#define OPTLGMON		0x00080000
#define OPTIMGRES		0x00100000
#define OPTDISPLAY		0x00200000
#define OPTFIT			0x00400000
#define OPTINTVER		0x00800000

#define OPTLOC_UPPERLEFT		0
#define OPTLOC_CENTER			1

/* command line option define */
#define OPTSTRGUI			"gui"
#define OPTSTRLOCATION		"location"
#define OPTSTRMODEL			"model"
#define OPTSTRCARTRIDGE		"cartridge"
#define OPTSTRMEDIA			"media"
#define OPTSTRQUALITY		"quality"
#define OPTSTRGRAY			"grayscale"
#define OPTSTRHALFTONE		"halftoning"
#define OPTSTRBANNER		"banner"
#define OPTSTRLOAD			"load"
#define OPTSTRCORRECT		"correctionmode"
#define OPTSTRRENDER		"renderintent"
#define OPTSTRSOURCE		"imagesource"
#define OPTSTRBALC			"balance_c"
#define OPTSTRBALM			"balance_m"
#define OPTSTRBALY			"balance_y"
#define OPTSTRBALK			"balance_k"
#define OPTSTRGAMMA			"gamma"
#define OPTSTRDENSITY		"density"
#define OPTSTRPSIZE			"papersize"
#define OPTSTRLGMON			"lgmon"
#define OPTSTRIMGRES		"imageres"
#define OPTSTRDISPLAY		"display"
#define OPTSTRFIT			"fit"
#define OPTSTRINTVER		"internalversion"	

/* data base file path */
#define	BJLIBPATH			"/usr/lib/bjlib"

/* structure define */
typedef struct {
	int		gui;
/*	int		quality; */
	int		grayscale;
	int		banner;
	int		balance_c;
	int		balance_m;
	int		balance_y;
	int		balance_k;
	int		density;
	int		lgmon;
	int		imageres;
	int		fit;
	int		internalversion;
	char	*location;
	char	*model;
	char	*cartridge;
	char	*media;
	char	*halftoning;
	char	*paperload;
	char	*correctionmode;
	char	*renderintent;
	char	*imagesource;
	char	*gamma;
	char	*papersize;
	char	*display;
	char	*quality;
} OPT, *LPOPT;

typedef struct {
	short	location;
	short	fit;
	short	ui;
	short	stdswitch;
	short	imageres;
	short	modelid;
	short	lgmon;
} BJF_OPTINFO, *LPBJF_OPTINFO;

extern void usage( void );
extern int cmdlinesw(poptContext*, OPT*, LPBJF_OPTINFO, LPBJFLTCOLORSYSTEM, LPBJFLTDEVICE, LPCNCLPAPERSIZE, char*, char *);
extern void init_optioninfo( LPBJF_OPTINFO lpbjfoption );

#endif
