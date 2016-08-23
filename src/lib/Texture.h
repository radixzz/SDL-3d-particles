#ifndef SAX_TEXTURE_H
#define SAX_TEXTURE_H

#include <SDL.h>
#include <map>

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
			SDL_Surface* resizeSurface( SDL_Surface* surface, const int& width, const int& height );
			int getNearestPowerOf2( int num );
			int get_width();
			int get_height();
		private:
			int width;
			int height;
			int naturalWidth;
			int naturalHeight;
			GLuint textureId;
			std::string path;
	};
}

#endif