/*  Canon Inkjet Printer Driver for Linux
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


#define	PICTURE_WIDTH		100		
#define	PICTURE_HEIGHT		144		

#define	PICTURE_WIDTH_BIG2	118		
#define	PICTURE_HEIGHT_BIG2	170     

#define PICTURE_WIDTH_BIG3	128
#define PICTURE_HEIGHT_BIG3	180

#define PICTURE_WIDTH_BIG4	140
#define PICTURE_HEIGHT_BIG4	198

#define	PORT			0x0000		
#define	LAND			0x0001		
#define	NO_DISPLAY		0x0002		
#define	ORNAMENT_S600	0x0100		
#define	ORNAMENT_REG	0x0200		// Ornament of each box
#define	BANDREGI_TYPE	0x1000		
#define	BIGAREA_TYPE2	0x2000		
#define BIGAREA_TYPE3	0x4000
#define BIGAREA_TYPE4	0x8000

#define	BJLSTART		"BJLSTART\x0a"					
#define BJLCTRLMODE		"ControlMode=Common\x0a"		
#define	BJLCLEAN1		"@Cleaning=1\x0a"				
#define BJLCLEAN2		"@Cleaning=2\x0a"				
#define BJLCLEAN3		"@Cleaning=1ALL\x0a"			
#define	BJLCLEAN4		"@Cleaning=2ALL\x0a"			
#define	BJLCLEAN5		"@Cleaning=1K\x0a"				
#define	BJLCLEAN6		"@Cleaning=1CMY\x0a"			
#define BJLCLEAN7		"@Cleaning=2K\x0a"
#define BJLCLEAN8		"@Cleaning=2CMY\x0a"
#define	BJLCLEAN9		"@Cleaning=1G1\x0a"
#define	BJLCLEAN10		"@Cleaning=1G2\x0a"
#define	BJLCLEAN11		"@Cleaning=2G1\x0a"
#define	BJLCLEAN12		"@Cleaning=2G2\x0a"


#define BJLNOZZLECHECK	"@TestPrint=NozzleCheck\x0a"	
#define	BJLMANUAL		"@TestPrint=Manual\x0a"			
#define	BJLREGI1		"@TestPrint=Regi1\x0a"			
#define	BJLREGI2		"@TestPrint=Regi2\x0a"			
#define	BJLREGI3		"@TestPrint=Regi3\x0a"		// 2005/05/25
#define	BJLREGI4		"@TestPrint=Regi4\x0a"		// 2007/06/26
#define	BJLBANDREGI1	"@TestPrint=BandRegi1\x0a"		
#define	BJLMANUAL1		"@TestPrint=Manual1\x0a"		
#define	BJLMANUAL2		"@TestPrint=Manual2\x0a"		
#define BJLREGIAUTO1	"@TestPrint=Regi_Auto1\x0a"			
#define BJLREGICHECK	"@TestPrint=RegiCheck\x0a"			
#define BJLSETREG		"SetRegistration=%6s%c%02d\x0a"	
#define BJLSETREG2		"SetRegi2=%2s%c%01d\x0a"		// 2006/05/25
#define	BJLSETBANDREG	"SetBandRegi=%1s%c%02d\x0a"		
#define	BJLPOWEROFF		"@PowerOff\x0a"					
#define	BJLAUTOPOWEROFF	"AutoPowerOff=%s\x0a"			
#define	BJLAUTOPOWERON	"AutoPowerOn=%s\x0a"			
#define BJLEND			"BJLEND\x0a"					
#define BJLROLLER1		"@RollerCleaning=PLATE\x0a"		
#define	BJLROLLER2		"@RollerCleaning\x0a"			
#define BJLROLLER3		"@RollerCleaning=Platen\x0a"
#define BJLROLLER4		"@RollerCleaning=Roller\x0a"

#define BJLSCANDELAY	"Reserve=A311\x0a"				
#define BJLNOSCANDELAY	"Reserve=A312\x0a"				
#define BJLPAGEDELAY	"Reserve=A321\x0a"				
#define BJLNOPAGEDELAY	"Reserve=A322\x0a"				
#define BJLSCANDELAY1	"DelayMode=SD1\x0a"				
#define BJLNOSCANDELAY1	"DelayMode=SD0\x0a"				
#define BJLPAGEDELAY1	"DelayMode=PD1\x0a"				
#define BJLNOPAGEDELAY1	"DelayMode=PD0\x0a"				
#define	BJLSETTIME		"SetTime="						

#define BJLSILENT		"SetSilent=%s\x0a"
#define BJLDRYLEVEL		"DryLevel=%d\x0a"
#define BJLINKDETECTION	"InkDetection=%s\x0a"
#define BJLRESETBLACK	"@DotCountClear=ColorK\x0a"
#define BJLRESETCMY		"@DotCountClear=CMY\x0a"
#define BJLPAPERGAP		"PaperGap=%s\x0a"

#define BJLLEN				7
#define	BJLSTARTLEN			9
#define BJLCTRLMODELEN		19
#define	BJLCLEAN1LEN		12
#define BJLCLEAN2LEN		12
#define	BJLCLEAN3LEN		15
#define BJLCLEAN4LEN		15
#define	BJLCLEAN5LEN		13
#define	BJLCLEAN6LEN		15
#define BJLCLEAN7LEN		13
#define BJLCLEAN8LEN		15
#define BJLCLEAN9LEN		14
#define BJLCLEAN10LEN		14
#define BJLCLEAN11LEN		14
#define BJLCLEAN12LEN		14



#define BJLNOZZLECHECKLEN	23
#define	BJLMANUALLEN		18
#define	BJLREGI1LEN			17
#define	BJLREGI2LEN			17
#define	BJLREGI3LEN			17		// 2006/05/25
#define	BJLREGI4LEN			17		// 2007/06/26
#define	BJLBANDREGI1LEN		21
#define	BJLMANUAL1LEN		19
#define	BJLMANUAL2LEN		19
#define	BJLREGIAUTO1LEN		22
#define	BJLREGICHECKLEN		21
#define	BJLSETREGLEN		26
#define	BJLSETREG2LEN		14		// 2006/05/25
#define	BJLSETBANDREGLEN	17
#define	BJLPOWEROFFLEN		10

#define BJLENDLEN			7                           
#define	BJLROLLER1LEN		22                          
#define	BJLROLLER2LEN		16                          
#define	BJLROLLER3LEN		23
#define	BJLROLLER4LEN		23

#define BJLSCANDELAYLEN		13                          
#define	BJLNOSCANDELAYLEN	13                          
#define	BJLPAGEDELAYLEN		13                          
#define	BJLNOPAGEDELAYLEN	13                          
#define BJLSCANDELAYLEN1	14                          
#define	BJLNOSCANDELAYLEN1	14                          
#define	BJLPAGEDELAYLEN1	14                          
#define	BJLNOPAGEDELAYLEN1	14                          
#define	BJLSETTIMELEN		8							
#define BJLSETTIMEPARAMLEN	15							

// Added '01.11.16
#define BJLRESETBLACKLEN	22
#define BJLRESETCMYLEN		19


#define	REGI_BUF_SIZE		(20+30*14)
#define	REGI_TMP_SIZE		30                          


const char bjl_cmds[] = {0x1b, '[', 'K', 0x02, 0x00, 0x00, 0x1f };


typedef struct {
	short	len;		
	char	*cmd;		
} CLEANCMD, *LPCLEANCMD;

CLEANCMD	S600CleanCommand[3] = {
				{ BJLCLEAN3LEN, BJLCLEAN3 },	
				{ BJLCLEAN5LEN, BJLCLEAN5 },	
				{ BJLCLEAN6LEN, BJLCLEAN6 }		
			};
CLEANCMD	GroupCleanCommand[3] = {
				{ BJLCLEAN3LEN, BJLCLEAN3 },	
				{ BJLCLEAN9LEN, BJLCLEAN9 },	
				{ BJLCLEAN10LEN, BJLCLEAN10 }		
			};

CLEANCMD	RefreshingCommand[3] = {
				{ BJLCLEAN4LEN, BJLCLEAN4 },	
				{ BJLCLEAN7LEN, BJLCLEAN7 },	
				{ BJLCLEAN8LEN, BJLCLEAN8 }		
			};

CLEANCMD	GroupRefreshingCommand[3] = {
				{ BJLCLEAN4LEN, BJLCLEAN4 },	
				{ BJLCLEAN11LEN, BJLCLEAN11 },	
				{ BJLCLEAN12LEN, BJLCLEAN12 }		
			};


char	*AutoPowerOnKey[2] = {		
					"autopower_disable",		
					"autopower_enable"			
			};

char	*AutoPowerOnValue[2] = {		
					"Disable",                  
					"Enable",					
			};


char	*AutoPowerOffKey[6] = {		
					"autopower_disable",		
					"autopower_5min",			
					"autopower_10min",			
					"autopower_15min",			
					"autopower_30min",			
					"autopower_60min"			
			};

char	*AutoPowerOffValue[6] = {		
					"Disable",                  
					"5",                        
					"10",                       
					"15",                       
					"30",                       
					"60"                        
			};

// 2006/06/26
char	*AutoPowerOffBatteryKey[4] = {		
					"autopower_5min",			
					"autopower_10min",			
					"autopower_15min",			
					"autopower_30min",			
		};

char	*AutoPowerOffBatteryValue[4] = {		
					"B5",                        
					"B10",                       
					"B15",                       
					"B30",                       
		};


char	*SwitchString[2] = {
					"OFF",
					"ON"
			};

char	*PaperGapString[2] = {
					"AUTO",
					"WIDE"
			};



typedef struct {
	char	x;						
	char	y;                      
	char	width;                  
	char	len;                    
	char	step;                   
	char	stepdir;                
	char	linedir;                
	char	repeat;                 
                                    
	char	selbox_dx;              
	char	selbox_dy;              
	char	selbox_width;           
	char	selbox_height;          
                                    
	short	red;                    
	short	green;                  
	short	blue;                   

	short	ornament;               // 0:none 1:one 2:two
} BOXINF, *LPBOXINF;


typedef struct {
	char	*CtrlName;				
	short	nDefault;               
	short	nMin;                   
	short	nMax;                   
} CTRLITEM, *LPCTRLITEM;


#define REGI_TBL_MAX_NUM	4
typedef struct RegiInfo {
	char		*ModelName;			
	struct	RegiTbl {				
		char		*DialogName;	
		char		*DrawingName;	
		LPCTRLITEM	pCtrlItem;		
		char		**pBJLTbl;		
		LPBOXINF	lpBoxInf;		
		short		cnt;			
		u_short		type;			
//	} regi[3];					
	} regi[REGI_TBL_MAX_NUM];					
} REGINFO;


typedef struct {
	short	x;						
	short	y;                      
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

#define	REGI_EDITMAX		14           


/* IP2200 */
#define IDM_IP_2200		"IP2200"
#define REGI_IP2200_1STCNT	12
#define REGI_IP2200_1STCNT_BSCC	1


