#include <SDL.h>
#include "Stage.h"
#include "Log.h"

namespace Sax
{

	Stage::Stage() {
		_texture = NULL;
		_viewport = {};
	}

	Stage::~Stage() {
		SDL_DestroyTexture( _texture );
		setClearColor( 0, 0, 0, 255 );
	}

	void Stage::update() {

	}

	void Stage::setClearColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a ) {
		_clearColor[ 0 ] = r;
		_clearColor[ 1 ] = g;
		_clearColor[ 2 ] = b;
		_clearColor[ 3 ] = a;
	}

	void Stage::setViewport( SDL_Rect viewport ) {
		_viewport = viewport;
	}

	void Stage::updateTexture( RendererDescriptor &descriptor ) {
		//SDL_RenderClear( renderer );
		if ( _texture == NULL ) {
			Log::info( "Creating texture" );
			_texture = SDL_CreateTexture(
				descriptor.renderer, descriptor.pixelFormat,
				SDL_TEXTUREACCESS_TARGET,
				descriptor.width, descriptor.height );
			SDL_SetTextureBlendMode( _texture, SDL_BLENDMODE_BLEND );
		}

		SDL_SetRenderTarget( descriptor.renderer, _texture );

		SDL_SetRenderDrawColor(
			descriptor.renderer,
			_clearColor[ 0 ],
			_clearColor[ 1 ],
			_clearColor[ 2 ],
			_clearColor[ 3 ] );

		if ( _viewport.w == 0 || _viewport.h == 0 ){
			_viewport.w = descriptor.width;
			_viewport.h = descriptor.height;
		}

		SDL_RenderFillRect( descriptor.renderer, &_viewport );
	}

	int Stage::copyTo( RendererDescriptor &descriptor ) {
		updateTexture( descriptor );
		
		//SDL_RenderFillRect( renderer, NULL );

		SDL_SetRenderTarget( descriptor.renderer, NULL );
		SDL_SetRenderDrawBlendMode( descriptor.renderer, SDL_BLENDMODE_BLEND );
		SDL_SetRenderDrawColor( descriptor.renderer, 128, 128, 128, 255 );

		SDL_RenderCopy( descriptor.renderer, _texture, NULL, NULL );
		return 0;

	}
}