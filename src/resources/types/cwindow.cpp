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

#include "cwindow.h"

CWindow::CWindow( CControls& controls ) :
    mControls       (controls),
    mFrameControl   (),
    mBackground     (),
    mpBkgndImage    (NULL),
    mpBkgndColor    (NULL),
    mpText          (NULL),
    mpVariable      (NULL),
    mpVariables     (NULL),
    mWords          (),
    mSelectableParagraphs(),
    mFontFadeColor  (),
    mDimensions     (),
    mFontFadeSpeed  (0),
    mFps            (0),
    mFskip          (0),
    mPointerDrag    (false),
    mActive         (false)
{
    SetDefaults();
}

CWindow::CWindow(SDL_Rect& size, CControls& controls,
                 std::string& text,
                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image) :
    mControls       (controls),
    mFrameControl   (),
    mBackground     (),
    mpBkgndImage    (NULL),
    mpBkgndColor    (NULL),
    mpText          (NULL),
    mpVariable      (NULL),
    mpVariables     (NULL),
    mWords          (),
    mSelectableParagraphs(),
    mFontFadeColor  (),
    mDimensions     (),
    mFontFadeSpeed  (0),
    mFps            (0),
    mFskip          (0),
    mPointerDrag    (false),
    mActive         (false)
{
    SetDefaults();

    UpdateText( text );
    // Load data from pointers
    UpdateDimensions( size );
    if (bkgnd_color!=NULL)
        UpdateBackgroundColor( bkgnd_color );
    if (bkgnd_image!=NULL)
        UpdateBackgroundImage( bkgnd_image );

    ProcessText();
}

CWindow::CWindow(SDL_Rect& size, CControls& controls,
                 std::string& text,
                 std::string& variable,
                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image) :
    mControls       (controls),
    mFrameControl   (),
    mBackground     (),
    mpBkgndImage    (NULL),
    mpBkgndColor    (NULL),
    mpText          (NULL),
    mpVariable      (NULL),
    mpVariables     (NULL),
    mWords          (),
    mSelectableParagraphs(),
    mFontFadeColor  (),
    mDimensions     (),
    mFontFadeSpeed  (0),
    mFps            (0),
    mFskip          (0),
    mPointerDrag    (false),
    mActive         (false)
{
    SetDefaults();

    UpdateText( text );
    UpdateVariable( variable );
    // Load data from pointers
    UpdateDimensions( size );
    if (bkgnd_color!=NULL)
        UpdateBackgroundColor( bkgnd_color );
    if (bkgnd_image!=NULL)
        UpdateBackgroundImage( bkgnd_image );

    ProcessText();
}

CWindow::CWindow(SDL_Rect& size, CControls& controls,
                 std::string& text,
                 vec_string_t& variables,
                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image) :
    mControls       (controls),
    mFrameControl   (),
    mBackground     (),
    mpBkgndImage    (NULL),
    mpBkgndColor    (NULL),
    mpText          (NULL),
    mpVariable      (NULL),
    mpVariables     (NULL),
    mWords          (),
    mSelectableParagraphs(),
    mFontFadeColor  (),
    mDimensions     (),
    mFontFadeSpeed  (0),
    mFps            (0),
    mFskip          (0),
    mPointerDrag    (false),
    mActive         (false)
{
    SetDefaults();

    UpdateText( text );
    UpdateVariables( variables );
    // Load data from pointers
    UpdateDimensions( size );
    if (bkgnd_color!=NULL)
        UpdateBackgroundColor( bkgnd_color );
    if (bkgnd_image!=NULL)
        UpdateBackgroundImage( bkgnd_image );

    ProcessText();
}

CWindow::~CWindow()
{
    ResetWindow();

    Log( " ...CWindow: Released\n" );
}

void CWindow::SetDefaults( void )
{
     // Set defaults
    mDimensions.x   = 0;
    mDimensions.y   = 0;
    mDimensions.w   = 0;
    mDimensions.h   = 0;

    mFontFadeColor.r = 0;
    mFontFadeColor.g = 0;
    mFontFadeColor.b = 0;

    mFontFadeSpeed  = 5;
    mFps            = 0;
    mPointerDrag    = false;
    mActive         = false;
    mpText          = NULL;
    mpVariables     = NULL;
    mpVariable      = NULL;
    mpBkgndColor    = NULL;
    mpBkgndImage    = NULL;
    mWords.clear();
    mSelectableParagraphs.clear();
}

