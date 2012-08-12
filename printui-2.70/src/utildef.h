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
#ifndef _UTILDEF_H_
#define _UTILDEF_H_

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
	} regi[3];					
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





#define	IDM_BJC_F850		"BJF850"	
#define	REGI_F850_1STCNT	6           
#define	REGI_F850_2NDCNT	0           
#define	REGI_EDITMAX		14           


CTRLITEM F850Regi1stTbl[REGI_F850_1STCNT] = {

	{ "regi_spinbutton1", 0, -3, 7 },	
	{ "regi_spinbutton2", 0, -3, 7 },   
	{ "regi_spinbutton3", 0, -3, 7 },   
	{ "regi_spinbutton4", 0, -3, 7 },   
	{ "regi_spinbutton5", 0, -3, 7 },   
	{ "regi_spinbutton6", 0, -3, 3 },   
};


char *F850BJL1stTbl[REGI_F850_1STCNT+1] = {
	"X1200A",			
	"X1200C",           
	"X1200E",           
	"X1200I",           
	"X1200K",           
	"X1200L",           
	"X1200G"
};


BOXINF F850Box1stTbl[REGI_F850_1STCNT] = {

	{ 11, 9, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0x0000, 0x0000, 0x0000, 0 },	   
	{ 28, 9, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0x0000, 0xffff, 0xffff, 0 },    
	{ 45, 9, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0xffff, 0x0000, 0xffff, 0 },    
	{ 62, 9, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0x8000, 0xffff, 0xffff, 0 },    
	{ 79, 9, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0xffff, 0x8000, 0xffff, 0 },    
	{ 45,90, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0x8000, 0x8000, 0x8000, 0 }     
};




#define	IDM_BJC_F860		"BJF860"	
#define	REGI_F860_1STCNT	6           
#define	REGI_F860_2NDCNT	0           


CTRLITEM F860Regi1stTbl[REGI_F860_1STCNT] = {

	{ "regi_spinbutton1", 0, -3, 7 },	
	{ "regi_spinbutton2", 0, -3, 7 },   
	{ "regi_spinbutton3", 0, -3, 7 },   
	{ "regi_spinbutton4", 0, -3, 7 },   
	{ "regi_spinbutton5", 0, -3, 7 },   
	{ "regi_spinbutton6", 0, -5, 5 },   
};


char *F860BJL1stTbl[REGI_F860_1STCNT+1] = {
	"X1200A",			
	"X1200C",           
	"X1200E",           
	"X1200I",           
	"X1200K",           
	"X2400L",           
	"X1200G"
};


BOXINF F860Box1stTbl[REGI_F860_1STCNT] = {

	{ 11, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0x0000, 0x0000, 0 },	
	{ 28, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0xffff, 0xffff, 0 },    
	{ 45, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x0000, 0xffff, 0 },    
	{ 62, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x8000, 0xffff, 0xffff, 0 },    
	{ 79, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x8000, 0xffff, 0 },    
	{ 45,75, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x8000, 0x8000, 0x8000, 0 }	    
};




#define	IDM_BJC_F870		"BJF870"	
#define	REGI_F870_1STCNT	6           
#define	REGI_F870_2NDCNT	0           


CTRLITEM F870Regi1stTbl[REGI_F870_1STCNT] = {

	{ "regi_spinbutton1", 0, -3, 7 },	
	{ "regi_spinbutton2", 0, -3, 7 },   
	{ "regi_spinbutton3", 0, -3, 7 },   
	{ "regi_spinbutton4", 0, -3, 7 },   
	{ "regi_spinbutton5", 0, -3, 7 },   
	{ "regi_spinbutton6", 0, -5, 5 },   
};


char *F870BJL1stTbl[REGI_F870_1STCNT+1] = {
	"X1200A",		
	"X1200C",       
	"X1200E",       
	"X1200I",       
	"X1200K",       
	"X2400L",       
	"X1200G"		
};


BOXINF F870Box1stTbl[REGI_F870_1STCNT] = {

	{ 11, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0x0000, 0x0000, 0 },	
	{ 28, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0xffff, 0xffff, 0 },    
	{ 45, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x0000, 0xffff, 0 },    
	{ 62, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x8000, 0xffff, 0xffff, 0 },    
	{ 79, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x8000, 0xffff, 0 },    
	{ 45,75, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x8000, 0x8000, 0x8000, 0 }	    
};




#define	IDM_BJC_F360		"BJF360"	
#define	REGI_F360_1STCNT	2			
#define	REGI_F360_2NDCNT	2           


CTRLITEM F360Regi1stTbl[REGI_F360_1STCNT] = {

	{ "F360regi1_spinbutton1", 0, -7, 7 },	
	{ "F360regi1_spinbutton2", 0, -7, 7 }   
};


CTRLITEM F360Regi2ndTbl[REGI_F360_2NDCNT] = {

	{ "F360regi2_spinbutton1", 0, -1, 1 },	
	{ "F360regi2_spinbutton2", 0, -1, 1 }	
};


char *F360BJL1stTbl[REGI_F360_1STCNT] = {
	"X0720B",		
	"X0720C"        
};


char *F360BJL2ndTbl[REGI_F360_2NDCNT] = {
	"X1440B",		
	"X1440C"        
};


BOXINF F360Box1stTbl[REGI_F360_1STCNT] = {

	{ 6, 20, 2, 3, 6, 0, 1, 2, -2, -5, 6, 10, 0x0000, 0x0000, 0x0000, 0 },		
	{ 6, 46, 2, 3, 6, 0, 1, 2, -2, -5, 6, 10, 0x0000, 0x0000, 0x0000, 0 }  	
};


BOXINF F360Box2ndTbl[REGI_F360_2NDCNT] = {

	{ 40, 20, 2, 3, 6, 0, 1, 2, -2, -5, 6, 10, 0x0000, 0x0000, 0x0000, 0 },	
	{ 40, 46, 2, 3, 6, 0, 1, 2, -2, -5, 6, 10, 0x0000, 0x0000, 0x0000, 0 }     
};




#define	IDM_BJC_S600		"BJS600"	
#define	IDM_BJC_S630		"BJS630"	
#define	IDM_BJC_S6300		"BJS6300"	
#define	REGI_S600_1STCNT	6			
#define	REGI_S600_2NDCNT	2           


CTRLITEM S600Regi1stTbl[REGI_S600_1STCNT] = {

	{ "S600regi1_spinbutton1", 0, -3, 7 },	
	{ "S600regi1_spinbutton2", 0, -3, 7 },  
	{ "S600regi1_spinbutton3", 0, -3, 7 },	
	{ "S600regi1_spinbutton4", 0, -5, 5 },  
	{ "S600regi1_spinbutton5", 0, -5, 5 },	
	{ "S600regi1_spinbutton6", 0, -5, 5 }   
};


