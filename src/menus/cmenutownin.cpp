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

#include "cmenutownin.h"

CMenutownin::CMenutownin( CResources& resources, CDyntown* dyntown, CTown* town ) :
    mResources      (resources),
    mScreen         (mResources.Screen()),
    mStrings        (mResources.Data().Strings()),
    mGraphics       (mResources.Data().Graphics()),
    mManagerwindow  (mScreen,
                     mResources.Controls(),
                     mResources.Options().Font()),
    mpDynTown       (dyntown),
    mpTown          (town),
    mGovernor       (mResources, mManagerwindow, mpDynTown),
    mTavern         (mResources, mManagerwindow, mpDynTown),
    mMerchant       (mResources, mpDynTown),
    mShipwright     (mResources, mManagerwindow),
    mPlunder        (mResources, mManagerwindow),
    mInformation    (mResources, mManagerwindow)
{
}

CMenutownin::~CMenutownin()
{
    Log( "CMenutownin Released!\n" );
}

int8_t CMenutownin::Run( bool sneak )
{
    int8_t result = SIG_NONE;
    int8_t index;
    bool done;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    vec_string_t variables;

    result = mManagerwindow.LoadResources( mResources.Font(),
                                           mGraphics.Find(GFX_BORDER),
                                           mGraphics.Find(GFX_POINTER) );

    if (result==SIG_NONE)
    {
        // Start with a dark blue background
        SDL_FillRect( mScreen.Image(), NULL, SDL_MapRGB( mScreen.Image()->format, 0x00, 0x00, 0x40 ) );

        variables.clear();
        variables.resize( variables.size()+1, &mpTown->Name() );
        index = mManagerwindow.CreateNewWindow( rectMain,
                                                mStrings.Find( STR_TOWN_INSIDE )->Text(),
                                                variables,
                                                &colrMainColor, NULL );

        done = false;
        while ( done == false && result >= SIG_NONE )
        {
            result = mManagerwindow.ActivateWindow( index );

            if (result>SIG_NONE)
            {
                switch ( result )
                {
                    case 1:
                        if ( !sneak )
                        {
                            result = mGovernor.Run();
                        }
                        else
                        {
                            index = mManagerwindow.CreateNewWindow( rectMain,
                                                                    mStrings.Find( STR_TOWN_SNEAK )->Text(),
                                                                    &colrMainColor, NULL );
                            result = mManagerwindow.ActivateWindow( index );
                        }
                        break;
                    case 2:
                        result = mTavern.Run();
                        break;
                    case 3:
                        result = mMerchant.Run();
                        break;
                    case 4:
                        result = mShipwright.Run();
                        break;
                    case 5:
                        result = mPlunder.Run();
                        break;
                    case 6:
                        result = mInformation.Run();
                        break;
                    case 7:      // Leave town
                        done = true;
                        result = SIG_NONE;
                        break;
                    default:
                        Error( __FILE__, __LINE__, "menu index out of range\n" );
                        result = SIG_FAIL;
                        break;
                }
            }
            else
            {
                Error( __FILE__, __LINE__, "menu index out of range\n" );
                result = SIG_FAIL;
            }
        }
    }

    return result;
}
