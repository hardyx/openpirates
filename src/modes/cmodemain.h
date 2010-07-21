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

#ifndef CMODEMAIN_H
#define CMODEMAIN_H

#include "global.h"
#include "menus/cmenustart.h"
#include "menus/cmenumain.h"
#include "modes/cmodenav.h"

/**
 * @section DESCRIPTION
 * The main mode loop handles loading and init of the application.
 */

class CModeMain
{
    public:
        /** Constructor. */
        CModeMain( void );
        /** Destructor. */
        virtual ~CModeMain( void );

        int8_t Run( int argc, char *argv[] );
        void Unload( void );

    private:
        // Resource files
        std::string     mBasePath;
        // Pointers to structures for game data
        CResources      mResources;     // Data/System Resources
        CManagerWindow  mManagerwindow; // Window Manager
        CMenumain       mMainmenu;      // Main Menu
        CMenustart      mStartmenu;     // Start Menu
        CModeNav        mModenav;       // Navagation loop

        void SetBasePath( const char* base_path );
        int8_t OpenSystem( int argc, char *argv[] );
        int8_t ProcessArguments( int argc, char *argv[] );
        int8_t LoadResources( void );
};

#endif // CMODEMAIN_H
