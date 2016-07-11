#ifndef SAX_APPLICATION_H
#define SAX_APPLICATION_H
#include <SDL.h>
#include <vector>
#include "Window.h"

namespace Sax {
	class Application {
		public:
			Application();
			~Application();
			bool initializeSDL();
			void processEvents();
			void render();
			bool running();
			void addWindow( Window* window );
		private:
			void handleWindowEvent( SDL_WindowEvent* e );
			void closeWindow( int id );
			static bool _initted;
			static bool _running;
			static std::vector< Window* > _windows;
	};
}

#endif