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
 *
 *  @section LOCATION
 */

#ifndef CDATE_H
#define CDATE_H

#include "global.h"

/** @brief A class that contains a date.
 */
class CDate
{
    public:
        /** Constructor. */
        CDate();
        /** Destructor. */
        virtual ~CDate();

        // Getters
        uint8_t     Day( void )     const { return mDay; }      /** Get the day of this date. */
        uint8_t     Month( void )   const { return mMonth; }    /** Get the month of this date. */
        uint16_t    Year( void )    const { return mYear; }     /** Get the year of this date. */
        // Setters
        void        Day( uint8_t v )    { mDay = v; }           /** Set the day of this date. */
        void        Month( uint8_t v )  { mMonth = v; }         /** Set the month of this date. */
        void        Year( uint16_t v )  { mYear = v; }          /** Set the year of this date. */

    private:
        uint8_t     mDay;                                       /** The day of this date. */
        uint8_t     mMonth;                                     /** The month of this date. */
        uint16_t    mYear;                                      /** The year of this date. */
};

#endif // CDATE_H
