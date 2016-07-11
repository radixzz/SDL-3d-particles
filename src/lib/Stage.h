#ifndef SAX_STAGE_H
#define SAX_STAGE_H

#include <SDL.h>

namespace Sax {
	class Stage {
		private:
			SDL_Texture* _texture;
		public:
			Stage();
			~Stage();
			void update();
			int copyTo( SDL_Renderer* renderer, int width, int height, int format );
	};
}

#endif