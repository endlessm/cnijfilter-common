#/bin/bash



Font(){
	__Font=`cat include/canon_font.txt | grep "${model_master,,}"`
	if [ ! "${__Font}" = "" ]; then
		_font=`echo ${__Font} | cut '-d-' -f1`

		if [ ${_font} = "1" ]; then
			echo "*DefaultFont: Courier" >> ${_dest}
			echo "*Font AvantGarde-Book: Standard \"(001.006S)\" Standard ROM" >> ${_dest}
			echo "*Font AvantGarde-BookOblique: Standard \"(001.006S)\" Standard ROM" >> ${_dest}
			echo "*Font AvantGarde-Demi: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font AvantGarde-DemiOblique: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font Bookman-Demi: Standard \"(001.004S)\" Standard ROM" >> ${_dest}
			echo "*Font Bookman-DemiItalic: Standard \"(001.004S)\" Standard ROM" >> ${_dest}
			echo "*Font Bookman-Light: Standard \"(001.004S)\" Standard ROM" >> ${_dest}
			echo "*Font Bookman-LightItalic: Standard \"(001.004S)\" Standard ROM" >> ${_dest}
			echo "*Font Courier: Standard \"(002.004S)\" Standard ROM" >> ${_dest}
			echo "*Font Courier-Bold: Standard \"(002.004S)\" Standard ROM" >> ${_dest}
			echo "*Font Courier-BoldOblique: Standard \"(002.004S)\" Standard ROM" >> ${_dest}
			echo "*Font Courier-Oblique: Standard \"(002.004S)\" Standard ROM" >> ${_dest}
			echo "*Font Helvetica: Standard \"(001.006S)\" Standard ROM" >> ${_dest}
			echo "*Font Helvetica-Bold: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font Helvetica-BoldOblique: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font Helvetica-Narrow: Standard \"(001.006S)\" Standard ROM" >> ${_dest}
			echo "*Font Helvetica-Narrow-Bold: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font Helvetica-Narrow-BoldOblique: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font Helvetica-Narrow-Oblique: Standard \"(001.006S)\" Standard ROM" >> ${_dest}
			echo "*Font Helvetica-Oblique: Standard \"(001.006S)\" Standard ROM" >> ${_dest}
			echo "*Font NewCenturySchlbk-Bold: Standard \"(001.009S)\" Standard ROM" >> ${_dest}
			echo "*Font NewCenturySchlbk-BoldItalic: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font NewCenturySchlbk-Italic: Standard \"(001.006S)\" Standard ROM" >> ${_dest}
			echo "*Font NewCenturySchlbk-Roman: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font Palatino-Bold: Standard \"(001.005S)\" Standard ROM" >> ${_dest}
			echo "*Font Palatino-BoldItalic: Standard \"(001.005S)\" Standard ROM" >> ${_dest}
			echo "*Font Palatino-Italic: Standard \"(001.005S)\" Standard ROM" >> ${_dest}
			echo "*Font Palatino-Roman: Standard \"(001.005S)\" Standard ROM" >> ${_dest}
			echo "*Font Symbol: Special \"(001.007S)\" Special ROM" >> ${_dest}
			echo "*Font Times-Bold: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font Times-BoldItalic: Standard \"(001.009S)\" Standard ROM" >> ${_dest}
			echo "*Font Times-Italic: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font Times-Roman: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font ZapfChancery-MediumItalic: Standard \"(001.007S)\" Standard ROM" >> ${_dest}
			echo "*Font ZapfDingbats: Special \"(001.004S)\" Standard ROM" >> ${_dest}
			echo "" >> ${_dest}
		fi

		if [ ${_font} = "2" ]; then
			echo "*DefaultFont: Courier" >> ${_dest}
			echo "*Font Courier: Standard \"(001.001)\" Standard ROM" >> ${_dest}
			echo "" >> ${_dest}
		fi
	fi
}
