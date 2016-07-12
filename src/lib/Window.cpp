#include <algorithm>
#include "Window.h"
#include "Stage.h"
#include "Log.h"
#include "Utils.h"

namespace Sax{

	Window::Window( int width, int height ) {
		_wnd = SDL_CreateWindow( "SaxApp", 0, 0, 0, 0, SDL_WINDOW_SHOWN );
		_renderer = SDL_CreateRenderer( _wnd, -1, SDL_RENDERER_ACCELERATED );
		resize( width, height );
		_active = true;
		Log::info( "Window created" );
	}

	Window::~Window() {
		Log::info( "Destroying Window" );
		_active = false;
		std::vector<Stage*>::iterator it;
		for ( it = _stages.begin(); it != _stages.end(); ++it ) {
			delete *it;
		}
		_stages.clear();
		SDL_DestroyWindow( _wnd );
		SDL_DestroyRenderer( _renderer );
	}

	void Window::resize( int width, int height ) {
		_width = width;
		_height = height;
		if ( _wnd != NULL ) {
			SDL_SetWindowSize( _wnd, width, height );
			SDL_SetWindowPosition( _wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED );
			updateRendererDescriptor();

		}
	}

	void Window::updateRendererDescriptor() {
		_rendererDescriptor = {
			_renderer,
			_width,
			_height,
			SDL_PIXELFORMAT_RGBA8888
		};
	}

	void Window::render() {
		if ( !_active ) {
			return;
		}

		std::vector<Stage*>::iterator it;
		for ( it = _stages.begin(); it != _stages.end(); ++it ) {
			( *it )->copyTo( _rendererDescriptor );
		}

		SDL_RenderPresent( _renderer );
	}

	void Window::addStage( Stage* stage ) {
		bool exists = std::find( _stages.begin(), _stages.end(), stage ) != _stages.end();
		if ( !exists ) {
			_stages.push_back( stage );
		}
	}

	bool Window::active() {
		return _active;
	}

	int Window::id() {
		return SDL_GetWindowID( _wnd );
	}
}