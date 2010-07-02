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

#include "cmenutownout.h"

CMenutownout::CMenutownout( CResources& resources, CManagerWindow& winmanager ) :
    mResources      (resources),
    mScreen         (mResources.Screen()),
    mStrings        (mResources.Data().Strings()),
    mGraphics       (mResources.Data().Graphics()),
    mManagerwindow  (winmanager),
    mpDyntown       (NULL),
    mpTown          (NULL),
    mpMenutownin    (NULL),
    mEntertype      (0)
{
}

CMenutownout::~CMenutownout()
{
    Log( " CMenutownout Released!\n" );
}

int8_t CMenutownout::Run( int8_t entertype, int16_t town_index )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    vec_string_t variables;

    result = mManagerwindow.LoadResources( mResources.Font(),
                                           mGraphics.Find(GFX_BORDER),
                                           mGraphics.Find(GFX_POINTER) );

    if (result==SIG_NONE)
    {
        mEntertype      = entertype;
        mpDyntown       = mResources.Data().TownsDyn().At(town_index);
        mpTown          = mResources.Data().Towns().At( mpDyntown->DataTag() );
        mpMenutownin    = new CMenutownin( mResources, mManagerwindow, mpDyntown, mpTown );

        // Start with a dark blue background
        SDL_FillRect( mScreen.Image(), NULL, SDL_MapRGB( mScreen.Image()->format, 0x00, 0x00, 0x40 ) );

        variables.clear();
        variables.resize( variables.size()+1, &mpTown->Name() );
        if ( mEntertype == ENTER_BY_SEA )
        {
            index = mManagerwindow.CreateNewWindow( rectMain,
                                                    mStrings.Find( STR_TOWN_SEA )->Text(),
                                                    variables,
                                                    &colrMainColor, NULL );
        }
        else
        {
            index = mManagerwindow.CreateNewWindow( rectMain,
                                                    mStrings.Find( STR_TOWN_LAND )->Text(),
                                                    variables,
                                                    &colrMainColor, NULL );
        }

        result = mManagerwindow.ActivateWindow( index );

        if (result > SIG_NONE)
        {
            switch ( result )
            {
                case 1:
                    result = EnterTown();
                    break;
                case 2:
                    result = AttackTown();
                    break;
                case 3:
                    result = SneakTown();
                    break;
                case 4:
                    // Leave town
                    result = SIG_NONE;
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

        delete mpMenutownin;
    }

    return result;
}

int8_t CMenutownout::EnterTown( void )
{
    int8_t result = SIG_NONE;
    bool allowedin;
    uint8_t ship;

    allowedin = true;

    // Hostile town
    if ( 0 < mResources.Data().Player().NationReps().at( mpDyntown->NationTag() ) )
    {
        if ( 0 < mpDyntown->Forts() )
        {
            if ( mEntertype == ENTER_BY_SEA )
            {
                allowedin = false;
                ship = getRandomValue( 0, GAME_MAXSHIPS-1 );
                if ( mResources.Data().Player().Ships(ship).Tag() != 0 )
                {
                    // TODO blowup a ship
                }
                else
                {
                    // TODO Escaped with no damage
                }
            }
            else // By Land
            {
                allowedin = false;
                // TODO Fort fires (maybe lose some men?)
            }
        }
    }

    if (allowedin)
    {
        mpMenutownin->Run( false );
    }

    return result;
}

int8_t CMenutownout::AttackTown( void )
{
    int8_t result = SIG_NONE;

    if ( mEntertype == ENTER_BY_SEA )
    {
        // TODO Start sea battle mode
    }
    else
    {
        // TODO Start land battle mode
    }

    return result;
}

int8_t CMenutownout::SneakTown( void )
{
    int8_t result = SIG_NONE;
    // TODO add some logic, the richer the town the less likey you get in or face a guard

    mpMenutownin->Run( true );

    return result;
}
