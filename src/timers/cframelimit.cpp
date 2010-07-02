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

#include "cframelimit.h"

CFramelimit::CFramelimit( void ) :
    tmrFrameSync    (),
    tmrFrameSingle  (),
    tmrFPSCalculate (),
    mFrameSkip      (false),
    mFps            (0),
    mFskip          (0),
    mFramedrawn     (0),
    mFrameskipped   (0),
    mFrameinterval  (0),
    mTicksLeft      (0)
{
    printf( "Framelimit: msec/frame %d msec/sync %d\n", MS_PER_FRAME, MS_PER_SYNC );
}

CFramelimit::~CFramelimit()
{
}

void CFramelimit::ControlFPS( bool limit, bool calc )
{
    int16_t delay;
    int16_t ticks;
    int16_t duration;

    // A frame has been drawn
    if (mFrameSkip == true)
        mFrameskipped++;
    else
        mFramedrawn++;


    //Calculate the FPS every second
    if ( calc )
    {
        if ( !tmrFPSCalculate.is_started() )
        {
            tmrFPSCalculate.start();
        }
        else
        {
            // After 1 sec
            if ( tmrFPSCalculate.get_ticks() >= MS_PER_SECOND )
            {
                mFps            = mFramedrawn;
                mFskip          = mFrameskipped;
                mFramedrawn     = 0;
                mFrameskipped   = 0;
                tmrFPSCalculate.start();
#ifdef DEBUG
                printf( "FPS Total: %d Drawn: %d Skipped: %d\n", mFps+mFskip, mFps, mFskip );
#endif
            }
        }
    }

    //Cap the frame rate
    if ( limit )
    {
        mFrameinterval++;

        //mFrameSkip = false;
        if ( !tmrFrameSync.is_started() || !tmrFrameSingle.is_started() )
        {
            tmrFrameSync.start();
            tmrFrameSingle.start();
            mFrameinterval = 0;
        }
        else
        {
            // Calculate the delay
            if (mFrameinterval < SYNC_FRAME)
            {
                ticks = tmrFrameSingle.get_ticks();
                duration = MS_PER_FRAME;
            }
            else
            {
                ticks = tmrFrameSync.get_ticks();
                duration = MS_PER_SYNC;
            }
            delay = duration - mTicksLeft - ticks;

            if (delay > 0 && delay < MS_PER_SECOND) // Time left
            {
                tmrFrameSingle.delay( delay );
                mFrameSkip = false;
                mTicksLeft = 0;
            }
            else if (delay < 0)                     // Time was excedded
            {
                mFrameSkip = true;
                mTicksLeft = abs(delay);
            }

            //printf( "%d T:%4d D:%4d L:%4d\n", mFrameinterval, ticks, delay, mTicksLeft );

            // Reset timers
            if (mFrameinterval >= SYNC_FRAME)
            {
                tmrFrameSync.start();
                mFrameinterval = 0;
                if (mTicksLeft>MS_PER_SECOND)
                    mTicksLeft = 0;
            }
            tmrFrameSingle.start();
        }
    }
}
