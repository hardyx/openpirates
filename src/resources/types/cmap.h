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

#ifndef CMAP_H
#define CMAP_H

#include "global.h"
#include "resources/types/cmaplocation.h"

/** @brief Loads and contains attributes and data for the a world map.
 */
class CMap
{
    public:
        /** @brief Loads an image from file to an SDL surface for reference
         * @param gridx : the x coordinate (tiles) for the map location
         * @param gridy : the y coordinate (tiles) for the map location
         * @param gridw : the width (tiles) of the map
         * @param gridh : the height (tiles) of the map
         * @param path : the relative path of the map data file
         */
        CMap( int16_t gridx, int16_t gridy, int16_t gridw, int16_t gridh, std::string path );
        /** Destructor. */
        virtual ~CMap();

        // Getters
        uint8_t Tag( void )             const { return mTag; }                  /** Get tag identifier. */
        int16_t GridX( void )           const { return mDimensions.TileX(); }   /** Get the map x coordinate (tiles). */
        int16_t GridY( void )           const { return mDimensions.TileY(); }   /** Get the map y coordinate (tiles). */
        int16_t GridW( void )           const { return mDimensions.TileW(); }   /** Get the map width (tiles). */
        int16_t GridH( void )           const { return mDimensions.TileH(); }   /** Get the map height (tiles). */
        std::string& Path( void )             { return mPath; }
        // Setters
        void Tag( uint8_t tag )                 { mTag = tag; }                 /** Set tag identifier. */
        void GridX( int16_t gridx )             { mDimensions.TileX( gridx ); } /** Set the map x coordinate (tiles) . */
        void GridY( int16_t gridy )             { mDimensions.TileY( gridy ); } /** Set the map y coordinate (tiles) . */
        void GridW( int16_t gridw )             { mDimensions.TileW( gridw ); } /** Set the map width (tiles) . */
        void GridH( int16_t gridh )             { mDimensions.TileH( gridh ); } /** Set the map height (tiles) . */
        void Path( const std::string& path )    { mPath = path; }               /** Set the path. */

        /** @brief Returns the numeric value of a tile from the map data
         * @param x : the x coordinate of the tile (tiles)
         * @param y : the y coordinate of the tile (tiles)
         * @return value of of the tile.
         */
        uint8_t TileAt( int16_t x, int16_t y );

        /** @brief Determine if the dimensions given overlap with the map data
         * @param box : dimensions (tiles)
         * @return true if collision occurs else false
         */
        bool CheckMapCollision( CMapLocation& box );

    private:
        uint8_t mTag;                   /** The tag identifier. */
        CMapLocation mDimensions;       /** The map dimensions/location (tiles). */
        std::string mPath;              /** The relative file path to the map data. */
        vec_uint8_t mTileData;          /** The collection of tile data. */

        /** @brief Loads the tile data from the file into memory
         */
        void LoadTileData( void );
};

#endif // CMAP_H
