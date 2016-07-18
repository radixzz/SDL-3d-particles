#ifndef SAX_RESOURCES_H
#define SAX_RESOURCES_H

#include <map>
#include <SDL.h>

#include "Types.h"

namespace sax {
	class Resources {
		public:
			static bool file_exists( std::string path );
			static TextureInfo* get_texture_info( std::string path );
			static SDL_Texture* get_texture( SDL_Renderer* renderer, std::string path );
			static void release_all();
		private:
			Resources();
			~Resources();
			static int get_path_id( std::string path );
			static SDL_Texture* get_texture_from_cache( std::string path );
			static void add_texture_to_cache( std::string path, SDL_Texture* texture, TextureInfo* info );
			static void release_cached_textures();
			static std::map< std::string, SDL_Texture* > Cache;
	};
}

#endif
