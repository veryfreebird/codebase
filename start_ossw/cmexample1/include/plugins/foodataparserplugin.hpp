#include <cm/plugin/dataparserplugin.hpp>
#include <cm/reader.hpp>
#include "fookeyformatter.hpp"

using configurationmanagement::plugin::DataParserPlugin;
using configurationmanagement::Data;

namespace cmexample1
{
    class FooDataParserPlugin: public DataParserPlugin
    {
    public:
        FooDataParserPlugin();
        ~FooDataParserPlugin();

        std::shared_ptr<const google::protobuf::Message> parse(const std::string& key,
                                                               const Data& data) override;
    private:
        FooKeyFormatter keyFormatter;
    };
}
