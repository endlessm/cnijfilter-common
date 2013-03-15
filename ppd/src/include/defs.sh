#/bin/bash

Copyright(){
	echo "*PPD-Adobe: \"4.3\"" >> ${_dest}
	echo "*% CUPS add-on PPD file for Canon Inkjet Printer Driver." >> ${_dest}
	echo "*% Copyright CANON INC. 2001-2013" >> ${_dest}
	echo "*% All Rights Reserved." >> ${_dest}
	echo "*% " >> ${_dest}
	echo "*% This program is free software; you can redistribute it and/or modify" >> ${_dest}
	echo "*% it under the terms of the GNU General Public License as published by" >> ${_dest}
	echo "*% the Free Software Foundation; version 2 of the License." >> ${_dest}
	echo "*% " >> ${_dest}
	echo "*% This program is distributed in the hope that it will be useful," >> ${_dest}
	echo "*% but WITHOUT ANY WARRANTY; without even the implied warranty of" >> ${_dest}
	echo "*% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" >> ${_dest}
	echo "*% GNU General Public License for more details." >> ${_dest}
	echo "*% " >> ${_dest}
	echo "*% You should have received a copy of the GNU General Public License" >> ${_dest}
	echo "*% along with this program; if not, write to the Free Software" >> ${_dest}
	echo "*% Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA." >> ${_dest}
	echo "" >> ${_dest}
}

HWMargins(){
	margin=`cat include/canon_margin.txt | grep "${model_master,,}"`
	_HWMargins1=`echo ${margin} | cut '-d-' -f1`
	_HWMargins2=`echo ${margin} | cut '-d-' -f2`
	_HWMargins3=`echo ${margin} | cut '-d-' -f3`
	_HWMargins4=`echo ${margin} | cut '-d-' -f4`
	_Width1=`echo ${margin} | cut '-d-' -f5`
	_Width2=`echo ${margin} | cut '-d-' -f6`
	_Height1=`echo ${margin} | cut '-d-' -f7`
	_Height2=`echo ${margin} | cut '-d-' -f8`
	_MaxMediaWidth=`echo ${margin} | cut '-d-' -f9`
	_MaxMediaHeight=`echo ${margin} | cut '-d-' -f10`
	echo "*MaxMediaWidth: \"${_MaxMediaWidth}\"" >> ${_dest}
	echo "*MaxMediaHeight: \"${_MaxMediaHeight}\"" >> ${_dest}
	echo "*CenterRegistered: False" >> ${_dest}
	echo "*HWMargins: ${_HWMargins1} ${_HWMargins2} ${_HWMargins3} ${_HWMargins4}" >> ${_dest}
	echo "*LeadingEdge Short: \"\"" >> ${_dest}
	echo "*DefaultLeadingEdge: Short" >> ${_dest}
	echo "*VariablePaperSize: True" >> ${_dest}
	echo "*ParamCustomPageSize Width: 1 points ${_Width1} ${_Width2}" >> ${_dest}
	echo "*ParamCustomPageSize Height: 2 points ${_Height1} ${_Height2}" >> ${_dest}
	echo "*ParamCustomPageSize WidthOffset: 3 points 0 0" >> ${_dest}
	echo "*ParamCustomPageSize HeightOffset: 4 points 0 0" >> ${_dest}
	echo "*ParamCustomPageSize Orientation: 5 int 1 1" >> ${_dest}
	echo "*CustomPageSize True: \"pop pop pop <</PageSize [5 -2 roll] /ImagingBBox null>>setpagedevice\"" >> ${_dest}
	echo "" >> ${_dest}
}

PpdPut1(){
	echo "*FileVersion: \"1.0\"" >> ${_dest}
	echo "*FormatVersion:	\"4.3\"" >> ${_dest}
	echo "*LanguageEncoding: ISOLatin1" >> ${_dest}
	echo "*LanguageVersion: English" >> ${_dest}
	echo "*Manufacturer: \"Canon\"" >> ${_dest}
	if [ ${model_type} = "0" ]; then
		echo "*ModelName: \"Canon ${model_name1}\"" >> ${_dest}
		echo "*NickName: \"Canon ${model_name1} Ver.${_new_ver}\"" >> ${_dest}
	elif [ ${model_type} = "4" ]; then
		echo "*ModelName: \"Canon ${model_name1} series\"" >> ${_dest}
		echo "*NickName: \"Canon ${model_name1} series Ver.${_new_ver}\"" >> ${_dest}
	elif [ ${model_type} = "1" ]; then
		echo "*ModelName: \"BJ${model_name1}\"" >> ${_dest}
		echo "*NickName: \"Canon BJ ${model_name1} Ver.${_new_ver}\"" >> ${_dest}
	elif [ ${model_type} = "2" ]; then
		echo "*ModelName: \"Canon PIXUS ${model_name1}\"" >> ${_dest}
		echo "*NickName: \"Canon PIXUS ${model_name1} Ver.${_new_ver}\"" >> ${_dest}
	elif [ ${model_type} = "3" ]; then
		echo "*ModelName: \"Canon PIXMA ${model_name1}\"" >> ${_dest}
		echo "*NickName: \"Canon PIXMA ${model_name1} Ver.${_new_ver}\"" >> ${_dest}
	fi
	echo "*PCFileName: \"${model_name2^^}.PPD\"" >> ${_dest}
	if [ ! "${model_master}" = "" ]; then
		model_type_master=`cat include/canon_plug.txt | grep "\-${model_master}-" | cut '-d-' -f15`
		if [ ${model_type_master} = "1" ]; then
			echo "*Product: \"(bj${model_master,,})\"" >> ${_dest}
		elif [ ${model_type_master} = "2" ]; then
			echo "*Product: \"(pixus${model_master,,})\"" >> ${_dest}
		elif [ ${model_type_master} = "3" ]; then
			echo "*Product: \"(pixma${model_master,,})\"" >> ${_dest}
		else
			echo "*Product: \"(${model_master,,})\"" >> ${_dest}
		fi
	else
		if [ ${model_type} = "1" ]; then
			echo "*Product: \"(bj${model_smol,,})\"" >> ${_dest}
		elif [ ${model_type} = "2" ]; then
			echo "*Product: \"(pixus${model_smol,,})\"" >> ${_dest}
		elif [ ${model_type} = "3" ]; then
			echo "*Product: \"(pixma${model_smol,,})\"" >> ${_dest}
		else
			echo "*Product: \"(${model_smol,,})\"" >> ${_dest}
		fi
	fi
	echo "*PSVersion: \"(3010.000) 550\"" >> ${_dest}
	echo "*PSVersion: \"(3010.000) 651\"" >> ${_dest}
	echo "*PSVersion: \"(3010.000) 705\"" >> ${_dest}
	echo "*PSVersion: \"(3010.000) 715\"" >> ${_dest}
	if [ ${model_type} = "1" ]; then
		echo "*ShortNickName: \"BJ${model_smol^^}\"" >> ${_dest}
	elif [ ${model_type} = "2" ]; then
		echo "*ShortNickName: \"PIXUS${model_name1^^}\"" >> ${_dest}
	elif [ ${model_type} = "3" ]; then
		echo "*ShortNickName: \"PIXMA${model_name1^^}\"" >> ${_dest}
	else
		echo "*ShortNickName: \"${model_smol^^}\"" >> ${_dest}
	fi
	echo "" >> ${_dest}
}

