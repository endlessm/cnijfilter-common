#/bin/bash




translate(){
#ls -1 ppd/*.ppd > file_lists2

for lng in cs da de es fi fr el hu it nl no pl pt ru sv tr ko zh zh_TW th id ja
do
	echo "translate ${lng} ${model_smol}"
	for _media in manual asf asf2bin auto cassette cassette1 cassette2 cassetteauto continuous front front2 frontplain switch consecutive1 consecutive2 tractor
	do
		_find=`cat ${_dest} | grep "*InputSlot ${_media}/"`
		if [ ! "${_find}" = "" ]; then
			_find=`cat lang/${lng}.translate | grep "*${lng}.InputSlot ${_media}/"`
			if [ ! "${_find}" = "" ]; then
				echo ${_find} >> ${_dest}
			fi
		fi
	done

	for _media in CNMain MediaType InputSlot CNQuality CNGrayscale CNPagesetup PageSize Duplex CNBorderless CNExtension CNHalftoning CNRenderIntent CNPaperGap CNColorAdjust CNBalanceC CNBalanceM CNBalanceY CNBalanceK CNGamma CNDensity CNContrast CNTone CNInkCartridgeSettings
	do
		_find=`cat ${_dest} | grep "*OpenGroup: \*${_media}/"`
		if [ ! "${_find}" = "" ]; then
			_find=`cat lang/${lng}.translate | grep "*${lng}.Translation ${_media}/" | cut '-d/' -f2`
			if [ ! "${_find}" = "" ]; then
				echo "*${lng}.Translation *${_media}/${_find}" >> ${_dest}
			fi
		else
			_find=`cat ${_dest} | grep "*OpenUI \*${_media}/"`
			if [ ! "${_find}" = "" ]; then
				_find=`cat lang/${lng}.translate | grep "*${lng}.Translation ${_media}/"`
				if [ ! "${_find}" = "" ]; then
					echo ${_find} >> ${_dest}
				fi
			fi
		fi
	done

	for _media in DuplexNoTumble DuplexTumble
	do
		_find=`cat ${_dest} | grep "*Duplex ${_media}/"`
		if [ ! "${_find}" = "" ]; then
			_find=`cat lang/${lng}.translate | grep "*${lng}.Duplex ${_media}/"`
			if [ ! "${_find}" = "" ]; then
				echo ${_find} >> ${_dest}
			fi
		fi
	done

	for _media in 1.4 1.8 2.2
	do
		_find=`cat ${_dest} | grep "*CNGamma ${_media}/"`
		if [ ! "${_find}" = "" ]; then
			_find=`cat lang/${lng}.translate | grep "*${lng}.CNGamma ${_media}/"`
			if [ ! "${_find}" = "" ]; then
				echo ${_find} >> ${_dest}
			fi
		fi
	done

	for _media in color bk bkcolor
	do
		_find=`cat ${_dest} | grep "*CNInkCartridgeSettings ${_media}/"`
		if [ ! "${_find}" = "" ]; then
			_find=`cat lang/${lng}.translate | grep "*${lng}.CNInkCartridgeSettings ${_media}/"`
			if [ ! "${_find}" = "" ]; then
				echo ${_find} >> ${_dest}
			fi
		fi
	done

	for _media in 1 4
	do
		_find=`cat ${_dest} | grep "*CNQuality ${_media}/"`
		if [ ! "${_find}" = "" ]; then
			_find=`cat lang/${lng}.translate | grep "*${lng}.CNQuality ${_media}/"`
			if [ ! "${_find}" = "" ]; then
				echo ${_find} >> ${_dest}
			fi
		fi
	done

	for _media in Letter Letter.bl Legal ledger ledger.bl A5 A4 A4.bl a3 a3.bl a3plus a3plus.bl B5 b4 4X6 4X6.bl 4X8 4X8.bl 5X7 5X7.bl 8X10 8X10.bl 10X12 10X12.bl l l.bl 2l 2l.bl letterfineart35 a4fineart35 postcard postcard.bl postdbl panorama envelop10p envelopdlp envj4p envj6p creditcard creditcard.bl businesscard businesscard.bl wide wide.bl fineartletter finearta4 
	do
		_find=`cat ${_dest} | grep "*PageSize ${_media}/"`
		if [ ! "${_find}" = "" ]; then
			_find=`cat lang/${lng}.translate | grep "*${lng}.PageSize ${_media}/"`
			if [ ! "${_find}" = "" ]; then
				echo ${_find} >> ${_dest}
			fi
		fi
	done

	for _media in plain prophoto superphoto glossygold prophoto2 proplatinum luster doublesidephoto semigloss glossypaper matte fineartphotorag otherfineart envelope postcardaddress ijpostcard glossypost prophotopost postcard_type photocard higloss2 highres tshirt ohp otherphoto
	do
		_find=`cat ${_dest} | grep "*MediaType ${_media}/"`
		if [ ! "${_find}" = "" ]; then
			_find=`cat lang/${lng}.translate | grep "*${lng}.MediaType ${_media}/"`
			if [ ! "${_find}" = "" ]; then
				echo ${_find} >> ${_dest}
			fi
		fi
	done

done

#rm -f file_lists2
}


