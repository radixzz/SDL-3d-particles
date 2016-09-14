#include "Renderer.h"

namespace sax {
	Renderer::Renderer( int width, int height ) {
		initGlew();
		initGL();
		spriteRenderer = std::make_unique< SpriteRenderer >();
	}

	void Renderer::initGlew() {
		SDL_GL_SetSwapInterval( 1 ); // VSYNC 1 = ENABLED
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if ( err != GLEW_OK ) {
			Log::info( "Glew init error: " + to_string( glewGetErrorString( err ) ) );
		}
	}

	void Renderer::initGL() {
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES );
		//SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
		glEnable( GL_DEPTH_TEST );
	}

	void Renderer::render( Sprite* sprite ) {
		spriteRenderer->render( sprite );
	}
	
	void Renderer::render( DisplayObject* displayObject ) {
		if ( typeid( *displayObject ).name() == typeid( Sprite ).name() ) {
			this->render( dynamic_cast< Sprite* >( displayObject ) );
		}
		
	}
}