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
 */

#ifndef CSAILHO_H
#define CSAILHO_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "resources/types/ctransferwindow.h"

enum sailho_list_t {
    SAILHO_NONE=0       ,
    SAILHO_SAILAWAY     ,
    SAILHO_NEWS         ,
    SAILHO_BATTLE
};

/**
 * @section DESCRIPTION
 * The menu for the sailho (ship spotted) window dialogs
 */

class CSailho
{
    public:
        /** Constructor. */
        CSailho( CResources& resources, CManagerWindow& winmanager );
        /** Destructor. */
        virtual ~CSailho();

        int8_t Run( void );
        int8_t P1EscapeDialog( void );
        int8_t AIEscapeDialog( void );
        int8_t P1SunkDialog( void );
        int8_t AISunkDialog( void );
        int8_t SunSetDialog( void );

    private:
        CResources&         mResources;
        CManager<CString>&  mStrings;
        CManagerWindow&     mManagerwindow;

        int8_t SeeSail( void );
        int8_t SeeShip( void );
        int8_t SeeColors( void );
        bool IsHostileShip( void );
};

#endif // CSAILHO_H
