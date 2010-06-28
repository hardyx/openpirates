/*
    openPirates
    Copyright (C) 2010 Scott Smith

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "managers/cmanagerwindow.h"

CManagerWindow::CManagerWindow( CResources& resources ) :
    mResources  (resources),
    mEvents     (mResources.Controls()),
    mpBorder    (NULL),
    mpFont      (NULL),
    mPointer    (),
    mWindows    ()
{
    mWindows.clear();
}

CManagerWindow::~CManagerWindow()
{
    CloseWindows();
}

int8_t CManagerWindow::LoadResources( TTF_Font* font, CGraphic* border, CGraphic* pointer )
{
    int8_t result = SIG_NONE;

    if (font!=NULL)
    {
        mpFont = font;
    }
    else
    {
        Error( __FILE__, __LINE__, "CManagerWindow: could not create window\n" );
        result = SIG_FAIL;
    }

    if (border!=NULL)
    {
        mpBorder = border;
    }

    if (pointer!=NULL)
    {
        mPointer.Open( 0, 0, ANI_NONE, 0, 1, 0, 0, false, true );
        mPointer.AssignGraphic( pointer );
    }

    return result;
}

uint8_t CManagerWindow::CreateNewWindow( SDL_Rect& size,
                                         std::string& text,
                                         SDL_Color* bkgnd_color, CGraphic* bkgnd_image )
{
    // Create the window
    CWindow* window = new CWindow( size, mEvents, text, bkgnd_color, bkgnd_image );
    return AddWindow( window );
}

uint8_t CManagerWindow::CreateNewWindow( SDL_Rect& size,
                                         std::string& text,
                                         std::string& variable,
                                         SDL_Color* bkgnd_color, CGraphic* bkgnd_image )
{
    // Create the window
    CWindow* window = new CWindow( size, mEvents, text, variable, bkgnd_color, bkgnd_image );
    return AddWindow( window );
}

uint8_t CManagerWindow::CreateNewWindow( SDL_Rect& size,
                                         std::string& text,
                                         vec_string_t& variables,
                                         SDL_Color* bkgnd_color, CGraphic* bkgnd_image )
{
    // Create the window
    CWindow* window = new CWindow( size, mEvents, text, variables, bkgnd_color, bkgnd_image );
    return AddWindow( window );
}

int8_t CManagerWindow::AddWindow( CWindow* window )
{
    int8_t index, count;

    // Store the window
    if (window!=NULL)
    {
        count = mWindows.size();
        // Check for existing empty slots
        for ( index=0; index<count; index++ )
        {
            if (mWindows.at(index)==NULL)
            {
                mWindows.at(index) = window;
                Log( "CManagerWindow: Reusing empty window slot %d of %d\n", index+1, mWindows.size() );
                break;
            }
        }

        // Create a new slot if an empty one doesnt exist
        if (index>=count)
        {
            mWindows.resize( count+1, window );   // Store the window
            index = count;
            Log( "CManagerWindow: Adding window slot %d of %d\n", index+1, mWindows.size() );
        }
    }
    else
    {
        Error( __FILE__, __LINE__, "CManagerWindow: could not create window\n" );
        index = -1;
    }
    return index;   // Return a index reference
}

void CManagerWindow::CloseWindows( void )
{
    Log( "CManagerWindow %d Windows to release\n", mWindows.size() );

    if ( mWindows.size() > 0 )
    {
        for ( int8_t i=mWindows.size()-1; i>=0; i-- )
        {
            CloseWindow(i);
        }
        mWindows.clear();
    }
    Log( "...Windows released\n" );
}

void CManagerWindow::CloseWindow( uint8_t index )
{
    if (mWindows.at(index)!=NULL)
    {
        Log( "CManagerWindow: Releasing window slot %d of %d", index+1, mWindows.size() );
        delete mWindows.at(index);
        mWindows.at(index) = NULL;
    }
}

CWindow* CManagerWindow::GetWindow( uint8_t index )
{
    return mWindows.at(index);
}

uint8_t CManagerWindow::ActivateWindow( uint8_t index )
{
    int8_t result;

    if ( index <= mWindows.size()-1 )
    {
        result = mWindows.at(index)->Activate( mResources, mpBorder, mPointer, mpFont );
    }
    else
    {
        Error( __FILE__, __LINE__, "index out of range\n" );
        result = SIG_FAIL;
    }

    return result;
}

void CManagerWindow::ReprocessWindow( uint8_t index )
{
    mWindows.at(index)->Reprocess();
}

void CManagerWindow::UpdateWindowPosition( uint8_t index, int16_t x, int16_t y )
{
    mWindows.at(index)->UpdatePosition( x, y );
}

void CManagerWindow::UpdateWindowSize( uint8_t index, uint16_t w, uint16_t h )
{
    mWindows.at(index)->UpdateSize( w, h );
}

void CManagerWindow::UpdateWindowText( uint8_t index, std::string& text )
{
    mWindows.at(index)->UpdateText( text );
}

void CManagerWindow::UpdateWindowVariable( uint8_t index, std::string& variable )
{
    mWindows.at(index)->UpdateVariable( variable );
}

void CManagerWindow::UpdateWindowVariables( uint8_t index, vec_string_t& variables )
{
    mWindows.at(index)->UpdateVariables( variables );
}

void CManagerWindow::UpdateWindowBackgroundImage( uint8_t index, CGraphic* bkgnd_image )
{
    mWindows.at(index)->UpdateBackgroundImage( bkgnd_image );
}

void CManagerWindow::UpdateWindowBackGroundColor( uint8_t index, SDL_Color* bkgnd_color )
{
    mWindows.at(index)->UpdateBackgroundColor( bkgnd_color );
}
