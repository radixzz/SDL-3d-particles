#include "DisplayObject.h"
#include "Log.h"
#include "Types.h"
#include <algorithm>

namespace sax {
	DisplayObject::DisplayObject(): rotation(0.f) {
		anchor = new Point();
		position = new Point();
		children = {};
	}

	DisplayObject::~DisplayObject() {
		//Log::info( "Destroying Display Object" );
		if ( parent != nullptr ) {
			parent->removeChild( this );
		}

		// remove all children
		auto it = children.begin();
		while( it != children.end() ) {
			removeChild( *it );
			it = children.begin();
		}

		delete anchor;
		delete position;
	}

	void DisplayObject::addChild( DisplayObject* displayObject ) {
		// avoid self aggregation
		if ( displayObject == this ) return;
		// already in some other parent?
		if ( parent != nullptr && parent != this ) {
			parent->removeChild( displayObject );
		}
		removeChild( displayObject );
		children.insert( children.begin(), displayObject );
		displayObject->parent = this;
	}

	void DisplayObject::removeChild( DisplayObject* displayObject ) {
		auto existingObject = std::find( children.begin(), children.end(), displayObject );
		if ( existingObject != children.end() ) {
			( *existingObject )->parent = nullptr;
			children.erase( existingObject );
		}
	}

	void DisplayObject::draw( RendererDescriptor* descriptor ) {
		auto it = children.begin();
		for ( ; it != children.end(); it++ ) {
			( *it )->draw( descriptor );
		}
	}

}