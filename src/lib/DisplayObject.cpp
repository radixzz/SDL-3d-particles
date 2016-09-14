#include "DisplayObject.h"

namespace sax {
	DisplayObject::DisplayObject(): rotation(0.f) {
		anchor = glm::vec2();
		position = glm::vec2();
		children = {};
		count = 0;
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
		// avoid self aggregation or already parented objects
		if ( displayObject == this || displayObject->parent == this ) return;
		// already in some other parent?
		if ( parent != nullptr && parent != this ) {
			parent->removeChild( displayObject );
		}
		children.insert( children.begin(), displayObject );
		displayObject->parent = this;
	}

	void DisplayObject::addToFront( DisplayObject* displayObject ) {
		removeChild( displayObject );
		addChild( displayObject );
	}

	void DisplayObject::removeChild( DisplayObject* displayObject ) {
		if ( displayObject->parent == this ) {
			children.erase( std::find( children.begin(), children.end(), displayObject ) );
		}
	}
	
	void DisplayObject::onTextureDraw( std::function<void( Texture* tex )> drawCallback ) {
		
		if ( children.empty() ) return;
		auto it = children.rbegin();
		auto end = children.rend();
		for ( ; it != end; ++it ) {
			( *it )->onTextureDraw( drawCallback );
		}
		
	}
	
}