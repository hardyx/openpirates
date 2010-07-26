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
 *
 *  @section LOCATION
 */

#ifndef CPLUNDER_H
#define CPLUNDER_H

#include "global.h"
#include "managers/cmanagerwindow.h"

/** @brief The menu for the plunder window dialogs
 */
class CPlunder
{
    public:
        #define RETIRE 1
        #define REFIT  2

        /** @brief Constructor.
         * @param resources : reference to the resources object
         * @param winmanager : reference to the window manager object
         */
        CPlunder( CResources& resources, CManagerWindow& winmanager );
        /** Destructor. */
        virtual ~CPlunder();

        /** @brief Main loop for the menu and logic.
         * @return value of type result_signal_t.
         */
        int8_t Run( void );

    private:
        CResources&         mResources;         /** Reference to the resources object. */
        CManagerWindow&     mManagerwindow;     /** Reference to the window manager. */
        CManager<CString>&  mStrings;           /** Reference to the strings manager. */

        /** @brief Handles window interaction for dividing the plunder.
         * @return value of type result_signal_t.
         */
        int8_t DividePlunder( void );

        /** @brief Handles window interaction for deciding to refit or retire (end the career).
         * @return value of type result_signal_t.
         */
        int8_t RefitOrRetire( void );

        /** @brief Handles window interaction for assuring the player wants to retire (end the career).
         * @return value of type result_signal_t.
         */
        bool VerifyRetire( void );
};

#endif // CPLUNDER_H
