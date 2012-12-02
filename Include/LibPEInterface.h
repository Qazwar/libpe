#pragma once

#include "LibPEBase.h"
#include "LibPETrait.h"

LIBPE_NAMESPACE_BEGIN

#define LIBPE_CALLTYPE      __stdcall

class ILibPEInterface
{
public:
    virtual uint32_t LIBPE_CALLTYPE AddRef() = 0;
    virtual uint32_t LIBPE_CALLTYPE Release() = 0;
};

#define LIBPE_METHOD_(ret_type, f)      virtual ret_type LIBPE_CALLTYPE f
#define LIBPE_METHOD(f)                 LIBPE_METHOD_(error_t, f)

template <class T> class IPEFileT;
template <class T> class IPEBodyPartT;
template <class T> class IPESectionT;
template <class T> class IPEDataDirectoryT;
template <class T> class IPEDataDirectoryItemT;
template <class T> class IPEExportTableT;
template <class T> class IPEExportTableItemT;
template <class T> class IPEImportTableT;
template <class T> class IPEImportTableItemT;
template <class T> class IPEResourceTableT;
template <class T> class IPEResourceTableItemT;
template <class T> class IPEExceptionTableT;
template <class T> class IPECertificateTableT;
template <class T> class IPERelocationTableT;
template <class T> class IPEDebugInfoTableT;
template <class T> class IPEGlobalRegisterT;
template <class T> class IPETlsTableT;
template <class T> class IPEBoundImportTableT;
template <class T> class IPEImportAddressTableT;
template <class T> class IPEDelayImportTableT;
template <class T> class IPECLRHeaderT;

template <class T>
class IPEFileT : public ILibPEInterface
{
public:
    // Rebuild
    virtual error_t LIBPE_CALLTYPE Rebuild(const file_char_t *pFilePath) = 0;

    // Basic info
    virtual bool_t LIBPE_CALLTYPE Is32BitFile() = 0;
    virtual PEDosHeaderT<T> * LIBPE_CALLTYPE GetDosHeader() = 0;
    virtual PENtHeadersT<T> * LIBPE_CALLTYPE GetNtHeaders() = 0;
    virtual PEFileHeaderT<T> * LIBPE_CALLTYPE GetFileHeader() = 0;
    virtual PEOptionalHeaderT<T> * LIBPE_CALLTYPE GetOptionalHeader() = 0;

    // Section
    virtual int32_t LIBPE_CALLTYPE GetSectionNum() = 0;
    virtual error_t LIBPE_CALLTYPE GetSection(int32_t nIndex, IPESectionT<T> **ppSection) = 0;

    // PEAddress<T> convert tools
    virtual PEAddressT<T> LIBPE_CALLTYPE GetRVAFromFOA(PEAddressT<T> nFOA) = 0;
    virtual PEAddressT<T> LIBPE_CALLTYPE GetVAFromFOA(PEAddressT<T> nFOA) = 0;
    virtual PEAddressT<T> LIBPE_CALLTYPE GetFOAFromRVA(PEAddressT<T> nRVA) = 0;
    virtual PEAddressT<T> LIBPE_CALLTYPE GetFOAFromVA(PEAddressT<T> nVA) = 0;

    // Data directory & Data Directory Entries
    virtual error_t LIBPE_CALLTYPE GetDataDirectory(int32_t nIndex, IPEDataDirectoryT<T> **ppDataDirectory) = 0;
    virtual error_t LIBPE_CALLTYPE GetExportTable(IPEExportTableT<T> **ppExportTable) = 0;
    virtual error_t LIBPE_CALLTYPE GetImportTable(IPEImportTableT<T> **ppImportTable) = 0;
    virtual error_t LIBPE_CALLTYPE GetResourceTable(IPEResourceTableT<T> **ppResourceTable) = 0;
    virtual error_t LIBPE_CALLTYPE GetExceptionTable(IPEExceptionTableT<T> **ppExceptionTable) = 0;
    virtual error_t LIBPE_CALLTYPE GetCertificateTable(IPECertificateTableT<T> **ppCertificateTable) = 0;
    virtual error_t LIBPE_CALLTYPE GetRelocationTable(IPERelocationTableT<T> **ppRelocationTable) = 0;
    virtual error_t LIBPE_CALLTYPE GetDebugInfoTable(IPEDebugInfoTableT<T> **ppDebugInfoTable) = 0;
    virtual error_t LIBPE_CALLTYPE GetGlobalRegister(IPEGlobalRegisterT<T> **ppGlobalRegister) = 0;
    virtual error_t LIBPE_CALLTYPE GetTlsTable(IPETlsTableT<T> **ppTlsTable) = 0;
    virtual error_t LIBPE_CALLTYPE GetBoundImportTable(IPEBoundImportTableT<T> **ppBoundImportTable) = 0;
    virtual error_t LIBPE_CALLTYPE GetImportAddressTable(IPEImportAddressTableT<T> **ppImportAddressTable) = 0;
    virtual error_t LIBPE_CALLTYPE GetDelayImportTable(IPEDelayImportTableT<T> **ppDelayImportTable) = 0;
    virtual error_t LIBPE_CALLTYPE GetCLRHeader(IPECLRHeaderT<T> **ppCLRHeader) = 0;

