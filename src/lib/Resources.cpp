#include <SDL.h>
#include <SDL_image.h>

#include "Resources.h"
#include "Log.h"
#include "Utils.h"

namespace sax {

	static std::map< std::string, SDL_Surface* > SurfaceCache = {};
	
	bool Resources::file_exists( std::string path ) {
		Log::info( "File exists?" );
		auto a = std::hash<std::string>()( path );
		std::string id = "tex_" + to_string( a );
		SDL_RWops *file = SDL_RWFromFile( path.c_str(), "r" );
		return file != NULL;
	}

	void Resources::release_all() {
		Log::info( "Releasing all" );
		release_cached_surfaces();
	}

	void Resources::release_cached_surfaces() {
		auto it = SurfaceCache.begin();
		while ( it != SurfaceCache.end() ) {
			SDL_FreeSurface( it->second );
			it = SurfaceCache.erase( it );
		}
	}

	SDL_Surface* Resources::get_surface( std::string path ) {
		
		auto hash = std::hash<std::string>()( path );
		std::string id = "surface_" + to_string( hash );

		auto it = SurfaceCache.find( id );
		SDL_Surface* surface;

		if ( it != SurfaceCache.end() ) {
			surface = it->second;
		} else {
			surface = IMG_Load( path.c_str() );
			SurfaceCache[ id ] = surface;

			if ( surface == nullptr ) {
				Log::error( "Cannot load image: " + path + " Error: " + to_string( IMG_GetError() ) );
			}
			else {
				Log::info( "Image loaded: " + path );
			}
		}
		
		return surface;
	}
		
}