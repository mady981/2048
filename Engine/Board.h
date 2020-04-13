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
		Vec2i getpos() const;
		Vec2i nextpos( const Vec2i& dir ) const;
		int getvalue() const;
	private:
		Vec2i pos;
		int value;
	};
public:
	Board();
	void Move( const Vec2i& dir );
	void Draw( Graphics& gfx,SpriteCodex& sc ) const;
	void DrawBoarder( Graphics& gfx,SpriteCodex& sc ) const;
	void AddTile();
private:
	bool CeckMovePossible() const;
private:
	static constexpr int TileSize = 64;
	static constexpr int width = 4;
	static constexpr int height = 4;
	const Vec2i gridpos = Vec2i( Graphics::ScreenWidth / 2 - 2 * TileSize,Graphics::ScreenHeight / 2 - 2 * TileSize );
private:
	std::vector<Tile> tiles;
	std::mt19937 rng;
private:
	struct
	{
		bool operator()( Tile a,Tile b )
		{
			return a.getpos().x > b.getpos().x;
		}
	} customGreaterx;
	struct
	{
		bool operator()( Tile a,Tile b )
		{
			return a.getpos().y > b.getpos().y;
		}
	} customGreatery;
	struct
	{
		bool operator()( Tile a,Tile b )
		{
			return a.getpos().x < b.getpos().x;
		}
	} customSmallerx;
	struct
	{
		bool operator()( Tile a,Tile b )
		{
			return a.getpos().y < b.getpos().y;
		}
	} customSmallery;
};