CTRLITEM S600Regi2ndTbl[REGI_S600_2NDCNT] = {

	{ "S600regi2_spinbutton1", 0, -3, 3 },	
	{ "S600regi2_spinbutton2", 0, -3, 3 }	
};


char *S600BJL1stTbl[REGI_S600_1STCNT+1] = {
	"X1200A",		
	"X1200B",		
	"X1200C",		
	"X1200F",		
	"X1200G",		
	"X1200E",		
	"X1200D"		
};


char *S600BJL2ndTbl[REGI_S600_2NDCNT] = {
	"A",			
	"B"				
};


BOXINF S600Box1stTbl[REGI_S600_1STCNT] = {

	{ 26,  8, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0x0000, 0x0000, 0x0000, 0 },	
	{ 53,  8, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0x0000, 0xffff, 0xffff, 0 },	
	{ 80,  8, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0xffff, 0x0000, 0xffff, 0 },	
	{ 26, 91, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0x0000, 0x0000, 0x0000, 0 },	
	{ 53, 91, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0x0000, 0xffff, 0xffff, 0 },	
	{ 80, 91, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0x0000, 0x0000, 0x0000, 0 }	
};


BOXINF S600Box2ndTbl[REGI_S600_2NDCNT] = {

	{ 25, 18, 16, 3, 21, 1, 1, 0, -2, -5, 19, 10, 0x8000, 0x8000, 0x8000, 0 },	
	{ 69, 20, 16, 6, 21, 1, 1, 0, -2, -8, 19, 17, 0x8000, 0x8000, 0x8000, 0 }	
};




// Added '01.11.05

#define	IDM_BJC_F900		"BJF900"	
#define	IDM_BJC_F9000		"BJF9000"	
#define	REGI_F900_1STCNT	6           
#define	REGI_F900_2NDCNT	0           


CTRLITEM F900Regi1stTbl[REGI_F900_1STCNT] = {

	{ "F900regi_spinbutton1", 0, -3, 7 },	
	{ "F900regi_spinbutton2", 0, -3, 7 },   
	{ "F900regi_spinbutton3", 0, -3, 7 },   
	{ "F900regi_spinbutton4", 0, -3, 7 },   
	{ "F900regi_spinbutton5", 0, -3, 7 },   
	{ "F900regi_spinbutton6", 0, -5, 5 },   
};


char *F900BJL1stTbl[REGI_F900_1STCNT+1] = {
	"X1200A",			
	"X1200C",           
	"X1200E",           
	"X1200I",           
	"X1200K",           
	"X2400L",           
	"X1200G"
};


BOXINF F900Box1stTbl[REGI_F900_1STCNT] = {

	{ 12, 6, 13, 3, 7, 1, 1, 0, -2, -5, 16, 9, 0x0000, 0x0000, 0x0000, 0 },	
	{ 32, 6, 13, 3, 7, 1, 1, 0, -2, -5, 16, 9, 0x0000, 0xffff, 0xffff, 0 },    
	{ 52, 6, 13, 3, 7, 1, 1, 0, -2, -5, 16, 9, 0xffff, 0x0000, 0xffff, 0 },    
	{ 72, 6, 13, 3, 7, 1, 1, 0, -2, -5, 16, 9, 0x8000, 0xffff, 0xffff, 0 },    
	{ 92, 6, 13, 3, 7, 1, 1, 0, -2, -5, 16, 9, 0xffff, 0x8000, 0xffff, 0 },    
	{ 71,88, 10, 3, 7, 1, 1, 0, -2, -5, 13, 9, 0x8000, 0x8000, 0x8000, 0 }	    

};



// Added '01.11.05
#define	IDM_BJC_S300		"BJS300"
#define	IDM_BJC_S500		"BJS500"


// Ver.2.2 start

// PIXUS 950i

#define IDM_PIXUS_950I		"PIXUS950I"
#define REGI_PX950I_1STCNT	8
#define REGI_PX950I_2NDCNT	0


CTRLITEM PX950IRegi1stTbl[REGI_PX950I_1STCNT] = {

	{ "PX950Iregi_spinbutton1", 0, -3, 7 },	
	{ "PX950Iregi_spinbutton2", 0, -3, 7 },   
	{ "PX950Iregi_spinbutton3", 0, -3, 7 },   
	{ "PX950Iregi_spinbutton4", 0, -3, 7 },   
	{ "PX950Iregi_spinbutton5", 0, -3, 7 },   
	{ "PX950Iregi_spinbutton6", 0, -5, 5 },   
	{ "PX950Iregi_spinbutton7", 0, -5, 5 },   
	{ "PX950Iregi_spinbutton8", 0, -5, 5 },   
};


char *PX950IBJL1stTbl[REGI_PX950I_1STCNT+4] = {
	"X1200A",
	"X1200C",
	"X1200E",
	"X1200I",
	"X1200K",
	"X2400L",
	"X2400M",
	"X2400N",
	"X1200G",
	"X2400O",
	"X2400P",
	"X2400Q"
};


BOXINF PX950IBox1stTbl[REGI_PX950I_1STCNT] = {

	{ 11, 5, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0x0000, 0x0000, 0 },	
	{ 28, 5, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0xffff, 0xffff, 0 },    
	{ 45, 5, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x0000, 0xffff, 0 },    
	{ 62, 5, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x8000, 0xffff, 0xffff, 0 },    
	{ 79, 5, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x8000, 0xffff, 0 },    
	{ 28,74,  9, 2, 6, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0x8000, 0x8000, 0 },
	{ 45,74,  9, 2, 6, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 62,74,  9, 2, 6, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff, 0 }

};

// PIXUS 850i

#define IDM_PIXUS_850I		"PIXUS850I"
#define REGI_PX850I_1STCNT	11
#define REGI_PX850I_2NDCNT	2


CTRLITEM PX850IRegi1stTbl[REGI_PX850I_1STCNT] = {

	{ "PX850Iregi1_spinbutton1", 0, -3, 7 },	
	{ "PX850Iregi1_spinbutton2", 0, -3, 7 },   
	{ "PX850Iregi1_spinbutton3", 0, -3, 7 },   
	{ "PX850Iregi1_spinbutton4", 0, -3, 7 },   
	{ "PX850Iregi1_spinbutton5", 0, -3, 7 },   
	{ "PX850Iregi1_spinbutton6", 0, -5, 5 },   
	{ "PX850Iregi1_spinbutton7", 0, -5, 5 },   
	{ "PX850Iregi1_spinbutton8", 0, -5, 5 },   
	{ "PX850Iregi1_spinbutton9", 0, -5, 5 },   
	{ "PX850Iregi1_spinbutton10",0, -5, 5 },   
	{ "PX850Iregi1_spinbutton11",0, -5, 5 },   

};


CTRLITEM PX850IRegi2ndTbl[REGI_PX850I_2NDCNT] = {

	{ "PX850Iregi2_spinbutton1", 0, -3, 3 },	
	{ "PX850Iregi2_spinbutton2", 0, -3, 3 }

};


