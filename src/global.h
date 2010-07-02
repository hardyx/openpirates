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

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdint.h>
#include <math.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "constants.h"

// Global Types
typedef std::vector<bool>               vec_bool_t;
typedef std::vector<uint8_t>            vec_uint8_t;
typedef std::vector<uint16_t>           vec_uint16_t;
typedef std::vector<std::string*>       vec_string_t;

// Global Functions
void Log( const char* output, ... );
void Error( const char* file, int line, const char* output, ... );
int8_t VerifyPointer( const char* file, int line, void* ptr );
int16_t getRandomValue( int16_t min, int16_t max );
bool getProbability( uint16_t prob );
int32_t a_to_i( const std::string& line );
std::string i_to_a( int32_t num );
std::string Spaces( int count );

#endif // GLOBAL_H
