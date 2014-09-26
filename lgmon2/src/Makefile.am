## Process this file with automake to produce Makefile.in

#cnijlgmon2_bindir = /usr/local/bin
bin_PROGRAMS = cnijlgmon2
transform = 

cnijlgmon2_SOURCES = cnijcomif.c cnijifusb.c cnijlgmon2.c cnijifnet.c keytext.c

CFLAGS = -O2 -Wall -I/usr/include/libusb-1.0 -I./common @XML2_CFLAGS@

cnijlgmon2_LDADD = -ldl -lusb-1.0 -lcnnet -lxml2
