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
 */

#ifndef CCALANDER_H
#define CCALANDER_H

#include "global.h"
#include "managers/cmanager.h"
#include "resources/types/cstringvalue.h"
#include "resources/types/cdate.h"

/**
 * @section DESCRIPTION
 * Provides date/time calculation and logic.
 */

class CCalander
{
    public:
        /** Constructor. */
        CCalander( CManager<CStringValue>& months );
        /** Destructor. */
        virtual ~CCalander();

        uint16_t TimeDuration( CDate& before, CDate& after );
        CDate AdvanceDate( CDate& now, uint16_t days );
        std::string DateToString( CDate& date );

    private:
        CManager<CStringValue>& mMonths;

        CCalander(const CCalander&);
        CCalander& operator=(const CCalander&);
};

#endif // CCALANDER_H
