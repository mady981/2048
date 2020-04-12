#include "Board.h"
#include <iterator>

Board::Board()
	:
	rng( std::random_device()() )
{
	AddTile();
	AddTile();
	AddTile();
	AddTile();
}

void Board::Move( const Vec2i& dir )
{
	for ( int i = 0; i < tiles.size(); ++i )
	{
		bool ok = true;
		while ( ok )
		{
			Vec2i next = tiles[i].nextpos( dir );
			for ( int n = 0; n < tiles.size(); ++n )
			{
				if ( next.x < 0 || next.x >= width || next.y < 0 || next.y >= height || next == tiles[n].getpos() )
				{
					if ( next == tiles[n].getpos() )
					{
						tiles.erase( tiles.begin() + n );
					}
					ok = false;
					break;
				}
			}
			if ( ok )
			{
				tiles[i].Move( dir );
			}
		}
	}
}

void Board::Draw( Graphics& gfx ) const
{
	for ( int i = 0; i < tiles.size(); ++i )
	{
		tiles[i].Draw( gfx,gridpos );
	}
}

void Board::DrawBoarder( Graphics& gfx ) const
{
	for ( int y = gridpos.y - 10; y < gridpos.y + height * TileSize + 10; ++y )
	{
		for ( int x = gridpos.x - 10; x < gridpos.x + width * TileSize + 10; ++x )
		{
			if ( !( x > gridpos.x && y > gridpos.y && x < gridpos.x + width * TileSize && y < gridpos.y + height * TileSize ) )
			{
				gfx.PutPixel( x,y,Colors::Green );
			}
		}
	}
}

void Board::AddTile()
{
	bool repeat = false;
	Vec2i rpos;
	int rval = 1;
	do
	{
		std::uniform_int_distribution<int> xDist( 0,width - 1 );
		std::uniform_int_distribution<int> yDist( 0,height - 1 );
		std::uniform_int_distribution<int> val( 0,3 );
		rpos = { xDist( rng ),yDist( rng ) };
		if ( val( rng ) == val.max() )
		{
			rval = 2;
		}
		for ( int i = 0; i < tiles.size(); ++i )
		{
			if ( rpos == tiles[i].getpos() )
			{
				repeat = true;
				break;
			}
			repeat = false;
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

void Board::Tile::Move( const Vec2i& dir )
{
	pos += dir;
}

void Board::Tile::Advance()
{
	++value;
}

void Board::Tile::Draw( Graphics& gfx,const Vec2i& gridpos ) const
{
	gfx.DrawRecDim( pos * TileSize + gridpos,TileSize,TileSize,Color( 128,128,value * 100 ) );
}

Vec2i Board::Tile::getpos() const
{
	return( pos );
}

Vec2i Board::Tile::nextpos( const Vec2i& dir ) const
{
	return Vec2i( pos + dir );
}
