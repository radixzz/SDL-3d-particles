#ifndef SAX_POINT_H
#define SAX_POINT_H

namespace Sax {
	class Point {
		public:
			Point::Point( double x = 0.f, double y = 0.f );
			double x;
			double y;
	};
}

#endif