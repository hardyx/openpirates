/***
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
    mScreen     (),
    mSound      (),
    mFont       (),
    mControls   (),
    mWave       (),
    mCloud      (),
    mMap        ()
{
}

COptions::~COptions()
{
    Log( "COptions Released!\n" );
}

int8_t COptions::Load( const std::string& base_path )
{
    int8_t result = SIG_NONE;
    std::string file_path;
    std::string line;
    std::ifstream fin;
    int8_t video_mode = DEF_SCREEN_VMODE;
    int16_t custom_width = 0;
    int16_t custom_height = 0;

    if (result==SIG_NONE)
    {
        file_path = base_path + FILE_OPTIONS;

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
                        else if ( line.find( CFG_CTRLKEY_UP ) == 0 )
                        {
                            mControls.SetKeyMapping( CTRL_UP, (SDLKey)ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CTRLKEY_DOWN ) == 0 )
                        {
                            mControls.SetKeyMapping( CTRL_DOWN, (SDLKey)ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CTRLKEY_LEFT ) == 0 )
                        {
                            mControls.SetKeyMapping( CTRL_LEFT, (SDLKey)ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CTRLKEY_RIGHT ) == 0 )
                        {
                            mControls.SetKeyMapping( CTRL_RIGHT, (SDLKey)ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CTRLKEY_ACTION ) == 0 )
                        {
                            mControls.SetKeyMapping( CTRL_ACTION, (SDLKey)ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CTRLKEY_MENU ) == 0 )
                        {
                            mControls.SetKeyMapping( CTRL_MENU, (SDLKey)ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CTRLJOY_UP ) == 0 )
                        {
                            mControls.SetJoyMapping( CTRL_UP, (SDLKey)ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CTRLJOY_DOWN ) == 0 )
                        {
                            mControls.SetJoyMapping( CTRL_DOWN, (SDLKey)ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CTRLJOY_LEFT ) == 0 )
                        {
                            mControls.SetJoyMapping( CTRL_LEFT, (SDLKey)ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CTRLJOY_RIGHT ) == 0 )
                        {
                            mControls.SetJoyMapping( CTRL_RIGHT, (SDLKey)ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CTRLJOY_ACTION ) == 0 )
                        {
                            mControls.SetJoyMapping( CTRL_ACTION, (SDLKey)ReadInteger(line) );
                        }
                        else if ( line.find( CFG_CTRLJOY_MENU ) == 0 )
                        {
                            mControls.SetJoyMapping( CTRL_MENU, (SDLKey)ReadInteger(line) );
                        }
                    }
                }
            }
            else
            {
                Error( false, __FILE__, __LINE__, "COptions::Load ERROR Couldn't open resource file at %s: %s\n", file_path.c_str(), SDL_GetError() );
                result = SIG_FAIL;
            }
            fin.close();

            // Custom video mode
            if ( video_mode == 0 && custom_width>0 && custom_height>0 )
            {
                mScreen.CustomMode( custom_width, custom_height );
            }
            else
            {
                mScreen.VideoMode( video_mode );
            }
        }
        else
        {
            Error( false, __FILE__, __LINE__, "COptions::Load ERROR Couldn't open file bad path given\n" );
            result = SIG_FAIL;
        }
    }
    return result;
}

int8_t COptions::Save( const std::string& base_path )
{
    int8_t result = SIG_NONE;
    std::string file_path;
    std::ofstream fin;
    int8_t index;

    if (result==SIG_NONE)
    {
        file_path = base_path + FILE_OPTIONS;

        if ( file_path.length() > 0 )
        {
            fin.open( file_path.c_str() );
            if ( fin.is_open() )
            {
                fin << WriteInteger( CFG_SCREEN_VMODE,  mScreen.VideoMode()     );
                fin << "    // Selecting a mode > 0 will use a preset resolution, list is below.\n";
                fin << "    // If mode 0 is selected then the custom resolution specified\n";
                fin << "    // in the " << CFG_SCREEN_WIDTH << " and " << CFG_SCREEN_HEIGHT << " options will be used\n";
                for ( index=1; index<SCREEN_MODES; index++ )
                {
                    fin << "    // Mode " << i_to_a(index) << " " <<  limitsScreenWidth[index] << " x " << limitsScreenHeight[index] << "\n";
                }
                fin << WriteInteger( CFG_SCREEN_WIDTH,  mScreen.Width()         );
                fin << WriteInteger( CFG_SCREEN_HEIGHT, mScreen.Height()        );
                fin << WriteInteger( CFG_SCREEN_BPP,    mScreen.DepthMode()     );
                for ( index=0; index<SCREEN_DEPTHS; index++ )
                {
                    fin << "    // Mode " << i_to_a(index) << " " << limitsScreenDepth[index] << " Bpp\n";
                }
                fin << WriteInteger( CFG_FULLSCREEN,    mScreen.Fullscreen()    );
                fin << WriteInteger( CFG_DOUBLEBUF,     mScreen.Doublebuf()     );
                fin << WriteInteger( CFG_SOUND_FREQ,    mSound.FrequencyMode()  );
                for ( index=0; index<SOUND_FREQ; index++ )
                {
                    fin << "    // Mode " << i_to_a(index) << " " << limitsSoundFreq[index] << " Hz\n";
                }
                fin << WriteInteger( CFG_SOUND_CHAN,    mSound.ChannelsMode()   );
                for ( index=0; index<SOUND_CHANNELS; index++ )
                {
                    fin << "    // Mode " << i_to_a(index) << " " << limitsSoundChannels[index] << " Channels\n";
                }
                fin << WriteInteger( CFG_SOUND_SAMPLE,  mSound.SampleSizeMode() );
                for ( index=0; index<SOUND_SAMPLE; index++ )
                {
                    fin << "    // Mode " << i_to_a(index) << " " << limitsSoundSamples[index] << " Samples\n";
                }
                fin << "    // Control mappings\n";
                fin << WriteString(  CFG_FONTFILE,      mFont.Path()            );
                fin << WriteInteger( CFG_FONTSIZE,      mFont.Size()            );
                fin << WriteInteger( CFG_WAVECNT,       mWave.Count()           );
                fin << WriteInteger( CFG_WAVESPD,       mWave.Speed()           );
                fin << WriteInteger( CFG_CLOUDCNT,      mCloud.Count()          );
                fin << WriteInteger( CFG_CTRLKEY_UP,    mControls.GetKeyMapping( CTRL_UP )      );
                fin << WriteInteger( CFG_CTRLKEY_DOWN,  mControls.GetKeyMapping( CTRL_DOWN )    );
                fin << WriteInteger( CFG_CTRLKEY_LEFT,  mControls.GetKeyMapping( CTRL_LEFT )    );
                fin << WriteInteger( CFG_CTRLKEY_RIGHT, mControls.GetKeyMapping( CTRL_RIGHT )   );
                fin << WriteInteger( CFG_CTRLKEY_ACTION,mControls.GetKeyMapping( CTRL_ACTION )  );
                fin << WriteInteger( CFG_CTRLKEY_MENU,  mControls.GetKeyMapping( CTRL_MENU )    );
                fin << WriteInteger( CFG_CTRLJOY_UP,    mControls.GetJoyMapping( CTRL_UP )      );
                fin << WriteInteger( CFG_CTRLJOY_DOWN,  mControls.GetJoyMapping( CTRL_DOWN )    );
                fin << WriteInteger( CFG_CTRLJOY_LEFT,  mControls.GetJoyMapping( CTRL_LEFT )    );
                fin << WriteInteger( CFG_CTRLJOY_RIGHT, mControls.GetJoyMapping( CTRL_RIGHT )   );
                fin << WriteInteger( CFG_CTRLJOY_ACTION,mControls.GetJoyMapping( CTRL_ACTION )  );
                fin << WriteInteger( CFG_CTRLJOY_MENU,  mControls.GetJoyMapping( CTRL_MENU )    );
            }
            else
            {
                Error( true, __FILE__, __LINE__, "COptions::Save ERROR Couldn't open resource file at %s: %s\n", file_path.c_str(), SDL_GetError() );
                result = SIG_FAIL;
            }
            fin.close();
        }
        else
        {
            Error( true, __FILE__, __LINE__, "COptions::Save ERROR Couldn't open file bad path given\n" );
            result = SIG_FAIL;
        }
    }
    return result;
}
