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

#include "ccontrols.h"

CControls::CControls() :
    mSysMaps        (),
    mKeyMaps        (),
    mJoyMaps        (),
    mMouseMaps      (),
    mEnabledSys     (true),
    mEnabledKey     (true),
    mEnabledJoy     (true),
    mEnabledMouse   (true)
{
    ClearControls();

    // SDL system event maps
    mSysMaps.resize( mSysMaps.size()+1, new CControlMap(CTRL_QUIT,   SDL_QUIT) );

    // SDL key event maps
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_QUIT,   SDL_KEYDOWN, SDLK_c, (SDLMod)KMOD_CTRL) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_UP,     SDL_KEYDOWN, SDLK_UP) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_UP,     SDL_KEYUP,   SDLK_UP) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_DOWN,   SDL_KEYDOWN, SDLK_DOWN) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_DOWN,   SDL_KEYUP,   SDLK_DOWN) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_LEFT,   SDL_KEYDOWN, SDLK_LEFT) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_LEFT,   SDL_KEYUP,   SDLK_LEFT) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_RIGHT,  SDL_KEYDOWN, SDLK_RIGHT) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_RIGHT,  SDL_KEYUP,   SDLK_RIGHT) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_ACTION, SDL_KEYDOWN, SDLK_SPACE) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_ACTION, SDL_KEYUP,   SDLK_SPACE) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_MENU,   SDL_KEYDOWN, SDLK_ESCAPE) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_MENU,   SDL_KEYUP,   SDLK_ESCAPE) );

    // SDL joy event maps
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_UP,     SDL_JOYBUTTONDOWN, JOYBUTTON_UP ) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_UP,     SDL_JOYBUTTONUP,   JOYBUTTON_UP) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_DOWN,   SDL_JOYBUTTONDOWN, JOYBUTTON_DOWN) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_DOWN,   SDL_JOYBUTTONUP,   JOYBUTTON_DOWN) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_LEFT,   SDL_JOYBUTTONDOWN, JOYBUTTON_LEFT) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_LEFT,   SDL_JOYBUTTONUP,   JOYBUTTON_LEFT) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_RIGHT,  SDL_JOYBUTTONDOWN, JOYBUTTON_RIGHT) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_RIGHT,  SDL_JOYBUTTONUP,   JOYBUTTON_RIGHT) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_ACTION, SDL_JOYBUTTONDOWN, JOYBUTTON_ACTION) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_ACTION, SDL_JOYBUTTONUP,   JOYBUTTON_ACTION) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_MENU,   SDL_JOYBUTTONDOWN, JOYBUTTON_ESCAPE) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_MENU,   SDL_JOYBUTTONUP,   JOYBUTTON_ESCAPE) );

    // SDL mouse event maps
    mMouseMaps.resize( mMouseMaps.size()+1, new CControlMap(CTRL_ACTION, SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT) );
    mMouseMaps.resize( mMouseMaps.size()+1, new CControlMap(CTRL_ACTION, SDL_MOUSEBUTTONUP,   SDL_BUTTON_LEFT) );

#ifdef DEBUG
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap(CTRL_DBG_BOXES, SDL_KEYDOWN, SDLK_b, (SDLMod)KMOD_CTRL) );
#endif
}

CControls::~CControls()
{
    ClearControls();
}

void CControls::ClearControls( void )
{
    for (uint8_t i=0; i<mSysMaps.size(); i++)
    {
        delete mSysMaps.at(i);
    }
    mSysMaps.clear();
    for (uint8_t i=0; i<mKeyMaps.size(); i++)
    {
        delete mKeyMaps.at(i);
    }
    mKeyMaps.clear();
    for (uint8_t i=0; i<mJoyMaps.size(); i++)
    {
        delete mJoyMaps.at(i);
    }
    mJoyMaps.clear();
    for (uint8_t i=0; i<mMouseMaps.size(); i++)
    {
        delete mMouseMaps.at(i);
    }
    mMouseMaps.clear();
}

int8_t CControls::Poll(CControl& event)
{
    int8_t result;
    SDL_Event sdl_event;

	/* Check for events */
	result = SDL_PollEvent(&sdl_event);

    event.Type(CTRL_UNKNOWN);
    event.State(CTRL_DEACTIVATED);

	if (result>0)
	{
        switch (sdl_event.type)
        {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                if (mEnabledKey)
                {
                    if (mKeyMaps.size()>0)
                    {
                        for (uint8_t i=0; i<mKeyMaps.size(); i++)
                        {
                            if (mKeyMaps.at(i)->Type() == SDL_KEYDOWN ||
                                mKeyMaps.at(i)->Type() == SDL_KEYUP      )
                            {
                                if ((sdl_event.key.keysym.sym == mKeyMaps.at(i)->Sym()) &&
                                    (mKeyMaps.at(i)->Mod() == 0 ||
                                    (mKeyMaps.at(i)->Mod() > 0 && (sdl_event.key.keysym.mod & mKeyMaps.at(i)->Mod()) > 0)) )
                                {
                                    event.Type( mKeyMaps.at(i)->Action() );
                                    event.State( sdl_event.type==SDL_KEYDOWN ? CTRL_ACTIVATED : CTRL_DEACTIVATED );
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                if (mEnabledMouse)
                {
                    if (mMouseMaps.size()>0)
                    {
                        for (uint8_t i=0; i<mMouseMaps.size(); i++)
                        {
                            if (mMouseMaps.at(i)->Type() == SDL_MOUSEBUTTONDOWN ||
                                mMouseMaps.at(i)->Type() == SDL_MOUSEBUTTONUP      )
                            {
                                if (sdl_event.button.button == mMouseMaps.at(i)->Button() )
                                {
                                    event.Type( mMouseMaps.at(i)->Action() );
                                    event.State( sdl_event.type==SDL_MOUSEBUTTONDOWN ? CTRL_ACTIVATED : CTRL_DEACTIVATED );
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                if (mEnabledMouse)
                {
                    event.Type( CTRL_MOTION );
                    event.State( CTRL_ACTIVATED );
                    event.X( sdl_event.motion.x );
                    event.Y( sdl_event.motion.y );
                }
                break;
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
                if (mEnabledJoy)
                {
                    if (mJoyMaps.size()>0)
                    {
                        for (uint8_t i=0; i<mJoyMaps.size(); i++)
                        {
                            if (mJoyMaps.at(i)->Type() == SDL_JOYBUTTONDOWN ||
                                mJoyMaps.at(i)->Type() == SDL_JOYBUTTONUP      )
                            {
                                if (sdl_event.jbutton.button == mJoyMaps.at(i)->Button() )
                                {
                                    event.Type( mJoyMaps.at(i)->Action() );
                                    event.State( sdl_event.type==SDL_JOYBUTTONDOWN ? CTRL_ACTIVATED : CTRL_DEACTIVATED );
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
            case SDL_QUIT:
                if (mEnabledSys)
                {
                    if (mSysMaps.size()>0)
                    {
                        for (uint8_t i=0; i<mSysMaps.size(); i++)
                        {
                            if (mSysMaps.at(i)->Type() == SDL_QUIT)
                            {
                                event.Type( mSysMaps.at(i)->Action() );
                                event.State( CTRL_ACTIVATED );
                                break;
                            }
                        }
                    }
                }
                break;
            default:
                break;
        }
	}
	return result;
}
