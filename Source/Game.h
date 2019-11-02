/**
 * @file       Game.h
 * @brief      Header file for CGame class
 * @mainpage
 * @author     Mark L. Short
 * @date       February 12, 2017
 *
 *
 * <b>Course:</b>      CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor :</b> Sean Orme
 *
 * <b>Assignment :</b> Magic Maze
 *
 * <b> Objective : </b>
 *      The purpose of this assignment is to give you experience working with tools that
 *      facilitate flexible game architecture. In this assignment you will:
 *
 *      *    construct an extensible, flexible, SUD-style/text-based game space using an
 *           inheritance hierarchy of objects that exhibit polymorphic behavior and rely
 *           extensively on templated storage containers;
 *
 *      *    construct a library of object assets using the ObjectFactory pattern; and,
 *
 *      *    utilize the TinyXML library to load, parse, and configure a game state from XML.
 */
#pragma once

#if !defined(__GAME_H__)
#define __GAME_H__

#ifndef __ROOM_MAP_H__
    #include "RoomMap.h"
#endif

class CGame
{
    int        m_iHealth;  ///< Player Health
    CRoomMap   m_RoomMap;

public:
    /// Default Constructor
    CGame (void) noexcept
        : m_iHealth(),
          m_RoomMap()
    {};

    /// Initialization Constructor
    explicit CGame( int iHealth ) noexcept
        : m_iHealth ( iHealth ),
          m_RoomMap()
    { };

    /// Default Destructor
    ~CGame() = default;


    bool           LoadConfigFile  ( const TCHAR* szConfigFile );

    bool           IsGameFinished  ( const CRoom* pRoom ) const noexcept;

    constexpr int  GetHealth       ( void ) const noexcept
    { return m_iHealth; };

    CRoom*         FindNextRoom    ( const CRoom* pRoom )
    { return m_RoomMap.FindNextRoom( pRoom ); };

    CRoom*         Execute         ( CRoom* pRoom );

/////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CGame(const CGame&) = delete;
    CGame& operator=( const CGame& ) = delete;
};

#endif
