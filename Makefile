#dirs = libs cngpij cngpijmon ppd pstocanonij 
dirs = libs cngpij pstocanonij backend backendnet cngpijmon-3.60/cnijnpr \
	cngpijmon-2.70 cnijfilter-2.70 lgmon-2.70 ppd-2.70 printui-2.70 \
	cngpijmon-2.80 cnijfilter-2.80 lgmon-2.80 ppd-2.80 printui-2.80 \
	cngpijmon-2.90 cnijfilter-2.90 lgmon-2.90 ppd-2.90 printui-2.90 \
	cngpijmon-3.00 cnijfilter-3.00 lgmon-3.00 ppd-3.00 printui-3.00 \
	cngpijmon-3.10 cnijfilter-3.10 lgmon-3.10 ppd-3.10 printui-3.10 \
	cngpijmon-3.20 cnijfilter-3.20 lgmon-3.20 ppd-3.20 printui-3.20 \
	cngpijmon-3.30 cnijfilter-3.30 lgmon-3.30 ppd-3.30 printui-3.30 \
	cngpijmon-3.40 cnijfilter-3.40 lgmon-3.40 ppd-3.40 printui-3.40 \
	cngpijmon-3.50 cnijfilter-3.50 lgmon-3.50 ppd-3.50 printui-3.50 \
	cngpijmon-3.60 cnijfilter-3.60 lgmon-3.60 ppd-3.60 printui-3.60

scripts=for dir in $(dirs); do\
			(cd $$dir; make $$target)|| exit 1;\
		done

all :
	$(scripts)

clean :
	target=clean; $(scripts)

distclean :
	target=distclean; $(scripts)

install :
	target=install; $(scripts)

