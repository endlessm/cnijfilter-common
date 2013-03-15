#dirs = libs cngpij cngpijmon ppd pstocanonij 
dirs = libs cngpij cngpijmnt pstocanonbj pstocanonij backend backendnet cngpijmon-3.90/cnijnpr ppd \
	cngpijmon-2.20 cnijfilter-2.20 lgmon-2.20 printui-2.20 \
	cngpijmon-2.40 cnijfilter-2.40 lgmon-2.40 printui-2.40 \
	cngpijmon-2.50 cnijfilter-2.50 lgmon-2.50 printui-2.50 \
	cngpijmon-2.60 cnijfilter-2.60 lgmon-2.60 printui-2.60 \
	cngpijmon-2.70 cnijfilter-2.70 lgmon-2.70 printui-2.70 \
	cngpijmon-2.80 cnijfilter-2.80 lgmon-2.80 printui-2.80 \
	cngpijmon-2.90 cnijfilter-2.90 lgmon-2.90 printui-2.90 \
	cngpijmon-3.00 cnijfilter-3.00 lgmon-3.00 printui-3.00 \
	cngpijmon-3.10 cnijfilter-3.10 lgmon-3.10 printui-3.10 \
	cngpijmon-3.20 cnijfilter-3.20 lgmon-3.20 printui-3.20 \
	cngpijmon-3.30 cnijfilter-3.30 lgmon-3.30 printui-3.30 \
	cngpijmon-3.40 cnijfilter-3.40 lgmon-3.40 printui-3.40 \
	cngpijmon-3.50 cnijfilter-3.50 lgmon-3.50 printui-3.50 \
	cngpijmon-3.60 cnijfilter-3.60 lgmon-3.60 printui-3.60 \
	cngpijmon-3.70 cnijfilter-3.70 lgmon-3.70 printui-3.70 \
	cngpijmon-3.80 cnijfilter-3.80 lgmon-3.80 printui-3.80 \
	cngpijmon-3.90 cnijfilter-3.90 lgmon-3.90 printui-3.90

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

