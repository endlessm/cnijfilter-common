/*  Canon Inkjet Printer Driver for Linux
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>
#ifdef	USE_LIB_GLADE
#	include <glade/glade.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "callbacks.h"
#ifndef USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"

#include "util_cmd.h"
#include "util_com.h"
#include "util_setconfig.h"

/* parameter for spinbutton */
typedef struct {
	char	*CtrlName;				
	short	nDefault;               
	short	nMin;                   
	short	nMax;                   
} CTRLITEM, *LPCTRLITEM;

CTRLITEM CtrItemType_0046[] = {
	{ "regi_common_type001_spinbutton1", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton2", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton3", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton4", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton5", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton6", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton11", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton12", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton13", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton14", 0, -5, 5 },	
	{ NULL, 0, 0, 0 },	
};

CTRLITEM CtrItemType_0047[] = {
	{ "regi_common_type001_spinbutton1", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton2", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton3", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton4", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton5", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton6", 0, -5, 5 },	
	{ NULL, 0, 0, 0 },	
};

CTRLITEM CtrItemType_0048[] = {
	{ "regi_common_type001_spinbutton1", 0, -4, 4 },	
	{ "regi_common_type001_spinbutton11", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton12", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton13", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton14", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton21", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton22", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton23", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton24", 0, -2, 2 },	
	{ NULL, 0, 0, 0 },	
};

CTRLITEM CtrItemType_0049[] = {
	{ "regi_common_type001_spinbutton1", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton2", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton3", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton4", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton5", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton11", 0, -3, 3 },	
	{ "regi_common_type001_spinbutton21", 0, -3, 3 },	
	{ NULL, 0, 0, 0 },	
};

CTRLITEM CtrItemType_0039[] = {
	{ "regi_common_type001_spinbutton1", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton2", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton3", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton4", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton5", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton11", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton12", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton13", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton14", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton15", 0, -5, 5 },	
	{ NULL, 0, 0, 0 },	
};

CTRLITEM CtrItemType_0040[] = {
	{ "regi_common_type001_spinbutton1", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton2", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton3", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton4", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton5", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton11", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton12", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton13", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton14", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton15", 0, -2, 2 },	
	{ NULL, 0, 0, 0 },	
};

/* Ver.3.50 */
CTRLITEM CtrItemType_0051[] = {
	{ "regi_common_type001_spinbutton1", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton2", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton3", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton4", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton5", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton11", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton12", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton13", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton14", 0, -5, 5 },	
	{ NULL, 0, 0, 0 },	
};

/* Ver.3.50 */
CTRLITEM CtrItemType_0052[] = {
	{ "regi_common_type001_spinbutton1", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton2", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton3", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton4", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton5", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton11", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton12", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton13", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton14", 0, -2, 2 },	
	{ NULL, 0, 0, 0 },	
};

/* Ver.3.60 */
CTRLITEM CtrItemType_0053[] = {
	{ "regi_common_type001_spinbutton1", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton2", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton3", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton4", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton5", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton6", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton11", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton12", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton13", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton14", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton15", 0, -5, 5 },	
	{ NULL, 0, 0, 0 },	
};

/* Ver.3.60 */
CTRLITEM CtrItemType_0054[] = {
	{ "regi_common_type001_spinbutton1", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton2", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton3", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton4", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton5", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton6", 0, -5, 5 },	
	{ NULL, 0, 0, 0 },	
};

/* Ver.3.60 */
CTRLITEM CtrItemType_0055[] = {
	{ "regi_common_type001_spinbutton1", 0, -4, 4 },	
	{ "regi_common_type001_spinbutton11", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton12", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton13", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton14", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton21", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton22", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton23", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton24", 0, -2, 2 },	
	{ NULL, 0, 0, 0 },	
};

/* Ver.3.70 */
CTRLITEM CtrItemType_0030[] = {
	{ "regi_common_type001_spinbutton1", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton2", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton3", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton4", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton5", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton6", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton7", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton11", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton12", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton13", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton14", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton15", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton16", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton17", 0, -5, 5 },	
	{ NULL, 0, 0, 0 },	
};

/* Ver.3.70 */
CTRLITEM CtrItemType_0031[] = {
	{ "regi_common_type001_spinbutton1", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton2", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton3", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton4", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton5", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton6", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton11", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton12", 0, -2, 2 },	
	{ NULL, 0, 0, 0 },	
};

/* Ver.3.70 */
CTRLITEM CtrItemType_0032[] = {
	{ "regi_common_type001_spinbutton1", 0, -3, 3 },	
	{ "regi_common_type001_spinbutton2", 0, -3, 3 },	
	{ NULL, 0, 0, 0 },	
};

/* Ver.3.80 */
CTRLITEM CtrItemType_0060[] = {
	{ "regi_common_type001_spinbutton1", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton2", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton3", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton4", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton5", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton6", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton11", 0, -3, 3 },	
	{ "regi_common_type001_spinbutton21", 0, -3, 3 },	
	{ NULL, 0, 0, 0 },	
};

/* Ver.3.80 */
CTRLITEM CtrItemType_0061[] = {
	{ "regi_common_type001_spinbutton1", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton2", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton3", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton4", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton11", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton12", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton13", 0, -5, 5 },	
	{ "regi_common_type001_spinbutton14", 0, -5, 5 },	
	{ NULL, 0, 0, 0 },	
};

/* Ver.3.80 */
CTRLITEM CtrItemType_0062[] = {
	{ "regi_common_type001_spinbutton1", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton2", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton3", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton4", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton11", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton12", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton13", 0, -2, 2 },	
	{ "regi_common_type001_spinbutton14", 0, -2, 2 },	
	{ NULL, 0, 0, 0 },	
};



/* parameter for BJL */
COMMANDDATA BJLTblType_0046[] = {
	{ 2, "1A" },
	{ 2, "1B" },
	{ 2, "1C" },
	{ 2, "1D" },
	{ 2, "1E" },
	{ 2, "1F" },
	{ 2, "1G" },
	{ 2, "1H" },
	{ 2, "1I" },
	{ 2, "1J" },
	{ 0, NULL }
};

COMMANDDATA BJLTblType_0047[] = {
	{ 2, "2K" },
	{ 2, "2L" },
	{ 2, "2M" },
	{ 2, "2N" },
	{ 2, "2O" },
	{ 2, "2P" },
	{ 0, NULL }
};

COMMANDDATA BJLTblType_0048[] = {
	{ 2, "3Q" },
	{ 2, "3R" },
	{ 2, "3S" },
	{ 2, "3T" },
	{ 2, "3U" },
	{ 2, "3V" },
	{ 2, "3W" },
	{ 2, "3X" },
	{ 2, "3Y" },
	{ 0, NULL }
};

COMMANDDATA BJLTblType_0049[] = {
	{ 2, "1A" },
	{ 2, "1B" },
	{ 2, "1C" },
	{ 2, "1D" },
	{ 2, "1E" },
	{ 2, "1F" },
	{ 2, "1G" },
	{ 0, NULL }
};

COMMANDDATA BJLTblType_0039[] = {
	{ 2, "2H" },
	{ 2, "2I" },
	{ 2, "2J" },
	{ 2, "2K" },
	{ 2, "2L" },
	{ 2, "2M" },
	{ 2, "2N" },
	{ 2, "2O" },
	{ 2, "2P" },
	{ 2, "2Q" },
	{ 0, NULL }
};

COMMANDDATA BJLTblType_0040[] = {
	{ 2, "3a" },
	{ 2, "3b" },
	{ 2, "3c" },
	{ 2, "3d" },
	{ 2, "3e" },
	{ 2, "3f" },
	{ 2, "3g" },
	{ 2, "3h" },
	{ 2, "3i" },
	{ 2, "3j" },
	{ 0, NULL }
};

/* Ver.3.50 */
COMMANDDATA BJLTblType_0051[] = {
	{ 2, "2H" },
	{ 2, "2I" },
	{ 2, "2J" },
	{ 2, "2K" },
	{ 2, "2L" },
	{ 2, "2M" },
	{ 2, "2N" },
	{ 2, "2O" },
	{ 2, "2P" },
	{ 0, NULL }
};

/* Ver.3.50 */
COMMANDDATA BJLTblType_0052[] = {
	{ 2, "3a" },
	{ 2, "3b" },
	{ 2, "3c" },
	{ 2, "3d" },
	{ 2, "3e" },
	{ 2, "3f" },
	{ 2, "3g" },
	{ 2, "3h" },
	{ 2, "3i" },
	{ 0, NULL }
};

/* Ver.3.60 */
COMMANDDATA BJLTblType_0053[] = {
	{ 2, "1A" },
	{ 2, "1B" },
	{ 2, "1C" },
	{ 2, "1D" },
	{ 2, "1E" },
	{ 2, "1F" },
	{ 2, "1G" },
	{ 2, "1H" },
	{ 2, "1I" },
	{ 2, "1J" },
	{ 2, "1K" },
	{ 0, NULL,}
};

/* Ver.3.60 */
COMMANDDATA BJLTblType_0054[] = {
	{ 2, "2L" },
	{ 2, "2M" },
	{ 2, "2N" },
	{ 2, "2O" },
	{ 2, "2P" },
	{ 2, "2Q" },
	{ 0, NULL }
};

/* Ver.3.60 */
COMMANDDATA BJLTblType_0055[] = {
	{ 2, "3R" },
	{ 2, "3S" },
	{ 2, "3T" },
	{ 2, "3U" },
	{ 2, "3V" },
	{ 2, "3W" },
	{ 2, "3X" },
	{ 2, "3Y" },
	{ 2, "3Z" },
	{ 0, NULL }
};

/* Ver.3.70 */
COMMANDDATA BJLTblType_0030[] = {
	{ 2, "1A" },
	{ 2, "1B" },
	{ 2, "1C" },
	{ 2, "1D" },
	{ 2, "1E" },
	{ 2, "1F" },
	{ 2, "1G" },
	{ 2, "1H" },
	{ 2, "1I" },
	{ 2, "1J" },
	{ 2, "1K" },
	{ 2, "1L" },
	{ 2, "1M" },
	{ 2, "1N" },
	{ 0, NULL }
};

/* Ver.3.70 */
COMMANDDATA BJLTblType_0031[] = {
	{ 2, "2O" },
	{ 2, "2P" },
	{ 2, "2Q" },
	{ 2, "2R" },
	{ 2, "2S" },
	{ 2, "2T" },
	{ 2, "2U" },
	{ 2, "2V" },
	{ 0, NULL }
};

/* Ver.3.70 */
COMMANDDATA BJLTblType_0032[] = {
	{ 2, "3W" },
	{ 2, "3X" },
	{ 0, NULL }
};

/* Ver.3.80 */
COMMANDDATA BJLTblType_0060[] = {
	{ 2, "1A" },
	{ 2, "1B" },
	{ 2, "1C" },
	{ 2, "1D" },
	{ 2, "1E" },
	{ 2, "1F" },
	{ 2, "1G" },
	{ 2, "1H" },
	{ 0, NULL }
};

/* Ver.3.80 */
COMMANDDATA BJLTblType_0061[] = {
	{ 2, "2I" },
	{ 2, "2J" },
	{ 2, "2K" },
	{ 2, "2L" },
	{ 2, "2M" },
	{ 2, "2N" },
	{ 2, "2O" },
	{ 2, "2P" },
	{ 0, NULL }
};

/* Ver.3.80 */
COMMANDDATA BJLTblType_0062[] = {
	{ 2, "3a" },
	{ 2, "3b" },
	{ 2, "3c" },
	{ 2, "3d" },
	{ 2, "3e" },
	{ 2, "3f" },
	{ 2, "3g" },
	{ 2, "3h" },
	{ 0, NULL }
};


/* parameter for drawing area */
typedef struct {
	short	x;						
	short	y;                      
	short	width;                  
	short	len;                    
	short	step;                   
	short	stepdir;                
	short	linedir;                
	short	repeat;                 
                                    
	short	selbox_dx;              
	short	selbox_dy;              
	short	selbox_width;           
	short	selbox_height;          
                                    
	short	red;                    
	short	green;                  
	short	blue;                   

	short	ornament;               // 0:none 1:one 2:two
	short	isOddHeight;
} BOXINF, *LPBOXINF;

BOXINF BoxInfoType_0046[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 18,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0x8000, 0x8000, 0, 1 },
	{ 32,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0x8000, 0x8000, 0, 1 },
	{ 46,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 60,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0x8000, 0x8000, 0, 1 },
	{ 74,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0x0000, 0x0000, 0, 1 },
	{ 88,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0x0000, 0x0000, 0, 1 },
	{ 32, 84,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 46, 84,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0xffff, 0xffff, 0, 1 },
	{ 60, 84,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x8000, 0xffff, 0, 1 },
	{ 74, 84,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x0000, 0xffff, 0, 1 },
};

BOXINF BoxInfoType_0047[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 18,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 32,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 46,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0xffff, 0xffff, 0, 1 },
	{ 60,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x8000, 0xffff, 0, 1 },
	{ 74,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x0000, 0xffff, 0, 1 },
	{ 88,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x0000, 0xffff, 0, 1 },
};

BOXINF BoxInfoType_0048[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 46, 21,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 32, 81,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 46, 81,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0xffff, 0xffff, 0, 1 },
	{ 60, 81,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x8000, 0xffff, 0, 1 },
	{ 74, 81,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x0000, 0xffff, 0, 1 },
	{ 32, 116,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 46, 116,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0xffff, 0xffff, 0, 1 },
	{ 60, 116,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x8000, 0xffff, 0, 1 },
	{ 74, 116,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x0000, 0xffff, 0, 1 },
};

BOXINF BoxInfoType_0049[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 34,  22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0xffff, 0xffff, 0, 0 },
	{ 48,  22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 62,  22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0, 0 },
	{ 76,  22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0, 0 },
	{ 90,  22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0, 0 },
	{ 44, 94,  16,  2,  7, 1,  1,   0,       -2,       -4,       19,          8, 0x8000, 0x8000, 0x8000, 1, 0 },
	{ 44, 148, 16,  2,  7, 1,  1,   0,       -2,       -4,       19,          8, 0x8000, 0x8000, 0x8000, 1, 0 },
};

BOXINF BoxInfoType_0039[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 81, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 25, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 81, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
};

BOXINF BoxInfoType_0040[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 81, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 25, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 81, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
};

/* Ver.3.50 */
BOXINF BoxInfoType_0051[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 81, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 25, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
};

/* Ver.3.50 */
BOXINF BoxInfoType_0052[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 81, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 25, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
};

/* Ver.3.60 */
BOXINF BoxInfoType_0053[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 18,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0x8000, 0x8000, 0, 1 },
	{ 32,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0x8000, 0x8000, 0, 1 },
	{ 46,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0x8000, 0x8000, 0, 1 },
	{ 60,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0x8000, 0x8000, 0, 1 },
	{ 74,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 88,  16,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0x0000, 0x0000, 0, 1 },
	{ 32, 84,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 46, 84,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0xffff, 0xffff, 0, 1 },
	{ 60, 84,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x8000, 0xffff, 0, 1 },
	{ 74, 84,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x0000, 0xffff, 0, 1 },
	{ 88, 84,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0x8000, 0x8000, 0, 1 },
};

/* Ver.3.60 */
BOXINF BoxInfoType_0054[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 18,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 32,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 46,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0xffff, 0xffff, 0, 1 },
	{ 60,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x8000, 0xffff, 0, 1 },
	{ 74,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x0000, 0xffff, 0, 1 },
	{ 88,  46,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x0000, 0xffff, 0, 1 },
};

/* Ver.3.60 */
BOXINF BoxInfoType_0055[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 46, 21,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 32, 81,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 46, 81,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0xffff, 0xffff, 0, 1 },
	{ 60, 81,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x8000, 0xffff, 0, 1 },
	{ 74, 81,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x0000, 0xffff, 0, 1 },
	{ 32, 116,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x0000, 0xffff, 0xffff, 0, 1 },
	{ 46, 116,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0x8000, 0xffff, 0xffff, 0, 1 },
	{ 60, 116,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x8000, 0xffff, 0, 1 },
	{ 74, 116,  9,  2,  5, 1,  1,   0,       -2,       -4,       12,          6, 0xffff, 0x0000, 0xffff, 0, 1 },
};

/* Ver.3.70 */
BOXINF BoxInfoType_0030[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 15,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0, 0 },
	{ 29,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0, 0 },
	{ 43,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 57,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 71,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0, 0 },
	{ 85,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0, 0 },
	{ 99,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0, 0 },
	{ 15,  93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0, 0 },
	{ 29,  93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0, 0 },
	{ 43,  93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 57,  93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 71,  93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0, 0 },
	{ 85,  93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0, 0 },
	{ 99,  93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0, 0 },
};

/* Ver.3.70 */
BOXINF BoxInfoType_0031[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0, 0 },	
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0, 0 },	
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0, 0 },	
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0, 0 },	
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0, 0 },	
	{ 95,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0, 0 },	
	{ 53,  51, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0, 0 },	
	{ 67,  51, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0, 0 },	
};

