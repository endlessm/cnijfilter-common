## Process this file with automake to produce Makefile.in

INCLUDES = \
	-I$(top_srcdir)/src \
	@GTK_CFLAGS@

bin_PROGRAMS = lgmon

lgmon_SOURCES = \
	langmon.c lm.h \
	lm_print.c \
	lm_status.c \
	lm_sub.c \
	lmsmsock.h \
	bscc2sts.h
lgmon_LDADD = @GTK_LIBS@ $(INTLLIBS) libbscc2sts.a

libbscc2sts_a_SOURCES = \
	bscc2sts.c \
	commonfunc.c \
	f9xxfunc.c \
	s300func.c \
	s500func.c \
	550ifunc.c \
	850ifunc.c \
	950ifunc.c \
	560ifunc.c \
	860ifunc.c \
	990ifunc.c \
	f9xxtbl.c \
	s300tbl.c \
	s500tbl.c \
	550itbl.c \
	850itbl.c \
	950itbl.c \
	560itbl.c \
	860itbl.c \
	990itbl.c \
	bscc2sts.h \
	commonfunc.h

noinst_LIBRARIES = libbscc2sts.a

