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

#include "modes/cmodemain.h"

CModeMain::CModeMain() :
    mFileOptions    (FILE_OPTIONS),
    mFileResources  (FILE_RESOURCES),
    mResources      (),
    mStartmenu      (mResources),
    mMainmenu       (mResources),
    mModenav        (mResources, mMainmenu)
{
}

CModeMain::~CModeMain()
{
    // Free the joystick
    Log( "Close Joystick\n" );
    if ( SDL_JoystickOpened(0) ) SDL_JoystickClose( mResources.Joystick() );

    // Free the mixer
    Log( "Close Mixer!\n" );
    Mix_CloseAudio();	        //Quit SDL_mixer

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
    std::string path;

    done = false;
    while ( done == false && result == SIG_NONE )
    {
        switch ( state )
        {
            case 1:
                result = OpenSystem(path, argc, argv);
                break;
            case 2:
                result = LoadResources(path);
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
                Error( __FILE__, __LINE__, "state out of range\n" );
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
    return result;
}

int8_t CModeMain::OpenSystem( const std::string& file_path, int argc, char *argv[] )
{
    int8_t result = SIG_NONE;

    if ( file_path.length() > 0 ) mFileOptions = file_path;

    result = mResources.Options().Load( mFileOptions );
    if ( result == SIG_FAIL )
    {
		Log( "WARNING Couldn't load options file\n" );
		result = SIG_NONE; // The program will use hardcoded option values
    }

    // Setting any overrides set by arguments
    result = ProcessArguments( argc, argv );

    // Make sure settings are set to allowed states
    VerifySettings();

	// Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK ) < 0 )
    {
        Error( __FILE__, __LINE__, "Couldn't initialize SDL: %s\n", SDL_GetError() );
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
            Error( __FILE__, __LINE__, "Couldn't start SDL_TTF: %s\n", TTF_GetError() );
            result = SIG_FAIL;
        }
	}

    if ( result == SIG_NONE )
    {
        result = mResources.LoadFont();
        if ( result == SIG_FAIL )
        {
            Error( __FILE__, __LINE__, "Couldn't load font\n" );
        }
    }

    // Initialize SDL_mixer
	if ( result == SIG_NONE )
	{
        if ( Mix_OpenAudio( mResources.Options().Sound().Frequency(),
                            MIX_DEFAULT_FORMAT,
                            mResources.Options().Sound().Channels(),
                            mResources.Options().Sound().SampleSize() ) == -1 )
        {
            Error( __FILE__, __LINE__, "Couldn't start SDL_MIXER: %s\n", SDL_GetError() );
            result = SIG_FAIL;
        }
	}

	// Check and open joystick device
	if ( result == SIG_NONE )
	{
        if ( SDL_NumJoysticks()>0 )
        {
            mResources.Joystick( SDL_JoystickOpen(0) );
            if ( mResources.Joystick() == NULL )
            {
                Error( __FILE__, __LINE__, "Couldn't open joystick 0: %s\n", SDL_GetError() );
                result = SIG_FAIL;
            }
        }
        else
        {
            Log( "WARNING No joysticks detected\n" );
        }
	}

  	Log( "CModeMain::OpenSystem Complete!\n" );
	return result;
}

#define ARG_LEN 15
#define ARGL_HELP       "--help"
#define ARGS_HELP       "-h"
#define ARGD_HELP       "prints this menu"
#define ARGL_WIDTH      "--width"
#define ARGS_WIDTH      "-W"
#define ARGD_WIDTH      "pixel width of the screen"
#define ARGL_HEIGHT     "--height"
#define ARGS_HEIGHT     "-H"
#define ARGD_HEIGHT     "pixel height of the screen"
#define ARGL_DEPTH      "--depth"
#define ARGS_DEPTH      "-D"
#define ARGD_DEPTH      "pixel depth of the screen"
#define ARGL_FULLSCREEN "--fullscreen"
#define ARGS_FULLSCREEN "-F"
#define ARGD_FULLSCREEN "view mode of the screen"

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
    int32_t value;
    std::string arg;

    Log( "Running from location: %s\n", argv[0] );
    for ( index=1; index<argc; )
    {
        arg = argv[index];
        if (arg.compare(ARGL_HELP) == 0 || arg.compare(ARGS_HELP) == 0)
        {
            printf( "Usage: pirates [OPTIONS]...\n\n" );
            printf( "Options:\n" );
            printf( "%s, %s%s %s\n",     ARGS_HELP,         ARGL_HELP,          Spaces(ARG_LEN-strlen(ARGL_HELP)).c_str(),          ARGD_HELP   );
            printf( "%s, %s [v]%s %s\n", ARGS_WIDTH,        ARGL_WIDTH,         Spaces(ARG_LEN-strlen(ARGL_WIDTH)).c_str(),         ARGD_WIDTH  );
            printf( "%s, %s [v]%s %s\n", ARGS_HEIGHT,       ARGL_HEIGHT,        Spaces(ARG_LEN-strlen(ARGL_HEIGHT)).c_str(),        ARGD_HEIGHT );
            printf( "%s, %s [v]%s %s\n", ARGS_DEPTH,        ARGL_DEPTH,         Spaces(ARG_LEN-strlen(ARGL_DEPTH)).c_str(),         ARGD_DEPTH  );
            printf( "%s, %s [v]%s %s\n", ARGS_FULLSCREEN,   ARGL_FULLSCREEN,    Spaces(ARG_LEN-strlen(ARGL_FULLSCREEN)).c_str(),    ARGD_FULLSCREEN  );
            printf( "%s, %s [v]%s %s\n", ARGS_FREQ,         ARGL_FREQ,          Spaces(ARG_LEN-strlen(ARGL_FREQ)).c_str(),          ARGD_FREQ   );
            printf( "%s, %s [v]%s %s\n", ARGS_CHAN,         ARGL_CHAN,          Spaces(ARG_LEN-strlen(ARGL_CHAN)).c_str(),          ARGD_CHAN   );
            printf( "%s, %s [v]%s %s\n", ARGS_SAMPLE,       ARGL_SAMPLE,        Spaces(ARG_LEN-strlen(ARGL_SAMPLE)).c_str(),        ARGD_SAMPLE );
            printf( "\n" );
            result = SIG_QUIT;
            break;
        }
        else if (arg.compare(ARGL_WIDTH) == 0 || arg.compare(ARGS_WIDTH) == 0)
        {
            value = a_to_i(argv[index+1]);
            mResources.Options().Screen().Width(value);
            index+=2;
        }
        else if (arg.compare(ARGL_HEIGHT) == 0 || arg.compare(ARGS_HEIGHT) == 0)
        {
            value = a_to_i(argv[index+1]);
            mResources.Options().Screen().Height(value);
            index+=2;
        }
        else if (arg.compare(ARGL_DEPTH) == 0 || arg.compare(ARGS_DEPTH) == 0)
        {
            value = a_to_i(argv[index+1]);
            mResources.Options().Screen().Bpp(value);
            index+=2;
        }
        else if (arg.compare(ARGL_FULLSCREEN) == 0 || arg.compare(ARGS_FULLSCREEN) == 0)
        {
            value = a_to_i(argv[index+1]);
            mResources.Options().Screen().Fullscreen(value);
            index+=2;
        }
        else
        {
            Error( __FILE__, __LINE__, "Unknown parameter: %s\n", arg.c_str() );
            index++;
        }
    }
    return result;
}

