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

#include "cinformation.h"

CInformation::CInformation( CResources& resources, CManagerWindow& winmanager ) :
    mResources      (resources),
    mManagerwindow  (winmanager),
    mStrings        (resources.Data().Strings())
{
}

CInformation::~CInformation()
{
}

int8_t CInformation::Run( void )
{
    int8_t result = SIG_NONE;
    int8_t index, selection;
    bool quit = false;
    SDL_Rect rectMain = { 20, 20, 400, 400 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    if (result==SIG_NONE)
    {
        index = mManagerwindow.CreateNewWindow( rectMain,
                                                mStrings.Find( STR_INFORMATION )->Text(),
                                                &colrMainColor, NULL );

        while ( quit == false && result >= SIG_NONE )
        {
            selection = mManagerwindow.ActivateWindow( index );
            switch ( selection )
            {
                case 1:
                    quit = true;
                    result = SIG_NONE;
                    break;
                case 2:
                    result = PartyStatus();
                    break;
                case 3:
                    result = PersonalStatus();
                    break;
                case 4:
                    result = ShipLog();
                    break;
                case 5:
                    result = Maps();
                    break;
                case 6:
                    result = Towns();
                    break;
                case 7:
                    result = TakeSunSight();
                    break;
                case 8:
                    result = Search();
                    break;
                case 9:
                    result = SaveGame();
                    break;
                default:
                    Error( true, __FILE__, __LINE__, "menu index out of range\n" );
                    result = SIG_FAIL;
                    break;
            }

            if (result<SIG_NONE)
            {
                quit = true;
                result = SIG_FAIL;
            }
        }
        mManagerwindow.CloseWindow( index );
    }

    return result;
}

int8_t CInformation::PartyStatus( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    CRole& player = mResources.Data().Player();
    vec_string_t variables;
    std::string gold_count, crew_count;

    gold_count = i_to_a( player.Cargo().Gold().Count() );
    crew_count = i_to_a( player.Crew() );

    variables.clear();
    variables.resize( variables.size()+1, &gold_count );
    variables.resize( variables.size()+1, &crew_count );

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_INFO_PARTY )->Text(),
                                            variables,
                                            &colrMainColor, NULL );

    mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CInformation::PersonalStatus( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    CRole& player = mResources.Data().Player();
    vec_string_t variables;
    std::string gold_count, land_count;

    gold_count = i_to_a( player.CareerGold() );
    land_count = i_to_a( player.CareerLand() );

    variables.clear();
    variables.resize( variables.size()+1, &player.Name() );
    variables.resize( variables.size()+1, &gold_count );
    variables.resize( variables.size()+1, &land_count );

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_INFO_PERSONAL )->Text(),
                                            variables,
                                            &colrMainColor, NULL );

    mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CInformation::ShipLog( void )
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

int8_t CInformation::Maps( void )
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

#define TOWNS_PER_COLUMN 10
int8_t CInformation::Towns( void )
{
    int8_t result = SIG_NONE;
    int8_t index, selection;
    int16_t town_size, columns;
    uint16_t i, j, k;
    bool quit;
    SDL_Rect rectMain = { 10, 10, 750, 300 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    CManager<CTown>& towns = mResources.Data().Towns();
    vec_uint8_t indices;
    vec_string_t variables;
    std::string town_string;

    town_string = mStrings.Find( STR_INFO_TOWNS )->Text();

    // Calculate the number of vertical column lists needed
    columns = 0;
    town_size = towns.Size();
    do {
        columns++;
        town_size -= TOWNS_PER_COLUMN;
    } while ( town_size >= TOWNS_PER_COLUMN );

    if (town_size>0)
    {
        columns++;
    }

    indices.clear();
    variables.clear();
    for ( i=0; i<TOWNS_PER_COLUMN; i++ )
    {
        for ( j=0; j<columns; j++ )
        {
            k = i+(j*10);
            if ( k < towns.Size() )
            {
                if ( j>0 )
                {
                    town_string += "\\z";
                    town_string += "\\c" + i_to_a(j*13);
                }

                indices.resize( indices.size()+1, k );
                variables.resize( variables.size()+1, &towns.At(k)->Name() );
                town_string += "%" + i_to_a(variables.size());

                Log( " %d %s", k, towns.At(k)->Name().c_str() );
            }
        }
        town_string += "\\s";
        Log( " %d \n", j );
    }

    town_string += "Done\\s";

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            town_string,
                                            variables,
                                            &colrMainColor, NULL );

    quit = false;
    while ( quit == false && result >= SIG_NONE )
    {
        selection = mManagerwindow.ActivateWindow( index );

        if ( selection>0 && selection<=towns.Size() )
        {
            result = ShowTownStats( indices.at(selection-1) );
        }
        else
        {
            quit = true;
        }
    }

    mManagerwindow.CloseWindow( index );

    indices.clear();
    variables.clear();

    return result;
}

int8_t CInformation::ShowTownStats( uint16_t selection )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    vec_string_t variables;

    variables.clear();
    variables.resize( variables.size()+1, &mResources.Data().Towns().At(selection)->Name() );

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_INFO_TOWN )->Text(),
                                            variables,
                                            &colrMainColor, NULL );

    mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CInformation::TakeSunSight( void )
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

int8_t CInformation::Search( void )
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

int8_t CInformation::SaveGame( void )
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