/* Ver.3.70 */
BOXINF BoxInfoType_0032[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 41,  16,  16,  2,  13, 1,  1,   0,       -2,       -4,       19,          8, 0x8000, 0x8000, 0x8000, 1, 0 },
	{ 72,  16,  16,  4,  13, 1,  1,   0,       -2,       -6,       19,          12, 0x8000, 0x8000, 0x8000, 1, 0 },
};

/* Ver.3.80 */
BOXINF BoxInfoType_0060[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25,  22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0xffff, 0xffff, 0, 0 },
	{ 39,  22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53,  22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0, 0 },
	{ 67,  22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0, 0 },
	{ 81,  22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0, 0 },
	{ 95,  22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0, 0 },
	{ 44, 94,  16,  2,  7, 1,  1,   0,       -2,       -4,       19,          8, 0x8000, 0x8000, 0x8000, 1, 0 },
	{ 44, 148, 16,  2,  7, 1,  1,   0,       -2,       -4,       19,          8, 0x8000, 0x8000, 0x8000, 1, 0 },
};

/* Ver.3.80 */
BOXINF BoxInfoType_0061[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 25, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 95,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
};

/* Ver.3.80 */
BOXINF BoxInfoType_0062[] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 22,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 25, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 39, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 53, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
	{ 67, 57,  9,  2,  6, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0, 0 },
};




/* dialog prameter num */

/* type define */
#define	PICTURE_WIDTH		100		
#define	PICTURE_HEIGHT		144		

#define	PICTURE_WIDTH_BIG2	118		
#define	PICTURE_HEIGHT_BIG2	170     

#define PICTURE_WIDTH_BIG3	128
#define PICTURE_HEIGHT_BIG3	180

#define PICTURE_WIDTH_BIG4	146
#define PICTURE_HEIGHT_BIG4	205

#define	PORT			0x0000		
#define	LAND			0x0001		
#define	NO_DISPLAY		0x0002		
#define	ORNAMENT_S600	0x0100		
#define	ORNAMENT_REG	0x0200		// Ornament of each box
#define	BANDREGI_TYPE	0x1000		
#define	BIGAREA_TYPE2	0x2000		
#define BIGAREA_TYPE3	0x4000
#define BIGAREA_TYPE4	0x8000


/* hot spot */
typedef struct {
	short	drawx;                  
	short	drawy;                  
	short	width;                  
	short	len;                    
	short	step;                   
	short	stepdir;                
	short	linedir;                
	short	repeat;                 
	short	cnt;                    
    short	selbox_x;               
	short	selbox_y;               
	short	selbox_width;           
	short	selbox_height;          
	short	red;                    
	short	green;                  
	short	blue;                   
} HOTSPOT, *LPHOTSPOT; 

