#ifndef SAX_POINT_H
#define SAX_POINT_H

#include <memory>
#include <iostream>

namespace sax {
	class Point {
		public:
			Point( double x = 0, double y = 0 );
			double x;
			double y;
	};
}

#endif