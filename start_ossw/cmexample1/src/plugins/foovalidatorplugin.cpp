#include "plugins/foovalidatorplugin.hpp"
#include <syslog.h>
#include "protobuf/cmexample1domain/databasevalues/foodescription.pb.h"
#include "protobuf/cmexample1domain/databasevalues/foovalues.pb.h"

using namespace cmexample1;
using namespace cmexample1domain::databasevalues;

FooValidatorPlugin::FooValidatorPlugin():
        keyFormatter(FooKeyFormatter())
{
}

FooValidatorPlugin::~FooValidatorPlugin()
{
}

ValidatorPlugin::Result FooValidatorPlugin::validateDelta(Reader& reader, const Map&, const Keys&)
{
    if (!checkFooDescriptionsUniqueness(reader))
        return Result("Delta validation failed, descriptions are not unique.");
    return Result();
}

ValidatorPlugin::Result FooValidatorPlugin::validateFull(Reader& reader)
{
    if (!checkFooDescriptionsUniqueness(reader))
        return Result("Full validation failed, descriptions are not unique.");
    return Result();
}

bool FooValidatorPlugin::checkFooDescriptionsUniqueness(Reader& reader)
{
    std::set<std::string>descriptions;
    auto descriptionKeys = reader.searchKeys(keyFormatter.getFooDescriptionKeyPrefix());
    for (const auto& key : descriptionKeys)
    {
        FooDescription fooDescription;
        auto serializedFooDescription = reader.read(key);
        serializedFooDescription.parse(fooDescription);
        if (!descriptions.insert(fooDescription.description()).second)
        {
            syslog(LOG_ERR, "Validation failed. Foo description not unique: %s",
                   fooDescription.description().c_str());
            return false;
        }
    }
    return true;
}

CM_DEFINE_VALIDATOR_PLUGIN_CREATOR()
{
    return std::make_shared<FooValidatorPlugin>();
}
