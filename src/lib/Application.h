#ifndef SAX_APPLICATION_H
#define SAX_APPLICATION_H
#include <gl\glew.h>
#include <SDL.h>
#include <vector>
#include <functional>
#include <iostream>
#include <memory>

#include "Window.h"
#include "Stage.h"
#include "Types.h"
#include "Ticker.h"
#include "Text.h"
#include "Color.h"

namespace sax {
	
	class Application {
		public:
			Application( int width, int height, std::function<void( double, double )> );
			~Application();
			
			void run();
			void resize( int width, int height );
			void addStage( Stage* stage );
			void setTitle( std::string title );
			void setClearColor( Color color );
			bool showFps;
		private:
			void processEvents();
			void render();
			void logInfo();
			void renderFps( Stage* stage );
			void renderClear();
			void onTickerUpdate( double dt );
			void updateFpsText();
			void updateRendererDescriptor();
			void handleWindowEvent( SDL_WindowEvent* e );
			Color clearColor;
			
			std::unique_ptr<Ticker> ticker;
			std::function< void( double, double ) > updateCallback;
			RendererDescriptor rendererDescriptor;
			std::unique_ptr<Window> window;
			
			std::unique_ptr<Text> fpsText;
			std::unique_ptr<Timer> fpsTimer;
			std::vector< Stage* > stages;
	};
}

#endif