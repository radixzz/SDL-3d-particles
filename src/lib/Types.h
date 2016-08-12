#ifndef SAX_TYPES_H
#define SAX_TYPES_H

#include <SDL.h>
#include <gl\glew.h>

namespace sax
{
	struct RendererDescriptor {
		SDL_Renderer* renderer;
		int width;
		int height;
		Uint32 pixelFormat;
	};

	struct TextureCacheEntry {
		GLuint textureId;
		Uint32 pixelFormat;
		int width;
		int height;
	};
}

#endif