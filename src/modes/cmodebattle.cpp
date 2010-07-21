/***
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

#include "cmodebattle.h"

CModeBattle::CModeBattle( CResources& resources, CMenumain mainmenu ) :
    CModeWorld(resources),
    mMainmenu       (mainmenu),
    mArmySelectAll  (false),
    mArmySelected   (0),
    mBattleMode     (0),
    mBattleAngle    (0),
    mpShipStatsP1   (NULL),
    mpShipStatsAI   (NULL),
    mpArmyStatsP1   (NULL),
    mpArmyStatsAI   (NULL),
    mShipSpriteP1   (),
    mShipSpriteAI   (),
    mArmyP1         (),
    mArmyAI         (),
    mCalvaryAI      (),
    mFortAI         (),
    mCannonP1       (),
    mCannonAI       ()
{
}

CModeBattle::~CModeBattle()
{
}


int8_t CModeBattle::Run( CBattleShipStats* shipp1, CBattleShipStats* shipai )
{
    int8_t result = SIG_NONE;

    mBattleMode = SEA_VS_SEA;

    mpShipStatsP1 = shipp1;
    mpArmyStatsP1 = NULL;
    mpShipStatsAI = shipai;
    mpArmyStatsAI = NULL;

    OpenShipP1();
    OpenShipAI();

    result = Loop();
    return result;
}

int8_t CModeBattle::Run( CBattleShipStats* shipp1, CBattleArmyStats* armyai )
{
    int8_t result = SIG_NONE;

    mBattleMode = SEA_VS_LAND;

    mpShipStatsP1 = shipp1;
    mpArmyStatsP1 = NULL;
    mpShipStatsAI = NULL;
    mpArmyStatsAI = armyai;

    OpenShipP1();
    OpenArmyAI();

    result = Loop();
    return result;
}

int8_t CModeBattle::Run( CBattleArmyStats* armyp1, CBattleArmyStats* armyai )
{
    int8_t result = SIG_NONE;

    mBattleMode = LAND_VS_LAND;

    mpShipStatsP1 = NULL;
    mpArmyStatsP1 = armyp1;
    mpShipStatsAI = NULL;
    mpArmyStatsAI = armyai;

    OpenArmyP1();
    OpenArmyAI();

    result = Loop();
    return result;
}

void CModeBattle::OpenShipP1( void )
{
    uint16_t xorigin    = mPixelCamera.w/2;
    uint16_t yorigin    = mPixelCamera.w/2;
    uint16_t radius     = mPixelCamera.h/2 - mPixelCamera.h/4;
    uint16_t angle      = mBattleAngle;

    mShipSpriteP1.Open( 0, 0, ANI_CONT, 0, 4, 0, 0, true, true, 0, 0, 1 );
    mShipSpriteP1.AssignGraphic( mResources.Data().Graphics().Find(mpShipStatsP1->ShipTag()) );
    AddSprite(&mShipSpriteP1);
    mCannonP1.Open( 0, 0, ANI_BYROW, 60, 2, 0, 0, true, false );
    mCannonP1.AssignGraphic( mResources.Data().Graphics().Find(GFX_CANNON) );
    AddSprite(&mCannonP1);

    mShipSpriteP1.XPos( xorigin - radius * gSpriteAngleDirection[angle][0] / 32767  );
    mShipSpriteP1.YPos( yorigin - radius * gSpriteAngleDirection[angle][1] / 32767  );
    mShipSpriteP1.Angle( angle );
}

void CModeBattle::OpenShipAI( void )
{
    uint16_t xorigin    = mPixelCamera.w/2;
    uint16_t yorigin    = mPixelCamera.w/2;
    uint16_t radius     = mPixelCamera.h/2 - mPixelCamera.h/4;
    uint16_t angle;

    if (mBattleAngle<180)
        angle = mBattleAngle+180;
    else
        angle = mBattleAngle-180;

    mShipSpriteAI.Open( 0, 0, ANI_CONT, 0, 4, 0, 0, true, true, 0, 0, 1 );
    mShipSpriteAI.AssignGraphic( mResources.Data().Graphics().Find(mpShipStatsAI->ShipTag()) );
    AddSprite(&mShipSpriteAI);
    mCannonAI.Open( 0, 0, ANI_BYROW, 60, 2, 0, 0, true, false );
    mCannonAI.AssignGraphic( mResources.Data().Graphics().Find(GFX_CANNON) );
    AddSprite(&mCannonAI);

    mShipSpriteP1.XPos( xorigin - radius * gSpriteAngleDirection[angle][0] / 32767  );
    mShipSpriteP1.YPos( yorigin - radius * gSpriteAngleDirection[angle][1] / 32767  );
    mShipSpriteP1.Angle( angle );
}

void CModeBattle::OpenArmyP1( void )
{
    for (int8_t t=0; t<MAX_ARMIES; t++)
    {
        mArmyP1[t].Open( 0, 0, ANI_BYROW, 60, 2, 0, 0, true, false );
        mArmyP1[t].AssignGraphic( mResources.Data().Graphics().Find(GFX_ARMY) );
        AddSprite(&mArmyP1[t]);
    }
}

void CModeBattle::OpenArmyAI( void )
{
    if ( mBattleMode==SEA_VS_LAND )
    {
        mCannonAI.Open(  0, 0, ANI_BYROW, 60, 2, 0, 0, true, false );
        mCannonAI.AssignGraphic(  mResources.Data().Graphics().Find(GFX_CANNON) );
        AddSprite(&mCannonAI);
    }
    else if ( mBattleMode==LAND_VS_LAND )
    {
        for (int8_t t=0; t<MAX_ARMIES; t++)
        {
            mArmyAI[t].Open( 0, 0, ANI_BYROW, 60, 2, 0, 0, true, false );
            mArmyAI[t].AssignGraphic( mResources.Data().Graphics().Find(GFX_ARMY) );
            AddSprite(&mArmyAI[t]);
        }
        mCalvaryAI.Open( 0, 0, ANI_BYROW, 60, 2, 0, 0, true, false );
        mCalvaryAI.AssignGraphic( mResources.Data().Graphics().Find(GFX_CALVARY) );
        AddSprite(&mCalvaryAI);
    }
    mFortAI.Open(    2, 0, 0, true, false );
    mFortAI.AssignGraphic(    mResources.Data().Graphics().Find(GFX_FORT) );
    AddSprite(&mFortAI);
}

int8_t CModeBattle::Loop( void )
{
    int8_t result = SIG_NONE;

    result = InitWorld();

    while ( result != SIG_FAIL )
    {
        // Check key & buttons to move objects
		result = HandleEvents();

		if ( mBattleMode==SEA_VS_SEA || mBattleMode==SEA_VS_LAND )
		{
            // Set wind direction
            mWind.Run();
		}

		// Move sprites and check for collisions
		MoveP1();
		MoveAI();

        MoveWorld();
#ifdef DEBUG
        Debug();
#endif
        // Draw everything
        DrawWorld();
    }

    return result;
}

int8_t CModeBattle::HandleEvents( void )
{
    int8_t result = SIG_NONE;
    CControl control;

	/* Check for events */
	while ( mResources.Options().Controls().Poll(control) )
	{
		switch (control.State())
		{
			case CTRL_ACTIVATED:
                //Set the velocity
                switch ( control.Type() )
                {
                    case CTRL_QUIT:
                        result = SIG_FAIL;
                        break;
                    case CTRL_FULLSCREEN:
                        mResources.ToggleFullscreen();
                        break;;
                    case CTRL_MENU:
                        result = mMainmenu.Run();
                        break;
                    case CTRL_UP:
                        VelocityP1( -DEF_P1_BATTLE_SPEED, YAXIS );
                        break;
                    case CTRL_DOWN:
                        VelocityP1( DEF_P1_BATTLE_SPEED, YAXIS );
                        break;
                    case CTRL_RIGHT:
                        VelocityP1( DEF_P1_BATTLE_SPEED, XAXIS );
                        break;
                    case CTRL_LEFT:
                        VelocityP1( -DEF_P1_BATTLE_SPEED, XAXIS );
                        break;
                    case CTRL_ACTION:
                        if ( mBattleMode==SEA_VS_SEA || mBattleMode==SEA_VS_LAND )
                        {
                            FireCannon();
                        }
                        else
                        {
                            mArmySelectAll = true;
                        }
                        break;
#ifdef DEBUG
                    case CTRL_DBG_BOXES:
                        gDrawCollsionBox = !gDrawCollsionBox;
                        break;
#endif
                    default:
                        break;
                }
				break;
			case CTRL_DEACTIVATED:
                //Set the velocity
                switch ( control.Type() )
                {
                    case CTRL_UP:
                        VelocityP1( 0, YAXIS );
                        break;
                    case CTRL_DOWN:
                        VelocityP1( 0, YAXIS );
                        break;
                    case CTRL_RIGHT:
                        VelocityP1( 0, XAXIS );
                        break;
                    case CTRL_LEFT:
                        VelocityP1( 0, XAXIS );
                        break;
                    case CTRL_ACTION:
                        if ( mBattleMode==LAND_VS_LAND )
                        {
                            mArmySelectAll = false;
                            mArmySelected++;
                            if (mArmySelected>=MAX_ARMIES)
                                mArmySelected = 0;
                        }
                        break;
                    default:
                        break;
                }
				break;
			default:
				break;
		}
	}
    return result;
}

