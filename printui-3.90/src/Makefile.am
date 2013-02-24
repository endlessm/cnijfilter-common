## Process this file with automake to produce Makefile.in

INCLUDES = \
  -I$(top_srcdir)/include/cncl \
  -I$(top_srcdir)/include/misc \
  @XML2_CFLAGS@ \
  @GTK_CFLAGS@

bin_PROGRAMS = maintenance

maintenance_SOURCES =  main.c \
  msgtable.h \
  globals.h \
  callbacks.c callbacks.h \
  comdb.c comdb.h \
  keytext.c keytext.h \
  msgicon.h \
  ipcproc.c ipcproc.h \
  interface.c interface.h \
  util_regi.c util_regi.h  \
  util_parse_flow.c util_parse_flow.h \
  util_parse_dialogstr.c util_parse_dialogstr.h \
  util_parse_function.c util_parse_function.h \
  util_com.c util_com.h  \
  util_cmd.h \
  util_funclist.c util_funclist.h \
  util_cmdlist.c util_cmdlist.h \
  util_setconfig.c util_setconfig.h \
  util_cleaning.c util_cleaning.h \
  util_nozzlecheck.c util_nozzlecheck.h \
  support.c support.h

#UI_DFLAGS= -D_PRINTUI_DEBUG_

#CFLAGS = -O2 -Wall
#maintenance_CFLAGS = -O2 -Wall
maintenance_CFLAGS = -O2 -Wall @UI_DFLAGS@

#maintenance_LDADD = @GTK_LIBS@ -lxml -lpopt \
#  -lcnbpcnclui@CNCL_LIB_ID@ -lcnbpcmcm@CNCL_LIB_ID@
maintenance_LDADD = @GTK_LIBS@ -lxml2 -lpopt -lcnbpcmcm@CNCL_LIB_ID@ -lcnbpcnclapi@CNCL_LIB_ID@ \
  -lcnbpcnclbjcmd@CNCL_LIB_ID@ -lcnbpess@CNCL_LIB_ID@ -ldl

maintenance_LDFLAGS = -L../../@CNCL_LIB_ID@/libs_bin@ARC@ -L../../com/libs_bin@ARC@
