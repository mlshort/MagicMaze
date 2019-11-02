/**
 *  @file       XmlGraphDataHandler.h
 *  @brief      XML data mapping class for the XML Parser
 *  @author     Mark L. Short
 *  @date       December 2, 2016
 *
 *  @sa https://www.viksoe.dk/code
 */

#pragma once

#if !defined(__XMLGAME_DATAHANDLER_H__)
#define __XMLGAME_DATAHANDLER_H__


#ifndef __XMLGAME_DATA_H__
    #include "XmlGameData.h"
#endif
#ifndef __XMLPARSER_H__
    #include "XmlParser.h"
#endif


/**
    @brief provides basic XML data-mapping functionality
*/
class CXmlGameDataHandler
    : public PUZZLE_DATA,
      public IXmlElementHandler
{
public:

    /// default constructor
    CXmlGameDataHandler(void) noexcept
        : PUZZLE_DATA(),
          IXmlElementHandler()
    {};

    virtual ~CXmlGameDataHandler()
    {};


    XML_DEFINE_TEMP(ROOM_DATA* pRoom)
    XML_DEFINE_TEMP(NEIGHBOR_DATA* pNeighbor)

    BEGIN_XML_PARSE_MAP()
        BEGIN_XML_ELEMENT(_T("Puzzle"))
        END_XML_ELEMENT()
        BEGIN_XML_ELEMENT(_T("Room"))
            XML_ATTRIB_INIT(ROOM_DATA room; m_rgRoomData.push_back(room); pRoom = &m_rgRoomData.back(); )
            XML_ATTRIB_STR(_T("type"), pRoom->m_strType)
            XML_ATTRIB_INT(_T("condition"), pRoom->m_iCondition)
            XML_ATTRIB_STR(_T("name"), pRoom->m_strName)
            XML_ATTRIB_STR(_T("description"), pRoom->m_strDescription)
        END_XML_ELEMENT()
        BEGIN_XML_ELEMENT(_T("Neighbor"))
            XML_ATTRIB_INIT(NEIGHBOR_DATA neighbor; pRoom->m_rgNeighborData.push_back(neighbor); pNeighbor = &pRoom->m_rgNeighborData.back(); )
            XML_ATTRIB_INT(_T("transition"), pNeighbor->m_iTransitionKey)
            XML_ATTRIB_STR(_T("target"), pNeighbor->m_strTarget)
        END_XML_ELEMENT()
    END_XML_PARSE_MAP()
    
    void OnAttribute(const TCHAR* pszName, const TCHAR* pszValue) override;
    void OnElementInit(const TCHAR* pszName) override;
};


#endif