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

#ifndef CMERCHANT_H
#define CMERCHANT_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "resources/types/ctransferwindow.h"

class CMerchant
{
    public:
        CMerchant( CResources& resources, CDyntown* dyntown );
        virtual ~CMerchant();

        int8_t Run( void );

    private:
        CResources&         mResources;
        CDyntown*           mpDynTown;
        CTransferWindow     mTransferWindow;

        CMerchant(const CMerchant &);
        CMerchant & operator=(const CMerchant&);
};

#endif // CMERCHANT_H
