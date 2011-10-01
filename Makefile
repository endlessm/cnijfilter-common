#dirs = libs cngpij cngpijmon ppd pstocanonij 
dirs = libs cngpij pstocanonij backend backendnet cngpijmon/cnijnpr

scripts=for dir in $(dirs); do\
			(cd $$dir; make $$target)|| exit 1;\
		done

all :
	$(scripts)

clean :
	target=clean; $(scripts)

install :
	target=install; $(scripts)

