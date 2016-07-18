#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>

// Memory Leak Analyzer
#if defined( _WIN32 )
#include "vld.h"
#endif
#include "lib/Sax.h"
#include "lib/Log.h"
#include "lib/Application.h"
#include "lib/Stage.h"
#include "lib/Sprite.h"
#include "lib/DisplayObject.h"
#include "lib/Utils.h"
#include "lib/Timer.h"

using namespace sax;

Application* app = nullptr;
Stage* stage = nullptr;

std::vector<Sprite*> vsprites;

void update( double dt ) {
	//Log::info( to_string( dt ) );
	auto it = vsprites.begin();
	for ( ; it != vsprites.end(); it++ ) {
		( *it )->position->x += 1;
		if ( ( *it )->position->x > 1000 ) {
			( *it )->position->x = 0;
		}
	}
}

int getRand( int min, int max ) {
	return min + ( rand() % (int)( max - min + 1 ) );
}

int main( int argc, char* args[] ){
	
	app = new Application( 800, 600, update );
	stage = new Stage();
	stage->setViewport( { 0, 0, 100, 100 } );
	app->addStage( stage );
	
	for ( int i = 0; i < 1000; i++ ) {
		Sprite* s = new Sprite();
		s->position->x = getRand( 0, 800 );
		s->position->y = getRand( 0, 600 );
		s->fromImage( "res/piece_vibrance.png" );
		vsprites.push_back( s );
		stage->addChild( s );
	}
	
	app->run();
	
	auto it = vsprites.begin();
	while( it != vsprites.end() ) {
		delete ( *it );
		it = vsprites.erase( it );
	}

	delete app;
	delete stage;

    return EXIT_SUCCESS;
}
