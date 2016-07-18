#ifndef SAX_RESOURCES_H
#define SAX_RESOURCES_H

#include <map>
#include <SDL.h>

namespace sax {
	class Resources {
		public:
			static bool file_exists( std::string path );
			static SDL_Surface* get_surface( std::string path );
			static void release_all();
		private:
			Resources();
			~Resources();
			static void release_cached_surfaces();
			static std::map< std::string, SDL_Texture* > Cache;
	};
}

#endif
