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

#ifndef COPTIONS_H
#define COPTIONS_H

#include "global.h"
#include "resources/cini.h"

class CScreenOptions
{
    public:
        CScreenOptions() :
            mWidth  (0),
            mHeight (0),
            mBpp    (0)
        {
        }
        virtual ~CScreenOptions() {}

        // Getters
        uint16_t Width( void )      { return mWidth; }
        uint16_t Height( void )     { return mHeight; }
        uint8_t Bpp( void )         { return mBpp; }
        // Setters
        void Width( uint16_t v )    { mWidth = v; }
        void Height( uint16_t v )   { mHeight = v; }
        void Bpp( uint8_t v )       { mBpp = v; }

    private:
        uint16_t    mWidth;
        uint16_t    mHeight;
        uint8_t     mBpp;
};

class CSoundOptions
{
    public:
        CSoundOptions() :
            mChannels   (0),
            mFrequency  (0),
            mSampleSize (0)
        {
        }
        virtual ~CSoundOptions() {}

        // Getters
        uint8_t Channels( void )        { return mChannels; }
        uint16_t Frequency( void )      { return mFrequency; }
        uint16_t SampleSize( void )     { return mSampleSize; }
        // Setters
        void Channels( uint8_t v )      { mChannels = v; }
        void Frequency( uint16_t v )    { mFrequency = v; }
        void SampleSize( uint16_t v )   { mSampleSize = v; }

    private:
        uint8_t     mChannels;
        uint16_t    mFrequency;
        uint16_t    mSampleSize;
};

class CFontOptions
{
    public:
        CFontOptions() :
            mSize   (0),
            mColor  (),
            mPath   ()
        {
        }
        virtual ~CFontOptions() {}

        // Getters
        uint8_t             Size( void )    { return mSize; }
        SDL_Color*          Color( void )   { return &mColor; }
        const std::string&  Path( void )    { return mPath; }
        // Setters
        void Size( uint8_t v )              { mSize = v; }
        void Color( SDL_Color v )           { mColor = v; }
        void Path( const std::string& v )   { mPath = v; }

    private:
        uint8_t     mSize;
        SDL_Color   mColor;
        std::string mPath;
};

class CWaveOptions
{
    public:
        CWaveOptions() :
            mCount  (0),
            mSpeed  (0)
        {
        }
        virtual ~CWaveOptions() {}

        // Getters
        uint8_t Count( void )       { return mCount; }
        uint8_t Speed( void )       { return mSpeed; }
        // Setters
        void Count( uint8_t count ) { mCount = count; }
        void Speed( uint8_t speed ) { mSpeed = speed; }

    private:
        uint8_t mCount;
        uint8_t mSpeed;
};

class CCloudOptions
{
    public:
        CCloudOptions() :
            mCount(0)
        {
        }
        virtual ~CCloudOptions() {}

        // Getters
        uint8_t Count( void )       { return mCount; }
        // Setters
        void Count( uint8_t count ) { mCount = count; }

    private:
        uint8_t mCount;
};

class CMapOptions
{
    public:
        CMapOptions() :
            mWidth  (0),
            mHeight (0)
        {
        }
        virtual ~CMapOptions() {}

        // Getters
        uint16_t Width( void )          { return mWidth; }
        uint16_t Height( void )         { return mHeight; }
        // Setters
        void Width( uint16_t width )    { mWidth = width; }
        void Height( uint16_t height )  { mHeight = height; }

    private:
        uint16_t    mWidth;
        uint16_t    mHeight;
};

class COptions : public CIni
{
    public:
        COptions();
        virtual ~COptions();

        // Getters
        CScreenOptions&     Screen( void )  { return mScreen; }
        CSoundOptions&      Sound( void )   { return mSound; }
        CFontOptions&       Font( void )    { return mFont; }
        CWaveOptions&       Wave( void )    { return mWave; }
        CCloudOptions&      Cloud( void )   { return mCloud; }
        CMapOptions&        Map( void )     { return mMap; }

        int8_t Load( const std::string& file_path );

    private:
        CScreenOptions  mScreen;
        CSoundOptions   mSound;
        CFontOptions    mFont;
        CWaveOptions    mWave;
        CCloudOptions   mCloud;
        CMapOptions     mMap;
};

#endif // COPTIONS_H
