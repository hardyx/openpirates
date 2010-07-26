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

#include "cmodeworld.h"

CModeWorld::CModeWorld( CResources& resources ) :
    mResources      (resources),
    mWind           (),
    mTiles          (),
    mTowns          (),
    mTownTags       (),
#ifdef DEBUG
    mDebugStrings   (),
#endif
    mTileCamera     (),
    mPixelCamera    (),
    mFollowCameraIndex(-1),
    mFollowCameraType(true),
    mTilewidth      (0),
    mTileheight     (0),
    mScreen         (mResources.Screen()),
    mMaps           (mResources.Data().Maps()),
    mFrameControl   (),
    mWindcompass    (),
    mDraw           (),
#ifdef DEBUG
    mDebugMessage   (), // Graphic (temp for debug)
#endif
    mClouds         (),
    mWaves          (),
    mSpritesAng     (),
    mSpritesDyn     (),
    mSpritesSta     (),
    mLoopTime       (0),
    mLoopTimeAvg    (0),
    mFps            (0),
    mFskip          (0),
    mFpscap         (DEF_FRAME_LIMIT),
    mFpscalc        (DEF_FRAME_CALC)
{
}

CModeWorld::~CModeWorld()
{
    ClearMapTiles();
    ClearMapTowns();

    // Clouds
    Log( "CModeWorld %d Clouds to release", mClouds.size() );
    if ( mClouds.size() > 0 )
    {
        for ( int16_t i=mClouds.size()-1; i>=0; i-- )
        {
            delete mClouds.at(i);
        }
        mClouds.clear();
    }
    Log( " ...Done\n" );

    // Waves
    Log( "CModeWorld %d Waves to release", mWaves.size() );
    if ( mWaves.size() > 0 )
    {
        for ( int16_t i=mWaves.size()-1; i>=0; i-- )
        {
            delete mWaves.at(i);
        }
        mWaves.clear();
    }
    Log( " ...Done\n" );

    Log( "CModeWorld Released!\n" );
}

int16_t CModeWorld::AddSprite( CSpriteAngular* sprite )
{
    uint16_t size = mSpritesAng.size();
    mSpritesAng.resize( size+1, sprite );
    return size;
}

int16_t CModeWorld::AddSprite( CSpriteDynamic* sprite )
{
    uint16_t size = mSpritesDyn.size();
    mSpritesDyn.resize( size+1, sprite );
    return size;
}

int16_t CModeWorld::AddSprite( CSpriteStatic* sprite )
{
    uint16_t size = mSpritesSta.size();
    mSpritesSta.resize( size+1, sprite );
    return size;
}

int8_t CModeWorld::InitWorld( void )
{
    int8_t result = SIG_NONE;

    mWindcompass.Open( 0, 0, ANI_NONE, 0, 1 );
    mWindcompass.AssignGraphic( mResources.Data().Graphics().Find(GFX_NAVCOMPASS) );

    mWind.Open( 359, 5, 5, 5 );

    mTilewidth  = mResources.Data().Graphics().Find(GFX_NAVTILES)->FrameWidth();
    mTileheight = mResources.Data().Graphics().Find(GFX_NAVTILES)->FrameHeight();

    mTileCamera.TileX(0);
    mTileCamera.TileY(0);
    mTileCamera.TileW((mResources.Options().Screen().Width()  / mTilewidth) +TILE_CAMERA_OFFSET);
    mTileCamera.TileH((mResources.Options().Screen().Height() / mTileheight)+TILE_CAMERA_OFFSET);

    mPixelCamera.x = 0;
    mPixelCamera.y = 0;
    mPixelCamera.h = mResources.Options().Screen().Height();
    mPixelCamera.w = mResources.Options().Screen().Width();

	//Create Angle Tables
	for (int16_t a = 0; a < 360; a++)
	{
		gSpriteAngleDirection[a][0] =  (int16_t)(sin(a*M_PI/180) * 32767);	// X
		gSpriteAngleDirection[a][1] = -(int16_t)(cos(a*M_PI/180) * 32767);	// Y
	}

    RefreshMapTiles();
	result = LoadEffects();

    return result;
}

