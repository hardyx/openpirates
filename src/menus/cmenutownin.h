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

#ifndef CMENUTOWNIN_H
#define CMENUTOWNIN_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "menus/cgovernor.h"
#include "menus/ctavern.h"
#include "menus/cmerchant.h"
#include "menus/cshipwright.h"
#include "menus/cplunder.h"
#include "menus/cinformation.h"

/** @brief The menu for the inside of town window dialogs
 */
class CMenutownin
{
    public:
        /** @brief Constructor.
         * @param resources : reference to the resources object
         * @param winmanager : reference to the window manager object
         * @param dyntown : reference to the current dynamic town data
         * @param town : reference to the current static town data
         */
        CMenutownin( CResources& resources, CManagerWindow& winmanager, CDyntown* dyntown, CTown* town);
        /** Destructor. */
        virtual ~CMenutownin();

        /** @brief Main loop for the menu and logic.
         * @return value of type result_signal_t.
         */
		int8_t Run( bool sneak );

    private:
        CResources&         mResources;         /** Reference to the resources object. */
        CManagerWindow&     mManagerwindow;     /** Reference to the window manager. */
        CManager<CString>&  mStrings;           /** Reference to the strings manager. */
        CManager<CGraphic>& mGraphics;          /** Reference to the graphics manager. */
        CGraphic&           mScreen;            /** Reference to the screen object. */
        CDyntown*           mpDynTown;          /** Reference to the current town's dynamic data. */
        CTown*              mpTown;             /** Reference to the current town's static data. */
        CGovernor           mGovernor;          /** Menu for governor. */
        CTavern             mTavern;            /** Menu for tavern. */
        CMerchant           mMerchant;          /** Menu for merchant. */
        CShipwright         mShipwright;        /** Menu for shipwright. */
        CPlunder            mPlunder;           /** Menu for plunder. */
        CInformation        mInformation;       /** Menu for information. */

        CMenutownin(const CMenutownin &);
        CMenutownin& operator=(const CMenutownin&);
};

#endif // CMENUTOWNIN_H
