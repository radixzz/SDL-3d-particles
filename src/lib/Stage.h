#ifndef SAX_STAGE_H
#define SAX_STAGE_H

#include <SDL.h>
#include "Sprite.h"
#include "Types.h"
#include "DisplayObject.h"

namespace Sax {
	class Stage {
		public:
			Stage();
			~Stage();
			void update();
			void updateTexture( RendererDescriptor &descriptor );
			void setClearColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
			int copyTo( RendererDescriptor &descriptor );
			void setViewport( SDL_Rect viewport );
			void addChild( DisplayObject* displayObject );
	private:
		SDL_Texture* texture;
		Uint8 clearColor[ 4 ];
		SDL_Rect viewport;
		std::vector< DisplayObject* > children;
	};
}

#endif