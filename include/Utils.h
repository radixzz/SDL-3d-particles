#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

// http://stackoverflow.com/a/20861692
namespace xtd
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
}

#endif // UTILS_H
