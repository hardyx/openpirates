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

#ifndef CMENUTOWNOUT_H
#define CMENUTOWNOUT_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "menus/cmenutownin.h"

/** @brief The menu for the outside of town window dialogs
 */
class CMenutownout
{
    public:
        /** @brief Constructor.
         * @param resources : reference to the resources object
         * @param winmanager : reference to the window manager object
         */
        CMenutownout( CResources& resources, CManagerWindow& winmanager );
        /** Destructor. */
        virtual ~CMenutownout();

        /** @brief Main loop for the menu and logic.
         * @return value of type result_signal_t.
         */
        int8_t Run( int8_t entertype, int16_t town_index );

    private:
        CResources&         mResources;         /** Reference to the resources object. */
        CManagerWindow&     mManagerwindow;     /** Reference to the window manager. */
        CManager<CString>&  mStrings;           /** Reference to the strings manager. */
        CManager<CGraphic>& mGraphics;          /** Reference to the graphics manager. */
        CGraphic&           mScreen;            /** Reference to the screen object. */
        CDyntown*           mpDynTown;          /** Reference to the current town's dynamic data. */
        CTown*              mpTown;             /** Reference to the current town's static data. */
        CMenutownin*        mpMenutownin;       /** Reference to the in-town menu. */
        int8_t              mEntertype;         /** How the player intends to enter the town. */

        /** @brief Handles window interaction for entering a town.
         * @return value of type result_signal_t.
         */
        int8_t EnterTown( void );

        /** @brief Handles window interaction for attacking a town.
         * @return value of type result_signal_t.
         */
        int8_t AttackTown( void );

        /** @brief Handles window interaction for sneaking into a town.
         * @return value of type result_signal_t.
         */
        int8_t SneakTown( void );

        CMenutownout(const CMenutownout&);
        CMenutownout& operator=(const CMenutownout&);
};

#endif // CMENUTOWNOUT_H