void CModeWorld::MoveWorld( void )
{
    MoveClouds();
    MoveCameras();
}

int8_t CModeWorld::DrawWorld( void )
{
    int8_t result = SIG_NONE;
    SDL_Surface* screen;

    if (mFrameControl.FrameSkip()==false)
    {
        screen = mScreen.Image();
        // Fill Background
        SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x00, 0x00, 0xFF ) );

        // Draw everything
        DrawWaves();
        DrawMapTiles();
        DrawMapTowns();
        DrawSprites();
        DrawClouds();
        DrawWindCompass();
#ifdef DEBUG
        DrawDebugMessages();
#endif

        // Update the screen
        if ( SDL_Flip( screen ) == -1 )
        {
            Error( true, __FILE__, __LINE__, "CModeWorld SDL_Flip failed\n" );
            result = SIG_FAIL;
        }
    }

    mFrameControl.ControlFPS( mFpscap, mFpscalc );
#ifdef DEBUG
    mFps            = mFrameControl.FramesDrawn();
    mFskip          = mFrameControl.FramesSkipped();
    mLoopTime       = mFrameControl.LoopTime();
    mLoopTimeAvg    = mFrameControl.LoopTimeAvg();
#endif

    return result;
}

int8_t CModeWorld::LoadEffects( void )
{
    int8_t result = SIG_NONE;
    CSpriteAngular* cloud   = NULL;
    CSpriteStatic*  wave    = NULL;

    if ( mResources.Options().Game().CloudCount() > 0 )
    {
        for ( uint16_t t=0; t<mResources.Options().Game().CloudCount(); t++ )
        {
            cloud = new CSpriteAngular();
            if (cloud!=NULL)
            {
                cloud->AssignGraphic( mResources.Data().Graphics().Find(GFX_NAVCLOUD) );
                cloud->Open( 0, 0, ANI_NONE, 5, 1,
                             0, 0, false, true,
                             0, 0, 0 );
                mClouds.resize( mClouds.size()+1, cloud );
            }
            else
            {
                Error( true, __FILE__, __LINE__, "null pointer\n" );
                return SIG_FAIL;
            }
        }
    }

    if ( mResources.Options().Game().WaveCount() > 0 )
    {
        for ( uint16_t t=0; t<mResources.Options().Game().WaveCount(); t++ )
        {
            wave = new CSpriteStatic();
            if (wave!=NULL)
            {
                wave->AssignGraphic( mResources.Data().Graphics().Find(GFX_NAVWAVE) );
                wave->Open( 0, 0, ANI_CONT, mResources.Options().Game().WaveSpeed(), 1 );
                mWaves.resize( mWaves.size()+1, wave );
            }
            else
            {
                Error( true, __FILE__, __LINE__, "null pointer\n" );
                return SIG_FAIL;
            }
        }
    }
    return result;
}

void CModeWorld::ClearMapTiles( void )
{
    if ( 0 < mTiles.size() )
    {
        for ( uint16_t t=0; t<mTiles.size(); t++ )
        {
            delete mTiles.at(t);
        }
    }
    mTiles.clear();
}

void CModeWorld::ClearMapTowns( void )
{
    if ( 0 < mTowns.size() )
    {
        for ( uint16_t t=0; t<mTowns.size(); t++ )
        {
            if ( mTowns.at(t) != NULL )
            {
                delete mTowns.at(t);
            }
        }
    }
    mTowns.clear();
    mTownTags.clear();
}

