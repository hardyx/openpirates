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
 */

#ifndef CDRAW_H
#define CDRAW_H

#include "global.h"

/**
 * @section DESCRIPTION
 * This class provides simple drawing routines that can draw shapes and individual pixels.
 */

class CDraw
{
    public:
        /** Constructor. */
        CDraw();
        /** Destructor. */
        virtual ~CDraw();

        void Square( SDL_Surface* screen, SDL_Rect* size, SDL_Color* pcolor );
        void Circle( SDL_Surface* screen, uint16_t xorigin, uint16_t yorigin, uint16_t radius, SDL_Color* pcolor  );
        void Pixel( SDL_Surface* screen, uint16_t x, uint16_t y, SDL_Color* pcolor );
};

extern int16_t gSpriteAngleDirection[360][2];

#endif // CDRAW_H
