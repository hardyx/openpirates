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

#ifndef CDYNTOWN_H
#define CDYNTOWN_H

#include "global.h"
#include "resources/types/ccargo.h"

/** @brief Contains dynamic data for the a town.
 */
class CDyntown
{
    public:
        /** Constructor. */
        CDyntown();
        /** Destructor. */
        virtual ~CDyntown();

        // Getters
		uint16_t    Tag( void )               const { return mTag; }        /** Get the tag of this town. */
        uint8_t     DataTag( void )           const { return mDataTag; }    /** Get the data-tag of this town. */
        uint8_t     NationTag( void )         const { return mNationTag; }  /** Get the nation-tag of this town. */
        uint8_t     Forts( void )             const { return mForts; }      /** Get the forts of this town. */
        uint16_t    Population( void )        const { return mPopulation; } /** Get the population of this town. */
        uint16_t    Soldiers( void )          const { return mSoldiers; }   /** Get the soliders of this town. */
        uint16_t    Sailors( void )           const { return mSailors; }    /** Get the sailors of this town. */
        CCargo&     Cargo( void )                   { return mCargo; }      /** Get reference to the cargo object of this town. */
        // Setters
        void        Tag( uint8_t v )                { mTag = v; }           /** Set the tag of this town. */
        void        DataTag( uint8_t v )            { mDataTag = v; }       /** Set the data-tag of this town. */
        void        NationTag( uint8_t v )          { mNationTag = v; }     /** Set the nation-tag of this town. */
        void        Forts( uint8_t v )              { mForts = v; }         /** Set the forts of this town. */
        void        Population( uint16_t v )        { mPopulation = v; }    /** Set the population of this town. */
        void        Soldiers( uint16_t v )          { mSoldiers = v; }      /** Set the soldiers of this town. */
        void        Sailors( uint16_t v )           { mSailors = v; }       /** Set the sailors of this town. */
        void        Cargo( const CCargo& v )        { mCargo = v; }         /** Set the cargo object of this town. */
        // Increment/Decrement
        void        DataTag_Inc( uint8_t v )        { mDataTag += v; }      /** Increment/Decrement the data-tag of this town. */
        void        NationTag_Inc( uint8_t v )      { mNationTag += v; }    /** Increment/Decrement the nation-tag  of this town. */
        void        Forts_Inc( uint8_t v )          { mForts += v; }        /** Increment/Decrement the forts of this town. */
        void        Population_Inc( uint16_t v )    { mPopulation += v; }   /** Increment/Decrement the population of this town. */
        void        Soldiers_Inc( uint16_t v )      { mSoldiers += v; }     /** Increment/Decrement the soldiers of this town. */
        void        Sailors_Inc( uint16_t v )       { mSailors += v; }      /** Increment/Decrement the sailors of this town. */

    private:
		uint16_t    mTag;           /** The tag of this town. */
        uint8_t     mDataTag;       /** The data-tag of this town. */
        uint8_t     mNationTag;     /** The nation-tag of this town. */
        uint8_t     mForts;         /** The forts of this town. */
        uint16_t    mPopulation;    /** The population of this town. */
        uint16_t    mSoldiers;      /** The soldiers of this town. */
        uint16_t    mSailors;       /** The sailors of this town. */
        CCargo      mCargo;         /** The cargo object of this town. */
};

#endif // CDYNTOWN_H
