/**
 *  @file       FileStream.cpp
 *  @brief      CFileStream COM object implementation
 *  @author     Mark L. Short
 *  @date       November 9, 2016
 *
 * <b>Cite:</b>
 *      based on SDK samples published by Microsoft
 */

#include "FileStream.h"



CFileStream::~CFileStream()
{
    if (m_hFile != INVALID_HANDLE_VALUE)
    {
        ::CloseHandle(m_hFile);
    }
}


HRESULT CFileStream::OpenFile(const TCHAR* pName, IStream** ppIStream, bool fWrite)
{
    if (ppIStream == nullptr)
        return E_POINTER;

    HANDLE hFile = ::CreateFile(pName, fWrite ? GENERIC_WRITE : GENERIC_READ, FILE_SHARE_READ,
                                 nullptr, fWrite ? CREATE_ALWAYS : OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
        return HRESULT_FROM_WIN32(GetLastError());

    *ppIStream = new CFileStream(hFile);

    if (*ppIStream == nullptr)
        ::CloseHandle(hFile);

    return S_OK;
}

HRESULT STDMETHODCALLTYPE CFileStream::QueryInterface(REFIID iid, __RPC__deref_out _Result_nullonfailure_ void __RPC_FAR *__RPC_FAR *ppvObject)
{
    if (!ppvObject)
        return E_INVALIDARG;
    ( *ppvObject ) = nullptr;

    if (iid == __uuidof( IUnknown )
        || iid == __uuidof( IStream )
        || iid == __uuidof( ISequentialStream ))
    {
        *ppvObject = static_cast<IStream*>( this );
        AddRef();
        return S_OK;
    }
    else
        return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CFileStream::AddRef(void)
{
    return static_cast<ULONG>(::InterlockedIncrement(&m_refCount));
}

ULONG STDMETHODCALLTYPE CFileStream::Release(void)
{
    ULONG res = static_cast<ULONG>(::InterlockedDecrement(&m_refCount));
    if (res == 0)
        delete this;
    return res;
}

HRESULT STDMETHODCALLTYPE CFileStream::Read(_Out_writes_bytes_to_(cb, *pcbRead) void* pv, _In_ ULONG cb, _Out_opt_ ULONG* pcbRead)
{
    BOOL bResult = ::ReadFile(m_hFile, pv, cb, pcbRead, nullptr);
    return  bResult ? S_OK : HRESULT_FROM_WIN32(GetLastError());
}

HRESULT STDMETHODCALLTYPE CFileStream::Write(_In_reads_bytes_(cb) const void* pv, _In_ ULONG cb, _Out_opt_ ULONG* pcbWritten)
{
    BOOL bResult = ::WriteFile(m_hFile, pv, cb, pcbWritten, nullptr);
    return bResult ? S_OK : HRESULT_FROM_WIN32(GetLastError());
}

// IStream Interface
HRESULT STDMETHODCALLTYPE CFileStream::SetSize(ULARGE_INTEGER)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CFileStream::CopyTo(_In_ IStream*, ULARGE_INTEGER, _Out_opt_ ULARGE_INTEGER*, _Out_opt_ ULARGE_INTEGER*)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CFileStream::Commit(DWORD)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CFileStream::Revert(void)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CFileStream::LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CFileStream::UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CFileStream::Clone(__RPC__deref_out_opt IStream **)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CFileStream::Seek(LARGE_INTEGER liDistanceToMove, DWORD dwOrigin, _Out_opt_ ULARGE_INTEGER* pNewFilePointer)
{

    DWORD dwMoveMethod;

    switch (dwOrigin)
    {
        case STREAM_SEEK_SET:
            dwMoveMethod = FILE_BEGIN;
            break;
        case STREAM_SEEK_CUR:
            dwMoveMethod = FILE_CURRENT;
            break;
        case STREAM_SEEK_END:
            dwMoveMethod = FILE_END;
            break;
        default:
            return STG_E_INVALIDFUNCTION;
            break;
    }

    if (::SetFilePointerEx(m_hFile, liDistanceToMove, (PLARGE_INTEGER) pNewFilePointer,
                           dwMoveMethod) == FALSE)
        return HRESULT_FROM_WIN32(GetLastError());
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CFileStream::Stat(__RPC__out STATSTG* pStatstg, DWORD)
{
    if (pStatstg == nullptr)
        return E_POINTER;

    if (::GetFileSizeEx(m_hFile, (PLARGE_INTEGER) &pStatstg->cbSize) == FALSE)
        return HRESULT_FROM_WIN32(GetLastError());
    return S_OK;
}
