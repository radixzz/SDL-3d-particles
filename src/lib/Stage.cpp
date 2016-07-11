#include <SDL.h>
#include "Stage.h"
#include "Log.h"

Sax::Stage::Stage() {
	_texture = NULL;
}

Sax::Stage::~Stage() {
	SDL_DestroyTexture( _texture );
}

void Sax::Stage::update() {

}

int Sax::Stage::copyTo( SDL_Renderer* renderer, int width, int height, int format ) {
	if ( _texture == NULL ) {
		Log::info( "Creating texture" );
		_texture = SDL_CreateTexture(
			renderer, format,
			SDL_TEXTUREACCESS_TARGET,
			width, height );
		Uint8 r; Uint8 g; Uint8 b; Uint8 a;
		SDL_GetRenderDrawColor( renderer, &r, &g, &b, &a );
	}
	return SDL_RenderCopy( renderer, _texture, NULL, NULL );
}