void CModeBattle::MoveP1( void )
{
    int16_t level_w;
    int16_t level_h;

    level_w = mTileCamera.TileW() * mTilewidth;
    level_h = mTileCamera.TileH() * mTileheight;

    if ( mBattleMode==SEA_VS_SEA || mBattleMode==SEA_VS_LAND )
    {
        //mWind.Apply( mShipSpriteP1 );
        mShipSpriteP1.Move( NULL, level_h, level_w );
    }
    else
    {
        for (int8_t t=0; t<MAX_ARMIES; t++)
        {
            mArmyP1[t].Move( NULL, level_h, level_w );
        }
    }
}

void CModeBattle::VelocityP1( int16_t vel, uint8_t axis )
{
    if ( mBattleMode==SEA_VS_SEA || mBattleMode==SEA_VS_LAND )
    {
        if ( 0 == vel )
        {
            mShipSpriteP1.AngleVel( 0 );
        }
        else
        {
            mShipSpriteP1.OffsetAngleVel( vel );
        }
        mShipSpriteP1.XVel( 0 );
        mShipSpriteP1.YVel( 0 );
    }
    else
    {
        for (int8_t t=0; t<MAX_ARMIES; t++)
        {
            if (mArmySelectAll==true || (mArmySelectAll==false && mArmySelected==t))
            {
                if ( 0 == vel )
                {
                    if ( axis == XAXIS )
                    {
                        mArmyP1[t].XVel( 0 );
                    }
                    else if ( axis == YAXIS )
                    {
                        mArmyP1[t].YVel( 0 );
                    }
                }
                else
                {
                    if ( axis == XAXIS )
                    {
                        mArmyP1[t].OffsetXVel( vel );
                    }
                    else if ( axis == YAXIS )
                    {
                        mArmyP1[t].OffsetYVel( vel );
                    }
                }
            }
        }
    }
}

