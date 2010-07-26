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

#ifndef CSPRITESTATIC_H
#define CSPRITESTATIC_H

#include "global.h"
#include "resources/types/cgraphic.h"
#include "sprites/cdraw.h"

/** @brief A simple sprite that does not move, but can be animated.
 */
class CSpriteStatic
{
	public:
        /** Constructor. */
		CSpriteStatic( void );
        /** Destructor. */
		virtual ~CSpriteStatic();

        // Getters
		int16_t         XPos( void )                const { return mXpos; }                       /**< Get X position (pixels). */
		int16_t         YPos( void )                const { return mYpos; }                       /**< Get Y position (pixels). */
        SDL_Rect& CollisionBox( void )                    { return mCollisionbox; }               /**< Get ref to collision box. */
        uint16_t        FrameRow( void )            const { return mFrame.row; }                  /**< Get frame row. */
        uint16_t        FrameColumn( void )         const { return mFrame.column; }               /**< Get frame column. */
        uint8_t         FrameSpeed( void )          const { return mFrame.speed; }                /**< Get frame speed. */
        uint8_t         FrameSpeedMax( void )       const { return mFrame.speedmax; }             /**< Get frame max speed. */
        SDL_Rect& ClipBox( void )                         { return mpGraphic->ClipBox(); }        /**< Get ref to slip box. */
        uint16_t        FrameCount( void )          const { return mpGraphic->FrameCount(); }     /**< Get frame total. */
        uint16_t        FrameWidth( void )          const { return mpGraphic->FrameWidth(); }     /**< Get frame width (pixels). */
        uint16_t        FrameHeight( void )         const { return mpGraphic->FrameHeight(); }    /**< Get frame height (pixels). */
        bool            GetRender( void )           const { return mRender; }                     /**< Get render state. */
        // Setters
		void        XPos( int16_t x )               { mXpos = x; mCollisionbox.x = mXpos + mXCollisionOffset; }         /**< Set X position (pixels). */
		void        YPos( int16_t y )               { mYpos = y; mCollisionbox.y = mYpos + mYCollisionOffset; }         /**< Set Y position (pixels). */
		void        OffsetXPos( int16_t offset )    { mXpos += offset; mCollisionbox.x = mXpos + mXCollisionOffset; }   /**< Offset X position (pixels). */
		void        OffsetYPos( int16_t offset )    { mYpos += offset; mCollisionbox.y = mYpos + mYCollisionOffset; }   /**< Offset Y position (pixels). */
        void        FrameSpeed( uint8_t speed )     { mFrame.speed = speed; }               /**< Set frame speed. */
        void        IncFrameSpeed( void )           { mFrame.speed++; }                     /**< Increment (by 1) frame speed. */
        void        DecFrameSpeed( void )           { mFrame.speed--; }                     /**< Decrement (by 1) frame speed. */
        void        FrameSpeedMax( uint8_t max )    { mFrame.speedmax = max; }              /**< Set frame max speed. */
        void        IncFrameSpeedMax( void )        { mFrame.speedmax++; }                  /**< Increment (by 1) frame max speed. */
        void        DecFrameSpeedMax( void )        { mFrame.speedmax--; }                  /**< Decrement (by 1) frame max speed. */
        void        SetRender( bool v )             { mRender = v; }                        /**< Set render state. */
        // Functions
        /** @brief Initalize and configure the sprite.
         * @param x : initial X position (pixels)
         * @param y : initial Y position (pixels)
         * @param anitype : the type of animation
         * @param frame_speed_max : the max speed allowed
         * @param divisor : decreases the collision area
         */
        virtual void Open( int16_t x, int16_t y, uint8_t anitype, uint8_t frame_speed_max, uint8_t divisor );

        /** @brief Reset the sprite.
         */
        void ResetFrame( void );

        /** @brief Select the a frame by row and column.
         * @param column : the frame column to select
         * @param row : the frame row select
         */
        void SetFrame( uint16_t column, uint16_t row );

        /** @brief Select the a frame by number.
         * @param frame : the frame to select
         */
        void SetFrame( uint16_t frame );

        /** @brief Select the next frame from the current frame.
         */
        void IncFrameCurrent( void );

        /** @brief Select the previous frame from the current frame.
         */
        void DecFrameCurrent( void );

        /** @brief Calculate if the referenced box has collided with the sprite collision box
         * @return true if collision occured else false
         */
        bool CheckRectCollision( const SDL_Rect& box );

        /** @brief Draw the sprite to the screen
         * @param screen : a pointer to the screen surface
         * @param camera : the camera size and position
         */
        void Draw( SDL_Surface* screen, SDL_Rect* camera = NULL );

        /** @brief Get the animation status
         * @return true if animation is enabled
         */
        bool IsAnimated( void );

        /** @brief Assign a new graphic to the sprite
         */
        void AssignGraphic( CGraphic* graphic );

    protected:
        CGraphic*   mpGraphic;          /**< Interface to the pixel data. */
        CDraw       mDraw;              /**< Interface to the basic pixel operations. */
        SDL_Rect    mCollisionbox;      /**< Defines space the sprite consumes for collision physics. */
        int16_t     mXpos, mYpos;       /**< The coordinates of the sprite in pixels. */
        int16_t     mXCollisionOffset;  /**< X offset of the sprite in pixels. */
        int16_t     mYCollisionOffset;  /**< Y offset of the sprite in pixels. */
        uint8_t     mDivisor;           /**< Decreases the size of the collision area. */
        uint8_t     mAnimationType;     /**< Type of animation the sprite should use. */
        bool        mRender;            /**< Draw the sprite to screen if true. */

        struct {
            uint16_t    column;     /**< Column of the current frame. */
            uint16_t    row;        /**< Row of the current frame. */
            uint8_t     speedmax;   /**< The fastest the frame can be animated. */
            uint8_t     speed;      /**< The speed the frame is animated. */
        } mFrame;                   /**< Current frame information. */

        /** @brief Perform sprite anitmation and drawing to screen.
         */
        virtual void Animate( void );

    private:
        CSpriteStatic(const CSpriteStatic&);
        CSpriteStatic& operator=(const CSpriteStatic&);
};

/** @brief A collection vector of static sprites
 */
typedef std::vector<CSpriteStatic*> vec_spritestatic_t;

#ifdef DEBUG
extern bool gDrawCollsionBox;
#endif

#endif // CSPRITESTATIC_H
