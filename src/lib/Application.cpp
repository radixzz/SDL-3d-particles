#include <SDL.h>
#include "Application.h"
#include <algorithm>
#include "Log.h"
#include "Utils.h"
#include "Timer.h"

namespace Sax {

	bool Application::sdl_initted = false;

	Application::Application( int width, int height ) {
		initializeSDL();
		_lastFrameTime = 0;
		_fpsTimer = Timer( true );
		_wnd = SDL_CreateWindow( "SaxApp", 0, 0, 0, 0, SDL_WINDOW_SHOWN );
		_renderer = SDL_CreateRenderer( _wnd, -1, SDL_RENDERER_ACCELERATED );
		resize( width, height );
	}

	Application::~Application() {
		Log::info( "Releasing..." );
		_running = false;
		std::vector<Stage*>::iterator it;
		for ( it = _stages.begin(); it != _stages.end(); ++it ) {
			delete *it;
		}
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
				_running = true;
				Log::info( "SDL successfuly initialized." );
			}
			else {
				Log::error( "Cannot initialize SDL." );
			}
		}
		return sdl_initted;
	}

	bool Application::running() {
		return _running;
	}

	void Application::processEvents() {
		SDL_Event e;
		while ( SDL_PollEvent( &e ) != 0 ) {
			switch ( e.type )
			{
			case SDL_QUIT:
				_running = false;
				break;
			}
		}
	}

	double Application::getFPS() {
		double sum = 0;
		auto it = _fpsSamples.begin();
		for ( ; it != _fpsSamples.end(); it++ ) {
			sum += *it;
		}
		return sum / _fpsSamples.size();
	}

	void Application::updateFPS() {
		double frameTime = _fpsTimer.getSeconds() - _lastFrameTime;
		_lastFrameTime = _fpsTimer.getSeconds();
		if ( _fpsSamples.size() > 100 ) {
			_fpsSamples.pop_back();
		}
		_fpsSamples.push_front( 1 / frameTime );
	}

	void Application::render() {
		
		if ( !_running ) {
			return;
		}

		updateFPS();

		std::vector<Stage*>::iterator it;
		for ( it = _stages.begin(); it != _stages.end(); ++it ) {
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