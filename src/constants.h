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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TITLE           "openPirates"
#define FILE_OPTIONS    "options.conf"
#define FILE_RESOURCES  "data.conf"

// Function/Window Signals
// 1,2,3... is reserved to window feedback
#define SIG_NONE         0  // operation has finished with no errors
#define SIG_END         -1  // operation has requested to start over (back to start menu)
#define SIG_QUIT        -2  // operation has resulted in a request to shutdown
#define SIG_FAIL        -3  // operation has detected an error

// Event Signals
#define EVENT_NONE      0
#define EVENT_PRESSED   1
#define EVENT_RELEASED  2

// Game Control/Defaults
#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480
#define SCREEN_BPP      16
#define FRAME_LIMIT     true
#define FRAME_CALC      true
#define SOUND_FREQ      44100
#define SOUND_CHAN      2
#define SOUND_SAMPLE    4096
#define FONT_SIZE       12
#define FONTCOLOR_R     255
#define FONTCOLOR_G     255
#define FONTCOLOR_B     255
#define CLOUD_COUNT     5
#define WAVE_COUNT      40
#define WAVE_SPEED      15

// Frame Control/Defaults
#define SYNC_FRAME          3
#define FRAMES_PER_SECOND   60
#define MS_PER_SECOND       1000
#define MS_PER_FRAME        MS_PER_SECOND / FRAMES_PER_SECOND
#define MS_PER_SYNC         ((MS_PER_SECOND*SYNC_FRAME) / FRAMES_PER_SECOND)

// Generic Constants
#define TRUE  "True"
#define FALSE "False"

#define PI 3.14159265
#define XAXIS 1
#define YAXIS 2

// Animation methods for animated sprites
#define ANI_NONE    0
#define ANI_CONT    1
#define ANI_BYROW   2

// Player Control/Defaults
#define DEFAULT_NAME        "Incognito"
#define MAX_LENGTH_NAME     15
#define DEFAULT_AGE         23
#define DEFAULT_HEALTH      100
#define HEALTH_CUTOFF       10
#define GAME_MAXDIFFS       4
#define GAME_MAXSHIPS       8
#define GAME_MAXCOMMODITIES 4

// Config file identifiers
#define CFG_SCREEN_WIDTH    "*screen_width"
#define CFG_SCREEN_HEIGHT   "*screen_height"
#define CFG_SCREEN_BPP      "*screen_bpp"
#define CFG_SOUND_FREQ      "*sound_frequency"
#define CFG_SOUND_CHAN      "*sound_channels"
#define CFG_SOUND_SAMPLE    "*sound_sample"
#define CFG_FONTFILE        "*font_file"
#define CFG_FONTSIZE        "*font_size"
#define CFG_MAPFILE         "*map_file"
#define CFG_CLOUDCNT        "*cloud_count"
#define CFG_WAVECNT         "*wave_count"
#define CFG_WAVESPD         "*wave_speed"

#define CFG_STRING          "*string"
#define CFG_GRAPHIC         "*graphic"
#define CFG_SOUND           "*sound"
#define CFG_MAP             "*map"

#define CFG_MONTH           "*month"
#define CFG_REP             "*rep"
#define CFG_TITLE           "*title"
#define CFG_TIMEPERIOD      "*timeperiod"
#define CFG_ECONOMY         "*economy"
#define CFG_NATION          "*nation"
#define CFG_NEL             "|nel"
#define CFG_SHIP            "*ship"
#define CFG_SHIPNATION      "|snation"
#define CFG_TOWN            "*town"
#define CFG_TTP             "|ttp"
#define CFG_MAPLOC          "|maploc"
#define CFG_ROLE            "*role"
#define CFG_NATIONTITLE     "|nt"
#define CFG_SRTLOC          "|srtloc"

#define TILE_CAMERA_OFFSET  8  // Must be a factor of 2 ( and no smaller than 2)

enum graphics_list_t
{
    GFX_POINTER=1   ,
    GFX_BORDER      ,
    GFX_NAVTILES    ,
    GFX_NAVCREW     ,
    GFX_NAVTOWN     ,
    GFX_NAVCLOUD    ,
    GFX_NAVWAVE     ,
    GFX_NAVCOMPASS  ,
    GFX_INTOWN      ,
    GFX_CANNON      ,
    GFX_ARMY        ,
    GFX_CALVARY     ,
    GFX_FORT
};

