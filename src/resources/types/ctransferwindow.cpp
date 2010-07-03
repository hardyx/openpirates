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

#include "ctransferwindow.h"

CTransferWindow::CTransferWindow( CResources& resources ) :
    CWindow         (resources.Options().Controls()),
    mResources      (resources),
    mScreen         (mResources.Screen()),
    mStrings        (mResources.Data().Strings()),
    mPointer        (),
    mpBorder        (mResources.Data().Graphics().Find(GFX_BORDER)),
    mGoldUnit       (),
    mGoldCountA     (),
    mGoldCountB     (),
    mHoldSpace      (),
    mType           (0),
    mHoldSpaceCnt   (0),
    mGoldA          (0),
    mGoldB          (0),
    mSpaceA         (0),
    mSpaceB         (0)
{
    mPointer.Open( 0, 0, ANI_NONE, 0, 1, 0, 0, false, true );
    mPointer.AssignGraphic( mResources.Data().Graphics().Find(GFX_POINTER) );

    mpText      = new std::string;
    mpVariables = new vec_string_t;
}

CTransferWindow::~CTransferWindow()
{
    delete mpVariables;
    delete mpText;
}

int8_t CTransferWindow::Run( int type, const std::string& namea, const std::string& nameb,
                             CCargo& cargoa, CCargo& cargob )
{
    int8_t result = SIG_NONE;
    bool done;

    mType       = type;
    mDimensions.x = 100;
    mDimensions.x = 100;
    mDimensions.w = 500;
    mDimensions.h = 200;
    mGoldA = cargoa.Gold().Count();
    mGoldB = cargob.Gold().Count();
    mGoldUnit = cargoa.Gold().Unit();

    mSpaceA = PlayerShipSpace();
    if (mType == TRANSFER_PLUNDER) {
        mSpaceB = 100;   // TBD
    }
    else {
        mSpaceB = UNLIMITED_SPACE;
    }

    done = false;
    while( done == false && result >= SIG_NONE )
    {
        BuildText( namea, nameb, cargoa, cargob );
        Reprocess();

        // Start with a dark blue background
        SDL_FillRect(mScreen.Image(), NULL, SDL_MapRGB( mScreen.Image()->format, 0x00, 0x00, 0x40 ) );

        result = Activate( mResources,
                           mpBorder,
                           mPointer,
                           mResources.Font() );

        switch( result )
        {
            // Food
            case 1:
                Transfer( TRANSER_ALL, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.Food(), cargoa.Food() );
                break;
            case 2:
                Transfer( TRANSER_ONE, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.Food(), cargoa.Food() );
                break;
            case 3:
                Transfer( TRANSER_ONE, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.Food(), cargob.Food() );
                break;
            case 4:
                Transfer( TRANSER_ALL, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.Food(), cargob.Food() );
                break;
            // Good A
            case 5:
                Transfer( TRANSER_ALL, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.GoodTypeA(), cargoa.GoodTypeA() );
                break;
            case 6:
                Transfer( TRANSER_ONE, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.GoodTypeA(), cargoa.GoodTypeA() );
                break;
            case 7:
                Transfer( TRANSER_ONE, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.GoodTypeA(), cargob.GoodTypeA() );
                break;
            case 8:
                Transfer( TRANSER_ALL, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.GoodTypeA(), cargob.GoodTypeA() );
                break;
            // Good B
            case 9:
                Transfer( TRANSER_ALL, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.GoodTypeB(), cargoa.GoodTypeB() );
                break;
            case 10:
                Transfer( TRANSER_ONE, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.GoodTypeB(), cargoa.GoodTypeB() );
                break;
            case 11:
                Transfer( TRANSER_ONE, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.GoodTypeB(), cargob.GoodTypeB() );
                break;
            case 12:
                Transfer( TRANSER_ALL, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.GoodTypeB(), cargob.GoodTypeB() );
                break;
            // Cannon
            case 13:
                Transfer( TRANSER_ALL, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.Cannon(), cargoa.Cannon() );
                break;
            case 14:
                Transfer( TRANSER_ONE, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.Cannon(), cargoa.Cannon() );
                break;
            case 15:
                Transfer( TRANSER_ONE, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.Cannon(), cargob.Cannon() );
                break;
            case 16:
                Transfer( TRANSER_ALL, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.Cannon(), cargob.Cannon() );
                break;
            // Everything
            case 17:
                Transfer( TRANSER_ALL, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.Food(),      cargoa.Food()      );
                Transfer( TRANSER_ALL, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.GoodTypeA(), cargoa.GoodTypeA() );
                Transfer( TRANSER_ALL, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.GoodTypeB(), cargoa.GoodTypeB() );
                Transfer( TRANSER_ALL, mGoldB, mGoldA, mSpaceB, mSpaceA, cargob.Cannon(),    cargoa.Cannon()    );
                break;
            case 18:
                Transfer( TRANSER_ALL, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.Food(),      cargob.Food()      );
                Transfer( TRANSER_ALL, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.GoodTypeA(), cargob.GoodTypeA() );
                Transfer( TRANSER_ALL, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.GoodTypeB(), cargob.GoodTypeB() );
                Transfer( TRANSER_ALL, mGoldA, mGoldB, mSpaceA, mSpaceB, cargoa.Cannon(),    cargob.Cannon()    );
                break;
            case 19:
                done = true;
                result = SIG_NONE;
                break;
            default:
                Error( __FILE__, __LINE__, "menu index out of range\n" );
                result = SIG_FAIL;
                break;
        }
    }

    cargoa.Gold().Count(mGoldA);
    cargob.Gold().Count(mGoldB);

    return result;
}

