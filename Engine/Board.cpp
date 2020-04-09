#include "Board.h"

Board::Board( std::random_device& rng )
	:
	rng( rng )
{
	std::uniform_int_distribution<int> xDist( 0,width );
	std::uniform_int_distribution<int> yDist( 0,height );
	tiles.push_back( tiles[1].setpos( Vec2i( xDist( rng ),yDist( rng ) ) ) );
}
