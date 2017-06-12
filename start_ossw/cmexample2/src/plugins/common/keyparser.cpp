#include "plugins/common/keyparser.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>

using namespace cmexample2;

KeyParser::KeyParser():
        infrastructureKey("infrastructure"),
        citizenKeyPrefix("citizen_")
{
}

KeyParser::~KeyParser()
{
}

std::string KeyParser::getInfrastructureKey() const
{
    return infrastructureKey;
}

std::string KeyParser::getCitizenKey(const std::string& name) const
{
    return boost::replace_all_copy(citizenKeyPrefix + name, " ", "_");
}

std::string KeyParser::getCitizenKeyPrefix() const
{
    return citizenKeyPrefix;
}

std::string KeyParser::parseCitizenName(const std::string& key) const
{
    if (boost::starts_with(key, citizenKeyPrefix))
        return boost::replace_all_copy(key.substr(citizenKeyPrefix.size()), "_", " ");
    else
        throw KeyParser::IllegalKeyFormatException("Citizen key format error, not identified as a citizen key: " + key);
}
