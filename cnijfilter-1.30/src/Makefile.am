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
	uitypes.h 

bjfilter_LDADD = -lcnbpcmcm -lcnbpwcc -lcnbphtmg -lm -ldl -ltiff -lpng\
			-lcnclapi -lcnclbjcmd -lcnbpsmth -lcnclui -lpopt -ldl
bjfilter_LDFLAGS = -L../../001/libs_bin@ARC@