#define REGI_EDITMAX	30
#define REIG_BUF_MAX_SIZE	64



/* Each Type Function Resource */
enum {
	RES_REGI_COMPTYPE001=1,
	RES_REGI_COMPTYPE002,
};

/* REGI COMPTYPE001 */
typedef struct {
	long			resType;
	short			isPermitCancel;
	char			*DrawingName;	
	LPCTRLITEM		lpCtrlItem;		
	COMMANDDATA		*lpCmdData;		
	LPBOXINF		lpBoxInf;		
	short			cnt;			
	u_short			type;			
	GtkWidget *(*ptrCreateDialog )( void );
} REGICOMPTYPE001RES, *LPREGICOMPTYPE001RES;


REGICOMPTYPE001RES	regiType001Res[] = {
	{ RES_REGI_COMPTYPE001, 1, "regi_common_type001_drawingarea1", CtrItemType_0046, BJLTblType_0046, BoxInfoType_0046, 10, 
		PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG, create_regi_common_type001_dialog },
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0047, BJLTblType_0047, BoxInfoType_0047, 6, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog },
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0048, BJLTblType_0048, BoxInfoType_0048, 9, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog },
	{ RES_REGI_COMPTYPE001, 1, "regi_common_type001_drawingarea1", CtrItemType_0049, BJLTblType_0049, BoxInfoType_0049, 7, 
		PORT|BIGAREA_TYPE4|BANDREGI_TYPE|ORNAMENT_REG, create_regi_common_type001_dialog },
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0039, BJLTblType_0039, BoxInfoType_0039, 10, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog },
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0040, BJLTblType_0040, BoxInfoType_0040, 10, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog },
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0051, BJLTblType_0051, BoxInfoType_0051, 9, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog }, /* Ver.3.50 */
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0052, BJLTblType_0052, BoxInfoType_0052, 9, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog }, /* Ver.3.50 */
	{ RES_REGI_COMPTYPE001, 1, "regi_common_type001_drawingarea1", CtrItemType_0053, BJLTblType_0053, BoxInfoType_0053, 11, 
		PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG, create_regi_common_type001_dialog }, /* Ver.3.60 */
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0054, BJLTblType_0054, BoxInfoType_0054, 6, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog }, /* Ver.3.60 */
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0055, BJLTblType_0055, BoxInfoType_0055, 9, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog }, /* Ver.3.60 */
	{ RES_REGI_COMPTYPE001, 1, "regi_common_type001_drawingarea1", CtrItemType_0030, BJLTblType_0030, BoxInfoType_0030, 14, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog }, /* Ver.3.70 */
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0031, BJLTblType_0031, BoxInfoType_0031, 8, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog }, /* Ver.3.70 */
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0032, BJLTblType_0032, BoxInfoType_0032, 2, 
		PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG, create_regi_common_type001_dialog }, /* Ver.3.70 */
	{ RES_REGI_COMPTYPE001, 1, "regi_common_type001_drawingarea1", CtrItemType_0060, BJLTblType_0060, BoxInfoType_0060, 8, 
		PORT|BIGAREA_TYPE4|BANDREGI_TYPE|ORNAMENT_REG, create_regi_common_type001_dialog }, /* Ver.3.80 */
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0061, BJLTblType_0061, BoxInfoType_0061, 8, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog }, /* Ver.3.80 */
	{ RES_REGI_COMPTYPE001, 0, "regi_common_type001_drawingarea1", CtrItemType_0062, BJLTblType_0062, BoxInfoType_0062, 8, 
		PORT|BIGAREA_TYPE3, create_regi_common_type001_dialog }, /* Ver.3.80 */
};

/* UI type */
enum {
	UI_REGI_START_TYPE001 = 1,
	UI_REGI_START_TYPE002,
	UI_REGI_START_TYPE003,
	UI_AUTOREGI_START_TYPE001,
	UI_AUTOREGI_START_TYPE002,
	UI_AUTOREGI_START_TYPE003,
	UI_AUTOREGI_START_TYPE004, /* Ver.3.80 */
	UI_BINSELECT_TYPE001,
	UI_BINSELECT_TYPE002,
};


/* REGI COMPTYPE002 */
typedef struct {
	long			resType;
	long	uiType;
	GtkWidget 		*(*ptrCreateDialog )( void );
} REGICOMPTYPE002RES, *LPREGICOMPTYPE002RES;

REGICOMPTYPE002RES	regiType002Res[] = {
	{ RES_REGI_COMPTYPE002, UI_REGI_START_TYPE001, create_regi_common_type002_dialog }, /* LUI_UTD_14M_0045 */
	{ RES_REGI_COMPTYPE002, UI_REGI_START_TYPE002, create_regi_common_type002_dialog }, /* LUI_UTD_14M_0033 */
	{ RES_REGI_COMPTYPE002, UI_AUTOREGI_START_TYPE001, create_regi_common_type002_dialog }, /* LUI_UTD_14A_0007 */
	{ RES_REGI_COMPTYPE002, UI_AUTOREGI_START_TYPE001, create_regi_common_type002_dialog }, /* LUI_UTD_14A_0008 */
	{ RES_REGI_COMPTYPE002, UI_BINSELECT_TYPE001, create_regi_common_type002_dialog }, /* LUI_UTD_14A_0005 */
	{ RES_REGI_COMPTYPE002, UI_REGI_START_TYPE003, create_regi_common_type002_dialog }, /* LUI_UTD_14M_0058 */
	{ RES_REGI_COMPTYPE002, UI_AUTOREGI_START_TYPE002, create_regi_common_type002_dialog }, /* LUI_UTD_14M_0014 */
	{ RES_REGI_COMPTYPE002, UI_AUTOREGI_START_TYPE003, create_regi_common_type002_dialog }, /* LUI_UTD_14M_0015 */
	{ RES_REGI_COMPTYPE002, UI_BINSELECT_TYPE002, create_regi_common_type002_dialog }, /* LUI_UTD_14M_0016 */
	{ RES_REGI_COMPTYPE002, UI_AUTOREGI_START_TYPE004, create_regi_common_type002_dialog }, /* LUI_UTD_14M_0017 */
};


/* Each Type Function Work */
enum {
	WORK_REGI_COMPTYPE001=1,
	WORK_REGI_COMPTYPE002,
};

typedef struct {
	short		mediaSupplyType;	
} REGIGLOBAL, *LPREGIGLOBAL;

typedef struct {
	long		workType;
	HOTSPOT		HotSpot[REGI_EDITMAX];
	LPCTRLITEM	lpCtrlItem;
	LPBOXINF	lpBoxInf;
	GtkWidget	*regi_dialog;
	GtkWidget	*draw_area;
	GdkPixmap	*regi_pixmap;
	COMMANDDATA	*lpCmdData;
	u_short		type;
	short		frameWidth;
	short		frameHeight;
	short		itemValue[REGI_EDITMAX];
	short		itemNum;
	short		isPermitCancel;
	short 		status;
} REGICOMPTYPE001WORK, *LPREGICOMPTYPE001WORK;

typedef struct {
	long	workType;
	long	uiType;
	GtkWidget	*regi_dialog;
	short	defMediaSupply;
	short 		status;
} REGICOMPTYPE002WORK, *LPREGICOMPTYPE002WORK;

#define TYPE001_N_STEP 17


#define REGI_TYPE002_BINVALUE_MAX	2
#define REGI_TYPE002_BINVALUE_REARTRAY	0
#define REGI_TYPE002_BINVALUE_CASETTE	1
#define REGI_TYPE002_BINVALUE_CASETTE_AUTO	8
#define REGI_TYPE002_BINVALUE_NA			128
static const gchar* regi_common_type002_radiobutton_name[] = {
	"regi_common_type002_radiobutton1",
	"regi_common_type002_radiobutton2",
	NULL
};


/* global  */
static void * gLPRegiWork = NULL;
static int gBinValueRegi;
static int gItemNum;
static COMMANDDATA *gLPItem;
static int gItemValue[REGI_EDITMAX];

/* function prototypes */
static gboolean isGetPrinterSupplyInfo( int type );


/*** Output *************************************************************************************************/
static short OutputUtilityCommand_CMD_REGI( short type, short index, COMMANDDATA *cmdData, short cmdNum )
{
	char buf[CMD_BUF_MAX_SIZE * 3];
	char *p;
	long size;
	long i, value;
	short isSetTime;
	short result = -1;

	if ( cmdData == NULL ) goto Err;
	if ( index > (cmdNum -1 ) ) goto Err;

	p = buf;
	size = 0;
	isSetTime = 1;
	if ( type == CMD_REGI_TYPE001 ){
		for ( i=0; i<gItemNum; i++ ){
			value = gItemValue[i];
			size = snprintf( p, CMD_BUF_MAX_SIZE, cmdData[index].cmd, gLPItem[i].cmd, value<0? '-':'+', abs(value));p += size;
		}

		*p = 0x00; p++;
		size = (long)(p -buf);
		OutputCmdType002( buf, size, isSetTime );
	}
	else if ( type == CMD_REGI_TYPE002 ){
		int currentIndex;
		if ( gBinValueRegi == REGI_TYPE002_BINVALUE_CASETTE ){
			currentIndex = index + 5;
		}
		else {
			currentIndex = index;
		}
		size = cmdData[currentIndex].len;
		memcpy( p, cmdData[currentIndex].cmd, size ); p += size;

		*p = 0x00; p++;
		size = (long)(p -buf);
		OutputCmdType001( buf, size );
	}

	result = 0;
Err:
	return result;
}

short OutputUtilityCommand_CMD_REGI_TYPE001( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_REGI( CMD_REGI_TYPE001, index, cmdData, cmdNum );
}

short OutputUtilityCommand_CMD_REGI_TYPE002( short index, COMMANDDATA *cmdData, short cmdNum )
{
	return OutputUtilityCommand_CMD_REGI( CMD_REGI_TYPE002, index, cmdData, cmdNum );
}

