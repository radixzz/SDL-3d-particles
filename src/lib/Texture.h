#ifndef SAX_TEXTURE_H
#define SAX_TEXTURE_H

#include <SDL.h>
#include <map>

#include "Point.h"

namespace sax {
	
	class Texture {
		public:
			Texture();
			~Texture();
			void draw( SDL_Renderer* renderer, SDL_Rect* destRect, double rotation, Point* anchor );
			void fromImage( std::string path );
			int get_width();
			int get_height();
		private:
			int width;
			int height;
			int realWidth;
			int realHeight;
			bool textureCreated;
			bool valid;
			SDL_Rect* crop;
			SDL_Texture* sdlTexture;
			std::string path;
	};
}

#endif