
# Table of contents

- [Introduction](#introduction)
- [Prerequisites](#prerequisites)
- [Example1: Simple read-only and read-write transactions with one domain](#example1)
- [Example2: Town configuration with change notifications](#example2)

# Introduction

This repository contains CM (Configuration Management) service usage examples.

Examples are delivered as shared libraries.

Repository [configurationmanagement-demo](https://gitlabe1.ext.net.nokia.com/cm/configurationmanagement-demo)
contains demo applications, which uses above mentioned library interfaces.

# Prerequisites

## Read documentation

From CM main repository [README](https://gitlabe1.ext.net.nokia.com/cm/configurationmanagement/blob/master/README.md)
file you will find instructions that how to generate Doxygen documentation.

Read documentation as a reference, issues described there are not explained
again in examples. Without understanding the basic concepts (like different
plugin types and offered API's) it might be difficult to follow these examples.

## Install CM API libraries and header files

Another prerequisite is that you are familiar how to compile, install and
start-up CM services. Instructions for those steps are also found from main
repository [README](https://gitlabe1.ext.net.nokia.com/cm/configurationmanagement/blob/master/README.md)
file.

For example:

    git clone https://gitlabe1.ext.net.nokia.com/cm/configurationmanagement.git
    cd configurationmanagement
    ./autogen.sh
    ./configure
    make install

Automake tools configure script checks that all dependencies are fulfilled,
install possibly missing packages to continue.

## Configure Redis to its default port

CM can be deployed on top of any noSQL database, by default it uses
[Redis](http://redis.io/). If not otherwise configured it tries to find
`redis-server` from its default port (localhost:6379).

You will find a script to start `redis-server` on that port from its code
repository, see Redis [README](https://github.com/antirez/redis/blob/unstable/README.md).

# Compiling and installing examples

## Create separate compile folder

Repository folder is kept cleaner when compilation is done in separate folder.

In following instructions `<repopath>` refers to place where this repository
was cloned.

Path to folder that you created for compilation is referred as `<compilepath>`.

## Compile and install

Run `autogen.sh` script in repo folder for both example libraries and demo
application:

    cd <repopath>
    ./autogen.sh

Then execute `configure` script and `make install` in compilation folder:

    mkdir <compilepath>
    <repopath>/configure
    make install

Produced deliverables (in `/usr/local/` or in path given with `--prefix` option
for configure script):
* `/lib/`: Shared libraries for examples (starts with prefix "libcmexample").
* `/etc/`: JSON configuration files defining data domains and transaction groups
(starts with prefix "cmexample").
* `/include/cmexamples/`: Headers for example library services.

## Restart cmengine

Process `cmengine` must be restarted always when new plugins are installed
(i.e. when new version of examplelibs are installed in our case). This is
because plugins are loaded only in start-up phase.

Note that restarting `cmengine` will have effect also to possible other users
of CM services (ongoing transactions will fail), but if you are running tests
in development / test environment you can restart it with following commands:

    pkill cmengine
    cmengine -p

If `cmengine` is managed by systemd (depends on deployment), then use systemd
commands instead:

    systemctl stop cmengine
    systemctl start cmengine

## Verify installation

Demo applications are on separate [repository](https://gitlabe1.ext.net.nokia.com/cm/configurationmanagement-demo)
compile and install those.

Verify installation by executing for example the first demo application:

    cmdemo1

## Typical problems

### No package 'libcmapi' found

When running `configure` script for examplelibs it will check that all
dependencies have been installed.

If `libcmapi` is missing it means that cm services have not been installed
successfully - or those are installed to the place where pkg-config can't
find it.

### No package 'libcmex1' found

Demo applications depends on examplelibs, check that you have installed example
libraries as instructed above.

### Start transaction fails to Redis error

If all transactions fail due Redis errors (exact error may vary a bit
depending on the example use case), then most likely `redis-server` is not
running on expected port.

Check redis configuration instructions above.

You can test redis connection with following command:

    redis-cli
    127.0.0.1:6379> PING
    PONG
    127.0.0.1:6379> exit

### Start transaction fails: 'unknown or empty group'

`cmengine` does not find JSON configuration files produced by examplelibs
installation.

If you have installed CM libraries and example JSON files to different place
on purpose, you may set path with `--conf-dir` option (note that `--help` will
show that what is the default path).

### Start transaction will take exceptionally long time or return timeout

Check that `cmengine` process is running.

    ps -C cmengine

Other possibility is that there are ongoing transaction(s) that are preventing
new one, e.g. only one write transaction is allowed at the time for same domain.

Output ongoing transactions:

    loki list-transactions

In transaction listing, there are first transaction type (`read` or
`read-write`), and after that transaction group.

Transaction groups in these examples are all starting with `cmexample` prefix
(e.g. `cmexample1trgroup`).

If those exists, you may remove them with following command (long string after
transaction group is `<transactionID>` in loki list command output):

    loki cancel-transaction --txn-id "<transactionID>"

When playing around with demo applications (e.g. by modifying the code of
those), you may easily cause transactions that are neither properly committed
nor cancelled.

# Examples

## Example1: Simple read-only and read-write transactions with one domain <a name="example1"></a>

### Overview

In this example we have only one configuration item [Foo](cmexample1/include/foo.hpp)
which contains ID, description and array of values.

Addition to interface library, following plugins are implemented:
* Request handler plugin
* Data parser plugin
* Validator plugin

### Implementation

#### Library interface to access `Foo` configuration item

Header file: /cmexample1/include/[fooconfiguration.hpp](cmexample1/include/fooconfiguration.hpp)   
Source code: /cmexample1/src/[fooconfiguration.cpp](cmexample1/src/fooconfiguration.cpp)

Implemented as a `FooConfiguration` class, it provides methods `writeFoo`,
`readFoo`, `readDescriptions` & `deleteFoo`.

Library interface provides an abstraction between data types used
at the application side and data model used inside data domain.

Notice that transaction management is at the upper level, i.e. transaction ID
is given as a input parameter to this library.

Implementation uses synchronous CM `RequestDispatcher` API (see its documentation as
a reference).

RequestDispatcher instance must be created by calling `create` method, this is done in
`FooConfiguration` class constructor.

RequestDispatcher is used to send messages to our self-implemented request handler plugin.

All methods in our example library class will work in a similar way, let's
look closer the `FooConfiguration::writeFoo` implementation.

At first it fills `ReadWriteRequest` protobuf message, this message is our
self-defined interface towards request handler plugin. From CM point of view this
message is transparent data.

Messages are sent to request handler plugin with RequestDispatcher `readWriteRequest`
or `readOnlyRequest` method. If `readWriteRequest` is tried to be used inside
read-only transaction, an exception will be raised by CM. Inside read-write
transaction both request types may be used.

`ReadWriteResponse` is accordingly our self-defined Protobuf message sent by
request handler plugin as a response to request in question.

Because CM does not know the actual Protobuf messages that domain will use,
return value is transparent binary data. It must be parsed to Protobuf message
before fields can be accessed.

    auto ret = requestDispatcher->readWriteRequest(txid, domainName, readWriteRequest);
    ret.parse(readWriteResponse);

See CM API documentation for `Data` class for further details.

#### Request handler plugin

Header file: /cmexample1/include/plugins/[foorequesthandlerplugin.hpp](cmexample1/include/plugins/foorequesthandlerplugin.hpp)   
Source code: /cmexample1/src/plugins/[foorequesthandlerplugin.cpp](cmexample1/src/plugins/foorequesthandlerplugin.cpp)

The main task of request handler plugin is to manage database key model. It hides
that how keys are formed and what is stored behind each key.

Interface that it provides for above mentioned data domain public library
should not contain any direct information related to database keys.

Recommendation for request handler plugin interface is that it will implement
a bigger use case with one request. This is much more efficient and use case
specific interfaces are also better from maintenance point of view.

Example of (simple) use case in our case is reading all Foo descriptions,
instead of reading each Foo data in library side in a loop we ask all
descriptions with one request from request handler plugin.

Let's look some details in request handler plugin implementation.

We need to implement `RequestHandlerPlugin` abstract class interface. Instance
of this class is provided to CM with `CM_DEFINE_REQUESTHANDLER_PLUGIN_CREATOR`
macro.

    CM_DEFINE_REQUESTHANDLER_PLUGIN_CREATOR()
    {
        return std::make_shared<FooRequestHandlerPlugin>();
    }

Protobuf message that was sent by interface library (as explained in previous
chapter) will be delivered by CM to `executeReadWriteRequest` method. Because
CM does not know the structure of this message it is given as a `Data` class
instance, we need to parse (i.e. de-serialize) message before accessing
`ReadWriteRequest` message fields.

The real functionality in case of Foo write request is in
`handleWriteFooRequest` method.

In our simple example we have only two key types:
* Key name: `foo_description_<foo_id>`, Value type: [FooDescription](cmexample1/protobuf/cmexample1domain/databasevalues/foodescription.proto)
* Key name: `foo_values_<foo_id>`, Value type: [FooValues](cmexample1/protobuf/cmexample1domain/databasevalues/foovalues.proto)

To access values behind these keys in database, we use CM `Reader` API for
read-only requests and `ReaderWriter` API for read-write requests.

For example in case of Foo description key:

    auto description = std::make_shared<FooDescription>();
    description->set_description(request.foo().description());
    readerWriter.write(getFooDescriptionKey(request.foo().id()), description);

#### Data parser plugin

Header file: /cmexample1/include/plugins/[foodataparserplugin.hpp](cmexample1/include/plugins/foodataparserplugin.hpp)   
Source code: /cmexample1/src/plugins/[foodataparserplugin.cpp](cmexample1/src/plugins/foodataparserplugin.cpp)

CM does not have protobuf generated code available to parse data behind
database keys.

For normal operations it is just fine, as data is transparent for CM.

In case of problem investigations it would be really nice to see database
key values in user readable format. To achieve this it is very much recommended
that all domains will provide `DataParserPlugin` implementation for CM.

Implementation is very easy, only one abstract method `parse` exists and actual
implementation has been automatically generated by protobuf code generator:

For example, for `FooDescription` value in our example case:

    auto msg = std::make_shared<FooDescription>();
    data.parse(*msg);
    return msg;

#### Validator plugin

Validator plugin is optional.

Idea is that configuration change transaction can be first built step by step,
and after whole transaction is ready then it is validated at once.

Two validation types exist:
* Delta validation: Executed automatically when read-write transaction is
committed. May also be executed manually via `TransactionManager` API.
Validator implementation may check added/removed keys, and read
existing keys.
* Full validation: Manually validating the whole configuration.

If manually executed validation fails, then user may fix configuration
and re-try later. If validation executed automatically in commit phase
fails, then transaction is automatically canceled.

In our simple Foo configuration case we have defined only one validation
rule, Foo descriptions must be unique.

Notice that when we read keys and values in `checkFooDescriptionsUniqueness`
method, reader returns those as they would be in configuration if ongoing
transaction would have been committed - not the current configuration from
database.

If validation fails `ValidatorPlugin::Result` is filled with string containing
error message.

In case that validation is passed, an empty result is returned.

#### Protobuf messages

Messages between library interface and request handler plugin, as well as
values behind database keys are defined as [Google Protocol Buffer](https://developers.google.com/protocol-buffers/)
messages.

It has very good documentation and guideline for best practices, reading
those is very much recommended before starting to implement data
domain functionality.

One issue that is not so well documented is that if libprotobuf library is
loaded only once to the application (which is the typical case), then canonical
names for all protobuf messages used in application must be unique. This
uniqueness applies also to all messages used inside libraries that are
linked to the application.

Protobuf library creates canonical name for messages so that it includes
path given for `protoc` command, and the file name. To avoid name collision
path should contain something that is most likely not used in other domain's
library interfaces. In our example case we have followed naming convention
`/<domain name>/<message package name>/<message name>.proto`.

It is up to domain how to manage message types, in this example message types
related to database values and request handler plugin interface are totally
separated. Those are defined in separate message packages (namespaces) and same
message types are not cross referred between packages.

Doing this way some basic types might be duplicate in these packages, but in
other hand separation gives following benefits:
* Request interface use cases can be modified without a fear that it will have
some side effect to data structures in database. If message types stored to
database are changed then data version numbering, backward combability and
possibly also data conversions must be considered.
* Data behind keys can be re-structured without any visibility to request
handler plugin interface.

## Example2: Town configuration with change notifications <a name="example2"></a>

### Overview

This example library provides configuration interface for Town Demo (demo2),
which is located in [demo repository.](https://gitlabe1.ext.net.nokia.com/cm/configurationmanagement-demo)

Modifications to Town configuration will publish notifications, which can be
subscribed by activators. Demo2 will use this mechanism to reload daemon
process configuration after changes has been applied.

Plugin implementations are not explained in detailed level, those will work
in a similar way than plugins explained in example1.

### Library interface for Town configuration

Header file: /cmexample2/include/[town.hpp](cmexample2/include/town.hpp)   
Source code: /cmexample2/src/[town.cpp](cmexample2/src/town.cpp)

Provides methods to add, delete and show buildings & citizens of the town.

### Validation rules

Total building operating expenses may not exceed total tax income.

Citizen may not be attached to building that does not exists.

Citizen limit set for building may not be exceeded.

### Notifications

In domain [JSON configuration file](cmexample2/cmexample2.json.in)
notifications are defined in "notifications" section.

It will define the notification key that listeners should monitor, and
key prefixes to trigger notification key publishing.

In our example we have one notification key "cmexample2notificationkey", which
is published on any change in domain (Town) configuration.

