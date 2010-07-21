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

#ifndef CNATIONECONOMY_H
#define CNATIONECONOMY_H

#include "global.h"

/**
 * @section DESCRIPTION
 * Defines attributes for the a nation's overall economy during a timeperiod.
 */

class CNationEconomy
{
    public:
        /** Constructor. */
        CNationEconomy();
        /** Destructor. */
        virtual ~CNationEconomy();

        // Getters
        uint8_t TimePeriodTag( void )        { return mTimePeriodTag; }
        uint8_t EconomyTag( void )           { return mEconomyTag; }
        // Setters
        void    TimePeriodTag( uint8_t v )   { mTimePeriodTag = v; }
        void    EconomyTag( uint8_t v )      { mEconomyTag = v; }

    private:
        uint8_t mTimePeriodTag;
        uint8_t mEconomyTag;
};

typedef std::vector<CNationEconomy*> vec_natecon_t;

#endif // CNATIONECONOMY_H
