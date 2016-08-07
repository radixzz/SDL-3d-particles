#ifndef SAX_WINDOW_H
#define SAX_WINDOW_H

#include <SDL.h>
#include <string>

namespace sax {
	class Window {
		public:
			Window( std::string title, int width, int height );
			~Window();
			void resize( int width, int height );
			void setTitle( std::string title );
			void update();
		protected:
			SDL_GLContext glContext;
			SDL_Window* sdlWindow;
			int width;
			int height;
	};
}

#endif
