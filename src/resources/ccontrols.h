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

#ifndef CCONTROLS_H
#define CCONTROLS_H

#include "global.h"
#include "resources/ccontrol.h"
#include "resources/ccontrolmap.h"

typedef std::vector<CControlMap*> vec_ctrlmap_t;

class CControls
{
    public:
        CControls();
        virtual ~CControls();

        // Getters
        bool SysEventsEnabled( void )       { return mEnabledSys; }
        bool KeyEventsEnabled( void )       { return mEnabledKey; }
        bool JoyEventsEnabled( void )       { return mEnabledJoy; }
        bool MouseEventsEnabled( void )     { return mEnabledMouse; }
        // Setters
        void SysEventsEnabled( bool v )     { mEnabledSys = v; }
        void KeyEventsEnabled( bool v )     { mEnabledKey = v; }
        void JoyEventsEnabled( bool v )     { mEnabledJoy = v; }
        void MouseEventsEnabled( bool v )   { mEnabledMouse = v; }

        int8_t Poll(CControl& event);

    private:
        vec_ctrlmap_t mSysMaps;
        vec_ctrlmap_t mKeyMaps;
        vec_ctrlmap_t mJoyMaps;
        vec_ctrlmap_t mMouseMaps;
        bool mEnabledSys;
        bool mEnabledKey;
        bool mEnabledJoy;
        bool mEnabledMouse;

        void ClearControls( void );
};

#endif // CCONTROLS_H
