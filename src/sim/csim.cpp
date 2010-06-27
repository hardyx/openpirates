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

#include "csim.h"

CSim::CSim( CResources& resources ) :
    mResources      (resources),
    mStrings        (mResources.Data().Strings()),
    mCalander       (mResources.Data().Months()),
    mCurrentDate    (),
    mLoops          (0)
{
}

CSim::~CSim()
{
}

void CSim::Simulate( void )
{
    mLoops++;

    if (mLoops>=SIMLOOPS_PER_DAY)
    {
        mCalander.AdvanceDate( mCurrentDate, 1 );

        WorldEvents();

        mLoops = 0;
    }
}

void CSim::WorldEvents ( void )
{
    vec_string_t variables;
    CDyntown* town;
    CTown* towndata;
    std::string strDate;
    uint8_t nation1, nation2;
    uint16_t index, soldiers, population;
    uint32_t gold, food, cannon, gooda, goodb;

    strDate = mCalander.DateToString(mCurrentDate);

    // Town events
    if (getProbability(EVENT_PROB_TOWN))
    {
        index       = getRandomValue( 0, mResources.Data().TownsDyn().Size()-1 );
        town        = mResources.Data().TownsDyn().At(index);
        towndata    = mResources.Data().Towns().Find(town->DataTag());
        soldiers    = town->Soldiers();
        population  = town->Population();
        gold        = town->Cargo().Gold().Count();
        food        = town->Cargo().Food().Count();
        cannon      = town->Cargo().Cannon().Count();
        gooda       = town->Cargo().GoodTypeA().Count();
        goodb       = town->Cargo().GoodTypeB().Count();

        variables.clear();
        variables.resize( variables.size()+1, &towndata->Name() );

        // Indians Attack (lower soldiers)
        if (getProbability(EVENT_PROB_INDIANS))
        {
            town->Soldiers(soldiers-(soldiers/DIV_INDIANS_SOLDIERS));
            StoreEvent( strDate,
                        mStrings.Find( STR_EVENT_INDIANS )->Text(),
                        variables );
        }
        // Pirates Attack (lower econ/soldiers)
        else if (getProbability(EVENT_PROB_PIRATES))
        {
            town->Soldiers(soldiers-(soldiers/DIV_PIRATES_SOLDIERS));
            town->Cargo().Gold().Count( gold-(gold/DIV_PIRATES_GOODS) );
            town->Cargo().Food().Count( food-(gold/DIV_PIRATES_GOODS) );
            town->Cargo().Cannon().Count( cannon-(gold/DIV_PIRATES_GOODS) );
            town->Cargo().GoodTypeA().Count( gooda-(gold/DIV_PIRATES_GOODS) );
            town->Cargo().GoodTypeB().Count( goodb-(gold/DIV_PIRATES_GOODS) );
            StoreEvent( strDate,
                        mStrings.Find( STR_EVENT_PIRATES )->Text(),
                        variables );
        }
        // Gold Mine (higher gold)
        else if (getProbability(EVENT_PROB_GOLDMINE))
        {
            town->Cargo().Gold().Count( gold+(gold/DIV_GOLDMINE) );
            StoreEvent( strDate,
                        mStrings.Find( STR_EVENT_GOLDMINE )->Text(),
                        variables );
        }
        // New Governor
        else if (getProbability(EVENT_PROB_NEWGOV))
        {
            town->Soldiers(soldiers-(soldiers/DIV_PIRATES_SOLDIERS));
            town->Population(population-(population/DIV_PIRATES_SOLDIERS));
            StoreEvent( strDate,
                        mStrings.Find( STR_EVENT_GOLDMINE )->Text(),
                        variables );
        }
        // Malaria
        else if (getProbability(EVENT_PROB_NEWGOV))
        {
            StoreEvent( strDate,
                        mStrings.Find( STR_EVENT_NEWGOV )->Text(),
                        variables );
        }
    }

    // Nation events
    if (getProbability(EVENT_PROB_NATION))
    {
        // Select a random nation's
        nation1 = getRandomValue( 0, mResources.Data().Nations().Size()-1 );
        nation2 = getRandomValue( 0, mResources.Data().Nations().Size()-1 );
        if ((nation1 == nation2) && (nation2 < mResources.Data().Nations().Size()))
        {
            nation2++;
        }
        else
        {
            nation2 = 0;
        }

        variables.clear();
        variables.resize( variables.size()+1, &mResources.Data().Nations().At(nation1)->Name() );
        variables.resize( variables.size()+1, &mResources.Data().Nations().At(nation2)->Name() );

        // War
        if (getProbability(EVENT_PROB_WAR))
        {
            mResources.Data().Nations().At(nation1)->Relations().at(nation2) = NATION_WAR;
            StoreEvent( strDate,
                        mStrings.Find( STR_EVENT_WAR )->Text(),
                        variables );
        }
        // Peace
        if ( mResources.Data().Nations().At(nation1)->Relations().at(nation2) == NATION_WAR)
        {
            if (getProbability(EVENT_PROB_PEACE))
            {
                mResources.Data().Nations().At(nation1)->Relations().at(nation2) = NATION_PEACE;
                StoreEvent( strDate,
                            mStrings.Find( STR_EVENT_PEACE )->Text(),
                            variables );
            }

            // Amnesty
            if (getProbability(EVENT_PROB_AMNESTY))
            {
                mResources.Data().Nations().At(nation1)->Amnesty(true);
                variables.clear();
                variables.resize( variables.size()+1, &mResources.Data().Nations().At(nation1)->Name() );
                StoreEvent( strDate,
                            mStrings.Find( STR_EVENT_AMNESTY )->Text(),
                            variables );
            }
            else if (getProbability(EVENT_PROB_AMNESTY))
            {
                mResources.Data().Nations().At(nation2)->Amnesty(true);
                variables.clear();
                variables.resize( variables.size()+1, &mResources.Data().Nations().At(nation2)->Name() );
                StoreEvent( strDate,
                            mStrings.Find( STR_EVENT_AMNESTY )->Text(),
                            variables );
            }
            else
            {
                mResources.Data().Nations().At(nation1)->Amnesty(false);
                mResources.Data().Nations().At(nation2)->Amnesty(false);
            }
        }
        // Alliance
        if ( mResources.Data().Nations().At(nation1)->Relations().at(nation2) == NATION_PEACE)
        {
            if (getProbability(EVENT_PROB_ALLIANCE))
            {
                mResources.Data().Nations().At(nation1)->Relations().at(nation2) = NATION_ALLIED;
                StoreEvent( strDate,
                            mStrings.Find( STR_EVENT_ALLIANCE )->Text(),
                            variables );
            }
        }

        // Capture City
        if ( mResources.Data().Nations().At(nation1)->Relations().at(nation2) == NATION_WAR)
        {
            if (getProbability(EVENT_PROB_CAPCITY))
            {
                    // TODO
            }
        }
    }

    // Player events
        // ShipSpotted
        // AddStorm?

}

void CSim::StoreEvent( const std::string& date, const std::string& event, vec_string_t& variables )
{
    std::string text;

    text = date + " " + event;
    ProcessText( variables, text );
    mResources.Data().Events().AddEntry( text );
}

void CSim::ProcessText( vec_string_t& variables, std::string& text )
{
    uint8_t index;
    std::string::iterator text_iterator;

    index = 0;
    for ( text_iterator = text.begin(); text_iterator < text.end(); text_iterator++ )
    {
        if (*text_iterator=='%')
        {
            if (index <= variables.size()-1)
            {
                text.replace( text_iterator, text_iterator+1, *variables.at(index) );
                text_iterator += variables.at(index)->size();
            }
        }
    }
}
