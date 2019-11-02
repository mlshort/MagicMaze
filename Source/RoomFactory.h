/**
 * @file       RoomFactory.h
 * @brief      Header file for CRoomFactory class
 * @author     Mark L. Short
 * @date       February 12, 2017
 *
 *
 * <b>Course:</b>       CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor : </b> Sean Orme
 *
 * <b>Assignment : </b> Magic Maze
 *
 * <b> Objective : </b>
 */
#pragma once

#if !defined(__ROOM_FACTORY_H__)
#define __ROOM_FACTORY_H__

#ifndef __DEFINITIONS_H__
    #include "definitions.h"
#endif

#ifndef _MAP_
    #include <map>
#endif

 /////////////////////////////////////////////////////////////////////////
 // forward declarations
class CRoom;

class CRoomFactory
{
    std::multimap<ROOM_TYPE, CRoom*> m_mmRooms;

public:

    /// Default Constructor
    CRoomFactory(void) noexcept
        : m_mmRooms()
    {};

    /// Default Destructor
    ~CRoomFactory();


    CRoom* Create(ROOM_TYPE rmType);

/////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CRoomFactory( const CRoomFactory& ) = delete;
    CRoomFactory& operator=( const CRoomFactory& ) = delete;

};

#endif