/*** COMPTYPE001 *********************************************************************************************/
void SetPenColor(GdkGC *gc, int red, int green, int blue)
{
  GdkColor  color;

  color.red   = red;
  color.green = green;
  color.blue  = blue;

  gdk_color_alloc(gdk_colormap_get_system(),&color);	
  gdk_gc_set_foreground(gc, &color);					
}

static short DrawTestPrintPageType001( LPREGICOMPTYPE001WORK lpWork, short currentPos )
{
	GdkGC	*gc;
	GdkPoint aPoints[6];
	GdkRectangle	update_rect;    
	int width = 0, height = 0;
	short x, y;
	int i;
	short result = -1;

	if ( lpWork == NULL ) goto Err;

	gc = gdk_gc_new( lpWork->regi_dialog->window );

	gdk_window_get_size( lpWork->regi_pixmap, &width, &height );
	gdk_draw_rectangle( lpWork->regi_pixmap,
						lpWork->regi_dialog->style->bg_gc[GTK_STATE_NORMAL],
						TRUE, 0, 0, width, height);

	aPoints[0].x = 0;			
	aPoints[0].y = 0;
	aPoints[1].x = 0;
	aPoints[1].y = height -1;
	aPoints[2].x = width - TYPE001_N_STEP;
	aPoints[2].y = height -1;
	aPoints[3].x = width - TYPE001_N_STEP;
	aPoints[3].y = height - TYPE001_N_STEP;
	aPoints[4].x = width -1;
	aPoints[4].y = height - TYPE001_N_STEP;
	aPoints[5].x = width -1;
	aPoints[5].y = 0;
	SetPenColor(gc, 0xffff, 0xffff, 0xffff);	
	gdk_draw_polygon(lpWork->regi_pixmap, gc, TRUE, aPoints, 6);	
	SetPenColor(gc, 0, 0, 0);		
	gdk_draw_polygon(lpWork->regi_pixmap, gc, FALSE, aPoints, 6);	


	aPoints[0].x = width - TYPE001_N_STEP;
	aPoints[0].y = height -1;
	aPoints[1].x = width - TYPE001_N_STEP;
	aPoints[1].y = height - TYPE001_N_STEP;
	aPoints[2].x = width -1;
	aPoints[2].y = height - TYPE001_N_STEP;
	SetPenColor(gc, 0xc000, 0xc000, 0xc000);		
	gdk_draw_polygon(lpWork->regi_pixmap, gc, TRUE, aPoints, 3);	
	SetPenColor(gc, 0, 0, 0);				
	gdk_draw_polygon(lpWork->regi_pixmap, gc, FALSE, aPoints, 3);	


	SetPenColor(gc, 0x8000, 0x8000, 0x8000);		
	gdk_draw_line(lpWork->regi_pixmap, gc, 0, 0, 0, height -1);
	gdk_draw_line(lpWork->regi_pixmap, gc, 0, 0, width -1, 0);
	gdk_draw_line(lpWork->regi_pixmap, gc, width - TYPE001_N_STEP, height-1, width-1, height - TYPE001_N_STEP);

	
	for ( i=0; i<lpWork->itemNum; i++ ){
		short	nOffsetX, nOffsetY, nStepX, nStepY, j;
		short	dx, dy;
		short	box_width, box_height;
		short	rep;
		
		if (lpWork->HotSpot[i].linedir) {	
			nOffsetX = 0;				
			nOffsetY = lpWork->HotSpot[i].len;	
			dx = lpWork->HotSpot[i].width;		
			dy = 0;
		} else {		
			nOffsetX = lpWork->HotSpot[i].len;	
			nOffsetY = 0;				
			dx = 0;
			dy = lpWork->HotSpot[i].width;		
		}
		
		if (lpWork->HotSpot[i].stepdir) {	
			nStepX = 0;					
			nStepY = lpWork->HotSpot[i].step;	
		} else {					
			nStepX = lpWork->HotSpot[i].step;	
			nStepY = 0;					
		}
		
		if (lpWork->HotSpot[i].repeat) {	
			if (i == currentPos)
				SetPenColor(gc,
					lpWork->HotSpot[i].red, lpWork->HotSpot[i].green, lpWork->HotSpot[i].blue);
			else
				SetPenColor(gc, 0xc000, 0xc000, 0xc000);
				
			for (rep=0; rep < lpWork->HotSpot[i].repeat; rep++) {
				x = lpWork->HotSpot[i].drawx + dx * rep;
				y = lpWork->HotSpot[i].drawy + dy * rep;
				for (j=0; j < lpWork->HotSpot[i].cnt; j++, x+=nStepX, y+=nStepY) {
					gdk_draw_line(lpWork->regi_pixmap, gc,
						x-nOffsetX, y-nOffsetY, x+nOffsetX, y+nOffsetY);
				}
			}
		} else if (lpWork->type & ORNAMENT_S600) {	
		 	x = lpWork->HotSpot[i].drawx;		
		 	y = lpWork->HotSpot[i].drawy;
		 	box_width = lpWork->HotSpot[i].width;
		 	box_height =  lpWork->HotSpot[i].len*2 + (i+1);
		 	for (j=0; j<lpWork->HotSpot[i].cnt; j++, x+=nStepX, y+=nStepY) {	
		 		int		startx, starty;
				if (i == currentPos)		
				 	SetPenColor(gc,
						lpWork->HotSpot[i].red, lpWork->HotSpot[i].green, lpWork->HotSpot[i].blue);	
		 		else		
					SetPenColor(gc, 0xc000, 0xc000, 0xc000);	
		 		startx = x - nOffsetX;	
		 		starty = y - nOffsetY; 
		 		gdk_draw_rectangle(lpWork->regi_pixmap, gc, TRUE, startx, starty,	
		 								box_width, box_height);
		 		
				if (i == currentPos)		
				 	SetPenColor(gc, 0, 0, 0);				
			 	else		
		 			SetPenColor(gc, 0xc000, 0xc000, 0xc000);	

		 		if (i == 0) {		
		 			int		linex, liney;
		 			linex = startx + box_width + 3;
		 			liney = starty + box_height/2;
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+5, liney);
		 			
		 			linex = startx;
		 			gdk_draw_line (lpWork->regi_pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 		} else {	
		 			int		linex, liney;
		 			linex = startx + box_width + 3;
		 			liney = starty + box_height/3;
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+5, liney);
		 			linex = startx;
		 			gdk_draw_line (lpWork->regi_pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 			
		 			linex = startx + box_width + 3;
		 			liney += box_height/3 + 1;
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+5, liney);
		 			linex = startx;
		 			gdk_draw_line (lpWork->regi_pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 		}
			}
			
		} else if ( (lpWork->type & ORNAMENT_REG) && (lpWork->lpBoxInf[i].ornament) ) {	
		 	x = lpWork->HotSpot[i].drawx;		
		 	y = lpWork->HotSpot[i].drawy;
		 	box_width = lpWork->HotSpot[i].width;
		 	box_height =  lpWork->HotSpot[i].len*2+1;
		 	for (j=0; j<lpWork->HotSpot[i].cnt; j++, x+=nStepX, y+=nStepY) {	
		 		int		startx, starty;
				if (i == currentPos)		
				 	SetPenColor(gc,
						lpWork->HotSpot[i].red, lpWork->HotSpot[i].green, lpWork->HotSpot[i].blue);	
		 		else		
					SetPenColor(gc, 0xc000, 0xc000, 0xc000);	
		 		startx = x - nOffsetX;	
		 		starty = y - nOffsetY; 
		 		gdk_draw_rectangle(lpWork->regi_pixmap, gc, TRUE, startx, starty,	
		 								box_width, box_height);
		 		
				if (i == currentPos)		
				 	SetPenColor(gc, 0, 0, 0);				
			 	else		
		 			SetPenColor(gc, 0xc000, 0xc000, 0xc000);	

		 		if (lpWork->lpBoxInf[i].ornament == 1) {		
		 			int		linex, liney;
		 			linex = startx + box_width + 3;
		 			liney = starty + box_height/2;
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+5, liney);
		 			
		 			linex = startx;
		 			gdk_draw_line (lpWork->regi_pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 		} else if(lpWork->lpBoxInf[i].ornament == 2) {	
		 			int		linex, liney;
		 			linex = startx + box_width + 3;
		 			liney = starty + box_height/3;
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+5, liney);
		 			linex = startx;
		 			gdk_draw_line (lpWork->regi_pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 			
		 			linex = startx + box_width + 3;
		 			liney += box_height/3 + 1;
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney-2);		
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+2, liney+2);
		 			gdk_draw_line (lpWork->regi_pixmap, gc, linex, liney, linex+5, liney);
		 			linex = startx;
		 			gdk_draw_line (lpWork->regi_pixmap, gc,
						linex, liney, linex+box_width-1, liney);	
		 		}
			}
			
		} else {
			if (i == currentPos)		
			 	SetPenColor(gc,
					lpWork->HotSpot[i].red, lpWork->HotSpot[i].green, lpWork->HotSpot[i].blue);	
		 	else		
		 		SetPenColor(gc, 0xc000, 0xc000, 0xc000);	
		 	
		 	x = lpWork->HotSpot[i].drawx;		
		 	y = lpWork->HotSpot[i].drawy;
		 	box_width = lpWork->HotSpot[i].width;
			if ( lpWork->lpBoxInf[i].isOddHeight == 1 ){
				box_height = lpWork->HotSpot[i].len*2-1;
			}
			else {
				box_height = lpWork->HotSpot[i].len*2;
			}
		 	for (j=0; j<lpWork->HotSpot[i].cnt; j++, x+=nStepX, y+=nStepY) {	
		 		int		startx, starty;
		 		startx = x - nOffsetX;	
		 		starty = y - nOffsetY; 
		 		gdk_draw_rectangle(lpWork->regi_pixmap, gc, TRUE, startx, starty,	
		 								box_width, box_height);
		 	}
		}
	}
	
	for (i=0; i<lpWork->itemNum; i++) {		
		if (i == currentPos) 		
			SetPenColor(gc, 0xffff, 0x0000, 0x0000);	
		else 		
			SetPenColor(gc, 0xc000, 0xc000, 0xc000);	
		
		x = lpWork->HotSpot[i].selbox_x;
		y = lpWork->HotSpot[i].selbox_y;
		if (lpWork->HotSpot[i].stepdir) 	
			y += lpWork->HotSpot[i].step*(lpWork->lpCtrlItem[i].nMax - lpWork->itemValue[i]);
		else			
			x += lpWork->HotSpot[i].step*(lpWork->lpCtrlItem[i].nMax + lpWork->itemValue[i]);
		
		gdk_gc_set_line_attributes(	gc, 1, GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_MITER );
		gdk_draw_rectangle(lpWork->regi_pixmap, gc, FALSE, x, y,	 		
							lpWork->HotSpot[i].selbox_width, lpWork->HotSpot[i].selbox_height);
	}

	gdk_window_get_size(lpWork->draw_area->window, &width, &height);
	update_rect.x      = 0;			
	update_rect.y      = 0;
	update_rect.width  = width;
	update_rect.height = height;
	gtk_widget_draw(lpWork->draw_area, &update_rect);		


	gdk_gc_destroy(gc);			

	result = 0;