CTRLITEM IP2200Regi1stTbl[REGI_IP2200_1STCNT] = {

	{ "IP2200regi_spinbutton1", 0, -5, 5 },	
	{ "IP2200regi_spinbutton2", 0, -5, 5 },   
	{ "IP2200regi_spinbutton3", 0, -5, 5 },   
	{ "IP2200regi_spinbutton4", 0, -5, 5 },   
	{ "IP2200regi_spinbutton5", 0, -5, 5 },   
	{ "IP2200regi_spinbutton6", 0, -5, 5 },   
	{ "IP2200regi_spinbutton7", 0, -5, 5 },   
	{ "IP2200regi_spinbutton8", 0, -5, 5 },   
	{ "IP2200regi_spinbutton9", 0, -5, 5 },   
	{ "IP2200regi_spinbutton10",0, -5, 5 },   
	{ "IP2200regi_spinbutton11",0, -5, 5 },   
	{ "IP2200regi_spinbutton12",0, -5, 5 }   

};


char *IP2200BJL1stTbl[REGI_IP2200_1STCNT+3] = {	// 2006/06/01 modify
	"Z1200A",
	"X1200H",
	"Z1200I",
	"X1200J",
	"X0600K",
	"Y0600L",
	"X1200B",
	"X1200C",
	"X1200D",
	"X1200E",
	"X1200F", 
	"X1200G",
	"X1200M",
	"X1200N",
	"X1200O"

};


