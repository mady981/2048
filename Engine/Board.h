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
		Tile( const Vec2i& pos );
		void Move();
		void Draw();
		Vec2i getpos() const;
		Vec2i setpos( const Vec2i& val );
	private:
		Vec2_<int> pos;
	};
public:
	Board( std::random_device& rng );
	void Move();
	void Draw();
private:
	void AddTile();
private:
	static constexpr int TileSize = 128;
	static constexpr int width = 4;
	static constexpr int height = 4;
	int nTiles = 2;
private:
	std::random_device& rng;
	std::vector<Tile> tiles;
	bool istile[width * height] = { false };
};