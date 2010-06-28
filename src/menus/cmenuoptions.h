#ifndef CMENUOPTIONS_H
#define CMENUOPTIONS_H

#include "global.h"
#include "managers/cmanagerwindow.h"

class CMenuOptions
{
    public:
        CMenuOptions( CResources& resources );
		virtual ~CMenuOptions();

        int8_t Run( void );

    private:
        CResources&         mResources;
        CGraphic&           mScreen;
        CRole&              mPlayer;
        CManager<CString>&  mStrings;
        CManager<CGraphic>& mGraphics;
        CManagerWindow      mManagerwindow;

        int8_t Video( void );
        int8_t Sound( void );
        int8_t Controls( void );
};

#endif // CMENUOPTIONS_H
