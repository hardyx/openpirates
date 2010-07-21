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

#ifndef CNAVMODE_H
#define CNAVMODE_H

#include "global.h"
#include "modes/cmodeworld.h"
#include "modes/cmodefencing.h"
#include "resources/ccontrols.h"
#include "sim/csimulate.h"
#include "menus/cmenumain.h"
#include "menus/cmenutownout.h"
#include "menus/csailho.h"

/**
 * @section DESCRIPTION
 * Provides interfaces for handling the presentation of the world map view.
 */

class CModeNav : public CModeWorld
{
	public:
        /** Constructor. */
        CModeNav( CResources& resources, CManagerWindow& winmanager, CMenumain& mainmenu );
        /** Destructor. */
		virtual ~CModeNav();

		int8_t Run( void );

    private:
        CSpriteAngular      mPlayership;
        CSpriteDynamic      mPlayercrew;
        CSimulate           mSimulate;
        CMenumain&          mMainmenu;
        CMenutownout        mMenutownout;
        CSailho             mSailho;
        CWind               mWind;
        CModeBattle         mModeBattle;
        CBattleShipStats    mShipStatsP1;
        CBattleShipStats    mShipStatsAI;
        CBattleArmyStats    mArmyStatsP1;
        CBattleArmyStats    mArmyStatsAI;
        CModeFencing        mModeFencing;
        int16_t             mPlayershipIndex;
        int16_t             mPlayercrewIndex;
        // Ship Info
        bool                mShipMode;
        bool                mCrewOutsideShip;
        bool                mInsideTown;
        SDL_Rect            mAnchorPosition;

        int8_t Init( void );
        int8_t HandleEvents();
        void MovePlayer( void );
        void CheckTownCollisions( void );
        void ApplyAngularVelocity( void );
        void PlayerVelocity( int16_t vel, uint8_t axis );
        int8_t ShipEncounter( void );
#ifdef DEBUG
        void Debug( void );
#endif
};

#endif // CNAVMODE_H
