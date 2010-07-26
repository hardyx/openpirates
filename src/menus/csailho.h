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

#ifndef CSAILHO_H
#define CSAILHO_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "resources/types/ctransferwindow.h"

/** @brief The menu for the sailho (ship spotted) window dialogs
 */
class CSailho
{
    public:
        enum sailho_list_t {
            SAILHO_NONE=0       ,
            SAILHO_SAILAWAY     ,
            SAILHO_NEWS         ,
            SAILHO_BATTLE
        };

        /** @brief Constructor.
         * @param resources : reference to the resources object
         * @param winmanager : reference to the window manager object
         */
        CSailho( CResources& resources, CManagerWindow& winmanager );
        /** Destructor. */
        virtual ~CSailho();

        /** @brief Main loop for the menu and logic.
         * @return value of type result_signal_t.
         */
        int8_t Run( void );

        int8_t P1EscapeDialog( void );
        int8_t AIEscapeDialog( void );
        int8_t P1SunkDialog( void );
        int8_t AISunkDialog( void );
        int8_t SunSetDialog( void );

    private:
        CResources&         mResources;         /** Reference to the resources object. */
        CManagerWindow&     mManagerwindow;     /** Reference to the window manager. */
        CManager<CString>&  mStrings;           /** Reference to the strings manager. */

        /** @brief Handles window interaction for when a sail of a ship is spotted.
         * @return value of type result_signal_t.
         */
        int8_t SeeSail( void );

        /** @brief Handles window interaction for when a ship type is determined.
         * @return value of type result_signal_t.
         */
        int8_t SeeShip( void );

        /** @brief Handles window interaction for when a ship colors are determined.
         * @return value of type result_signal_t.
         */
        int8_t SeeColors( void );

        /** @brief Determines if a ship should be hostile to the player.
         * @return true ship is hostile, else friendly.
         */
        bool IsHostileShip( void );
};

#endif // CSAILHO_H
