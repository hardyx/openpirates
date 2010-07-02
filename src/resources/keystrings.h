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

#ifndef KEYSTRINGS_H
#define KEYSTRINGS_H

#define KEYS_MAX 324
std::string keys_strings[KEYS_MAX] = {
    "Unknown_000",                  // SDLK_UNKNOWN     = 0,
    "Undefined_001","Undefined_002","Undefined_003","Undefined_004",
    "Undefined_005","Undefined_006","Undefined_007",
    "Backspace",                    // SDLK_BACKSPACE   = 8,
    "Tab",                          // SDLK_TAB         = 9,
    "Unknown_010",
    "Unknown_011",
    "Clear",                        // SDLK_CLEAR       = 12,
    "Return",                       // SDLK_RETURN      = 13,
    "Undefined_014","Undefined_015","Undefined_016","Undefined_017",
    "Undefined_018",
    "Pause",                        // SDLK_PAUSE       = 19,
    "Undefined_020","Undefined_021","Undefined_022","Undefined_023",
    "Undefined_024","Undefined_025","Undefined_026",
    "Escape",                       // SDLK_ESCAPE      = 27,
    "Undefined_028","Undefined_029","Undefined_030","Undefined_031",
    "Space",                        // SDLK_SPACE       = 32,
    "Exclaim",                      // SDLK_EXCLAIM     = 33,
    "DoubleQuote",                  // SDLK_QUOTEDBL    = 34,
    "Hash",                         // SDLK_HASH        = 35,
    "Dollar",                       // SDLK_DOLLAR      = 36,
    "Undefined_037",
    "Ampersand",                    // SDLK_AMPERSAND   = 38,
    "Quote",                        // SDLK_QUOTE       = 39,
    "LeftParen",                    // SDLK_LEFTPAREN   = 40,
    "RightParen",                   // SDLK_RIGHTPAREN  = 41,
    "Asterisk",                     // SDLK_ASTERISK    = 42,
    "Plus",                         // SDLK_PLUS        = 43,
    "Comma",                        // SDLK_COMMA       = 44,
    "Minus",                        // SDLK_MINUS       = 45,
    "Period",                       // SDLK_PERIOD      = 46,
    "Slash",                        // SDLK_SLASH       = 47,
    "Zero",                         // SDLK_0           = 48,
    "One",                          // SDLK_1           = 49,
    "Two",                          // SDLK_2           = 50,
    "Three",                        // SDLK_3           = 51,
    "Four",                         // SDLK_4           = 52,
    "Five",                         // SDLK_5           = 53,
    "Six",                          // SDLK_6           = 54,
    "Seven",                        // SDLK_7           = 55,
    "Eight",                        // SDLK_8           = 56,
    "Nine",                         // SDLK_9           = 57,
    "Colon",                        // SDLK_COLON       = 58,
    "SemiColon",                    // SDLK_SEMICOLON   = 59,
    "LessThan",                     // SDLK_LESS        = 60,
    "Equals",                       // SDLK_EQUALS      = 61,
    "Greater",                      // SDLK_GREATER     = 62,
    "Question",                     // SDLK_QUESTION    = 63,
    "At",                           // SDLK_AT          = 64,
    "A",                            //                  = 65,
    "B",                            //                  = 66,
    "C",                            //                  = 67,
    "D",                            //                  = 68,
    "E",                            //                  = 69,
    "F",                            //                  = 70,
    "G",                            //                  = 71,
    "H",                            //                  = 72,
    "I",                            //                  = 73,
    "J",                            //                  = 74,
    "K",                            //                  = 75,
    "L",                            //                  = 76,
    "M",                            //                  = 77,
    "N",                            //                  = 78,
    "O",                            //                  = 79,
    "P",                            //                  = 80,
    "Q",                            //                  = 81,
    "R",                            //                  = 82,
    "S",                            //                  = 83,
    "T",                            //                  = 84,
    "U",                            //                  = 85,
    "V",                            //                  = 86,
    "W",                            //                  = 87,
    "X",                            //                  = 88,
    "Y",                            //                  = 89,
    "Z",                            //                  = 90,
    "LeftBracket",                  // SDLK_LEFTBRACKET = 91,
    "Backslash",                    // SDLK_BACKSLASH   = 92,
    "RightBracket",                 // SDLK_RIGHTBRACKET= 93,
    "Caret",                        // SDLK_CARET       = 94,
    "Underscore",                   // SDLK_UNDERSCORE  = 95,
    "Backquote",                    // SDLK_BACKQUOTE   = 96,
    "a",                            // SDLK_a           = 97,
    "b",                            // SDLK_b           = 98,
    "c",                            // SDLK_c           = 99,
    "d",                            // SDLK_d           = 100,
    "e",                            // SDLK_e           = 101,
    "f",                            // SDLK_f           = 102,
    "g",                            // SDLK_g           = 103,
    "h",                            // SDLK_h           = 104,
    "i",                            // SDLK_i           = 105,
    "j",                            // SDLK_j           = 106,
    "k",                            // SDLK_k           = 107,
    "l",                            // SDLK_l           = 108,
    "m",                            // SDLK_m           = 109,
    "n",                            // SDLK_n           = 110,
    "o",                            // SDLK_o           = 111,
    "p",                            // SDLK_p           = 112,
    "q",                            // SDLK_q           = 113,
    "r",                            // SDLK_r           = 114,
    "s",                            // SDLK_s           = 115,
    "t",                            // SDLK_t           = 116,
    "u",                            // SDLK_u           = 117,
    "v",                            // SDLK_v           = 118,
    "w",                            // SDLK_w           = 119,
    "x",                            // SDLK_x           = 120,
    "y",                            // SDLK_y           = 121,
    "z",                            // SDLK_z           = 122
    "Undefined_123","Undefined_124","Undefined_125","Undefined_126",
    "Delete",                       // SDLK_DELETE      = 127,
    /* End of ASCII mapped keysyms */
    "Undefined_128",
    "Undefined_129",
    "Undefined_130","Undefined_131","Undefined_132","Undefined_133","Undefined_134",
    "Undefined_135","Undefined_136","Undefined_137","Undefined_138","Undefined_139",
    "Undefined_140","Undefined_141","Undefined_142","Undefined_143","Undefined_144",
    "Undefined_145","Undefined_146","Undefined_147","Undefined_148","Undefined_149",
    "Undefined_150","Undefined_151","Undefined_152","Undefined_153","Undefined_154",
    "Undefined_155","Undefined_156","Undefined_157","Undefined_158","Undefined_159",
    /* International keyboard syms */
    "World_00","World_01","World_02","World_03","World_04","World_05","World_06", // 160-166
    "World_07","World_08","World_09","World_10","World_11","World_12","World_13", // 167-173
    "World_14","World_15","World_16","World_17","World_18","World_19","World_20", // 174-180
    "World_21","World_22","World_23","World_24","World_25","World_26","World_27", // 181-187
    "World_28","World_29","World_30","World_31","World_32","World_33","World_34", // 188-194
    "World_35","World_36","World_37","World_38","World_39","World_40","World_41", // 195-201
    "World_42","World_43","World_44","World_45","World_46","World_47","World_48", // 202-208
    "World_49","World_50","World_51","World_52","World_53","World_54","World_55", // 209-215
    "World_56","World_57","World_58","World_59","World_60","World_61","World_62", // 216-222
    "World_63","World_64","World_65","World_66","World_67","World_68","World_69", // 223-229
    "World_70","World_71","World_72","World_73","World_74","World_75","World_76", // 230-236
    "World_77","World_78","World_79","World_80","World_81","World_82","World_83", // 237-243
    "World_84","World_85","World_86","World_87","World_88","World_89","World_90", // 244-250
    "World_91","World_92","World_93","World_94","World_95",                       // 152-255
    /* Numeric keypad */
    "Keypad-Zero",                  // SDLK_KP0         = 256,
    "Keypad-One",                   // SDLK_KP1         = 257,
    "Keypad-Two",                   // SDLK_KP2         = 258,
    "Keypad-Three",                 // SDLK_KP3         = 259,
    "Keypad-Four",                  // SDLK_KP4         = 260,
    "Keypad-Five",                  // SDLK_KP5         = 261,
    "Keypad-Six",                   // SDLK_KP6         = 262,
    "Keypad-Seven",                 // SDLK_KP7         = 263,
    "Keypad-Eight",                 // SDLK_KP8         = 264,
    "Keypad-Nine",                  // SDLK_KP9         = 265,
    "Keypad-Period",                // SDLK_KP_PERIOD   = 266,
    "Keypad-Divide",                // SDLK_KP_DIVIDE   = 267,
    "Keypad-Multiply",              // SDLK_KP_MULTIPLY = 268,
    "Keypad-Minus",                 // SDLK_KP_MINUS    = 269,
    "Keypad-Plus",                  // SDLK_KP_PLUS     = 270,
    "Keypad-Enter",                 // SDLK_KP_ENTER    = 271,
    "Keypad-Equals",                // SDLK_KP_EQUALS   = 272,
    /* Arrows + Home/End pad */
    "Up",                           // SDLK_UP          = 273,
    "Down",                         // SDLK_DOWN        = 274,
    "Right",                        // SDLK_RIGHT       = 275,
    "Left",                         // SDLK_LEFT        = 276,
    "Insert",                       // SDLK_INSERT      = 277,
    "Home",                         // SDLK_HOME        = 278,
    "End",                          // SDLK_END         = 279,
    "PageUp",                       // SDLK_PAGEUP      = 280,
    "PageDown",                     // SDLK_PAGEDOWN    = 281,
    /* Function keys */
    "F1",                           // SDLK_F1          = 282,
    "F2",                           // SDLK_F2          = 283,
    "F3",                           // SDLK_F3          = 284,
    "F4",                           // SDLK_F4          = 285,
    "F5",                           // SDLK_F5          = 286,
    "F6",                           // SDLK_F6          = 287,
    "F7",                           // SDLK_F7          = 288,
    "F8",                           // SDLK_F8          = 289,
    "F9",                           // SDLK_F9          = 290,
    "F10",                          // SDLK_F10         = 291,
    "F11",                          // SDLK_F11         = 292,
    "F12",                          // SDLK_F12         = 293,
    "F13",                          // SDLK_F13         = 294,
    "F14",                          // SDLK_F14         = 295,
    "F15",                          // SDLK_F15         = 296,
    "UNDEFINED_297","UNDEFINED_298","UNDEFINED_299",
    /* Key state modifier keys */
    "Numslock",                     // SDLK_NUMLOCK     = 300,
    "Capslock",                     // SDLK_CAPSLOCK    = 301,
    "ScrollLock",                   // SDLK_SCROLLOCK   = 302,
    "RightShift",                   // SDLK_RSHIFT      = 303,
    "LeftShift",                    // SDLK_LSHIFT      = 304,
    "RightCtrl",                    // SDLK_RCTRL       = 305,
    "LeftCtrl",                     // SDLK_LCTRL       = 306,
    "RightAlt",                     // SDLK_RALT        = 307,
    "LeftAlt",                      // SDLK_LALT        = 308,
    "RightMeta",                    // SDLK_RMETA       = 309,
    "LeftMeta",                     // SDLK_LMETA       = 310,
    "LeftSuper",                    // SDLK_LSUPER      = 311,        /* Left "Windows" key */
    "RightSuper",                   // SDLK_RSUPER      = 312,        /* Right "Windows" key */
    "Mode",                         // SDLK_MODE        = 313,        /* "Alt Gr" key */
    "Compose",                      // SDLK_COMPOSE     = 314,        /* Multi-key compose key */
    /* Miscellaneous function keys */
    "Help",                         // SDLK_HELP        = 315,
    "Print",                        // SDLK_PRINT       = 316,
    "SysReq",                       // SDLK_SYSREQ      = 317,
    "Break",                        // SDLK_BREAK       = 318,
    "Menu",                         // SDLK_MENU        = 319,
    "Power",                        // SDLK_POWER       = 320,        /* Power Macintosh power key */
    "Euro",                         // SDLK_EURO        = 321,        /* Some european keyboards */
    "Undo",                         // SDLK_UNDO        = 322,        /* Atari keyboard has Undo */
    /* Add any other keys here */
    "Last",                         // SDLK_LAST        = 323
};

#endif // KETSTRING_H