char *PX850IBJL1stTbl[REGI_PX850I_1STCNT+2] = {
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
	"X1200D",	//  magenda
	"X1200M"	//  small cyan
	
};



char *PX850IBJL2ndTbl[REGI_PX850I_2NDCNT] = {
	"A",
	"B"

};


BOXINF PX850IBox1stTbl[REGI_PX850I_1STCNT] = {

	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },	
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },    
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff, 0 },    
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },    
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },    
	{ 25, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0x8000, 0x8000, 0 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 53, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0x8000, 0x8000, 0 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 95, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 }

};



BOXINF PX850IBox2ndTbl[REGI_PX850I_2NDCNT] = {

	{ 29, 17, 20,  2, 17, 1, 1, 0, -2, -5, 24,  9, 0x8000, 0x8000, 0x8000, 0 },
	{ 79, 17, 20,  4, 17, 1, 1, 0, -2, -9, 24, 18, 0x8000, 0x8000, 0x8000, 0 }
	
};



// PIXUS 550i

#define IDM_PIXUS_550I		"PIXUS550I"
#define REGI_PX550I_1STCNT	6
#define REGI_PX550I_2NDCNT	0


CTRLITEM PX550IRegi1stTbl[REGI_PX550I_1STCNT] = {

	{ "PX550Iregi_spinbutton1", 0, -3, 7 },	
	{ "PX550Iregi_spinbutton2", 0, -3, 7 },   
	{ "PX550Iregi_spinbutton3", 0, -3, 7 },   
	{ "PX550Iregi_spinbutton4", 0, -5, 5 },   
	{ "PX550Iregi_spinbutton5", 0, -5, 5 },   
	{ "PX550Iregi_spinbutton6", 0, -5, 5 },   

};


char *PX550IBJL1stTbl[REGI_PX550I_1STCNT+1] = {
	"X1200A",
	"X1200B",
	"X1200C",
	"X1200F",
	"X1200G",
	"X1200E",
	"X1200D" 

};


BOXINF PX550IBox1stTbl[REGI_PX550I_1STCNT] = {

	{ 19,  9, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0x0000, 0x0000, 0x0000, 0 },	
	{ 54,  9, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0x0000, 0xffff, 0xffff, 0 },    
	{ 89,  9, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0xffff, 0x0000, 0xffff, 0 },    
	{ 19, 93, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0x8000, 0x8000, 0x8000, 0 },    
	{ 54, 93, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0x0000, 0xffff, 0xffff, 0 },    
	{ 89, 93, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0x8000, 0x8000, 0x8000, 0 }

};

/* I250 */
#define IDM_I250	"I250"
#define REGI_I250_1STCNT	6


/* I255 */
#define IDM_I255	"I255"
#define REGI_I255_1STCNT	6


/* PIXUS 560i */
#define IDM_PIXUS_560I		"PIXUS560I"

/* PIXUS 860i */
#define IDM_PIXUS_860I		"PIXUS860I"
#define REGI_PX860I_1STCNT	12
#define REGI_PX860I_2NDCNT	2


CTRLITEM PX860IRegi1stTbl[REGI_PX860I_1STCNT] = {

	{ "PX860Iregi1_spinbutton1", 0, -3, 7 },	
	{ "PX860Iregi1_spinbutton2", 0, -3, 7 },   
	{ "PX860Iregi1_spinbutton3", 0, -3, 7 },   
	{ "PX860Iregi1_spinbutton4", 0, -3, 7 },   
	{ "PX860Iregi1_spinbutton5", 0, -3, 7 },   
	{ "PX860Iregi1_spinbutton6", 0, -3, 7 },   
	{ "PX860Iregi1_spinbutton7", 0, -5, 5 },   
	{ "PX860Iregi1_spinbutton8", 0, -5, 5 },   
	{ "PX860Iregi1_spinbutton9", 0, -5, 5 },   
	{ "PX860Iregi1_spinbutton10",0, -5, 5 },   
	{ "PX860Iregi1_spinbutton11",0, -5, 5 },   
	{ "PX860Iregi1_spinbutton12",0, -5, 5 },   


};


CTRLITEM PX860IRegi2ndTbl[REGI_PX860I_2NDCNT] = {

	{ "PX860Iregi2_spinbutton1", 0, -3, 3 },	
	{ "PX860Iregi2_spinbutton2", 0, -3, 3 }

};


char *PX860IBJL1stTbl[REGI_PX860I_1STCNT+2] = {
	"X1200A",
	"X1200B",
	"X1200C",
	"X1200E",
	"X1200F",
	"X1200N",
	"X1200J",
	"X1200K", 
	"X1200G",
	"X1200L",
	"X1200H",
	"X1200I",
	"X1200D",
	"X1200M"	
	
};



char *PX860IBJL2ndTbl[REGI_PX860I_2NDCNT] = {
	"A",
	"B"

};


BOXINF PX860IBox1stTbl[REGI_PX860I_1STCNT] = {

	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },	
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },    
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff, 0 },    
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },    
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },    
	{ 95,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 25, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 53, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 95, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 }

};



BOXINF PX860IBox2ndTbl[REGI_PX860I_2NDCNT] = {

	{ 29, 17, 20,  2, 17, 1, 1, 0, -2, -5, 24,  9, 0x8000, 0x8000, 0x8000, 0 },
	{ 79, 17, 20,  4, 17, 1, 1, 0, -2, -9, 24, 18, 0x8000, 0x8000, 0x8000, 0 }
	
};

/* PIXUS 990i */
#define IDM_PIXUS_990I		"PIXUS990I"
#define REGI_PX990I_1STCNT	10
#define REGI_PX990I_2NDCNT	0
#define REGI_PX990I_3RDCNT	4


CTRLITEM PX990IRegi1stTbl[REGI_PX990I_1STCNT] = {

	{ "PX990Iregi_spinbutton1", 0, -3, 7 },	
	{ "PX990Iregi_spinbutton2", 0, -3, 7 },   
	{ "PX990Iregi_spinbutton3", 0, -3, 7 },   
	{ "PX990Iregi_spinbutton4", 0, -3, 7 },   
	{ "PX990Iregi_spinbutton5", 0, -3, 7 },   
	{ "PX990Iregi_spinbutton6", 0, -3, 7 },   
	{ "PX990Iregi_spinbutton7", 0, -5, 5 },   
	{ "PX990Iregi_spinbutton8", 0, -5, 5 },   
	{ "PX990Iregi_spinbutton9", 0, -5, 5 },   
	{ "PX990Iregi_spinbutton10", 0, -5, 5 }

};


char *PX990IBJL1stTbl[REGI_PX990I_1STCNT] = {
	"X1200A",
	"X1200C",
	"X1200E",
	"X1200F",
	"X1200G",
	"X1200H",
	"X2400I", 
	"X2400K", 
	"X2400M", 
	"X2400P"
};


