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
		textureId(0),
		path("")
	{}

	Texture::~Texture() {
		clear();
	}

	void Texture::clear() {
		
	}

	void Texture::fromImage( std::string path ) {
		clear();
		if ( !path.empty() ) {
			/*
			SDL_Surface* surface = IMG_Load( path.c_str() );
			const char* error = nullptr;
			if ( surface == nullptr ) {
				error = IMG_GetError();
				return nullptr;
			} else {
				TextureCacheEntry* entry = new TextureCacheEntry();
				entry->width = surface->w;
				entry->height = surface->h;
				glGenTextures( 1, &entry->textureId );
				glBindTexture( GL_TEXTURE_2D, entry->textureId );
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels );
				// TODO: Add Wrapping modes
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
				//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				TextureCache.insert( std::make_pair( path, std::unique_ptr< TextureCacheEntry >( entry ) ) );
				Log::info( "Texture loaded: " + path );
				return entry;
			}
			SDL_FreeSurface( surface );

			if ( error != nullptr ) {
				Log::error( "Cannot load texture: " + path + " Error: " + to_string( error ) );
			}
			*/
			this->path = path;
			//realWidth = texture->width;
			//realHeight = texture->height;
			//width = texture->width;
			//height = texture->height;
		}
	}

	void Texture::fromSurface( SDL_Surface* surface ) {
		realWidth = surface->w;
		realHeight = surface->h;
		width = surface->w;
		height = surface->h;
	}

	void Texture::bind() {
	
	}

	void Texture::unbind() {
	
	}

	int Texture::get_width() {
		return width;
	}

	int Texture::get_height() {
		return height;
	}
	
}