    // PE Verification
    virtual bool_t LIBPE_CALLTYPE IsValidPE() = 0;
};

template <class T>
class IPEBodyPartT : ILibPEInterface
{
public:
    virtual PEAddressT<T> LIBPE_CALLTYPE GetFOA() = 0;
    virtual PEAddressT<T> LIBPE_CALLTYPE GetRVA() = 0;
    virtual PEAddressT<T> LIBPE_CALLTYPE GetVA() = 0;
    virtual PEAddressT<T> LIBPE_CALLTYPE GetSizeInFile() = 0;
    virtual PEAddressT<T> LIBPE_CALLTYPE GetSizeInMemory() = 0;
    virtual HRESULT LIBPE_CALLTYPE DumpElement(uint8_t *pData, PEAddressT<T> nMaxDataSize) = 0;
};

template <class T>
class IPESectionT : IPEBodyPartT<T>
{
public:
    virtual HRESULT LIBPE_CALLTYPE GetName(char *pName, int32_t nMaxSize) = 0;
    virtual HRESULT LIBPE_CALLTYPE SetName(const char *pName) = 0;
};

template <class T>
class IPEDataDirectoryT : IPEBodyPartT<T>
{
public:
    virtual HRESULT LIBPE_CALLTYPE AddItem(int32_t nItemId, IPEDataDirectoryItemT<T> *pItem) = 0;
    virtual HRESULT LIBPE_CALLTYPE RemoveItem(int32_t nItemId) = 0;
    virtual HRESULT LIBPE_CALLTYPE GetItem(int32_t nItemId, IPEDataDirectoryItemT<T> **ppItem) = 0;
};

template <class T>
class IPEExportTableT : IPEBodyPartT<T>
{
public:
    virtual HRESULT LIBPE_CALLTYPE AddOrUpdateItem() = 0;
    virtual HRESULT LIBPE_CALLTYPE RemoveItem() = 0;
    virtual HRESULT LIBPE_CALLTYPE GetItem() = 0;

    virtual uint32_t LIBPE_CALLTYPE GetItemCount() = 0;
    virtual HRESULT LIBPE_CALLTYPE GetItemByIndex(int32_t nIndex) = 0;
};

template <class T>
class IPEExportTableItemT : IPEBodyPartT<T> {};

template <class T>
class IPEImportTableT : IPEBodyPartT<T>
{
public:
    virtual HRESULT LIBPE_CALLTYPE AddOrUpdateItem() = 0;
    virtual HRESULT LIBPE_CALLTYPE RemoveItem() = 0;
    virtual HRESULT LIBPE_CALLTYPE GetItem() = 0;

    virtual uint32_t LIBPE_CALLTYPE GetItemCount() = 0;
    virtual HRESULT LIBPE_CALLTYPE GetItemByIndex(int32_t nIndex) = 0;
};

template <class T>
class IPEImportTableItemT : IPEBodyPartT<T> {};

template <class T>
class IPEResourceTableT : IPEBodyPartT<T>
{
public:
    virtual HRESULT LIBPE_CALLTYPE AddItem(IPEResourceTableItemT<T> *pItem) = 0;
    virtual HRESULT LIBPE_CALLTYPE RemoveItem(int32_t nIndex) = 0;
    virtual HRESULT LIBPE_CALLTYPE GetItem(int32_t nIndex, IPEResourceTableItemT<T> **ppItem) = 0;
    virtual HRESULT LIBPE_CALLTYPE GetItemCount() = 0;
};

template <class T>
class IPEResourceTableItemT : IPEBodyPartT<T> {};

template <class T>
class IPEExceptionTableT : IPEBodyPartT<T> {};

template <class T>
class IPECertificateTableT : IPEBodyPartT<T> {};

template <class T>
class IPERelocationTableT : IPEBodyPartT<T> {};

template <class T>
class IPEDebugInfoTableT : IPEBodyPartT<T> {};

template <class T>
class IPEGlobalRegisterT : IPEBodyPartT<T> {};

template <class T>
class IPETlsTableT : IPEBodyPartT<T> {};

template <class T>
class IPEBoundImportTableT : IPEBodyPartT<T> {};

template <class T>
class IPEImportAddressTableT : IPEBodyPartT<T> {};

template <class T>
class IPEDelayImportTableT : IPEBodyPartT<T> {};

template <class T>
class IPECLRHeaderT : IPEBodyPartT<T> {};

LIBPE_NAMESPACE_END