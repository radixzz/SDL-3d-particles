#ifndef SAX_H
#define SAX_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include <SDL_opengles2.h>
#include "Log.h"
#include "Utils.h"
#include "Resources.h"

namespace sax {
	class Sax {
	public:
		static void initialize();
		static void release();
	private:
		static bool initted;
		static void initialize_sdl();
		static void initialize_image();
		static void initialize_ttf();
		Sax();
	};
	
}

#endif