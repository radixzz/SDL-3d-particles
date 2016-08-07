#include <SDL.h>
#include "Window.h"
#include "Sax.h"

namespace sax {
	
	Window::Window( std::string title, int width, int height ) {
		sdlWindow = SDL_CreateWindow( title.c_str(), 0, 0, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
		this->resize( width, height );
		glContext = SDL_GL_CreateContext( sdlWindow );
		Sax::initialize_glew();
	}

	Window::~Window() {
		SDL_GL_DeleteContext( glContext );
		SDL_DestroyWindow( sdlWindow );
	}

	void Window::resize( int width, int height ) {
		this->width = width;
		this->height = height;
		if ( sdlWindow != nullptr ) {
			SDL_SetWindowSize( sdlWindow, width, height );
			SDL_SetWindowPosition( sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED );
		}
	}

	void Window::setTitle( std::string title ) {
		SDL_SetWindowTitle( sdlWindow, title.c_str() );
	}

	void Window::update() {
		SDL_GL_SwapWindow( sdlWindow );
	}
}