PpdPut2(){
	echo "*ColorDevice: True" >> ${_dest}
	echo "*DefaultColorSpace: RGB" >> ${_dest}
	echo "*Throughput: \"1\"" >> ${_dest}
	echo "*LandscapeOrientation: Plus90" >> ${_dest}
	echo "*LanguageLevel: \"3\"" >> ${_dest}
	echo "*FileSystem: False" >> ${_dest}
	echo "*TTRasterizer: Type42" >> ${_dest}
	echo "" >> ${_dest}
}

PpdPut3(){
	if [ ${_ver} = "1.30" ]; then
		_pstocanon="pstocanonbj"
	elif [ ${_ver} = "2.00" ]; then
		_pstocanon="pstocanonbj"
	elif [ ${_ver} = "2.10" ]; then
		_pstocanon="pstocanonbj"
	elif [ ${_ver} = "2.20" ]; then
		_pstocanon="pstocanonbj"
	elif [ ${_ver} = "2.30" ]; then
		_pstocanon="pstocanonbj"
	elif [ ${_ver} = "2.40" ]; then
		_pstocanon="pstocanonbj"
	elif [ ${_ver} = "2.50" ]; then 
		_pstocanon="pstocanonbj"
	else
		_pstocanon="pstocanonij"
	fi
	echo "*cupsFilter: \"application/vnd.cups-postscript 0 ${_pstocanon}\"" >> ${_dest}
	echo "*cupsManualCopies: True" >> ${_dest}
	echo "*cupsModelNumber: ${_num}" >> ${_dest}
	echo "*cupsVersion: 1.2" >> ${_dest}
	echo "*cupsLanguages: \"cs da de es fi fr el hu it nl no pl pt ru sv tr ko zh zh_TW th id ja\"" >> ${_dest}
	echo "" >> ${_dest}
}

CNMain(){
	echo "" >> ${_dest}
	echo "*OpenGroup: *CNMain/Main" >> ${_dest}
	echo "" >> ${_dest}
}

CNMain_close(){
	echo "*CloseGroup: *CNMain" >> ${_dest}
	echo "" >> ${_dest}
}

CNColorAdjust(){
	echo "" >> ${_dest}
	echo "*OpenGroup: *CNColorAdjust/Manual Color Adjustment" >> ${_dest}
	echo "" >> ${_dest}
}

CNColorAdjust_close(){
	echo "*CloseGroup: *CNColorAdjust" >> ${_dest}
	echo "" >> ${_dest}
}

CNBorderless(){
	echo "" >> ${_dest}
	echo "*OpenGroup: *CNBorderless/Borderless" >> ${_dest}
	echo "" >> ${_dest}
}
	
CNBorderless_close(){
	echo "*CloseGroup: *CNBorderless" >> ${_dest}
	echo "" >> ${_dest}
}

CNGeneral(){
	echo "" >> ${_dest}
	echo "*OpenGroup: *CNGeneral/General" >> ${_dest}
	echo "" >> ${_dest}
}

CNGeneral_close(){
	echo "*CloseGroup: *CNGeneral" >> ${_dest}
	echo "" >> ${_dest}
}

CNPagesetup(){
	echo "" >> ${_dest}
	echo "*OpenGroup: *CNPagesetup/Page Setup" >> ${_dest}
	echo "" >> ${_dest}
}

CNPagesetup_close(){
	echo "*CloseGroup: *CNPagesetup" >> ${_dest}
	echo "" >> ${_dest}
}



CNQuality(){
	echo "*OpenUI *CNQuality/Print Quality: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNQuality" >> ${_dest}
	echo "*DefaultCNQuality: 3" >> ${_dest}
	echo "*CNQuality 1/1(High): \"<</CNQuality(1)>>setpagedevice\"" >> ${_dest}
	echo "*CNQuality 2/2: \"<</CNQuality(2)>>setpagedevice\"" >> ${_dest}
	echo "*CNQuality 3/3: \"<</CNQuality(3)>>setpagedevice\"" >> ${_dest}
	echo "*CNQuality 4/4(Fast): \"<</CNQuality(4)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNQuality" >> ${_dest}
	echo "" >> ${_dest}
}

CNGrayscale(){
	echo "*OpenUI *CNGrayscale/Grayscale Printing: Boolean" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNGrayscale" >> ${_dest}
	echo "*DefaultCNGrayscale: False" >> ${_dest}
	echo "*CNGrayscale True/ON: \"<</CNGrayscale(True)>>setpagedevice\"" >> ${_dest}
	echo "*CNGrayscale False/OFF: \"<</CNGrayscale(False)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNGrayscale" >> ${_dest}
	echo "" >> ${_dest}
}

CNHalftoning(){
	echo "*OpenUI *CNHalftoning/Halftoning: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNHalftoning" >> ${_dest}
	echo "*DefaultCNHalftoning: ed" >> ${_dest}
	echo "*CNHalftoning ed/Diffusion: \"<</CNHalftoning(ed)>>setpagedevice\"" >> ${_dest}
	echo "*CNHalftoning pattern/Dither: \"<</CNHalftoning(pattern)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNHalftoning" >> ${_dest}
	echo "" >> ${_dest}
}

CNRenderIntent(){
	echo "*OpenUI *CNRenderIntent/Vivid Photo: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNRenderIntent" >> ${_dest}
	echo "*DefaultCNRenderIntent: photo" >> ${_dest}
	echo "*CNRenderIntent photo/Photo: \"<</CNRenderIntent(photo)>>setpagedevice\"" >> ${_dest}
	echo "*CNRenderIntent vivid/Vivid: \"<</CNRenderIntent(vivid)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNRenderIntent" >> ${_dest}
	echo "" >> ${_dest}
}

CNPaperGap(){
	echo "*%OpenUI *CNPaperGap/Paper Gap: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNPaperGap" >> ${_dest}
	echo "*%DefaultCNPaperGap: auto" >> ${_dest}
	echo "*%CNPaperGap auto/Auto: \"<</CNPaperGap(auto)>>setpagedevice\"" >> ${_dest}
	echo "*%CNPaperGap wide/Wide: \"<</CNPaperGap(wide)>>setpagedevice\"" >> ${_dest}
	echo "*%CloseUI: *CNPaperGap" >> ${_dest}
	echo "" >> ${_dest}
}


