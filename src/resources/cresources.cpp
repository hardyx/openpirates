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

#include "resources/cresources.h"

CResources::CResources() :
    mScreen     (),
    mData       (),
    mOptions    (),
    mControls   (),
    mpJoystick  (NULL),
    mpFont      (NULL)
{
}

CResources::~CResources()
{
  	Log( "CResources Released!\n" );
}

int8_t CResources::SetVideoMode( void )
{
    SDL_Surface* screen;
    int8_t result = SIG_NONE;
    uint32_t flags = 0;

    // Assign video mode flags
    flags = SDL_HWSURFACE;
    if ( mOptions.Screen().Fullscreen() == true )
    {
        flags |= SDL_FULLSCREEN;
    }
    if ( mOptions.Screen().Doublebuf() == true )
    {
        flags |= SDL_DOUBLEBUF;
    }

    screen = SDL_SetVideoMode( mOptions.Screen().Width(),
                               mOptions.Screen().Height(),
                               mOptions.Screen().Bpp(),
                               flags );
    if ( screen == NULL)
    {
        Error( __FILE__, __LINE__, "Couldn't set SDL video mode with %dx%dx%d with flags %X: %s\n",
               mOptions.Screen().Width(),
               mOptions.Screen().Height(),
               mOptions.Screen().Bpp(),
               flags,
               SDL_GetError() );
        result = SIG_FAIL;
    }
    else
    {
        mScreen.AssignImage(screen, false);
        Log( "CResources::AssignScreenImage Screen Loaded!\n" );

        SDL_ShowCursor( SDL_DISABLE );

        #if defined(WIN32) || defined(LINUX)
            SDL_WM_SetCaption( TITLE, NULL );
        #endif
    }

	return result;
}

int8_t CResources::ToggleFullscreen( void )
{
    int8_t result = SIG_NONE;
    bool fmode;

    // Invert the current state
    fmode = mOptions.Screen().Fullscreen();
    mOptions.Screen().Fullscreen(!fmode);

    // Set video mode
	if ( result == SIG_NONE )
	{
        result = SetVideoMode();
	}

	return result;
}

void CResources::Free_Font( void )
{
    TTF_CloseFont( mpFont );	//Close the font
}

