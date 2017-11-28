#ifndef __SAFE_TYVALVE__H__
#define __SAFE_TYVALVE__H__
#if _MSC_VER > 1000
#pragma once
#endif

// 减压阀
class CLIBMISC_IMP CSafetyValve
{
public:
	CSafetyValve(DWORD cbMsgHdr,DWORD cbMsgMax,BOOL bPoolOn);
	virtual~CSafetyValve(){ Stop(); }
	// 参数设置
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
	// 操作
	BOOL Start();
	VOID Stop();
	BOOL Enqueue(LPCBYTE pMsgHdr,LPCBYTE pBody,DWORD cbBody);
	// 定时处理和事件响应
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
	DWORD m_cbMsgHdr;				// 消息头大小
	DWORD m_cbMsgMax;				// 消息体最大大小
	DWORD m_cbMsgItem;				// 消息正文大小
	TClibStr m_strCacheDir;			// 缓冲路径
	LONG m_nEnqueueSpeedLimit;		// 排队速度限制(条/秒)
	LONG m_nSubmitSpeedLimit;		// 处理速度限制(条/秒)
	LONG m_nPendingNumLimit;		// 未定处理限制(条)
	BOOL m_bPendingSupported;		// 支持半处理状态
	BOOL m_bCacheRestore;			// 缓存恢复(是/否)
	BOOL m_bMemCacheUsing;			// 使用内存缓冲(是/否)
	LONG m_nMemCacheSizeLimit;		// 内存缓冲大小限制(条)
	BOOL m_bExtCacheUsing;			// 使用外部缓冲(是/否)
	LONG m_nExtCacheSizeLimit;		// 外部缓冲大小限制(条)
	DWORD m_dwExtCachePerPage;		// 外部缓冲页大小(条)
	LONG m_nResubmitBlock;			// 重提交序列大小限制(条)

	THeapList m_HeapList;			// 内存池
	LPBYTE m_pSubmitCache;			// 提交缓冲
	TListPtr m_lstMemCache;			// 内存缓冲
	DWORD m_dwNumInExtCache;		// 外部缓存中的条数
	DWORD m_dwExtFirstPage;			// 最前一个页面序号
	DWORD m_dwExtNextPage;			// 最后下个页面序号
	TListPtr m_lstExtTempPage;		// 二级缓冲临时页

	LONG m_nPendingNum;				// 处理中的条数
	LONG m_nEnqueuedInSec;			// 当前秒内入队的条数
	LONG m_nSubmitedInSec;			// 当前秒内入队的条数
	LONG m_nPumpedOutInSec;			// 处理完毕的条数(秒内)

	CLock m_CsSafetyValve;			// 队列锁
};



#endif

