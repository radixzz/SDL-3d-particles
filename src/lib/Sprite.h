#ifndef SAX_SPRITE_H
#define SAX_SPRITE_H

#include <memory>
#include <iostream>

#include "DisplayObject.h"
#include "Texture.h"
#include "Types.h"

namespace sax {
	class Sprite: public DisplayObject {
		public:
			Sprite();
			Sprite( std::unique_ptr<Texture> texture );
			~Sprite();
			void fromImage( std::string path );
			void draw( const RendererDescriptor* descriptor );
			int width;
			int height;
		protected:
			std::unique_ptr< Texture > texture;
	};
}

#endif