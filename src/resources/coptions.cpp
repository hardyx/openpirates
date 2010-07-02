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

uint16_t limitsScreenWidth[SCREEN_MODES]     = { 0, 320, 640, 800, 800, 1024, 1280, 1280, 1600, 1920 };
uint16_t limitsScreenHeight[SCREEN_MODES]    = { 0, 240, 480, 480, 600,  768,  800, 1024, 1200, 1080 };
uint16_t limitsScreenDepth[SCREEN_DEPTHS]    = { 8, 16, 32 };

uint16_t limitsSoundFreq[SOUND_FREQ]         = { 11025, 22050, 44100, 48000 };
uint16_t limitsSoundChannels[SOUND_CHANNELS] = { 1, 2 };
uint16_t limitsSoundSamples[SOUND_SAMPLE]    = { 128, 256, 512, 1024, 2048, 4096 };

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
    int8_t video_mode = DEF_SCREEN_VMODE;
    int16_t custom_width = 0;
    int16_t custom_height = 0;
    SDL_Color defcolor = { DEF_FONTCOLOR_R, DEF_FONTCOLOR_G, DEF_FONTCOLOR_B, 0 };

    mFont.Color(defcolor); // White

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
                        if (      line.find( CFG_SCREEN_VMODE ) == 0 )
                        {
                            video_mode = ReadInteger(line);
                        }
                        else if ( line.find( CFG_SCREEN_WIDTH ) == 0 )
                        {
                            custom_width = ReadInteger(line);
                        }
                        else if ( line.find( CFG_SCREEN_HEIGHT ) == 0 )
                        {
                            custom_height = ReadInteger(line);
                        }
                        else if ( line.find( CFG_SCREEN_BPP ) == 0 )
                        {
                            mScreen.DepthMode( ReadInteger(line) );
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
                            mSound.FrequencyMode( ReadInteger(line) );
                        }
                        else if ( line.find( CFG_SOUND_CHAN ) == 0 )
                        {
                            mSound.ChannelsMode( ReadInteger(line) );
                        }
                        else if ( line.find( CFG_SOUND_SAMPLE ) == 0 )
                        {
                            mSound.SampleSizeMode( ReadInteger(line) );
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

            // Custom video mode
            if ( video_mode == 0 && custom_width>0 && custom_height>0 )
            {
               mScreen.CustomMode( custom_width, custom_height );
            }
        }
        else
        {
            Error( __FILE__, __LINE__, "COptions::Load ERROR Couldn't open file bad path given\n" );
            result = SIG_FAIL;
        }
    }
    return result;
}
