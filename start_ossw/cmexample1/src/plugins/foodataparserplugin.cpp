#include "plugins/foodataparserplugin.hpp"
#include "protobuf/cmexample1domain/databasevalues/foodescription.pb.h"
#include "protobuf/cmexample1domain/databasevalues/foovalues.pb.h"

using namespace cmexample1;
using namespace cmexample1domain::databasevalues;

FooDataParserPlugin::FooDataParserPlugin():
        keyFormatter(FooKeyFormatter())
{
}

FooDataParserPlugin::~FooDataParserPlugin()
{
}

std::shared_ptr<const google::protobuf::Message> FooDataParserPlugin::parse(const std::string& key, const Data& data)
{
    if (keyFormatter.isFooDescriptionKey(key))
    {
        auto msg = std::make_shared<FooDescription>();
        data.parse(*msg);
        return msg;
    }
    if (keyFormatter.isFooValuesKey(key))
    {
        auto msg = std::make_shared<FooValues>();
        data.parse(*msg);
        return msg;
    }
    return nullptr;
}

CM_DEFINE_DATAPARSER_PLUGIN_CREATOR()
{
    return std::make_shared<FooDataParserPlugin>();
}
