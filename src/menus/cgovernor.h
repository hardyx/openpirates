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

#ifndef CGOVERNOR_H
#define CGOVERNOR_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "resources/types/cdyntown.h"

class CGovernor
{
    public:
        CGovernor( CResources& resources, CManagerWindow& winmanager, CDyntown* dyntown );
        virtual ~CGovernor();

        int8_t Run( void );

    private:
        CResources&         mResources;
        CManager<CString>&  mStrings;
        CManagerWindow&    mManagerwindow;
        CDyntown*           mpDynTown;

        CGovernor(const CGovernor &);
        CGovernor& operator=(const CGovernor&);
        int8_t VerifyPointers( void );
        int8_t StateOfWar( void );
        int8_t Prisoner( void );
        int8_t Title( void );
        int8_t Daughter( void );
        uint16_t RewardLand( uint8_t reputation );
};

#endif // CGOVERNOR_H
