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
		void Move( const Vec2i& dir );
		void Advance();
		void Draw( Graphics& gfx) const;
		Vec2i getpos() const;
	private:
		Vec2i pos;
		int value = 0;
	};
public:
	Board( std::mt19937& rng );
	void Move( const Vec2i& dir );
	void Draw( Graphics& gfx ) const;
private:
	void AddTile( std::mt19937& rng );
private:
	static constexpr int TileSize = 128;
	static constexpr int width = 4;
	static constexpr int height = 4;
private:
	std::vector<Tile> tiles;
	std::mt19937& rng;
};