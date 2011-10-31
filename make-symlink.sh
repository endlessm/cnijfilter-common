#/bin/sh

find . -name lib*.so.* -print > file_lists2

val0=$(pwd)
for fn in `cat file_lists2`; do
	val1=`echo ${fn} | cut -d/ -f2`
	if [ ! ${val1} = "debian" ]; then
		val2=`echo ${fn} | cut -d/ -f3`
		val3=`echo ${fn} | cut -d/ -f4`
		val4=`echo ${val3} | cut -d. -f1`
		val5=`echo ${val3} | cut -d. -f2`
		val6=${val4}.${val5}
		val7=${val0}/${val1}/${val2}
		echo "Create symlink from " ${val3} " to " ${val6}
		cd ${val7}
		rm -f ${val6}
		ln -s ${val3} ${val6}
	fi
done

cd ${val0}
rm -f file_lists2