BOXINF PX990IBox1stTbl[REGI_PX990I_1STCNT] = {
	{ 30, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0x0000, 0x0000, 0 },	
	{ 44, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0xffff, 0xffff, 0 },    
	{ 58, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x0000, 0xffff, 0 },    
	{ 72, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x8000, 0xffff, 0xffff, 0 },    
	{ 86, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x8000, 0xffff, 0 },    
	{100, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x8000, 0x0000, 0 },
	{ 44,100, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 58,100, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 72,100, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x0000, 0xffff, 0 },
	{ 86,100, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0x0000, 0x0000, 0 }
};


CTRLITEM PX990IRegi3rdTbl[REGI_PX990I_3RDCNT] = {

	{ "PX990Iauto_regi_spinbutton1", 0, -3, 7 },	
	{ "PX990Iauto_regi_spinbutton2", 0, -3, 7 },   
	{ "PX990Iauto_regi_spinbutton3", 0, -3, 7 },   
	{ "PX990Iauto_regi_spinbutton4", 0, -5, 5 }
};


char *PX990IBJL3rdTbl[REGI_PX990I_3RDCNT] = {
	"X1200E",
	"X1200G",
	"X1200H",
	"X2400M"
};


BOXINF PX990IBox3rdTbl[REGI_PX990I_3RDCNT] = {

	{ 46, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x0000, 0xffff, 0 },    
	{ 60, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x8000, 0xffff, 0 },    
	{ 74, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x8000, 0x0000, 0 },
	{ 60,100, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x0000, 0xffff, 0 },
};

/* PIXUS iP3100 */
// Under construction start

#define IDM_IP_3100		"PIXUSIP3100"

// Under construction End

/* PIXUS iP4100 */
// Under construction start
#define IDM_IP_4100		"PIXUSIP4100"

/* PIXUS iP8600 */
#define IDM_IP_8600		"PIXUSIP8600"
#define REGI_IP8600_1STCNT	11
#define REGI_IP8600_2NDCNT	0


CTRLITEM IP8600Regi1stTbl[REGI_IP8600_1STCNT] = {

	{ "ip8600regi_spinbutton1",  0, -3, 7 },	
	{ "ip8600regi_spinbutton2",  0, -3, 7 },   
	{ "ip8600regi_spinbutton3",  0, -3, 7 },   
	{ "ip8600regi_spinbutton4",  0, -3, 7 },   
	{ "ip8600regi_spinbutton5",  0, -3, 7 },   
	{ "ip8600regi_spinbutton6",  0, -3, 7 },   
	{ "ip8600regi_spinbutton7",  0, -3, 7 },   
	{ "ip8600regi_spinbutton8",  0, -5, 5 },   
	{ "ip8600regi_spinbutton9",  0, -5, 5 },   
	{ "ip8600regi_spinbutton10", 0, -5, 5 },   
	{ "ip8600regi_spinbutton11", 0, -5, 5 }

};


char *IP8600BJL1stTbl[REGI_IP8600_1STCNT] = {
	"X1200J",
	"X1200I",
	"X1200H",
	"X1200A",
	"X1200G",
	"X1200C",
	"X1200E",
	"X2400L", 
	"X2400N", 
	"X2400P", 
	"X2400W"
};


BOXINF IP8600Box1stTbl[REGI_IP8600_1STCNT] = {
	{ 10,  8, 9, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0xffff, 0x0000, 0 },	
	{ 24,  8, 9, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x8000, 0x0000, 0 },	
	{ 38,  8, 9, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x8000, 0xffff, 0 },    
	{ 52,  8, 9, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0x0000, 0x0000, 0 },    
	{ 66,  8, 9, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x8000, 0xffff, 0xffff, 0 },    
	{ 80,  8, 9, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0xffff, 0xffff, 0 },    
	{ 94,  8, 9, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x0000, 0xffff, 0 },
	{ 24, 92, 9, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 38, 92, 9, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 52, 92, 9, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x0000, 0xffff, 0 },
	{ 66, 92, 9, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0x0000, 0x0000, 0 }
};


// PIXMA IP1000

#define IDM_IP_1000		"PIXMAIP1000"
#define REGI_IP1000_1STCNT	6
#define REGI_IP1000_2NDCNT	0

char *IP1000BJL1stTbl[REGI_IP1000_1STCNT+1] = {
	"X1200A",
	"X1200B",
	"X1200C",
	"X1200J",
	"X1200K",
	"X1200G",
	"X1200D" 

};

// PIXMA IP1500

#define IDM_IP_1500		"PIXMAIP1500"
#define REGI_IP1500_1STCNT	11
#define REGI_IP1500_2NDCNT	0


char *IP1500BJL1stTbl[REGI_IP1500_1STCNT+5] = {
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
	"X1200O"
};



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


// PIXUS MP500 */
#define IDM_MP_500		"MP500"
// Under construction start

// PIXUS IP4200
#define IDM_IP_4200		"IP4200"
#define REGI_IP4200_1STCNT	10
#define REGI_IP4200_2NDCNT	6

CTRLITEM IP4200Regi1stTbl[REGI_IP4200_1STCNT] = {

	{ "IP4200regi1_spinbutton1", 0, -3, 7 },	
	{ "IP4200regi1_spinbutton2", 0, -3, 7 },   
	{ "IP4200regi1_spinbutton3", 0, -3, 7 },   
	{ "IP4200regi1_spinbutton4", 0, -3, 7 },   
	{ "IP4200regi1_spinbutton5", 0, -3, 7 },   
	{ "IP4200regi1_spinbutton6", 0, -3, 7 },   
	{ "IP4200regi1_spinbutton7", 0, -5, 5 },   
	{ "IP4200regi1_spinbutton8", 0, -5, 5 },   
	{ "IP4200regi1_spinbutton9", 0, -5, 5 },   
	{ "IP4200regi1_spinbutton10",0, -5, 5 }   

};

CTRLITEM IP4200Regi2ndTbl[REGI_IP4200_2NDCNT] = {

	{ "IP4200regi2_spinbutton1", 0, -5, 5 },   
	{ "IP4200regi2_spinbutton2", 0, -5, 5 },   
	{ "IP4200regi2_spinbutton3", 0, -5, 5 },   
	{ "IP4200regi2_spinbutton4", 0, -5, 5 },   
	{ "IP4200regi2_spinbutton5", 0, -3, 3 },   
	{ "IP4200regi2_spinbutton6", 0, -3, 3 }   

};

char *IP4200BJL1stTbl[REGI_IP4200_1STCNT+2] = {
	"A1200A",
	"A1200B",
	"A1200C",
	"A1200E",
	"A1200F",
	"A1200G",
	"A1200N",
	"A1200O",
	"A1200K",
	"A1200L",
	"A1200D",
	"A1200P"

};

