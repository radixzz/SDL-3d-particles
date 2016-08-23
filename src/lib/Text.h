#ifndef SAX_TEXT_H
#define SAX_TEXT_H

#include <SDL_ttf.h>

#include "Sprite.h"
#include "Renderer.h"

namespace sax {
	class Text: public Sprite {
		public:
			Text( std::string fontName, int fontSize );
			~Text();
			void draw( Renderer* renderer );
			void setFontFamily( std::string fontName );
			void setFontSize( int size );
			void setText( std::string text );
			void setColor( SDL_Color color );
		private:
			void updateTexture( Renderer* renderer );
			void updateFont();
			std::string fontName;
			int fontSize;
			bool smooth;
			bool dirty;
			std::string text;
			SDL_Color color;
			TTF_Font* font;
			std::unique_ptr<Texture> texture;
	};
}

#endif
