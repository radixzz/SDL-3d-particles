#include <SDL.h>
#include <algorithm>
#include <functional>

#include "Application.h"
#include "Log.h"
#include "Utils.h"
#include "Timer.h"

namespace Sax {

	bool Application::sdl_initted = false;

	Application::Application( int width, int height, std::function<void( double )> cb ) {
		initializeSDL();
		updateCallback = cb;
		ticker = new Ticker( std::bind( &Application::onTickerUpdate, this, std::placeholders::_1 ) );
		window = SDL_CreateWindow( "SaxApp", 0, 0, 0, 0, SDL_WINDOW_SHOWN );
		renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
		resize( width, height );
	}

	Application::~Application() {
		Log::info( "Releasing..." );
		std::vector<Stage*>::iterator it;
		for ( it = stages.begin(); it != stages.end(); ++it ) {
			delete *it;
		}
		delete ticker;
		stages.clear();
		SDL_DestroyWindow( window );
		SDL_DestroyRenderer( renderer );
		SDL_Quit();
	}

	void Application::resize( int width, int height ) {
		this->width = width;
		this->height = height;
		if ( window != NULL ) {
			SDL_SetWindowSize( window, width, height );
			SDL_SetWindowPosition( window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED );
			updateRendererDescriptor();
		}
	}

	bool Application::initializeSDL() {
		if ( !sdl_initted ){
			if ( SDL_Init( SDL_INIT_VIDEO ) == 0 ){
				sdl_initted = true;
				Log::info( "SDL successfuly initialized." );
			}
			else {
				Log::error( "Cannot initialize SDL." );
			}
		}
		return sdl_initted;
	}

	void Application::processEvents() {
		SDL_Event e;
		while ( SDL_PollEvent( &e ) != 0 ) {
			switch ( e.type )
			{
			case SDL_QUIT:
				ticker->stop();
				break;
			}
		}
	}

	void Application::run() {
		if ( sdl_initted ) {
			ticker->resume();
		}
	}

	void Application::onTickerUpdate( double dt ) {
		processEvents();
		updateCallback( dt );
		render();
	}

	void Application::render() {
		auto it = stages.begin();
		for ( ; it != stages.end(); ++it ) {
			( *it )->copyTo( rendererDescriptor );
		}

		SDL_RenderPresent( renderer );
	}

	void Application::updateRendererDescriptor() {
		rendererDescriptor = {
			renderer,
			width,
			height,
			SDL_PIXELFORMAT_RGBA8888
		};
	}

	void Application::addStage( Stage* stage ) {
		bool exists = std::find( stages.begin(), stages.end(), stage ) != stages.end();
		if ( !exists ) {
			stages.push_back( stage );
		}
	}
}