Err:
	return result;	
}





static LPREGICOMPTYPE001WORK CreateWorkRegiType001( LPREGICOMPTYPE001RES lpRegiRes )
{
	LPREGICOMPTYPE001WORK lpWork = NULL;
	short i;

	if( lpRegiRes == NULL ) goto Err;
	if ( (lpWork = g_malloc0(sizeof(REGICOMPTYPE001WORK))) == NULL ) goto Err;

	for ( i=0; i<REGI_EDITMAX; i++ ){
		lpWork->itemValue[i] = 0;
	}

	lpWork->workType = WORK_REGI_COMPTYPE001;
Err:
	return lpWork;
}

static void DisposeWorkRegiType001( LPREGICOMPTYPE001WORK lpWork )
{
	if ( lpWork == NULL ) goto EXIT;

	gdk_pixmap_unref( lpWork->regi_pixmap );

	g_free( lpWork );
EXIT:
	return;
}

static void SetLabelRegiType001( LPREGICOMPTYPE001RES lpRegiRes, void *lpGWork, char *dialogName )
{
	LPREGICOMPTYPE001WORK lpWork = (LPREGICOMPTYPE001WORK)lpGWork;

	SetLabelUtilDialog( lpWork->regi_dialog, dialogName );

}


static void SetSpinButtonRegiType001( LPREGICOMPTYPE001RES lpRegiRes, void *lpGWork )
{
	LPREGICOMPTYPE001WORK lpWork = (LPREGICOMPTYPE001WORK)lpGWork;
	LPCTRLITEM	pCurrentCtrlItem = lpRegiRes->lpCtrlItem;

	while( pCurrentCtrlItem->CtrlName != NULL ){
			GtkAdjustment *pAdjustment;
			pAdjustment = gtk_spin_button_get_adjustment((GtkSpinButton *)LookupWidget(lpWork->regi_dialog, pCurrentCtrlItem->CtrlName));
			pAdjustment->value = pCurrentCtrlItem->nDefault;
			pAdjustment->lower = pCurrentCtrlItem->nMin;
			pAdjustment->upper = pCurrentCtrlItem->nMax;
			pAdjustment->step_increment = 1;
			pAdjustment->page_increment = 0;
			pAdjustment->page_size = 0;
			gtk_widget_show( LookupWidget(lpWork->regi_dialog, pCurrentCtrlItem->CtrlName) );
			pCurrentCtrlItem++;
	}
}

static void SetDefaultRegiType001( LPREGICOMPTYPE001RES lpRegiRes, void *lpGWork )
{
	LPREGICOMPTYPE001WORK lpWork = (LPREGICOMPTYPE001WORK)lpGWork;
	int i;

	for ( i=0; i<lpWork->itemNum; i++ ){
		gtk_spin_button_set_value(
			GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(lpWork->regi_dialog),
			lpWork->lpCtrlItem[i].CtrlName)),lpWork->itemValue[i]);
	}
}

static void InitParamRegiType001( LPREGICOMPTYPE001RES lpRegiRes, void *lpGWork )
{
	LPREGICOMPTYPE001WORK lpWork = (LPREGICOMPTYPE001WORK)lpGWork;
	short i;
	int frameWidth, frameHeight;

	/* create and realize dialog */
	lpWork->regi_dialog = lpRegiRes->ptrCreateDialog();
	lpWork->draw_area = LookupWidget( GTK_WIDGET(lpWork->regi_dialog), lpRegiRes->DrawingName );
	gtk_widget_realize( lpWork->regi_dialog );
	gtk_widget_realize( lpWork->draw_area );

	lpWork->isPermitCancel = lpRegiRes->isPermitCancel;

	lpWork->status = US_DEFAULT;
	lpWork->lpCtrlItem  = lpRegiRes->lpCtrlItem;
	lpWork->lpCmdData   = lpRegiRes->lpCmdData;
	lpWork->lpBoxInf   = lpRegiRes->lpBoxInf;
	lpWork->itemNum    = lpRegiRes->cnt;
	lpWork->type       = lpRegiRes->type;

	if (lpWork->type & BIGAREA_TYPE2) {
		frameWidth  = PICTURE_WIDTH_BIG2;
		frameHeight = PICTURE_HEIGHT_BIG2;
	} else if (lpWork->type & BIGAREA_TYPE3) {
		frameWidth  = PICTURE_WIDTH_BIG3;
		frameHeight = PICTURE_HEIGHT_BIG3;
	} else if (lpWork->type & BIGAREA_TYPE4) {
		frameWidth  = PICTURE_WIDTH_BIG4;
		frameHeight = PICTURE_HEIGHT_BIG4;
	} else {
		frameWidth  = PICTURE_WIDTH;
		frameHeight = PICTURE_HEIGHT;
	}

	for ( i=0; i<lpWork->itemNum; i++ ){

		lpWork->HotSpot[i].drawx   = lpRegiRes->lpBoxInf[i].x;	
		lpWork->HotSpot[i].drawy   = lpRegiRes->lpBoxInf[i].y;
		lpWork->HotSpot[i].width   = lpRegiRes->lpBoxInf[i].width;
		lpWork->HotSpot[i].len     = lpRegiRes->lpBoxInf[i].len;
		lpWork->HotSpot[i].step    = lpRegiRes->lpBoxInf[i].step;
		lpWork->HotSpot[i].stepdir = lpRegiRes->lpBoxInf[i].stepdir;
		lpWork->HotSpot[i].linedir = lpRegiRes->lpBoxInf[i].linedir;
		lpWork->HotSpot[i].repeat  = lpRegiRes->lpBoxInf[i].repeat;
		lpWork->HotSpot[i].cnt     = lpRegiRes->lpCtrlItem[i].nMax - lpRegiRes->lpCtrlItem[i].nMin + 1;	


		lpWork->HotSpot[i].selbox_x = lpWork->HotSpot[i].drawx + lpRegiRes->lpBoxInf[i].selbox_dx;
		lpWork->HotSpot[i].selbox_y = lpWork->HotSpot[i].drawy + lpRegiRes->lpBoxInf[i].selbox_dy;
		lpWork->HotSpot[i].selbox_width = lpRegiRes->lpBoxInf[i].selbox_width;		
		lpWork->HotSpot[i].selbox_height = lpRegiRes->lpBoxInf[i].selbox_height;

		lpWork->HotSpot[i].red = lpRegiRes->lpBoxInf[i].red;			
		lpWork->HotSpot[i].green = lpRegiRes->lpBoxInf[i].green;       
		lpWork->HotSpot[i].blue = lpRegiRes->lpBoxInf[i].blue;

	}

	lpWork->regi_pixmap = gdk_pixmap_new(lpWork->regi_dialog->window, frameWidth, frameHeight, -1);	

	lpWork->frameWidth =  frameWidth;
	lpWork->frameHeight = frameHeight;
}

static void ShowDialogRegiType001( LPREGICOMPTYPE001RES lpRegiRes, void *lpGWork )
{
	LPREGICOMPTYPE001WORK lpWork = (LPREGICOMPTYPE001WORK)lpGWork;

	gtk_widget_show( lpWork->regi_dialog );
	gtk_window_set_transient_for( GTK_WINDOW(lpWork->regi_dialog), GTK_WINDOW(g_main_window) );
	gtk_main();
}

static short GetStatusType001( void *lpGWork )
{
	LPREGICOMPTYPE001WORK lpWork = (LPREGICOMPTYPE001WORK)lpGWork;

	return lpWork->status;
}


/*-------------------------------------------------------------------------------
	static short ExecRegiType001( void *lpWork )
-------------------------------------------------------------------------------*/
short ExecRegiType001( void *lpWork, char *dialogName )
{
	LPREGICOMPTYPE001RES lpRegiRes = (LPREGICOMPTYPE001RES)lpWork;
	short	result = -1;

	/* confirm data type */
	if ( lpRegiRes->resType != RES_REGI_COMPTYPE001 ) goto Err;

	/* allocate  work */
	if ( (gLPRegiWork = CreateWorkRegiType001( lpRegiRes )) == NULL ) goto Err;

	/* ---- Show Dialog ---- */
	/* init parameter */
	InitParamRegiType001( lpRegiRes, gLPRegiWork );

	/* show labels */
	SetLabelRegiType001( lpRegiRes, gLPRegiWork, dialogName );

	/* set spinbutton */
	SetSpinButtonRegiType001( lpRegiRes, gLPRegiWork );

	/* set default setting */
	SetDefaultRegiType001( lpRegiRes, gLPRegiWork );

	/* show drawingarea */
	DrawTestPrintPageType001( gLPRegiWork, 0 );

	/* show dialog */
	ShowDialogRegiType001( lpRegiRes, gLPRegiWork );

	result = GetStatusType001( gLPRegiWork );

	/* dispose work */
	DisposeWorkRegiType001( gLPRegiWork );

Err:
	gLPRegiWork = NULL;
	return result;
}

