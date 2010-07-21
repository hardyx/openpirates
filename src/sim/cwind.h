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

#ifndef CWIND_H
#define CWIND_H

#include "global.h"
#include "sprites/cspriteangular.h"
#include "resources/types/cship.h"



enum sails_t {
    SAIL_SQUARE=0   ,
    SAIL_FOREAFT    ,
    SAIL_TOTAL
};


#define SAIL_ANGLES 16
const uint16_t sail_angles[SAIL_ANGLES] = {   0,  22,  45,  67,
                                             90, 112, 135, 157,
                                             80, 202, 225, 247,
                                            270, 292, 315, 337 };

const uint16_t sail_effects[SAIL_TOTAL][SAIL_ANGLES] = {{ 10,  20, 30, 40,        // SAIL_SQUARE
                                                          50,  60, 70, 80,
                                                          90, 100, 70, 80,
                                                          90, 100, 10, 20 },      // SAIL_FOREAFT
                                                        { 10,  20, 30, 40,
                                                          50,  60, 70, 80,
                                                          90, 100, 70, 80,
                                                          90, 100, 10, 20 }};

/**
 * @section DESCRIPTION
 * Simulates a wind (angle and magnitude) for navgation and ship battle modes.
 */

class CWind
{
	public:
        /** Constructor. */
		CWind();
        /** Destructor. */
		virtual ~CWind();

        void    Angle( int16_t angle )      { mAngle = CheckAngle(angle); }
        int16_t Angle( void )               { return mAngle; }
        void    AngleMag( int8_t anglemag ) { mAngleMag = anglemag; }
        int8_t  AngleMag( void )            { return mAngleMag; }

        void Open( int16_t angle, int8_t anglemag, int8_t anglemagmax, int8_t angleminorchangemax );
		void Run( void );
		void Apply( uint8_t sailtype, uint8_t speed_max, CSpriteAngular* sprite );
		bool RotateClockwise( int16_t angle );

    private:
        int16_t mAngle;
        int8_t  mAngleMag;
        int8_t  mAngleMagMax;
        int8_t  mAngleMajorChangeMax;
        int8_t  mAngleMinorChangeMax;

        int16_t CheckAngle( int16_t angle );
};

#endif // CWIND_H
