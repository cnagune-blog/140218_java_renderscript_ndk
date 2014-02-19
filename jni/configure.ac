# -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT(vision, 0.1, blog@cnagune.pe.kr)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
#AC_PROG_INSTALL
#AC_PROG_MAKE_SET

#gcov test
AC_ARG_WITH([gcovflag],
    AC_HELP_STRING([--with-gcovflag], [compile with gcov flags (default is NO)]),
    [GCOVFLAG=yes],
    [GCOVFLAG=no]
)
AC_MSG_RESULT(gcovflag = $GCOVFLAG)
AC_SUBST(GCOVFLAG)


#ARM_NEON
AC_ARG_WITH([armneon],
    AC_HELP_STRING([--with-armneon], [compile with arm neon instruction (default is NO)]),
    [ARMNEON=yes],
    [ARMNEON=no]
)
AC_MSG_RESULT(armneon = $ARMNEON)
AC_SUBST(ARMNEON)


# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([float.h limits.h stddef.h stdint.h stdlib.h string.h strings.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([atexit dup2 floor memset rmdir sqrt strcasecmp strchr strdup strerror])

# enable debug
AC_ARG_ENABLE([debug],
	[AC_HELP_STRING([--enable-debug],
					[Turn on debugging and compile time warning (default=enable)])],
	[DBG=$enableval],
	[DBG=no]
)
if test $DBG = yes; then
	AC_MSG_RESULT([enable debug])
else
	AC_MSG_RESULT([disable debug])
fi
AC_SUBST(DBG)


AC_CONFIG_FILES([Makefile.common])
AC_OUTPUT
