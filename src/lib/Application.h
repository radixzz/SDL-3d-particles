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
			int width;
			int height;
			Ticker* ticker;
			std::function< void(double) > updateCallback;
			RendererDescriptor rendererDescriptor;
			SDL_Window* window;
			SDL_Renderer* renderer;
			std::vector< Stage* > stages;
	};
}

#endif