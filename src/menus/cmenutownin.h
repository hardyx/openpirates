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

class CMenutownin
{
    public:
        CMenutownin( CResources& resources, CManagerWindow& winmanager, CDyntown* dyntown, CTown* town);
        virtual ~CMenutownin();

		int8_t Run( bool sneak );

    private:
        CResources&         mResources;
        CGraphic&           mScreen;
        CManager<CString>&  mStrings;
        CManager<CGraphic>& mGraphics;
        CManagerWindow&     mManagerwindow;
        CDyntown*           mpDynTown;
        CTown*              mpTown;
        CGovernor           mGovernor;
        CTavern             mTavern;
        CMerchant           mMerchant;
        CShipwright         mShipwright;
        CPlunder            mPlunder;
        CInformation        mInformation;

        CMenutownin(const CMenutownin &);
        CMenutownin& operator=(const CMenutownin&);
};

#endif // CMENUTOWNIN_H
