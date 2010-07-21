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

#include "global.h"

// Global Variables
int16_t gSpriteAngleDirection[360][2];

#ifdef DEBUG
bool gDrawCollsionBox = false;
#endif

// Global Functions
void Log( const char* output, ... )
{
    va_list fmtargs;
    char buffer[1024];

    va_start( fmtargs, output );
    vsnprintf( buffer, sizeof(buffer)-1, output,  fmtargs );
    va_end( fmtargs );

    fprintf( stdout, "%s", buffer );
}

void Error( bool quit, const char* file, int line, const char* output, ... )
{
    va_list fmtargs;
    char buffer[1024];

    va_start( fmtargs, output );
    vsnprintf( buffer, sizeof(buffer)-1, output,  fmtargs );
    va_end( fmtargs );

    fprintf( stderr, "ERROR File: %s Line: %d Reason: %s", file, line, buffer );

    if (quit)
    {
        exit(-1);
    }
}

int8_t VerifyPointer( const char* file, int line, void* ptr )
{
    int8_t result = SIG_NONE;

    if (ptr==NULL) {
        Error( true, file, line, "null pointer\n" );
        result = SIG_FAIL;
    }
    return result;
}

int16_t getRandomValue( int16_t low, int16_t high )
{
    //srand((uint8_t)time(0) * rand()); // This is supposed to make the random number more random, but it doesnt seem to work
    return rand() % (high - low + 1) + low;
}

bool getProbability(unsigned short prob)
{
    return ( (rand()%100) <= prob ) ? true : false;
}

int32_t a_to_i( const std::string& line )
{
    int32_t number;

    std::stringstream ss( line.c_str() );
    ss >> number;       // Convert string to integer
    return number;
}

std::string i_to_a( int32_t num )
{
    std::string str;
    std::stringstream ss;

    ss << num;
    ss >> str;          // Convert string to integer
    return str;
}

std::string Spaces( int count )
{
    std::string output;

    output.clear();
    for ( int i=0; i<count; i++ )
    {
        output.append( " " );
    }

    return output;
}
