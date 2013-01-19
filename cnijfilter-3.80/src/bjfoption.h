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

#define NETWORK_SUPPORT_YES		1
#define NETWORK_SUPPORT_NO		0

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
#define OPTHELP			40
#define OPTDUPLEX		41
#define OPTSTAPLESIDE	42
#define OPTINKCARTRIDGESETTINGS		43

#define OPTCONTRAST		44

#define OPTBIDI					45
#define OPTSUPPORTNETWORK		46
#define OPTTONE			47

#define OPTROTATE		48

#define	OPTINDEX(x)		( (x >> 5) & 0xf)
#define	OPTBIT(x)		( 1 << (x & 0x1f) )

/* command line option define */
#define OPTSTRLOCATION		"location"

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
#define	OPTSTRHELP			"help"
#define	OPTSTRDUPLEX			"duplex"
#define OPTSTRSTAPLESIDE	"stapleside"
#define OPTSTRINKCARTRIDGESETTINGS		"inkcartridgesettings"

#define OPTSTRCONTRAST		"contrast"

#define OPTSTRBIDI				"bidi"
#define OPTSTRSUPPORTNETWORK	"supportnetwork"

#define OPTSTRTONE			"tone"

#define OPTSTRROTATE		"rotate"

/* cif.bscc value */
#define	BSCCREG		0


/* structure define */
typedef struct {
/*	int		quality; */
	int		grayscale;
	int		banner;
	int		balance_c;
	int		balance_m;
	int		balance_y;
	int		balance_k;
	int		density;
	int		contrast;
	int		imageres;
	int		fit;
	int		full;
	int		internalversion;
	char	*location;
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
	int		help;
	int		duplex;
	char	*stapleside;
	char	*inkcartridgesettings;
	int		bidi;
	int		supportnetwork;
	int		tone;
	int		rotate;
} OPT, *LPOPT;


typedef struct {
	short	bbox_flag;
	short	dummy;
	long	value[4];
} BJF_BBOX, *LPBJF_BBOX;


typedef struct {
	short	location;
	short	fit;
	short	stdswitch;
	short	imageres;
	short	modelid;
	short	extension;
	short	percent;
	short	copies;
	short	revprint;
	short	collate;
	short	stapleside;
	short	is_ivec;
	short	rotate;
	BJF_BBOX	bbox;
} BJF_OPTINFO, *LPBJF_OPTINFO;

/* over margin */
static short ExtensionTbl[][2] = 
{
	{0, CND_OVERMARGINLEVEL_00},
	{1, CND_OVERMARGINLEVEL_01},
	{2, CND_OVERMARGINLEVEL_02},
	{3, CND_OVERMARGINLEVEL_03},
	{-1, -1}			/* Max indicator */	
};



#define		OPT_ERR_IME			(0)
#define		OPT_ERR_CAR			(1)
#define		OPT_ERR_MED			(2)
#define		OPT_ERR_HAL			(3)
#define		OPT_ERR_QUA			(4)
#define		OPT_ERR_PAP			(5)
#define		OPT_ERR_PAL			(6)
#define		OPT_ERR_EXT			(7)
#define		OPT_ERR_LOC			(8)
#define		OPT_ERR_PER			(9)
#define		OPT_ERR_COP			(10)
#define		OPT_ERR_INT			(11)
#define		OPT_ERR_GAM			(12)
#define		OPT_ERR_BAC			(13)
#define		OPT_ERR_BAM			(14)
#define		OPT_ERR_BAY			(15)
#define		OPT_ERR_BAK			(16)
#define		OPT_ERR_DEN			(17)
#define		OPT_ERR_GAP			(18)
#define		OPT_ERR_BBOX		(19)
#define		OPT_ERR_STAPLE		(20)
#define		OPT_ERR_INKCAR		(21)
#define		OPT_ERR_CONTRAST	(22)
#define		OPT_ERR_TONE		(23)
#define		OPT_ERR_ROTATE		(24)

#define		OPT_ERR_CODE_MAX	(25)


static char usage_err_mes[OPT_ERR_CODE_MAX][256]={
	"Allowed argument of \"--imageres\" : 1 - 32767\n",
	"",
	"",
	"Allowed argument of \"--halftoning\" : ed / pattern\n",
	"Allowed argument of \"--quality\" : 1 - 5\n",
	"",
	"",
	"Allowed argument of \"--extension\" : 0 - 3\n",
	"Allowed argument of \"--location\" : upperleft / center\n",
	"Allowed argument of \"--percent\" : 20 - 400\n",
	"Allowed argument of \"--copies\" : 1 - 999\n",
	"",
	"Allowed argument of \"--gamma\" : 1.4 / 1.8 / 2.2\n",
	"Allowed argument of \"--balance_c\" : -50  -   50\n",
	"Allowed argument of \"--balance_m\" : -50  -   50\n",
	"Allowed argument of \"--balance_y\" : -50  -   50\n",
	"Allowed argument of \"--balance_k\" : -50  -   50\n",
	"Allowed argument of \"--density\" : -50  -   50\n",
	"Allowed argument of \"--papergap\" : auto / wide\n",
	"",
	"Allowed argument of \"--stapleside\" : longside / shortside\n",
	"",
	"Allowed argument of \"--contrast\" : -50  -   50\n",
	"Allowed argument of \"--tone\" : -50  -   50\n",
	"Allowed argument of \"--rotate\" : 0  -  3\n",
	
};




extern 	short SetCmdOption(int, char **, LPBJF_OPTINFO, LPBJFLTCOLORSYSTEM, LPBJFLTDEVICE, LPCNCLPAPERSIZE, char *, char *, char *);
extern void MakeModelnameConfname(  char *, char *, char *, char *, char *);
extern short CheckSettings( LPBJFLTDEVICE , char * );

#endif
