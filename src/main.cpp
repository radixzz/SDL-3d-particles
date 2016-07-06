#include <SDL.h>
#include <stdio.h>
#include "Log.h"
#include <string>
#include <Utils.h>
#include <iostream>

int main( int argc, char* args[] ){
    Log::debugMode = true;
    for (int i = 0; i < 1000; i++){
        SDL_Delay(100);
        Log::info( "Initializing" + xtd::to_string(i));
    }

    return 0;
}
