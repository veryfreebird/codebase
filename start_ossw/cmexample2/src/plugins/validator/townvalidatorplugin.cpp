#include "plugins/validator/townvalidatorplugin.hpp"

using namespace cmexample2;

TownValidatorPlugin::TownValidatorPlugin():
        citizens(),
        buildings()
{
}

TownValidatorPlugin::~TownValidatorPlugin()
{
}

ValidatorPlugin::Result TownValidatorPlugin::validateDelta(Reader& reader,
                                                           const Map&,
                                                           const Keys&)
{
    return validateFull(reader);
}

ValidatorPlugin::Result TownValidatorPlugin::validateFull(Reader& reader)
{
    if (citizens.totalTax(reader) < buildings.totalOpex(reader))
        return Result("Total building operating expenses exceeds total tax income.");

    for (const auto& i : citizens.readAll(reader))
    {
        if (!buildings.exists(reader, i.second.building()))
            return Result("Citizen " + i.first +
                          " attached to building " + i.second.building() +
                          " which does not exist.");

    }

    for (const auto& building : buildings.readAll(reader))
    {
        if (building.citizen_limit() < citizens.countInBuilding(reader, building.name()))
            return Result("Building " + building.name() + " citizen limit exceeded.");
    }
    return Result();
}

CM_DEFINE_VALIDATOR_PLUGIN_CREATOR()
{
    return std::make_shared<TownValidatorPlugin>();
}
