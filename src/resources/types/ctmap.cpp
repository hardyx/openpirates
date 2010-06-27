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

#include "ctmap.h"

CTMap::CTMap() :
    mMapIndex   (1),
    mTileX      (1),
    mTileY      (1)
{
}

CTMap::~CTMap()
{
}

bool CTMap::IsLocation( int16_t map, int16_t tilex, int16_t tiley )
{
    if ( map  == mMapIndex &&
        tilex == mTileX    &&
        tiley == mTileY       )
    {
        return true;
    }
    else {
        return false;
    }
}

bool CTMap::IsMissingPiece( void )
{
    if ( pieces[0] == false || pieces[1] == false ||
         pieces[2] == false || pieces[3] == false    )
    {
        return true;
    }
    else {
        return false;
    }
}

void CTMap::AddPiece( void )
{
    int piece1, piece2;

    if ( IsMissingPiece() == true )
    {
        piece1 = getRandomValue( 0, 3 );
        piece2  = -1;

        while ( piece1 != piece2 )
        {
            if ( pieces[piece1] == false )
            {
                pieces[piece1] = true;
                piece2 = piece1;    // End the loop
            }
            else
            {
                if ( piece2 == -1 ) piece2 = piece1;
                piece1++;
                if ( piece1 > 3 ) piece1 = 0;
            }
        }
    }
}

void CTMap::View( void )
{

}
