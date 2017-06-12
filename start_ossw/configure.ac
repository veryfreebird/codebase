AC_INIT([configurationmanagement-examples], [0.0.0], [], [], [https://gitlabe1.ext.net.nokia.com/cm/configurationmanagement-examples])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([subdir-objects foreign tar-pax])
AM_SILENT_RULES([yes])
AC_PROG_CXX
AC_LANG([C++])
AM_PROG_LIBTOOL
AC_CONFIG_MACRO_DIR([m4])
PKG_CHECK_MODULES([LIBCM], [libcm])
PKG_CHECK_MODULES([PROTOBUF], [protobuf >= 2.5.0])
AC_ARG_WITH([cm-conf-dir],
    AS_HELP_STRING([--with-cm-conf-dir[=PATH]],
        [Install CM configuration files in this directory. @<:@default=yes@:>@]),
    [],
    [with_cm_conf_dir=yes])
if test "x$with_cm_conf_dir" = "xyes"; then
    CM_CONF_DIR="`pkg-config libcm --variable=confdir`"
else
    CM_CONF_DIR="$with_cm_conf_dir"
fi
AC_SUBST(CM_CONF_DIR)
AM_CONDITIONAL([ENABLE_CM_CONF],[test "x$with_cm_conf_dir" != "xno"])
AX_CXX_COMPILE_STDCXX(11, [noext], [mandatory])
AC_CHECK_PROG([PROTOC], [protoc], [protoc], [no])
AC_CONFIG_FILES([
 Makefile
 cmexample1/Makefile
 cmexample2/Makefile
])
AC_OUTPUT