int8_t CResources::LoadResources( const std::string& file_path )
{
    int8_t result = SIG_NONE;
    std::ifstream fin;
    std::string line;
    int8_t lasttype = TYPE_NUL;
    bool verbose;
    const char * temp;

    // Get resource information from file
    if ( file_path.length() > 0 )
    {
        fin.open( file_path.c_str() );
        if ( fin.is_open() )
        {
            while ( !fin.eof() )
            {
                getline( fin, line );
                if ( line.find("//") != 0 )    // Check if line is a comment line
                {
                    Options().EraseCharFromString( line, ' ' );
                    Options().EraseCharFromString( line, '\"' );
                    Options().EraseCharFromString( line, '\r' ); // Linux will leave a carriage return

                    temp = line.c_str();

                    verbose = true;
                    if (      line.find( CFG_STRING ) == 0 )
                    {
                        CString* string = LoadString(line);
                        if ( string != NULL )
                        {
                            if (lasttype == TYPE_STR)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_STR;

                            mData.Strings().Add(string, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_GRAPHIC ) == 0 )
                    {
                        CGraphic* graphic = LoadGraphic(line);
                        if ( graphic != NULL )
                        {
                            if (lasttype == TYPE_GFX)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_GFX;

                            mData.Graphics().Add(graphic, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_SOUND ) == 0 )
                    {
                        CSound* sound = LoadSound(line);
                        if ( sound != NULL )
                        {
                            if (lasttype == TYPE_SND)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_SND;

                            mData.Sounds().Add(sound, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_MAP ) == 0 )
                    {
                        CMap* map = LoadMap(line);
                        if ( map != NULL )
                        {
                            lasttype = TYPE_MAP;

                            mData.Maps().Add(map, true);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_MONTH ) == 0 )
                    {
                        CStringValue* month = LoadStringvalue(line);
                        if ( month != NULL )
                        {
                            if (lasttype == TYPE_MON)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_MON;

                            mData.Months().Add(month, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_REP ) == 0 )
                    {
                        CStringValue* rep = LoadStringvalue(line);
                        if ( rep != NULL )
                        {
                            if (lasttype == TYPE_REP)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_REP;

                            mData.Reputations().Add(rep, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_TITLE ) == 0 )
                    {
                        CStringValue* title = LoadStringvalue(line);
                        if ( title != NULL )
                        {
                            if (lasttype == TYPE_TIL)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_TIL;

                            mData.Titles().Add(title, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_TIMEPERIOD ) == 0 )
                    {
                        CStringValue* timeperiod = LoadStringvalue(line);
                        if ( timeperiod != NULL )
                        {
                            if (lasttype == TYPE_TMP)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_TMP;

                            mData.Timeperiods().Add(timeperiod, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_ECONOMY ) == 0 )
                    {
                        CEconomy* economy = LoadEconomy(line);
                        if ( economy != NULL )
                        {
                            if (lasttype == TYPE_ECN)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_ECN;

                            mData.Economies().Add(economy, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_NATION ) == 0 )
                    {
                        CNation* nation = LoadNation(line);
                        if ( nation != NULL )
                        {
                            if (lasttype == TYPE_NAT)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_NAT;

                            mData.Nations().Add(nation, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_NEL ) == 0 )
                    {
                        if ( mData.Nations().Size() > 0 )
                        {
                            CNation* nation = mData.Nations().Back();
                            CNationEconomy* nel = LoadNationEconomyLevel(line);
                            if ( nel != NULL )
                            {
                                nation->EconomySettings().resize( nation->EconomySettings().size()+1, nel );
                            }
                            else
                            {
                                Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                                return result = SIG_FAIL;
                            }
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: No parent objects to add child object to!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_SHIP ) == 0 )
                    {
                        CShip* ship = LoadShip(line);
                        if ( ship != NULL )
                        {
                            if (lasttype == TYPE_NAT)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_NAT;

                            mData.Ships().Add(ship, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_SHIPNATION ) == 0 )
                    {
                        if ( mData.Ships().Size() > 0 )
                        {
                            CShip* ship = mData.Ships().Back();
                            CShipNation* shipnation = LoadShipNation(line);
                            if ( shipnation != NULL )
                            {
                                ship->ShipNations().resize( ship->ShipNations().size()+1, shipnation );
                            }
                            else
                            {
                                Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                                return result = SIG_FAIL;
                            }
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: No parent objects to add child object to!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_TOWN ) == 0 )
                    {
                        CTown* town = LoadTown(line);
                        if ( town != NULL )
                        {
                            if (lasttype == TYPE_TWN)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_TWN;

                            mData.Towns().Add(town, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_TTP ) == 0 )
                    {
                        if ( mData.Towns().Size() > 0 )
                        {
                            CTown* town = mData.Towns().Back();
                            CTownTimePeriod* ttp = LoadTownTimePeriod(line);
                            if ( ttp != NULL )
                            {
                                town->TownTimePeriods().resize( town->TownTimePeriods().size()+1, ttp );
                            }
                            else
                            {
                                Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                                return result = SIG_FAIL;
                            }
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: No parent objects to add child object to!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_MAPLOC ) == 0 )
                    {
                        if ( mData.Towns().Size() > 0 )
                        {
                            CTown* town = mData.Towns().Back();
                            CMapLocation* maploc = LoadTownMapLocation(line);
                            if ( maploc != NULL )
                            {
                                town->Location(*maploc);
                            }
                            else
                            {
                                Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                                return result = SIG_FAIL;
                            }
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: No parent objects to add child object to!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                    else if ( line.find( CFG_ROLE ) == 0 )
                    {
                        CRole* role = LoadRole( line);
                        if ( role != NULL )
                        {
                            if (lasttype == TYPE_ROL)
                            {
                                verbose = false;
                            }
                            lasttype = TYPE_ROL;

                            mData.Roles().Add(role, verbose);
                        }
                        else
                        {
                            Error( __FILE__, __LINE__, "LoadResources: NULL object returned!\n" );
                            return result = SIG_FAIL;
                        }
                    }
                }
            }
        }
        else
        {
            Error( __FILE__, __LINE__, "LoadResources:  Couldn't open resource file at %s: %s\n", file_path.c_str(), SDL_GetError() );
            result = SIG_FAIL;
        }
        fin.close();
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadResources: Couldn't open file bad path given\n" );
        result = SIG_FAIL;
    }

    // Difficulties
    mData.Difficulties().clear();
    for ( uint8_t t=STR_DIFF1; t<=STR_DIFF4; t++ )
    {
        mData.Difficulties().resize( mData.Difficulties().size()+1, &mData.Strings().Find( t )->Text() );
    }

    // Skills
    mData.Skills().clear();
    for ( uint8_t t=STR_SKILL1; t<=STR_SKILL5; t++ )
    {
        mData.Skills().resize( mData.Skills().size()+1, &mData.Strings().Find( t )->Text() );
    }

    // Swords
    mData.Swords().clear();
    for ( uint8_t t=STR_SWORD1; t<=STR_SWORD3; t++ )
    {
        mData.Swords().resize( mData.Swords().size()+1, &mData.Strings().Find( t )->Text() );
    }

    // Moral
    mData.Moral().clear();
    for ( uint8_t t=STR_MORAL1; t<=STR_MORAL6; t++ )
    {
        mData.Moral().resize( mData.Moral().size()+1, &mData.Strings().Find( t )->Text() );
    }

    // Nation Relations
    for ( uint8_t t=0; t<mData.Nations().Size(); t++ )
    {
        mData.Nations().At(t)->SetRelations( mData.Nations().Size() );
    }

    //If everything loaded fine
  	Log( "\nLoadResources: Complete!\n" );
    return result;
}

int8_t CResources::LoadFont( void )
{
    int8_t result = SIG_NONE;
    uint8_t size;
    const char* path;
    std::ifstream fin;

    path = Options().Font().Path().c_str();
    size = Options().Font().Size();

    //Open the font
    if ( path != NULL )
    {
        fin.open( path );
        if ( fin.is_open() )
        {
            fin.close();
            mpFont = TTF_OpenFont( path, size );
            //If there was an error in loading the font
            if ( mpFont == NULL )
            {
                Error( __FILE__, __LINE__, "LoadFont: SDL_TTF Couldn't Load Font: %s\n", TTF_GetError() );
                result = SIG_FAIL;
            }
        }
        else
        {
            fin.close();
            Error( __FILE__, __LINE__, "LoadFont: Couldn't open resource file at %s: %s\n", path, SDL_GetError() );
            result = SIG_FAIL;
        }
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadFont: Couldn't open file bad path given\n" );
        result = SIG_FAIL;
    }
    return result;
}

int8_t CResources::LoadActiveRole( void )
{
    int8_t result = SIG_NONE;
    uint8_t t;
    uint8_t timeperiod;
    uint8_t nation;

    // Find the selected role
    timeperiod  = mData.Player().Timeperiod();
    nation      = mData.Player().Nationality();

    for ( t=0; t<mData.Roles().Size(); t++ )
    {
        if ( mData.Roles().At(t)->Timeperiod()  == timeperiod &&
             mData.Roles().At(t)->Nationality() == nation        )
        {
            // Copy the standard role into the game role
            mData.Player() = *mData.Roles().At(t);
            break;
        }
    }

    // No role was found
    if ( t >= mData.Roles().Size() )
    {
        result = SIG_END;
    }

    return result;
}

int8_t CResources::LoadActiveTowns( void )
{
    int8_t result = SIG_NONE;
    uint8_t j, k;
    uint8_t timeperiod;
    uint8_t nation;
    uint16_t economy_index, economy_total;
    bool first_item;
    CDyntown* dyntown;
    CTownTimePeriod* ttp;

    // Find the selected role
    timeperiod  = mData.Player().Timeperiod();
    nation      = mData.Player().Nationality();

    first_item = true;
    mData.TownsDyn().Clear();
    for ( j=0; j<mData.Towns().Size(); j++ )
    {
        for ( k=0; k<mData.Towns().At(j)->TownTimePeriods().size(); k++ )
        {
            ttp = mData.Towns().At(j)->TownTimePeriods().at(k);
            if ( ttp->TimePeriodTag() == timeperiod )
            {
                if ( ttp->Exists() == true )
                {
                    economy_index = ttp->EconomyLevel();
                    economy_total = mData.Economies().Size();
                    if ( economy_index < economy_total )
                    {
                        dyntown = new CDyntown();

                        dyntown->DataTag(j);
                        dyntown->NationTag( ttp->NationTag() );
                        dyntown->Forts(      mData.Economies().At(economy_index)->Forts() );
                        dyntown->Population( mData.Economies().At(economy_index)->Population() );
                        dyntown->Soldiers(   mData.Economies().At(economy_index)->Soldiers() );
                        dyntown->Cargo(mData.Player().Cargo());
                        dyntown->Cargo().Gold().Count( mData.Economies().At(economy_index)->Gold() );

                        mData.TownsDyn().Add(dyntown, first_item);
                        first_item = false;
                        break;
                    }
                    else
                    {
                        Error( __FILE__, __LINE__, "LoadActiveTowns: Economy out of range(%d of %d)\n", economy_index, economy_total );
                    }
                }
            }
        }

        // No special cases
        if ( k >= mData.Towns().At(j)->TownTimePeriods().size() )
        {
            ttp = &mData.Towns().At(j)->TimePeriodDefault();

            economy_index = ttp->EconomyLevel();
            economy_total = mData.Economies().Size();
            if ( economy_index < economy_total )
            {
                dyntown = new CDyntown();

                dyntown->DataTag(j);
                dyntown->NationTag( ttp->NationTag() );
                dyntown->Forts(      mData.Economies().At(economy_index)->Forts() );
                dyntown->Population( mData.Economies().At(economy_index)->Population() );
                dyntown->Soldiers(   mData.Economies().At(economy_index)->Soldiers() );
                dyntown->Cargo( mData.Player().Cargo() );
                dyntown->Cargo().Gold().Count( mData.Economies().At(economy_index)->Gold() );

                mData.TownsDyn().Add(dyntown, false);
            }
            else
            {
                Error( __FILE__, __LINE__, "Economy out of range (%d of %d)\n", economy_index, economy_total );
                result = SIG_FAIL;
            }
        }
    }

    return result;
}

CString* CResources::LoadString( const std::string& line )
{
    const uint8_t delimiters_total = 2;
    vec_uint16_t delimiters;
    CString* pstring = NULL;
    std::string text;

    Options().GetDelimiters(line, delimiters, DELIMIT_NONE);
    if ( delimiters.size() == delimiters_total )
    {
        text    = Options().ReadSubString(  line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 );
        pstring = new CString( text );
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadString: Invalid numbers of parameters. raw data: %s\n", line.c_str() );
        pstring = NULL;
    }
    return pstring;
}

CGraphic* CResources::LoadGraphic( const std::string& line )
{
    const uint8_t delimiters_total = 4;
    vec_uint16_t delimiters;
    CGraphic* pgraphic = NULL;
    uint8_t count;
    uint8_t rows;
    std::string path;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        count   = Options().ReadSubInteger( line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 );
        rows    = Options().ReadSubInteger( line, delimiters.at(1)+1, delimiters.at(2)-delimiters.at(1)-1 );
        path    = Options().ReadSubString(  line, delimiters.at(2)+1, delimiters.at(3)-delimiters.at(2)-1 );
        pgraphic = new CGraphic();
        if( pgraphic->LoadFile( path, count, rows ) != SIG_NONE ) {
            delete pgraphic;
            pgraphic = NULL;
        }
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadGraphic: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        pgraphic = NULL;
    }
    return pgraphic;
}

CSound* CResources::LoadSound( const std::string& line )
{
    const uint8_t delimiters_total = 1;
    vec_uint16_t delimiters;
    CSound* psound = NULL;
    std::string name;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        name    = Options().ReadSubString(  line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 );
        psound = new CSound( name );
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadSound: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        psound = NULL;
    }
    return psound;
}

CMap* CResources::LoadMap( const std::string& line )
{
    const uint8_t delimiters_total = 6;
    vec_uint16_t delimiters;
    CMap* pmap = NULL;
    uint16_t gridx;
    uint16_t gridy;
    uint16_t gridw;
    uint16_t gridh;
    std::string path;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        gridx   = Options().ReadSubInteger( line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 );
        gridy   = Options().ReadSubInteger( line, delimiters.at(1)+1, delimiters.at(2)-delimiters.at(1)-1 );
        gridw   = Options().ReadSubInteger( line, delimiters.at(2)+1, delimiters.at(3)-delimiters.at(2)-1 );
        gridh   = Options().ReadSubInteger( line, delimiters.at(3)+1, delimiters.at(4)-delimiters.at(3)-1 );
        path    = Options().ReadSubString(  line, delimiters.at(4)+1, delimiters.at(5)-delimiters.at(4)-1 );
        pmap    = new CMap( gridx, gridy, gridw, gridh, path );

        if ( pmap->GridX() + pmap->GridW() > Options().Map().Width() )
        {
            Options().Map().Width( pmap->GridX() + pmap->GridW() );
        }
        if ( pmap->GridY() + pmap->GridH() > Options().Map().Height() )
        {
            Options().Map().Height( pmap->GridY() + pmap->GridH() );
        }
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadMap: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        pmap = NULL;
    }
    return pmap;
}

CStringValue* CResources::LoadStringvalue( const std::string& line )
{
    const uint8_t delimiters_total = 3;
    vec_uint16_t delimiters;
    CStringValue* pstrval = NULL;
    uint16_t value;
    std::string name;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        name    = Options().ReadSubString(  line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 );
        value   = Options().ReadSubInteger( line, delimiters.at(1)+1, delimiters.at(2)-delimiters.at(1)-1 );
        pstrval = new CStringValue(value, name);
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadSound: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        pstrval = NULL;
    }
    return pstrval;
}

CEconomy* CResources::LoadEconomy( const std::string& line )
{
    const uint8_t delimiters_total = 6;
    vec_uint16_t delimiters;
    CEconomy* peconomy = NULL;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        peconomy = new CEconomy();
        peconomy->Name(       Options().ReadSubString(  line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 ) );
        peconomy->Population( Options().ReadSubInteger( line, delimiters.at(1)+1, delimiters.at(2)-delimiters.at(1)-1 ) );
        peconomy->Soldiers(   Options().ReadSubInteger( line, delimiters.at(2)+1, delimiters.at(3)-delimiters.at(2)-1 ) );
        peconomy->Forts(      Options().ReadSubInteger( line, delimiters.at(3)+1, delimiters.at(4)-delimiters.at(3)-1 ) );
        peconomy->Gold(       Options().ReadSubInteger( line, delimiters.at(4)+1, delimiters.at(5)-delimiters.at(4)-1 ) );
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadEconomy: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        peconomy = NULL;
    }
    return peconomy;
}

CNation* CResources::LoadNation( const std::string& line )
{
    const uint8_t delimiters_total = 3;
    vec_uint16_t delimiters;
    CNation* pnation = NULL;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        pnation = new CNation();
        pnation->Name(        Options().ReadSubString(  line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 ) );
        pnation->GraphicPath( Options().ReadSubString(  line, delimiters.at(1)+1, delimiters.at(2)-delimiters.at(1)-1 ) );
        pnation->EconomySettings().clear();
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadNation: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        pnation = NULL;
    }
    return pnation;
}

CNationEconomy* CResources::LoadNationEconomyLevel( const std::string& line )
{
    const uint8_t delimiters_total = 3;
    vec_uint16_t delimiters;
    CNationEconomy* pnatecon = NULL;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        pnatecon = new CNationEconomy();
        pnatecon->TimePeriodTag( Options().ReadSubInteger( line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 ) );
        pnatecon->EconomyTag(    Options().ReadSubInteger( line, delimiters.at(1)+1, delimiters.at(2)-delimiters.at(1)-1 ) );
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadNationEconomyLevel: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        pnatecon = NULL;
    }
    return pnatecon;
}

CShip* CResources::LoadShip( const std::string& line )
{
    const uint8_t delimiters_total = 10;
    vec_uint16_t delimiters;
    CShip* pship = NULL;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        pship = new CShip();
        pship->Name(        Options().ReadSubString(  line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 ) );
        pship->Cannon(      Options().ReadSubInteger( line, delimiters.at(1)+1, delimiters.at(2)-delimiters.at(1)-1 ) );
        pship->CargoSpace(  Options().ReadSubInteger( line, delimiters.at(2)+1, delimiters.at(3)-delimiters.at(2)-1 ) );
        pship->HP(          Options().ReadSubInteger( line, delimiters.at(3)+1, delimiters.at(4)-delimiters.at(3)-1 ) );
        pship->Value(       Options().ReadSubInteger( line, delimiters.at(4)+1, delimiters.at(5)-delimiters.at(4)-1 ) );
        pship->Speed(       Options().ReadSubInteger( line, delimiters.at(5)+1, delimiters.at(6)-delimiters.at(5)-1 ) );
        pship->SailType(    Options().ReadSubInteger( line, delimiters.at(6)+1, delimiters.at(7)-delimiters.at(6)-1 ) );
        pship->GraphicPath( Options().ReadSubString(  line, delimiters.at(7)+1, delimiters.at(8)-delimiters.at(7)-1 ) );
        pship->ShipNations().clear();
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadShip: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        pship = NULL;
    }
    return pship;
}

CShipNation* CResources::LoadShipNation( const std::string& line )
{
    const uint8_t delimiters_total = 3;
    vec_uint16_t delimiters;
    CShipNation* pshipnation = NULL;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        pshipnation = new CShipNation();
        pshipnation->NationTag(  Options().ReadSubInteger( line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 ) );
        pshipnation->NationUsed( Options().ReadSubBool(    line, delimiters.at(1)+1, delimiters.at(2)-delimiters.at(1)-1 ) );
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadShipNation: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        pshipnation = NULL;
    }
    return pshipnation;
}

CTown* CResources::LoadTown( const std::string& line )
{
    const uint8_t delimiters_total = 4;
    vec_uint16_t delimiters;
    CTown* ptown = NULL;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        ptown = new CTown();
        ptown->TimePeriodDefault().NationTag(    Options().ReadSubInteger( line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 ) );
        ptown->TimePeriodDefault().EconomyLevel( Options().ReadSubInteger( line, delimiters.at(1)+1, delimiters.at(2)-delimiters.at(1)-1 ) );
        ptown->Name(                             Options().ReadSubString(  line, delimiters.at(2)+1, delimiters.at(3)-delimiters.at(2)-1 ) );

        ptown->TownTimePeriods().clear();
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadTown: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        ptown = NULL;
    }
    return ptown;
}

CTownTimePeriod* CResources::LoadTownTimePeriod( const std::string& line )
{
    const uint8_t delimiters_total = 5;
    vec_uint16_t delimiters;
    CTownTimePeriod* ptowntimeperiod = NULL;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        ptowntimeperiod = new CTownTimePeriod();
        ptowntimeperiod->TimePeriodTag( Options().ReadSubInteger( line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1 ) );
        ptowntimeperiod->NationTag(     Options().ReadSubInteger( line, delimiters.at(1)+1, delimiters.at(2)-delimiters.at(1)-1 ) );
        ptowntimeperiod->EconomyLevel(  Options().ReadSubInteger( line, delimiters.at(2)+1, delimiters.at(3)-delimiters.at(2)-1 ) );
        ptowntimeperiod->Exists(        Options().ReadSubBool(    line, delimiters.at(3)+1, delimiters.at(4)-delimiters.at(3)-1 ) );
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadTownTimePeriod: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        ptowntimeperiod = NULL;
    }
    return ptowntimeperiod;
}

CMapLocation* CResources::LoadTownMapLocation( const std::string& line )
{
    const uint8_t delimiters_total = 3;
    vec_uint16_t delimiters;
    CMapLocation* plocation = NULL;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        plocation = new CMapLocation;
        plocation->TileX( Options().ReadSubInteger(line, delimiters.at(0)+1, delimiters.at(1)-delimiters.at(0)-1) );
        plocation->TileY( Options().ReadSubInteger(line, delimiters.at(1)+1, delimiters.at(2)-delimiters.at(1)-1) );
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadTownMapLocation: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        plocation = NULL;
    }
    return plocation;
}

CRole* CResources::LoadRole( const std::string& line )
{
    uint8_t delimiters_total;    // The total is dynamic based on the other total of other items
    vec_uint16_t delimiters;
    CRole* prole = NULL;
    CGood good;

    uint16_t i;

    delimiters_total = 21 + GAME_MAXSHIPS;

    Options().GetDelimiters(line, delimiters);
    if ( delimiters.size() == delimiters_total )
    {
        prole = new CRole;
        prole->Nationality(     Options().ReadSubInteger( line, delimiters.at(0) +1, delimiters.at(1) -delimiters.at(0) -1 ) );
        prole->Timeperiod(      Options().ReadSubInteger( line, delimiters.at(1) +1, delimiters.at(2) -delimiters.at(1) -1 ) );
        prole->Type(            Options().ReadSubString(  line, delimiters.at(2) +1, delimiters.at(3) -delimiters.at(2) -1 ) );
        prole->Crew(            Options().ReadSubInteger( line, delimiters.at(3) +1, delimiters.at(4) -delimiters.at(3) -1 ) );
        prole->Cargo().Gold().Name(  Options().ReadSubString(  line, delimiters.at(4)+1, delimiters.at(5)-delimiters.at(4)-1 ) );
        prole->Cargo().Gold().Unit(  Options().ReadSubString(  line, delimiters.at(5)+1, delimiters.at(6)-delimiters.at(5)-1 ) );
        prole->Cargo().Gold().Count( Options().ReadSubInteger( line, delimiters.at(6)+1, delimiters.at(7)-delimiters.at(6)-1 ) );
        prole->CareerGold(      Options().ReadSubInteger( line, delimiters.at(7) +1, delimiters.at(8) -delimiters.at(7) -1 ) );

        good.Name(              Options().ReadSubString(  line, delimiters.at(8) +1, delimiters.at(9) -delimiters.at(8) -1 ) );
        good.Unit(              Options().ReadSubString(  line, delimiters.at(9) +1, delimiters.at(10)-delimiters.at(9) -1 ) );
        good.Count(             Options().ReadSubInteger( line, delimiters.at(10)+1, delimiters.at(11)-delimiters.at(10)-1 ) );
        prole->Cargo().Food(good);
        good.Name(              Options().ReadSubString(  line, delimiters.at(11)+1, delimiters.at(12)-delimiters.at(11)-1 ) );
        good.Unit(              Options().ReadSubString(  line, delimiters.at(12)+1, delimiters.at(13)-delimiters.at(12)-1 ) );
        good.Count(             Options().ReadSubInteger( line, delimiters.at(13)+1, delimiters.at(14)-delimiters.at(13)-1 ) );
        prole->Cargo().Cannon(good);
        good.Name(              Options().ReadSubString(  line, delimiters.at(14)+1, delimiters.at(15)-delimiters.at(14)-1 ) );
        good.Unit(              Options().ReadSubString(  line, delimiters.at(15)+1, delimiters.at(16)-delimiters.at(15)-1 ) );
        good.Count(             Options().ReadSubInteger( line, delimiters.at(16)+1, delimiters.at(17)-delimiters.at(16)-1 ) );
        prole->Cargo().GoodTypeA(good);
        good.Name(              Options().ReadSubString(  line, delimiters.at(17)+1, delimiters.at(18)-delimiters.at(17)-1 ) );
        good.Unit(              Options().ReadSubString(  line, delimiters.at(18)+1, delimiters.at(19)-delimiters.at(18)-1 ) );
        good.Count(             Options().ReadSubInteger( line, delimiters.at(19)+1, delimiters.at(20)-delimiters.at(19)-1 ) );
        prole->Cargo().GoodTypeB(good);
        prole->FlagShip(0);
        for ( i=0; i<GAME_MAXSHIPS; i++ )
        {
            prole->Ships(i).Tag( Options().ReadSubInteger( line, delimiters.at(20+i)+1, delimiters.at(21+i)-delimiters.at(20+i)-1 ) );
            prole->Ships(i).Damage(0);
        }

        prole->NationReps().clear();
        for ( i=0; i<mData.Nations().Size(); i++ )
        {
            prole->NationReps().resize( prole->NationReps().size()+1, 0 );
        }

        prole->NationTitles().clear();
        for ( i=0; i<mData.Nations().Size(); i++ )
        {
            prole->NationTitles().resize( prole->NationTitles().size()+1, 0 );
        }
    }
    else
    {
        Error( __FILE__, __LINE__, "LoadRole: Invalid numbers of parameters Expected=%d Actual=%d\n",
               delimiters_total, delimiters.size() );
        prole = NULL;
    }
    return prole;
}
