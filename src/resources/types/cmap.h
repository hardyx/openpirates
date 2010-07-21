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

#ifndef CMAP_H
#define CMAP_H

#include "global.h"
#include "resources/types/cmaplocation.h"

/**
 * @section DESCRIPTION
 * Defines attributes for the a map.
 */

class CMap
{
    public:
        /** Constructor. */
        CMap( int16_t gridx, int16_t gridy, int16_t gridw, int16_t gridh, std::string path );
        /** Destructor. */
        virtual ~CMap();

        // Getters
        uint8_t Tag( void )             { return mTag; }
        int16_t GridX( void )           { return mDimensions.TileX(); }
        int16_t GridY( void )           { return mDimensions.TileY(); }
        int16_t GridW( void )           { return mDimensions.TileW(); }
        int16_t GridH( void )           { return mDimensions.TileH(); }
        std::string& Path( void )       { return mPath; }
        // Setters
        void Tag( uint8_t tag )         { mTag = tag; }
        void GridX( int16_t gridx )     { mDimensions.TileX( gridx ); }
        void GridY( int16_t gridy )     { mDimensions.TileY( gridy ); }
        void GridW( int16_t gridw )     { mDimensions.TileW( gridw ); }
        void GridH( int16_t gridh )     { mDimensions.TileH( gridh ); }
        void Path( const std::string& path )    { mPath = path; }

        uint8_t TileAt( int16_t x, int16_t y );
        bool CheckMapCollision( CMapLocation& box );

    private:
        uint8_t mTag;
        CMapLocation mDimensions;
        std::string mPath;
        vec_uint8_t mTileData;

        void LoadTileData( void );
};

#endif // CMAP_H
