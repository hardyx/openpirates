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

#include "cgraphic.h"

CGraphic::CGraphic() :
    mpImage     (NULL),
    mClipbox    (),
    mPath       ("N/A"),
    mTag        (0),
    mColumns    (1),
    mRows       (1),
    mRelease    (true)
{
}

CGraphic::~CGraphic()
{
    if (mRelease == true)
    {
        ReleaseImage();
    }
}

int8_t CGraphic::LoadFile( const std::string& path, uint16_t columns, uint16_t rows )
{
    int8_t result = SIG_NONE;

    mTag        = 0;
    mColumns    = columns;
    mRows       = rows;
    mPath       = path;
    mpImage     = LoadImage( mPath );

    if ( mpImage != NULL )
    {
        SetupClipbox();
    }
    else
    {
        Error( true, __FILE__, __LINE__, "null pointer\n" );
        return SIG_FAIL;
    }
    return result;
}

void CGraphic::AssignImage( SDL_Surface* pimage, bool release, uint16_t tag, uint16_t columns, uint16_t rows )
{
    if ( mpImage != NULL )
    {
        Log( "CGraphic: WARNING Image reference is not NULL, during a request to set the image\n" );
        ReleaseImage();
    }

    mpImage     = pimage;
    mRelease    = release;

    if ( mpImage != NULL )
    {
        mTag        = tag;
        mColumns    = columns;
        mRows       = rows;
        SetupClipbox();
    }
    else
    {
        Error( true, __FILE__, __LINE__, "null pointer\n" );
    }
}

void CGraphic::ReleaseImage( void )
{
    if ( mRelease == true && mpImage != NULL )
    {
        SDL_FreeSurface( mpImage );
        mpImage = NULL;
    }
}

void CGraphic::SetupClipbox( void )
{
    if ( mpImage != NULL )
    {
        mClipbox.x = 0;
        mClipbox.y = 0;
        mClipbox.w = mpImage->w / mColumns;
        mClipbox.h = mpImage->h / mRows;
    }
    else
    {
  		Error( true, __FILE__, __LINE__, "null pointer\n" );
    }
}

void CGraphic::ApplyImage( int16_t x, int16_t y, SDL_Surface* destination, SDL_Rect* clip )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    if ( mpImage != NULL )
    {
        SDL_BlitSurface( mpImage, clip, destination, &offset );
    }
    else
    {
  		Error( true, __FILE__, __LINE__, "null pointer\n" );
    }
}

SDL_Surface* CGraphic::LoadImage( const std::string& filename )
{
    SDL_Surface* loaded_image    = NULL; //The mpImage that's loaded
    SDL_Surface* optimized_image = NULL; //The optimized surface that will be used

    loaded_image = IMG_Load( filename.c_str() ); //Load the mpImage

    //If the mpImage loaded
    if ( loaded_image != NULL )
    {
        optimized_image = SDL_DisplayFormat( loaded_image );  //Create an optimized surface
        SDL_FreeSurface( loaded_image );                     //Free the old surface

        //If the surface was optimized
        if ( optimized_image != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimized_image, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimized_image->format, 0xFF, 0, 0xFF ) );
        }
    }
    else
    {
  		Error( true, __FILE__, __LINE__, "CGraphic::LoadImage -> Could not load image: %s at path='%s'\n", SDL_GetError(), filename.c_str() );
  		return NULL;
    }

    //Return the optimized surface
    return optimized_image;
}
