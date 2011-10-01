filterdir=$(libdir)/cups/filter

filter_PROGRAMS= pstocanonij

pstocanonij_SOURCES= \
	pstocanonij.c canonopt.c \
	canonopt.h paramlist.c \
	paramlist.h 

pstocanonij_LDADD= -lcups ../../libs/buftool/libbuftool.a
pstocanonij_LDFLAGS = -L../../libs/buftool

AM_CFLAGS= -O2 -Wall -I../../libs/buftool

