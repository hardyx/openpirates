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

#ifndef CSHIPWRIGHT_H
#define CSHIPWRIGHT_H

#include "global.h"
#include "managers/cmanagerwindow.h"

/** @brief The menu for the shipwroght window dialogs
 */
class CShipwright
{
    public:
        /** @brief Constructor.
         * @param resources : reference to the resources object
         * @param winmanager : reference to the window manager object
         */
        CShipwright( CResources& resources, CManagerWindow& winmanager );
        /** Destructor. */
        virtual ~CShipwright();

        /** @brief Main loop for the menu and logic.
         * @return value of type result_signal_t.
         */
        int8_t Run( void );

    private:
        CResources&         mResources;         /** Reference to the resources object. */
        CManagerWindow&     mManagerwindow;     /** Reference to the window manager. */
        CManager<CString>&  mStrings;           /** Reference to the strings manager. */
        vec_string_t        mShips;             /** List of players ship names. */
        vec_uint8_t         mIndices;           /** List of ship tags. */
        vec_uint16_t        mPrices;            /** List of ship prices. */

        /** @brief Handles window interaction for repairing a ship.
         * @return value of type result_signal_t.
         */
        int8_t RepairShip( void );

        /** @brief Determines how much the repairs will cost.
         * @return value of type result_signal_t.
         */
        bool CheckRepairs( void );

        /** @brief Handles window interaction for selling a ship.
         * @return value of type result_signal_t.
         */
        int8_t SellShip( void );

        /** @brief Determines how much the the ship is worth.
         * @return value of type result_signal_t.
         */
        bool CheckSales( void );

        /** @brief Clears the ship lists.
         */
        void ClearShips( void );
};

#endif // CSHIPWRIGHT_H