#if 0
static  int getnum( char *ptr )
{
	char num_buf[32];
	int num_size = 0;

	while(*ptr != '\0'){
		if( *ptr >= 0x30 && *ptr <= 0x39){
    		num_size++;
			break;
		}
		ptr++;
	}

	if( num_size == 0 )
		return 0;

	while( ptr[num_size] != '\0' ){
		if( ptr[num_size] < 0x30 || ptr[num_size] > 0x39 )
			break;
		num_size++;
	}
	if( num_size > 31 )
		num_size = 31;

	memset(num_buf, 0, 32);
	strncpy(num_buf, ptr, num_size);

	return (atoi(num_buf));
}
#endif

static short CheckWorkType001( void )
{
	LPREGICOMPTYPE001WORK lpWk = gLPRegiWork;
	short result = -1;

	if ( lpWk == NULL ) goto Err;
	if ( lpWk->workType != WORK_REGI_COMPTYPE001 ) goto Err;

	result = 0;
Err:
	return result;		
}



static int GetCurrentSpinButtonNum( LPCTRLITEM lpCtrlItem, char *ctrlName )
{
	LPREGICOMPTYPE001WORK lpWk = gLPRegiWork;
	LPCTRLITEM lpTop = lpCtrlItem;
	int i, currentNum = -1;

	if ( CheckWorkType001() != 0 ) goto Err;

	for ( i=0; i<lpWk->itemNum; i++, lpTop++ ){
		if ( !strcmp( lpTop->CtrlName, ctrlName ) ){
			currentNum = i;
			break;
		}
	}

Err:
	return currentNum;
}


static void on_regi_common_type001_button_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data, 
										char			*spinbuttonName)
{
	int current, i;
	LPREGICOMPTYPE001WORK lpWk = gLPRegiWork;

	if ( CheckWorkType001() != 0 ) goto Err;

	current = GetCurrentSpinButtonNum( lpWk->lpCtrlItem, spinbuttonName );

	if( !strncmp( gtk_entry_get_text( GTK_ENTRY( spinbutton ) ), "-0" , 2 ) ) {
		gtk_spin_button_set_value( GTK_SPIN_BUTTON( spinbutton ), 1 );
		gtk_spin_button_set_value( GTK_SPIN_BUTTON( spinbutton ), 0 );
	}
	
	for (i=0; i<lpWk->itemNum; i++) {
		lpWk->itemValue[i] = gtk_spin_button_get_value_as_int(
			GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(spinbutton), lpWk->lpCtrlItem[i].CtrlName)));
	}

	DrawTestPrintPageType001( lpWk, current );

Err:
	return ;
}

static void on_regi_common_type001_focus_in_event(
	GtkWidget *widget, GdkEventFocus *event, gpointer user_data, char *spinbuttonName)
{
	int current, i;
	LPREGICOMPTYPE001WORK lpWk = gLPRegiWork;

	if ( CheckWorkType001() != 0 ) goto Err;

	current = GetCurrentSpinButtonNum( lpWk->lpCtrlItem, spinbuttonName );

	for (i=0; i<lpWk->itemNum; i++) {
		lpWk->itemValue[i] = gtk_spin_button_get_value_as_int(
			GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(widget), lpWk->lpCtrlItem[i].CtrlName)));
	}

	DrawTestPrintPageType001( lpWk, current );
Err:
	return ;
}


gboolean
on_regi_common_type001_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	LPREGICOMPTYPE001WORK lpWk = gLPRegiWork;

	if ( CheckWorkType001() != 0 ) goto Err;

	if ( lpWk->isPermitCancel != 0 ){
		gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(widget)));
		lpWk->status = US_CANCEL;
	}
Err:
	return TRUE;
}


void
on_regi_common_type001_dialog_destroy  (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


gboolean
on_regi_common_type001_drawingarea_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	LPREGICOMPTYPE001WORK lpWk = gLPRegiWork;
	int width, height, pix_width, pix_height;

	if ( CheckWorkType001() != 0 ) goto Err;


	gdk_window_get_size( widget->window, &width, &height );
	gdk_window_get_size( lpWk->regi_pixmap, &pix_width, &pix_height );

	gdk_draw_pixmap( widget->window,
					widget->style->fg_gc[GTK_WIDGET_STATE(widget)],	
					lpWk->regi_pixmap,
					event->area.x-(width - pix_width)/2,            
					event->area.y-(height - pix_height)/2,          
					event->area.x,                                  
					event->area.y,                                  
					event->area.width, event->area.height);         
Err:
	return FALSE;
}


gboolean
on_regi_common_type001_drawingarea_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	LPREGICOMPTYPE001WORK lpWk = gLPRegiWork;
	int		xPos, yPos, hit, i, j, current;
	int xOffset, yOffset;
	int drawWidth, drawHeight;
	GtkWidget	*spin_button;

	if ( CheckWorkType001() != 0 ) goto Err;

	gdk_window_get_size( lpWk->draw_area->window, &drawWidth, &drawHeight );

	xOffset = (drawWidth - lpWk->frameWidth)/2;
	yOffset = (drawHeight - lpWk->frameHeight)/2;
	
	xPos = event->x;		
	yPos = event->y;
	hit = FALSE;

	current = 0;
	for (i=0; i<lpWk->itemNum && !hit; i++) {	
		if (lpWk->HotSpot[i].stepdir) {		
			if(lpWk->HotSpot[i].selbox_x + xOffset <= xPos
			   && xPos <= lpWk->HotSpot[i].selbox_x + xOffset + lpWk->HotSpot[i].selbox_width) {	
				for(j=0; j<lpWk->HotSpot[i].cnt; j++) {	
					if(lpWk->HotSpot[i].selbox_y + yOffset + lpWk->HotSpot[i].step*j <= yPos &&
					   yPos <= (lpWk->HotSpot[i].selbox_y + yOffset + lpWk->HotSpot[i].step*j
											 + lpWk->HotSpot[i].selbox_height))
					{
						hit = TRUE;			
						current= i;		
						gtk_spin_button_set_value(
							GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(widget),
								lpWk->lpCtrlItem[i].CtrlName)),
									lpWk->lpCtrlItem[i].nMax - j);	
						break;
					}
				}
			}
		} else {		
			if (lpWk->HotSpot[i].selbox_y + yOffset <=yPos
			 && yPos<=(lpWk->HotSpot[i].selbox_y + yOffset + lpWk->HotSpot[i].selbox_height)) {
				for(j=0; j<lpWk->HotSpot[i].cnt; j++) {
					if ((lpWk->HotSpot[i].selbox_x + xOffset + lpWk->HotSpot[i].step*j)<=xPos
					  && xPos<=(lpWk->HotSpot[i].selbox_x + xOffset + lpWk->HotSpot[i].step*j
											 + lpWk->HotSpot[i].selbox_width))
					{
						hit = TRUE;
						current = i;
						gtk_spin_button_set_value(
							GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(widget),
								lpWk->lpCtrlItem[i].CtrlName)),
									j + lpWk->lpCtrlItem[i].nMin);
						break;
					}
				}
			}
		}
	}

	if (!hit)			
		return FALSE;			
	
	for (i=0; i<lpWk->itemNum; i++){
		lpWk->itemValue[i] = gtk_spin_button_get_value_as_int(
			GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(widget), lpWk->lpCtrlItem[i].CtrlName)) );
	}

	
	DrawTestPrintPageType001( lpWk, current );

	// focus spinbutton ver.3.20
	spin_button = LookupWidget( lpWk->regi_dialog, lpWk->lpCtrlItem[current].CtrlName );
	gtk_widget_grab_focus( spin_button );

Err:
  return FALSE;
}


void
on_regi_common_type001_button_changed_01
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton1");
}


gboolean
on_regi_common_type001_button_focus_in_event_01
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton1" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_02
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton2");
}


gboolean
on_regi_common_type001_button_focus_in_event_02
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton2" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_03
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton3");
}


gboolean
on_regi_common_type001_button_focus_in_event_03
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton3" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_04
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton4");
}


gboolean
on_regi_common_type001_button_focus_in_event_04
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton4" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_05
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton5");
}


gboolean
on_regi_common_type001_button_focus_in_event_05
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton5" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_06
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton6");
}


gboolean
on_regi_common_type001_button_focus_in_event_06
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton6" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_07
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton7");
}


gboolean
on_regi_common_type001_button_focus_in_event_07
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton7" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_08
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton8");
}


gboolean
on_regi_common_type001_button_focus_in_event_08
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton8" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_09
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton9");
}


gboolean
on_regi_common_type001_button_focus_in_event_09
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton9" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_11
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton11");
}


gboolean
on_regi_common_type001_button_focus_in_event_11
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton11" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_12
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton12");
}


gboolean
on_regi_common_type001_button_focus_in_event_12
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton12" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_13
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton13");
}


gboolean
on_regi_common_type001_button_focus_in_event_13
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton13" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_14
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton14");
}


gboolean
on_regi_common_type001_button_focus_in_event_14
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton14" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_15
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton15");
}


gboolean
on_regi_common_type001_button_focus_in_event_15
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton15" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_16
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton16");
}


gboolean
on_regi_common_type001_button_focus_in_event_16
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton16" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_17
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton17");
}


gboolean
on_regi_common_type001_button_focus_in_event_17
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton17" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_18
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton18");
}


gboolean
on_regi_common_type001_button_focus_in_event_18
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton18" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_19
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton19");
}


gboolean
on_regi_common_type001_button_focus_in_event_19
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton19" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_21
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton21");
}


gboolean
on_regi_common_type001_button_focus_in_event_21
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton21" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_22
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton22");
}


gboolean
on_regi_common_type001_button_focus_in_event_22
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton22" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_23
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton23");
}


gboolean
on_regi_common_type001_button_focus_in_event_23
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton23" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_24
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton24");
}


gboolean
on_regi_common_type001_button_focus_in_event_24
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton24" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_25
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton25");
}


