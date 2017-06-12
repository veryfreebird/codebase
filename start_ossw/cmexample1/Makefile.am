lib_LTLIBRARIES = libcmexample1protobuf.la libcmexample1.la
plugindir = @libexecdir@/$(PACKAGE)
plugin_LTLIBRARIES = libcmexample1plugins.la

BASE_CPPFLAGS = \
    -Wall -Werror -Wextra \
    -I$(srcdir)/include -I$(builddir)/include \
    $(PROTOBUF_CFLAGS)
BASE_LDFLAGS =
BASE_LIBS =

dist_noinst_DATA = \
    protobuf/cmexample1domain/requestinterface/foo.proto \
    protobuf/cmexample1domain/requestinterface/fooiddescriptionpair.proto \
    protobuf/cmexample1domain/requestinterface/readfoorequest.proto \
    protobuf/cmexample1domain/requestinterface/readrequest.proto \
    protobuf/cmexample1domain/requestinterface/readfooresponse.proto \
    protobuf/cmexample1domain/requestinterface/readalldescriptionsresponse.proto \
    protobuf/cmexample1domain/requestinterface/readresponse.proto \
    protobuf/cmexample1domain/requestinterface/writefoorequest.proto \
    protobuf/cmexample1domain/requestinterface/deletefoorequest.proto \
    protobuf/cmexample1domain/requestinterface/readwriterequest.proto \
    protobuf/cmexample1domain/requestinterface/readwriteresponse.proto \
    protobuf/cmexample1domain/databasevalues/foodescription.proto \
    protobuf/cmexample1domain/databasevalues/foovalues.proto

BUILT_SOURCES = \
    $(builddir)/protobuf/cmexample1domain/requestinterface/foo.pb.h \
    $(builddir)/protobuf/cmexample1domain/requestinterface/fooiddescriptionpair.pb.h \
    $(builddir)/protobuf/cmexample1domain/requestinterface/readfoorequest.pb.h \
    $(builddir)/protobuf/cmexample1domain/requestinterface/readrequest.pb.h \
    $(builddir)/protobuf/cmexample1domain/requestinterface/readfooresponse.pb.h \
    $(builddir)/protobuf/cmexample1domain/requestinterface/readalldescriptionsresponse.pb.h \
    $(builddir)/protobuf/cmexample1domain/requestinterface/readresponse.pb.h \
    $(builddir)/protobuf/cmexample1domain/requestinterface/deletefoorequest.pb.h \
    $(builddir)/protobuf/cmexample1domain/requestinterface/writefoorequest.pb.h \
    $(builddir)/protobuf/cmexample1domain/requestinterface/readwriterequest.pb.h \
    $(builddir)/protobuf/cmexample1domain/requestinterface/readwriteresponse.pb.h \
    $(builddir)/protobuf/cmexample1domain/databasevalues/foodescription.pb.h \
    $(builddir)/protobuf/cmexample1domain/databasevalues/foodescription.pb.h \
    $(builddir)/protobuf/cmexample1domain/databasevalues/foovalues.pb.h \
    $(builddir)/protobuf/cmexample1domain/databasevalues/foovalues.pb.h

nodist_libcmexample1protobuf_la_SOURCES = \
    protobuf/cmexample1domain/requestinterface/foo.pb.cc \
    protobuf/cmexample1domain/requestinterface/foo.pb.h \
    protobuf/cmexample1domain/requestinterface/fooiddescriptionpair.pb.cc \
    protobuf/cmexample1domain/requestinterface/fooiddescriptionpair.pb.h \
    protobuf/cmexample1domain/requestinterface/readfoorequest.pb.cc \
    protobuf/cmexample1domain/requestinterface/readfoorequest.pb.h \
    protobuf/cmexample1domain/requestinterface/readrequest.pb.cc \
    protobuf/cmexample1domain/requestinterface/readrequest.pb.h \
    protobuf/cmexample1domain/requestinterface/readfooresponse.pb.cc \
    protobuf/cmexample1domain/requestinterface/readfooresponse.pb.h \
    protobuf/cmexample1domain/requestinterface/readalldescriptionsresponse.pb.cc \
    protobuf/cmexample1domain/requestinterface/readalldescriptionsresponse.pb.h \
    protobuf/cmexample1domain/requestinterface/readresponse.pb.cc \
    protobuf/cmexample1domain/requestinterface/readresponse.pb.h \
    protobuf/cmexample1domain/requestinterface/deletefoorequest.pb.cc \
    protobuf/cmexample1domain/requestinterface/deletefoorequest.pb.h \
    protobuf/cmexample1domain/requestinterface/writefoorequest.pb.cc \
    protobuf/cmexample1domain/requestinterface/writefoorequest.pb.h \
    protobuf/cmexample1domain/requestinterface/readwriterequest.pb.cc \
    protobuf/cmexample1domain/requestinterface/readwriterequest.pb.h \
    protobuf/cmexample1domain/requestinterface/readwriteresponse.pb.cc \
    protobuf/cmexample1domain/requestinterface/readwriteresponse.pb.h \
    protobuf/cmexample1domain/databasevalues/foodescription.pb.cc \
    protobuf/cmexample1domain/databasevalues/foodescription.pb.h \
    protobuf/cmexample1domain/databasevalues/foovalues.pb.cc \
    protobuf/cmexample1domain/databasevalues/foovalues.pb.h

