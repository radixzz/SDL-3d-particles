#ifndef SAX_SPRITE_H
#define SAX_SPRITE_H

#include <memory>
#include <iostream>

#include "DisplayObject.h"
#include "Texture.h"
#include <functional>

namespace sax {
	class Sprite: public DisplayObject {
		public:
			Sprite();
			~Sprite();
			void fromImage( const std::string& path );
			void onTextureDraw( std::function< void( Texture* tex ) > );
			int width;
			int height;
		protected:
			std::string path;
			Shader* shader;
			Texture* texture;
	};
}

#endif