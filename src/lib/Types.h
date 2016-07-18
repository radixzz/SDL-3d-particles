#ifndef SAX_TYPES_H
#define SAX_TYPES_H

#include <SDL.h>

namespace sax
{
	struct RendererDescriptor {
		SDL_Renderer* renderer;
		int width;
		int height;
		Uint32 pixelFormat;
	};

	struct TextureInfo {
		int width;
		int height;
		Uint32 pixelFormat;
	};

	struct TextureCacheEntry {
		SDL_Texture* texture;
		TextureInfo* textureInfo;
	};
}

#endif