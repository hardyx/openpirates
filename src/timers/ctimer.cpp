/***
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
 */

#include "ctimer.h"

CTimer::CTimer() :
    mStartTicks   (0),
    mPauseTicks   (0),
    mPause        (false),
    mStart        (false)
{
}

CTimer::~CTimer()
{
}

void CTimer::start()
{
    mStart = true;                  // Start the timer
    mPause = false;                 // Unpause the timer
    mStartTicks = SDL_GetTicks();   // Get the current clock time
    //printf( "Start:%d\n", intStartTicks );
}

void CTimer::stop()
{
    mStart = false;                 // Stop the timer
    mPause = false;                 // Unpause the timer
}

void CTimer::delay( int16_t ticks )
{
#ifdef SDL_DELAY
    SDL_Delay( ticks );
#else
    int16_t now   = SDL_GetTicks();
    int16_t begin = now;
    int16_t delta = 0;

    while( delta >= 0 && delta < ticks )
    {
        now = SDL_GetTicks();
        delta = now - begin;
    }
#endif
}

void CTimer::pause()
{
    if ((mStart == true) && (mPause == false))      // If the timer is running and isn't already paused
    {
        mPause = true;                              // Pause the timer
        mPauseTicks = SDL_GetTicks() - mStartTicks; // Calculate the paused ticks
    }
}

void CTimer::unpause()
{
    // If the timer is paused
    if ( mPause == true )
    {
        mPause = false;                             // Unpause the timer
        mStartTicks = SDL_GetTicks() - mPauseTicks; // Reset the starting ticks
        mPauseTicks = 0;                            // Reset the paused ticks
    }
}

int16_t CTimer::get_ticks()
{
    int16_t ticks;

    if ( mStart == true )
    {
        if ( mPause == true )
        {
            return mPauseTicks;                     // Return the number of ticks when the timer was paused
        }
        else
        {
            ticks = SDL_GetTicks();
            //printf( "T:%d - T:%d\n", ticks, intStartTicks );
            return ticks - mStartTicks;             // Return the current time minus the start time
        }
    }
    return 0;                                       // If the timer isn't running
}

bool CTimer::is_started()
{
    return mStart;
}

bool CTimer::is_paused()
{
    return mPause;
}
