#include "Ticker.h"

namespace Sax {
	Ticker::Ticker( std::function<void( double )> cb ) {
		_tickCallback = cb;
		_lastFrameTime = 0;
		_running = false;
		_fpsTimer = Timer( true );
		updateFPS();
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

	void Ticker::updateFPS() {
		double frameTime = _fpsTimer.getSeconds() - _lastFrameTime;
		_lastFrameTime = _fpsTimer.getSeconds();
		if ( _fpsSamples.size() > 100 ) {
			_fpsSamples.pop_back();
		}
		_fpsSamples.push_front( 1 / frameTime );
	}

	void Ticker::resume() {
		_running = true;
		while ( _running ) {
			_tickCallback( 0 );
		}
	}

	void Ticker::stop() {
		_running = false;
	}
}