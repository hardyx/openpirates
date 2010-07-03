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

#include "cmodenav.h"

CModeNav::CModeNav( CResources& resources, CManagerWindow& winmanager, CMenumain& mainmenu ) :
    CModeWorld          (resources),
    tmrSimulate         (),
    mPlayership         (),
    mPlayercrew         (),
    mMenutownout        (mResources, winmanager),
    mMainmenu           (mainmenu),
    mPlayershipIndex    (-1),
    mPlayercrewIndex    (-1),
    mShipMode           (true),
    mCrewOutsideShip    (false),
    mInsideTown         (false),
    mAnchorPosition     ()
{
    mPlayershipIndex    = AddSprite(&mPlayership);
    mPlayercrewIndex    = AddSprite(&mPlayercrew);
    mPlayership.SetRender(true);
    mPlayercrew.SetRender(false);
    mFollowCameraIndex  = mPlayershipIndex;
    mFollowCameraType   = true;

    mAnchorPosition.x   = 0;
    mAnchorPosition.y   = 0;
    mAnchorPosition.w   = 0;
    mAnchorPosition.h   = 0;
}

CModeNav::~CModeNav()
{
    Log( "CModeNav Released!\n" );
}

int8_t CModeNav::Run( void )
{
    int8_t result = SIG_NONE;

    mPlayercrew.Open( 0, 0, ANI_BYROW, 60, 2,
                      0, 0, true, false );
    mPlayercrew.AssignGraphic( mResources.Data().Graphics().Find(GFX_NAVCREW) );
    mPlayership.Open( 0, 0, ANI_CONT, 0, 4,
                      0, 0, true, true,
                      0, 0, 1 );
    mPlayership.AssignGraphic( mResources.Data().Graphics().Find(18) );


    mPlayercrew.SetRender(false);
    mFollowCameraIndex  = mPlayershipIndex;
    mFollowCameraType   = true; // Angular
    mShipMode = true;
    mPlayership.XPos( 500 );
    mPlayership.YPos( 200 );
    mPlayership.Angle( 180 );

    result = InitWorld();

    tmrSimulate.start();
    while ( result == SIG_NONE )
    {
        // Check key & buttons to move objects
		result = HandleEvents();

		// Activate Wind Factor
		mWind.Simulate();
        //mpSim->Simulate());

		// Move sprites and check for collisions
		MovePlayer();
        MoveWorld();
#ifdef DEBUG
        Debug();
#endif
        // Draw everything
        DrawWorld();
    }
    return result;
}

int8_t CModeNav::HandleEvents( void )
{
    int8_t result = SIG_NONE;
    CControl event;

	/* Check for events */
	while ( mResources.Options().Controls().Poll(event) )
	{
		switch (event.State())
		{
			case CTRL_ACTIVATED:
                //Set the velocity
                switch ( event.Type() )
                {
                    case CTRL_QUIT:
                        result = SIG_FAIL;
                        break;
                    case CTRL_FULLSCREEN:
                        mResources.ToggleFullscreen();
                        break;
                    case CTRL_MENU:
                        result = mMainmenu.Run();
                        break;
                    case CTRL_UP:
                        PlayerVelocity( -DEF_P1_NAV_SPEED, YAXIS );
                        break;
                    case CTRL_DOWN:
                        PlayerVelocity( DEF_P1_NAV_SPEED, YAXIS );
                        break;
                    case CTRL_RIGHT:
                        PlayerVelocity( DEF_P1_NAV_SPEED, XAXIS );
                        break;
                    case CTRL_LEFT:
                        PlayerVelocity( -DEF_P1_NAV_SPEED, XAXIS );
                        break;
#ifdef DEBUG
                    case CTRL_DBG_BOXES:
                        gDrawCollsionBox = !gDrawCollsionBox;
                        break;
#endif
                    default:
                        break;
                }
				break;
			case CTRL_DEACTIVATED:
                //Set the velocity
                switch ( event.Type() )
                {
                    case CTRL_UP:
                        PlayerVelocity( 0, YAXIS );
                        break;
                    case CTRL_DOWN:
                        PlayerVelocity( 0, YAXIS );
                        break;
                    case CTRL_RIGHT:
                        PlayerVelocity( 0, XAXIS );
                        break;
                    case CTRL_LEFT:
                        PlayerVelocity( 0, XAXIS );
                        break;
                    default:
                        break;
                }
				break;
			default:
				break;
		}
	}
    return result;
}

