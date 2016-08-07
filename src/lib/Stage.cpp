#include <SDL.h>
#include <memory>
#include "Stage.h"
#include "Log.h"

namespace sax
{

	Stage::Stage() {
		container = std::make_unique< DisplayObject >();
		viewport = { 0 };
	}

	Stage::~Stage() {
	}

	void Stage::setViewport( SDL_Rect viewport ) {
		this->viewport = viewport;
	}

	void Stage::render( RendererDescriptor* rendererDescriptor ) {
		container->draw( rendererDescriptor );
	}

	void Stage::addChild( DisplayObject* displayObject ) {
		container->addChild( displayObject );
	}

	void Stage::removeChild( DisplayObject* displayObject ) {
		container->removeChild( displayObject );
	}
}