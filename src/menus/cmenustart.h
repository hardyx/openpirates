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

#ifndef CMENUSTART_H
#define CMENUSTART_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "menus/cmenuoptions.h"

class CMenustart
{
	public:
        CMenustart( CResources& resources );
		virtual ~CMenustart();

        int8_t Run( void );

    private:
        CResources&         mResources;
        CGraphic&           mScreen;
        CRole&              mPlayer;
        CManager<CString>&  mStrings;
        CManager<CGraphic>& mGraphics;
        CManagerWindow      mManagerwindow;
        CMenuOptions        mMenuOptions;
        bool mAutoselect;

		int8_t NewCareer( bool autoselect );
		int8_t GetTimePeriod( void );
		int8_t GetNation( void );
		int8_t GetName( void );
		int8_t GetDifficulty( void );
		int8_t GetSkill( void );
        int8_t LoadCareer( void );
        void NoActiveRole( void );
};

#endif // CMENUSTART_H
