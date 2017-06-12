lib_LTLIBRARIES = libcmexample2protobuf.la libcmexample2.la
plugindir = @libexecdir@/$(PACKAGE)
plugin_LTLIBRARIES = libcmexample2plugins.la

BASE_CPPFLAGS = \
    -Wall -Werror -Wextra \
    -I$(srcdir)/include -I$(builddir)/include \
    $(PROTOBUF_CFLAGS)
BASE_LDFLAGS =
BASE_LIBS =

dist_noinst_DATA = \
    protobuf/cmexample2domain/requestinterface/readrequest.proto \
    protobuf/cmexample2domain/requestinterface/readresponse.proto \
    protobuf/cmexample2domain/requestinterface/readwriterequest.proto \
    protobuf/cmexample2domain/requestinterface/readwriteresponse.proto \
    protobuf/cmexample2domain/requestinterface/readtownsummaryresponse.proto \
    protobuf/cmexample2domain/requestinterface/readinfrastructureresponse.proto \
    protobuf/cmexample2domain/requestinterface/readcitizensresponse.proto \
    protobuf/cmexample2domain/requestinterface/addbuildingrequest.proto \
    protobuf/cmexample2domain/requestinterface/deletebuildingrequest.proto \
    protobuf/cmexample2domain/requestinterface/addcitizenrequest.proto \
    protobuf/cmexample2domain/requestinterface/deletecitizenrequest.proto \
    protobuf/cmexample2domain/requestinterface/clearallrequest.proto \
    protobuf/cmexample2domain/databasevalues/value.proto \
    protobuf/cmexample2domain/databasevalues/citizen.proto \
    protobuf/cmexample2domain/databasevalues/building.proto \
    protobuf/cmexample2domain/databasevalues/infrastructure.proto

BUILT_SOURCES = \
    $(builddir)/protobuf/cmexample2domain/requestinterface/readrequest.pb.h \
    $(builddir)/protobuf/cmexample2domain/requestinterface/readresponse.pb.h \
    $(builddir)/protobuf/cmexample2domain/requestinterface/readwriterequest.pb.h \
    $(builddir)/protobuf/cmexample2domain/requestinterface/readwriteresponse.pb.h \
    $(builddir)/protobuf/cmexample2domain/requestinterface/readtownsummaryresponse.pb.h \
    $(builddir)/protobuf/cmexample2domain/requestinterface/readinfrastructureresponse.pb.h \
    $(builddir)/protobuf/cmexample2domain/requestinterface/readcitizensresponse.pb.h \
    $(builddir)/protobuf/cmexample2domain/requestinterface/addbuildingrequest.pb.h \
    $(builddir)/protobuf/cmexample2domain/requestinterface/deletebuildingrequest.pb.h \
    $(builddir)/protobuf/cmexample2domain/requestinterface/addcitizenrequest.pb.h \
    $(builddir)/protobuf/cmexample2domain/requestinterface/deletecitizenrequest.pb.h \
    $(builddir)/protobuf/cmexample2domain/requestinterface/clearallrequest.pb.h \
    $(builddir)/protobuf/cmexample2domain/databasevalues/value.pb.h \
    $(builddir)/protobuf/cmexample2domain/databasevalues/citizen.pb.h \
    $(builddir)/protobuf/cmexample2domain/databasevalues/building.pb.h \
    $(builddir)/protobuf/cmexample2domain/databasevalues/infrastructure.pb.h

nodist_libcmexample2protobuf_la_SOURCES = \
    protobuf/cmexample2domain/requestinterface/readrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/readrequest.pb.h \
    protobuf/cmexample2domain/requestinterface/readresponse.pb.cc \
    protobuf/cmexample2domain/requestinterface/readresponse.pb.h \
    protobuf/cmexample2domain/requestinterface/readwriterequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/readwriterequest.pb.h \
    protobuf/cmexample2domain/requestinterface/readwriteresponse.pb.cc \
    protobuf/cmexample2domain/requestinterface/readwriteresponse.pb.h \
    protobuf/cmexample2domain/requestinterface/readtownsummaryresponse.pb.cc \
    protobuf/cmexample2domain/requestinterface/readtownsummaryresponse.pb.h \
    protobuf/cmexample2domain/requestinterface/readinfrastructureresponse.pb.cc \
    protobuf/cmexample2domain/requestinterface/readinfrastructureresponse.pb.h \
    protobuf/cmexample2domain/requestinterface/readcitizensresponse.pb.cc \
    protobuf/cmexample2domain/requestinterface/readcitizensresponse.pb.h \
    protobuf/cmexample2domain/requestinterface/addbuildingrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/addbuildingrequest.pb.h \
    protobuf/cmexample2domain/requestinterface/deletebuildingrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/deletebuildingrequest.pb.h \
    protobuf/cmexample2domain/requestinterface/addcitizenrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/addcitizenrequest.pb.h \
    protobuf/cmexample2domain/requestinterface/deletecitizenrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/deletecitizenrequest.pb.h \
    protobuf/cmexample2domain/requestinterface/clearallrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/clearallrequest.pb.h \
    protobuf/cmexample2domain/databasevalues/value.pb.cc \
    protobuf/cmexample2domain/databasevalues/value.pb.h \
    protobuf/cmexample2domain/databasevalues/citizen.pb.cc \
    protobuf/cmexample2domain/databasevalues/citizen.pb.h \
    protobuf/cmexample2domain/databasevalues/building.pb.cc \
    protobuf/cmexample2domain/databasevalues/building.pb.h \
    protobuf/cmexample2domain/databasevalues/infrastructure.pb.cc \
    protobuf/cmexample2domain/databasevalues/infrastructure.pb.h

