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

#include "cspritedynamic.h"

CSpriteDynamic::CSpriteDynamic() :
    CSpriteStatic       (),
    mXvel               (0),
    mYvel               (0),
    mXvelscaled         (0),
    mYvelscaled         (0),
    mPlayer             (false),
    mXtileCollision     (false),
    mYtileCollision     (false),
    mOutsideCollision   (true),
    mLastCollisiontile  ()
{
    mLastCollisiontile.x   = 0;
    mLastCollisiontile.y   = 0;
    mLastCollisiontile.w   = 0;
    mLastCollisiontile.h   = 0;
}

CSpriteDynamic::~CSpriteDynamic()
{
}

void CSpriteDynamic::Open( int16_t x, int16_t y, uint8_t anitype, uint8_t frame_speed_max, uint8_t divisor,
                           int8_t xvel, int8_t yvel, bool player, bool collision_type )
{
    CSpriteStatic::Open( x, y, anitype, frame_speed_max, divisor );

    mXvel               = xvel;
    mYvel               = yvel;
    mPlayer             = player;
    mOutsideCollision   = collision_type;
}

void CSpriteDynamic::OffsetXVelAccurate( int16_t xvel_scaled )
{
    uint16_t velocity_offset;

    velocity_offset = abs(xvel_scaled);

    if ( 0 < xvel_scaled )      //Positive
    {
        if ( velocity_offset >= 65535 - mXvelscaled )
        {
            mXvelscaled = velocity_offset - (65535 - mXvelscaled);
            OffsetXVel( 1 );
        }
        else
        {
            mXvelscaled += velocity_offset;
        }
    }
    else if ( 0 > xvel_scaled ) //Negative
    {
        if ( velocity_offset >= mXvelscaled )
        {
            mXvelscaled = 65535 - (velocity_offset - mXvelscaled);
            OffsetXVel( -1 );
        }
        else
        {
            mXvelscaled -= velocity_offset;
        }
    }
}

void CSpriteDynamic::OffsetYVelAccurate( int16_t yvel_scaled )
{
    uint16_t velocity_offset;

    velocity_offset = abs(yvel_scaled);

    if ( 0 < yvel_scaled )      //Positive
    {
        if ( velocity_offset >= 65535 - mYvelscaled )
        {
            mYvelscaled = velocity_offset - (65535 - mYvelscaled);
            OffsetYVel( 1 );
        }
        else
        {
            mYvelscaled += velocity_offset;
        }
    }
    else if ( 0 > yvel_scaled ) //Negative
    {
        if ( velocity_offset >= mYvelscaled )
        {
            mYvelscaled = 65535 - (velocity_offset - mYvelscaled);
            OffsetYVel( -1 );
        }
        else
        {
            mYvelscaled -= velocity_offset;
        }
    }
}

void CSpriteDynamic::LastTileCollisionBox( const SDL_Rect& box )
{
    mLastCollisiontile.x = box.x;
    mLastCollisiontile.y = box.y;
    mLastCollisiontile.w = box.w;
    mLastCollisiontile.h = box.h;
}

void CSpriteDynamic::Move( vec_spritestatic_t* tiles, uint16_t level_h, uint16_t level_w )
{
    // Move the sprite by the velocity
    MoveSprite( tiles, level_h, level_w );
}

void CSpriteDynamic::MoveSprite( vec_spritestatic_t* tiles, uint16_t level_h, uint16_t level_w )
{
    // Correct the position of the sprite, if it has crossed any boundaries
    mXtileCollision = false;
    mYtileCollision = false;

    if ( mYvel != 0 )
    {
        OffsetYPos( mYvel );
        if ( tiles != NULL) DetectCollisions( YAXIS, tiles, level_h );
    }

    if ( mXvel != 0 )
    {
        OffsetXPos( mXvel );
        if ( tiles != NULL) DetectCollisions( XAXIS, tiles, level_w );
    }
}

