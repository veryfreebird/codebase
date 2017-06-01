#include "plugins/common/buildings.hpp"

using namespace cmexample2;

Buildings::Buildings():
        keyParser()
{
}

Buildings::~Buildings()
{
}

bool Buildings::exists(Reader& reader, const std::string& name) const
{
    auto data =reader.read(keyParser.getInfrastructureKey());
    if (data != nullptr)
    {
        Value value;
        data.parse(value);
        for (const auto& building : value.infrastructure().building())
            if (building.name().compare(name) == 0)
                return true;
    }
    return false;
}

Building Buildings::read(Reader& reader, const std::string& name) const
{
    auto data =reader.read(keyParser.getInfrastructureKey());
    if (data != nullptr)
    {
        Value value;
        data.parse(value);
        for (const auto& building : value.infrastructure().building())
            if (building.name().compare(name) == 0)
                return building;
    }
    return Building();
}

std::vector<Building> Buildings::readAll(Reader& reader) const
{
    std::vector<Building> buildings;
    auto data =reader.read(keyParser.getInfrastructureKey());
    if (data != nullptr)
    {
        Value value;
        data.parse(value);
        for (const auto& building : value.infrastructure().building())
            buildings.push_back(building);
    }
    return buildings;
}

unsigned int Buildings::totalOpex(Reader& reader) const
{
    int totalOpex = 0;
    auto buildings = readAll(reader);
    for (const auto& building : buildings)
        totalOpex += building.opex();
    return totalOpex;
}

void Buildings::write(ReaderWriter& readerWriter, const Building& building) const
{
    auto value = std::make_shared<Value>();
    bool found = false;
    auto data =readerWriter.read(keyParser.getInfrastructureKey());
    if (data != nullptr)
    {
        data.parse(*value);
        for (auto currentBuilding : *(value->mutable_infrastructure()->mutable_building()))
        {
            if (currentBuilding.name().compare(building.name()) == 0)
            {
                currentBuilding.CopyFrom(building);
                found = true;
            }
        }
    }
    if (!found)
    {
        auto newBuilding = value->mutable_infrastructure()->add_building();
        newBuilding->CopyFrom(building);
    }
    readerWriter.write(keyParser.getInfrastructureKey(), value);
}

void Buildings::remove(ReaderWriter& readerWriter, const std::string& name) const
{
    auto value = std::make_shared<Value>();
    bool found = false;

    auto data =readerWriter.read(keyParser.getInfrastructureKey());
    if (data != nullptr)
    {
        data.parse(*value);
        for (int i = 0; i < value->infrastructure().building().size(); ++i)
        {
            if (value->infrastructure().building().Get(i).name().compare(name) == 0)
            {
                int lastIndex = value->infrastructure().building().size() - 1;
                if (i != lastIndex)
                    value->mutable_infrastructure()->mutable_building()->SwapElements(i,lastIndex);
                value->mutable_infrastructure()->mutable_building()->RemoveLast();
                found = true;
            }
        }
    }

    if (found)
        readerWriter.write(keyParser.getInfrastructureKey(), value);
}
