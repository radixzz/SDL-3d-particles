#ifndef SAX_DISPLAY_OBJECT_H
#define SAX_DISPLAY_OBJECT_H

#include <vector>

#include "Point.h"
#include "DisplayObject.h"

namespace Sax {
	class DisplayObject {
		public:
			DisplayObject();
			virtual ~DisplayObject();
			Point* position;
		private:
			std::vector< DisplayObject* > children;
	};
}

#endif