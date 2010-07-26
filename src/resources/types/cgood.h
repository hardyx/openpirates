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

#ifndef CGOOD_H
#define CGOOD_H

#include "global.h"

/** @brief Defines attributes for the a good.
 */
class CGood
{
    public:
        /** Constructor. */
        CGood();
        /** Destructor. */
        virtual ~CGood();

        // Getters
        uint32_t        Count( void ) const { return mCount; }  /** Get the count. */
        uint8_t         Price( void ) const { return mPrice; }  /** Get the price. */
        std::string&    Name( void )        { return mName; }   /** Get refernce to the name string. */
        std::string&    Unit( void )        { return mUnit; }   /** Get refernce to the unit string. */
        // Setters
        void Count( uint32_t v )            { mCount = v; }     /** Set the count. */
        void Price( uint8_t v )             { mPrice = v; }     /** Set the price. */
        void Name( const std::string& v )   { mName = v; }      /** Set the name. */
        void Unit( const std::string& v )   { mUnit = v; }      /** Set the unit. */
         // Increment/Decrement
        void Count_Inc( uint32_t v )        { mCount += v; }    /** Increment/Decrement the count. */
        void Price_Inc( uint8_t v )         { mPrice += v; }    /** Increment/Decrement the price. */

    private:
        uint32_t    mCount; /** The count. */
        uint8_t     mPrice; /** The price. */
        std::string mName;  /** The name. */
        std::string mUnit;  /** The unit. */
};

#endif // CGOOD_H
