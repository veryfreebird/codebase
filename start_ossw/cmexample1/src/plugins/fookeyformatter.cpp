#include "plugins/fookeyformatter.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>

using namespace cmexample1;

FooKeyFormatter::FooKeyFormatter():
        descriptionKeyPrefix("foo_description_"),
        valuesKeyPrefix("foo_values_")
{
}

FooKeyFormatter::~FooKeyFormatter()
{
}

std::string FooKeyFormatter::getFooDescriptionKey(const int fooId)
{
    return descriptionKeyPrefix + std::to_string(fooId);
}

std::string FooKeyFormatter::getFooValuesKey(const int fooId)
{
    return valuesKeyPrefix + std::to_string(fooId);
}

bool FooKeyFormatter::isFooDescriptionKey(const std::string& key)
{
    return boost::starts_with(key, descriptionKeyPrefix);
}

bool FooKeyFormatter::isFooValuesKey(const std::string& key)
{
    return boost::starts_with(key, valuesKeyPrefix);
}

std::string FooKeyFormatter::getFooDescriptionKeyPrefix()
{
    return descriptionKeyPrefix;
}

std::string FooKeyFormatter::getFooValuesKeyPrefix()
{
    return valuesKeyPrefix;
}

int FooKeyFormatter::parseFooId(const std::string& key)
{
    std::vector<std::string> sections;
    int fooId = -1;
    boost::split(sections,key,boost::is_any_of("_"));
    if (sections.size() > 0)
    {
        try
        {
            fooId = boost::lexical_cast<int>(sections[sections.size()-1]);
        }
        catch (const boost::bad_lexical_cast&)
        {
            throw FooKeyFormatter::IllegalKeyFormatException("Key format error, last section not integer: " + key);
        }
    }
    else
        throw FooKeyFormatter::IllegalKeyFormatException("Key format error, split separator not found: " + key);
    return fooId;
}
