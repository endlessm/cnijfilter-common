## Process this file with automake to produce Makefile.in

INCLUDES = \
  -I$(top_srcdir)/include/cncl \
  -I$(top_srcdir)/include/misc \
  @XML2_CFLAGS@ \
  @GTK_CFLAGS@

bin_PROGRAMS = printui

printui_SOURCES =  main.c \
  loadres.c loadres.h \
  bjuidefs.h \
  msgtable.h \
  globals.h \
  modeltbl.c modeltbl.h \
  callbacks.c callbacks.h \
  comdb.c comdb.h \
  widgets.c widgets.h \
  gdktool.c gdktool.h \
  keytext.c keytext.h \
  msgicon.h \
  dialog.c dialog.h \
  uimain.c uimain.h \
  qualitydlg.c qualitydlg.h \
  colordlg.c colordlg.h \
  colordlg2.c colordlg2.h \
  usrsizedlg.c usrsizedlg.h \
  versiondlg.c versiondlg.h \
  mediasizedlg.c mediasizedlg.h \
  mediatypedlg.c mediatypedlg.h \
  mediaborderdlg.c mediaborderdlg.h \
  pagesizedlg.c pagesizedlg.h \
  xpmproc.c xpmproc.h \
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
#printui_CFLAGS = -O2 -Wall
printui_CFLAGS = -O2 -Wall @UI_DFLAGS@

#printui_LDADD = @GTK_LIBS@ -lxml -lpopt \
#  -lcnbpcnclui@CNCL_LIB_ID@ -lcnbpcmcm@CNCL_LIB_ID@
printui_LDADD = @GTK_LIBS@ -lxml2 -lpopt \
  -lcnbpcnclui@CNCL_LIB_ID@ -lcnbpcmcm@CNCL_LIB_ID@ -lcnbpcnclapi@CNCL_LIB_ID@ \
  -lcnbpcnclbjcmd@CNCL_LIB_ID@ -lcnbpess@CNCL_LIB_ID@ -lcnnet 

printui_LDFLAGS = -L../../@CNCL_LIB_ID@/libs_bin@ARC@ -L../../com/libs_bin@ARC@
