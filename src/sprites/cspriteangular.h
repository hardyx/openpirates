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

#ifndef CSPRITEANGULAR_H
#define CSPRITEANGULAR_H

#include "sprites/cspritedynamic.h"

/** @brief A sprite that does move according to an angle and magnitude.
 */
class CSpriteAngular : public CSpriteDynamic
{
    public:
        /** Constructor. */
        CSpriteAngular();
        /** Destructor. */
        virtual ~CSpriteAngular();

        // Getters
        int16_t Angle( void )                   { return mAngle; }                      /**< Get angle (degrees). */
        int8_t  AngleVel( void )                { return mAngleVel; }                   /**< Get angle velocity. */
        int8_t  AngleMag( void )                { return mAngleMag; }                   /**< Get angle magnitude. */
        // Setters
        void    Angle( int16_t angle )          { mAngle = CheckAngle(angle); }         /**< Set angle (degrees). */
        void    AngleVel( int8_t anglevel )     { mAngleVel = anglevel; }               /**< Set angle velocity. */
        void    AngleMag( int8_t anglemag )     { mAngleMag = anglemag; }               /**< Set angle magnitude. */
        // Offset
        void    OffsetAngle( int16_t offset )   { mAngle = CheckAngle(mAngle+offset); } /**< Offset angle (degrees). */
        void    OffsetAngleVel( int8_t offset ) { mAngleVel += offset; }                /**< Offset angle velocity. */
        void    OffsetAngleMag( int8_t offset ) { mAngleMag += offset; }                /**< Offset angle magnitude. */
        // Functions
        /** @brief Initalize and configure the sprite.
         * @param x : initial X position (pixels)
         * @param y : initial Y position (pixels)
         * @param anitype : the type of animation
         * @param frame_speed_max : the max speed allowed
         * @param divisor : decreases the collision area
         * @param xvel : initial X velocity (pixels)
         * @param yvel : initial Y velocity (pixels)
         * @param player : is the sprite player controlled
         * @param collision_type : the type of tile collision
         * @param angle : initial angle position
         * @param anglevel : initial angle velocity
         * @param anglemag : initial angle magnitude
         */
        void Open( int16_t x, int16_t y, uint8_t anitype, uint8_t frame_speed_max, uint8_t divisor,
                   int16_t xvel, int16_t yvel, bool player, bool collision_type,
                   int16_t angle, int8_t anglevel, int8_t anglemag );

        /** @brief Move the sprite within the level dimensions and tiles
         * @param tiles : the collection of tiles to check against tile collisions
         * @param level_h : the vertical dimension of the level
         * @param level_w : the horizontal dimension of the level
         */
        virtual void Move( vec_spritestatic_t* tiles = NULL, uint16_t level_h = 0, uint16_t level_w = 0 );

        /** @brief Sets the frame of the sprite based on the anglel
         */
        void FrameByAngle( void );

    protected:
        int16_t mAngle;     /**< The angle (degrees). */
        int8_t  mAngleVel;  /**< The angle velocity. */
        int8_t  mAngleMag;  /**< The angle magnitude. */

        /** @brief Checks the angle for overflows and adjusts it
         */
        int16_t CheckAngle( int16_t angle );
        /** @brief Do frame animation and draw the result to the screen
         */
        virtual void Animate( void );
};

/** @brief A collection vector of angular sprites
 */
typedef std::vector<CSpriteAngular*> vec_spriteangular_t;

extern int16_t gSpriteAngleDirection[360][2];

#endif // CSPRITEANGULAR_H
