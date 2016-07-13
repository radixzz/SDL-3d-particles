#ifndef SAX_TIMER_H
#define SAX_TIMER_H

#include <SDL.h>

namespace Sax
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
			bool _running;
			bool _paused;
			Uint32 _startTicks;
			Uint32 _pauseTicks;
	};
}

#endif