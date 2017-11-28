#ifndef __SAFE_TYVALVE__H__
#define __SAFE_TYVALVE__H__
#if _MSC_VER > 1000
#pragma once
#endif

// ��ѹ��
class CLIBMISC_IMP CSafetyValve
{
public:
	CSafetyValve(DWORD cbMsgHdr,DWORD cbMsgMax,BOOL bPoolOn);
	virtual~CSafetyValve(){ Stop(); }
	// ��������
	VOID SetCacheDir(LPCSTR pszCacheDir) { m_strCacheDir=pszCacheDir; }
	VOID SetEnqueueSpeedLimit(LONG nEnqueueSpeedLimit) { m_nEnqueueSpeedLimit=nEnqueueSpeedLimit; }
	VOID SetSubmitSpeedLimit(LONG nSubmitSpeedLimit) { m_nSubmitSpeedLimit=nSubmitSpeedLimit; }
	VOID SetPendingNumLimit(LONG nPendingNumLimit) { m_nPendingNumLimit=nPendingNumLimit; }
	VOID SetPendingSupported(BOOL bPendingSupported) { m_bPendingSupported=bPendingSupported; }
	VOID SetCacheRestore(BOOL bCacheRestore) { m_bCacheRestore=bCacheRestore; }
	VOID SetMemCacheUsing(BOOL bMemCacheUsing) { m_bMemCacheUsing=bMemCacheUsing; }
	VOID SetMemCacheSizeLimit(LONG nMemCacheSizeLimit) { m_nMemCacheSizeLimit=nMemCacheSizeLimit; }
	VOID SetExtCacheUsing(BOOL bExtCacheUsing) { m_bExtCacheUsing=bExtCacheUsing; }
	VOID SetExtCacheSizeLimit(LONG nExtCacheSizeLimit) { m_nExtCacheSizeLimit=nExtCacheSizeLimit; }
	VOID SetExtCachePerPage(DWORD dwExtCachePerPage) { m_dwExtCachePerPage=dwExtCachePerPage; }
	VOID SetResubmitBlock(LONG nResubmitBlock) { m_nResubmitBlock=nResubmitBlock; }
	// ����
	BOOL Start();
	VOID Stop();
	BOOL Enqueue(LPCBYTE pMsgHdr,LPCBYTE pBody,DWORD cbBody);
	// ��ʱ������¼���Ӧ
	VOID CheckPoint();
	VOID InformCompleted(LONG nCompletedNum);
	VOID InformDeviceIdle();
protected:
	typedef struct tagMSGINFO
	{	DWORD m_cbBody;
	} MSGINFO;
protected:
	BOOL LoadFromCacheFile(LPCSTR pszFilePath,TListPtr& lstCache);
	BOOL SaveFromCacheFile(LPCSTR pszFilePath,TListPtr& lstCache);
	VOID FreeCache(TListPtr& lstCache);
	VOID InitOrRestoreMemCache();
	VOID InitOrRestoreExtCache();
	BOOL SubmitOrEnqueue(LPCBYTE pMsgHdr,LPCBYTE pBody,DWORD cbBody);
	BOOL SubmitFromQueue();
	VOID SerializeToCache(LPBYTE pCache,LPCBYTE pMsgHdr,LPCBYTE pBody,DWORD cbBody);
	BOOL PutIntoMemCache(LPCBYTE pMsgHdr,LPCBYTE pBody,DWORD cbBody);
	BOOL PutIntoExtCache(LPCBYTE pMsgHdr,LPCBYTE pBody,DWORD cbBody);
	BOOL IsLocalBlocked();
protected:
	virtual BOOL OnSubmit(LPCBYTE pMsgHdr,LPCBYTE pBody,DWORD cbBody,BOOL& bWouldBlock) PURE;
protected:
	DWORD m_cbMsgHdr;				// ��Ϣͷ��С
	DWORD m_cbMsgMax;				// ��Ϣ������С
	DWORD m_cbMsgItem;				// ��Ϣ���Ĵ�С
	TClibStr m_strCacheDir;			// ����·��
	LONG m_nEnqueueSpeedLimit;		// �Ŷ��ٶ�����(��/��)
	LONG m_nSubmitSpeedLimit;		// �����ٶ�����(��/��)
	LONG m_nPendingNumLimit;		// δ����������(��)
	BOOL m_bPendingSupported;		// ֧�ְ봦��״̬
	BOOL m_bCacheRestore;			// ����ָ�(��/��)
	BOOL m_bMemCacheUsing;			// ʹ���ڴ滺��(��/��)
	LONG m_nMemCacheSizeLimit;		// �ڴ滺���С����(��)
	BOOL m_bExtCacheUsing;			// ʹ���ⲿ����(��/��)
	LONG m_nExtCacheSizeLimit;		// �ⲿ�����С����(��)
	DWORD m_dwExtCachePerPage;		// �ⲿ����ҳ��С(��)
	LONG m_nResubmitBlock;			// ���ύ���д�С����(��)

	THeapList m_HeapList;			// �ڴ��
	LPBYTE m_pSubmitCache;			// �ύ����
	TListPtr m_lstMemCache;			// �ڴ滺��
	DWORD m_dwNumInExtCache;		// �ⲿ�����е�����
	DWORD m_dwExtFirstPage;			// ��ǰһ��ҳ�����
	DWORD m_dwExtNextPage;			// ����¸�ҳ�����
	TListPtr m_lstExtTempPage;		// ����������ʱҳ

	LONG m_nPendingNum;				// �����е�����
	LONG m_nEnqueuedInSec;			// ��ǰ������ӵ�����
	LONG m_nSubmitedInSec;			// ��ǰ������ӵ�����
	LONG m_nPumpedOutInSec;			// ������ϵ�����(����)

	CLock m_CsSafetyValve;			// ������
};



#endif