void CModeNav::MovePlayer( void )
{
    int16_t level_w;
    int16_t level_h;
    const SDL_Rect& lasttile_collisionbox = mPlayership.LastTileCollisionBox();

    level_w = mTileCamera.TileW() * mTilewidth;
    level_h = mTileCamera.TileH() * mTileheight;

    if ( mShipMode == true )
    {
        //mWind.Apply( 1, mpPlayership );
        mPlayership.Move( &mTiles, level_h, level_w );
        CheckTownCollisions();

        if ( mPlayership.CollisionStatus() )
        {
            mPlayercrew.XPos( lasttile_collisionbox.x );
            mPlayercrew.YPos( lasttile_collisionbox.y );
            mCrewOutsideShip    = false;
            mShipMode           = false;
            mPlayercrew.SetRender(true);
            mFollowCameraIndex  = mPlayercrewIndex;
            mFollowCameraType   = false; // Dynamic

            PlayerVelocity( 0, XAXIS );
            PlayerVelocity( 0, YAXIS );
        }
    }
    else
    {
        mPlayercrew.Move( &mTiles, level_h, level_w );
        CheckTownCollisions();

        if ( mPlayercrew.CheckRectCollision( mPlayership.CollisionBox() ) )
        {
            if ( mCrewOutsideShip )
            {
                mPlayership.Angle( mPlayership.Angle() + 180 );
                mPlayercrew.SetRender(false);
                mShipMode           = true;
                mFollowCameraIndex  = mPlayershipIndex;
                mFollowCameraType   = true; // Angular

                PlayerVelocity( 0, XAXIS );
                PlayerVelocity( 0, YAXIS );
            }
        }
        else
        {
            mCrewOutsideShip    = true;
        }
    }
}

void CModeNav::PlayerVelocity( int16_t vel, uint8_t axis )
{
    if ( mShipMode == true )
    {
        if ( 0 == vel )
        {
            mPlayership.AngleVel( 0 );
        }
        else
        {
            mPlayership.OffsetAngleVel( vel );
        }
        mPlayership.XVel( 0 );
        mPlayership.YVel( 0 );
    }
    else
    {
        if ( 0 == vel )
        {
            if ( axis == XAXIS )
            {
                mPlayercrew.XVel( 0 );
            }
            else if ( axis == YAXIS )
            {
                mPlayercrew.YVel( 0 );
            }
        }
        else
        {
            if ( axis == XAXIS )
            {
                mPlayercrew.OffsetXVel( vel );
            }
            else if ( axis == YAXIS )
            {
                mPlayercrew.OffsetYVel( vel );
            }
        }
        mPlayership.AngleVel( 0 );
    }
}

void CModeNav::CheckTownCollisions( void )
{
    bool collision = false;

    for ( uint16_t t=0; t<mTowns.size(); t++ )
    {
        if ( mShipMode == true )
        {
            if ( mPlayership.CheckRectCollision( mTowns.at(t)->CollisionBox() ))
            {
                if ( !mInsideTown )
                {
                    mMenutownout.Run( ENTER_BY_SEA, mTownTags.at(t) );
                    PlayerVelocity( 0, XAXIS );
                    PlayerVelocity( 0, YAXIS );
                }
                collision = true;
                break;
            }
        }
        else
        {
            if ( mPlayercrew.CheckRectCollision( mTowns.at(t)->CollisionBox() ))
            {
                if ( !mInsideTown )
                {
                    mMenutownout.Run( ENTER_BY_LAND, mTownTags.at(t) );
                    PlayerVelocity( 0, XAXIS );
                    PlayerVelocity( 0, YAXIS );
                }
                collision = true;
                break;
            }
        }
    }

    if ( collision )
    {
        mInsideTown = true;
    }
    else
    {
        mInsideTown = false;
    }
}

#ifdef DEBUG
void CModeNav::Debug( void )
{
    #define SIZE 100
    char caption[SIZE];

    mDebugStrings.clear();

    // Draw Messages
    snprintf( caption, SIZE, "Ship X=%.3d Y=%.3d Angle=%.3d Col %d Row %d", mPlayership.XPos(),
                                                                            mPlayership.YPos(),
                                                                            mPlayership.Angle(),
                                                                            mPlayership.FrameColumn(),
                                                                            mPlayership.FrameRow() );
    mDebugStrings.resize( mDebugStrings.size()+1, caption );

    snprintf( caption, SIZE, "Crew X=%.3d Y=%.3d Col %d Row %d", mPlayercrew.XPos(),
                                                                 mPlayercrew.YPos(),
                                                                 mPlayercrew.FrameColumn(),
                                                                 mPlayercrew.FrameRow() );
    mDebugStrings.resize( mDebugStrings.size()+1, caption );

    snprintf( caption, SIZE, "Tile X=%.3d Y=%.3d W=%.3d H=%.3d PixelCamera X=%.3d Y=%.3d W=%.3d H=%.3d",mTileCamera.TileX(),
                                                                                                        mTileCamera.TileY(),
                                                                                                        mTileCamera.TileW(),
                                                                                                        mTileCamera.TileH(),
                                                                                                        mPixelCamera.x,
                                                                                                        mPixelCamera.y,
                                                                                                        mPixelCamera.w,
                                                                                                        mPixelCamera.h );
    mDebugStrings.resize( mDebugStrings.size()+1, caption );

    snprintf( caption, SIZE, "Wind Angle=%d Magnitude=%d", mWind.Angle(), mWind.AngleMag() );
    mDebugStrings.resize( mDebugStrings.size()+1, caption );
}
#endif
