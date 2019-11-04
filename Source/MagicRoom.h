/**
 * @file       MagicRoom.h
 * @brief      Header file for CMagicRoom class
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
 * <b>Objective: </b>
 */
#pragma once

#if !defined(__MAGIC_ROOM_H__)
#define __MAGIC_ROOM_H__

#ifndef __ROOM_H__
    #include "Room.h"
#endif

 /////////////////////////////////////////////////////////////////////////
 // forward declarations
class CRoomFactory;

class CMagicRoom :
    public CRoom
{
protected:
    /// Default Constructor
    CMagicRoom (void) noexcept
        : CRoom ( RM_MAGIC )
    { };

public:
    /// Copy Constructor
    CMagicRoom( const CMagicRoom& othr )
        : CRoom ( othr )
    { };

    /// Default Destructor
    virtual ~CMagicRoom() = default;

    // virtual methods
    CRoom* Execute( CRoomMap*, int& iHealth ) override;

    friend CRoomFactory;
};

#endif

