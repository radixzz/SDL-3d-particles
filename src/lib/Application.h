#ifndef SAX_APPLICATION_H
#define SAX_APPLICATION_H
#include <SDL.h>
#include <deque>
#include <vector>

#include "Timer.h"
#include "Stage.h"
#include "Types.h"

namespace Sax {
	
	class Application {
		static bool sdl_initted;
		public:
			Application( int width, int height );
			~Application();
			bool initializeSDL();
			void processEvents();
			void updateFPS();
			void render();
			bool running();
			void resize( int, int );
			void addStage( Stage* stage );
			void setTitle( std::string title );
			double getFPS();
		private:
			void updateRendererDescriptor();
			void handleWindowEvent( SDL_WindowEvent* e );
			
			bool _running;
			int _width;
			int _height;

			Timer _fpsTimer;
			double _lastFrameTime;
			std::deque<double> _fpsSamples;
			
			RendererDescriptor _rendererDescriptor;
			SDL_Window* _wnd;
			SDL_Renderer* _renderer;
			std::vector<Stage*> _stages;
	};
}

#endif