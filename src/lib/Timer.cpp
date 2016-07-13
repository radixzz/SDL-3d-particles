#include "Timer.h"

namespace Sax {
	
	Timer::Timer() {
		reset( true );
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

	Uint32 Timer::getTicks() {
		if ( _running ) {
			return _paused ? _pauseTicks : SDL_GetTicks() - _startTicks;
		}
		else {
			return 0;
		}
	}

}