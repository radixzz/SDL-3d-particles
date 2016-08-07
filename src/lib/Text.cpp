#include <SDL_ttf.h>

#include "Text.h"
#include "Log.h"
#include "Utils.h"
#include "Resources.h"

namespace sax {
	
	Text::Text( std::string fontName, int _fontSize = 24 ) {
		setFontSize( _fontSize );
		setFontFamily( fontName );
		this->text = "";
		this->color = { 255, 255, 255, 255 };
		smooth = true;
		dirty = true;
	}

	Text::~Text() {
		TTF_CloseFont(font);
		font = nullptr;
	}

	void Text::setFontSize( int size ) {
		if (this->fontSize != size) {
			this->fontSize = size;
			dirty = true;
		}
	}

	void Text::setFontFamily( std::string fontName ) {
		if ( this->fontName != fontName ) {
			this->fontName = fontName;
			dirty = true;
		}
	}

	void Text::updateFont() {
		if ( font == nullptr ) {
			font = TTF_OpenFont( "res/fonts/Roboto-Medium.ttf", fontSize );
			if (font == nullptr) {
				Log::error( "TTF_OpenFont error:" + to_string( TTF_GetError() ) );
			}
		}
	}

	void Text::updateTexture( const RendererDescriptor* rendererDescriptor) {
		if ( dirty ) {
			dirty = false;
			if ( text.empty() )
				return;
			updateFont();
			SDL_Surface *surface = nullptr;
			if ( smooth ) {
				// Add bg color with TTF_RenderText_Shaded ?
				surface = TTF_RenderText_Blended( font, text.c_str(), color );
			}
			else {
				surface = TTF_RenderText_Solid( font, text.c_str(), color );
			}

			if (surface == nullptr) {
				Log::error( "Unable create surface render of text:" + to_string( TTF_GetError() ) );
			} else {
				texture->fromSurface( rendererDescriptor->renderer, surface );
			}

			SDL_FreeSurface(surface);
		}
	}

	void Text::draw( const RendererDescriptor* rendererDescriptor ) {
		
		updateTexture( rendererDescriptor );

		SDL_Rect rect = {
			int( position->x ),
			int( position->y ),
			texture->get_width(),
			texture->get_height()
		};

		texture->draw( rendererDescriptor->renderer, &rect, rotation, anchor.get() );
	}

	void Text::setText( std::string text ) {
		this->text = text;
		dirty = true;
	}

	void Text::setColor( SDL_Color color ) {
		this->color = color;
		dirty = true;
	}

}