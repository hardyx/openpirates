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

#ifndef CDATE_H
#define CDATE_H

#include "global.h"

/**
 * @section DESCRIPTION
 * Simple class that holds a date.
 */

class CDate
{
    public:
        /** Constructor. */
        CDate();
        /** Destructor. */
        virtual ~CDate();

        // Getters
        uint8_t     Day( void )     { return mDay; }
        uint8_t     Month( void )   { return mMonth; }
        uint16_t    Year( void )    { return mYear; }
        // Setters
        void        Day( uint8_t v )    { mDay = v; }
        void        Month( uint8_t v )  { mMonth = v; }
        void        Year( uint16_t v )  { mYear = v; }

    private:
        uint8_t     mDay;
        uint8_t     mMonth;
        uint16_t    mYear;
};

#endif // CDATE_H
