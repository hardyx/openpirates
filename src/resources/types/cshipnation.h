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

#ifndef CSHIPNATION_H
#define CSHIPNATION_H

#include "global.h"

/** @brief Defines if a nation uses a ship
 */
class CShipNation
{
    public:
        /** Constructor. */
        CShipNation();
        /** Destructor. */
        virtual ~CShipNation();

        // Getters
        bool    NationUsed( void )      const { return mNationUsed; }
        uint8_t NationTag( void )       const { return mNationTag; }
        // Setters
        void    NationUsed( bool v )    { mNationUsed = v; }
        void    NationTag( uint8_t v )  { mNationTag = v; }

    private:
        bool    mNationUsed;
        uint8_t mNationTag;
};

typedef std::vector<CShipNation*> vec_shipnat_t;

#endif // CSHIPNATION_H
