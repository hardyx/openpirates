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

#ifndef CSHIPWRIGHT_H
#define CSHIPWRIGHT_H

#include "global.h"
#include "managers/cmanagerwindow.h"

class CShipwright
{
    public:
        CShipwright( CResources& resources, CManagerWindow& winmanager );
        virtual ~CShipwright();

        int8_t Run( void );

    private:
        CResources&         mResources;
        CManager<CString>&  mStrings;
        CManagerWindow&     mManagerwindow;
        vec_string_t        mShips;
        vec_uint8_t         mIndices;
        vec_uint16_t        mPrices;

        int8_t RepairShip( void );
        bool CheckRepairs( void );
        int8_t SellShip( void );
        bool CheckSales( void );
        void ClearShips( void );
};

#endif // CSHIPWRIGHT_H
