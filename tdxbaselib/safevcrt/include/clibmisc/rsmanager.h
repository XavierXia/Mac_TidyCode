//////////////////////////////////////////////////////////////////////////
// 说明: 当前类用于实现全局资源管理,在复合服务器中,内存管理和线程管理都需要统一进行
//		 以避免系统使用上独立模块使用更多的内存
// 
#ifndef __RS_MANAGER__H__
#define __RS_MANAGER__H__


// 1.线程首先作为系统共享资源和连接一样
// 2.除IOCP模式的服务器外(事务,TCP),也应该其他的连接管理器(流式,TCP),其他报文(UDP)等,所以内存资源和


// 1.线程管理类,通过这个类分配线程,并管理线程
// 2.内存管理类,通过这个类分配内存,并管理内存
// 3.线程和内存这些资源也需要可管理特性
// 4.日志对象(磁盘对象)也需要统一

// 这些对象都需要早于服务启动的时候启动,并支持多线程可监控可管理特性
// 这会使得线程池的


// 系统资源管理(磁盘和网络,SOCKET资源)
class CLIBMISC_IMP CSysRSManager
{
public:
	CSysRSManager();
	virtual~CSysRSManager();
};





// 内存池管理模块
class CLIBMISC_IMP CHeapPoolManager
{
public:
	CHeapPoolManager();
	virtual~CHeapPoolManager();
};



// 基本线程数据
typedef struct tagTHDINF
{	HTHREAD			m_hHandle;						// 线程句柄
	BOOL			m_bQueueAborted;				// 线程退出信号
	systm_t			m_tLastIdle;					// 上次空闲时间(线程)
	THREADID		m_nId;							// 线程ID
	BOOL			m_bBusy;						// 是否繁忙(线程)
	systm_t			m_tLastActive;					// 上次激活时间(线程)
	systm_t			m_tBusinessCreated;				// 事务创建时间(解包前)
	systm_t			m_tBusinessEntry;				// 事务进入处理时间(解包后)
	WORD			m_wCmdNo;						// 当前事务的协议号
	CHAR			m_szCmdDesc[64];				// 当前事务的描述
	DWORD			m_dwInWaitTime;					// 在处理上消耗的时间(毫秒)
	DWORD			m_dwInProcTime;					// 在处理上消耗的时间(毫秒)
	DWORD			m_dwInApiTime;					// 在API上消耗的时间(毫秒)
	DWORD			m_dwHisBusinessNum;				// 累计处理事务数
	CHAR			m_szComment[64];				// 线程备注信息
} THDINF,*LPTHDINF;


// 线程池管理
class CLIBMISC_IMP CThreadPoolManager
{
public:
	CThreadPoolManager();
	virtual~CThreadPoolManager();
};


#endif
