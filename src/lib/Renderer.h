#ifndef SAX_RENDERER_H
#define SAX_RENDERER_H

#include <GL/glew.h>
#include <SDL.h>
#include <memory>

#include "SpriteRenderer.h"
#include "DisplayObject.h"
#include "Sprite.h"
#include "Stage.h"
#include "Log.h"
#include "Utils.h"


namespace sax {
	class Renderer {
		public:
			Renderer( int width, int height );
			void render( Sprite* sprite );
			void render( DisplayObject* displayObject );
			void resize( int width, int height );
		private:
			void initGL();
			void initGlew();
			std::unique_ptr<SpriteRenderer> spriteRenderer;
			int width;
			int height;
	};
}

#endif