CNBalanceC(){
	echo "*OpenUI *CNBalanceC/Cyan: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNBalanceC" >> ${_dest}
	echo "*DefaultCNBalanceC: 0" >> ${_dest}
	echo "*CNBalanceC -50/-50: \"<</CNBalanceC(-50)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -49/-49: \"<</CNBalanceC(-49)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -48/-48: \"<</CNBalanceC(-48)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -47/-47: \"<</CNBalanceC(-47)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -46/-46: \"<</CNBalanceC(-46)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -45/-45: \"<</CNBalanceC(-45)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -44/-44: \"<</CNBalanceC(-44)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -43/-43: \"<</CNBalanceC(-43)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -42/-42: \"<</CNBalanceC(-42)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -41/-41: \"<</CNBalanceC(-41)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -40/-40: \"<</CNBalanceC(-40)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -39/-39: \"<</CNBalanceC(-39)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -38/-38: \"<</CNBalanceC(-38)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -37/-37: \"<</CNBalanceC(-37)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -36/-36: \"<</CNBalanceC(-36)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -35/-35: \"<</CNBalanceC(-35)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -34/-34: \"<</CNBalanceC(-34)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -33/-33: \"<</CNBalanceC(-33)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -32/-32: \"<</CNBalanceC(-32)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -31/-31: \"<</CNBalanceC(-31)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -30/-30: \"<</CNBalanceC(-30)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -29/-29: \"<</CNBalanceC(-29)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -28/-28: \"<</CNBalanceC(-28)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -27/-27: \"<</CNBalanceC(-27)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -26/-26: \"<</CNBalanceC(-26)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -25/-25: \"<</CNBalanceC(-25)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -24/-24: \"<</CNBalanceC(-24)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -23/-23: \"<</CNBalanceC(-23)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -22/-22: \"<</CNBalanceC(-22)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -21/-21: \"<</CNBalanceC(-21)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -20/-20: \"<</CNBalanceC(-20)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -19/-19: \"<</CNBalanceC(-19)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -18/-18: \"<</CNBalanceC(-18)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -17/-17: \"<</CNBalanceC(-17)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -16/-16: \"<</CNBalanceC(-16)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -15/-15: \"<</CNBalanceC(-15)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -14/-14: \"<</CNBalanceC(-14)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -13/-13: \"<</CNBalanceC(-13)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -12/-12: \"<</CNBalanceC(-12)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -11/-11: \"<</CNBalanceC(-11)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -10/-10: \"<</CNBalanceC(-10)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -9/-9: \"<</CNBalanceC(-9)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -8/-8: \"<</CNBalanceC(-8)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -7/-7: \"<</CNBalanceC(-7)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -6/-6: \"<</CNBalanceC(-6)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -5/-5: \"<</CNBalanceC(-5)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -4/-4: \"<</CNBalanceC(-4)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -3/-3: \"<</CNBalanceC(-3)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -2/-2: \"<</CNBalanceC(-2)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC -1/-1: \"<</CNBalanceC(-1)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 0/0: \"<</CNBalanceC(0)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 1/1: \"<</CNBalanceC(1)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 2/2: \"<</CNBalanceC(2)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 3/3: \"<</CNBalanceC(3)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 4/4: \"<</CNBalanceC(4)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 5/5: \"<</CNBalanceC(5)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 6/6: \"<</CNBalanceC(6)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 7/7: \"<</CNBalanceC(7)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 8/8: \"<</CNBalanceC(8)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 9/9: \"<</CNBalanceC(9)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 10/10: \"<</CNBalanceC(10)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 11/11: \"<</CNBalanceC(11)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 12/12: \"<</CNBalanceC(12)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 13/13: \"<</CNBalanceC(13)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 14/14: \"<</CNBalanceC(14)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 15/15: \"<</CNBalanceC(15)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 16/16: \"<</CNBalanceC(16)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 17/17: \"<</CNBalanceC(17)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 18/18: \"<</CNBalanceC(18)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 19/19: \"<</CNBalanceC(19)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 20/20: \"<</CNBalanceC(20)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 21/21: \"<</CNBalanceC(21)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 22/22: \"<</CNBalanceC(22)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 23/23: \"<</CNBalanceC(23)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 24/24: \"<</CNBalanceC(24)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 25/25: \"<</CNBalanceC(25)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 26/26: \"<</CNBalanceC(26)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 27/27: \"<</CNBalanceC(27)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 28/28: \"<</CNBalanceC(28)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 29/29: \"<</CNBalanceC(29)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 30/30: \"<</CNBalanceC(30)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 31/31: \"<</CNBalanceC(31)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 32/32: \"<</CNBalanceC(32)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 33/33: \"<</CNBalanceC(33)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 34/34: \"<</CNBalanceC(34)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 35/35: \"<</CNBalanceC(35)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 36/36: \"<</CNBalanceC(36)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 37/37: \"<</CNBalanceC(37)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 38/38: \"<</CNBalanceC(38)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 39/39: \"<</CNBalanceC(39)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 40/40: \"<</CNBalanceC(40)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 41/41: \"<</CNBalanceC(41)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 42/42: \"<</CNBalanceC(42)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 43/43: \"<</CNBalanceC(43)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 44/44: \"<</CNBalanceC(44)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 45/45: \"<</CNBalanceC(45)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 46/46: \"<</CNBalanceC(46)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 47/47: \"<</CNBalanceC(47)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 48/48: \"<</CNBalanceC(48)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 49/49: \"<</CNBalanceC(49)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceC 50/50: \"<</CNBalanceC(50)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNBalanceC" >> ${_dest}
	echo "" >> ${_dest}
}

CNBalanceM(){
	echo "*OpenUI *CNBalanceM/Magenta: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNBalanceM" >> ${_dest}
	echo "*DefaultCNBalanceM: 0" >> ${_dest}
	echo "*CNBalanceM -50/-50: \"<</CNBalanceM(-50)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -49/-49: \"<</CNBalanceM(-49)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -48/-48: \"<</CNBalanceM(-48)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -47/-47: \"<</CNBalanceM(-47)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -46/-46: \"<</CNBalanceM(-46)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -45/-45: \"<</CNBalanceM(-45)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -44/-44: \"<</CNBalanceM(-44)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -43/-43: \"<</CNBalanceM(-43)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -42/-42: \"<</CNBalanceM(-42)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -41/-41: \"<</CNBalanceM(-41)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -40/-40: \"<</CNBalanceM(-40)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -39/-39: \"<</CNBalanceM(-39)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -38/-38: \"<</CNBalanceM(-38)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -37/-37: \"<</CNBalanceM(-37)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -36/-36: \"<</CNBalanceM(-36)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -35/-35: \"<</CNBalanceM(-35)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -34/-34: \"<</CNBalanceM(-34)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -33/-33: \"<</CNBalanceM(-33)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -32/-32: \"<</CNBalanceM(-32)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -31/-31: \"<</CNBalanceM(-31)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -30/-30: \"<</CNBalanceM(-30)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -29/-29: \"<</CNBalanceM(-29)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -28/-28: \"<</CNBalanceM(-28)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -27/-27: \"<</CNBalanceM(-27)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -26/-26: \"<</CNBalanceM(-26)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -25/-25: \"<</CNBalanceM(-25)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -24/-24: \"<</CNBalanceM(-24)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -23/-23: \"<</CNBalanceM(-23)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -22/-22: \"<</CNBalanceM(-22)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -21/-21: \"<</CNBalanceM(-21)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -20/-20: \"<</CNBalanceM(-20)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -19/-19: \"<</CNBalanceM(-19)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -18/-18: \"<</CNBalanceM(-18)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -17/-17: \"<</CNBalanceM(-17)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -16/-16: \"<</CNBalanceM(-16)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -15/-15: \"<</CNBalanceM(-15)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -14/-14: \"<</CNBalanceM(-14)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -13/-13: \"<</CNBalanceM(-13)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -12/-12: \"<</CNBalanceM(-12)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -11/-11: \"<</CNBalanceM(-11)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -10/-10: \"<</CNBalanceM(-10)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -9/-9: \"<</CNBalanceM(-9)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -8/-8: \"<</CNBalanceM(-8)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -7/-7: \"<</CNBalanceM(-7)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -6/-6: \"<</CNBalanceM(-6)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -5/-5: \"<</CNBalanceM(-5)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -4/-4: \"<</CNBalanceM(-4)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -3/-3: \"<</CNBalanceM(-3)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -2/-2: \"<</CNBalanceM(-2)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM -1/-1: \"<</CNBalanceM(-1)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 0/0: \"<</CNBalanceM(0)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 1/1: \"<</CNBalanceM(1)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 2/2: \"<</CNBalanceM(2)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 3/3: \"<</CNBalanceM(3)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 4/4: \"<</CNBalanceM(4)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 5/5: \"<</CNBalanceM(5)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 6/6: \"<</CNBalanceM(6)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 7/7: \"<</CNBalanceM(7)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 8/8: \"<</CNBalanceM(8)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 9/9: \"<</CNBalanceM(9)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 10/10: \"<</CNBalanceM(10)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 11/11: \"<</CNBalanceM(11)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 12/12: \"<</CNBalanceM(12)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 13/13: \"<</CNBalanceM(13)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 14/14: \"<</CNBalanceM(14)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 15/15: \"<</CNBalanceM(15)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 16/16: \"<</CNBalanceM(16)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 17/17: \"<</CNBalanceM(17)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 18/18: \"<</CNBalanceM(18)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 19/19: \"<</CNBalanceM(19)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 20/20: \"<</CNBalanceM(20)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 21/21: \"<</CNBalanceM(21)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 22/22: \"<</CNBalanceM(22)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 23/23: \"<</CNBalanceM(23)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 24/24: \"<</CNBalanceM(24)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 25/25: \"<</CNBalanceM(25)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 26/26: \"<</CNBalanceM(26)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 27/27: \"<</CNBalanceM(27)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 28/28: \"<</CNBalanceM(28)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 29/29: \"<</CNBalanceM(29)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 30/30: \"<</CNBalanceM(30)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 31/31: \"<</CNBalanceM(31)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 32/32: \"<</CNBalanceM(32)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 33/33: \"<</CNBalanceM(33)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 34/34: \"<</CNBalanceM(34)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 35/35: \"<</CNBalanceM(35)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 36/36: \"<</CNBalanceM(36)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 37/37: \"<</CNBalanceM(37)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 38/38: \"<</CNBalanceM(38)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 39/39: \"<</CNBalanceM(39)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 40/40: \"<</CNBalanceM(40)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 41/41: \"<</CNBalanceM(41)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 42/42: \"<</CNBalanceM(42)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 43/43: \"<</CNBalanceM(43)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 44/44: \"<</CNBalanceM(44)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 45/45: \"<</CNBalanceM(45)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 46/46: \"<</CNBalanceM(46)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 47/47: \"<</CNBalanceM(47)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 48/48: \"<</CNBalanceM(48)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 49/49: \"<</CNBalanceM(49)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceM 50/50: \"<</CNBalanceM(50)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNBalanceM" >> ${_dest}
	echo "" >> ${_dest}
}

