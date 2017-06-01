#ifndef CMEXAMPLE1_FOO_HPP_
#define CMEXAMPLE1_FOO_HPP_

#include <string>
#include <set>

namespace cmexample1
{
    struct Foo
    {
    public:
        int id;
        std::string description;
        std::set<std::string> values;
    };
}
#endif
