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

#include "ctavern.h"

CTavern::CTavern( CResources& resources, CManagerWindow& winmanager, CDyntown* dyntown ) :
    mResources      (resources),
    mStrings        (mResources.Data().Strings()),
    mManagerwindow  (winmanager),
    mpDynTown       (dyntown)
{
}

CTavern::~CTavern()
{
}

int8_t CTavern::Run( void )
{
    int8_t result = SIG_NONE;
    int8_t state  = 1;
    bool done;

    if (result==SIG_NONE)
    {
        done = false;
        while ( done == false && result == SIG_NONE )
        {
            switch ( state )
            {
                case 1:
                    result = Sailors();
                    break;
                case 2:
                    result = Traveler();
                    break;
                case 3:
                    result = TreasureMap();
                    break;
                case 4:
                    result = BartenderNews();
                    break;
                case 5:
                    done = true;
                    result = SIG_NONE;
                    break;
                default:
                    Error( true, __FILE__, __LINE__, "state out of range\n" );
                    result = SIG_FAIL;
                    break;
            }
            state++;
        }
    }

    return result;
}

int8_t CTavern::Sailors( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    uint8_t nation, curr_title;
    std::string sailors;
    vec_string_t variables;

    if ( mpDynTown->Sailors() > 0 )
    {
        sailors    = i_to_a( mpDynTown->Sailors() );
        nation     = mpDynTown->NationTag();
        curr_title = mResources.Data().Player().NationTitles().at(nation);

        variables.clear();
        variables.resize( variables.size()+1, mResources.Data().GetReputationName(mResources.Data().Player().OverallRep()) );
        variables.resize( variables.size()+1, &mResources.Data().Player().Name() );
        variables.resize( variables.size()+1, &mResources.Data().Titles().At(curr_title)->Text() );
        variables.resize( variables.size()+1, &sailors );

        index = mManagerwindow.CreateNewWindow( rectMain,
                                                mStrings.Find( STR_TAV_MEN )->Text(),
                                                variables,
                                                &colrMainColor, NULL );
        result = mManagerwindow.ActivateWindow( index );

        mManagerwindow.CloseWindow( index );

        if (result >= SIG_NONE)
        {
            mResources.Data().Player().Crew_Inc( mpDynTown->Sailors() );
            mpDynTown->Sailors(0);
        }
    }
    return result;
}

int8_t CTavern::Traveler( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    vec_string_t variables;

    if ( getProbability(PROB_TRAVELER) )
    {
        variables.clear();
        //variables.resize( variables.size()+1,  );     // Town name
        //variables.resize( variables.size()+1,  );     // Price

        index = mManagerwindow.CreateNewWindow( rectMain,
                                                mStrings.Find( STR_TAV_TRAVELER )->Text(),
                                                variables,
                                                &colrMainColor, NULL );
        mManagerwindow.ActivateWindow( index );

        mManagerwindow.CloseWindow( index );

        if (result >= SIG_NONE)
        {
            // Allow info to be viewable
        }
    }

    return result;
}

int8_t CTavern::TreasureMap( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    vec_string_t variables;

    if ( getProbability(PROB_TREASUREMAP) )
    {
        variables.clear();
        //variables.resize( variables.size()+1, TREASUREMAP_PRICE ) );

        index = mManagerwindow.CreateNewWindow( rectMain,
                                                mStrings.Find( STR_TAV_TREASUREMAP )->Text(),
                                                variables,
                                                &colrMainColor, NULL );
        mManagerwindow.ActivateWindow( index );

        mManagerwindow.CloseWindow( index );

        if (result >= SIG_NONE)
        {
            // Remove map block
        }
    }

    return result;
}

int8_t CTavern::BartenderNews( void )
{
    return 0;
}
