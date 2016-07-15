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
#include "lib/Texture.h"
#include "lib/Timer.h"

using namespace Sax;

Application* app = NULL;
Stage* stage = NULL;


void update( int dt ) {
	//Log::info( to_string( dt ) );
}

int main( int argc, char* args[] ){
    
	Log::debugMode = true;
	Log::info( "Initializing" );
	app = new Application( 800, 600, update );
	stage = new Stage();
	stage->setViewport( { 0, 0, 100, 100 } );
	stage->setClearColor( 255, 255, 255, 255 );
	app->addStage( stage );
	
	Texture tex = Texture();
	tex.fromImage( "dude.png" );
	//stage->addChild( tex );
	app->run();
	delete app;
	
    return EXIT_SUCCESS;
}
