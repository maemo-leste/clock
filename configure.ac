AC_INIT([clock], [1.00])
AC_CANONICAL_SYSTEM

AM_CONFIG_HEADER(config.h)

AM_MAINTAINER_MODE

AM_INIT_AUTOMAKE

AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_LIBTOOL

AC_HEADER_STDC

AC_PATH_X
AC_PATH_XTRA
AC_SUBST(X_CFLAGS)

AM_GCONF_SOURCE_2
AC_PATH_PROG(GCONFTOOL, gconftool-2)

PKG_PROG_PKG_CONFIG

#+++++++++++++++
# Misc programs 
#+++++++++++++++

AC_SUBST(CFLAGS)

PKG_CHECK_MODULES(CLOCK,
		  [glib-2.0 dnl
		   hildon-1 dnl
		   libcityinfo0-0 dnl
		   libtime dnl
		   gconf-2.0])

AC_SUBST(CLOCK_LIBS)
AC_SUBST(CLOCK_CFLAGS)

#+++++++++++++++++++
# Directories setup
#+++++++++++++++++++

dnl Localization
GETTEXT_PACKAGE=osso-connectivity-ui
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "${GETTEXT_PACKAGE}", [gettext package])

AC_OUTPUT([
Makefile
src/Makefile
libclockcore0-0.pc
])