gboolean
on_regi_common_type001_button_focus_in_event_25
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton25" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_26
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton26");
}


gboolean
on_regi_common_type001_button_focus_in_event_26
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton26" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_27
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton27");
}


gboolean
on_regi_common_type001_button_focus_in_event_27
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton27" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_28
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton28");
}


gboolean
on_regi_common_type001_button_focus_in_event_28
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton28" );
	return FALSE;
}


void
on_regi_common_type001_button_changed_29
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	on_regi_common_type001_button_changed( spinbutton, user_data, "regi_common_type001_spinbutton29");
}


gboolean
on_regi_common_type001_button_focus_in_event_29
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	on_regi_common_type001_focus_in_event( widget, event, user_data, "regi_common_type001_spinbutton29" );
	return FALSE;
}

/* OK */
void
on_regi_common_type001_button1_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	LPREGICOMPTYPE001WORK lpWk = gLPRegiWork;
	int i;

	if ( CheckWorkType001() != 0 ) goto Err;

	for ( i=0; i<lpWk->itemNum; i++ ){
		lpWk->itemValue[i]= gtk_spin_button_get_value_as_int(
			GTK_SPIN_BUTTON(LookupWidget(GTK_WIDGET(button), lpWk->lpCtrlItem[i].CtrlName)) );
	}

	/* set global */
	gLPItem = lpWk->lpCmdData;
	gItemNum = lpWk->itemNum;
	for ( i=0; i<gItemNum; i++ ){
		gItemValue[i] = lpWk->itemValue[i];
	}

	lpWk->status = US_OK;

	gtk_widget_destroy( gtk_widget_get_toplevel(GTK_WIDGET(button)) );
Err:
	return;
}

/* Cancel */
void
on_regi_common_type001_button2_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	LPREGICOMPTYPE001WORK lpWk = gLPRegiWork;

	if ( CheckWorkType001() != 0 ) goto Err;

	lpWk->status = US_CANCEL;
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
Err:
	return;
}



/*** COMPTYPE002 *********************************************************************************************/
static LPREGICOMPTYPE002WORK CreateWorkRegiType002( LPREGICOMPTYPE002RES lpRegiRes )
{
	LPREGICOMPTYPE002WORK lpWork = NULL;

	if( lpRegiRes == NULL ) goto Err;
	if ( (lpWork = g_malloc0(sizeof(REGICOMPTYPE002WORK))) == NULL ) goto Err;

	lpWork->workType = WORK_REGI_COMPTYPE002;
Err:
	return lpWork;
}

static void InitParamRegiType002( LPREGICOMPTYPE002RES lpRegiRes, void *lpGWork )
{
	LPREGICOMPTYPE002WORK lpWork = (LPREGICOMPTYPE002WORK)lpGWork;
	int paperSource;

	lpWork->status = US_DEFAULT;
	lpWork->regi_dialog = lpRegiRes->ptrCreateDialog();
	lpWork->uiType = lpRegiRes->uiType;

	gBinValueRegi = REGI_TYPE002_BINVALUE_CASETTE;

	if ( isGetPrinterSupplyInfo( lpWork->uiType ) == TRUE ){
		if ( GetMSIPaperSourceSettings01( &paperSource ) != -1 ){
			if ( paperSource == CND_SUPPLY_CASSETTE ) gBinValueRegi = REGI_TYPE002_BINVALUE_CASETTE;
			else if ( paperSource == CND_SUPPLY_ASF ) gBinValueRegi = REGI_TYPE002_BINVALUE_REARTRAY;
			else if ( paperSource == CND_SUPPLY_CASSETTE_AUTO ) gBinValueRegi = REGI_TYPE002_BINVALUE_CASETTE_AUTO;
		}
		else {
			gBinValueRegi = REGI_TYPE002_BINVALUE_NA;
		}
	}
}

static void SetLabelRegiType002( LPREGICOMPTYPE002RES lpRegiRes, void *lpGWork, char *dialogName )
{
	LPREGICOMPTYPE002WORK lpWork = (LPREGICOMPTYPE002WORK)lpGWork;

	SetLabelUtilDialog( lpWork->regi_dialog, dialogName );
}

static void SetDefaultRegiType002( LPREGICOMPTYPE002RES lpRegiRes, void *lpGWork )
{
	LPREGICOMPTYPE002WORK lpWork = (LPREGICOMPTYPE002WORK)lpGWork;
	GtkWidget *button;

	if ( (lpWork->uiType == UI_REGI_START_TYPE002) || (lpWork->uiType == UI_REGI_START_TYPE003) ){
		button = LookupWidget( lpWork->regi_dialog, regi_common_type002_radiobutton_name[gBinValueRegi] );
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );
	}
	else if ( (lpWork->uiType == UI_BINSELECT_TYPE001) || (lpWork->uiType == UI_BINSELECT_TYPE002) ){
		button = LookupWidget( lpWork->regi_dialog, regi_common_type002_radiobutton_name[gBinValueRegi] );
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), TRUE );

		button = LookupWidget( lpWork->regi_dialog, "regi_common_type002_button4" );
		gtk_widget_grab_focus( button );
		gtk_widget_grab_default( button );
	}
	else if ( (lpWork->uiType == UI_AUTOREGI_START_TYPE001) || (lpWork->uiType == UI_AUTOREGI_START_TYPE002) || 
				(lpWork->uiType == UI_AUTOREGI_START_TYPE003) || (lpWork->uiType == UI_AUTOREGI_START_TYPE004) ){
		button = LookupWidget( lpWork->regi_dialog, "regi_common_type002_button1" );
		gtk_widget_grab_focus( button );
		gtk_widget_grab_default( button );
	}
}

static void ShowDialogRegiType002( LPREGICOMPTYPE002RES lpRegiRes, void *lpGWork )
{
	LPREGICOMPTYPE002WORK lpWork = (LPREGICOMPTYPE002WORK)lpGWork;

	gtk_widget_show( lpWork->regi_dialog );
	gtk_window_set_transient_for( GTK_WINDOW(lpWork->regi_dialog), GTK_WINDOW(g_main_window) );

	gtk_main();
}


static void DisposeWorkRegiType002( LPREGICOMPTYPE002WORK lpWork )
{
	if ( lpWork == NULL ) goto Err;

	g_free( lpWork );
Err:
	return;
}

static short CheckWorkType002( void )
{
	LPREGICOMPTYPE002WORK lpWk = gLPRegiWork;
	short result = -1;

	if ( lpWk == NULL ) goto Err;
	if ( lpWk->workType != WORK_REGI_COMPTYPE002 ) goto Err;

	result = 0;
Err:
	return result;		
}


static short GetStatusType002( void *lpGWork )
{
	LPREGICOMPTYPE002WORK lpWork = (LPREGICOMPTYPE002WORK)lpGWork;
	return lpWork->status;
}


/*-------------------------------------------------------------------------------
	static short ExecRegiType002( void *lpWork )
-------------------------------------------------------------------------------*/
short ExecRegiType002( void *lpWork, char *dialogName )
{
	LPREGICOMPTYPE002RES lpRegiRes = (LPREGICOMPTYPE002RES)lpWork;
	short result = -1;

	/* confirm data type */
	if ( lpRegiRes->resType != RES_REGI_COMPTYPE002 ) goto Err;
		
	/* allocate  work */
	if ( (gLPRegiWork = CreateWorkRegiType002( lpRegiRes )) == NULL ) goto Err;

	/* ---- Show Dialog ---- */
	/* init parameter */
	InitParamRegiType002( lpRegiRes, gLPRegiWork );

	/* show labels */
	SetLabelRegiType002( lpRegiRes, gLPRegiWork, dialogName );

	/* set default */
	SetDefaultRegiType002( lpRegiRes, gLPRegiWork );

	/* show dialog */
	ShowDialogRegiType002( lpRegiRes, gLPRegiWork );

	/* get status */
	result = GetStatusType002( gLPRegiWork );

	DisposeWorkRegiType002( gLPRegiWork );

Err:
	gLPRegiWork = NULL;	
	return result;
}


void
on_regi_common_type002_dialog_destroy  (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


gboolean
on_regi_common_type002_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	LPREGICOMPTYPE002WORK lpWk = gLPRegiWork;
	if ( CheckWorkType002() != 0 ) goto Err;

	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(widget)));
	lpWk->status = US_CANCEL;
Err:
	return TRUE;
}

/* Close button */
void
on_regi_common_type002_button1_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	LPREGICOMPTYPE002WORK lpWk = gLPRegiWork;
	if ( CheckWorkType002() != 0 ) goto Err;


	lpWk->status = US_CLOSE;
Err:
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	return;
}

/* Align Print Head button */
void
on_regi_common_type002_button2_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	LPREGICOMPTYPE002WORK lpWk = gLPRegiWork;
	GtkWidget *window = GetTopWidget(GTK_WIDGET(button));
	short current;
	int type;

	if ( CheckWorkType002() != 0 ) goto Err;

	type = lpWk->uiType;
	switch( type ) {
		case UI_REGI_START_TYPE001:
		case UI_AUTOREGI_START_TYPE001:
		case UI_AUTOREGI_START_TYPE003:
		case UI_AUTOREGI_START_TYPE004:
			lpWk->status = US_ALIGIN_PRINT_HEAD;
			break;

		case UI_REGI_START_TYPE002:
			current = (short)GetActiveButtonIndex( window, regi_common_type002_radiobutton_name, REGI_TYPE002_BINVALUE_CASETTE );
			gBinValueRegi = current;
			if ( current == REGI_TYPE002_BINVALUE_REARTRAY ) lpWk->status = US_ALIGIN_PRINT_HEAD_REARTRAY;
			else if ( current == REGI_TYPE002_BINVALUE_CASETTE ) lpWk->status = US_ALIGIN_PRINT_HEAD_CASETTE;
			break;

		case UI_REGI_START_TYPE003:
			current = (short)GetActiveButtonIndex( window, regi_common_type002_radiobutton_name, REGI_TYPE002_BINVALUE_CASETTE );
			gBinValueRegi = current;
			if ( current == REGI_TYPE002_BINVALUE_REARTRAY ) lpWk->status = US_APH_ASF;
			else if ( current == REGI_TYPE002_BINVALUE_CASETTE ) lpWk->status = US_APH_FSF;
			break;

		default:
			lpWk->status = -1;
	}