void CModeWorld::RefreshMapTiles( void )
{
    uint8_t tile_data;
    SDL_Rect pixel_pos;
    CMapLocation tile_pos;
    CSpriteStatic* tile;

    ClearMapTiles();
    for ( uint16_t t=0; t<mMaps.Size(); t++ )
    {
        if ( mMaps.At(t)->CheckMapCollision( mTileCamera ) )
        {
            pixel_pos.x  = 0;
            pixel_pos.y  = 0;
            tile_pos.TileW(1);
            tile_pos.TileH(1);
            for ( tile_pos.TileY(mTileCamera.TileY()); tile_pos.TileY()<mTileCamera.TileY()+mTileCamera.TileH(); tile_pos.OffsetY(1) )
            {
                for ( tile_pos.TileX(mTileCamera.TileX()); tile_pos.TileX()<mTileCamera.TileX()+mTileCamera.TileW(); tile_pos.OffsetX(1) )
                {
                    tile_data = mMaps.At(t)->TileAt(tile_pos.TileX(), tile_pos.TileY());
                    if ( tile_data != 0x00 && mMaps.At(t)->CheckMapCollision( tile_pos ) )
                    {
                        tile = new CSpriteStatic();
                        tile->AssignGraphic( mResources.Data().Graphics().Find(GFX_NAVTILES) );
                        tile->YPos( pixel_pos.y );
                        tile->XPos( pixel_pos.x );
                        tile->SetFrame( tile_data );
                        mTiles.resize( mTiles.size()+1, tile );
                    }
                    pixel_pos.x += mTilewidth;
                }
                pixel_pos.x = 0;
                pixel_pos.y += mTileheight;
            }
        }
    }
}

void CModeWorld::MoveClouds( void )
{
    for ( uint16_t t=0; t<mClouds.size(); t++ )
    {
        // Adjust cloud angles to approach the wind angle
        if ( abs(mClouds.at(t)->Angle()-mWind.Angle()) < DEF_CLOUD_ANGLE_CHG)
        {
            mClouds.at(t)->Angle(mWind.Angle());
        }
        else
        {
            if (mWind.RotateClockwise(mClouds.at(t)->Angle() == true) )
            {
                mClouds.at(t)->OffsetAngle( DEF_CLOUD_ANGLE_CHG );
            }
            else
            {
                mClouds.at(t)->OffsetAngle( -DEF_CLOUD_ANGLE_CHG );
            }
        }

        // Adjust cloud speed based on the wind speed
        if ( abs(mClouds.at(t)->AngleMag()-mWind.AngleMag()) < DEF_CLOUD_MAG_CHG)
        {
            mClouds.at(t)->AngleMag(mWind.AngleMag());
        }
        else
        {
            if (mClouds.at(t)->AngleMag() < mWind.AngleMag())
            {
                mClouds.at(t)->OffsetAngleMag( DEF_CLOUD_MAG_CHG );
            }
            else
            {
                mClouds.at(t)->OffsetAngleMag( -DEF_CLOUD_MAG_CHG );
            }
        }

        mClouds.at(t)->Move();
    }
}

