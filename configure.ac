#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Lavender Throne], [0.8], [lvt-bugs@kurtweber.us])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([m], [sqrt], , AC_MSG_ERROR([no libm found]))
AC_CHECK_LIB([ncurses], [initscr], , AC_MSG_ERROR([ncurses not found]))

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([math.h])
AC_CHECK_HEADERS([time.h])
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stdbool.h])
AC_CHECK_HEADERS([ncurses.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES(Makefile src/Makefile)

AC_OUTPUT
