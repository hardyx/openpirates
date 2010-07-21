/***
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

#include "cwind.h"

CWind::CWind() :
    mAngle                  (240),
    mAngleMag               (10),
    mAngleMagMax            (20),
    mAngleMajorChangeMax    (5),
    mAngleMinorChangeMax    (1)
{
}

CWind::~CWind()
{
}

void CWind::Open( int16_t angle, int8_t anglemag, int8_t anglemagmax, int8_t angleminorchangemax )
{
    mAngle                  = angle;
    mAngleMag               = anglemag;
    mAngleMagMax            = anglemagmax;
    mAngleMajorChangeMax    = angleminorchangemax;
    mAngleMinorChangeMax    = 0;
}

void CWind::Run( void )
{
    if ( getProbability(WIND_PROB_ANGLE_MAJOR) )
    {
        mAngle = getRandomValue( 0, 359 );
    }

    if ( getProbability(WIND_PROB_ANGLE_MINOR) )
    {
        mAngle = getRandomValue( -mAngleMinorChangeMax, mAngleMinorChangeMax );
        mAngle = CheckAngle( mAngle );
    }

    if ( getProbability(WIND_PROB_MAGNITUDE) )
    {
        mAngleMag = getRandomValue( 0, mAngleMagMax );
    }
}

void CWind::Apply( uint8_t sailtype, uint8_t speed_max, CSpriteAngular* sprite )
{
    int16_t sprite_angle, sail_effect, speed_effect;
    int8_t  angle_indexA, angle_indexB;
    int8_t  sprite_magnitude;

    // Get current angle
    sprite_angle        = sprite->Angle();
    sprite_magnitude    = sprite->AngleMag();

    // Determine sail effect
    for (angle_indexA=0; angle_indexA<SAIL_ANGLES-1; angle_indexA++)
    {
        if ( sprite_angle >= sail_angles[angle_indexA]  &&
             sprite_angle <= sail_angles[angle_indexA+1]   )
        {
            break;
        }
    }

    if (angle_indexA==SAIL_ANGLES-1)
    {
        angle_indexB = 0;
    }
    else
    {
        angle_indexB = angle_indexA+1;
    }

    sail_effect = sail_effects[sailtype][angle_indexA] + (  (sprite_angle-sail_angles[angle_indexA])
                                                          / (sail_angles[angle_indexB]-sail_angles[angle_indexA])
                                                          * (sail_effects[sailtype][angle_indexB]-sail_effects[sailtype][angle_indexA]) );

    // Determine the speed effect and the new angle magnitude
    speed_effect = (speed_max * sail_effect)/100;
    if ( sprite_magnitude < speed_effect )
    {
        sprite_magnitude++;
    }
    else if ( sprite_magnitude > speed_effect )
    {
        sprite_magnitude--;
    }

    sprite->AngleMag( sprite_magnitude );
}

int16_t CWind::CheckAngle( int16_t angle )
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

bool CWind::RotateClockwise( int16_t angle )
{
    bool result = false;

    if (angle < mAngle)
    {
        if (mAngle - angle < 180)
        {
            result = true;
        }
    }
    else if (angle > mAngle)
    {
        if (angle - mAngle < 180)
        {
            result = true;
        }
    }

    return result;
}