char *IP4200BJL2ndTbl[REGI_IP4200_2NDCNT+1] = {
	"B1200J",
	"B1200M",
	"B1200N",
	"B1200O",
	"A",
	"B",
	"B1200P"

};

BOXINF IP4200Box1stTbl[REGI_IP4200_1STCNT] = {

	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff, 0 },
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },
	{ 95,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 53, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 }

};



BOXINF IP4200Box2ndTbl[REGI_IP4200_2NDCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 39,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0 },
	{ 53,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0 },
	{ 67,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0xffff, 0xffff, 0 },
	{ 81,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 34, 90, 16,  2, 13, 1,  1,   0,       -2,       -4,       19,          8, 0x8000, 0x8000, 0x8000, 1 },
	{ 65, 90, 16,  4, 13, 1,  1,   0,       -2,       -6,       19,         12, 0x8000, 0x8000, 0x8000, 1 }
};


// PIXUS IP6600D
#define IDM_IP_6600D		"IP6600D"
#define REGI_IP6600D_1STCNT	7
#define REGI_IP6600D_2NDCNT	3

CTRLITEM IP6600DRegi1stTbl[REGI_IP6600D_1STCNT] = {

	{ "IP6600Dregi1_spinbutton1", 0, -3, 7 },	
	{ "IP6600Dregi1_spinbutton2", 0, -3, 7 },   
	{ "IP6600Dregi1_spinbutton3", 0, -3, 7 },   
	{ "IP6600Dregi1_spinbutton4", 0, -3, 7 },   
	{ "IP6600Dregi1_spinbutton5", 0, -3, 7 },   
	{ "IP6600Dregi1_spinbutton6", 0, -5, 5 },   
	{ "IP6600Dregi1_spinbutton7", 0, -5, 5 }   

};

CTRLITEM IP6600DRegi2ndTbl[REGI_IP6600D_2NDCNT] = {

	{ "IP6600Dregi2_spinbutton1", 0, -5, 5 },   
	{ "IP6600Dregi2_spinbutton2", 0, -5, 5 },   
	{ "IP6600Dregi2_spinbutton3", 0, -3, 3 }   

};

char *IP6600DBJL1stTbl[REGI_IP6600D_1STCNT+2] = {
	"A1200B",
	"A1200E",
	"A1200F",
	"A1200G",
	"A1200H",
	"A1200J",
	"A1200K",
	"A1200C",
	"A1200L"
	
};

char *IP6600DBJL2ndTbl[REGI_IP6600D_2NDCNT+1] = {
	"B1200J",
	"B1200K",
	"B",
	"B1200L"

};

BOXINF IP6600DBox1stTbl[REGI_IP6600D_1STCNT] = {

	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff, 0 },
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 }

};

BOXINF IP6600DBox2ndTbl[REGI_IP6600D_2NDCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 39,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0xffff, 0xffff, 0 },
	{ 67,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 50, 90, 16,  4, 13, 1,  1,   0,       -2,       -6,       19,         12, 0x8000, 0x8000, 0x8000, 1 }

};


// PIXUS IP7500
#define IDM_IP_7500		"IP7500"
#define REGI_IP7500_1STCNT	8
#define REGI_IP7500_2NDCNT	5

CTRLITEM IP7500Regi1stTbl[REGI_IP7500_1STCNT] = {

	{ "IP7500regi1_spinbutton1", 0, -3, 7 },	
	{ "IP7500regi1_spinbutton2", 0, -3, 7 },   
	{ "IP7500regi1_spinbutton3", 0, -3, 7 },   
	{ "IP7500regi1_spinbutton4", 0, -3, 7 },   
	{ "IP7500regi1_spinbutton5", 0, -3, 7 },   
	{ "IP7500regi1_spinbutton6", 0, -3, 7 },   
	{ "IP7500regi1_spinbutton7", 0, -5, 5 },   
	{ "IP7500regi1_spinbutton8", 0, -5, 5 }   

};

CTRLITEM IP7500Regi2ndTbl[REGI_IP7500_2NDCNT] = {

	{ "IP7500regi2_spinbutton1", 0, -5, 5 },   
	{ "IP7500regi2_spinbutton2", 0, -5, 5 },   
	{ "IP7500regi2_spinbutton3", 0, -5, 5 },   
	{ "IP7500regi2_spinbutton4", 0, -5, 5 },   
	{ "IP7500regi2_spinbutton5", 0, -3, 3 }   

};

char *IP7500BJL1stTbl[REGI_IP7500_1STCNT+2] = {
	"A1200A",
	"A1200E",
	"A1200F",
	"A1200G",
	"A1200H",
	"A1200B",
	"A1200J",
	"A1200K",
	"A1200C",
	"A1200L"
	
};

char *IP7500BJL2ndTbl[REGI_IP7500_2NDCNT+1] = {
	"B1200D",
	"B1200I",
	"B1200J",
	"B1200K",
	"B",
	"B1200L"

};

BOXINF IP7500Box1stTbl[REGI_IP7500_1STCNT] = {

	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff, 0 },
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 },
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff, 0 },
	{ 95,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000, 0 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff, 0 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff, 0 }

};


