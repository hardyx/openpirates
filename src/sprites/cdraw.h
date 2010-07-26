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

#ifndef CDRAW_H
#define CDRAW_H

#include "global.h"

/** @brief This class provides simple drawing routines that can draw shapes and individual pixels.
 */
class CDraw
{
    public:
        /** Constructor. */
        CDraw();
        /** Destructor. */
        virtual ~CDraw();

        // Functions
        /** @brief Draw a square of one pixel wide lines
         * @param screen : pointer the destination screen
         * @param size : the dimensions of the square
         * @param pcolor : the color of the lines
         */
        void Square( SDL_Surface* screen, SDL_Rect* size, SDL_Color* pcolor );

        /** @brief Draw a circle of one pixel wide lines
         * @param screen : pointer the destination screen
         * @param xorigin : the x location on the screen where to center the circle
         * @param yorigin : the y location on the screen where to center the circle
         * @param radius : the size of the circle
         * @param pcolor : the color of the line
         */
        void Circle( SDL_Surface* screen, uint16_t xorigin, uint16_t yorigin, uint16_t radius, SDL_Color* pcolor  );

        /** @brief Draw a pixel to the screen
         * @param screen : pointer the destination screen
         * @param x : the x location on the screen where to draw the pixel
         * @param y : the y location on the screen where to draw the pixel
         * @param pcolor : the color of the pixel
         */
        void Pixel( SDL_Surface* screen, uint16_t x, uint16_t y, SDL_Color* pcolor );
};

extern int16_t gSpriteAngleDirection[360][2];

#endif // CDRAW_H
