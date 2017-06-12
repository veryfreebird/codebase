#ifndef CMEXAMPLE2_PLUGINS_COMMON_BUILDINGS_HPP_
#define CMEXAMPLE2_PLUGINS_COMMON_BUILDINGS_HPP_

#include <string>
#include <vector>
#include <cm/reader.hpp>
#include <cm/readerwriter.hpp>
#include "plugins/common/keyparser.hpp"
#include "protobuf/cmexample2domain/databasevalues/value.pb.h"

using configurationmanagement::Reader;
using configurationmanagement::ReaderWriter;
using cmexample2domain::databasevalues::Value;
using cmexample2domain::databasevalues::Infrastructure;
using cmexample2domain::databasevalues::Building;

namespace cmexample2
{
    class Buildings
    {
    public:
        Buildings();
        Buildings(const Buildings&) = delete;
        Buildings& operator = (const Buildings&) = delete;
        ~Buildings();

        bool exists(Reader& reader, const std::string& name) const;

        // Returns empty Building if building with given name does not exist (empty = message filled with default values).
        Building read(Reader& reader, const std::string& name) const;

        std::vector<Building> readAll(Reader& reader) const;

        unsigned int totalOpex(Reader& reader) const;

        void write(ReaderWriter& readerWriter, const Building& citizen) const;

        void remove(ReaderWriter& readerWriter, const std::string& name) const;

    private:
        KeyParser keyParser;
    };
}

#endif
