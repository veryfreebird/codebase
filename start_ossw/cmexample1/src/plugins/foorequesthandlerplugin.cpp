#include "plugins/foorequesthandlerplugin.hpp"
#include <syslog.h>
#include "protobuf/cmexample1domain/databasevalues/foodescription.pb.h"
#include "protobuf/cmexample1domain/databasevalues/foovalues.pb.h"

using namespace cmexample1;
using namespace cmexample1domain::databasevalues;

FooRequestHandlerPlugin::FooRequestHandlerPlugin():
        keyFormatter(FooKeyFormatter())
{
}

FooRequestHandlerPlugin::~FooRequestHandlerPlugin()
{
}

std::shared_ptr<const google::protobuf::Message> FooRequestHandlerPlugin::executeReadOnlyRequest(const Data& params,
                                                                                                Reader& reader)
{
    ReadRequest request;
    auto response = std::make_shared<ReadResponse>();
    response->set_status(ReadResponse::SUCCESS);

    params.parse(request);
    switch (request.type())
    {
        case (ReadRequest::READ_FOO):
            response->set_status(handleReadFooRequest(reader, request.readfoorequest(), response->mutable_readfooresponse()));
            break;
        case (ReadRequest::READ_ALL_DESCRIPTIONS):
            handleReadAllDescriptionsRequest(reader, response->mutable_readalldescriptionsresponse());
            break;
        default:
            syslog(LOG_ERR, "FooRequestHandlerPlugin::executeReadOnlyRequest, unsupported request type: %d", request.type());
            response->set_status(ReadResponse::INVALID_TYPE);
            break;
    }

    return response;
}

std::shared_ptr<const google::protobuf::Message> FooRequestHandlerPlugin::executeReadWriteRequest(const Data& params,
                                                                                                 ReaderWriter& readerWriter)
{
    ReadWriteRequest request;
    auto response = std::make_shared<ReadWriteResponse>();
    response->set_status(ReadWriteResponse::SUCCESS);

    params.parse(request);
    switch (request.type())
    {
        case (ReadWriteRequest::WRITE_FOO):
            response->set_status(handleWriteFooRequest(readerWriter, request.writefoorequest()));
            break;
        case (ReadWriteRequest::DELETE_FOO):
            handleDeleteFooRequest(readerWriter, request.deletefoorequest());
            break;
        default:
            syslog(LOG_ERR, "FooRequestHandlerPlugin::executeReadWriteRequest, unsupported request type: %d", request.type());
            response->set_status(ReadWriteResponse::INVALID_TYPE);
            break;
    }

    return response;
}

ReadWriteResponse::Status FooRequestHandlerPlugin::handleWriteFooRequest(ReaderWriter& readerWriter,
                                                                        const WriteFooRequest& request)
{
    if (request.foo().has_id())
    {
        auto description = std::make_shared<FooDescription>();
        description->set_description(request.foo().description());
        readerWriter.write(keyFormatter.getFooDescriptionKey(request.foo().id()), description);

        auto values = std::make_shared<FooValues>();
        for (const auto& val : request.foo().value())
            values->add_value(val);
        readerWriter.write(keyFormatter.getFooValuesKey(request.foo().id()), values);
    }
    else
        return ReadWriteResponse::FOO_ID_MISSING;

    return ReadWriteResponse::SUCCESS;
}

ReadResponse::Status FooRequestHandlerPlugin::handleReadFooRequest(Reader& reader,
                                                                  const ReadFooRequest& request,
                                                                  ReadFooResponse* response)
{
    response->mutable_foo()->set_id(request.fooid());

    FooDescription fooDescription;
    auto serializedDescription = reader.read(keyFormatter.getFooDescriptionKey(request.fooid()));
    if (serializedDescription == nullptr)
        return ReadResponse::FOO_NOT_FOUND;
    serializedDescription.parse(fooDescription);
    response->mutable_foo()->set_description(fooDescription.description());

    FooValues fooValues;
    auto serializedValues = reader.read(keyFormatter.getFooValuesKey(request.fooid()));
    if (serializedValues == nullptr)
        return ReadResponse::FOO_NOT_FOUND;
    serializedValues.parse(fooValues);
    for (const auto& val : fooValues.value())
        response->mutable_foo()->add_value(val);

    return ReadResponse::SUCCESS;
}

void FooRequestHandlerPlugin::handleReadAllDescriptionsRequest(Reader& reader,
                                                              ReadAllDescriptionsResponse* response)
{
    auto descriptionKeys = reader.searchKeys(keyFormatter.getFooDescriptionKeyPrefix());
    for (const auto& key : descriptionKeys)
    {
        FooDescription fooDescription;
        auto serializedFooDescription = reader.read(key);
        serializedFooDescription.parse(fooDescription);
        auto item = response->add_fooiddescriptionpair();
        item->set_fooid(keyFormatter.parseFooId(key));
        item->set_description(fooDescription.description());
    }
}

void FooRequestHandlerPlugin::handleDeleteFooRequest(ReaderWriter& readerWriter,
                                                    const DeleteFooRequest& request)
{
    readerWriter.remove(keyFormatter.getFooDescriptionKey(request.fooid()));
    readerWriter.remove(keyFormatter.getFooValuesKey(request.fooid()));
}

CM_DEFINE_REQUESTHANDLER_PLUGIN_CREATOR()
{
    return std::make_shared<FooRequestHandlerPlugin>();
}
