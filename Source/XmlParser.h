/**
 *  @file       XmlParser.h
 *  @brief
 *  @author     Mark L. Short
 *  @date       December 3, 2016
 *
 *  <b>Cite:</b>
 *              fixed & enhanced sample by originally by Bjarke Viksoe
 *  @sa https://www.viksoe.dk/code
 */

#pragma once

#if !defined(__XMLPARSER_H__)
#define __XMLPARSER_H__

#ifndef __COMMON_H__
    #include "Common.h"
#endif

#ifndef _VECTOR_
    #include <vector>
#endif

 /////////////////////////////////////////////////////////////////////////
 // forward declarations

struct IXmlReader;
struct IStream;


class  CXmlParser;

struct ATTRIBUTE
{
    std::wstring m_strName;
    std::wstring m_strValue;

    ATTRIBUTE() noexcept
        : m_strName(),
          m_strValue()
    { };

    explicit ATTRIBUTE( const wchar_t* szName )
        : m_strName( szName ),
          m_strValue()
    { };

    explicit ATTRIBUTE( const wchar_t* szName, const wchar_t* szValue )
        : m_strName( szName ),
          m_strValue( szValue)
    { };

    ATTRIBUTE( const ATTRIBUTE& othr )
        : m_strName( othr.m_strName ),
          m_strValue( othr.m_strValue )
    { };

    ATTRIBUTE& operator=( const ATTRIBUTE& rhs )
    {
        if ( this != &rhs )
        {
            m_strName.assign(rhs.m_strName);
            m_strValue.assign(rhs.m_strValue);
        }
        return *this;
    };

    bool operator==(const ATTRIBUTE& rhs) const noexcept
    { return ((m_strName.compare(rhs.m_strName) == 0) &&
              (m_strValue.compare(rhs.m_strValue) == 0)); };
};

/**
    @brief abstract base class
*/
class IXmlElementHandler
{
public:
   virtual void OnParseInit    (CXmlParser* /*pParser*/) = 0;
   virtual void OnStartElement (const TCHAR* /*pszName*/, const std::vector<ATTRIBUTE>& /*ppszAttribs*/) = 0;
   virtual void OnEndElement   (const TCHAR* /*pszName*/) = 0;
   virtual void OnCharacterData(const TCHAR* /*pszName*/, const TCHAR* /*pszValue*/, int /*cchValue*/) = 0;
   virtual void OnElementInit  (const TCHAR* /*pszName*/) = 0;
   virtual void OnAttribute    (const TCHAR* /*pszName*/, const TCHAR* /*pszValue*/) = 0;
};


/**
    @brief XML Parser wrapper
*/
class CXmlParser
{
   IXmlReader*         m_pIXmlReader;
   IXmlElementHandler* m_pHandler;

public:
    /// default constructor
   constexpr CXmlParser(void) noexcept
       : m_pIXmlReader(nullptr),
         m_pHandler(nullptr)
   { };


   /// default destructor
   ~CXmlParser(void);

   void ClearHandler(void) noexcept
   { m_pHandler = nullptr; };

   bool Create      (void);
   void Destroy     (void) noexcept;
   void SetHandler  (IXmlElementHandler* pHandler);


   bool Parse       (IStream* pInputStream);
};


/////////////////////////////////////////////////////////////////////////
// XML attribute map macros

#define BEGIN_XML_PARSE_MAP() tstring* _pData; CXmlParser* _pParser; \
   virtual void OnStartElement(const TCHAR* szElement, const std::vector<ATTRIBUTE>& rgAttr) { _pData = nullptr;

// #define BEGIN_XML_ELEMENT(_name) if ( _tcscmp( _name, szElement)==0 ) for ( const TCHAR** _it = rgAttr; *_it; _it += 2 ) {
#define BEGIN_XML_ELEMENT(_ele) if ( _tcscmp( _ele, szElement)==0 ) for ( auto _it = rgAttr.begin(); _it != rgAttr.end(); ++_it ) {

#define XML_ELEMENT_TEST(_ele, _expr) if ( _tcscmp( _ele, szElement)==0 ) { _expr; };

#define XML_ATTRIB_INIT(_expr) if ( _it == rgAttr.begin() ) { _expr; };

#define XML_ATTRIB_STR(_attrib, _value) if ( _tcscmp( _attrib, _it->m_strName.c_str() )==0 ) { _value = _it->m_strValue; };

#define XML_ATTRIB_SZ(_attrib, _value) if ( _tcscmp( _attrib, _it->m_strName.c_str() )==0 ) { _tcsncpy(_value, _it->m_strValue.c_str(), (_countof(_value)-1) ); _value[_countof(_value)-1] = '\0'; };

#define XML_ATTRIB_INT(_attrib, _value) if ( _tcscmp( _attrib, _it->m_strName.c_str() )==0 ) { _value = _ttoi( _it->m_strValue.c_str() ); };

#define XML_ATTRIB_DBL(_attrib, _value) if ( _tcscmp( _attrib, _it->m_strName.c_str() )==0 ) { _value = (double)_ttof( _it->m_strValue.c_str() ); };

#define XML_ATTRIB_BOOL(_attrib, _value) if ( _tcscmp( _attrib, _it->m_strName.c_str() )==0 ) { _value = _it->m_strValue.c_str()[0] == 't' || **(_it+1)=='T'; };

#define XML_ATTRIB_TEST(_attrib, _value, _expr) if ( _tcscmp( _attrib, _it.m_strName.c_str() )==0 && _tcscmp(_value, _it->m_strValue.c_str() )==0 ) { _expr; };

#define XML_TEXT_STR(_name, _value) if ( _tcscmp( _name, szElement)==0 ) { _pData = &(_value); };

#define XML_IF(_test) if ( _test ) {

#define XML_ENDIF() }

#define XML_CHANGE_HANDLER(_handler) _pParser.SetHandler(_handler);

#define END_XML_ELEMENT() }

#define END_XML_PARSE_MAP() }; \
   virtual void OnCharacterData(const TCHAR* szName, const TCHAR* szValue, int cch) { if ( _pData != nullptr ) (*_pData) += tstring(szValue, (size_t)cch); }; \
   virtual void OnEndElement(const TCHAR* /*pszName*/) noexcept { _pData = nullptr; }; \
   virtual void OnParseInit(CXmlParser* pParser) noexcept { _pData = nullptr; _pParser = pParser; };

#define XML_DEFINE_TEMP(_temp) _temp;


#endif
