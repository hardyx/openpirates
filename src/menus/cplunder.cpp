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

#include "cplunder.h"

CPlunder::CPlunder( CResources& resources, CManagerWindow& wmanager ) :
    mResources     (resources),
    mManagerwindow (wmanager),
    mStrings       (mResources.Data().Strings())
{
}

CPlunder::~CPlunder()
{
}

int8_t CPlunder::Run( void )
{
    int8_t result   = SIG_NONE;
    int8_t state    = 1;
    bool done;

    done = false;
    while ( done == false && result >= SIG_NONE )
    {
        switch ( state )
        {
            case 1:
                result = DividePlunder();
                break;
            case 2:
                result = RefitOrRetire();
                if (result==RETIRE)
                {
                    result = VerifyRetire();
                }
                break;
            case 3:
                done = true;
                result = SIG_NONE;
                break;
            default:
                Error( __FILE__, __LINE__, "menu index out of range\n" );
                result = SIG_FAIL;
                break;
        }
        state++;
    }
    return result;
}

int8_t CPlunder::DividePlunder( void )
{
    int8_t result   = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    CRole& player = mResources.Data().Player();
    vec_string_t variables;
    uint32_t percent, gold_total;
    uint32_t gold_patrons, gold_captain, gold_officers, gold_crew;
    std::string share_patrons, share_captain, share_officers, share_crew;

    gold_total = player.Cargo().Gold().Count();

    // Patron's share
    gold_patrons = PERCENTOF( PLUNDER_PATRONS, gold_total );
    share_patrons = i_to_a( gold_patrons );
    gold_total -= gold_patrons;

    // Captain's share
    switch (player.Difficulty())
    {
        case 0:
            percent = PLUNDER_DIFF1;
            break;
        case 1:
            percent = PLUNDER_DIFF2;
            break;
        case 2:
            percent = PLUNDER_DIFF3;
            break;
        case 3:
            percent = PLUNDER_DIFF4;
            break;
        default:
            percent = PLUNDER_DIFF1;
            break;
    }
    gold_captain = PERCENTOF( percent, gold_total );
    share_captain = i_to_a( gold_captain );
    gold_total -= gold_captain;

    // Officers share
    if (PLUNDER_OFFICERS != percent)
    {
        gold_officers = PERCENTOF( PLUNDER_OFFICERS-percent, gold_total );
        gold_total -= gold_officers;
        share_officers = i_to_a( gold_captain );
    }
    else
    {
        share_officers = "N/A";
    }

    // Crew share
    gold_crew = gold_total/player.Crew();
    share_crew = i_to_a( gold_crew );
    player.Cargo().Gold().Count(0);

    variables.clear();
    variables.resize( variables.size()+1, &share_captain );
    variables.resize( variables.size()+1, &share_patrons );
    variables.resize( variables.size()+1, &share_officers );
    variables.resize( variables.size()+1, &share_crew );

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_DIV_SHARES )->Text(),
                                            variables,
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CPlunder::RefitOrRetire( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    vec_string_t variables;
    std::string text;
    uint8_t diff;

    diff = mResources.Data().Player().Difficulty();

    variables.clear();
    variables.resize( variables.size()+1, mResources.Data().Difficulties().at(diff) );
    if ( diff<(STR_DIV_SHARES-1) )
    {
        variables.resize( variables.size()+1, mResources.Data().Difficulties().at(diff+1) );
        text = mStrings.Find( STR_DIV_REFIT1 )->Text();
    }
    else
    {
        text = mStrings.Find( STR_DIV_REFIT2 )->Text();
    }

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            text,
                                            variables,
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    if ( result == SIG_NONE )
    {
        result = REFIT;
        if ( diff<(STR_DIV_SHARES-1) )
        {
            if (result==1)
            {
                diff++;
            }
            else if (result==2)
            {
                result = RETIRE;
            }
        }
        else
        {
            if (result==1)
            {
                result = RETIRE;
            }
        }
    }

    return result;
}

bool CPlunder::VerifyRetire( void )
{
    if (mResources.Data().Player().Health()<HEALTH_CUTOFF)
        return true;
    else
        return false;
}
