#include "Board.h"
#include <iterator>
#include <assert.h>

Board::Board()
	:
	rng( std::random_device()() )
{
	tiles.reserve( width * height );
	AddTile();
	AddTile();
}

void Board::Move( const Vec2i& dir )
{
	if ( tiles.size() == tiles.capacity() ? CeckMovePossible() : true )
	{
		std::vector<int> eras;
		if ( dir.x < 0 )
		{
			std::sort( tiles.begin(),tiles.end(),customSmallerx );
		}
		else if ( dir.y < 0 )
		{
			std::sort( tiles.begin(),tiles.end(),customSmallery );
		}
		else if ( dir.x > 0 )
		{
			std::sort( tiles.begin(),tiles.end(),customGreaterx );
		}
		else if ( dir.y > 0 )
		{
			std::sort( tiles.begin(),tiles.end(),customGreatery );
		}
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
						if ( next == tiles[n].getpos() && tiles[i].getvalue() == tiles[n].getvalue() )
						{
							tiles[n].Advance();
							eras.emplace_back( i );
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
		eras.shrink_to_fit();
		if ( eras.size() > 0 )
		{
			std::sort( eras.begin(),eras.end() );
			for ( size_t i = eras.size() - 1; i < eras.size(); --i )
			{
				tiles.erase( tiles.begin() + eras[i] );
			}
		}
		AddTile();
	}
}

void Board::Draw( Graphics& gfx,SpriteCodex& sc ) const
{
	for ( int i = 0; i < tiles.size(); ++i )
	{
		tiles[i].Draw( gridpos,gfx,sc );
	}
}

void Board::DrawBoarder( Graphics& gfx,SpriteCodex& sc ) const
{
	sc.DrawGrid( gridpos,gfx );
}

void Board::AddTile()
{
	if ( tiles.size() != tiles.capacity() )
	{
		bool repeat = false;
		Vec2i rpos;
		int rval = 0;
		do
		{
			std::uniform_int_distribution<int> xDist( 0,width - 1 );
			std::uniform_int_distribution<int> yDist( 0,height - 1 );
			std::uniform_int_distribution<int> val( 0,3 );
			rpos = { xDist( rng ),yDist( rng ) };
			if ( val( rng ) == val.max() )
			{
				rval = 1;
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
}

bool Board::CeckMovePossible() const
{
	bool MovePossible[4] = { false };
	std::vector<Vec2i> dir = { Vec2i( 0,-1 ),Vec2i( 0,1 ),Vec2i( -1,0 ),Vec2i( 1,0 ) };
	for ( int d = 0; d < dir.size(); ++d ) //diractions
	{
		for ( int t = 0; t < tiles.size(); ++t ) //tiles
		{
			Vec2i next = tiles[t].nextpos( { dir[d] } );
			for ( int n = 0; n < tiles.size(); ++n ) //other tiles
			{
				if ( tiles[t].getvalue() == tiles[n].getvalue() )
				{
					MovePossible[d] = true;
				}
			}
		}
	}
	if ( MovePossible == false )
	{
		return false;
	}
	return true;
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

void Board::Tile::Draw( const Vec2i& gridpos,Graphics& gfx,SpriteCodex& sc ) const
{
	sc.DrawNumbers( pos * TileSize + gridpos,value,gfx );
}

Vec2i Board::Tile::getpos() const
{
	return( pos );
}

Vec2i Board::Tile::nextpos( const Vec2i& dir ) const
{
	return Vec2i( pos + dir );
}

int Board::Tile::getvalue() const
{
	return value;
}