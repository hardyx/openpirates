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

#include "csailho.h"

CSailho::CSailho( CResources& resources, CManagerWindow& winmanager ) :
    mResources          (resources),
    mStrings            (mResources.Data().Strings()),
    mManagerwindow      (winmanager)
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

    done = false;
    while ( done == false && result == SIG_NONE )
    {
        switch ( state )
        {
            case 1:
                result = SeeSail();
                break;
            case 2:
                result = SeeShip();
                break;
            case 3:
                result = SeeColors();
                break;
            default:
                Error( __FILE__, __LINE__, "state out of range\n" );
                result = SIG_FAIL;
                break;
        }

        if ((state <= 2 && result==2) ||
            (state >= 3 && result==3)    )
        {
            result = SailAway(state);
            done = true;
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

int8_t CSailho::SailAway( int8_t state )
{
    int8_t result = SIG_NONE;

    switch (state)
    {
        case 1:
            result = SAILHO_SAILAWAY;
            break;
        case 2:
            if (1 /*pirate and more numbers*/)
            {
                result = SAILHO_BATTLE;
            }
            else
            {
                result = SAILHO_SAILAWAY;
            }
            break;
        case 3:
            if (1 /*pirate and more numbers*/)
            {
                result = SAILHO_BATTLE;
            }
            else
            {
                result = SAILHO_SAILAWAY;
            }
            break;
        default:
            break;
    }

    return result;
}