BOXINF IP7500Box2ndTbl[REGI_IP7500_2NDCNT] = {
/*    x   y   w	 len stp sdir ldir repeat	selbox_dx selbox_dy	selbox_width selbox_height	r	g	b */
	{ 39,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0 },
	{ 53,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0x0000, 0x0000, 0 },
	{ 67,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x0000, 0xffff, 0xffff, 0 },
	{ 81,  9,  9,  2,  7, 1,  1,   0,       -2,       -4,       12,          7, 0x8000, 0xffff, 0xffff, 0 },
	{ 50, 90, 16,  4, 13, 1,  1,   0,       -2,       -6,       19,         12, 0x8000, 0x8000, 0x8000, 1 }

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
	{ 53,  16,  9,  4,  13, 1,  1,   0,       -2,       -6,       12,          11, 0x0000, 0xffff, 0xffff, 0 },
	{ 67,  16,  9,  4,  13, 1,  1,   0,       -2,       -6,       12,          11, 0x8000, 0xffff, 0xffff, 0 },
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


REGINFO	RegiInfo[] = 
	{
	{ IDM_BJC_F850,		
	{ { "regi_dialog", "regi_drawingarea", F850Regi1stTbl, F850BJL1stTbl, F850Box1stTbl, 6, PORT },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }

	} },
	
	{ IDM_BJC_F860,		
	{ { "regi_dialog", "regi_drawingarea", F860Regi1stTbl, F860BJL1stTbl, F860Box1stTbl, 6, PORT },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	
	{ IDM_BJC_F870,			
	{ { "regi_dialog", "regi_drawingarea", F870Regi1stTbl, F870BJL1stTbl, F870Box1stTbl, 6, PORT },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },

	{ IDM_BJC_F360,			
	{ { "F360regi1_dialog", "F360regi1_drawingarea", F360Regi1stTbl, F360BJL1stTbl, F360Box1stTbl, 2, PORT },
		{ "F360regi2_dialog", "F360regi2_drawingarea", F360Regi2ndTbl, F360BJL2ndTbl, F360Box2ndTbl, 2, PORT },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },

	{ IDM_BJC_S600,			
	{ { "S600regi1_dialog", "S600regi1_drawingarea", S600Regi1stTbl, S600BJL1stTbl, S600Box1stTbl, 6, PORT|BIGAREA_TYPE2 },
		{ "S600regi2_dialog", "S600regi2_drawingarea", S600Regi2ndTbl, S600BJL2ndTbl, S600Box2ndTbl, 2, PORT|BIGAREA_TYPE2|BANDREGI_TYPE|ORNAMENT_S600 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	
	{ IDM_BJC_S630,			
	{ { "S600regi1_dialog", "S600regi1_drawingarea", S600Regi1stTbl, S600BJL1stTbl, S600Box1stTbl, 6, PORT|BIGAREA_TYPE2 },
		{ "S600regi2_dialog", "S600regi2_drawingarea", S600Regi2ndTbl, S600BJL2ndTbl, S600Box2ndTbl, 2, PORT|BIGAREA_TYPE2|BANDREGI_TYPE|ORNAMENT_S600 },
	  { 0, 0, 0, 0, 0, 0, 0 }
	} },
	
	{ IDM_BJC_S6300,			
	{ { "S600regi1_dialog", "S600regi1_drawingarea", S600Regi1stTbl, S600BJL1stTbl, S600Box1stTbl, 6, PORT|BIGAREA_TYPE2 },
		{ "S600regi2_dialog", "S600regi2_drawingarea", S600Regi2ndTbl, S600BJL2ndTbl, S600Box2ndTbl, 2, PORT|BIGAREA_TYPE2|BANDREGI_TYPE|ORNAMENT_S600 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },

	// Added '01.11.05
	{ IDM_BJC_F900,				
	{ { "F900regi_dialog", "F900regi_drawingarea",  F900Regi1stTbl,  F900BJL1stTbl, F900Box1stTbl, 6, PORT|BIGAREA_TYPE2 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	
	// Added '01.11.05
	{ IDM_BJC_F9000,				
	{ { "F900regi_dialog", "F900regi_drawingarea",  F900Regi1stTbl,  F900BJL1stTbl, F900Box1stTbl, 6, PORT|BIGAREA_TYPE2 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },

	// Added '01.11.16
	{ IDM_BJC_S300,
	{ { "S600regi1_dialog", "S600regi1_drawingarea", S600Regi1stTbl, S600BJL1stTbl, S600Box1stTbl, 6, PORT|BIGAREA_TYPE2 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },

	// Added '01.11.16
	{ IDM_BJC_S500,
	{ { "S600regi1_dialog", "S600regi1_drawingarea", S600Regi1stTbl, S600BJL1stTbl, S600Box1stTbl, 6, PORT|BIGAREA_TYPE2 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },


	{ IDM_PIXUS_950I,
	{ { "PX950Iregi_dialog", "PX950Iregi_drawingarea", PX950IRegi1stTbl, 
		PX950IBJL1stTbl, PX950IBox1stTbl, 8, PORT },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },

	{ IDM_PIXUS_850I,
	{ { "PX850Iregi1_dialog", "PX850Iregi1_drawingarea", PX850IRegi1stTbl,
		PX850IBJL1stTbl, PX850IBox1stTbl, 11, PORT|BIGAREA_TYPE3 },
	  { "PX850Iregi2_dialog", "PX850Iregi2_drawingarea", PX850IRegi2ndTbl, 
		  PX850IBJL2ndTbl, PX850IBox2ndTbl, 2, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_S600 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },

	{ IDM_PIXUS_550I,
	{ { "PX550Iregi_dialog", "PX550Iregi_drawingarea", PX550IRegi1stTbl,
		PX550IBJL1stTbl, PX550IBox1stTbl, 6, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },		
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },

	{ IDM_I250,
	{ { "PX550Iregi_dialog", "PX550Iregi_drawingarea", PX550IRegi1stTbl,
		PX550IBJL1stTbl, PX550IBox1stTbl, 6, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_I255,
	{ { "PX550Iregi_dialog", "PX550Iregi_drawingarea", PX550IRegi1stTbl,
		PX550IBJL1stTbl, PX550IBox1stTbl, 6, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },

	{ IDM_PIXUS_560I,
	{ { "PX850Iregi1_dialog", "PX850Iregi1_drawingarea", PX850IRegi1stTbl,
		PX850IBJL1stTbl, PX850IBox1stTbl, 11, PORT|BIGAREA_TYPE3 },
	  { "PX850Iregi2_dialog", "PX850Iregi2_drawingarea", PX850IRegi2ndTbl, 
		  PX850IBJL2ndTbl, PX850IBox2ndTbl, 2, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_S600 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_PIXUS_860I,
	{ { "PX860Iregi1_dialog", "PX860Iregi1_drawingarea", PX860IRegi1stTbl,
		PX860IBJL1stTbl, PX860IBox1stTbl, 12, PORT|BIGAREA_TYPE3 },
	  { "PX860Iregi2_dialog", "PX860Iregi2_drawingarea", PX860IRegi2ndTbl, 
		  PX860IBJL2ndTbl, PX860IBox2ndTbl, 2, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_S600 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_PIXUS_990I,
	{ { "PX990Iregi_dialog", "PX990Iregi_drawingarea", PX990IRegi1stTbl,
		PX990IBJL1stTbl, PX990IBox1stTbl, 10, PORT|BIGAREA_TYPE4 },
	  { 0, 0, 0, 0, 0, 0, 0 },
	  { "PX990Iauto_regi_dialog", "PX990Iauto_regi_drawingarea", 
		 PX990IRegi3rdTbl, PX990IBJL3rdTbl, PX990IBox3rdTbl, 4, 
		 PORT|BIGAREA_TYPE4 }
	} },
	{ IDM_IP_3100,
	{ { "PX850Iregi1_dialog", "PX850Iregi1_drawingarea", PX850IRegi1stTbl,
		PX850IBJL1stTbl, PX850IBox1stTbl, 11, PORT|BIGAREA_TYPE3 },
	  { "PX850Iregi2_dialog", "PX850Iregi2_drawingarea", PX850IRegi2ndTbl, 
		  PX850IBJL2ndTbl, PX850IBox2ndTbl, 2, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_S600 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_IP_4100,
	{ { "PX860Iregi1_dialog", "PX860Iregi1_drawingarea", PX860IRegi1stTbl,
		PX860IBJL1stTbl, PX860IBox1stTbl, 12, PORT|BIGAREA_TYPE3 },
	  { "PX860Iregi2_dialog", "PX860Iregi2_drawingarea", PX860IRegi2ndTbl, 
		PX860IBJL2ndTbl, PX860IBox2ndTbl, 2, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_S600 },
		  { 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_IP_8600,
	{ { "ip8600regi_dialog", "ip8600regi_drawingarea", IP8600Regi1stTbl,
			IP8600BJL1stTbl, IP8600Box1stTbl, 11, PORT|BIGAREA_TYPE3 },
	  { 0, 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0, 0 }
	} },

	{ IDM_IP_1000,
	{ { "PX550Iregi_dialog", "PX550Iregi_drawingarea", PX550IRegi1stTbl,
		IP1000BJL1stTbl, PX550IBox1stTbl, 6, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_IP_1500,
	{ { "PX850Iregi1_dialog", "PX850Iregi1_drawingarea", PX850IRegi1stTbl,
		IP1500BJL1stTbl, PX850IBox1stTbl, 11, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_IP_2200,
	{ { "IP2200regi_dialog", "IP2200regi_drawingarea", IP2200Regi1stTbl,
		IP2200BJL1stTbl, IP2200Box1stTbl, 12, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_IP_4200,
	{ { "IP4200regi1_dialog", "IP4200regi1_drawingarea", IP4200Regi1stTbl,
		IP4200BJL1stTbl, IP4200Box1stTbl, 10, PORT|BIGAREA_TYPE3 },
	  { "IP4200regi2_dialog", "IP4200regi2_drawingarea", IP4200Regi2ndTbl, 
		  IP4200BJL2ndTbl, IP4200Box2ndTbl, 6, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_IP_6600D,
	{ { "IP6600Dregi1_dialog", "IP6600Dregi1_drawingarea", IP6600DRegi1stTbl,
		IP6600DBJL1stTbl, IP6600DBox1stTbl, 7, PORT|BIGAREA_TYPE3 },
	  { "IP6600Dregi2_dialog", "IP6600Dregi2_drawingarea", IP6600DRegi2ndTbl, 
		  IP6600DBJL2ndTbl, IP6600DBox2ndTbl, 3, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_IP_7500,
	{ { "IP7500regi1_dialog", "IP7500regi1_drawingarea", IP7500Regi1stTbl,
		IP7500BJL1stTbl, IP7500Box1stTbl, 8, PORT|BIGAREA_TYPE3 },
	  { "IP7500regi2_dialog", "IP7500regi2_drawingarea", IP7500Regi2ndTbl, 
		  IP7500BJL2ndTbl, IP7500Box2ndTbl, 5, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_MP_500,
	{ { "IP4200regi1_dialog", "IP4200regi1_drawingarea", IP4200Regi1stTbl,
		IP4200BJL1stTbl, IP4200Box1stTbl, 10, PORT|BIGAREA_TYPE3 },
	  { "IP4200regi2_dialog", "IP4200regi2_drawingarea", IP4200Regi2ndTbl, 
		  IP4200BJL2ndTbl, IP4200Box2ndTbl, 6, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2006/06/27
	{ IDM_MP_160,
	{ { "IP2200regi_dialog", "IP2200regi_drawingarea", IP2200Regi1stTbl,
		MP160BJL1stTbl, IP2200Box1stTbl, REGI_IP2200_1STCNT, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2006/05/29
	{ IDM_IP_3300,
	{ { "IP3300regi1_dialog", "IP3300regi1_drawingarea", IP3300Regi1stTbl,
		IP3300BJL1stTbl, IP3300Box1stTbl, REGI_IP3300_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "IP3300regi2_dialog", "IP3300regi2_drawingarea", IP3300Regi2ndTbl, 
		  IP3300BJL2ndTbl, IP3300Box2ndTbl,REGI_IP3300_2NDCNT , PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
   		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	{ IDM_MP_510,
	{ { "IP3300regi1_dialog", "IP3300regi1_drawingarea", IP3300Regi1stTbl,
		IP3300BJL1stTbl, IP3300Box1stTbl, REGI_IP3300_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "IP3300regi2_dialog", "IP3300regi2_drawingarea", IP3300Regi2ndTbl, 
		  IP3300BJL2ndTbl, IP3300Box2ndTbl,REGI_IP3300_2NDCNT , PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
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
	} },
	{ IDM_MP_600,
	{ { "IP4300regi1_dialog", "IP4300regi1_drawingarea", IP4300Regi1stTbl,
		IP4300BJL1stTbl, IP4300Box1stTbl, REGI_IP4300_1STCNT, PORT|BIGAREA_TYPE3 },
	  { "IP4300regi2_dialog", "IP4300regi2_drawingarea", IP4300Regi2ndTbl, 
		  IP4300BJL2ndTbl, IP4300Box2ndTbl,REGI_IP4300_2NDCNT , PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
	  { "IP4300regi3_dialog", "IP4300regi3_drawingarea", IP4300Regi3rdTbl, 
		  IP4300BJL3rdTbl, IP4300Box3rdTbl, REGI_IP4300_3RDCNT, PORT|BIGAREA_TYPE3|BANDREGI_TYPE|ORNAMENT_REG },
	} },
	// 2006/10/11
	{ IDM_IP_90,
	{ { "IP90regi_dialog", "IP90regi_drawingarea", IP90Regi1stTbl,
		IP90BJL1stTbl, IP90Box1stTbl, REGI_IP90_1STCNT, PORT|BIGAREA_TYPE3 },
	  { 0, 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2006/07/06
	{ IDM_IP_2500,
	{ { "IP2200regi_dialog", "IP2200regi_drawingarea", IP2200Regi1stTbl,
		IP2200BJL1stTbl, IP2200Box1stTbl, REGI_IP2200_1STCNT, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },
	// 2006/07/06
	{ IDM_IP_1800,
	{ { "IP2200regi_dialog", "IP2200regi_drawingarea", IP2200Regi1stTbl,
		IP2200BJL1stTbl, IP2200Box1stTbl, REGI_IP2200_1STCNT, PORT|BIGAREA_TYPE3 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	} },

};


#define BJTESTFILEPATH	"/usr/local/share/printui"

#define NOZZLEPATTERN	0
#define REGIPATTERN1		1
#define REGIPATTERN2		2

char *I250TestPatternTbl[2] = {
		"bjnozl_i250.utl", 	/* NozzleCheck Pattern */
		"bjregi_i250.utl"		/* Regi Pattern */
};

char *I255TestPatternTbl[2] = {
		"bjnozl_i255.utl", 	/* NozzleCheck Pattern */
		"bjregi_i255.utl"		/* Regi Pattern */
};

char *IP1000TestPatternTbl[2] = {
		"nozl_pixmaip1000.utl", 	/* NozzleCheck Pattern */
		"regi_pixmaip1000.utl"		/* Regi Pattern */
};


char *IP1500TestPatternTbl[2] = {
		"nozl_pixmaip1500.utl", 	/* NozzleCheck Pattern */
		"regi_pixmaip1500.utl"		/* Regi Pattern */
};


char *IP2200TestPatternTbl[2] = {
		"nozl_ip2200.utl", 	/* NozzleCheck Pattern */
		"regi_ip2200.utl"		/* Regi Pattern */
};

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

{ { IDM_I250,    I250TestPatternTbl   },
  { IDM_I255,    I255TestPatternTbl   },
  { IDM_IP_1000, IP1000TestPatternTbl },
  { IDM_IP_1500, IP1500TestPatternTbl },
  { IDM_IP_2200, IP2200TestPatternTbl },
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

/* I250 I255*/
int I250_REG_INDEX[REGI_I250_1STCNT+1] =
{ 0, 1, 2, 2, 5, 3, 4 };

int I250_REG_STR_INDEX[REGI_I250_1STCNT+1] =
{ 0, 1, 2, 6, 5, 3, 4 };

/* IP2200 IP2500 */
int IP2200_REG_INDEX[REGI_IP2200_1STCNT_BSCC] =
{ 5 };

int IP2200_REG_STR_INDEX[REGI_IP2200_1STCNT_BSCC] =
{ 5 };

BSCCREGINFO BsccRegInfo[] =
{
	/*	I250 */
	{ IDM_I250, "bjfilteri250.bscc",
	  { { REGI_I250_1STCNT+1, I250_REG_INDEX, I250_REG_STR_INDEX,
		  PX550IBJL1stTbl },
		{ 0, 0, 0 } }
   	},
	/* I255 */
	{ IDM_I255, "bjfilteri255.bscc",
	  { { REGI_I250_1STCNT+1, I250_REG_INDEX, I250_REG_STR_INDEX,
		  PX550IBJL1stTbl },
		{ 0, 0, 0 } }
	},
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
	/* PIXUS560i  or Default */
	{ IDM_PIXUS_560I, 0,
		{"util_ink_all_1","util_ink_black_1","util_ink_color_1"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* PIXUS860i */
	{ IDM_PIXUS_860I, 0,
		{"util_ink_all_1","util_ink_black_1","util_ink_color_2"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* PIXUS990i */
	{ IDM_PIXUS_990I, 1,
		{"util_ink_all_1","util_ink_gr1_1","util_ink_gr2_1"},
		{"utility_message_12","utility_message_31","utility_message_32"} 
	},
	/* PIXUS IP3100 */
	{ IDM_IP_3100, 0,
		{"util_ink_all_1","util_ink_black_1","util_ink_color_3"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* PIXUS IP4100 */
	{ IDM_IP_4100, 0,
		{"util_ink_all_1","util_ink_black_1","util_ink_color_4"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* PIXUS IP8600 */
	{ IDM_IP_8600, 1,
		{"util_ink_all_1","util_ink_gr1_2","util_ink_gr2_2"},
		{"utility_message_12","utility_message_31","utility_message_32"} 
	},
	/* IP4200 */
	{ IDM_IP_4200, 0,
		{"util_ink_all_1","util_ink_black_2","util_ink_color_5"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* IP7500 */
	{ IDM_IP_7500, 0,
		{"util_ink_all_1","util_ink_black_2","util_ink_color_6"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
	/* MP500 */
	{ IDM_MP_500, 0,
		{"util_ink_all_1","util_ink_black_2","util_ink_color_5"},
		{"utility_message_12","utility_message_23","utility_message_24"} 
	},
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

typedef struct{
	char* ModelName;
	short ConfigFlag;
}SETCONFIGINFO;

SETCONFIGINFO SetConfigInfo[] = 
{
	{ IDM_PIXUS_560I, CONFIG_P560I  },
	{ IDM_PIXUS_860I, CONFIG_P860I  },
	{ IDM_PIXUS_990I, CONFIG_P990I  },
	{ IDM_IP_3100,    CONFIG_P860I  },
	{ IDM_IP_4100,    CONFIG_P860I  },
	{ IDM_IP_8600,    CONFIG_P990I  },
	{ IDM_IP_1000,    CONFIG_IP1000 },
	{ IDM_IP_1500,    CONFIG_IP1000 },
	{ IDM_IP_2200,    CONFIG_IP1000  },
	{ IDM_IP_4200,    CONFIG_P860I  },
	{ IDM_IP_6600D,   CONFIG_P860I  },
	{ IDM_IP_7500,    CONFIG_P860I  },
	{ IDM_MP_500,     CONFIG_P860I  },
	{ IDM_MP_160,     CONFIG_IP1000  }, // 2006/05/30
	{ IDM_IP_3300,    CONFIG_IP1000  },
	{ IDM_MP_510,     CONFIG_IP1000  },
	{ IDM_IP_4300,    CONFIG_P860I  },
	{ IDM_MP_600,     CONFIG_P860I  },
	{ IDM_IP_90,      CONFIG_IP1000  }, // 2006/10/12
	{ IDM_IP_2500,    CONFIG_IP1000  },	// 2006/07/06
	{ IDM_IP_1800,    CONFIG_IP1000  },	// 2006/07/06
};


// CheckPattern Info
#define OK_CHECK_PATTN 0
#define NG_CHECK_PATTN 1

#define CHECKPATTERNPATH	"/usr/local/share/printui"

typedef struct{
	char* ModelName;
	char* pattn_filename[2];
}PATTERNCHECKINFO;

PATTERNCHECKINFO PatternCheckInfo[] = 
{
	{ IDM_IP_3100, { "okptn_pixusip3100.xpm", 
					 "ngptn_pixusip3100.xpm" } },
	{ IDM_IP_4100, { "okptn_pixusip4100.xpm", 
					 "ngptn_pixusip4100.xpm" } },
	{ IDM_IP_8600, { "okptn_pixusip8600.xpm", 
					 "ngptn_pixusip8600.xpm" } },
	{ IDM_IP_1000, { "okptn_pixmaip1000.xpm", 
					 "ngptn_pixmaip1000.xpm" } },
	{ IDM_IP_1500, { "okptn_pixmaip1500.xpm", 
					 "ngptn_pixmaip1500.xpm" } },
	{ IDM_IP_2200, { "okptn_ip2200.xpm", 
					 "ngptn_ip2200.xpm" } },
	{ IDM_IP_4200, { "okptn_ip4200.xpm", 
					 "ngptn_ip4200.xpm" } },
	{ IDM_IP_6600D, { "okptn_ip6600d.xpm", 
					 "ngptn_ip6600d.xpm" } },
	{ IDM_IP_7500, { "okptn_ip7500.xpm", 
					 "ngptn_ip7500.xpm" } },
	{ IDM_MP_500, { "okptn_mp500.xpm", 
					 "ngptn_mp500.xpm" } },
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

#endif