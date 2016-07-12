#ifndef SAX_TYPES_H
#define SAX_TYPES_H

#include <SDL.h>

namespace Sax
{
	struct RendererDescriptor {
		SDL_Renderer* renderer;
		int width;
		int height;
		int pixelFormat;
	};
}

#endif