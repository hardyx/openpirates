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

#ifndef FRAMECTRL_H
#define FRAMECTRL_H

#include "global.h"
#include "timers/ctimer.h"

class CFramelimit
{
	public:
        CFramelimit();
		virtual ~CFramelimit();

        // Getters
        bool    FrameSkip( void )       { return mFrameSkip; }
        uint8_t FramesDrawn( void )     { return mFps; }
        uint8_t FramesSkipped( void )   { return mFskip; }

        void ControlFPS( bool limit, bool calc );

    private:
        CTimer tmrFrameSync;
        CTimer tmrFrameSingle;
        CTimer tmrFPSCalculate;

        bool        mFrameSkip;
        uint8_t     mFps;
        uint8_t     mFskip;
        uint8_t     mFramedrawn;
        uint8_t     mFrameskipped;
        uint8_t     mFrameinterval;
        uint16_t    mTicksLeft;
};

#endif // FRAMECTRL_H
