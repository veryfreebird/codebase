#ifndef CMEXAMPLE1_FOOCONFIGURATION_HPP_
#define CMEXAMPLE1_FOOCONFIGURATION_HPP_

#include <exception>
#include <string>
#include <map>
#include <memory>
#include <cm/api/requestdispatcher.hpp>
#include "foo.hpp"

namespace cmexample1
{

    class FooConfiguration
    {
    public:
        class FooIdMissingException;
        class FooNotFoundException;
        class InternalErrorException;

        typedef std::map<int,std::string> FooIdDescriptionPairs;

        FooConfiguration();
        FooConfiguration(const FooConfiguration&) = delete;
        FooConfiguration& operator = (const FooConfiguration&) = delete;
        
        void writeFoo(const std::string& txid, const Foo& foo);
        std::shared_ptr<Foo> readFoo(const std::string& txid, int fooId);
        std::shared_ptr<FooIdDescriptionPairs> readDescriptions(const std::string& txid);
        void deleteFoo(const std::string& txid, int fooId);

    private:
        std::string domainName;
        std::shared_ptr<configurationmanagement::api::RequestDispatcher> requestDispatcher;
    };

    class FooConfiguration::FooIdMissingException: public std::invalid_argument
    {
    public:
        FooIdMissingException() = delete;
        explicit FooIdMissingException(const std::string& msg): std::invalid_argument(msg) { }
    };

    class FooConfiguration::FooNotFoundException: public std::invalid_argument
    {
    public:
        FooNotFoundException() = delete;
        explicit FooNotFoundException(const std::string& msg): std::invalid_argument(msg) { }
    };

    class FooConfiguration::InternalErrorException: public std::runtime_error
    {
    public:
        InternalErrorException() = delete;
        explicit InternalErrorException(const std::string& msg): std::runtime_error(msg) { }
    };
}
#endif
