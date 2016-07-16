#include <SDL.h>
#include "Stage.h"
#include "Log.h"

namespace Sax
{

	Stage::Stage() {
		texture = NULL;
		viewport = {};
	}

	Stage::~Stage() {
		SDL_DestroyTexture( texture );
		setClearColor( 0, 0, 0, 255 );
	}

	void Stage::update() {

	}

	void Stage::setClearColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a ) {
		clearColor[ 0 ] = r;
		clearColor[ 1 ] = g;
		clearColor[ 2 ] = b;
		clearColor[ 3 ] = a;
	}

	void Stage::setViewport( SDL_Rect viewport ) {
		this->viewport = viewport;
	}

	void Stage::updateTexture( RendererDescriptor &descriptor ) {
		//SDL_RenderClear( renderer );
		if ( texture == NULL ) {
			Log::info( "Creating texture" );
			texture = SDL_CreateTexture(
				descriptor.renderer, descriptor.pixelFormat,
				SDL_TEXTUREACCESS_TARGET,
				descriptor.width, descriptor.height );
			SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
		}

		SDL_SetRenderTarget( descriptor.renderer, texture );

		SDL_SetRenderDrawColor(
			descriptor.renderer,
			clearColor[ 0 ],
			clearColor[ 1 ],
			clearColor[ 2 ],
			clearColor[ 3 ] );

		if ( viewport.w == 0 || viewport.h == 0 ){
			viewport.w = descriptor.width;
			viewport.h = descriptor.height;
		}

		SDL_RenderFillRect( descriptor.renderer, &viewport );
	}

	int Stage::copyTo( RendererDescriptor &descriptor ) {
		updateTexture( descriptor );
		
		//SDL_RenderFillRect( renderer, NULL );

		SDL_SetRenderTarget( descriptor.renderer, NULL );
		SDL_SetRenderDrawBlendMode( descriptor.renderer, SDL_BLENDMODE_BLEND );
		SDL_SetRenderDrawColor( descriptor.renderer, 128, 128, 128, 255 );

		SDL_RenderCopy( descriptor.renderer, texture, NULL, NULL );
		return 0;
	}

	void Stage::addChild( DisplayObject* displayObject ) {
	}
}