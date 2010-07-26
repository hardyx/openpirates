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

#ifndef CNATION_H
#define CNATION_H

#include "global.h"
#include "resources/types/cnationeconomy.h"

/** @brief Defines attributes for the a nation.
 */
class CNation
{
    public:
        enum nation_relations_t {
            NATION_PEACE=0  ,
            NATION_WAR      ,
            NATION_ALLIED
        };

        /** Constructor. */
        CNation();
        /** Destructor. */
        virtual ~CNation();

        // Getters
        uint8_t         Tag( void )                 const { return mTag; }
        bool            Amnesty( void )             const { return mAmnesty; }
        std::string&    Name( void )                      { return mName; }
        std::string&    GraphicPath( void )               { return mGraphicPath; }
        vec_natecon_t&  EconomySettings( void )           { return mEconomySettings; }
        vec_uint8_t&    Relations( void )                 { return mRelations; }
        // Setters
        void Tag( uint8_t v )                       { mTag = v; }
        void Amnesty( bool v )                      { mAmnesty = v; }
        void Name( const std::string& v )           { mName = v; }
        void GraphicPath( const std::string& v )    { mGraphicPath = v; }

        void SetRelations( uint8_t total );

    private:
        uint8_t         mTag;
        bool            mAmnesty;
        std::string     mName;
        std::string     mGraphicPath;
        vec_natecon_t   mEconomySettings;
        vec_uint8_t     mRelations;
};

#endif // CNATION_H
