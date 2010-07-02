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

#include "cmenumain.h"

CMenumain::CMenumain( CResources& resources, CManagerWindow& winmanager ) :
    mResources      (resources),
    mScreen         (mResources.Screen()),
    mPlayer         (mResources.Data().Player()),
    mStrings        (mResources.Data().Strings()),
    mGraphics       (mResources.Data().Graphics()),
    mManagerwindow  (winmanager)
{
}

CMenumain::~CMenumain()
{
    Log( "CMenumain Released!\n" );
}

int8_t CMenumain::Run( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 400, 110 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    result = mManagerwindow.LoadResources( mResources.Font(),
                                           mGraphics.Find(GFX_BORDER),
                                           mGraphics.Find(GFX_POINTER) );

    if (result==SIG_NONE)
    {
        // Start with a dark blue background
        //SDL_FillRect( mScreen.Image(), NULL, SDL_MapRGB( mScreen.Image()->format, 0x00, 0x00, 0x40 ) );

        index = mManagerwindow.CreateNewWindow( rectMain,
                                                mStrings.Find( STR_MAIN_MENU )->Text(),
                                                &colrMainColor, NULL );
        result = mManagerwindow.ActivateWindow( index );

        if (result>SIG_NONE)
        {
            switch ( result )
            {
                case 1:
                    result = EndGame();         // End career (back to start menu)
                    break;
                case 2:
                    result = SaveCareer();      // Save career
                    break;
                case 3:
                    result = LoadCareer();      // Load career
                    break;
                case 4:
                    result = SIG_NONE;          // Go back to game
                    break;
                case 5:
                    result = SIG_QUIT;          // Quit
                    break;
                default:
                    Error( __FILE__, __LINE__, "menu index out of range\n" );
                    result = SIG_FAIL;
                    break;
            }
        }
        else
        {
            Error( __FILE__, __LINE__, "menu index out of range\n" );
            result = SIG_FAIL;
        }
    }

    return result;
}

int8_t CMenumain::EndGame( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_MAIN_RESTART )->Text(),
                                            &colrMainColor, NULL );
    if( mManagerwindow.ActivateWindow( index ) == 1 )
    {
        result = SIG_END;
    }
    else
    {
        result = SIG_NONE;
    }
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CMenumain::SaveCareer( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_NOT_IMPLEMENTED )->Text(),
                                            &colrMainColor, NULL );
    mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CMenumain::LoadCareer( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_NOT_IMPLEMENTED )->Text(),
                                            &colrMainColor, NULL );
    mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}
