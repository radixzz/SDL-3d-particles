#ifndef SAX_STAGE_H
#define SAX_STAGE_H

#include <SDL.h>
#include "Types.h"

namespace Sax {
	class Stage {
		private:
			SDL_Texture* _texture;
			Uint8 _clearColor[4];
			SDL_Rect _viewport;
		public:
			Stage();
			~Stage();
			void update();
			void updateTexture( RendererDescriptor &descriptor );
			void setClearColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
			int copyTo( RendererDescriptor &descriptor );
			void setViewport( SDL_Rect viewport );
	};
}

#endif