#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include <random>

class Board
{
public:
	Board( std::random_device& rng );
	void MoveTiles( const Vec2i& dir );
	void Draw( Graphics& gfx ) const;
private:
	void SpawnTile( std::mt19937& rng );
private:
	static constexpr int TileSize = 128;
	static constexpr int Width = 4;
	static constexpr int Height = 4;
private:
	std::random_device& rng;
	RecI Tiles[Width * Height];
};