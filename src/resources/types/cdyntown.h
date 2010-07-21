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

#ifndef CDYNTOWN_H
#define CDYNTOWN_H

#include "global.h"
#include "resources/types/ccargo.h"

/**
 * @section DESCRIPTION
 * Defines dynamic data for the a town.
 */

class CDyntown
{
    public:
        /** Constructor. */
        CDyntown();
        /** Destructor. */
        virtual ~CDyntown();

        // Getters
		uint16_t    Tag( void )                 { return mTag; }
        uint8_t     DataTag( void )             { return mDataTag; }
        uint8_t     NationTag( void )           { return mNationTag; }
        uint8_t     Forts( void )               { return mForts; }
        uint16_t    Population( void )          { return mPopulation; }
        uint16_t    Soldiers( void )            { return mSoldiers; }
        uint16_t    Sailors( void )             { return mSailors; }
        CCargo&     Cargo( void )               { return mCargo; }
        // Setters
        void        Tag( uint8_t v )            { mTag = v; }
        void        DataTag( uint8_t v )        { mDataTag = v; }
        void        NationTag( uint8_t v )      { mNationTag = v; }
        void        Forts( uint8_t v )          { mForts = v; }
        void        Population( uint16_t v )    { mPopulation = v; }
        void        Soldiers( uint16_t v )      { mSoldiers = v; }
        void        Sailors( uint16_t v )       { mSailors = v; }
        void        Cargo( const CCargo& v )    { mCargo = v; }
        // Inc
        void        DataTag_Inc( uint8_t v )        { mDataTag += v; }
        void        NationTag_Inc( uint8_t v )      { mNationTag += v; }
        void        Forts_Inc( uint8_t v )          { mForts += v; }
        void        Population_Inc( uint16_t v )    { mPopulation += v; }
        void        Soldiers_Inc( uint16_t v )      { mSoldiers += v; }
        void        Sailors_Inc( uint16_t v )       { mSailors += v; }

    private:
		uint16_t    mTag;
        uint8_t     mDataTag;
        uint8_t     mNationTag;
        uint8_t     mForts;
        uint16_t    mPopulation;
        uint16_t    mSoldiers;
        uint16_t    mSailors;
        CCargo      mCargo;
};

#endif // CDYNTOWN_H