void CTransferWindow::BuildText( const std::string& namea, const std::string& nameb,
                                 CCargo& cargoa, CCargo& cargob )
{
    mpText->clear();
    mpVariables->clear();

    // Transfer gold automatically
    if ( mType == TRANSFER_PLUNDER )
    {
        cargoa.Gold_Inc( mGoldA );
        mpText->append( mStrings.Find( STR_CAR_PLUNDERGOLD )->Text() );
        mGoldCountA = i_to_a( mGoldB );
        mpVariables->resize( mpVariables->size()+1, &mGoldCountA );
    }

    mpText->append( BuildNames( namea, nameb ) );
    mpText->append( BuildGold( mGoldA, mGoldB,     cargob.Gold().Name() ) );
    mpText->append( BuildGood( cargoa.Food(),      cargob.Food() ) );
    mpText->append( BuildGood( cargoa.GoodTypeA(), cargob.GoodTypeA() ) );
    mpText->append( BuildGood( cargoa.GoodTypeB(), cargob.GoodTypeB() ) );
    mpText->append( BuildGood( cargoa.Cannon(),    cargob.Cannon() ) );
    mpText->append( BuildTransferAll() );
    mpText->append( BuildShipHold() );
    mpText->append( BuildContinue() );
}

std::string CTransferWindow::BuildNames( const std::string& namea, const std::string& nameb )
{
    std::string output;

    output.clear();
    output.append(BACKSLASH_t08);
    output.append(namea);
    output.append(BACKSLASH_u);
    output.append(BACKSLASH_t24);
    output.append(nameb);
    output.append(BACKSLASH_n);

    return output;
}

std::string CTransferWindow::BuildGold( uint32_t counta, uint32_t countb,
                                        const std::string& name )
{
    std::string output;
    std::string goodcnta, goodcntb;

    goodcnta = i_to_a( counta );
    goodcntb = i_to_a( countb );

    output.clear();
    output.append(name);
    output.append(BACKSLASH_u);
    output.append(BACKSLASH_t08);
    output.append(goodcnta);    // Left gold
    output.append(BACKSLASH_u);
    output.append(BACKSLASH_t12);
    output.append(mGoldUnit);
    output.append(BACKSLASH_u);
    output.append(BACKSLASH_t24);
    output.append(goodcntb);    // Right gold
    output.append(BACKSLASH_u);
    output.append(BACKSLASH_t12);
    output.append(mGoldUnit);
    output.append(BACKSLASH_n);

    return output;
}

