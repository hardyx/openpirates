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

#ifndef CSPRITEDYNAMIC_H
#define CSPRITEDYNAMIC_H

#include "sprites/cspritestatic.h"

/** @brief A sprite that does move according to vertical and horizontal directions.
 */
class CSpriteDynamic : public CSpriteStatic
{
	public:
        /** Constructor. */
        CSpriteDynamic();
        /** Destructor. */
        virtual ~CSpriteDynamic();

        // Getters
        int8_t          XVel( void )                    { return mXvel; }                               /**< Get X velocity (pixels). */
        int8_t          YVel( void )                    { return mYvel; }                               /**< Get Y velocity (pixels). */
        uint16_t        XVelAccurate( void )            { return mXvelscaled; }                         /**< Get X accurate velocity. */
        uint16_t        YVelAccurate( void )            { return mYvelscaled; }                         /**< Get Y accurate velocity. */
        bool            CollisionStatus( void )         { return mXtileCollision || mYtileCollision; }  /**< Get collision status, has the sprite collided. */
        const SDL_Rect& LastTileCollisionBox( void )    { return mLastCollisiontile; }                  /**< Get ref to last tile that was collided into. */
        // Setters
        void        XVel( int8_t xvel )             { mXvel = xvel; }                                   /**< Set X velocity (pixels). */
        void        YVel( int8_t yvel )             { mYvel = yvel; }                                   /**< Set Y velocity (pixels). */
        void        OffsetXVel( int8_t offset )     { mXvel += offset; }                                /**< Get X accurate velocity. */
        void        OffsetYVel( int8_t offset )     { mYvel += offset; }                                /**< Get Y accurate velocity. */
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
         */
        virtual void Open( int16_t x, int16_t y, uint8_t anitype, uint8_t frame_speed_max, uint8_t divisor,
                           int8_t xvel, int8_t yvel, bool player, bool collision_type );

        /** @brief Set the accurate X velocity to a value
         * @param xvel_scaled : the value to store
         */
        void        OffsetXVelAccurate( int16_t xvel_scaled );

        /** @brief Set the accurate Y velocity to a value
         * @param yvel_scaled : the value to store
         */
        void        OffsetYVelAccurate( int16_t yvel_scaled );

        /** @brief Store the dimensions for the last collided tile with the sprite
         * @param box : the reference to the tile box
         */
        void        LastTileCollisionBox( const SDL_Rect& box );

        /** @brief Move the sprite within the level dimensions and tiles
         * @param tiles : the collection of tiles to check against tile collisions
         * @param level_h : the vertical dimension of the level
         * @param level_w : the horizontal dimension of the level
         */
        virtual void Move( vec_spritestatic_t* tiles = NULL, uint16_t level_h = 0, uint16_t level_w = 0 );

    protected:
        int8_t      mXvel;                      /**< The X velocity (pixels). */
        int8_t      mYvel;                      /**< The Y velocity (pixels). */
        uint16_t    mXvelscaled;                /**< The X accurate velocity. */
        uint16_t    mYvelscaled;                /**< The Y accurate velocity. */
        bool        mPlayer;                    /**< Is this the sprite for the player. */
        bool        mXtileCollision;            /**< Is the sprite colliding with a tile in the X axis. */
        bool        mYtileCollision;            /**< Is the sprite colliding with a tile in the Y axis. */
        bool        mOutsideCollision;          /**< Is the sprite expected to collide. */
        SDL_Rect    mLastCollisiontile;         /**< The last tile collided with. */

        /** @brief Move the sprite within the level dimensions and tiles
         * @param tiles : the collection of tiles to check against tile collisions
         * @param level_h : the vertical dimension of the level
         * @param level_w : the horizontal dimension of the level
         */
        void MoveSprite( vec_spritestatic_t* tiles, uint16_t level_h, uint16_t level_w );

        /** @brief Keep sprite within the level bounds and setup for tile detections
         * @param axis : the axis to check collisions
         * @param tiles : the tiles to check
         * @param dimension : the limit on the axis (level size)
         */
        void DetectCollisions( uint8_t axis, vec_spritestatic_t* tiles, uint16_t dimension );

        /** @brief Detect if the tiles have collided on the specified axis
         * @param axis : the axis to check collisions
         * @param tiles : the tiles to check
         */
        int16_t CheckTileCollisions( uint8_t axis, vec_spritestatic_t* tiles );

        /** @brief Do frame animation and draw the result to the screen
         */
        virtual void Animate( void );
};

/** @brief A collection vector of dynamic sprites
 */
typedef std::vector<CSpriteDynamic*> vec_spritedynamic_t;

#endif // CSPRITEDYNAMIC_H
