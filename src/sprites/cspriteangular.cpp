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

#include "cspriteangular.h"

CSpriteAngular::CSpriteAngular() :
    mAngle      (0),
    mAngleVel   (0),
    mAngleMag   (0)
{
}

CSpriteAngular::~CSpriteAngular()
{
}

int16_t CSpriteAngular::CheckAngle( int16_t angle )
{
    if ( 359 < angle )
    {
        angle = angle - 360;
    }
    else if ( angle < 0 )
    {
        angle = 360 - -angle;
    }

    return angle;
}

void CSpriteAngular::Open( int16_t x, int16_t y, uint8_t anitype, uint8_t frame_speed_max, uint8_t divisor,
                           int16_t xvel, int16_t yvel, bool player, bool collision_type,
                           int16_t angle, int8_t anglevel, int8_t anglemag )
{
    CSpriteDynamic::Open( x, y, anitype, frame_speed_max, divisor, xvel, yvel, player, collision_type );

    mAngle      = angle;
    mAngleVel   = anglevel;
    mAngleMag   = anglemag;
}


void CSpriteAngular::Move( vec_spritestatic_t* tiles, uint16_t level_h, uint16_t level_w )
{
    // Calculate Angular velocity
    OffsetAngle( mAngleVel );
    OffsetXVelAccurate( mAngleMag * gSpriteAngleDirection[mAngle][0] );
    OffsetYVelAccurate( mAngleMag * gSpriteAngleDirection[mAngle][1] );

    MoveSprite( tiles, level_h, level_w );

    mYvel = 0;
    mXvel = 0;
}

void CSpriteAngular::Animate( void )
{
    int16_t deg_div_full, deg_div_half, angle1, angle2;
    int16_t frame_total;

    if ( SIG_NONE != VerifyPointer(__FILE__, __LINE__, mpGraphic) )
        return;

    frame_total = mpGraphic->FrameCount();

    // Frame Animation by Angle
    deg_div_full = 360/frame_total;    // deg / frame
    deg_div_half = deg_div_full/2;     // +/- frame range

    ResetFrame();
    if ( (mAngle > deg_div_half ) && (mAngle < 359-deg_div_half) )
    {
        for ( uint16_t index=0; index<frame_total; index++ )  // Determine the frame by the angle
        {
            angle1 = ((deg_div_full * index)-deg_div_half);
            angle2 = ((deg_div_full * index)+deg_div_half);
            if ( mAngle >= angle1 && mAngle <= angle2 )          // If the angle is bewtween the limts then select this frame
            {
                break;
            }
            IncFrameCurrent();
        }
    }
}
