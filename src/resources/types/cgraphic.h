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

#ifndef CGRAPHIC_H
#define CGRAPHIC_H

#include "global.h"

/** @brief Container for graphical data (or SDL screen)
 */
class CGraphic
{
	public:
        /** Constructor. */
        CGraphic();
        /** Destructor. */
		virtual ~CGraphic();

        // Getters
		SDL_Surface*    Image( void )             { return mpImage; }           /** Get reference to the surface. */
        SDL_Rect&       ClipBox( void )           { return mClipbox; }          /** Get reference to the clip box. */
        std::string&    Path( void )              { return mPath; }             /** Get reference to the file path. */
        uint16_t        Tag( void )         const { return mTag; }              /** Get the tag. */
        uint16_t        FrameWidth( void )  const { return mClipbox.w; }        /** Get the frame width (pixel). */
        uint16_t        FrameHeight( void ) const { return mClipbox.h; }        /** Get the frame height (pixel). */
        uint16_t        FrameCount( void )  const { return mColumns*mRows; }    /** Get the frame count. */
        uint16_t        Columns( void )     const { return mColumns; }          /** Get the columns of frames. */
        uint16_t        Rows( void )        const { return mRows; }             /** Get the rows of frames. */
        // Setters
        void Tag( uint16_t tag ) { mTag = tag; }                                /** Set the tag. */
        // Functions
        /** @brief Loads an image from file to an SDL surface for reference
         * @param path : the relative path of the file
         * @param columns : the number of frame columns in the sheet
         * @param rows : the number of frame rows in the sheet
         * @return value of type result_signal_t.
         */
        int8_t LoadFile( const std::string& path, uint16_t columns, uint16_t rows );

        /** @brief Assigns an preloaded surface to surface reference
         * @param pimage : the new surface
         * @param release : attempt to release the previous surface (optional)
         * @param tag : the tag identifier (optional).
         * @param columns : the number of frame columns in the sheet (optional).
         * @param rows : the number of frame rows in the sheet (optional).
         */
		void AssignImage( SDL_Surface* pimage, bool release = true, uint16_t tag = 0, uint16_t columns = 1, uint16_t rows = 1 );

        /** @brief Releases the SDL surface.
         */
        void ReleaseImage( void );

        /** @brief Draws the surface to the destination surface (screen)
         * @param x : the x coordinate on the destination surface to place the local surface
         * @param y : the y coordinate on the destination surface to place the local surface
         * @param destination : where to draw the local surface
         * @param clip : the clip dimensions for the local surface (optional)
         */
        void ApplyImage( int16_t x, int16_t y, SDL_Surface* destination, SDL_Rect* clip = NULL );

    private:
        SDL_Surface*    mpImage;    /** The local surface reference. */
        SDL_Rect        mClipbox;   /** Clip box dimensions for clipping part to the local surface (i.e one frame). */
        std::string     mPath;      /** The relative path the file where the surface data is. */
        uint16_t        mTag;       /** The tag identifier. */
        uint16_t        mColumns;   /** The number of frame columns in the sheet. */
        uint16_t        mRows;      /** The number of frame rows in the sheet. */
        bool            mRelease;   /** Enable/Disable the release of the local surface (used for the SDL screen, as it shouldnt be released). */

        /** @brief Sets the dimensions of the clip box based on the number of frames in the sheet
         */
        void SetupClipbox( void );

        /** @brief Sets the dimensions of the clip box based on the number of frames in the sheet
         * @param filename : the x coordinate on the destination surface to place the local surface.
         * @return reference to the surface, if errror null is returned
         */
        SDL_Surface* LoadImage( const std::string& filename );    // Loads the mImage frome file in an optimized format

        CGraphic(const CGraphic&);
        CGraphic& operator=(const CGraphic&);
};

#endif // CGRAPHIC_H
