/**
 * @file       NormalRoom.h
 * @brief      Header file for CNormalRoom class
 * @author     Mark L. Short
 * @date       February 12, 2017
 *
 *
 * <b>Course:</b>       CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor:</b> Sean Orme
 *
 * <b>Assignment:</b> Magic Maze
 *
 * <b>Objective:</b>
 */
#pragma once

#if !defined(__NORMAL_ROOM_H__)
#define __NORMAL_ROOM_H__

#if !defined(__ROOM_H__)
    #include "Room.h"
#endif

 /////////////////////////////////////////////////////////////////////////
 // forward declarations
class CRoomFactory;

class CNormalRoom :
    public CRoom
{
protected:
    /// Default Constructor
    CNormalRoom (void) noexcept
        : CRoom ( RM_NORMAL )
    { };

public:
    /// Copy Constructor
    CNormalRoom( const CNormalRoom& othr )
        : CRoom ( othr )
    { };

    /// Default Destructor
    virtual ~CNormalRoom() = default;

    // virtual methods
    CRoom* Execute( CRoomMap*, int& iHealth ) override;

    friend CRoomFactory;
};

#endif

