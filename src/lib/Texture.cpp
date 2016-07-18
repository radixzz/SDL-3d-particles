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
		SDL_Surface* surface = Resources::get_surface( path );
		this->path = path;
		if ( surface != nullptr ) {
			realWidth = surface->w;
			realHeight = surface->h;
			width = surface->w;
			height = surface->h;
			textureCreated = false;
		}
	}

	void Texture::draw( SDL_Renderer* renderer, SDL_Rect* destRect, double rotation, Point* anchor) {
		if ( textureCreated == false ) {
			SDL_Surface* surface = Resources::get_surface( path );
			sdlTexture = SDL_CreateTextureFromSurface( renderer, surface );
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