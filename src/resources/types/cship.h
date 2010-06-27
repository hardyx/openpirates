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

#ifndef CSHIP_H
#define CSHIP_H

#include "global.h"
#include "resources/types/cshipnation.h"

class CShip
{
    public:
        CShip();
        virtual ~CShip();

        // Getters
        uint8_t         Tag( void )         { return mTag; }
        uint8_t         Cannon( void )      { return mCannon; }
        uint8_t         Speed( void )       { return mSpeed; }
        uint8_t         SailType( void )    { return mSailType; }
        uint16_t        Crew( void )        { return mCrew; }
        uint16_t        CargoSpace( void )  { return mCargoSpace; }
        uint16_t        HP( void )          { return mHP; }
        uint16_t        Value( void )       { return mValue; }
        std::string&    Name( void )        { return mName; }
        std::string&    GraphicPath( void ) { return mGraphicPath; }
        vec_shipnat_t&  ShipNations( void ) { return mShipNations; }
        // Setters
        void Tag( uint8_t v )                       { mTag = v; }
        void Cannon( uint8_t v )                    { mCannon = v; }
        void Speed( uint8_t v )                     { mSpeed = v; }
        void SailType( uint8_t v )                  { mSailType = v; }
        void Crew( uint16_t v )                     { mCrew = v; }
        void CargoSpace( uint16_t v )               { mCargoSpace = v; }
        void HP( uint16_t v )                       { mHP = v; }
        void Value( uint16_t v )                    { mValue = v; }
        void Name( const std::string& v )           { mName = v; }
        void GraphicPath( const std::string& v )    { mGraphicPath = v; }

    private:
        uint8_t         mTag;
        uint8_t         mCannon;
        uint8_t         mSpeed;
        uint8_t         mSailType;
        uint16_t        mCrew;
        uint16_t        mCargoSpace;
        uint16_t        mHP;
        uint16_t        mValue;
        std::string     mName;
        std::string     mGraphicPath;
        vec_shipnat_t   mShipNations;
};

#endif // CSHIP_H
