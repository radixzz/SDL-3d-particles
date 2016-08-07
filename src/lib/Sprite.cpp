#include "Sprite.h"
#include "Log.h"

namespace sax {
	
	Sprite::Sprite() {
		this->texture = std::make_unique<Texture>();
	}

	
	Sprite::Sprite( std::unique_ptr<Texture> texture ) {
		this->texture = std::move( texture );
	}

	Sprite::~Sprite() {
		//Log::info( "Destroying Sprite" );
	}

	void Sprite::fromImage( std::string path ) {
		texture->fromImage( path );
		width = texture->get_width();
		height = texture->get_height();
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

			texture->draw( rendererDescriptor->renderer, &destRect, rotation, anchor.get() );
		}
		
		DisplayObject::draw( rendererDescriptor );
	}
}