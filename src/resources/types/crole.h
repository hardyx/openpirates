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

#ifndef CROLE_H
#define CROLE_H

#include "global.h"
#include "resources/types/cgood.h"
#include "resources/types/ccargo.h"
#include "resources/types/cplayership.h"
#include "resources/types/cmaplocation.h"
#include "resources/types/cprisoner.h"
#include "resources/types/cdate.h"
#include "resources/types/ctmap.h"
#include "resources/types/ceventlog.h"

/** @brief Defines attributes for a role during a timeperiod.
 */
class CRole
{
    public:
        /** Constructor. */
        CRole();
        /** Destructor. */
        virtual ~CRole();

        // Getters
		uint16_t        Tag( void )             const { return mTag; }
        uint8_t         Timeperiod( void )      const { return mTimeperiod; }
        uint8_t         Nationality( void )     const { return mNationality; }
        uint8_t         OverallRep( void )      const { return mOverallRep; }
        uint8_t         FlagShip( void )        const { return mFlagShip; }
        uint8_t         Skill( void )           const { return mSkill; }
        uint8_t         Difficulty( void )      const { return mDifficulty; }
        uint8_t         Health( void )          const { return mHealth; }
        uint8_t         Wounds( void )          const { return mWounds; }
        uint8_t         Age( void )             const { return mAge; }
        uint16_t        Crew( void )            const { return mCrew; }
        uint16_t        CareerLand( void )      const { return mCareerLand; }
        uint32_t        CareerGold( void )      const { return mCareerGold; }
        std::string&    Name( void )                  { return mName; }
        std::string&    Type( void )                  { return mType; }
        CMapLocation&   Location( void )              { return mLocation; }
        CDate&          Date( void )                  { return mDate; }
        CCargo&         Cargo( void )                 { return mCargo; }
        CTMap&          NormalMap( void )             { return mMapNormal; }
        CTMap&          FamilyMap( void )             { return mMapFamily; }
        CTMap&          FortuneMap( void )            { return mMapFortune; }
        CEventLog&      ShipLog( void )               { return mShipLog; }
        vec_uint8_t&    NationTitles( void )          { return mNationTitles; }
        vec_uint8_t&    NationReps( void )            { return mNationReps; }
        CPlayerShip&    Ships( uint8_t v )            { return mShips[v]; }
        vec_prisoner_t& Prisoners( void )             { return mPrisoners; }

        // Setters
        void            Tag( uint8_t v )                    { mTag = v; }
        void            Timeperiod( uint8_t v )             { mTimeperiod = v; }
        void            Nationality( uint8_t v )            { mNationality = v; }
        void            OverallRep( uint8_t v )             { mOverallRep = v; }
        void            FlagShip( uint8_t v )               { mFlagShip = v; }
        void            Skill( uint8_t v )                  { mSkill = v; }
        void            Difficulty( uint8_t v )             { mDifficulty = v; }
        void            Health( uint8_t v )                 { mHealth = v; }
        void            Wounds( uint8_t v )                 { mWounds = v; }
        void            Crew( uint16_t v )                  { mCrew = v; }
        void            CareerLand( uint16_t v )            { mCareerLand = v; }
        void            CareerGold( uint32_t v )            { mCareerGold = v; }
        void            Name( const std::string& v )        { mName = v; }
        void            Type( const std::string& v )        { mType = v; }
        void            Location( const CMapLocation& v )   { mLocation = v; }
        void            Date( const CDate& v )              { mDate = v; }
        void            Cargo( const CCargo& v )            { mCargo = v; }
        void            NormalMap( const CTMap& v )         { mMapNormal = v; }
        void            FamilyMap( const CTMap& v )         { mMapFamily = v; }
        void            FortuneMap( const CTMap& v )        { mMapFortune = v; }
         // Increment/Decrement
        void            Timeperiod_Inc( uint8_t v )         { mTimeperiod += v; }
        void            Nationality_Inc( uint8_t v )        { mNationality += v; }
        void            OverallRep_Inc( uint8_t v )         { mOverallRep += v; }
        void            FlagShip_Inc( uint8_t v )           { mFlagShip += v; }
        void            Skill_Inc( uint8_t v )              { mSkill += v; }
        void            Difficulty_Inc( uint8_t v )         { mDifficulty += v; }
        void            Crew_Inc( uint16_t v )              { mCrew += v; }
        void            CareerLand_Inc( uint16_t v )        { mCareerLand += v; }
        void            CareerGold_Inc( uint32_t v )        { mCareerGold += v; }

    private:
		uint16_t        mTag;
        uint8_t         mTimeperiod;
        uint8_t         mNationality;
        uint8_t         mOverallRep;
        uint8_t         mFlagShip;
        uint8_t         mSkill;
        uint8_t         mDifficulty;
        uint8_t         mHealth;
        uint8_t         mWounds;
        uint8_t         mAge;
        uint16_t        mCrew;
        uint16_t        mCareerLand;
        uint32_t        mCareerGold;
        std::string     mName;
        std::string     mType;
        CMapLocation    mLocation;
        CDate           mDate;
        CCargo          mCargo;
        CTMap           mMapNormal;
        CTMap           mMapFamily;
        CTMap           mMapFortune;
        CEventLog       mShipLog;
        vec_uint8_t     mNationTitles;
        vec_uint8_t     mNationReps;
        CPlayerShip     mShips[GAME_MAXSHIPS];
        vec_prisoner_t  mPrisoners;
};

#endif // CROLE_H
