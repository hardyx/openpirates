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

#ifndef CRESOURCES_H
#define CRESOURCES_H

#include "global.h"
#include "resources/cdata.h"
#include "resources/options/coptions.h"
#include "resources/types/cstring.h"
#include "resources/types/cgraphic.h"
#include "resources/types/csound.h"
#include "resources/types/cmap.h"
#include "resources/types/ceconomy.h"
#include "resources/types/cnation.h"
#include "resources/types/cnationeconomy.h"
#include "resources/types/cship.h"
#include "resources/types/cshipnation.h"
#include "resources/types/ctown.h"
#include "resources/types/ctowntimeperiod.h"
#include "resources/types/cmaplocation.h"
#include "resources/types/crole.h"

/** @brief This class contains all of the resource data needed for the application, such as (but not limited to) string, graphic, and sound data.
 */
class CResources
{
    public:
        /** @brief Defines all of the object types that can be stored as a resource.
         */
        enum types_t {
            TYPE_NUL=0, /** Undefined object. */
            TYPE_STR,   /** String object. */
            TYPE_GFX,   /** Graphic object. */
            TYPE_SND,   /** Sound object. */
            TYPE_MAP,   /** Map object. */
            TYPE_MON,   /** Month object. */
            TYPE_REP,   /** Reputation object. */
            TYPE_TIL,   /** Title object. */
            TYPE_TMP,   /** Timeperiod object. */
            TYPE_ECN,   /** Economy object. */
            TYPE_NAT,   /** Nation object. */
            TYPE_TWN,   /** Town object. */
            TYPE_ROL    /** Role object. */
        };

        /** Constructor. */
        CResources();
        /** Destructor. */
        virtual ~CResources();

        // Getters
        CGraphic&       Screen( void )          { return mScreen; }         /** Get reference to screen resource. */
        CData&          Data( void )            { return mData; }           /** Get reference to data resources. */
        COptions&       Options( void )         { return mOptions; }        /** Get reference to option resources. */
        SDL_Joystick*   Joystick( void )        { return mpJoystick; }      /** Get reference to joystick resource. */
        TTF_Font*       Font( void )            { return mpFont; }          /** Get reference to font resources. */
        // Setters
        void Joystick( SDL_Joystick* v )    { mpJoystick = v; }             /** Set reference to joystick. */
        void Font( TTF_Font* v )            { mpFont = v; }                 /** Set reference to ttf font. */
        // Functions
        /** @brief Checks if the video mode is safe to use according to SDL
         * @param width : screen pixel width
         * @param height : screen pixel height
         * @param depth : screen pixel depth (bits per pixel)
         * @param flags : screen SDL flags
         * @return value of type result_signal_t
         */
        int8_t CheckVideoMode( int16_t width, int16_t height, int8_t depth, uint32_t flags );

        /** @brief Sets the video mode through SDL with the current options.
         * @return value of type result_signal_t
         */
        int8_t SetVideoMode( void );

        /** @brief Switches between fullscreen and windows modes, depending on the current mode.
         * @return value of type result_signal_t
         */
        int8_t ToggleFullscreen( void );

        /** @brief Sets the mixer through SDL with the current options.
         * @return value of type result_signal_t
         */
        int8_t OpenAudioMixer( void );

        /** @brief Closes the mixer through SDL.
         */
        void   CloseAudioMixer( void );

        /** @brief Opens the first joystick through SDL.
         * @return value of type result_signal_t
         */
        int8_t OpenJoystick( void );

        /** @brief Closes the first joystick through SDL.
         */
        void   CloseJoystick( void );

        /** @brief Begins the process of loading all settings and data.
         * @param base_path : this is the execution path
         * @return value of type result_signal_t
         */
        int8_t LoadResources( const std::string& base_path );

        /** @brief Opens the ttf font file through SDL.
         * @param base_path : this is the execution path
         * @return value of type result_signal_t
         */
        int8_t LoadFont( const std::string& base_path );

        /** @brief Loads the data for the current role selected.
         * @return value of type result_signal_t
         */
        int8_t LoadActiveRole( void );

        /** @brief Loads and setups the data for towns that will be active in the selected timeperiod.
         * @return value of type result_signal_t
         */
        int8_t LoadActiveTowns( void );

        /** @brief Closes the ttf font through SDL.
         */
        void Free_Font( void );

    private:
        CGraphic            mScreen;            /** The screen resources object. */
        CData               mData;              /** The game data resources object. */
        COptions            mOptions;           /** The options resource object. */
        SDL_Joystick*       mpJoystick;         /** The joystick (if there is one). */
        TTF_Font*           mpFont;             /** The font object. */

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @return an reference to a object
         */
        CString*            LoadString              ( const std::string& line );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @param base_path : this is the execution path
         * @return an reference to a object
         */
        CGraphic*           LoadGraphic             ( const std::string& line, const std::string& base_path );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @param base_path : this is the execution path
         * @return an reference to a object
         */
        CSound*             LoadSound               ( const std::string& line, const std::string& base_path );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @param base_path : this is the execution path
         * @return an reference to a object
         */
        CMap*               LoadMap                 ( const std::string& line, const std::string& base_path );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @return an reference to a object
         */
        CStringValue*       LoadStringvalue         ( const std::string& line );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @return an reference to a object
         */
        CEconomy*           LoadEconomy             ( const std::string& line );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @return an reference to a object
         */
        CNation*            LoadNation              ( const std::string& line );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @return an reference to a object
         */
        CNationEconomy*     LoadNationEconomyLevel  ( const std::string& line );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @return an reference to a object
         */
        CShip*              LoadShip                ( const std::string& line );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @return an reference to a object
         */
        CShipNation*        LoadShipNation          ( const std::string& line );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @return an reference to a object
         */
        CTown*              LoadTown                ( const std::string& line );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @return an reference to a object
         */
        CTownTimePeriod*    LoadTownTimePeriod      ( const std::string& line );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @return an reference to a object
         */
        CMapLocation*       LoadTownMapLocation     ( const std::string& line );

        /** @brief Parses the line and loads an object with the with the data read.
         * @param line : the current read config line
         * @return an reference to a object
         */
        CRole*              LoadRole                ( const std::string& line );

        CResources(const CResources&);
        CResources& operator=(const CResources&);
};

#endif // CRESOURCES_H
