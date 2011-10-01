bin_PROGRAMS=cngpij

cngpij_SOURCES=\
	bjcups.c getipc.c bjutil.c \
	bjutil.h

cngpij_LDADD= -lpopt -lcups -lparamlist 
cngpij_LDFLAGS = -L../../libs/paramlist

AM_CFLAGS= -O2 -Wall -I../include/cncl -I../include/misc -I../../libs/paramlist

