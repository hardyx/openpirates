#include "cmenuoptions.h"

#define STR_OPT_MAIN  "Select...\\n\\t01Video Options\\s\\t01Sound Options\\s\\t01Control Options\\s\\t01Back\\s"
#define STR_OPT_VIDEO "Video Options\\n\\t01Width: %1\\u +\\z -\\s\\t01Height: %2\\u +\\z -\\s\\t01Depth: %3\\u +\\z -\\s\\t01Fullscreen:\\u %4\\s\\t01Doublebuffer:\\u %5\\s \\nBack\\z\\t10Apply\\s"
#define STR_OPT_SOUND "Sound Options\\n\\t01Frequency: %1\\u +\\z -\\s\\t01Channels: %2\\u +\\z -\\s\\t01Sample size: %3\\u +\\z -\\s\\sApply\\sBack\\s"
#define STR_OPT_CTRLS "Control Options\\n\\t01Up: %1\\s\\t01Down: %2\\s\\t01Left: %3\\s\\t01Right: %4\\s\\t01Action: %5\\s\\t01Menu: %6\\sApply\\sBack\\s"

CMenuOptions::CMenuOptions( CResources& resources ) :
    mResources      (resources),
    mScreen         (mResources.Screen()),
    mPlayer         (mResources.Data().Player()),
    mStrings        (mResources.Data().Strings()),
    mGraphics       (mResources.Data().Graphics()),
    mManagerwindow  (mResources)
{
}

CMenuOptions::~CMenuOptions()
{
}

int8_t CMenuOptions::Run( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 400, 110 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };
    std::string strFormat = STR_OPT_MAIN;

    result = mManagerwindow.LoadResources( mResources.Font(),
                                           mGraphics.Find(GFX_BORDER),
                                           mGraphics.Find(GFX_POINTER) );

    if (result==SIG_NONE)
    {
        // Start with a dark blue background
        SDL_FillRect( mScreen.Image(), NULL, SDL_MapRGB( mScreen.Image()->format, 0x00, 0x00, 0x40 ) );

        index = mManagerwindow.CreateNewWindow( rectMain,
                                                strFormat,
                                                &colrMainColor, NULL );
        result = mManagerwindow.ActivateWindow( index );

        if (result>SIG_NONE)
        {
            switch ( result )
            {
                case 1:
                    result = Video();
                    break;
                case 2:
                    result = Sound();
                    break;
                case 3:
                    result = Controls();
                    break;
                case 4:
                    result = SIG_QUIT;
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

int8_t CMenuOptions::Video( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    vec_string_t variables;
    bool done;
    uint16_t intWidth, intHeight, intDepth;
    std::string strWidth, strHeight, strDepth;
    std::string strFullscreen, strDoublebuf;
    std::string strFormat = STR_OPT_VIDEO;

    intWidth   = mResources.Options().Screen().Width();
    intHeight  = mResources.Options().Screen().Height();
    intDepth   = mResources.Options().Screen().Bpp();

    done = false;
    while ( done == false && result >= SIG_NONE )
    {
        strWidth   = i_to_a(intWidth);
        strHeight  = i_to_a(intHeight);
        strDepth   = i_to_a(intDepth);

        strFullscreen  = mResources.Options().Screen().Fullscreen() ? TRUE : FALSE;
        strDoublebuf   = mResources.Options().Screen().Doublebuf() ? TRUE : FALSE;

        variables.clear();
        variables.resize( variables.size()+1, &strWidth );
        variables.resize( variables.size()+1, &strHeight );
        variables.resize( variables.size()+1, &strDepth );
        variables.resize( variables.size()+1, &strFullscreen );
        variables.resize( variables.size()+1, &strDoublebuf );

        index = mManagerwindow.CreateNewWindow( rectMain,
                                                strFormat,
                                                variables,
                                                &colrMainColor, NULL );
        result = mManagerwindow.ActivateWindow( index );

        if (result>SIG_NONE)
        {
            switch ( result )
            {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    result = SIG_QUIT;
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

int8_t CMenuOptions::Sound( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };

    return result;
}

int8_t CMenuOptions::Controls( void )
{
    int8_t result = SIG_NONE;
    int8_t index;
    SDL_Rect rectMain = { 20, 20, 200, 100 };
    SDL_Color colrMainColor = { 0, 0, 0, 0 };


    return result;
}
