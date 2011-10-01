#dirs = libs cngpij cngpijmon ppd pstocanonij 
dirs = libs cngpij pstocanonij backend backendnet cngpijmon/cnijnpr cngpijmon cnijfilter lgmon ppd printui

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

