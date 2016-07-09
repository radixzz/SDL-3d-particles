#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "main/Log.h"
#include "main/Utils.h"


int main( int argc, char* args[] ){
    Log::debugMode = true;
    for (int i = 0; i < 100; i++){
        Log::info( "Initializing" + xtd::to_string(i) );
    }
    return 0;
}
