#ifndef __MT__H__
#define __MT__H__

// 无限等待
#ifndef INFINITE
	#define INFINITE 0xFFFFFFFF
#endif

// 单事件
class CLIBMISC_IMP CSingleEvent
{
public:
	CSingleEvent();
	virtual~CSingleEvent();
	BOOL Pulse() { return Signal(FALSE,1); }
	BOOL Signal(BOOL bBroadcast,LONG nAwakeNum=1);
	BOOL IsSignaled(LONG nMicroSeconds);
	BOOL WaitForSignal(LONG nMicroSeconds);
	#if defined(PLATFORM_WINDOWS)
		HANDLE GetEvent() { return m_hEvent; }
	#endif
private:
	#if defined(PLATFORM_WINDOWS)
		CRITICAL_SECTION m_cs;
		HANDLE m_hEvent;
	#else
		pthread_mutex_t m_Mutex;
		pthread_cond_t m_Cond;
	#endif
	LONG m_nSignaled;
};


// 多事件
class CLIBMISC_IMP CMultiEvent
{
public:
	CMultiEvent(LONG nEventNum,BOOL bSystemDrive=FALSE);
	virtual~CMultiEvent();
	BOOL Pulse(LONG nSignalNo) { return Signal(nSignalNo,FALSE,1); }
	BOOL Signal(LONG nSignalNo,BOOL bBroadcast,LONG nAwakeNum=1);
	BOOL IsSignaled(LONG nSignalNo,LONG nMicroSeconds);
	LONG WaitForSingleSignal(LONG nMicroSeconds);
	BOOL WaitForSingleSignal(LONG nSignalNo,LONG nMicroSeconds);
	BOOL WaitForAllSignal(LONG nMicroSeconds);
	LONG WaitForMultiSignal(LONG* pnIndexs,LONG nCount,LONG nMicroSeconds);
	#if defined(PLATFORM_WINDOWS)
		HANDLE GetEventAt(LONG nSignalNo) { return m_ahEvent[nSignalNo]; }
	#endif
private:
	#if defined(PLATFORM_WINDOWS)
		CRITICAL_SECTION m_cs;
		HANDLE m_ahEvent[64];
	#else
		pthread_mutex_t m_Mutex;
		pthread_cond_t m_Cond;
	#endif
	LONG m_nEventNum;
	BOOL m_bSystemDrive;
	LONG m_anSignaled[64];
};





//////////////////////////////////////////////////////////////////////////
// 互斥区(封装)
class CLIBMISC_IMP CLock
{
public:
	CLock()	{ InitializeCriticalSection(&m_cs); }
	~CLock() { DeleteCriticalSection(&m_cs); };
	VOID Lock() { EnterCriticalSection(&m_cs); };
	VOID Unlock() { LeaveCriticalSection(&m_cs); };
private:
	CRITICAL_SECTION m_cs;
};



//////////////////////////////////////////////////////////////////////////
// 自动锁
class CLIBMISC_IMP CAutoLock
{
public:
	CAutoLock(CLock* pLock);
	virtual~CAutoLock();
	VOID PauseLock(CLock* pLock);
	VOID ContinueLock(CLock* pLock);
protected:
	CLock* m_pLock;
};




//////////////////////////////////////////////////////////////////////////
// 并行锁
//		CParallelLock g_ParallelLock(10,1,5000);
//		PLWAITRESULT ePLWaitResult=g_ParallelLock.WaitForParallelEnter();
//		if(ePLWaitResult!=PLW_SUCCESS) return;
//		CParallelAutoLock ParallelAutoLock(&g_ParallelLock);
// 并行锁等待结果
typedef enum enumPLWAITRESULT
{	PLW_SUCCESS,			// 锁成功
	PLW_TIMEOUT,			// 并行锁超时
	PLW_ABORT,				// 并行锁被取消
	PLW_FATALERROR,			// 并行锁冲突
	PLW_QUEUE_OVERFLOW,		// 队列深度满
} PLWAITRESULT;
class CLIBMISC_IMP CParallelLock
{
public:
	CParallelLock(LONG nQueueMax,LONG nParallelMax,LONG nTimeout);
	virtual~CParallelLock();
	PLWAITRESULT WaitForParallelEnter();
	VOID ReleaseParallel();
	VOID AbortAllParallelWaitings();
protected:
	PLWAITRESULT WaitForParallelRelease();
protected:
	CRITICAL_SECTION m_cs;
	LONG m_nQueueMax;
	LONG m_nParallelMax;
	LONG m_nTimeout;
	LONG m_nQueueCount;
	LONG m_nParallelCount;
	CMultiEvent m_ParallelEvent;
};
// 并行自动锁
class CLIBMISC_IMP CParallelAutoLock
{
public:
	CParallelAutoLock(CParallelLock* pLock) { m_pLock=pLock; }
	virtual~CParallelAutoLock() { if(m_pLock!=NULL) m_pLock->ReleaseParallel(); }
protected:
	CParallelLock* m_pLock;
};