void CWindow::ResetWindow( void )
{
    if ( mWords.size() > 0 )
    {
        if ( mWords.size() > 0 )
        {
            for ( int16_t i=mWords.size()-1; i>=0; i-- )
            {
                delete mWords.at(i);
            }
            mWords.clear();
        }
        mSelectableParagraphs.clear();
    }
}

void CWindow::UpdateDimensions( SDL_Rect& dim )
{
    UpdatePosition( dim.x, dim.y );
    UpdateSize( dim.w, dim.h );
}

void CWindow::UpdatePosition( int16_t x, int16_t y )
{
    mDimensions.x = x;
    mDimensions.y = y;
}

void CWindow::UpdateSize( int16_t w, int16_t h )
{
    mDimensions.w = w;
    mDimensions.h = h;
}

void CWindow::UpdateText( std::string& text )
{
    mpText = &text;
}

void CWindow::UpdateVariable( std::string& variable )
{
    mpVariable = &variable;
}

void CWindow::UpdateVariables( vec_string_t& variables )
{
    mpVariables = &variables;
}

void CWindow::UpdateBackgroundImage( CGraphic* bkgnd_image )
{
    mpBkgndImage = bkgnd_image;
}

void CWindow::UpdateBackgroundColor( SDL_Color* bkgnd_color )
{
    mpBkgndColor = bkgnd_color;
}

void CWindow::Reprocess( void )
{
    ResetWindow();
    ProcessText();
}

int8_t CWindow::Activate( CResources& resources, CGraphic* border_gfx, CSpriteDynamic& pointer, TTF_Font* font )
{
    int8_t paragraph_result = SIG_NONE;
    bool user_interactive = false;
    int8_t user_result = EVENT_NONE;

    CGraphic& screen            = resources.Screen();
    CFontOptions& fontoptions   = resources.Options().Font();
#ifdef DEBUG
    #define SIZE 100
    CGraphic debug_message;
    char debug_caption[SIZE];
#endif

    // Determine if any part of this window is selectable
    for ( uint16_t t=0; t<mSelectableParagraphs.size(); t++ )
    {
        if ( mSelectableParagraphs.at(t) == true )
        {
            user_interactive = true;  // There is at least one selectable paragraph
            break;
        }
    }

    if ( user_interactive == true )
    {
        while ( paragraph_result == SIG_NONE )
        {
            // Save the background, so the pointer doesnt blur
            if ( mActive == false )
            {
                mBackground.AssignImage( SDL_CreateRGBSurface( SDL_HWSURFACE,
                                                               screen.Image()->w,
                                                               screen.Image()->h,
                                                               screen.Image()->format->BitsPerPixel,
                                                               0, 0, 0, 0) );
                screen.ApplyImage( 0, 0, mBackground.Image() );
                mActive = true;
            }
            mBackground.ApplyImage( 0, 0, screen.Image() );

            // Check events
            user_result = HandleEvents( resources, pointer );

            if ( EVENT_NONE     == user_result ||
                 EVENT_PRESSED  == user_result ||
                 EVENT_RELEASED == user_result    )
            {
                // Draw the window
                if (mFrameControl.FrameSkip()==false)
                {
                    // Draw and handle the pointer
                    paragraph_result = Draw( screen.Image(), font, fontoptions.Color(), border_gfx, pointer, user_result );

                    pointer.Draw( screen.Image() );

#ifdef DEBUG
                    snprintf( debug_caption, SIZE, "FPS Total: %d Drawn: %d Skipped: %d", mFps+mFskip, mFps, mFskip );
                    debug_message.AssignImage(TTF_RenderText_Solid( font, debug_caption, *fontoptions.Color() ));  //Draw the text
                    debug_message.ApplyImage( 0, 0, screen.Image() ); //FPS
                    debug_message.ReleaseImage();
#endif

                    // Send the final frame to the screen
                    if ( SDL_Flip( screen.Image() ) == -1 )
                    {
                        Error( __FILE__, __LINE__, "CWindow: SDL_Flip failed\n" );
                        paragraph_result = SIG_FAIL;
                        break;
                    }
                }
                mFrameControl.ControlFPS( FRAME_LIMIT, FRAME_CALC );
#ifdef DEBUG
                mFps   = mFrameControl.FramesDrawn();
                mFskip = mFrameControl.FramesSkipped();
#endif
            }
            else
            {
                Error( __FILE__, __LINE__, "CWindow: returned unexpected user event\n" );
                paragraph_result = SIG_FAIL;
                break;
            }
        }
    }
    else
    {
        Draw( screen.Image(), font, fontoptions.Color(), border_gfx, pointer );
    }

    return paragraph_result;
}

