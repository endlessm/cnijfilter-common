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


#ifndef _UTIL_CMD_H_
#define _UTIL_CMD_H_

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
#define BJLNOZZLECHECKBIN1	"@TestPrint=NozzleCheckBin1\x0a"		
#define BJLNOZZLECHECKBIN2	"@TestPrint=NozzleCheckBin2\x0a"		
#define	BJLMANUAL		"@TestPrint=Manual\x0a"			
#define	BJLREGI1		"@TestPrint=Regi1\x0a"			
#define	BJLREGI2		"@TestPrint=Regi2\x0a"			
#define	BJLREGI3		"@TestPrint=Regi3\x0a"
#define	BJLREGI4		"@TestPrint=Regi4\x0a"
#define	BJLREGI1BIN1		"@TestPrint=Regi1Bin1\x0a"			
#define	BJLREGI2BIN1		"@TestPrint=Regi2Bin1\x0a"			
#define	BJLREGI3BIN1		"@TestPrint=Regi3Bin1\x0a"
#define	BJLREGI4BIN1		"@TestPrint=Regi4Bin1\x0a"
#define	BJLREGI1BIN2		"@TestPrint=Regi1Bin2\x0a"			
#define	BJLREGI2BIN2		"@TestPrint=Regi2Bin2\x0a"			
#define	BJLREGI3BIN2		"@TestPrint=Regi3Bin2\x0a"
#define	BJLREGI4BIN2		"@TestPrint=Regi4Bin2\x0a"
#define	BJLBANDREGI1	"@TestPrint=BandRegi1\x0a"		
#define	BJLMANUAL1		"@TestPrint=Manual1\x0a"		
#define	BJLMANUAL2		"@TestPrint=Manual2\x0a"		
#define BJLREGIAUTO1	"@TestPrint=Regi_Auto1\x0a"			
#define BJLREGICHECK	"@TestPrint=RegiCheck\x0a"			
#define BJLREGICHECKBIN1	"@TestPrint=RegiCheckBin1\x0a"		
#define BJLREGICHECKBIN2	"@TestPrint=RegiCheckBin2\x0a"			
#define BJLSETREG		"SetRegistration=%6s%c%02d\x0a"	
#define BJLSETREG2		"SetRegi2=%2s%c%01d\x0a"
#define	BJLSETBANDREG	"SetBandRegi=%1s%c%02d\x0a"		
#define	BJLPOWEROFF		"@PowerOff\x0a"					
#define	BJLAUTOPOWEROFF	"AutoPowerOff=%s\x0a"			
#define	BJLAUTOPOWERON	"AutoPowerOn=%s\x0a"			
#define BJLEND			"BJLEND\x0a"					
#define BJLROLLER1		"@RollerCleaning=PLATE\x0a"		
#define	BJLROLLER2		"@RollerCleaning\x0a"			
#define BJLROLLER3		"@RollerCleaning=Platen\x0a"
#define BJLROLLER4		"@RollerCleaning=Roller\x0a"
#define BJLROLLER4BIN1	"@RollerCleaning=RollerBin1\x0a"
#define BJLROLLER4BIN2	"@RollerCleaning=RollerBin2\x0a"

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
#define BJLSILENTTIME	"SetSilentTime=%s\x0a"
#define BJLDRYLEVEL		"DryLevel=%d\x0a"
#define BJLINKDETECTION	"InkDetection=%s\x0a"
#define BJLRESETBLACK	"@DotCountClear=ColorK\x0a"
#define BJLRESETCMY		"@DotCountClear=CMY\x0a"
#define BJLPAPERGAP		"PaperGap=%s\x0a"
#define BJLPAPERJAM		"PreventPaperJam=%s\x0a"
#define BJLPAPERWEFEED	"PreventWFeed=%s\x0a"

#define BJLPAPERSOURCESETTING1		"SetPPFeeder=ASF\x0a"
#define BJLPAPERSOURCESETTING2		"SetPPFeeder=FSF\x0a"

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
#define BJLNOZZLECHECKBIN1LEN	27	
#define BJLNOZZLECHECKBIN2LEN	27
#define	BJLMANUALLEN		18
#define	BJLREGI1LEN			17
#define	BJLREGI2LEN			17
#define	BJLREGI3LEN			17
#define	BJLREGI4LEN			17
#define	BJLREGI1BIN1LEN		21		
#define	BJLREGI2BIN1LEN		21
#define	BJLREGI3BIN1LEN		21
#define	BJLREGI4BIN1LEN		21
#define	BJLREGI1BIN2LEN		21		
#define	BJLREGI2BIN2LEN		21
#define	BJLREGI3BIN2LEN		21
#define	BJLREGI4BIN2LEN		21
#define	BJLBANDREGI1LEN		21
#define	BJLMANUAL1LEN		19
#define	BJLMANUAL2LEN		19
#define	BJLREGIAUTO1LEN		22
#define	BJLREGICHECKLEN		21
#define	BJLREGICHECKBIN1LEN		25	
#define	BJLREGICHECKBIN2LEN		25
#define	BJLSETREGLEN		26
#define	BJLSETREG2LEN		14
#define	BJLSETBANDREGLEN	17
#define	BJLPOWEROFFLEN		10

#define BJLENDLEN			7                           
#define	BJLROLLER1LEN		22                          
#define	BJLROLLER2LEN		16                          
#define	BJLROLLER3LEN		23
#define	BJLROLLER4LEN		23
#define	BJLROLLER4BIN1LEN	27	
#define	BJLROLLER4BIN2LEN	27

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

#define BJLPAPERSOURCESETTING1LEN		16
#define BJLPAPERSOURCESETTING2LEN		16

// Added '01.11.16
#define BJLRESETBLACKLEN	22
#define BJLRESETCMYLEN		19


#define	REGI_BUF_SIZE		(20+30*14)
#define	REGI_TMP_SIZE		30                          

/* Ver.3.70 */
#define BJL_STR_SIZE	32
#define BJL_STR_ON		"ON"
#define BJL_STR_OFF		"OFF"
#define BJL_STR_AUTO	"AUTO"
#define BJL_STR_WIDE	"WIDE"
#define BJL_STR_ENABLE	"Enable"
#define BJL_STR_DISABLE	"Disable"
#define BJL_STR_VAL_1	"1"
#define BJL_STR_VAL_2	"2"
#define BJL_STR_VAL_3	"3"
#define BJL_STR_VAL_4	"4"
#define BJL_STR_VAL_5	"5"
#define BJL_STR_005_MIN	"5"
#define BJL_STR_010_MIN	"10"
#define BJL_STR_015_MIN	"15"
#define BJL_STR_030_MIN	"30"
#define BJL_STR_060_MIN	"60"
#define BJL_STR_120_MIN	"120"
#define BJL_STR_240_MIN	"240"
#define BJL_STR_BT005_MIN	"B5"
#define BJL_STR_BT010_MIN	"B10"
#define BJL_STR_BT015_MIN	"B15"
#define BJL_STR_BT030_MIN	"B30"
#define BJL_STR_TIME	"TIME"


#endif
