/**
 * @file       Game.cpp
 * @brief      CGame class implementation
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
#include "XmlParser.h"
#include "XmlGameDataHandler.h"
#include "FileStream.h"

#include "Game.h"
#include "Room.h"

#ifndef FAILED
    #define FAILED(hr) (((HRESULT)(hr)) < 0)
#endif


bool CGame::IsGameFinished( const CRoom* pRoom ) const noexcept
{
    bool bResult = false;

    if ( (pRoom == nullptr) || pRoom->IsFinished() || m_iHealth <= 0 )
    {
        bResult = true;
    }

    return bResult;
}

bool CGame::LoadConfigFile ( const TCHAR* szXmlFile )
{
    bool bResult = false;

    if ( szXmlFile && szXmlFile[0] )
    {
        HRESULT hr;
        IStream*  pFileStream = nullptr;

        // open a read only input stream
        if ( FAILED( hr = CFileStream::OpenFile( szXmlFile, &pFileStream, false ) ) )
            return false;

        CXmlParser xmlParser;
        if ( xmlParser.Create() )
        {
            CXmlGameDataHandler dataHandler;
            xmlParser.SetHandler( &dataHandler );

            bResult = xmlParser.Parse( pFileStream );

            if ( bResult )
                return m_RoomMap.Initialize( dataHandler );
        }
    }

    return bResult;
};

CRoom* CGame::Execute( CRoom* pRoom )
{
    return pRoom ? pRoom->Execute( &m_RoomMap, m_iHealth ) : nullptr;
};