#include <SDL.h>
#include <algorithm>
#include <functional>

#include "Application.h"
#include "Log.h"
#include "Utils.h"
#include "Timer.h"
#include "Sax.h"

namespace sax {

	Application::Application( int width, int height, std::function<void( double )> cb ) {
		Sax::initialize();
		updateCallback = cb;
		ticker = new Ticker( std::bind( &Application::onTickerUpdate, this, std::placeholders::_1 ) );
		window = SDL_CreateWindow( "SaxApp", 0, 0, 0, 0, SDL_WINDOW_SHOWN );
		renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
		setClearColor( 0, 0, 0, 255 );
		resize( width, height );
	}

	Application::~Application() {
		delete ticker;
		stages.clear();
		SDL_DestroyWindow( window );
		SDL_DestroyRenderer( renderer );
		Sax::release();
	}

	void Application::setClearColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a ) {
		clearColor[ 0 ] = r;
		clearColor[ 1 ] = g;
		clearColor[ 2 ] = b;
		clearColor[ 3 ] = a;
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
		ticker->resume();
	}

	void Application::renderClear() {
		
		SDL_SetRenderDrawColor( 
			rendererDescriptor.renderer,
			clearColor[ 0 ],
			clearColor[ 1 ],
			clearColor[ 2 ],
			clearColor[ 3 ]
		);
		
		SDL_RenderClear( rendererDescriptor.renderer );
	}

	void Application::onTickerUpdate( double dt ) {
		processEvents();
		renderClear();
		updateCallback( dt );
		render();
	}

	void Application::render() {
		auto it = stages.begin();
		for ( ; it != stages.end(); ++it ) {
			( *it )->render( &rendererDescriptor );
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