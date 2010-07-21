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

#ifndef CINI_H
#define CINI_H

#include "global.h"

/**
 * @section DESCRIPTION
 * This class provides tools for interfacing with the applications conf file system.
 */

#define DELIMIT_NONE    0
#define DELIMIT_START   '='
#define DELIMIT_DEFAULT ','

class CIni
{
    public:
        /** Constructor. */
        CIni();
        /** Destructor. */
        virtual ~CIni();

        void GetDelimiters( const std::string& line, vec_uint16_t& delimiters, char delimiter=DELIMIT_DEFAULT );
        void EraseCharFromString( std::string& line, char character );
        void ReplaceStringFromString( std::string& line, char find[], char copy[] );
        int32_t ReadInteger( const std::string& line );
        int32_t ReadSubInteger( const std::string& line, uint16_t pos1, uint16_t pos2 );
        bool ReadSubBool( const std::string& line, uint16_t pos1, uint16_t pos2 );
        std::string ReadString( const std::string& line );
        std::string ReadSubString( const std::string& id, uint16_t pos1, uint16_t pos2 );
        std::string WriteInteger( const std::string& id, int32_t value );
        std::string WriteString( const std::string& id, const std::string& value );
};

#endif // CINI_H
