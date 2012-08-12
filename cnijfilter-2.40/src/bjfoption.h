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

#ifndef __BJFOPTION_H__
#define __BJFOPTION_H__

#define ON  1
#define OFF 0

#define	BBOX_ON		1
#define	BBOX_OFF	0


#define	OPTGUI			1
#define OPTMODEL		2
#define OPTCARTRIDGE	3
#define OPTMEDIA		4
#define OPTQUALITY		5
#define OPTGRAY			6
#define OPTHALFTONE		7
#define OPTBANNER		8
#define OPTLOAD			9
#define OPTCORRECT		10
#define OPTRENDER		11
#define OPTSOURCE		12
#define OPTBALC			13
#define OPTBALM			14
#define OPTBALY			15
#define OPTBALK			16
#define OPTGAMMA		17
#define OPTDENSITY		18
#define OPTPSIZE		19
#define OPTLGMON		20
#define OPTIMGRES		21
#define OPTDISPLAY		22
#define OPTFIT			23
#define OPTLOCATION		24
#define OPTINTVER		25
#define	OPTFULL			26

#define OPTBORDERLESS	30
#define OPTEXTENSION	31
#define OPTPERCENT		32
#define	OPTBBOX			33
#define OPTCOPIES		34
#define OPTREVPRINT		35
#define OPTCOLLATE		36

#define OPTPAPERWIDTH	37
#define OPTPAPERHEIGHT	38

#define OPTPAPERGAP		39


#define	OPTINDEX(x)		( (x >> 5) & 0xf)
#define	OPTBIT(x)		( 1 << (x & 0x1f) )

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
#define OPTSTRLOAD			"paperload"
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
#define OPTSTRFULL			"full"
#define OPTSTRINTVER		"internalversion"	
#define OPTSTRBORDERLESS	"borderless"
#define OPTSTREXTENSION		"extension"
#define OPTSTRPERCENT		"percent"
#define OPTSTRBBOX			"bbox"
#define OPTSTRPRNAREA		"prnarea"
#define OPTSTRCOPIES		"copies"
#define OPTSTRREVPRINT		"revprint"
#define OPTSTRCOLLATE		"collate"

#define OPTSTRPAPERWIDTH	"paperwidth"
#define OPTSTRPAPERHEIGHT	"paperheight"

#define	OPTSTRPAPERGAP		"papergap"

/* cif.bscc value */
#define	BSCCREG		0


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
	int		full;
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
	char	*bbox;
	int		borderless;
	int		extension;
	int		percent;
	int		copies;
	int		revprint;
	int		collate;
	char	*paperwidth;
	char	*paperheight;
	char	*papergap;
} OPT, *LPOPT;


typedef struct {
	short	bbox_flag;
	short	dummy;
	long	value[4];
} BJF_BBOX, *LPBJF_BBOX;


typedef struct {
	short	location;
	short	fit;
	short	ui;
	short	stdswitch;
	short	imageres;
	short	modelid;
	short	lgmon;
	short	extension;
	short	percent;
	short	copies;
	short	revprint;
	short	collate;
	BJF_BBOX	bbox;
} BJF_OPTINFO, *LPBJF_OPTINFO;



extern 	short SetCmdOption(int, char **, LPBJF_OPTINFO, LPBJFLTCOLORSYSTEM, LPBJFLTDEVICE, LPCNCLPAPERSIZE, char *, char *, char *);
extern void MakeModelnameConfname(  char *, char *, char *, char *, char *);

#endif