CNBalanceY(){
	echo "*OpenUI *CNBalanceY/Yellow: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNBalanceY" >> ${_dest}
	echo "*DefaultCNBalanceY: 0" >> ${_dest}
	echo "*CNBalanceY -50/-50: \"<</CNBalanceY(-50)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -49/-49: \"<</CNBalanceY(-49)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -48/-48: \"<</CNBalanceY(-48)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -47/-47: \"<</CNBalanceY(-47)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -46/-46: \"<</CNBalanceY(-46)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -45/-45: \"<</CNBalanceY(-45)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -44/-44: \"<</CNBalanceY(-44)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -43/-43: \"<</CNBalanceY(-43)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -42/-42: \"<</CNBalanceY(-42)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -41/-41: \"<</CNBalanceY(-41)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -40/-40: \"<</CNBalanceY(-40)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -39/-39: \"<</CNBalanceY(-39)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -38/-38: \"<</CNBalanceY(-38)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -37/-37: \"<</CNBalanceY(-37)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -36/-36: \"<</CNBalanceY(-36)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -35/-35: \"<</CNBalanceY(-35)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -34/-34: \"<</CNBalanceY(-34)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -33/-33: \"<</CNBalanceY(-33)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -32/-32: \"<</CNBalanceY(-32)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -31/-31: \"<</CNBalanceY(-31)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -30/-30: \"<</CNBalanceY(-30)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -29/-29: \"<</CNBalanceY(-29)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -28/-28: \"<</CNBalanceY(-28)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -27/-27: \"<</CNBalanceY(-27)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -26/-26: \"<</CNBalanceY(-26)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -25/-25: \"<</CNBalanceY(-25)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -24/-24: \"<</CNBalanceY(-24)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -23/-23: \"<</CNBalanceY(-23)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -22/-22: \"<</CNBalanceY(-22)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -21/-21: \"<</CNBalanceY(-21)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -20/-20: \"<</CNBalanceY(-20)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -19/-19: \"<</CNBalanceY(-19)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -18/-18: \"<</CNBalanceY(-18)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -17/-17: \"<</CNBalanceY(-17)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -16/-16: \"<</CNBalanceY(-16)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -15/-15: \"<</CNBalanceY(-15)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -14/-14: \"<</CNBalanceY(-14)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -13/-13: \"<</CNBalanceY(-13)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -12/-12: \"<</CNBalanceY(-12)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -11/-11: \"<</CNBalanceY(-11)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -10/-10: \"<</CNBalanceY(-10)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -9/-9: \"<</CNBalanceY(-9)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -8/-8: \"<</CNBalanceY(-8)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -7/-7: \"<</CNBalanceY(-7)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -6/-6: \"<</CNBalanceY(-6)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -5/-5: \"<</CNBalanceY(-5)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -4/-4: \"<</CNBalanceY(-4)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -3/-3: \"<</CNBalanceY(-3)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -2/-2: \"<</CNBalanceY(-2)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY -1/-1: \"<</CNBalanceY(-1)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 0/0: \"<</CNBalanceY(0)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 1/1: \"<</CNBalanceY(1)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 2/2: \"<</CNBalanceY(2)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 3/3: \"<</CNBalanceY(3)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 4/4: \"<</CNBalanceY(4)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 5/5: \"<</CNBalanceY(5)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 6/6: \"<</CNBalanceY(6)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 7/7: \"<</CNBalanceY(7)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 8/8: \"<</CNBalanceY(8)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 9/9: \"<</CNBalanceY(9)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 10/10: \"<</CNBalanceY(10)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 11/11: \"<</CNBalanceY(11)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 12/12: \"<</CNBalanceY(12)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 13/13: \"<</CNBalanceY(13)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 14/14: \"<</CNBalanceY(14)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 15/15: \"<</CNBalanceY(15)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 16/16: \"<</CNBalanceY(16)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 17/17: \"<</CNBalanceY(17)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 18/18: \"<</CNBalanceY(18)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 19/19: \"<</CNBalanceY(19)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 20/20: \"<</CNBalanceY(20)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 21/21: \"<</CNBalanceY(21)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 22/22: \"<</CNBalanceY(22)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 23/23: \"<</CNBalanceY(23)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 24/24: \"<</CNBalanceY(24)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 25/25: \"<</CNBalanceY(25)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 26/26: \"<</CNBalanceY(26)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 27/27: \"<</CNBalanceY(27)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 28/28: \"<</CNBalanceY(28)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 29/29: \"<</CNBalanceY(29)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 30/30: \"<</CNBalanceY(30)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 31/31: \"<</CNBalanceY(31)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 32/32: \"<</CNBalanceY(32)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 33/33: \"<</CNBalanceY(33)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 34/34: \"<</CNBalanceY(34)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 35/35: \"<</CNBalanceY(35)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 36/36: \"<</CNBalanceY(36)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 37/37: \"<</CNBalanceY(37)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 38/38: \"<</CNBalanceY(38)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 39/39: \"<</CNBalanceY(39)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 40/40: \"<</CNBalanceY(40)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 41/41: \"<</CNBalanceY(41)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 42/42: \"<</CNBalanceY(42)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 43/43: \"<</CNBalanceY(43)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 44/44: \"<</CNBalanceY(44)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 45/45: \"<</CNBalanceY(45)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 46/46: \"<</CNBalanceY(46)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 47/47: \"<</CNBalanceY(47)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 48/48: \"<</CNBalanceY(48)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 49/49: \"<</CNBalanceY(49)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceY 50/50: \"<</CNBalanceY(50)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNBalanceY" >> ${_dest}
	echo "" >> ${_dest}
}

