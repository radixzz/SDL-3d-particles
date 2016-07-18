#include "Log.h"
#include "Utils.h"

#include <chrono>
#include <sstream>

namespace sax{

	bool Log::debugMode = false;
	bool Log::verboseMode = false;

	std::string Log::getTime() {
		// http://stackoverflow.com/a/19555298
		using namespace std::chrono;
		milliseconds ms = duration_cast<milliseconds>( system_clock::now().time_since_epoch() );
		std::string msStr = to_string( ms.count() );
		return "T" + msStr.substr( msStr.size() - 6, 3 ) + "." + msStr.substr( msStr.size() - 3, 3 );
	}

	void Log::info( std::string msg ) {
		std::clog << "INFO:" << getTime() << " " << msg << std::endl;
	}

	void Log::warn( std::string msg ) {
		std::cout << "WARN:" << getTime() << " " << msg << std::endl;
	}

	void Log::error( std::string msg ) {
		std::cerr << "ERROR:" << getTime() << " " << msg << std::endl;
	}

}