#include <cm/plugin/validatorplugin.hpp>
#include <cm/reader.hpp>
#include "fookeyformatter.hpp"
#include <set>
#include <string>

using configurationmanagement::plugin::ValidatorPlugin;
using configurationmanagement::Reader;

namespace cmexample1
{
    class FooValidatorPlugin: public ValidatorPlugin
    {
    public:
        FooValidatorPlugin();
        ~FooValidatorPlugin();

        Result validateDelta(Reader& reader,
                             const Map& valuesToBeWrittenToDB,
                             const Keys& keysToBeRemovedFromDB) override;

        Result validateFull(Reader& reader) override;

    private:
        FooKeyFormatter keyFormatter;
        bool checkFooDescriptionsUniqueness(Reader& reader);
    };
}
