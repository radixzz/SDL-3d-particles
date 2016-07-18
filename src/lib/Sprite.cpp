//
#include "Sprite.h"
#include "Log.h"

namespace sax {
	Sprite::Sprite( Texture* texture ) {
		this->texture = texture;
	}

	Sprite::~Sprite() {
		//Log::info( "Destroying Sprite" );
		delete texture;
	}

	void Sprite::fromImage( std::string path ) {
		if ( texture == nullptr ) {
			texture = new Texture();
			texture->fromImage( path );
			width = texture->get_width();
			height = texture->get_height();
		} else {
			Log::info( "Delete old texture and load new one" );
		}
	}

	void Sprite::draw( RendererDescriptor* rendererDescriptor ) {
		//Do drawing logic here
		//Log::info( "Drawing Sprite" );
		if ( texture != nullptr ) {
			
			SDL_Rect destRect = { 
				int( position->x ),
				int( position->y ),
				width,
				height
			};

			texture->draw( rendererDescriptor->renderer, &destRect, rotation, anchor );
		}
		
		DisplayObject::draw( rendererDescriptor );
	}
}