void CModeWorld::MoveCameras( void )
{
    bool refresh = false;
    int16_t tile_offset = TILE_CAMERA_OFFSET/2;
    int16_t level_w;
    int16_t level_h;
    int16_t level_tile_w;
    int16_t level_tile_h;
    int16_t prev_pos, delta;
    int16_t follow_xpos, follow_ypos;
    int16_t size;

    follow_xpos = 0;
    follow_ypos = 0;
    size = mSpritesAng.size();
    if (mFollowCameraIndex>=0)
    {
        if (mFollowCameraType==true && mFollowCameraIndex < size)
        {
            follow_xpos = mSpritesAng.at(mFollowCameraIndex)->XPos()
                          +mSpritesAng.at(mFollowCameraIndex)->FrameWidth()/2;
            follow_ypos = mSpritesAng.at(mFollowCameraIndex)->YPos()
                          +mSpritesAng.at(mFollowCameraIndex)->FrameWidth()/2;
        }
        else if(mFollowCameraIndex < size)
        {
            follow_xpos = mSpritesDyn.at(mFollowCameraIndex)->XPos();
                          +mSpritesDyn.at(mFollowCameraIndex)->FrameWidth()/2;
            follow_ypos = mSpritesDyn.at(mFollowCameraIndex)->YPos();
                          +mSpritesDyn.at(mFollowCameraIndex)->FrameWidth()/2;
        }
    }

    // Entire size of the map in tiles
    level_tile_w = mResources.Options().Game().MapWidth();
    level_tile_h = mResources.Options().Game().MapHeight();

    // The size of the tile camera area in pixels
    level_w = mTileCamera.TileW() * mTilewidth;
    level_h = mTileCamera.TileH() * mTileheight;

    // Center the pixel camera
    mPixelCamera.x = follow_xpos - (mPixelCamera.w/2);
    mPixelCamera.y = follow_ypos - (mPixelCamera.h/2);

    // RIGHT
    // Pixel camera limit
    if ( mPixelCamera.x + mPixelCamera.w >= level_w )
    {
        refresh = true;
        prev_pos = mTileCamera.TileX();
        mTileCamera.OffsetX(tile_offset);

        // Tile Limit
        if ( mTileCamera.TileX() + mTileCamera.TileW() >= level_tile_w )
        {
            mTileCamera.TileX( level_tile_w - mTileCamera.TileW());
        }

        // Correct the pixel camera
        delta = mTileCamera.TileX()-prev_pos;
        if ( 0 == delta )
        {
            mPixelCamera.x = level_w - mPixelCamera.w;
        }
        else
        {
            mPixelCamera.x -= (mTilewidth*delta);
            OffsetSprites( -mTilewidth*delta, 0 );
        }
    }
    // LEFT
    // Pixel camera limit
    if ( 0 >= mPixelCamera.x )
    {
        refresh = true;
        prev_pos = mTileCamera.TileX();
        mTileCamera.OffsetX(-tile_offset);

        // Tile Limit
        if ( 0 >= mTileCamera.TileX() )
        {
            mTileCamera.TileX(0);
        }

        // Correct the pixel camera
        delta = mTileCamera.TileX()-prev_pos;
        if ( 0 == delta )
        {
            mPixelCamera.x = 0;
        }
        else
        {
            mPixelCamera.x -= (mTilewidth*delta);
            OffsetSprites( -mTilewidth*delta, 0 );
        }
    }
    // DOWN
    // Pixel camera limit
    if ( mPixelCamera.y + mPixelCamera.h >= level_h )
    {
        refresh = true;
        prev_pos = mTileCamera.TileY();
        mTileCamera.OffsetY(tile_offset);

        // Tile Limit
        if ( mTileCamera.TileY() + mTileCamera.TileH() >= level_tile_h )
        {
            mTileCamera.TileY( level_tile_h - mTileCamera.TileH());
        }

        // Correct the pixel camera
        delta = mTileCamera.TileY()-prev_pos;
        if ( 0 == delta )
        {
            mPixelCamera.y = level_h - mPixelCamera.h;
        }
        else
        {
            mPixelCamera.y -= (mTileheight*delta);
            OffsetSprites( 0, -mTileheight*delta );
        }
    }
    // UP
    // Pixel camera limit
    if ( 0 >= mPixelCamera.y )
    {
        refresh = true;
        prev_pos = mTileCamera.TileY();
        mTileCamera.OffsetY(-tile_offset);

        // Tile Limit
        if ( 0 >= mTileCamera.TileY() )
        {
            mTileCamera.TileY(0);
        }

        // Correct the pixel camera
        delta = mTileCamera.TileY()-prev_pos;
        if ( 0 == delta )
        {
            mPixelCamera.y = 0;
        }
        else
        {
            mPixelCamera.y -= (mTileheight*delta);
            OffsetSprites( 0, -mTileheight*delta );
        }
    }

    if (refresh)
    {
        RefreshMapTiles();
    }
}

void CModeWorld::OffsetClouds( int16_t offsetX, int16_t offsetY )
{
    for ( uint8_t t=0; t<mClouds.size(); t++ )
    {
        mClouds.at(t)->OffsetXPos( offsetX );
        mClouds.at(t)->OffsetYPos( offsetY );
    }
}

void CModeWorld::OffsetWaves( int16_t offsetX, int16_t offsetY )
{
    for ( uint8_t t=0; t<mWaves.size(); t++ )
    {
        mWaves.at(t)->OffsetXPos( offsetX );
        mWaves.at(t)->OffsetYPos( offsetY );
    }
}

