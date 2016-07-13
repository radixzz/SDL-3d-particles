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
#include "lib/Window.h"
#include "lib/Stage.h"
#include "lib/Sprite.h"
#include "lib/Utils.h"

using namespace Sax;
int main( int argc, char* args[] ){
    
	Log::debugMode = true;
	Log::info( "Initializing" );
	Application* app = new Application();
	Window* window = new Window( 800, 600 );
	app->addWindow( window );
	Stage* stage = new Stage();
	stage->setViewport( { 0, 0, 100, 100 } );
	stage->setClearColor( 255, 255, 255, 255 );
	window->addStage( stage );
	
	Sprite* sprite = new Sprite();
	
	while ( app->running() ) {
		app->processEvents();
		app->render();
	}
	
	delete app;
	delete sprite;
	
    return EXIT_SUCCESS;
}
