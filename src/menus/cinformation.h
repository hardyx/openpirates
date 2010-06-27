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

#ifndef CINFORMATION_H
#define CINFORMATION_H

#include "global.h"
#include "managers/cmanagerwindow.h"

class CInformation
{
    public:
        CInformation(CResources& resources, CManagerWindow& wmanager);
        virtual ~CInformation();

        int8_t Run( void );

    private:
        CResources&         mResources;
        CManagerWindow&     mManagerwindow;
        CManager<CString>&  mStrings;

        int8_t PartyStatus( void );
        int8_t PersonalStatus( void );
        int8_t ShipLog( void );
        int8_t Maps( void );
        int8_t Towns( void );
        int8_t ShowTownStats( uint16_t index );
        int8_t TakeSunSight( void );
        int8_t Search( void );
        int8_t SaveGame( void );
};

#endif // CINFORMATION_H
