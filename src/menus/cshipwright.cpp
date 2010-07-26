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

#include "cshipwright.h"

CShipwright::CShipwright( CResources& resources, CManagerWindow& winmanager ) :
    mResources      (resources),
    mManagerwindow  (winmanager),
    mStrings        (mResources.Data().Strings()),
    mShips          (0),
    mIndices        (0),
    mPrices         (0)
{
}

CShipwright::~CShipwright()
{
}

int8_t CShipwright::Run( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    bool done;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_SHP_OPTIONS )->Text(),
                                            &colrMainColor, NULL );

    done = false;
    while ( done == false && result == SIG_NONE )
    {
        result = mManagerwindow.ActivateWindow( index );
        switch ( result )
        {
            case 1:
                result = RepairShip();
                break;
            case 2:
                result = SellShip();
                break;
            case 3:
                done = true;
                result = SIG_NONE;
                break;
            default:
                Error( true, __FILE__, __LINE__, "state out of range\n" );
                result = SIG_FAIL;
                break;
        }
    }

    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CShipwright::RepairShip( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    uint8_t ship;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_SHP_REPAIR )->Text(),
                                            mShips,
                                            &colrMainColor, NULL );

    while( CheckRepairs() && result != SIG_FAIL  )
    {
        mManagerwindow.ReprocessWindow( index );

        result = mManagerwindow.ActivateWindow( index )-1;

        if (result<SIG_NONE)
        {
            Error( true, __FILE__, __LINE__, "CShipwright menu index out of range!\n" );
            result = SIG_FAIL;
        }
        else
        {
            ship = result;
            if( ship >= mShips.size() )
            {
                Error( true, __FILE__, __LINE__, "CShipwright ship index out of range!\n" );
                result = SIG_FAIL;
            }
            else
            {
                if( mResources.Data().Player().Cargo().Gold().Count() >= mPrices.at(ship) )
                {
                    mResources.Data().Player().Cargo().Gold_Inc( -mPrices.at(ship) );
                    mResources.Data().Player().Ships(mIndices.at(ship)).Damage(0);
                }
            }
        }
    }

    mManagerwindow.CloseWindow( index );
    ClearShips();

    return result;
}

bool CShipwright::CheckRepairs( void )
{
    bool result = false;
    CPlayerShip* ship;
    CShip*       shiptype;
    std::string* label;
    uint16_t     cost;

    ClearShips();
    for( int i=0; i < GAME_MAXSHIPS; i++ )
    {
        ship = &mResources.Data().Player().Ships(i);

        if( ship->Tag() > 0 && ship->Damage() > 0 )
        {
            shiptype = mResources.Data().Ships().At(ship->Tag());
            mIndices.resize( mShips.size()+1, i );

            label = new std::string( shiptype->Name() );
            cost = shiptype->Value() * (uint16_t)(ship->Damage() * 0.01);
            mPrices.resize( mPrices.size()+1, cost );
            label->append( " (" );
            label->append( i_to_a(cost) );
            label->append( " gold pieces)" );
            mShips.resize( mShips.size()+1, label );

            result = true;
        }
    }

    if( mShips.size() > 0 )
    {
        label = new std::string( "Done!" );
        mShips.resize( mShips.size()+1, label );
    }
    return result;
}

int8_t CShipwright::SellShip( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    uint8_t ship;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_SHP_SELL )->Text(),
                                            mShips,
                                            &colrMainColor, NULL );

    while( CheckSales() && result != SIG_FAIL  )
    {
        mManagerwindow.ReprocessWindow( index );

        result = mManagerwindow.ActivateWindow( index )-1;

        if (result<SIG_NONE)
        {
            Error( true, __FILE__, __LINE__, "menu index out of range\n" );
            result = SIG_FAIL;
        }
        else
        {
            ship = result;
            if( ship >= mShips.size()-1 )
            {
                Error( true, __FILE__, __LINE__, "menu index out of range\n" );
                result = SIG_FAIL;
            }
            else
            {
                mResources.Data().Player().Cargo().Gold_Inc( mPrices.at(ship) );
                mResources.Data().Player().Ships(mIndices.at(ship)).Tag(0);
            }
        }
    }

    mManagerwindow.CloseWindow( index );
    ClearShips();

    return result;
}

bool CShipwright::CheckSales( void )
{
    bool result = false;
    CPlayerShip* ship;
    CShip*       shiptype;
    std::string* label;
    uint16_t     cost;
    uint8_t      tag;

    ClearShips();
    for( int i=0; i < GAME_MAXSHIPS; i++ )
    {
        ship = &mResources.Data().Player().Ships(i);

        tag = ship->Tag();
        if( tag > 0 )
        {
            shiptype = mResources.Data().Ships().At(tag);
            mIndices.resize( mShips.size()+1, i );

            label = new std::string( shiptype->Name() );
            cost = shiptype->Value() - (shiptype->Value() * (uint16_t)(ship->Damage() * 0.01));
            mPrices.resize( mPrices.size()+1, cost );
            label->append( " (" );
            label->append( i_to_a(cost) );
            label->append( " gold pieces)" );
            mShips.resize( mShips.size()+1, label );

            if( mShips.size() > 1 )
            {
                result = true;
            }
        }
    }

    if( mShips.size() > 0 )
    {
        label = new std::string( "Done!" );
        mShips.resize( mShips.size()+1, label );
    }

    return result;
}

void CShipwright::ClearShips( void )
{
    mIndices.clear();
    mPrices.clear();

    for( uint8_t i=0; i<mShips.size(); i++ )
    {
        delete mShips.at(i);
    }
    mShips.clear();
}
