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

#ifndef CDATA_H
#define CDATA_H

#include "global.h"
#include "managers/cmanager.h"
#include "resources/types/cstring.h"
#include "resources/types/cgraphic.h"
#include "resources/types/csound.h"
#include "resources/types/cmap.h"
#include "resources/types/cstringvalue.h"
#include "resources/types/ceconomy.h"
#include "resources/types/cnation.h"
#include "resources/types/cship.h"
#include "resources/types/ctown.h"
#include "resources/types/crole.h"
#include "resources/types/cdyntown.h"
#include "resources/types/ceventlog.h"

/** @brief This class handles all game related data, such as (but not limited to) player and town data.
 */
class CData
{
    public:
        /** Constructor. */
        CData();
        /** Destructor. */
        virtual ~CData();

        // Getters (static data)
        vec_string_t&           Difficulties( void )    { return mDifficulties; }   /** Get reference to difficulties string data. */
        vec_string_t&           Skills( void )          { return mSkills; }         /** Get reference to skills string data. */
        vec_string_t&           Swords( void )          { return mSwords; }         /** Get reference to swords string data. */
        vec_string_t&           Moral( void )           { return mMoral; }          /** Get reference to morals string data. */
        CManager<CString>&      Strings( void )         { return mStrings; }        /** Get reference to the string manager. */
        CManager<CGraphic>&     Graphics( void )        { return mGraphics; }       /** Get reference to the graphic manager. */
        CManager<CSound>&       Sounds( void )          { return mSounds; }         /** Get reference to the sound manager. */
        CManager<CMap>&         Maps( void )            { return mMaps; }           /** Get reference to the map manager. */
        CManager<CStringValue>& Months( void )          { return mMonths; }         /** Get reference to the months manager. */
        CManager<CStringValue>& Reputations( void )     { return mReputations; }    /** Get reference to the reputations manager. */
        CManager<CStringValue>& Titles( void )          { return mTitles; }         /** Get reference to the titles manager. */
        CManager<CStringValue>& Timeperiods( void )     { return mTimeperiods; }    /** Get reference to the timeperiods manager. */
        CManager<CEconomy>&     Economies( void )       { return mEconomies; }      /** Get reference to the economies manager. */
        CManager<CNation>&      Nations( void )         { return mNations; }        /** Get reference to the nations manager. */
        CManager<CShip>&        Ships( void )           { return mShips; }          /** Get reference to the ships manager. */
        CManager<CTown>&        Towns( void )           { return mTowns; }          /** Get reference to the towns manager. */
        CManager<CRole>&        Roles( void )           { return mRoles; }          /** Get reference to the roles manager. */
        // Getters (dynamic data)
        CManager<CDyntown>&     TownsDyn( void )        { return mTownsDynamic; }   /** Get reference to the dynmic town manager. */
        CEventLog&              Events( void )          { return mEvents; }         /** Get reference to the events manager. */
        CRole&                  Player( void )          { return mPlayer; }         /** Get reference to the months manager. */
        // Functions
        /** @brief Converts the value to the string equalivilant.
         * @param value : the value
         * @return string data
         */
        std::string* GetReputationName( uint16_t value );

    private:
        // Static string data
        vec_string_t            mDifficulties;      /** Collection of difficulties string data. */
        vec_string_t            mSkills;            /** Collection of skills string data. */
        vec_string_t            mSwords;            /** Collection of swords string data. */
        vec_string_t            mMoral;             /** Collection of morals string data. */
        // Static data
        CManager<CString>       mStrings;           /** Manager for all string data loaded from resource conf file. */
        CManager<CGraphic>      mGraphics;          /** Manager for all graphic data loaded from resource conf file. */
        CManager<CSound>        mSounds;            /** Manager for all sound data loaded from resource conf file. */
        CManager<CMap>          mMaps;              /** Manager for all map data loaded from resource conf file. */
        CManager<CStringValue>  mMonths;            /** Manager for all months data loaded from resource conf file. */
        CManager<CStringValue>  mReputations;       /** Manager for all repuatation data loaded from resource conf file. */
        CManager<CStringValue>  mTitles;            /** Manager for all titles data loaded from resource conf file. */
        CManager<CStringValue>  mTimeperiods;       /** Manager for all timeperiods data loaded from resource conf file. */
        CManager<CEconomy>      mEconomies;         /** Manager for all economies data loaded from resource conf file. */
        CManager<CNation>       mNations;           /** Manager for all nations data loaded from resource conf file. */
        CManager<CShip>         mShips;             /** Manager for all ships data loaded from resource conf file. */
        CManager<CTown>         mTowns;             /** Manager for all towns data loaded from resource conf file. */
        CManager<CRole>         mRoles;             /** Manager for all roles data loaded from resource conf file. */
        //Dynamic Data
        CManager<CDyntown>      mTownsDynamic;      /** Manager for all dynamic town data. */
        CEventLog               mEvents;            /** Manager for all event data. */
        CRole                   mPlayer;            /** Manager for all player data (init with data loaded from resource conf file). */
};

#endif // CDATA_H
