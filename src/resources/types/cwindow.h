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

#ifndef CWINDOW_H
#define CWINDOW_H

#include "global.h"
#include "resources/cresources.h"
#include "resources/ccontrols.h"
#include "resources/coptions.h"
#include "resources/types/cgraphic.h"
#include "sprites/cspritedynamic.h"
#include "timers/cframelimit.h"
#include "timers/ctimer.h"

class CWord
{
    public:
        CWord() :
            mImage      (),
            mRawword    (),
            mNewline    (false),
            mTabAlign   (0),
            mColAlign   (0),
            mParagraph  (0),
            mXpos       (0),
            mYpos       (0)
        {
        }
		virtual ~CWord() {};

        CGraphic    mImage;     // The bitmap version of the text
        std::string mRawword;   // The ascii text to be rendered
        bool        mNewline;   // If the word should be followed by a newline
        uint8_t     mTabAlign;  // Align the text to a tab
        uint8_t     mColAlign;  // Align the text to a fixed column position
        uint8_t     mParagraph; // The paragraph group that the word belongs to
        int16_t     mXpos;      // Position of the surface
        int16_t     mYpos;
};

typedef std::vector<CWord*> vec_word_t;

// Class that provides a window for showing text and getting user input
class CWindow
{
	public:
        CWindow( CControls& controls );
        CWindow( SDL_Rect& size, CControls& events,
                 std::string& text,
                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image );
        CWindow( SDL_Rect& size, CControls& events,
                 std::string& text,
                 std::string& variable,
                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image );
        CWindow( SDL_Rect& size, CControls& events,
                 std::string& text,
                 vec_string_t& variables,
                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image );
		virtual ~CWindow();

		void ResetWindow( void );
        void UpdateDimensions( SDL_Rect& dim );
        void UpdatePosition( int16_t x, int16_t y );
        void UpdateSize( int16_t w, int16_t h );
        void UpdateText( std::string& text );
        void UpdateVariable( std::string& variable );
        void UpdateVariables( vec_string_t& variables );
        void UpdateBackgroundImage( CGraphic* bkgnd_image );
        void UpdateBackgroundColor( SDL_Color* bkgnd_color );
        void Reprocess( void );
        int8_t Activate( CResources& resources, CGraphic* border_gfx, CSpriteDynamic& pointer, TTF_Font* font );

    protected:
        CControls&      mControls;
        CFramelimit     mFrameControl;
        CGraphic        mBackground;
        CGraphic*       mpBkgndImage;   // Optional bitmap for background inside border
        SDL_Color*      mpBkgndColor;   // Optional color to fill the background inside border
        std::string*    mpText;         // Optional text to be drawn over background
        std::string*    mpVariable;     // Optional if there is only one variable
        vec_string_t*   mpVariables;            // Optional if there are no variables defined in the text std::string
        vec_word_t      mWords;
        vec_bool_t      mSelectableParagraphs;  // Collection for determining which lines of text can be selected
        SDL_Color       mFontFadeColor; // Change color of a selected line
        SDL_Rect        mDimensions;    // The position and size of the window
        uint8_t         mFontFadeSpeed;
        uint8_t         mFps;
        uint8_t         mFskip;
        bool            mPointerDrag;
        bool            mActive;

        void    SetDefaults( void );
        void    ProcessText( void );
		int8_t  Draw( SDL_Surface* screen, TTF_Font* font, SDL_Color* fontcolor, CGraphic* border_gfx, CSpriteDynamic& pointer, int8_t pointer_select = 0 );
        int8_t  DrawText( SDL_Surface* screen, TTF_Font* font, SDL_Color* fontcolor, SDL_Rect* dimensions, CSpriteDynamic& pointer, int8_t pointer_select );
        void    DrawBorder( SDL_Surface* screen, CGraphic* border_gfx );
        int8_t  HandleEvents( CResources& resources, CSpriteDynamic& pointer );
        void    FadeFontColor( void );
        void    FadeColor( uint8_t& colorcomp, int8_t delta );

    private:
        CWindow(const CWindow &);
        CWindow & operator=(const CWindow&);
};

typedef std::vector<CWindow*> vec_window_t;

#ifdef DEBUG
extern bool gDrawCollsionBox;
#endif

#endif // CWINDOW_H
