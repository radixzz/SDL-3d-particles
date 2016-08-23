#include "Sprite.h"
#include "Log.h"
#include "Resources.h"

namespace sax {
	
	Sprite::Sprite() {}

	Sprite::~Sprite() {
		//Log::info( "Destroying Sprite" );
		shader = Resources::get_shader( "sprite" );
	}

	void Sprite::fromImage( std::string path ) {
		this->path = path;
		Texture* texture = Resources::get_texture( path );
		width = texture->get_width();
		height = texture->get_height();
	}

	void Sprite::draw( Renderer* renderer ) {
		//renderer->render( this );
		DisplayObject::draw( renderer );
	}
}