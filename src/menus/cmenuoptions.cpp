#include "cmenuoptions.h"

#include "resources/keystrings.h"

#define STR_OPT_MAIN    "Select...\\n\\t01Video Options\\s\\t01Sound Options\\s\\t01Keyboard Control Options\\s\\t01Joystick Control Options\\s\\t01Back\\s"
#define STR_OPT_VIDEO   "Video Options\\n\\t01Resolution:\\u\\c10%1x%2\\u\\c20Change Resolution\\s\\t01Depth:\\u\\c10%3\\u\\c20- \\z +\\s\\t01Fullscreen:\\u\\c10%4\\s\\t01Doublebuffer:\\u\\c10%5\\s \\nApply\\z\\t10Back\\s"
#define STR_OPT_SOUND   "Sound Options\\n\\t01Frequency:\\u\\c10%1\\u\\c20-\\z +\\s\\t01Channels:\\u\\c10%2\\u\\c20-\\z +\\s\\t01Sample size:\\u\\c10%3\\u\\c20-\\z +\\s \\nApply\\z\\t10Back\\s"
#define STR_OPT_CTRLS   "Control Options\\n\\t01Up:\\u\\c10%1\\s\\t01Down:\\u\\c10%2\\s\\t01Left:\\u\\c10%3\\s\\t01Right:\\u\\c10%4\\s\\t01Action:\\u\\c10%5\\s\\t01Menu:\\u\\c10%6\\s\\nBack\\s"
#define STR_OPT_RES     "Select a resolution:\\n%aCancel\\s"
#define STR_OPT_CHG     "SDL is recommends switching the screen depth from %1 bpp to %2 bpp.\\nSelecting yes will switch to that depth and attempt to set\\nSelecting no will keep the current depth and and attempt to set\\nYes\\sNo\\s"
#define STR_OPT_FAILED  "The current selection failed to set.\\nOk\\s"
#define STR_OPT_NEWKEY  "Press any key\\n"
#define STR_OPT_NEWJOY  "Press any button\\n"

#define OLD 0
#define NEW 1

CMenuOptions::CMenuOptions( CResources& resources, CManagerWindow& winmanager ) :
    mResources      (resources),
    mScreen         (mResources.Screen()),
    mPlayer         (mResources.Data().Player()),
    mStrings        (mResources.Data().Strings()),
    mGraphics       (mResources.Data().Graphics()),
    mManagerwindow  (winmanager)
{
}

CMenuOptions::~CMenuOptions()
{
}

