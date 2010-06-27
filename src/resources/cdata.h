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

class CData
{
    public:
        CData();
        virtual ~CData();

        // Getters
        vec_string_t&  Difficulties( void )    { return mDifficulties; }
        vec_string_t&  Skills( void )          { return mSkills; }
        vec_string_t&  Swords( void )          { return mSwords; }
        vec_string_t&  Moral( void )           { return mMoral; }

        CManager<CString>&      Strings( void )        { return mStrings; }
        CManager<CGraphic>&     Graphics( void )       { return mGraphics; }
        CManager<CSound>&       Sounds( void )         { return mSounds; }
        CManager<CMap>&         Maps( void )           { return mMaps; }
        CManager<CStringValue>& Months( void )         { return mMonths; }
        CManager<CStringValue>& Reputations( void )    { return mReputations; }
        CManager<CStringValue>& Titles( void )         { return mTitles; }
        CManager<CStringValue>& Timeperiods( void )    { return mTimeperiods; }
        CManager<CEconomy>&     Economies( void )      { return mEconomies; }
        CManager<CNation>&      Nations( void )        { return mNations; }
        CManager<CShip>&        Ships( void )          { return mShips; }
        CManager<CTown>&        Towns( void )          { return mTowns; }
        CManager<CRole>&        Roles( void )          { return mRoles; }

        CManager<CDyntown>&     TownsDyn( void )       { return mTownsDynamic; }
        CEventLog&              Events( void )         { return mEvents; }
        CRole&                  Player( void )         { return mPlayer; }

        std::string* GetReputationName( uint16_t value );

    private:
        // Static Data
        vec_string_t mDifficulties;
        vec_string_t mSkills;
        vec_string_t mSwords;
        vec_string_t mMoral;

        CManager<CString>       mStrings;    // All strings from resources.txt
        CManager<CGraphic>      mGraphics;   // All graphics from resources.txt
        CManager<CSound>        mSounds;     // All sounds from resources.txt
        CManager<CMap>          mMaps;       // All maps from resources.txt
        CManager<CStringValue>  mMonths;
        CManager<CStringValue>  mReputations;
        CManager<CStringValue>  mTitles;
        CManager<CStringValue>  mTimeperiods;
        CManager<CEconomy>      mEconomies;
        CManager<CNation>       mNations;
        CManager<CShip>         mShips;
        CManager<CTown>         mTowns;
        CManager<CRole>         mRoles;

        //Dynamic Data
        CManager<CDyntown>      mTownsDynamic;
        CEventLog               mEvents;
        CRole                   mPlayer;

};

#endif // CDATA_H
