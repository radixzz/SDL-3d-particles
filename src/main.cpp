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

std::vector< std::unique_ptr<Sprite> > vsprites;

void update( double dt, double time ) {
	auto it = vsprites.begin();
	for ( ; it != vsprites.end(); it++ ) {
		( *it )->position->x += dt * 0.1;
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
	app->showFps = true;
	stage = new Stage();
	stage->setViewport( { 0, 0, 100, 100 } );
	app->addStage( stage );
	
	for ( int i = 0; i < 100; i++ ) {
		std::unique_ptr<Sprite> s = std::make_unique<Sprite>();
		s->position->x = getRand( 0, 800 );
		s->position->y = getRand( 0, 600 );
		s->fromImage( "res/piece_vibrance.png" );
		stage->addChild( s.get() );
		vsprites.push_back( std::move( s ) );
	}
	
	app->run();
	
	auto it = vsprites.begin();
	vsprites.clear();
	delete app;
	delete stage;

    return EXIT_SUCCESS;
}