enum strings_list_t
{
    STR_DIFF1=1         ,
    STR_DIFF2           ,
    STR_DIFF3           ,
    STR_DIFF4           ,
    STR_SKILL1          ,
    STR_SKILL2          ,
    STR_SKILL3          ,
    STR_SKILL4          ,
    STR_SKILL5          ,
    STR_SWORD1          ,
    STR_SWORD2          ,
    STR_SWORD3          ,
    STR_MORAL1          ,
    STR_MORAL2          ,
    STR_MORAL3          ,
    STR_MORAL4          ,
    STR_MORAL5          ,
    STR_MORAL6          ,
    STR_INTRO           ,
    STR_LOAD            ,
    STR_PICK_TIMEP      ,
    STR_PICK_NATION     ,
    STR_PICK_NAMEUP     ,
    STR_PICK_NAMELO     ,
    STR_PICK_DIFF       ,
    STR_PICK_SKILL      ,
    STR_PICK_NOROLE     ,
    STR_MAIN_MENU       ,
    STR_MAIN_RESTART    ,
    STR_INFORMATION     ,
    STR_INFO_PARTY      ,
    STR_INFO_PERSONAL   ,
    STR_INFO_TOWNS      ,
    STR_INFO_TOWN       ,
    STR_TOWN_ARRIVE     ,
    STR_TOWN_SEA        ,
    STR_TOWN_LAND       ,
    STR_TOWN_INSIDE     ,
    STR_TOWN_SNEAK      ,
    STR_GOV_RELATIONS   ,
    STR_GOV_PRISONER    ,
    STR_GOV_MARQUE      ,
    STR_GOV_PROMOTE     ,
    STR_GOV_LAND        ,
    STR_GOV_DAUGHTER    ,
    STR_TAV_MEN         ,
    STR_TAV_TRAVELER    ,
    STR_TAV_TREASUREMAP ,
    STR_CAR_SHIPHOLD    ,
    STR_CAR_PLUNDERGOLD ,
    STR_SHP_OPTIONS     ,
    STR_SHP_REPAIR      ,
    STR_SHP_SELL        ,
    STR_DIV_SHARES      ,
    STR_DIV_REFIT1      ,
    STR_DIV_REFIT2      ,
    STR_DIV_CHECKRETIRE ,
    STR_DIV_FORCERETIRE ,
    STR_SAILHO_SAIL     ,
    STR_SAILHO_SHIP     ,
    STR_SAILHO_COLORS   ,
    STR_SAILHO_PIRATE   ,
    STR_EVENT_INDIANS   ,
    STR_EVENT_PIRATES   ,
    STR_EVENT_GOLDMINE  ,
    STR_EVENT_NEWGOV    ,
    STR_EVENT_MALARIA   ,
    STR_EVENT_WAR       ,
    STR_EVENT_PEACE     ,
    STR_EVENT_ALLIANCE  ,
    STR_EVENT_AMNESTY   ,
    STR_EVENT_CITYLOST  ,
    STR_NOT_IMPLEMENTED
};

enum controls_list_t
{
    CTRL_UNKNOWN=0 ,
    CTRL_UP        ,
    CTRL_DOWN      ,
    CTRL_LEFT      ,
    CTRL_RIGHT     ,
    CTRL_ACTION    ,
    CTRL_MOTION    ,
    CTRL_MENU      ,
#ifdef DEBUG
    CTRL_DBG_BOXES ,
#endif
    CTRL_QUIT
};

enum diffs_list_t
{
    DIFF_APPRENTICE=0   ,
    DIFF_JOURNEYMAN     ,
    DIFF_ADVENTURER     ,
    DIFF_SWASHBUCKLER
};


#define JOYBUTTON_UP        0
#define JOYBUTTON_DOWN      1
#define JOYBUTTON_LEFT      2
#define JOYBUTTON_RIGHT     3
#define JOYBUTTON_ACTION    4
#define JOYBUTTON_ESCAPE    5


#define DAYS_IN_YEAR        365
#define SIMLOOPS_PER_DAY    120

#define ENTER_BY_SEA        0
#define ENTER_BY_LAND       1

#define PRISONER_FACTOR     100     // Factor effects ransom over time imprisioned
#define REP_PERCENT_LAND    10
#define LAND_ACRE_UNIT      50      // Number of acres given
#define TREASUREMAP_PRICE   500     // Cost for part of a map
#define CITIZENS_GOVERNOR   600     // Number of citizens needed to have a governor

#define PROB_TRAVELER       70      // Percent chance traveller is at tavern
#define PROB_TREASUREMAP    10      // Percent chance map seller is at tavern

#define PLUNDER_PATRONS     10      // Percent of plunder goes to investors
#define PLUNDER_OFFICERS    20      // Percent of plunder goes to officers and captain
#define PLUNDER_DIFF1       5       // Percent of plunder to the captain
#define PLUNDER_DIFF2       10
#define PLUNDER_DIFF3       15
#define PLUNDER_DIFF4       20

#define EVENT_PROB_TOWN         10
#define EVENT_PROB_INDIANS      10
#define DIV_INDIANS_SOLDIERS    4   // 1/4
#define EVENT_PROB_PIRATES      10
#define DIV_PIRATES_SOLDIERS    2   // 1/2
#define DIV_PIRATES_GOODS       2   // 1/2
#define EVENT_PROB_GOLDMINE     10
#define DIV_GOLDMINE            2   // 1/2
#define EVENT_PROB_NEWGOV       10

#define EVENT_PROB_NATION       1
#define EVENT_PROB_WAR          10
#define EVENT_PROB_PEACE        10
#define EVENT_PROB_ALLIANCE     10
#define EVENT_PROB_AMNESTY      50
#define EVENT_PROB_CAPCITY      5


#define PERCENTOF(P,T) (T*P)/100

#endif // CONSTANTS_H
