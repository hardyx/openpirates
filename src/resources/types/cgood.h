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

#ifndef CGOOD_H
#define CGOOD_H

#include "global.h"

/**
 * @section DESCRIPTION
 * Defines attributes for the a good.
 */

class CGood
{
    public:
        /** Constructor. */
        CGood();
        /** Destructor. */
        virtual ~CGood();

        // Getters
        uint32_t        Count( void )   { return mCount; }
        uint8_t         Price( void )   { return mPrice; }
        std::string&    Name( void )    { return mName; }
        std::string&    Unit( void )    { return mUnit; }
        // Setters
        void Count( uint32_t v )            { mCount = v; }
        void Price( uint8_t v )             { mPrice = v; }
        void Name( const std::string& v )   { mName = v; }
        void Unit( const std::string& v )   { mUnit = v; }
        // Inc
        void Count_Inc( uint32_t v )        { mCount += v; }
        void Price_Inc( uint8_t v )         { mPrice += v; }

    private:
        uint32_t    mCount;
        uint8_t     mPrice;
        std::string mName;
        std::string mUnit;
};

#endif // CGOOD_H