//////////////////////////////////////////////////////////////////////////
// 读写锁
class CLIBMISC_IMP CRWLock
{
public:
	CRWLock();
	virtual~CRWLock();
	VOID Lock(BOOL bToWrite);
	VOID Unlock(BOOL bToWrite);
protected:
	typedef TMapDwordPtrToDword LOCKMAP;
protected:
	BOOL m_bWritePriority;
	LOCKMAP m_mapReadLockCount;
	DWORD m_dwReadLockCount;
	LONG m_nWriteTryCount;
	CLock m_LockWrite;
	CSingleEvent m_ReadUnlocker;
	CSingleEvent m_WriteUnlocker;
};


// 读写自动锁
class CLIBMISC_IMP CAutoRWLock
{
public:
	CAutoRWLock(CRWLock* pRWLock,BOOL bToWrite)
		{	m_pRWLock=pRWLock;
			m_bToWrite=bToWrite;
			m_pRWLock->Lock(m_bToWrite);
		}
	virtual~CAutoRWLock()
		{	m_pRWLock->Unlock(m_bToWrite);
		}
protected:
	CRWLock* m_pRWLock;
	BOOL m_bToWrite;
};










// 自动递减计数器
class CLIBMISC_IMP CAutoDecrement
{
public:
	CAutoDecrement(LPLONG pCount) { m_pCount=pCount; }
	virtual~CAutoDecrement() { if(m_pCount!=NULL) InterlockedDecrement(m_pCount); }
protected:
	LPLONG m_pCount;
};

// 自动递增计数器
class CLIBMISC_IMP CAutoIncrement
{
public:
	CAutoIncrement(LPLONG pCount) { m_pCount=pCount; }
	virtual~CAutoIncrement() { if(m_pCount!=NULL) InterlockedIncrement(m_pCount); }
protected:
	LPLONG m_pCount;
};


// 自动标志器
class CLIBMISC_IMP CAutoFlag
{
public:
	CAutoFlag(LPBOOL pbFlag,BOOL bAutoState) { m_pFlag=pbFlag;  m_bAutoState=bAutoState; *m_pFlag=bAutoState; }
	virtual~CAutoFlag() { (*m_pFlag)=!m_bAutoState; }
protected:
	LPBOOL m_pFlag;
	BOOL m_bAutoState;
};








// 线程处理类
class CLIBMISC_IMP CThreadCreator
{
public:
	CThreadCreator();
	virtual~CThreadCreator();
public:
	class CLIBMISC_IMP CThreadContext
	{
	public:
		CThreadContext(CThreadCreator* pCreator,UINT nID);
		virtual~CThreadContext();
		UINT GetID() const { return m_nID; }
		BOOL SleepAndWaitQuit(DWORD dwTimeout=INFINITE);
		VOID QuitThread();
	protected:
		static HRTHREAD WINAPI RoutineThreadMain(LPVOID lpParam);
	protected:
		CThreadCreator* m_pCreator;		// 线程容器
		UINT			m_nID;			// 线程ID
		HTHREAD			m_hThread;		// 线程句柄
		THREADID		m_nThreadId;	// 线程ID
		CSingleEvent	m_ThreadQuited;	// 退出线程(完成)
		CSingleEvent	m_ThreadQuit;	// 退出线程	
	};
protected:
	friend class CThreadContext;
	CThreadContext* CreateThread(UINT nID);
	VOID DestroyThread(UINT nID);
	VOID DestroyAllThread();
	virtual BOOL ThreadMain(CThreadContext* pContext) PURE;
protected:
	TListPtr m_lstThreads;
};

#endif
