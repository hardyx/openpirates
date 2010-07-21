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

#include "modes/cmodemain.h"

CModeMain::CModeMain() :
    mBasePath       (""),
    mResources      (),
    mManagerwindow  (mResources),
    mMainmenu       (mResources, mManagerwindow),
    mStartmenu      (mResources, mManagerwindow),
    mModenav        (mResources, mManagerwindow, mMainmenu)
{
}

CModeMain::~CModeMain()
{
    // Free the joystick
    Log( "Close Joystick\n" );
    mResources.CloseJoystick();

    // Free the mixer
    Log( "Close Mixer!\n" );
    mResources.CloseAudioMixer();

    // Free font and TTF
    Log( "Close Font!\n" );
    mResources.Free_Font();

    Log( "Close TTF!\n" );
    TTF_Quit();				    //Quit SDL_ttf

    // CLose SDL
    Log( "Close SDL!\n" );
    SDL_Quit();

  	Log( "CModeMain Released!\n" );
}

int8_t CModeMain::Run( int argc, char *argv[] )
{
    int8_t state    = 1;
    int8_t result   = SIG_NONE;
    bool done;

    // Setup file path and resource path's
    SetBasePath( argv[0] );

    done = false;
    while ( done == false && result >= SIG_NONE )
    {
        switch ( state )
        {
            case 1:
                result = OpenSystem( argc, argv );
                break;
            case 2:
                result = LoadResources();
                break;
            case 3:
                result = mStartmenu.Run();
                break;
            case 4:
                result = mResources.LoadActiveTowns();
                break;
            case 5:
                result = mModenav.Run();
                break;
            case 6:
                done = true;
                break;
            default:
                Error( true, __FILE__, __LINE__, "state out of range\n" );
                result = SIG_FAIL;
                break;
        }
        state++;

        // Restart program / Go to start menu
        if (result == SIG_END )
        {
            result = SIG_NONE;
            state = 3;
        }
    }

    // Save current options to file
    result = mResources.Options().Save( mBasePath );
    if ( result == SIG_FAIL )
    {
		Log( "WARNING Couldn't save options file\n" );
		result = SIG_NONE;
    }

    return result;
}

void CModeMain::SetBasePath( const char* base_path )
{
    uint32_t pos;

    mBasePath = base_path;
    pos = mBasePath.find_last_of( '/' );
    if (pos != std::string::npos)
    {
        mBasePath.erase( pos+1, mBasePath.length() );
    }
    else
    {
        mBasePath.clear();
    }
}

int8_t CModeMain::OpenSystem( int argc, char *argv[] )
{
    int8_t result = SIG_NONE;

    result = mResources.Options().Load( mBasePath );
    if ( result == SIG_FAIL )
    {
		result = SIG_NONE; // The program will use hardcoded option values
    }

    // Setting any overrides set by arguments
    result = ProcessArguments( argc, argv );

	// Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK ) < 0 )
    {
        Error( true, __FILE__, __LINE__, "Couldn't initialize SDL: %s\n", SDL_GetError() );
        result = SIG_FAIL;
    }

    // Set video mode
	if ( result == SIG_NONE )
	{
        result = mResources.SetVideoMode();
	}

	// Initialize SDL_ttf
	if ( result == SIG_NONE )
	{
        if ( TTF_Init() == -1 )
        {
            Error( true, __FILE__, __LINE__, "Couldn't start SDL_TTF: %s\n", TTF_GetError() );
            result = SIG_FAIL;
        }
	}

    // Load the ttf font
    if ( result == SIG_NONE )
    {
        result = mResources.LoadFont( mBasePath );
        if ( result == SIG_FAIL )
        {
            Error( true, __FILE__, __LINE__, "Couldn't load font\n" );
        }
    }

    // Initialize SDL_mixer
	if ( result == SIG_NONE )
	{
        result = mResources.OpenAudioMixer();
	}

	// Check and open joystick device
	if ( result == SIG_NONE )
	{
        result = mResources.OpenJoystick();
	}

  	Log( "CModeMain::OpenSystem Complete!\n" );
	return result;
}

#define ARG_LEN 15
#define ARGL_HELP       "--help"
#define ARGS_HELP       "-h"
#define ARGD_HELP       "prints this menu"
#define ARGL_VMODE      "--vmode"
#define ARGS_VMODE      "-V"
#define ARGD_VMODE      "standard video mode resolutions"
#define ARGL_WIDTH      "--width"
#define ARGS_WIDTH      "-W"
#define ARGD_WIDTH      "custom pixel width of the screen"
#define ARGL_HEIGHT     "--height"
#define ARGS_HEIGHT     "-H"
#define ARGD_HEIGHT     "custom pixel height of the screen"
#define ARGL_DEPTH      "--depth"
#define ARGS_DEPTH      "-D"
#define ARGD_DEPTH      "pixel depth of the screen"
#define ARGL_FS         "--fullscreen"
#define ARGS_FS         "-F"
#define ARGD_FS         "view mode of the screen"

#define ARGL_FREQ       "--frequency"
#define ARGS_FREQ       "-f"
#define ARGD_FREQ       "sound system sample frequency"
#define ARGL_CHAN       "--channels"
#define ARGS_CHAN       "-c"
#define ARGD_CHAN       "sound system channels"
#define ARGL_SAMPLE     "--samplesize"
#define ARGS_SAMPLE     "-s"
#define ARGD_SAMPLE     "sound system sample size"

