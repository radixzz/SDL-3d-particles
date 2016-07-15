#ifndef SAX_TEXTURE_H
#define SAX_TEXTURE_H

#include <SDL.h>
#include <map>

namespace Sax {
	
	class Texture {
		static std::map< std::string, SDL_Texture* > Cache;
		public:
			Texture();
			~Texture();
			void draw( SDL_Renderer* renderer );
			void fromImage( std::string path );
		private:
			double _width;
			double _height;
			double _realWidth;
			double _realHeight;
			std::string _path;
	};
}

#endif