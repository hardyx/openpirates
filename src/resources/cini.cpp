/***
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

#include "cini.h"

CIni::CIni()
{
}

CIni::~CIni()
{
}

void CIni::GetDelimiters( const std::string& line, vec_uint16_t& delimiters, char delimiter )
{
    std::string::size_type location;
#ifdef DEBUG
    std::string debug;
#endif

    location = 0;
    delimiters.clear();
    delimiters.resize( delimiters.size()+1, line.find(DELIMIT_START) ); // After the equal is the data
    if (delimiter>0)
    {
        do {
            location = line.find(delimiter, location);
            if ( location != std::string::npos )
            {
                delimiters.resize( delimiters.size()+1, location );
                location++;
            }
        } while ( location != std::string::npos );
    }
    delimiters.resize( delimiters.size()+1, line.length() );  // Save the end as a delimiter

#ifdef DEBUG
    debug = line;
    for ( uint16_t i=0; i<delimiters.size(); i++ )
    {
        debug.append( i_to_a( delimiters.at(i) ) );
        debug.append( " " );
    }
    Log( "%s\n", debug.c_str() );
#endif
}

void CIni::EraseCharFromString( std::string& line, char character )
{
    bool blnString = false;
    char chr;

    for ( int16_t i=line.length()-1; i>=0; i-- )
    {
        chr = line.at(i);
        if ( chr == '\"' && character != '\"' )
        {
            if ( blnString == false )
            {
                blnString = true;
            }
            else if ( blnString == true )
            {
                blnString = false;
            }
        }

        if ( chr == character && !blnString )
        {
            line.erase( i, 1);   // Remove character
        }
    }
}

void CIni::ReplaceStringFromString( std::string& line, char find[], char copy[] )
{
    std::string::size_type location = 0;

    do {
        location = line.find( find, location );
        if ( location != std::string::npos )
        {
            line.replace( location, sizeof(copy), copy );
            location++;
        }
    } while ( location != std::string::npos );
}

int32_t CIni::ReadInteger( const std::string& line )
{
    int32_t value;
    std::string str;

    str = line.substr(line.find('=')+1);
    value = a_to_i( str );
    return value;
}

int32_t CIni::ReadSubInteger( const std::string& line, uint16_t pos1, uint16_t pos2 )
{
    int32_t value;
    std::string str;
    const char* temp;

    temp = line.c_str();
    str = line.substr(pos1, pos2);
    temp = str.c_str();
    value = a_to_i( str );
    return value;
}

bool CIni::ReadSubBool( const std::string& line, uint16_t pos1, uint16_t pos2 )
{
    bool result;

    std::string str = line.substr(pos1, pos2);

    if ( str.compare( TRUE ) == 0 )
    {
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}


std::string CIni::ReadString( const std::string& line )
{
    int8_t start, length;
    std::string str;

    start = line.find('=')+1;
    length = line.length()-start;
    str = line.substr( start, length );
    EraseCharFromString( str, '"' );
    EraseCharFromString( str, '\r' ); // Linux will leave a carriage return
    return str;
}

std::string CIni::ReadSubString( const std::string& line, uint16_t pos1, uint16_t pos2 )
{
    std::string str;

    str = line.substr( pos1, pos2 );
    EraseCharFromString( str, '"' );
    return str;
}

std::string CIni::WriteInteger( const std::string& id, int32_t value )
{
    std::string str = id;

    str += " = ";
    str += i_to_a(value);
    str += '\n';

    return str;
}

std::string CIni::WriteString( const std::string& id, const std::string& value )
{
    std::string str = id;

    str += " = \"" + value + "\"\n";

    return str;
}
