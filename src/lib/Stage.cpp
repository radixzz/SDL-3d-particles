#include <SDL.h>
#include "Stage.h"
#include "Log.h"

Sax::Stage::Stage() {
	_texture = NULL;
}

Sax::Stage::~Stage() {
	SDL_DestroyTexture( _texture );
	setClearColor( 0, 0, 0, 255 );
}

void Sax::Stage::update() {

}

void Sax::Stage::setClearColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a ) {
	_clearColor[ 0 ] = r;
	_clearColor[ 1 ] = g;
	_clearColor[ 2 ] = b;
	_clearColor[ 3 ] = a;
}

int Sax::Stage::copyTo( SDL_Renderer* renderer, int width, int height, int format ) {
	if ( _texture == NULL ) {
		Log::info( "Creating texture" );
		_texture = SDL_CreateTexture(
			renderer, format,
			SDL_TEXTUREACCESS_TARGET,
			width, height );
		
	}

	SDL_SetRenderTarget( renderer, _texture );
	SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_NONE );
	
	SDL_SetRenderDrawColor(
		renderer,
		_clearColor[ 0 ],
		_clearColor[ 1 ],
		_clearColor[ 2 ],
		_clearColor[ 3 ] );
	//SDL_RenderClear( renderer );
	
	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
	
	SDL_Rect rectangle;
	
	rectangle.x = 0;
	rectangle.y = 0;
	rectangle.w = 150;
	rectangle.h = 150;
	SDL_RenderFillRect( renderer, &rectangle );
	
	//SDL_RenderFillRect( renderer, NULL );

	SDL_SetRenderTarget( renderer, NULL );
	SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );
	SDL_SetRenderDrawColor( renderer, 128, 128, 128, 255 );

	SDL_RenderCopy( renderer, _texture, NULL, NULL );
	return 0;
	
}