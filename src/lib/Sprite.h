#ifndef SAX_SPRITE_H
#define SAX_SPRITE_H

#include "DisplayObject.h"
#include "Texture.h"
#include "Types.h"

namespace sax {
	class Sprite: public DisplayObject {
		public:
			Sprite( Texture* texture = nullptr );
			~Sprite();
			void fromImage( std::string path );
			void draw( RendererDescriptor* descriptor );
			int width;
			int height;
		private:
			Texture* texture;
	};
}

#endif