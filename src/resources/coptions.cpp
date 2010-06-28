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

#include "coptions.h"

COptions::COptions() :
    CIni(),
    mScreen (),
    mSound  (),
    mFont   (),
    mWave   (),
    mCloud  (),
    mMap    ()
{
}

COptions::~COptions()
{
    Log( "COptions Released!\n" );
}

int8_t COptions::Load( const std::string& file_path )
{
    int8_t result = SIG_NONE;
    std::string line;
    std::ifstream fin;

    if (result==SIG_NONE)
    {
        // Get screen settings information from file
        if ( file_path.length() > 0 )
        {
            fin.open( file_path.c_str() );
            if ( fin.is_open() )
            {
                while ( !fin.eof() )
                {
                    getline( fin, line );
                    if ( line.find("\\") != 0 )    // Check if line is a comment line
                    {
                        EraseCharFromString( line, ' ' );
                        if (      line.find( CFG_SCREEN_WIDTH ) == 0 )
                        {
                            mScreen.Width( ReadInteger(line) );
                        }
                        else if ( line.find( CFG_SCREEN_HEIGHT ) == 0 )
                        {
                            mScreen.Height( ReadInteger(line) );
                        }
                        else if ( line.find( CFG_SCREEN_BPP ) == 0 )
                        {
                            mScreen.Bpp( ReadInteger(line) );
                        }
                        else if ( line.find( CFG_FULLSCREEN ) == 0 )
                        {
                            mScreen.Fullscreen( ReadInteger(line) ? true : false );
                        }
                        else if ( line.find( CFG_DOUBLEBUF ) == 0 )
                        {
                            mScreen.Doublebuf( ReadInteger(line) ? true : false );
                        }
                        else if ( line.find( CFG_SOUND_FREQ ) == 0 )
                        {
                            mSound.Frequency( ReadInteger(line) );
                        }
                        else if ( line.find( CFG_SOUND_CHAN ) == 0 )
                        {
                            mSound.Channels( ReadInteger(line) );
                        }
                        else if ( line.find( CFG_SOUND_SAMPLE ) == 0 )
                        {
                            mSound.SampleSize( ReadInteger(line) );
                        }
                        else if ( line.find( CFG_FONTFILE ) == 0 )
                        {
                            mFont.Path( ReadString(line) );
                        }
                        else if ( line.find( CFG_FONTSIZE ) == 0 )
                        {
                            mFont.Size( ReadInteger(line) );
                        }
                        else if ( line.find( CFG_WAVECNT  ) == 0 )
                        {
                            mWave.Count( ReadInteger(line) );
                        }
                        else if ( line.find( CFG_WAVESPD  ) == 0 )
                        {
                            mWave.Speed( ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CLOUDCNT ) == 0 )
                        {
                            mCloud.Count( ReadInteger(line) );
                        }
                    }
                }
            }
            else
            {
                Error( __FILE__, __LINE__, "COptions::Load ERROR Couldn't open resource file at %s: %s\n", file_path.c_str(), SDL_GetError() );
                result = SIG_FAIL;
            }
            fin.close();
        }
        else
        {
            Error( __FILE__, __LINE__, "COptions::Load ERROR Couldn't open file bad path given\n" );
            result = SIG_FAIL;
        }
    }
    return result;
}