BOXINF IP2200Box1stTbl[REGI_IP2200_1STCNT] = {

	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },	
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },    
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },    
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },    
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },    
	{ 95,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 25, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 53, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff, 0 },
	{ 81, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },
	{ 95, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 }

};


/*--- Ver.2.70 Model -------------------------------------------------------------------------------------------------*/
// MP160
#define IDM_MP_160		"MP160"

char *MP160BJL1stTbl[REGI_IP2200_1STCNT+3] = {
	"Z1200W",
	"X1200N",
	"Z1200Y",
	"X1200M",
	"X0600O",
	"Y0600P",
	"X1200B",
	"X1200F",
	"X1200R",
	"X1200C",
	"X1200G", 
	"X1200S",
	"X1200D",
	"X1200H",
	"X1200T"

};

// IP3300
#define IDM_IP_3300		"IP3300"
// MP510
#define IDM_MP_510		"MP510"

#define REGI_IP3300_1STCNT	11 	
#define REGI_IP3300_2NDCNT	2
#define REGI_IP3300_3RDCNT	0

CTRLITEM IP3300Regi1stTbl[REGI_IP3300_1STCNT] = {

	{ "IP3300regi1_spinbutton1", 0, -3, 7 },	
	{ "IP3300regi1_spinbutton2", 0, -3, 7 },   
	{ "IP3300regi1_spinbutton3", 0, -3, 7 },   
	{ "IP3300regi1_spinbutton4", 0, -3, 7 },   
	{ "IP3300regi1_spinbutton5", 0, -3, 7 },   
	{ "IP3300regi1_spinbutton6", 0, -5, 5 },   
	{ "IP3300regi1_spinbutton7", 0, -5, 5 },   
	{ "IP3300regi1_spinbutton8", 0, -5, 5 },   
	{ "IP3300regi1_spinbutton9", 0, -5, 5 },   
	{ "IP3300regi1_spinbutton10", 0, -5, 5 },   
	{ "IP3300regi1_spinbutton11", 0, -5, 5 },   

};

CTRLITEM IP3300Regi2ndTbl[REGI_IP3300_2NDCNT] = {

	{ "IP3300regi2_spinbutton1", 0, -3, 3 },   
	{ "IP3300regi2_spinbutton2", 0, -3, 3 },   

};

char *IP3300BJL1stTbl[REGI_IP3300_1STCNT+2] = {	
	"X1200A",
	"X1200B",
	"X1200C",
	"X1200E",
	"X1200F",
	"X1200M",
	"X1200N",
	"X1200J",
	"X1200O",
	"X1200K",
	"X1200L",
	"X1200D",
	"X1200P",
};

char *IP3300BJL2ndTbl[REGI_IP3300_2NDCNT] = {
	"A",
	"B",

};

BOXINF IP3300Box1stTbl[REGI_IP3300_1STCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff, 0 },
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },
	{ 25, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 53, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 95, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },

};

BOXINF IP3300Box2ndTbl[REGI_IP3300_2NDCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 41,  16,  16,  2,  13, 1,  1,   0,       -2,       -4,       19,          8, 0x8000, 0x8000, 0x8000, 1 },
	{ 72,  16,  16,  4,  13, 1,  1,   0,       -2,       -6,       19,          12, 0x8000, 0x8000, 0x8000, 1 },
};


// IP4300
#define IDM_IP_4300		"IP4300"
// MP600
#define IDM_MP_600		"MP600"

#define REGI_IP4300_1STCNT	6
#define REGI_IP4300_2NDCNT	6
#define REGI_IP4300_3RDCNT	2	

CTRLITEM IP4300Regi1stTbl[REGI_IP4300_1STCNT] = {

	{ "IP4300regi1_spinbutton1", 0, -3, 7 },	
	{ "IP4300regi1_spinbutton2", 0, -3, 7 },   
	{ "IP4300regi1_spinbutton3", 0, -3, 7 },   
	{ "IP4300regi1_spinbutton4", 0, -5, 5 },   
	{ "IP4300regi1_spinbutton5", 0, -5, 5 },   
	{ "IP4300regi1_spinbutton6", 0, -5, 5 },   

};

CTRLITEM IP4300Regi2ndTbl[REGI_IP4300_2NDCNT] = {

	{ "IP4300regi2_spinbutton1", 0, -5, 5 },   
	{ "IP4300regi2_spinbutton2", 0, -5, 5 },   
	{ "IP4300regi2_spinbutton3", 0, -5, 5 },   
	{ "IP4300regi2_spinbutton4", 0, -5, 5 },   
	{ "IP4300regi2_spinbutton5", 0, -3, 3 },   
	{ "IP4300regi2_spinbutton6", 0, -3, 3 },   

};

CTRLITEM IP4300Regi3rdTbl[REGI_IP4300_3RDCNT] = {

	{ "IP4300regi3_spinbutton1", 0, -2, 2 },   
	{ "IP4300regi3_spinbutton2", 0, -2, 2 },   

};

char *IP4300BJL1stTbl[REGI_IP4300_1STCNT] = {
	"1A",
	"1B",
	"1C",
	"1D",
	"1E",
	"1F",

};

char *IP4300BJL2ndTbl[REGI_IP4300_2NDCNT] = {
	"2G",
	"2H",
	"2I",
	"2J",
	"2K",
	"2L"

};

char *IP4300BJL3rdTbl[REGI_IP4300_3RDCNT] = {
	"3M",
	"3N",
};

