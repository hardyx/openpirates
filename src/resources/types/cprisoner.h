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

#ifndef CPRISONER_H
#define CPRISONER_H

#include "global.h"
#include "resources/types/cdate.h"

class CPrisoner
{
    public:
        CPrisoner();
        virtual ~CPrisoner();

        // Getters
        std::string&    Name( void )        { return mName; }
        uint8_t         Nation( void )      { return mNation; }
        bool            Pirate( void )      { return mPirate; }
        // Setters
        void Name( const std::string& v )   { mName = v; }
        void Nation( uint8_t v )            { mNation = v; }
        void Pirate( bool v )               { mPirate = v; }

        uint16_t RewardReputation( void );
        uint16_t RewardRansom( const CDate& current_date );

    private:
        bool        mPirate;
        uint8_t     mNation;
        uint8_t     mTitle;
        std::string mName;
        CDate       mCaptureDate;
};

typedef std::vector<CPrisoner> vec_prisoner_t;

#endif // CPRISONER_H
