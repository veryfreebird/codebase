#include "plugins/dataparser/towndataparserplugin.hpp"
#include "protobuf/cmexample2domain/databasevalues/value.pb.h"

using namespace cmexample2;
using namespace cmexample2domain::databasevalues;

TownDataParserPlugin::TownDataParserPlugin()
{
}

TownDataParserPlugin::~TownDataParserPlugin()
{
}

std::shared_ptr<const google::protobuf::Message> TownDataParserPlugin::parse(const std::string&, const Data& data)
{
    auto msg = std::make_shared<Value>();
    data.parse(*msg);
    return msg;
}

CM_DEFINE_DATAPARSER_PLUGIN_CREATOR()
{
    return std::make_shared<TownDataParserPlugin>();
}
