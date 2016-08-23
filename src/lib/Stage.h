#ifndef SAX_STAGE_H
#define SAX_STAGE_H

#include <SDL.h>
#include <memory>
//#include <iostream>

#include "Renderer.h"
#include "Sprite.h"
#include "Types.h"
#include "DisplayObject.h"

namespace sax {
	class Stage {
		public:
			Stage();
			~Stage();
			void render( Renderer* renderer );
			void addChild( DisplayObject* displayObject );
			void removeChild( DisplayObject* displayObject );
			void setViewport( SDL_Rect viewport );
		private:
			SDL_Rect viewport;
			std::shared_ptr<DisplayObject> container;
	};
}

#endif