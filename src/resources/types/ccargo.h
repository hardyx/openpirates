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

#ifndef CCARGO_H
#define CCARGO_H

#include "global.h"
#include "resources/types/cgood.h"

class CCargo
{
    public:
        CCargo();
        virtual ~CCargo();

        // Getters
        CGood&  Gold( void )                { return mGold; }
        CGood&  Food( void )                { return mFood; }
        CGood&  Cannon( void )              { return mCannon; }
        CGood&  GoodTypeA( void )           { return mGoodTypeA; }
        CGood&  GoodTypeB( void )           { return mGoodTypeB; }
        // Setters
        void    Gold( CGood v )             { mGold = v; }
        void    Food( CGood v )             { mFood = v; }
        void    Cannon( CGood v )           { mCannon = v; }
        void    GoodTypeA( CGood v )        { mGoodTypeA = v; }
        void    GoodTypeB( CGood v )        { mGoodTypeB = v; }
        // Inc
        void    Gold_Inc( uint32_t v )      { mGold.Count_Inc(v); }
        void    Food_Inc( uint8_t v )       { mFood.Count_Inc(v); }
        void    Cannon_Inc( uint8_t v )     { mCannon.Count_Inc(v); }
        void    GoodTypeA_Inc( uint8_t v )  { mGoodTypeA.Count_Inc(v); }
        void    GoodTypeB_Inc( uint8_t v )  { mGoodTypeB.Count_Inc(v); }

    private:
        CGood mGold;
        CGood mFood;
        CGood mCannon;
        CGood mGoodTypeA;
        CGood mGoodTypeB;
};

#endif // CCARGO_H
