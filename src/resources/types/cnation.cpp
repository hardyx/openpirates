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

#include "cnation.h"

CNation::CNation() :
    mTag                (0),
    mAmnesty            (false),
    mName               (),
    mGraphicPath        (),
    mEconomySettings    (),
    mRelations          ()
{
}

CNation::~CNation()
{
    Log( " CNation %d econs to release\n", mEconomySettings.size() );
    if ( mEconomySettings.size() > 0 )
    {
        for ( int16_t i=mEconomySettings.size()-1; i>=0; i-- )
        {
            delete mEconomySettings.at(i);
        }
        mEconomySettings.clear();
    }
}

void CNation::SetRelations( uint8_t total )
{
    mRelations.clear();
    mRelations.resize( total, NATION_PEACE );
}
