#include <SDL.h>
#include <algorithm>
#include <functional>

#include "Application.h"
#include "Log.h"
#include "Utils.h"
#include "Timer.h"
#include "Sax.h"

namespace sax {

	Application::Application( int width, int height, std::function<void( double, double )> cb ) {
		Sax::initialize();
		updateCallback = cb;
		fpsTimer = std::make_unique<Timer>( true );
		ticker = std::make_unique<Ticker>( std::bind( &Application::onTickerUpdate, this, std::placeholders::_1 ) );
		window = SDL_CreateWindow( "SaxApp", 0, 0, 0, 0, SDL_WINDOW_SHOWN );
		renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
		setClearColor( 0, 0, 0, 255 );
		resize( width, height );
		logInfo();
	}

	Application::~Application() {
		stages.clear();
		fpsText.reset();
		SDL_DestroyWindow( window );
		SDL_DestroyRenderer( renderer );
		Sax::release();
	}

	void Application::logInfo() {
		SDL_RendererInfo info;
		SDL_GetRendererInfo( renderer, &info );
		std::string accelerated = ( SDL_RENDERER_ACCELERATED & info.flags ) ? "Yes" : "No";
		auto texW = to_string( info.max_texture_width );
		auto texH = to_string( info.max_texture_height );
		Log::info( "HW Acceleration: " + accelerated );
		Log::info( "Renderer name: " + to_string( info.name ) );
		Log::info( "Max texture size: " + texW + "x" + texH );
	}

	void Application::updateFpsText() {
		if (this->fpsText == NULL) {
			this->fpsText = std::make_unique<Text>( "Roboto", 16 );
			this->fpsText->position->x = 10;
			this->fpsText->position->y = 10;
		}
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
		updateCallback( dt, ticker->getElapsedTime() );
		updateFpsText();
		render();
	}

	void Application::render() {
		auto it = stages.begin();
		for ( ; it != stages.end(); ++it ) {
			
			if ( this->showFps ) {
				if ( fpsTimer->getSeconds() > 0.5 ) {
					fpsTimer->reset();
					std::string label = "FPS @ " + to_string( ticker->getFPS() );
					SDL_SetWindowTitle( window, label.c_str() );
					this->fpsText->setText( label );
				}
				( *it )->addChild( this->fpsText.get() );
			}
			
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