libcmexample1plugins_la_SOURCES = \
    src/plugins/foorequesthandlerplugin.cpp \
    src/plugins/foodataparserplugin.cpp \
    src/plugins/foovalidatorplugin.cpp \
    src/plugins/fookeyformatter.cpp \
    include/plugins/foorequesthandlerplugin.hpp \
    include/plugins/foodataparserplugin.hpp \
    include/plugins/foovalidatorplugin.hpp \
    include/plugins/fookeyformatter.hpp
libcmexample1plugins_la_CPPFLAGS = $(BASE_CPPFLAGS) $(LIBCM_CFLAGS)
libcmexample1plugins_la_LDFLAGS = $(BASE_LDFLAGS) -avoid-version -module -shared
libcmexample1plugins_la_LIBADD = $(BASE_LIBS) $(LIBCM_LIBS) -lcmexample1protobuf
EXTRA_libcmexample1plugins_la_DEPENDENCIES = libcmexample1protobuf.la

libcmexample1_la_SOURCES = \
    src/fooconfiguration.cpp \
    include/fooconfiguration.hpp
libcmexample1_la_CPPFLAGS = $(BASE_CPPFLAGS) $(LIBCM_CFLAGS)
libcmexample1_la_LDFLAGS = $(BASE_LDFLAGS)
libcmexample1_la_LIBADD = $(BASE_LIBS) $(LIBCM_LIBS) -lcmexample1protobuf
EXTRA_libcmexample1_la_DEPENDENCIES = libcmexample1protobuf.la

%.pb.cc %.pb.h: %.proto
	$(PROTOC) --proto_path=$(srcdir) --cpp_out=$(builddir) $^

libcmexample1.pc: libcmexample1.pc.in
	sed -e 's![@]prefix[@]!$(prefix)!g' \
        -e 's![@]exec_prefix[@]!$(exec_prefix)!g' \
        -e 's![@]includedir[@]!$(includedir)!g' \
        -e 's![@]libdir[@]!$(libdir)!g' \
        -e 's![@]PACKAGE_VERSION[@]!$(PACKAGE_VERSION)!g' \
        -e 's![@]PACKAGE_URL[@]!$(PACKAGE_URL)!g' \
        $< > $@

cmexample1.json: cmexample1.json.in
	sed -e 's![@]plugindir[@]!$(plugindir)!g' \
        $< > $@

pkgincludedir = $(includedir)/cmexamples
pkginclude_HEADERS = \
    include/foo.hpp \
    include/fooconfiguration.hpp

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = libcmexample1.pc

if ENABLE_CM_CONF
cmconfigdir = $(CM_CONF_DIR)
nodist_cmconfig_DATA = cmexample1.json
endif

EXTRA_DIST = \
    libcmexample1.pc.in \
    cmexample1.json.in

MOSTLYCLEANFILES = \
    libcmexample1.pc \
    cmexample1.json \
    protobuf/cmexample1domain/requestinterface/foo.pb.cc \
    protobuf/cmexample1domain/requestinterface/foo.pb.h \
    protobuf/cmexample1domain/requestinterface/fooiddescriptionpair.pb.cc \
    protobuf/cmexample1domain/requestinterface/fooiddescriptionpair.pb.h \
    protobuf/cmexample1domain/requestinterface/readfoorequest.pb.cc \
    protobuf/cmexample1domain/requestinterface/readfoorequest.pb.h \
    protobuf/cmexample1domain/requestinterface/readrequest.pb.cc \
    protobuf/cmexample1domain/requestinterface/readrequest.pb.h \
    protobuf/cmexample1domain/requestinterface/readfooresponse.pb.cc \
    protobuf/cmexample1domain/requestinterface/readfooresponse.pb.h \
    protobuf/cmexample1domain/requestinterface/readalldescriptionsresponse.pb.cc \
    protobuf/cmexample1domain/requestinterface/readalldescriptionsresponse.pb.h \
    protobuf/cmexample1domain/requestinterface/readresponse.pb.cc \
    protobuf/cmexample1domain/requestinterface/readresponse.pb.h \
    protobuf/cmexample1domain/requestinterface/deletefoorequest.pb.cc \
    protobuf/cmexample1domain/requestinterface/deletefoorequest.pb.h \
    protobuf/cmexample1domain/requestinterface/writefoorequest.pb.cc \
    protobuf/cmexample1domain/requestinterface/writefoorequest.pb.h \
    protobuf/cmexample1domain/requestinterface/readwriterequest.pb.cc \
    protobuf/cmexample1domain/requestinterface/readwriterequest.pb.h \
    protobuf/cmexample1domain/requestinterface/readwriteresponse.pb.cc \
    protobuf/cmexample1domain/requestinterface/readwriteresponse.pb.h \
    protobuf/cmexample1domain/databasevalues/foodescription.pb.cc \
    protobuf/cmexample1domain/databasevalues/foodescription.pb.h \
    protobuf/cmexample1domain/databasevalues/foovalues.pb.cc \
    protobuf/cmexample1domain/databasevalues/foovalues.pb.h
