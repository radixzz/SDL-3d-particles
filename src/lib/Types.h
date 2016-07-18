#ifndef SAX_TYPES_H
#define SAX_TYPES_H

#include <SDL.h>
#include <vector>
#include "DisplayObject.h"

namespace sax
{
	struct RendererDescriptor {
		SDL_Renderer* renderer;
		int width;
		int height;
		int pixelFormat;
	};
}

#endif