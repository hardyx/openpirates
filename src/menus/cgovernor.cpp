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

#include "cgovernor.h"

CGovernor::CGovernor( CResources& resources, CManagerWindow& wmanager, CDyntown* dyntown ) :
    mResources      (resources),
    mStrings        (resources.Data().Strings()),
    mManagerwindow  (wmanager),
    mpDynTown       (dyntown)
{
}

CGovernor::~CGovernor()
{
}

int8_t CGovernor::Run( void )
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
                result = StateOfWar();
                break;
            case 2:
                result = Prisoner();
                break;
            case 3:
                result = Title();
                break;
            case 4:
                result = Daughter(); // TODO If the rep is bad then dont see
                break;
            case 5:
                done = true;
                result = SIG_NONE;
                break;
            default:
                Error( __FILE__, __LINE__, "state out of range\n" );
                result = SIG_FAIL;
                break;
        }
        state++;
    }

    return result;
}

int8_t CGovernor::StateOfWar( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    vec_string_t variables;

    CRole& player = mResources.Data().Player();
    uint8_t nation = mpDynTown->NationTag();
    uint8_t title_index = player.NationTitles().at(nation);
    std::string title, enemies, allies;

    enemies.clear();
    allies.clear();
    for (uint8_t t=0; t<mResources.Data().Nations().Size(); t++ )
    {
        switch (mResources.Data().Nations().At(nation)->Relations().at(t))
        {
            case NATION_WAR:
                enemies += mResources.Data().Nations().At(t)->Name() + ' ';
                break;
            case NATION_ALLIED:
                allies += mResources.Data().Nations().At(t)->Name()  + ' ';
                break;
            default:
                break;
        }
    }

    if (title_index<2)
    {
        title = "Mr.";
    }
    else
    {
        title = mResources.Data().Titles().At(title_index)->Text();
    }

    if (enemies.length() <= 0 )
    {
        enemies = "NONE";
    }

    if (allies.length() <= 0 )
    {
        allies = "NONE";
    }

    variables.clear();
    variables.resize( variables.size()+1, &title );
    variables.resize( variables.size()+1, &player.Name() );
    variables.resize( variables.size()+1, &enemies );
    variables.resize( variables.size()+1, &allies );

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_GOV_RELATIONS )->Text(),
                                            variables,
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CGovernor::Prisoner( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    CRole& player = mResources.Data().Player();
    vec_prisoner_t& prisoners = player.Prisoners();
    vec_prisoner_t::iterator iter;
    uint8_t total, curr_rep;
    uint16_t reward;

    total = prisoners.size();
    if ( total > 0 )
    {
        for ( iter = prisoners.begin(); iter != prisoners.end(); iter++ )
        {

            if ( iter->Nation() == mpDynTown->NationTag() &&
                 iter->Pirate() == true )
            {
                // Pirate and nation is hostile, goes towards reputation
                reward = iter->RewardReputation();

                index = mManagerwindow.CreateNewWindow( rectMain,
                                                        mStrings.Find( STR_GOV_PRISONER )->Text(),
                                                        &colrMainColor, NULL );
                result = mManagerwindow.ActivateWindow( index );
                mManagerwindow.CloseWindow( index );

                curr_rep = player.NationReps().at(mpDynTown->NationTag());
                player.NationReps().at(mpDynTown->NationTag()) = curr_rep+reward;
                prisoners.erase(iter);
            }
            else
            {
                // Pirate or hunter, nation is neutral, family offers ransom (Gold)
                reward = iter->RewardRansom( player.Date() );

                index = mManagerwindow.CreateNewWindow( rectMain,
                                                        mStrings.Find( STR_GOV_PRISONER )->Text(),
                                                        &colrMainColor, NULL );
                result = mManagerwindow.ActivateWindow( index );
                mManagerwindow.CloseWindow( index );

                // Accepted ransom
                if (result>SIG_NONE)
                {
                    player.Cargo().Gold_Inc( reward );
                    prisoners.erase(iter);
                }
                else
                {
                    Error( __FILE__, __LINE__, "menu index out of range\n" );
                    result = SIG_FAIL;
                }
            }
        }
    }

    return result;
}

int8_t CGovernor::Title( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    CRole& player = mResources.Data().Player();
    uint8_t nation, curr_title;
    uint16_t curr_level, next_level, delta, curr_land, land_reward;

    // Get the parameters
    nation      = mpDynTown->NationTag();
    curr_title  = player.NationTitles().at(nation);
    curr_level  = player.NationReps().at(nation);

    if ( curr_title < mResources.Data().Titles().Size() )
    {
        next_level = mResources.Data().Titles().At(curr_title+1)->Value();

        // Check to see if the rep has exceded the next limit
        if ( curr_level > next_level )
        {
            player.NationTitles().at(nation) = curr_title+1;
            player.NationReps().at(nation)   = next_level;   // Reset to the current exceded limit

            index = mManagerwindow.CreateNewWindow( rectMain,
                                                    mStrings.Find( STR_GOV_PROMOTE )->Text(),
                                                    &colrMainColor, NULL );
            result = mManagerwindow.ActivateWindow( index );
            mManagerwindow.CloseWindow( index );

            // Reward extra with land
            delta = curr_level - next_level;
            if ( delta > 0 )
            {
                curr_land   = player.CareerLand();
                land_reward = RewardLand(delta);
                player.CareerLand(curr_land+land_reward);

                index = mManagerwindow.CreateNewWindow( rectMain,
                                                        mStrings.Find( STR_GOV_LAND )->Text(),
                                                        &colrMainColor, NULL );
                mManagerwindow.ActivateWindow( index );
                mManagerwindow.CloseWindow( index );
            }
        }
    }
    else
    {

    }

    return result;
}

int8_t CGovernor::Daughter( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_GOV_DAUGHTER )->Text(),
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

uint16_t CGovernor::RewardLand( uint8_t reputation )
{
    //uint8_t rep_per_land;

    //rep_per_land = (uint8_t)(mValue * REP_PERCENT_LAND * 0.01);
    //return LAND_ACRE_UNIT * (reputation/rep_per_land);
    return 0;
}
