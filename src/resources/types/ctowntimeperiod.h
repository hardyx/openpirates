/**
 *  @section LICENSE
 *
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

#ifndef CTOWNTIMEPERIOD_H
#define CTOWNTIMEPERIOD_H

#include "global.h"

/**
 * @section DESCRIPTION
 * Defines a economy/nation for a town during the assigned timeperiod.
 */

class CTownTimePeriod
{
    public:
        /** Constructor. */
        CTownTimePeriod();
        /** Destructor. */
        virtual ~CTownTimePeriod();

        // Getters
        bool    Exists( void )              { return mExists; }
        uint8_t TimePeriodTag( void )       { return mTimePeriodTag; }
        uint8_t NationTag( void )           { return mNationTag; }
        uint8_t EconomyLevel( void )        { return mEconomyLevel; }
        // Setters
        void    Exists( bool v )            { mExists = v; }
        void    TimePeriodTag( uint8_t v )  { mTimePeriodTag = v; }
        void    NationTag( uint8_t v )      { mNationTag = v; }
        void    EconomyLevel( uint8_t v )   { mEconomyLevel = v; }

    private:
        bool    mExists;
        uint8_t mTimePeriodTag;
        uint8_t mNationTag;
        uint8_t mEconomyLevel;
};

typedef std::vector<CTownTimePeriod*> vec_towntimep_t;

#endif // CTOWNTIMEPERIOD_H
