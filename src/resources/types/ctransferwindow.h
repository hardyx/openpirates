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

#ifndef CTRANSFERWINDOW_H
#define CTRANSFERWINDOW_H

#include "global.h"
#include "cwindow.h"
#include "ccargo.h"
#include "resources/cresources.h"

/** @brief This class represents a special interactive window which is only used to transfer items.
 */
class CTransferWindow : public CWindow
{
    public:
        #define TRANSFER_TRADE      0
        #define TRANSFER_PLUNDER    1
        #define UNLIMITED_SPACE     -1
        #define TRANSER_ALL         0
        #define TRANSER_ONE         1

        #define COLUMN_SPACES       10
        #define ARROW_SIDE_SPACES   5
        #define DIGITS              7

        #define BACKSLASH_n     "\\n" // end section on a new line (not selectable)
        #define BACKSLASH_u     "\\u" // end section on the current line (not selectable)
        #define BACKSLASH_s     "\\s" // end section on a new line and preceding line text is selectable
        #define BACKSLASH_z     "\\z" // end section on the current line and preceding line text is selectable
        #define BACKSLASH_t04   "\\t04"  // align the current word
        #define BACKSLASH_t08   "\\t08"
        #define BACKSLASH_t12   "\\t12"
        #define BACKSLASH_t16   "\\t16"
        #define BACKSLASH_t20   "\\t20"
        #define BACKSLASH_t24   "\\t24"

        /** @brief Constructor.
         * @param resources : reference to the resources object
         */
        CTransferWindow( CResources& resources );
        /** Destructor. */
        virtual ~CTransferWindow();

        int8_t Run( int type, const std::string& namea, const std::string& nameb,
                    CCargo& cargoa , CCargo& cargob );

    private:
        CResources&         mResources;
        CGraphic&           mScreen;
        CManager<CString>&  mStrings;
        CSpriteDynamic      mPointer;
        CGraphic*           mpBorder;

        std::string     mGoldUnit;
        std::string     mGoldCountA;
        std::string     mGoldCountB;
        std::string     mHoldSpace;

        int8_t          mType;
        uint16_t        mHoldSpaceCnt;
        uint32_t        mGoldA, mGoldB;
        int16_t         mSpaceA, mSpaceB;

        void BuildText( const std::string& namea, const std::string& nameb,
                        CCargo& cargoa, CCargo& cargob );
        std::string BuildGold( uint32_t counta, uint32_t countb, const std::string& name );
        std::string BuildNames( const std::string& namea, const std::string& nameb );
        std::string BuildGood( CGood& gooda, CGood& goodb );
        std::string BuildTransferAll( void );
        std::string BuildShipHold( void );
        std::string BuildContinue( void );
        int16_t PlayerShipSpace( void );
        void Transfer( uint16_t unit_amount,
                       uint32_t& gold_src, uint32_t& gold_dst,
                       int16_t& space_src, int16_t& space_dst,
                       CGood& good_src, CGood& good_dst );

        CTransferWindow(const CTransferWindow&);
        CTransferWindow& operator=(const CTransferWindow&);
};

#endif // CTRANSFERWINDOW_H
