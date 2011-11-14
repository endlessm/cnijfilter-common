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
## lgmon_DEPENDENCIES = libbscc2sts.a

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
	ip1000func.c \
	ip3100func.c \
	ip4100func.c \
	ip8600func.c \
	ip2200func.c \
	ip4200func.c \
	ip6600dfunc.c \
	ip7500func.c \
	mp500func.c \
	ip3300func.c \
	ip4300func.c \
	mp510func.c \
	mp600func.c \
	mp160func.c \
	ip2500func.c \
	ip90func.c \
	mp210func.c \
	f9xxtbl.c \
	s300tbl.c \
	s500tbl.c \
	550itbl.c \
	850itbl.c \
	950itbl.c \
	560itbl.c \
	860itbl.c \
	990itbl.c \
	ip1000tbl.c \
	ip3100tbl.c \
	ip4100tbl.c \
	ip8600tbl.c \
	ip2200tbl.c \
	ip4200tbl.c \
	ip6600dtbl.c \
	ip7500tbl.c \
	mp500tbl.c \
	ip3300tbl.c \
	ip4300tbl.c \
	mp510tbl.c \
	mp600tbl.c \
	mp160tbl.c \
	ip2500tbl.c \
	ip90tbl.c \
	mp210tbl.c \
	bscc2sts.h \
	commonfunc.h

noinst_LIBRARIES = libbscc2sts.a

