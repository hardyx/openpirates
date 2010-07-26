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

#ifndef CMENUOPTIONS_H
#define CMENUOPTIONS_H

#include "global.h"
#include "managers/cmanagerwindow.h"

/** @brief The menu for the game options window dialogs
 */
class CMenuOptions
{
    public:
        /** @brief Constructor.
         * @param resources : reference to the resources object
         * @param winmanager : reference to the window manager object
         */
        CMenuOptions( CResources& resources, CManagerWindow& winmanager );
        /** Destructor. */
		virtual ~CMenuOptions();

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

        /** @brief Handles window interaction changing video options.
         * @return value of type result_signal_t.
         */
        int8_t Video( void );

        /** @brief Handles window interaction changing screen resolution.
         * @return value of type result_signal_t.
         */
        int8_t ChangeResolution( int8_t current_mode );

        /** @brief Handles window interaction changing sound options.
         * @return value of type result_signal_t.
         */
        int8_t Sound( void );

        /** @brief Handles window interaction changing keyboard mappings.
         * @return value of type result_signal_t.
         */
        int8_t KeyControls( void );

        /** @brief Handles window interaction changing joystick mappings.
         * @return value of type result_signal_t.
         */
        int8_t JoyControls( void );

        /** @brief Handles window interaction if SDL suggests different video settings.
         * @return value of type result_signal_t.
         */
        int8_t UseSuggestedSettings( uint8_t cur, uint8_t sug );

        /** @brief Handles window interaction for waiting and getting a keyboard press.
         * @return value of type result_signal_t.
         */
        int8_t PressAnyKey( void );

        /** @brief Handles window interaction for waiting and getting a joystick press.
         * @return value of type result_signal_t.
         */
        int8_t PressAnyJoy( void );

        /** @brief Handles window interaction if the current settings have failed.
         * @return value of type result_signal_t.
         */
        int8_t FailedSettings( void );
};

#endif // CMENUOPTIONS_H
