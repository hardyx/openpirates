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

#ifndef CSIM_H
#define CSIM_H

#include "global.h"
#include "resources/cresources.h"
#include "modes/cmodebattle.h"
#include "sim/ccalander.h"

/** @brief Contains the logic to simulate random player/town/nation events.
 */
class CSimulate
{
    public:
        enum sim_events_list_t {
            SIM_EVENT_NONE=0    ,
            SIM_EVENT_SHIP      ,
            SIM_EVENT_MUTINY
        };

        /** @brief Constructor.
         * @param resources : reference to the resources object
         */
        CSimulate( CResources& resources );
        /** Destructor. */
        virtual ~CSimulate();

        uint8_t Run( void );

    private:
        CResources&         mResources;
        CManager<CString>&  mStrings;
        CCalander           mCalander;
        CDate               mCurrentDate;
        uint8_t mLoops;

        uint8_t PlayerEvents ( const std::string& date );
        void TownEvents( const  std::string& date );
        void NationEvents( const  std::string& date );
        bool CalcCrewMorale( void ) const;
        void StoreEvent( const std::string& date, const std::string& event );
        void StoreEvent( const std::string& date, const std::string& event, vec_string_t& variables );
        void ProcessText( vec_string_t& variables, std::string& text );
};

#endif // CSIM_H
