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

#include "cspritestatic.h"

CSpriteStatic::CSpriteStatic() :
    mpGraphic           (NULL),
    mDraw               (),
    mCollisionbox       (),
    mXpos               (0),
    mYpos               (0),
    mXCollisionOffset   (0),
    mYCollisionOffset   (0),
    mDivisor            (1),
    mAnimationType      (0),
    mRender             (true),
    mFrame              ()
{
}

CSpriteStatic::~CSpriteStatic()
{
}

void CSpriteStatic::Open( int16_t x, int16_t y, uint8_t anitype, uint8_t speedmax, uint8_t divisor )
{
    mXpos           = x;
    mYpos           = y;
    mAnimationType  = anitype;
    mFrame.speedmax = speedmax;
    mDivisor        = divisor;
}

void CSpriteStatic::SetFrame( uint16_t column, uint16_t row )
{
    if ( SIG_NONE != VerifyPointer(__FILE__, __LINE__, mpGraphic) )
        return;

    if ( column < mpGraphic->Columns() )
    {
        mFrame.column = column;
    }

    if ( row < mpGraphic->Rows() )
    {
        mFrame.row = row;
    }
    mFrame.speed = 0;
}

void CSpriteStatic::ResetFrame( void )
{
    mFrame.column   = 0;
    mFrame.row      = 0;
}

void CSpriteStatic::SetFrame( uint16_t frame )
{
    if ( SIG_NONE != VerifyPointer(__FILE__, __LINE__, mpGraphic) )
        return;

    ResetFrame();

    frame -= 1;
    mFrame.row    = frame / mpGraphic->Columns();
    mFrame.column = frame % mpGraphic->Columns();
    mFrame.speed = 0;
}

void CSpriteStatic::IncFrameCurrent( void )
{
    if ( SIG_NONE != VerifyPointer(__FILE__, __LINE__, mpGraphic) )
        return;

    mFrame.column++;
    if ( mFrame.column >= mpGraphic->Columns() )
    {
        mFrame.column = 0;

        if ( mAnimationType == ANI_CONT )
        {
            mFrame.row++;
            if ( mFrame.row >= mpGraphic->Rows() )
            {
                mFrame.row = 0;
            }
        }
    }
}

void CSpriteStatic::DecFrameCurrent( void )
{
    if ( SIG_NONE != VerifyPointer(__FILE__, __LINE__, mpGraphic) )
        return;

    mFrame.column--;
    if ( 0 >= mFrame.column )
    {
        mFrame.column = mpGraphic->Columns();

        if ( mAnimationType == ANI_CONT )
        {
            mFrame.row--;
            if ( 0 >= mFrame.row )
            {
                mFrame.row = mpGraphic->Rows();
            }
        }
    }
}

bool CSpriteStatic::CheckRectCollision( const SDL_Rect& box )
{
    // The sides of the SDL_Rects
    int16_t leftA, leftB;
    int16_t rightA, rightB;
    int16_t topA, topB;
    int16_t bottomA, bottomB;

    // Calculate the sides of rec mCollisionbox
    leftA   = mCollisionbox.x;
    rightA  = mCollisionbox.x + mCollisionbox.w;
    topA    = mCollisionbox.y;
    bottomA = mCollisionbox.y + mCollisionbox.h;

    // Calculate the sides of rec box
    leftB   = box.x;
    rightB  = box.x + box.w;
    topB    = box.y;
    bottomB = box.y + box.h;

    // If any of the sides from mCollisionbox are outside of box
    if ( bottomA <= topB ) return false;
    if ( topA >= bottomB ) return false;
    if ( rightA <= leftB ) return false;
    if ( leftA >= rightB ) return false;
    // If none of the sides from mCollisionbox are outside box
    return true;    // Collision has occured
}

void CSpriteStatic::Draw( SDL_Surface* screen, SDL_Rect* camera )
{
    if ( SIG_NONE != VerifyPointer(__FILE__, __LINE__, mpGraphic) )
        return;

#ifdef DEBUG
    SDL_Rect  box;
    SDL_Color color = { 0xFF, 0xFF, 0xFF, 0 };
#endif
    SDL_Rect& clipbox = mpGraphic->ClipBox();

    if ( 0 < mAnimationType ) Animate();

    clipbox.x = mFrame.column * clipbox.w;
    clipbox.y = mFrame.row * clipbox.h;

    if ( camera != NULL )    //If the camera is given, adjust coordinates to the camera
    {
        mpGraphic->ApplyImage( mXpos - camera->x, mYpos - camera->y, screen, &clipbox );

#ifdef DEBUG
        if (gDrawCollsionBox)
        {
            box = mCollisionbox;
            box.x = box.x - camera->x;
            box.y = box.y - camera->y;
            mDraw.Square( screen, &box, &color );

            // Clip box
            if ( 1<mDivisor )
            {
                box.w = clipbox.w;
                box.h = clipbox.h;
                box.x = mXpos - camera->x;
                box.y = mYpos - camera->y;
                mDraw.Square( screen, &box, &color );
            }
        }
#endif
    }
    else                    //Display at the current coordinates
    {
        mpGraphic->ApplyImage( mXpos, mYpos, screen, &clipbox );
#ifdef DEBUG
        if (gDrawCollsionBox)
        {
            mDraw.Square( screen, &mCollisionbox, &color );

            // Clip box
            if ( 1<mDivisor )
            {
                box.w = clipbox.w;
                box.h = clipbox.h;
                box.x = mXpos;
                box.y = mYpos;
                mDraw.Square( screen, &box, &color );
            }
        }
#endif
    }
}

void CSpriteStatic::AssignGraphic( CGraphic* graphic )
{
    if (graphic!=NULL)
    {
        mpGraphic = graphic;

        // Setup the collision box
        if ( 1 < mDivisor )
        {
            mCollisionbox.w = mpGraphic->FrameWidth()  / mDivisor;
            mCollisionbox.h = mpGraphic->FrameHeight() / mDivisor;
            mXCollisionOffset = (mpGraphic->FrameWidth()  - mCollisionbox.w) / 2;
            mYCollisionOffset = (mpGraphic->FrameHeight() - mCollisionbox.h) / 2;
            OffsetXPos(0);  // Refresh the coordinates
            OffsetYPos(0);
        }
        else
        {
            mCollisionbox.w = mpGraphic->FrameWidth();
            mCollisionbox.h = mpGraphic->FrameHeight();
        }
    }
}

void CSpriteStatic::Animate( void )
{
    if ( SIG_NONE != VerifyPointer(__FILE__, __LINE__, mpGraphic) )
        return;

    //Frame Animation
    if ( mAnimationType == ANI_CONT )
    {
        if ( mpGraphic->FrameCount() > 1 && mFrame.speed == mFrame.speedmax )        //Frames defined for script
        {
            mFrame.speed = 0;
            IncFrameCurrent();
        }
        else
        {
            mFrame.speed++;
        }
    }
}
