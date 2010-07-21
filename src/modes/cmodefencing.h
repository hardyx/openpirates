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

#ifndef CMODEFENCING_H
#define CMODEFENCING_H

#include "global.h"
#include "sprites/cspritedynamic.h"

enum fencing_list_t {
    FENCING_WIN=0    ,
    FENCING_ESCAPE   ,
    FENCING_LOSE
};

/**
 * @section DESCRIPTION
 * The fencing mode loop
 */

class CModeFencing
{
    public:
        /** Constructor. */
        CModeFencing();
        /** Destructor. */
        virtual ~CModeFencing();

        int8_t Run( void );

    private:
        CSpriteDynamic  mSwordsmanP1;
        CSpriteDynamic  mSwordsmanAI;
};

#endif // CMODEFENCING_H

