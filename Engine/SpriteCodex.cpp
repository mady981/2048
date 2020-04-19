#include "SpriteCodex.h"

SpriteCodex::SpriteCodex()
{
	sprite.push_back( Surface( L"2.bmp" ) );
	sprite.push_back( Surface( L"4.bmp" ) );
	sprite.push_back( Surface( L"8.bmp" ) );
	sprite.push_back( Surface( L"16.bmp" ) );
	sprite.push_back( Surface( L"32.bmp" ) );
	sprite.push_back( Surface( L"64.bmp" ) );
	sprite.push_back( Surface( L"128.bmp" ) );
	sprite.push_back( Surface( L"256.bmp" ) );
}

void SpriteCodex::DrawNumbers( const Vec2i& pos,const int num,Graphics& gfx ) const
{
	gfx.DrawSprite( pos.x,pos.y,sprite[num] );
}

void SpriteCodex::DrawGrid( const Vec2i& pos,Graphics& gfx ) const
{
	gfx.DrawSpriteNoChroma( pos.x,pos.y,grid );
}

void SpriteCodex::DrawNewGame( const Vec2i& pos,Graphics& gfx ) const
{
	gfx.DrawSprite( pos.x,pos.y,newgame );
}

void SpriteCodex::DrawGameOver( const Vec2i& gridpos,Graphics& gfx ) const
{
	gfx.DrawSprite( gridpos.x,gridpos.y,gameover );
}

Surface SpriteCodex::getSPGameOver() const
{
	return Surface( gameover );
}

Surface SpriteCodex::getSPGrid() const
{
	return Surface( grid );
}
