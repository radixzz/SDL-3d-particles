#ifndef SAX_H
#define SAX_H

namespace sax {
	class Sax {
	public:
		static void initialize();
		static void release();
	private:
		static bool initted;
		static void initialize_sdl();
		static void initialize_image();
		static void initialize_ttf();
		Sax();
	};
	
}

#endif