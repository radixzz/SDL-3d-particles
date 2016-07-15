#include "Texture.h"
#include <SDL.h>
#include <map>

namespace Sax {

	std::map< std::string, SDL_Texture* > Texture::Cache;

	Texture::Texture() {

	}

	Texture::~Texture() {

	}

	void Texture::fromImage( std::string path ) {
		
	}

	void Texture::draw( SDL_Renderer* renderer ) {

	}
	
}