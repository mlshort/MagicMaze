/**
 * @file       Room.cpp
 * @brief      CRoom class implementation
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

#include "Room.h"


void  CRoom::Initialize( CONDITION_TYPE cnd, tstring strID, tstring strDesc )
{
    m_cndType        = cnd;
    m_strIdentifier  = strID;
    m_strDescription = strDesc;
}

/**
    This method translates the END_CONDITION enum into a boolean value( i.e., WIN, LOSE, QUIT
    translate to true and NONE translates to false ).
*/
bool CRoom::IsFinished(void) const noexcept
{
    bool bResult = false;

    switch (m_cndType)
    {
        case CND_WIN:
        case CND_LOSE:
        case CND_QUIT:
            bResult = true;
            break;
    }

    return bResult;
};

/**
    This methods finds and returns the next Room identifier associated with the current Room and
    the current transition. The next Room identifier is found by invoking the neighbors member’s
    find method
*/
bool CRoom::GetNextRoomID(tstring& strID) const
{
    bool bResult = false;

    if ( m_strDescription.empty() == false )
    {
        int iTransKey = m_strTransition.c_str()[0];
        auto it = m_mapNeighbors.find( iTransKey );
        if ( it != m_mapNeighbors.end() )
        {
            strID = it->second;
            bResult = true;
        }
    }

    return bResult;
};

bool CRoom::AddNeighbor( int iTransKey, const tstring& strValue )
{
    auto& it = m_mapNeighbors.insert(std::make_pair(iTransKey, strValue));
    return it.second;
};