libcmexample2plugins_la_SOURCES = \
    src/plugins/common/keyparser.cpp \
    include/plugins/common/keyparser.hpp \
    src/plugins/common/buildings.cpp \
    include/plugins/common/buildings.hpp \
    src/plugins/common/citizens.cpp \
    include/plugins/common/citizens.hpp \
    src/plugins/requesthandler/townrequesthandlerplugin.cpp \
    include/plugins/requesthandler/townrequesthandlerplugin.hpp \
    src/plugins/validator/townvalidatorplugin.cpp \
    include/plugins/validator/townvalidatorplugin.hpp \
    src/plugins/dataparser/towndataparserplugin.cpp \
    include/plugins/dataparser/towndataparserplugin.hpp
libcmexample2plugins_la_CPPFLAGS = $(BASE_CPPFLAGS) $(LIBCM_CFLAGS)
libcmexample2plugins_la_LDFLAGS = $(BASE_LDFLAGS) -avoid-version -module -shared
libcmexample2plugins_la_LIBADD = $(BASE_LIBS) $(LIBCM_LIBS) -lcmexample2protobuf
EXTRA_libcmexample2plugins_la_DEPENDENCIES = libcmexample2protobuf.la

libcmexample2_la_SOURCES = \
    src/town.cpp \
    include/town.hpp
libcmexample2_la_CPPFLAGS = $(BASE_CPPFLAGS) $(LIBCM_CFLAGS)
libcmexample2_la_LDFLAGS = $(BASE_LDFLAGS)
libcmexample2_la_LIBADD = $(BASE_LIBS) $(LIBCM_LIBS) -lcmexample2protobuf
EXTRA_libcmexample2_la_DEPENDENCIES = libcmexample2protobuf.la

%.pb.cc %.pb.h: %.proto
	$(PROTOC) --proto_path=$(srcdir) --cpp_out=$(builddir) $^

libcmexample2.pc: libcmexample2.pc.in
	sed -e 's![@]prefix[@]!$(prefix)!g' \
        -e 's![@]exec_prefix[@]!$(exec_prefix)!g' \
        -e 's![@]includedir[@]!$(includedir)!g' \
        -e 's![@]libdir[@]!$(libdir)!g' \
        -e 's![@]PACKAGE_VERSION[@]!$(PACKAGE_VERSION)!g' \
        -e 's![@]PACKAGE_URL[@]!$(PACKAGE_URL)!g' \
        $< > $@

cmexample2.json: cmexample2.json.in
	sed -e 's![@]plugindir[@]!$(plugindir)!g' \
        $< > $@

pkgincludedir = $(includedir)/cmexamples
pkginclude_HEADERS = \
    include/town.hpp

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = libcmexample2.pc

if ENABLE_CM_CONF
cmconfigdir = $(CM_CONF_DIR)
nodist_cmconfig_DATA = cmexample2.json
endif

EXTRA_DIST = \
    libcmexample2.pc.in \
    cmexample2.json.in

MOSTLYCLEANFILES = \
    libcmexample2.pc \
    cmexample2.json \
    protobuf/cmexample2domain/requestinterface/readrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/readrequest.pb.h \
    protobuf/cmexample2domain/requestinterface/readresponse.pb.cc \
    protobuf/cmexample2domain/requestinterface/readresponse.pb.h \
    protobuf/cmexample2domain/requestinterface/readwriterequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/readwriterequest.pb.h \
    protobuf/cmexample2domain/requestinterface/readwriteresponse.pb.cc \
    protobuf/cmexample2domain/requestinterface/readwriteresponse.pb.h \
    protobuf/cmexample2domain/requestinterface/readtownsummaryresponse.pb.cc \
    protobuf/cmexample2domain/requestinterface/readtownsummaryresponse.pb.h \
    protobuf/cmexample2domain/requestinterface/readinfrastructureresponse.pb.cc \
    protobuf/cmexample2domain/requestinterface/readinfrastructureresponse.pb.h \
    protobuf/cmexample2domain/requestinterface/readcitizensresponse.pb.cc \
    protobuf/cmexample2domain/requestinterface/readcitizensresponse.pb.h \
    protobuf/cmexample2domain/requestinterface/addbuildingrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/addbuildingrequest.pb.h \
    protobuf/cmexample2domain/requestinterface/deletebuildingrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/deletebuildingrequest.pb.h \
    protobuf/cmexample2domain/requestinterface/addcitizenrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/addcitizenrequest.pb.h \
    protobuf/cmexample2domain/requestinterface/deletecitizenrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/deletecitizenrequest.pb.h \
    protobuf/cmexample2domain/requestinterface/clearallrequest.pb.cc \
    protobuf/cmexample2domain/requestinterface/clearallrequest.pb.h \
    protobuf/cmexample2domain/databasevalues/value.pb.cc \
    protobuf/cmexample2domain/databasevalues/value.pb.h \
    protobuf/cmexample2domain/databasevalues/citizen.pb.cc \
    protobuf/cmexample2domain/databasevalues/citizen.pb.h \
    protobuf/cmexample2domain/databasevalues/building.pb.cc \
    protobuf/cmexample2domain/databasevalues/building.pb.h \
    protobuf/cmexample2domain/databasevalues/infrastructure.pb.cc \
    protobuf/cmexample2domain/databasevalues/infrastructure.pb.h
