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

#include "cprisoner.h"

CPrisoner::CPrisoner() :
    mPirate         (false),
    mNation         (0),
    mTitle          (0),
    mName           (),
    mCaptureDate    ()
{
}

CPrisoner::~CPrisoner()
{
}

uint16_t CPrisoner::RewardReputation( void )
{
    return mTitle * PRISONER_FACTOR;
}

uint16_t CPrisoner::RewardRansom( const CDate& current_date )
{
    //return mTitle * PRISONER_FACTOR * mCaptureDate.DifferenceOfDays( current_date );
}