Err:
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	return;
}

/* Print Alignment Value button */
void
on_regi_common_type002_button3_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	LPREGICOMPTYPE002WORK lpWk = gLPRegiWork;
	GtkWidget *window = GetTopWidget(GTK_WIDGET(button));
	short current;

	if ( CheckWorkType002() != 0 ) goto Err;

	int type = lpWk->uiType;
	switch( type ) {
		case UI_REGI_START_TYPE001:
		case UI_AUTOREGI_START_TYPE001:
			lpWk->status = US_PRINT_ALIGINMENT_VALUE;
			break;

		case UI_REGI_START_TYPE002:
			current = (short)GetActiveButtonIndex( window, regi_common_type002_radiobutton_name, REGI_TYPE002_BINVALUE_CASETTE );
			gBinValueRegi = current;
			if ( current == REGI_TYPE002_BINVALUE_REARTRAY ) lpWk->status = US_PRINT_ALIGINMENT_VALUE_REARTRAY;
			else lpWk->status = US_PRINT_ALIGINMENT_VALUE_CASETTE;
			break;

		case UI_REGI_START_TYPE003:
			current = (short)GetActiveButtonIndex( window, regi_common_type002_radiobutton_name, REGI_TYPE002_BINVALUE_CASETTE );
			gBinValueRegi = current;
			if ( current == REGI_TYPE002_BINVALUE_REARTRAY ) lpWk->status = US_PAV_ASF;
			else lpWk->status = US_PAV_FSF;
			break;

		case UI_AUTOREGI_START_TYPE002:
			if ( gBinValueRegi == REGI_TYPE002_BINVALUE_REARTRAY ) lpWk->status = US_PAV_ASF;
			else if ( gBinValueRegi == REGI_TYPE002_BINVALUE_CASETTE ) lpWk->status = US_PAV_FSF;
			else if ( gBinValueRegi == REGI_TYPE002_BINVALUE_NA ) lpWk->status = US_PAV_UNKNOWN;
			break;

		case UI_AUTOREGI_START_TYPE003:
			if ( gBinValueRegi == REGI_TYPE002_BINVALUE_REARTRAY ) lpWk->status = US_PAV_ASF;
			else if ( gBinValueRegi == REGI_TYPE002_BINVALUE_CASETTE ) lpWk->status = US_PAV_FSF;
			else if ( gBinValueRegi == REGI_TYPE002_BINVALUE_NA ) lpWk->status = US_PAV_SELECT_BIN;
			break;

		case UI_AUTOREGI_START_TYPE004:
			if ( gBinValueRegi == REGI_TYPE002_BINVALUE_CASETTE_AUTO ) lpWk->status = US_PAV_FRONT2;
			else if ( gBinValueRegi == REGI_TYPE002_BINVALUE_NA ) lpWk->status = US_PAV_UNKNOWN;
			break;

		default:
			lpWk->status = -1;
	}

	/* set return status */
Err:
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	return;

}

/* OK button */
void
on_regi_common_type002_button4_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	LPREGICOMPTYPE002WORK lpWk = gLPRegiWork;
	GtkWidget *window = GetTopWidget(GTK_WIDGET(button));
	short current;
	int type;

	if ( CheckWorkType002() != 0 ) goto Err;

	type = lpWk->uiType;
	switch( type ) {
		case UI_BINSELECT_TYPE001:
			current = (short)GetActiveButtonIndex( window, regi_common_type002_radiobutton_name, REGI_TYPE002_BINVALUE_CASETTE );
			gBinValueRegi = current;
			if ( current == REGI_TYPE002_BINVALUE_REARTRAY ) lpWk->status = US_OK_REARTRAY;
			else if ( current == REGI_TYPE002_BINVALUE_CASETTE ) lpWk->status = US_OK_CASETTE;
			break;

		case UI_BINSELECT_TYPE002:
			current = (short)GetActiveButtonIndex( window, regi_common_type002_radiobutton_name, REGI_TYPE002_BINVALUE_CASETTE );
			gBinValueRegi = current;
			if ( current == REGI_TYPE002_BINVALUE_REARTRAY ) lpWk->status = US_OK_ASF;
			else if ( current == REGI_TYPE002_BINVALUE_CASETTE ) lpWk->status = US_OK_FSF;
			break;

		default:
			lpWk->status = -1;
	}
Err:
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	return;
} 

/* Cancel button */
void
on_regi_common_type002_button5_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	LPREGICOMPTYPE002WORK lpWk = gLPRegiWork;

	if ( CheckWorkType002() != 0 ) goto Err;

	lpWk->status = US_CANCEL;
Err:
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
	return;
}

short ExecRegiType000_001( char *dialogName )
{
	int paperSource;
	short result = US_F_PHA_UNKNOWN;

	if ( GetMSIPaperSourceSettings01( &paperSource ) != -1 ){ 
		if ( paperSource == CND_SUPPLY_CASSETTE ){
			result = US_F_PHA_FSF;
		}
	}
	return result;
}

short ExecRegiType000_002( char *dialogName )
{
	int paperSource;
	short result = US_F_PHA_SELECT_BIN;

	if ( GetMSIPaperSourceSettings01( &paperSource ) != -1 ){ 
		if ( paperSource == CND_SUPPLY_CASSETTE ){
			gBinValueRegi = REGI_TYPE002_BINVALUE_CASETTE;
			result = US_F_PHA_FSF;
		}
		else if ( paperSource == CND_SUPPLY_ASF ){
			gBinValueRegi = REGI_TYPE002_BINVALUE_REARTRAY;
			result = US_F_PHA_ASF;
		}
	}
	return result;
}

/* Ver.3.80 */
short ExecRegiType000_003( char *dialogName )
{
	int paperSource;
	short result = US_F_PHA_UNKNOWN;

	if ( GetMSIPaperSourceSettings01( &paperSource ) != -1 ){ 
		if ( paperSource == CND_SUPPLY_CASSETTE ){
			result = US_F_PHA_FSF;
		}
		else if ( paperSource == CND_SUPPLY_ASF ){
			result = US_F_PHA_ASF;
		}
		else if ( paperSource == CND_SUPPLY_CASSETTE_AUTO ){
			result = US_F_PHA_FRONT2;
		}
	}
	return result;
}

static gboolean isGetPrinterSupplyInfo( int type )
{
	gboolean result = FALSE;

	switch ( type ) {
		case UI_AUTOREGI_START_TYPE002:
		case UI_AUTOREGI_START_TYPE003:
		case UI_AUTOREGI_START_TYPE004:
		case UI_REGI_START_TYPE001: /* Ver.3.70 */
			result = TRUE;
			break;
		default:
			break;
	}
	return result;
}

/* export functions */
short ExecRegiType000_000( char *dialogName ){ return US_F_HEAD_ALIGNMENT; }
short ExecRegiType001_000( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[0], dialogName) ); }
short ExecRegiType001_001( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[1], dialogName) ); }
short ExecRegiType001_002( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[2], dialogName) ); }
short ExecRegiType001_003( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[3], dialogName) ); }
short ExecRegiType001_004( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[4], dialogName) ); }
short ExecRegiType001_005( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[5], dialogName) ); }
short ExecRegiType001_006( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[6], dialogName) ); } /* Ver.3.50 */
short ExecRegiType001_007( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[7], dialogName) ); } /* Ver.3.50 */
short ExecRegiType001_008( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[8], dialogName) ); } /* Ver.3.60 */
short ExecRegiType001_009( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[9], dialogName) ); } /* Ver.3.60 */
short ExecRegiType001_010( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[10], dialogName) ); } /* Ver.3.60 */
short ExecRegiType001_011( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[11], dialogName) ); } /* Ver.3.70 */
short ExecRegiType001_012( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[12], dialogName) ); } /* Ver.3.70 */
short ExecRegiType001_013( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[13], dialogName) ); } /* Ver.3.70 */
short ExecRegiType001_014( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[14], dialogName) ); } /* Ver.3.80 */
short ExecRegiType001_015( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[15], dialogName) ); } /* Ver.3.80 */
short ExecRegiType001_016( char *dialogName ){ return ( ExecRegiType001( (void *)&regiType001Res[16], dialogName) ); } /* Ver.3.80 */
short ExecRegiType002_000( char *dialogName ){ return ( ExecRegiType002( (void *)&regiType002Res[0], dialogName) ); }
short ExecRegiType002_001( char *dialogName ){ return ( ExecRegiType002( (void *)&regiType002Res[1], dialogName) ); }
short ExecRegiType002_002( char *dialogName ){ return ( ExecRegiType002( (void *)&regiType002Res[2], dialogName) ); }
short ExecRegiType002_003( char *dialogName ){ return ( ExecRegiType002( (void *)&regiType002Res[3], dialogName) ); }
short ExecRegiType002_004( char *dialogName ){ return ( ExecRegiType002( (void *)&regiType002Res[4], dialogName) ); }
short ExecRegiType002_005( char *dialogName ){ return ( ExecRegiType002( (void *)&regiType002Res[5], dialogName) ); } /* Ver.3.70 */
short ExecRegiType002_006( char *dialogName ){ return ( ExecRegiType002( (void *)&regiType002Res[6], dialogName) ); } /* Ver.3.70 */
short ExecRegiType002_007( char *dialogName ){ return ( ExecRegiType002( (void *)&regiType002Res[7], dialogName) ); } /* Ver.3.70 */
short ExecRegiType002_008( char *dialogName ){ return ( ExecRegiType002( (void *)&regiType002Res[8], dialogName) ); } /* Ver.3.70 */
short ExecRegiType002_009( char *dialogName ){ return ( ExecRegiType002( (void *)&regiType002Res[9], dialogName) ); } /* Ver.3.80 */


