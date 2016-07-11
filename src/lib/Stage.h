#ifndef SAX_STAGE_H
#define SAX_STAGE_H

#include <SDL.h>

namespace Sax {
	class Stage {
		private:
			SDL_Texture* _texture;
			Uint8 _clearColor[4];
		public:
			Stage();
			~Stage();
			void update();
			void setClearColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
			int copyTo( SDL_Renderer* renderer, int width, int height, int format );
	};
}

#endif