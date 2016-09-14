#ifndef SAX_STAGE_H
#define SAX_STAGE_H

#include <SDL.h>
#include <memory>
#include <functional>

#include "DisplayObject.h"
#include "Log.h"

namespace sax {
	class Stage: public DisplayObject {
		public:
			Stage();
			~Stage();
			void setViewport( SDL_Rect viewport );
			void onObjectRender( std::function< void( DisplayObject* ) > );
		private:
			SDL_Rect viewport;
	};
}

#endif