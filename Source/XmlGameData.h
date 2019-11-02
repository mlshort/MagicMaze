/**
 *  @file       XmlGameData.h
 *  @brief      Raw Game data structures used by the Xml Parser
 *  @author     Mark L. Short
 *  @date       February 1, 2017
 */

#pragma once

#if !defined(__XMLGAME_DATA_H__)
#define __XMLGAME_DATA_H__

#ifndef __COMMON_H__
    #include "Common.h"
#endif

#ifndef _VECTOR_
    #include <vector>
#endif

 /**
    @brief primitive structure containing raw Neighbor data
 */
struct NEIGHBOR_DATA
{
    int          m_iTransitionKey;
    tstring      m_strTarget;

    /// default constructor
    NEIGHBOR_DATA( void ) noexcept
        : m_iTransitionKey(),
          m_strTarget()
    { };

    /// Copy constructor
    NEIGHBOR_DATA( const NEIGHBOR_DATA& othr ) noexcept
        : m_iTransitionKey( othr.m_iTransitionKey ),
          m_strTarget       ( othr.m_strTarget )
    { };

    NEIGHBOR_DATA( int iTrans, const tstring& strTarget ) noexcept
        : m_iTransitionKey(iTrans),
          m_strTarget(strTarget)
    { };

    /// Assignment operator
    NEIGHBOR_DATA& operator=(const NEIGHBOR_DATA& rhs)
    {
        if (this != &rhs)
        {
            m_iTransitionKey = rhs.m_iTransitionKey;
            m_strTarget        = rhs.m_strTarget;
        }
        return *this;
    };
};


/**
    @brief primitive structure containing raw Room data
*/
struct ROOM_DATA
{
    int                         m_iCondition;
    tstring                     m_strType;
    tstring                     m_strName;
    tstring                     m_strDescription;
    std::vector<NEIGHBOR_DATA>  m_rgNeighborData;


    /// default constructor
    ROOM_DATA(void) noexcept
        : m_iCondition(),
          m_strType(),
          m_strName(),
          m_strDescription(),
          m_rgNeighborData()
    { };

    /// copy constructor
    ROOM_DATA( const ROOM_DATA& othr ) noexcept
        : m_iCondition    ( othr.m_iCondition ),
          m_strType       ( othr.m_strType ),
          m_strName       ( othr.m_strName ),
          m_strDescription( othr.m_strDescription ),
          m_rgNeighborData( othr.m_rgNeighborData )
    { };

    /// assignment operator
    ROOM_DATA& operator=(const ROOM_DATA& rhs )
    {
        if (this != &rhs)
        {
            m_iCondition     = rhs.m_iCondition;
            m_strType        = rhs.m_strType;
            m_strName        = rhs.m_strName;
            m_strDescription = rhs.m_strDescription;
            m_rgNeighborData = rhs.m_rgNeighborData;
        }
        return *this;
    };
};

/**
    @brief primitive structure containing raw Puzzle data
*/
struct PUZZLE_DATA
{
    std::vector<ROOM_DATA>    m_rgRoomData;

    /// default constructor
    PUZZLE_DATA(void) noexcept
        : m_rgRoomData()
    { };
};

#endif