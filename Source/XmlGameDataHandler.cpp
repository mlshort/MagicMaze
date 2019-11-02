/**
 * @file       XmlGameDataHandler.cpp
 * @brief      CXmlGameDataHandler class implementation
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

#include "XmlGameDataHandler.h"

#define GET_XML_ATTRIB_STR(_Test, _Loc, _attrib, _value) if ( _tcsicmp( _Test, _attrib )==0 ) { _Loc = _value; }
#define GET_XML_ATTRIB_INT(_Test, _Loc, _attrib, _value) if ( _tcsicmp( _Test, _attrib )==0 ) { _Loc = _ttoi( _value ); }
#define GET_XML_ATTRIB_CHAR(_Test, _Loc, _attrib, _value) if ( _tcsicmp( _Test, _attrib )==0 ) { _Loc = _value[0]; }


void CXmlGameDataHandler::OnElementInit(const TCHAR* pszName)
{
    if ( _tcsicmp( _T( "Room" ), pszName ) == 0 )
    {
        ROOM_DATA room;

        m_rgRoomData.push_back( room );
        pRoom = &m_rgRoomData.back();
        pNeighbor = nullptr;
    }
    else if ( _tcsicmp( _T( "Neighbor" ), pszName ) == 0 )
    {
        if ( pRoom )
        {
            NEIGHBOR_DATA neighbor;
            pRoom->m_rgNeighborData.push_back( neighbor );
            pNeighbor = &pRoom->m_rgNeighborData.back();
        }
    }
};

void CXmlGameDataHandler::OnAttribute(const TCHAR* pszName, const TCHAR* pszValue)
{
    if (pRoom)
    {
        GET_XML_ATTRIB_STR( _T( "Description" ), pRoom->m_strDescription, pszName, pszValue )
        GET_XML_ATTRIB_STR( _T( "Type" ), pRoom->m_strType, pszName, pszValue )
        GET_XML_ATTRIB_STR( _T( "Name" ), pRoom->m_strName, pszName, pszValue )
        GET_XML_ATTRIB_INT( _T( "Condition" ), pRoom->m_iCondition, pszName, pszValue )
    }

    if (pNeighbor)
    {
        GET_XML_ATTRIB_STR( _T( "Target" ), pNeighbor->m_strTarget, pszName, pszValue )
        GET_XML_ATTRIB_CHAR( _T( "Transition" ), pNeighbor->m_iTransitionKey, pszName, pszValue )
    }
};