BOXINF IP4300Box1stTbl[REGI_IP4300_1STCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 46,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 60,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 74,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 46, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 60, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 74, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },

};

BOXINF IP4300Box2ndTbl[REGI_IP4300_2NDCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 39,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0 },
	{ 53,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0 },
	{ 67,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0xffff, 0xffff, 0 },
	{ 81,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 34, 90, 16,  2, 13, 1,  1,   0,       -2,       -4,       19,          8, 0x8000, 0x8000, 0x8000, 1 },
	{ 65, 90, 16,  4, 13, 1,  1,   0,       -2,       -6,       19,         12, 0x8000, 0x8000, 0x8000, 1 }
};

BOXINF IP4300Box3rdTbl[REGI_IP4300_3RDCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 53,  16,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x0000, 0xffff, 0xffff, 0 },//2007/06/28
	{ 67,  16,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },
};


// IP90								// 2006/10/11
#define IDM_IP_90		"IP90"

#define REGI_IP90_1STCNT	11

CTRLITEM IP90Regi1stTbl[REGI_IP90_1STCNT] = {

	{ "IP90regi_spinbutton1", 0, -3, 7 },	
	{ "IP90regi_spinbutton2", 0, -3, 7 },   
	{ "IP90regi_spinbutton3", 0, -3, 7 },   
	{ "IP90regi_spinbutton4", 0, -3, 7 },   
	{ "IP90regi_spinbutton5", 0, -3, 7 },   
	{ "IP90regi_spinbutton6", 0, -5, 5 },   
	{ "IP90regi_spinbutton7", 0, -5, 5 },   
	{ "IP90regi_spinbutton8", 0, -5, 5 },   
	{ "IP90regi_spinbutton9", 0, -5, 5 },
	{ "IP90regi_spinbutton10", 0, -5, 5 },
	{ "IP90regi_spinbutton11", 0, -5, 5 },
};


char *IP90BJL1stTbl[REGI_IP90_1STCNT+5] = {
	"X1200A",
	"X1200B",
	"X1200C",
	"X1200E",
	"X1200F",
	"X1200J",
	"X1200K",
	"X1200G",
	"X1200L",
	"X1200H",
	"X1200I",
	"X1200D",
	"X1200N",
	"X1200M",
	"X1200P",
	"X1200O",
};


BOXINF IP90Box1stTbl[REGI_IP90_1STCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff, 0 },
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },
	{ 25, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 53, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 95, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },

};


// IP1800							// 2006/07/05
#define IDM_IP_1800		"IP1800"

// IP2500							// 2006/07/05
#define IDM_IP_2500		"IP2500"


/*--- Ver.2.80 Model -------------------------------------------------------------------------------------------------*/
// MP140							// 2007/05/31
#define IDM_MP_140		"MP140"

// MP210							// 2007/06/19
#define IDM_MP_210		"MP210"

#define REGI_MP210_1STCNT	12
#define REGI_MP210_2NDCNT	6

CTRLITEM MP210Regi1stTbl[REGI_MP210_1STCNT] = {

	{ "IP2200regi_spinbutton1", 0, -5, 5 },	
	{ "IP2200regi_spinbutton2", 0, -5, 5 },   
	{ "IP2200regi_spinbutton3", 0, -5, 5 },   
	{ "IP2200regi_spinbutton4", 0, -5, 5 },   
	{ "IP2200regi_spinbutton5", 0, -5, 5 },   
	{ "IP2200regi_spinbutton6", 0, -5, 5 },   
	{ "IP2200regi_spinbutton7", 0, -5, 5 },   
	{ "IP2200regi_spinbutton8", 0, -5, 5 },   
	{ "IP2200regi_spinbutton9", 0, -5, 5 },   
	{ "IP2200regi_spinbutton10",0, -5, 5 },   
	{ "IP2200regi_spinbutton11",0, -5, 5 },   
	{ "IP2200regi_spinbutton12",0, -5, 5 }   

};

CTRLITEM MP210Regi2ndTbl[REGI_MP210_2NDCNT] = {

	{ "TYPE_G_regi2_spinbutton1", 0, -2, 2 },   
	{ "TYPE_G_regi2_spinbutton2", 0, -2, 2 },   
	{ "TYPE_G_regi2_spinbutton3", 0, -2, 2 },   
	{ "TYPE_G_regi2_spinbutton4", 0, -2, 2 },   
	{ "TYPE_G_regi2_spinbutton5", 0, -4, 4 },   
	{ "TYPE_G_regi2_spinbutton6", 0, -4, 4 }

};

char *MP210BJL1stTbl[REGI_MP210_1STCNT] = {

	"1A",
	"1B",
	"1C",
	"1D",
	"1E",
	"1F",
	"1G",
	"1H",
	"1I",
	"1J",
	"1K",
	"1L"

};

char *MP210BJL2ndTbl[REGI_MP210_2NDCNT] = {

	"2M",
	"2N",
	"2O",
	"2P",
	"2Q",
	"2R"

};

BOXINF MP210Box1stTbl[REGI_MP210_1STCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },	
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },    
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },    
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },    
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },    
	{ 95,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 25, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 53, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff, 0 },
	{ 81, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },
	{ 95, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 }

};

BOXINF MP210Box2ndTbl[REGI_MP210_2NDCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },	
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },    
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff, 0 },    
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },    
	{ 53,  51, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },    
	{ 67,  51, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },    

};


// IP3500							// 2007/06/25
#define IDM_IP_3500		"IP3500"
// MP520							// 2007/06/25
#define IDM_MP_520		"MP520"

// IP4500							// 2007/06/25
#define IDM_IP_4500		"IP4500"
// MP610							// 2007/06/25
#define IDM_MP_610		"MP610"

#define REGI_TYPE_F_1STCNT 7	
#define REGI_TYPE_F_2NDCNT 8
#define REGI_TYPE_F_3RDCNT 7	
#define REGI_TYPE_F_4THCNT 11

