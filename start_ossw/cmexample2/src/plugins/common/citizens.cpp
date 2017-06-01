#include "plugins/common/citizens.hpp"

using namespace cmexample2;

Citizens::Citizens():
        keyParser()
{
}

Citizens::~Citizens()
{
}

bool Citizens::exists(Reader& reader, const Name& name) const
{
    auto citizenKeys = reader.searchKeys(keyParser.getCitizenKeyPrefix());
    for (const auto& key : citizenKeys)
        if (keyParser.parseCitizenName(key).compare(name) == 0)
            return true;
    return false;
}

Citizen Citizens::read(Reader& reader, const Name& name) const
{
    Value value;
    auto data = reader.read(keyParser.getCitizenKey(name));
    if (data != nullptr)
        data.parse(value);
    return value.citizen();
}

std::map<Citizens::Name,Citizen> Citizens::readAll(Reader& reader) const
{
    std::map<Name,Citizen> citizens;
    auto citizenKeys = reader.searchKeys(keyParser.getCitizenKeyPrefix());
    if (!citizenKeys.empty())
    {
        auto dataMap = reader.read(citizenKeys);
        for (const auto& keyDataPair : dataMap)
        {
            Value value;
            keyDataPair.second.parse(value);
            citizens.insert(std::make_pair(keyParser.parseCitizenName(keyDataPair.first),value.citizen()));
        }
    }
    return citizens;
}

unsigned int Citizens::countInBuilding(Reader& reader, const std::string& buildingName) const
{
    int count = 0;
    auto citizens = readAll(reader);
    for (const auto& item : citizens)
        if (buildingName.compare(item.second.building()) == 0)
            count += 1;
    return count;
}

unsigned int Citizens::totalTax(Reader& reader) const
{
    int totalTax = 0;
    auto citizens = readAll(reader);
    for (const auto& item : citizens)
        totalTax += item.second.tax();
    return totalTax;
}

void Citizens::write(ReaderWriter& readerWriter, const Name& name, const Citizen& citizen) const
{
    auto value = std::make_shared<Value>();
    value->mutable_citizen()->CopyFrom(citizen);
    readerWriter.write(keyParser.getCitizenKey(name), value);
}

void Citizens::remove(ReaderWriter& readerWriter, const Name& name) const
{
    readerWriter.remove(keyParser.getCitizenKey(name));
}
