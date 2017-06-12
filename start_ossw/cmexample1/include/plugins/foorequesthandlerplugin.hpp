#include <memory>
#include <cm/reader.hpp>
#include <cm/readerwriter.hpp>
#include <cm/plugin/requesthandlerplugin.hpp>
#include "protobuf/cmexample1domain/requestinterface/readrequest.pb.h"
#include "protobuf/cmexample1domain/requestinterface/readresponse.pb.h"
#include "protobuf/cmexample1domain/requestinterface/readwriterequest.pb.h"
#include "protobuf/cmexample1domain/requestinterface/readwriteresponse.pb.h"
#include "fookeyformatter.hpp"

using configurationmanagement::Data;
using configurationmanagement::Reader;
using configurationmanagement::ReaderWriter;
using configurationmanagement::plugin::RequestHandlerPlugin;
using namespace cmexample1domain::requestinterface;

namespace cmexample1
{
    class FooRequestHandlerPlugin: public RequestHandlerPlugin
    {
    public:
        FooRequestHandlerPlugin();
        ~FooRequestHandlerPlugin();

        std::shared_ptr<const google::protobuf::Message> executeReadOnlyRequest(const Data& params,
                                                                                Reader& reader) override;

        std::shared_ptr<const google::protobuf::Message> executeReadWriteRequest(const Data& params,
                                                                                 ReaderWriter& readerWriter) override;

    private:
        FooKeyFormatter keyFormatter;
        ReadWriteResponse::Status handleWriteFooRequest(ReaderWriter& readerWriter,
                                                        const WriteFooRequest& request);
        ReadResponse::Status handleReadFooRequest(Reader& reader,
                                                  const ReadFooRequest& request,
                                                  ReadFooResponse* response);
        void handleReadAllDescriptionsRequest(Reader& reader, ReadAllDescriptionsResponse* response);
        void handleDeleteFooRequest(ReaderWriter& readerWriter, const DeleteFooRequest& request);
    };
}
