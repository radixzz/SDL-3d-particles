#ifndef SAX_SPRITE_H
#define SAX_SPRITE_H

#include "DisplayObject.h"
#include "Texture.h"

namespace Sax {
	class Sprite: public DisplayObject {
		public:
			Sprite( Texture* texture = nullptr );
			~Sprite();
			void fromImage( std::string path );
		private:
			Texture* texture;
	};
}

#endif