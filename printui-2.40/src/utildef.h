/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2013
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
#define	BJLBANDREGI1	"@TestPrint=BandRegi1\x0a"		
#define	BJLMANUAL1		"@TestPrint=Manual1\x0a"		
#define	BJLMANUAL2		"@TestPrint=Manual2\x0a"		
#define BJLREGIAUTO1	"@TestPrint=Regi_Auto1\x0a"			
#define BJLSETREG		"SetRegistration=%6s%c%02d\x0a"	
#define	BJLSETBANDREG	"SetBandRegi=%1s%c%02d\x0a"		
#define	BJLPOWEROFF		"@PowerOff\x0a"					
#define	BJLAUTOPOWEROFF	"AutoPowerOff=%s\x0a"			
#define	BJLAUTOPOWERON	"AutoPowerOn=%s\x0a"			
#define BJLEND			"BJLEND\x0a"					
#define BJLROLLER1		"@RollerCleaning=PLATE\x0a"		
#define	BJLROLLER2		"@RollerCleaning\x0a"			

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
#define	BJLBANDREGI1LEN		21
#define	BJLMANUAL1LEN		19
#define	BJLMANUAL2LEN		19
#define	BJLREGIAUTO1LEN		22
#define	BJLSETREGLEN		26
#define	BJLSETBANDREGLEN	17
#define	BJLPOWEROFFLEN		10

#define BJLENDLEN			7                           
#define	BJLROLLER1LEN		22                          
#define	BJLROLLER2LEN		16                          

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
} BOXINF, *LPBOXINF;


typedef struct {
	char	*CtrlName;				
	short	nDefault;               
	short	nMin;                   
	short	nMax;                   
} CTRLITEM, *LPCTRLITEM;


#define REGI_TBL_MAX_NUM	3
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


/* BJF850 */
#define	IDM_BJC_F850		"BJF850"	
#define	REGI_F850_1STCNT	6           
#define	REGI_F850_2NDCNT	0           


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

	{ 11, 9, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0x0000, 0x0000, 0x0000 },	
	{ 28, 9, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0x0000, 0xffff, 0xffff },    
	{ 45, 9, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0xffff, 0x0000, 0xffff },    
	{ 62, 9, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0x8000, 0xffff, 0xffff },    
	{ 79, 9, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0xffff, 0x8000, 0xffff },    
	{ 45,90, 11, 3, 7, 1, 1, 0, -2, -5, 14, 8, 0x8000, 0x8000, 0x8000 }     
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

	{ 11, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0x0000, 0x0000 },	
	{ 28, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0xffff, 0xffff },    
	{ 45, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x0000, 0xffff },    
	{ 62, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x8000, 0xffff, 0xffff },    
	{ 79, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x8000, 0xffff },    
	{ 45,75, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x8000, 0x8000, 0x8000 }	    
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

	{ 11, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0x0000, 0x0000 },	
	{ 28, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0xffff, 0xffff },    
	{ 45, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x0000, 0xffff },    
	{ 62, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x8000, 0xffff, 0xffff },    
	{ 79, 6, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x8000, 0xffff },    
	{ 45,75, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x8000, 0x8000, 0x8000 }	    
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

	{ 6, 20, 2, 3, 6, 0, 1, 2, -2, -5, 6, 10, 0x0000, 0x0000, 0x0000 },		
	{ 6, 46, 2, 3, 6, 0, 1, 2, -2, -5, 6, 10, 0x0000, 0x0000, 0x0000 }  	
};


BOXINF F360Box2ndTbl[REGI_F360_2NDCNT] = {

	{ 40, 20, 2, 3, 6, 0, 1, 2, -2, -5, 6, 10, 0x0000, 0x0000, 0x0000 },	
	{ 40, 46, 2, 3, 6, 0, 1, 2, -2, -5, 6, 10, 0x0000, 0x0000, 0x0000 }     
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

	{ 26,  8, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0x0000, 0x0000, 0x0000 },	
	{ 53,  8, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0x0000, 0xffff, 0xffff },	
	{ 80,  8, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0xffff, 0x0000, 0xffff },	
	{ 26, 91, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0x0000, 0x0000, 0x0000 },	
	{ 53, 91, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0x0000, 0xffff, 0xffff },	
	{ 80, 91, 11, 3, 7, 1, 1, 0, -2, -5, 14, 9, 0x0000, 0x0000, 0x0000 }	
};


