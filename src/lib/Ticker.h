#ifndef SAX_TICKER_H
#define SAX_TICKER_H

#include <functional>
#include <deque>

#include "Timer.h"

namespace sax {
	class Ticker {
		public:
			Ticker( std::function<void( double )> );
			~Ticker();
			double getFPS();
			void resume();
			void stop();
		private:
			bool running;
			std::function<void( double )> tickCallback;
			Timer fpsTimer;
			double lastFrameTime;
			std::deque<double> fpsSamples;
	};
}

#endif