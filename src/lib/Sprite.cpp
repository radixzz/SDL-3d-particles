#include "Sprite.h"
#include "Log.h"
#include "Resources.h"

namespace sax {
	
	Sprite::Sprite() {}

	Sprite::~Sprite() {
		//Log::info( "Destroying Sprite" );
	}

	void Sprite::fromImage( std::string path ) {
		this->path = path;
		Texture* texture = Resources::get_texture( path );
		width = texture->get_width();
		height = texture->get_height();
	}

	void Sprite::draw( const RendererDescriptor* rendererDescriptor ) {
		
		DisplayObject::draw( rendererDescriptor );
	}
}