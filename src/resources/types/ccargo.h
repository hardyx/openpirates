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

#ifndef CCARGO_H
#define CCARGO_H

#include "global.h"
#include "resources/types/cgood.h"

/** @brief Defines attributes for the cargo types and amounts.
 */
class CCargo
{
    public:
        /** Constructor. */
        CCargo();
        /** Destructor. */
        virtual ~CCargo();

        // Getters
        CGood&  Gold( void )                { return mGold; }               /** Get reference to gold good object. */
        CGood&  Food( void )                { return mFood; }               /** Get reference to food good object. */
        CGood&  Cannon( void )              { return mCannon; }             /** Get reference to cannon good object. */
        CGood&  GoodTypeA( void )           { return mGoodTypeA; }          /** Get reference to type a good object. */
        CGood&  GoodTypeB( void )           { return mGoodTypeB; }          /** Get reference to type b good object. */
        // Setters
        void    Gold( CGood v )             { mGold = v; }                  /** Set gold good object. */
        void    Food( CGood v )             { mFood = v; }                  /** Set food good object. */
        void    Cannon( CGood v )           { mCannon = v; }                /** Set cannon good object. */
        void    GoodTypeA( CGood v )        { mGoodTypeA = v; }             /** Set type a good object. */
        void    GoodTypeB( CGood v )        { mGoodTypeB = v; }             /** Set type b good object. */
        // Increment/Decrement
        void    Gold_Inc( uint32_t v )      { mGold.Count_Inc(v); }         /** Increment/Decrement the gold good count. */
        void    Food_Inc( uint8_t v )       { mFood.Count_Inc(v); }         /** Increment/Decrement the food good count. */
        void    Cannon_Inc( uint8_t v )     { mCannon.Count_Inc(v); }       /** Increment/Decrement the cannon good count. */
        void    GoodTypeA_Inc( uint8_t v )  { mGoodTypeA.Count_Inc(v); }    /** Increment/Decrement the type a good count. */
        void    GoodTypeB_Inc( uint8_t v )  { mGoodTypeB.Count_Inc(v); }    /** Increment/Decrement the type b good count. */

    private:
        CGood mGold;        /** The gold good object. */
        CGood mFood;        /** The food good object. */
        CGood mCannon;      /** The cannon good object. */
        CGood mGoodTypeA;   /** The type a good object. */
        CGood mGoodTypeB;   /** The type b good object. */
};

#endif // CCARGO_H
