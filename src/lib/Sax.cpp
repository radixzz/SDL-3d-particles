#include "Sax.h"

#include <GL\glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Log.h"
#include "Utils.h"
#include "Resources.h"

namespace sax {

	const Uint32 SDL_FLAGS = SDL_INIT_VIDEO;
	const Uint32 IMG_FLAGS = IMG_INIT_JPG | IMG_INIT_PNG;

	bool Sax::initted = false;

	void Sax::initialize() {
		
		if ( initted ) {
			return;
		}

		Log::debugMode = true;
		Log::info( "Initializing Sax..." );
		try {
			initialize_sdl();
			initialize_gl();
			initialize_image();
			initialize_ttf();
			initted = true;
			Log::info( "Sax successfuly initialized." );
		} catch ( const std::exception& e ) {
			Log::error( "Cannot initialize Sax > " + to_string( e.what() ) );
			std::exit( EXIT_FAILURE );
		}
	}

	void Sax::release() {
		if ( initted == true ) {
			Log::info( "Releasing Sax..." );
			Resources::release_all();
			TTF_Quit();
			IMG_Quit();
			SDL_Quit();
			initted = false;
		}
	}

	void Sax::initialize_sdl() {
		if ( SDL_Init( SDL_FLAGS ) < 0 ) {
			throw std::runtime_error( "SDL_Init: " + to_string( SDL_GetError() ) );
		} else {
			SDL_GL_SetSwapInterval( 1 );
		}
	}

	void Sax::initialize_gl() {
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES );
		//SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	}

	void Sax::initialize_glew() {
		SDL_GL_SetSwapInterval( 1 ); // VSYNC 1 = ENABLED
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if ( err != GLEW_OK ) {
			Log::info( "Glew init error: " + to_string( glewGetErrorString( err ) ) );
		}
		
	}

	void Sax::initialize_image() {
		int initted = IMG_Init( IMG_FLAGS );
		if ( ( initted & IMG_FLAGS ) != IMG_FLAGS ) {
			throw std::runtime_error( "IMG_Init: " + to_string( IMG_GetError() ) );
		}
	}

	void Sax::initialize_ttf() {
		if ( TTF_Init() != 0 ) {
			throw std::runtime_error( "TTF_Init: " + to_string( TTF_GetError() ) );
		}
	}

}