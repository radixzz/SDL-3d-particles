#ifndef SAX_TEXTURE_H
#define SAX_TEXTURE_H

#include <SDL.h>
#include <map>

#include "Point.h"
#include "Shader.h"

namespace sax {
	
	class Texture {
		public:
			Texture();
			~Texture();
			void clear();
			void bind();
			void unbind();
			void fromImage( std::string path );
			void fromSurface( SDL_Surface* surface );
			int get_width();
			int get_height();
		private:
			int width;
			int height;
			int realWidth;
			int realHeight;
			GLuint textureId;
			std::string path;
	};
}

#endif