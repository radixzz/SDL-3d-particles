#include "DisplayObject.h"

namespace Sax {
	DisplayObject::DisplayObject() {
		position = new Point();

	}

	DisplayObject::~DisplayObject() {
		delete position;
	}
}