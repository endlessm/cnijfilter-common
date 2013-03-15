#/bin/bash

ImageableArea(){
	_ImageableArea=`cat include/canon_pagesize.txt | grep "${model_master,,}"`
	if [ ! "${_ImageableArea}" = "" ]; then
		_Letter=`echo ${_ImageableArea} | cut '-d-' -f1`
		_Legal=`echo ${_ImageableArea} | cut '-d-' -f2`
		_ledger=`echo ${_ImageableArea} | cut '-d-' -f3`
		_A5=`echo ${_ImageableArea} | cut '-d-' -f4`
		_A4=`echo ${_ImageableArea} | cut '-d-' -f5`
		_a3=`echo ${_ImageableArea} | cut '-d-' -f6`
		_a3plus=`echo ${_ImageableArea} | cut '-d-' -f7`
		_B5=`echo ${_ImageableArea} | cut '-d-' -f8`
		_b4=`echo ${_ImageableArea} | cut '-d-' -f9`
		_4X6=`echo ${_ImageableArea} | cut '-d-' -f10`
		_4X8=`echo ${_ImageableArea} | cut '-d-' -f11`
		_5X7=`echo ${_ImageableArea} | cut '-d-' -f12`
		_8X10=`echo ${_ImageableArea} | cut '-d-' -f13`
		_10X12=`echo ${_ImageableArea} | cut '-d-' -f14`
		_l=`echo ${_ImageableArea} | cut '-d-' -f15`
		_2l=`echo ${_ImageableArea} | cut '-d-' -f16`
		_letterfineart35=`echo ${_ImageableArea} | cut '-d-' -f17`
		_a4fineart35=`echo ${_ImageableArea} | cut '-d-' -f18`
		_postcard=`echo ${_ImageableArea} | cut '-d-' -f19`
		_postdbl=`echo ${_ImageableArea} | cut '-d-' -f20`
		_panorama=`echo ${_ImageableArea} | cut '-d-' -f21`
		_creditcard=`echo ${_ImageableArea} | cut '-d-' -f22`
		_businesscard=`echo ${_ImageableArea} | cut '-d-' -f23`
		_wide=`echo ${_ImageableArea} | cut '-d-' -f24`
		_fineartletter=`echo ${_ImageableArea} | cut '-d-' -f25`
		_finearta4=`echo ${_ImageableArea} | cut '-d-' -f26`
		_envelop10p=`echo ${_ImageableArea} | cut '-d-' -f27`
		echo "*DefaultImageableArea: A4" >> ${_dest}

		if [ ${_Letter} = "1" ]; then
			echo "*ImageableArea Letter: \"18.14 14.17 594.14 783.50\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea Letter.bl: \"0 0 612 792\"" >> ${_dest}
			fi
		fi

		if [ ${_Legal} = "1" ]; then
			echo "*ImageableArea Legal: \"18.14 14.17 594.14 999.50\"" >> ${_dest}
		fi

		if [ ${_ledger} = "1" ]; then
			echo "*ImageableArea ledger: \"9.64 14.17 782.36 1215.50\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea ledger.bl: \"0 0 792 1224\"" >> ${_dest}
			fi
		fi

		if [ ${_A5} = "1" ]; then
			echo "*ImageableArea A5: \"9.64 14.17 409.89 586.77\"" >> ${_dest}
		fi

		if [ ${_A4} = "1" ]; then
			echo "*ImageableArea A4: \"9.64 14.17 585.64 833.39\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea A4.bl: \"0 0 595 842\"" >> ${_dest}
			fi
		fi

		if [ ${_a3} = "1" ]; then
			echo "*ImageableArea a3: \"9.64 14.17 832.25 1182.05\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea a3.bl: \"0 0 842 1191\"" >> ${_dest}
			fi
		fi

		if [ ${_a3plus} = "1" ]; then
			echo "*ImageableArea a3plus: \"9.64 14.17 922.96 1360.63\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea a3plus.bl: \"0 0 933 1369\"" >> ${_dest}
			fi
		fi

		if [ ${_B5} = "1" ]; then
			echo "*ImageableArea B5: \"9.64 14.17 506.27 720.00\"" >> ${_dest}
		fi

		if [ ${_b4} = "1" ]; then
			echo "*ImageableArea b4: \"9.64 14.17 718.87 1023.31\"" >> ${_dest}
		fi

		if [ ${_4X6} = "1" ]; then
			echo "*ImageableArea 4X6: \"9.64 14.17 278.36 423.50\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea 4X6.bl: \"0 0 288 432\"" >> ${_dest}
			fi
		fi

		if [ ${_4X8} = "1" ]; then
			echo "*ImageableArea 4X8: \"9.64 14.17 278.36 567.50\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea 4X8.bl: \"0 0 288 576\"" >> ${_dest}
			fi
		fi

		if [ ${_5X7} = "1" ]; then
			echo "*ImageableArea 5X7: \"9.64 14.17 350.36 495.50\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea 5X7.bl: \"0 0 360 504\"" >> ${_dest}
			fi
		fi

		if [ ${_8X10} = "1" ]; then
			echo "*ImageableArea 8X10: \"9.64 14.17 566.36 711.50\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea 8X10.bl: \"0 0 576 720\"" >> ${_dest}
			fi
		fi

		if [ ${_10X12} = "1" ]; then
			echo "*ImageableArea 10X12: \"9.64 14.17 710.36 855.50\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea 10X12.bl: \"0 0 720 864\"" >> ${_dest}
			fi
		fi

		if [ ${_l} = "1" ]; then
			echo "*ImageableArea l: \"9.64 14.17 242.65 351.50\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea l.bl: \"0 0 252 360\"" >> ${_dest}
			fi
		fi

		if [ ${_2l} = "1" ]; then
			echo "*ImageableArea 2l: \"9.64 14.17 350.36 496.06\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea 2l.bl: \"0 0 360 505\"" >> ${_dest}
			fi
		fi

		if [ ${_letterfineart35} = "1" ]; then
			echo "*ImageableArea letterfineart35: \"18.14 99.21 594.14 692.79\"" >> ${_dest}
		fi

		if [ ${_a4fineart35} = "1" ]; then
			echo "*ImageableArea a4fineart35: \"9.64 99.21 585.64 742.68\"" >> ${_dest}
		fi

		if [ ${_postcard} = "1" ]; then
			echo "*ImageableArea postcard: \"9.64 14.17 273.83 411.02\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea postcard.bl: \"0 0 283 420\"" >> ${_dest}
			fi
		fi

		if [ ${_postdbl} = "1" ]; then
			echo "*ImageableArea postdbl: \"9.64 14.17 557.29 411.02\"" >> ${_dest}
		fi

		if [ ${_panorama} = "1" ]; then
			echo "*ImageableArea panorama: \"9.64 14.17 242.65 711.50\"" >> ${_dest}
		fi

		if [ ${_envelop10p} = "1" ]; then
			echo "*ImageableArea envelop10p: \"9.64 75.12 287.35 661.32\"" >> ${_dest}
			echo "*ImageableArea envelopdlp: \"9.64 75.12 302.17 600.94\"" >> ${_dest}
			echo "*ImageableArea envj4p: \"9.64 75.12 288.00 657.64\"" >> ${_dest}
			echo "*ImageableArea envj6p: \"9.64 75.12 268.16 530.08\"" >> ${_dest}
		elif [ ${_envelop10p} = "2" ]; then
			echo "*ImageableArea envelop10p: \"9.64 88.44 287.35 661.32\"" >> ${_dest}
			echo "*ImageableArea envelopdlp: \"9.64 88.44 302.17 600.94\"" >> ${_dest}
			echo "*ImageableArea envj4p: \"9.64 88.44 288.00 643.46\"" >> ${_dest}
			echo "*ImageableArea envj6p: \"9.64 88.44 268.16 515.91\"" >> ${_dest}
		elif [ ${_envelop10p} = "3" ]; then
			echo "*ImageableArea envelop10p: \"9.64 89.29 287.35 661.32\"" >> ${_dest}
			echo "*ImageableArea envelopdlp: \"9.64 89.29 302.17 600.94\"" >> ${_dest}
			echo "*ImageableArea envj4p: \"9.64 89.29 288.00 643.46\"" >> ${_dest}
			echo "*ImageableArea envj6p: \"9.64 89.29 268.16 515.91\"" >> ${_dest}
		elif [ ${_envelop10p} = "4" ]; then
			echo "*ImageableArea envelop10p: \"9.64 92.13 287.35 661.32\"" >> ${_dest}
			echo "*ImageableArea envelopdlp: \"9.64 92.13 302.17 600.94\"" >> ${_dest}
			echo "*ImageableArea envj4p: \"9.64 92.13 288.00 643.46\"" >> ${_dest}
			echo "*ImageableArea envj6p: \"9.64 92.13 268.16 515.91\"" >> ${_dest}
		elif [ ${_envelop10p} = "5" ]; then
			echo "*ImageableArea envelop10p: \"9.64 106.02 287.35 675.50\"" >> ${_dest}
			echo "*ImageableArea envelopdlp: \"9.64 106.02 302.17 615.12\"" >> ${_dest}
			echo "*ImageableArea envj4p: \"9.64 106.02 288.00 657.64\"" >> ${_dest}
			echo "*ImageableArea envj6p: \"9.64 106.02 268.16 530.08\"" >> ${_dest}
		elif [ ${_envelop10p} = "6" ]; then
			echo "*ImageableArea envelop10p: \"15.87 106.02 281.11 675.50\"" >> ${_dest}
			echo "*ImageableArea envelopdlp: \"15.87 106.02 295.94 615.12\"" >> ${_dest}
			echo "*ImageableArea envj4p: \"15.87 106.02 281.76 657.64\"" >> ${_dest}
			echo "*ImageableArea envj6p: \"15.87 106.02 261.92 530.08\"" >> ${_dest}
		elif [ ${_envelop10p} = "7" ]; then
			echo "*ImageableArea envelop10p: \"15.87 92.13 281.11 661.32\"" >> ${_dest}
			echo "*ImageableArea envelopdlp: \"15.87 92.13 295.94 600.94\"" >> ${_dest}
			echo "*ImageableArea envj4p: \"15.87 92.13 281.76 643.46\"" >> ${_dest}
			echo "*ImageableArea envj6p: \"15.87 92.13 261.92 515.91\"" >> ${_dest}
		fi

		if [ ${_creditcard} = "1" ]; then
			echo "*ImageableArea creditcard: \"9.64 14.17 143.43 235.28\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea creditcard.bl: \"0 0 153 244\"" >> ${_dest}
			fi
		fi

		if [ ${_businesscard} = "1" ]; then
			echo "*ImageableArea businesscard: \"9.64 14.17 146.27 249.45\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea businesscard.bl: \"0 0 156 258\"" >> ${_dest}
			fi
		fi

		if [ ${_wide} = "1" ]; then
			echo "*ImageableArea wide: \"9.64 14.17 278.36 503.49\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*ImageableArea wide.bl: \"0 0 288 512\"" >> ${_dest}
			fi
		fi

		if [ ${_fineartletter} = "1" ]; then
			echo "*ImageableArea fineartletter: \"18.14 99.21 594.14 692.79\"" >> ${_dest}
		fi

		if [ ${_finearta4} = "1" ]; then
			echo "*ImageableArea finearta4: \"9.64 99.21 585.64 742.68\"" >> ${_dest}
		fi

	fi
	echo "" >> ${_dest}
}

