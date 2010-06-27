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

#include "cdraw.h"

CDraw::CDraw()
{
}

CDraw::~CDraw()
{
}

void CDraw::Square( SDL_Surface* screen, SDL_Rect* box, SDL_Color* pcolor )
{
    int16_t x1, x2, y1, y2;

    // Draw top and bottom
    y1 = box->y;
    y2 = box->y + box->h;
    for ( x1=box->x; x1<box->x+box->w; x1++ )
    {
        Pixel( screen, x1, y1, pcolor );
        Pixel( screen, x1, y2, pcolor );
    }

    // Draw left and right
    x1 = box->x;
    x2 = box->x + box->w;
    for ( y1=box->y; y1<box->y+box->h; y1++ )
    {
        Pixel( screen, x1, y1, pcolor );
        Pixel( screen, x2, y1, pcolor );
    }
}


// source: http://tille.garrels.be/training/sdl/circle.php
void CDraw::Circle( SDL_Surface* screen, uint16_t xorigin, uint16_t yorigin, uint16_t radius, SDL_Color* pcolor  )
{
    for ( int16_t angle=0; angle<360; angle++ )
    {
        int16_t x = xorigin + (radius * gSpriteAngleDirection[angle][0] / 32767);
        int16_t y = yorigin + (radius * gSpriteAngleDirection[angle][1] / 32767);

        Pixel( screen, x, y, pcolor );
    }
}

// source: http://tille.garrels.be/training/sdl/circle.php
void CDraw::Pixel(SDL_Surface *screen, uint16_t x, uint16_t y, SDL_Color* pcolor)
{
    // Don't fail on attempts to draw outside the screen.
    if ( x >= screen->w || y >= screen->h ) return;

    Uint32 color = SDL_MapRGB(screen->format, pcolor->r, pcolor->g, pcolor->b );

    if ( SDL_MUSTLOCK(screen) )
    {
        if ( SDL_LockSurface(screen) < 0 )
        {
            return;
        }
    }

    switch ( screen->format->BytesPerPixel ) {
        case 1: { /* Assuming 8-bpp */
            uint8_t *bufp;

            bufp = (uint8_t *)screen->pixels + y*screen->pitch + x;
            *bufp = color;
        }
        break;

        case 2: { /* Probably 15-bpp or 16-bpp */
            uint16_t *bufp;

            bufp = (uint16_t *)screen->pixels + y*screen->pitch/2 + x;
            *bufp = color;
        }
        break;

        case 3: { /* Slow 24-bpp mode, usually not used */
            uint32_t *bufp;

            bufp = (uint32_t *)screen->pixels + y*screen->pitch + x * 3;
            if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
                bufp[0] = color;
                bufp[1] = color >> 8;
                bufp[2] = color >> 16;
            } else {
                bufp[2] = color;
                bufp[1] = color >> 8;
                bufp[0] = color >> 16;
            }
        }
        break;

        case 4: { /* Probably 32-bpp */
            Uint32 *bufp;

            bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
            *bufp = color;
        }
        break;

        default: {
            Error( __FILE__, __LINE__, "wrong bpp %d\n", screen->format->BytesPerPixel );
        }
        break;

    }
    if ( SDL_MUSTLOCK(screen) ) SDL_UnlockSurface( screen );
}
