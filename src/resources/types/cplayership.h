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

#ifndef CPLAYERSHIP_H
#define CPLAYERSHIP_H

#include "global.h"

/** @brief Defines attributes for the player's ship(s).
 */
class CPlayerShip
{
    public:
        /** Constructor. */
        CPlayerShip();
        /** Destructor. */
        virtual ~CPlayerShip();

        // Getters
        uint8_t Tag( void )         const { return mTag; }
        uint8_t Damage( void )      const { return mDamage; }
        // Setters
        void    Tag( uint8_t v )    { mTag = v; }
        void    Damage( uint8_t v ) { mDamage = v; }

    private:
        uint8_t mTag;
        uint8_t mDamage;
};

#endif // CPLAYERSHIP_H
