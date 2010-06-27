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

#ifndef CSAILHO_H
#define CSAILHO_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "resources/types/ctransferwindow.h"

enum sailhomodes_t {
    SAILHO_SAILAWAY=1   ,
    SAILHO_BATTLE       ,
    SAILHO_NEWS
};

class CSailho
{
    public:
        CSailho( CResources& resources, CManagerWindow& wmanager );
        virtual ~CSailho();

        int8_t Run( void );

    private:
        CResources&         mResources;
        CManager<CString>&  mStrings;
        CManagerWindow&     mManagerwindow;

        int8_t SeeSail( void );
        int8_t SeeShip( void );
        int8_t SeeColors( void );
        int8_t SailAway( int8_t state );
};

#endif // CSAILHO_H
