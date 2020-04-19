#pragma once
#include "Graphics.h"
#include "Rec.h"
#include "Vec2.h"
#include "Surface.h"
#include <vector>
#include <string>

class Text
{
public:
	Text( std::wstring& text,Surface& font,unsigned char CharWidth,unsigned char CharHeight );
	void DrawText( const Vec2i& pos,Graphics& gfx ) const;
private:
	void CharMaping();
private:
	std::vector<RecI> car;
	std::wstring text;
	Surface font;
	unsigned char CharHeight;
	unsigned char CharWidth;
};