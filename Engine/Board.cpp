#include "Board.h"

Board::Board( std::random_device& rng )
	:
	rng( rng )
{
	for ( int y = 0; y < Height; ++y )
	{
		for ( int x = 0; x < Width; ++x )
		{
			Tiles[y * Width + x] = RecI( x * TileSize,( x + 1 ) * TileSize,y * TileSize,( y + 1 ) * TileSize);
		}
	}
}

void Board::MoveTiles( const Vec2i& dir )
{
}

void Board::Draw( Graphics& gfx ) const
{
	for ( int i = 0; i < ( Width * Height ); ++i )
	{
		gfx.DrawRec( Tiles[i],Colors::Gray );
	}
}

void Board::SpawnTile( std::mt19937& rng )
{
}
