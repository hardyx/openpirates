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

#include "ccalander.h"

CCalander::CCalander( CManager<CStringValue>& months ) :
    mMonths(months)
{
}

CCalander::~CCalander()
{
}

uint16_t CCalander::TimeDuration( CDate& before, CDate& after )
{
    uint16_t total;
    int16_t years;

    years = after.Year() - before.Year();
    if (years>=0)
    {
        total = years*DAYS_IN_YEAR;

        total += mMonths.At(before.Month()-1)->Value() - before.Day();

        for (uint8_t i=before.Month(); i<after.Month(); i++ )
        {
            total += mMonths.At(i)->Value();
        }

        total += after.Day();
    }
    else
    {
        total = 0;
    }

    return total;
}

CDate CCalander::AdvanceDate( CDate& now, uint16_t days )
{
    CDate after;

    // Advance years
    while (days>DAYS_IN_YEAR)
    {
        days -= DAYS_IN_YEAR;
        after.Year(now.Year()+1);
    }

    // Advance months
    while (days > mMonths.At(now.Month()-1)->Value())
    {
        days -= mMonths.At(now.Month()-1)->Value() - now.Day();
        after.Month(now.Month()+1);
        if (after.Month() >= mMonths.Size())
        {
            after.Month(1);
        }
        now.Day(0);
    }

    // Advance days
    after.Day(days);

    return after;
}

std::string CCalander::DateToString( CDate& date )
{
    std::string output;

    output = mMonths.At(date.Month()-1)->Text();
    output += i_to_a(date.Day()) + ", ";
    output += i_to_a(date.Year());

    return output;
}
