#include <stdexcept>
#include <string>

namespace cmexample1
{
    class FooKeyFormatter
    {
    public:
        class IllegalKeyFormatException;

        FooKeyFormatter();
        ~FooKeyFormatter();

        std::string getFooDescriptionKey(const int fooId);
        std::string getFooValuesKey(const int fooId);
        bool isFooDescriptionKey(const std::string& key);
        bool isFooValuesKey(const std::string& key);
        std::string getFooDescriptionKeyPrefix();
        std::string getFooValuesKeyPrefix();
        int parseFooId(const std::string& key);

    private:
        std::string descriptionKeyPrefix;
        std::string valuesKeyPrefix;
    };

    class FooKeyFormatter::IllegalKeyFormatException: public std::runtime_error
    {
    public:
        IllegalKeyFormatException() = delete;
        explicit IllegalKeyFormatException(const std::string& msg): std::runtime_error(msg) { }
        virtual ~IllegalKeyFormatException() noexcept { }
    };
}
