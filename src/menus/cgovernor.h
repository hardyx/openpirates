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

#ifndef CGOVERNOR_H
#define CGOVERNOR_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "resources/types/cdyntown.h"

/** @brief The menu for the governor window dialogs
 */
class CGovernor
{
    public:
        /** @brief Constructor.
         * @param resources : reference to the resources object
         * @param winmanager : reference to the window manager object
         * @param dyntown : reference to the current dynamic town
         */
        CGovernor( CResources& resources, CManagerWindow& winmanager, CDyntown* dyntown );
        /** Destructor. */
        virtual ~CGovernor();

        /** @brief Main loop for the menu and logic.
         * @return value of type result_signal_t.
         */
        int8_t Run( void );

    private:
        CResources&         mResources;         /** Reference to the resources object. */
        CManagerWindow&     mManagerwindow;     /** Reference to the window manager. */
        CManager<CString>&  mStrings;           /** Reference to the strings manager. */
        CDyntown*           mpDynTown;          /** Reference to the current town's dynamic data. */

        /** @brief Check references are valid.
         * @return value of type result_signal_t.
         */
        int8_t VerifyPointers( void );

        /** @brief Handles window interaction for displaying current nation relations.
         * @return value of type result_signal_t.
         */
        int8_t StateOfWar( void );

        /** @brief Handles window interaction for player prisoners.
         * @return value of type result_signal_t.
         */
        int8_t Prisoner( void );

        /** @brief Handles window interaction for player promotions.
         * @return value of type result_signal_t.
         */
        int8_t Title( void );

        /** @brief Handles window interaction for player/ gov-daughter.
         * @return value of type result_signal_t.
         */
        int8_t Daughter( void );

        /** @brief Handles window interaction for player land rewards.
         * @return value of type result_signal_t.
         */
        uint16_t RewardLand( uint8_t reputation );

        CGovernor(const CGovernor &);
        CGovernor& operator=(const CGovernor&);
};

#endif // CGOVERNOR_H
