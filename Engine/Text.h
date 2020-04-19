#pragma once
#include "Graphics.h"
#include "Rec.h"
#include "Vec2.h"
#include "Surface.h"
#include <string>

class Text
{
public:
	Text( Surface& font );
	void DrawText( const std::string& text,const Vec2i& pos,Graphics& gfx ) const;
private:
	RecI CharMaping( char c ) const;
private:
	Surface font;
	const char CharHeight;
	const char CharWidth;
};