#include <SDL.h>
#include "Application.h"
#include <algorithm>
#include "Log.h"
#include "Utils.h"
#include "Timer.h"

namespace Sax {

	Application::Application() {
		_initted = false;
		_running = false;
		_lastFrameTime = 0;
		_fpsTimer = Timer( true );

		initializeSDL();
	}

	Application::~Application() {
		Log::info( "Releasing..." );
		_running = false;
		SDL_Quit();
	}

	bool Application::initializeSDL() {
		if ( !_initted ){
			if ( SDL_Init( SDL_INIT_VIDEO ) == 0 ){
				_initted = true;
				_running = true;
				Log::info( "SDL successfuly initialized." );
			}
			else {
				Log::error( "Cannot initialize SDL." );
			}
		}
		return _initted;
	}

	bool Application::running() {
		return _running;
	}

	void Application::processEvents() {
		SDL_Event e;
		while ( SDL_PollEvent( &e ) != 0 ) {
			switch ( e.type )
			{
			case SDL_WINDOWEVENT:
				handleWindowEvent( &e.window );
				break;
			case SDL_QUIT:
				_running = false;
				break;
			}
		}
	}

	void Application::handleWindowEvent( SDL_WindowEvent* e ) {
		switch ( e->event ) {
		case SDL_WINDOWEVENT_CLOSE:
			closeWindow( e->windowID );
			break;
		}
	}

	void Application::closeWindow( int id ) {
		auto it = _windows.begin();
		for ( ; it != _windows.end(); it++ ) {
			if ( ( *it )->id() == id ) {
				delete *it;
				_windows.erase( it );
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
		updateFPS();
		auto it = _windows.begin();
		for ( ; it != _windows.end(); ++it ) {
			( *it )->render();
		}
	}

	void Application::addWindow( Window* window ) {
		bool exists = std::find( _windows.begin(), _windows.end(), window ) != _windows.end();
		if ( !exists ) {
			_windows.push_back( window );
		}
	}
}