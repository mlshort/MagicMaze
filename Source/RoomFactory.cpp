
/**
 * @file       RoomFactory.cpp
 * @brief      CRoomFactory class implementation
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

#include "NormalRoom.h"
#include "MagicRoom.h"

#include "RoomFactory.h"

CRoomFactory::~CRoomFactory()
{
    for ( auto& it : m_mmRooms )
    {
        delete it.second;
    }
};

CRoom* CRoomFactory::Create(ROOM_TYPE rmType)
{
    CRoom* pReturn = nullptr;

    switch (rmType)
    {
        case RM_NORMAL:
            pReturn = new CNormalRoom();
            break;
        case RM_MAGIC:
            pReturn = new CMagicRoom();
            break;
        case RM_INVALID:
        default:
            break;
    }

    if (pReturn)
        m_mmRooms.insert(std::make_pair(rmType, pReturn) );

    return pReturn;
};



