## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DUSE_LIB_GLASE	\
	@GTK_CFLAGS@

bin_PROGRAMS = cngpijmon

cngpijmon_SOURCES = \
	bjcupsmon_main.c \
	bjcupsmon_cups.c bjcupsmon_cups.h \
	bjcupsmon_draw.c bjcupsmon_draw.h \
	bjcupsmon_err.h  bjcupsmon_common.h \
	bjcupsmon_callbacks.c bjcupsmon_funcprot.h \
	bjcupsmon_msgidset.c \
	bjcupsmon_transsts.c bjcupsmon_transsts.h \
	bjcupsmon_ui.c       bjcupsmon_ui.h \
	bjcupsmon_support.h \
	interface.c interface.h support.c support.h 


#cngpijmon_LDADD = @GTK_LIBS@ $(INTLLIBS) -lxml -lcups 
#cngpijmon_LDADD = @GTK_LIBS@ $(INTLLIBS) -lcups 
#cngpijmon_LDADD = @GTK_LIBS@ $(INTLLIBS) -lcups libbscc2sts.a
#cngpijmon_LDADD = @GTK_LIBS@ $(INTLLIBS) -lcups -lbscc2sts
cngpijmon_LDADD = @GTK_LIBS@ $(INTLLIBS) -lcups

cngpijmon_LDFLAGS = -L../../lgmon/src
