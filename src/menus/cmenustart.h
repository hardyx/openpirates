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

#ifndef CMENUSTART_H
#define CMENUSTART_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "menus/cmenuoptions.h"

/** @brief The menu for the starting of a game window dialogs
 */
class CMenustart
{
	public:
        /** @brief Constructor.
         * @param resources : reference to the resources object
         * @param winmanager : reference to the window manager object
         */
        CMenustart( CResources& resources, CManagerWindow& winmanager );
        /** Destructor. */
		virtual ~CMenustart();

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
        CMenuOptions        mMenuOptions;       /** Reference to the menu for options. */
        uint8_t             mGameSlot;          /** Slot to save game to. */
        bool                mAutoselect;        /** If true all selections are wuatoselected for the player. */

        /** @brief Handles window interaction for starting a new career.
         * @param autoselect : if true the selections will be defaults and the window sequence will be skipped, false you go through the windows.
         * @return value of type result_signal_t.
         */
		int8_t NewCareer( bool autoselect );

        /** @brief Handles window interaction for selecting the timeperiod.
         * @return value of type result_signal_t.
         */
		int8_t GetTimePeriod( void );

        /** @brief Handles window interaction for selecting the nation.
         * @return value of type result_signal_t.
         */
		int8_t GetNation( void );

        /** @brief Handles window interaction for selecting the player's name.
         * @return value of type result_signal_t.
         */
		int8_t GetName( void );

        /** @brief Handles window interaction for selecting the difficulty.
         * @return value of type result_signal_t.
         */
		int8_t GetDifficulty( void );

        /** @brief Handles window interaction for selecting the skill.
         * @return value of type result_signal_t.
         */
		int8_t GetSkill( void );

        /** @brief Handles window interaction for loading a career.
         * @return value of type result_signal_t.
         */
        int8_t LoadCareer( void );

        /** @brief Handles window interaction if a role doesnt yet exist (hopefully one day this wont be used).
         */
        void NoActiveRole( void );
};

#endif // CMENUSTART_H
