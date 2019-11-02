/**
 * @file       Room.h
 * @brief      Header file for CRoom class
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
 * <b> Objective :</b>
 */
#pragma once

#if !defined(__ROOM_H__)
#define __ROOM_H__

#ifndef __COMMON_H__
    #include "Common.h"
#endif

#ifndef _MAP_
    #include <map>
#endif

#ifndef __DEFINITIONS_H__
    #include "definitions.h"
#endif


 /////////////////////////////////////////////////////////////////////////
 // forward declarations
class CRoomMap;


class CRoom
{
public:
    typedef typename std::map< int, tstring >   neighbors;

protected:
    ROOM_TYPE      m_rmType;
/**
    This enum type stores the Room's role in end-of-game.
*/
    CONDITION_TYPE m_cndType;
/**
    This string stores the player's requested action, which is usually a single character
    but could be stored as a more complex system.
 */
    tstring        m_strTransition;
/**
    This string stores the unique name of the Room within the game space
*/
    tstring        m_strIdentifier;
/**
    This string should describe the Room in a way meaningful in the context of the game
 */
    tstring        m_strDescription;
/**
    This maps a transition keyword onto a particular room identifier. In theory this member
    implements the transition function( the current Room is the state, s, the key is the transition,
    a, and the paired value is the next - state, s
*/
    neighbors      m_mapNeighbors;

public:
    /// Default Constructor
    CRoom( void ) noexcept
        : m_rmType( RM_INVALID ),
          m_cndType( CND_INVALID ),
          m_strTransition(),
          m_strIdentifier(),
          m_strDescription(),
          m_mapNeighbors()
    { };

    /// Initialization Constructor
    explicit CRoom( ROOM_TYPE type ) noexcept
        : m_rmType( type ),
          m_cndType( CND_INVALID ),
          m_strTransition(),
          m_strIdentifier(),
          m_strDescription(),
          m_mapNeighbors()
    { };

    explicit CRoom( ROOM_TYPE type, CONDITION_TYPE cnd, const tstring& strId, const tstring& strDesc )
        : m_rmType( type ),
          m_cndType( cnd ),
          m_strTransition(),
          m_strIdentifier( strId ),
          m_strDescription( strDesc ),
          m_mapNeighbors()
    { };

    /// Copy Constructor
    CRoom( const CRoom& othr )
        : m_rmType         ( othr.m_rmType ),
          m_cndType        ( othr.m_cndType ),
          m_strTransition  ( othr.m_strTransition ),
          m_strIdentifier  ( othr.m_strIdentifier ),
          m_strDescription ( othr.m_strDescription ),
          m_mapNeighbors   ( othr.m_mapNeighbors )
    { };

    /// Default Destructor
    virtual ~CRoom() = default;

    /// assignment operator
    CRoom& operator= (const CRoom& rhs)
    {
        if (this != &rhs)
        {
            m_rmType         = rhs.m_rmType;
            m_cndType        = rhs.m_cndType;
            m_strTransition  = rhs.m_strTransition;
            m_strIdentifier  = rhs.m_strIdentifier;
            m_strDescription = rhs.m_strDescription;
            m_mapNeighbors   = rhs.m_mapNeighbors;
        }
        return *this;
    }

    void                Initialize ( CONDITION_TYPE cnd, tstring strID, tstring strDesc );


    bool                IsFinished ( void ) const noexcept;

 /**
    @brief Returns the ID of the next room

    This methods finds and returns the next Room identifier associated with the
    current Room and the current transition. The next Room identifier is found by
    invoking the neighbors member's find method

    @param [out]        strID        reference to string location to be used
                                     to return the ID

    @retval true         if strID successfully retrieved and is valid
    @retval false        if unable to find ID and strID is not set on return
 */
    bool                          GetNextRoomID   ( tstring& strID ) const;

    // virtual methods
    virtual CRoom*                Execute         ( CRoomMap*, int& iHealth ) = 0;

    // Accessor methods
    constexpr const tstring&      GetIdentifier   ( void ) const noexcept
    { return m_strIdentifier; };

    void                          SetIdentifier   ( const tstring& strIdent )
    { m_strIdentifier = strIdent; };

    constexpr CONDITION_TYPE      GetConditionType( void ) const
    { return m_cndType; };

    constexpr ROOM_TYPE           GetRoomType     ( void ) const
    { return m_rmType; };


    constexpr const tstring&      GetDescription  ( void ) const
    { return m_strDescription; };

    void                          SetDescription  ( const tstring& strDesc )
    { m_strDescription = strDesc; };

    constexpr const neighbors&    GetNeighbors    ( void ) const
    { return m_mapNeighbors; };

    neighbors&                    GetNeighbors    ( void ) noexcept
    { return m_mapNeighbors; };

    bool                          AddNeighbor     ( int iTransKey, const tstring& strValue );

    void                          ClearNeighbors  ( void ) noexcept
    { m_mapNeighbors.clear(); };



};

#endif