CNBalanceK(){
	echo "*OpenUI *CNBalanceK/Black: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNBalanceK" >> ${_dest}
	echo "*DefaultCNBalanceK: 0" >> ${_dest}
	echo "*CNBalanceK -50/-50: \"<</CNBalanceK(-50)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -49/-49: \"<</CNBalanceK(-49)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -48/-48: \"<</CNBalanceK(-48)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -47/-47: \"<</CNBalanceK(-47)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -46/-46: \"<</CNBalanceK(-46)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -45/-45: \"<</CNBalanceK(-45)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -44/-44: \"<</CNBalanceK(-44)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -43/-43: \"<</CNBalanceK(-43)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -42/-42: \"<</CNBalanceK(-42)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -41/-41: \"<</CNBalanceK(-41)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -40/-40: \"<</CNBalanceK(-40)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -39/-39: \"<</CNBalanceK(-39)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -38/-38: \"<</CNBalanceK(-38)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -37/-37: \"<</CNBalanceK(-37)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -36/-36: \"<</CNBalanceK(-36)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -35/-35: \"<</CNBalanceK(-35)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -34/-34: \"<</CNBalanceK(-34)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -33/-33: \"<</CNBalanceK(-33)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -32/-32: \"<</CNBalanceK(-32)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -31/-31: \"<</CNBalanceK(-31)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -30/-30: \"<</CNBalanceK(-30)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -29/-29: \"<</CNBalanceK(-29)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -28/-28: \"<</CNBalanceK(-28)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -27/-27: \"<</CNBalanceK(-27)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -26/-26: \"<</CNBalanceK(-26)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -25/-25: \"<</CNBalanceK(-25)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -24/-24: \"<</CNBalanceK(-24)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -23/-23: \"<</CNBalanceK(-23)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -22/-22: \"<</CNBalanceK(-22)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -21/-21: \"<</CNBalanceK(-21)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -20/-20: \"<</CNBalanceK(-20)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -19/-19: \"<</CNBalanceK(-19)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -18/-18: \"<</CNBalanceK(-18)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -17/-17: \"<</CNBalanceK(-17)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -16/-16: \"<</CNBalanceK(-16)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -15/-15: \"<</CNBalanceK(-15)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -14/-14: \"<</CNBalanceK(-14)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -13/-13: \"<</CNBalanceK(-13)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -12/-12: \"<</CNBalanceK(-12)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -11/-11: \"<</CNBalanceK(-11)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -10/-10: \"<</CNBalanceK(-10)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -9/-9: \"<</CNBalanceK(-9)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -8/-8: \"<</CNBalanceK(-8)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -7/-7: \"<</CNBalanceK(-7)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -6/-6: \"<</CNBalanceK(-6)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -5/-5: \"<</CNBalanceK(-5)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -4/-4: \"<</CNBalanceK(-4)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -3/-3: \"<</CNBalanceK(-3)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -2/-2: \"<</CNBalanceK(-2)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK -1/-1: \"<</CNBalanceK(-1)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 0/0: \"<</CNBalanceK(0)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 1/1: \"<</CNBalanceK(1)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 2/2: \"<</CNBalanceK(2)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 3/3: \"<</CNBalanceK(3)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 4/4: \"<</CNBalanceK(4)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 5/5: \"<</CNBalanceK(5)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 6/6: \"<</CNBalanceK(6)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 7/7: \"<</CNBalanceK(7)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 8/8: \"<</CNBalanceK(8)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 9/9: \"<</CNBalanceK(9)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 10/10: \"<</CNBalanceK(10)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 11/11: \"<</CNBalanceK(11)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 12/12: \"<</CNBalanceK(12)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 13/13: \"<</CNBalanceK(13)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 14/14: \"<</CNBalanceK(14)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 15/15: \"<</CNBalanceK(15)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 16/16: \"<</CNBalanceK(16)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 17/17: \"<</CNBalanceK(17)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 18/18: \"<</CNBalanceK(18)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 19/19: \"<</CNBalanceK(19)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 20/20: \"<</CNBalanceK(20)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 21/21: \"<</CNBalanceK(21)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 22/22: \"<</CNBalanceK(22)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 23/23: \"<</CNBalanceK(23)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 24/24: \"<</CNBalanceK(24)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 25/25: \"<</CNBalanceK(25)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 26/26: \"<</CNBalanceK(26)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 27/27: \"<</CNBalanceK(27)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 28/28: \"<</CNBalanceK(28)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 29/29: \"<</CNBalanceK(29)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 30/30: \"<</CNBalanceK(30)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 31/31: \"<</CNBalanceK(31)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 32/32: \"<</CNBalanceK(32)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 33/33: \"<</CNBalanceK(33)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 34/34: \"<</CNBalanceK(34)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 35/35: \"<</CNBalanceK(35)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 36/36: \"<</CNBalanceK(36)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 37/37: \"<</CNBalanceK(37)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 38/38: \"<</CNBalanceK(38)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 39/39: \"<</CNBalanceK(39)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 40/40: \"<</CNBalanceK(40)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 41/41: \"<</CNBalanceK(41)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 42/42: \"<</CNBalanceK(42)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 43/43: \"<</CNBalanceK(43)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 44/44: \"<</CNBalanceK(44)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 45/45: \"<</CNBalanceK(45)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 46/46: \"<</CNBalanceK(46)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 47/47: \"<</CNBalanceK(47)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 48/48: \"<</CNBalanceK(48)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 49/49: \"<</CNBalanceK(49)>>setpagedevice\"" >> ${_dest}
	echo "*CNBalanceK 50/50: \"<</CNBalanceK(50)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNBalanceK" >> ${_dest}
	echo "" >> ${_dest}
}

CNGamma(){
	echo "*OpenUI *CNGamma/Brightness: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNGamma" >> ${_dest}
	echo "*DefaultCNGamma: 1.8" >> ${_dest}
	echo "*CNGamma 1.4/Light: \"<</CNGamma(1.4)>>setpagedevice\"" >> ${_dest}
	echo "*CNGamma 1.8/Normal: \"<</CNGamma(1.8)>>setpagedevice\"" >> ${_dest}
	echo "*CNGamma 2.2/Dark: \"<</CNGamma(2.2)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNGamma" >> ${_dest}
	echo "" >> ${_dest}
}