void CModeWorld::OffsetSprites( int16_t offsetX, int16_t offsetY )
{
    for ( uint8_t t=0; t<mSpritesAng.size(); t++ )
    {
        mSpritesAng.at(t)->OffsetXPos( offsetX );
        mSpritesAng.at(t)->OffsetYPos( offsetY );
    }
    for ( uint8_t t=0; t<mSpritesDyn.size(); t++ )
    {
        mSpritesDyn.at(t)->OffsetXPos( offsetX );
        mSpritesDyn.at(t)->OffsetYPos( offsetY );
    }
    for ( uint8_t t=0; t<mSpritesSta.size(); t++ )
    {
        mSpritesSta.at(t)->OffsetXPos( offsetX );
        mSpritesSta.at(t)->OffsetYPos( offsetY );
    }
    OffsetWaves(  offsetX, offsetY );
    OffsetClouds( offsetX, offsetY );
}

void CModeWorld::DrawMapTiles( void )
{
    if ( 0 < mTiles.size() )
    {
        for ( uint16_t t=0; t<mTiles.size(); t++ )
        {
            if ( mTiles.at(t)->CheckRectCollision(mPixelCamera) )
            {
                mTiles.at(t)->Draw( mScreen.Image(), &mPixelCamera );
            }
        }
    }
}

void CModeWorld::DrawMapTowns( void )
{
    SDL_Rect pixel_pos;
    CSpriteStatic* town;
    CMapLocation* location;

    ClearMapTowns();

    for ( uint16_t t=0; t<mResources.Data().TownsDyn().Size(); t++ )
    {
        location = &mResources.Data().Towns().At( mResources.Data().TownsDyn().At(t)->DataTag() )->Location();
        if ( location->CheckMapCollision( mTileCamera ) )
        {
            town = new CSpriteStatic();

            pixel_pos.y = ((location->TileY() - mTileCamera.TileY()) * mTilewidth);
            pixel_pos.x = ((location->TileX() - mTileCamera.TileX()) * mTileheight);

            town->AssignGraphic( mResources.Data().Graphics().Find(GFX_NAVTOWN) );
            town->YPos( pixel_pos.y );
            town->XPos( pixel_pos.x );
            town->Draw( mScreen.Image(), &mPixelCamera );
            mTowns.resize( mTowns.size()+1, town );
            mTownTags.resize( mTownTags.size()+1, t );
        }
    }
}

void CModeWorld::DrawSprites( void )
{
    for ( uint8_t t=0; t<mSpritesAng.size(); t++ )
    {
        if (mSpritesAng.at(t)->GetRender()==true) {
            mSpritesAng.at(t)->Draw( mScreen.Image(), &mPixelCamera );
        }
    }
    for ( uint8_t t=0; t<mSpritesDyn.size(); t++ )
    {
        if (mSpritesDyn.at(t)->GetRender()==true) {
            mSpritesDyn.at(t)->Draw( mScreen.Image(), &mPixelCamera );
        }
    }
    for ( uint8_t t=0; t<mSpritesSta.size(); t++ )
    {
        if (mSpritesSta.at(t)->GetRender()==true) {
            mSpritesSta.at(t)->Draw( mScreen.Image(), &mPixelCamera );
        }
    }
}

void CModeWorld::DrawWaves( void )
{
    for ( uint8_t t=0; t<mWaves.size(); t++ )
    {
        if ( mWaves.at(t)->FrameColumn() == 0 &&
            mWaves.at(t)->FrameSpeed() == 0  )
        {
            mWaves.at(t)->XPos( getRandomValue( mPixelCamera.x, mPixelCamera.x + mPixelCamera.w ) );
            mWaves.at(t)->YPos( getRandomValue( mPixelCamera.y, mPixelCamera.y + mPixelCamera.h ) );
            mWaves.at(t)->SetFrame(getRandomValue( 1, mWaves.at(t)->FrameCount() ), 0 );
        }
        mWaves.at(t)->Draw( mScreen.Image(), &mPixelCamera );
    }
}

