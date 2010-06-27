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

#include "cmerchant.h"

CMerchant::CMerchant( CResources& resources, CDyntown* dyntown ) :
    mResources         (resources),
    mpDynTown          (dyntown),
    mTransferWindow    (mResources)
{
}

CMerchant::~CMerchant()
{
}

int8_t CMerchant::Run( void )
{
    int8_t result = SIG_NONE;
    CRole& player = mResources.Data().Player();
    std::string merchant = "Merchant";

    result = mTransferWindow.Run( TRANSFER_TRADE, player.Name(), merchant,
                                  player.Cargo(), mpDynTown->Cargo() );

    return result;
}
