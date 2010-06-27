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

#include "cmenustart.h"

CMenustart::CMenustart( CResources& resources ) :
    mResources      (resources),
    mScreen         (mResources.Screen()),
    mPlayer         (mResources.Data().Player()),
    mStrings        (mResources.Data().Strings()),
    mGraphics       (mResources.Data().Graphics()),
    mManagerwindow  (mScreen,
                     mResources.Controls(),
                     mResources.Options().Font()),
    mAutoselect     (false)
{
}

CMenustart::~CMenustart()
{
    Log( "CMenustart Released!\n" );
}

int8_t CMenustart::Run( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 400, 110 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    result = mManagerwindow.LoadResources( mResources.Font(),
                                           mGraphics.Find(GFX_BORDER),
                                           mGraphics.Find(GFX_POINTER) );

    if (result==SIG_NONE)
    {
        // Start with a dark blue background
        SDL_FillRect( mScreen.Image(), NULL, SDL_MapRGB( mScreen.Image()->format, 0x00, 0x00, 0x40 ) );

        index = mManagerwindow.CreateNewWindow( rectMain,
                                                mStrings.Find( STR_INTRO )->Text(),
                                                &colrMainColor, NULL );
        result = mManagerwindow.ActivateWindow( index );

        if (result>SIG_NONE)
        {
            switch ( result )
            {
                case 1:
                    result = NewCareer(true);   // Quick Start
                    break;
                case 2:
                    result = NewCareer(false);  // Normal Start
                    break;
                case 3:
                    result = LoadCareer();      // Load a game
                    break;
                case 4:
                    result = SIG_QUIT;          // Quit
                    break;
                default:
                    Error( __FILE__, __LINE__, "menu index out of range\n" );
                    result = SIG_FAIL;
                    break;
            }
        }
        else
        {
            Error( __FILE__, __LINE__, "menu index out of range\n" );
            result = SIG_FAIL;
        }
    }

    return result;
}

int8_t CMenustart::NewCareer( bool autoselect )
{
    int8_t result   = SIG_NONE;
    int8_t state    = 1;
    bool done;

    mAutoselect = autoselect;

    done = false;
    while ( done == false && result == SIG_NONE )
    {
        switch ( state )
        {
            case 1:
                result = GetTimePeriod();
                break;
            case 2:
                result = GetNation();
                break;
            case 3:
                result = mResources.LoadActiveRole();

                if (result==SIG_END)
                {
                    NoActiveRole();
                }
                break;
            case 4:
                result = GetName();
                break;
            case 5:
                result = GetDifficulty();
                break;
            case 6:
                result = GetSkill();
                break;
            case 7:
                done = true;
                break;
            default:
                Error( __FILE__, __LINE__, "menu index out of range\n" );
                result = SIG_FAIL;
                break;
        }
        state++;
    }

    return result;
}

int8_t CMenustart::GetTimePeriod( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 200, 200, 250, 150 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    CManager<CStringValue>& timeperiods = mResources.Data().Timeperiods();
    vec_string_t names;
    std::string* name;

    if ( timeperiods.Size() > 0 )
    {
        if ( mAutoselect )
        {
            mPlayer.Timeperiod(0);
        }
        else
        {
            for ( uint16_t t=0; t<timeperiods.Size(); t++ )
            {
                name = new std::string( i_to_a( timeperiods.At(t)->Value() ) );
                name->append( " " );
                name->append( timeperiods.At(t)->Text() );
                names.resize( names.size()+1, name );
            }

            index = mManagerwindow.CreateNewWindow( rectWindow,
                                                    mStrings.Find( STR_PICK_TIMEP )->Text(),
                                                    names,
                                                    &colrMainColor, NULL );

            result = mManagerwindow.ActivateWindow( index );
            if ( SIG_NONE < result )
            {
                mPlayer.Timeperiod(result-1);
                result = SIG_NONE;
            }
            else
            {
                Error( __FILE__, __LINE__, "menu index out of range\n" );
                result = SIG_FAIL ;
            }

            for ( uint16_t t=0; t<names.size(); t++ )
            {
                delete names.at(t);
            }
            names.clear();
        }
    }

    return result;
}

int8_t CMenustart::GetNation( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 200, 200, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    CManager<CNation>& nations = mResources.Data().Nations();
    vec_string_t names;
    std::string* name;

    if ( nations.Size() > 0 )
    {
        if ( mAutoselect )
        {
            mPlayer.Nationality(0);
        }
        else
        {
            for ( uint16_t t=0; t<nations.Size(); t++ )
            {
                name = new std::string( nations.At(t)->Name() );
                names.resize( names.size()+1, name );
            }

            index = mManagerwindow.CreateNewWindow( rectWindow,
                                                    mStrings.Find( STR_PICK_NATION )->Text(),
                                                    names,
                                                    &colrMainColor, NULL );

            result = mManagerwindow.ActivateWindow( index );
            if ( SIG_NONE < result )
            {
                mPlayer.Nationality(result-1);
                result = SIG_NONE;
            }
            else
            {
                Error( __FILE__, __LINE__, "menu index out of range\n" );
                result = SIG_FAIL ;
            }

            for ( uint16_t t=0; t<names.size(); t++ )
            {
                delete names.at(t);
            }
            names.clear();
        }
    }

    return result;
}

