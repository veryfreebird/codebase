#include <cm/plugin/validatorplugin.hpp>
#include <cm/reader.hpp>
#include "plugins/common/citizens.hpp"
#include "plugins/common/buildings.hpp"

using configurationmanagement::plugin::ValidatorPlugin;
using configurationmanagement::Reader;

namespace cmexample2
{
    class TownValidatorPlugin: public ValidatorPlugin
    {
    public:
        TownValidatorPlugin();
        ~TownValidatorPlugin();

        Result validateDelta(Reader& reader,
                             const Map& valuesToBeWrittenToDB,
                             const Keys& keysToBeRemovedFromDB) override;

        Result validateFull(Reader& reader) override;

    private:
        Citizens citizens;
        Buildings buildings;
    };
}
