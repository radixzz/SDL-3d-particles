#ifndef SAX_TICKER_H
#define SAX_TICKER_H

#include <functional>
#include <deque>

#include "Timer.h"

namespace Sax {
	class Ticker {
		public:
			Ticker( std::function<void( double )> );
			~Ticker();
			double getFPS();
			void resume();
			void stop();
		private:
			bool _running;
			std::function<void( double )> _tickCallback;
			Timer _fpsTimer;
			double _lastFrameTime;
			std::deque<double> _fpsSamples;
	};
}

#endif