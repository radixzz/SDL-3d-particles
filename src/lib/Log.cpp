#include "Log.h"
#include "Utils.h"

#include <ctime>
#include <chrono>
#include <sstream>

using namespace std;
using namespace std::chrono;

bool Sax::Log::debugMode = false;
bool Sax::Log::verboseMode = false;

std::string Sax::Log::getTime() {
    // http://stackoverflow.com/a/19555298
    milliseconds ms = duration_cast< milliseconds >( system_clock::now().time_since_epoch() );
    std::string msStr = to_string( ms.count() );
    return "T" + msStr.substr( msStr.size() - 6, 3 ) + "." + msStr.substr( msStr.size() - 3, 3 );
}

void Sax::Log::info( string msg ) {
    clog << "INFO:" << getTime() << " " << msg << endl;
}

void Sax::Log::warn( string msg ) {
    cout << "WARN:" << getTime() << " " << msg << endl;
}

void Sax::Log::error( string msg ) {
    cerr << "ERROR:" << getTime() << " " << msg << endl;
}