void CSpriteDynamic::DetectCollisions( uint8_t axis, vec_spritestatic_t* tiles, uint16_t dimension )
{
    int16_t new_xpos = 0;
    int16_t new_ypos = 0;

    if ( axis == YAXIS )
    {
        //Keep the figure in bounds
        if ( 0 > mCollisionbox.y )                          // Top
        {
            mYpos = -mYCollisionOffset;
        }
        else if ( mCollisionbox.y + mCollisionbox.h >= dimension )    // Bottom
        {
            mYpos = dimension - mCollisionbox.h - mYCollisionOffset;
        }
        else
        {
            new_ypos = CheckTileCollisions( YAXIS, tiles );   // Tiles
            if ( new_ypos != 0 )
            {
                mYpos = new_ypos;
            }
        }
    }
    else if ( axis == XAXIS )
    {
        //Keep the figure in bounds
        if ( 0 > mCollisionbox.x )                          // Left
        {
            mXpos = -mXCollisionOffset;
        }
        else if ( mCollisionbox.x + mCollisionbox.w >= dimension )    // Right
        {
            mXpos = dimension - mCollisionbox.w - mXCollisionOffset;
        }
        else
        {
            new_xpos = CheckTileCollisions( XAXIS, tiles );   // Tiles
            if ( new_xpos != 0 )
            {
                mXpos = new_xpos;
            }
        }
    }
}

int16_t CSpriteDynamic::CheckTileCollisions( uint8_t axis, vec_spritestatic_t* tiles )
{
    for ( uint16_t t=0; t<tiles->size(); t++ )
    {
        const SDL_Rect& tilecollsionbox = tiles->at(t)->CollisionBox();
        if ( CheckRectCollision( tilecollsionbox ) )
        {
            LastTileCollisionBox( tilecollsionbox );

            if ( axis == XAXIS )
            {
                mXtileCollision = true;

                if ( mOutsideCollision )  // Collision occured, force sprite back
                {
                    if ( mXvel > 0 )
                    {
                        return tilecollsionbox.x - mCollisionbox.w - mXCollisionOffset - 1;
                    }
                    else
                    {
                        return tilecollsionbox.x + tilecollsionbox.w - mXCollisionOffset;
                    }
                }
                else
                {
                    return 0;   // Inside mode, do nothing if sprite was detected to have collided
                }
            }
            else    // Yaxis
            {
                mYtileCollision = true;

                if ( mOutsideCollision )  // Collision occured, force sprite back
                {
                    if ( mYvel > 0 )
                    {
                        return tilecollsionbox.y - mCollisionbox.h - mYCollisionOffset;
                    }
                    else
                    {
                        return tilecollsionbox.y + tilecollsionbox.h - mYCollisionOffset;
                    }
                }
                else
                {
                    return 0;   // Inside mode, do nothing if sprite was detected to have collided
                }
            }
        }
        else
        {
            if ( axis == XAXIS )
            {
                mXtileCollision = false; // No collision for this tile
            }
            else
            {
                mYtileCollision = false; // No collision for this tile
            }
        }
    }

    // No collision's have occured, if inside mode move sprite back into tiles
    if ( !mOutsideCollision && (!mXtileCollision || !mYtileCollision) )
    {
#ifdef DEBUG
        Log( "Keeping Sprite Inside\n" );
#endif
        if ( axis == XAXIS )
        {
            return mXpos - mXvel;
        }
        else    // Yaxis
        {
            return mYpos - mYvel;
        }
    }
    return 0;
}


void CSpriteDynamic::Animate( void )
{
    uint8_t old_row, new_row;

    if ( SIG_NONE != VerifyPointer(__FILE__, __LINE__, mpGraphic) )
        return;

    if ( mAnimationType == ANI_CONT )
    {
        CSpriteStatic::Animate();
    }
    else if ( mAnimationType == ANI_BYROW )
    {
        //Frame Animation
        if ( 1 < mpGraphic->FrameCount() && FrameSpeed() == FrameSpeedMax() )        //Frames defined for script
        {
            new_row = 0;
            old_row = FrameRow();
            if ( 0 < mXvel )                 // If Sprite is moving right
            {
                new_row = 1;
            }
            else if ( 0 > mXvel )            // If Sprite is moving left
            {
                new_row = 2;
            }

            if ( 0 < mYvel )                 // If Sprite is moving down
            {
                new_row = 3;
            }
            else if ( 0 > mYvel )            // If Sprite is moving up
            {
                new_row = 4;
            }

            if ( mXvel == 0 && mYvel == 0 )  // The sprite is not moving
            {
                new_row = 0;
            }

            if ( old_row == new_row )
            {
                mFrame.speed = 0;
                IncFrameCurrent();
            }
            else
            {
                mFrame.speed = mFrame.speedmax;
                SetFrame( 0, new_row );
            }
        }
        else
        {
            IncFrameSpeed();
        }
    }
}
