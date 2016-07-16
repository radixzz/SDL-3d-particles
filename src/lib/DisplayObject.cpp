#include "DisplayObject.h"
#include "Log.h"

namespace Sax {
	DisplayObject::DisplayObject() {
		position = new Point();
	}

	DisplayObject::~DisplayObject() {
		Log::info( "Destroying Display Object" );
		delete position;
	}



}