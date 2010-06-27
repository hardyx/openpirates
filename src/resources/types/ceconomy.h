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

#ifndef CECONOMY_H
#define CECONOMY_H

#include "global.h"

class CEconomy
{
    public:
        CEconomy();
        virtual ~CEconomy();

        // Getters
        uint8_t         Tag( void )         { return mTag; }
        uint8_t         Forts( void )       { return mForts; }
        uint16_t        Population( void )  { return mPopulation; }
        uint16_t        Soldiers( void )    { return mSoldiers; }
        uint16_t        Gold( void )        { return mGold; }
        std::string&    Name( void )        { return mName; }
        // Setters
        void Tag( uint8_t v )               { mTag = v; }
        void Forts( uint8_t v )             { mForts = v; }
        void Population( uint16_t v )       { mPopulation = v; }
        void Soldiers( uint16_t v )         { mSoldiers = v; }
        void Gold( uint16_t v )             { mGold = v; }
        void Name( const std::string& v )   { mName = v; }

    private:
        uint8_t     mTag;
        uint8_t     mForts;
        uint16_t    mPopulation;
        uint16_t    mSoldiers;
        uint16_t    mGold;
        std::string mName;
};

#endif // CECONOMY_H
