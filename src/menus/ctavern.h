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

#ifndef CTAVERN_H
#define CTAVERN_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "resources/types/cdyntown.h"

/**
 * @section DESCRIPTION
 * The menu for the tavern window dialogs
 */

class CTavern
{
    public:
        /** Constructor. */
        CTavern( CResources& resources, CManagerWindow& winmanager, CDyntown* dyntown );
        /** Destructor. */
        virtual ~CTavern();

        int8_t Run( void );

    private:
        CResources&         mResources;
        CManager<CString>&  mStrings;
        CManagerWindow&     mManagerwindow;
        CDyntown*           mpDynTown;

        CTavern(const CTavern&);
        CTavern& operator=(const CTavern&);
        int8_t Sailors( void );
        int8_t Traveler( void );
        int8_t TreasureMap( void );
        int8_t BartenderNews( void );
};

#endif // CTAVERN_H