void CModeWorld::DrawClouds( void )
{
    int16_t cloud_x,cloud_y;

    for ( uint16_t t=0; t<mClouds.size(); t++ )
    {
        if ( mClouds.at(t)->CheckRectCollision(mPixelCamera) )    // Cloud inside mPixelCamera
        {
            mClouds.at(t)->Draw( mScreen.Image(), &mPixelCamera );
        }
        else                                                 // Cloud outside mPixelCamera
        {
            cloud_x = mClouds.at(t)->XPos();
            cloud_y = mClouds.at(t)->YPos();

            if ( cloud_x < mPixelCamera.x )                        // Too far to the left
            {
                mClouds.at(t)->XPos( mPixelCamera.x + mPixelCamera.w - 1 );
                mClouds.at(t)->YPos( mPixelCamera.y + getRandomValue(0, mPixelCamera.h) );
            }
            else if ( cloud_x > mPixelCamera.x + mPixelCamera.h )        // Too far to the right
            {
                mClouds.at(t)->XPos( mPixelCamera.x - mClouds.at(t)->ClipBox().w + 1 );
                mClouds.at(t)->YPos( mPixelCamera.y + getRandomValue(0, mPixelCamera.h) );
            }

            if ( cloud_y < mPixelCamera.y )                        // Too far up
            {
                mClouds.at(t)->YPos( mPixelCamera.y + mPixelCamera.h - 1 );
                mClouds.at(t)->XPos( mPixelCamera.x + getRandomValue(0, mPixelCamera.w) );
            }
            else if ( cloud_y > mPixelCamera.y + mPixelCamera.h )        // Too far down
            {
                mClouds.at(t)->YPos( mPixelCamera.y - mClouds.at(t)->ClipBox().h + 1 );
                mClouds.at(t)->XPos( mPixelCamera.x + getRandomValue(0, mPixelCamera.w) );
            }
        }
    }
}

void CModeWorld::DrawWindCompass( void )
{
    uint16_t xorigin    = mPixelCamera.h / 10;
    uint16_t yorigin    = mPixelCamera.h - (mPixelCamera.h / 10);
    uint16_t radius     = mPixelCamera.h / 15;
    uint16_t angle      = mWind.Angle();
    SDL_Color colrColor = { 0xFF, 0xFF, 0xFF, 0 };

    // Draw a circle
    mDraw.Circle( mScreen.Image(), xorigin, yorigin, radius, &colrColor );

    // Draw the red dot for Wind angle
    mWindcompass.ResetFrame();
    mWindcompass.XPos( xorigin - mWindcompass.CollisionBox().w/2 + radius * gSpriteAngleDirection[angle][0] / 32767  );
    mWindcompass.YPos( yorigin - mWindcompass.CollisionBox().h/2 + radius * gSpriteAngleDirection[angle][1] / 32767  );
    mWindcompass.Draw( mScreen.Image() );
}

#ifdef DEBUG
void CModeWorld::DrawDebugMessage( int16_t x, int16_t y, const std::string& text )
{
    SDL_Surface* screen;

    screen = mScreen.Image();
    mDebugMessage.AssignImage( TTF_RenderText_Solid( mResources.Font(), text.c_str(), *mResources.Options().Font().Color() ) );  //Draw the text
    mDebugMessage.ApplyImage( x, y, screen );
    mDebugMessage.ReleaseImage();
}

void CModeWorld::DrawDebugMessages( void )
{
    #define SIZE 100
    uint8_t pos = 15;
    char debug_caption[SIZE];

    snprintf( debug_caption, SIZE, "FPS Total: %d Drawn: %d Skipped: %d", mFps+mFskip, mFps, mFskip );
    DrawDebugMessage( 0, 0, debug_caption );

    snprintf( debug_caption, SIZE, "Loop Time %.4d Average %.4d", mLoopTime, mLoopTimeAvg );
    DrawDebugMessage( 300, 0, debug_caption );

    for ( uint8_t t=0; t<mDebugStrings.size(); t++ )
    {
        DrawDebugMessage( 0, pos, mDebugStrings.at(t) );
        pos+=15;
    }
}
#endif
