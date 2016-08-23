#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <map>

#include "Log.h"
#include "Utils.h"
#include "Resources.h"

namespace sax {

	Texture::Texture():
		width(0),
		height(0),
		naturalWidth(0),
		naturalHeight(0),
		textureId(0),
		path("")
	{
		glGenTextures( 1, &textureId );
	}

	Texture::~Texture() {
		clear();
	}

	int Texture::getNearestPowerOf2( int num ) {
		num--;
		num |= num >> 1;
		num |= num >> 2;
		num |= num >> 4;
		num |= num >> 8;
		num |= num >> 16;
		return num++;
	}

	void Texture::clear() {
		if ( textureId > 0 ) {
			glDeleteTextures( 1, &textureId );
			textureId = 0;
		}
	}

	SDL_Surface* Texture::resizeSurface( SDL_Surface* surface, const int& width, const int& height ) {
		if ( surface != nullptr && surface->w != width || surface->h != height ) {
			
			SDL_Surface* newSurface = nullptr;

			int bpp;
			Uint32 Rmask, Gmask, Bmask, Amask;

			SDL_PixelFormatEnumToMasks( SDL_PIXELFORMAT_ABGR8888, &bpp, &Rmask, &Gmask, &Bmask, &Amask );
			newSurface = SDL_CreateRGBSurface( 0, width, height, bpp, Rmask, Gmask, Bmask, Amask );
			SDL_Rect area = { 0, 0, surface->w, surface->h }; // x, y, w, h
			SDL_SetSurfaceAlphaMod( surface, 0xFF );
			SDL_SetSurfaceBlendMode( surface, SDL_BLENDMODE_NONE );
			SDL_BlitSurface( surface, &area, newSurface, &area );

			return newSurface;
		} else {
			return surface;
		}
	}

	void Texture::fromImage( std::string path ) {
		clear();
		if ( !path.empty() ) {
			this->path = path;
			SDL_Surface* surface = IMG_Load( path.c_str() );
			SDL_Surface* pow2Surface = nullptr;
			const char* error = nullptr;
			
			if ( surface == nullptr ) {
				error = IMG_GetError();
			} else {
				
				naturalWidth = surface->w;
				naturalHeight = surface->h;
				
				width = getNearestPowerOf2( naturalWidth );
				height = getNearestPowerOf2( naturalHeight );

				pow2Surface = resizeSurface( surface, width, height );

				glGenTextures( 1, &textureId );
				glBindTexture( GL_TEXTURE_2D, textureId );
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, pow2Surface->w, pow2Surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pow2Surface->pixels );
				// TODO: Add Wrapping modes
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
				//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				
				Log::info( "Texture loaded: " + path );
				
			}
			
			SDL_FreeSurface( surface );
			SDL_FreeSurface( pow2Surface );

			if ( error != nullptr ) {
				Log::error( "Cannot load texture: " + path + " Error: " + to_string( error ) );
			}
		}
	}

	void Texture::fromSurface( SDL_Surface* surface ) {
		naturalWidth = surface->w;
		naturalHeight = surface->h;
		width = surface->w;
		height = surface->h;
	}

	void Texture::bind() {
		if ( textureId > 0 ) {
			glActiveTexture( GL_TEXTURE0 );
			glBindTexture( GL_TEXTURE_2D, textureId );
		}
	}

	void Texture::unbind() {
		if ( textureId > 0 ) {
			glBindTexture( GL_TEXTURE_2D, 0 );
		}
	}

	int Texture::get_width() {
		return width;
	}

	int Texture::get_height() {
		return height;
	}
	
}