#include "Text.h"

Text::Text( Surface& font )
	:
	font( font ),
	CharWidth( font.getWidht() / 32 ),
	CharHeight( font.getHeight() / 4 )
{
}

void Text::DrawText( const std::string& text,const Vec2i& pos,Graphics& gfx ) const
{
	for ( auto c : text )
	{
		gfx.DrawSprite( pos.x + c * CharWidth,pos.y + c * CharHeight,CharMaping( c ),font );
	}
}

RecI Text::CharMaping( char c ) const
{
	const char y = c / ( font.getWidht() / CharWidth );
	const char x = c % ( font.getWidht() / CharWidth );
	return RecI( x * CharWidth,( x + 1 ) * CharWidth,y * CharHeight,( y + 1 ) * CharHeight );
}
