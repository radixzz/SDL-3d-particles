#ifndef SAX_TIMER_H
#define SAX_TIMER_H

#include <SDL.h>

namespace sax
{
	class Timer {
		public:
			Timer( bool autostart = false );
			void resume();
			void reset( bool stop = false );
			void pause();
			void stop();
			Uint32 getTicks();
			double getSeconds();
		private:
			bool running;
			bool paused;
			Uint32 startTicks;
			Uint32 pauseTicks;
	};
}

#endif