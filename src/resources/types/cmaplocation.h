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

#ifndef CMAPLOCATION_H
#define CMAPLOCATION_H

#include "global.h"

/** @brief Defines a location and size on the world map.
 */
class CMapLocation
{
    public:
        /** Constructor. */
        CMapLocation();
        /** Destructor. */
        virtual ~CMapLocation();

        // Getters
        int16_t TileX( void )           const { return mX; }    /** Get the map x coordinate (tiles). */
        int16_t TileY( void )           const { return mY; }    /** Get the map y coordinate (tiles). */
        int16_t TileW( void )           const { return mW; }    /** Get the map width (tiles). */
        int16_t TileH( void )           const { return mH; }    /** Get the map height (tiles). */
        // Setters
        void TileX( int16_t x )         { mX = x; }             /** Set the map x coordinate (tiles). */
        void TileY( int16_t y )         { mY = y; }             /** Set the map y coordinate (tiles). */
        void TileW( int16_t w )         { mW = w; }             /** Set the map width (tiles). */
        void TileH( int16_t h )         { mH = h; }             /** Set the map height (tiles). */
        // Increment/Decrement
        void OffsetX( int16_t offset )  { mX += offset; }       /** Increment/Decrement the map x coordinate (tiles). */
        void OffsetY( int16_t offset )  { mY += offset; }       /** Increment/Decrement the map y coordinate (tiles). */
        void OffsetW( int16_t offset )  { mW += offset; }       /** Get the map width (tiles). */
        void OffsetH( int16_t offset )  { mH += offset; }       /** Get the map height (tiles). */

        /** @brief Determine if the dimensions given overlap with the map data
         * @param box : dimensions (tiles)
         * @return true if collision occurs else false
         */
        bool CheckMapCollision( CMapLocation& box );

    private:
        int16_t mX; /** The map x coordinate (tiles). */
        int16_t mY; /** The map y coordinate (tiles). */
        int16_t mW; /** The map width (tiles). */
        int16_t mH; /** The map height (tiles). */
};

#endif // CMAPLOCATION_H