BOXINF S600Box2ndTbl[REGI_S600_2NDCNT] = {

	{ 25, 18, 16, 3, 21, 1, 1, 0, -2, -5, 19, 10, 0x8000, 0x8000, 0x8000 },	
	{ 69, 20, 16, 6, 21, 1, 1, 0, -2, -8, 19, 17, 0x8000, 0x8000, 0x8000 }	
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

	{ 12, 6, 13, 3, 7, 1, 1, 0, -2, -5, 16, 9, 0x0000, 0x0000, 0x0000 },	
	{ 32, 6, 13, 3, 7, 1, 1, 0, -2, -5, 16, 9, 0x0000, 0xffff, 0xffff },    
	{ 52, 6, 13, 3, 7, 1, 1, 0, -2, -5, 16, 9, 0xffff, 0x0000, 0xffff },    
	{ 72, 6, 13, 3, 7, 1, 1, 0, -2, -5, 16, 9, 0x8000, 0xffff, 0xffff },    
	{ 92, 6, 13, 3, 7, 1, 1, 0, -2, -5, 16, 9, 0xffff, 0x8000, 0xffff },    
	{ 71,88, 10, 3, 7, 1, 1, 0, -2, -5, 13, 9, 0x8000, 0x8000, 0x8000 }	    

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

	{ 11, 5, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0x0000, 0x0000 },	
	{ 28, 5, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x0000, 0xffff, 0xffff },    
	{ 45, 5, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x0000, 0xffff },    
	{ 62, 5, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0x8000, 0xffff, 0xffff },    
	{ 79, 5, 11, 2, 6, 1, 1, 0, -2, -4, 14, 7, 0xffff, 0x8000, 0xffff },    
	{ 28,74,  9, 2, 6, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0x8000, 0x8000 },
	{ 45,74,  9, 2, 6, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff },
	{ 62,74,  9, 2, 6, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff }

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

	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000 },	
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff },    
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff },    
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff },    
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff },    
	{ 25, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0x8000, 0x8000 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff },
	{ 53, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0x8000, 0x8000 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff },
	{ 81, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff },
	{ 95, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff }

};



BOXINF PX850IBox2ndTbl[REGI_PX850I_2NDCNT] = {

	{ 29, 17, 20,  2, 17, 1, 1, 0, -2, -5, 24,  9, 0x8000, 0x8000, 0x8000 },
	{ 79, 17, 20,  4, 17, 1, 1, 0, -2, -9, 24, 18, 0x8000, 0x8000, 0x8000 }
	
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

	{ 19,  9, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0x0000, 0x0000, 0x0000 },	
	{ 54,  9, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0x0000, 0xffff, 0xffff },    
	{ 89,  9, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0xffff, 0x0000, 0xffff },    
	{ 19, 93, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0x8000, 0x8000, 0x8000 },    
	{ 54, 93, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0x0000, 0xffff, 0xffff },    
	{ 89, 93, 20, 2, 7, 1, 1, 0, -2, -4, 23, 7, 0x8000, 0x8000, 0x8000 }

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

	{ 25,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000 },	
	{ 39,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff },    
	{ 53,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x0000, 0xffff },    
	{ 67,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff },    
	{ 81,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff },    
	{ 95,  9, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000 },
	{ 25, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000 },
	{ 39, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0xffff, 0xffff },
	{ 53, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x0000, 0x0000, 0x0000 },
	{ 67, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff },
	{ 81, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0x8000, 0xffff, 0xffff },
	{ 95, 93, 9, 2, 7, 1, 1, 0, -2, -4, 12, 7, 0xffff, 0x8000, 0xffff }

};



BOXINF PX860IBox2ndTbl[REGI_PX860I_2NDCNT] = {

	{ 29, 17, 20,  2, 17, 1, 1, 0, -2, -5, 24,  9, 0x8000, 0x8000, 0x8000 },
	{ 79, 17, 20,  4, 17, 1, 1, 0, -2, -9, 24, 18, 0x8000, 0x8000, 0x8000 }
	
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
	{ 30, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0x0000, 0x0000 },	
	{ 44, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0xffff, 0xffff },    
	{ 58, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x0000, 0xffff },    
	{ 72, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x8000, 0xffff, 0xffff },    
	{ 86, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x8000, 0xffff },    
	{100, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x8000, 0x0000 },
	{ 44,100, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0x0000, 0x0000 },
	{ 58,100, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x8000, 0xffff, 0xffff },
	{ 72,100, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x0000, 0xffff },
	{ 86,100, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0x0000, 0x0000, 0x0000 }
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

	{ 46, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x0000, 0xffff },    
	{ 60, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x8000, 0xffff },    
	{ 74, 16, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x8000, 0x0000 },
	{ 60,100, 10, 2, 7, 1, 1, 0, -2, -4, 13, 7, 0xffff, 0x0000, 0xffff },
};



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
	} }
};


#define BJTESTFILEPATH	PACKAGE_DATA_DIR

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


typedef struct{
	char *ModelName;
	char **TestPatternTbl;

}TESTPATTERNINFO;


TESTPATTERNINFO TestPatternInfo[] =

{ { IDM_I250, I250TestPatternTbl },
  { IDM_I255, I255TestPatternTbl }

};

#define BSCCREGFORMAT	"%6s%c%02d\x0a"	
#define BSCCFILEPATH	catpath(mkpath(XBJLIBPATH),"/")
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
	}
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
	}
};

// SetConfig Info
#define SETCONFIG_DRY_3		1
#define SETCONFIG_DRY_5		2
#define SETCONFIG_ABRASION	4
#define SETCONFIG_MANHEAD	8


#define CONFIG_P560I (SETCONFIG_DRY_5|SETCONFIG_ABRASION)
#define CONFIG_P860I (SETCONFIG_DRY_5|SETCONFIG_ABRASION|SETCONFIG_MANHEAD)
#define CONFIG_P990I (SETCONFIG_DRY_3|SETCONFIG_ABRASION|SETCONFIG_MANHEAD)

typedef struct{
	char* ModelName;
	short ConfigFlag;
}SETCONFIGINFO;

SETCONFIGINFO SetConfigInfo[] = 
{
	{ IDM_PIXUS_560I, CONFIG_P560I },
	{ IDM_PIXUS_860I, CONFIG_P860I },
	{ IDM_PIXUS_990I, CONFIG_P990I }
};

#endif