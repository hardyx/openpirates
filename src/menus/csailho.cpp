/***
 *  openPirates
 *  Copyright (C) 2010 Scott Smith
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "csailho.h"

CSailho::CSailho( CResources& resources, CManagerWindow& winmanager ) :
    mResources          (resources),
    mManagerwindow      (winmanager),
    mStrings            (mResources.Data().Strings())
{
}

CSailho::~CSailho()
{
}


int8_t CSailho::Run( void )
{
    int8_t result = SIG_NONE;
    int8_t state  = 1;
    bool done;
    bool hostile;
    SDL_Color colrBackColor = { 0, 0, 0x50, 0 };

    hostile = IsHostileShip();
    mManagerwindow.DrawBackgroundColor( colrBackColor );

    done = false;
    while ( done == false && result == SIG_NONE )
    {
        switch ( state )
        {
            case 1: // See a sail on the horizon
                result = SeeSail();
                if (result==2)                          // Sail away
                {
                    result = SAILHO_SAILAWAY;
                    done = true;
                }
                else                                    // Continue to check ship type
                {
                    result = SAILHO_NONE;
                }
                break;
            case 2: // See the ship type
                result = SeeShip();
                if (result==2 && hostile==false)        // Sail away
                {
                    result = SAILHO_SAILAWAY;
                    done = true;
                }
                else                                    // Continue to check ship colors
                {
                    result = SAILHO_NONE;
                }
                break;
            case 3: // See the colors of the ship
                result = SeeColors();
                if (result==1 && hostile==false)        // Hail for news
                {
                    result = SAILHO_NEWS;
                    done = true;
                }
                else if(result==2 && hostile==false)    // Sail away
                {
                    result = SAILHO_SAILAWAY;
                    done = true;
                }
                else                                    // Go to battle with ship
                {
                    result = SAILHO_BATTLE;
                    done = true;
                }
                break;
            default:
                Error( true, __FILE__, __LINE__, "state out of range\n" );
                result = SIG_FAIL;
                break;
        }
        state++;
    }

    return result;
}

int8_t CSailho::SeeSail( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_SAILHO_SAIL )->Text(),
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CSailho::SeeShip( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_SAILHO_SHIP )->Text(),
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CSailho::SeeColors( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_SAILHO_COLORS )->Text(),
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

bool CSailho::IsHostileShip( void )
{
    int8_t result = SIG_NONE;

    if (1)  // TODO hostile ship and more numbers
    {
        result = true;
    }
    else
    {
        result = false;
    }

    return result;
}

int8_t CSailho::P1EscapeDialog( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_SAILHO_P1ESCAPE )->Text(),
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CSailho::AIEscapeDialog( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_SAILHO_AIESCAPE )->Text(),
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CSailho::P1SunkDialog( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_SAILHO_P1SUNK )->Text(),
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CSailho::AISunkDialog( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_SAILHO_AISUNK )->Text(),
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CSailho::SunSetDialog( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_SAILHO_SUNSET )->Text(),
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}
