#ifndef SAX_RENDERER_H
#define SAX_RENDERER_H

#include <GL\glew.h>
#include <SDL.h>
#include <memory>

#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Log.h"
#include "Utils.h"

namespace sax {
	class Renderer {
		public:
			Renderer( int width, int height );
			void render( Sprite* sprite );
		private:
			void initGL();
			void initGlew();
			std::unique_ptr<SpriteRenderer> spriteRenderer;
	};
}

#endif
