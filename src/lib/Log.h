#ifndef SAX_LOG_H
#define SAX_LOG_H

#include <iostream>
namespace sax {
	class Log
	{
		public:
			static void info(std::string msg);
			static void warn(std::string msg);
			static void error(std::string msg);
		private:
			static std::string getTime();
		public:
			static bool debugMode;
			static bool verboseMode;
	};
}

#endif // SAX_LOG_H
