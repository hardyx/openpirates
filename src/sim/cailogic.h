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

#ifndef CAILOGIC_H
#define CAILOGIC_H

#include "global.h"
#include "resources/types/cbattleshipstats.h"

/** @brief Computer AI and logic for battle/fencing modes.
 */
class CAILogic
{
    public:
        enum aitype_t {
            AI_MERCHANT=0   ,
            AI_HUNTER       ,
            AI_PIRATE
        };

        enum aicontrols_t {
            AI_NONE=0   ,
            AI_UP       ,
            AI_DOWN     ,
            AI_RIGHT    ,
            AI_LEFT     ,
            AI_FIRE
        };

        /** Constructor. */
        CAILogic();
        /** Destructor. */
        virtual ~CAILogic();

        int8_t Ship( CBattleShipStats* shipp1, CBattleShipStats* shipai,  uint16_t windangle, uint8_t difficulty );
        int8_t ShipRunAway( void ) const;
        int8_t ShipRam( void ) const;
        int8_t ShipAttack( void ) const;

    private:
        uint8_t mDifficulty;
};

#endif // CAILOGIC_H
