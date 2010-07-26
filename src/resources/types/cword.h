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

#ifndef CWORD_H
#define CWORD_H

#include "global.h"

/** @brief Represents a word within a paragraph of text that is drawn on a window.
 */
class CWord
{
    public:
        /** @brief A collection vector of cword
        */
        typedef std::vector<CWord*> vec_word_t;

        /** Constructor. */
        CWord() :
            mImage      (),
            mRawword    (),
            mNewline    (false),
            mTabAlign   (0),
            mColAlign   (0),
            mParagraph  (0),
            mXpos       (0),
            mYpos       (0)
        {
        }
        /** Destructor. */
		virtual ~CWord() {};

        CGraphic    mImage;     /** The bitmap version of the text. */
        std::string mRawword;   /** The ascii text to be rendered. */
        bool        mNewline;   /** If the word should be followed by a newline. */
        uint8_t     mTabAlign;  /** Align the text to a tab. */
        uint8_t     mColAlign;  /** Align the text to a fixed column position. */
        uint8_t     mParagraph; /** The paragraph group that the word belongs to. */
        int16_t     mXpos;      /** X Position of the surface. */
        int16_t     mYpos;      /** Y Position of the surface. */
};

#endif // CWIND_H
