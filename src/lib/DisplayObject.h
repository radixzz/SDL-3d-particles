#ifndef SAX_DISPLAY_OBJECT_H
#define SAX_DISPLAY_OBJECT_H

#include <vector>
#include <functional>

#include <memory>
#include <iostream>
#include <algorithm>
#include <glm\glm.hpp>

#include "Texture.h"
#include "Log.h"

namespace sax {
	class DisplayObject {
		public:
			DisplayObject();
			virtual ~DisplayObject();
			void addChild( DisplayObject* displayObject );
			void addToFront( DisplayObject* displayObject );
			void removeChild( DisplayObject* displayObject );
			void onTextureDraw( std::function<void( Texture* tex )> );
			glm::vec2 position;
			glm::vec2 anchor;
			float rotation;
		protected:
			std::vector< DisplayObject* > children;
			int count;
			DisplayObject* parent;
	};

}

#endif
