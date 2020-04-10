#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include <vector>
#include <random>

class Board
{
private:
	class Tile
	{
	public:
		Tile( const Vec2i& pos,const int val );
		//void Move( const Vec2i& dir );
		void Advance();
		void Draw( Graphics& gfx,const Vec2i& gridpos ) const;
		Vec2i getpos() const;
	private:
		Vec2i pos;
		int value = 0;
	};
public:
	Board();
	//void Move( const Vec2i& dir );
	void Draw( Graphics& gfx ) const;
	void DrawBoarder( Graphics& gfx ) const;
	void AddTile();
private:
	static constexpr int TileSize = 64;
	static constexpr int width = 4;
	static constexpr int height = 4;
	const Vec2i gridpos = Vec2i( Graphics::ScreenWidth / 2 - 2 * TileSize,Graphics::ScreenHeight / 2 - 2 * TileSize );
private:
	std::vector<Tile> tiles;
	std::mt19937 rng;
};