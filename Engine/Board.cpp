#include "Board.h"

Board::Board( std::mt19937& rng )
	:
	rng( rng )
{
	AddTile( rng );
	AddTile( rng );
}

void Board::Draw( Graphics& gfx ) const
{
	for ( int n : tiles.size )
	{
		tiles[n].Draw( gfx );
	}
}

void Board::AddTile( std::mt19937& rng )
{
	bool repeat = true;
	Vec2i rpos;
	int rval;
	do
	{
		std::uniform_int_distribution<int> xDist( 0,width );
		std::uniform_int_distribution<int> yDist( 0,height );
		std::uniform_int_distribution<int> val( 1,2 );
		rpos = { xDist( rng ),yDist( rng ) };
		rval = val( rng );
		for ( int n : tiles.size )
		{
			if ( rpos != tiles[n].getpos() )
			{
				repeat = false;
			}
		}
	} while ( repeat );
	tiles.emplace_back( Tile( rpos,rval ) );
}

Board::Tile::Tile( const Vec2i& pos,const int val )
	:
	pos( pos ),
	value( val )
{
}

void Board::Tile::Advance()
{
	++value;
}

void Board::Tile::Draw( Graphics& gfx ) const
{
	gfx.DrawRec( RecI( pos.x,pos.x * TileSize,pos.y,pos.y * TileSize ),Color( 128,128,0 ) );
}

Vec2i Board::Tile::getpos() const
{
	return( pos );
}
