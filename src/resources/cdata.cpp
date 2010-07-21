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

#include "cdata.h"

CData::CData() :
    mDifficulties    (),
    mSkills          (),
    mSwords          (),
    mMoral           (),
    mStrings         ("Strings"),
    mGraphics        ("Graphics"),
    mSounds          ("Sounds"),
    mMaps            ("Maps"),
    mMonths          ("Months"),
    mReputations     ("Reputations"),
    mTitles          ("Titles"),
    mTimeperiods     ("Timeperiods"),
    mEconomies       ("Economies"),
    mNations         ("Nations"),
    mShips           ("Ships"),
    mTowns           ("Towns"),
    mRoles           ("Roles"),
    mTownsDynamic    ("TownsDynamic"),
    mEvents          (),
    mPlayer          ()
{
}

CData::~CData()
{
  	Log( "CData Released!\n" );
}

std::string* CData::GetReputationName( uint16_t value )
{
    int8_t index;

    for ( index=0; index<mReputations.Size(); index++ )
    {
        if ( value < mReputations.At(index)->Value() )
            return &mReputations.At(index)->Text();
    }
    return NULL;
}
