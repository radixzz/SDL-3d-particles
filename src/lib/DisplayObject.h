#ifndef SAX_DISPLAY_OBJECT_H
#define SAX_DISPLAY_OBJECT_H

#include <vector>
#include "Point.h"
#include "Types.h"

namespace sax {
	
	class DisplayObject {
		public:
			typedef std::vector< DisplayObject* > DOVector;
			typedef DOVector::const_iterator DOIterator;

			DisplayObject();
			virtual ~DisplayObject();
			void addChild( DisplayObject* displayObject );
			void removeChild( DisplayObject* displayObject );
			virtual void draw( RendererDescriptor* descriptor );
			DOIterator DisplayObject::begin() const { return children.begin(); }
			DOIterator DisplayObject::end() const { return children.end(); }
			
			Point* position;
			Point* anchor;
			double rotation;
		protected:
			DOVector children;
			DisplayObject* parent;
	};

}

#endif