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

#ifndef CSPRITEDYNAMIC_H
#define CSPRITEDYNAMIC_H

#include "sprites/cspritestatic.h"

/**
 * @section DESCRIPTION
 * A sprite that does move according to vertical and horizontal directions.
 */

class CSpriteDynamic : public CSpriteStatic
{
	public:
        /** Constructor. */
        CSpriteDynamic();
        /** Destructor. */
        virtual ~CSpriteDynamic();

        // Getters
        int8_t          XVel( void )                    { return mXvel; }
        int8_t          YVel( void )                    { return mYvel; }
        uint16_t        XVelAccurate( void )            { return mXvelscaled; }
        uint16_t        YVelAccurate( void )            { return mYvelscaled; }
        bool            CollisionStatus( void )         { return mXtileCollision || mYtileCollision; }
        const SDL_Rect& LastTileCollisionBox( void )    { return mLastCollisiontile; }
        //Setters
        void        XVel( int8_t xvel )             { mXvel = xvel; }
        void        YVel( int8_t yvel )             { mYvel = yvel; }
        void        OffsetXVel( int8_t offset )     { mXvel += offset; }
        void        OffsetYVel( int8_t offset )     { mYvel += offset; }


        virtual void Open( int16_t x, int16_t y, uint8_t anitype, uint8_t frame_speed_max, uint8_t divisor,
                           int8_t xvel, int8_t yvel, bool player, bool collision_type );
        void        OffsetXVelAccurate( int16_t xvel_scaled );
        void        OffsetYVelAccurate( int16_t yvel_scaled );
        void        LastTileCollisionBox( const SDL_Rect& box );
        virtual void Move( vec_spritestatic_t* tiles = NULL, uint16_t level_h = 0, uint16_t level_w = 0 );

    protected:
        int8_t      mXvel, mYvel;               // Speed
        uint16_t    mXvelscaled, mYvelscaled;   // Accurate speed positioning
        bool        mPlayer;                    // Is this the sprite for the player
        bool        mXtileCollision;            // Is the sprite colliding with a tile in the X axis
        bool        mYtileCollision;            // Is the sprite colliding with a tile in the Y axis
        bool        mOutsideCollision;          // Is the sprite expected to collide
        SDL_Rect    mLastCollisiontile;         // The last tile collided with

        void MoveSprite( vec_spritestatic_t* tiles, uint16_t level_h, uint16_t level_w );
        void DetectCollisions( uint8_t axis, vec_spritestatic_t* tiles, uint16_t dimension );
        int16_t CheckTileCollisions( uint8_t axis, vec_spritestatic_t* tiles );
        virtual void Animate( void );
};

typedef std::vector<CSpriteDynamic*> vec_spritedynamic_t;

#endif // CSPRITEDYNAMIC_H
