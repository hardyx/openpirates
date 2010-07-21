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

#ifndef CSOUND_H
#define CSOUND_H

#include "global.h"

/**
 * @section DESCRIPTION
 * Container for sound data
 */

class CSound
{
	public:
        /** Constructor. */
        CSound( const std::string& path );
        /** Destructor. */
		virtual ~CSound();

        // Getters
        uint16_t        Tag( void )         { return mTag; }
        std::string&    Path( void )        { return mPath; }
        // Setters
        void            Tag( uint16_t v )   { mTag = v; }

    private:
        uint16_t    mTag;
        std::string mPath;
};

#endif // CSOUND_H
