#include <memory>
#include <iostream>
#include <algorithm>

#include "DisplayObject.h"
#include "Log.h"
#include "Types.h"

namespace sax {
	DisplayObject::DisplayObject(): rotation(0.f) {
		anchor = std::make_unique<Point>();
		position = std::make_unique<Point>();
		children = {};
	}

	DisplayObject::~DisplayObject() {
		//Log::info( "Destroying Display Object" );
		
		// remove self from any parent
		if ( parent != nullptr ) {
			parent->removeChild( this );
		}

		// remove all children
		auto it = children.begin();
		while( it != children.end() ) {
			removeChild( *it );
			it = children.begin();
		}
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
			children.erase( existingObject );
		}
	}

	void DisplayObject::draw( RendererDescriptor* descriptor ) {
		auto it = children.rbegin();
		for ( ; it != children.rend(); it++ ) {
			( *it )->draw( descriptor );
		}
	}

}