int8_t CModeMain::ProcessArguments( int argc, char *argv[] )
{
    int8_t result = SIG_NONE;
    int16_t index;
    int16_t custom_width = 0;
    int16_t custom_height = 0;
    int32_t value;
    std::string arg;

    arg.clear();
    for ( index=1; index<argc; index++ )
    {
        arg.append( "'" );
        arg.append( argv[index] );
        arg.append( "' " );
    }
    Log( "Running from location: %s\n   with %d agruments: %s\n", argv[0], argc-1, arg.c_str() );

    for ( index=1; index<argc; )
    {
        arg = argv[index];

        if (arg.length() > 0)
        {
            if (arg.compare(ARGL_HELP) == 0 || arg.compare(ARGS_HELP) == 0)
            {
                printf( "Usage: pirates [OPTIONS]...\n\n" );
                printf( "Options:\n" );
                printf( "%s, %s%s %s\n",     ARGS_HELP,         ARGL_HELP,          Spaces(ARG_LEN-strlen(ARGL_HELP)).c_str(),          ARGD_HELP   );
                printf( "%s, %s [v]%s %s\n", ARGS_VMODE,        ARGL_VMODE,         Spaces(ARG_LEN-strlen(ARGL_VMODE)).c_str(),         ARGD_VMODE  );
                for ( index=1; index<SCREEN_MODES; index++ )
                {
                    printf( "    Mode %d %d x %d\n", index, limitsScreenWidth[index], limitsScreenHeight[index] );
                }
                printf( "%s, %s [v]%s %s\n", ARGS_WIDTH,        ARGL_WIDTH,         Spaces(ARG_LEN-strlen(ARGL_WIDTH)).c_str(),         ARGD_WIDTH  );
                printf( "%s, %s [v]%s %s\n", ARGS_HEIGHT,       ARGL_HEIGHT,        Spaces(ARG_LEN-strlen(ARGL_HEIGHT)).c_str(),        ARGD_HEIGHT );
                printf( "%s, %s [v]%s %s\n", ARGS_DEPTH,        ARGL_DEPTH,         Spaces(ARG_LEN-strlen(ARGL_DEPTH)).c_str(),         ARGD_DEPTH  );
                for ( index=0; index<SCREEN_DEPTHS; index++ )
                {
                    printf( "    Mode %d %d Bpp\n", index, limitsScreenDepth[index] );
                }
                printf( "%s, %s [v]%s %s\n", ARGS_FS,           ARGL_FS,            Spaces(ARG_LEN-strlen(ARGL_FS)).c_str(),            ARGD_FS     );
                printf( "%s, %s [v]%s %s\n", ARGS_FREQ,         ARGL_FREQ,          Spaces(ARG_LEN-strlen(ARGL_FREQ)).c_str(),          ARGD_FREQ   );
                for ( index=0; index<SOUND_FREQ; index++ )
                {
                    printf( "    Mode %d %d Hz\n", index, limitsSoundFreq[index] );
                }
                printf( "%s, %s [v]%s %s\n", ARGS_CHAN,         ARGL_CHAN,          Spaces(ARG_LEN-strlen(ARGL_CHAN)).c_str(),          ARGD_CHAN   );
                for ( index=0; index<SOUND_CHANNELS; index++ )
                {
                    printf( "    Mode %d %d Channels\n", index, limitsSoundChannels[index] );
                }
                printf( "%s, %s [v]%s %s\n", ARGS_SAMPLE,       ARGL_SAMPLE,        Spaces(ARG_LEN-strlen(ARGL_SAMPLE)).c_str(),        ARGD_SAMPLE );
                for ( index=0; index<SOUND_SAMPLE; index++ )
                {
                    printf( "    Mode %d %d Samples\n", index, limitsSoundSamples[index] );
                }
                printf( "\n" );
                result = SIG_QUIT;
                break;
            }
            else if (arg.compare(ARGL_VMODE) == 0 || arg.compare(ARGS_VMODE) == 0)
            {
                value = a_to_i(argv[index+1]);
                mResources.Options().Screen().VideoMode(value);
                index+=2;
            }
            else if (arg.compare(ARGL_WIDTH) == 0 || arg.compare(ARGS_WIDTH) == 0)
            {
                value = a_to_i(argv[index+1]);
                custom_width = value;
                index+=2;
            }
            else if (arg.compare(ARGL_HEIGHT) == 0 || arg.compare(ARGS_HEIGHT) == 0)
            {
                value = a_to_i(argv[index+1]);
                custom_height = value;
                index+=2;
            }
            else if (arg.compare(ARGL_DEPTH) == 0 || arg.compare(ARGS_DEPTH) == 0)
            {
                value = a_to_i(argv[index+1]);
                mResources.Options().Screen().DepthMode(value);
                index+=2;
            }
            else if (arg.compare(ARGL_FS) == 0 || arg.compare(ARGS_FS) == 0)
            {
                value = a_to_i(argv[index+1]);
                mResources.Options().Screen().Fullscreen(value);
                index+=2;
            }
            else
            {
                Error( false, __FILE__, __LINE__, "Unknown parameter: %s\n", arg.c_str() );
                index++;
            }
        }
        else
        {
            Error( false, __FILE__, __LINE__, "Empty parameter at %d\n", index );
            index++;
        }
    }

    // Custom video mode
    if ( mResources.Options().Screen().VideoMode() == 0 && custom_width>0 && custom_height>0 )
    {
        mResources.Options().Screen().CustomMode( custom_width, custom_height );
    }

    return result;
}

int8_t CModeMain::LoadResources( void )
{
    int8_t result = SIG_NONE;

    result = mResources.LoadResources( mBasePath );
    if ( result == SIG_FAIL || result == SIG_FAIL )
    {
		Error( true, __FILE__, __LINE__, "Couldn't load resources file\n" );
        result = SIG_FAIL;
    }
    return result;
}
