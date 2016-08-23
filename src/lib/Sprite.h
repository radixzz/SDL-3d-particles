#ifndef SAX_SPRITE_H
#define SAX_SPRITE_H

#include <memory>
#include <iostream>

#include "Renderer.h"
#include "DisplayObject.h"
#include "Texture.h"

namespace sax {
	class Sprite: public DisplayObject {
		public:
			Sprite();
			~Sprite();
			void fromImage( std::string path );
			void draw( Renderer* renderer );
			int width;
			int height;
		protected:
			std::string path;
			Shader* shader;
	};
}

#endif