void CWindow::ProcessText( void )
{
    uint8_t index = 0;
    uint8_t paragraph = 0;
    std::string::iterator text_iterator;
    CWord* current_word = NULL;

    // Process each character
    for ( text_iterator = mpText->begin(); text_iterator < mpText->end(); text_iterator++ )
    {
        if ( current_word == NULL )
        {
            current_word = new CWord();
            current_word->mParagraph  = paragraph;
            current_word->mNewline    = false;
            current_word->mTabAlign      = 0;
        }

        switch ( *text_iterator )
        {
            case '\\':  // Formatting
                text_iterator++;
                if ( text_iterator != mpText->end() )
                {
                    switch ( *text_iterator )
                    {
                        case 'u':   //  end section on the current line (not selectable)
                            mSelectableParagraphs.resize( mSelectableParagraphs.size()+1, false );
                            mWords.resize( mWords.size()+1, current_word );
                            current_word = NULL;
                            paragraph++;
                            break;
                        case 'n':   // end section on a new line (not selectable)
                            mSelectableParagraphs.resize( mSelectableParagraphs.size()+1, false );
                            current_word->mNewline = true;
                            mWords.resize( mWords.size()+1, current_word );
                            current_word = NULL;
                            paragraph++;
                            break;
                        case 'z':   // end section on the current line and preceding line text is selectable
                            mSelectableParagraphs.resize( mSelectableParagraphs.size()+1, true );
                            mWords.resize( mWords.size()+1, current_word );
                            current_word = NULL;
                            paragraph++;
                            break;
                        case 's':   // end section on a new line and preceding line text is selectable
                            mSelectableParagraphs.resize( mSelectableParagraphs.size()+1, true );
                            current_word->mNewline = true;
                            mWords.resize( mWords.size()+1, current_word );
                            current_word = NULL;
                            paragraph++;
                            break;
                        case 't':
                            // First digit
                            text_iterator++;
                            current_word->mTabAlign = (*text_iterator-0x30)*10;
                            // Second digit
                            text_iterator++;
                            current_word->mTabAlign += (*text_iterator-0x30);
                            break;
                        case 'c':
                            // First digit
                            text_iterator++;
                            current_word->mColAlign = (*text_iterator-0x30)*10;
                            // Second digit
                            text_iterator++;
                            current_word->mColAlign += (*text_iterator-0x30);
                            break;
                        case '\\':
                            current_word->mRawword += *text_iterator;
                            break;
                        default:
                            Error( __FILE__, __LINE__, "CWindow: unknown text iterator %c\n", *text_iterator );
                            break;
                    }
                }
                break;
            case '%':   // Variables
                text_iterator++;
                if ( mpVariables != NULL )
                {
                    if ( mpVariables->size() > 0 )
                    {
                        if ( text_iterator != mpText->end() )
                        {
                            if ( *text_iterator == 'a' || *text_iterator == 'A' )
                            {
                                for ( uint8_t v=0; v<mpVariables->size(); v++ )
                                {
                                    current_word = new CWord();
                                    current_word->mParagraph = paragraph;
                                    current_word->mNewline   = true;
                                    current_word->mTabAlign     = 1;
                                    current_word->mRawword  += mpVariables->at(v)->c_str();
                                    mSelectableParagraphs.resize( mSelectableParagraphs.size()+1, true );
                                    mWords.resize( mWords.size()+1, current_word );

                                    paragraph++;    // Make the current paragraph line selectable
                                }
                                current_word = NULL;
                            }
                            else
                            {
                                // Get the variable text
                                if ( (*text_iterator >= 0x30) && (*text_iterator <= 0x39) )
                                {
                                    index = *text_iterator - 0x30;
                                }

                                text_iterator++;
                                if ( (*text_iterator >= 0x30) && (*text_iterator <= 0x39) )
                                {
                                    index *= 10;
                                    index += *text_iterator - 0x30;
                                }
                                else
                                {
                                    text_iterator--;
                                }
                                index--;

                                if (index <= mpVariables->size()-1 )
                                {
                                    current_word->mRawword += mpVariables->at(index)->c_str();
                                }
                                else
                                {
                                    Error( __FILE__, __LINE__, "CWindow: requested to replace a text variable, \
                                                                but not enough variables exist. index: %d total: %d\n", index, mpVariables->size() );
                                }
                            }
                        }
                    }
                }
                else if ( mpVariable != NULL )
                {
                    current_word->mRawword += mpVariable->c_str();
                }
                else
                {
                    current_word->mRawword += "VARERR!";
                }
                break;
            case ' ':   // Separate Words by spaces
                current_word->mRawword += *text_iterator;
                if ( current_word->mRawword.length() > 1 )
                {
                    mWords.resize( mWords.size()+1, current_word );
                    current_word = NULL;
                }
                break;
            default:    // Any other character
                current_word->mRawword += *text_iterator;
                break;
        }
    }
}

