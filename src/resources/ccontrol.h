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

#ifndef CCONTROL_H
#define CCONTROL_H

#include "global.h"

#define CTRL_DEACTIVATED   0
#define CTRL_ACTIVATED     1

/**
 * @section DESCRIPTION
 * This class contains the event data from an SDL event.
 */

class CControl
{
    public:
        /** Constructor. */
        CControl();
        /** Destructor. */
        virtual ~CControl();

        // Getters
        uint8_t Type( void )    { return mType; }
        uint8_t State( void )   { return mState; }
        uint16_t X( void )      { return mX; }
        uint16_t Y( void )      { return mY; }
        // Setters
        void Type( uint8_t v )  { mType = v; }
        void State( uint8_t v ) { mState = v; }
        void X( uint16_t v )    { mX = v; }
        void Y( uint16_t v )    { mY = v; }

    private:
        uint8_t mType;
        uint8_t mState;
        uint16_t mX, mY;
};

#endif // CCONTROL_H
