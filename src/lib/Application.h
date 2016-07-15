#ifndef SAX_APPLICATION_H
#define SAX_APPLICATION_H

#include <SDL.h>
#include <vector>
#include <functional>

#include "Stage.h"
#include "Types.h"
#include "Ticker.h"

namespace Sax {
	
	class Application {
		static bool sdl_initted;

		public:
			Application( int width, int height, std::function<void( double )> );
			~Application();
			bool initializeSDL();
			void processEvents();
			void render();
			void run();
			void resize( int, int );
			void addStage( Stage* stage );
			void setTitle( std::string title );
		private:
			void onTickerUpdate( double dt );
			void updateRendererDescriptor();
			void handleWindowEvent( SDL_WindowEvent* e );
			int _width;
			int _height;
			Ticker* _ticker;
			std::function<void(double)> _updateCallback;
			RendererDescriptor _rendererDescriptor;
			SDL_Window* _wnd;
			SDL_Renderer* _renderer;
			std::vector<Stage*> _stages;
	};
}

#endif