CNDensity(){
	echo "*OpenUI *CNDensity/Intensity: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNDensity" >> ${_dest}
	echo "*DefaultCNDensity: 0" >> ${_dest}
	echo "*CNDensity -50/-50: \"<</CNDensity(-50)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -49/-49: \"<</CNDensity(-49)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -48/-48: \"<</CNDensity(-48)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -47/-47: \"<</CNDensity(-47)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -46/-46: \"<</CNDensity(-46)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -45/-45: \"<</CNDensity(-45)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -44/-44: \"<</CNDensity(-44)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -43/-43: \"<</CNDensity(-43)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -42/-42: \"<</CNDensity(-42)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -41/-41: \"<</CNDensity(-41)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -40/-40: \"<</CNDensity(-40)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -39/-39: \"<</CNDensity(-39)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -38/-38: \"<</CNDensity(-38)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -37/-37: \"<</CNDensity(-37)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -36/-36: \"<</CNDensity(-36)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -35/-35: \"<</CNDensity(-35)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -34/-34: \"<</CNDensity(-34)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -33/-33: \"<</CNDensity(-33)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -32/-32: \"<</CNDensity(-32)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -31/-31: \"<</CNDensity(-31)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -30/-30: \"<</CNDensity(-30)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -29/-29: \"<</CNDensity(-29)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -28/-28: \"<</CNDensity(-28)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -27/-27: \"<</CNDensity(-27)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -26/-26: \"<</CNDensity(-26)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -25/-25: \"<</CNDensity(-25)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -24/-24: \"<</CNDensity(-24)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -23/-23: \"<</CNDensity(-23)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -22/-22: \"<</CNDensity(-22)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -21/-21: \"<</CNDensity(-21)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -20/-20: \"<</CNDensity(-20)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -19/-19: \"<</CNDensity(-19)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -18/-18: \"<</CNDensity(-18)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -17/-17: \"<</CNDensity(-17)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -16/-16: \"<</CNDensity(-16)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -15/-15: \"<</CNDensity(-15)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -14/-14: \"<</CNDensity(-14)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -13/-13: \"<</CNDensity(-13)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -12/-12: \"<</CNDensity(-12)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -11/-11: \"<</CNDensity(-11)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -10/-10: \"<</CNDensity(-10)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -9/-9: \"<</CNDensity(-9)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -8/-8: \"<</CNDensity(-8)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -7/-7: \"<</CNDensity(-7)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -6/-6: \"<</CNDensity(-6)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -5/-5: \"<</CNDensity(-5)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -4/-4: \"<</CNDensity(-4)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -3/-3: \"<</CNDensity(-3)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -2/-2: \"<</CNDensity(-2)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity -1/-1: \"<</CNDensity(-1)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 0/0: \"<</CNDensity(0)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 1/1: \"<</CNDensity(1)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 2/2: \"<</CNDensity(2)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 3/3: \"<</CNDensity(3)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 4/4: \"<</CNDensity(4)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 5/5: \"<</CNDensity(5)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 6/6: \"<</CNDensity(6)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 7/7: \"<</CNDensity(7)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 8/8: \"<</CNDensity(8)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 9/9: \"<</CNDensity(9)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 10/10: \"<</CNDensity(10)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 11/11: \"<</CNDensity(11)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 12/12: \"<</CNDensity(12)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 13/13: \"<</CNDensity(13)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 14/14: \"<</CNDensity(14)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 15/15: \"<</CNDensity(15)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 16/16: \"<</CNDensity(16)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 17/17: \"<</CNDensity(17)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 18/18: \"<</CNDensity(18)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 19/19: \"<</CNDensity(19)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 20/20: \"<</CNDensity(20)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 21/21: \"<</CNDensity(21)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 22/22: \"<</CNDensity(22)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 23/23: \"<</CNDensity(23)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 24/24: \"<</CNDensity(24)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 25/25: \"<</CNDensity(25)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 26/26: \"<</CNDensity(26)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 27/27: \"<</CNDensity(27)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 28/28: \"<</CNDensity(28)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 29/29: \"<</CNDensity(29)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 30/30: \"<</CNDensity(30)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 31/31: \"<</CNDensity(31)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 32/32: \"<</CNDensity(32)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 33/33: \"<</CNDensity(33)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 34/34: \"<</CNDensity(34)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 35/35: \"<</CNDensity(35)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 36/36: \"<</CNDensity(36)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 37/37: \"<</CNDensity(37)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 38/38: \"<</CNDensity(38)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 39/39: \"<</CNDensity(39)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 40/40: \"<</CNDensity(40)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 41/41: \"<</CNDensity(41)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 42/42: \"<</CNDensity(42)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 43/43: \"<</CNDensity(43)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 44/44: \"<</CNDensity(44)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 45/45: \"<</CNDensity(45)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 46/46: \"<</CNDensity(46)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 47/47: \"<</CNDensity(47)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 48/48: \"<</CNDensity(48)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 49/49: \"<</CNDensity(49)>>setpagedevice\"" >> ${_dest}
	echo "*CNDensity 50/50: \"<</CNDensity(50)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNDensity" >> ${_dest}
	echo "" >> ${_dest}
}

CNContrast(){
	echo "*OpenUI *CNContrast/Contrast: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNContrast" >> ${_dest}
	echo "*DefaultCNContrast: 0" >> ${_dest}
	echo "*CNContrast -50/-50: \"<</CNContrast(-50)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -49/-49: \"<</CNContrast(-49)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -48/-48: \"<</CNContrast(-48)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -47/-47: \"<</CNContrast(-47)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -46/-46: \"<</CNContrast(-46)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -45/-45: \"<</CNContrast(-45)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -44/-44: \"<</CNContrast(-44)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -43/-43: \"<</CNContrast(-43)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -42/-42: \"<</CNContrast(-42)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -41/-41: \"<</CNContrast(-41)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -40/-40: \"<</CNContrast(-40)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -39/-39: \"<</CNContrast(-39)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -38/-38: \"<</CNContrast(-38)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -37/-37: \"<</CNContrast(-37)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -36/-36: \"<</CNContrast(-36)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -35/-35: \"<</CNContrast(-35)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -34/-34: \"<</CNContrast(-34)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -33/-33: \"<</CNContrast(-33)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -32/-32: \"<</CNContrast(-32)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -31/-31: \"<</CNContrast(-31)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -30/-30: \"<</CNContrast(-30)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -29/-29: \"<</CNContrast(-29)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -28/-28: \"<</CNContrast(-28)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -27/-27: \"<</CNContrast(-27)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -26/-26: \"<</CNContrast(-26)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -25/-25: \"<</CNContrast(-25)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -24/-24: \"<</CNContrast(-24)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -23/-23: \"<</CNContrast(-23)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -22/-22: \"<</CNContrast(-22)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -21/-21: \"<</CNContrast(-21)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -20/-20: \"<</CNContrast(-20)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -19/-19: \"<</CNContrast(-19)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -18/-18: \"<</CNContrast(-18)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -17/-17: \"<</CNContrast(-17)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -16/-16: \"<</CNContrast(-16)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -15/-15: \"<</CNContrast(-15)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -14/-14: \"<</CNContrast(-14)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -13/-13: \"<</CNContrast(-13)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -12/-12: \"<</CNContrast(-12)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -11/-11: \"<</CNContrast(-11)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -10/-10: \"<</CNContrast(-10)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -9/-9: \"<</CNContrast(-9)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -8/-8: \"<</CNContrast(-8)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -7/-7: \"<</CNContrast(-7)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -6/-6: \"<</CNContrast(-6)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -5/-5: \"<</CNContrast(-5)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -4/-4: \"<</CNContrast(-4)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -3/-3: \"<</CNContrast(-3)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -2/-2: \"<</CNContrast(-2)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast -1/-1: \"<</CNContrast(-1)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 0/0: \"<</CNContrast(0)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 1/1: \"<</CNContrast(1)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 2/2: \"<</CNContrast(2)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 3/3: \"<</CNContrast(3)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 4/4: \"<</CNContrast(4)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 5/5: \"<</CNContrast(5)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 6/6: \"<</CNContrast(6)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 7/7: \"<</CNContrast(7)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 8/8: \"<</CNContrast(8)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 9/9: \"<</CNContrast(9)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 10/10: \"<</CNContrast(10)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 11/11: \"<</CNContrast(11)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 12/12: \"<</CNContrast(12)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 13/13: \"<</CNContrast(13)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 14/14: \"<</CNContrast(14)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 15/15: \"<</CNContrast(15)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 16/16: \"<</CNContrast(16)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 17/17: \"<</CNContrast(17)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 18/18: \"<</CNContrast(18)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 19/19: \"<</CNContrast(19)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 20/20: \"<</CNContrast(20)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 21/21: \"<</CNContrast(21)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 22/22: \"<</CNContrast(22)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 23/23: \"<</CNContrast(23)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 24/24: \"<</CNContrast(24)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 25/25: \"<</CNContrast(25)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 26/26: \"<</CNContrast(26)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 27/27: \"<</CNContrast(27)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 28/28: \"<</CNContrast(28)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 29/29: \"<</CNContrast(29)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 30/30: \"<</CNContrast(30)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 31/31: \"<</CNContrast(31)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 32/32: \"<</CNContrast(32)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 33/33: \"<</CNContrast(33)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 34/34: \"<</CNContrast(34)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 35/35: \"<</CNContrast(35)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 36/36: \"<</CNContrast(36)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 37/37: \"<</CNContrast(37)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 38/38: \"<</CNContrast(38)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 39/39: \"<</CNContrast(39)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 40/40: \"<</CNContrast(40)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 41/41: \"<</CNContrast(41)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 42/42: \"<</CNContrast(42)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 43/43: \"<</CNContrast(43)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 44/44: \"<</CNContrast(44)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 45/45: \"<</CNContrast(45)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 46/46: \"<</CNContrast(46)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 47/47: \"<</CNContrast(47)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 48/48: \"<</CNContrast(48)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 49/49: \"<</CNContrast(49)>>setpagedevice\"" >> ${_dest}
	echo "*CNContrast 50/50: \"<</CNContrast(50)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNContrast" >> ${_dest}
	echo "" >> ${_dest}
}

