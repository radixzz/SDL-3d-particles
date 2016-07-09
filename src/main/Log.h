#ifndef LOG_H
#define LOG_H

#include <iostream>

class Log
{
    public:
        static void info( std::string msg );
        static void warn( std::string msg );
        static void error( std::string msg );
    private:
        static std::string getTime();
    public:
        static bool debugMode;
        static bool verboseMode;
};

#endif // LOG_H
