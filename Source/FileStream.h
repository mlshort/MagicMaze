/**
 *  @file       FileStream.h
 *  @brief      CFileStream COM object definition
 *  @author     Mark L. Short
 *  @date       November 9, 2016
 *
 * <b>Cite:</b>
 *      based on SDK samples published by Microsoft
 */

#pragma once

#include "ObjIdl.h"


/**
    @brief IStream class implementation

    Will be needed for XML File Parsing
*/
class CFileStream : public IStream
{
    HANDLE m_hFile;
    LONG   m_refCount;

/// Initialization constructor
    CFileStream(HANDLE hFile)
        : IStream(),
          m_hFile (hFile),
          m_refCount(1)
    { };

/// Default Destructor
    virtual ~CFileStream();


public:
    HRESULT static OpenFile(const TCHAR* pName, IStream** ppIStream, bool fWrite);

    // IUknown Interface
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, __RPC__deref_out _Result_nullonfailure_ void __RPC_FAR *__RPC_FAR *ppvObject);
    virtual ULONG   STDMETHODCALLTYPE AddRef(void);
    virtual ULONG   STDMETHODCALLTYPE Release(void);

    // ISequentialStream Interface
    virtual HRESULT STDMETHODCALLTYPE Read(_Out_writes_bytes_to_(cb, *pcbRead) void* pv, _In_ ULONG cb, _Out_opt_ ULONG* pcbRead);
    virtual HRESULT STDMETHODCALLTYPE Write(_In_reads_bytes_(cb) const void* pv, _In_ ULONG cb, _Out_opt_ ULONG* pcbWritten);

    // IStream Interface
    virtual HRESULT STDMETHODCALLTYPE SetSize(ULARGE_INTEGER);
    virtual HRESULT STDMETHODCALLTYPE CopyTo(_In_ IStream*, ULARGE_INTEGER, _Out_opt_ ULARGE_INTEGER*, _Out_opt_ ULARGE_INTEGER*);
    virtual HRESULT STDMETHODCALLTYPE Commit(DWORD);
    virtual HRESULT STDMETHODCALLTYPE Revert(void);
    virtual HRESULT STDMETHODCALLTYPE LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
    virtual HRESULT STDMETHODCALLTYPE UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
    virtual HRESULT STDMETHODCALLTYPE Clone(__RPC__deref_out_opt IStream **);
    virtual HRESULT STDMETHODCALLTYPE Seek(LARGE_INTEGER liDistanceToMove, DWORD dwOrigin, _Out_opt_ ULARGE_INTEGER* lpNewFilePointer);
    virtual HRESULT STDMETHODCALLTYPE Stat(__RPC__out STATSTG* pStatstg, DWORD);

};
