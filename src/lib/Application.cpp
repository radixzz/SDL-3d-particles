#include <gl\glew.h>
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
		window = std::make_unique<Window>( "SaxApp", width, height );
		setClearColor( { 0.5, 0, 0, 1.0 } );
		resize( width, height );
		logInfo();
	}

	Application::~Application() {
		stages.clear();
		fpsText.reset();
		window.reset();
		Sax::release();
	}

	void Application::setTitle( std::string title ) {
		this->window->setTitle( title );
	}

	void Application::logInfo() {
		/*
		SDL_RendererInfo info;
		SDL_GetRendererInfo( renderer, &info );
		std::string accelerated = ( SDL_RENDERER_ACCELERATED & info.flags ) ? "Yes" : "No";
		auto texW = to_string( info.max_texture_width );
		auto texH = to_string( info.max_texture_height );
		Log::info( "HW Acceleration: " + accelerated );
		Log::info( "Renderer name: " + to_string( info.name ) );
		Log::info( "Max texture size: " + texW + "x" + texH );
		*/
	}

	void Application::updateFpsText() {
		if (this->fpsText == NULL) {
			this->fpsText = std::make_unique<Text>( "Roboto", 16 );
			this->fpsText->position.x = 10;
			this->fpsText->position.y = 10;
		}
	}

	void Application::setClearColor( Color color ) {
		clearColor = color;
	}

	void Application::resize( int width, int height ) {
		this->window->resize( width, height );
		
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
		glClearColor(
			clearColor.r,
			clearColor.g,
			clearColor.b,
			clearColor.a
		);
		
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	void Application::onTickerUpdate( double dt ) {
		processEvents();
		renderClear();
		updateCallback( dt, ticker->getElapsedTime() );
		updateFpsText();
		render();
	}

	void Application::renderFps( Stage* stage ) {
		if ( this->showFps ) {
			if ( fpsTimer->getSeconds() > 0.33 ) {
				fpsTimer->reset();
				std::string label = "FPS @ " + to_string( ticker->getFPS() );
				this->window->setTitle( label );
				this->fpsText->setText( label );
			}
			stage->addChild( this->fpsText.get() );
		}
	}

	void Application::render() {
		auto it = stages.begin();

		for ( ; it != stages.end(); ++it ) {
			renderFps( *it );
			( *it )->render( window->renderer.get() );
		}

		window->update();
	}

	void Application::addStage( Stage* stage ) {
		bool exists = std::find( stages.begin(), stages.end(), stage ) != stages.end();
		if ( !exists ) {
			stages.push_back( stage );
		}
	}
}