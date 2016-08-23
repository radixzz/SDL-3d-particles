#ifndef SAX_TICKER_H
#define SAX_TICKER_H

#include <functional>
#include <memory>
#include <iostream>

#include "Timer.h"

namespace sax {
	
	class Ticker {
		public:
			Ticker( std::function<void( double )> );
			~Ticker();
			double getFPS();
			double getElapsedTime();
			void resume();
			void stop();
		private:
			enum { MAX_FPS_SAMPLES = 8 };
			bool running;
			std::function<void( double )> tickCallback;
			std::unique_ptr<Timer> fpsTimer;
			double lastFrameTime;
			Uint32 fpsIndex;
			double fpsSamples[ 50 ];
	};
}

#endif