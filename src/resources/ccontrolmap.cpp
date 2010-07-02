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

#include "ccontrolmap.h"

// Keyboard Keys Events
CControlMap::CControlMap( uint8_t action, SDLKey key, SDLMod mod ) :
    mAction (action),
    mButton (0),
    mSym    (key),
    mMod    (mod)
{
}

// Joystick and Mouse Button Events
CControlMap::CControlMap( uint8_t action, uint8_t button ) :
    mAction (action),
    mButton (button),
    mSym    (SDLK_UNKNOWN),
    mMod    (KMOD_NONE)
{
}

CControlMap::~CControlMap()
{
    //dtor
}
