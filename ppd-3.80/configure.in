AC_INIT(canonmp230.ppd)
AM_INIT_AUTOMAKE(canonppd, 1.0.0, no-define)

if test "${program_suffix}" = "NONE"; then
	program_suffix="mp230"
fi
PPD_SUFFIX=$program_suffix
AC_SUBST(PPD_SUFFIX)

AC_ARG_ENABLE(ppdpath)
if test "$enable_ppdpath" = ""; then
	enable_ppdpath="${datadir}/cups/model"
fi
XPPDPATH=$enable_ppdpath
AC_SUBST(XPPDPATH)

AC_PROG_INSTALL

AC_OUTPUT(Makefile)
