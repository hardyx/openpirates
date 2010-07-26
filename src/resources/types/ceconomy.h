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

#ifndef CECONOMY_H
#define CECONOMY_H

#include "global.h"

/** @brief Defines attributes for a economy level.
 */
class CEconomy
{
    public:
        /** Constructor. */
        CEconomy();
        /** Destructor. */
        virtual ~CEconomy();

        // Getters
        uint8_t         Tag( void )         const { return mTag; }          /** Get the tag. */
        uint8_t         Forts( void )       const { return mForts; }        /** Get the forts. */
        uint16_t        Population( void )  const { return mPopulation; }   /** Get the population. */
        uint16_t        Soldiers( void )    const { return mSoldiers; }     /** Get the soldiers. */
        uint16_t        Gold( void )        const { return mGold; }         /** Get the gold. */
        std::string&    Name( void )              { return mName; }         /** Get reference to the name string. */
        // Setters
        void Tag( uint8_t v )                     { mTag = v; }             /** Set the tag. */
        void Forts( uint8_t v )                   { mForts = v; }           /** Set the forts. */
        void Population( uint16_t v )             { mPopulation = v; }      /** Set the population. */
        void Soldiers( uint16_t v )               { mSoldiers = v; }        /** Set the soldiers. */
        void Gold( uint16_t v )                   { mGold = v; }            /** Set the gold. */
        void Name( const std::string& v )         { mName = v; }            /** Set the name string. */

    private:
        uint8_t     mTag;           /** The tag. */
        uint8_t     mForts;         /** The forts. */
        uint16_t    mPopulation;    /** The population. */
        uint16_t    mSoldiers;      /** The soldiers. */
        uint16_t    mGold;          /** The gold. */
        std::string mName;          /** The name. */
};

#endif // CECONOMY_H
