#include "Timer.h"

namespace Sax {
	
	Timer::Timer( bool autostart ) {
		reset( true );
		
		if ( autostart ) {
			resume();
		}
	}

	void Timer::reset( bool stop ) {
		_startTicks = SDL_GetTicks();
		_pauseTicks = 0;
		if ( stop ) {
			_paused = false;
			_running = false;
		}
	}

	void Timer::resume() {

		_running = true;

		if ( _paused ) {
			_paused = false;
			_startTicks = SDL_GetTicks() - _pauseTicks;
			_pauseTicks = 0;
		}

	}

	void Timer::stop() {
		reset( true );
	}

	void Timer::pause() {
		_paused = true;
		_pauseTicks = SDL_GetTicks();
	}

	double Timer::getSeconds() {
		return getTicks() / 1000.f;
	}

	Uint32 Timer::getTicks() {
		if ( _running ) {
			return _paused ? _pauseTicks : SDL_GetTicks() - _startTicks;
		}
		else {
			return 0;
		}
	}

}