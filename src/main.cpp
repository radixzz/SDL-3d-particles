#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>

// Memory Leak Analyzer
#if defined( _WIN32 )
#include "vld.h"
#endif

#include "lib/Log.h"
#include "lib/Application.h"
#include "lib/Stage.h"
#include "lib/Sprite.h"
#include "lib/Utils.h"

#include "lib/Timer.h"

using namespace Sax;
int main( int argc, char* args[] ){
    
	Log::debugMode = true;
	Log::info( "Initializing" );
	Application* app = new Application( 800, 600 );
	Stage* stage = new Stage();
	stage->setViewport( { 0, 0, 100, 100 } );
	stage->setClearColor( 255, 255, 255, 255 );
	app->addStage( stage );
	
	Sprite* sprite = new Sprite();

	while ( app->running() ) {
		app->processEvents();
		app->render();
		Log::info( to_string( app->getFPS() ) );
	}
	
	delete app;
	delete sprite;
	
    return EXIT_SUCCESS;
}
