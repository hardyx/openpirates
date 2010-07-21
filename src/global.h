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

/**
 * @section DESCRIPTION
 * This file contains types, functions, variables that should be available to all classes.
 */

// Global Types
typedef std::vector<bool>               vec_bool_t;
typedef std::vector<uint8_t>            vec_uint8_t;
typedef std::vector<uint16_t>           vec_uint16_t;
typedef std::vector<std::string*>       vec_string_t;

// Global Functions
/**
 * Prints a normal message in char format to be putput to stdout.
 * @param output : the formatted char.
 * @param ... the variables for the formatting.
 */
void Log( const char* output, ... );

/**
 * Prints a error message in char format to be putput to stderr.
 * @param quit : kill the program after sending the message.
 * @param file : the source file from which the message originated.
 * @param line : the line number in the source file.
 * @param output : the formatted char.
 * @param ... : the variables for the formatting.
 */
void Error( bool quit, const char* file, int line, const char* output, ... );

/**
 * Checks for a null pointer.
 * @param file : the source file from which the pointer originated.
 * @param line : the line number in the source file.
 * @param ptr : the pointer.
 * @return result of the pointer check
 */
int8_t VerifyPointer( const char* file, int line, void* ptr );

/**
 * Genereates a random 16 bit number.
 * @param min : the smallest the random number can be.
 * @param max : the largest the random number can be.
 * @param ptr : the pointer.
 * @return the random number
 */
int16_t getRandomValue( int16_t min, int16_t max );

/**
 * Determines if an action can occur. Like rolling the dice.
 * @param prob : the precentage that the action can occur.
 * @return true if the action should occur.
 */
bool getProbability( uint16_t prob );

/**
 * Converts an ascii string to an integer form.
 * @param line : the string to convert.
 * @return the numerical form of the string.
 */
int32_t a_to_i( const std::string& line );

/**
 * Converts an integer string to an ascii form.
 * @param num : integer to convert.
 * @return the string form of the number.
 */
std::string i_to_a( int32_t num );

/**
 * Returns a number of spaces in a string.
 * @param count : the number of spaces to generate.
 * @return the string with spaces.
 */
std::string Spaces( int count );

#endif // GLOBAL_H
