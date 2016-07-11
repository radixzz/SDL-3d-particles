#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "vld.h"
#include "lib\Log.h"
#include "lib\Application.h"
#include "lib\Window.h"
#include "lib\Stage.h"
#include "lib\Sprite.h"

using namespace Sax;
int main( int argc, char* args[] ){
    
	Log::debugMode = true;
	Log::info( "Initializing" );
	Application* app = new Application();
	Window* window = new Window( 800, 600 );
	window->setClearColor( 255, 255, 255, 255 );
	app->addWindow( window );
	Stage* stage = new Stage();
	window->addStage( stage );
	/*
	Window* window2 = new Window( 200, 200 );
	app->addWindow( window2 );
	window2->setClearColor( 0xFF, 0xFF, 0xFF, 0xFF );
	Stage* stage2 = new Stage();
	window2->addStage( stage2 );
	*/

	Sprite* sprite = new Sprite();
	
	while ( app->running() ) {
		app->processEvents();
		app->render();
	}
	
	delete app;
	delete sprite;
	
    return EXIT_SUCCESS;
}
