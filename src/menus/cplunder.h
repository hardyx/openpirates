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

#ifndef CPLUNDER_H
#define CPLUNDER_H

#include "global.h"
#include "managers/cmanagerwindow.h"

#define RETIRE 1
#define REFIT  2

/**
 * @section DESCRIPTION
 * The menu for the plunder window dialogs
 */

class CPlunder
{
    public:
        /** Constructor. */
        CPlunder( CResources& resources, CManagerWindow& winmanager );
        /** Destructor. */
        virtual ~CPlunder();

        int8_t Run( void );

    private:
        CResources&         mResources;
        CManagerWindow&     mManagerwindow;
        CManager<CString>&  mStrings;

        int8_t DividePlunder( void );
        int8_t RefitOrRetire( void );
        bool VerifyRetire( void );
};

#endif // CPLUNDER_H
