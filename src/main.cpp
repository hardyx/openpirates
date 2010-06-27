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

#include "main.h"

int main( int argc, char *argv[] )
{
    int8_t result = SIG_NONE;

    CModeMain ModeMain;

    Log( "openPirates Copyright (C) 2010  Scott Smith\n" );
    Log( "This program comes with ABSOLUTELY NO WARRANTY\n" );
    Log( "This is free software, and you are welcome to redistribute it\n" );
    Log( "under certain conditions.\n\n" );

    Log( "Starting %s\n", TITLE );
    result = ModeMain.Run( argc, argv );

    switch ( result )
    {
        case SIG_NONE:
        case SIG_QUIT:
            Log( "%s Terminated by normal request\n", TITLE );
            result = 0;
            break;
        case SIG_FAIL:
            Log( "%s Terminated by error signal (check stderr)\n", TITLE );
            result = -1;
            break;
        default:
            Log( "%s Terminated by unknown signal %d (check stderr)\n", TITLE, result );
            result = -2;
            break;
    }

    return result;
}
