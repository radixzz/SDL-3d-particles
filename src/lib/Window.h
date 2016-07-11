#ifndef SAX_WINDOW_H
#define SAX_WINDOW_H
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Stage.h"

namespace Sax {
	class Window {
		private:
			static bool SDLInitted;
		public:
			Window(int, int);
			~Window();
			static bool InitSDL();
			void render();
			void resize( int, int );
			void setClearColor( int r, int g, int b, int a );
			void addStage(Stage* stage);
			void setTitle(std::string title);
			bool active();
			int id();
		private:
			int _width;
			int _height;
			bool _active;
			SDL_Window* _wnd;
			SDL_Renderer* _renderer;
			std::vector<Stage*> _stages;
	};
}

#endif