CNTone(){
	echo "*OpenUI *CNTone/Tone: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNTone" >> ${_dest}
	echo "*DefaultCNTone: 0" >> ${_dest}
	echo "*CNTone -50/-50: \"<</CNTone(-50)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -49/-49: \"<</CNTone(-49)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -48/-48: \"<</CNTone(-48)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -47/-47: \"<</CNTone(-47)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -46/-46: \"<</CNTone(-46)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -45/-45: \"<</CNTone(-45)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -44/-44: \"<</CNTone(-44)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -43/-43: \"<</CNTone(-43)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -42/-42: \"<</CNTone(-42)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -41/-41: \"<</CNTone(-41)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -40/-40: \"<</CNTone(-40)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -39/-39: \"<</CNTone(-39)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -38/-38: \"<</CNTone(-38)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -37/-37: \"<</CNTone(-37)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -36/-36: \"<</CNTone(-36)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -35/-35: \"<</CNTone(-35)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -34/-34: \"<</CNTone(-34)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -33/-33: \"<</CNTone(-33)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -32/-32: \"<</CNTone(-32)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -31/-31: \"<</CNTone(-31)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -30/-30: \"<</CNTone(-30)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -29/-29: \"<</CNTone(-29)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -28/-28: \"<</CNTone(-28)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -27/-27: \"<</CNTone(-27)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -26/-26: \"<</CNTone(-26)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -25/-25: \"<</CNTone(-25)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -24/-24: \"<</CNTone(-24)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -23/-23: \"<</CNTone(-23)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -22/-22: \"<</CNTone(-22)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -21/-21: \"<</CNTone(-21)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -20/-20: \"<</CNTone(-20)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -19/-19: \"<</CNTone(-19)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -18/-18: \"<</CNTone(-18)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -17/-17: \"<</CNTone(-17)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -16/-16: \"<</CNTone(-16)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -15/-15: \"<</CNTone(-15)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -14/-14: \"<</CNTone(-14)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -13/-13: \"<</CNTone(-13)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -12/-12: \"<</CNTone(-12)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -11/-11: \"<</CNTone(-11)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -10/-10: \"<</CNTone(-10)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -9/-9: \"<</CNTone(-9)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -8/-8: \"<</CNTone(-8)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -7/-7: \"<</CNTone(-7)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -6/-6: \"<</CNTone(-6)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -5/-5: \"<</CNTone(-5)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -4/-4: \"<</CNTone(-4)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -3/-3: \"<</CNTone(-3)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -2/-2: \"<</CNTone(-2)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone -1/-1: \"<</CNTone(-1)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 0/0: \"<</CNTone(0)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 1/1: \"<</CNTone(1)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 2/2: \"<</CNTone(2)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 3/3: \"<</CNTone(3)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 4/4: \"<</CNTone(4)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 5/5: \"<</CNTone(5)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 6/6: \"<</CNTone(6)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 7/7: \"<</CNTone(7)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 8/8: \"<</CNTone(8)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 9/9: \"<</CNTone(9)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 10/10: \"<</CNTone(10)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 11/11: \"<</CNTone(11)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 12/12: \"<</CNTone(12)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 13/13: \"<</CNTone(13)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 14/14: \"<</CNTone(14)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 15/15: \"<</CNTone(15)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 16/16: \"<</CNTone(16)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 17/17: \"<</CNTone(17)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 18/18: \"<</CNTone(18)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 19/19: \"<</CNTone(19)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 20/20: \"<</CNTone(20)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 21/21: \"<</CNTone(21)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 22/22: \"<</CNTone(22)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 23/23: \"<</CNTone(23)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 24/24: \"<</CNTone(24)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 25/25: \"<</CNTone(25)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 26/26: \"<</CNTone(26)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 27/27: \"<</CNTone(27)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 28/28: \"<</CNTone(28)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 29/29: \"<</CNTone(29)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 30/30: \"<</CNTone(30)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 31/31: \"<</CNTone(31)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 32/32: \"<</CNTone(32)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 33/33: \"<</CNTone(33)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 34/34: \"<</CNTone(34)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 35/35: \"<</CNTone(35)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 36/36: \"<</CNTone(36)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 37/37: \"<</CNTone(37)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 38/38: \"<</CNTone(38)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 39/39: \"<</CNTone(39)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 40/40: \"<</CNTone(40)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 41/41: \"<</CNTone(41)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 42/42: \"<</CNTone(42)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 43/43: \"<</CNTone(43)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 44/44: \"<</CNTone(44)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 45/45: \"<</CNTone(45)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 46/46: \"<</CNTone(46)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 47/47: \"<</CNTone(47)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 48/48: \"<</CNTone(48)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 49/49: \"<</CNTone(49)>>setpagedevice\"" >> ${_dest}
	echo "*CNTone 50/50: \"<</CNTone(50)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNTone" >> ${_dest}
	echo "" >> ${_dest}
}

CNExtension(){
	echo "*OpenUI *CNExtension/Amount of Extension: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNExtension" >> ${_dest}
	echo "*DefaultCNExtension: 2" >> ${_dest}
	echo "*CNExtension 0/0: \"<</CNExtension(0)>>setpagedevice\"" >> ${_dest}
	echo "*CNExtension 1/1: \"<</CNExtension(1)>>setpagedevice\"" >> ${_dest}
	echo "*CNExtension 2/2: \"<</CNExtension(2)>>setpagedevice\"" >> ${_dest}
	echo "*CNExtension 3/3: \"<</CNExtension(3)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNExtension" >> ${_dest}
	echo "" >> ${_dest}
}

