#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Resources.h"
#include "Log.h"
#include "Utils.h"
#include "Texture.h"

namespace sax {

	static std::unordered_map< std::string, std::unique_ptr< Texture > > TextureCache = {};
	static std::unordered_map< std::string, std::unique_ptr< Shader > > ShaderCache = {};
	
	int Resources::get_path_id( std::string path ) {
		return std::hash<std::string>()( path );
	}

	std::string Resources::getFileContents( const std::string &filePath ) {
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
		TextureCache.clear();
	}
	
	Shader* Resources::get_shader( const std::string& id, const std::string& vertexSrc, const std::string& fragmentSrc ) {
		if ( ShaderCache.count( id ) == 0 ) {
			auto shader = std::make_unique<Shader>();
			shader->load( vertexSrc, fragmentSrc );
			ShaderCache[ id ] = std::move( shader );
			return ShaderCache[ id ].get();
		} else {
			return ShaderCache.at( id ).get();
		}
	}

	Shader* Resources::get_shader( const std::string& id ) {
		return get_shader( id, "", "" );
	}
	
	Texture* Resources::get_texture( const std::string& path ) {
		
		if ( TextureCache.count( path ) == 0 ) {
			Texture* texture = new Texture();
			texture->fromImage( path );
			TextureCache.insert( std::make_pair( path, std::unique_ptr< Texture >( texture ) ) );
			return texture;
		} else {
			return TextureCache.at( path ).get();
		}
		
		
	}
		
}