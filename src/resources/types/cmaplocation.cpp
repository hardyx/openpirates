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

#include "cmaplocation.h"

CMapLocation::CMapLocation() :
    mX(0),
    mY(0),
    mW(0),
    mH(0)
{
}

CMapLocation::~CMapLocation()
{
}

bool CMapLocation::CheckMapCollision( CMapLocation& box )
{
    // The sides of the SDL_Rects
    int16_t leftA, leftB;
    int16_t rightA, rightB;
    int16_t topA, topB;
    int16_t bottomA, bottomB;

    // Calculate the sides of internal box
    leftA   = mX;
    rightA  = mX + mW;
    topA    = mY;
    bottomA = mY + mH;

    // Calculate the sides of rec box
    leftB   = box.TileX();
    rightB  = box.TileX() + box.TileW();
    topB    = box.TileY();
    bottomB = box.TileY() + box.TileH();

    // If any of the sides from box are outside of box
    if ( bottomA <= topB ) return false;
    if ( topA >= bottomB ) return false;
    if ( rightA <= leftB ) return false;
    if ( leftA >= rightB ) return false;
    // If none of the sides from box are outside box
    return true;    // Collision has occured
}