std::string CTransferWindow::BuildGood( CGood& gooda, CGood& goodb )
{
    std::string output;
    std::string goodcnta, goodcntb;

    goodcnta = i_to_a( gooda.Count() );
    goodcntb = i_to_a( goodb.Count() );

    output.clear();
    output.append(goodb.Name());   // Left good
    output.append(BACKSLASH_u);
    output.append(BACKSLASH_t08);
    output.append(goodcnta);
    output.append(BACKSLASH_u);
    if (goodb.Unit().length() <= 0) {
        output.append(BACKSLASH_t16);
    }
    else {
        output.append(BACKSLASH_t04);
        output.append(goodb.Unit());
        output.append(BACKSLASH_u);
        output.append(BACKSLASH_t04);
    }
    output.append("<< ");           // Middle trasfer buttons
    output.append(BACKSLASH_z);
    output.append("<- ");
    output.append(BACKSLASH_z);
    output.append(" ->");
    output.append(BACKSLASH_z);
    output.append(" >>" );
    output.append(BACKSLASH_z);
    output.append(BACKSLASH_u);
    output.append(BACKSLASH_t04);
    output.append(goodcntb);          // Right good
    output.append(BACKSLASH_u);
    if (goodb.Unit().length() <= 0) {
        output.append(BACKSLASH_t24);
    }
    else {
        output.append(BACKSLASH_t04);
        output.append(goodb.Unit());
        output.append(BACKSLASH_u);
    }
    // Price
    if ( mType == TRANSFER_TRADE ) {
        output.append(BACKSLASH_t08);
        output.append(i_to_a(goodb.Price()));
        output.append(BACKSLASH_u);
        output.append(BACKSLASH_t04);
        output.append(mGoldUnit);
        output.append(BACKSLASH_n);
    }
    else {
        output.append(BACKSLASH_n);
    }

    return output;
}

int16_t CTransferWindow::PlayerShipSpace( void )
{
    int8_t tag;
    int16_t space;
    CShip* ship;

    space = 0;
    for( int i=0; i<GAME_MAXSHIPS; i++ )
    {
        tag = mResources.Data().Player().Ships(i).Tag();
        if (tag>0)
        {
            ship = mResources.Data().Ships().At(tag);
            space += ship->CargoSpace();
        }
    }

    return space;
}

std::string CTransferWindow::BuildTransferAll( void )
{
    std::string output;

    output.clear();
    output.append(BACKSLASH_u);
    output.append(BACKSLASH_t16);
    output.append("<<");
    output.append(BACKSLASH_z);
    output.append("           ");
    output.append(BACKSLASH_u);
    output.append(">>");
    output.append(BACKSLASH_s);

    return output;
}

std::string CTransferWindow::BuildShipHold( void )
{
    std::string output;

    // Space left in ship hold
    output.clear();
    mpText->append( mStrings.Find( STR_CAR_SHIPHOLD )->Text() );
    mHoldSpace = i_to_a(mSpaceA);
    mpVariables->resize( mpVariables->size()+1, &mHoldSpace );
    output.append(BACKSLASH_n);

    return output;
}

std::string CTransferWindow::BuildContinue( void )
{
    std::string output;

    output.clear();
    output.append("Continue");
    output.append(BACKSLASH_s);

    return output;
}

void CTransferWindow::Transfer( uint16_t unit_amount,
                                uint32_t& gold_src, uint32_t& gold_dst,
                                int16_t& space_src, int16_t& space_dst,
                                CGood& good_src, CGood& good_dst )
{
    uint8_t  unit_price;
    uint16_t total_price;

    // Make sure a transfer can occur
    if (good_src.Count() <= 0 || space_dst== 0)
        return;

    // Start with the max amount the source has
    if (unit_amount==0)
        unit_amount = good_src.Count();

    // Limit by destinations available space
    if (space_dst != UNLIMITED_SPACE)
    {
        if (unit_amount > space_dst)
        {
            unit_amount = space_dst;
        }
    }

    // Limit by destinations gold total
    if (mType == TRANSFER_TRADE)
    {
        // No gold no sale!
        if (gold_dst <= 0)
            return;

        unit_price  = good_dst.Price();
        total_price = unit_amount*unit_price;
        if (total_price > gold_dst)
        {
            unit_amount = gold_dst/unit_price;
            total_price = unit_amount*unit_price;
        }

        // Transfer the gold
        gold_dst -= total_price;
        gold_src += total_price;
    }

    // Transfer the goods
    good_src.Count_Inc(-unit_amount);
    good_dst.Count_Inc( unit_amount);

    // Adjust the available space
    if (space_src != UNLIMITED_SPACE)
        space_src += unit_amount;
    if (space_dst != UNLIMITED_SPACE)
        space_dst -= unit_amount;
}
