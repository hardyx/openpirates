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
    mKeyMaps        (),
    mJoyMaps        (),
    mMouseMaps      (),
    mEnabledKey     (true),
    mEnabledJoy     (true),
    mEnabledMouse   (true)
{
    ClearControls();

    //                                                  Internal Event      SDL key/button  SDL Modifier
    // SDL key event maps
#ifdef DEBUG
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap( CTRL_DBG_BOXES,     SDLK_b,         (SDLMod)KMOD_CTRL ) );
#endif
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap( CTRL_QUIT,          SDLK_c,         (SDLMod)KMOD_CTRL ) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap( CTRL_FULLSCREEN,    SDLK_RETURN,    (SDLMod)KMOD_ALT ) );

    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap( CTRL_UP,            SDLK_UP ) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap( CTRL_DOWN,          SDLK_DOWN ) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap( CTRL_LEFT,          SDLK_LEFT ) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap( CTRL_RIGHT,         SDLK_RIGHT ) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap( CTRL_ACTION,        SDLK_SPACE ) );
    mKeyMaps.resize( mKeyMaps.size()+1, new CControlMap( CTRL_MENU,          SDLK_ESCAPE ) );

    // SDL joy event maps
    mJoyMaps.resize( mJoyMaps.size()+1, new CControlMap( CTRL_UP,            JOYBUTTON_UP ) );
    mJoyMaps.resize( mJoyMaps.size()+1, new CControlMap( CTRL_DOWN,          JOYBUTTON_DOWN ) );
    mJoyMaps.resize( mJoyMaps.size()+1, new CControlMap( CTRL_LEFT,          JOYBUTTON_LEFT ) );
    mJoyMaps.resize( mJoyMaps.size()+1, new CControlMap( CTRL_RIGHT,         JOYBUTTON_RIGHT ) );
    mJoyMaps.resize( mJoyMaps.size()+1, new CControlMap( CTRL_ACTION,        JOYBUTTON_ACTION ) );
    mJoyMaps.resize( mJoyMaps.size()+1, new CControlMap( CTRL_MENU,          JOYBUTTON_ESCAPE ) );

    // SDL mouse event maps
    mMouseMaps.resize( mMouseMaps.size()+1, new CControlMap(CTRL_ACTION,    SDL_BUTTON_LEFT) );
}

CControls::~CControls()
{
    ClearControls();
}

void CControls::ClearControls( void )
{
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
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                if (mEnabledMouse)
                {
                    if (mMouseMaps.size()>0)
                    {
                        for (uint8_t i=0; i<mMouseMaps.size(); i++)
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
                            if (sdl_event.jbutton.button == mJoyMaps.at(i)->Button() )
                            {
                                event.Type( mJoyMaps.at(i)->Action() );
                                event.State( sdl_event.type==SDL_JOYBUTTONDOWN ? CTRL_ACTIVATED : CTRL_DEACTIVATED );
                                break;
                            }
                        }
                    }
                }
                break;
            case SDL_QUIT:
                event.Type( CTRL_QUIT );
                event.State( CTRL_ACTIVATED );
                break;
            default:
                break;
        }
	}
	return result;
}

SDLKey CControls::WaitForKeyPress( SDLKey oldkey )
{
    int8_t result;
    SDL_Event sdl_event;

    do {
        result = SDL_WaitEvent(&sdl_event);
    } while ( result != 0 && sdl_event.type != SDL_KEYDOWN );

    if (result==0)
    {
        return oldkey;
    }
    else
    {
        return sdl_event.key.keysym.sym;
    }
}

uint8_t CControls::WaitForJoyPress( uint8_t oldbutton )
{
    int8_t result;
    SDL_Event sdl_event;

    do {
        result = SDL_WaitEvent(&sdl_event);
    } while ( result != 0 && sdl_event.type != SDL_JOYBUTTONDOWN );

    if (result==0)
    {
        return oldbutton;
    }
    else
    {
        return sdl_event.jbutton.button;
    }
}

SDLKey CControls::GetKeyMapping( uint8_t internalevent )
{
    if (mKeyMaps.size()>0)
    {
        for (uint8_t i=0; i<mKeyMaps.size(); i++)
        {
            if (internalevent == mKeyMaps.at(i)->Action())
            {
                return mKeyMaps.at(i)->Sym();
            }
        }
    }
    return SDLK_UNKNOWN;
}

uint16_t CControls::GetJoyMapping( uint8_t internalevent )
{
    if (mJoyMaps.size()>0)
    {
        for (uint8_t i=0; i<mJoyMaps.size(); i++)
        {
            if (internalevent == mJoyMaps.at(i)->Action())
            {
                return mJoyMaps.at(i)->Button();
            }
        }
    }
    return 0;
}

int8_t CControls::SetKeyMapping( uint8_t internalevent, SDLKey newkey )
{
    if (mKeyMaps.size()>0)
    {
        for (uint8_t i=0; i<mKeyMaps.size(); i++)
        {
            if (internalevent == mKeyMaps.at(i)->Action())
            {
                mKeyMaps.at(i)->Sym(newkey);
                return i;
            }
        }
    }
    return SIG_FAIL;
}

int8_t CControls::SetJoyMapping( uint8_t internalevent, uint8_t newbutton )
{
    if (mJoyMaps.size()>0)
    {
        for (uint8_t i=0; i<mJoyMaps.size(); i++)
        {
            if (internalevent == mJoyMaps.at(i)->Action())
            {
                mJoyMaps.at(i)->Button(newbutton);
                return i;
            }
        }
    }
    return SIG_FAIL;
}

