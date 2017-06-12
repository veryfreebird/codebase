#include <memory>
#include <vector>
#include <cm/reader.hpp>
#include <cm/readerwriter.hpp>
#include <cm/plugin/requesthandlerplugin.hpp>
#include "plugins/common/citizens.hpp"
#include "plugins/common/buildings.hpp"
#include "protobuf/cmexample2domain/requestinterface/readwriterequest.pb.h"
#include "protobuf/cmexample2domain/requestinterface/readresponse.pb.h"
#include "protobuf/cmexample2domain/requestinterface/readtownsummaryresponse.pb.h"
#include "protobuf/cmexample2domain/requestinterface/readwriteresponse.pb.h"

using configurationmanagement::Data;
using configurationmanagement::Reader;
using configurationmanagement::ReaderWriter;
using configurationmanagement::plugin::RequestHandlerPlugin;
using namespace cmexample2domain::requestinterface;

namespace cmexample2
{
    class TownRequestHandlerPlugin: public RequestHandlerPlugin
    {
    public:
        TownRequestHandlerPlugin();
        ~TownRequestHandlerPlugin();

        std::shared_ptr<const google::protobuf::Message> executeReadOnlyRequest(const Data& params,
                                                                                Reader& reader) override;

        std::shared_ptr<const google::protobuf::Message> executeReadWriteRequest(const Data& params,
                                                                                 ReaderWriter& readerWriter) override;

    private:
        Citizens citizens;
        Buildings buildings;

        void handleRequest(Reader& reader, ReadTownSummaryResponse& response);
        void handleRequest(Reader& reader, ReadInfrastructureResponse& response);
        void handleRequest(Reader& reader, ReadCitizensResponse& response);
        ReadWriteResponse::Status handleRequest(ReaderWriter& readerWriter, const AddBuildingRequest& request);
        void handleRequest(ReaderWriter& readerWriter, const DeleteBuildingRequest& request);
        ReadWriteResponse::Status handleRequest(ReaderWriter& readerWriter, const AddCitizenRequest& request);
        void handleRequest(ReaderWriter& readerWriter, const DeleteCitizenRequest& request);
        void handleClearAllRequest(ReaderWriter& readerWriter);
    };
}
