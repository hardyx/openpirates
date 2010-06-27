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

#ifndef CTMAP_H
#define CTMAP_H

#include "global.h"

class CTMap
{
    public:
        CTMap();
        virtual ~CTMap();

        bool IsLocation( int16_t map, int16_t tilex, int16_t tiley );
        bool IsMissingPiece( void );
        void AddPiece( void );
        void View();

    private:
        int16_t mMapIndex;
        int16_t mTileX;
        int16_t mTileY;
        bool pieces[4];
};

#endif // CTMAP_H
