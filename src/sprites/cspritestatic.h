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

#ifndef CSPRITESTATIC_H
#define CSPRITESTATIC_H

#include "global.h"
#include "resources/types/cgraphic.h"
#include "sprites/cdraw.h"

// Sprite that does not move, but can be animated
class CSpriteStatic
{
	public:
		CSpriteStatic( void );
		virtual ~CSpriteStatic();

        // Getters
		int16_t         XPos( void )                { return mXpos; }
		int16_t         YPos( void )                { return mYpos; }
        const SDL_Rect& CollisionBox( void )        { return mCollisionbox; }
        uint16_t        FrameRow( void )            { return mFrame.row; }
        uint16_t        FrameColumn( void )         { return mFrame.column; }
        uint8_t         FrameSpeed( void )          { return mFrame.speed; }
        uint8_t         FrameSpeedMax( void )       { return mFrame.speedmax; }
        const SDL_Rect& ClipBox( void )             { return mpGraphic->ClipBox(); }
        uint16_t        FrameCount( void )          { return mpGraphic->FrameCount(); }
        uint16_t        FrameWidth( void )          { return mpGraphic->FrameWidth(); }
        uint16_t        FrameHeight( void )         { return mpGraphic->FrameHeight(); }
        bool            GetRender( void )           { return mRender; }
        // Setters
		void        XPos( int16_t x )               { mXpos = x; mCollisionbox.x = mXpos + mXCollisionOffset; }
		void        YPos( int16_t y )               { mYpos = y; mCollisionbox.y = mYpos + mYCollisionOffset; }
		void        OffsetXPos( int16_t offset )    { mXpos += offset; mCollisionbox.x = mXpos + mXCollisionOffset; }
		void        OffsetYPos( int16_t offset )    { mYpos += offset; mCollisionbox.y = mYpos + mYCollisionOffset; }
        void        FrameSpeed( uint8_t speed )     { mFrame.speed = speed; }
        void        IncFrameSpeed( void )           { mFrame.speed++; }
        void        DecFrameSpeed( void )           { mFrame.speed--; }
        void        FrameSpeedMax( uint8_t max )    { mFrame.speedmax = max; }
        void        IncFrameSpeedMax( void )        { mFrame.speedmax++; }
        void        DecFrameSpeedMax( void )        { mFrame.speedmax--; }
        void        SetRender( bool v )             { mRender = v; }

        virtual void Open( int16_t x, int16_t y, uint8_t anitype, uint8_t speedmax, uint8_t divisor );
        void ResetFrame( void );
        void SetFrame( uint16_t column, uint16_t row );
        void SetFrame( uint16_t frame );
        void IncFrameCurrent( void );
        void DecFrameCurrent( void );
        bool CheckRectCollision( const SDL_Rect& box );
        void Draw( SDL_Surface* screen, SDL_Rect* camera = NULL );
        bool IsAnimated( void );
        void AssignGraphic( CGraphic* graphic );

    protected:
        CGraphic*   mpGraphic;
        CDraw       mDraw;
        SDL_Rect    mCollisionbox;  // Specifies area the sprite inhabits
        int16_t     mXpos, mYpos;   // Coordinates (protected so when changed the collision box is updated)
        int16_t     mXCollisionOffset, mYCollisionOffset;
        uint8_t     mDivisor;       // Decreases the size of the collision
        uint8_t     mAnimationType; // Type of animation the sprite should use
        bool        mRender;

        struct {
            uint16_t column;
            uint16_t row;
            uint8_t speedmax;
            uint8_t speed;
        } mFrame;

        virtual void Animate( void );

    private:
        CSpriteStatic(const CSpriteStatic &);
        CSpriteStatic & operator=(const CSpriteStatic&);
};

typedef std::vector<CSpriteStatic*> vec_spritestatic_t;

#ifdef DEBUG
extern bool gDrawCollsionBox;
#endif

#endif // CSPRITESTATIC_H
