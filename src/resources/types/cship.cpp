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

#include "resources/types/cship.h"

CShip::CShip() :
    mTag            (0),
    mCannon         (0),
    mSpeed          (0),
    mSailType       (0),
    mCrew           (0),
    mCargoSpace     (0),
    mHP             (0),
    mValue          (0),
    mName           (),
    mGraphicPath    (),
    mShipNations    ()
{
}

CShip::~CShip()
{
    Log( "    CShip %d shipnations to release\n", mShipNations.size() );
    if ( mShipNations.size() > 0 )
    {
        for ( int16_t i=mShipNations.size()-1; i>=0; i-- )
        {
            delete mShipNations.at(i);
        }
        mShipNations.clear();
    }
}
