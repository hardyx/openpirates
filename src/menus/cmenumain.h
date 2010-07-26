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

#ifndef CMENUMAIN_H
#define CMENUMAIN_H

#include "global.h"
#include "managers/cmanagerwindow.h"

/** @brief The menu for the in-game main menu window dialogs
 */
class CMenumain
{
    public:
        /** @brief Constructor.
         * @param resources : reference to the resources object
         * @param winmanager : reference to the window manager object
         */
        CMenumain( CResources& resources, CManagerWindow& winmanager );
        /** Destructor. */
		virtual ~CMenumain();

        /** @brief Main loop for the menu and logic.
         * @return value of type result_signal_t.
         */
        int8_t Run( void );

    private:
        CResources&         mResources;         /** Reference to the resources object. */
        CManagerWindow&     mManagerwindow;     /** Reference to the window manager. */
        CManager<CString>&  mStrings;           /** Reference to the strings manager. */
        CManager<CGraphic>& mGraphics;          /** Reference to the graphics manager. */
        CGraphic&           mScreen;            /** Reference to the screen object. */
        CRole&              mPlayer;            /** Reference to the players dynamic data. */

        /** @brief Handles window interaction for ending the game.
         * @return value of type result_signal_t.
         */
		int8_t EndGame( void );

        /** @brief Handles window interaction saving.
         * @return value of type result_signal_t.
         */
		int8_t SaveCareer( void );

        /** @brief Handles window interaction loading.
         * @return value of type result_signal_t.
         */
		int8_t LoadCareer( void );
};

#endif // CMENUMAIN_H
