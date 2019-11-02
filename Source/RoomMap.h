/**
 *  @file       RoomMap.h
 *  @brief      Header file for CRoomMap class
 *  @author     Mark L. Short
 *  @date       February 12, 2017
 *
 *
 *  <b>Course:</b>       CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor :</b>  Sean Orme
 *
 *  <b>Assignment :</b>  Magic Maze
 *
 *  <b> Objective :</b>
 */
#pragma once

#if !defined(__ROOM_MAP_H__)
#define __ROOM_MAP_H__

#ifndef __COMMON_H__
    #include "Common.h"
#endif

#ifndef _MAP_
    #include <map>
#endif

#ifndef __ROOM_FACTORY_H__
    #include "RoomFactory.h"
#endif


 /////////////////////////////////////////////////////////////////////////
 // forward declarations
struct PUZZLE_DATA;
class  CRoom;

class CRoomMap
{
    CRoomFactory                       m_RoomFactory;
    std::map<tstring, CRoom*>          m_mapRooms;

public:
    /// Default Constructor
    CRoomMap(void) noexcept
        : m_RoomFactory(),
          m_mapRooms()
    { };

    /// Default Destructor
    ~CRoomMap();

    bool    Initialize       (const PUZZLE_DATA& data);

    CRoom*  FindNextRoom     (const CRoom* pRoom);

    void    RandomizeRooms   (void);

    void    ClearAllNeighbors(void);

/////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CRoomMap( const CRoomMap& ) = delete;
    CRoomMap& operator=( const CRoomMap& ) = delete;

};

#endif