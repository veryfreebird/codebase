#ifndef CMEXAMPLE2_PLUGINS_COMMON_KEYPARSER_HPP_
#define CMEXAMPLE2_PLUGINS_COMMON_KEYPARSER_HPP_

#include <stdexcept>
#include <string>

namespace cmexample2
{
    class KeyParser
    {
    public:
        class IllegalKeyFormatException;

        KeyParser();
        KeyParser(const KeyParser&) = delete;
        KeyParser& operator = (const KeyParser&) = delete;
        ~KeyParser();

        std::string getInfrastructureKey() const;

        std::string getCitizenKey(const std::string& name) const;

        std::string getCitizenKeyPrefix() const;

        std::string parseCitizenName(const std::string& key) const;

    private:
        std::string infrastructureKey;
        std::string citizenKeyPrefix;
    };

    class KeyParser::IllegalKeyFormatException: public std::runtime_error
    {
    public:
        IllegalKeyFormatException() = delete;
        explicit IllegalKeyFormatException(const std::string& msg): std::runtime_error(msg) { }
        virtual ~IllegalKeyFormatException() noexcept { }
    };
}

#endif