CTRLITEM TYPE_F_Regi1stTbl[REGI_TYPE_F_1STCNT] = {
	{ "TYPE_F_regi1_spinbutton1", 0, -3, 7 },	
	{ "TYPE_F_regi1_spinbutton2", 0, -3, 7 },	
	{ "TYPE_F_regi1_spinbutton3", 0, -3, 7 },	
	{ "TYPE_F_regi1_spinbutton4", 0, -3, 7 },	
	{ "TYPE_F_regi1_spinbutton5", 0, -5, 5 },	
	{ "TYPE_F_regi1_spinbutton6", 0, -5, 5 },	
	{ "TYPE_F_regi1_spinbutton7", 0, -5, 5 },	

};

CTRLITEM TYPE_F_Regi2ndTbl[REGI_TYPE_F_2NDCNT] = {
	{ "TYPE_F_regi2_spinbutton1", 0, -5, 5 },	
	{ "TYPE_F_regi2_spinbutton2", 0, -5, 5 },	
	{ "TYPE_F_regi2_spinbutton3", 0, -5, 5 },	
	{ "TYPE_F_regi2_spinbutton4", 0, -5, 5 },	
	{ "TYPE_F_regi2_spinbutton5", 0, -5, 5 },	
	{ "TYPE_F_regi2_spinbutton6", 0, -5, 5 },	
	{ "TYPE_F_regi2_spinbutton7", 0, -5, 5 },	
	{ "TYPE_F_regi2_spinbutton8", 0, -5, 5 },	

};

CTRLITEM TYPE_F_Regi3rdTbl[REGI_TYPE_F_3RDCNT] = {
	{ "TYPE_F_regi3_spinbutton1", 0, -5, 5 },	
	{ "TYPE_F_regi3_spinbutton2", 0, -5, 5 },	
	{ "TYPE_F_regi3_spinbutton3", 0, -5, 5 },	
	{ "TYPE_F_regi3_spinbutton4", 0, -5, 5 },	
	{ "TYPE_F_regi3_spinbutton5", 0, -5, 5 },	
	{ "TYPE_F_regi3_spinbutton6", 0, -3, 3 },	
	{ "TYPE_F_regi3_spinbutton7", 0, -3, 3 },	

};

CTRLITEM TYPE_F_Regi4thTbl[REGI_TYPE_F_4THCNT] = {
	{ "TYPE_F_regi4_spinbutton1", 0, -2, 2 },	
	{ "TYPE_F_regi4_spinbutton2", 0, -2, 2 },	
	{ "TYPE_F_regi4_spinbutton3", 0, -2, 2 },	
	{ "TYPE_F_regi4_spinbutton4", 0, -2, 2 },	
	{ "TYPE_F_regi4_spinbutton5", 0, -2, 2 },	
	{ "TYPE_F_regi4_spinbutton6", 0, -2, 2 },	
	{ "TYPE_F_regi4_spinbutton7", 0, -2, 2 },	
	{ "TYPE_F_regi4_spinbutton8", 0, -2, 2 },	
	{ "TYPE_F_regi4_spinbutton9", 0, -2, 2 },	
	{ "TYPE_F_regi4_spinbutton10", 0, -2, 2 },	
	{ "TYPE_F_regi4_spinbutton11", 0, -2, 2 },	

};

char *TYPE_F_BJL1stTbl[REGI_TYPE_F_1STCNT] = {
	"1A",
	"1B",
	"1C",
	"1D",
	"1E",
	"1F",
	"1G",
};

char *TYPE_F_BJL2ndTbl[REGI_TYPE_F_2NDCNT] = {
	"2H",
	"2I",
	"2J",
	"2K",
	"2L",
	"2M",
	"2N",
	"2O",

};

char *TYPE_F_BJL3rdTbl[REGI_TYPE_F_3RDCNT] = {
	"3P",
	"3Q",
	"3R",
	"3S",
	"3T",
	"3U",
	"3V",

};

char *TYPE_F_BJL4thTbl[REGI_TYPE_F_4THCNT] = {
	"4a",
	"4b",
	"4c",
	"4d",
	"4e",
	"4f",
	"4g",
	"4h",
	"4i",
	"4j",
	"4k",

};

BOXINF TYPE_F_Box1stTbl[REGI_TYPE_F_1STCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 53, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },

};

BOXINF TYPE_F_Box2ndTbl[REGI_TYPE_F_2NDCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 39,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 53,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 67,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 39, 90,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 53, 90,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 67, 90,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81, 90,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },

};

BOXINF TYPE_F_Box3rdTbl[REGI_TYPE_F_3RDCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 39,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0 },
	{ 53,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0 },
	{ 67,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0xffff, 0xffff, 0 },
	{ 81,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 95,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 34, 90, 16,  2, 13, 1,  1,   0,       -2,       -4,       19,          8, 0x8000, 0x8000, 0x8000, 1 },
	{ 65, 90, 16,  4, 13, 1,  1,   0,       -2,       -6,       19,         12, 0x8000, 0x8000, 0x8000, 1 }

};

BOXINF TYPE_F_Box4thTbl[REGI_TYPE_F_4THCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 26,  32,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },
	{ 40,  32,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },
	{ 54,  32,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },
	{ 68,  32,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },
	{ 82,  32,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },
	{ 26,  86,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },
	{ 40,  86,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },
	{ 54,  86,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },
	{ 68,  86,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },
	{ 82,  86,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },
	{ 96,  86,  9,  3,  9, 1,  1,   0,       -2,       -5,       12,          9, 0x8000, 0xffff, 0xffff, 0 },

};


