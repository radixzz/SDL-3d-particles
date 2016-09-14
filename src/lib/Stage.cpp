#include "Stage.h"

namespace sax
{

	Stage::Stage() {
		viewport = { 0 };
	}

	Stage::~Stage() {
	}

	void Stage::setViewport( SDL_Rect viewport ) {
		this->viewport = viewport;
	}

	void Stage::onObjectRender( std::function< void( DisplayObject* ) > renderCallback ) {
		if ( children.empty() ) return;
		auto it = children.rbegin();
		auto end = children.rend();
		for ( ; it != end; ++it ) {
			renderCallback( *it );
		}
	}

}