int8_t CWindow::Draw( SDL_Surface* screen, TTF_Font* font, SDL_Color* fontcolor, CGraphic* border_gfx, CSpriteDynamic& pointer, int8_t pointer_select )
{
    SDL_Rect background = mDimensions;
    SDL_Rect backcolor  = mDimensions;
    int8_t paragraph_result = -1;

    // Compensate for the border
    if ( border_gfx != NULL )
    {
        background.x += border_gfx->ClipBox().w;
        background.y += border_gfx->ClipBox().h;

        // Fill the entire area including the border
        backcolor.h += border_gfx->ClipBox().h * 2;
        backcolor.w += border_gfx->ClipBox().w * 2;
    }

    // Background
    if ( mpBkgndColor != NULL )
    {
        SDL_FillRect( screen, &backcolor, SDL_MapRGB( screen->format, mpBkgndColor->r, mpBkgndColor->g, mpBkgndColor->b ) );
    }
    else if ( mpBkgndImage != NULL )
    {
        mpBkgndImage->ApplyImage( background.x, background.y, screen );
    }

    // Determine actual width and height of bitmap
    if ( mDimensions.w == 0 && mDimensions.h == 0 && mpBkgndImage != NULL )
    {
        mDimensions.w = mpBkgndImage->Image()->w;
        mDimensions.h = mpBkgndImage->Image()->h;
    }

    // Text
    paragraph_result = DrawText( screen, font, fontcolor, &background, pointer, pointer_select );

    // Border
    if ( border_gfx != NULL )
    {
        DrawBorder( screen, border_gfx );
    }

    return paragraph_result;
}

