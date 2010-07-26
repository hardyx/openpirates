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

#ifndef CEVENTLOG_H
#define CEVENTLOG_H

#include "global.h"

/** @brief Contains and provides a circluar list of ingame events.
 */
class CEventLog
{
    public:
        #define MAX_LOG_ENTRIES 30        /** Limit of number of entries. */

        /** Constructor. */
        CEventLog();
        /** Destructor. */
        virtual ~CEventLog();

        /**
         *  @brief Clears the queue of entries.
         */
        void Clear( void );

        /**
         *  @brief Adds an entry to the queue.
         *  @param newentry : string entry to add
         */
        void AddEntry( const std::string& newentry );

    private:
        std::queue<std::string> mEntries;   /** The queue of entries. */
};

#endif // CEVENTLOG_H
