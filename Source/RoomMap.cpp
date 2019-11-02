/**
 * @file       RoomMap.cpp
 * @brief      CRoomMap class implementation
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


#include <iostream>
#include <algorithm>
#include <random>
#include <set>

#include "XmlGameData.h"
#include "Room.h"
#include "RoomMap.h"


ROOM_TYPE StringToRoomType( const TCHAR* szType )
{
    ROOM_TYPE tReturn = RM_INVALID;

    if ( _tcscmp( szType, _T("Normal") ) == 0 )
        tReturn = RM_NORMAL;
    else if ( _tcscmp ( szType, _T("Magic") ) == 0 )
        tReturn = RM_MAGIC;

    return tReturn;
};

CRoomMap::~CRoomMap()
{
};

bool CRoomMap::Initialize( const PUZZLE_DATA& data )
{
    bool bReturn = false;

    for ( auto& it : data.m_rgRoomData )
    {

        ROOM_TYPE rmType = StringToRoomType( it.m_strType.c_str() );

        if ( IsValid( rmType ) )
        {
            CRoom* pRoom = m_RoomFactory.Create( rmType );

            if ( pRoom )
            {
                pRoom->Initialize ( (CONDITION_TYPE)it.m_iCondition, it.m_strName, it.m_strDescription );

                for ( auto& it2 : it.m_rgNeighborData )
                {
                    pRoom->AddNeighbor( it2.m_iTransitionKey, it2.m_strTarget );
                }
                //Add the initialized object to the game space
                m_mapRooms[pRoom->GetIdentifier()] = pRoom;

                bReturn = true;
            }

        }
    }

    return bReturn;
}


CRoom* CRoomMap::FindNextRoom( const CRoom* pRoom )
{
    CRoom* pNextRoom = nullptr;
    std::map<tstring, CRoom*>::iterator miter;

    //If room is a valid pointer, search for its next
    //Otherwise, search for the starting room
    if ( pRoom != nullptr )
    {
        tstring strID;
        if ( pRoom->GetNextRoomID( strID ) )
            miter = m_mapRooms.find( strID );
        else
            miter = m_mapRooms.end();
    }
    else
    {
        miter = m_mapRooms.find( _T("start") );
    }

    //Check validity of search
    if ( miter != m_mapRooms.end() )
    {
        pNextRoom = miter->second;
    }

    return pNextRoom;
}

void CRoomMap::ClearAllNeighbors(void)
{
    //Clear all neighbors
    for ( auto& room : m_mapRooms )
    {
        room.second->ClearNeighbors();
    }
};


void CRoomMap::RandomizeRooms(void)
{
    static std::random_device                 rDev;
    static std::default_random_engine         e( rDev() );
    static std::uniform_int_distribution<int> ud( 0, m_mapRooms.size() * 2 );

    ClearAllNeighbors();

    //Iterate through.
    for ( auto& itRoom : m_mapRooms )
    {
        //skip the "quit" room
        if ( itRoom.second->GetIdentifier() != _T("quit") )
        {
            //get the neighbors for the current room.
            auto& neighbors = itRoom.second->GetNeighbors();
            //always have the quit option.
            neighbors['q'] = _T( "quit" );
            //keep doing this until I have at least one neighbor
            do
            {
                //Now we need to make a list of possible neighbors.
                std::map<int, int> possibleNeighbors;

                std::set<int> setRandomNums;
                //for every direction that does not have a connection, select a random room.
                auto& itNeighbor = neighbors.find( 'a' );
                if ( itNeighbor == neighbors.end() )
                {
                    int iRNG = ud(e);
                    possibleNeighbors['a'] = iRNG;
                    setRandomNums.insert(iRNG);
                }
                itNeighbor = neighbors.find( 'w' );
                if ( itNeighbor == neighbors.end() )
                {
                    int iRNG = ud(e);
                    if ( setRandomNums.find(iRNG) == setRandomNums.end() )
                    {
                        possibleNeighbors['w'] = iRNG;
                        setRandomNums.insert(iRNG);
                    }
                }
                itNeighbor = neighbors.find( 'd' );
                if ( itNeighbor == neighbors.end() )
                {
                    int iRNG = ud(e);
                    if ( setRandomNums.find(iRNG) == setRandomNums.end() )
                    {
                        possibleNeighbors['d'] = iRNG;
                        setRandomNums.insert(iRNG);
                    }
                }
                itNeighbor = neighbors.find( 's' );
                if ( itNeighbor == neighbors.end() )
                {
                    int iRNG = ud(e);
                    if ( setRandomNums.find(iRNG) == setRandomNums.end() )
                    {
                        possibleNeighbors['s'] = iRNG;
                    }
                }
                //set up neighbor connection
                for ( auto& itPossible : possibleNeighbors )
                {
                    bool skipMe = false;

                    auto& itRoom2 = m_mapRooms.begin();
                    //only a connection if the possible neighbor number is a room number
                    if ( static_cast<size_t>(itPossible.second) < m_mapRooms.size() )
                    {
                        //advance the iterator to the room we want to connect to.
                        for ( int i = 0; i < itPossible.second; i++ )
                        {
                            itRoom2++;
                        }
                        //make sure I am not connecting to myself or to the "quit" room
                        if ( itRoom2->second->GetIdentifier() == _T("quit") ||
                             itRoom2->second->GetIdentifier() == itRoom.second->GetIdentifier() )
                        {
                            skipMe = true;
                        }
                        //connect the rooms.
                        if ( skipMe == false )
                        {
                            auto& neighbors2 = itRoom2->second->GetNeighbors();
                            if ( itPossible.first == 'a' )
                            {
                                //make sure there isn't a neighbor already using this wall.
                                if ( neighbors2.find( 'd' ) == neighbors2.end() )
                                {
                                    if (itRoom2->second->AddNeighbor( 'd', itRoom.second->GetIdentifier() ) )
                                        itRoom.second->AddNeighbor( 'a', itRoom2->second->GetIdentifier() );
                                }
                            }
                            if ( itPossible.first == 'd' )
                            {
                                if ( neighbors2.find( 'a' ) == neighbors2.end() )
                                {
                                    if (itRoom2->second->AddNeighbor( 'a', itRoom.second->GetIdentifier() ) )
                                        itRoom.second->AddNeighbor( 'd', itRoom2->second->GetIdentifier() );
                                }
                            }
                            if ( itPossible.first == 's' )
                            {
                                if ( neighbors2.find( 'w' ) == neighbors2.end() )
                                {
                                    if (itRoom2->second->AddNeighbor( 'w', itRoom.second->GetIdentifier() ))
                                        itRoom.second->AddNeighbor( 's', itRoom2->second->GetIdentifier() );
                                }
                            }
                            if ( itPossible.first == 'w' )
                            {
                                if ( neighbors2.find( 's' ) == neighbors2.end() )
                                {
                                    if (itRoom2->second->AddNeighbor( 's', itRoom.second->GetIdentifier() ))
                                        itRoom.second->AddNeighbor( 'w', itRoom2->second->GetIdentifier() );
                                }
                            }
                        }
                    }
                }
            }
            while ( neighbors.size() < 2 );
        }
    }
}
