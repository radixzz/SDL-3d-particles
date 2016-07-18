#include "Ticker.h"

namespace sax {
	Ticker::Ticker( std::function<void( double )> cb ) {
		tickCallback = cb;
		lastFrameTime = 0.f;
		running = false;
		fpsTimer = Timer( true );
	}

	Ticker::~Ticker() {
		running = false;
	}

	double Ticker::getFPS() {
		double sum = 0;
		auto it = fpsSamples.begin();
		for ( ; it != fpsSamples.end(); it++ ) {
			sum += *it;
		}
		return sum / fpsSamples.size();
	}

	void Ticker::resume() {
		running = true;
		while ( running ) {
			double frameTime = fpsTimer.getTicks() - lastFrameTime;
			lastFrameTime = fpsTimer.getTicks();
			if ( fpsSamples.size() > 100 ) {
				fpsSamples.pop_back();
			}
			fpsSamples.push_front( 1000 / frameTime );
			tickCallback( frameTime );
		}
	}

	void Ticker::stop() {
		running = false;
	}
}