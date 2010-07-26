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

#ifndef CINFORMATION_H
#define CINFORMATION_H

#include "global.h"
#include "managers/cmanagerwindow.h"

/** @brief The menu for the in-game information window dialogs
 */
class CInformation
{
    public:
        /** @brief Constructor.
         * @param resources : reference to the resources object
         * @param winmanager : reference to the window manager object
         */
        CInformation( CResources& resources, CManagerWindow& winmanager );
        /** Destructor. */
        virtual ~CInformation();

        /** @brief Main loop for the menu and logic.
         * @return value of type result_signal_t.
         */
        int8_t Run( void );

    private:
        CResources&         mResources;         /** Reference to the resources object. */
        CManagerWindow&     mManagerwindow;     /** Reference to the window manager. */
        CManager<CString>&  mStrings;           /** Reference to the strings manager. */

        /** @brief Handles window interaction for party status info.
         * @return value of type result_signal_t.
         */
        int8_t PartyStatus( void );

        /** @brief Handles window interaction for personal status info.
         * @return value of type result_signal_t.
         */
        int8_t PersonalStatus( void );

        /** @brief Handles window interaction for ship log info.
         * @return value of type result_signal_t.
         */
        int8_t ShipLog( void );

        /** @brief Handles window interaction for maps (treasure/family maps).
         * @return value of type result_signal_t.
         */
        int8_t Maps( void );

        /** @brief Handles window interaction for town info (lists all of the towns, some info may be missing if the player has not obtained it).
         * @return value of type result_signal_t.
         */
        int8_t Towns( void );

        /** @brief Handles window interaction for a single town's info.
         * @return value of type result_signal_t.
         */
        int8_t ShowTownStats( uint16_t index );

        /** @brief Handles window interaction for taking the sun sight (determine position).
         * @return value of type result_signal_t.
         */
        int8_t TakeSunSight( void );

        /** @brief Handles window interaction for search (searches the ground for treasure/family).
         * @return value of type result_signal_t.
         */
        int8_t Search( void );

        /** @brief Handles window interaction for saving.
         * @return value of type result_signal_t.
         */
        int8_t SaveGame( void );
};

#endif // CINFORMATION_H
