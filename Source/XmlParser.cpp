/**
 *  @file       XmlParser.cpp
 *  @brief      CXmlParser class implementation
 *  @author     Mark L. Short
 *  @date       December 3, 2016
 *
 *  <b>Cite:</b>
 *              fixed & enhanced sample by Bjarke Viksoe
 *  @sa https://www.viksoe.dk/code
 */


#include <stack>
#include <vector>

 // include the Microsoft XmlLite library
#include <xmllite.h>
#pragma comment(lib, "xmllite.lib")


#include "XmlParser.h"


#ifndef _ASSERTE
    #define _ASSERTE(x)
#endif


CXmlParser::~CXmlParser()
{
    Destroy();
}


bool CXmlParser::Create(void)
{
    if (m_pIXmlReader != nullptr)
    {
        m_pIXmlReader->Release();
        m_pIXmlReader = nullptr;
    }

    ::CreateXmlReader(__uuidof( IXmlReader ), reinterpret_cast<LPVOID*>( &m_pIXmlReader ), 0);
    _ASSERTE(m_pIXmlReader);
    return m_pIXmlReader != nullptr;
}

void CXmlParser::Destroy()
{
    if (m_pIXmlReader != nullptr)
        m_pIXmlReader->Release();
    m_pIXmlReader = nullptr;
}

void CXmlParser::SetHandler(IXmlElementHandler * pHandler)
{
    _ASSERTE(m_pIXmlReader);
    m_pHandler = pHandler;
    pHandler->OnParseInit(this);
}


bool CXmlParser::Parse( IStream* pInputStream )
{
    _ASSERTE( m_pIXmlReader );

    HRESULT hr = m_pIXmlReader->SetInput( pInputStream );

    LPCWSTR pszName  = nullptr;
    LPCWSTR pszValue = nullptr;
    UINT  cch = 0;


    XmlNodeType NodeType = XmlNodeType_None;
    while ( m_pIXmlReader->Read( &NodeType ) == S_OK )
    {
        switch ( NodeType )
        {
            case XmlNodeType_Element:
            {
                if ( m_pHandler != nullptr )
                {
                    if ( FAILED( hr = m_pIXmlReader->GetLocalName( &pszName, nullptr ) ) )
                    {
                        _tprintf( _T( "XmlElement Error getting local name: %08.8lx \n" ), hr );
                        return false;
                    }


#ifdef _DEBUG
                    _tprintf( _T( "< %s \n" ), pszName );
#endif
                    m_pHandler->OnElementInit( pszName );


                    hr = m_pIXmlReader->MoveToFirstAttribute();

                    while ( hr == S_OK )
                    {
                        if ( !m_pIXmlReader->IsDefault() )
                        {
                            LPCWSTR pszAttribName  = nullptr;
                            LPCWSTR pszAttribValue = nullptr;

                            if ( FAILED( hr = m_pIXmlReader->GetLocalName( &pszAttribName, nullptr ) ) )
                            {
                                _tprintf( _T( "XmlAttribute Error getting local name: %08.8lx \n" ), hr );
                                return false;
                            }

                            if ( FAILED( hr = m_pIXmlReader->GetValue( &pszAttribValue, nullptr ) ) )
                            {
                                _tprintf( _T( "XmlAttribute Error getting value: %08.8lx \n" ), hr );
                                return false;
                            }

#ifdef _DEBUG
                            _tprintf( _T( "   XmlAttribute '%s' = '%s' \n" ), pszAttribName, pszAttribValue );
#endif
                            m_pHandler->OnAttribute( pszAttribName, pszAttribValue );
                        }
                        hr = m_pIXmlReader->MoveToNextAttribute();
                    }
                }
            }
            break;

            case XmlNodeType_Whitespace:
#ifdef _DEBUG
                _tprintf( _T( "XmlWhitespace \n" ) );
#endif
                break;

            case XmlNodeType_EndElement:
#ifdef _DEBUG
                _tprintf( _T( "XmlEndElement \n" ) );
#endif
                break;

            case XmlNodeType_Text:
#ifdef _DEBUG
                _tprintf( _T( "XmlText \n" ) );
#endif
                break;

            case XmlNodeType_None:
#ifdef _DEBUG
                _tprintf( _T( "XmlNone \n" ) );
#endif
                break;

            case XmlNodeType_Attribute:
#ifdef _DEBUG
                _tprintf( _T( "XmlAttribute \n" ) );
#endif
                break;

            case XmlNodeType_CDATA:
                if ( FAILED( hr = m_pIXmlReader->GetValue( &pszValue, nullptr ) ) )
                {
                    _tprintf( _T( "XmlCDATA Error getting value: %08.8lx \n" ), hr );
                    return false;
                }
#ifdef _DEBUG
                _tprintf( _T( "XmlCDATA: %s\n" ), pszValue );
#endif
                break;

            case XmlNodeType_ProcessingInstruction:
                if ( FAILED( hr = m_pIXmlReader->GetLocalName( &pszName, nullptr ) ) )
                {
                    _tprintf( _T( "Error getting name: %08.8lx \n" ), hr );
                    return false;
                }
                if ( FAILED( hr = m_pIXmlReader->GetValue( &pszValue, nullptr ) ) )
                {
                    _tprintf( _T( "Error getting value: %08.8lx \n" ), hr );
                    return false;
                }
#ifdef _DEBUG
                _tprintf( _T( "XmlProcessingInstruction Name:%s Value:%s \n" ), pszName, pszValue );
#endif
                break;

            case XmlNodeType_Comment:
                if ( FAILED( hr = m_pIXmlReader->GetValue( &pszValue, nullptr ) ) )
                {
                    _tprintf( _T( "XmlComment Error getting value: %08.8lx \n" ), hr );
                    return false;
                }
#ifdef _DEBUG
                _tprintf( _T( "<!--%s--> \n" ), pszValue );
#endif
                break;

            case XmlNodeType_DocumentType:
#ifdef _DEBUG
                _tprintf( _T( "XmlDOCTYPE is not printed \n" ) );
#endif
                break;

            case XmlNodeType_XmlDeclaration:
#ifdef _DEBUG
                _tprintf( _T( "XmlDeclaration \n" ) );
#endif
                break;

            default:
#ifdef _DEBUG
                _tprintf( _T( "Unknown Xml Node Type \n" ) );
#endif
                break;

        }
    }

    return true;
}

