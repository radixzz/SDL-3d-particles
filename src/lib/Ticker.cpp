#include "Ticker.h"

namespace sax {
	Ticker::Ticker( std::function<void( double )> cb ) {
		fpsSamples[ MAX_FPS_SAMPLES ] = {};
		tickCallback = cb;
		fpsIndex = 0;
		lastFrameTime = 0;
		running = false;
		fpsTimer = std::make_unique<Timer>( true );
	}

	Ticker::~Ticker() {
		running = false;
	}

	double Ticker::getFPS() {
		if ( fpsIndex > MAX_FPS_SAMPLES ) {
			
			double total = 0;
			for ( int i = 0; i < MAX_FPS_SAMPLES; i++ ) {
				total += fpsSamples[ i ];
			}

			return 1000 * MAX_FPS_SAMPLES / total;
		} else {
			return 0;
		}
	}

	double Ticker::getElapsedTime() {
		return fpsTimer->getSeconds();
	}

	void Ticker::resume() {
		running = true;
		
		while ( running ) {
			double frameTime = fpsTimer->getTicks() - lastFrameTime;
			lastFrameTime = fpsTimer->getTicks();
			fpsSamples[ fpsIndex++ % MAX_FPS_SAMPLES ] = frameTime;	
			tickCallback( frameTime );
		}
	}

	void Ticker::stop() {
		running = false;
	}
}