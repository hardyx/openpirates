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

#ifndef CSTRINGVALUE_H
#define CSTRINGVALUE_H

#include "global.h"
#include "resources/types/cstring.h"

/**
 * @section DESCRIPTION
 * Defines a integer vlaue to a string name.
 */

class CStringValue : public CString
{
    public:
        /** Constructor. */
        CStringValue( int16_t value, const std::string& text );
        /** Destructor. */
        virtual ~CStringValue();

        // Getters
        uint16_t    Value( void )       { return mValue; }
        // Setters
        void        Value( uint16_t v ) { mValue = v; }

    private:
        uint16_t    mValue;
};

#endif // CSTRINGVALUE_H
