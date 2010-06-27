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

#ifndef CMODEBATTLE_H
#define CMODEBATTLE_H

#include "global.h"
#include "menus/cmenumain.h"
#include "modes/cmodeworld.h"
#include "resources/ccontrols.h"
#include "resources/types/cbattleshipstats.h"
#include "resources/types/cbattlearmystats.h"
#include "sim/cailogic.h"

#define MAX_ARMIES      3

enum battlemodes_t {
    SEA_VS_SEA=0    ,
    SEA_VS_LAND     ,
    LAND_VS_LAND
};

enum battleresults_t {
    SHIPP1_BOARD=0  ,
    SHIPP1_SUNK     ,
    SHIPP1_ESCAPE   ,
    SHIPAI_BOARD    ,
    SHIPAI_SUNK     ,
    SHIPAI_ESCAPE   ,
    ARMYP1_INFORT   ,
    ARMYP1_KILLED   ,
    ARMYP1_FLEE     ,
    ARMYAI_KILLED
};

class CModeBattle : public CModeWorld
{
    public:
        CModeBattle( CResources& resources, CMenumain mainmenu );
        virtual ~CModeBattle();

        int8_t Run( CBattleShipStats* shipp1, CBattleShipStats* shipai );
        int8_t Run( CBattleShipStats* shipp1, CBattleArmyStats* armyai );
        int8_t Run( CBattleArmyStats* armyp1, CBattleArmyStats* armyai );

    private:
        CMenumain&          mMainmenu;
        bool                mArmySelectAll;
        int8_t              mArmySelected;
        int8_t              mBattleMode;
        int16_t             mBattleAngle;
        CBattleShipStats*   mpShipStatsP1;
        CBattleShipStats*   mpShipStatsAI;
        CBattleArmyStats*   mpArmyStatsP1;
        CBattleArmyStats*   mpArmyStatsAI;
        CSpriteAngular      mShipSpriteP1;
        CSpriteAngular      mShipSpriteAI;
        CSpriteDynamic      mArmyP1[MAX_ARMIES];
        CSpriteDynamic      mArmyAI[MAX_ARMIES];
        CSpriteDynamic      mCalvaryAI;
        CSpriteStatic       mFortAI;
        CSpriteDynamic      mCannonP1;
        CSpriteDynamic      mCannonAI;

        CModeBattle(const CModeBattle &);
        CModeBattle & operator=(const CModeBattle&);
        void OpenShipP1( void );
        void OpenShipAI( void );
        void OpenArmyP1( void );
        void OpenArmyAI( void );
        int8_t Loop( void );
        int8_t HandleEvents( void );
        void MoveP1( void );
        void ApplyAngularVelocity( void );
        void VelocityP1( int16_t vel, uint8_t axis );
        void FireCannon( void );
        void MoveAI( void );
        void MoveCannons( void );
#ifdef DEBUG
        void Debug( void );
#endif
};

#endif // CMODEBATTLE_H
