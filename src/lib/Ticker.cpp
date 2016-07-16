#include "Ticker.h"

namespace Sax {
	Ticker::Ticker( std::function<void( double )> cb ) {
		_tickCallback = cb;
		_lastFrameTime = 0.f;
		_running = false;
		_fpsTimer = Timer( true );
	}

	Ticker::~Ticker() {
		_running = false;
	}

	double Ticker::getFPS() {
		double sum = 0;
		auto it = _fpsSamples.begin();
		for ( ; it != _fpsSamples.end(); it++ ) {
			sum += *it;
		}
		return sum / _fpsSamples.size();
	}

	void Ticker::resume() {
		_running = true;
		while ( _running ) {
			double frameTime = _fpsTimer.getTicks() - _lastFrameTime;
			_lastFrameTime = _fpsTimer.getTicks();
			if ( _fpsSamples.size() > 100 ) {
				_fpsSamples.pop_back();
			}
			_fpsSamples.push_front( 1000 / frameTime );
			_tickCallback( frameTime );
		}
	}

	void Ticker::stop() {
		_running = false;
	}
}