void CModeMain::VerifySettings( void )
{
    int32_t value;
    SDL_Color defcolor = { FONTCOLOR_R, FONTCOLOR_G, FONTCOLOR_B, 0 };

    mResources.Options().Font().Color(defcolor); // White

    value = mResources.Options().Screen().Width();
    if ( value < 320 || value > 1024 ) {
        Error( __FILE__, __LINE__, "Unsupported value for screen width %d\n", value );
        mResources.Options().Screen().Width(        SCREEN_WIDTH    );
    }
    value = mResources.Options().Screen().Height();
    if ( value < 240 || value > 768 ) {
        Error( __FILE__, __LINE__, "Unsupported value for screen height %d\n", value );
        mResources.Options().Screen().Height(       SCREEN_HEIGHT   );
    }
    value = mResources.Options().Screen().Bpp();
    if ( value != 16 && value != 24 && value != 32 ) {
        Error( __FILE__, __LINE__, "Unsupported value for screen depth %d\n", value );
        mResources.Options().Screen().Bpp(          SCREEN_BPP      );
    }

    value = mResources.Options().Sound().Frequency();
    if ( value != 11025 && value != 22050 && value != 44100 && value != 48000 ) {
        Error( __FILE__, __LINE__, "Unsupported value for sound frequency %d\n", value );
        mResources.Options().Sound().Frequency(     SOUND_FREQ      );
    }
    value = mResources.Options().Sound().Channels();
    if ( value != 1 && value != 2 ) {
        Error( __FILE__, __LINE__, "Unsupported value for sound channels %d\n", value );
        mResources.Options().Sound().Channels(      SOUND_CHAN      );
    }
    value = mResources.Options().Sound().SampleSize();
    if ( value != 256 && value != 512 && value != 1024 && value != 2048 && value != 4096 ) {
        Error( __FILE__, __LINE__, "Unsupported value for sound sample size %d\n", value );
        mResources.Options().Sound().SampleSize(    SOUND_SAMPLE    );
    }

    value = mResources.Options().Cloud().Count();
    if ( value < 0 && value > 20 ) {
        Error( __FILE__, __LINE__, "Unsupported value for cloud size %d\n", value );
        mResources.Options().Cloud().Count(         CLOUD_COUNT     );
    }
    value = mResources.Options().Wave().Count();
    if ( value < 0 && value > 100 ) {
        Error( __FILE__, __LINE__, "Unsupported value for wave size %d\n", value );
        mResources.Options().Wave().Count(          WAVE_COUNT      );
    }
    value = mResources.Options().Wave().Speed();
    if ( value < 0 && value > 50 ) {
        Error( __FILE__, __LINE__, "Unsupported value for wave speed %d\n", value );
        mResources.Options().Wave().Speed(          WAVE_SPEED      );
    }
    value = mResources.Options().Font().Size();
    if ( value < 0 && value > 24 ) {
        Error( __FILE__, __LINE__, "Unsupported value for font size %d\n", value );
        mResources.Options().Font().Size(           FONT_SIZE       );
    }
}

int8_t CModeMain::LoadResources( const std::string& file_path )
{
    int8_t result = SIG_NONE;

    if ( file_path.length() > 0 ) mFileResources = file_path;

    result = mResources.LoadResources( mFileResources );
    if ( result == SIG_FAIL || result == SIG_FAIL )
    {
		Error( __FILE__, __LINE__, "Couldn't load resources file\n" );
        result = SIG_FAIL;
    }
    return result;
}
