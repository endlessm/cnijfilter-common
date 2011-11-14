## Process this file with automake to produce Makefile.in

SUBDIRS = po src include

install-data-local:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir); \
	for glade in $(srcdir)/*.glade; do \
	  if test -f $$glade; then \
	    $(INSTALL_DATA) $$glade $(DESTDIR)$(pkgdatadir); \
	  fi \
	done

	if test -d $(srcdir)/pixmaps; then \
	  for pixmap in $(srcdir)/pixmaps/*; do \
	    if test -f $$pixmap; then \
	      $(INSTALL_DATA) $$pixmap $(DESTDIR)$(pkgdatadir); \
	    fi \
	  done \
	fi

	if test -d $(srcdir)/keytext; then \
	  for keytext in $(srcdir)/keytext/*; do \
	    if test -f $$keytext; then \
	      $(INSTALL_DATA) $$keytext $(DESTDIR)$(pkgdatadir); \
	    fi \
	  done \
	fi

	if test -d $(srcdir)/data; then \
	 model=`echo | sed '$(transform)'`; \
	  for data in $(srcdir)/data/*$$model.utl; do \
	    if test -f $$data; then \
	      $(INSTALL_DATA) $$data $(DESTDIR)$(pkgdatadir); \
	    fi \
	  done \
	fi

	if test -d $(srcdir)/pixmaps/pattern; then \
	 model=`echo | sed '$(transform)'`; \
	  for pattern in $(srcdir)/pixmaps/pattern/*$$model.xpm; do \
	    if test -f $$pattern; then \
	      $(INSTALL_DATA) $$pattern $(DESTDIR)$(pkgdatadir); \
	    fi \
	  done \
	fi

dist-hook:
	mkdir $(distdir); \
	for glade in glade/*; do \
	  if test -f $$glade; then \
	    cp -p $$glade $(distdir); \
	  fi \
	done

	if test -d pixmaps; then \
	  mkdir $(distdir)/pixmaps; \
	  for pixmap in pixmaps/*; do \
	    if test -f $$pixmap; then \
	      cp -p $$pixmap $(distdir)/pixmaps; \
	    fi \
	  done \
	fi

	if test -d keytext; then \
	  mkdir $(distdir)/keytext; \
	  for keytext in keytext/*; do \
	    if test -f $$keytext; then \
	      cp -p $$keytext $(distdir)/keytext; \
	    fi \
	  done \
	fi

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = mkinstalldirs  config.rpath
