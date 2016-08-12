#ifndef SAX_RESOURCES_H
#define SAX_RESOURCES_H

#include <unordered_map>
#include <SDL.h>

#include "Types.h"
#include "Shader.h"
#include "Texture.h"

namespace sax {
	class Resources {
		public:
			static bool file_exists( std::string path );
			static Texture* get_texture( const std::string& path );
			static Shader* get_shader( const std::string& id, const std::string& vertexSrc, const std::string& fragmentSrc );
			static Shader* get_shader( const std::string& id );
			static std::string getFileContents( const std::string &filePath );
			static void release_all();
		private:
			Resources();
			static int get_path_id( std::string path );
			static void release_cached_textures();
	};
}

#endif
