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

#include "crole.h"

CRole::CRole() :
    mTag            (0),
    mTimeperiod     (0),
    mNationality    (0),
    mOverallRep     (0),
    mFlagShip       (0),
    mSkill          (0),
    mDifficulty     (0),
    mHealth         (DEFAULT_HEALTH),
    mWounds         (0),
    mAge            (DEFAULT_AGE),
    mCrew           (0),
    mCareerLand     (0),
    mCareerGold     (0),
    mName           (),
    mType           (),
    mLocation       (),
    mDate           (),
    mCargo          (),
    mMapNormal      (),
    mMapFamily      (),
    mMapFortune     (),
    mShipLog        (),
    mNationTitles   (),
    mNationReps     (),
    mShips          (),
    mPrisoners      ()
{
}

CRole::~CRole()
{
}
