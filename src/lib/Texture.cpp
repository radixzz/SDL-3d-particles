#include "Texture.h"
#include <SDL.h>
#include <map>

namespace Sax {

	std::map< std::string, SDL_Texture* > Texture::Cache;

	Texture::Texture():
		width(0),
		height(0),
		realWidth(0),
		realHeight(0),
		crop {0},
		path("")
	{}

	Texture::~Texture() {
	}

	void Texture::fromImage( std::string path ) {
		
	}

	void Texture::draw( SDL_Renderer* renderer ) {

	}
	
}