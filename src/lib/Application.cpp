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
		_updateCallback = cb;
		_ticker = new Ticker( std::bind( &Application::onTickerUpdate, this, std::placeholders::_1 ) );
		_wnd = SDL_CreateWindow( "SaxApp", 0, 0, 0, 0, SDL_WINDOW_SHOWN );
		_renderer = SDL_CreateRenderer( _wnd, -1, SDL_RENDERER_ACCELERATED );
		resize( width, height );
	}

	Application::~Application() {
		Log::info( "Releasing..." );
		std::vector<Stage*>::iterator it;
		for ( it = _stages.begin(); it != _stages.end(); ++it ) {
			delete *it;
		}
		delete _ticker;
		_stages.clear();
		SDL_DestroyWindow( _wnd );
		SDL_DestroyRenderer( _renderer );
		SDL_Quit();
	}

	void Application::resize( int width, int height ) {
		_width = width;
		_height = height;
		if ( _wnd != NULL ) {
			SDL_SetWindowSize( _wnd, width, height );
			SDL_SetWindowPosition( _wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED );
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
				_ticker->stop();
				break;
			}
		}
	}

	void Application::run() {
		if ( sdl_initted ) {
			_ticker->resume();
		}
	}

	void Application::onTickerUpdate( double dt ) {
		processEvents();
		_updateCallback( dt );
		render();
	}

	void Application::render() {
		auto it = _stages.begin();
		for ( ; it != _stages.end(); ++it ) {
			( *it )->copyTo( _rendererDescriptor );
		}

		SDL_RenderPresent( _renderer );
	}

	void Application::updateRendererDescriptor() {
		_rendererDescriptor = {
			_renderer,
			_width,
			_height,
			SDL_PIXELFORMAT_RGBA8888
		};
	}

	void Application::addStage( Stage* stage ) {
		bool exists = std::find( _stages.begin(), _stages.end(), stage ) != _stages.end();
		if ( !exists ) {
			_stages.push_back( stage );
		}
	}
}