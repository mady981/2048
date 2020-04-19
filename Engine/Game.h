/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Text.h"
#include <random>

class Game
{
private:
    enum class State
    {
        Menue,
        inGame
    };
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
private:
	MainWindow& wnd;
	Graphics gfx;
    SpriteCodex sc;
    Text text;
    Board* pBrd = nullptr;
    State currState = State::Menue;
    Vec2i dir = { 0,0 };
    bool keypressed = false;
    bool mousepressed = false;
    const RecI* pNewGame = nullptr;
    const RecI smallrec = RecI( gfx.ScreenWidth / 2 - ( ( 6 * 16 ) / 2 ),gfx.ScreenWidth / 2 + ( ( 6 * 16 ) / 2 ),190,200 + 18 );
    const RecI mediumrec = RecI( gfx.ScreenWidth / 2 - ( ( 7 * 16 ) / 2 ),gfx.ScreenWidth / 2 + ( ( 7 * 16 ) / 2 ),290,300 + 18 );
    const RecI largerec = RecI( gfx.ScreenWidth / 2 - ( ( 6 * 16 ) / 2 ),gfx.ScreenWidth / 2 + ( ( 6 * 16 ) / 2 ),390,400 + 18 );
};