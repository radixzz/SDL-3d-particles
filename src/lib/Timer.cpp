#include "Timer.h"

namespace Sax {
	
	Timer::Timer( bool autostart ) {
		reset( true );
		
		if ( autostart ) {
			resume();
		}
	}

	void Timer::reset( bool stop ) {
		startTicks = SDL_GetTicks();
		pauseTicks = 0;
		if ( stop ) {
			paused = false;
			running = false;
		}
	}

	void Timer::resume() {

		running = true;

		if ( paused ) {
			paused = false;
			startTicks = SDL_GetTicks() - pauseTicks;
			pauseTicks = 0;
		}

	}

	void Timer::stop() {
		reset( true );
	}

	void Timer::pause() {
		paused = true;
		pauseTicks = SDL_GetTicks();
	}

	double Timer::getSeconds() {
		return getTicks() / 1000.f;
	}

	Uint32 Timer::getTicks() {
		if ( running ) {
			return paused ? pauseTicks : SDL_GetTicks() - startTicks;
		}
		else {
			return 0;
		}
	}

}