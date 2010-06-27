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

#ifndef CMODEMAIN_H
#define CMODEMAIN_H

#include "global.h"
#include "menus/cmenustart.h"
#include "menus/cmenumain.h"
#include "modes/cmodenav.h"

class CModeMain
{
    public:
        CModeMain( void );
        virtual ~CModeMain( void );

        int8_t Run( int argc, char *argv[] );
        void Unload( void );

    private:
        // Resource files
        std::string     mFileOptions;
        std::string     mFileResources;
        // Pointers to structures for game data
        CResources      mResources;  // Data/System Resources
        CMenustart      mStartmenu;  // Start Menu
        CMenumain       mMainmenu;   // Main Menu
        CModeNav        mModenav;    // Navagation loop

        int8_t OpenSystem( const std::string& file_path, int argc, char *argv[] );
        int8_t ProcessArguments( int argc, char *argv[] );
        void VerifySettings( void );
        int8_t LoadResources( const std::string& file_path );
};

#endif // CMODEMAIN_H
