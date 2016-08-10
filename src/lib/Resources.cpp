#include <SDL.h>
#include <SDL_image.h>
#include <memory>

#include "Resources.h"

#include "Log.h"
#include "Utils.h"


namespace sax {

	static std::map< size_t, TextureCacheEntry* > TextureCache = {};
	static std::map< std::string, std::unique_ptr< Shader > > ShaderCache = {};
	
	int Resources::get_path_id( std::string path ) {
		return std::hash<std::string>()( path );
	}

	std::string Resources::getFileContents( std::string filePath ) {
		SDL_RWops* rwOps = SDL_RWFromFile( filePath.c_str(), "r" );
		if ( rwOps == NULL ) {
			Log::info( "getFileContents error: " + to_string( SDL_GetError() ) );
			return "";
		} else {
			size_t size = size_t( SDL_RWsize( rwOps ) );
			char* res = new char[ size + 1 ];
			size_t total = 0, read = 1;
			char* buff = res;

			while ( total < size && read != 0 ) {
				read = SDL_RWread( rwOps, buff, 1, ( size - total ) );
				total += read;
				buff += read;
			}
			res[ total ] = '\0';
			std::string result(res, total);
			delete res;
			SDL_RWclose( rwOps );
			return result;
		}
		
	}

	bool Resources::file_exists( std::string path ) {
		return SDL_RWFromFile( path.c_str(), "r" ) != NULL;
	}

	void Resources::release_all() {
		Log::info( "Releasing all" );
		release_cached_textures();
	}

	void Resources::release_cached_textures() {
		auto it = TextureCache.begin();
		while ( it != TextureCache.end() ) {
			SDL_DestroyTexture( it->second->texture );
			delete it->second->textureInfo;
			delete it->second;
			it = TextureCache.erase( it );
		}
	}

	SDL_Texture* Resources::get_texture_from_cache( std::string path ) {
		auto id = std::hash<std::string>()( path );
		auto it = TextureCache.find( id );
		return it != TextureCache.end() ? it->second->texture : NULL;
	}

	void Resources::add_texture_to_cache( std::string path, SDL_Texture* texture, TextureInfo* info ) {
		TextureCacheEntry* entry = nullptr;
		size_t id = get_path_id( path );
		// already on cache?
		auto it = TextureCache.find( id );
		if ( it != TextureCache.end() ) {
			entry = it->second;
		} else {
			entry = new TextureCacheEntry();
		}
		// update fields only if not null
		entry->texture = texture != nullptr ? texture : entry->texture;
		entry->textureInfo = info != nullptr ? info : entry->textureInfo;
		TextureCache[ id ] = entry;
	}
	
	Shader* Resources::get_shader( std::string id, std::string vertexSrc, std::string fragmentSrc ) {	
		auto it = ShaderCache.find( id );
		if ( it != ShaderCache.end() ) {
			return it->second.get();
		} else {
			auto shader = std::make_unique<Shader>();
			shader->load( vertexSrc, fragmentSrc );
			ShaderCache[ id ] = std::move( shader );
			return ShaderCache[ id ].get();
		}
	}

	TextureInfo* Resources::get_texture_info( std::string path ) {
		TextureInfo* info = nullptr;
		auto it = TextureCache.find( get_path_id( path ) );
		if ( it != TextureCache.end() ) {
			info = it->second->textureInfo;
		} else {
			SDL_Surface* surface = IMG_Load( path.c_str() );
			if ( surface != nullptr ) {
				info = new TextureInfo();
				info->width = surface->w;
				info->height = surface->h;
				info->pixelFormat = surface->format->format;
				add_texture_to_cache( path, nullptr, info );
			}
			SDL_FreeSurface( surface );
		}
		return info;
	}

	SDL_Texture* Resources::get_texture( SDL_Renderer* renderer, std::string path ) {
		
		SDL_Texture* texture = get_texture_from_cache( path );

		if ( texture == nullptr ) {
			SDL_Surface* surface = IMG_Load( path.c_str() );
			const char* error = nullptr;
			if ( surface == nullptr ) {
				error = IMG_GetError();
			}
			else {
				SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
				if ( texture == nullptr ) {
					error = SDL_GetError();
				} else {
					Log::info( "Texture loaded: " + path );
					add_texture_to_cache( path, texture, nullptr );
				}
				
				SDL_FreeSurface( surface );
			}

			if ( error != nullptr ) {
				Log::error( "Cannot load texture: " + path + " Error: " + to_string( error ) );
			}
			
		}
		
		return texture;
	}
		
}