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

#ifndef CCONTROLMAP_H
#define CCONTROLMAP_H

#include "global.h"

class CControlMap
{
    public:
        CControlMap( uint8_t action, uint8_t type );
        CControlMap( uint8_t action, uint8_t type, SDLKey key, SDLMod mod=KMOD_NONE );
        CControlMap( uint8_t action, uint8_t type, uint8_t button );
        virtual ~CControlMap();

        // Getters
        uint8_t Action( void )      { return mAction; }
        uint8_t Type( void )        { return mType; }
        uint8_t Button( void )      { return mButton; }
        const SDLKey& Sym( void )   { return mSym; }
        const SDLMod& Mod( void )   { return mMod; }
        // Setters
        void Action( uint8_t v )    { mAction = v; }
        void Type( uint8_t v )      { mType = v; }
        void Button( uint8_t v )    { mButton = v; }
        void Sym( SDLKey v )        { mSym = v; }
        void Mod( SDLMod v )        { mMod = v; }

    private:
        uint8_t mAction;
        uint8_t mType;
        uint8_t mButton;
        SDLKey  mSym;
        SDLMod  mMod;
};


#endif // CCONTROLMAP_H
