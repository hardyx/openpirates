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

#include "cailogic.h"

CAILogic::CAILogic() :
    mDifficulty (DIFF_APPRENTICE)
{
    //ctor
}

CAILogic::~CAILogic()
{
    //dtor
}

int8_t CAILogic::Ship( CBattleShipStats* shipp1, CBattleShipStats* shipai,  uint16_t windangle, uint8_t difficulty )
{
    int8_t state = AI_NONE;
    float sailor_ratio;

    mDifficulty     = difficulty;
    sailor_ratio    = shipai->Sailors() / shipp1->Sailors();

    switch (shipai->AIType())
    {
        case AI_MERCHANT:
            if (mDifficulty>DIFF_JOURNEYMAN && sailor_ratio > 2 )
            {
                state = ShipAttack();
            }
            else
            {
                state = ShipRunAway();
            }
            break;
        case AI_HUNTER:
            if ( sailor_ratio < 0.3 && shipai->Damage() > 0 )
            {
                state = ShipRunAway();
            }
            else if ( sailor_ratio > 3 )
            {
                state = ShipRam();
            }
            else
            {
                state = ShipAttack();
            }
            break;
        case AI_PIRATE:
            if ( sailor_ratio < 0.5 && shipai->Damage() < 60 )
            {
                state = ShipRunAway();
            }
            else if ( sailor_ratio > 2 || shipp1->Damage() > 50 )
            {
                state = ShipRam();
            }
            else
            {
                state = ShipAttack();
            }
            break;
        default:
            // Error
            break;
    }
    return state;
}

int8_t CAILogic::ShipRunAway( void )
{
    int8_t state = AI_NONE;

    // run away
    if (mDifficulty>DIFF_JOURNEYMAN)
    {
        // run away at fastest direction
    }
    else
    {
        // run away at slow direction
    }

    return state;
}

int8_t CAILogic::ShipRam( void )
{
    int8_t state = AI_NONE;

    return state;
}

int8_t CAILogic::ShipAttack( void )
{
    int8_t state = AI_NONE;

    return state;
}
