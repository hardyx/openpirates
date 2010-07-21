/***
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
 */

#ifndef CTIMER_H
#define CTIMER_H

#include "global.h"

/**
 * @section DESCRIPTION
 * SDL based timer class. A class to handle timer measurement through the SDL timer API
 */

class CTimer
{
	public:
        /** Constructor. */
		CTimer();
        /** Destructor. */
		virtual ~CTimer();

        /**
         * Starts the timer at the current SDL tick count.
         */
	    void start( void );

        /**
         * Stops the timer.
         */
	    void stop( void );

        /**
         * Delays the program until the number of ticks has elapsed. Note: if SDL_DELAY is not defined then the delay is done be
         * @param ticks : the number of ticks (milliseconds) to delay
         */
	    void delay( int16_t ticks );

        /**
         * Pause the timer. Stores the number of ticks since the timer was last started/unpaused.
         */
	    void pause( void );

        /**
         * Unpause the timer. Restarts the start ticks to the current ticks.
         */
	    void unpause( void );

        /**
         * Will return the amount of ticks since the timer was started. If the timer is paused the tick count at the time of being paused is returned.
         * @return the number of SDL ticks.
         */
	    int16_t get_ticks( void );

        /**
         * Determine if the timer has already been started.
         * @return boolean True : timer is started. False : the timer is not started.
         */
	    bool is_started( void );

        /**
         * Determine if the timer has already been paused.
         * @return boolean True : timer is paused. False : the timer is not paused.
         */
	    bool is_paused( void );

	private:
		int16_t mStartTicks;    /**< Contains the raw tick value from when the timer was started. */
	    int16_t mPauseTicks;    /**< Contains the raw tick value from when the timer was last paused. */
	    bool    mPause;         /**< Contains the pause state. */
	    bool    mStart;         /**< Contains the timer state. */
};

#endif // CTIMER_H
