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

#ifndef CMANAGER_H
#define CMANAGER_H

#include "global.h"

/** @brief A wrapper for managing the vector of objects T
 */
template <class T>
class CManager
{
    public:
        /** Constructor with no name. */
        CManager( void ) :
            mName("unknown"),
            mObjects()
        {
        }

        /** @brief Constructor with name.
         * @param name : name of the collection
         */
        CManager( const std::string& name ) :
            mName(name),
            mObjects()
        {
        }

        /** Destructor. */
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

        /** @brief Add an object to the collection
         * @param object : pointer to the object
         * @param verbose : if true enable log output
         */
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

        /** @brief Find an object by tag in the collection
         * @param tag : the unique numeric tag assigned
         * @return : pointer to the object
         */
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

        /** @brief Retreieve an object by index in the collection
         * @param index : vector index
         * @return : pointer to the object
         */
		T* At( uint16_t index )
		{
		    return mObjects.at(index);
		}

        /** @brief Get the size of the collection vector
         * @return : integer size
         */
		uint16_t Size( void )
		{
            return mObjects.size();
		}

        /** @brief Retreieve the last added object in the collection
         * @return : pointer to the object
         */
		T* Back( void )
		{
		    return mObjects.back();
		}

        /** @brief Clear out the collection
         * @note the manager is not responible for freeing the objects.
         */
		void Clear( void )
		{
            mObjects.clear();
		}

    private:
        std::string     mName;       /** The name of the collection. */
        std::vector<T*> mObjects;    /** The collection vector of the objects. */
};

#endif // CMANAGER_H
