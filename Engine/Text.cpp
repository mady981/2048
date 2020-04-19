#include "Text.h"

Text::Text( std::wstring& text,Surface& font,unsigned char CharWidth,unsigned char CharHeight )
	:
	text( text ),
	font( font ),
	CharWidth( CharWidth ),
	CharHeight( CharHeight )
{
	CharMaping();
}

void Text::DrawText( const Vec2i& pos,Graphics& gfx ) const
{
	for ( int n = 0; n < car.size(); ++n )
	{
		gfx.DrawSprite( pos.x + n * CharWidth,pos.y,car[n],font );
	}
}

void Text::CharMaping()
{
	for ( unsigned char l = 0; l <= text.length(); ++l )
	{
		unsigned char y = ( unsigned char )text[l] / ( font.getWidht() / CharWidth );
		unsigned char x = ( unsigned char )text[l] % ( font.getWidht() / CharWidth );
		car.push_back( RecI( x * CharWidth,( x + 1 ) * CharWidth,y * CharHeight,( y + 1 ) * CharHeight ) );
	}
}