/*--- Set initial Parameter ------------------------------------------------------------------------------------*/
REGINFO	RegiInfo[] = 
	{
	// 2006/06/27
	{ IDM_MP_160,
	{ { "IP2200regi_dialog", "IP2200regi_drawingarea", IP2200Regi1stTbl,
		MP160BJL1stTbl, IP2200Box1stTbl, REGI_IP2200_1STCNT, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2006/05/29
	{ IDM_IP_3300,
	{ { "IP3300regi1_dialog", "IP3300regi1_drawingarea", IP3300Regi1stTbl,
		IP3300BJL1stTbl, IP3300Box1stTbl, REGI_IP3300_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "IP3300regi2_dialog", "IP3300regi2_drawingarea", IP3300Regi2ndTbl, 
		  IP3300BJL2ndTbl, IP3300Box2ndTbl,REGI_IP3300_2NDCNT , PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
		{ 0, 0, 0, 0, 0, 0, 0 },
   		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_MP_510,
	{ { "IP3300regi1_dialog", "IP3300regi1_drawingarea", IP3300Regi1stTbl,
		IP3300BJL1stTbl, IP3300Box1stTbl, REGI_IP3300_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "IP3300regi2_dialog", "IP3300regi2_drawingarea", IP3300Regi2ndTbl, 
		  IP3300BJL2ndTbl, IP3300Box2ndTbl,REGI_IP3300_2NDCNT , PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
		{ 0, 0, 0, 0, 0, 0, 0 },
    	{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2006/05/26
	{ IDM_IP_4300,
	{ { "IP4300regi1_dialog", "IP4300regi1_drawingarea", IP4300Regi1stTbl,
		IP4300BJL1stTbl, IP4300Box1stTbl, REGI_IP4300_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "IP4300regi2_dialog", "IP4300regi2_drawingarea", IP4300Regi2ndTbl, 
		  IP4300BJL2ndTbl, IP4300Box2ndTbl,REGI_IP4300_2NDCNT , PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
	  { "IP4300regi3_dialog", "IP4300regi3_drawingarea", IP4300Regi3rdTbl, 
		  IP4300BJL3rdTbl, IP4300Box3rdTbl, REGI_IP4300_3RDCNT, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_MP_600,
	{ { "IP4300regi1_dialog", "IP4300regi1_drawingarea", IP4300Regi1stTbl,
		IP4300BJL1stTbl, IP4300Box1stTbl, REGI_IP4300_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "IP4300regi2_dialog", "IP4300regi2_drawingarea", IP4300Regi2ndTbl, 
		  IP4300BJL2ndTbl, IP4300Box2ndTbl,REGI_IP4300_2NDCNT , PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
	  { "IP4300regi3_dialog", "IP4300regi3_drawingarea", IP4300Regi3rdTbl, 
		  IP4300BJL3rdTbl, IP4300Box3rdTbl, REGI_IP4300_3RDCNT, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2006/10/11
	{ IDM_IP_90,
	{ { "IP90regi_dialog", "IP90regi_drawingarea", IP90Regi1stTbl,
		IP90BJL1stTbl, IP90Box1stTbl, REGI_IP90_1STCNT, PORT|BIGAREA_TYPE3 },
	  { 0, 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2006/07/06
	{ IDM_IP_2500,
	{ { "IP2200regi_dialog", "IP2200regi_drawingarea", IP2200Regi1stTbl,
		IP2200BJL1stTbl, IP2200Box1stTbl, REGI_IP2200_1STCNT, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2006/07/06
	{ IDM_IP_1800,
	{ { "IP2200regi_dialog", "IP2200regi_drawingarea", IP2200Regi1stTbl,
		IP2200BJL1stTbl, IP2200Box1stTbl, REGI_IP2200_1STCNT, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2007/05/31
	{ IDM_MP_140,
	{ { "IP2200regi_dialog", "IP2200regi_drawingarea", IP2200Regi1stTbl,
		MP160BJL1stTbl, IP2200Box1stTbl, REGI_IP2200_1STCNT, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2007/06/25
	{ IDM_MP_210,
	{ { "IP2200regi_dialog", "IP2200regi_drawingarea", MP210Regi1stTbl,
		MP210BJL1stTbl, MP210Box1stTbl, REGI_MP210_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "TYPE_G_regi2_dialog", "TYPE_G_regi2_drawingarea1", MP210Regi2ndTbl,
		MP210BJL2ndTbl, MP210Box2ndTbl, REGI_MP210_2NDCNT, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2007/06/25
	{ IDM_IP_3500,
	{ { "IP3300regi1_dialog", "IP3300regi1_drawingarea", IP3300Regi1stTbl,
		IP3300BJL1stTbl, IP3300Box1stTbl, REGI_IP3300_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "IP3300regi2_dialog", "IP3300regi2_drawingarea", IP3300Regi2ndTbl, 
		  IP3300BJL2ndTbl, IP3300Box2ndTbl,REGI_IP3300_2NDCNT , PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
		{ 0, 0, 0, 0, 0, 0, 0 },
   		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_MP_520,
	{ { "IP3300regi1_dialog", "IP3300regi1_drawingarea", IP3300Regi1stTbl,
		IP3300BJL1stTbl, IP3300Box1stTbl, REGI_IP3300_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "IP3300regi2_dialog", "IP3300regi2_drawingarea", IP3300Regi2ndTbl, 
		  IP3300BJL2ndTbl, IP3300Box2ndTbl,REGI_IP3300_2NDCNT , PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
		{ 0, 0, 0, 0, 0, 0, 0 },
   		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2007/06/25
	{ IDM_IP_4500,
	{ { "TYPE_F_regi1_dialog", "TYPE_F_regi1_drawingarea1", TYPE_F_Regi1stTbl,
		TYPE_F_BJL1stTbl, TYPE_F_Box1stTbl, REGI_TYPE_F_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "TYPE_F_regi2_dialog", "TYPE_F_regi2_drawingarea1", TYPE_F_Regi2ndTbl,
		TYPE_F_BJL2ndTbl, TYPE_F_Box2ndTbl, REGI_TYPE_F_2NDCNT, PORT|BIGAREA_TYPE3 },
	  { "TYPE_F_regi3_dialog", "TYPE_F_regi3_drawingarea1", TYPE_F_Regi3rdTbl,
		TYPE_F_BJL3rdTbl, TYPE_F_Box3rdTbl, REGI_TYPE_F_3RDCNT, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
	  { "TYPE_F_regi4_dialog", "TYPE_F_regi4_drawingarea1", TYPE_F_Regi4thTbl,
		TYPE_F_BJL4thTbl, TYPE_F_Box4thTbl, REGI_TYPE_F_4THCNT, PORT|BIGAREA_TYPE3 },
	} },
	{ IDM_MP_610,
	{ { "TYPE_F_regi1_dialog", "TYPE_F_regi1_drawingarea1", TYPE_F_Regi1stTbl,
		TYPE_F_BJL1stTbl, TYPE_F_Box1stTbl, REGI_TYPE_F_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "TYPE_F_regi2_dialog", "TYPE_F_regi2_drawingarea1", TYPE_F_Regi2ndTbl,
		TYPE_F_BJL2ndTbl, TYPE_F_Box2ndTbl, REGI_TYPE_F_2NDCNT, PORT|BIGAREA_TYPE3 },
	  { "TYPE_F_regi3_dialog", "TYPE_F_regi3_drawingarea1", TYPE_F_Regi3rdTbl,
		TYPE_F_BJL3rdTbl, TYPE_F_Box3rdTbl, REGI_TYPE_F_3RDCNT, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
	  { "TYPE_F_regi4_dialog", "TYPE_F_regi4_drawingarea1", TYPE_F_Regi4thTbl,
		TYPE_F_BJL4thTbl, TYPE_F_Box4thTbl, REGI_TYPE_F_4THCNT, PORT|BIGAREA_TYPE3 },
	} },

};


//#define BJTESTFILEPATH	"/usr/local/share/printui"
#define BJTESTFILEPATH	PACKAGE_DATA_DIR

#define NOZZLEPATTERN	0
#define REGIPATTERN1		1
#define REGIPATTERN2		2

char *IP2500TestPatternTbl[2] = {		// 2006/05/30
		"nozl_ip2500.utl", 		/* NozzleCheck Pattern */
		"regi_ip2500.utl"		/* Regi Pattern */
};

char *IP1800TestPatternTbl[2] = {		// 2006/05/30
		"nozl_ip1800.utl",	 	/* NozzleCheck Pattern */
		"regi_ip1800.utl"		/* Regi Pattern */
};



typedef struct{
	char *ModelName;
	char **TestPatternTbl;

}TESTPATTERNINFO;


TESTPATTERNINFO TestPatternInfo[] =

{
  { IDM_IP_2500, IP2500TestPatternTbl },
  { IDM_IP_1800, IP1800TestPatternTbl },

};

#define BSCCREGFORMAT	"%6s%c%02d\x0a"	
#define BSCCFILEPATH	"/usr/lib/bjlib/"
#define BSCCREGLEN		9

#define BSCCID_REG	0
#define BSCC_TAG "bscc"
#define BSCCREGTAG		"REG:"

typedef struct{
		int reg_num;
		int *reg_value_index;
		int *reg_str_index;
		char** pBJLTbl;
}BSCCREGTBL,*PBSCCREGTBL;


typedef struct{
	char*		ModelName;
	char*		bscc_file;	
	BSCCREGTBL	tBsccRegTbl[2];	

}BSCCREGINFO;

/* IP2200 IP2500 */
int IP2200_REG_INDEX[REGI_IP2200_1STCNT_BSCC] =
{ 5 };

int IP2200_REG_STR_INDEX[REGI_IP2200_1STCNT_BSCC] =
{ 5 };

BSCCREGINFO BsccRegInfo[] =
{
	/* IP2200 */
	{ IDM_IP_2200, "cifip2200.bscc",
	  { { REGI_IP2200_1STCNT_BSCC, IP2200_REG_INDEX, IP2200_REG_STR_INDEX,
		  IP2200BJL1stTbl },
		{ 0, 0, 0 } }
	},
	/* IP2500 */
	{ IDM_IP_2500, "cifip2500.bscc",
	  { { REGI_IP2200_1STCNT_BSCC, IP2200_REG_INDEX, IP2200_REG_STR_INDEX,
		  IP2200BJL1stTbl },
		{ 0, 0, 0 } }
	},
	/* IP1800 */
	{ IDM_IP_1800, "cifip1800.bscc",
	  { { REGI_IP2200_1STCNT_BSCC, IP2200_REG_INDEX, IP2200_REG_STR_INDEX,
		  IP2200BJL1stTbl },
		{ 0, 0, 0 } }
	},
};
	  
typedef struct{
	char* ModelName;
	int   GroupFlag;
	char* InkName[3];
	char* RefMsg[3];
}INKMSGINFO;

INKMSGINFO InkMsgInfo[] =
{
	/* IP3300 */																// 2006/05/16
	{ IDM_IP_3300, 0,
		{"util_ink_all_1","util_ink_black_2","util_ink_color_7"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* MP510 */																// 2006/05/16
	{ IDM_MP_510, 0,
		{"util_ink_all_1","util_ink_black_2","util_ink_color_7"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* IP4300 */																// 2006/05/16
	{ IDM_IP_4300, 0,
		{"util_ink_all_1","util_ink_black_2","util_ink_color_5"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* MP600 */																// 2006/05/16
	{ IDM_MP_600, 0,
		{"util_ink_all_1","util_ink_black_2","util_ink_color_5"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* IP90 */																// 2006/10/12
	{ IDM_IP_90, 0,
		{"util_ink_all_1","util_ink_black_0","util_ink_color_0"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* IP3500 */															// 2007/06/26
	{ IDM_IP_3500, 0,
		{"util_ink_all_1","util_ink_black_2","util_ink_color_7"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* MP520 */																// 2007/06/26
	{ IDM_MP_520, 0,
		{"util_ink_all_1","util_ink_black_2","util_ink_color_7"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* IP4500 */															// 2007/06/26
	{ IDM_IP_4500, 0,
		{"util_ink_all_1","util_ink_black_2","util_ink_color_5"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* MP610 */																// 2006/05/16
	{ IDM_MP_610, 0,
		{"util_ink_all_1","util_ink_black_2","util_ink_color_5"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
};

// SetConfig Info
#define SETCONFIG_DRY_3		1
#define SETCONFIG_DRY_5		2
#define SETCONFIG_ABRASION	4
#define SETCONFIG_MANHEAD	8


#define CONFIG_P560I (SETCONFIG_DRY_5|SETCONFIG_ABRASION)
#define CONFIG_P860I (SETCONFIG_DRY_5|SETCONFIG_ABRASION|SETCONFIG_MANHEAD)
#define CONFIG_P990I (SETCONFIG_DRY_3|SETCONFIG_ABRASION|SETCONFIG_MANHEAD)
#define CONFIG_IP1000 (SETCONFIG_DRY_5)
#define CONFIG_TYPE_A (SETCONFIG_DRY_5|SETCONFIG_ABRASION)

typedef struct{
	char* ModelName;
	short ConfigFlag;
}SETCONFIGINFO;

SETCONFIGINFO SetConfigInfo[] = 
{
	{ IDM_MP_160,     CONFIG_IP1000  }, // 2006/05/30
	{ IDM_IP_3300,    CONFIG_IP1000  },
	{ IDM_MP_510,     CONFIG_IP1000  },
	{ IDM_IP_4300,    CONFIG_P860I  },
	{ IDM_MP_600,     CONFIG_P860I  },
	{ IDM_IP_90,      CONFIG_IP1000  }, // 2006/10/12
	{ IDM_IP_2500,    CONFIG_IP1000  },	// 2006/07/06
	{ IDM_IP_1800,    CONFIG_IP1000  },	// 2006/07/06
	{ IDM_MP_140,     CONFIG_IP1000  }, // 2007/05/31
	{ IDM_MP_210,     CONFIG_IP1000  }, // 2007/06/19
	{ IDM_IP_3500,    CONFIG_IP1000  }, // 2007/06/27
	{ IDM_MP_520,     CONFIG_TYPE_A  }, // 2007/06/27
	{ IDM_IP_4500,    CONFIG_P860I   }, // 2007/06/27
	{ IDM_MP_610,     CONFIG_P860I   }, // 2007/06/27
};


// CheckPattern Info
#define OK_CHECK_PATTN 0
#define NG_CHECK_PATTN 1

//#define CHECKPATTERNPATH	"/usr/local/share/printui"
#define CHECKPATTERNPATH	PACKAGE_DATA_DIR

typedef struct{
	char* ModelName;
	char* pattn_filename[2];
}PATTERNCHECKINFO;

PATTERNCHECKINFO PatternCheckInfo[] = 
{
	{ IDM_MP_160,  { "okptn_mp160.xpm", 		// 2006/06/22
					 "ngptn_mp160.xpm" } },
	{ IDM_IP_3300, { "okptn_ip3300.xpm", 
					 "ngptn_ip3300.xpm" } },
	{ IDM_MP_510,  { "okptn_mp510.xpm", 
					 "ngptn_mp510.xpm" } },
	{ IDM_IP_4300, { "okptn_ip4300.xpm", 
					 "ngptn_ip4300.xpm" } },
	{ IDM_MP_600,  { "okptn_mp600.xpm", 
					 "ngptn_mp600.xpm" } },
	{ IDM_IP_90,  { "okptn_ip90.xpm", 		// 2006/06/22
					 "ngptn_ip90.xpm" } },
	{ IDM_IP_2500, { "okptn_ip2500.xpm", 		// 2006/07/06
					 "ngptn_ip2500.xpm" } },
	{ IDM_IP_1800, { "okptn_ip1800.xpm", 		// 2006/07/06
					 "ngptn_ip1800.xpm" } },
	{ IDM_MP_140,  { "okptn_mp140.xpm", 		// 2007/05/31
					 "ngptn_mp140.xpm" } },
	{ IDM_MP_210,  { "okptn_mp210.xpm", 		// 2007/06/19
					 "ngptn_mp210.xpm" } },
	{ IDM_IP_3500,  { "okptn_ip3500.xpm", 		// 2007/06/28
					 "ngptn_ip3500.xpm" } },
	{ IDM_MP_520,  { "okptn_mp520.xpm", 		// 2007/06/28
					 "ngptn_mp520.xpm" } },
	{ IDM_IP_4500,  { "okptn_ip4500.xpm", 		// 2007/06/28
					 "ngptn_ip4500.xpm" } },
	{ IDM_MP_610,  { "okptn_mp610.xpm", 		// 2007/06/28
					 "ngptn_mp610.xpm" } },
};


char* DryLevel3NameList[4] = 
	{ "drylevel3_radiobutton1",		// Default
	  "drylevel3_radiobutton1", 
	  "drylevel3_radiobutton2",
	  "drylevel3_radiobutton3" 
	};

char* DryLevel5NameList[6] = 
	{ "drylevel5_radiobutton3", 	// Default
	  "drylevel5_radiobutton1", 
	  "drylevel5_radiobutton2",
	  "drylevel5_radiobutton3", 
	  "drylevel5_radiobutton4",
	  "drylevel5_radiobutton5"
	};


// Ink Cartridge Settings

#define INKCRTRG_DIALOG_TYPE	0
#define INKCRTRG_NUM_MAX		3

typedef struct{
	int   index_num;
	int   index_default;
	char* type[INKCRTRG_NUM_MAX];
	char* info[INKCRTRG_NUM_MAX];
	short nValue[INKCRTRG_NUM_MAX];
}INKCRTRGMSGINFO;

INKCRTRGMSGINFO InkCartridgeInfo = 
{ 
	3, 2, { "util_ink_cartridge_1", 
	   		"util_ink_cartridge_2", 
		    "util_ink_cartridge_3" },
 		  { "utility_message_55",
		   	"utility_message_56",
			"utility_message_57" },
 		  { CND_CARTRIDGE_COLOR,
		   	CND_CARTRIDGE_BK,
			CND_CARTRIDGE_BK_COLOR }
};

