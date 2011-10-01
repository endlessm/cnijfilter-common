## Process this file with automake to produce Makefile.in

# backendnet_bindir = /usr/local/bin
bin_PROGRAMS = cnijnetprn
transform = 

cnijnetprn_SOURCES = cnijnetchk.c cnijnetprn.c 

CFLAGS = -O2 -Wall -I. -I./common 

cnijnetprn_LDADD = -lcnnet -lc -ldl 
cnijnetprn_LDFLAGS = -L../../com/libs_bin@ARC@

