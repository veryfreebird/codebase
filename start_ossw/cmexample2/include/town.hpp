#ifndef CMEXAMPLE2_TOWN_HPP_
#define CMEXAMPLE2_TOWN_HPP_

#include <stdexcept>
#include <set>
#include <vector>
#include <cm/api/requestdispatcher.hpp>

namespace cmexample2
{
    class Town
    {
    public:
        struct Building;
        struct Citizen;
        struct Summary;
        struct Infrastructure;
        class BuildingAlreadyExists;
        class InvalidCitizenName;
        class CitizenAlreadyExists;
        class InternalError;

        Town();
        Town(const Town&) = delete;
        Town& operator = (const Town&) = delete;
        
        void addBuilding(const std::string& txid, const Building& building);

        void deleteBuilding(const std::string& txid, const std::string& name);

        void addCitizen(const std::string& txid, const Citizen& citizen);

        void deleteCitizen(const std::string& txid, const std::string& name);

        Summary getSummary(const std::string& txid);

        Infrastructure getInfrastructure(const std::string& txid);

        std::vector<Citizen> getCitizens(const std::string& txid);

        void clearAll(const std::string& txid);

    private:
        std::string domainName;
        std::shared_ptr<configurationmanagement::api::RequestDispatcher> requestDispatcher;
    };

    struct Town::Building
    {
        std::string name;
        unsigned int opex;
        unsigned int citizenLimit;
    };

    struct Town::Citizen
    {
        std::string name;
        unsigned int tax;
        std::string building;
    };

    struct Town::Summary
    {
        unsigned int population;
        unsigned int finance;
    };

    struct Town::Infrastructure
    {
        struct BuildingInfo
        {
            std::string name;
            unsigned int opex;
            unsigned int freeSpaces;
            std::set<std::string> citizens;
        };
        std::vector<BuildingInfo> buildings;
    };

    class Town::BuildingAlreadyExists: public std::invalid_argument
    {
    public:
        BuildingAlreadyExists() = delete;
        explicit BuildingAlreadyExists(const std::string& msg): std::invalid_argument(msg) { }
    };

    class Town::InvalidCitizenName: public std::invalid_argument
    {
    public:
        InvalidCitizenName() = delete;
        explicit InvalidCitizenName(const std::string& msg): std::invalid_argument(msg) { }
    };

    class Town::CitizenAlreadyExists: public std::invalid_argument
    {
    public:
        CitizenAlreadyExists() = delete;
        explicit CitizenAlreadyExists(const std::string& msg): std::invalid_argument(msg) { }
    };

    class Town::InternalError: public std::runtime_error
    {
    public:
        InternalError() = delete;
        explicit InternalError(const std::string& msg): std::runtime_error(msg) { }
    };
}

#endif
