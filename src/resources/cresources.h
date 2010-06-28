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

#ifndef CRESOURCES_H
#define CRESOURCES_H

#include "global.h"
#include "resources/cdata.h"
#include "resources/coptions.h"
#include "resources/ccontrols.h"
#include "resources/types/cstring.h"
#include "resources/types/cgraphic.h"
#include "resources/types/csound.h"
#include "resources/types/cmap.h"
#include "resources/types/ceconomy.h"
#include "resources/types/cnation.h"
#include "resources/types/cnationeconomy.h"
#include "resources/types/cship.h"
#include "resources/types/cshipnation.h"
#include "resources/types/ctown.h"
#include "resources/types/ctowntimeperiod.h"
#include "resources/types/cmaplocation.h"
#include "resources/types/crole.h"

enum types_t {
    TYPE_NUL=0,
    TYPE_STR,
    TYPE_GFX,
    TYPE_SND,
    TYPE_MAP,
    TYPE_MON,
    TYPE_REP,
    TYPE_TIL,
    TYPE_TMP,
    TYPE_ECN,
    TYPE_NAT,
    TYPE_TWN,
    TYPE_ROL
};

class CResources
{
    public:
        CResources();
        virtual ~CResources();

        // Getters
        CGraphic&       Screen( void )      { return mScreen; }
        CData&          Data( void )        { return mData; }
        COptions&       Options( void )     { return mOptions; }
        CControls&      Controls( void )    { return mControls; }
        SDL_Joystick*   Joystick( void )    { return mpJoystick; }
        TTF_Font*       Font( void )        { return mpFont; }
        // Setters
        void Joystick( SDL_Joystick* v )    { mpJoystick = v; }
        void Font( TTF_Font* v )            { mpFont = v; }

        int8_t SetVideoMode( void );
        int8_t ToggleFullscreen( void );
        int8_t LoadResources( const std::string& file_path );
        int8_t LoadFont( void );
        int8_t LoadActiveRole( void );
        int8_t LoadActiveTowns( void );
        void Free_Font( void );

    private:
        CGraphic            mScreen;
        CData               mData;
        COptions            mOptions;
        CControls           mControls;
        SDL_Joystick*       mpJoystick;       // The joystick (if there is one)
        TTF_Font*           mpFont;           // The font

        CString*            LoadString              ( const std::string& line );
        CGraphic*           LoadGraphic             ( const std::string& line );
        CSound*             LoadSound               ( const std::string& line );
        CMap*               LoadMap                 ( const std::string& line );
        CStringValue*       LoadStringvalue         ( const std::string& line );
        CEconomy*           LoadEconomy             ( const std::string& line );
        CNation*            LoadNation              ( const std::string& line );
        CNationEconomy*     LoadNationEconomyLevel  ( const std::string& line );
        CShip*              LoadShip                ( const std::string& line );
        CShipNation*        LoadShipNation          ( const std::string& line );
        CTown*              LoadTown                ( const std::string& line );
        CTownTimePeriod*    LoadTownTimePeriod      ( const std::string& line );
        CMapLocation*       LoadTownMapLocation     ( const std::string& line );
        CRole*              LoadRole                ( const std::string& line );

        CResources(const CResources &);
        CResources & operator=(const CResources&);
};

#endif // CRESOURCES_H
