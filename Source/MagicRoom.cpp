/**
 * @file       MagicRoom.cpp
 * @brief      CMagicRoom class implementation
 * @author     Mark L. Short
 * @date       February 12, 2017
 *
 *
 * <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor:</b> Sean Orme
 *
 * <b>Assignment:</b> Magic Maze
 *
 * <b> Objective:</b>
 */

#include "Common.h"

#include <iomanip>
#include "RoomMap.h"
#include "Console.h"

#include "MagicRoom.h"


using std::setw;

constexpr const TCHAR g_szMagicRoomDesc[] = _T("You hear loud grinding sounds and you feel your strength restored!");

CMagicRoom::~CMagicRoom()
{
}


CRoom* CMagicRoom::Execute( CRoomMap* pRoomMap, int& iHealth )
{
    iHealth += 2;
    pRoomMap->RandomizeRooms();

    tcout << std::setiosflags( std::ios::left )
          << std::setfill<TCHAR>( ' ' ) << setw( 20 );

    tcout << _T( "View:" ) << std::endl;

    OutputConsoleFillChar( '-' );
    OutputConsoleText( g_szMagicRoomDesc );
    OutputConsoleFillChar( '-' );

    tcout << setw( 20 );
    tcout << _T( "Health:" ) << setw( 20 )
          << iHealth << std::endl << std::endl;
    tcout << setw( 20 );
    tcout << _T( "Available Moves:" );
    for ( const auto& it : GetNeighbors() )
    {
        tcout << static_cast<TCHAR>( it.first ) << _T( " " );
    }
    tcout << std::endl << std::endl;

    tcout << _T( "Select a Move:" );

    tcin  >> this->m_strTransition;

    return pRoomMap->FindNextRoom( this );
};
