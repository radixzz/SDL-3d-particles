#include "Texture.h"
#include <SDL.h>
#include <map>

#include "Log.h"
#include "Utils.h"
#include "Resources.h"
#include "Point.h"

namespace sax {

	Texture::Texture():
		width(0),
		height(0),
		realWidth(0),
		realHeight(0),
		crop(nullptr),
		path("")
	{}

	Texture::~Texture() {
		SDL_DestroyTexture( sdlTexture );
	}

	void Texture::fromImage( std::string path ) {
		TextureInfo* info = Resources::get_texture_info( path );
		this->path = path;
		realWidth = info->width;
		realHeight = info->height;
		width = info->width;
		height = info->height;
		textureCreated = false;

	}

	void Texture::draw( SDL_Renderer* renderer, SDL_Rect* destRect, double rotation, Point* anchor) {
		
		if ( textureCreated == false ) {
			sdlTexture = Resources::get_texture( renderer, path );
			textureCreated = true;
		}

		if ( sdlTexture != nullptr ) {
			SDL_Point _anchor = { anchor->x, anchor->y };
			SDL_RenderCopyEx( renderer, sdlTexture, crop, destRect, rotation, &_anchor, SDL_FLIP_NONE );
		}
	}

	int Texture::get_width() {
		return width;
	}

	int Texture::get_height() {
		return height;
	}
	
}