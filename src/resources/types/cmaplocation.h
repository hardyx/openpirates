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

#ifndef CMAPLOCATION_H
#define CMAPLOCATION_H

#include "global.h"

class CMapLocation
{
    public:
        CMapLocation();
        virtual ~CMapLocation();

        // Getters
        int16_t TileX( void )           { return mX; }
        int16_t TileY( void )           { return mY; }
        int16_t TileW( void )           { return mW; }
        int16_t TileH( void )           { return mH; }
        // Setters
        void TileX( int16_t x )         { mX = x; }
        void TileY( int16_t y )         { mY = y; }
        void TileW( int16_t w )         { mW = w; }
        void TileH( int16_t h )         { mH = h; }
        void OffsetX( int16_t offset )  { mX += offset; }
        void OffsetY( int16_t offset )  { mY += offset; }
        void OffsetW( int16_t offset )  { mW += offset; }
        void OffsetH( int16_t offset )  { mH += offset; }

        bool CheckMapCollision( CMapLocation& box );

    private:
        int16_t mX;
        int16_t mY;
        int16_t mW;
        int16_t mH;
};

#endif // CMAPLOCATION_H
