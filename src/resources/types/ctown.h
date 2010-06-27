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

#ifndef CTOWN_H
#define CTOWN_H

#include "global.h"
#include "resources/types/ctowntimeperiod.h"
#include "resources/types/cmaplocation.h"

class CTown
{
    public:
        CTown();
        virtual ~CTown();

        // Getters
        uint8_t             Tag( void )                 { return mTag; }
        std::string&        Name( void )                { return mName; }
        CTownTimePeriod&    TimePeriodDefault( void )   { return mTimePeriodDefault; }
        CMapLocation&       Location( void )            { return mLocation; }
        vec_towntimep_t&    TownTimePeriods( void )     { return mTownTimePeriods; }
        // Setters
        void Tag( uint8_t v )                               { mTag = v; }
        void Name( const std::string& v )                   { mName = v; }
        void TimePeriodDefault( const CTownTimePeriod& v )  { mTimePeriodDefault = v; }
        void Location( const CMapLocation& v )              { mLocation = v; }

    private:
        uint8_t         mTag;
        std::string     mName;
        CTownTimePeriod mTimePeriodDefault;
        CMapLocation    mLocation;
        vec_towntimep_t mTownTimePeriods;
};

#endif // CTOWN_H