#define WINDOW_SIGNAL_ORIGIN 1
int8_t CWindow::DrawText( SDL_Surface* screen, TTF_Font* font, SDL_Color* fontcolor, SDL_Rect* dimensions, CSpriteDynamic& pointer, int8_t pointer_select )
{
    int16_t x = 0;
    int16_t y = 0;
    int8_t MaxCharHeight       = TTF_FontHeight(font);
    int8_t paragraph_current   = 0;
    int8_t hover_paragraph     = -1;
    int8_t paragraph_result    = SIG_NONE;

    FadeFontColor();

    // Go through each word to determine if any part of paragraph is being hovered over
    for ( uint16_t t=0; t<mWords.size(); t++ )
    {
        if ( mWords.at(t)->mImage.Image() != NULL && mWords.at(t)->mParagraph <= mSelectableParagraphs.size()-1 )
        {
            if ( mSelectableParagraphs.at( mWords.at(t)->mParagraph ) == true &&
                pointer.XPos() >= mWords.at(t)->mXpos && pointer.XPos() <= mWords.at(t)->mXpos + mWords.at(t)->mImage.Image()->w &&
                pointer.YPos() >= mWords.at(t)->mYpos && pointer.YPos() <= mWords.at(t)->mYpos + mWords.at(t)->mImage.Image()->h )
            {
                hover_paragraph = mWords.at(t)->mParagraph;
                if ( pointer_select == 1 )
                {
                    paragraph_result = WINDOW_SIGNAL_ORIGIN;
                    for ( uint16_t i=mWords.at(t)->mParagraph-1; i>0; i-- )
                    {
                        if ( mSelectableParagraphs.at(i) == true )
                        {
                            paragraph_result++;
                        }
                    }
                }
                break;
            }
        }
    }

    // Go through each word for rendering
    for ( uint16_t t=0; t<mWords.size(); t++ )
    {
        // Render the Text
        if ( mWords.at(t)->mRawword.length() > 0 )
        {
            if ( hover_paragraph >= 0 && mWords.at(t)->mParagraph == hover_paragraph )
            {
                if ( mWords.at(t)->mImage.Image() != NULL ) mWords.at(t)->mImage.ReleaseImage();
                mWords.at(t)->mImage.AssignImage( TTF_RenderText_Solid( font, mWords.at(t)->mRawword.c_str(), mFontFadeColor ) );
            }
            else
            {
                if ( mWords.at(t)->mImage.Image() != NULL ) mWords.at(t)->mImage.ReleaseImage();
                mWords.at(t)->mImage.AssignImage( TTF_RenderText_Solid( font, mWords.at(t)->mRawword.c_str(), *fontcolor ) );
            }

            if ( mWords.at(t)->mImage.Image() == NULL )
            {
                Error( __FILE__, __LINE__, "CWindow: Drawtext failed %s\n", mWords.at(t)->mRawword.c_str() );
                return -1;
            }

            // Tab Alignment
            if ( mWords.at(t)->mTabAlign > 0 )
            {
                uint16_t div = screen->w/(screen->w/(10*mWords.at(t)->mTabAlign));

                for( int i=0; i<screen->w; i+=div )
                {
                    if (i > x)
                    {
                        x = i;
                        break;
                    }
                }
            }

            // Column Alignment
            #define TEXT_COL_DIV 10
            if ( mWords.at(t)->mColAlign > 0 )
            {
                x = mWords.at(t)->mColAlign*TEXT_COL_DIV;
            }

            // Determine the word will fit on the current line
            if ( (x > 0 && x + mWords.at(t)->mImage.Image()->w > dimensions->w) )
            {
                x = 0;
                y += MaxCharHeight;
                paragraph_current = mWords.at(t)->mParagraph;

                // If the words go beyond the bottom of the window, expand the window to fit
                if ( y >= mDimensions.h )
                {
                    mDimensions.h = y + MaxCharHeight;
                }
            }

            // Draw the Text
            mWords.at(t)->mXpos = dimensions->x + x;
            mWords.at(t)->mYpos = dimensions->y + y;
            if ( mWords.at(t)->mImage.Image() != NULL )
            {
                mWords.at(t)->mImage.ApplyImage( mWords.at(t)->mXpos, mWords.at(t)->mYpos, screen, NULL );
            }

            // Set the x,y-coordinates for the next word
            if ( mWords.at(t)->mNewline )
            {
                x = 0;
                y += MaxCharHeight;
                // If the words go beyond the bottom of the window, expand the window to fit
                if ( y >= mDimensions.h )
                {
                    mDimensions.h = y + MaxCharHeight;
                }
            }
            else
            {
                x += mWords.at(t)->mImage.Image()->w;
            }
        }
    }

    return paragraph_result;
}

