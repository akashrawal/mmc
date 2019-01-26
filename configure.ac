#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([MMC],[0.0.0],[],[mmc],[https://github.com/akashrawal/mmc])
AC_CONFIG_SRCDIR([mmc/mmc.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([auxdir])
AM_INIT_AUTOMAKE([-Wall -Werror silent-rules])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])
AM_PROG_AR
LT_INIT

# Checks for programs.
#TODO: Enforce C11
AC_PROG_CC
AM_PROG_CC_C_O

# Checks for libraries
PKG_CHECK_MODULES([MDSL], [mdsl >= 0.0.0])

#Write all output

AC_CONFIG_FILES([Makefile
                 data/Makefile
                 data/mmc.pc
                 mmc/Makefile])
AC_OUTPUT
