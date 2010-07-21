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

#include "cmap.h"

CMap::CMap( int16_t gridx, int16_t gridy, int16_t gridw, int16_t gridh, std::string path ) :
    mTag        (0),
    mDimensions (),
    mPath       (path),
    mTileData   ()
{
    mDimensions.TileX( gridx );
    mDimensions.TileY( gridy );
    mDimensions.TileW( gridw );
    mDimensions.TileH( gridh );

    LoadTileData();
}

CMap::~CMap()
{
}

void CMap::LoadTileData( void )
{
    std::ifstream fin;

    //Open the font
    if ( 0 < mPath.length() )
    {
        fin.open( mPath.c_str() );
        if ( fin.is_open() )
        {
            mTileData.clear();

            while ( !fin.eof() )
            {
                mTileData.resize( mTileData.size()+1, fin.get() );
            }
            Log( "\nCMap::LoadTileData Map loaded at %s", mPath.c_str() );
        }
        else
        {
            fin.close();
            Error( true, __FILE__, __LINE__, "LoadTileData: Couldn't open resource file at %s\n", mPath.c_str() );
        }
    }
    else
    {
        Error( true, __FILE__, __LINE__, "LoadTileData: Couldn't open file bad path given\n" );
    }
}

uint8_t CMap::TileAt( int16_t x, int16_t y )
{
    int16_t relx, rely;
    uint16_t index;
    uint8_t value = 0x00;

    relx = x-mDimensions.TileX();
    rely = y-mDimensions.TileY();
    if ( 0 <= relx && 0 <= rely )
    {
        index = rely*mDimensions.TileW() + relx;
        if ( mTileData.size() > index )
        {
            value = mTileData.at(index);
        }
    }
    return value;
}

bool CMap::CheckMapCollision( CMapLocation& box )
{
    return mDimensions.CheckMapCollision( box );
}
