/**
 * @file       NormalRoom.cpp
 * @brief      CNormalRoom class implementation
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
#include "Console.h"
#include "RoomMap.h"
#include "NormalRoom.h"

#include <iomanip>


using std::setw;
using std::setiosflags;
using std::resetiosflags;
using std::ios;


CRoom* CNormalRoom::Execute( CRoomMap* pRoomMap, int& iHealth )
{
    if (pRoomMap)
    {
        iHealth--;

        tcout << std::setiosflags(std::ios::left)
            << std::setfill<TCHAR>(' ') << setw(20);

        tcout << _T("View:") << std::endl;

        OutputConsoleFillChar('-');
        OutputConsoleText(GetDescription().c_str());
        OutputConsoleFillChar('-');


        tcout << setw(20);
        tcout << _T("Health:") << setw(20)
            << iHealth << std::endl << std::endl;
        tcout << setw(20);
        tcout << _T("Available Moves:");
        for (const auto& it : GetNeighbors())
        {
            tcout << static_cast<TCHAR>(it.first) << _T(" ");
        }
        tcout << std::endl << std::endl;

        tcout << _T("Select a Move:");

        tcin >> this->m_strTransition;

        return pRoomMap->FindNextRoom(this);
    }
    else
    {
        return nullptr;
    }
};
