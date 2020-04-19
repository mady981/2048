#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include "SpriteCodex.h"
#include <vector>
#include <random>

class Board
{
private:
	class Tile
	{
	public:
		Tile( const Vec2i& pos,const int val );
		void Move( const Vec2i& dir );
		void Advance();
		void Draw( const Vec2i& gridpos,Graphics& gfx,SpriteCodex& sc ) const;
	public:
		Vec2i getpos() const;
		Vec2i nextpos( const Vec2i& dir ) const;
		int getvalue() const;
	private:
		Vec2i pos;
		int value;
	};
public:
	Board( int width,int height );
	void Move( const Vec2i& dir );
	void Draw( Graphics& gfx,SpriteCodex& sc ) const;
private:
	void DrawBoarder( Graphics& gfx,SpriteCodex& sc ) const;
	void AddTile();
	bool CeckMovePossible() const;
public:
	bool getGameOver() const
	{
		return GameOver;
	}
	Vec2i getgridpos() const
	{
		return Vec2i( gridpos );
	}
	int getTileSize() const
	{
		return TileSize;
	}
	int getwidth() const
	{
		return width;
	}
	int getheight() const
	{
		return height;
	}
private:
	static constexpr int TileSize = 64;
	const int width;
	const int height;
	const Vec2i gridpos = Vec2i( Graphics::ScreenWidth / 2 - ( width / 2 * TileSize ),Graphics::ScreenHeight / 2 - ( height / 2 * TileSize ) );
	bool GameOver = false;
private:
	std::vector<Tile> tiles;
	std::mt19937 rng;
};