PaperDimension(){
	_PaperDimension=`cat include/canon_pagesize.txt | grep "${model_master,,}"`
	if [ ! "${_PaperDimension}" = "" ]; then
		_Letter=`echo ${_PaperDimension} | cut '-d-' -f1`
		_Legal=`echo ${_PaperDimension} | cut '-d-' -f2`
		_ledger=`echo ${_PaperDimension} | cut '-d-' -f3`
		_A5=`echo ${_PaperDimension} | cut '-d-' -f4`
		_A4=`echo ${_PaperDimension} | cut '-d-' -f5`
		_a3=`echo ${_PaperDimension} | cut '-d-' -f6`
		_a3plus=`echo ${_PaperDimension} | cut '-d-' -f7`
		_B5=`echo ${_PaperDimension} | cut '-d-' -f8`
		_b4=`echo ${_PaperDimension} | cut '-d-' -f9`
		_4X6=`echo ${_PaperDimension} | cut '-d-' -f10`
		_4X8=`echo ${_PaperDimension} | cut '-d-' -f11`
		_5X7=`echo ${_PaperDimension} | cut '-d-' -f12`
		_8X10=`echo ${_PaperDimension} | cut '-d-' -f13`
		_10X12=`echo ${_PaperDimension} | cut '-d-' -f14`
		_l=`echo ${_PaperDimension} | cut '-d-' -f15`
		_2l=`echo ${_PaperDimension} | cut '-d-' -f16`
		_letterfineart35=`echo ${_PaperDimension} | cut '-d-' -f17`
		_a4fineart35=`echo ${_PaperDimension} | cut '-d-' -f18`
		_postcard=`echo ${_PaperDimension} | cut '-d-' -f19`
		_postdbl=`echo ${_PaperDimension} | cut '-d-' -f20`
		_panorama=`echo ${_PaperDimension} | cut '-d-' -f21`
		_creditcard=`echo ${_PaperDimension} | cut '-d-' -f22`
		_businesscard=`echo ${_PaperDimension} | cut '-d-' -f23`
		_wide=`echo ${_PaperDimension} | cut '-d-' -f24`
		_fineartletter=`echo ${_PaperDimension} | cut '-d-' -f25`
		_finearta4=`echo ${_PaperDimension} | cut '-d-' -f26`
		_envelop10p=`echo ${_PaperDimension} | cut '-d-' -f27`
		echo "*DefaultPaperDimension: A4" >> ${_dest}

		if [ ${_Letter} = "1" ]; then
			echo "*PaperDimension Letter: \"612 792\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension Letter.bl: \"613 793\"" >> ${_dest}
			fi
		fi

		if [ ${_Legal} = "1" ]; then
			echo "*PaperDimension Legal: \"612 1008\"" >> ${_dest}
		fi

		if [ ${_ledger} = "1" ]; then
			echo "*PaperDimension ledger: \"792 1224\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension ledger.bl: \"793 1225\"" >> ${_dest}
			fi
		fi

		if [ ${_A5} = "1" ]; then
			echo "*PaperDimension A5: \"420 595\"" >> ${_dest}
		fi

		if [ ${_A4} = "1" ]; then
			echo "*PaperDimension A4: \"595 842\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension A4.bl: \"596 843\"" >> ${_dest}
			fi
		fi

		if [ ${_a3} = "1" ]; then
			echo "*PaperDimension a3: \"842 1191\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension a3.bl: \"843 1192\"" >> ${_dest}
			fi
		fi

		if [ ${_a3plus} = "1" ]; then
			echo "*PaperDimension a3plus: \"933 1369\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension a3plus.bl: \"934 1370\"" >> ${_dest}
			fi
		fi

		if [ ${_B5} = "1" ]; then
			echo "*PaperDimension B5: \"516 729\"" >> ${_dest}
		fi

		if [ ${_b4} = "1" ]; then
			echo "*PaperDimension b4: \"729 1032\"" >> ${_dest}
		fi

		if [ ${_4X6} = "1" ]; then
			echo "*PaperDimension 4X6: \"288 432\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension 4X6.bl: \"289 433\"" >> ${_dest}
			fi
		fi

		if [ ${_4X8} = "1" ]; then
			echo "*PaperDimension 4X8: \"288 576\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension 4X8.bl: \"289 577\"" >> ${_dest}
			fi
		fi

		if [ ${_5X7} = "1" ]; then
			echo "*PaperDimension 5X7: \"360 504\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension 5X7.bl: \"361 505\"" >> ${_dest}
			fi
		fi

		if [ ${_8X10} = "1" ]; then
			echo "*PaperDimension 8X10: \"576 720\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension 8X10.bl: \"577 721\"" >> ${_dest}
			fi
		fi

		if [ ${_10X12} = "1" ]; then
			echo "*PaperDimension 10X12: \"720 864\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension 10X12.bl: \"721 865\"" >> ${_dest}
			fi
		fi

		if [ ${_l} = "1" ]; then
			echo "*PaperDimension l: \"252 360\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension l.bl: \"253 361\"" >> ${_dest}
			fi
		fi

		if [ ${_2l} = "1" ]; then
			echo "*PaperDimension 2l: \"360 505\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension 2l.bl: \"361 506\"" >> ${_dest}
			fi
		fi

		if [ ${_letterfineart35} = "1" ]; then
			echo "*PaperDimension letterfineart35: \"612 792\"" >> ${_dest}
		fi

		if [ ${_a4fineart35} = "1" ]; then
			echo "*PaperDimension a4fineart35: \"595 842\"" >> ${_dest}
		fi

		if [ ${_postcard} = "1" ]; then
			echo "*PaperDimension postcard: \"283 420\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension postcard.bl: \"284 421\"" >> ${_dest}
			fi
		fi

		if [ ${_postdbl} = "1" ]; then
			echo "*PaperDimension postdbl: \"567 420\"" >> ${_dest}
		fi

		if [ ${_panorama} = "1" ]; then
			echo "*PaperDimension panorama: \"252 720\"" >> ${_dest}
		fi

		if [ ! ${_envelop10p} = "0" ]; then
			echo "*PaperDimension envelop10p: \"297 684\"" >> ${_dest}
			echo "*PaperDimension envelopdlp: \"312 624\"" >> ${_dest}
			echo "*PaperDimension envj4p: \"298 666\"" >> ${_dest}
			echo "*PaperDimension envj6p: \"278 539\"" >> ${_dest}
		fi

		if [ ${_creditcard} = "1" ]; then
			echo "*PaperDimension creditcard: \"153 244\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension creditcard.bl: \"154 245\"" >> ${_dest}
			fi
		fi

		if [ ${_businesscard} = "1" ]; then
			echo "*PaperDimension businesscard: \"156 258\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension businesscard.bl: \"157 259\"" >> ${_dest}
			fi
		fi

		if [ ${_wide} = "1" ]; then
			echo "*PaperDimension wide: \"288 512\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PaperDimension wide.bl: \"289 513\"" >> ${_dest}
			fi
		fi

		if [ ${_fineartletter} = "1" ]; then
			echo "*PaperDimension fineartletter: \"612 792\"" >> ${_dest}
		fi

		if [ ${_finearta4} = "1" ]; then
			echo "*PaperDimension finearta4: \"595 842\"" >> ${_dest}
		fi

	fi
	echo "" >> ${_dest}
}


