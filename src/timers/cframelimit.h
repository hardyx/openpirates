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

#ifndef FRAMECTRL_H
#define FRAMECTRL_H

#include "global.h"
#include "timers/ctimer.h"

/** @brief A class to handle counting and limiting of the frames drawn and when following frames should be skipped.
 */
class CFramelimit
{
	public:
        /** Constructor. */
        CFramelimit();
        /** Destructor. */
		virtual ~CFramelimit();

        // Getters
        bool        FrameSkip( void )       const { return mFrameSkip; }    /** Get if the next frame should be skipped. */
        uint8_t     FramesDrawn( void )     const { return mFps; }          /**< Get the number of frames drawn at the current point in time. */
        uint8_t     FramesSkipped( void )   const { return mFskip; }        /**< Get the number of frames skipped at the current point in time. */
        uint16_t    LoopTime( void )        const { return mLoopTime; }     /**< Get the last loop time. */
        uint16_t    LoopTimeAvg( void )     const { return mLoopTimeAvg; }  /**< Get the last loop time average. */

        // Functions
        /** @brief Controls if the class should limit the framerate and also calculate the FPS.
         * @param limit : set to true to limit the frame rate
         * @param calc : set to true to calculate the frame rate
         */
        void ControlFPS( bool limit, bool calc );

    private:
        CTimer tmrFrameSync;        /**< This timer counts the overall time for the number of sync frames (usually 3 for 50 ms). */
        CTimer tmrFrameSingle;      /**< This timer counts the time taken to draw a single frame. */
        CTimer tmrFPSCalculate;     /**< This timer counts for one second, in order to determine the FPS. */

        bool        mFrameSkip;     /**< True if the next frame should be skipped. */
        uint8_t     mFps;           /**< Number of frames drawn in the previous second. */
        uint8_t     mFskip;         /**< Number of frames skipped in the previous second. */
        uint8_t     mFramedrawn;    /**< Running count of frames drawn. */
        uint8_t     mFrameskipped;  /**< Running count of frames skipped.*/
        uint8_t     mFrameinterval; /**< Represents the frame of the current sync group. */
        uint16_t    mTicksLeft;     /**< Contains the number of ticks the program exceded. */
        uint16_t    mLoopTime;      /**< Time taken on this loop. */
        uint16_t    mLoopTimeAvg;   /**< Average loop time. */
};

#endif // FRAMECTRL_H