void CWindow::DrawBorder( SDL_Surface* screen, CGraphic* border_gfx )
{
    SDL_Rect border_clip = border_gfx->ClipBox();

    // 2 tiles per corner, then the gaps on the edges are filled (one corner piece must overlap an edge piece)

    // Upper left corner
    border_clip.x = 0;
    border_clip.y = 0;
    border_gfx->ApplyImage( mDimensions.x, mDimensions.y, screen, &border_clip );
    border_clip.x = 0;
    border_clip.y = border_clip.h;
    border_gfx->ApplyImage( mDimensions.x, mDimensions.y + border_clip.h, screen, &border_clip );

    // Lower left corner
    border_clip.x = border_clip.w;
    border_clip.y = 0;
    border_gfx->ApplyImage( mDimensions.x, mDimensions.y + mDimensions.h, screen, &border_clip );
    border_clip.x = border_clip.w;
    border_clip.y = border_clip.h;
    border_gfx->ApplyImage( mDimensions.x, mDimensions.y + border_clip.h + mDimensions.h, screen, &border_clip );

    // Upper right corner
    border_clip.x = border_clip.w * 2;
    border_clip.y = 0;
    border_gfx->ApplyImage( mDimensions.x + border_clip.w + mDimensions.w, mDimensions.y, screen, &border_clip );
    border_clip.x = border_clip.w * 2;
    border_clip.y = border_clip.h;
    border_gfx->ApplyImage( mDimensions.x + border_clip.w + mDimensions.w, mDimensions.y + border_clip.h, screen, &border_clip );

    // Lower right corner
    border_clip.x = border_clip.w * 3;
    border_clip.y = 0;
    border_gfx->ApplyImage( mDimensions.x + border_clip.w + mDimensions.w, mDimensions.y + mDimensions.h, screen, &border_clip );
    border_clip.x = border_clip.w * 3;
    border_clip.y = border_clip.h;
    border_gfx->ApplyImage( mDimensions.x + border_clip.w + mDimensions.w, mDimensions.y + border_clip.h + mDimensions.h, screen, &border_clip );

    // Left side
    border_clip.x = border_clip.w * 4;
    border_clip.y = 0;
    for ( int16_t height = mDimensions.y + border_clip.h*2; height < mDimensions.y + mDimensions.h - border_clip.h; height += border_clip.h )
    {
        border_gfx->ApplyImage( mDimensions.x, height, screen, &border_clip );
    }
    border_gfx->ApplyImage( mDimensions.x, mDimensions.y + mDimensions.h - border_clip.h, screen, &border_clip ); // The filler

    // Right side
    border_clip.x = border_clip.w * 4;
    border_clip.y = border_clip.h;
    for ( int16_t height = mDimensions.y + border_clip.h*2; height < mDimensions.y + mDimensions.h - border_clip.h; height += border_clip.h )
    {
        border_gfx->ApplyImage( mDimensions.x + border_clip.w + mDimensions.w, height, screen, &border_clip );
    }
    border_gfx->ApplyImage( mDimensions.x + border_clip.w + mDimensions.w, mDimensions.y + mDimensions.h - border_clip.h, screen, &border_clip ); // The filler

    // Top side
    border_clip.x = border_clip.w * 5;
    border_clip.y = 0;
    for ( int16_t width = mDimensions.x + border_clip.w; width < mDimensions.x + mDimensions.w; width += border_clip.w )
    {
        border_gfx->ApplyImage( width, mDimensions.y, screen, &border_clip );
    }
    border_gfx->ApplyImage( mDimensions.x + mDimensions.w, mDimensions.y, screen, &border_clip ); // The filler

    // Bottom side
    border_clip.x = border_clip.w * 5;
    border_clip.y = border_clip.h;
    for ( int16_t width = mDimensions.x + border_clip.w; width < mDimensions.x + mDimensions.w; width += border_clip.w )
    {
        border_gfx->ApplyImage( width, mDimensions.y + border_clip.h + mDimensions.h, screen, &border_clip );
    }
    border_gfx->ApplyImage( mDimensions.x + mDimensions.w, mDimensions.y + border_clip.h + mDimensions.h, screen, &border_clip ); // The filler
}

