#ifndef SAX_COLOR_H
#define SAX_COLOR_H

#include <GL/glew.h>
#include <SDL.h>

namespace sax {
	struct Color {
		GLclampf r;
		GLclampf g;
		GLclampf b;
		GLclampf a;
		// TODO: make utils to convert from/to HEX
	};
}

#endif
