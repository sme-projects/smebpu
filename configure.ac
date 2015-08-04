AC_INIT([bpusme], [0.1.0])
AM_INIT_AUTOMAKE

AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX

# Enable compiler warnings/errors
AX_CHECK_COMPILE_FLAG([-Wall], [CXXFLAGS="$CXXFLAGS -Wall"], [], [])
AX_CHECK_COMPILE_FLAG([-Werror], [CXXFLAGS="$CXXFLAGS -Werror"], [], [])
AX_CHECK_COMPILE_FLAG([-pedantic], [CXXFLAGS="$CXXFLAGS -pedantic"], [], [])

AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])
#LT_INIT

PKG_CHECK_MODULES([SME], [libsme >= 0.0.1])
#AC_SUBST(SME_CFLAGS)
#AC_SUBST(SME_LIBS)


AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
