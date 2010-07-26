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

#ifndef CMERCHANT_H
#define CMERCHANT_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "resources/types/ctransferwindow.h"

/** @brief The menu for the merchant window dialogs
 */
class CMerchant
{
    public:
        /** @brief Constructor.
         * @param resources : reference to the resources object
         * @param dyntown : reference to the current dynamic town dataa
         */
        CMerchant( CResources& resources, CDyntown* dyntown );
        /** Destructor. */
        virtual ~CMerchant();

        /** @brief Main loop for the menu and logic.
         * @return value of type result_signal_t.
         */
        int8_t Run( void );

    private:
        CResources&         mResources;         /** Reference to the resources object. */
        CDyntown*           mpDynTown;          /** Reference to the current town's dynamic data. */
        CTransferWindow     mTransferWindow;    /** The transfer window for trading goods a for gold. */

        CMerchant(const CMerchant&);
        CMerchant& operator=(const CMerchant&);
};

#endif // CMERCHANT_H
