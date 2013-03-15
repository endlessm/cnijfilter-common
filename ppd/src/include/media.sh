#/bin/bash



MediaType(){
	media_type=`cat include/canon_media.txt | grep "${model_master,,}"`
	if [ ! "${media_type}" = "" ]; then
		_plain=`echo ${media_type} | cut '-d-' -f1`
		_prophoto=`echo ${media_type} | cut '-d-' -f2`
		_superphoto=`echo ${media_type} | cut '-d-' -f3`
		_glossygold=`echo ${media_type} | cut '-d-' -f4`
		_prophoto2=`echo ${media_type} | cut '-d-' -f5`
		_proplatinum=`echo ${media_type} | cut '-d-' -f6`
		_luster=`echo ${media_type} | cut '-d-' -f7`
		_doublesidephoto=`echo ${media_type} | cut '-d-' -f8`
		_semigloss=`echo ${media_type} | cut '-d-' -f9`
		_glossypaper=`echo ${media_type} | cut '-d-' -f10`
		_matte=`echo ${media_type} | cut '-d-' -f11`
		_fineartphotorag=`echo ${media_type} | cut '-d-' -f12`
		_otherfineart=`echo ${media_type} | cut '-d-' -f13`
		_envelope=`echo ${media_type} | cut '-d-' -f14`
		_postcardaddress=`echo ${media_type} | cut '-d-' -f15`
		_ijpostcard=`echo ${media_type} | cut '-d-' -f16`
		_glossypost=`echo ${media_type} | cut '-d-' -f17`
		_prophotopost=`echo ${media_type} | cut '-d-' -f18`
		_postcard=`echo ${media_type} | cut '-d-' -f19`
		_photocard=`echo ${media_type} | cut '-d-' -f20`
		_higloss2=`echo ${media_type} | cut '-d-' -f21`
		_highres=`echo ${media_type} | cut '-d-' -f22`
		_tshirt=`echo ${media_type} | cut '-d-' -f23`
		_ohp=`echo ${media_type} | cut '-d-' -f24`
		_otherphoto=`echo ${media_type} | cut '-d-' -f25`
		echo "*OpenUI *MediaType/Media Type: PickOne" >> ${_dest}
		echo "*DefaultMediaType: plain" >> ${_dest}
		if [ ${_plain} = "1" ]; then
			echo "*MediaType plain/Plain Paper: \"<</MediaType(plain)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_prophoto} = "1" ]; then
			echo "*MediaType prophoto/Photo Paper Pro: \"<</MediaType(prophoto)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_superphoto} = "1" ]; then
			echo "*MediaType superphoto/Photo Paper Plus Glossy: \"<</MediaType(superphoto)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_glossygold} = "1" ]; then
			echo "*MediaType glossygold/Photo Paper Plus Glossy II: \"<</MediaType(glossygold)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_prophoto2} = "1" ]; then
			echo "*MediaType prophoto2/Photo Paper Pro II: \"<</MediaType(prophoto2)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_proplatinum} = "1" ]; then
			echo "*MediaType proplatinum/Photo Paper Pro Platinum: \"<</MediaType(proplatinum)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_luster} = "1" ]; then
			echo "*MediaType luster/Photo Paper Pro Luster: \"<</MediaType(luster)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_doublesidephoto} = "1" ]; then
			echo "*MediaType doublesidephoto/Photo Paper Plus Double Sided: \"<</MediaType(doublesidephoto)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_semigloss} = "1" ]; then
			echo "*MediaType semigloss/Photo Paper Plus Semi-gloss: \"<</MediaType(semigloss)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_glossypaper} = "1" ]; then
			echo "*MediaType glossypaper/Glossy Photo Paper: \"<</MediaType(glossypaper)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_matte} = "1" ]; then
			echo "*MediaType matte/Matte Photo Paper: \"<</MediaType(matte)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_fineartphotorag} = "1" ]; then
			echo "*MediaType fineartphotorag/Fine Art \"Photo Rag\": \"<</MediaType(fineartphotorag)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_otherfineart} = "1" ]; then
			echo "*MediaType otherfineart/Other Fine Art Paper: \"<</MediaType(otherfineart)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_envelope} = "1" ]; then
			echo "*MediaType envelope/Envelope: \"<</MediaType(envelope)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_postcardaddress} = "1" ]; then
			echo "*MediaType postcardaddress/Hagaki A: \"<</MediaType(postcardaddress)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_ijpostcard} = "1" ]; then
			echo "*MediaType ijpostcard/Ink Jet Hagaki: \"<</MediaType(ijpostcard)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_glossypost} = "1" ]; then
			echo "*MediaType glossypost/Hagaki K: \"<</MediaType(glossypost)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_prophotopost} = "1" ]; then
			echo "*MediaType prophotopost/Hagaki P: \"<</MediaType(prophotopost)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_postcard} = "1" ]; then
			echo "*MediaType postcard/Hagaki: \"<</MediaType(postcard)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_photocard} = "1" ]; then
			echo "*MediaType photocard/Glossy Photo Cards: \"<</MediaType(photocard)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_higloss2} = "1" ]; then
			echo "*MediaType higloss2/High Gloss Photo Film: \"<</MediaType(higloss2)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_highres} = "1" ]; then
			echo "*MediaType highres/High Resolution Paper: \"<</MediaType(highres)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_tshirt} = "1" ]; then
			echo "*MediaType tshirt/T-Shirt Transfers: \"<</MediaType(tshirt)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_ohp} = "1" ]; then
			echo "*MediaType ohp/Transparency: \"<</MediaType(ohp)>>setpagedevice\"" >> ${_dest}
		fi
		if [ ${_otherphoto} = "1" ]; then
			echo "*MediaType otherphoto/Other Photo Paper: \"<</MediaType(otherphoto)>>setpagedevice\"" >> ${_dest}
		fi
		echo "*CloseUI: *MediaType" >> ${_dest}
	fi
	echo "" >> ${_dest}
}



