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

#ifndef CTIMER_H
#define CTIMER_H

#include "global.h"

// SDL based timer
class CTimer
{
	public:
		CTimer();
		virtual ~CTimer();

	    //Ctimer Functions
	    void    start();
	    void    stop();
	    void    delay( int16_t ticks );
	    void    pause();
	    void    unpause();
	    int16_t get_ticks();      //Number of ticks from start or pause
	    bool    is_started();
	    bool    is_paused();

	private:
		int16_t mStartTicks;    //Ticks from when the timer was started
	    int16_t mPauseTicks;    //Ticks stored when the timer was paused
	    bool    mPause;         //Timer status's
	    bool    mStart;
};

#endif // CTIMER_H
