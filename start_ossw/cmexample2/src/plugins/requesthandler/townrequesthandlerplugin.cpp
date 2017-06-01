#include "plugins/requesthandler/townrequesthandlerplugin.hpp"
#include <syslog.h>
#include "protobuf/cmexample2domain/requestinterface/readrequest.pb.h"

using namespace cmexample2;
using namespace cmexample2domain::databasevalues;

namespace
{
    typedef std::string BuildingName;
    typedef std::string CitizenName;
    typedef std::map<BuildingName,std::set<CitizenName>> BuildingCitizensMap;

    BuildingCitizensMap initBuildingCitizensMap(const std::map<Citizens::Name,Citizen>& citizens);

    void addToBuildingCitizensMap(BuildingCitizensMap& buildingMap,
                                  const std::string& buildingName,
                                  const std::string& citizenName);
}

TownRequestHandlerPlugin::TownRequestHandlerPlugin():
        citizens(),
        buildings()
{
}

TownRequestHandlerPlugin::~TownRequestHandlerPlugin()
{
}

std::shared_ptr<const google::protobuf::Message> TownRequestHandlerPlugin::executeReadOnlyRequest(const Data& params,
                                                                                                  Reader& reader)
{
    ReadRequest request;
    params.parse(request);
    auto response = std::make_shared<ReadResponse>();

    switch (request.type())
    {
        case (ReadRequest::READ_TOWN_SUMMARY):
            handleRequest(reader, *response->mutable_townsummary());
            break;
        case (ReadRequest::READ_INFRASTRUCTURE):
            handleRequest(reader, *response->mutable_infrastructure());
            break;
        case (ReadRequest::READ_CITIZENS):
            handleRequest(reader, *response->mutable_citizens());
            break;
        case (ReadRequest::UNKNOWN):
            syslog(LOG_ERR, "TownRequestHandlerPlugin::executeReadOnlyRequest, unknown request type.");
            break;
    }

    return response;
}

std::shared_ptr<const google::protobuf::Message> TownRequestHandlerPlugin::executeReadWriteRequest(const Data& params,
                                                                                                   ReaderWriter& readerWriter)
{
    ReadWriteRequest request;
    params.parse(request);
    auto response = std::make_shared<ReadWriteResponse>();
    response->set_status(ReadWriteResponse::SUCCESS);

    switch (request.readWriteRequest_case())
    {
        case (ReadWriteRequest::kAddBuildingRequest):
            response->set_status(handleRequest(readerWriter, request.addbuildingrequest()));
            break;
        case (ReadWriteRequest::kDeleteBuildingRequest):
            handleRequest(readerWriter, request.deletebuildingrequest());
            break;
        case (ReadWriteRequest::kAddCitizenRequest):
            response->set_status(handleRequest(readerWriter, request.addcitizenrequest()));
            break;
        case (ReadWriteRequest::kDeleteCitizenRequestFieldNumber):
            handleRequest(readerWriter, request.deletecitizenrequest());
            break;
        case (ReadWriteRequest::kClearAllRequest):
            handleClearAllRequest(readerWriter);
            break;
        case (ReadWriteRequest::READWRITEREQUEST_NOT_SET):
            syslog(LOG_ERR, "TownRequestHandlerPlugin::executeReadWriteRequest, empty request!");
            break;
    }

    return response;
}

void TownRequestHandlerPlugin::handleRequest(Reader& reader, ReadTownSummaryResponse& response)
{
    response.set_population(citizens.readAll(reader).size());
    response.set_finance(citizens.totalTax(reader) - buildings.totalOpex(reader));
}

void TownRequestHandlerPlugin::handleRequest(Reader& reader, ReadInfrastructureResponse& response)
{
    auto buildingCitizensMap = initBuildingCitizensMap(citizens.readAll(reader));
    for (const auto& building : buildings.readAll(reader))
    {
        auto buildingInfo = response.add_buildinginfo();
        buildingInfo->set_name(building.name());
        buildingInfo->set_opex(building.opex());
        auto it = buildingCitizensMap.find(building.name());
        if (it != buildingCitizensMap.end())
        {
            buildingInfo->set_freespaces(building.citizen_limit() - it->second.size());
            for (const auto& citizen : it->second)
                buildingInfo->add_citizen(citizen);
        }
        else
            buildingInfo->set_freespaces(building.citizen_limit());
    }
}

void TownRequestHandlerPlugin::handleRequest(Reader& reader, ReadCitizensResponse& response)
{
    for (const auto& citizen : citizens.readAll(reader))
    {
        auto citizenInfo = response.add_citizeninfo();
        citizenInfo->set_name(citizen.first);
        citizenInfo->set_tax(citizen.second.tax());
        citizenInfo->set_building(citizen.second.building());
    }
}

ReadWriteResponse::Status TownRequestHandlerPlugin::handleRequest(ReaderWriter& readerWriter, const AddBuildingRequest& request)
{
    if (buildings.exists(readerWriter, request.name()))
        return ReadWriteResponse::BUILDING_ALREADY_EXISTS;
    else
    {
        Building building;
        building.set_name(request.name());
        building.set_opex(request.opex());
        building.set_citizen_limit(request.citizen_limit());
        buildings.write(readerWriter, building);
    }
    return ReadWriteResponse::SUCCESS;
}

void TownRequestHandlerPlugin::handleRequest(ReaderWriter& readerWriter, const DeleteBuildingRequest& request)
{
    buildings.remove(readerWriter, request.name());
}

ReadWriteResponse::Status TownRequestHandlerPlugin::handleRequest(ReaderWriter& readerWriter, const AddCitizenRequest& request)
{
    if (citizens.exists(readerWriter, request.name()))
        return ReadWriteResponse::CITIZEN_ALREADY_EXISTS;
    else
    {
        Citizen citizen;
        citizen.set_tax(request.tax());
        citizen.set_building(request.building());
        citizens.write(readerWriter, request.name(), citizen);
    }
    return ReadWriteResponse::SUCCESS;
}

void TownRequestHandlerPlugin::handleRequest(ReaderWriter& readerWriter, const DeleteCitizenRequest& request)
{
    citizens.remove(readerWriter, request.name());
}

void TownRequestHandlerPlugin::handleClearAllRequest(ReaderWriter& readerWriter)
{
    for (const auto& citizen : citizens.readAll(readerWriter))
        citizens.remove(readerWriter, citizen.first);
    for (const auto& building : buildings.readAll(readerWriter))
        buildings.remove(readerWriter, building.name());
}

namespace
{

void addToBuildingCitizensMap(BuildingCitizensMap& buildingMap, const std::string& buildingName, const std::string& citizenName)
{
    auto i = buildingMap.find(buildingName);
    if (i != buildingMap.end())
        i->second.insert(citizenName);
    else
        buildingMap.insert(std::make_pair(buildingName,std::set<std::string>({citizenName})));
}

BuildingCitizensMap initBuildingCitizensMap(const std::map<Citizens::Name,Citizen>& citizens)
{
    BuildingCitizensMap buildingCitizensMap;
    for (const auto& citizenMap : citizens)
        if (citizenMap.second.has_building())
            addToBuildingCitizensMap(buildingCitizensMap, citizenMap.second.building(), citizenMap.first);
    return buildingCitizensMap;
}

}

CM_DEFINE_REQUESTHANDLER_PLUGIN_CREATOR()
{
    return std::make_shared<TownRequestHandlerPlugin>();
}
