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

#include "cvelocity.h"

CVelocity::CVelocity() :
    mAngle                  (0),
    mAngleMag               (0),
    mAngleMagMax            (0),
    mAngleMajorChangeMax    (0),
    mAngleMinorChangeMax    (0)
{
}

CVelocity::~CVelocity()
{
}

void CVelocity::Open( int16_t angle, int8_t anglemag, int8_t anglemagmax, int8_t angleminorchangemax )
{
    mAngle                  = angle;
    mAngleMag               = anglemag;
    mAngleMagMax            = anglemagmax;
    mAngleMajorChangeMax    = angleminorchangemax;
    mAngleMinorChangeMax    = 0;
                       // 000.0 022.5
                       // 045.0 067.5 090.0 112.5
                       // 135.0 157.5 180.0 202.5
                       // 225.0 247.5 270.0 292.5
                       // 315.0 337.5
                       /*
    mSails[SAIL_SQUARE] = { 10, 20,
                          30, 40, 50, 60,
                          70, 80, 90, 100,
                          70, 80, 90, 100,
                          10, 20 };
    mSails[SAIL_FOREAFT] = { 10, 20,
                          30, 40, 50, 60,
                          70, 80, 90, 100,
                          70, 80, 90, 100,
                          10, 20 };
                          */
}

void CVelocity::Simulate( void )
{
    uint8_t MajorProbability = 100;
    uint8_t MinorProbability = 50;
    uint8_t MagniProbability = 25;

    if ( getProbability(MajorProbability) )
    {
        mAngle = getRandomValue( 0, 359 );
    }

    if ( getProbability(MinorProbability) )
    {
        mAngle = getRandomValue( -mAngleMinorChangeMax, mAngleMinorChangeMax );
        mAngle = CheckAngle( mAngle );
    }

    if ( getProbability(MagniProbability) )
    {
        mAngleMag = getRandomValue( 0, mAngleMagMax );
    }
}

void CVelocity::Apply( CSpriteAngular* sprite, CShip* ship )
{
    int16_t ldelta = 0;
    int16_t rdelta = 0;

    int8_t  sprite_magnitude    = sprite->AngleMag();
    int16_t sprite_angle        = sprite->Angle();


}

int16_t CVelocity::CheckAngle( int16_t angle )
{
    if ( angle > 359 )
    {
        angle = angle - 360;
    }
    else if ( angle < 0 )
    {
        angle = 360 - -angle;
    }
    return angle;
}
