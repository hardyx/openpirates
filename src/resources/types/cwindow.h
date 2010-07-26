/**
 *  @section LICENSE
 *
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
 *
 *  @section LOCATION
 */

#ifndef CWINDOW_H
#define CWINDOW_H

#include "global.h"
#include "resources/cresources.h"
#include "resources/controls/ccontrols.h"
#include "resources/options/coptions.h"
#include "resources/types/cword.h"
#include "resources/types/cgraphic.h"
#include "sprites/cspritedynamic.h"
#include "timers/cframelimit.h"
#include "timers/ctimer.h"

/** @brief This class represents a interactive window which can display a graphic or text.
 */
class CWindow
{
	public:
        /** Constructor for window with no text */
        CWindow( CControls& controls );
        /** Constructor for window with a no varables. */
        CWindow( SDL_Rect& size, CControls& events,
                 std::string& text,
                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image );
        /** Constructor for window with a single varable. */
        CWindow( SDL_Rect& size, CControls& events,
                 std::string& text,
                 std::string& variable,
                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image );
        /** Constructor for window with multiple varables. */
        CWindow( SDL_Rect& size, CControls& events,
                 std::string& text,
                 vec_string_t& variables,
                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image );
        /** Destructor. */
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
        void DrawBackgroundColor( SDL_Surface* screen, const SDL_Color& color );
        int8_t Activate( CResources& resources, CGraphic* border_gfx, CSpriteDynamic& pointer, TTF_Font* font );

    protected:
        CControls&          mControls;
        CFramelimit         mFrameControl;
        CGraphic            mBackground;
        CGraphic*           mpBkgndImage;   // Optional bitmap for background inside border
        SDL_Color*          mpBkgndColor;   // Optional color to fill the background inside border
        std::string*        mpText;         // Optional text to be drawn over background
        std::string*        mpVariable;     // Optional if there is only one variable
        vec_string_t*       mpVariables;    // Optional if there are no variables defined in the text std::string
        CWord::vec_word_t   mWords;
        vec_bool_t          mSelectableParagraphs;  // Collection for determining which lines of text can be selected
        SDL_Color           mFontFadeColor; // Change color of a selected line
        SDL_Rect            mDimensions;    // The position and size of the window
        int16_t             mLoopTime;
        int16_t             mLoopTimeAvg;
        uint8_t             mFontFadeSpeed;
        uint8_t             mFps;
        uint8_t             mFskip;
        bool                mPointerDrag;
        bool                mActive;

        void    SetDefaults( void );
        void    ProcessText( void );
		int8_t  Draw( SDL_Surface* screen, TTF_Font* font, SDL_Color* fontcolor, CGraphic* border_gfx, CSpriteDynamic& pointer, int8_t pointer_select = 0 );
        int8_t  DrawText( SDL_Surface* screen, TTF_Font* font, SDL_Color* fontcolor, SDL_Rect* dimensions, CSpriteDynamic& pointer, int8_t pointer_select );
        void    DrawBorder( SDL_Surface* screen, CGraphic* border_gfx );
        int8_t  HandleEvents( CResources& resources, CSpriteDynamic& pointer );
        void    FadeFontColor( void );
        void    FadeColor( uint8_t& colorcomp, int8_t delta );

    private:
        CWindow(const CWindow&);
        CWindow& operator=(const CWindow&);
};

typedef std::vector<CWindow*> vec_window_t;

#ifdef DEBUG
extern bool gDrawCollsionBox;
#endif

#endif // CWINDOW_H
