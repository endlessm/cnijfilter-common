#/bin/bash



InputSlot(){
	slot=`cat include/canon_slot.txt | grep "${model_master,,}"`
	if [ ! "${slot}" = "" ]; then
		_manual=`echo ${slot} | cut '-d-' -f1`
		_asf=`echo ${slot} | cut '-d-' -f2`
		_asf2bin=`echo ${slot} | cut '-d-' -f3`
		_auto=`echo ${slot} | cut '-d-' -f4`
		_cassette=`echo ${slot} | cut '-d-' -f5`
		_cassette1=`echo ${slot} | cut '-d-' -f6`
		_cassette2=`echo ${slot} | cut '-d-' -f7`
		_cassetteauto=`echo ${slot} | cut '-d-' -f8`
		_continuous=`echo ${slot} | cut '-d-' -f9`
		_front=`echo ${slot} | cut '-d-' -f10`
		_front2=`echo ${slot} | cut '-d-' -f11`
		_frontplain=`echo ${slot} | cut '-d-' -f12`
		_switch=`echo ${slot} | cut '-d-' -f13`
		_consecutive1=`echo ${slot} | cut '-d-' -f14`
		_consecutive2=`echo ${slot} | cut '-d-' -f15`
		_tractor=`echo ${slot} | cut '-d-' -f16`
		_default=`echo ${slot} | cut '-d-' -f17`
		let i=0
		echo "*OpenUI *InputSlot/Paper Source: PickOne" >> ${_dest}
		echo "*DefaultInputSlot: ${_default}" >> ${_dest}

		if [ ${_manual} = "1" ]; then
			echo "*InputSlot manual/Manual: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_asf} = "1" ]; then
			echo "*InputSlot asf/Auto Sheet Feeder: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_asf2bin} = "1" ]; then
			echo "*InputSlot asf2bin/Auto Sheet Feeder 2bin: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_auto} = "1" ]; then
			echo "*InputSlot auto/Automatically Select: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_cassette} = "1" ]; then
			echo "*InputSlot cassette/Cassette: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_cassette1} = "1" ]; then
			echo "*InputSlot cassette1/Cassette1: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_cassette2} = "1" ]; then
			echo "*InputSlot cassette2/Cassette2: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_cassetteauto} = "1" ]; then
			echo "*InputSlot cassetteauto/Cassette: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_continuous} = "1" ]; then
			echo "*InputSlot continuous/Continuous Autofeed: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_front} = "1" ]; then
			echo "*InputSlot front/Front Tray: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_front2} = "1" ]; then
			echo "*InputSlot front2/Front Tray: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_frontplain} = "1" ]; then
			echo "*InputSlot frontplain/Front for Plain Paper: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_switch} = "1" ]; then
			echo "*InputSlot switch/Paper Feed Switch: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_consecutive1} = "1" ]; then
			echo "*InputSlot consecutive1/Consecutive 1: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_consecutive2} = "1" ]; then
			echo "*InputSlot consecutive2/Consecutive 2: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		if [ ${_tractor} = "1" ]; then
			echo "*InputSlot tractor/Tractor: \"<</MediaPosition ${i}>>setpagedevice\"" >> ${_dest}
			let i=i+1
		fi

		echo "*CloseUI: *InputSlot" >> ${_dest}
		echo "" >> ${_dest}
	fi
}
