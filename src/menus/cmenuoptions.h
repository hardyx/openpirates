#ifndef CMENUOPTIONS_H
#define CMENUOPTIONS_H

#include "global.h"
#include "managers/cmanagerwindow.h"

class CMenuOptions
{
    public:
        CMenuOptions( CResources& resources, CManagerWindow& winmanager );
		virtual ~CMenuOptions();

        int8_t Run( void );

    private:
        CResources&         mResources;
        CGraphic&           mScreen;
        CRole&              mPlayer;
        CManager<CString>&  mStrings;
        CManager<CGraphic>& mGraphics;
        CManagerWindow&     mManagerwindow;

        int8_t Video( void );
        int8_t ChangeResolution( int8_t current_mode );
        int8_t Sound( void );
        int8_t KeyControls( void );
        int8_t JoyControls( void );
        int8_t UseSuggestedSettings( uint8_t cur, uint8_t sug );
        int8_t PressAnyKey( void );
        int8_t PressAnyJoy( void );
        int8_t FailedSettings( void );
};

#endif // CMENUOPTIONS_H
