#ifndef SAX_TYPES_H
#define SAX_TYPES_H

#include <SDL.h>
#include <gl\glew.h>

namespace sax
{

	struct TextureCacheEntry {
		GLuint textureId;
		Uint32 pixelFormat;
		int width;
		int height;
	};
}

#endif