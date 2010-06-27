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

#ifndef CVELOCITY_H
#define CVELOCITY_H

#include "global.h"
#include "sprites/cspriteangular.h"
#include "resources/types/cship.h"

enum sails_t {
    SAIL_SQUARE=0   ,
    SAIL_FOREAFT
};

// This creates a randomly inc/dec velocity in a random inc/dec angle
class CVelocity
{
	public:
		CVelocity();
		virtual ~CVelocity();

        void    Angle( int16_t angle )      { mAngle = CheckAngle(angle); }
        int16_t Angle( void )               { return mAngle; }
        void    AngleMag( int8_t anglemag ) { mAngleMag = anglemag; }
        int8_t  AngleMag( void )            { return mAngleMag; }

        void Open( int16_t angle, int8_t anglemag, int8_t anglemagmax, int8_t angleminorchangemax );
		void Simulate( void );
		void Apply( CSpriteAngular* sprite, CShip* ship );

    private:
        int16_t mAngle;
        int8_t  mAngleMag;
        int8_t  mAngleMagMax;
        int8_t  mAngleMajorChangeMax;
        int8_t  mAngleMinorChangeMax;
        int16_t mSails[2][16];

        int16_t CheckAngle( int16_t angle );
};

#endif // CVELOCITY_H
