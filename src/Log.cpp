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
    time_t t = time( 0 );
    struct tm* now = localtime( &t );
    milliseconds ms = duration_cast<milliseconds>( system_clock::now().time_since_epoch() );
    std::string msStr = xtd::to_string( ms.count() );
    return "[" + msStr.substr( msStr.size() - 6, 3 ) + ":" + msStr.substr( msStr.size() - 3, 3 ) + "]";
}

void Log::info( string msg ) {
    clog << getTime() << "[Info]: " << msg << endl;
}

void Log::warn( string msg ) {
    cout << getTime() << "[Warn]: " << msg << endl;
}

void Log::error( string msg ) {
    cerr << getTime() << "[Error]: " << msg << endl;
}
