#ifndef __NIO_STREAM__H__
#define __NIO_STREAM__H__
#if _MSC_VER > 1000
#pragma once
#endif

class CLIBMISC_IMP CNioStream
{
public:
	CNioStream();
	virtual~CNioStream();
	BOOL Init(DWORD cbDeviceBlock,DWORD cbMemCacheMax,LPCSTR pszCacheFile);
	VOID Lock();
	VOID Unlock();
	BOOL Flush() { return TryWriteMoreToDevice(TRUE); }
	BOOL Write(LPBYTE pData,DWORD cbData);
	BOOL WhenDeviceIdle() { return TryWriteMoreToDevice(FALSE); }
protected:
	virtual CLock* GetDeviceLock() PURE;
	virtual BOOL IsDeviceBusy() PURE;
	virtual BOOL WriteToDevice(UINT64 nOffset,LPBYTE pData,DWORD cbData,DWORD& cbWrote) PURE;
protected:
	DWORD GetNumInMemCache() { return (m_cbMemCacheMax+1+m_cbMemCacheTail-m_cbMemCacheHead)%(m_cbMemCacheMax+1); }
	DWORD GetNumInDiskCache() { return (DWORD)((m_cbDiskCacheTail-m_cbDiskCacheHead<ULONG_MAX)?(m_cbDiskCacheTail-m_cbDiskCacheHead):ULONG_MAX); }
	BOOL TryWriteMoreToDevice(BOOL bForce);
	BOOL TryReadMoreFromDiskCache();
protected:
	DWORD m_cbDeviceBlock;
	DWORD m_cbMemCacheMax;
	TCHAR m_szCacheFile[MAX_PATH];
	UINT64 m_cbTotal;
	UINT64 m_cbOffset;
	LPBYTE m_pMemCache;
	DWORD m_cbMemCacheTail;
	DWORD m_cbMemCacheHead;
	FILE* m_pfnDiskCache;
	UINT64 m_cbDiskCacheTail;
	UINT64 m_cbDiskCacheHead;
	BOOL m_bUpdateLocked;
};

#endif
