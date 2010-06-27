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

#ifndef CBATTLESHIPSTATS_H
#define CBATTLESHIPSTATS_H

#include "global.h"

class CBattleShipStats
{
    public:
        CBattleShipStats();
        virtual ~CBattleShipStats();

        // Getters
        uint8_t         ShipTag( void )     { return mShipTag; }
        uint8_t         AIType( void )      { return mAIType; }
        uint8_t         Damage( void )      { return mAIType; }
        uint16_t        Sailors( void )     { return mSailors; }
        uint16_t        Cannon( void )      { return mCannon; }
        uint16_t        Angle( void )       { return mAngle; }
        uint16_t        X( void )           { return mX; }
        uint16_t        Y( void )           { return mY; }
        uint16_t        Reload( void )      { return mReload; }
        std::string&    Title( void )       { return mTitle; }
        // Setters
        void ShipTag( uint8_t v )           { mShipTag = v; }
        void AIType( uint8_t v )            { mAIType = v; }
        void Sailors( uint16_t v )          { mSailors = v; }
        void Cannon( uint16_t v )           { mCannon = v; }
        void Title( const std::string& v )  { mTitle = v; }

    private:
        uint8_t     mShipTag;
        uint8_t     mAIType;
        uint16_t    mSailors;
        uint16_t    mCannon;
        uint16_t    mAngle;
        uint16_t    mX;
        uint16_t    mY;
        uint16_t    mReload;
        std::string mTitle;
};

#endif // CBATTLESHIPSTATS_H