int8_t CWindow::HandleEvents( CResources& resources, CSpriteDynamic& pointer )
{
    int8_t result = EVENT_NONE;
    CControl control;
    int16_t oldy, oldx;
    int16_t offsety, offsetx;

    oldx = pointer.XPos();
    oldy = pointer.YPos();

	/* Check for events */
	while ( mControls.Poll(control) )
	{
		switch (control.State())
		{
			case CTRL_ACTIVATED:
                //Set the velocity
                switch (control.Type())
                {
                    case CTRL_QUIT:
                        result = SIG_FAIL;
                        break;
                    case CTRL_FULLSCREEN:
                        resources.ToggleFullscreen();
                        break;
                    case CTRL_MENU:
                        // Do Nothing
                        break;
                    case CTRL_MOTION:
                        pointer.XPos( control.X() );
                        pointer.YPos( control.Y() );
                        break;
                    case CTRL_ACTION:
                        result = EVENT_PRESSED;
                        break;
                    case CTRL_UP:
                        pointer.YVel( -POINTER_SPEED );
                        break;
                    case CTRL_DOWN:
                        pointer.YVel( POINTER_SPEED );
                        break;
                    case CTRL_RIGHT:
                        pointer.XVel( POINTER_SPEED );
                        break;
                    case CTRL_LEFT:
                        pointer.XVel( -POINTER_SPEED );
                        break;
#ifdef DEBUG
                    case CTRL_DBG_BOXES:
                        gDrawCollsionBox = !gDrawCollsionBox;
                        break;
#endif
                    default:
                        break;
                }
				break;
			case CTRL_DEACTIVATED:
                //Set the velocity
                switch (control.Type())
                {
                    case CTRL_ACTION:
                        result = EVENT_RELEASED;
                        break;
                    case CTRL_UP:
                         pointer.YVel( 0 );
                        break;
                    case CTRL_DOWN:
                        pointer.YVel( 0 );
                        break;
                    case CTRL_RIGHT:
                        pointer.XVel( 0 );
                        break;
                    case CTRL_LEFT:
                        pointer.XVel( 0 );
                        break;
                    default:
                        break;
                }
				break;
			default:
				break;
		}
	}
    pointer.Move();

    // Keep pointer in window
    if ( pointer.XPos() < 0 )
    {
        pointer.XPos(0);
    }
    int16_t widthlimit = resources.Options().Screen().Width()-(pointer.ClipBox().w/2);
    if ( pointer.XPos() > widthlimit )
    {
        pointer.XPos( widthlimit );
    }

    if ( pointer.YPos() < 0 )
    {
        pointer.YPos(0);
    }
    int16_t heightlimit = resources.Options().Screen().Height()-(pointer.ClipBox().w/2);
    if ( pointer.YPos() > heightlimit )
    {
        pointer.YPos( heightlimit );
    }

    if (EVENT_PRESSED == result )
    {
        if ( pointer.XPos() >= mDimensions.x && pointer.XPos() <= mDimensions.x+16 &&
             pointer.YPos() >= mDimensions.y && pointer.YPos() <= mDimensions.y+16 )
        {
            mPointerDrag = true;
        }
    }
    else if ( EVENT_RELEASED == result )
    {
        mPointerDrag = false;
    }

    if ( mPointerDrag )
    {
        offsetx = pointer.XPos() - oldx;
        offsety = pointer.YPos() - oldy;

        mDimensions.x += offsetx;
        mDimensions.y += offsety;
    }

    return result;
}

void CWindow::FadeFontColor( void )
{
    static uint8_t speed = 0;
    int8_t delta = 5;
    if ( speed == mFontFadeSpeed )
    {
        speed = 0;
        // Blue fade
        FadeColor( mFontFadeColor.b, delta );
        // Green fade
        FadeColor( mFontFadeColor.g, delta );
        // Red fade
        FadeColor( mFontFadeColor.r, delta );
    }
    speed++;
}

void CWindow::FadeColor( uint8_t& color_component, int8_t delta )
{
    if ( color_component > 0 )
    {
        color_component += delta;
    }
    else
    {
        color_component = getRandomValue( 1, 255 );
    }
}
