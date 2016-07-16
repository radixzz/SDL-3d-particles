//
#include "Sprite.h"
#include "Log.h"

namespace Sax {
	Sprite::Sprite( Texture* texture ) {
		this->texture = texture;
	}

	Sprite::~Sprite() {
		Log::info( "Destroying Sprite" );
	}

	void Sprite::fromImage( std::string path ) {

	}
}