void CModeBattle::FireCannon( void )
{

}

void CModeBattle::MoveAI( void )
{
    int8_t result = 0;

    if ( mBattleMode==SEA_VS_SEA )
    {
        //result = AILogic.Ship();
        switch(result)
        {
            case AI_RIGHT:
                break;

            case AI_LEFT:
                break;

            case AI_FIRE:
                break;

            default:
                break;
        }
    }
    else if ( mBattleMode==SEA_VS_LAND )
    {
        //result = AILogic.SeaFort();
        switch(result)
        {
            case AI_FIRE:
                break;

            default:
                break;
        }
    }
    else if ( mBattleMode==LAND_VS_LAND )
    {
        //result = AILogic.Armies();
        switch(result)
        {
            case AI_UP:
                break;

            case AI_DOWN:
                break;

            case AI_RIGHT:
                break;

            case AI_LEFT:
                break;

            case AI_FIRE:
                break;

            default:
                break;
        }
    }
    else
    {
        // Error
    }
}

void CModeBattle::MoveCannons( void )
{

}

#ifdef DEBUG
void CModeBattle::Debug( void )
{
    #define SIZE 100
    char caption[SIZE];

    mDebugStrings.clear();

    // Draw Messages
    snprintf( caption, SIZE, "ShipA X=%.3d Y=%.3d Angle=%.3d Col %d Row %d", mShipSpriteP1.XPos(),
                                                                             mShipSpriteP1.YPos(),
                                                                             mShipSpriteP1.Angle(),
                                                                             mShipSpriteP1.FrameColumn(),
                                                                             mShipSpriteP1.FrameRow() );
    mDebugStrings.resize( mDebugStrings.size()+1, caption );

    snprintf( caption, SIZE, "ShipB X=%.3d Y=%.3d Angle=%.3d Col %d Row %d", mShipSpriteAI.XPos(),
                                                                             mShipSpriteAI.YPos(),
                                                                             mShipSpriteAI.Angle(),
                                                                             mShipSpriteAI.FrameColumn(),
                                                                             mShipSpriteAI.FrameRow() );
    mDebugStrings.resize( mDebugStrings.size()+1, caption );
}
#endif
