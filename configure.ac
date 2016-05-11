#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([MMC],[0.0.0],[],[mtc],[https://github.com/akashrawal/mmc])
AC_CONFIG_SRCDIR([mmc/utils.h]) #FIXME: filename
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror silent-rules])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])
AM_PROG_AR
LT_INIT

# Checks for programs.
#TODO: Enforce C11
AC_PROG_CC
AM_PROG_CC_C_O

#Write all output

AC_CONFIG_FILES([Makefile
                 data/Makefile
                 data/mmc.pc
                 mmc/Makefile])
AC_OUTPUT
