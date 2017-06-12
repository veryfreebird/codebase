#include <cm/plugin/dataparserplugin.hpp>
#include <cm/reader.hpp>

using configurationmanagement::plugin::DataParserPlugin;
using configurationmanagement::Data;

namespace cmexample2
{
    class TownDataParserPlugin: public DataParserPlugin
    {
    public:
        TownDataParserPlugin();
        ~TownDataParserPlugin();

        std::shared_ptr<const google::protobuf::Message> parse(const std::string& key,
                                                               const Data& data) override;
    };
}
