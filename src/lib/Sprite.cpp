#include "Sprite.h"
#include "Log.h"
#include "Resources.h"

namespace sax {
	
	Sprite::Sprite(): texture(nullptr) {}

	Sprite::~Sprite() {
		//Log::info( "Destroying Sprite" );
		shader = Resources::get_shader( "sprite" );
	}

	void Sprite::fromImage( const std::string& path ) {
		this->path = path;
		this->texture = Resources::get_texture( path );
		width = texture->get_width();
		height = texture->get_height();
	}

	void Sprite::onTextureDraw( std::function<void( Texture* tex )> drawCallback ) {
		drawCallback( this->texture );
	}
}