#define SELECT_A    1
#define SELECT_Z    26
#define SELECT_CASE 27
#define SELECT_RUB  28
#define SELECT_DONE 29

int8_t CMenustart::GetName( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 100, 100, 460, 100 };
    SDL_Color colrNameColor = { 0, 0, 0, 0 };
    bool blnCase = true;
    std::string name;

    if ( mAutoselect )
    {
        mPlayer.Name(DEFAULT_NAME);
    }
    else
    {
        name.clear();

        index = mManagerwindow.CreateNewWindow( rectWindow,
                                                mStrings.Find( STR_PICK_NAMEUP )->Text(),
                                                name,
                                                &colrNameColor, NULL );

        while ( result != SELECT_DONE && result >= SIG_NONE )
        {
            result = mManagerwindow.ActivateWindow( index );

            if ( result < SELECT_A )
            {
                Error( __FILE__, __LINE__, "menu index out of range\n" );
                result = SIG_FAIL;
                break;
            }

            if ( result >= SELECT_A && result <= SELECT_Z )
            {
                if ( name.length() <= MAX_LENGTH_NAME )
                {
                    if ( blnCase )
                    {
                        name += 0x40 + result;   // Upper case
                    }
                    else
                    {
                        name += 0x60 + result;   // Lower case
                    }
                }
            }
            else if ( result == SELECT_CASE )
            {
                if ( blnCase )
                {
                    blnCase = false;    // Lower case
                    mManagerwindow.UpdateWindowText( index, mStrings.Find( STR_PICK_NAMELO )->Text() );
                }
                else
                {
                    blnCase = true;     // Upper case
                    mManagerwindow.UpdateWindowText( index, mStrings.Find( STR_PICK_NAMEUP )->Text() );
                }
            }
            else if ( result == SELECT_RUB )
            {
                if ( name.length() > 0 )
                {
                    name.erase( name.length()-1, 1 );   // Rub out the last char
                }
            }
            else if ( result == SELECT_DONE )
            {
                if ( name.length() == 0 )
                {
                    mPlayer.Name(DEFAULT_NAME);
                }
                else
                {
                    mPlayer.Name(name);
                }
            }
            mManagerwindow.ReprocessWindow( index );
        }

        if (result == SELECT_DONE)
        {
            result = SIG_NONE;
        }
        else
        {
            result = SIG_FAIL;
        }
    }

    return result;
}

int8_t CMenustart::GetDifficulty( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    vec_string_t& diffs = mResources.Data().Difficulties();
    vec_string_t variables;
    SDL_Rect rectWindow = { 300, 300, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    if ( mAutoselect )
    {
        mPlayer.Difficulty(0);
    }
    else
    {
        variables.clear();
        variables.resize( variables.size()+1, diffs.at(0) );
        variables.resize( variables.size()+1, diffs.at(1) );
        variables.resize( variables.size()+1, diffs.at(2) );
        variables.resize( variables.size()+1, diffs.at(3) );
        variables.resize( variables.size()+1, &mPlayer.Name() );

        index = mManagerwindow.CreateNewWindow( rectWindow,
                                                mStrings.Find( STR_PICK_DIFF )->Text(),
                                                variables,
                                                &colrMainColor, NULL );

        result = mManagerwindow.ActivateWindow( index );
        if ( SIG_NONE < result )
        {
            mPlayer.Difficulty(result-1);
            result = SIG_NONE;
        }
        else
        {
            Error( __FILE__, __LINE__, "menu index out of range\n" );
            result = SIG_FAIL ;
        }
    }

    return result;
}

int8_t CMenustart::GetSkill( void )
{
    int8_t result = SIG_NONE;
    int8_t index;

    SDL_Rect rectWindow = { 300, 300, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    if ( mAutoselect )
    {
        mPlayer.Skill(0);
    }
    else
    {
        index = mManagerwindow.CreateNewWindow( rectWindow,
                                                mStrings.Find( STR_PICK_SKILL )->Text(),
                                                mResources.Data().Skills(),
                                                &colrMainColor, NULL );

        result = mManagerwindow.ActivateWindow( index );
        if ( SIG_NONE < result )
        {
            mPlayer.Skill(result-1);
            result = SIG_NONE;
        }
        else
        {
            Error( __FILE__, __LINE__, "menu index out of range\n" );
            result = SIG_FAIL ;
        }
    }

    return result;
}

int8_t CMenustart::LoadCareer( void )
{
    int8_t result = SIG_NONE;
/*
    int8_t index;
    SDL_Rect rectMain = { 50, 50, 200, 200 };


    while ( result == 0 )
    {
        index = mManagerwindow.CreateNewWindow( rectMain, *mStrings.Find( STR_LOAD )->Text() );

        switch ( mManagerwindow.ActivateWindow( index ) )
        {
            case 1:
                // Need to create a list of games from a folder and then load data from the file
                result = SIG_NONE;
                break;
            case SIG_FAIL:
                result = SIG_FAIL;
                break;
            default:;
                break;
        }
    }
*/
    return result;
}

void CMenustart::NoActiveRole( void )
{
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    index = mManagerwindow.CreateNewWindow( rectMain,
                                            mStrings.Find( STR_PICK_NOROLE )->Text(),
                                            &colrMainColor, NULL );
    mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );
}
