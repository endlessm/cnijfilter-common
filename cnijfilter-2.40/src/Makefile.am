INCLUDES = \
	-I$(top_srcdir)/include/cncl \
	-I$(top_srcdir)/include/misc

bin_PROGRAMS = bjfilter

bjfilter_SOURCES = \
	bjferror.c \
	bjferror.h \
	bjfilter.c \
	bjfilter.h \
	bjfimage.c \
	bjfimage.h \
	bjfoption.c \
	bjfoption.h \
	bjfpos.c \
	bjfpos.h \
	bjipc.h \
	bjfrcaccess.c \
	bjfrcaccess.h \
	bjfversion.h \
	getipc.c \
	bjflist.c \
	uitypes.h 


bjfilter_LDADD = -lcnbpcmcm@CNCL_LIB_ID@ -lcnbpess@CNCL_LIB_ID@ -lm -ldl -ltiff -lpng\
			-lcnbpcnclapi@CNCL_LIB_ID@ -lcnbpcnclbjcmd@CNCL_LIB_ID@ -lcnbpcnclui@CNCL_LIB_ID@ -lpopt
bjfilter_LDFLAGS = -L../../@CNCL_LIB_ID@/libs_bin@ARC@
