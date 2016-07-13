#include <SDL.h>
#include "Application.h"
#include <algorithm>
#include "Log.h"
#include "Utils.h"


namespace Sax {
	
	std::vector< Window* > Application::_windows;
	int FPS = 60;
	int TPF = 1000 / FPS;
	
	bool Application::_initted = false;
	bool Application::_running = false;

	Application::Application() {
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
		std::vector< Window* >::iterator it;
		for ( it = _windows.begin(); it != _windows.end(); it++ ) {
			if ( ( *it )->id() == id ) {
				delete *it;
				_windows.erase( it );
				break;
			}
		}
	}

	void Application::render() {
		std::vector<Window*>::iterator it;
		for ( it = _windows.begin(); it != _windows.end(); ++it ) {
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