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
		sdlTexture(nullptr),
		path("")
	{}

	Texture::~Texture() {
		clear();
	}

	void Texture::clear() {
		if ( sdlTexture != nullptr ) {
			SDL_DestroyTexture( sdlTexture );
		}
	}

	void Texture::fromImage( std::string path ) {
		clear();
		TextureInfo* info = Resources::get_texture_info( path );
		this->path = path;
		realWidth = info->width;
		realHeight = info->height;
		width = info->width;
		height = info->height;
	}

	void Texture::fromSurface( SDL_Renderer* renderer, SDL_Surface* surface ) {
		clear();
		sdlTexture = SDL_CreateTextureFromSurface( renderer, surface );
		realWidth = surface->w;
		realHeight = surface->h;
		width = surface->w;
		height = surface->h;
	}

	void Texture::draw( SDL_Renderer* renderer, SDL_Rect* destRect, double rotation, Point* anchor) {
		
		if ( sdlTexture == nullptr && ! path.empty() ) {
			sdlTexture = Resources::get_texture( renderer, path );
		}

		if ( sdlTexture != nullptr ) {
			SDL_Point _anchor = { (int)anchor->x, (int)anchor->y };
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