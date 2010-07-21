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

#ifndef CMODEWORLD_H
#define CMODEWORLD_H

#include "global.h"
#include "timers/ctimer.h"
#include "timers/cframelimit.h"
#include "resources/cresources.h"
#include "resources/types/cgraphic.h"
#include "resources/types/cmap.h"
#include "sprites/cspritestatic.h"
#include "sprites/cspritedynamic.h"
#include "sprites/cspriteangular.h"
#include "sim/cwind.h"
#include "sprites/cdraw.h"

/**
 * @section DESCRIPTION
 * Provides base interfaces for handling the presentation of the world view.
 */

class CModeWorld
{
    public:
        /** Constructor. */
        CModeWorld( CResources& resources );
        /** Destructor. */
        virtual ~CModeWorld();

    protected:
        CResources&         mResources;
        CWind               mWind;
        vec_spritestatic_t  mTiles;
        vec_spritestatic_t  mTowns;
        vec_uint16_t        mTownTags;
#ifdef DEBUG
        std::vector<std::string> mDebugStrings;
#endif
        // Camera info
        CMapLocation    mTileCamera;
        SDL_Rect        mPixelCamera;
        int16_t         mFollowCameraIndex;
        bool            mFollowCameraType;
        // Tile info
        uint16_t mTilewidth;
        uint16_t mTileheight;

        int16_t AddSprite( CSpriteAngular* sprite );
        int16_t AddSprite( CSpriteDynamic* sprite );
        int16_t AddSprite( CSpriteStatic* sprite );
		int8_t InitWorld( void );
        void MoveWorld( void );
        int8_t DrawWorld( void );
#ifdef DEBUG
        void DrawDebugMessages( void );
#endif
    private:

        CGraphic&       mScreen;
        CManager<CMap>& mMaps;
        CFramelimit     mFrameControl;
        CSpriteStatic   mWindcompass;
        CDraw           mDraw;
#ifdef DEBUG
        CGraphic        mDebugMessage; // Graphic (temp for debug)
#endif
        vec_spriteangular_t    mClouds;
        vec_spritestatic_t     mWaves;
        vec_spriteangular_t    mSpritesAng;
        vec_spritedynamic_t    mSpritesDyn;
        vec_spritestatic_t     mSpritesSta;

        // Frame Count
        int8_t  mFps;
        int8_t  mFskip;
        bool    mFpscap;
        bool    mFpscalc;

        int8_t LoadEffects( void );
        void ClearMapTiles( void );
        void ClearMapTowns( void );
        void RefreshMapTiles( void );
        void MoveClouds( void );
        void MoveCameras( void );
        void OffsetClouds( int16_t offsetX, int16_t offsetY );
        void OffsetWaves( int16_t offsetX, int16_t offsetY );
        void OffsetSprites( int16_t offsetX, int16_t offsetY );
        void DrawMapTiles( void );
        void DrawMapTowns( void );
        void DrawSprites( void );
        void DrawWaves( void );
        void DrawClouds( void );
        void DrawWindCompass( void );
#ifdef DEBUG
        void DrawDebugMessage( int16_t y, const std::string& text );
#endif
};

#endif // CMODEWORLD_H
