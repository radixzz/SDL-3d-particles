#include "Sax.h"

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
			//print_opengl_info();
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