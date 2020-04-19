/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include <assert.h>

Game::Game( MainWindow& wnd )
    :
    wnd( wnd ),
    gfx( wnd ),
    text( Surface( L"FontSheet16x18.bmp"))
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    //dir imputs
    if ( wnd.kbd.KeyIsPressed( VK_UP ) )
    {
        dir = { 0,-1 };
    }
    else if ( wnd.kbd.KeyIsPressed( VK_DOWN ) )
    {
        dir = { 0,1 };
    }
    else if ( wnd.kbd.KeyIsPressed( VK_LEFT ) )
    {
        dir = { -1,0 };
    }
    else if ( wnd.kbd.KeyIsPressed( VK_RIGHT ) )
    {
        dir = { 1,0 };
    }
    else
    {
        dir = { 0,0 };
        keypressed = false;
    }
    if ( dir != Vec2i( 0,0 ) && !keypressed )
    {
        pBrd->Move( dir );
        keypressed = true;
    }
    //new game button
    if ( newgame.isOverlappingWith( wnd.mouse.GetPos() ) && wnd.mouse.LeftIsPressed() && !mousepressed )
    {
        mousepressed = true;
        delete pBrd;
        pBrd = new Board;
    }
    const Mouse::Event e = wnd.mouse.Read();
    if ( e.GetType() == Mouse::Event::Type::LRelease )
    {
        mousepressed = false;
    }
}

void Game::ComposeFrame()
{
    pBrd->Draw( gfx,sc );
    if ( pBrd->getGameOver() )
    {
        sc.DrawGameOver( pBrd->getgridpos(),gfx );
    }
}