PageSize(){
	_PageSize=`cat include/canon_pagesize.txt | grep "${model_master,,}"`
	if [ ! "${_PageSize}" = "" ]; then
		_Letter=`echo ${_PageSize} | cut '-d-' -f1`
		_Legal=`echo ${_PageSize} | cut '-d-' -f2`
		_ledger=`echo ${_PageSize} | cut '-d-' -f3`
		_A5=`echo ${_PageSize} | cut '-d-' -f4`
		_A4=`echo ${_PageSize} | cut '-d-' -f5`
		_a3=`echo ${_PageSize} | cut '-d-' -f6`
		_a3plus=`echo ${_PageSize} | cut '-d-' -f7`
		_B5=`echo ${_PageSize} | cut '-d-' -f8`
		_b4=`echo ${_PageSize} | cut '-d-' -f9`
		_4X6=`echo ${_PageSize} | cut '-d-' -f10`
		_4X8=`echo ${_PageSize} | cut '-d-' -f11`
		_5X7=`echo ${_PageSize} | cut '-d-' -f12`
		_8X10=`echo ${_PageSize} | cut '-d-' -f13`
		_10X12=`echo ${_PageSize} | cut '-d-' -f14`
		_l=`echo ${_PageSize} | cut '-d-' -f15`
		_2l=`echo ${_PageSize} | cut '-d-' -f16`
		_letterfineart35=`echo ${_PageSize} | cut '-d-' -f17`
		_a4fineart35=`echo ${_PageSize} | cut '-d-' -f18`
		_postcard=`echo ${_PageSize} | cut '-d-' -f19`
		_postdbl=`echo ${_PageSize} | cut '-d-' -f20`
		_panorama=`echo ${_PageSize} | cut '-d-' -f21`
		_creditcard=`echo ${_PageSize} | cut '-d-' -f22`
		_businesscard=`echo ${_PageSize} | cut '-d-' -f23`
		_wide=`echo ${_PageSize} | cut '-d-' -f24`
		_fineartletter=`echo ${_PageSize} | cut '-d-' -f25`
		_finearta4=`echo ${_PageSize} | cut '-d-' -f26`
		_envelop10p=`echo ${_PageSize} | cut '-d-' -f27`
		echo "*OpenUI *PageSize/Page Size: PickOne" >> ${_dest}
		echo "*DefaultPageSize: A4" >> ${_dest}


		if [ ${_Letter} = "1" ]; then
			echo "*PageSize Letter/Letter [8.50\"x11.00\" 215.9x279.4mm]: \"<</CNPageSizeName(Letter)/PageSize[612 792]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize Letter.bl/Letter(borderless) [8.50\"x11.00\" 215.9x279.4mm]: \"<</CNPageSizeName(Letter.bl)/PageSize[612 792]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_Legal} = "1" ]; then
			echo "*PageSize Legal/Legal [8.50\"x14.00\" 215.9x355.6mm]: \"<</CNPageSizeName(Legal)/PageSize[612 1008]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_ledger} = "1" ]; then
			echo "*PageSize ledger/11\"x17\" [11.00\"x17.00\" 279.4x431.8mm]: \"<</CNPageSizeName(ledger)/PageSize[792 1224]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize ledger.bl/11\"x17\"(borderless) [11.00\"x17.00\" 279.4x431.8mm]: \"<</CNPageSizeName(ledger.bl)/PageSize[792 1224]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_A5} = "1" ]; then
			echo "*PageSize A5/A5 [5.83\"x8.27\" 148.0x210.0mm]: \"<</CNPageSizeName(A5)/PageSize[420 595]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_A4} = "1" ]; then
			echo "*PageSize A4/A4 [8.27\"x11.69\" 210.0x297.0mm]: \"<</CNPageSizeName(A4)/PageSize[595 842]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize A4.bl/A4(borderless) [8.27\"x11.69\" 210.0x297.0mm]: \"<</CNPageSizeName(A4.bl)/PageSize[595 842]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_a3} = "1" ]; then
			echo "*PageSize a3/A3 [11.69\"x16.54\" 297.0x420.0mm]: \"<</CNPageSizeName(a3)/PageSize[842 1191]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize a3.bl/A3(borderless) [11.69\"x16.54\" 297.0x420.0mm]: \"<</CNPageSizeName(a3.bl)/PageSize[842 1191]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_a3plus} = "1" ]; then
			echo "*PageSize a3plus/A3+ [12.95\"x19.02\" 329.0x483.0mm]: \"<</CNPageSizeName(a3plus)/PageSize[933 1369]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize a3plus.bl/A3+(borderless) [12.95\"x19.02\" 329.0x483.0mm]: \"<</CNPageSizeName(a3plus.bl)/PageSize[933 1369]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_B5} = "1" ]; then
			echo "*PageSize B5/B5 [7.17\"x10.12\" 182.0x257.0mm]: \"<</CNPageSizeName(B5)/PageSize[516 729]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_b4} = "1" ]; then
			echo "*PageSize b4/B4 [10.12\"x14.33\" 257.0x364.0mm]: \"<</CNPageSizeName(b4)/PageSize[729 1032]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_4X6} = "1" ]; then
			echo "*PageSize 4X6/4\"x6\" [4.00\"x6.00\" 101.6x152.4mm]: \"<</CNPageSizeName(4X6)/PageSize[288 432]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize 4X6.bl/4\"x6\"(borderless) [4.00\"x6.00\" 101.6x152.4mm]: \"<</CNPageSizeName(4X6.bl)/PageSize[288 432]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_4X8} = "1" ]; then
			echo "*PageSize 4X8/4\"x8\" [4.00\"x8.00\" 101.6x203.2mm]: \"<</CNPageSizeName(4X8)/PageSize[288 576]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize 4X8.bl/4\"x8\"(borderless) [4.00\"x8.00\" 101.6x203.2mm]: \"<</CNPageSizeName(4X8.bl)/PageSize[288 576]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_5X7} = "1" ]; then
			echo "*PageSize 5X7/5\"x7\" [5.00\"x7.00\" 127.0x177.8mm]: \"<</CNPageSizeName(5X7)/PageSize[360 504]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize 5X7.bl/5\"x7\"(borderless) [5.00\"x7.00\" 127.0x177.8mm]: \"<</CNPageSizeName(5X7.bl)/PageSize[360 504]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_8X10} = "1" ]; then
			echo "*PageSize 8X10/8\"x10\" [8.00\"x10.00\" 203.2x254.0mm]: \"<</CNPageSizeName(8X10)/PageSize[576 720]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize 8X10.bl/8\"x10\"(borderless) [8.00\"x10.00\" 203.2x254.0mm]: \"<</CNPageSizeName(8X10.bl)/PageSize[576 720]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_10X12} = "1" ]; then
			echo "*PageSize 10X12/10\"x12\" [10.00\"x12.00\" 254.0x304.8mm]: \"<</CNPageSizeName(10X12)/PageSize[720 864]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize 10X12.bl/10\"x12\"(borderless) [10.00\"x12.00\" 254.0x304.8mm]: \"<</CNPageSizeName(10X12.bl)/PageSize[720 864]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_l} = "1" ]; then
			echo "*PageSize l/L [3.50\"x5.00\" 89.0x127.0mm]: \"<</CNPageSizeName(l)/PageSize[252 360]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize l.bl/L(borderless) [3.50\"x5.00\" 89.0x127.0mm]: \"<</CNPageSizeName(l.bl)/PageSize[252 360]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_2l} = "1" ]; then
			echo "*PageSize 2l/2L [5.00\"x7.01\" 127.0x178.0mm]: \"<</CNPageSizeName(2l)/PageSize[360 505]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize 2l.bl/2L(borderless) [5.00\"x7.01\" 127.0x178.0mm]: \"<</CNPageSizeName(2l.bl)/PageSize[360 505]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_letterfineart35} = "1" ]; then
			echo "*PageSize letterfineart35/Letter (Art Paper Margin 35) [8.50\"x11.00\" 215.9x279.4mm]: \"<</CNPageSizeName(letterfineart35)/PageSize[612 792]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_a4fineart35} = "1" ]; then
			echo "*PageSize a4fineart35/A4 (Art Paper Margin 35) [8.27\"x11.69\" 210.0x297.0mm]: \"<</CNPageSizeName(a4fineart35)/PageSize[595 842]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_postcard} = "1" ]; then
			echo "*PageSize postcard/Hagaki [3.94\"x5.83\" 100.0x148.0mm]: \"<</CNPageSizeName(postcard)/PageSize[283 420]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize postcard.bl/Hagaki(borderless) [3.94\"x5.83\" 100.0x148.0mm]: \"<</CNPageSizeName(postcard.bl)/PageSize[283 420]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_postdbl} = "1" ]; then
			echo "*PageSize postdbl/Hagaki 2 [7.87\"x5.83\" 200.0x148.0mm]: \"<</CNPageSizeName(postdbl)/PageSize[567 420]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_panorama} = "1" ]; then
			echo "*PageSize panorama/Panorama [3.50\"x10.00\" 89.0x254.0mm]: \"<</CNPageSizeName(panorama)/PageSize[252 720]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ! ${_envelop10p} = "0" ]; then
			echo "*PageSize envelop10p/Comm. Env. #10 [4.12\"x9.50\" 104.8x241.3mm]: \"<</CNPageSizeName(envelop10p)/PageSize[297 684]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			echo "*PageSize envelopdlp/DL Env. [4.33\"x8.66\" 110.0x220.0mm]: \"<</CNPageSizeName(envelopdlp)/PageSize[312 624]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			echo "*PageSize envj4p/Youkei 4 [4.13\"x9.25\" 105.0x235.0mm]: \"<</CNPageSizeName(envj4p)/PageSize[298 666]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			echo "*PageSize envj6p/Youkei 6 [3.86\"x7.48\" 98.0x190.0mm]: \"<</CNPageSizeName(envj6p)/PageSize[278 539]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_businesscard} = "1" ]; then
			echo "*PageSize creditcard/Credit Card [2.13\"x3.39\" 54.0x86.0mm]: \"<</CNPageSizeName(creditcard)/PageSize[153 244]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize creditcard.bl/Credit Card(borderless) [2.13\"x3.39\" 54.0x86.0mm]: \"<</CNPageSizeName(creditcard.bl)/PageSize[153 244]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_businesscard} = "1" ]; then
			echo "*PageSize businesscard/Card [2.16\"x3.58\" 55.0x91.0mm]: \"<</CNPageSizeName(businesscard)/PageSize[156 258]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize businesscard.bl/Card(borderless) [2.16\"x3.58\" 55.0x91.0mm]: \"<</CNPageSizeName(businesscard.bl)/PageSize[156 258]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_wide} = "1" ]; then
			echo "*PageSize wide/Wide [4.00\"x7.11\" 101.6x180.6mm]: \"<</CNPageSizeName(wide)/PageSize[288 512]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize wide.bl/Wide(borderless) [4.00\"x7.11\" 101.6x180.6mm]: \"<</CNPageSizeName(wide.bl)/PageSize[288 512]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_fineartletter} = "1" ]; then
			echo "*PageSize fineartletter/Fine Art Letter [8.50\"x11.00\" 215.9x279.4mm]: \"<</CNPageSizeName(fineartletter)/PageSize[612 792]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_finearta4} = "1" ]; then
			echo "*PageSize finearta4/Fine Art A4 [8.27\"x11.69\" 210.0x297.0mm]: \"<</CNPageSizeName(finearta4)/PageSize[595 842]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi


	fi
	echo "*CloseUI: *PageSize" >> ${_dest}
	echo "" >> ${_dest}
}

PageRegion(){
	_PageRegion=`cat include/canon_pagesize.txt | grep "${model_master,,}"`
	if [ ! "${_PageRegion}" = "" ]; then
		_Letter=`echo ${_PageRegion} | cut '-d-' -f1`
		_Legal=`echo ${_PageRegion} | cut '-d-' -f2`
		_ledger=`echo ${_PageRegion} | cut '-d-' -f3`
		_A5=`echo ${_PageRegion} | cut '-d-' -f4`
		_A4=`echo ${_PageRegion} | cut '-d-' -f5`
		_a3=`echo ${_PageRegion} | cut '-d-' -f6`
		_a3plus=`echo ${_PageRegion} | cut '-d-' -f7`
		_B5=`echo ${_PageRegion} | cut '-d-' -f8`
		_b4=`echo ${_PageRegion} | cut '-d-' -f9`
		_4X6=`echo ${_PageRegion} | cut '-d-' -f10`
		_4X8=`echo ${_PageRegion} | cut '-d-' -f11`
		_5X7=`echo ${_PageRegion} | cut '-d-' -f12`
		_8X10=`echo ${_PageRegion} | cut '-d-' -f13`
		_10X12=`echo ${_PageRegion} | cut '-d-' -f14`
		_l=`echo ${_PageRegion} | cut '-d-' -f15`
		_2l=`echo ${_PageRegion} | cut '-d-' -f16`
		_letterfineart35=`echo ${_PageRegion} | cut '-d-' -f17`
		_a4fineart35=`echo ${_PageRegion} | cut '-d-' -f18`
		_postcard=`echo ${_PageRegion} | cut '-d-' -f19`
		_postdbl=`echo ${_PageRegion} | cut '-d-' -f20`
		_panorama=`echo ${_PageRegion} | cut '-d-' -f21`
		_creditcard=`echo ${_PageRegion} | cut '-d-' -f22`
		_businesscard=`echo ${_PageRegion} | cut '-d-' -f23`
		_wide=`echo ${_PageRegion} | cut '-d-' -f24`
		_fineartletter=`echo ${_PageRegion} | cut '-d-' -f25`
		_finearta4=`echo ${_PageRegion} | cut '-d-' -f26`
		_envelop10p=`echo ${_PageRegion} | cut '-d-' -f27`
		echo "*OpenUI *PageRegion: PickOne" >> ${_dest}
		echo "*DefaultPageRegion: A4" >> ${_dest}


		if [ ${_Letter} = "1" ]; then
			echo "*PageRegion Letter/Letter [8.50\"x11.00\" 215.9x279.4mm]: \"<</CNPageSizeName(Letter)/PageSize[612 792]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion Letter.bl/Letter(borderless) [8.50\"x11.00\" 215.9x279.4mm]: \"<</CNPageSizeName(Letter.bl)/PageSize[612 792]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_Legal} = "1" ]; then
			echo "*PageRegion Legal/Legal [8.50\"x14.00\" 215.9x355.6mm]: \"<</CNPageSizeName(Legal)/PageSize[612 1008]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_ledger} = "1" ]; then
			echo "*PageRegion ledger/11\"x17\" [11.00\"x17.00\" 279.4x431.8mm]: \"<</CNPageSizeName(ledger)/PageSize[792 1224]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion ledger.bl/11\"x17\"(borderless) [11.00\"x17.00\" 279.4x431.8mm]: \"<</CNPageSizeName(ledger.bl)/PageSize[792 1224]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_A5} = "1" ]; then
			echo "*PageRegion A5/A5 [5.83\"x8.27\" 148.0x210.0mm]: \"<</CNPageSizeName(A5)/PageSize[420 595]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_A4} = "1" ]; then
			echo "*PageRegion A4/A4 [8.27\"x11.69\" 210.0x297.0mm]: \"<</CNPageSizeName(A4)/PageSize[595 842]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion A4.bl/A4(borderless) [8.27\"x11.69\" 210.0x297.0mm]: \"<</CNPageSizeName(A4.bl)/PageSize[595 842]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_a3} = "1" ]; then
			echo "*PageRegion a3/A3 [11.69\"x16.54\" 297.0x420.0mm]: \"<</CNPageSizeName(a3)/PageSize[842 1191]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion a3.bl/A3(borderless) [11.69\"x16.54\" 297.0x420.0mm]: \"<</CNPageSizeName(a3.bl)/PageSize[842 1191]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_a3plus} = "1" ]; then
			echo "*PageRegion a3plus/A3+ [12.95\"x19.02\" 329.0x483.0mm]: \"<</CNPageSizeName(a3plus)/PageSize[933 1369]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion a3plus.bl/A3+(borderless) [12.95\"x19.02\" 329.0x483.0mm]: \"<</CNPageSizeName(a3plus.bl)/PageSize[933 1369]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_B5} = "1" ]; then
			echo "*PageRegion B5/B5 [7.17\"x10.12\" 182.0x257.0mm]: \"<</CNPageSizeName(B5)/PageSize[516 729]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_b4} = "1" ]; then
			echo "*PageRegion b4/B4 [10.12\"x14.33\" 257.0x364.0mm]: \"<</CNPageSizeName(b4)/PageSize[729 1032]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_4X6} = "1" ]; then
			echo "*PageRegion 4X6/4\"x6\" [4.00\"x6.00\" 101.6x152.4mm]: \"<</CNPageSizeName(4X6)/PageSize[288 432]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion 4X6.bl/4\"x6\"(borderless) [4.00\"x6.00\" 101.6x152.4mm]: \"<</CNPageSizeName(4X6.bl)/PageSize[288 432]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_4X8} = "1" ]; then
			echo "*PageRegion 4X8/4\"x8\" [4.00\"x8.00\" 101.6x203.2mm]: \"<</CNPageSizeName(4X8)/PageSize[288 576]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion 4X8.bl/4\"x8\"(borderless) [4.00\"x8.00\" 101.6x203.2mm]: \"<</CNPageSizeName(4X8.bl)/PageSize[288 576]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_5X7} = "1" ]; then
			echo "*PageRegion 5X7/5\"x7\" [5.00\"x7.00\" 127.0x177.8mm]: \"<</CNPageSizeName(5X7)/PageSize[360 504]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion 5X7.bl/5\"x7\"(borderless) [5.00\"x7.00\" 127.0x177.8mm]: \"<</CNPageSizeName(5X7.bl)/PageSize[360 504]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_8X10} = "1" ]; then
			echo "*PageRegion 8X10/8\"x10\" [8.00\"x10.00\" 203.2x254.0mm]: \"<</CNPageSizeName(8X10)/PageSize[576 720]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion 8X10.bl/8\"x10\"(borderless) [8.00\"x10.00\" 203.2x254.0mm]: \"<</CNPageSizeName(8X10.bl)/PageSize[576 720]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_10X12} = "1" ]; then
			echo "*PageRegion 10X12/10\"x12\" [10.00\"x12.00\" 254.0x304.8mm]: \"<</CNPageSizeName(10X12)/PageSize[720 864]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion 10X12.bl/10\"x12\"(borderless) [10.00\"x12.00\" 254.0x304.8mm]: \"<</CNPageSizeName(10X12.bl)/PageSize[720 864]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_l} = "1" ]; then
			echo "*PageRegion l/L [3.50\"x5.00\" 89.0x127.0mm]: \"<</CNPageSizeName(l)/PageSize[252 360]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion l.bl/L(borderless) [3.50\"x5.00\" 89.0x127.0mm]: \"<</CNPageSizeName(l.bl)/PageSize[252 360]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_2l} = "1" ]; then
			echo "*PageRegion 2l/2L [5.00\"x7.01\" 127.0x178.0mm]: \"<</CNPageSizeName(2l)/PageSize[360 505]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion 2l.bl/2L(borderless) [5.00\"x7.01\" 127.0x178.0mm]: \"<</CNPageSizeName(2l.bl)/PageSize[360 505]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_letterfineart35} = "1" ]; then
			echo "*PageRegion letterfineart35/Letter (Art Paper Margin 35) [8.50\"x11.00\" 215.9x279.4mm]: \"<</CNPageSizeName(letterfineart35)/PageSize[612 792]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_a4fineart35} = "1" ]; then
			echo "*PageRegion a4fineart35/A4 (Art Paper Margin 35) [8.27\"x11.69\" 210.0x297.0mm]: \"<</CNPageSizeName(a4fineart35)/PageSize[595 842]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_postcard} = "1" ]; then
			echo "*PageRegion postcard/Hagaki [3.94\"x5.83\" 100.0x148.0mm]: \"<</CNPageSizeName(postcard)/PageSize[283 420]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion postcard.bl/Hagaki(borderless) [3.94\"x5.83\" 100.0x148.0mm]: \"<</CNPageSizeName(postcard.bl)/PageSize[283 420]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_postdbl} = "1" ]; then
			echo "*PageRegion postdbl/Hagaki 2 [7.87\"x5.83\" 200.0x148.0mm]: \"<</CNPageSizeName(postdbl)/PageSize[567 420]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_panorama} = "1" ]; then
			echo "*PageRegion panorama/Panorama [3.50\"x10.00\" 89.0x254.0mm]: \"<</CNPageSizeName(panorama)/PageSize[252 720]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ! ${_envelop10p} = "0" ]; then
			echo "*PageRegion envelop10p/Comm. Env. #10 [4.12\"x9.50\" 104.8x241.3mm]: \"<</CNPageSizeName(envelop10p)/PageSize[297 684]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			echo "*PageRegion envelopdlp/DL Env. [4.33\"x8.66\" 110.0x220.0mm]: \"<</CNPageSizeName(envelopdlp)/PageSize[312 624]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			echo "*PageRegion envj4p/Youkei 4 [4.13\"x9.25\" 105.0x235.0mm]: \"<</CNPageSizeName(envj4p)/PageSize[298 666]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			echo "*PageRegion envj6p/Youkei 6 [3.86\"x7.48\" 98.0x190.0mm]: \"<</CNPageSizeName(envj6p)/PageSize[278 539]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_businesscard} = "1" ]; then
			echo "*PageRegion creditcard/Credit Card [2.13\"x3.39\" 54.0x86.0mm]: \"<</CNPageSizeName(creditcard)/PageSize[153 244]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageSize creditcard.bl/Credit Card(borderless) [2.13\"x3.39\" 54.0x86.0mm]: \"<</CNPageSizeName(creditcard.bl)/PageSize[153 244]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_businesscard} = "1" ]; then
			echo "*PageRegion businesscard/Card [2.16\"x3.58\" 55.0x91.0mm]: \"<</CNPageSizeName(businesscard)/PageSize[156 258]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion businesscard.bl/Card(borderless) [2.16\"x3.58\" 55.0x91.0mm]: \"<</CNPageSizeName(businesscard.bl)/PageSize[156 258]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_wide} = "1" ]; then
			echo "*PageRegion wide/Wide [4.00\"x7.11\" 101.6x180.6mm]: \"<</CNPageSizeName(wide)/PageSize[288 512]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			if [ ${_extension} = "1" ]; then
				echo "*PageRegion wide.bl/Wide(borderless) [4.00\"x7.11\" 101.6x180.6mm]: \"<</CNPageSizeName(wide.bl)/PageSize[288 512]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
			fi
		fi

		if [ ${_fineartletter} = "1" ]; then
			echo "*PageRegion fineartletter/Fine Art Letter [8.50\"x11.00\" 215.9x279.4mm]: \"<</CNPageSizeName(fineartletter)/PageSize[612 792]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

		if [ ${_finearta4} = "1" ]; then
			echo "*PageRegion finearta4/Fine Art A4 [8.27\"x11.69\" 210.0x297.0mm]: \"<</CNPageSizeName(finearta4)/PageSize[595 842]/ImagingBBox null>>setpagedevice\"" >> ${_dest}
		fi

	fi
	echo "*CloseUI: *PageRegion" >> ${_dest}
	echo "" >> ${_dest}
}