Resolution(){
	echo "*OpenUI *Resolution/Output Resolution: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *Resolution" >> ${_dest}
	echo "*DefaultResolution: 600dpi" >> ${_dest}
	echo "*Resolution 600dpi/600 dpi: \"<</HWResolution[600 600]>>setpagedevice\"" >> ${_dest}
	echo "*Resolution 1200dpi/1200 dpi: \"<</HWResolution[1200 1200]>>setpagedevice\"" >> ${_dest}
	echo "*Resolution 2400dpi/2400 dpi: \"<</HWResolution[2400 2400]>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *Resolution" >> ${_dest}
	echo "" >> ${_dest}
}

ColorModel(){
	echo "*OpenUI *ColorModel/Color Model: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *ColorModel" >> ${_dest}
	echo "*DefaultColorModel: RGB" >> ${_dest}
	echo "*ColorModel Gray/Grayscale: \"<</cupsColorSpace 0/cupsColorOrder 0/cupsCompression 0/cupsBitsPerColor 8>>setpagedevice\"" >> ${_dest}
	echo "*ColorModel Black/Inverted Grayscale: \"<</cupsColorSpace 3/cupsColorOrder 0/cupsCompression 0/cupsBitsPerColor 8>>setpagedevice\"" >> ${_dest}
	echo "*ColorModel RGB/RGB Color: \"<</cupsColorSpace 1/cupsColorOrder 0/cupsCompression 0/cupsBitsPerColor 8>>setpagedevice\"" >> ${_dest}
	echo "*ColorModel CMY/CMY Color: \"<</cupsColorSpace 4/cupsColorOrder 0/cupsCompression 0/cupsBitsPerColor 8>>setpagedevice\"" >> ${_dest}
	echo "*ColorModel CMYK/CMYK: \"<</cupsColorSpace 6/cupsColorOrder 0/cupsCompression 0/cupsBitsPerColor 8>>setpagedevice\"" >> ${_dest}
	echo "*ColorModel KCMY/KCMY: \"<</cupsColorSpace 8/cupsColorOrder 0/cupsCompression 0/cupsBitsPerColor 8>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *ColorModel" >> ${_dest}
	echo "" >> ${_dest}
}

CNInkCartridgeSettings(){
	echo "*OpenUI *CNInkCartridgeSettings/Ink Cartridge Settings: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *CNInkCartridgeSettings" >> ${_dest}
	echo "*DefaultCNInkCartridgeSettings: bkcolor" >> ${_dest}
	echo "*CNInkCartridgeSettings color/Color Only: \"<</CNInkCartridgeSettings(color)>>setpagedevice\"" >> ${_dest}
	echo "*CNInkCartridgeSettings bk/Black Only: \"<</CNInkCartridgeSettings(bk)>>setpagedevice\"" >> ${_dest}
	echo "*CNInkCartridgeSettings bkcolor/Both Black and Color: \"<</CNInkCartridgeSettings(bkcolor)>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *CNInkCartridgeSettings" >> ${_dest}
	echo "" >> ${_dest}
}


Duplex(){
	echo "*OpenUI *Duplex/Duplex Printing: PickOne" >> ${_dest}
#	echo "*OrderDependency: 0 AnySetup *Duplex" >> ${_dest}
	echo "*DefaultDuplex: None" >> ${_dest}
	echo "*Duplex None/OFF: \"<</Duplex false>>setpagedevice\"" >> ${_dest}
	echo "*Duplex DuplexNoTumble/ON (Long-side stapling): \"<</Duplex true/Tumble false>>setpagedevice\"" >> ${_dest}
	echo "*Duplex DuplexTumble/ON (Short-side stapling): \"<</Duplex true/Tumble true>>setpagedevice\"" >> ${_dest}
	echo "*CloseUI: *Duplex" >> ${_dest}
	echo "" >> ${_dest}
}

CNInternal(){
	echo "" >> ${_dest}
	echo "*%" >> ${_dest}
	echo "*% Internal for Canon Printers" >> ${_dest}
	echo "*%" >> ${_dest}
}

CNOptKey_PageSize(){
	echo "*%CNPpdToOptKey PageSize --papersize" >> ${_dest}
}

CNOptKey_MediaType(){
	echo "*%CNPpdToOptKey MediaType --media" >> ${_dest}
}

CNOptKey_InputSlot(){
	echo "*%CNPpdToOptKey InputSlot --paperload" >> ${_dest}
}

CNOptKey_CNCartridge(){
	echo "*%CNPpdToOptKey CNCartridge --cartridge" >> ${_dest}
}

CNOptKey_CNQuality(){
	echo "*%CNPpdToOptKey CNQuality --quality" >> ${_dest}
}

CNOptKey_CNHalftoning(){
	echo "*%CNPpdToOptKey CNHalftoning --halftoning" >> ${_dest}
}

CNOptKey_CNRenderIntent(){
	echo "*%CNPpdToOptKey CNRenderIntent --renderintent" >> ${_dest}
}

CNOptKey_CNGamma(){
	echo "*%CNPpdToOptKey CNGamma --gamma" >> ${_dest}
}

CNOptKey_CNBalanceC(){
	echo "*%CNPpdToOptKey CNBalanceC --balance_c" >> ${_dest}
}

CNOptKey_CNBalanceM(){
	echo "*%CNPpdToOptKey CNBalanceM --balance_m" >> ${_dest}
}

CNOptKey_CNBalanceY(){
	echo "*%CNPpdToOptKey CNBalanceY --balance_y" >> ${_dest}
}

CNOptKey_CNBalanceK(){
	echo "*%CNPpdToOptKey CNBalanceK --balance_k" >> ${_dest}
}

CNOptKey_CNDensity(){
	echo "*%CNPpdToOptKey CNDensity --density" >> ${_dest}
}

CNOptKey_CNGrayscale(){
	echo "*%CNPpdToOptKey CNGrayscale --grayscale" >> ${_dest}
}

CNOptKey_CNCopies(){
	echo "*%CNPpdToOptKey CNCopies --copies" >> ${_dest}
}

CNOptKey_CNPaperGap(){
	echo "*%CNPpdToOptKey CNPaperGap --papergap" >> ${_dest}
}

CNOptKey_Duplex(){
	echo "*%CNPpdToOptKey Duplex --duplex" >> ${_dest}
}

CNOptKey_CNStapleSide(){
	echo "*%CNPpdToOptKey CNStapleSide --stapleside" >> ${_dest}
}

CNOptKey_CNContrast(){
	echo "*%CNPpdToOptKey CNContrast --contrast" >> ${_dest}
}

CNOptKey_CNInkCartridgeSettings(){
	echo "*%CNPpdToOptKey CNInkCartridgeSettings --inkcartridgesettings" >> ${_dest}
}

CNOptKey_CNExtension(){
	echo "*%CNPpdToOptKey CNExtension --extension" >> ${_dest}
}

CNOptKey_CNTone(){
	echo "*%CNPpdToOptKey CNTone --tone" >> ${_dest}
}

CNOptKey_EnableDEVURIOption(){
	echo "" >> ${_dest}
	echo "*%CNPpdOptions EnableDEVURIOption" >> ${_dest}
}

CNOptKey_EnableFrontEnd(){
	echo "*%CNPpdOptions EnableFrontEnd" >> ${_dest}
}

CNOptKey_EnableCNGPIJMNT(){
	echo "*%CNPpdOptions EnableCNGPIJMNT" >> ${_dest}
}


CNInternalVersion(){
	echo "" >> ${_dest}
	echo "*%" >> ${_dest}
	echo "*% internalversion : ${_ver}.02.001" >> ${_dest}
	echo "*%" >> ${_dest}
	echo "" >> ${_dest}
}
