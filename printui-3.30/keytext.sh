#!/bin/sh
/usr/bin/perl keytext.pl <keytext/printui.res >po/keystr.h

/usr/bin/intltool-extract --type=gettext/glade printui.glade > /dev/null
mv printui.glade.h po/gladestr.h
