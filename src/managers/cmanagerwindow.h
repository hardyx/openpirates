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

#ifndef CMANAGERWINDOW_H
#define CMANAGERWINDOW_H

#include "global.h"
#include "resources/cresources.h"
#include "resources/types/cwindow.h"

// Class that provides a window for showing text and getting user input
class CManagerWindow
{
	public:
        CManagerWindow(CGraphic& screen, CControls& events, CFontOptions& fontoptions );
        virtual ~CManagerWindow();

        int8_t LoadResources( TTF_Font* font, CGraphic* border, CGraphic* pointer );
        uint8_t CreateNewWindow( SDL_Rect& size,
                                 std::string& text,
                                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image );
        uint8_t CreateNewWindow( SDL_Rect& size,
                                 std::string& text,
                                 std::string& variable,
                                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image );
        uint8_t CreateNewWindow( SDL_Rect& size,
                                 std::string& text,
                                 vec_string_t& variables,
                                 SDL_Color* bkgnd_color, CGraphic* bkgnd_image );
        int8_t AddWindow( CWindow* window );
        void CloseWindows( void );
        void CloseWindow( uint8_t index );
        CWindow* GetWindow( uint8_t index );
        void MoveWindow( uint8_t index, int16_t x, int16_t y );
        uint8_t ActivateWindow( uint8_t index );
        void ReprocessWindow( uint8_t index );
        void UpdateWindowPosition( uint8_t index, int16_t x, int16_t y );
        void UpdateWindowSize( uint8_t index, uint16_t w, uint16_t h );
        void UpdateWindowText( uint8_t index, std::string& text );
        void UpdateWindowVariable( uint8_t index, std::string& variable );
        void UpdateWindowVariables( uint8_t index, vec_string_t& variables );
        void UpdateWindowBackgroundImage( uint8_t index, CGraphic* bkgnd_image );
        void UpdateWindowBackGroundColor( uint8_t index, SDL_Color* bkgnd_color );

    private:
        CGraphic&       mScreen;
        CControls&      mEvents;
        CGraphic*       mpBorder;
        TTF_Font*       mpFont;
        CFontOptions&   mFontOptions;
        CSpriteDynamic  mPointer;
        vec_window_t    mWindows;

        CManagerWindow(const CManagerWindow &);
        CManagerWindow & operator=(const CManagerWindow&);
};

#endif // CMANAGERWINDOW_H
