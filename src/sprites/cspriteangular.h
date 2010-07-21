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

#ifndef CSPRITEANGULAR_H
#define CSPRITEANGULAR_H

#include "sprites/cspritedynamic.h"

/**
 * @section DESCRIPTION
 * A sprite that does move according to an angle and magnitude.
 */

class CSpriteAngular : public CSpriteDynamic
{
    public:
        /** Constructor. */
        CSpriteAngular();
        /** Destructor. */
        virtual ~CSpriteAngular();

        // Getters
        int16_t Angle( void )                   { return mAngle; }
        int8_t  AngleVel( void )                { return mAngleVel; }
        int8_t  AngleMag( void )                { return mAngleMag; }
        // Setters
        void    Angle( int16_t angle )          { mAngle = CheckAngle(angle); }
        void    AngleVel( int8_t anglevel )     { mAngleVel = anglevel; }
        void    AngleMag( int8_t anglemag )     { mAngleMag = anglemag; }
        // Offset
        void    OffsetAngle( int16_t offset )   { mAngle = CheckAngle(mAngle+offset); }
        void    OffsetAngleVel( int8_t offset ) { mAngleVel += offset; }
        void    OffsetAngleMag( int8_t offset ) { mAngleMag += offset; }

        void Open( int16_t x, int16_t y, uint8_t anitype, uint8_t frame_speed_max, uint8_t divisor,
                   int16_t xvel, int16_t yvel, bool player, bool collision_type,
                   int16_t angle, int8_t anglevel, int8_t anglemag );
        virtual void Move( vec_spritestatic_t* tiles = NULL, uint16_t level_h = 0, uint16_t level_w = 0 );
        void FrameByAngle( void );

    protected:
        int16_t mAngle;
        int8_t  mAngleVel;
        int8_t  mAngleMag;

        int16_t CheckAngle( int16_t angle );
        virtual void Animate( void );
};

typedef std::vector<CSpriteAngular*> vec_spriteangular_t;

extern int16_t gSpriteAngleDirection[360][2];

#endif // CSPRITEANGULAR_H
