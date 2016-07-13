#ifndef SAX_APPLICATION_H
#define SAX_APPLICATION_H
#include <SDL.h>
#include <deque>
#include <vector>

#include "Window.h"
#include "Timer.h"

namespace Sax {
	
	class Application {
		
		public:
			Application();
			~Application();
			bool initializeSDL();
			void processEvents();
			void updateFPS();
			void render();
			bool running();
			void addWindow( Window* window );
			double getFPS();
		private:
			void handleWindowEvent( SDL_WindowEvent* e );
			void closeWindow( int id );
			bool _initted;
			bool _running;

			Timer _fpsTimer;
			double _lastFrameTime;
			std::deque<double> _fpsSamples;

			std::vector< Window* > _windows;
	};
}

#endif