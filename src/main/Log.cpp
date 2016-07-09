#include "Log.h"
#include "Utils.h"

#include <ctime>
#include <chrono>
#include <sstream>

using namespace std;
using namespace std::chrono;

bool Log::debugMode = false;
bool Log::verboseMode = false;

std::string Log::getTime() {
    // http://stackoverflow.com/a/19555298
    milliseconds ms = duration_cast< milliseconds >( system_clock::now().time_since_epoch() );
    std::string msStr = xtd::to_string( ms.count() );
    return "T" + msStr.substr( msStr.size() - 6, 3 ) + "." + msStr.substr( msStr.size() - 3, 3 );
}

void Log::info( string msg ) {
    clog << "INFO:" << getTime() << " " << msg << endl;
}

void Log::warn( string msg ) {
    cout << "WARN:" << getTime() << " " << msg << endl;
}

void Log::error( string msg ) {
    cerr << "ERROR:" << getTime() << " " << msg << endl;
}
