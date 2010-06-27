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

#ifndef CMENUTOWNOUT_H
#define CMENUTOWNOUT_H

#include "global.h"
#include "managers/cmanagerwindow.h"
#include "menus/cmenutownin.h"

class CMenutownout
{
    public:
        CMenutownout( CResources& resources );
        virtual ~CMenutownout();

        int8_t Run( int8_t entertype, int16_t town_index );

    private:
        CMenutownout(const CMenutownout &);
        CMenutownout & operator=(const CMenutownout&);
        int8_t EnterTown( void );
        int8_t AttackTown( void );
        int8_t SneakTown( void );

        CResources&         mResources;
        CGraphic&           mScreen;
        CManager<CString>&  mStrings;
        CManager<CGraphic>& mGraphics;
        CManagerWindow      mManagerwindow;
        CDyntown*           mpDyntown;
        CTown*              mpTown;
        CMenutownin*        mpMenutownin;
        int8_t              mEntertype;
};

#endif // CMENUTOWNOUT_H