int8_t CMenuOptions::Run( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 20, 20, 400, 110 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    std::string strFormat = STR_OPT_MAIN;
    bool done;

    result = mManagerwindow.LoadResources( mResources.Font(),
                                           mGraphics.Find(GFX_BORDER),
                                           mGraphics.Find(GFX_POINTER) );

    if (result==SIG_NONE)
    {
        index = mManagerwindow.CreateNewWindow( rectWindow,
                                                strFormat,
                                                &colrMainColor, NULL );

        done = false;
        while ( done == false && result >= SIG_NONE )
        {
            // Start with a dark blue background
            SDL_FillRect( mScreen.Image(), NULL, SDL_MapRGB( mScreen.Image()->format, 0x00, 0x00, 0x40 ) );

            result = mManagerwindow.ActivateWindow( index );

            switch ( result )
            {
                case 1:
                    result = Video();
                    break;
                case 2:
                    result = Sound();
                    break;
                case 3:
                    result = KeyControls();
                    break;
                case 4:
                    result = JoyControls();
                    break;
                case 5: // Back
                    result = SIG_NONE;
                    done = true;
                    break;
                default:
                    Error( __FILE__, __LINE__, "menu index out of range\n" );
                    result = SIG_FAIL;
                    break;
            }
        }
    }

    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CMenuOptions::Video( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    int8_t i;
    SDL_Rect rectWindow = { 200, 200, 400, 200 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    vec_string_t variables;
    bool video_updated, done;
    bool Fullscreen[2], Doublebuf[2];
    int16_t Vidmode[2], Depth[2];
    uint32_t flags;
    std::string strWidth, strHeight, strDepth, strFullscreen, strDoublebuf;
    std::string strFormat = STR_OPT_VIDEO;

    done            = false;
    video_updated   = false;

    index = mManagerwindow.CreateNewWindow( rectWindow,
                                            strFormat,
                                            variables,
                                            &colrMainColor, NULL );

    while ( done == false && result >= SIG_NONE )
    {
        if ( video_updated == false )
        {
            Vidmode[OLD]       = Vidmode[NEW]     = mResources.Options().Screen().VideoMode();
            Depth[OLD]         = Depth[NEW]       = mResources.Options().Screen().DepthMode();
            Fullscreen[OLD]    = Fullscreen[NEW]  = mResources.Options().Screen().Fullscreen();
            Doublebuf[OLD]     = Doublebuf[NEW]   = mResources.Options().Screen().Doublebuf();
        }

        strWidth        = i_to_a(limitsScreenWidth[Vidmode[NEW]]);
        strHeight       = i_to_a(limitsScreenHeight[Vidmode[NEW]]);
        strDepth        = i_to_a(limitsScreenDepth[Depth[NEW]]);
        strFullscreen   = Fullscreen[NEW] ? TRUE : FALSE;
        strDoublebuf    = Doublebuf[NEW]  ? TRUE : FALSE;

        variables.clear();
        variables.resize( variables.size()+1, &strWidth );
        variables.resize( variables.size()+1, &strHeight );
        variables.resize( variables.size()+1, &strDepth );
        variables.resize( variables.size()+1, &strFullscreen );
        variables.resize( variables.size()+1, &strDoublebuf );

        mManagerwindow.UpdateWindowVariables( index, variables );
        mManagerwindow.ReprocessWindow( index );
        result = mManagerwindow.ActivateWindow( index );

        if (result>SIG_NONE)
        {
            switch ( result )
            {
                case 1: // Resolution
                    Vidmode[NEW] = ChangeResolution( Vidmode[NEW] );

                    if ( Vidmode[OLD] != Vidmode[NEW] )
                    {
                        video_updated = true;
                    }
                    break;
                case 2: // Depth +
                    Depth[NEW]--;
                    if ( Depth[NEW] < 0 )
                    {
                        Depth[NEW] = 0;
                    }
                    video_updated = true;
                    break;
                case 3: // Depth -
                    Depth[NEW]++;
                    if ( Depth[NEW] >= SCREEN_DEPTHS )
                    {
                        Depth[NEW] = SCREEN_DEPTHS-1;
                    }
                    video_updated = true;
                    break;
                case 4: // Fullscren
                    Fullscreen[NEW] = !Fullscreen[NEW];
                    video_updated = true;
                    break;
                case 5: // Doublebuffer
                    Doublebuf[NEW] = !Doublebuf[NEW];
                    video_updated = true;
                    break;
                case 6: // Apply
                    if ( video_updated )
                    {
                        flags = SDL_HWSURFACE;
                        if ( mResources.Options().Screen().Fullscreen() == true )
                        {
                            flags |= SDL_FULLSCREEN;
                        }
                        if ( mResources.Options().Screen().Doublebuf() == true )
                        {
                            flags |= SDL_DOUBLEBUF;
                        }

                        result = mResources.CheckVideoMode( limitsScreenWidth[Vidmode[NEW]],
                                                            limitsScreenHeight[Vidmode[NEW]],
                                                            limitsScreenDepth[Depth[NEW]],
                                                            flags );

                        if ( result != SIG_FAIL )
                        {
                            // SDL has suggested the depth be changed
                            if ( result != 0 )
                            {
                                if ( UseSuggestedSettings( result, limitsScreenDepth[Depth[NEW]] ) == 1 )
                                {
                                    // Get the index of the suggested screen depth
                                    for ( i=0; i<SCREEN_DEPTHS; i++ )
                                    {
                                       if (limitsScreenDepth[i] == result)
                                       {
                                            Depth[NEW] = i;
                                            break;
                                       }
                                    }
                                }
                            }
                            mResources.Options().Screen().VideoMode(Vidmode[NEW]);
                            mResources.Options().Screen().DepthMode(Depth[NEW]);
                            mResources.Options().Screen().Fullscreen(Fullscreen[NEW]);
                            mResources.Options().Screen().Doublebuf(Doublebuf[NEW]);

                            result = mResources.SetVideoMode();
                            mManagerwindow.ResetWindows();  // The windows need to be reset to adjust to the new screen size

                            // Start with a dark blue background
                            SDL_FillRect( mScreen.Image(), NULL, SDL_MapRGB( mScreen.Image()->format, 0x00, 0x00, 0x40 ) );

                            video_updated = false;
                        }
                        else
                        {
                            FailedSettings();
                        }
                    }
                    result = SIG_NONE;
                    break;
                case 7: // Back
                    result = SIG_NONE;
                    done = true;
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

    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CMenuOptions::ChangeResolution( int8_t current_mode )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 200, 200, 150, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    vec_string_t resolutions;
    std::string* res;
    std::string strVidmode, strWidth, strHeight;
    std::string strFormat = STR_OPT_RES;

    for ( uint16_t t=1; t<SCREEN_MODES; t++ )
    {
        strVidmode  = i_to_a(t);
        strWidth    = i_to_a(limitsScreenWidth[t]);
        strHeight   = i_to_a(limitsScreenHeight[t]);

        res = new std::string( strVidmode + ". " + strWidth + "x"  + strHeight );
        resolutions.resize( resolutions.size()+1, res );
    }

    index = mManagerwindow.CreateNewWindow( rectWindow,
                                            strFormat,
                                            resolutions,
                                            &colrMainColor, NULL );

    result = mManagerwindow.ActivateWindow( index );
    if ( SIG_NONE < result )
    {
        if ( result < 0 || result >= SCREEN_MODES )
        {
            result = current_mode;
        }
    }
    else
    {
        Error( __FILE__, __LINE__, "menu index out of range\n" );
        result = SIG_FAIL;
    }

    for ( uint16_t t=0; t<resolutions.size(); t++ )
    {
        delete resolutions.at(t);
    }
    resolutions.clear();

    mManagerwindow.CloseWindow( index );

    return result;
}


int8_t CMenuOptions::Sound( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 200, 200, 250, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    vec_string_t variables;
    bool sound_updated, done;
    int16_t Freq[2], Channels[2], Samples[2];
    std::string strFreq, strChannels, strSample;
    std::string strFormat = STR_OPT_SOUND;

    done            = false;
    sound_updated   = false;

    index = mManagerwindow.CreateNewWindow( rectWindow,
                                            strFormat,
                                            variables,
                                            &colrMainColor, NULL );

    while ( done == false && result >= SIG_NONE )
    {
        if ( sound_updated == false )
        {
            Freq[OLD]      = Freq[NEW]        = mResources.Options().Sound().FrequencyMode();
            Channels[OLD]  = Channels[NEW]    = mResources.Options().Sound().ChannelsMode();
            Samples[OLD]   = Samples[NEW]     = mResources.Options().Sound().SampleSizeMode();
        }

        strFreq     = i_to_a(limitsSoundFreq[Freq[NEW]]);
        strChannels = i_to_a(limitsSoundChannels[Channels[NEW]]);
        strSample   = i_to_a(limitsSoundSamples[Samples[NEW]]);

        variables.clear();
        variables.resize( variables.size()+1, &strFreq );
        variables.resize( variables.size()+1, &strChannels );
        variables.resize( variables.size()+1, &strSample );

        mManagerwindow.UpdateWindowVariables( index, variables );
        mManagerwindow.ReprocessWindow( index );
        result = mManagerwindow.ActivateWindow( index );

        if (result>SIG_NONE)
        {
            switch ( result )
            {
                case 1: // Frequency -
                    Freq[NEW]--;
                    if ( Freq[NEW] < 0 )
                    {
                        Freq[NEW] = 0;
                    }
                    sound_updated = true;
                    break;

                case 2: // Frequency +
                    Freq[NEW]++;
                    if ( Freq[NEW] >= SOUND_FREQ )
                    {
                        Freq[NEW] = SOUND_FREQ-1;
                    }
                    sound_updated = true;
                    break;
                case 3: // Channels -
                    Channels[NEW]--;
                    if ( Channels[NEW] < 0 )
                    {
                        Channels[NEW] = 0;
                    }
                    sound_updated = true;
                    break;
                case 4: // Channels +
                    Channels[NEW]++;
                    if ( Channels[NEW] >= SOUND_CHANNELS )
                    {
                        Channels[NEW] = SOUND_CHANNELS-1;
                    }
                    sound_updated = true;
                    break;
                case 5: // Sample size 0
                    Samples[NEW]--;
                    if ( Samples[NEW] < 0 )
                    {
                        Samples[NEW] = 0;
                    }
                    sound_updated = true;
                    break;
                case 6: // Sample size +
                    Samples[NEW]++;
                    if ( Samples[NEW] >= SOUND_SAMPLE )
                    {
                        Samples[NEW] = SOUND_SAMPLE-1;
                    }
                    sound_updated = true;
                    break;
                case 7: // Apply
                    if ( sound_updated )
                    {
                        mResources.Options().Sound().FrequencyMode(Freq[NEW]);
                        mResources.Options().Sound().ChannelsMode(Channels[NEW]);
                        mResources.Options().Sound().SampleSizeMode(Samples[NEW]);

                        mResources.CloseAudio();
                        result = mResources.OpenAudio();

                        sound_updated = false;
                    }
                    result = SIG_NONE;
                    break;
                case 8: // Back
                    result = SIG_NONE;
                    done = true;
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

    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CMenuOptions::KeyControls( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 200, 200, 200, 150 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    vec_string_t variables;
    bool ctrls_updated, done;
    SDLKey Up[2], Down[2], Left[2], Right[2], Action[2], Menu[2];
    std::string strFormat = STR_OPT_CTRLS;

    done            = false;
    ctrls_updated   = false;

    index = mManagerwindow.CreateNewWindow( rectWindow,
                                            strFormat,
                                            variables,
                                            &colrMainColor, NULL );

    while ( done == false && result >= SIG_NONE )
    {
        if ( ctrls_updated == false )
        {
            Up[OLD]     = Up[NEW]       = mResources.Options().Controls().GetKeyMapping( CTRL_UP );
            Down[OLD]   = Down[NEW]     = mResources.Options().Controls().GetKeyMapping( CTRL_DOWN );
            Left[OLD]   = Left[NEW]     = mResources.Options().Controls().GetKeyMapping( CTRL_LEFT );
            Right[OLD]  = Right[NEW]    = mResources.Options().Controls().GetKeyMapping( CTRL_RIGHT );
            Action[OLD] = Action[NEW]   = mResources.Options().Controls().GetKeyMapping( CTRL_ACTION );
            Menu[OLD]   = Menu[NEW]     = mResources.Options().Controls().GetKeyMapping( CTRL_MENU );
        }

        variables.clear();
        variables.resize( variables.size()+1, &keys_strings[Up[NEW]] );
        variables.resize( variables.size()+1, &keys_strings[Down[NEW]] );
        variables.resize( variables.size()+1, &keys_strings[Left[NEW]] );
        variables.resize( variables.size()+1, &keys_strings[Right[NEW]] );
        variables.resize( variables.size()+1, &keys_strings[Action[NEW]] );
        variables.resize( variables.size()+1, &keys_strings[Menu[NEW]] );

        mManagerwindow.UpdateWindowVariables( index, variables );
        mManagerwindow.ReprocessWindow( index );
        result = mManagerwindow.ActivateWindow( index );

        if (result>SIG_NONE)
        {
            switch ( result )
            {
                case 1: // Up
                    PressAnyKey();
                    Up[NEW] = mResources.Options().Controls().WaitForKeyPress( Up[NEW] );
                    if ( Up[NEW] != Up[OLD] )
                    {
                        mResources.Options().Controls().SetKeyMapping( CTRL_UP, Up[NEW] );
                    }
                    break;
                case 2: // Down
                    PressAnyKey();
                    Down[NEW] = mResources.Options().Controls().WaitForKeyPress( Down[NEW] );
                    if ( Down[NEW] != Down[OLD] )
                    {
                        mResources.Options().Controls().SetKeyMapping( CTRL_DOWN, Down[NEW] );
                    }
                    break;
                case 3: // Left
                    PressAnyKey();
                    Left[NEW] = mResources.Options().Controls().WaitForKeyPress( Left[NEW] );
                    if ( Left[NEW] != Left[OLD] )
                    {
                        mResources.Options().Controls().SetKeyMapping( CTRL_LEFT, Left[NEW] );
                    }
                    break;
                case 4: // Right
                    PressAnyKey();
                    Right[NEW] = mResources.Options().Controls().WaitForKeyPress( Right[NEW] );
                    if ( Right[NEW] != Right[OLD] )
                    {
                        mResources.Options().Controls().SetKeyMapping( CTRL_RIGHT, Right[NEW] );
                    }
                    break;
                case 5: // Action
                    PressAnyKey();
                    Action[NEW] = mResources.Options().Controls().WaitForKeyPress( Action[NEW] );
                    if ( Action[NEW] != Action[OLD] )
                    {
                        mResources.Options().Controls().SetKeyMapping( CTRL_ACTION, Action[NEW] );
                    }
                    break;
                case 6: // Menu
                    PressAnyKey();
                    Menu[NEW] = mResources.Options().Controls().WaitForKeyPress( Menu[NEW] );
                    if ( Menu[NEW] != Menu[OLD] )
                    {
                        mResources.Options().Controls().SetKeyMapping( CTRL_MENU, Menu[NEW] );
                    }
                    break;
                case 7: // Cancel
                    result = SIG_NONE;
                    done = true;
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

    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CMenuOptions::JoyControls( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 200, 200, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    vec_string_t variables;
    bool ctrls_updated, done;
    uint8_t Up[2], Down[2], Left[2], Right[2], Action[2], Menu[2];
    std::string strUp, strDown, strLeft, strRight, strAction, strMenu;
    std::string strFormat = STR_OPT_CTRLS;

    done            = false;
    ctrls_updated   = false;

    index = mManagerwindow.CreateNewWindow( rectWindow,
                                            strFormat,
                                            variables,
                                            &colrMainColor, NULL );

    while ( done == false && result >= SIG_NONE )
    {
        if ( ctrls_updated == false )
        {
            Up[OLD]     = Up[NEW]       = mResources.Options().Controls().GetJoyMapping( CTRL_UP );
            Down[OLD]   = Down[NEW]     = mResources.Options().Controls().GetJoyMapping( CTRL_DOWN );
            Left[OLD]   = Left[NEW]     = mResources.Options().Controls().GetJoyMapping( CTRL_LEFT );
            Right[OLD]  = Right[NEW]    = mResources.Options().Controls().GetJoyMapping( CTRL_RIGHT );
            Action[OLD] = Action[NEW]   = mResources.Options().Controls().GetJoyMapping( CTRL_ACTION );
            Menu[OLD]   = Menu[NEW]     = mResources.Options().Controls().GetJoyMapping( CTRL_MENU );
        }

        strUp       = i_to_a(Up[NEW]);
        strDown     = i_to_a(Down[NEW]);
        strLeft     = i_to_a(Left[NEW]);
        strRight    = i_to_a(Right[NEW]);
        strAction   = i_to_a(Action[NEW]);
        strMenu     = i_to_a(Menu[NEW]);

        variables.clear();
        variables.resize( variables.size()+1, &strUp );
        variables.resize( variables.size()+1, &strDown );
        variables.resize( variables.size()+1, &strLeft );
        variables.resize( variables.size()+1, &strRight );
        variables.resize( variables.size()+1, &strAction );
        variables.resize( variables.size()+1, &strMenu );

        mManagerwindow.UpdateWindowVariables( index, variables );
        mManagerwindow.ReprocessWindow( index );
        result = mManagerwindow.ActivateWindow( index );

        if (result>SIG_NONE)
        {
            switch ( result )
            {
                case 1: // Up
                    PressAnyJoy();
                    Up[NEW] = mResources.Options().Controls().WaitForJoyPress( Up[NEW] );
                    if ( Up[NEW] != Up[OLD] )
                    {
                        mResources.Options().Controls().SetJoyMapping( CTRL_UP, Up[NEW] );
                    }
                    break;
                case 2: // Down
                    PressAnyJoy();
                    Down[NEW] = mResources.Options().Controls().WaitForJoyPress( Down[NEW] );
                    if ( Down[NEW] != Down[OLD] )
                    {
                        mResources.Options().Controls().SetJoyMapping( CTRL_DOWN, Down[NEW] );
                    }
                    break;
                case 3: // Left
                    PressAnyJoy();
                    Left[NEW] = mResources.Options().Controls().WaitForJoyPress( Left[NEW] );
                    if ( Left[NEW] != Left[OLD] )
                    {
                        mResources.Options().Controls().SetJoyMapping( CTRL_LEFT, Left[NEW] );
                    }
                    break;
                case 4: // Right
                    PressAnyJoy();
                    Right[NEW] = mResources.Options().Controls().WaitForJoyPress( Right[NEW] );
                    if ( Right[NEW] != Right[OLD] )
                    {
                        mResources.Options().Controls().SetJoyMapping( CTRL_RIGHT, Right[NEW] );
                    }
                    break;
                case 5: // Action
                    PressAnyJoy();
                    Action[NEW] = mResources.Options().Controls().WaitForJoyPress( Action[NEW] );
                    if ( Action[NEW] != Action[OLD] )
                    {
                        mResources.Options().Controls().SetJoyMapping( CTRL_ACTION, Action[NEW] );
                    }
                    break;
                case 6: // Menu
                    PressAnyJoy();
                    Menu[NEW] = mResources.Options().Controls().WaitForJoyPress( Menu[NEW] );
                    if ( Menu[NEW] != Menu[OLD] )
                    {
                        mResources.Options().Controls().SetJoyMapping( CTRL_MENU, Menu[NEW] );
                    }
                    break;
                case 7: // Cancel
                    result = SIG_NONE;
                    done = true;
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

    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CMenuOptions::UseSuggestedSettings( uint8_t cur, uint8_t sug )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 200, 200, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    vec_string_t variables;
    std::string strCurrent, strSuggest;
    std::string strFormat = STR_OPT_CHG;

    strCurrent  = i_to_a(cur);
    strSuggest  = i_to_a(sug);

    variables.clear();
    variables.resize( variables.size()+1, &strCurrent );
    variables.resize( variables.size()+1, &strSuggest );

    index = mManagerwindow.CreateNewWindow( rectWindow,
                                            strFormat,
                                            variables,
                                            &colrMainColor, NULL );
    result = mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CMenuOptions::PressAnyKey( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 200, 200, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    std::string strFormat = STR_OPT_NEWKEY;

    index = mManagerwindow.CreateNewWindow( rectWindow,
                                            strFormat,
                                            &colrMainColor, NULL );
    mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CMenuOptions::PressAnyJoy( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 200, 200, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    std::string strFormat = STR_OPT_NEWKEY;

    index = mManagerwindow.CreateNewWindow( rectWindow,
                                            strFormat,
                                            &colrMainColor, NULL );
    mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}

int8_t CMenuOptions::FailedSettings( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectWindow = { 200, 200, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    std::string strFormat = STR_OPT_FAILED;

    index = mManagerwindow.CreateNewWindow( rectWindow,
                                            strFormat,
                                            &colrMainColor, NULL );
    mManagerwindow.ActivateWindow( index );
    mManagerwindow.CloseWindow( index );

    return result;
}
