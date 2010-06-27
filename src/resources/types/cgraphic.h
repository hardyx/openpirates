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

#ifndef CGRAPHIC_H
#define CGRAPHIC_H

#include "global.h"

// Class that provides graphical mpResources for a sprite to use
class CGraphic
{
	public:
        CGraphic();
		virtual ~CGraphic();

        // Getters
		SDL_Surface*    Image( void )       { return mpImage; }
        uint16_t        Tag( void )         { return mTag; }
        SDL_Rect&       ClipBox( void )     { return mClipbox; }
        std::string&    Path( void )        { return mPath; }
        uint16_t        FrameWidth( void )  { return mClipbox.w; }
        uint16_t        FrameHeight( void ) { return mClipbox.h; }
        uint16_t        FrameCount( void )  { return mColumns*mRows; }
        uint16_t        Columns( void )     { return mColumns; }
        uint16_t        Rows( void )        { return mRows; }
        // Setters
        void Tag( uint16_t tag ) { mTag = tag; }

        int8_t LoadFile( const std::string& path, uint16_t columns, uint16_t rows );
		void AssignImage( SDL_Surface* pimage, bool release = true, uint16_t tag = 0, uint16_t columns = 1, uint16_t rows = 1 );
        void ReleaseImage( void );
        void ApplyImage( int16_t x, int16_t y, SDL_Surface* destination, SDL_Rect* clip = NULL );

    private:
        CGraphic(const CGraphic &);
        CGraphic & operator=(const CGraphic&);

        SDL_Surface*    mpImage;
        SDL_Rect        mClipbox;
        std::string     mPath;
        uint16_t        mTag;
        uint16_t        mColumns;
        uint16_t        mRows;
        bool            mRelease;

        void SetupClipbox( void );
        SDL_Surface* LoadImage( const std::string& filename );    // Loads the mImage frome file in an optimized format
};

#endif // CGRAPHIC_H
