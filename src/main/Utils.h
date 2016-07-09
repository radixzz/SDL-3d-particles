#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

// http://stackoverflow.com/a/20861692
namespace xtd
{
template < typename T > std::string to_string( const T& n );
// Fix compilation time error http://stackoverflow.com/a/3040706
#include "Utils.cpp"
}

#endif // UTILS_H
