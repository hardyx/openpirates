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

#ifndef CMANAGER_H
#define CMANAGER_H

#include "global.h"

template <class T>
class CManager
{
    public:
        CManager( void ) :
            mName("unknown"),
            mObjects()
        {
        }

        CManager( const std::string& name ) :
            mName(name),
            mObjects()
        {
        }

        virtual ~CManager()
        {
            Log( "CManager(%s) %d objects to release", mName.c_str(), mObjects.size() );
            if ( mObjects.size() > 0 )
            {
                for ( int16_t i=mObjects.size()-1; i>=0; i-- )
                {
                    delete mObjects.at(i);
                    Log( " %d", i );
                }
                mObjects.clear();
            }
            Log( " ...Done.\n" );
        }

        void Add( T* object, bool verbose = true )
        {
            // Assign a tag
            object->Tag(mObjects.size()+1);
            // Save the object
            mObjects.resize( mObjects.size()+1, object );
            if ( verbose == true )
            {
                Log( "\nCManager(%s)::Add Loaded item %d", mName.c_str(), mObjects.size() );
            }
            else
            {
                Log( " %d", mObjects.size() );
            }
        }

		T* Find( uint16_t tag )
		{
            for ( uint16_t i=0; i<mObjects.size(); i++ )
            {
                if ( mObjects.at(i)->Tag() == tag )
                {
                    return mObjects.at(i);
                }
            }
            return NULL;
		}

		T* At( uint16_t index )
		{
		    return mObjects.at(index);
		}

		uint16_t Size( void )
		{
            return mObjects.size();
		}

		T* Back( void )
		{
		    return mObjects.back();
		}

		void Clear( void )
		{
            mObjects.clear();
		}

    private:
        std::string     mName;
        std::vector<T*> mObjects;
};

#endif // CMANAGER_H
