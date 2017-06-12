#include "town.hpp"
#include <boost/lexical_cast.hpp>
#include <cctype>
#include "protobuf/cmexample2domain/requestinterface/readrequest.pb.h"
#include "protobuf/cmexample2domain/requestinterface/readresponse.pb.h"
#include "protobuf/cmexample2domain/requestinterface/readwriterequest.pb.h"
#include "protobuf/cmexample2domain/requestinterface/readwriteresponse.pb.h"

using namespace cmexample2;
using namespace cmexample2domain::requestinterface;

namespace
{
    void checkName(const std::string& name);
    void checkResponse(const ReadWriteResponse& response);
    void checkResponse(const ReadResponse& response, ReadResponse::ReadResponseCase expectedResponseType);
}

Town::Town():
        domainName("cmexample2domain"),
        requestDispatcher(configurationmanagement::api::RequestDispatcher::create())
{
}

void Town::addBuilding(const std::string& txid, const Building& building)
{
    ReadWriteRequest request;
    ReadWriteResponse response;

    request.mutable_addbuildingrequest()->set_name(building.name);
    request.mutable_addbuildingrequest()->set_opex(building.opex);
    request.mutable_addbuildingrequest()->set_citizen_limit(building.citizenLimit);
    requestDispatcher->readWriteRequest(txid, domainName, request).parse(response);
    checkResponse(response);
}

void Town::deleteBuilding(const std::string& txid, const std::string& name)
{
    ReadWriteRequest request;
    ReadWriteResponse response;

    request.mutable_deletebuildingrequest()->set_name(name);
    requestDispatcher->readWriteRequest(txid, domainName, request).parse(response);
    checkResponse(response);
}

void Town::addCitizen(const std::string& txid, const Citizen& citizen)
{
    ReadWriteRequest request;
    ReadWriteResponse response;

    checkName(citizen.name);
    request.mutable_addcitizenrequest()->set_name(citizen.name);
    request.mutable_addcitizenrequest()->set_tax(citizen.tax);
    request.mutable_addcitizenrequest()->set_building(citizen.building);
    requestDispatcher->readWriteRequest(txid, domainName, request).parse(response);
    checkResponse(response);
}

void Town::deleteCitizen(const std::string& txid, const std::string& name)
{
    ReadWriteRequest request;
    ReadWriteResponse response;

    request.mutable_deletecitizenrequest()->set_name(name);
    requestDispatcher->readWriteRequest(txid, domainName, request).parse(response);
    checkResponse(response);
}

Town::Summary Town::getSummary(const std::string& txid)
{
    Town::Summary summary;
    ReadRequest request;
    ReadResponse response;

    request.set_type(ReadRequest::READ_TOWN_SUMMARY);
    requestDispatcher->readOnlyRequest(txid, domainName, request).parse(response);
    checkResponse(response, ReadResponse::kTownSummary);

    summary.population = response.townsummary().population();
    summary.finance = response.townsummary().finance();

    return summary;
}

Town::Infrastructure Town::getInfrastructure(const std::string& txid)
{
    Infrastructure infrastructure;
    ReadRequest request;
    ReadResponse response;

    request.set_type(ReadRequest::READ_INFRASTRUCTURE);
    requestDispatcher->readOnlyRequest(txid, domainName, request).parse(response);
    checkResponse(response, ReadResponse::kInfrastructure);

    for (const auto& responseBuildingInfo : response.infrastructure().buildinginfo())
    {
        Infrastructure::BuildingInfo buildingInfo;
        buildingInfo.name = responseBuildingInfo.name();
        buildingInfo.opex = responseBuildingInfo.opex();
        buildingInfo.freeSpaces = responseBuildingInfo.freespaces();
        for (const auto& citizenName : responseBuildingInfo.citizen())
            buildingInfo.citizens.insert(citizenName);
        infrastructure.buildings.push_back(buildingInfo);
    }

    return infrastructure;
}

std::vector<Town::Citizen> Town::getCitizens(const std::string& txid)
{
    std::vector<Citizen> citizens;
    ReadRequest request;
    ReadResponse response;

    request.set_type(ReadRequest::READ_CITIZENS);
    requestDispatcher->readOnlyRequest(txid, domainName, request).parse(response);
    checkResponse(response, ReadResponse::kCitizens);

    for (const auto& responseCitizenInfo : response.citizens().citizeninfo())
    {
        Citizen citizen;
        citizen.name = responseCitizenInfo.name();
        citizen.tax = responseCitizenInfo.tax();
        citizen.building = responseCitizenInfo.building();
        citizens.push_back(citizen);
    }

    return citizens;
}

void Town::clearAll(const std::string& txid)
{
    ReadWriteRequest request;
    ReadWriteResponse response;

    request.mutable_clearallrequest();
    requestDispatcher->readWriteRequest(txid, domainName, request).parse(response);
    checkResponse(response);
}

namespace
{
    void checkName(const std::string& name)
    {
        for (const auto ch : name)
            if (!isalnum(ch) && ch != ' ' && ch != '-' && ch != '.')
                throw Town::InvalidCitizenName("Citizen name contains invalid characters.");
    }

    void checkResponse(const ReadWriteResponse& response)
    {
        switch (response.status())
        {
            case (ReadWriteResponse::SUCCESS):
                break;
            case (ReadWriteResponse::BUILDING_ALREADY_EXISTS):
                throw Town::BuildingAlreadyExists("Building already exists.");
            case (ReadWriteResponse::CITIZEN_ALREADY_EXISTS):
                throw Town::CitizenAlreadyExists("Citizen already exists.");
            case (ReadWriteResponse::UNKNOWN):
                throw Town::InternalError("Internal error: " + boost::lexical_cast<std::string>(response.status()));
        }
    }

    void checkResponse(const ReadResponse& response, ReadResponse::ReadResponseCase expectedResponseType)
    {
        if (response.readResponse_case() != expectedResponseType)
            throw Town::InternalError("Wrong response type: " + boost::lexical_cast<std::string>(response.readResponse_case()) +
                                      ", expected: " + boost::lexical_cast<std::string>(expectedResponseType));
    }
}
