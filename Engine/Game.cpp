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
#include <string>

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
    if ( currState == State::Menue )
    {
        //size selection
        if ( smallrec.isOverlappingWith( wnd.mouse.GetPos() ) )
        {
            //drawoutline
            if ( wnd.mouse.LeftIsPressed() )
            {
                pBrd = new Board( 4,4 );
                currState = State::inGame;
                pNewGame = new RecI( pBrd->getgridpos().x,pBrd->getgridpos().x + sc.getSPGameOver().getWidht(),
                    pBrd->getgridpos().y - 35,pBrd->getgridpos().y - 35 + sc.getSPGameOver().getHeight() );
                mousepressed = true;
            }
        }
        else if ( mediumrec.isOverlappingWith( wnd.mouse.GetPos() ) )
        {
            //drawoutline
            if ( wnd.mouse.LeftIsPressed() )
            {
                pBrd = new Board( 6,6 );
                currState = State::inGame;
                pNewGame = new RecI( pBrd->getgridpos().x,pBrd->getgridpos().x + sc.getSPGameOver().getWidht(),
                    pBrd->getgridpos().y - 35,pBrd->getgridpos().y - 35 + sc.getSPGameOver().getHeight() );
                mousepressed = true;
            }
        }
        else if ( largerec.isOverlappingWith( wnd.mouse.GetPos() ) )
        {
            //drawoutline
            if ( wnd.mouse.LeftIsPressed() )
            {
                pBrd = new Board( 8,8 );
                currState = State::inGame;
                pNewGame = new RecI( pBrd->getgridpos().x,pBrd->getgridpos().x + sc.getSPGameOver().getWidht(),
                    pBrd->getgridpos().y - 35,pBrd->getgridpos().y - 35 + sc.getSPGameOver().getHeight() );
                mousepressed = true;
            }
        }
    }
    else
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
        if ( pNewGame->isOverlappingWith( wnd.mouse.GetPos() ) && wnd.mouse.LeftIsPressed() && !mousepressed )
        {
            mousepressed = true;
            delete pBrd;
            delete pNewGame;
            currState = State::Menue;
        }
    }
    const Mouse::Event e = wnd.mouse.Read();
    if ( e.GetType() == Mouse::Event::Type::LRelease )
    {
        mousepressed = false;
    }
}

void Game::ComposeFrame()
{
    if ( currState == State::Menue )
    {
        text.DrawText( std::string( "Small" ),Vec2i( gfx.ScreenWidth / 2 - ( ( 5 * 16 ) / 2 ),200 ),gfx );
        text.DrawText( std::string( "Medium" ),Vec2i( gfx.ScreenWidth / 2 - ( ( 6 * 16 ) / 2 ),300 ),gfx );
        text.DrawText( std::string( "Large" ),Vec2i( gfx.ScreenWidth / 2 - ( ( 5 * 16 ) / 2 ),400 ),gfx );
    }
    else
    {
        pBrd->Draw( gfx,sc );
        if ( pBrd->getGameOver() )
        {
            sc.DrawGameOver( pBrd->getgridpos(),gfx );
        }
    }
}
