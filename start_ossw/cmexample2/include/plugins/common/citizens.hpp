#ifndef CMEXAMPLE2_PLUGINS_COMMON_CITIZENS_HPP_
#define CMEXAMPLE2_PLUGINS_COMMON_CITIZENS_HPP_

#include <string>
#include <map>
#include <cm/reader.hpp>
#include <cm/readerwriter.hpp>
#include "plugins/common/keyparser.hpp"
#include "protobuf/cmexample2domain/databasevalues/value.pb.h"

using configurationmanagement::Reader;
using configurationmanagement::ReaderWriter;
using cmexample2domain::databasevalues::Value;
using cmexample2domain::databasevalues::Citizen;

namespace cmexample2
{
    class Citizens
    {
    public:
        Citizens();
        Citizens(const Citizens&) = delete;
        Citizens& operator = (const Citizens&) = delete;
        ~Citizens();

        typedef std::string Name;

        bool exists(Reader& reader, const Name& name) const;

        // Returns empty Citizen if citizen with given name does not exist (empty = message filled with default values).
        Citizen read(Reader& reader, const Name& name) const;

        std::map<Name,Citizen> readAll(Reader& reader) const;

        unsigned int countInBuilding(Reader& reader, const std::string& buildingName) const;

        unsigned int totalTax(Reader& reader) const;

        void write(ReaderWriter& readerWriter, const Name& name, const Citizen& citizen) const;

        void remove(ReaderWriter& readerWriter, const Name& name) const;

    private:
        KeyParser keyParser;
    };
}

#endif
